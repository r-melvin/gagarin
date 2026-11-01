#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original. Reimplemented from the published idea of cross-build pairing (strings, then
# vtables, then call order, repeated to a fixed point); no code taken from other projects. Reads the
# developer's own images; writes addresses and numbers only, no retail bytes and no string contents.
"""twinpair: pair Yuri's Revenge functions with their Red Alert 2 twins to a fixed point.

    GAMEMD_BINARY=gamemd.exe GAG_RA2_BINARY=game.exe twinpair.py [--out scripts/data/twin_map.json]
                                                    [--csv pairs.csv] [--old old_pairs.csv]

Both images get the same function discovery (x86scan.discover from the entry point, padding-aligned
starts, RTTI vtable slots and direct calls; the YR side also takes the census starts). Then:

  1. strings    a string a function of each image references, and no other function of that image,
                pairs the two functions (votes when a function has several such strings)
  2. vtables    same RTTI class, same sub-object offset, same slot index (votes; a pair whose code
                is nothing alike is kept apart as weak and not used)
  3. hash       relocation-masked code hashes that are unique among the still-unpaired functions of
                both sides; groups of several are split by position between monotone anchors
  4. callees    paired functions with the same number of direct calls pair their callees in order
  repeated until nothing new pairs.

Output scripts/data/twin_map.json: one row per pair (yr_addr, ra2_addr, method, byte_identical,
similarity), the coverage, per-method agreement with independent evidence, and the conflicts
(including against the earlier ra2diff pairs.csv, which this tool supersedes). With --csv the same
pairs are written in the old pairs.csv layout that permute_queue.py reads.
byte_identical means the relocation-masked code is equal (same source, same compiler output).
"""
import argparse
import bisect
import collections
import csv
import difflib
import hashlib
import json
import os
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import x86scan as X  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
YR_SHA256 = "1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c"
RA2_SHA256 = "6fc4b410f8841ba3ad6c57b59fccae65f58a8871d86750af3c1e2d5a7c5ad39d"
SCHEMA = "gagarin/twin_map/1"
MIN_STRING = 5
MIN_HASH_BYTES = 6
WEAK_SIM = 0.35
NEAR_SIM = 0.9
VTABLE_SIM = 0.5
SIM_TOKEN_CAP = 700


class Fn:
    __slots__ = ("addr", "end", "toks", "hash", "shape", "strs", "calls", "nbytes")


def build(img, extra_roots=()):
    """Discover and summarise the functions of one image. Returns (funcs, vtables, discovery info)."""
    vt = X.rtti_vtables(img)
    roots = set(extra_roots)
    roots.add(img.entry)
    roots.update(X.padding_starts(img))
    for slots in vt.values():
        roots.update(slots)
    walks, starts, _ = X.discover(img, sorted(roots))
    funcs = {}
    for a, w in walks.items():
        if w.bad or w.suspicious or w.out_of_text or not w.insns:
            continue
        f = Fn()
        f.addr, f.end = a, w.end
        f.toks = X.mask_bytes(img, w)
        tbl = b"".join(t.to_bytes(4, "little") for tv, ts, bt, bc in w.tables for t in [x - a & 0xFFFFFFFF for x in ts])
        h = hashlib.md5(b"".join(f.toks) + b"|" + tbl)
        f.hash = h.digest()
        f.nbytes = sum(len(t) for t in f.toks)
        f.shape = hashlib.md5(bytes(v for a2 in sorted(w.insns) for v in (w.insns[a2][4] & 0xFF, w.insns[a2][0]))).digest()
        ss = set()
        for _, v in w.refs:
            s = img.cstring(v, minlen=MIN_STRING)
            if s:
                ss.add(s)
        f.strs = frozenset(ss)
        f.calls = tuple(t for _, t in sorted(w.calls))
        funcs[a] = f
    return funcs, vt, dict(starts=len(starts), walks=len(walks), kept=len(funcs))


def similarity(a, b):
    """1.0 when the masked code is equal, else a ratio over the instruction token sequences."""
    if a.hash == b.hash:
        return 1.0
    x, y = a.toks, b.toks
    if max(len(x), len(y)) > 4 * min(len(x), len(y)) + 4:
        return 0.0
    if len(x) > SIM_TOKEN_CAP or len(y) > SIM_TOKEN_CAP:
        cx, cy = collections.Counter(x), collections.Counter(y)
        return round(2.0 * sum((cx & cy).values()) / (len(x) + len(y)), 4)
    sm = difflib.SequenceMatcher(None, x, y, autojunk=False)
    if sm.real_quick_ratio() < WEAK_SIM:
        return round(sm.real_quick_ratio() * 0.5, 4)
    return round(sm.ratio(), 4)


class Pairing:
    def __init__(self, yf, rf, yvt, rvt):
        self.yf, self.rf = yf, rf
        self.y2r, self.r2y, self.method = {}, {}, {}
        self.sim = {}
        self.conflicts = []
        self.weak = []
        self.log = []
        self._cdis = set()
        self.yslot = collections.defaultdict(set)   # y func -> {(cls, off, i)}
        self.rslot = collections.defaultdict(set)
        self.yslot_inv = collections.defaultdict(set)   # (cls, off, i) -> y funcs
        for (cls, off), slots in yvt.items():
            for i, t in enumerate(slots):
                self.yslot[t].add((cls, off, i))
                self.yslot_inv[(cls, off, i)].add(t)
        self.rslot_inv = collections.defaultdict(set)
        for (cls, off), slots in rvt.items():
            for i, t in enumerate(slots):
                self.rslot[t].add((cls, off, i))
                self.rslot_inv[(cls, off, i)].add(t)

    def sim_of(self, y, r):
        k = (y, r)
        if k not in self.sim:
            self.sim[k] = similarity(self.yf[y], self.rf[r])
        return self.sim[k]

    def add(self, y, r, method):
        if y in self.y2r or r in self.r2y or y not in self.yf or r not in self.rf:
            return False
        self.y2r[y], self.r2y[r], self.method[y] = r, y, method
        return True

    def _vote_pairs(self, votes, method, min_sim=0.0, record_weak=False):
        """votes {(y, r): n}. Pair where each side's single best candidate is the other (ties skipped)."""
        by_y, by_r = collections.defaultdict(list), collections.defaultdict(list)
        # a candidate whose code differs is vetoed while either side still has an unpaired
        # function with byte-identical masked code: the identical twin wins (hash passes pair it)
        yh = {f.hash for a, f in self.yf.items() if a not in self.y2r and f.nbytes >= MIN_HASH_BYTES}
        rh = {f.hash for a, f in self.rf.items() if a not in self.r2y and f.nbytes >= MIN_HASH_BYTES}
        for (y, r), n in votes.items():
            if y in self.y2r or r in self.r2y or y not in self.yf or r not in self.rf:
                continue
            fy, fr = self.yf[y], self.rf[r]
            if fy.hash != fr.hash and (fy.hash in rh or fr.hash in yh):
                continue
            by_y[y].append((n, r))
            by_r[r].append((n, y))
        added = 0
        for y, cands in by_y.items():
            cands.sort(reverse=True)
            if len(cands) > 1 and cands[0][0] == cands[1][0]:
                self.conflicts.append(dict(kind="%s-tie" % method, yr=y, ra2=sorted({c[1] for c in cands if c[0] == cands[0][0]})))
                continue
            r = cands[0][1]
            rc = sorted(by_r[r], reverse=True)
            if len(rc) > 1 and rc[0][0] == rc[1][0]:
                continue
            if rc[0][1] != y:
                self.conflicts.append(dict(kind="%s-contested" % method, yr=y, ra2=r, other_yr=rc[0][1]))
                continue
            if len(cands) > 1:
                self.conflicts.append(dict(kind="%s-multi" % method, yr=y, ra2=r, rivals=sorted(c[1] for c in cands[1:])))
            if min_sim and self.sim_of(y, r) < min_sim:
                if record_weak:
                    self.weak.append((y, r, method))
                continue
            added += self.add(y, r, method)
        return added

    def by_strings(self):
        gy, gr = collections.defaultdict(set), collections.defaultdict(set)
        for a, f in self.yf.items():
            for s in sorted(f.strs):
                gy[s].add(a)
        for a, f in self.rf.items():
            for s in sorted(f.strs):
                gr[s].add(a)
        votes = collections.Counter()
        for s, ys in sorted(gy.items()):
            rs = gr.get(s)
            if rs and len(ys) == 1 and len(rs) == 1:
                votes[(next(iter(ys)), next(iter(rs)))] += 1
        n = self._vote_pairs(votes, "string")
        self.log.append(("string", n))
        return n

    def by_vtables(self):
        votes = collections.Counter()
        for key, ys in self.yslot_inv.items():
            rs = self.rslot_inv.get(key)
            if not rs:
                continue
            for y in ys:
                for r in rs:
                    votes[(y, r)] += 1
        n = self._vote_pairs(votes, "vtable", min_sim=VTABLE_SIM, record_weak=True)
        self.log.append(("vtable", n))
        return n

    def _groups(self, key):
        gy, gr = collections.defaultdict(list), collections.defaultdict(list)
        for a, f in self.yf.items():
            if a not in self.y2r and f.nbytes >= MIN_HASH_BYTES:
                gy[key(f)].append(a)
        for a, f in self.rf.items():
            if a not in self.r2y and f.nbytes >= MIN_HASH_BYTES:
                gr[key(f)].append(a)
        return gy, gr

    def by_hash(self):
        gy, gr = self._groups(lambda f: f.hash)
        n = 0
        for k, ys in gy.items():
            rs = gr.get(k)
            if rs and len(ys) == 1 and len(rs) == 1:
                n += self.add(ys[0], rs[0], "hash")
        self.log.append(("hash", n))
        return n

    def anchors(self):
        """Longest chain of existing pairs that is increasing in both address spaces."""
        seq = sorted((r, y) for y, r in self.y2r.items())
        tails, tidx, prev = [], [], [-1] * len(seq)
        for i, (_, y) in enumerate(seq):
            j = bisect.bisect_left(tails, y)
            if j == len(tails):
                tails.append(y)
                tidx.append(i)
            else:
                tails[j] = y
                tidx[j] = i
            prev[i] = tidx[j - 1] if j else -1
        out, i = [], tidx[-1] if tidx else -1
        while i >= 0:
            out.append(seq[i])
            i = prev[i]
        return [(y, r) for r, y in out[::-1]]

    def by_hash_anchored(self):
        """Equal-hash groups of several functions: pair by position between anchors, both ways unique."""
        gy, gr = self._groups(lambda f: f.hash)
        an = self.anchors()
        ay = [y for y, _ in an]
        ar = sorted(r for _, r in an)
        ar_by_y = [r for _, r in an]
        n = 0
        for k, ys in gy.items():
            rs = gr.get(k)
            if not rs or (len(ys) == 1 and len(rs) == 1):
                continue
            for y in ys:
                if y in self.y2r:
                    continue
                i = bisect.bisect_left(ay, y)
                rlo = ar_by_y[i - 1] if i else 0
                rhi = ar_by_y[i] if i < len(an) else 1 << 32
                cand = [r for r in rs if r not in self.r2y and rlo < r < rhi]
                if len(cand) != 1:
                    continue
                r = cand[0]
                j = bisect.bisect_left(ar_by_y, r)
                ylo = ay[j - 1] if j else 0
                yhi = ay[j] if j < len(an) else 1 << 32
                back = [yy for yy in ys if yy not in self.y2r and ylo < yy < yhi]
                if len(back) == 1:
                    n += self.add(y, r, "hash-anchor")
        self.log.append(("hash-anchor", n))
        return n

    def by_shape(self, min_sim=NEAR_SIM):
        """Opcode-and-length signature unique among the unpaired of both sides, and the code is close."""
        gy, gr = self._groups(lambda f: f.shape)
        n = 0
        for k, ys in gy.items():
            rs = gr.get(k)
            if rs and len(ys) == 1 and len(rs) == 1 and self.sim_of(ys[0], rs[0]) >= min_sim:
                n += self.add(ys[0], rs[0], "shape")
        self.log.append(("shape", n))
        return n

    def by_window(self, min_sim=NEAR_SIM, max_cells=40000):
        """Unpaired functions between two consecutive anchors: best-similarity greedy pairing."""
        an = self.anchors()
        uy = sorted(a for a in self.yf if a not in self.y2r)
        ur = sorted(a for a in self.rf if a not in self.r2y)
        bounds = [(0, 0)] + an + [(1 << 32, 1 << 32)]
        n = 0
        for (y0, r0), (y1, r1) in zip(bounds, bounds[1:]):
            cy = uy[bisect.bisect_right(uy, y0):bisect.bisect_left(uy, y1)]
            cr = ur[bisect.bisect_right(ur, r0):bisect.bisect_left(ur, r1)]
            if not cy or not cr or len(cy) * len(cr) > max_cells:
                continue
            sc = []
            for y in cy:
                ly = len(self.yf[y].toks)
                for r in cr:
                    lr = len(self.rf[r].toks)
                    if min(ly, lr) < 0.85 * max(ly, lr) or max(ly, lr) < 4:
                        continue
                    s = self.sim_of(y, r)
                    if s >= min_sim:
                        sc.append((s, y, r))
            sc.sort(reverse=True)
            for s, y, r in sc:
                n += self.add(y, r, "window-sim")
        self.log.append(("window-sim", n))
        return n

    def by_callees(self, min_sim):
        n = 0
        changed = True
        while changed:
            changed = False
            for y, r in list(self.y2r.items()):
                cy, cr = self.yf[y].calls, self.rf[r].calls
                if len(cy) != len(cr) or not cy:
                    continue
                if self.sim_of(y, r) < min_sim:
                    continue
                pending = []
                ok = True
                for a, b in zip(cy, cr):
                    if a in self.y2r or b in self.r2y:
                        if self.y2r.get(a) != b:
                            ok = False          # the call sequences disagree with an existing pair
                        continue
                    if a in self.yf and b in self.rf:
                        pending.append((a, b))
                if not ok:
                    if (y, r) not in self._cdis:
                        self._cdis.add((y, r))
                        self.conflicts.append(dict(kind="callee-order-disagrees", yr=y, ra2=r))
                    continue
                for a, b in pending:
                    if a in self.y2r or b in self.r2y:
                        continue
                    if self.sim_of(a, b) >= WEAK_SIM:
                        if self.add(a, b, "callee-order"):
                            n += 1
                            changed = True
        self.log.append(("callee-order", n))
        return n

    def run(self, verbose=False):
        self.by_hash()
        self.by_hash_anchored()
        self.by_strings()
        self.by_vtables()
        rounds = 0
        while True:
            rounds += 1
            before = len(self.y2r)
            self.by_hash()
            self.by_callees(0.8)
            self.by_hash_anchored()
            self.by_vtables()
            self.by_callees(0.5)
            self.by_shape()
            self.by_window()
            if verbose:
                print("round %d: %d pairs" % (rounds, len(self.y2r)), file=sys.stderr)
            if len(self.y2r) == before or rounds >= 12:
                break
        return rounds


def agreement(p):
    """Per method: how many pairs have independent evidence (shared string, same vtable slot) and agree."""
    out = collections.defaultdict(lambda: collections.Counter())
    for y, r in p.y2r.items():
        m = p.method[y]
        fy, fr = p.yf[y], p.rf[r]
        c = out[m]
        c["pairs"] += 1
        if fy.strs and fr.strs:
            c["string_agree" if fy.strs & fr.strs else "string_disagree"] += 1
        sy, sr = p.yslot.get(y), p.rslot.get(r)
        if sy and sr:
            c["vtable_agree" if sy & sr else "vtable_disagree"] += 1
    return {m: dict(c) for m, c in out.items()}


def kind_of(p, y):
    r = p.y2r[y]
    s = p.sim_of(y, r)
    if p.yf[y].hash == p.rf[r].hash:
        return "exact"
    return "near" if s >= 0.9 else "changed"


def load_old(path):
    """Old pairs.csv (ra2diff): {yr_addr: (ra2_addr, kind, similarity)}."""
    out = {}
    with open(path, newline="") as fh:
        for row in csv.DictReader(fh):
            try:
                out[int(row["yr_addr"], 16)] = (int(row["ra2_addr"], 16), row.get("kind", ""), float(row.get("similarity") or 0))
            except (KeyError, ValueError):
                continue
    return out


def load_twins(path=None):
    """Reader used by dispatch/permute_queue. {yr_addr: (kind, similarity, ra2_addr)} from
    twin_map.json (preferred) or a pairs.csv. kind is exact/near/changed."""
    p = Path(path) if path else ROOT / "scripts" / "data" / "twin_map.json"
    if not p.exists():
        return {}
    if p.suffix == ".csv":
        return {y: (k, s, r) for y, (r, k, s) in load_old(p).items()}
    d = json.loads(p.read_text())
    return {int(row["yr_addr"], 16): (row["kind"], row["similarity"], int(row["ra2_addr"], 16)) for row in d["pairs"]}


def twin_label(kind):
    """The worklist's ra2_twin vocabulary: identical / near / changed / none."""
    return {"exact": "identical", "normalised": "identical", "near": "near"}.get(kind, "changed" if kind else "none")


def compare_old(p, old):
    new = {y: r for y, r in p.y2r.items()}
    agree = [y for y in new if y in old and old[y][0] == new[y]]
    diff = [y for y in new if y in old and old[y][0] != new[y]]
    only_new = [y for y in new if y not in old]
    only_old = [y for y in old if y not in new]
    ident_old = {y for y, (r, k, s) in old.items() if k == "exact" and s >= 1.0}
    rows = []
    for y in sorted(diff):
        rows.append(dict(yr=y, ra2_new=new[y], ra2_old=old[y][0], new_method=p.method[y], new_sim=p.sim_of(y, new[y]),
                         old_kind=old[y][1], old_sim=old[y][2]))
    return dict(old_pairs=len(old), new_pairs=len(new), agree=len(agree), conflict=len(diff), only_new=len(only_new),
                only_old=len(only_old), old_exact_pairs=len(ident_old),
                old_exact_agree=len([y for y in agree if y in ident_old]),
                old_exact_conflict=len([y for y in diff if y in ident_old])), rows


def to_hex(a):
    return "0x%X" % a


def write_csv(path, p, yr_names=None):
    with open(path, "w", newline="") as fh:
        w = csv.writer(fh)
        w.writerow(["ra2_addr", "yr_addr", "size_ra2", "size_yr", "kind", "similarity", "yr_manifest_status", "yr_name", "class"])
        for y, r in sorted(p.y2r.items(), key=lambda kv: kv[1]):
            w.writerow([to_hex(r), to_hex(y), p.rf[r].end - r, p.yf[y].end - y, kind_of(p, y), p.sim_of(y, r), "", "", ""])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--yr", default=os.environ.get("GAMEMD_BINARY"))
    ap.add_argument("--ra2", default=os.environ.get("GAG_RA2_BINARY"))
    ap.add_argument("--out", default=str(ROOT / "scripts" / "data" / "twin_map.json"))
    ap.add_argument("--csv", help="also write the old pairs.csv layout")
    ap.add_argument("--old", default=os.environ.get("GAG_RA2_PAIRS"), help="earlier pairs.csv to compare against")
    ap.add_argument("--census", default=str(ROOT / "scripts" / "data" / "function_extents.json"))
    ap.add_argument("-v", "--verbose", action="store_true")
    a = ap.parse_args(argv)
    if not a.yr or not a.ra2:
        raise SystemExit("set GAMEMD_BINARY and GAG_RA2_BINARY (or --yr/--ra2)")
    t0 = time.time()
    yimg, rimg = X.Image(a.yr), X.Image(a.ra2)
    if yimg.sha256 != YR_SHA256:
        raise SystemExit("%s: not the pinned gamemd.exe (sha256 %s)" % (a.yr, yimg.sha256))
    census = []
    if os.path.exists(a.census):
        census = [int(e[0], 16) for e in json.load(open(a.census))["entries"]]
    yf, yvt, yinfo = build(yimg, census)
    rf, rvt, rinfo = build(rimg)
    if a.verbose:
        print("yr %s ra2 %s (%.0fs)" % (yinfo, rinfo, time.time() - t0), file=sys.stderr)
    p = Pairing(yf, rf, yvt, rvt)
    rounds = p.run(a.verbose)
    kinds = collections.Counter(kind_of(p, y) for y in p.y2r)
    meth = collections.Counter(p.method.values())
    out = dict(
        schema=SCHEMA,
        yr_sha256=yimg.sha256, ra2_sha256=rimg.sha256, ra2_is_known_build=rimg.sha256 == RA2_SHA256,
        method="strings, RTTI vtable slots, masked-byte hashes and callee order to a fixed point (scripts/agent_tools/twinpair.py)",
        coverage=dict(yr_functions=len(yf), ra2_functions=len(rf), pairs=len(p.y2r), rounds=rounds,
                      yr_paired_pct=round(100.0 * len(p.y2r) / max(1, len(yf)), 2),
                      ra2_paired_pct=round(100.0 * len(p.y2r) / max(1, len(rf)), 2),
                      by_method=dict(meth), by_kind=dict(kinds), pass_log=p.log,
                      census_functions_paired=sum(1 for c in census if c in p.y2r), census_functions=len(census)),
        agreement=agreement(p),
        conflicts=dict(internal=collections.Counter(c["kind"] for c in p.conflicts), weak_vtable_pairs=len(p.weak)),
        pairs=[dict(yr_addr=to_hex(y), ra2_addr=to_hex(r), method=p.method[y], byte_identical=p.yf[y].hash == p.rf[r].hash,
                    similarity=p.sim_of(y, r), kind=kind_of(p, y))
               for y, r in sorted(p.y2r.items())],
    )
    out["conflicts"]["internal"] = dict(out["conflicts"]["internal"])
    old_path = a.old
    if not old_path:
        for c in (os.path.join(os.environ.get("GAG_SCRATCH_ROOT", ""), "ra2diff/pairs.csv"),
                  str(ROOT.parent / "backups" / "int-evidence" / "ra2diff" / "pairs.csv"),
                  str(ROOT.parent.parent / "backups" / "int-evidence" / "ra2diff" / "pairs.csv"),
                  "/home/richard/Projects/backups/int-evidence/ra2diff/pairs.csv"):
            if os.path.exists(c):
                old_path = c
                break
    if old_path and os.path.exists(old_path):
        summ, rows = compare_old(p, load_old(old_path))
        out["versus_old_pairs_csv"] = dict(summ, source=os.path.basename(os.path.dirname(old_path)) + "/" + os.path.basename(old_path),
                                          conflict_rows=[dict(yr_addr=to_hex(x["yr"]), ra2_new=to_hex(x["ra2_new"]), ra2_old=to_hex(x["ra2_old"]),
                                                              new_method=x["new_method"], new_similarity=x["new_sim"], old_kind=x["old_kind"],
                                                              old_similarity=x["old_sim"]) for x in rows])
    Path(a.out).write_text(json.dumps(out, indent=1) + "\n")
    if a.csv:
        write_csv(a.csv, p)
    c = out["coverage"]
    print("pairs %d of YR %d (%.1f%%) / RA2 %d (%.1f%%); kinds %s; methods %s" % (
        c["pairs"], c["yr_functions"], c["yr_paired_pct"], c["ra2_functions"], c["ra2_paired_pct"], c["by_kind"], c["by_method"]))
    if "versus_old_pairs_csv" in out:
        v = out["versus_old_pairs_csv"]
        print("vs old: agree %d conflict %d only-new %d only-old %d" % (v["agree"], v["conflict"], v["only_new"], v["only_old"]))
    print("wrote %s (%.0fs)" % (a.out, time.time() - t0))
    return 0


if __name__ == "__main__":
    sys.exit(main())

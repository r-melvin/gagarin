#!/usr/bin/env python3
"""pktrebase.py: re-apply a READY packet onto the current tip, mechanically doing what the
b7 lander did by hand for every wave-6 packet.

    pktrebase.py READY_DIR --rev TIP [--repo R] [--out DIR] [--rekey MAP.json]...
                 [--gates inc|none] [--jobs 4] [--keep] [--no-merge]

  1. scratch worktree at TIP (disk-backed, see dlib.SCRATCH);
  2. the patch is split per file: manifest hunks dropped; hunks on a file that the
     migration/renames moved are re-targeted to where its manifest rows now live
     (base manifest -> tip manifest), applied with `patch -F3`; the rest `git apply --3way`;
     hunks that still fail are reported with their .rej text, per file and hunk;
  3. a NEW .cpp whose rows lie in an already-migrated original TU window is MERGED into
     that TU file in ascending retail address order (preamble hoisted, includes
     rewritten, provenance tags joined; bodies never rewritten). Rows the tip manifest
     already holds (initialisers placed by the migration) are dropped from the file and
     the delta, and listed;
  4. known re-key maps (old mangled symbol -> new) are applied to delta rows and symbol
     maps; rows whose symbol the compiled object does not define are re-keyed to the
     unique object symbol with the same ?name@Class@@ prefix (and listed), else reported;
  5. the delta is merged into the tip manifest with landlib's collision checks;
  6. every matched row is proved: raw_match, then strict verify_relocations with the
     packet maps + the central bindings (if present) + bindings derived from symbol names,
     the retail IAT and $L positions; the derived map is written beside the packet;
  7. optional incremental gates (land/gates.py --mode inc) on the result;
  8. the rebased packet is written to --out (default <packet>/../REBASED): patch.diff
     against TIP, manifest_delta.json (re-pointed, sorted), symbol maps, README.md with the
     proposed message amended by one sentence per merge, base_sha, report.json.

Exit 0 only if every step succeeded with no conflicts; 2 = conflicts reported (the
rebased output is still written for inspection); 1 = packet unusable.
"""
import argparse
import concurrent.futures as cf
import json
import os
import re
import shutil
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dlib as D  # noqa: E402
import landlib as L  # noqa: E402
import cppsplit  # noqa: E402

REKEY_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "rekeys")


def say(*a):
    print(*a, flush=True)


class Rebase:
    def __init__(self, packet, repo, rev, out, jobs, rekey_files, keep, merge=True):
        self.p = packet
        self.repo = os.path.abspath(repo)
        self.tip = L.rev_parse(self.repo, rev)
        self.out = out
        self.jobs = jobs
        self.keep = keep
        self.do_merge = merge
        self.report = dict(packet=packet.name, tip=self.tip, remapped=[], merged=[], dropped_rows=[], rekeyed=[],
                           conflicts=[], derived_bindings={}, unbound=[], notes=[], secs={})
        self.rekeys = {}
        for f in sorted(rekey_files):
            d = D.read_json(f)
            if isinstance(d, dict):
                self.rekeys.update({k: v for k, v in d.items() if isinstance(v, str)})
                for k in d:
                    why = D.guard_key_problem(k)
                    if why:
                        say("  warning: rekey file %s: %s" % (os.path.basename(f), why))
        self.tree = D.Tree(self.repo, self.tip)
        self.work = D.scratch_dir("pktrebase_%s_" % packet.name)
        self.wt = os.path.join(self.work, "wt")
        self.ok = True

    def conflict(self, kind, msg, **kw):
        self.ok = False
        self.report["conflicts"].append(dict(kind=kind, msg=msg, **kw))
        say("  CONFLICT %s: %s" % (kind, msg))

    # ------------------------------------------------------------ setup
    def setup(self):
        D.add_worktree(self.repo, self.wt, self.tip)
        self.ops = D.parse_delta(self.p.delta())
        self.rows = [r for _, r, _ in self.ops]
        self.diffs = [d for d in D.split_patch(open(self.p.patch, errors="replace").read()) if d.path != D.MANIFEST]
        self.base = self.p.base_sha()
        self.base_man = None
        if self.base:
            try:
                self.base_man = json.loads(L.git(self.repo, "show", "%s:%s" % (self.base, D.MANIFEST)))
            except Exception:
                self.report["notes"].append("base sha %s not in the repo; moved-file detection limited" % self.base)

    def cleanup(self):
        if self.keep:
            say("kept worktree", self.wt)
            return
        D.remove_worktree(self.repo, self.wt)
        D.remove_dir(self.work)

    # ------------------------------------------------------------ classify + apply
    def dest_of_moved(self, old_path):
        """Where the rows of a packet-base TU live at the tip (unique file or None)."""
        if not self.base_man:
            return None, []
        dests = {}
        for r in self.base_man:
            if r["tu"] == old_path:
                cur = self.tree.by_addr.get(D.hx(r["addr"]))
                if cur:
                    dests.setdefault(cur["tu"], []).append(r["addr"])
        if len(dests) == 1:
            return next(iter(dests)), []
        return None, sorted(dests.items())

    def apply(self):
        new_cpps = {d.path: d for d in self.diffs if d.is_new and d.path.lower().endswith(L.SRC_EXT) and not d.path.lower().endswith(".asm")}
        self.merge_plan = {}       # src path -> dest TU
        if self.do_merge:
            for path in new_cpps:
                dests = {}
                for r in self.rows:
                    if r.get("tu") == path:
                        dest = self.tree.tu_for_addr(D.hx(r["addr"]))
                        dests.setdefault(dest, []).append(r["addr"])
                real = {k: v for k, v in dests.items() if k}
                if not real:
                    continue
                if len(dests) > 1:
                    self.conflict("merge-split", "%s rows fall in several TU windows: %s" % (
                        path, {k or "(none)": v[:3] for k, v in dests.items()}), file=path)
                    continue
                self.merge_plan[path] = next(iter(real))
        direct, moved = [], []
        for d in self.diffs:
            if d.path in self.merge_plan:
                continue
            if d.mode_symlink:
                self.conflict("symlink", "patch touches a symlink: " + d.path, file=d.path)
                continue
            if not d.is_new and d.path not in self.tree.paths:
                dest, multi = self.dest_of_moved(d.path)
                if dest:
                    moved.append((d, dest))
                else:
                    self.conflict("gone", "%s no longer exists at the tip%s" % (
                        d.path, (" and its rows are spread over %s" % [k for k, _ in multi]) if multi else " (no manifest rows to follow)"), file=d.path)
                continue
            if d.is_new and d.path in self.tree.paths:
                self.conflict("exists", "%s already exists at the tip" % d.path, file=d.path)
                continue
            direct.append(d)
        # direct group: one 3-way apply, fall back per file to isolate failures
        if direct:
            r = self.git_apply("".join(d.text for d in direct))
            if r.returncode:
                L.git(self.wt, "reset", "-q", "--hard", self.tip)
                for d in direct:
                    r = self.git_apply(d.text)
                    if r.returncode:
                        if d.path in self.tree.paths:
                            L.git(self.wt, "reset", "-q", "--", d.path, check=False)
                            L.git(self.wt, "checkout", "-q", "--", d.path, check=False)
                        else:
                            L.git(self.wt, "rm", "-q", "-f", "--cached", "--", d.path, check=False)
                            try:
                                os.unlink(os.path.join(self.wt, d.path))
                            except OSError:
                                pass
                        rej = self.reject_text(d)
                        self.conflict("apply", "%s: %s" % (d.path, (r.stderr.strip().splitlines() or ["?"])[0][:200]), file=d.path, rejects=rej)
        for d, dest in moved:
            body = d.text[d.text.index("\n--- ") + 1:]
            body = body.replace("--- a/" + d.path, "--- a/" + dest, 1).replace("+++ b/" + d.path, "+++ b/" + dest, 1)
            r = subprocess.run(["patch", "-p1", "-F3", "--no-backup-if-mismatch", "-r", "-", "-s"], cwd=self.wt, input=body, text=True, capture_output=True)
            if r.returncode:
                L.git(self.wt, "checkout", "-q", "--", dest)
                self.conflict("remap", "%s -> %s: hunks do not apply: %s" % (d.path, dest, (r.stdout + r.stderr).strip()[:300]), file=d.path, dest=dest)
            else:
                L.git(self.wt, "add", "--", dest)
                self.report["remapped"].append(dict(src=d.path, dest=dest))
                say("  remapped %s -> %s" % (d.path, dest))

    def git_apply(self, text):
        return subprocess.run(["git", "-C", self.wt, "apply", "--3way", "--index", "--whitespace=nowarn", "-"],
                              input=text, text=True, capture_output=True)

    def reject_text(self, d):
        """Per-hunk failure detail via a dry `git apply --reject` into a scratch copy."""
        tmp = os.path.join(self.work, "rej", str(len(self.report["conflicts"])))   # fresh subdir inside our own work dir
        os.makedirs(os.path.dirname(os.path.join(tmp, d.path)), exist_ok=True)
        cur = self.tree.read(d.path)
        if cur is None:
            return ""
        open(os.path.join(tmp, d.path), "wb").write(cur)
        subprocess.run(["git", "apply", "--reject", "--whitespace=nowarn", "--directory=" + tmp, "-"], input=d.text, text=True, capture_output=True, cwd=tmp)
        rj = os.path.join(tmp, d.path + ".rej")
        return open(rj, errors="replace").read()[:3000] if os.path.isfile(rj) else ""

    # ------------------------------------------------------------ merge into migrated TUs
    def merge(self):
        if not self.merge_plan:
            return
        by_dest = {}
        for src, dest in self.merge_plan.items():
            by_dest.setdefault(dest, []).append(src)
        tip_rows = {r["tu"]: set() for r in self.tree.manifest}
        for r in self.tree.manifest:
            tip_rows[r["tu"]].add(D.hx(r["addr"]))
        for dest, srcs in sorted(by_dest.items()):
            texts, rows_by_file = {}, {dest: set(tip_rows.get(dest, set()))}
            for src in srcs:
                text = next(d for d in self.diffs if d.path == src).new_content()
                mine = {D.hx(r["addr"]) for r in self.rows if r.get("tu") == src}
                already = sorted(a for a in mine if a in self.tree.by_addr)
                if already:
                    text = self.drop_chunks(text, set(already))
                    for a in already:
                        cur = self.tree.by_addr[a]
                        self.report["dropped_rows"].append(dict(addr="0x%X" % a, tu=cur["tu"], why="already in the tip manifest (%s)" % cur["status"]))
                    say("  %s: dropped %d rows already in the tip manifest: %s" % (src, len(already), ", ".join("0x%X" % a for a in already[:5])))
                    mine -= set(already)
                texts[src] = text
                rows_by_file[src] = mine
                rows_by_file[dest] |= mine
            # headers the new file includes relative to its own dir must resolve from the dest dir;
            # merge_into_tu rewrites includes that exist in the worktree (new headers were applied above)
            new_text, tags = D.merge_into_tu(self.wt, dest, texts, rows_by_file)
            open(os.path.join(self.wt, dest), "w").write(new_text)
            L.git(self.wt, "add", "--", dest)
            for src in srcs:
                for r in self.rows:
                    if r.get("tu") == src:
                        r["tu"] = dest
            self.report["merged"].append(dict(dest=dest, srcs=srcs, tags_added=tags,
                                              rows=sum(len(rows_by_file[s]) for s in srcs)))
            say("  merged %s -> %s (%d rows)" % (", ".join(os.path.basename(s) for s in srcs), dest, sum(len(rows_by_file[s]) for s in srcs)))
        dropped = {D.hx(x["addr"]) for x in self.report["dropped_rows"]}
        self.ops = [(op, r, old) for op, r, old in self.ops if D.hx(r["addr"]) not in dropped]
        self.rows = [r for _, r, _ in self.ops]

    @staticmethod
    def drop_chunks(text, addrs):
        lines, pre_end, chunks, inters = D.split(text)
        drop = set()
        for c in chunks:
            if c["addrs"] and all(a in addrs for a in c["addrs"]):
                drop.update(range(c["start"], c["end"]))
        return "\n".join(l for i, l in enumerate(lines) if i not in drop)


    # ------------------------------------------------------------ declaration clashes
    ERR_RE = re.compile(r"^(?P<file>[^\n(]+)\((?P<line>\d+)\) : error (?P<code>C\d+): '(?P<name>[^']+)' : (?P<what>.*)$", re.M)
    DECL_CODES = {"C2371", "C2556", "C2373", "C2374", "C2084", "C2668", "C2011"}

    def unify(self):
        """Resolve declaration-only clashes created by a merge (the packet's header and the
        migrated TU both declare one global or function). A fix drops ONE declaration line;
        drops are tentative and the whole set is accepted only if the TU then compiles and
        every matched row of the TU (tip rows and packet rows) is still byte-identical to
        retail; otherwise every drop is reverted and both declaration sites are reported.
        Class redefinitions (C2011) and body-level errors are reported, never guessed."""
        for m in self.report["merged"]:
            dest = m["dest"]
            dest_rows = [r for r in self.tree.manifest if r["tu"] == dest and r["status"] == "matched"]
            dest_rows += [r for r in self.rows if r.get("tu") == dest and r.get("status") == "matched"]
            obj = os.path.join(self.work, "obj", os.path.splitext(dest)[0] + ".obj")
            files = [dest] + [d.path for d in self.diffs if d.is_new and d.path.lower().endswith(L.HDR_EXT)]
            snap = {f: open(os.path.join(self.wt, f)).read() for f in files if os.path.isfile(os.path.join(self.wt, f))}
            drops, tried = [], set()

            def revert():
                for f, t in snap.items():
                    open(os.path.join(self.wt, f), "w").write(t)
                    L.git(self.wt, "add", "--", f)

            def errors_of(text):
                return [e.groupdict() for e in self.ERR_RE.finditer(text)]

            def is_bad(errs):
                return any(e["code"] not in self.DECL_CODES for e in errs)

            result, rekeys_done, residual = None, [], []
            TYPE_CODES = {"C2011", "C2953"}

            def drop_site(site, name):
                before = open(os.path.join(self.wt, site["file"])).read()
                lines = before.split("\n")
                if site.get("block"):
                    drop = list(range(site["line"], min(site["end"] + 1, len(lines))))
                    k = site["line"] - 1
                    while k >= 0 and lines[k].lstrip().startswith("//"):
                        drop.append(k)
                        k -= 1
                else:
                    drop = [site["line"]]
                    if site["line"] > 0 and re.match(r"\s*//\s*(GLOBAL|FUNCTION|STRING): GAMEMD", lines[site["line"] - 1]):
                        drop.append(site["line"] - 1)
                open(os.path.join(self.wt, site["file"]), "w").write("\n".join(l for i, l in enumerate(lines) if i not in drop))
                drops.append(dict(name=name, **site))
                return before

            # phase 1: every type redefinition -> retire the local view (tip's first, else the packet's
            # when the class has a canonical header): the standing "adopt the canonical header" rule
            canon = self.tree.canonical_classes()
            for _round in range(6):
                ok, text = D.compile_tu(self.wt, dest, obj)
                if ok:
                    break
                errs = errors_of(text)
                todo = [e for e in errs if e["code"] in TYPE_CODES and e["name"] not in tried]
                if not todo:
                    break
                for e in todo:
                    tried.add(e["name"])
                    sites = [x for x in self.decl_sites(dest, e["name"]) if x.get("block")]
                    tip_sites = [x for x in sites if x["side"] == "tip"]
                    pk_sites = [x for x in sites if x["side"] == "packet"]
                    pick = tip_sites[:1] or (pk_sites[:1] if e["name"] in canon else [])
                    for site in pick:
                        drop_site(site, e["name"])
                        self.report.setdefault("unify_attempts", []).append(dict(dest=dest, phase="adopt", name=e["name"], site=site))
            # phase 2: declaration clashes one at a time; a drop stays if the name's errors vanish
            for _round in range(24):
                ok, text = D.compile_tu(self.wt, dest, obj)
                if ok:
                    break
                errs = errors_of(text)
                decl = [e for e in errs if e["code"] in self.DECL_CODES and e["code"] not in TYPE_CODES and e["name"] not in tried]
                if not decl:
                    residual = errs
                    break
                name = decl[0]["name"]
                tried.add(name)
                for site in self.decl_sites(dest, name):
                    before = drop_site(site, name)
                    ok2, text2 = D.compile_tu(self.wt, dest, obj)
                    errs2 = errors_of(text2)
                    gone = name not in {x["name"] for x in errs2}
                    self.report.setdefault("unify_attempts", []).append(dict(dest=dest, phase="decl", name=name, site=site, compiles=ok2, resolved=gone))
                    if ok2 or gone:
                        break
                    open(os.path.join(self.wt, site["file"]), "w").write(before)
                    drops.pop()
            else:
                residual = errors_of(D.compile_tu(self.wt, dest, obj)[1])
            # phase 3: accept only on compile + re-key + byte identity
            ok, text = D.compile_tu(self.wt, dest, obj)
            if ok:
                rows2, rk, unres = self.rekey_rows(obj, dest_rows)
                if unres:
                    result, residual = "errors", [dict(code="symbol", name=a_, what="row symbol undefined after unification", file=dest, line="")
                                                  for a_ in unres]
                elif self.bytes_hold(obj, rows2):
                    result, rekeys_done = "ok", rk
                else:
                    result = "bytes"
            else:
                result, residual = "errors", errors_of(text)
            if result == "ok":
                for f in snap:
                    L.git(self.wt, "add", "--", f)
                for rk in rekeys_done:
                    self.report["rekeyed"].append(rk)
                    if rk["where"] == "tip":
                        cur = dict(self.tree.by_addr[D.hx(rk["addr"])])
                        cur["sym"] = rk["new"]
                        self.ops.append(("change", cur, {"sym": rk["old"]}))
                        self.rows.append(cur)
                    if rk["where"] == "packet":
                        for r in self.rows:
                            if r.get("addr") and D.hx(r["addr"]) == D.hx(rk["addr"]):
                                r["sym"] = rk["new"]
                    say("  re-keyed %s %s -> %s (%s row, view retired)" % (rk["addr"], rk["old"], rk["new"], rk["where"]))
                for d in drops:
                    self.report["notes"].append("unify: dropped %s %s of %s in %s:%d (TU compiles, all %d rows byte-identical)" % (
                        d["side"], "class view" if d.get("block") else "declaration", d["name"], d["file"], d["line"] + 1, len(dest_rows)))
                    self.report.setdefault("unified", []).append(d)
                    say("  unify: dropped %s declaration of %s (%s:%d)" % (d["side"], d["name"], d["file"], d["line"] + 1))
                continue
            tried_desc = ["%s %s %s:%d" % (d["side"], "view" if d.get("block") else "decl", d["file"], d["line"] + 1) for d in drops]
            revert()
            if result == "bytes":
                self.conflict("view", "%s: after retiring %s the TU compiles but matched bytes change" % (dest, ", ".join(tried_desc)), file=dest, tried=tried_desc)
                continue
            seen = set()
            for e in residual[:16]:
                key = (e["code"], e["name"])
                if key in seen:
                    continue
                seen.add(key)
                sites = self.decl_sites(dest, e["name"]) if e["code"] in self.DECL_CODES else []
                self.conflict("view", "%s: %s '%s' %s at %s:%s%s" % (
                    dest, e["code"], e["name"], e["what"][:90], os.path.basename(e["file"]), e["line"],
                    ("; sites: " + "; ".join("%s %s:%d" % (x["side"], x["file"], x["line"] + 1) for x in sites)) if sites else ""),
                    file=dest, name=e["name"], code=e["code"], sites=sites, after_retiring=tried_desc)
            if tried_desc:
                self.report["notes"].append("%s: retiring %s did not make the TU compile; all reverted. Residual errors are the hand-off list." % (dest, ", ".join(tried_desc)))

    def decl_sites(self, dest, name):
        """Column-zero declaration lines (extern / prototype) and local class-view blocks of NAME
        in the merged TU and in packet-new headers, tagged tip/packet. Never inside a body."""
        out = []
        files = [dest] + [d.path for d in self.diffs if d.is_new and d.path.lower().endswith(L.HDR_EXT)]
        rx = re.compile(r"^(?:extern\b[^;{}]*\b%s\b[^;{}]*;|[A-Za-z_][^;{}=]*\b%s\s*\([^;{}]*\)\s*;)\s*(//.*)?$" % (re.escape(name), re.escape(name)))
        crx = re.compile(r"^(?:template\s*<[^>]*>\s*)?(class|struct)\s+(?:__declspec\([^)]*\)\s+)?%s\b[^;]*$" % re.escape(name))
        for f in files:
            path = os.path.join(self.wt, f)
            if not os.path.isfile(path):
                continue
            lines = open(path).read().split("\n")
            dep = cppsplit.depth_scan(lines)
            former = None
            for i, l in enumerate(lines):
                if l.startswith("// ---- from the former "):
                    former = i
                side = "packet" if (f != dest or (former is not None and i > former)) else "tip"
                if dep[i][0] == 0 and rx.match(l):
                    out.append(dict(file=f, line=i, side=side, text=l.strip()[:120]))
                elif dep[i][0] == 0 and crx.match(l):
                    j = i + 1
                    while j < len(lines) and not (dep[j][0] > 0 and dep[j][1] == 0):
                        j += 1
                    out.append(dict(file=f, line=i, end=j, side=side, text=l.strip()[:120], block=True))
        return sorted(out, key=lambda x: 0 if x["side"] == "tip" else 1)

    def rekey_rows(self, obj, rows):
        """Rows whose symbol the object no longer defines (a view was retired) get the unique
        object symbol with the same ?name@Class@@ prefix or a U/V class-key variant.
        Returns (rows with new syms, [{addr, old, new, where}], [unresolved addrs])."""
        names = D.defined_names(obj)
        packet = {D.hx(r["addr"]) for r in self.rows}
        out, rk, unres = [], [], []
        for r in rows:
            if r["sym"] in names:
                out.append(r)
                continue
            pre = r["sym"].split("@@")[0] + "@@"
            cand = [n for n in names if n.startswith(pre)]
            if len(cand) != 1:
                uv = [n for n in names if len(n) == len(r["sym"]) and all(x == y or {x, y} == {"U", "V"} for x, y in zip(n, r["sym"]))]
                cand = uv if len(uv) == 1 else cand
            if len(cand) == 1:
                r2 = dict(r, sym=cand[0])
                out.append(r2)
                rk.append(dict(addr=r["addr"], old=r["sym"], new=cand[0], where="packet" if D.hx(r["addr"]) in packet else "tip",
                               why="view retired by unify; object defines this symbol"))
            else:
                unres.append(r["addr"])
        return out, rk, unres

    def bytes_hold(self, obj, rows):
        with cf.ThreadPoolExecutor(self.jobs) as ex:
            res = list(ex.map(lambda r: D.raw_match(self.wt, obj, r)[0], rows))
        return all(res)

    # ------------------------------------------------------------ bookkeeping fixes (re-proved by prove())
    def normalise(self):
        """Two defects the linter reports that are safe to fix mechanically because every row is
        re-proved afterwards: (1) a row length that counts NOP/INT3 padding after the CFG-closed
        span becomes the span; (2) body claims of a NEW file out of ascending address order are
        reordered chunk by chunk (bodies untouched; /Gy puts each function in its own section)."""
        for r in self.rows:
            if r.get("status") not in ("matched", "partial") or "len" not in r:
                continue
            try:
                span, why = D.cfg_span(D.hx(r["addr"]))
            except Exception:
                continue
            ln = D.hx(r["len"])
            if span and ln > span:
                tail = D.retail_bytes(D.hx(r["addr"]) + span, ln - span)
                if tail and all(b in (0x90, 0xCC) for b in tail):
                    self.report.setdefault("fixed_lens", []).append(dict(addr=r["addr"], old=r["len"], new="0x%x" % span))
                    r["len"] = "0x%x" % span
        for d in self.diffs:
            if not (d.is_new and d.path.lower().endswith(L.SRC_EXT)) or d.path.lower().endswith(".asm") or d.path in self.merge_plan:
                continue
            path = os.path.join(self.wt, d.path)
            if not os.path.isfile(path):
                continue
            text = open(path).read()
            lines, pre_end, chunks, inters = D.split(text)
            keyed = [(min(c["addrs"]) if c["addrs"] else -1, c) for c in chunks]
            if [k for k, _ in keyed] == sorted(k for k, _ in keyed):
                continue
            out = lines[:pre_end]
            # keep interstitial code where it is relative to the preamble: hoist it, then sorted chunks
            for a, b in inters:
                if cppsplit.code_only(lines[a:b]):
                    out += [""] + lines[a:b]
            for k, c in sorted(keyed, key=lambda x: x[0]):
                out += [""] + lines[c["start"]:c["end"]]
            obj = os.path.join(self.work, "obj", os.path.splitext(d.path)[0] + ".obj")
            ok_before, _ = D.compile_tu(self.wt, d.path, obj)
            open(path, "w").write("\n".join(out).rstrip("\n") + "\n")
            ok_after, text2 = D.compile_tu(self.wt, d.path, obj)
            if ok_before and not ok_after:
                open(path, "w").write(text)          # the hoist broke a dependency between interstitial code and a body
                self.report["notes"].append("%s: claims are out of address order but reordering does not compile; left as the packet has it" % d.path)
                continue
            L.git(self.wt, "add", "--", d.path)
            self.report.setdefault("reordered", []).append(d.path)
            say("  reordered %d claims in %s into ascending address order" % (len(chunks), d.path))
        if self.report.get("fixed_lens"):
            say("  fixed %d padded row lengths to their CFG spans" % len(self.report["fixed_lens"]))

    # ------------------------------------------------------------ manifest + re-keys
    def rekey(self):
        n = 0
        for r in self.rows:
            if r.get("sym") in self.rekeys:
                self.report["rekeyed"].append(dict(addr=r["addr"], old=r["sym"], new=self.rekeys[r["sym"]], why="known re-key map"))
                r["sym"] = self.rekeys[r["sym"]]
                n += 1
        if n:
            say("  re-keyed %d rows from the known maps" % n)

    def auto_rekey(self, objs):
        for r in self.rows:
            obj = objs.get(r.get("tu"))
            if not obj or r.get("status") not in ("matched", "partial"):
                continue
            names = D.defined_names(obj)
            if r["sym"] in names:
                continue
            pre = r["sym"].split("@@")[0] + "@@"
            cand = [n for n in names if n.startswith(pre)]
            if len(cand) != 1:
                uv = [n for n in names if len(n) == len(r["sym"]) and all(x == y or {x, y} == {"U", "V"} for x, y in zip(n, r["sym"]))]
                cand = uv if len(uv) == 1 else cand
            if len(cand) == 1:
                self.report["rekeyed"].append(dict(addr=r["addr"], old=r["sym"], new=cand[0], why="object defines this symbol instead"))
                say("  re-keyed %s %s -> %s (object)" % (r["addr"], r["sym"], cand[0]))
                r["sym"] = cand[0]
            else:
                self.conflict("symbol", "row %s symbol %s not defined by %s (%d candidates)" % (r["addr"], r["sym"], r["tu"], len(cand)), addr=r["addr"])

    def manifest(self):
        man, _ = L.load_manifest(os.path.join(self.wt, D.MANIFEST))
        delta = [dict(r, **({"op": op} if op else {}), **({"old": old} if old else {})) for op, r, old in self.ops]
        merged, errs, warns = L.merge_deltas(man, [(self.p.name, delta)])
        for w in warns:
            self.report["notes"].append(w)
        if errs:
            for e in errs:
                self.conflict("manifest", e)
            return False
        open(os.path.join(self.wt, D.MANIFEST), "w").write(L.dump_manifest(merged))
        L.git(self.wt, "add", "--", D.MANIFEST)
        return True

    # ------------------------------------------------------------ compile + prove
    def prove(self):
        tus = sorted({r["tu"] for r in self.rows if r.get("tu")})
        objs = {}
        with cf.ThreadPoolExecutor(self.jobs) as ex:
            res = list(ex.map(lambda tu: (tu, D.compile_tu(self.wt, tu, os.path.join(self.work, "obj", os.path.splitext(tu)[0] + ".obj"))), tus))
        for tu, (ok, text) in res:
            if ok:
                objs[tu] = os.path.join(self.work, "obj", os.path.splitext(tu)[0] + ".obj")
            else:
                errl = [l for l in text.splitlines() if re.search(r"error|fatal", l, re.I)][:5]
                self.conflict("compile", "%s: %s" % (tu, " | ".join(errl)), file=tu, errors=errl)
        self.auto_rekey(objs)
        maps = list(self.p.symbol_map_files())
        central = D.first_existing(D.BINDINGS_CANDIDATES, self.wt)
        if central:
            maps.append(central)
            self.report["notes"].append("central bindings used: " + central)
        merged, clash = D.merge_maps(maps)
        for k in list(merged):
            if k in self.rekeys:
                merged[self.rekeys[k]] = merged.pop(k)
        packet_keys = set(merged)
        for tu, obj in objs.items():
            merged.update(D.label_bindings(obj, [r for r in self.rows if r["tu"] == tu]))
        mapfile = os.path.join(self.work, "map.json")
        json.dump(merged, open(mapfile, "w"), indent=1)
        iat = D.iat_by_name()
        rows = [r for r in self.rows if r.get("status") == "matched" and r.get("tu") in objs]
        lock = __import__("threading").Lock()

        def one(r):
            obj = objs[r["tu"]]
            ok, text = D.raw_match(self.wt, obj, r)
            if not ok:
                return r, "raw", text[-300:]
            for _ in range(12):
                sok, target, text = D.strict(self.wt, obj, r, mapfile)
                if sok:
                    return r, "ok", ""
                if not target:
                    return r, "strict", text[-300:]
                va = D.derive_binding(target, iat)
                with lock:
                    if target in merged or va is None:
                        return r, "unbound", target
                    merged[target] = "0x%X" % va
                    json.dump(merged, open(mapfile, "w"), indent=1)
            return r, "strict", text[-300:]

        with cf.ThreadPoolExecutor(self.jobs) as ex:
            out = list(ex.map(one, rows))
        for r, st, text in out:
            if st == "raw":
                self.conflict("raw", "row %s raw_match fails: %s" % (r["addr"], text.replace("\n", " ")), addr=r["addr"])
            elif st == "unbound":
                self.report["unbound"].append(dict(addr=r["addr"], target=text))
                self.conflict("unbound", "row %s: target %s has no binding (packet maps, central bindings, name, IAT, $L)" % (r["addr"], text), addr=r["addr"])
            elif st == "strict":
                self.conflict("strict", "row %s strict verify_relocations fails: %s" % (r["addr"], text.replace("\n", " ")), addr=r["addr"])
        self.report["derived_bindings"] = {k: v for k, v in merged.items() if k not in packet_keys}
        self.mapfile = mapfile
        self.report["proved_rows"] = sum(1 for _, st, _ in out if st == "ok")
        say("  proved %d/%d matched rows (%d bindings derived)" % (self.report["proved_rows"], len(rows), len(self.report["derived_bindings"])))

    # ------------------------------------------------------------ gates
    def gates(self):
        run = os.path.join(self.work, "gates")
        cmd = [sys.executable, os.path.join(D.TOOLS, "land", "gates.py"), "--tree", self.wt, "--base", self.tip, "--mode", "inc",
               "--jobs", str(self.jobs), "--run", run, "--symmap", self.mapfile]
        rc, text = L.run(cmd, cwd=self.wt, env=L.toolenv(), log=os.path.join(self.work, "gates.log"))
        lines = [l for l in text.splitlines() if l.startswith(("GATE", "RESULT", "changed paths"))]
        for l in lines:
            say("   ", l)
        self.report["gates"] = dict(rc=rc, lines=lines)
        if rc:
            self.conflict("gates", "incremental gates failed (see gates.log)")
        return os.path.join(self.work, "gates.log")

    # ------------------------------------------------------------ output
    def write(self, gates_log=None):
        out = self.out
        os.makedirs(out, exist_ok=True)
        diff = L.git(self.wt, "diff", "--cached", "--binary", self.tip, "--", ".", ":(exclude)%s" % D.MANIFEST)
        open(os.path.join(out, "patch.diff"), "w").write(diff)
        delta = []
        for op, r, old in sorted(self.ops, key=lambda x: D.hx(x[1]["addr"])):
            row = {k: v for k, v in r.items() if not k.startswith("_") and k not in ("op", "old")}
            if op:
                row["op"] = op
            if old and old.get("sym"):
                row["old"] = {"sym": old["sym"]}
            delta.append(row)
        json.dump(delta, open(os.path.join(out, "manifest_delta.json"), "w"), indent=1)
        if getattr(self, "mapfile", None):
            shutil.copy(self.mapfile, os.path.join(out, "symbol_map_rebased.json"))
        for f in ("results.tsv", "gates.log", "words_ok.txt", "waive_strict.txt", "spans_ok.txt", "symbol_bindings_delta.json", "binding_delta.json", "binding_corrections.json"):
            src = os.path.join(self.p.dir, f)
            if os.path.isfile(src):
                shutil.copy(src, os.path.join(out, f))
        if gates_log and os.path.isfile(gates_log):
            shutil.copy(gates_log, os.path.join(out, "gates_rebased.log"))
        open(os.path.join(out, "base_sha"), "w").write(self.tip + "\n")
        readme = open(self.p.readme, errors="replace").read() if os.path.isfile(self.p.readme) else ""
        msg = self.p.commit_message() or ""
        if self.report["merged"] and msg:
            sent = " ".join("The %s functions join the migrated %s in retail address order." % (
                os.path.splitext(os.path.basename(m["srcs"][0]))[0] if len(m["srcs"]) == 1 else "%d new files'" % len(m["srcs"]), m["dest"]) for m in self.report["merged"])
            lines = msg.rstrip("\n").split("\n")
            trailer = [l for l in lines if l.startswith("Co-Authored-By:")]
            body = [l for l in lines if not l.startswith("Co-Authored-By:")]
            msg = "\n".join(body).rstrip("\n") + "\n\n" + sent + "\n" + ("\n" + "\n".join(trailer) + "\n" if trailer else "")
        if msg:
            open(os.path.join(out, "commit_msg.txt"), "w").write(msg)
        note = "\n\n## Rebased by pktrebase onto %s\n%s\n" % (self.tip[:10], json.dumps(
            {k: self.report[k] for k in ("remapped", "merged", "dropped_rows", "rekeyed", "conflicts")}, indent=1))
        open(os.path.join(out, "README.md"), "w").write(readme + note)
        json.dump(self.report, open(os.path.join(out, "report.json"), "w"), indent=1)
        say("rebased packet written to", out)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("packet")
    ap.add_argument("--repo", default=D.MAIN_REPO)
    ap.add_argument("--rev", default="HEAD")
    ap.add_argument("--out")
    ap.add_argument("--rekey", action="append", default=[], help="JSON {old_sym: new_sym}; rekeys/*.json beside this tool are always used")
    ap.add_argument("--gates", choices=["inc", "none"], default="inc")
    ap.add_argument("--jobs", type=int, default=D.MAX_JOBS)
    ap.add_argument("--keep", action="store_true")
    ap.add_argument("--no-merge", action="store_true", help="do not merge new files into migrated TU files")
    a = ap.parse_args(argv)
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from pktlint import resolve_packet
    p = resolve_packet(a.packet)
    out = a.out or os.path.join(os.path.dirname(p.dir), "REBASED")
    rekeys = list(a.rekey)
    if os.path.isdir(REKEY_DIR):
        rekeys += [os.path.join(REKEY_DIR, f) for f in sorted(os.listdir(REKEY_DIR)) if f.endswith(".json")]
    t0 = time.time()
    R = Rebase(p, a.repo, a.rev, out, min(a.jobs, D.MAX_JOBS), rekeys, a.keep, merge=not a.no_merge)
    say("pktrebase %s onto %s (work %s)" % (p.name, R.tip[:10], R.work))
    try:
        R.setup()
        t = time.time(); R.apply(); R.report["secs"]["apply"] = round(time.time() - t, 1)
        t = time.time(); R.merge(); R.report["secs"]["merge"] = round(time.time() - t, 1)
        t = time.time(); R.unify(); R.report["secs"]["unify"] = round(time.time() - t, 1)
        R.normalise()
        R.rekey()
        gl = None
        if R.manifest():
            t = time.time(); R.prove(); R.report["secs"]["prove"] = round(time.time() - t, 1)
            if R.ok and a.gates == "inc":
                t = time.time(); gl = R.gates(); R.report["secs"]["gates"] = round(time.time() - t, 1)
        R.report["secs"]["total"] = round(time.time() - t0, 1)
        R.report["ok"] = R.ok
        R.write(gl)
        say("pktrebase %s: %s in %.0fs; %d conflicts" % (p.name, "OK" if R.ok else "CONFLICTS", time.time() - t0, len(R.report["conflicts"])))
        return 0 if R.ok else 2
    finally:
        R.cleanup()


if __name__ == "__main__":
    sys.exit(main())

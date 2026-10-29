#!/usr/bin/env python3
# Provenance: original. Reads the manifest, match/ sources and scripts/data/original_tu_map.json; report only.
"""placement_leads.py: files pinned without /Ob2 and the definitions in them that probably belong elsewhere.

    placement_leads.py [--tree PATH] [--file match/x.cpp]... [--json OUT] [--strong-only]

The project default includes /Ob2. A file carrying a `// VC6FLAGS:` line without it (they also carry a
"Placement lead" comment) usually holds a definition that was compiled in another original file, so the
better fix is to move the definition, not to keep a flag line.

For each such file the tool places every manifest row of the file in the original link order recorded
in scripts/data/original_tu_map.json: the witnessed translation units (link_order windows, from `__FILE__`
strings in assert calls) are ordered by address, and an address is either inside one window or in the
gap between two. The file's dominant slot is the most common one among its rows. A row in a different
slot is a lead:

  strong  at least one whole witnessed window lies between the row and the dominant slot (different original files)
  weak    adjacent slots (a window and the gap right after or before it); can still be one file

Each lead lists the map's own kind and evidence for that address and the other match/ files whose dominant
slot is the row's slot (where it might move to). Nothing is edited; verify a move with the usual
match.sh / verify_all.py loop.
"""
import argparse
import bisect
import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dlib as D  # noqa: E402

FLAGS = re.compile(r"^\s*//\s*VC6FLAGS:(.*)$", re.M)
LEAD = re.compile(r"^\s*//\s*Placement lead", re.M)


def hx(x):
    return x if isinstance(x, int) else int(x, 16)


class Order:
    """Slot index of an address: i for 'inside window i', i - 0.5 for 'in the gap before window i'."""

    def __init__(self, link_order):
        self.w = sorted((hx(e["lo"]), hx(e["hi"]), e["tu"]) for e in link_order)
        self.lo = [x[0] for x in self.w]

    def slot(self, a):
        i = bisect.bisect_right(self.lo, a) - 1
        if i >= 0 and a <= self.w[i][1]:
            return float(i)
        return i + 0.5

    def home_of(self, rel, text):
        """Window index of the original file the .cpp is named after (or declares in its header), else None."""
        names = [os.path.basename(rel).lower()]
        m = re.search(r"Original translation unit (\S+?)\.", text)
        if m:
            names.append(m.group(1).lower())
        for i, (_, _, tu) in enumerate(self.w):
            if tu.lower() in names or os.path.splitext(tu)[0].lower() == os.path.splitext(names[0])[0]:
                return float(i)
        return None

    def label(self, s):
        i = int(s)
        if s == i:
            return "in %s" % self.w[i][2]
        before = self.w[i][2] if 0 <= i < len(self.w) else "start"
        after = self.w[i + 1][2] if i + 1 < len(self.w) else "end"
        return "between %s and %s" % (before, after)


def pinned_files(tree, only):
    out = {}
    root = os.path.join(tree, "match")
    for dp, _, fs in os.walk(root):
        for f in fs:
            if not f.lower().endswith((".cpp", ".c")):
                continue
            path = os.path.join(dp, f)
            rel = os.path.relpath(path, tree)
            if only and rel not in only:
                continue
            text = open(path, errors="replace").read()
            m = FLAGS.search(text)
            lead = bool(LEAD.search(text))
            if only or lead or (m and "/Ob2" not in m.group(1).split()):
                if m and "/Ob2" in m.group(1).split() and not only:
                    continue
                out[rel] = dict(flags=m.group(1).strip() if m else None, lead_comment=lead, _text=text)
    return out


def analyse(tree, only=(), strong_only=False):
    omap = json.load(open(os.path.join(tree, "scripts/data/original_tu_map.json")))
    man = json.load(open(os.path.join(tree, D.MANIFEST)))
    order = Order(omap["link_order"])
    info = {hx(f["addr"]): f for f in omap["functions"]}
    by_file = collections.defaultdict(list)
    for r in man:
        by_file[r["tu"]].append(r)
    dominant = {}
    for tu, rows in by_file.items():
        c = collections.Counter(order.slot(hx(r["addr"])) for r in rows)
        dominant[tu] = c.most_common(1)[0][0]
    homes = collections.defaultdict(list)       # slot -> files whose dominant slot it is
    for tu, s in dominant.items():
        homes[s].append(tu)
    res = []
    for rel, meta in sorted(pinned_files(tree, set(only)).items()):
        meta = dict(meta)
        text = meta.pop("_text")
        rows = by_file.get(rel, [])
        if not rows:
            res.append(dict(file=rel, **meta, rows=0, leads=[]))
            continue
        home = order.home_of(rel, text)
        dom = dominant[rel] if home is None else home
        meta["home"] = "named window" if home is not None else "most common slot"
        slots = collections.Counter(order.slot(hx(r["addr"])) for r in rows)
        leads = []
        for r in sorted(rows, key=lambda r: hx(r["addr"])):
            a = hx(r["addr"])
            s = order.slot(a)
            if s == dom:
                continue
            strength = "strong" if abs(s - dom) >= 1 else "weak"
            if strong_only and strength != "strong":
                continue
            i = info.get(a, {})
            leads.append(dict(addr="0x%X" % a, name=r.get("name", ""), status=r.get("status"), slot=order.label(s), strength=strength,
                              map_kind=i.get("tu_kind"), map_tu=i.get("tu"), evidence=i.get("evidence"),
                              could_move_to=sorted(f for f in homes.get(s, []) if f != rel)[:6]))
        res.append(dict(file=rel, **meta, rows=len(rows), dominant=order.label(dom),
                        slots={order.label(k): v for k, v in sorted(slots.items())}, leads=leads))
    return res


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=os.environ.get("GAG_WORKTREE") or D.L.REPO_ROOT)
    ap.add_argument("--file", action="append", default=[], help="only this match/ file (repeatable)")
    ap.add_argument("--json")
    ap.add_argument("--strong-only", action="store_true")
    ap.add_argument("--per-group", type=int, default=3, help="rows listed under each group of leads (default 3)")
    a = ap.parse_args(argv)
    res = analyse(a.tree, a.file, a.strong_only)
    for f in res:
        print("%s  [%s]%s  %d rows" % (f["file"], f["flags"] or "no VC6FLAGS", "" if f["lead_comment"] else " (no Placement lead comment)", f["rows"]))
        if not f["rows"]:
            print("    no manifest rows")
            continue
        print("    home slot (%s): %s, %d of %d rows" % (f["home"], f["dominant"], f["slots"].get(f["dominant"], 0), f["rows"]))
        groups = collections.OrderedDict()
        for l in f["leads"]:
            groups.setdefault((l["strength"], l["slot"]), []).append(l)
        for (st, slot), ls in groups.items():
            kinds = collections.Counter(x["map_kind"] for x in ls)
            print("    %-6s %-40s %3d rows %s..%s  kinds %s%s" % (
                st, slot, len(ls), ls[0]["addr"], ls[-1]["addr"], dict(kinds),
                ("  -> " + ", ".join(ls[0]["could_move_to"][:3])) if ls[0]["could_move_to"] else ""))
            for x in ls[:a.per_group]:
                print("             %s %s" % (x["addr"], x["name"][:60]))
    nstrong = sum(l["strength"] == "strong" for f in res for l in f["leads"])
    print("%d pinned files, %d with leads, %d strong leads" % (len(res), sum(bool(f["leads"]) for f in res), nstrong))
    if a.json:
        json.dump(res, open(a.json, "w"), indent=1)
    return 0


if __name__ == "__main__":
    sys.exit(main())

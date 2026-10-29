#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; compares a run-time lifted draft with the repository's own matched source.
"""Score idiom_lift drafts against matched source: per pass, sites lifted vs sites that agree.

    idiom_lift_validate.py 0x721A50 0x551B90 ...

Needs Ghidra (or --file per address is not supported here). Nothing is stored."""
import re
import sys
from pathlib import Path

import idiom_lift as L

REPO = L.REPO


def matched_body(addr):
    for f in sorted(REPO.glob("match/**/*.cpp")):
        t = f.read_text(errors="replace")
        m = re.search(r"// FUNCTION: GAMEMD 0x0*%X\b[^\n]*\n" % addr, t, re.I)
        if not m:
            continue
        i = t.find("{", m.end())
        j = L.match_close(t, i, "{", "}")
        if i > 0 and j > 0:
            return t[m.start():j + 1], str(f.relative_to(REPO))
    return None, None


def idents(txt):
    return set(re.findall(r"[A-Za-z_]\w*", re.sub(r'"(?:\\.|[^"\\])*"', '""', txt)))


def literals(txt):
    return set(re.findall(r'"((?:\\.|[^"\\])*)"', txt))


def score(addr):
    src, where = matched_body(addr)
    if src is None:
        return None
    ctx = L.Ctx(addr=addr)
    doc, body = L.lift_text(L.fetch_pseudo(addr), ctx)
    st = ctx.stats
    res = {}
    # fields: lifted this->Name where Name occurs in the matched source
    lifted = re.findall(r"\bthis->(\w+)", body)
    ref = idents(src)
    res["fields"] = (sum(1 for n in lifted if n in ref), len(lifted))
    # symbols: lifted callee names that occur in matched source
    calls = [c for c in re.findall(r"(?:->|\.|::|\b)([A-Za-z_]\w*)\(", body) if c not in L.KEYWORDS]
    named = [c for c in calls if not c.startswith("FUN_") and c not in ("vf",)]
    res["symbols"] = (sum(1 for c in named if c in ref), len(named))
    # strings
    ls, rs = literals(body), literals(src)
    res["strings"] = (len(ls & rs), len(ls))
    # ini sites
    ini_l = re.findall(r'(\S+) = (?:\(\w+\))?\S+->Read\w+\([^,]+, "([^"]+)", \1\)', body.replace("this->", ""))
    ini_s = re.findall(r'(\S+) = (?:\(\w+\))?\S+->Read\w+\([^,]+, "([^"]+)", \1\)', src)
    res["ini"] = (len({k for _, k in ini_l} & {k for _, k in ini_s}), len(ini_l), len(ini_s))
    # vector / loops
    res["for_loops"] = (min(body.count("for ("), src.count("for (")), body.count("for ("), src.count("for ("))
    res["additem"] = (min(body.count(".AddItem(") + body.count("->AddItem("), src.count("AddItem(")),
                      body.count("AddItem("), src.count("AddItem("))
    res["timer"] = (min(body.count("GetTimeLeft"), src.count("GetTimeLeft")), body.count("GetTimeLeft"), src.count("GetTimeLeft"))
    res["marks"] = body.count("LIFT?")
    res["lines"] = (len(body.split("\n")), len(src.split("\n")))
    return where, res, st


def main(argv):
    tot = {}
    for a in argv:
        addr = L.to_int(a)
        r = score(addr)
        if r is None:
            print("%s: no matched source" % a)
            continue
        where, res, st = r
        print("%s %s" % (a, where))
        for k, v in res.items():
            print("    %-10s %s" % (k, v))
            if isinstance(v, tuple) and len(v) == 2 and k not in ("lines",):
                t = tot.setdefault(k, [0, 0])
                t[0] += v[0]
                t[1] += v[1]
    print("TOTAL (agreeing, lifted):", {k: tuple(v) for k, v in tot.items()})


if __name__ == "__main__":
    main(sys.argv[1:])

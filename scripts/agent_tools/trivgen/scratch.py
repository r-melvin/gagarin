#!/usr/bin/env python3
# Provenance: original. Developer helper: compile a scratch .cpp (in the worktree) and score every
# function in it against one retail address: scratch.py FILE.cpp ADDR LEN
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import data, verify

def main():
    f, addr, ln = sys.argv[1], int(sys.argv[2], 0), int(sys.argv[3], 0)
    rel = str(Path(f).resolve().relative_to(verify.WT))
    obj, errs, text = verify.compile_bin(rel)
    if obj is None:
        print(text); return
    sections, symbols = verify.text_symbols(obj)
    for s in symbols.values():
        if s["section"] in sections and sections[s["section"]]["name"].startswith(".text") and s["name"].startswith("?"):
            ok, pct, out = verify.run_raw(obj, s["name"], addr, ln)
            print(f"{pct:>8} {s['name']}")

main()

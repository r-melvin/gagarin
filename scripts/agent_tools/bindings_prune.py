#!/usr/bin/env python3
"""bindings_prune.py: report (and with --apply remove) stale entries of scripts/data/symbol_bindings.json.

An entry is stale when its mangled symbol is neither defined nor referenced (undefined external, COMDAT,
local, anything in the symbol table) by any compiled object of the tree. A scoped key `tu::sym` is stale
when the object of that TU does not hold `sym` (when the TU has no object, when no object holds it).

    bindings_prune.py --objs DIR [--tree WT] [--apply] [--json OUT]

DIR holds the compiled objects of the tree (searched recursively for *.obj): the gates' `<run>/new`
directory, or the project build output. Build the tree first; an incomplete object set prunes live entries.
Without --apply nothing is written. The file is rewritten with the same key order and formatting.
Exit 0 always unless the arguments are bad; the summary line gives the counts.
"""
import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
BINDINGS = "scripts/data/symbol_bindings.json"


def object_symbols(vt, path):
    d, ss, sy, aux = vt.parse_coff(path)
    return {s["name"] for s in sy.values() if s.get("name")}


def load_vt(tree):
    import importlib.util
    spec = importlib.util.spec_from_file_location("vt_prune", os.path.join(tree, "scripts/vc6/verify_vtable.py"))
    vt = importlib.util.module_from_spec(spec)
    sys.path.insert(0, os.path.join(tree, "scripts/vc6"))
    spec.loader.exec_module(vt)
    return vt


def scan(vt, objs):
    """({stem: symbol set}, union) for every *.obj under OBJS; stem is the path without extension, relative to OBJS."""
    per, union = {}, set()
    for root, _, names in os.walk(objs):
        for n in names:
            if n.lower().endswith(".obj"):
                p = os.path.join(root, n)
                try:
                    syms = object_symbols(vt, p)
                except Exception as ex:                                      # unreadable object: do not guess
                    raise SystemExit("cannot read %s: %s" % (p, ex))
                per[os.path.splitext(os.path.relpath(p, objs))[0]] = syms
                union |= syms
    return per, union


def stale_keys(bindings, per, union):
    out = []
    for k in bindings:
        tu, sep, name = k.partition("::")
        if sep:
            stem = os.path.splitext(tu)[0]
            syms = per.get(stem)
            if syms is None:
                syms = union
            if name not in syms:
                out.append(k)
        elif k not in union:
            out.append(k)
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", default=os.environ.get("GAG_WORKTREE") or os.path.dirname(os.path.dirname(HERE)))
    ap.add_argument("--objs", required=True)
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--json", default=None, help="write the stale entries ({key: address}) here")
    a = ap.parse_args(argv)
    tree = os.path.abspath(a.tree)
    path = os.path.join(tree, BINDINGS)
    with open(path) as f:
        raw = f.read()
    bindings = json.loads(raw)
    per, union = scan(load_vt(tree), a.objs)
    if len(per) < 100:
        print("only %d objects under %s: refusing (an incomplete object set would prune live entries)" % (len(per), a.objs), file=sys.stderr)
        return 2
    stale = stale_keys(bindings, per, union)
    for k in stale:
        print("STALE", k, bindings[k])
    if a.json:
        with open(a.json, "w") as f:
            json.dump({k: bindings[k] for k in stale}, f, indent=1)
            f.write("\n")
    if a.apply and stale:
        drop = set(stale)
        kept = {k: v for k, v in bindings.items() if k not in drop}
        indent = 1 if raw.startswith("{\n ") and not raw.startswith("{\n  ") else 2
        with open(path, "w") as f:
            f.write(json.dumps(kept, indent=indent, ensure_ascii=False) + ("\n" if raw.endswith("\n") else ""))
    print("%d entries, %d objects, %d stale%s" % (len(bindings), len(per), len(stale), " (removed)" if a.apply and stale else ""))
    return 0


if __name__ == "__main__":
    sys.exit(main())

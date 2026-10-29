#!/usr/bin/env python3
# Provenance: original. Caller-pattern evidence for a function's calling convention (Ghidra x-refs + retail bytes).
"""evidence(addr) -> dict(sites, ecx_set, edx_set, pushes{n: count}, tails)

For each direct call site of `addr` (Ghidra `x-ref to`), the instructions between the previous
call/branch/ret of the calling function and the call are scanned: pushes are counted as stack
arguments, a full write of ECX/EDX counts as that register being set for the callee.
"""
import functools
import json
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import calleesig  # noqa: E402
import common  # noqa: E402
import x86  # noqa: E402


def xrefs_to(addr):
    r = subprocess.run([common.GHIDRA, "x-ref", "to", hex(addr), "--json"], capture_output=True, text=True)
    try:
        return json.loads(r.stdout)
    except ValueError:
        return []


def _site(entry, site, call_kind):
    span = site + 5 - entry
    if span <= 0 or span > 0x600:
        return None
    insns = x86.decode(entry, span)
    prior = [i for i in insns if i.addr < site]
    ecx = edx = False
    pushes = 0
    for i in reversed(prior[-14:]):
        if i.mn in ("call", "ret") or (i.mn.startswith("j")):
            break
        if i.mn == "push":
            pushes += 1
        r, w = calleesig.rw(i)
        if "ecx" in w:
            ecx = True
        if "edx" in w:
            edx = True
    return dict(ecx=ecx, edx=edx, pushes=pushes, tail=(call_kind == "jmp"))


@functools.lru_cache(None)
def evidence(addr):
    sites = []
    for x in xrefs_to(addr):
        rt = str(x.get("ref_type", ""))
        if "CALL" not in rt and "JUMP" not in rt:
            continue
        fn = x.get("from_function")
        site = int(x["from"], 16)
        try:
            entry = int(fn.split("_")[-1], 16) if fn else None
        except ValueError:
            entry = None
        if entry is None or entry > site:
            continue
        s = _site(entry, site, "jmp" if "JUMP" in rt else "call")
        if s:
            sites.append(s)
    pushes = {}
    for s in sites:
        pushes[s["pushes"]] = pushes.get(s["pushes"], 0) + 1
    return dict(sites=len(sites), ecx_set=sum(s["ecx"] for s in sites), edx_set=sum(s["edx"] for s in sites),
                pushes=pushes, tails=sum(s["tail"] for s in sites))


def describe(ev):
    if not ev["sites"]:
        return "callers=0"
    p = ",".join(f"{k}x{v}" for k, v in sorted(ev["pushes"].items()))
    return f"callers={ev['sites']} ecx_set={ev['ecx_set']} edx_set={ev['edx_set']} push={p}"


if __name__ == "__main__":
    for a in sys.argv[1:]:
        print(a, describe(evidence(int(a, 0))))

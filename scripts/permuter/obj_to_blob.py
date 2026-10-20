#!/usr/bin/env python3
"""obj_to_blob.py — reduce a VC6 COFF object to the same shape as target.o.

The permuter compares two *objects* with one objdump invocation each.  Our two
sides are not symmetric out of the box: the retail side is a raw byte blob
(make_target.py) while cl's side is an i386 COFF object carrying a mangled
symbol name, COMDAT sections and — critically — up to fifteen bytes of trailing
`nop`/`lea` alignment padding that the permuter would score as insertions worth
100 points each, swamping the real signal.

So the candidate is put through the same door as the target: the named
function's instruction bytes are lifted out, trailing padding is trimmed exactly
as scripts/vc6/diff_retail.py trims it, and the result is assembled into an
ELF32 i386 blob.  Both sides then disassemble through the identical objdump path
and the only differences the scorer sees are real ones.

Relocated operands are the known asymmetry: retail's blob carries linked
absolute addresses where cl's carries zeros, so every call/global reference
costs a constant field penalty on every candidate.  That floor is the same for
every candidate and does not steer the search, but it does mean a *score of 0*
is only reachable for a relocation-free body.  See docs/permuter_workflow.md.

Usage: obj_to_blob.py <in.obj> <mangled-symbol> <out.o>
"""
import importlib.util, os, subprocess, sys

_spec = importlib.util.spec_from_file_location(
    "diff_retail",
    os.path.join(os.path.dirname(os.path.abspath(__file__)),
                 "..", "vc6", "diff_retail.py"))
_dr = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_dr)


def main():
    obj, sym, out = sys.argv[1:4]
    insns, _ = _dr.objdump_insns(obj, sym)
    while insns and (insns[-1][2] == "nop"
                     or (insns[-1][2] == "lea" and "+0x0]" in insns[-1][3])):
        insns.pop()
    if not insns:
        raise SystemExit(f"obj_to_blob: no instructions for {sym} in {obj}")
    blob = b"".join(bytes.fromhex(i[1]) for i in insns)
    asm = [".text", ".globl target_fn", "target_fn:"]
    for i in range(0, len(blob), 8):
        asm.append(".byte " + ",".join("0x%02x" % c for c in blob[i:i + 8]))
    s = out + ".s"
    open(s, "w").write("\n".join(asm) + "\n")
    subprocess.check_call(["as", "--32", "-o", out, s])
    os.remove(s)


if __name__ == "__main__":
    main()

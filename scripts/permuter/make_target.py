#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
"""make_target.py — build decomp-permuter's `target.o` from retail gamemd.exe.

The permuter scores a candidate object against a *target object*.  We have no
object file for retail code, only bytes in the user's binary, so this pulls the
function's bytes through the local Ghidra CLI and assembles them verbatim into
an ELF32 i386 object with a single `.text` symbol.  The permuter detects the
architecture from that ELF header (it already ships x86 support: X86_SETTINGS in
src/objdump.py), disassembles both sides with the same objdump, and compares.

Usage: make_target.py --addr 0x5B2990 --len 0x2a --out <rundir>/target.o

The explicit length must be validated against the complete retail entry span.
Ghidra's function-size field can omit post-call blocks or final RET bytes.
"""
import argparse, json, os, subprocess, sys

GHIDRA = os.environ.get("GHIDRA", os.path.expanduser("~/.cargo/bin/ghidra"))


def func_bytes(addr, length):
    # Ghidra's instruction listing can omit blocks (notably after calls it
    # misclassifies as noreturn). Concatenating that listing silently closes
    # gaps and can pull bytes from the next function into the target. Read the
    # actual contiguous memory span, independent of the analysis body shape.
    out = subprocess.run([GHIDRA, "memory", "read", hex(addr), str(length)],
                         capture_output=True, text=True, check=True).stdout
    blob = bytearray()
    for block in json.loads(out):
        expected = addr + len(blob)
        if int(block["address"], 16) != expected:
            raise ValueError(f"make_target: noncontiguous memory at {expected:#x}")
        blob.extend(bytes.fromhex(block["hex"]))
    if len(blob) != length:
        raise ValueError(f"make_target: got {len(blob)} of {length} memory bytes")
    return bytes(blob)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--addr", required=True)
    ap.add_argument("--len", required=True,
                    help="validated contiguous retail function length (hex)")
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    addr = int(a.addr, 16)
    length = int(a.len, 16)
    if length <= 0:
        ap.error("--len must be positive")
    blob = func_bytes(addr, length)
    if len(blob) != length:
        raise SystemExit(f"make_target: got {len(blob)} of {length} bytes")
    asm = [".text", ".globl target_fn", "target_fn:"]
    for i in range(0, len(blob), 8):
        asm.append(".byte " + ",".join("0x%02x" % c for c in blob[i:i + 8]))
    s = a.out[:-2] + ".s" if a.out.endswith(".o") else a.out + ".s"
    open(s, "w").write("\n".join(asm) + "\n")
    subprocess.check_call(["as", "--32", "-o", a.out, s])
    print(f"make_target: {addr:#x} {length} bytes -> {a.out}")


if __name__ == "__main__":
    main()

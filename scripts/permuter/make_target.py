#!/usr/bin/env python3
"""make_target.py — build decomp-permuter's `target.o` from retail gamemd.exe.

The permuter scores a candidate object against a *target object*.  We have no
object file for retail code, only bytes in the user's binary, so this pulls the
function's bytes through the local Ghidra CLI and assembles them verbatim into
an ELF32 i386 object with a single `.text` symbol.  The permuter detects the
architecture from that ELF header (it already ships x86 support: X86_SETTINGS in
src/objdump.py), disassembles both sides with the same objdump, and compares.

Usage: make_target.py --addr 0x5B2990 --out <rundir>/target.o [--len 0x2a]
"""
import argparse, json, os, subprocess, sys

GHIDRA = os.environ.get("GHIDRA", os.path.expanduser("~/.cargo/bin/ghidra"))


def func_size(addr):
    out = subprocess.run([GHIDRA, "function", "get", hex(addr), "--json"],
                         capture_output=True, text=True).stdout
    for r in json.loads(out):
        if int(r["entry_point"], 16) == addr and r.get("size"):
            return int(r["size"])
    raise SystemExit(f"make_target: {addr:#x} is not a function entry point; "
                     f"pass --len")


def func_bytes(addr, length):
    out = subprocess.run([GHIDRA, "disasm", hex(addr),
                          "-n", str(max(64, length // 2 + 16))],
                         capture_output=True, text=True).stdout
    blob, consumed = b"", 0
    for d in json.loads(out):
        if consumed >= length:
            break
        b = bytes.fromhex(d["bytes"])
        blob += b
        consumed += len(b)
    return blob[:length]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--addr", required=True)
    ap.add_argument("--len", default="auto")
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    addr = int(a.addr, 16)
    length = func_size(addr) if a.len == "auto" else int(a.len, 16)
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

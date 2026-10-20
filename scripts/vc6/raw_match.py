#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original
# raw_match.py — gold-standard byte-level match check for one function.
#
# Compares a compiled function's raw bytes (sliced straight from the i386-COFF
# .obj by symbol) against the retail gamemd.exe bytes (Ghidra memory read), and
# treats any difference confined to a <=4-byte aligned run as a relocation slot
# (an absolute address / rel32 the linker fixes up) — exactly as reccmp does.
#
# This is more robust than scripts/vc6/diff_retail.py for functions whose
# disassembly objdump prints out of address order (e.g. /Gy switch-case `$L`
# blocks + embedded jump tables): it works on the contiguous byte image, so the
# ordering never matters. Use it to confirm switch-heavy / table-driven matches.
#
# Relocations are read from the .obj's own COFF relocation table, NOT guessed
# from the size of a differing run. The earlier version treated any differing run
# of <=4 bytes as a relocation slot, which blessed register renames, swapped
# instruction pairs and different SETcc forms as matches: it reported 100.0% for
# functions diff_retail.py scored as low as 59.5%. Because verify_tus.py accepts
# either oracle, that also meant a regression producing short differing runs
# would not have been caught. Same defect, and same fix, as the zero-window
# heuristic removed from diff_retail.py.
#
# Usage:
#   raw_match.py --obj build-vc6/packet_class.obj \
#                --sym '?HostToNet@FieldClass@@QAEXXZ' --addr 0x4CB8B0 --len 0x5A
#
# Exit 0 iff every byte difference lies in a relocation slot.
import argparse, json, os, struct, subprocess, sys

GHIDRA = os.path.expanduser("~/.cargo/bin/ghidra")


def retail_bytes(addr, n):
    r = subprocess.run([GHIDRA, "memory", "read", hex(addr), str(n)],
                       capture_output=True, text=True).stdout
    return bytes.fromhex(json.loads(r)[0]["hex"])


def obj_func_bytes(obj, sym, n):
    """Slice `n` bytes of `sym` out of the COFF .obj's section raw data.

    Returns (bytes, reloc_offsets) where reloc_offsets are relative to the start
    of the function. With /Gy each function is its own COMDAT section, so the
    section's relocation table belongs to this function alone."""
    with open(obj, "rb") as stream:
        d = stream.read()
    nsec, = struct.unpack_from("<H", d, 2)
    sptr, nsym = struct.unpack_from("<II", d, 8)
    strtab = sptr + nsym * 18
    sec_raw, sec_rel = {}, {}
    for i in range(nsec):
        o = 20 + i * 40
        sec_raw[i + 1] = struct.unpack_from("<I", d, o + 20)[0]
        # PointerToRelocations at +24, NumberOfRelocations at +32.
        sec_rel[i + 1] = (struct.unpack_from("<I", d, o + 24)[0],
                          struct.unpack_from("<H", d, o + 32)[0])
    want = sym.encode()
    i = 0
    while i < nsym:
        o = sptr + i * 18
        # Auxiliary records are not symbols, even if their payload resembles one.
        i += 1 + d[o + 17]
        name = d[o:o + 8]
        if name[:4] == b"\0\0\0\0":
            so = struct.unpack_from("<I", d, o + 4)[0]
            nm = d[strtab + so:d.find(b"\0", strtab + so)]
        else:
            nm = name.rstrip(b"\0")
        if nm == want:
            val = struct.unpack_from("<I", d, o + 8)[0]
            sec = struct.unpack_from("<h", d, o + 12)[0]
            # VC6 can put an undefined declaration before the same name's
            # defined COMDAT (notably template deleting destructors). Keep
            # searching; undefined/absolute/debug symbols have no section bytes.
            if sec <= 0:
                continue
            base = sec_raw[sec]
            rptr, rcount = sec_rel[sec]
            relocs = set()
            for k in range(rcount):
                ro = rptr + k * 10          # VirtualAddress, SymbolTableIndex, Type
                rva = struct.unpack_from("<I", d, ro)[0]
                if val <= rva < val + n:
                    relocs.add(rva - val)
            return d[base + val:base + val + n], relocs
    return None, set()


def runs(diffs):
    out = []
    if not diffs:
        return out
    s = p = diffs[0]
    for x in diffs[1:]:
        if x == p + 1:
            p = x
        else:
            out.append((s, p)); s = p = x
    out.append((s, p))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--obj", required=True)
    ap.add_argument("--sym", required=True)
    ap.add_argument("--addr", required=True)
    ap.add_argument("--len", required=True)
    a = ap.parse_args()
    n = int(a.len, 16)
    rb = retail_bytes(int(a.addr, 16), n)
    ob, relocs = obj_func_bytes(a.obj, a.sym, n)
    if ob is None:
        print(f"raw_match: symbol {a.sym} not found in {a.obj}"); sys.exit(2)
    diffs = [i for i in range(n) if rb[i] != ob[i]]
    rr = runs(diffs)

    # Cover byte-by-byte rather than run-by-run. `runs()` merges adjacent
    # differing bytes, so two neighbouring relocated dwords — a switch jump table
    # is a row of them — form one eight-byte run that fits inside no single
    # four-byte field. Testing coverage per byte gets those right while still
    # rejecting anything outside a recorded field.
    covered = set()
    for r in relocs:
        covered.update(range(r, r + 4))

    def is_reloc(lo, hi):
        return all(i in covered for i in range(lo, hi + 1))

    reloc = [r for r in rr if is_reloc(*r)]
    real = [r for r in rr if not is_reloc(*r)]
    for s, e in rr:
        tag = "reloc" if is_reloc(s, e) else "**REAL**"
        print(f"  {s:#06x}..{e:#06x} {tag}  retail={rb[s:e+1].hex()} obj={ob[s:e+1].hex()}")
    print(f"{n - len(diffs)}/{n} bytes identical; "
          f"{len(reloc)} reloc slot(s), {len(real)} real diff(s)")
    print("match: 100.0%" if not real else "match: <100% (real diffs)")
    sys.exit(0 if not real else 1)


if __name__ == "__main__":
    main()

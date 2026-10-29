#!/usr/bin/env python3
# Provenance: original. Import-address-table reader for the pinned retail image (names attested by the PE itself).
import functools
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
import common  # noqa: E402


@functools.lru_cache(None)
def iat():
    """IAT slot VA -> (dll, import name)."""
    pe = common.pe()
    d = pe.data
    peoff = struct.unpack_from("<I", d, 0x3C)[0]
    opt = peoff + 24
    # PE32 data directory 1 = import table
    imp_rva = struct.unpack_from("<I", d, opt + 96 + 8)[0]
    base = pe.base

    def rva_off(rva):
        for name, va, vsize, roff, rsize in pe.sections:
            if va - base <= rva < va - base + max(vsize, rsize):
                return roff + rva - (va - base)
        return None

    out = {}
    off = rva_off(imp_rva)
    while off is not None:
        ilt, _, _, name_rva, iat_rva = struct.unpack_from("<IIIII", d, off)
        if not name_rva and not iat_rva:
            break
        dll = d[rva_off(name_rva):].split(b"\0", 1)[0].decode()
        thunk = rva_off(ilt or iat_rva)
        k = 0
        while True:
            v = struct.unpack_from("<I", d, thunk + 4 * k)[0]
            if v == 0:
                break
            if v & 0x80000000:
                nm = f"#{v & 0xFFFF}"
            else:
                o = rva_off(v)
                nm = d[o + 2:].split(b"\0", 1)[0].decode()
            out[base + iat_rva + 4 * k] = (dll, nm)
            k += 1
        off += 20
    return out


if __name__ == "__main__":
    t = iat()
    print(len(t))
    for a in sorted(t)[:5]:
        print(hex(a), t[a])

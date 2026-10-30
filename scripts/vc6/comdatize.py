#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""COFF post-pass for objects written by the toolchain's ml.exe (MASM 6.15).

ml emits one non-COMDAT .text section per object, and LINK cannot place such a section through
/ORDER (warning LNK4065). The original hand-written assembly objects are one COMDAT-like unit
each, so this pass marks every executable .text section IMAGE_SCN_LNK_COMDAT and sets the
selection byte of its section-symbol aux record to ANY. The bytes, symbols and relocations are
left alone.

Usage: comdatize.py IN.obj [OUT.obj]    (in place when OUT is omitted)
"""
import struct
import sys

import coffgen

CNT_CODE = coffgen.SCN_CNT_CODE


def comdatize(data):
    """Return (object bytes, number of sections converted)."""
    data = bytearray(data)
    if struct.unpack_from("<H", data, 0)[0] != coffgen.I386:
        raise ValueError("not an i386 COFF object")
    nsec = struct.unpack_from("<H", data, 2)[0]
    symptr = struct.unpack_from("<I", data, 8)[0]
    converted = 0
    for idx in range(1, nsec + 1):
        off = 20 + 40 * (idx - 1)
        name = bytes(data[off:off + 8]).rstrip(b"\0")
        flags = struct.unpack_from("<I", data, off + 36)[0]
        if name != b".text" or not flags & CNT_CODE or flags & coffgen.SCN_LNK_COMDAT:
            continue
        aux = None
        for sidx, sname, value, sec, scl, naux in coffgen.read_symbols(bytes(data)):
            if sec == idx and scl == coffgen.CLASS_STATIC and value == 0 and naux and sname == ".text":
                aux = symptr + 18 * (sidx + 1)
                break
        if aux is None:
            raise ValueError("section symbol for .text not found")
        struct.pack_into("<I", data, off + 36, flags | coffgen.SCN_LNK_COMDAT)
        data[aux + 14] = coffgen.COMDAT_ANY
        converted += 1
    return bytes(data), converted


def main(argv):
    if len(argv) not in (2, 3):
        print(__doc__.strip().splitlines()[-1], file=sys.stderr)
        return 2
    out = argv[-1]
    with open(argv[1], "rb") as stream:
        result, count = comdatize(stream.read())
    if not count:
        print("comdatize: no non-COMDAT .text section in " + argv[1], file=sys.stderr)
        return 1
    with open(out, "wb") as stream:
        stream.write(result)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))

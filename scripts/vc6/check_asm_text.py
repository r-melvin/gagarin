#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original.
"""Assemble each match/asm/*.asm with vc6asm.sh and compare its .text sha256 to asm_text_hashes.json.

The recorded hashes come from building our own source (ml.exe and JWasm agree), so this is a
binary-free CI check that the open-source assembler still produces the expected code.
Usage: check_asm_text.py [--update] [file.asm ...]   (default: every match/asm/*.asm)
"""
import hashlib
import json
import os
import struct
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
TABLE = os.path.join(HERE, "asm_text_hashes.json")


def text_bytes(data):
    """Raw bytes of the first .text section of a COFF object."""
    nsec = struct.unpack_from("<H", data, 2)[0]
    for i in range(nsec):
        off = 20 + 40 * i
        name, _, _, size, ptr = struct.unpack_from("<8sIIII", data, off)
        if name.rstrip(b"\0") == b".text":
            return data[ptr:ptr + size]
    raise ValueError("no .text section")


def assemble(asm, tmp):
    obj = os.path.join(tmp, os.path.basename(asm) + ".obj")
    r = subprocess.run(["bash", os.path.join(HERE, "vc6asm.sh"), "/Fo" + obj, os.path.basename(asm)],
                       cwd=os.path.dirname(os.path.abspath(asm)), capture_output=True, text=True)
    if r.returncode != 0 or not os.path.isfile(obj):
        raise RuntimeError("vc6asm failed (%d): %s" % (r.returncode, (r.stdout + r.stderr)[-400:]))
    with open(obj, "rb") as f:
        return f.read()


def main(argv):
    update = "--update" in argv
    files = [a for a in argv if a != "--update"]
    if not files:
        d = os.path.join(REPO, "match", "asm")
        files = sorted(os.path.join(d, n) for n in os.listdir(d) if n.lower().endswith(".asm"))
    table = json.load(open(TABLE)) if os.path.isfile(TABLE) else {}
    bad = 0
    with tempfile.TemporaryDirectory() as tmp:
        for asm in files:
            key = os.path.basename(asm)
            got = hashlib.sha256(text_bytes(assemble(asm, tmp))).hexdigest()
            if update:
                table[key] = got
                print("update %s %s" % (key, got))
            elif table.get(key) == got:
                print("ok   %s" % key)
            else:
                print("FAIL %s: .text sha256 %s, expected %s" % (key, got, table.get(key)))
                bad = 1
    if update:
        with open(TABLE, "w") as f:
            json.dump(table, f, indent=2, sort_keys=True)
            f.write("\n")
    return bad


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

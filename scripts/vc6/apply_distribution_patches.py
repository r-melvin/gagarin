#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; compiles source stand-ins, embeds no retail bytes.
"""Post-link distribution-patch step (AGENTS.md, "Distribution patches").

The pinned image carries post-link patches over the first instructions of a few
functions. scripts/data/distribution_patches.json records each site with a trivial
C++ stand-in body. This step compiles every stand-in with the project toolchain,
takes the compiled function's bytes from the object, checks that their length is
the recorded patch length, and writes them over the site in a linked image. It is
the only permitted post-link step.

Usage:
  scripts/vc6/apply_distribution_patches.py --image LINKED.exe [--out PATCHED.exe]
      [--check-against gamemd.exe]
Without --out the image is patched in place.
"""
import argparse
import json
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import coffgen  # noqa: E402
from verify_vtable import ROOT, load_pe  # noqa: E402

PATCHES = ROOT / "scripts/data/distribution_patches.json"


def stand_in_source(patches):
    """One translation unit with every stand-in as an extern "C" function named by address."""
    lines = ["// Distribution-patch stand-ins (generated at build time; not recovered source).\n",
             "struct tagMSG; typedef struct tagMSG MSG;\n"]
    for p in patches:
        s = p["stand_in"]
        name = f"gg_patch_{int(p['addr'], 16):08X}"
        sig = s["signature"].replace(" f(", f" {name}(", 1)
        if f" {name}(" not in sig:
            raise SystemExit(f"stand-in signature for {p['addr']} has no ' f(': {s['signature']!r}")
        lines.append(f'extern "C" {sig} {{ {s["body"]} }}\n')
    return "".join(lines)


def section_bytes(obj, stem):
    """Raw bytes of the section defining the symbol whose undecorated name is `stem`."""
    for _, name, value, section, _, _ in coffgen.read_symbols(obj):
        if section > 0 and name.lstrip("_@").split("@")[0] == stem:
            hdr = 20 + 40 * (section - 1)
            size, ptr = struct.unpack_from("<II", obj, hdr + 16)
            return obj[ptr + value:ptr + size]
    raise SystemExit(f"stand-in symbol {stem} not found in the compiled object")


def compile_stand_ins(patches):
    with tempfile.TemporaryDirectory(dir=ROOT / "build-vc6") as tmp:
        tmp = Path(tmp)
        (tmp / "stand_ins.cpp").write_text(stand_in_source(patches), encoding="latin-1")
        proc = subprocess.run(["bash", str(ROOT / "scripts/vc6/vc6cl.sh"), "/Gy", "/Fostand_ins.obj",
                               "stand_ins.cpp"], cwd=tmp, capture_output=True, text=True)
        objpath = tmp / "stand_ins.obj"
        if proc.returncode or not objpath.is_file():
            raise SystemExit(f"stand-in compile failed:\n{proc.stdout}{proc.stderr}")
        obj = objpath.read_bytes()
    out = {}
    for p in patches:
        code = section_bytes(obj, f"gg_patch_{int(p['addr'], 16):08X}")
        # VC6 pads each /Gy function section to 16 bytes with NOPs; the stand-in must
        # fill exactly patch_len bytes before that padding.
        n = p["patch_len"]
        if len(code) < n or any(b != 0x90 for b in code[n:]) or (n < len(code) and code[n - 1] == 0x90):
            raise SystemExit(f"{p['addr']}: stand-in compiles to {code.hex()}, which does not fill "
                             f"exactly patch_len={n} bytes")
        out[p["addr"]] = code[:n]
    return out


def file_offset(sections, va, size):
    for _, start, vsize, rawptr, rawsize in sections:
        if start <= va and va + size <= start + min(vsize, rawsize):
            return rawptr + va - start
    raise SystemExit(f"{va:#x} is not file-backed in the image")


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument("--image", required=True, type=Path, help="linked image to patch")
    ap.add_argument("--out", type=Path, help="write the patched image here instead of in place")
    ap.add_argument("--check-against", type=Path,
                    help="pinned retail image: report whether every patched site now equals it")
    args = ap.parse_args(argv)

    spec = json.loads(PATCHES.read_text())
    patches = spec["patches"]
    code = compile_stand_ins(patches)

    target = args.out or args.image
    if args.out:
        shutil.copyfile(args.image, args.out)
    import hashlib
    data = bytearray(target.read_bytes())
    _, _, sections = load_pe(target, hashlib.sha256(data).hexdigest())
    for p in patches:
        va = int(p["addr"], 16)
        off = file_offset(sections, va, p["patch_len"])
        data[off:off + p["patch_len"]] = code[p["addr"]]
    target.write_bytes(bytes(data))
    print(f"applied {len(patches)} distribution patches to {target}")

    if args.check_against:
        retail, _, rsec = load_pe(args.check_against, spec["binary_sha256"])
        bad = []
        for p in patches:
            va, n = int(p["addr"], 16), p["patch_len"]
            ro = file_offset(rsec, va, n)
            if retail[ro:ro + n] != code[p["addr"]]:
                bad.append(p["addr"])
        print(f"patched sites equal to the pinned image: {len(patches) - len(bad)}/{len(patches)}"
              + (f"; differ: {', '.join(bad)}" if bad else ""))
        return 1 if bad else 0
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

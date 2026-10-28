#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the developer-supplied pinned PE only.
"""Find patched function prologues in retail .text (distribution patches).

A distribution patch (a no-CD fix, say) overwrites the first bytes of a function
with a short stub such as `mov al,1 ; ret`. The rest of the original body is
left in place directly behind it, so retail shows a tiny "function" glued to
code that has an epilogue but no matching prologue. For every position where
a short stub (`mov r,imm ; ret[n]`, `xor r,r ; ret`, `mov r,r ; ret`, a bare
`ret[n]`, or a `jmp`) can start - every 16-aligned address and every entry of
function_extents.json / the Ghidra function list - the tool checks that:

  * the byte after the stub is not padding (cc / 90 / 00) and not a jump table;
  * decoding on from there (objdump, linear, up to the first ret) ends in an epilogue
    (register pops, `add esp,N`, `leave`) that the code's own start does not
    set up with matching pushes / `sub esp,N` / a frame - an epilogue without a prologue.

A candidate with that last property is "high" confidence; one that only
continues into non-padding code is "low" and listed only with --all.
The output is JSON of addresses, lengths and instruction text; no bytes.

Usage:
  GAMEMD_BINARY=/path/gamemd.exe scripts/vc6/patch_scan.py [--out FILE] [--all]
"""

import argparse
import json
import os
from pathlib import Path
import re
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import extent_census as ec  # noqa: E402

DATA = ec.DATA
PAD = (0xCC, 0x90, 0x00)
REG8 = "[0-7]"
# Byte patterns of stub bodies (without the terminator): mov r8,imm8 | mov r32,imm32 |
# xor/mov/or r,r (modrm mod=3) | push imm8 ; pop r | or eax,-1 | mov eax,[esp]
BODY = (rb"(?:[\xb0-\xb7].|[\xb8-\xbf].{4}|[\x31\x33\x89\x8b\x29\x2b][\xc0-\xff]"
        rb"|\x6a.[\x58-\x5f]|\x83\xc8\xff|\x8b\x04\x24|)")
STUB = re.compile(rb"(?s)(?:" + BODY + rb")(?:\xc3|\xc2..)|\xe9.{4}|\xeb.")


def stub_at(text, off):
    m = STUB.match(text, off)
    if not m or m.end() - off > 10:
        return 0
    return m.end() - off


SAVED = ("ebx", "esi", "edi", "ebp", "ecx", "edx", "eax")


def analyse(img, start):
    """Decode linearly from start up to the first ret; compare the epilogue with the prologue.

    The epilogue is the run of pops / `add esp,N` / `leave` / `mov esp,ebp` right before the
    ret. The prologue zone is the code before the first call / branch / ret, where the
    register pushes, `sub esp,N` and `mov ebp,esp` are collected. Registers popped but never pushed there, an `add esp,N` that
    is not a call clean-up and has no `sub esp,N`, or a frame teardown without a frame
    set-up are an epilogue without a prologue. (Pushes of arguments for stdcall calls make
    a plain stack-depth count unreliable, which is why the runs are compared instead.)
    """
    ins = ec.objdump(img.read(start, 0x400), start)
    seq = []
    for a in sorted(ins):
        txt = ins[a][1]
        if txt.startswith("(bad)") or txt.startswith(".byte"):
            return {"decodes": False}
        seq.append((a, txt))
        if re.match(r"ret\b", txt) or txt.startswith("jmp") or len(seq) > 250:
            break
    if not seq or not re.match(r"ret\b", seq[-1][1]):
        return {"decodes": True, "ret_at": None, "insns": len(seq)}
    pushed, subs, frame = [], [], False
    for _, txt in seq:
        if txt.startswith(("call", "j", "ret")):
            break
        m = re.fullmatch(r"push\s+(\w+)", txt)
        if m and m.group(1) in SAVED:
            pushed.append(m.group(1))
        elif m := re.fullmatch(r"sub\s+esp,(0x[0-9a-f]+)", txt):
            subs.append(int(m.group(1), 16))
        elif txt == "mov ebp,esp":
            frame = True
    popped, adds, teardown = [], [], False
    for i in range(len(seq) - 2, -1, -1):
        txt = seq[i][1]
        m = re.fullmatch(r"pop\s+(\w+)", txt)
        if m:
            popped.append(m.group(1))
        elif m := re.fullmatch(r"add\s+esp,(0x[0-9a-f]+)", txt):
            if i > 0 and seq[i - 1][1].startswith("call"):
                break
            adds.append(int(m.group(1), 16))
        elif txt == "leave" or txt == "mov esp,ebp":
            teardown = True
        else:
            break
    left = list(pushed)
    unmatched = []
    for r in popped:
        if r in left:
            left.remove(r)
        else:
            unmatched.append(r)
    adds_unmatched = [n for n in adds if n not in subs]
    return {"decodes": True, "insns": len(seq), "ret_at": f"{seq[-1][0]:#x}",
            "epilogue_pops": popped[::-1], "prologue_pushes": pushed,
            "pops_without_push": unmatched[::-1], "add_esp_without_sub": adds_unmatched,
            "frame_teardown_without_setup": teardown and not frame}


def looks_like_table(img, start):
    """Next dwords are .text addresses (a jump table follows the stub)."""
    words = struct.unpack("<4I", img.read(start, 16).ljust(16, b"\0"))
    return all(0x401000 <= w < 0x401000 + 0x3DF38D for w in words)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--out", help="write JSON here (default stdout)")
    ap.add_argument("--all", action="store_true", help="also list low-confidence candidates")
    args = ap.parse_args()

    path = os.environ.get("GAMEMD_BINARY")
    if not path:
        sys.exit("GAMEMD_BINARY must point at the pinned gamemd.exe")
    img = ec.Image(path)
    _, base, vsize, _, rawsize = img.text
    text = img.read(base, min(vsize, rawsize))

    extents = {int(e[0], 16): e for e in json.loads((DATA / "function_extents.json").read_text())["entries"]}
    ghidra = {int(f["addr"], 16): f.get("ghidra_name") for f in
              json.loads((DATA / "ret_imm_census.json").read_text())["functions"]
              if f.get("entry_source") == "ghidra-function-list"}
    manifest = {}
    for r in json.loads((DATA / "match_manifest.json").read_text()):
        manifest.setdefault(int(r["addr"], 16), r)

    # Entries, plus 16-aligned addresses that no known function's extent covers.
    covered = bytearray(len(text))
    for a, e in extents.items():
        if 0 <= a - base < len(text):
            lo = a - base
            covered[lo + 1:lo + int(e[1], 16)] = b"\1" * max(0, min(int(e[1], 16), len(text) - lo) - 1)
    entries = set(extents) | set(ghidra)
    aligned = {v for v in range(base - base % 16 + (16 if base % 16 else 0), base + len(text), 16)
               if not covered[v - base]}
    positions = sorted(entries | aligned)
    out = []
    for va in positions:
        off = va - base
        if not 0 <= off < len(text):
            continue
        n = stub_at(text, off)
        if not n:
            continue
        m = re.match(rb"\xc2(..)", text[off + n - 3:off + n]) if n >= 3 else None
        if m and (struct.unpack("<H", m.group(1))[0] > 0x40 or struct.unpack("<H", m.group(1))[0] % 4):
            continue
        if text[off] in (0xE9, 0xEB) and va not in entries:
            continue
        nxt = off + n
        if nxt >= len(text) or text[nxt] in PAD:
            continue
        if looks_like_table(img, va) or looks_like_table(img, va + n):
            continue
        if va not in entries and off and text[off - 1] not in PAD:
            continue   # mid-function: the stub is the tail of the preceding code
        ins = ec.objdump(img.read(va, n), va)
        stub_insns = [ins[a][1] for a in sorted(ins) if a < va + n]
        if stub_insns and stub_insns[0].startswith("jmp"):
            # a bare jmp is only interesting if the stub is an unfollowed entry; require ret-less tail
            pass
        ev = analyse(img, va + n)
        unbalanced = bool(ev.get("ret_at")) and bool(
            ev["pops_without_push"] or ev["add_esp_without_sub"] or ev["frame_teardown_without_setup"])
        nxt_entry = extents.get(va + n)
        evidence = {
            "followed_by_non_padding": True,
            "next_entry_at_stub_end": bool(nxt_entry),
            "next_entry_16_aligned": (va + n) % 16 == 0,
            "ghidra_entry": va in ghidra,
            "epilogue_without_prologue": unbalanced,
            "continuation": ev,
        }
        if not unbalanced and not args.all:
            continue
        row = manifest.get(va)
        out.append({
            "addr": f"{va:#X}".replace("0X", "0x"),
            "stub_len": n,
            "stub_insns": stub_insns,
            "region": ec.kind_of(va),
            "confidence": "high" if unbalanced else "low",
            "evidence": evidence,
            "continuation_entry": (f"{va + n:#x}" if nxt_entry else None),
            "manifest": ({"name": row.get("name"), "status": row.get("status"), "len": row.get("len")}
                         if row else None),
            "ghidra_name": ghidra.get(va),
        })

    result = {"schema": "gagarin/patch_scan/1", "binary_sha256": ec.SHA256,
              "generated_by": "scripts/vc6/patch_scan.py", "candidates": out}
    text_out = json.dumps(result, indent=1) + "\n"
    if args.out:
        Path(args.out).write_text(text_out)
    else:
        sys.stdout.write(text_out)
    print(f"{sum(1 for c in out if c['confidence'] == 'high')} high-confidence, {len(out)} listed",
          file=sys.stderr)


if __name__ == "__main__":
    main()

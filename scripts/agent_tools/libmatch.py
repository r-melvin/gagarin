#!/usr/bin/env python3
# Provenance: original; reads our toolchain's LIBCMT.LIB and our pinned PE.
"""libmatch.py — locate VC6 runtime library functions in retail .text.

Usage: libmatch.py [LIB ...] [--out PATH] [--min 8]
  default LIB: $GAG_MAIN/toolchain/MSVC600/VC98/Lib/LIBCMT.LIB

Every code section of every archive member is cut into functions at its
defined function symbols. Each function's bytes are searched for in the
retail .text with its relocation fields (DIR32/REL32/…, 4 bytes) as
wildcards. A function found exactly once, of --min (8) or more bytes, is kept.

Output: $GAG_WORKTREE/state/orchestration/library_map.json
  found      [{addr, len, name, member, lib}]
  ambiguous  count of functions found 2+ times (skipped)
Then a diff against the repo's existing LIBRARY claims (there are no LIBRARY
manifest rows; the claims are `// LIBRARY: GAMEMD 0x...` annotations under
match/, plus manifest rows at the same address of any status):
  new         found here, no LIBRARY annotation and no manifest row
  confirmed   found here and annotated LIBRARY
  conflicts   found here but the address has a non-LIBRARY manifest row or
              FUNCTION annotation, or a LIBRARY annotation not found here
The manifest is never modified.
"""
import argparse
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common  # noqa: E402

DEFAULT_LIB = common.MAIN / "toolchain/MSVC600/VC98/Lib/LIBCMT.LIB"
RELOC_WIDTH = {0x0006: 4, 0x0007: 4, 0x0014: 4, 0x000B: 4, 0x000A: 2}  # DIR32, DIR32NB, REL32, SECREL, SECTION


def ar_members(path):
    data = Path(path).read_bytes()
    if not data.startswith(b"!<arch>\n"):
        raise SystemExit(f"{path}: not an archive")
    pos, longnames = 8, b""
    while pos + 60 <= len(data):
        hdr = data[pos:pos + 60]
        name = hdr[:16].decode("latin-1").strip()
        size = int(hdr[48:58].decode().strip())
        body = data[pos + 60: pos + 60 + size]
        pos += 60 + size + (size & 1)
        if name == "//":
            longnames = body
            continue
        if name == "/":
            continue
        if name.startswith("/") and name[1:].isdigit():
            off = int(name[1:])
            name = longnames[off:longnames.index(b"\0", off)].decode("latin-1")
        yield name.rstrip("/"), body


def coff_functions(blob):
    """Yield (symbol, bytes, wildcard_offsets) per function in an i386 COFF blob."""
    if len(blob) < 20 or struct.unpack_from("<H", blob)[0] != 0x14C:
        return
    _, nsec, _, symptr, nsyms, opt, _ = struct.unpack_from("<HHIIIHH", blob)
    secs = []
    for i in range(nsec):
        o = 20 + opt + 40 * i
        size, rawp, relp = struct.unpack_from("<III", blob, o + 16)
        nrel = struct.unpack_from("<H", blob, o + 32)[0]
        ch = struct.unpack_from("<I", blob, o + 36)[0]
        rel = [struct.unpack_from("<IIH", blob, relp + 10 * k) for k in range(nrel)]
        secs.append(dict(size=size, raw=rawp, rel=rel, code=bool(ch & 0x20)))
    strtab = symptr + nsyms * 18
    syms, i = {}, 0
    while i < nsyms:
        o = symptr + 18 * i
        raw = blob[o:o + 8]
        if raw[:4] == b"\0\0\0\0":
            so = strtab + struct.unpack_from("<I", raw, 4)[0]
            name = blob[so:blob.index(b"\0", so)].decode("latin-1")
        else:
            name = raw.rstrip(b"\0").decode("latin-1")
        val, sec, typ, cls, aux = struct.unpack_from("<IhHBB", blob, o + 8)
        if sec > 0 and secs[sec - 1]["code"] and cls in (2, 3) and (typ >> 4) == 2:
            syms.setdefault(sec, []).append((val, name))
        i += 1 + aux
    for sec, lst in syms.items():
        s = secs[sec - 1]
        lst = sorted(set(lst))
        code = blob[s["raw"]: s["raw"] + s["size"]]
        for k, (val, name) in enumerate(lst):
            end = lst[k + 1][0] if k + 1 < len(lst) else s["size"]
            if end <= val:
                continue
            wild = set()
            for rva, _, typ in s["rel"]:
                for b in range(RELOC_WIDTH.get(typ, 4)):
                    if val <= rva + b < end:
                        wild.add(rva + b - val)
            yield name, code[val:end], wild


def pattern(body, wild):
    out, i = [], 0
    while i < len(body):
        if i in wild:
            j = i
            while j in wild:
                j += 1
            out.append(b".{%d}" % (j - i))
            i = j
        else:
            out.append(re.escape(body[i:i + 1]))
            i += 1
    return re.compile(b"".join(out), re.S)


def scan(libs, min_len):
    start, text = common.pe().sect_bytes(".text")
    found, ambiguous, seen = [], 0, set()
    for lib in libs:
        for member, blob in ar_members(lib):
            for name, body, wild in coff_functions(blob):
                if len(body) < min_len or len(body) - len(wild) < min_len // 2:
                    continue
                key = (body, frozenset(wild))
                if key in seen:
                    continue
                seen.add(key)
                hits = [m.start() for m in pattern(body, wild).finditer(text)]
                if len(hits) == 1:
                    found.append(dict(addr=f"0x{start + hits[0]:X}", len=hex(len(body)), name=name,
                                      member=member, lib=Path(lib).name))
                elif len(hits) > 1:
                    ambiguous += 1
    found.sort(key=lambda r: int(r["addr"], 16))
    return found, ambiguous


def diff(found):
    ann = common.annotations()
    man = common.manifest_by_addr()
    lib_ann = {a for a, xs in ann.items() if any(k == "LIBRARY" for k, *_ in xs)}
    new, confirmed, conflicts, mislabelled = [], [], [], []
    hit = set()
    for r in found:
        a = int(r["addr"], 16)
        hit.add(a)
        kinds = {k for k, *_ in ann.get(a, [])}
        if "LIBRARY" in kinds:
            confirmed.append(r)
        elif a in man or any(k in ("FUNCTION", "SYNTHETIC", "TEMPLATE", "STUB") and p.lower().endswith(".cpp")
                             and not re.search(r"decl|referenced|reloc", rest)
                             for k, p, _, rest in ann.get(a, [])):
            conflicts.append(dict(r, reason="address carries a non-LIBRARY body claim",
                                  claim=[x["name"] for x in man.get(a, [])] +
                                  [f"{k} {p}:{l}" for k, p, l, _ in ann.get(a, [])]))
        elif kinds:
            mislabelled.append(dict(r, header_note=[f"{k} {p}:{l} {rest[:60]}" for k, p, l, rest in ann[a]][:2]))
        else:
            new.append(r)
    for a in sorted(lib_ann - hit):
        conflicts.append(dict(addr=f"0x{a:X}", reason="LIBRARY annotation not located by libmatch "
                              "(different lib/member, < min bytes, ambiguous, or not a library function)",
                              claim=[f"{p}:{l} {rest[:50]}" for k, p, l, rest in ann[a] if k == "LIBRARY"][:1]))
    return new, confirmed, conflicts, mislabelled


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("libs", nargs="*", default=[str(DEFAULT_LIB)])
    ap.add_argument("--out", type=Path, default=common.STATE / "library_map.json")
    ap.add_argument("--min", type=int, default=8)
    a = ap.parse_args(argv)
    found, amb = scan(a.libs, a.min)
    new, confirmed, conflicts, mislabelled = diff(found)
    a.out.parent.mkdir(parents=True, exist_ok=True)
    a.out.write_text(json.dumps(dict(libs=a.libs, min_len=a.min, found=found, ambiguous=amb,
                                     diff=dict(new=new, confirmed=confirmed, conflicts=conflicts, function_decl_not_library=mislabelled)), indent=1))
    print(f"found {len(found)} unique library functions ({amb} ambiguous skipped) -> {a.out}")
    print(f"  confirmed LIBRARY annotations: {len(confirmed)}")
    print(f"  new (no claim at all):         {len(new)}")
    print(f"  FUNCTION decls/references (no body) at a library address: {len(mislabelled)}")
    for r in mislabelled:
        print(f"    {r['addr']} {r['name']} [{r['member']}]  <- {r['header_note'][0]}")
    print(f"  conflicts:                     {len(conflicts)}")
    for c in conflicts:
        if c["reason"].startswith("address"):
            print(f"    {c['addr']} {c.get('name')} ({c.get('member')}) vs {c['claim']}")
    print("  first new candidates:")
    for r in new[:15]:
        print(f"    {r['addr']} {r['len']:>6} {r['name']}  [{r['member']}]")


if __name__ == "__main__":
    main()

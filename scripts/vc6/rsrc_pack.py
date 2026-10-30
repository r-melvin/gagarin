#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Resource build for gamemd: RC.EXE for the reconstructed script, plus the icon and cursor groups.

VC6's RC.EXE cannot make the retail icon and cursor resources: it numbers the images itself and
rejects PNG-compressed images. The groups are therefore described by match/rsrc/art_images.txt and
written here into the .res that RC.EXE produced:

  kind  group-id  file                          image ids (in the file's image order)
  icon  93        placeholder_icon_93.ico       1 2 3 4 8 9 ...
  cursor 104      placeholder_cursor_104.cur    8

The files in match/rsrc/ are blank placeholders (zero pixels, fully transparent) with the retail
groups' image count, dimensions, bit depths and byte sizes. RA2's own artwork is unreleased art and is
never committed. --art-from-retail replaces the icon and cursor resources by the ones in $GAMEMD_BINARY
(read at build time, written only under build-vc6/) so that the complete image can be compared with
retail byte for byte.

Usage:  rsrc_pack.py [--art-from-retail] [--out build-vc6/rsrc/gamemd.res]
"""
import argparse
import os
import struct
import subprocess
import sys
import zlib
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
RSRC = ROOT / "match/rsrc"
LANG_EN_US = 0x409
RT_CURSOR, RT_ICON, RT_GROUP_CURSOR, RT_GROUP_ICON = 1, 3, 12, 14


# ---------------------------------------------------------------- .res files

def res_record(rtype, name, data, lang=LANG_EN_US, flags=0x1030):
    header = struct.pack("<HHHH", 0xFFFF, rtype, 0xFFFF, name)
    header += struct.pack("<IHHII", 0, flags, lang, 0, 0)
    size = 8 + len(header)
    rec = struct.pack("<II", len(data), size) + header + data
    return rec + bytes(-len(rec) % 4)


def read_res(data):
    """[(type, name, lang, bytes)] of the numeric-id records of a 32-bit .res file."""
    out, p = [], 0
    while p < len(data):
        size, hsize = struct.unpack_from("<II", data, p)
        h = p + 8
        ids = []
        for _ in range(2):
            if struct.unpack_from("<H", data, h)[0] == 0xFFFF:
                ids.append(struct.unpack_from("<H", data, h + 2)[0])
                h += 4
            else:
                s = h
                while data[h:h + 2] != b"\0\0":
                    h += 2
                ids.append(data[s:h].decode("utf-16-le"))
                h += 2
        h = (h + 3) & ~3
        lang = struct.unpack_from("<H", data, h + 6)[0]
        if size or hsize != 32:
            out.append((ids[0], ids[1], lang, data[p + hsize:p + hsize + size]))
        p = (p + hsize + size + 3) & ~3
    return out


def write_res(records):
    """A .res of the records in type, then id order: CVTRES lays the data out in file order and retail's
    resource data is in the order of its directory tree."""
    return res_record_empty() + b"".join(res_record(t, n, d, l) for t, n, l, d in sorted(records, key=lambda r: r[:2]))


def res_record_empty():
    return struct.pack("<II", 0, 32) + struct.pack("<HHHH", 0xFFFF, 0, 0xFFFF, 0) + bytes(16)


# ---------------------------------------------------------------- blank images

def blank_png(w, h, size):
    """A fully transparent RGBA PNG of w x h, padded to `size` bytes with a private ancillary chunk."""
    def chunk(tag, body):
        return struct.pack(">I", len(body)) + tag + body + struct.pack(">I", zlib.crc32(tag + body))
    head = b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0))
    idat = chunk(b"IDAT", zlib.compress(bytes((w * 4 + 1) * h), 9))
    end = chunk(b"IEND", b"")
    pad = size - len(head) - len(idat) - len(end) - 12
    if pad < 0:
        raise ValueError(f"{w}x{h} PNG does not fit in {size} bytes")
    return head + chunk(b"pbDd", bytes(pad)) + idat + end


def dib_size(w, h, bpp):
    palette = 4 << bpp if bpp <= 8 else 0
    return 40 + palette + (w * bpp + 31) // 32 * 4 * h + (w + 31) // 32 * 4 * h


def blank_dib(w, h, bpp):
    """Icon DIB: zero colour data (palette entry 0 is black / alpha 0) and an all-ones AND mask."""
    palette = 4 << bpp if bpp <= 8 else 0
    xor = (w * bpp + 31) // 32 * 4 * h
    mask = (w + 31) // 32 * 4 * h
    hdr = struct.pack("<IiiHHIIiiII", 40, w, 2 * h, 1, bpp, 0, xor + mask, 0, 0, 1 << bpp if bpp <= 8 else 0, 0)
    return hdr + bytes(palette + xor) + b"\xff" * mask


def write_ico(path, entries):
    """entries: [(w, h, colour count, planes, bpp, image bytes)]; w, h of 256 are stored as 0."""
    out = struct.pack("<HHH", 0, 1, len(entries))
    off, body = 6 + 16 * len(entries), b""
    for w, h, cc, planes, bpp, data in entries:
        out += struct.pack("<BBBBHHII", w & 255, h & 255, cc, 0, planes, bpp, len(data), off + len(body))
        body += data
    Path(path).write_bytes(out + body)


def write_cur(path, w, h, planes, bpp, hotspot, data):
    out = struct.pack("<HHH", 0, 2, 1) + struct.pack("<BBBBHHII", w & 255, h & 255, 2 if bpp == 1 else 0, 0,
                                                     hotspot[0], hotspot[1], len(data), 22)
    Path(path).write_bytes(out + data)


def read_ico(path):
    d = Path(path).read_bytes()
    _, kind, count = struct.unpack_from("<HHH", d, 0)
    out = []
    for i in range(count):
        w, h, cc, _, a, b, size, off = struct.unpack_from("<BBBBHHII", d, 6 + 16 * i)
        out.append((w or 256, h or 256, cc, a, b, d[off:off + size]))
    return kind, out


# ---------------------------------------------------------------- groups

def manifest(rsrc=RSRC):
    rows = []
    for line in (rsrc / "art_images.txt").read_text().splitlines():
        line = line.split("#")[0].split()
        if line:
            rows.append((line[0], int(line[1]), line[2], [int(x) for x in line[3:]]))
    return rows


def art_records(rsrc=RSRC):
    """Icon / cursor resources for the groups of art_images.txt, from the placeholder files."""
    out = []
    for kind, gid, fname, ids in manifest(rsrc):
        _, images = read_ico(rsrc / fname)
        if len(images) != len(ids):
            raise ValueError(f"{fname}: {len(images)} images but {len(ids)} ids")
        if kind == "icon":
            group = struct.pack("<HHH", 0, 1, len(images))
            for (w, h, cc, planes, bpp, data), iid in zip(images, ids):
                group += struct.pack("<BBBBHHIH", w & 255, h & 255, cc, 0, planes, bpp, len(data), iid)
                out.append((RT_ICON, iid, LANG_EN_US, data))
            out.append((RT_GROUP_ICON, gid, LANG_EN_US, group))
        else:
            d = Path(rsrc / fname).read_bytes()
            group = struct.pack("<HHH", 0, 2, len(images))
            for i, ((w, h, cc, a, b, data), iid) in enumerate(zip(images, ids)):
                hx, hy = struct.unpack_from("<HH", d, 6 + 16 * i + 4)
                dw, dh, planes, bpp = struct.unpack_from("<iiHH", data, 4)
                body = struct.pack("<HH", hx, hy) + data
                group += struct.pack("<HHHHIH", dw, dh, planes, bpp, len(body), iid)
                out.append((RT_CURSOR, iid, LANG_EN_US, body))
            out.append((RT_GROUP_CURSOR, gid, LANG_EN_US, group))
    return out


def retail_images(binary):
    """{(type, id): image bytes} of the icon and cursor images of the pinned image (build-time read)."""
    sys.path.insert(0, str(HERE))
    import rsrc_decompile
    res, _, _ = rsrc_decompile.read_resources(binary)
    return {(t, n): d for t, n, l, d in res if t in (RT_CURSOR, RT_ICON)}


# ---------------------------------------------------------------- build

def compile_rc(rc, res):
    """Run RC.EXE on `rc` (cwd: its directory) producing `res`; returns the process."""
    res.parent.mkdir(parents=True, exist_ok=True)
    return subprocess.run(["bash", str(HERE / "vc6rc.sh"), "/r", "/fo", str(res), rc.name],
                          cwd=rc.parent, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)


def pack(rc_res, out, art_from_retail=False, rsrc=RSRC):
    """Write `out`: the records of RC.EXE's `rc_res` plus the icon and cursor groups. With art_from_retail the
    image data (not the group directories) of the same ids comes from $GAMEMD_BINARY."""
    records = [r for r in read_res(Path(rc_res).read_bytes())
               if r[0] not in (RT_CURSOR, RT_ICON, RT_GROUP_CURSOR, RT_GROUP_ICON)]
    art = art_records(rsrc)
    if art_from_retail:
        binary = os.environ.get("GAMEMD_BINARY")
        if not binary:
            raise SystemExit("rsrc_pack: --art-from-retail needs GAMEMD_BINARY")
        images = retail_images(binary)
        swapped = []
        for t, n, l, d in art:
            if t in (RT_CURSOR, RT_ICON):
                if len(images[(t, n)]) != len(d):
                    raise SystemExit(f"rsrc_pack: image {t}/{n} is {len(images[(t, n)])} bytes in retail, "
                                     f"{len(d)} in the placeholder")
                d = images[(t, n)]
            swapped.append((t, n, l, d))
        art = swapped
    out = Path(out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_bytes(write_res(records + art))
    return out


def rsrc_section(records):
    """(section bytes, [offsets of the data RVA fields], each holding the data's offset in the section) of the
    resource tree of [(type, id, lang, bytes)] in the layout of retail's .rsrc: the root directory, then
    every type directory, every name directory, the data entry records, and the data (4-aligned), with
    entries in ascending id order. This is not CVTRES's layout (it pads data to 8 bytes): the retail
    resource section was written by a resource updater, not by the linker."""
    recs = sorted(records, key=lambda r: r[:3])
    types = sorted({r[0] for r in recs})
    names = [(t, n) for t, n in sorted({r[:2] for r in recs})]
    by_type = {t: [n for tt, n in names if tt == t] for t in types}
    langs = {(t, n): [r[2] for r in recs if r[:2] == (t, n)] for t, n in names}
    size = lambda count: 16 + 8 * count
    offset = size(len(types))
    type_dir = {}
    for t in types:
        type_dir[t] = offset
        offset += size(len(by_type[t]))
    name_dir = {}
    for key in names:
        name_dir[key] = offset
        offset += size(len(langs[key]))
    entry_at = {}
    for r in recs:
        entry_at[r[:3]] = offset
        offset += 16
    data_at = {}
    for r in recs:
        data_at[r[:3]] = offset
        offset += len(r[3]) + (-len(r[3]) % 4)
    out = bytearray(offset)

    def directory(at, entries):
        struct.pack_into("<IIHHHH", out, at, 0, 0, 0, 0, 0, len(entries))
        for i, (ident, target, sub) in enumerate(entries):
            struct.pack_into("<II", out, at + 16 + 8 * i, ident, target | (0x80000000 if sub else 0))
    directory(0, [(t, type_dir[t], True) for t in types])
    for t in types:
        directory(type_dir[t], [(n, name_dir[(t, n)], True) for n in by_type[t]])
    for key in names:
        directory(name_dir[key], [(lang, entry_at[key + (lang,)], False) for lang in langs[key]])
    fields = []
    for r in recs:
        at = entry_at[r[:3]]
        struct.pack_into("<IIII", out, at, data_at[r[:3]], len(r[3]), 0, 0)
        fields.append(at)
        out[data_at[r[:3]]:data_at[r[:3]] + len(r[3])] = r[3]
    return bytes(out), fields


def rsrc_object(records, obj):
    """COFF object with the resource section (.rsrc$01) of `records`; each data entry's RVA is an
    IMAGE_REL_I386_DIR32NB relocation against the section."""
    data, fields = rsrc_section(records)
    flags = 0x40000040 | 0x00300000   # initialized data, read, 4-byte alignment
    relocs = b"".join(struct.pack("<IIH", at, 0, 7) for at in fields)   # DIR32NB against symbol 0
    # a relocated field holds its target's offset in the section, as the section data has it
    sect = 20 + 40
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, sect + len(data) + len(relocs), 2, 0, 0)
    sec = b".rsrc$01".ljust(8, b"\0") + struct.pack("<IIIIIIHHI", 0, 0, len(data), sect, sect + len(data), 0,
                                                    len(fields), 0, flags)
    symbol = b".rsrc$01".ljust(8, b"\0") + struct.pack("<IhHBB", 0, 1, 0, 3, 1)
    aux = struct.pack("<IHHIHBBBB", len(data), len(fields), 0, 0, 0, 0, 0, 0, 0)
    obj = Path(obj)
    obj.write_bytes(header + sec + data + relocs + symbol + aux + struct.pack("<I", 4))
    return obj


def build(out, rsrc=RSRC):
    """RC.EXE on gamemd.rc, then the icon and cursor groups: writes `out` (gamemd.res) and, beside it,
    gamemd_rc.res (RC.EXE's own output)."""
    out = Path(out)
    rc_res = out.with_name(out.stem + "_rc.res")
    proc = compile_rc(rsrc / "gamemd.rc", rc_res)
    if proc.returncode or not rc_res.is_file():
        raise SystemExit("rsrc_pack: RC.EXE failed\n" + proc.stdout)
    return pack(rc_res, out, False, rsrc)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", type=Path, default=ROOT / "build-vc6/rsrc/gamemd.res")
    ap.add_argument("--art-from-retail", action="store_true",
                    help="take the icon and cursor image data from $GAMEMD_BINARY (byte comparison only; "
                         "--out must be under build-vc6/)")
    args = ap.parse_args(argv)
    out = args.out.resolve()
    if args.art_from_retail and ROOT / "build-vc6" not in out.parents:
        ap.error("--art-from-retail embeds retail artwork: --out must be under build-vc6/")
    built = build(out)
    if args.art_from_retail:
        pack(out.with_name(out.stem + "_rc.res"), out, True)
    print(built)
    return 0


if __name__ == "__main__":
    sys.exit(main())

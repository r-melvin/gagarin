#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling (edits project sources and symbol_bindings.json; reads the pinned PE).
"""Define the string-pointer globals (and arrays of them) that matched code references but no object defines.

For each undefined data symbol whose declaration is a `const char*`/`char*` variable or an array of them, the
initialiser is read from the pinned image: every non-null element points at text, which is named by a
`const char STR_xxxxxxxx[]` global (an existing binding for that address, or a new one added to
symbol_bindings.json) and defined next to the pointer. Definitions that do not compile, mangle differently or add a
dynamic initialiser are removed by `define_globals.py prune` afterwards, like the scalar ones.

Usage: define_pointers.py --objdir build-vc6/gate     (then build, then define_globals.py prune --base ...)
"""
import argparse
import collections
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import data_undefined  # noqa: E402
import define_globals as dg  # noqa: E402
import hybrid  # noqa: E402
import pindata  # noqa: E402

ROOT = dg.ROOT
PTR = re.compile(r"^(?:extern\s+)?((?:const\s+)?char\s*\*(?:\s*const)?)\s*(\w+)((?:\[\d+\])?);")
STRING_DEF = re.compile(r'extern const char \w+\[\] = "')
SCALAR_MANGLE = {"PBDB": "const char* const", "PBDA": "const char*"}   # a char* cannot point at a const string


def bindings_by_address():
    d = json.loads((ROOT / "scripts/data/symbol_bindings.json").read_text())
    out = collections.defaultdict(list)
    for k, v in d.items():
        m = dg.MANGLED.fullmatch(k)
        if m and k.endswith("QBDB") and m.group(1).startswith("STR_"):
            out[int(v, 16)].append((m.group(1), k))
    return d, out


def run(objdir):
    users, names = data_undefined.collect(objdir)
    decls = dg.declarations()
    retail = hybrid.Retail(pindata.retail_path())
    bind, strs = bindings_by_address()
    new_bind = {}
    string_users = {}          # va -> ident
    chosen = {}                # va -> (tu, definition text)
    uses = collections.defaultdict(set)    # string va -> files that name it

    def target(v, tu):
        if v == 0:
            return "0"
        if not 0x7E1000 <= v < 0x812000 + 0x6C000 or dg.string_definition("x", v, retail) is None:
            return None
        if v in strs:
            ident = strs[v][0][0]
        else:
            ident = "STR_%08X" % v
            new_bind["?%s@@3QBDB" % ident] = "0x%08X" % v
        string_users.setdefault(v, (ident, tu))
        uses[v].add(tu)
        return ident

    for n, va in sorted(names.items(), key=lambda kv: kv[1]):
        m = dg.MANGLED.fullmatch(n)
        if not m or data_undefined.region_of(va) not in ("data", "rdata") or va in chosen:
            continue
        ident = m.group(1)
        if ident.startswith(("VT_", "VTBL_", "VTABLE_")):
            continue
        sym_type = n[len(ident) + 4:]
        want_const_ptr = sym_type.endswith("B")
        dl = [(p, t) for p, t in decls.get(ident, []) if PTR.match(t) and bool(re.search(r"\*\s*const\b", t.split(ident)[0])) == want_const_ptr]
        if not dl:
            continue
        p0, t0 = dl[0]
        pm = PTR.match(t0)
        if not pm.group(1).startswith("const"):
            continue
        tus = sorted(users[n])
        tu = p0 if p0 in tus else tus[0]
        count = int(pm.group(3)[1:-1]) if pm.group(3) else 0
        if not count:
            if sym_type not in SCALAR_MANGLE:
                continue
            typ = SCALAR_MANGLE[sym_type]
            v = struct.unpack("<I", bytes(retail.fill(va, 4)))[0]
            t = target(v, tu)
            if t is None:
                continue
            chosen[va] = (tu, f"extern {typ} {ident} = {t};")
        else:
            vals = struct.unpack("<%dI" % count, bytes(retail.fill(va, 4 * count)))
            ts = [target(v, tu) for v in vals]
            if None in ts:
                continue
            while len(ts) > 1 and ts[-1] == "0":
                ts.pop()
            chosen[va] = (tu, f"extern {pm.group(1)} {ident}[{count}] = {{{', '.join(ts)}}};")
    lines = collections.defaultdict(list)
    for va, (tu, text) in chosen.items():
        lines[tu].append((va, text))
    for v, (ident, home) in string_users.items():
        if v not in strs:
            lines[home].append((v, dg.string_definition(ident, v, retail)))
        for tu in uses[v] - ({home} if v not in strs else set()):
            lines[tu].append((v, f"extern const char {ident}[];"))
    pending = collections.defaultdict(list)
    for tu, items in sorted(lines.items()):
        path = ROOT / tu
        src = path.read_text()
        out = []
        for va, text in sorted(items, key=lambda x: (not text_is_decl(x[1]), 0 if STRING_DEF.match(x[1]) else 1, x[0])):
            out += [f"// GLOBAL: GAMEMD 0x{va:X}", text]
            if not text_is_decl(text):
                pending[tu].append(va)
        if dg.BEGIN in src:
            src = src.replace(dg.END, "\n".join(out) + "\n" + dg.END, 1)
        else:
            src = src.rstrip("\n") + "\n\n" + "\n".join([dg.BEGIN] + out + [dg.END]) + "\n"
        path.write_text(src)
    if new_bind:
        bind.update(new_bind)
        (ROOT / "scripts/data/symbol_bindings.json").write_text(json.dumps({k: bind[k] for k in sorted(bind)}, indent=1) + "\n")
    pp = ROOT / "build-vc6/define_pending.json"
    pp.write_text(json.dumps(pending))
    print(f"{len(chosen)} pointer definitions, {len(string_users)} strings ({len(new_bind)} new bindings) in {len(lines)} files")


def text_is_decl(text):
    return text.startswith("extern") and "=" not in text


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--objdir", type=Path, required=True)
    run(ap.parse_args().objdir.resolve())


if __name__ == "__main__":
    main()

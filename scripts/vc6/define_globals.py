#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling (edits project sources; reads the pinned PE only for section ranges).
"""Define the globals that matched code reaches through an extern but no object defines.

For each such symbol (data_undefined.py: exact, relocation based) whose `extern T name;` declaration is found in
the source, append `T name;` to a translation unit that references it (preferring one whose own file declares
it), under a marker block. The compiler's mangled name has to equal the referenced symbol's; definitions that
do not (a different declared type) or that bring a dynamic initialiser are removed again (`--prune`).
With --region data / rdata the declared type must be a plain integer, float or double (or an array of one) and
the initial value is read from the pinned image at the symbol's address (`extern const T x = v;` for rdata).

Usage: define_globals.py apply --objdir build-vc6/gate     append the blocks
       define_globals.py prune --objdir build-vc6/gate --base build-vc6/gate-base
                                                           after a rebuild: drop definitions that did not take
"""
import argparse
import collections
import json
import os
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import coffgen  # noqa: E402
import pindata  # noqa: E402
from verify_vtable import parse_coff  # noqa: E402
import data_undefined  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
BEGIN = "// BEGIN defined globals (define_globals.py)"
END = "// END defined globals"
DECL = re.compile(r'^\s*extern\s+(?!"C")(.+?[\s\*&>])(\w+)((?:\[[^\]]*\])*)\s*;\s*(?://.*)?$')
MANGLED = re.compile(r"\?(\w+)@@3(.+)[AB]$")
SCALARS = {"char": ("b", 1), "signed char": ("b", 1), "unsigned char": ("B", 1), "bool": ("B", 1), "short": ("h", 2),
           "unsigned short": ("H", 2), "int": ("i", 4), "unsigned int": ("I", 4), "unsigned": ("I", 4), "long": ("i", 4),
           "unsigned long": ("I", 4), "float": ("f", 4), "double": ("d", 8), "__int64": ("q", 8),
           "unsigned __int64": ("Q", 8)}


def declarations():
    out = collections.defaultdict(list)   # identifier -> [(path, "T name[..];")]
    for root, _, files in os.walk(ROOT / "match"):
        for f in files:
            if f.endswith((".cpp", ".h")):
                p = Path(root) / f
                for line in p.read_text(errors="replace").splitlines():
                    m = DECL.match(line)
                    if m and "(" not in line:
                        out[m.group(2)].append((p.relative_to(ROOT).as_posix(), f"{m.group(1).strip()} {m.group(2)}{m.group(3)};"))
    return out


def undefined(objdir):
    return data_undefined.collect(objdir)


def string_definition(ident, va, retail, limit=2048):
    """`extern const char x[];` -> the NUL-terminated text retail holds at va, or None when it is not text."""
    raw = bytes(retail.fill(va, limit))
    end = raw.find(b"\0")
    if end < 1:
        return None
    body = raw[:end]
    out = []
    for b in body:
        c = chr(b)
        if c in '"\\':
            out.append("\\" + c)
        elif c == "?":
            out.append("\\077")
        elif 32 <= b < 127:
            out.append(c)
        elif c in "\n\r\t":
            out.append({"\n": "\\n", "\r": "\\r", "\t": "\\t"}[c])
        else:
            out.append("\\%03o" % b)
    text = "".join(out)
    if sum(1 for b in body if b < 32 and chr(b) not in "\n\r\t") > len(body) // 4:
        return None
    return f'extern const char {ident}[] = "{text}";'


def initial_value(text, va, retail):
    """`extern const T x[n];` -> (definition with the value retail holds at va) or None when T is not a plain
    integer/float type or the value has no exact source spelling."""
    ms = re.fullmatch(r"(?:extern\s+)?const\s+char\s+(\w+)\[\];", text)
    if ms:
        return string_definition(ms.group(1), va, retail)
    mg = re.fullmatch(r"(?:extern\s+)?const\s+(GUID|CLSID|IID|FMTID|_GUID)\s+(\w+);", text)
    if mg:
        d1, d2, d3, tail = struct.unpack("<IHH8s", bytes(retail.fill(va, 16)))
        return (f"extern const {mg.group(1)} {mg.group(2)} = {{0x{d1:08X}, 0x{d2:04X}, 0x{d3:04X}, "
                f"{{{', '.join(f'0x{b:02X}' for b in tail)}}}}};")
    m = re.fullmatch(r"(?:extern\s+)?(const\s+)?([\w ]+?)\s+(\w+)((?:\[\d+\])*);", text)
    if not m or m.group(2).strip() not in SCALARS:
        return None
    const, typ, ident, dims = m.group(1), m.group(2).strip(), m.group(3), re.findall(r"\d+", m.group(4))
    code, width = SCALARS[typ]
    count = 1
    for d in dims:
        count *= int(d)
    if len(dims) > 1 or count * width > 4096 or count < 1:
        return None
    raw = bytes(retail.fill(va, count * width))
    values = struct.unpack("<" + code * count, raw)
    out = []
    for v, chunk in zip(values, (raw[i:i + width] for i in range(0, len(raw), width))):
        if code in "fd":
            t = repr(float(v))
            if "nan" in t or "inf" in t or struct.pack("<" + code, float(t)) != chunk:
                return None
            out.append(t + ("f" if code == "f" else ""))
        elif typ == "bool":
            if v > 1:
                return None
            out.append("true" if v else "false")
        elif code in "qQ":
            out.append(f"{v}i64")
        elif code in "IQ" and typ != "unsigned char":
            out.append(f"0x{v:X}" if v > 9 else str(v))
        else:
            out.append(str(v))
    while len(out) > 1 and out[-1] in ("0", "false", "0.0", "0.0f"):
        out.pop()
    init = out[0] if not dims else "{" + ", ".join(out) + "}"
    return f"{'extern const ' if const else ''}{typ} {ident}{m.group(4)} = {init};"


def apply(objdir, region="bss"):
    users, names = undefined(objdir)
    decls = declarations()
    retail = None
    if region != "bss":
        import hybrid
        retail = hybrid.Retail(pindata.retail_path())
    chosen = {}   # va -> (name, ident, text, tu)
    failed_path = ROOT / "build-vc6/define_failed.json"
    failed = json.loads(failed_path.read_text()) if failed_path.exists() else {}
    for n, va in sorted(names.items(), key=lambda kv: kv[1]):
        m = MANGLED.fullmatch(n)
        if not m or data_undefined.region_of(va) != region or va in chosen:
            continue
        ident = m.group(1)
        if ident in failed.get(str(va), ()):
            continue   # another name for this address is tried instead
        const = n.endswith("B")
        options = [(p, t) for p, t in decls.get(ident, []) if ("const" in t.split(ident)[0]) == const]
        if not options:
            continue
        tus = sorted(users[n])
        own = [(t, text) for t in tus for p, text in options if p == t]
        tu, text = own[0] if own else (tus[0], options[0][1])
        if region != "bss":
            if ident.startswith(("VT_", "VTBL_")):   # addresses inside vtables, not variables
                continue
            text = initial_value(text, va, retail)
            if text is None:
                continue
        chosen[va] = (n, ident, text, tu)
    by_tu = collections.defaultdict(list)
    for va, (n, ident, text, tu) in chosen.items():
        by_tu[tu].append((va, n, text))
    for tu, items in sorted(by_tu.items()):
        path = ROOT / tu
        src = path.read_text()
        lines = []
        for va, n, text in sorted(items):
            lines += [f"// GLOBAL: GAMEMD 0x{va:X}", text]
        if BEGIN in src:
            src = src.replace(END, "\n".join(lines) + "\n" + END, 1)
        else:
            src = src.rstrip("\n") + "\n\n" + "\n".join([BEGIN] + lines + [END]) + "\n"
        path.write_text(src)
    print(f"{len(chosen)} definitions in {len(by_tu)} translation units")
    (ROOT / "build-vc6/define_pending.json").write_text(json.dumps({tu: [va for va, _, _ in items] for tu, items in by_tu.items()}))


def prune(objdir, base):
    """Remove definitions whose object does not define the referenced symbol, or gained a dynamic initialiser."""
    users, names = undefined_names = data_undefined.collect(base)
    index = json.loads((objdir / "objects.json").read_text())
    base_index = json.loads((base / "objects.json").read_text())
    base_xcu = {}
    for o in base_index["objects"]:
        try:
            _, secs, _, _ = parse_coff(base / o["object"])
        except Exception:
            continue
        base_xcu[o["source"]] = sum(1 for s in secs.values() if s["name"].startswith(".CRT$XCU"))
    pending_json = json.loads((ROOT / "build-vc6/define_pending.json").read_text())   # written by the last apply
    removed = 0
    failed_path = ROOT / "build-vc6/define_failed.json"   # identifiers whose definition did not take, per address
    failed = json.loads(failed_path.read_text()) if failed_path.exists() else {}
    for o in index["objects"]:
        path = ROOT / o["source"]
        src = path.read_text()
        if BEGIN not in src:
            continue
        head, rest = src.split(BEGIN, 1)
        body, tail = rest.split(END, 1)
        lines = body.strip("\n").splitlines()
        pairs = [(lines[i], lines[i + 1]) for i in range(0, len(lines), 2)]
        try:
            _, secs, syms, _ = parse_coff(objdir / o["object"])
            ok = o["success"]
        except Exception:
            secs, syms, ok = {}, {}, False
        bad_lines = set()
        if not o["success"]:   # compile errors inside the block name the definitions that do not belong
            log = (objdir / o["log"]).read_text(errors="replace")
            first = head.count("\n") + 2   # 1-based line of the first definition's annotation
            for m in re.finditer(r"\((\d+)\) : (?:fatal )?error", log):
                bad_lines.add((int(m.group(1)) - first) // 2)
        defined = {s["name"] for s in syms.values() if s["section"] > 0 and s["storage_class"] == coffgen.CLASS_EXTERNAL}
        gained = ok and sum(1 for s in secs.values() if s["name"].startswith(".CRT$XCU")) > base_xcu.get(o["source"], 0)
        keep = []
        for pos, (ann, text) in enumerate(pairs):
            va = int(ann.split("0x")[1], 16)
            if va not in pending_json.get(o["source"], ()):   # defined by an earlier pass: not up for pruning
                keep.append((ann, text))
                continue
            ident = re.search(r"(\w+)(?:\[[^\]]*\])*\s*(?:=.*)?;$", text).group(1)
            name = next((n for n, v in names.items() if v == va and MANGLED.fullmatch(n) and MANGLED.fullmatch(n).group(1) == ident
                         and n in defined), None)
            if name is None and va not in names.values():   # a name made for an address nothing referenced by name
                name = next((n for n in defined if MANGLED.fullmatch(n) and MANGLED.fullmatch(n).group(1) == ident), None)
            if not o["success"]:
                if pos in bad_lines or not bad_lines:
                    removed += 1
                    failed.setdefault(str(va), []).append(ident)
                else:
                    keep.append((ann, text))
            elif not gained and name is not None:
                keep.append((ann, text))
            else:
                removed += 1
                failed.setdefault(str(va), []).append(ident)
        new = head.rstrip("\n") + "\n"
        if keep:
            new += "\n" + BEGIN + "\n" + "\n".join(f"{a}\n{t}" for a, t in keep) + "\n" + END + tail
        else:
            new += tail.lstrip("\n")
        path.write_text(new)
    failed_path.write_text(json.dumps(failed))
    print(f"removed {removed} definitions")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("mode", choices=["apply", "prune"])
    ap.add_argument("--objdir", type=Path, required=True)
    ap.add_argument("--base", type=Path)
    ap.add_argument("--region", default="bss", choices=["bss", "data", "rdata"])
    a = ap.parse_args()
    if a.mode == "apply":
        apply(a.objdir.resolve(), a.region)
    else:
        prune(a.objdir.resolve(), a.base.resolve())


if __name__ == "__main__":
    main()

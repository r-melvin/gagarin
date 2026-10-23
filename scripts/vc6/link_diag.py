#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling.
"""Diagnostic link (milestone M0): link every project object with the toolchain
libraries and report what is still missing.

Links the objects indexed by build_project.py with the VC6 LINK.EXE, the
toolchain LIBCMT/COMSUPP/LIBCPMT and import libraries, and a binkw32.lib built
from scripts/vc6/binkw32.def. /FORCE lets the link complete with unresolved
externals and duplicate definitions; the output image is a diagnostic
by-product and is NOT an engine build (no layout, no retail addresses).

The report groups unresolved externals by kind: engine functions, data and
globals, vtables and RTTI, CRT/toolchain-library names, and DLL imports. It
needs the toolchain and the object build, never the retail binary.

Usage:
  scripts/vc6/build_project.py --out OBJDIR
  scripts/vc6/link_diag.py --objdir OBJDIR [--out DIR] [--json FILE]
"""

import argparse
from collections import Counter, defaultdict
import json
import os
from pathlib import Path
import re
import struct
import subprocess
import sys

from verify_vtable import parse_coff, VerifyError


ROOT = Path(__file__).resolve().parents[2]
TOOL_LIBS = ["LIBCMT.LIB", "COMSUPP.LIB", "LIBCPMT.LIB"]
IMPORT_LIBS = ["KERNEL32.LIB", "USER32.LIB", "GDI32.LIB", "ADVAPI32.LIB", "SHELL32.LIB",
               "OLE32.LIB", "OLEAUT32.LIB", "WINMM.LIB", "WSOCK32.LIB", "DDRAW.LIB",
               "DSOUND.LIB", "VERSION.LIB", "COMCTL32.LIB", "IMM32.LIB"]
# /OPT:NOREF keeps every reference visible. /NODEFAULTLIB:LIBC: the project
# objects are compiled without /MT and so request LIBC, while retail links
# LIBCMT (see the M0 notes in the packet README).
LINK_FLAGS = ["/NOLOGO", "/FORCE", "/SUBSYSTEM:WINDOWS", "/FIXED", "/BASE:0x400000",
              "/INCREMENTAL:NO", "/OPT:NOREF", "/NODEFAULTLIB:LIBC", "/MACHINE:IX86"]
# Retail code range of the statically linked CRT and COMSUPP block. A
# placeholder FUN_<addr> inside it names a toolchain-library function.
CRT_CODE = (0x7C8A8E, 0x7E1000)
ADDRESS = re.compile(r"(?:FUN_|DAT_|_)(00[0-9A-Fa-f]{6})(?![0-9A-Fa-f])")
KINDS = ["function", "data", "vtable", "crt", "import"]

UNRESOLVED = re.compile(r'^(?P<obj>.*?) : (?:error|warning) LNK20(?:01|19): unresolved external symbol '
                        r'(?:"(?P<text>.*)" \((?P<msym>[^()]+)\)|(?P<sym>\S+))\s*$')
DUPLICATE = re.compile(r'^(?P<obj>.*?) : (?:error|warning) LNK2005: (?:"(?P<text>.*)" \((?P<msym>[^()]+)\)|(?P<sym>\S+)) '
                       r'already defined in (?P<other>\S+)\s*$')
CALLCONV_FN = re.compile(r"__(?:thiscall|cdecl|stdcall|fastcall) [^(*]*\(")
REL32 = 0x14


def wine_path(path):
    return "Z:" + str(Path(path).resolve()).replace("/", "\\")


def toolenv():
    vc6 = Path(os.environ.get("VC6_ROOT", ROOT / "toolchain/MSVC600"))
    env = dict(os.environ)
    env.setdefault("WINEPREFIX", str(ROOT / "toolchain/wineprefix"))
    env.setdefault("WINEDEBUG", "-all")
    env["WINEPATH"] = f"{vc6 / 'VC98/Bin'};{vc6 / 'Common/MSDev98/Bin'}"
    env["LIB"] = str(vc6 / "VC98/Lib")
    return vc6, env


def archive_symbols(path):
    """Public symbol names from a COFF archive's first linker member."""
    data = Path(path).read_bytes()
    if not data.startswith(b"!<arch>\n"):
        raise ValueError(f"{path} is not a COFF archive")
    size = int(data[8 + 48:8 + 58])
    body = data[68:68 + size]
    count = struct.unpack_from(">I", body)[0]
    names = body[4 + 4 * count:].split(b"\0")[:count]
    return {n.decode("latin-1") for n in names}


def parse_link_log(text):
    """Unresolved symbols -> (undecorated text or None, referencing objects); duplicates."""
    unresolved = {}
    duplicates = {}
    for line in text.splitlines():
        m = UNRESOLVED.match(line.strip())
        if m:
            sym = m.group("msym") or m.group("sym")
            entry = unresolved.setdefault(sym, {"text": m.group("text"), "objects": set()})
            entry["objects"].add(m.group("obj"))
            continue
        m = DUPLICATE.match(line.strip())
        if m:
            sym = m.group("msym") or m.group("sym")
            duplicates.setdefault(sym, set()).update({m.group("obj"), m.group("other")})
    return unresolved, duplicates


def called_relatively(sym, objects):
    """True when any referencing object has a REL32 (call/jump) relocation to sym."""
    for obj in objects:
        try:
            _, sections, symbols, _ = parse_coff(obj)
        except (OSError, VerifyError):
            continue
        indices = {i for i, s in symbols.items() if s["name"] == sym}
        for section in sections.values():
            if any(kind == REL32 and idx in indices for _, idx, kind in section["relocs"]):
                return True
    return False


def classify(sym, text, library_names, objects=()):
    if sym.startswith("__imp_"):
        return "import"
    if sym in library_names:
        return "crt"
    if sym.startswith(("??_7", "??_8", "??_R")) or re.match(r"^[?_]?VT_[0-9A-Fa-f]{8}", sym):
        return "vtable"
    if sym.startswith("?"):
        if text is not None:
            return "function" if CALLCONV_FN.search(text) else "data"
        return "function" if re.search(r"@@[A-Z]", sym) and not re.search(r"@@[0-4]", sym) else "data"
    if re.match(r"^_?(?:\?)?DAT_[0-9A-Fa-f]{8}", sym):
        return "data"
    fun = re.match(r"^[_@]?FUN_([0-9A-Fa-f]{8})", sym)
    if fun and CRT_CODE[0] <= int(fun.group(1), 16) < CRT_CODE[1]:
        return "crt"
    if fun or re.match(r"^[_@][^@]+@\d+$", sym):
        return "function"
    return "function" if called_relatively(sym, objects) else "data"


def build_bink_lib(vc6, env, out):
    lib = out / "binkw32.lib"
    subprocess.run(["wine", str(vc6 / "VC98/Bin/LIB.EXE"), "/NOLOGO",
                    "/DEF:" + wine_path(ROOT / "scripts/vc6/binkw32.def"), "/MACHINE:IX86",
                    "/OUT:" + wine_path(lib)], env=env, check=True,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return lib


def object_paths(objdir):
    index = json.loads((objdir / "objects.json").read_text(encoding="utf-8"))
    if not index.get("success"):
        raise ValueError("object index records an unsuccessful build; rebuild first")
    return [objdir / item["object"] for item in index["objects"]]


def run_link(objdir, out):
    vc6, env = toolenv()
    out.mkdir(parents=True, exist_ok=True)
    bink = build_bink_lib(vc6, env, out)
    objects = object_paths(objdir)
    rsp = out / "link.rsp"
    lines = LINK_FLAGS + ["/OUT:" + wine_path(out / "diag.exe"), "/MAP:" + wine_path(out / "diag.map")]
    lines += [f'"{wine_path(o)}"' for o in objects]
    lines += TOOL_LIBS + IMPORT_LIBS + [f'"{wine_path(bink)}"']
    rsp.write_text("\r\n".join(lines) + "\r\n", encoding="latin-1")
    proc = subprocess.run(["wine", str(vc6 / "VC98/Bin/LINK.EXE"), "@" + wine_path(rsp)],
                          env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    log = proc.stdout.decode("latin-1")
    (out / "link.log").write_text(log, encoding="latin-1")
    libdir = vc6 / "VC98/Lib"
    library_names = set()
    for name in TOOL_LIBS:
        library_names |= archive_symbols(libdir / name)
    return log, proc.returncode, (out / "diag.exe").is_file(), library_names, len(objects)


def unix_object(name, objdir):
    """Map a LINK-reported object (Z:\\...\\x.obj or relative) back to a POSIX path."""
    if name.startswith(("Z:", "z:")):
        return name[2:].replace("\\", "/")
    return str(objdir / name.replace("\\", "/"))


def report(log, library_names, objdir):
    unresolved, duplicates = parse_link_log(log)
    groups = defaultdict(list)
    addresses = defaultdict(set)
    for sym, entry in sorted(unresolved.items()):
        objs = [unix_object(o, objdir) for o in entry["objects"]]
        kind = classify(sym, entry["text"], library_names, objs)
        m = ADDRESS.search(sym)
        addr = "0x" + m.group(1).upper() if m else None
        if addr:
            addresses[kind].add(addr)
        groups[kind].append({"symbol": sym, "text": entry["text"], "address": addr,
                             "referenced_by": len(entry["objects"])})
    return {
        "unresolved_total": len(unresolved),
        "counts": {k: len(groups.get(k, [])) for k in KINDS},
        # Symbols that embed a retail address (FUN_/DAT_/Name_<addr>), and how
        # many distinct addresses they name: several project names can denote
        # one retail object (case variants, per-TU views).
        "with_address": {k: sum(1 for e in groups.get(k, []) if e["address"]) for k in KINDS},
        "distinct_addresses": {k: len(addresses.get(k, ())) for k in KINDS},
        "duplicate_definitions": len(duplicates),
        "groups": {k: groups.get(k, []) for k in KINDS},
        "duplicates": {s: sorted(o) for s, o in sorted(duplicates.items())},
    }


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--objdir", type=Path, default=ROOT / "build-vc6/project")
    ap.add_argument("--out", type=Path, default=ROOT / "build-vc6/link_diag")
    ap.add_argument("--json", type=Path, help="write the full report here (default OUT/report.json)")
    args = ap.parse_args(argv)
    objdir, out = args.objdir.resolve(), args.out.resolve()
    try:
        log, code, linked, library_names, nobj = run_link(objdir, out)
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        print(f"link_diag: {exc}", file=sys.stderr)
        return 2
    result = report(log, library_names, objdir)
    result.update({"objects": nobj, "link_exit_code": code, "image_written": linked})
    path = args.json or out / "report.json"
    path.write_text(json.dumps(result, indent=1) + "\n", encoding="utf-8")
    print(f"{nobj} objects linked; LINK exit {code}; image {'written' if linked else 'NOT written'}")
    print(f"unresolved externals: {result['unresolved_total']}")
    for kind in KINDS:
        print(f"  {kind:<9} {result['counts'][kind]:>6}   ({result['with_address'][kind]} name a retail "
              f"address; {result['distinct_addresses'][kind]} distinct)")
    print(f"duplicate definitions: {result['duplicate_definitions']}")
    print(f"report: {path}  (diagnostic only; not an engine image)")
    return 0 if linked else 1


if __name__ == "__main__":
    sys.exit(main())

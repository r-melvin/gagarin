#!/usr/bin/env python3
# Provenance: original. Compile and verification gates for trivgen (drives the repo's own scripts).
"""compile_bin / check_function: compile a generated TU with the worktree's VC6 wrapper,
then raw_match (byte compare modulo COFF relocation slots) and strict
verify_relocations with a symbol map built from the object itself."""
import json
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

import data

WT = data.WT
BIN = os.environ.get("GAMEMD_BINARY", str(data.common.EXE))
sys.path.insert(0, str(WT / "scripts" / "vc6"))
from verify_vtable import parse_coff  # noqa: E402

ERR = re.compile(r"^(\S+?)\((\d+)\)\s*:\s*(?:fatal )?error (C\d+)\s*:?\s*(.*)$")


def compile_bin(cpp_rel, timeout=300):
    """Compile `match/<mod>/<stem>.cpp` in the worktree. Returns (obj_path|None, [errors], log)."""
    src = WT / cpp_rel
    obj = WT / "build-vc6" / (src.stem + ".obj")
    (WT / "build-vc6").mkdir(exist_ok=True)
    if obj.exists():
        obj.unlink()
    with tempfile.TemporaryFile(mode="w+t", encoding="utf-8", errors="replace") as log:
        try:
            subprocess.run(["bash", str(WT / "scripts/vc6/vc6cl.sh"), "/Fo" + str(obj), src.name],
                           cwd=src.parent, stdout=log, stderr=subprocess.STDOUT, text=True, timeout=timeout)
        except subprocess.TimeoutExpired:
            return None, [("", 0, "timeout", "compile timeout")], ""
        log.seek(0)
        text = log.read()
    errors = []
    for line in text.splitlines():
        m = ERR.match(line.strip())
        if m:
            errors.append((m.group(1), int(m.group(2)), m.group(3), m.group(4)))
    ok = obj.exists() and not errors
    if not ok and obj.exists():
        obj.unlink()
    return (obj if ok else None), errors, text


def text_symbols(obj):
    data_, sections, symbols, aux = parse_coff(str(obj))
    return sections, symbols


def find_symbol(obj, addr, hint=None):
    """Defined text symbol whose decorated name carries FUN_<addr> (or the given fragment)."""
    sections, symbols = text_symbols(obj)
    tag = hint or f"FUN_{addr:08X}"
    found = {s["name"] for s in symbols.values() if tag in s["name"] and s["section"] in sections
             and sections[s["section"]]["name"].startswith(".text")}
    if len(found) != 1:
        return None
    return found.pop()


ADDR_NAME = re.compile(r"(?:DAT|FUN|VT)_([0-9A-F]{8})")


def symbol_map(obj):
    """symbol -> VA for every external/declared symbol whose name carries its own address,
    plus __imp__<name>[@n] -> the IAT slot of that import in the retail image."""
    import pe_imports
    sections, symbols = text_symbols(obj)
    out = {}
    byname = {}
    for va, (dll, nm) in pe_imports.iat().items():
        byname.setdefault(nm, []).append(va)
    for s in symbols.values():
        m = ADDR_NAME.search(s["name"])
        if m:
            out[s["name"]] = "0x" + m.group(1)
            continue
        m = re.match(r"^__imp__([A-Za-z0-9_]+?)(?:@\d+)?$", s["name"])
        if m and len(byname.get(m.group(1), [])) == 1:
            out[s["name"]] = hex(byname[m.group(1)][0])
    return out


def run_raw(obj, sym, addr, ln):
    env = dict(os.environ, GAMEMD_BINARY=BIN)
    r = subprocess.run([sys.executable, str(WT / "scripts/vc6/raw_match.py"), "--obj", str(obj), "--sym", sym,
                        "--addr", hex(addr), "--len", hex(ln)], capture_output=True, text=True, env=env)
    out = r.stdout.strip().splitlines()
    pct = None
    for l in out:
        if l.startswith("match:"):
            pct = l.split()[-1]
    return r.returncode == 0 and pct == "100.0%", pct or (out[-1] if out else r.stderr.strip()[:80]), r.stdout


def run_reloc(obj, sym, addr, ln, smap_path):
    r = subprocess.run([sys.executable, str(WT / "scripts/vc6/verify_relocations.py"), "--obj", str(obj),
                        "--sym", sym, "--addr", hex(addr), "--len", hex(ln), "--binary", BIN,
                        "--symbol-map", str(smap_path)], capture_output=True, text=True)
    last = (r.stdout.strip().splitlines() or [r.stderr.strip()])[-1]
    return r.returncode == 0, last if r.returncode == 0 else r.stderr.strip()[:200]


def check_function(obj, addr, ln, smap_path, sym=None, hint=None):
    sym = sym or find_symbol(obj, addr, hint)
    if sym is None:
        return dict(ok=False, why="no-symbol", sym=None)
    rok, rpct, rout = run_raw(obj, sym, addr, ln)
    if not rok:
        return dict(ok=False, why="raw " + str(rpct), pct=rpct, sym=sym, rout=rout)
    kok, ktxt = run_reloc(obj, sym, addr, ln, smap_path)
    if not kok:
        return dict(ok=False, why="reloc " + ktxt, pct=rpct, sym=sym)
    return dict(ok=True, why="", pct=rpct, sym=sym, relocs=ktxt)

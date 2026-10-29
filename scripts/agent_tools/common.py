#!/usr/bin/env python3
# Provenance: original. Shared helpers for the proposed workflow tools.
"""Shared helpers: paths, pinned PE access, manifest/annotation indexes,
objdump-based linear disassembly, and cached Ghidra queries.

Paths (override with environment variables):
  GAG_WORKTREE  worktree whose match/ and state/ are read (default: the repo these tools are in)
  GAG_MAIN      main checkout; shared scripts/data are read from here when the
                worktree copy is missing (function_extent_audit.json is main-only)
  GAMEMD_BINARY retail gamemd.exe (SHA-256 pinned)
"""
import functools
import hashlib
import json
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parent
ROOT = TOOLS.parent.parent                      # the repo these tools ship in (scripts/agent_tools/..)


def _main_checkout(root):
    try:
        cd = subprocess.run(["git", "-C", str(root), "rev-parse", "--path-format=absolute", "--git-common-dir"],
                            capture_output=True, text=True, check=True).stdout.strip()
        return Path(cd).parent if Path(cd).name == ".git" else root
    except Exception:
        return root


MAIN = Path(os.environ.get("GAG_MAIN") or _main_checkout(ROOT))
WORKTREE = Path(os.environ.get("GAG_WORKTREE") or ROOT)
# No default image path: GAMEMD_BINARY must name the user's own retail gamemd.exe (SHA-256 checked).
EXE = Path(os.environ.get("GAMEMD_BINARY", "/nonexistent/set-GAMEMD_BINARY/gamemd.exe"))
SHA256 = "1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c"
CACHE = TOOLS / "cache"
# state/ is untracked, so a linked worktree usually lacks it: fall back to the main checkout
STATE = (WORKTREE if (WORKTREE / "state").is_dir() else MAIN) / "state" / "orchestration"
GHIDRA = os.path.expanduser("~/.cargo/bin/ghidra")

# Reuse the repo's own COFF parser (read-only import of a tracked module).
sys.path.insert(0, str(ROOT / "scripts" / "vc6"))
from verify_vtable import parse_coff  # noqa: E402

ANNOT = re.compile(r"//\s*(FUNCTION|LIBRARY|STUB|TEMPLATE|SYNTHETIC|GLOBAL|STRING|VTABLE):\s*GAMEMD\s+(0x[0-9A-Fa-f]+)(.*)")


def data_file(name):
    """scripts/data/<name>, worktree first, then main."""
    for root in (WORKTREE, MAIN):
        p = root / "scripts" / "data" / name
        if p.exists():
            return p
    raise FileNotFoundError(name)


@functools.lru_cache(None)
def load_json(name):
    return json.loads(data_file(name).read_text())


def h(x):
    return int(x, 16) if isinstance(x, str) else int(x)


# ---------------------------------------------------------------- PE image
class PE:
    def __init__(self, path=EXE):
        self.data = Path(path).read_bytes()
        if hashlib.sha256(self.data).hexdigest() != SHA256:
            raise SystemExit(f"{path}: SHA-256 differs from the pinned retail image")
        pe = struct.unpack_from("<I", self.data, 0x3C)[0]
        nsec = struct.unpack_from("<H", self.data, pe + 6)[0]
        opt = struct.unpack_from("<H", self.data, pe + 20)[0]
        self.base = struct.unpack_from("<I", self.data, pe + 24 + 28)[0]
        self.sections = []
        for i in range(nsec):
            name, vsize, va, rsize, roff = struct.unpack_from("<8sIIII", self.data, pe + 24 + opt + 40 * i)
            self.sections.append((name.rstrip(b"\0").decode(), self.base + va, vsize, roff, rsize))

    def section(self, name):
        for s in self.sections:
            if s[0] == name:
                return s
        raise KeyError(name)

    def section_of(self, va):
        for s in self.sections:
            if s[1] <= va < s[1] + max(s[2], s[4]):
                return s[0]
        return None

    def read(self, va, n):
        for _, start, vsize, roff, rsize in self.sections:
            if start <= va and va + n <= start + min(vsize, rsize):
                return self.data[roff + va - start: roff + va - start + n]
        return None

    def sect_bytes(self, name):
        _, start, vsize, roff, rsize = self.section(name)
        return start, self.data[roff: roff + min(vsize, rsize)]

    def cstring(self, va, limit=200):
        b = self.read(va, 1)
        if b is None:
            return None
        out = bytearray()
        while len(out) < limit:
            c = self.read(va + len(out), 1)
            if not c or c == b"\0":
                break
            out += c
        return out.decode("latin-1")


@functools.lru_cache(None)
def pe():
    return PE()


# ---------------------------------------------------------------- disassembly
OBJ_LINE = re.compile(r"^\s*([0-9a-f]+):\s+((?:[0-9a-f]{2} )+)\s*(.*)$")


def disasm(va, n):
    """Linear objdump disassembly of [va, va+n) from the pinned PE.
    Returns [(addr, bytes_hex, text)]."""
    blob = pe().read(va, n)
    if blob is None:
        raise SystemExit(f"{va:#x}+{n:#x} is not file-backed")
    CACHE.mkdir(exist_ok=True)
    tmp = CACHE / f"span_{os.getpid()}.bin"
    tmp.write_bytes(blob)
    try:
        out = subprocess.run(["objdump", "-D", "-b", "binary", "-m", "i386", "-M", "intel",
                              f"--adjust-vma={va:#x}", str(tmp)],
                             capture_output=True, text=True, check=True).stdout
    finally:
        tmp.unlink()
    insns = []
    for line in out.splitlines():
        m = OBJ_LINE.match(line)
        if not m:
            continue
        a, bts, txt = int(m.group(1), 16), m.group(2).split(), m.group(3).strip()
        if not txt and insns:  # continuation line of a long instruction
            pa, pb, pt = insns[-1]
            insns[-1] = (pa, pb + "".join(bts), pt)
            continue
        insns.append((a, "".join(bts), re.sub(r"\s+", " ", txt)))
    return insns


# ---------------------------------------------------------------- function entries
@functools.lru_cache(None)
def ghidra_functions():
    p = CACHE / "ghidra_functions.json"
    if not p.exists():
        CACHE.mkdir(exist_ok=True)
        out = subprocess.run([GHIDRA, "function", "list", "--limit", "25000", "--json"],
                             capture_output=True, text=True, check=True).stdout
        p.write_text(out)
    return {int(f["address"], 16): f for f in json.loads(p.read_text())}


@functools.lru_cache(None)
def entry_list():
    """Sorted known entry points: Ghidra list + manifest + extent audit + unlisted."""
    s = set(ghidra_functions())
    s.update(h(r["addr"]) for r in manifest())
    s.update(h(a) for a in load_json("unlisted_entry_points.json"))
    return sorted(s)


def next_entry(va):
    import bisect
    lst = entry_list()
    i = bisect.bisect_right(lst, va)
    return lst[i] if i < len(lst) else None


# ---------------------------------------------------------------- manifest/annotations
@functools.lru_cache(None)
def manifest():
    return load_json("match_manifest.json")


@functools.lru_cache(None)
def manifest_by_addr():
    d = {}
    for r in manifest():
        d.setdefault(h(r["addr"]), []).append(r)
    return d


@functools.lru_cache(None)
def annotations(root=None):
    """addr -> [(kind, path, lineno, rest)] across match/**/*.{cpp,h,hpp}."""
    root = Path(root or WORKTREE)
    d = {}
    for p in sorted((root / "match").rglob("*")):
        if p.suffix.lower() not in (".cpp", ".h", ".hpp", ".inl"):
            continue
        try:
            text = p.read_text(errors="replace")
        except OSError:
            continue
        for i, line in enumerate(text.splitlines(), 1):
            m = ANNOT.search(line)
            if m:
                d.setdefault(int(m.group(2), 16), []).append(
                    (m.group(1), str(p.relative_to(root)), i, m.group(3).strip()))
    return d


def name_of(va):
    """Best human name for an address: manifest, then annotation, then Ghidra."""
    rows = manifest_by_addr().get(va)
    if rows:
        return rows[0].get("name") or rows[0]["sym"]
    for kind, path, line, rest in annotations().get(va, ()):
        if kind in ("LIBRARY", "GLOBAL", "STRING", "VTABLE"):
            return f"{kind}:{rest[:50]}" if rest else f"{kind}@{path}"
    lib = library_map().get(va)
    if lib:
        return f"LIB:{lib}"
    g = ghidra_functions().get(va)
    return g["name"] if g else None


@functools.lru_cache(None)
def library_map():
    p = STATE / "library_map.json"
    if not p.exists():
        return {}
    return {h(r["addr"]): r["name"] for r in json.loads(p.read_text())["found"]}


def ghidra_json(*args):
    r = subprocess.run([GHIDRA, *args, "--json"], capture_output=True, text=True)
    try:
        return json.loads(r.stdout)
    except ValueError:
        return []

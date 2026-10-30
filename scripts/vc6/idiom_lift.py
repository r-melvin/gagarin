#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original; reads project metadata and, at run time only, the user's own
# Ghidra session / pinned gamemd.exe. No retail bytes or decompiler output are stored.
"""Idiom lifter: Ghidra pseudo-C for one function -> first-draft C++ body.

    idiom_lift.py 0x721A50 [--class TiberiumClass] [--out draft.cpp] [--passes a,b]
    idiom_lift.py --file pseudo.c --class Foo       # no Ghidra needed

The draft is a starting point for a matching worker, not compilable truth. Each rewrite
rule is a separate pass (see PASSES); a pass that half-matches leaves the code alone and
adds a `/* LIFT? ... */` marker. Everything the passes know comes from tracked project
metadata (scripts/data/*.json, match/**/*.h layouts); string literals are read from the
binary at run time (GAMEMD_BINARY, else `ghidra memory read`).
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys
from collections import OrderedDict, defaultdict
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
DATA = REPO / "scripts" / "data"

# ---------------------------------------------------------------------------
# small text helpers
# ---------------------------------------------------------------------------
IDENT = r"[A-Za-z_]\w*"
HEXNUM = r"(?:0x[0-9a-fA-F]+|\d+)"
KEYWORDS = {"if", "while", "switch", "return", "sizeof", "for", "do", "else", "case", "goto"}


def to_int(tok):
    tok = tok.strip().rstrip("uUlL")
    return int(tok, 16) if tok.lower().startswith("0x") else int(tok)


def match_close(s, i, open_ch="(", close_ch=")"):
    """Index of the bracket closing s[i], skipping string and char literals; -1 if none."""
    depth = 0
    j = i
    n = len(s)
    while j < n:
        c = s[j]
        if c == "/" and s[j + 1:j + 2] == "/":
            k = s.find("\n", j)
            j = n if k < 0 else k
            continue
        if c == "/" and s[j + 1:j + 2] == "*":
            k = s.find("*/", j + 2)
            j = n if k < 0 else k + 2
            continue
        if c in "\"'":
            q = c
            j += 1
            while j < n and s[j] != q:
                j += 2 if s[j] == "\\" else 1
        elif c == open_ch:
            depth += 1
        elif c == close_ch:
            depth -= 1
            if depth == 0:
                return j
        j += 1
    return -1


def split_top(s):
    """Split on top-level commas."""
    out, depth, cur, j, n = [], 0, [], 0, len(s)
    while j < n:
        c = s[j]
        if c in "\"'":
            q = c
            k = j + 1
            while k < n and s[k] != q:
                k += 2 if s[k] == "\\" else 1
            cur.append(s[j:k + 1])
            j = k + 1
            continue
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        if c == "," and depth == 0:
            out.append("".join(cur).strip())
            cur = []
        else:
            cur.append(c)
        j += 1
    tail = "".join(cur).strip()
    if tail or out:
        out.append(tail)
    return out


def find_calls(s, name_re):
    """Yield (start, end, name, args) for each `name(args)` call whose name matches name_re.
    Nested calls come back outer-first; callers re-scan after editing."""
    for m in re.finditer(r"(?<![\w>.])(" + name_re + r")\s*\(", s):
        op = m.end() - 1
        cl = match_close(s, op)
        if cl < 0:
            continue
        yield m.start(), cl + 1, m.group(1), split_top(s[op + 1:cl])


def is_primary(e):
    """True when `e` can take a `->`/`.`/`[` suffix without parentheses."""
    e = e.strip()
    if re.fullmatch(r"[\w.]+(?:(?:->|\.)\w+|\[[^\[\]]*\])*", e):
        return True
    if e.startswith("(") and match_close(e, 0) == len(e) - 1:
        return True
    m = re.match(r"^[\w:.>\-]+(?:\[[^\]]*\])?\s*\(", e)
    if m and match_close(e, m.end() - 1) == len(e) - 1:
        return True
    return False


def paren(e):
    return e if is_primary(e) else "(" + e + ")"


def strip_outer_parens(e):
    e = e.strip()
    while e.startswith("(") and match_close(e, 0) == len(e) - 1:
        e = e[1:-1].strip()
    return e


class Stats:
    def __init__(self):
        self.sites = OrderedDict()
        self.marks = defaultdict(int)
        self.notes = []

    def add(self, name, n=1):
        self.sites[name] = self.sites.get(name, 0) + n

    def mark(self, name, n=1):
        self.marks[name] += n


# ---------------------------------------------------------------------------
# minimal MSVC demangler (common forms only; returns None when out of its depth)
# ---------------------------------------------------------------------------
BUILTIN = {"X": "void", "D": "char", "C": "signed char", "E": "unsigned char", "F": "short",
           "G": "unsigned short", "H": "int", "I": "unsigned int", "J": "long",
           "K": "unsigned long", "M": "float", "N": "double", "O": "long double"}
OPS = {"0": "ctor", "1": "dtor", "4": "operator=", "8": "operator==", "9": "operator!=",
       "A": "operator[]", "C": "operator->", "D": "operator*", "G": "scalar_deleting_dtor",
       "E": "vector_deleting_dtor", "2": "operator new", "3": "operator delete"}


class _Fail(Exception):
    pass


class _Dm:
    def __init__(self, s):
        self.s = s
        self.i = 0
        self.names = []
        self.types = []

    def peek(self, n=1):
        return self.s[self.i:self.i + n]

    def comp(self):
        s = self.s
        if s[self.i].isdigit():
            idx = int(s[self.i])
            self.i += 1
            if idx >= len(self.names):
                raise _Fail
            return self.names[idx]
        if s.startswith("?$", self.i):
            self.i += 2
            j = s.index("@", self.i)
            base = s[self.i:j]
            self.i = j + 1
            saved = self.names
            self.names = []
            args = []
            while self.peek() != "@":
                args.append(self.type_(memo=False))
            self.i += 1
            self.names = saved
            out = base + "<" + ", ".join(args) + ">"
        else:
            j = s.index("@", self.i)
            out = s[self.i:j]
            self.i = j + 1
        if out not in self.names and len(self.names) < 10:
            self.names.append(out)
        return out

    def qual_name(self):
        parts = []
        while self.peek() != "@":
            if self.i >= len(self.s):
                raise _Fail
            parts.append(self.comp())
        self.i += 1
        return parts

    def type_(self, memo=True):
        s = self.s
        start = self.i
        c = s[self.i]
        if c == "_":
            self.i += 2
            code = s[self.i - 1]
            r = {"N": "bool", "J": "__int64", "K": "unsigned __int64", "W": "wchar_t"}.get(code)
            if r is None:
                raise _Fail
            return r
        if c in BUILTIN:
            self.i += 1
            return BUILTIN[c]
        if c.isdigit():
            idx = int(c)
            self.i += 1
            if idx >= len(self.types):
                raise _Fail
            return self.types[idx]
        if c in "PQRS":
            self.i += 1
            q = s[self.i]
            self.i += 1
            const = "const " if q in "BDH" or q == "B" else ""
            inner = self.type_(memo=False)
            out = const + inner + "*"
        elif c in "AB":
            self.i += 1
            q = s[self.i]
            self.i += 1
            const = "const " if (c == "B" or q in "BD") else ""
            inner = self.type_(memo=False)
            out = const + inner + "&"
        elif c in "VUT":
            self.i += 1
            out = "::".join(self.qual_name()[::-1])
        elif c == "W":
            self.i += 2
            out = "::".join(self.qual_name()[::-1])
        else:
            raise _Fail
        if memo and len(self.types) < 10 and self.i - start > 1:
            self.types.append(out)
        return out


def demangle(sym):
    """Return dict(qualified, cls, name, kind, ret, args, const) or None."""
    if not sym or not sym.startswith("?") or sym.startswith("??_7"):
        return None
    try:
        d = _Dm(sym)
        d.i = 1
        special = None
        if d.peek(1) == "?":
            d.i += 1
            special = sym[d.i]
            d.i += 1
            if special == "_":
                special = "_" + sym[d.i]
                d.i += 1
            parts = d.qual_name()
            if not parts:
                raise _Fail
            cls = "::".join(parts[::-1])
            short = re.sub(r"<.*", "", parts[0])
            nm = OPS.get(special.lstrip("_"), "operator" + special)
            if special == "0":
                nm = short
            elif special == "1":
                nm = "~" + short
            parts = [nm] + parts
        else:
            parts = d.qual_name()
        name = parts[0]
        cls = "::".join(parts[1:][::-1]) if len(parts) > 1 else ""
        acc = sym[d.i]
        d.i += 1
        if acc in "ABIJQRUMEFVW":                 # member functions
            kind = "virtual" if acc in "EFMNUV" else "member"
            const = sym[d.i] in "BDFHJLNP" if sym[d.i] in "ABCDEFGHIJKLMNOP" else False
            d.i += 1
            conv = sym[d.i]
            d.i += 1
        elif acc in "ST":
            kind = "static"
            conv = sym[d.i]
            d.i += 1
            const = False
        elif acc in "YZ":
            kind = "free"
            conv = sym[d.i]
            d.i += 1
            const = False
        else:
            return None
        if sym[d.i] == "@":
            d.i += 1
            ret = None
        else:
            if sym[d.i] == "?":
                d.i += 2
            ret = d.type_(memo=False)
        args = []
        if sym[d.i] == "X":
            d.i += 1
        else:
            while d.i < len(sym) and sym[d.i] not in "@Z":
                args.append(d.type_())
        return {"qualified": (cls + "::" if cls else "") + name, "cls": cls, "name": name,
                "kind": kind, "ret": ret, "args": args, "const": const, "conv": conv, "sym": sym}
    except (_Fail, IndexError, ValueError):
        return None


# ---------------------------------------------------------------------------
# project knowledge
# ---------------------------------------------------------------------------
class Layouts:
    """class -> offset map / member types / bases / virtual slot names from tracked headers."""

    CLASS_RE = re.compile(r"\b(?:class|struct)\s+(\w+)\s*(?::\s*([^{;]+))?\{")
    ASSERT_OFF = re.compile(r"GG_STATIC_ASSERT\s*\(\s*offsetof\s*\(\s*([\w:<>, ]+?)\s*,\s*([\w.\[\]]+?)\s*\)\s*==\s*(0x[0-9a-fA-F]+|\d+)\s*\)")
    ASSERT_SIZE = re.compile(r"GG_STATIC_ASSERT\s*\(\s*sizeof\s*\(\s*(\w+)\s*\)\s*==\s*(0x[0-9a-fA-F]+|\d+)\s*\)")
    MEMBER_RE = re.compile(r"^\s*((?:const\s+|unsigned\s+|struct\s+)*[\w:]+(?:<[^;()]*>)?[\s*&]+)(\w+)\s*(\[[^\]]*\])?\s*(?::\s*\d+)?\s*;")
    VIRT_RE = re.compile(r"^\s*virtual\b[^;]*?\b(~?\w+)\s*\([^;]*\)[^;]*;\s*//\s*(?:vf_)?(\d+)\b")

    # shapes the project defines in templates / unparsable headers
    BUILTIN_TYPES = {
        "DynamicVectorClass": ({0x04: "Items", 0x08: "Capacity", 0x0C: "IsInitialized",
                                0x0D: "IsAllocated", 0x10: "Count", 0x14: "CapacityIncrement"}, 0x18),
        "VectorClass": ({0x04: "Items", 0x08: "Capacity", 0x0C: "IsInitialized", 0x0D: "IsAllocated"}, 0x10),
        "CDTimerClass": ({0: "StartTime", 4: "CurrentTime", 8: "TimeLeft"}, 0xC),
        "CoordStruct": ({0: "X", 4: "Y", 8: "Z"}, 0xC),
        "CellStruct": ({0: "X", 2: "Y"}, 4),
    }

    def __init__(self, root=REPO / "match"):
        self.root = Path(root)
        self.offsets = defaultdict(dict)    # class -> {name: off}
        self.sizes = {}
        self.bases = {}
        self.types = defaultdict(dict)      # class -> {member: (type, is_array)}
        self.slots = defaultdict(dict)      # class -> {slot: name}
        self.loaded = False

    def load(self):
        if self.loaded:
            return
        self.loaded = True
        files = sorted(f for f in glob.glob(str(self.root / "**" / "*"), recursive=True) if f.lower().endswith(".h"))
        for f in files:
            try:
                text = Path(f).read_text(errors="replace")
            except OSError:
                continue
            if "offsetof" in text:
                self._asserts(text)
            if "class " in text or "struct " in text:
                self._bodies(text)

    def _asserts(self, text):
        for m in self.ASSERT_OFF.finditer(text):
            cls, field, off = m.group(1).strip(), m.group(2), to_int(m.group(3))
            if "." in field or "[" in field:
                continue
            self.offsets[cls].setdefault(field, off)
        for m in self.ASSERT_SIZE.finditer(text):
            self.sizes.setdefault(m.group(1), to_int(m.group(2)))

    def _bodies(self, text):
        for m in self.CLASS_RE.finditer(text):
            name = m.group(1)
            op = m.end() - 1
            cl = match_close(text, op, "{", "}")
            if cl < 0:
                continue
            if m.group(2) and name not in self.bases:
                bases = []
                for b in m.group(2).split(","):
                    b = re.sub(r"\b(public|protected|private|virtual)\b", "", b).strip()
                    if b:
                        bases.append(re.sub(r"<.*", "", b))
                self.bases[name] = bases
            body = text[op + 1:cl]
            depth = 0
            line_start = 0
            for line in body.split("\n"):
                d0 = depth
                depth += line.count("{") - line.count("}")
                if d0 == 0 and "(" not in line.split("//")[0]:
                    mm = self.MEMBER_RE.match(line)
                    if mm and name not in ("enum",):
                        t = mm.group(1).strip()
                        self.types[name].setdefault(mm.group(2), (t, bool(mm.group(3))))
                if d0 == 0:
                    vm = self.VIRT_RE.match(line)
                    if vm:
                        self.slots[name].setdefault(int(vm.group(2)), vm.group(1))
                    else:
                        vm = re.search(r"\bvf_(\d+)\s*\(", line)
                        if vm and line.lstrip().startswith("virtual"):
                            self.slots[name].setdefault(int(vm.group(1)), "vf_" + vm.group(1))

    def chain(self, cls):
        out, todo = [], [cls]
        while todo:
            c = todo.pop(0)
            if c in out:
                continue
            out.append(c)
            todo.extend(self.bases.get(c, []))
        return out

    def field_map(self, cls):
        """offset -> [(field, owner)] merged over the base chain (derived names first)."""
        self.load()
        base = re.sub(r"<.*", "", cls)
        fm = {}
        for c in reversed(self.chain(base)):
            offs = self.offsets.get(c)
            if not offs and c in self.BUILTIN_TYPES:
                offs = {v: k for k, v in self.BUILTIN_TYPES[c][0].items()}
            for field, off in (offs or {}).items():
                prev = fm.get(off)
                if prev is None or (prev[0].startswith("unknown_") and not field.startswith("unknown_")) \
                        or c != prev[1]:
                    fm[off] = (field, c)
        return fm

    def member_type(self, cls, field):
        self.load()
        for c in self.chain(re.sub(r"<.*", "", cls)):
            t = self.types.get(c, {}).get(field)
            if t:
                return t
        return None

    def size_of(self, typ):
        base = re.sub(r"<.*", "", typ.strip())
        base = re.sub(r"^(const\s+|struct\s+)+", "", base)
        if "*" in typ or "&" in typ:
            return 4
        if base in self.sizes:
            return self.sizes[base]
        if base in self.BUILTIN_TYPES:
            return self.BUILTIN_TYPES[base][1]
        return {"int": 4, "unsigned": 4, "float": 4, "double": 8, "short": 2, "char": 1,
                "bool": 1, "long": 4, "BYTE": 1, "WORD": 2, "DWORD": 4}.get(base)

    def resolve(self, cls, off, descend=False):
        """Return (path, type, is_array) naming byte `off` in `cls`, or (None, None, False).
        With descend, a struct member hit at its first byte resolves to its first subfield."""
        fm = self.field_map(cls)
        if off in fm:
            field = fm[off][0]
            t = self.member_type(cls, field)
            if descend and t and not t[1] and "*" not in t[0]:
                tb = re.sub(r"^(const\s+|struct\s+)+", "", t[0]).split()[0]
                if re.sub(r"<.*", "", tb) in self.BUILTIN_TYPES or tb in self.offsets:
                    sub = self.resolve(tb, 0)
                    if sub[0] and not sub[0].startswith("unknown_"):
                        return field + "." + sub[0], sub[1], sub[2]
            return field, (t[0] if t else None), (t[1] if t else False)
        starts = sorted(o for o in fm if o < off)
        if starts:
            o = starts[-1]
            field = fm[o][0]
            t = self.member_type(cls, field)
            if t and not t[1] and "*" not in t[0]:
                sz = self.size_of(t[0])
                if sz and off - o < sz:
                    sub = self.resolve(re.sub(r"^(const\s+|struct\s+)+", "", t[0]).split()[0], off - o)
                    if sub[0] and not sub[0].startswith("unknown_"):
                        return field + "." + sub[0], sub[1], sub[2]
        for nm in ("unknown_%02X" % off, "unknown_%X" % off):
            t = self.member_type(cls, nm)
            if t:
                return nm, t[0], t[1]
        return None, None, False

    def slot_name(self, cls, slot):
        self.load()
        for c in self.chain(re.sub(r"<.*", "", cls)):
            n = self.slots.get(c, {}).get(slot)
            if n:
                return n
        return "vf_%d" % slot

    def elem_class(self, typ):
        """`Foo*` / `Foo *` -> `Foo` when Foo has a known layout."""
        m = re.fullmatch(r"(?:const\s+|struct\s+|class\s+)*(\w+)\s*\*", typ.strip())
        if m and (m.group(1) in self.offsets or m.group(1) in self.bases):
            return m.group(1)
        return None

    def is_array_like(self, typ, flag):
        return flag or typ.startswith("GgBoundedText") or typ.startswith("char[")


class Names:
    """Address -> project names (functions and globals)."""

    GLOBAL_RE = re.compile(r"GLOBAL:\s*GAMEMD\s+0x0*([0-9A-Fa-f]+)")
    DECL_NAME = re.compile(r"\b(\w+)\s*(?:\[[^\]]*\])?\s*(?:=|;)")

    def __init__(self, data=DATA, match_root=REPO / "match"):
        self.data = Path(data)
        self.match_root = Path(match_root)
        self.manifest = {}
        self.sym_by_addr = defaultdict(list)
        self.globals = {}
        self.rtti_depth = {}
        self._loaded = False
        self._globals_loaded = False

    def load(self):
        if self._loaded:
            return
        self._loaded = True
        try:
            for r in json.loads((self.data / "match_manifest.json").read_text()):
                self.manifest[to_int(r["addr"])] = r
        except (OSError, ValueError):
            pass
        try:
            for sym, addr in json.loads((self.data / "symbol_bindings.json").read_text()).items():
                if "::" in sym:
                    continue
                self.sym_by_addr[to_int(addr)].append(sym)
        except (OSError, ValueError):
            pass
        try:
            rt = json.loads((self.data / "rtti_classes.json").read_text())["classes"]
            for c in rt.values():
                self.rtti_depth[c.get("demangled_name", "")] = c.get("num_base_classes", 1)
        except (OSError, ValueError, KeyError):
            pass

    def func(self, addr):
        """dict(qualified, kind, ret, args, cls, name, sym) for a function address, or None."""
        self.load()
        row = self.manifest.get(addr)
        if row:
            info = demangle(row.get("sym", ""))
            if info:
                return info
            nm = row.get("name") or ""
            if nm and not nm.startswith("FUN_"):
                cls, _, short = nm.rpartition("::")
                return {"qualified": nm, "cls": cls, "name": short, "kind": "member" if cls else "free",
                        "ret": None, "args": None, "const": False, "conv": "?", "sym": row.get("sym")}
            return None
        syms = self.sym_by_addr.get(addr)
        if not syms:
            return None
        best = None
        for s in syms:
            info = demangle(s)
            if not info:
                continue
            rank = (0 if self.rtti_depth.get(info["cls"]) else 1,
                    1 if re.search(r"_[0-9A-Fa-f]{6,8}$", info["cls"]) else 0,
                    -self.rtti_depth.get(info["cls"], 0), info["cls"])
            if best is None or rank < best[0]:
                best = (rank, info)
        return best[1] if best else None

    def load_globals(self):
        if self._globals_loaded:
            return
        self._globals_loaded = True
        for f in [g for g in glob.glob(str(self.match_root / "**" / "*"), recursive=True) if g.lower().endswith(".h")]:
            try:
                lines = Path(f).read_text(errors="replace").split("\n")
            except OSError:
                continue
            for i, line in enumerate(lines):
                m = self.GLOBAL_RE.search(line)
                if not m:
                    continue
                addr = int(m.group(1), 16)
                cand = line.split("//")[0]
                nm = None
                if cand.strip():
                    mm = self.DECL_NAME.search(cand)
                    nm = mm.group(1) if mm else None
                else:
                    for nxt in lines[i + 1:i + 4]:
                        c2 = nxt.split("//")[0]
                        if c2.strip():
                            mm = self.DECL_NAME.search(c2)
                            nm = mm.group(1) if mm else None
                            break
                if nm and not nm.startswith("DAT_") and addr not in self.globals:
                    self.globals[addr] = nm

    def glob(self, addr):
        self.load_globals()
        return self.globals.get(addr)


class Reader:
    """Run-time reads of the retail image: GAMEMD_BINARY first, then the Ghidra CLI."""

    def __init__(self, use_ghidra=True):
        self.use_ghidra = use_ghidra
        self.cache = {}
        self._pe = None

    def _pe_bytes(self, addr, n):
        binary = os.environ.get("GAMEMD_BINARY")
        if not binary:
            return None
        if self._pe is None:
            import struct
            b = Path(binary).read_bytes()
            pe = struct.unpack_from("<I", b, 0x3C)[0]
            nsec = struct.unpack_from("<H", b, pe + 6)[0]
            optsz = struct.unpack_from("<H", b, pe + 20)[0]
            base = struct.unpack_from("<I", b, pe + 24 + 28)[0]
            secs = []
            for i in range(nsec):
                _, vs, va, rs, ro = struct.unpack_from("<8sIIII", b, pe + 24 + optsz + 40 * i)
                secs.append((base + va, vs, ro, rs))
            self._pe = (b, secs)
        b, secs = self._pe
        for start, vs, ro, rs in secs:
            if start <= addr < start + min(vs, rs):
                o = ro + addr - start
                return b[o:o + min(n, start + min(vs, rs) - addr)]
        return None

    def read(self, addr, n=160):
        key = (addr, n)
        if key in self.cache:
            return self.cache[key]
        data = None
        try:
            data = self._pe_bytes(addr, n)
        except (OSError, ValueError):
            data = None
        if data is None and self.use_ghidra:
            try:
                out = subprocess.run(["ghidra", "memory", "read", "0x%X" % addr, str(n)],
                                     capture_output=True, text=True, timeout=60).stdout
                data = bytes.fromhex(json.loads(out)[0]["hex"])
            except (OSError, ValueError, KeyError, IndexError, subprocess.SubprocessError):
                data = None
        self.cache[key] = data
        return data

    def cstring(self, addr, limit=160):
        data = self.read(addr, limit)
        if not data:
            return None
        end = data.find(b"\0")
        if end < 0:
            return None
        txt = data[:end]
        if any(c < 0x20 and c not in (9, 10, 13) or c > 0x7E for c in txt):
            return None
        return txt.decode("ascii")


class Ctx:
    def __init__(self, names=None, layouts=None, reader=None, cls=None, addr=None, rtti_names=None):
        self.names = names or Names()
        self.layouts = layouts or Layouts()
        self.reader = reader or Reader()
        self.cls = cls
        self.addr = addr
        self.func = None
        self.stats = Stats()
        self.rtti_names = rtti_names
        self.ret_type = None
        self.types = {}          # expression text -> class name (pointer pointee)
        self.thiscall = True
        self.unmapped = {}       # class -> {offsets with no layout field}
        self.field_types = {}    # emitted field expression -> Ghidra cast type at the site
        self.this_is_param1 = True
        self.vtables = None
        self.string_probes = 0


# ---------------------------------------------------------------------------
# document model
# ---------------------------------------------------------------------------
PSEUDO_TYPES = [("undefined8", "long long"), ("undefined4", "int"), ("undefined2", "short"),
                ("undefined1", "char"), ("undefined", "char"), ("ulonglong", "unsigned long long"),
                ("longlong", "long long"), ("uint3", "unsigned int"), ("int3", "int"),
                ("uint", "unsigned int"), ("ushort", "unsigned short"), ("ulong", "unsigned long"),
                ("byte", "unsigned char"), ("uchar", "unsigned char"), ("float10", "double"),
                ("LPVOID", "void*"), ("code", "void")]
DECL_RE = re.compile(r"^\s*(?P<type>[A-Za-z_][\w ]*?[\s*])\s*(?P<name>[A-Za-z_]\w*)\s*(?P<dim>\[[^\]]*\])?\s*;\s*$")


class Doc:
    def __init__(self, text):
        self.raw = text
        self.ret = "int"
        self.conv = "__thiscall"
        self.fname = ""
        self.params = []          # [(type, name)]
        self.locals = OrderedDict()
        self.body = ""
        self.loop_decl = set()
        self.this_name = None
        self.parse(text)

    def parse(self, text):
        text = text.replace("\r", "")
        i = text.find("{")
        head = text[:i].strip()
        m = re.search(r"^(?P<ret>.*?)\s*(?P<conv>__thiscall|__fastcall|__stdcall|__cdecl)?\s+(?P<name>\*?\w+)\s*\((?P<params>.*)\)\s*$",
                      " ".join(head.split()), re.S)
        if m:
            self.ret = m.group("ret").strip() or "int"
            self.conv = m.group("conv") or "__cdecl"
            self.fname = m.group("name")
            prm = m.group("params").strip()
            if prm and prm != "void":
                for p in split_top(prm):
                    pm = re.match(r"^(.*?)(\w+)\s*(\[.*\])?$", p.strip())
                    if pm:
                        self.params.append((pm.group(1).strip() or "int", pm.group(2)))
        if self.conv == "__thiscall" and self.params:
            self.this_name = self.params[0][1]
        j = match_close(text, i, "{", "}")
        body = text[i + 1:j if j > 0 else len(text)]
        lines = body.split("\n")
        k = 0
        while k < len(lines):
            ln = lines[k]
            if not ln.strip():
                k += 1
                continue
            dm = DECL_RE.match(ln)
            if dm and dm.group("type").split()[0].strip("*") not in ("return", "goto", "break", "continue", "else", "case"):
                self.locals[dm.group("name")] = (re.sub(r"\s*\*", "*", dm.group("type").strip()), dm.group("dim") or "")
                k += 1
                continue
            break
        self.body = self.join_lines("\n".join(lines[k:]))

    @staticmethod
    def join_lines(text):
        out, cur = [], ""
        for ln in text.split("\n"):
            s = ln.strip()
            if not s:
                continue
            cur = (cur + " " + s) if cur else s
            if re.search(r"[;{}]\s*$", cur) or re.match(r"^(?:case\s.*|default):\s*$", cur) \
                    or re.match(r"^\w+:\s*$", cur) or cur.startswith("/*") and cur.endswith("*/"):
                out.append(cur)
                cur = ""
            elif cur.startswith("//"):
                out.append(cur)
                cur = ""
        if cur:
            out.append(cur)
        # split "} else {" glued by joining, and "}" tails
        res = []
        for ln in out:
            res.append(ln)
        return "\n".join(res)


def sub_count(pattern, repl, s, flags=0):
    new, n = re.subn(pattern, repl, s, flags=flags)
    return new, n


# ---------------------------------------------------------------------------
# pass: strings
# ---------------------------------------------------------------------------
def c_escape(txt):
    return '"' + txt.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n").replace("\r", "\\r").replace("\t", "\\t") + '"'


STR_LABEL = re.compile(r"(?:\(\s*(?:byte|char|LPCSTR|LPSTR|uchar|undefined1|undefined)\s*\*\s*\)\s*)?&?\bs_\w*?_([0-9a-fA-F]{8})\b")
STR_DAT = re.compile(r"(?:\(\s*(?:byte|char|LPCSTR|LPSTR|uchar|undefined1)\s*\*\s*\)\s*)?&_?(?:DAT|[A-Za-z]\w*)_([0-9a-fA-F]{8})\b")
NOT_STR = ("FUN_", "PTR_", "LAB_", "switchD", "caseD", "s_", "u_", "thunk_")


def p_strings(doc, ctx):
    n_ok = 0

    def rep(m):
        nonlocal n_ok
        txt = ctx.reader.cstring(int(m.group(1), 16))
        if txt is None:
            ctx.stats.mark("strings.unread")
            return m.group(0)
        n_ok += 1
        return c_escape(txt)
    doc.body = STR_LABEL.sub(rep, doc.body)

    def rep2(m):
        nonlocal n_ok
        whole = m.group(0)
        ident = re.search(r"&(_?\w+)", whole).group(1)
        if ident.startswith(NOT_STR):
            return whole
        addr = int(m.group(1), 16)
        if not whole.startswith("(") and ctx.string_probes >= 40:
            return whole
        ctx.string_probes += 0 if whole.startswith("(") else 1
        txt = ctx.reader.cstring(addr, 64)
        if txt is None or len(txt) > 40:
            return whole
        n_ok += 1
        return "STR_%08X /* %s */" % (addr, c_escape(txt))
    doc.body = STR_DAT.sub(rep2, doc.body)
    ctx.stats.add("strings", n_ok)


# ---------------------------------------------------------------------------
# pass: ghidra (early artefacts: CONCAT/SUB/ZEXT, zero casts, bool returns)
# ---------------------------------------------------------------------------
SIMPLE_VAL = re.compile(r"^(?:[\w.]+|\([^()]*\)|0x[0-9a-fA-F]+|-?\d+|'.')$")


def p_ghidra(doc, ctx):
    s = doc.body
    n = 0
    # CONCATnm(hi, lo) -> lo
    changed = True
    while changed:
        changed = False
        for a, b, name, args in find_calls(s, r"CONCAT[1-8][1-8]"):
            if name in ("CONCAT44", "CONCAT88", "CONCAT62", "CONCAT26", "CONCAT53", "CONCAT35") \
                    or len(args) != 2:
                ctx.stats.mark("ghidra.concat_kept")
                continue
            if name[-2] == "4" and name[-1] == "4":
                continue
            s = s[:a] + paren(args[1]) + s[b:]
            n += 1
            changed = True
            ctx.stats.add("ghidra.concat")
            break
    for a, b, name, args in list(find_calls(s, r"(?:SUB|ZEXT)[1-8][1-8]")):
        pass
    changed = True
    while changed:
        changed = False
        for a, b, name, args in find_calls(s, r"(?:SUB|ZEXT)[1-8][1-8]"):
            width = {"1": "unsigned char", "2": "unsigned short", "4": "unsigned int", "8": "unsigned long long"}
            if name.startswith("SUB"):
                out = "(%s)%s" % (width[name[4]], paren(args[0]))
            else:
                out = "(%s)%s" % (width[name[-1]], paren(args[0]))
            s = s[:a] + out + s[b:]
            ctx.stats.add("ghidra.sub_zext")
            changed = True
            break
    # zero-valued pointer casts
    s, k = sub_count(r"\(\s*[A-Za-z_][\w ]*\*+\s*\)\s*0x0\b", "0", s)
    ctx.stats.add("ghidra.zero_cast", k)
    s, k = sub_count(r"\(\s*(?:LPVOID|HANDLE|HWND|LPCSTR)\s*\)\s*0x0\b", "0", s)
    ctx.stats.add("ghidra.zero_cast", k)
    # bool-ish returns
    ret_bool = ctx.ret_type == "bool"
    s, k = sub_count(r"return\s+\w+\s*&\s*0xffffff00\s*;", "return false;", s)
    if k:
        ret_bool = True
        ctx.ret_type = ctx.ret_type or "bool"
        ctx.stats.add("ghidra.bool_return", k)
    if ret_bool or ctx.ret_type == "bool":
        s, k = sub_count(r"return\s+1\s*;", "return true;", s)
        ctx.stats.add("ghidra.bool_return", k)
        s, k = sub_count(r"return\s+0\s*;", "return false;", s)
        ctx.stats.add("ghidra.bool_return", k)
    doc.body = s


# ---------------------------------------------------------------------------
# pass: vcalls
# ---------------------------------------------------------------------------
CALL_PREFIX = re.compile(r"\(\*\*\(code \*\*\)|\(\*\(code \*\)\*\(\w+ \*\)")


def _strip_obj_cast(e):
    e = e.strip()
    m = re.match(r"^\(\s*(?:int|uint|undefined4|void|code|int \*|undefined4 \*)\s*\*?\s*\)\s*(.*)$", e)
    return m.group(1).strip() if m else e


def _same_obj(a, b):
    def norm(x):
        x = x.strip()
        prev = None
        while prev != x:
            prev = x
            x = _strip_obj_cast(strip_outer_parens(x))
        return re.sub(r"\s+", "", x)
    return norm(a) == norm(b)


def p_vcalls(doc, ctx):
    s = doc.body
    pos = 0
    while True:
        m = CALL_PREFIX.search(s, pos)
        if not m:
            break
        start = m.start()
        if "(*(code *)*" in m.group(0):
            # (*(code *)*(T *)( ... ))(args): address expression is the parenthesised part after the cast
            op = m.end() - 1
            cl = match_close(s, op)
            addr_expr = s[op:cl + 1] if cl > 0 else ""
            outer_close = cl + 1 if False else None
            x = addr_expr
            # the wrapper's own closing paren follows
            call_open = cl + 1
            if s[call_open:call_open + 1] != ")":
                pos = m.end()
                continue
            call_open += 1
        else:
            outer_close = match_close(s, start)
            if outer_close < 0:
                pos = m.end()
                continue
            x = s[m.end():outer_close]
            call_open = outer_close + 1
        if s[call_open:call_open + 1] != "(":
            pos = m.end()
            continue
        call_close = match_close(s, call_open)
        if call_close < 0:
            pos = m.end()
            continue
        args = split_top(s[call_open + 1:call_close])
        x = x.strip()
        off, ptr = 0, None
        if x.startswith("(") and match_close(x, 0) == len(x) - 1:
            inner = x[1:-1].strip()
            mm = re.match(r"^\*(.*)\s\+\s(" + HEXNUM + r")$", inner, re.S)
            if mm:
                ptr, off = mm.group(1), to_int(mm.group(2))
        elif x.startswith("*"):
            ptr, off = x[1:], 0
        if ptr is None:
            ctx.stats.mark("vcalls")
            pos = m.end()
            continue
        obj = _strip_obj_cast(ptr)
        explicit = bool(args) and _same_obj(obj, args[0])
        if not explicit:
            ctx.stats.mark("vcalls.implicit_this")
        slot = off // 4
        recv = strip_outer_parens(obj) if is_primary(strip_outer_parens(obj)) else obj
        name = "vf_%d" % slot
        if recv == ctx.doc.this_name and ctx.cls:
            name = ctx.layouts.slot_name(ctx.cls, slot)
        out = "%s->%s(%s)" % (paren(recv), name, ", ".join(args[1:] if explicit else args))
        s = s[:start] + out + s[call_close + 1:]
        ctx.stats.add("vcalls")
        pos = start + 1
    doc.body = s


# ---------------------------------------------------------------------------
# pass: fields
# ---------------------------------------------------------------------------
OFFSET_EXPR = r"\(\s*(?:int|uint|undefined4|undefined\d?)\s*\)\s*(?P<base>[A-Za-z_]\w*)\s*\+\s*(?P<off>" + HEXNUM + r")"


def _c_type_of(t):
    t = t.strip()
    for a, b in PSEUDO_TYPES:
        t = re.sub(r"\b%s\b" % a, b, t)
    return t


def _field_ref(ctx, cls, base_text, off, cast_type, addr_of):
    """Return replacement text, or None when the class has no usable layout."""
    path, ftype, is_arr = ctx.layouts.resolve(cls, off, descend=not addr_of and cast_type not in ("void",))
    if path is None:
        name = "unknown_%02X" % off
        ftype, is_arr = None, False
        ctx.stats.mark("fields.unmapped")
        ctx.unmapped.setdefault(cls, set()).add(off)
    else:
        ctx.stats.add("fields")
    recv = "this" if base_text == ctx.doc.this_name else base_text
    expr = "%s->%s" % (recv, path or name)
    if not addr_of:
        ctx.field_types[expr] = cast_type
        if ftype:
            c = ctx.layouts.elem_class(ftype)
            if c:
                ctx.types[expr] = c
        return expr
    if ftype and ctx.layouts.is_array_like(ftype, is_arr):
        return expr
    return "&" + expr


def p_fields(doc, ctx):
    if not ctx.cls:
        ctx.stats.mark("fields.no_class")
    s = doc.body
    ctx.this_is_param1 = doc.this_name is not None
    tn = doc.this_name or "param_1"
    bases = {}
    if ctx.cls and ctx.this_is_param1:
        bases[tn] = ctx.cls
        ctx.types["this"] = ctx.cls
        if tn != "this":
            bases["this"] = ctx.cls
    elif ctx.cls:
        ctx.stats.mark("fields.no_thiscall")
    # types of by-ref params could be added by callers via ctx.types
    for k, v in list(ctx.types.items()):
        if k != "this":
            bases.setdefault(k, v)
    deref = re.compile(r"\*\(\s*(?P<t>[\w ]+?)\s*\*\s*\)\s*\(\s*" + OFFSET_EXPR + r"\s*\)")
    addr = re.compile(r"\(\s*(?P<t>[\w ]+?)\s*\*\s*\)\s*\(\s*" + OFFSET_EXPR + r"\s*\)")
    deref0 = re.compile(r"\*\(\s*(?P<t>[\w ]+?)\s*\*\s*\)\s*(?P<base>param_1)\b(?!\s*[\[+])")
    tname_re = re.escape(tn)
    # pointer-typed expression keys: *(T*)((KEY) + off) and (int)KEY + off
    for _ in range(12):
        before = s
        # infer variable classes from simple assignments of typed expressions
        for vm in re.finditer(r"^\s*(\w+)\s*=\s*([^;=]+?)\s*;$", s, re.M):
            v, e = vm.group(1), vm.group(2).strip()
            e = e.lstrip("(").rstrip(")") if e.startswith("(") and e.endswith(")") and e.count("(") == e.count(")") else e
            if e in ctx.types and v not in bases and re.fullmatch(r"(?:i|p|u|b|c|s|l)?Var\d+|\w+_\w+", v) is None:
                pass
            if e in ctx.types and v not in bases:
                # only when assigned once
                if len(re.findall(r"^\s*%s\s*=" % re.escape(v), s, re.M)) == 1:
                    bases[v] = ctx.types[e]
                    ctx.types[v] = ctx.types[e]

        def rd(m, addr_of):
            b = m.group("base")
            cls = bases.get(b)
            if cls is None:
                return m.group(0)
            return _field_ref(ctx, cls, b, to_int(m.group("off")), m.group("t"), addr_of)
        s = deref.sub(lambda m: rd(m, False), s)
        s = addr.sub(lambda m: rd(m, True), s)
        # pointee of a typed field expression: *(T *)(KEY + off) / (int)KEY + off
        for key, cls in list(ctx.types.items()):
            if key in ("this",):
                continue
            ek = re.escape(key)
            pat = re.compile(r"\*\(\s*(?P<t>[\w ]+?)\s*\*\s*\)\s*\(\s*(?:\(\s*int\s*\)\s*)?" + ek + r"\s*\+\s*(?P<off>" + HEXNUM + r")\s*\)")
            s = pat.sub(lambda m, cls=cls, key=key: _field_ref(ctx, cls, key, to_int(m.group("off")), m.group("t"), False), s)
            pat2 = re.compile(r"\(\s*(?P<t>[\w ]+?)\s*\*\s*\)\s*\(\s*\(\s*int\s*\)\s*" + ek + r"\s*\+\s*(?P<off>" + HEXNUM + r")\s*\)")
            s = pat2.sub(lambda m, cls=cls, key=key: _field_ref(ctx, cls, key, to_int(m.group("off")), m.group("t"), True), s)
        if s == before:
            break
    if ctx.this_is_param1:
        s = re.sub(r"\(\s*(?:void|int|uint)\s*\*?\s*\)\s*%s\b" % tname_re, "this", s)
        s = re.sub(r"\b%s\b" % tname_re, "this", s)
    # slot names on typed receivers
    def slot_rep(m):
        key, slot = m.group(1), int(m.group(2))
        cls = ctx.types.get(key.strip("()"))
        if cls:
            return "%s->%s(" % (key, ctx.layouts.slot_name(cls, slot))
        return m.group(0)
    s = re.sub(r"((?:this|\w+)(?:->\w+)+)->vf_(\d+)\(", slot_rep, s)
    # remaining raw offset derefs: mark the statement
    out = []
    for ln in s.split("\n"):
        if re.search(r"\(\s*(?:int|uint)\s*\)\s*[A-Za-z_]\w*\s*\+\s*" + HEXNUM, ln) and "LIFT?" not in ln:
            ctx.stats.mark("fields.unresolved")
            ln += " /* LIFT? unresolved offset access */"
        out.append(ln)
    doc.body = "\n".join(out)


# ---------------------------------------------------------------------------
# pass: symbols
# ---------------------------------------------------------------------------
FUN_RE = r"FUN_[0-9a-fA-F]{8}"


def _fun_addr(name):
    return int(name[4:], 16)


def _recv_call(recv, info, rest, this_names=("this",)):
    nm = info["name"]
    recv = _strip_obj_cast(recv)
    if re.fullmatch(r"0x[0-9a-fA-F]+|\d+", recv.strip()):
        return "%s(%s)" % (info["qualified"], ", ".join([recv] + rest))
    if info["kind"] == "virtual" and recv in this_names:
        return "%s::%s(%s)" % (info["cls"], nm, ", ".join(rest))
    r = recv.strip()
    if r.startswith("&") and is_primary(r[1:]):
        return "%s.%s(%s)" % (r[1:], nm, ", ".join(rest))
    cls_q = ""
    if info["kind"] == "virtual" and "this" not in r:
        cls_q = ""
    if info["name"] == info["cls"].split("::")[-1].split("<")[0]:
        return "%s->%s::%s(%s)" % (paren(r), info["cls"], nm, ", ".join(rest))
    return "%s->%s%s(%s)" % (paren(r), cls_q, nm, ", ".join(rest))


def _rewrite_calls(s, ctx):
    out, pos = [], 0
    pat = re.compile(r"(?<![\w>.&])(" + FUN_RE + r")\s*\(")
    while True:
        m = pat.search(s, pos)
        if not m:
            out.append(s[pos:])
            break
        op = m.end() - 1
        cl = match_close(s, op)
        if cl < 0:
            out.append(s[pos:])
            break
        out.append(s[pos:m.start()])
        args = [_rewrite_calls(a, ctx) for a in split_top(s[op + 1:cl])]
        addr = _fun_addr(m.group(1))
        info = ctx.names.func(addr)
        if info and info["kind"] in ("member", "virtual") and args:
            out.append(_recv_call(args[0], info, args[1:]))
            ctx.stats.add("symbols.calls")
        elif info and info["kind"] == "static":
            out.append("%s(%s)" % (info["qualified"], ", ".join(args)))
            ctx.stats.add("symbols.calls")
        elif info:
            out.append("%s(%s)" % (info["name"] if not info["cls"] else info["qualified"], ", ".join(args)))
            ctx.stats.add("symbols.calls")
        else:
            out.append("FUN_%08X(%s)" % (addr, ", ".join(args)))
            ctx.stats.mark("symbols.unnamed_calls")
        pos = cl + 1
    return "".join(out)


def p_symbols(doc, ctx):
    s = _rewrite_calls(doc.body, ctx)
    # vtable pointer labels
    if ctx.vtables is None:
        ctx.vtables = {}
        try:
            rt = json.loads((ctx.names.data / "rtti_classes.json").read_text())["classes"]
            for c in rt.values():
                for loc in c.get("locators", []):
                    if loc.get("base_offset") == 0 and loc.get("vtable_va"):
                        ctx.vtables[to_int(loc["vtable_va"])] = c.get("demangled_name")
        except (OSError, ValueError, KeyError):
            pass

    def vt(m):
        addr = int(m.group(1), 16)
        nm = ctx.vtables.get(addr)
        if nm:
            ctx.stats.add("symbols.vtables")
            return "/* vtable %s */ %s" % (nm, m.group(0))
        return m.group(0)
    s = re.sub(r"&PTR_(?:FUN|LAB|s)_?\w*?([0-9a-fA-F]{8})\b", vt, s)

    def dat(m):
        addr = int(m.group(2), 16)
        nm = ctx.names.glob(addr)
        if nm:
            ctx.stats.add("symbols.globals")
            return nm
        return "DAT_%08X" % addr
    s = re.sub(r"(?<![\w])(_?)DAT_([0-9a-fA-F]{8})\b", lambda m: dat(m), s)

    def lbl(m):
        nm = ctx.names.glob(int(m.group(2), 16))
        if nm and not m.group(1).startswith(("FUN_", "switchD", "caseD", "LAB_", "s_")):
            ctx.stats.add("symbols.globals")
            return nm
        return m.group(0)
    s = re.sub(r"(?<![\w])([A-Za-z]\w*?)_([0-9a-fA-F]{8})\b", lambda m: lbl(m) if not m.group(1).startswith("DAT") else m.group(0), s)
    s = re.sub(r"(?<![\w])FUN_([0-9a-fA-F]{8})\b", lambda m: "FUN_%08X" % int(m.group(1), 16), s)
    doc.body = s


# ---------------------------------------------------------------------------
# pass: cleanup (temp collapse, alias inline, do-while -> for, type names)
# ---------------------------------------------------------------------------
PURE_ALIAS = re.compile(r"^(?:&?this(?:->\w+|\.\w+)*|param_\d+|0x[0-9a-fA-F]+|-?\d+)$")


def _count(var, s):
    return len(re.findall(r"(?<![\w.>])%s\b" % re.escape(var), s))


def _has_call_before(text):
    """True when `text` holds a complete call (so its side effects precede whatever follows)."""
    for m in re.finditer(r"([A-Za-z_][\w:>.-]*)\s*\(", text):
        if m.group(1) not in KEYWORDS and match_close(text, m.end() - 1) >= 0:
            return True
    return False


def _depths(lines):
    d, out = 0, []
    for ln in lines:
        st = ln.strip()
        out.append(max(0, d - 1) if st.startswith("}") else d)
        d += ln.count("{") - ln.count("}")
    return out


def _dead_after(v, lines, depth, i, j):
    """v (assigned on line i, consumed on line j) is not read again before being rewritten
    at the same nesting level, and was not live around a loop back-edge."""
    pat = re.compile(r"(?<![\w.>])%s\b" % re.escape(v))
    for k in range(i - 1, -1, -1):
        if depth[k] < depth[i]:
            break
        if pat.search(lines[k]):
            return False
    for k in range(j + 1, len(lines)):
        if depth[k] < depth[i]:
            return True
        if pat.search(lines[k]):
            m = re.match(r"^\s*%s\s*=(?!=)" % re.escape(v), lines[k])
            return bool(m) and depth[k] == depth[i] and pat.search(lines[k].split("=", 1)[1]) is None
    return True


def collapse_temps(doc, ctx):
    s = doc.body
    names = [v for v in doc.locals if v not in doc.loop_decl]
    n = 0
    for _ in range(200):
        lines = s.split("\n")
        depth = _depths(lines)
        done = False
        for i, ln in enumerate(lines[:-1]):
            m = re.match(r"^\s*(\w+)\s*=(?!=)\s*(.+);$", ln)
            if not m or m.group(1) not in names:
                continue
            v, rhs = m.group(1), m.group(2).strip()
            if re.search(r"(?<![\w.>])%s\b" % re.escape(v), rhs):
                continue
            nxt = lines[i + 1]
            pat = re.compile(r"(?<![\w.>])%s\b" % re.escape(v))
            if len(pat.findall(nxt)) != 1 or re.match(r"\s*(?:while|for|do)\b", nxt):
                continue
            if re.match(r"^\s*%s\s*=(?!=)" % re.escape(v), nxt):
                continue
            before = nxt[:pat.search(nxt).start()]
            if _has_call_before(before) and _has_call_before(rhs):
                continue
            if not _dead_after(v, lines, depth, i, i + 1):
                continue
            whole = re.search(r"=\s*%s\s*;$" % re.escape(v), nxt)
            text = rhs if (whole or is_primary(rhs)) else "(" + rhs + ")"
            lines[i + 1] = pat.sub(lambda _m: text, nxt, count=1)
            del lines[i]
            n += 1
            done = True
            break
        s = "\n".join(lines)
        if not done:
            break
    ctx.stats.add("ghidra.temps_collapsed", n)
    doc.body = s


def inline_aliases(doc, ctx):
    s = doc.body
    n = 0
    for v in list(doc.locals):
        assigns = re.findall(r"^\s*%s\s*=\s*(.+);$" % re.escape(v), s, re.M)
        if len(assigns) != 1 or not PURE_ALIAS.match(assigns[0].strip()):
            continue
        rhs = assigns[0].strip()
        if re.search(r"(?<![\w.>])%s\s*(?:\+\+|--|[-+*/&|]?=(?!=))" % re.escape(v), re.sub(r"^\s*%s\s*=.*$" % re.escape(v), "", s, count=1, flags=re.M)):
            continue
        if _count(v, s) < 3:
            continue
        s = re.sub(r"^\s*%s\s*=\s*.+;\n?" % re.escape(v), "", s, count=1, flags=re.M)
        k = _count(v, s)
        s = re.sub(r"(?<![\w.>])%s\b" % re.escape(v), lambda _m: rhs, s)
        n += k
    ctx.stats.add("ghidra.aliases_inlined", n)
    doc.body = s


STEP_UP = r"(?:{v} = {v} \+ 1;|{v}\+\+;|\+\+{v};)"
STEP_DOWN = r"(?:{v} = {v} - 1;|{v} = {v} \+ -1;|{v}--;|--{v};)"


def _loop_shape(cond, body):
    """Return (var, test, step) for a do-while condition/body pair, or None."""
    cond = strip_outer_parens(cond)
    cands = []
    m = re.match(r"^(\w+) (<|<=|!=) (.+)$", cond)
    if m:
        cands.append((m.group(1), "%s %s %s" % (m.group(1), m.group(2), m.group(3)), "++"))
    m = re.match(r"^(?:-1 < |0 <= )(\w+)$", cond) or re.match(r"^(\w+) (?:>= 0|> -1)$", cond)
    if m:
        cands.append((m.group(1), "%s >= 0" % m.group(1), "--"))
    m = re.match(r"^0 < (\w+)$", cond) or re.match(r"^(\w+) > 0$", cond)
    if m:
        cands.append((m.group(1), "%s > 0" % m.group(1), "--"))
    m = re.match(r"^(\w+) (>=|>) (.+)$", cond)
    if m and m.group(3) not in ("0", "-1"):
        cands.append((m.group(1), cond, "--"))
    for v, test, step in cands:
        pat = (STEP_UP if step == "++" else STEP_DOWN).format(v=re.escape(v))
        if re.search(r"(?:^|\n)\s*" + pat + r"\s*$", body):
            return v, test, step, pat
    return None


def loops_to_for(doc, ctx):
    s = doc.body
    n = 0
    for _ in range(30):
        changed = False
        for m in re.finditer(r"^[ \t]*do \{$", s, re.M):
            ob = s.index("{", m.start())
            cb = match_close(s, ob, "{", "}")
            if cb < 0:
                continue
            tail = re.match(r"\s*while \((?P<cond>.*)\);", s[cb + 1:])
            if not tail:
                continue
            body = s[ob + 1:cb]
            shape = _loop_shape(tail.group("cond"), body)
            if not shape:
                continue
            var, test, step, pat = shape
            if re.search(r"\bcontinue\b", body):
                ctx.stats.mark("ghidra.loops_kept")
                continue
            body2 = re.sub(r"\n?\s*" + pat + r"\s*$", "", body, count=1).strip("\n")
            pre = s[:m.start()].rstrip("\n").split("\n")
            after = s[cb + 1 + tail.end():]
            guarded = bool(pre) and re.match(r"^\s*if \(.*\) \{$", pre[-1]) is not None
            if guarded:
                if not after.lstrip().startswith("}"):
                    continue
                pre = pre[:-1]
                after = after.lstrip()[1:]
            init = None
            k = len(pre) - 1
            steps = 0
            while k >= 0 and steps < 8:
                ln = pre[k]
                im = re.match(r"^\s*%s = ([^;]+);$" % re.escape(var), ln)
                if im:
                    init = im.group(1)
                    del pre[k]
                    break
                if ln.strip().startswith("}"):
                    depth = 0
                    while k >= 0:
                        depth += pre[k].count("}") - pre[k].count("{")
                        if depth <= 0 and not pre[k].strip().startswith("}") or (depth == 0 and k != len(pre) - 1 and "{" in pre[k]):
                            break
                        k -= 1
                    k -= 1
                    steps += 1
                    continue
                if re.search(r"(?<![\w.>])%s\b" % re.escape(var), ln) or ln.strip().endswith("{"):
                    break
                k -= 1
                steps += 1
            outside = "\n".join(pre) + after
            used_outside = re.search(r"(?<![\w.>])%s\b" % re.escape(var), outside) is not None
            decl = "" if used_outside or init is None else "int "
            if init is None:
                hdr = "for (; %s; %s%s) {" % (test, var, step)
            else:
                hdr = "for (%s%s = %s; %s; %s%s) {" % (decl, var, init, test, var, step)
            if decl:
                doc.loop_decl.add(var)
            s = "\n".join(pre) + ("\n" if pre else "") + hdr + "\n" + body2 + "\n}" + after
            n += 1
            changed = True
            break
        if not changed:
            break
    # while (V = V + -1, -1 < V) { ... }   -> reverse counted loop
    for _ in range(10):
        m = re.search(r"^[ \t]*while \((?P<v>\w+) = (?P=v) \+ -1, (?:-1 < (?P=v)|(?P=v) >= 0)\) \{$", s, re.M)
        if not m:
            break
        v = m.group("v")
        pre = s[:m.start()].rstrip("\n").split("\n")
        init = None
        k = len(pre) - 1
        steps = 0
        while k >= 0 and steps < 8:
            ln = pre[k]
            im = re.match(r"^\s*%s = ([\w>.\-]+);$" % re.escape(v), ln)
            if im:
                init = im.group(1)
                if k == len(pre) - 1:
                    del pre[-1]
                break
            if ln.strip().startswith("}"):
                depth = 0
                while k >= 0:
                    depth += pre[k].count("}") - pre[k].count("{")
                    if depth <= 0 and "{" in pre[k]:
                        break
                    k -= 1
                k -= 1
                steps += 1
                continue
            if ln.strip().endswith("{"):
                break
            k -= 1
            steps += 1
        if init is None:
            s = s[:m.start()] + s[m.start():].replace(m.group(0), m.group(0) + " /* LIFT? reverse loop, init not found */", 1)
            ctx.stats.mark("ghidra.loops_kept")
            break
        adj = init if re.fullmatch(r"-?\d+", init) is None else str(int(init) - 1)
        hdr = "for (%s%s = %s - 1; %s >= 0; %s--) {" % ("int " if len(pre) == len(s[:m.start()].rstrip("\n").split("\n")) - 1 else "", v, init, v, v) \
            if adj == init else "for (%s = %s; %s >= 0; %s--) {" % (v, adj, v, v)
        if hdr.startswith("for (int"):
            doc.loop_decl.add(v)
        s = "\n".join(pre) + ("\n" if pre else "") + hdr + s[m.end():]
        n += 1
    ctx.stats.add("ghidra.loops_to_for", n)
    doc.body = s


def p_cleanup(doc, ctx):
    loops_to_for(doc, ctx)
    inline_aliases(doc, ctx)
    collapse_temps(doc, ctx)
    s = doc.body
    # (char)call == '\0'  ->  !call ; noise casts
    s, k = sub_count(r"\(\s*char\s*\)\s*([\w:>.-]+\([^;{}]*?\))\s*==\s*'\\0'", r"!\1", s)
    ctx.stats.add("ghidra.noise_casts", k)
    k2 = 0
    while True:
        mm = re.search(r"\(\s*char\s*\)\s*\(", s)
        if not mm:
            break
        op = mm.end() - 1
        cl = match_close(s, op)
        tail = re.match(r"\s*(==|!=)\s*'\\0'", s[cl + 1:]) if cl > 0 else None
        if not tail:
            s = s[:mm.start()] + "(char_)" + s[mm.end() - 1:]
            continue
        inner = s[op + 1:cl]
        rep = ("!" + paren(inner)) if tail.group(1) == "==" else inner
        s = s[:mm.start()] + rep + s[cl + 1 + tail.end():]
        k2 += 1
    s = s.replace("(char_)", "(char)")
    ctx.stats.add("ghidra.noise_casts", k2)
    s, k = sub_count(r"\(\s*char\s*\)\s*(\w+)\s*==\s*'\\0'", r"!\1", s)
    ctx.stats.add("ghidra.noise_casts", k)
    s, k = sub_count(r"\(\s*char\s*\)\s*(\w+)\s*!=\s*'\\0'", r"\1", s)
    ctx.stats.add("ghidra.noise_casts", k)
    s, k = sub_count(r"\(\s*(?:int|uint)\s*\)\s*(\w+)\s*(==|!=|<|>|<=|>=)\s*(-?\d+|0x[0-9a-f]+)\b", r"\1 \2 \3", s)
    ctx.stats.add("ghidra.noise_casts", k)
    # (this->X)->y  ->  this->X->y
    s = re.sub(r"\(((?:this|\w+)(?:->\w+|\.\w+)*)\)(->|\.)", r"\1\2", s)
    for a, b in PSEUDO_TYPES:
        s = re.sub(r"\b%s\b" % a, b, s)
    s = re.sub(r"\b0xffffffff\b", "-1", s)
    s = re.sub(r"\b0xfffffff([0-9a-e])\b", lambda m: str(int(m.group(1), 16) - 16), s)
    # drop declarations now unused
    doc.body = s
    ctx.stats.add("ghidra.locals_left", sum(1 for v in doc.locals if v not in doc.loop_decl and _count(v, s) > 0))


# ---------------------------------------------------------------------------
# pass: ini  (Field = ini->ReadX(ID, "Key", Field))
# ---------------------------------------------------------------------------
INI_ASSIGN = re.compile(r"^(?P<ind>\s*)(?P<lhs>[\w>.\-\[\]]+)\s*=\s*(?P<cast>\(\s*(?:float|double|bool|int|unsigned int|unsigned char)\s*\)\s*)?"
                        r"(?P<recv>[\w>.\-]+)->(?P<m>Read\w*)\((?P<args>.*)\);\s*(?P<tail>/\*.*\*/)?$")


def p_ini(doc, ctx):
    out = []
    for ln in doc.body.split("\n"):
        m = INI_ASSIGN.match(ln)
        if not m:
            out.append(ln)
            continue
        args = split_top(m.group("args"))
        lhs, cast = m.group("lhs"), (m.group("cast") or "").strip()
        meth = m.group("m")
        if len(args) < 3 or not (args[1].startswith('"') and args[1].endswith('"')):
            out.append(ln)
            ctx.stats.mark("ini.shape")
            continue
        sec = args[0].replace("this->", "") if args[0] == "this->ID" else args[0]
        dflt = strip_outer_parens(args[2])
        dflt_stripped = re.sub(r"^\(\s*\w+\s*\)\s*", "", dflt)
        ftype = ctx.field_types.get(lhs)
        keep_cast = cast
        ret = {"ReadDouble": "double", "ReadInteger": "int", "ReadBool": "bool"}.get(meth)
        if cast and re.sub(r"\s", "", cast.strip("()")) == ret:
            keep_cast = ""
        if dflt_stripped == lhs:
            # the default is the field itself: the canonical reader idiom
            new = "%s%s = %s%s->%s(%s);" % (m.group("ind"), lhs, keep_cast, m.group("recv"), meth,
                                             ", ".join([args[0]] + [args[1]] + [lhs] + args[3:]))
            out.append(new)
            ctx.stats.add("ini")
        else:
            out.append(ln)
            ctx.stats.mark("ini.other_default")
    doc.body = "\n".join(out)


# ---------------------------------------------------------------------------
# pass: vector
# ---------------------------------------------------------------------------
def _block_end(lines, i):
    """Given lines[i] ending with '{', return the index of the matching '}' line."""
    depth = 0
    for j in range(i, len(lines)):
        depth += lines[j].count("{") - lines[j].count("}")
        if depth == 0 and j > i or (depth == 0 and "}" in lines[j] and j >= i and lines[j].strip().startswith("}")):
            return j
    return -1


def _fld(vec, name):
    return re.escape(vec) + r"(?:\.|->)" + name


def _vcall(vec, text):
    return ("%s->%s" if vec == "this" else "%s.%s") % (vec, text)


def p_vector(doc, ctx):
    n_add = n_del = n_idx = n_loop = 0
    def elem(m):
        nonlocal n_idx
        t = m.group("t").strip()
        sz = {"int": 4, "unsigned int": 4, "uint": 4, "undefined4": 4, "float": 4, "double": 8,
              "short": 2, "char": 1, "byte": 1, "ushort": 2, "void *": 4}.get(t, 4 if t.endswith("*") else None)
        if sz is None or sz != to_int(m.group("n")):
            return m.group(0)
        n_idx += 1
        c = m.group("c")
        if c and to_int(c) % sz == 0:
            return "%s[%s + %d]" % (m.group("v"), m.group("i").strip(), to_int(c) // sz)
        if c:
            return m.group(0)
        return "%s[%s]" % (m.group("v"), m.group("i").strip())
    doc.body = re.sub(r"\*\(\s*(?P<t>[\w ]+?\s*\**)\s*\*\s*\)\s*\(\s*(?P<v>[A-Za-z_][\w>.\-]*)\s*\+\s*(?P<i>\w+)\s*\*\s*(?P<n>\d+)(?:\s*\+\s*(?P<c>\d+))?\s*\)", elem, doc.body)
    doc.body, k = re.subn(r"\(\s*(?:int|void)\s*\*\s*\)\s*\(\s*([\w>.\-]*Items)\s*\+\s*(\w+)\s*\*\s*4\s*\)", r"&\1[\2]", doc.body)
    n_idx += k
    lines = doc.body.split("\n")
    i = 0
    while i < len(lines):
        ln = lines[i]
        m = re.match(r"^(\s*)if \((.*)\) \{$", ln)
        if m and "CapacityIncrement" in ln and ".Count" in ln.replace("->Count", ".Count") and "IsAllocated" in ln:
            vm = re.search(r"([\w>.\-]+?)(?:\.|->)CapacityIncrement", ln)
            vec = vm.group(1)
            end = _block_end(lines, i)
            body = [l.strip() for l in lines[i + 1:end]]
            item = None
            keep = []
            for b in body:
                mi = re.match(r"^%s\.Items\[[^\]]+\]\s*=\s*(.+);$" % re.escape(vec), b) or \
                    re.match(r"^%s->Items\[[^\]]+\]\s*=\s*(.+);$" % re.escape(vec), b)
                if mi:
                    item = mi.group(1)
                    continue
                if re.match(r"^%s\s*=\s*.+\+ 1;$" % _fld(vec, "Count"), b) or re.match(r"^%s\+\+;$" % _fld(vec, "Count"), b) \
                        or re.match(r"^\w+ = %s;$" % _fld(vec, "Count"), b):
                    continue
                keep.append(b)
            if item is not None and end > 0:
                has_else = end + 1 < len(lines) and lines[end + 1].strip().startswith("else")
                if not keep and not has_else:
                    lines[i:end + 1] = [m.group(1) + _vcall(vec, "AddItem(%s);" % item)]
                else:
                    lines[i] = m.group(1) + "if (%s) {" % _vcall(vec, "AddItem(%s)" % item)
                    lines[i + 1:end] = [m.group(1) + "    " + k for k in keep]
                n_add += 1
                i += 1
                continue
            lines[i] = ln + " /* LIFT? AddItem-shaped condition */"
            ctx.stats.mark("vector.additem_partial")
        i += 1
    s = "\n".join(lines)
    # Delete(index): Count = Count - 1 followed by the shift loop
    pat = re.compile(r"(?P<ind>[ \t]*)(?P<v>[\w>.\-]+?)(?:\.|->)Count = (?P=v)(?:\.|->)Count - 1;\n\s*for \((?:int )?(?P<i>\w+) = (?P<idx>[^;]+); (?P=i) < (?P=v)(?:\.|->)Count; (?:(?P=i)\+\+|(?P=i) = (?P=i) \+ 1)\) \{\n\s*(?P=v)(?:\.|->)Items\[(?P=i)\] = (?P=v)(?:\.|->)Items\[(?P=i) \+ 1\];\n\s*\}")
    s, n_del = pat.subn(lambda m: "%s%s;" % (m.group("ind"), _vcall(m.group("v"), "Delete(%s)" % m.group("idx").strip())), s)
    pat2 = re.compile(r"(?P<ind>[ \t]*)(?P<i>\w+) = (?P<v>[\w>.\-]+?)(?:\.|->)vf_4\((?P<a>[^;]*)\);\n\s*if \((?:-1 < (?P=i)|(?P=i) != -1)\) \{\n\s*(?P=v)(?:\.|->)Delete\((?P=i)\);\n\s*\}")
    s, n_rm = pat2.subn(lambda m: "%s%s;" % (m.group("ind"), _vcall(m.group("v"), "RemoveItem(%s)" % m.group("a").lstrip("&"))), s)
    n_del += n_rm

    n_loop = len(re.findall(r"for \((?:int )?\w+ = [^;]+; \w+ [<>]=? [\w>.\-]+(?:\.|->)Count;", s)) + \
        len(re.findall(r"for \((?:int )?\w+ = [^;]*(?:\.|->)Count - 1; \w+ >= 0;", s))
    # drop pure temporaries the AddItem expansion left dead
    for v in list(doc.locals):
        if _count(v, s) == 1:
            s = re.sub(r"^[ \t]*%s = [\w>.\-]+;\n?" % re.escape(v), "", s, count=1, flags=re.M)
    doc.body = s
    ctx.stats.add("vector.additem", n_add)
    ctx.stats.add("vector.delete_remove", n_del)
    ctx.stats.add("vector.items_index", n_idx)
    ctx.stats.add("vector.count_loops", n_loop)


# ---------------------------------------------------------------------------
# pass: rtti
# ---------------------------------------------------------------------------
RTTI_TABLE = 0x816EE0
RTTI_COUNT = 74


def _load_rtti_names(ctx):
    if ctx.rtti_names is not None:
        return ctx.rtti_names
    ctx.rtti_names = {}
    raw = ctx.reader.read(RTTI_TABLE, RTTI_COUNT * 8)
    if raw and len(raw) >= RTTI_COUNT * 8:
        import struct
        for k in range(RTTI_COUNT):
            ptr, key = struct.unpack_from("<II", raw, k * 8)
            nm = ctx.reader.cstring(ptr, 64)
            if nm:
                ctx.rtti_names[key] = nm
    return ctx.rtti_names


def p_rtti(doc, ctx):
    names = None
    n = 0

    def rep(m):
        nonlocal names, n
        if names is None:
            names = _load_rtti_names(ctx)
        val = to_int(m.group("v"))
        n += 1
        label = names.get(val)
        return "%s %s %s /* %s */" % (m.group("call"), m.group("op"), m.group("v"),
                                      ("AbstractType " + label) if label else "AbstractType %d" % val)
    doc.body = re.sub(r"(?P<call>[\w>.\-]+->vf_11\(\))\s*(?P<op>==|!=)\s*(?P<v>0x[0-9a-fA-F]+|\d+)\b(?!\s*/\*)", rep, doc.body)
    ctx.stats.add("rtti", n)


# ---------------------------------------------------------------------------
# pass: timer
# ---------------------------------------------------------------------------
def p_timer(doc, ctx):
    s = doc.body
    frame = r"(?:CurrentFrame|DAT_00A8ED84)"
    pat = re.compile(
        r"(?P<ind>[ \t]*)(?P<v>\w+) = (?P<t>[\w>.\-]+)\.TimeLeft;\s*"
        r"if \((?P=t)\.StartTime != (?:-1|0xffffffff)\) \{\s*"
        r"(?P<e>\w+) = " + frame + r" - (?P=t)\.StartTime;\s*"
        r"if \((?P=e) < (?P=v)\) \{\s*(?P=v) = (?P=v) - (?P=e);\s*\}\s*else \{\s*(?P=v) = 0;\s*\}\s*\}")
    s, n = pat.subn(lambda m: "%s%s = %s.GetTimeLeft();" % (m.group("ind"), m.group("v"), m.group("t")), s)
    pat2 = re.compile(r"(?P<ind>[ \t]*)(?P<t>[\w>.\-]+)\.StartTime = " + frame + r";\s*(?P=t)\.TimeLeft = (?P<d>[^;]+);")
    s, n2 = pat2.subn(lambda m: "%s%s.Start(%s);" % (m.group("ind"), m.group("t"), m.group("d")), s)
    left = len(re.findall(frame + r" - [\w>.\-]+\.StartTime", s))
    if left:
        ctx.stats.mark("timer.partial", left)
        s = re.sub(r"^(.*" + frame + r" - [\w>.\-]+\.StartTime.*;)$", r"\1 /* LIFT? CDTimerClass inline */", s, flags=re.M)
    doc.body = s
    ctx.stats.add("timer", n + n2)


# ---------------------------------------------------------------------------
# pass: coord  (cell <-> lepton shifts)
# ---------------------------------------------------------------------------
def p_coord(doc, ctx):
    s = doc.body
    s, n1 = sub_count(r"(\b[\w>.\-]+\.(?:X|Y)|\b\w*[cC]oord\w*)\s*>>\s*8\b(?!\s*/\*)", r"\1 >> 8 /* coord->cell */", s)
    s, n2 = sub_count(r"(\b[\w>.\-]+\.(?:X|Y)|\b\w*[cC]ell\w*)\s*<<\s*8\b(?!\s*/\*)", r"\1 << 8 /* cell->coord */", s)
    doc.body = s
    ctx.stats.add("coord", n1 + n2)


# ---------------------------------------------------------------------------
# pass: assert
# ---------------------------------------------------------------------------
def p_assert(doc, ctx):
    n = 0
    out = []
    for ln in doc.body.split("\n"):
        m = re.search(r'\w[\w:>.\-]*\([^;]*"([^"]+\.(?:cpp|h|c))"[^;]*,\s*(\d{2,5})\b[^;]*\);', ln)
        if m and "LIFT" not in ln:
            ln += " /* assert site: %s:%s (retail builds no assert; project has no assert macro) */" % (m.group(1), m.group(2))
            n += 1
        out.append(ln)
    doc.body = "\n".join(out)
    ctx.stats.add("assert", n)


# ---------------------------------------------------------------------------
# pass: sinit  (runs of stores into consecutive globals -> table skeleton)
# ---------------------------------------------------------------------------
STORE_RE = re.compile(r"^\s*(?:\*\(\w[\w ]*\*\)\s*\(?\s*&?)?_?(?:DAT_(?P<a>[0-9a-fA-F]{8})|(?P<g>[A-Za-z_]\w*))\)?\s*=\s*(?P<v>-?0x[0-9a-fA-F]+|-?\d+)\s*;\s*$")
INDEXED_RE = re.compile(r"^\s*\(&(?:_?DAT_(?P<a>[0-9a-fA-F]{8}))\)\[(?P<i>\d+)\]\s*=\s*(?P<v>-?0x[0-9a-fA-F]+|-?\d+)\s*;\s*$")


def _signed(v, width=4):
    if v >= 1 << (8 * width - 1) and v < 1 << (8 * width):
        return v - (1 << (8 * width))
    return v


def p_sinit(doc, ctx):
    lines = doc.body.split("\n")
    out, i, n = [], 0, 0
    while i < len(lines):
        run = []
        j = i
        while j < len(lines):
            m = INDEXED_RE.match(lines[j])
            if m:
                run.append((int(m.group("a"), 16) + 4 * int(m.group("i")), to_int(m.group("v")), m.group("a")))
                j += 1
                continue
            m = STORE_RE.match(lines[j])
            if m and m.group("a"):
                run.append((int(m.group("a"), 16), to_int(m.group("v")), m.group("a")))
                j += 1
                continue
            break
        if len(run) >= 4 and len({a for a, _, _ in run}) == len(run):
            base = min(a for a, _, _ in run)
            addrs = sorted(a for a, _, _ in run)
            stride = 4
            if all((a - base) % 4 == 0 for a in addrs):
                stride = 4
            elif all((a - base) % 2 == 0 for a in addrs):
                stride = 2
            else:
                stride = 1
            last = max(addrs)
            count = (last - base) // stride + 1
            vals = {a: v for a, v, _ in run}
            cells = []
            for k in range(count):
                a = base + k * stride
                if a in vals:
                    cells.append(str(_signed(vals[a], stride)) if stride == 4 else str(vals[a]))
                else:
                    cells.append("0 /* LIFT? gap */")
            ty = {4: "int", 2: "short", 1: "char"}[stride]
            nm = ctx.names.glob(base) or "DAT_%08X" % base
            body = ",\n".join("    " + ", ".join(cells[k:k + 8]) for k in range(0, len(cells), 8))
            out.append("%s %s[%d] = {\n%s\n};" % (ty, nm, count, body.replace(",\n", ",\n")))
            n += 1
            i = j
            continue
        out.append(lines[i])
        i += 1
    doc.body = "\n".join(out)
    ctx.stats.add("sinit", n)


# ---------------------------------------------------------------------------
# driver
# ---------------------------------------------------------------------------
PASSES = OrderedDict([
    ("ghidra", p_ghidra),
    ("strings", p_strings),
    ("vcalls", p_vcalls),
    ("fields", p_fields),
    ("symbols", p_symbols),
    ("cleanup", p_cleanup),
    ("ini", p_ini),
    ("vector", p_vector),
    ("rtti", p_rtti),
    ("timer", p_timer),
    ("coord", p_coord),
    ("assert", p_assert),
    ("sinit", p_sinit),
])


def reindent(body):
    out, depth, case_extra = [], 0, []
    for ln in body.split("\n"):
        s = ln.strip()
        if not s:
            continue
        if s.startswith("}"):
            depth = max(0, depth - 1)
            if case_extra:
                case_extra.pop()
        is_case = bool(re.match(r"^(?:case\b.*|default):", s))
        extra = case_extra[-1] if case_extra else 0
        if is_case and case_extra:
            case_extra[-1] = 1
            out.append("    " * depth + s)
        else:
            out.append("    " * (depth + extra) + s)
        opens = s.count("{") - s.count("}") + (1 if s.startswith("}") else 0)
        if s.startswith("}") and s.rstrip().endswith("{"):
            case_extra.append(0)
            depth += 1
        elif opens > 0:
            for _ in range(opens):
                is_sw = s.startswith("switch")
                case_extra.append(0)
                depth += 1
    return "\n".join(out)


def c_ret(doc, ctx):
    t = ctx.ret_type or _c_type_of(doc.ret)
    return t


def lift_text(text, ctx, passes=None, implicit_this=False):
    doc = Doc(text)
    ctx.doc = doc
    info = None
    if ctx.addr is not None:
        info = ctx.names.func(ctx.addr)
        if info:
            ctx.func = info
            if not ctx.cls and info["cls"]:
                ctx.cls = info["cls"]
            if info["ret"]:
                ctx.ret_type = info["ret"]
    for name, fn in PASSES.items():
        if passes is not None and name not in passes:
            continue
        fn(doc, ctx)
    body = doc.body
    for _ in range(3):
        body = re.sub(r"([(,] ?)\(([\w>.\-]+(?:\[[\w>.\- +*]*\])?)\)(?=[,);])", r"\1\2", body)
    body = re.sub(r"\(((?:this|\w+)(?:->\w+|\.\w+)*)\)(->|\.)", r"\1\2", body)
    if implicit_this:
        body = re.sub(r"\bthis->", "", body)
    body = reindent(body)
    return doc, body


def _pname(t, gname):
    return "ini" if re.fullmatch(r"(?:const )?CCINIClass\*", t) else gname


def build_output(doc, body, ctx, addr=None):
    st = ctx.stats
    fn = ctx.func
    if fn and fn["args"] is not None:
        ptypes = fn["args"]
        gnames = [n for _, n in doc.params[1 if doc.this_name else 0:]]
        gnames += ["param_%d" % (k + 1) for k in range(len(gnames), len(ptypes))]
        plist = ", ".join("%s %s" % (t, _pname(t, gnames[k])) for k, t in enumerate(ptypes))
        qual = fn["qualified"]
        ret = ctx.ret_type or "int"
        sig = "%s %s(%s)" % (ret, qual, plist)
    else:
        prm = [p for p in doc.params[1 if doc.this_name else 0:]]
        plist = ", ".join("%s %s" % (_c_type_of(t), n) for t, n in prm)
        qual = (ctx.cls + "::" if ctx.cls else "") + (fn["name"] if fn else doc.fname)
        sig = "%s %s(%s)" % (ctx.ret_type or _c_type_of(doc.ret), qual, plist)
    hdr = ["// idiom_lift first draft%s -- NOT matched; confirm every fact against the binary" %
           (" for 0x%X" % addr if addr is not None else ""),
           "// Provenance: own-binary-via-Ghidra (pseudo-C rewritten at run time; hypotheses only)",
           "// passes fired (sites):"]
    for k, v in st.sites.items():
        if v:
            hdr.append("//   %-26s %d" % (k, v))
    for k, v in st.marks.items():
        if v:
            hdr.append("//   LIFT? %-20s %d" % (k, v))
    for cls, offs in ctx.unmapped.items():
        hdr.append("// LIFT? offsets with no layout field in %s: %s" % (cls, " ".join("0x%X" % o for o in sorted(offs))))
    if fn and fn["args"] is not None:
        for k, t in enumerate(fn["args"]):
            if k < len(gnames) and _pname(t, gnames[k]) != gnames[k]:
                body = re.sub(r"\b%s\b" % gnames[k], _pname(t, gnames[k]), body)
    decl = []
    for v, (t, dim) in doc.locals.items():
        if v in doc.loop_decl or _count(v, body) == 0:
            continue
        decl.append("    %s %s%s;" % (_c_type_of(t), v, dim))
    lines = ["// FUNCTION: GAMEMD 0x%X" % addr if addr is not None else "// FUNCTION: GAMEMD 0x????", sig, "{"]
    lines += decl
    lines += ["    " + l for l in body.split("\n")]
    lines.append("}")
    return "\n".join(hdr + lines) + "\n"


def fetch_pseudo(addr):
    out = subprocess.run(["ghidra", "decompile", "0x%X" % addr], capture_output=True, text=True, timeout=300)
    try:
        return json.loads(out.stdout)[0]["code"]
    except (ValueError, KeyError, IndexError):
        raise SystemExit("ghidra decompile failed for 0x%X: %s" % (addr, (out.stdout + out.stderr)[:300]))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("addr", nargs="?", help="function address, e.g. 0x721A50")
    ap.add_argument("--file", help="read pseudo-C from a file instead of Ghidra")
    ap.add_argument("--class", dest="cls", help="owning class (when not in manifest/bindings)")
    ap.add_argument("--out", help="write the draft here instead of stdout")
    ap.add_argument("--passes", help="comma list; default all: " + ",".join(PASSES))
    ap.add_argument("--implicit-this", action="store_true", help="drop the this-> prefix")
    ap.add_argument("--no-ghidra-reads", action="store_true", help="never shell out for string reads")
    a = ap.parse_args(argv)
    addr = to_int(a.addr) if a.addr else None
    if a.file:
        text = Path(a.file).read_text()
    elif addr is not None:
        text = fetch_pseudo(addr)
    else:
        ap.error("need an address or --file")
    ctx = Ctx(cls=a.cls, addr=addr, reader=Reader(use_ghidra=not a.no_ghidra_reads))
    passes = set(a.passes.split(",")) if a.passes else None
    doc, body = lift_text(text, ctx, passes, a.implicit_this)
    res = build_output(doc, body, ctx, addr)
    if a.out:
        Path(a.out).write_text(res)
    else:
        sys.stdout.write(res)
    return 0


if __name__ == "__main__":
    sys.exit(main())

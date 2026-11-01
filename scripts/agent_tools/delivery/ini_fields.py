#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads only the user's retail gamemd.exe (GAMEMD_BINARY), scripts/data/*.json and match/.
"""ini_fields.py: member names from the INI keys the retail readers store into them.

A retail type reader calls an INI read function with a key string and stores the result into `this+offset`
(or, in a writer, loads the member as the value argument). The key is binary-attested spelling for the member.
`extract` reads those sites straight from the image (matched and unmatched readers alike); `plan` joins them
with the canonical class headers and lists which placeholder members can be named; `apply` renames the
declaration, its assert and every use, then the full gate proves the bytes did not move.

    ini_fields.py extract [--out FILE]                evidence JSON (per reader function: class, key, offset, width, kind)
    ini_fields.py plan    [--tree T] [--evidence F] [--family F] [--json OUT]   rename plan per class family
    ini_fields.py apply   [--tree T] [--plan F] [--family F]

Rules: only placeholder members (unknown_*, field_*, DAT_* ...) are renamed, only to a name derived from the key;
an already-named member whose name differs from the key is reported as a conflict, never renamed.
"""
import argparse
import bisect
import collections
import json
import os
import re
import struct
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(os.path.dirname(HERE)))

# INI readers (address -> (kind, width in bytes))
READERS = {
    0x5276D0: ("ReadInteger", 4), 0x5295F0: ("ReadBool", 1), 0x5283D0: ("ReadDouble", 8), 0x528A10: ("ReadString", 0),
    0x474620: ("ReadFraction", 4), 0x474810: ("ReadPercentAsByte", 4), 0x475D70: ("ReadIntegerList", 0),
    0x4741F0: ("ReadCCFile", 0), 0x474DA0: ("ReadFoundation", 4), 0x474A90: ("ReadColorScheme", 4),
    0x4754B0: ("ReadLandType", 4), 0x4756F0: ("ReadMovie", 4), 0x4753F0: ("ReadArmor", 4), 0x4759F0: ("FUN_004759F0", 4),
    0x474B50: ("Read3Bytes", 0), 0x474C70: ("ReadColor", 0), 0x477640: ("ReadAbilities", 0), 0x476EB0: ("GetTechnoType", 4),
    0x4748A0: ("ReadPip", 4), 0x474940: ("ReadPipScale", 4), 0x474E40: ("ReadMovementZone", 4), 0x474EE0: ("ReadSuperWeaponAction", 4),
    0x4757D0: ("FUN_004757D0", 4), 0x475820: ("FUN_00475820", 4), 0x475870: ("FUN_00475870", 4), 0x4758F0: ("ReadTheme", 4),
    0x476340: ("ReadFloatTriple", 0), 0x476420: ("ReadIntTriple", 0), 0x4749E0: ("FUN_004749E0", 4), 0x474B20: ("FUN_00474B20", 4),
    0x474F50: ("FUN_00474F50", 4), 0x474FA0: ("FUN_00474FA0", 4), 0x474FF0: ("FUN_00474FF0", 4), 0x475060: ("FUN_00475060", 4),
    0x475980: ("FUN_00475980", 4),
}
# writers load the member as the value argument: (address -> kind)
WRITERS = {0x5275C0: "WriteInteger", 0x5285B0: "WriteDouble", 0x529560: "WriteBool"}

MEM = re.compile(r"\[(e[a-z]{2})(?:\+0x([0-9a-f]+))?\]")
STORE = re.compile(r"^mov\s+(BYTE|WORD|DWORD) PTR \[(e[a-z]{2})(?:\+0x([0-9a-f]+))?\],(e?[a-d][xlh]?|e?[sd]il?|e?[sb]p)$")
FSTP = re.compile(r"^fstp\s+(QWORD|DWORD) PTR \[(e[a-z]{2})(?:\+0x([0-9a-f]+))?\]$")
LOAD = re.compile(r"^(?:mov|movzx|movsx)\s+(e?[a-d]x|e?[sd]i|e?[a-d][lh]|e[sb]p)\w*,(?:(BYTE|WORD|DWORD) PTR )?\[(e[a-z]{2})(?:\+0x([0-9a-f]+))?\]$")
PUSHM = re.compile(r"^push\s+(?:DWORD PTR )?\[(e[a-z]{2})(?:\+0x([0-9a-f]+))?\]$")
FLD = re.compile(r"^fld\s+(?:QWORD|DWORD) PTR \[(e[a-z]{2})(?:\+0x([0-9a-f]+))?\]$")
LEA = re.compile(r"^lea\s+(e[a-d]x),\[(e[a-z]{2})(?:\+0x([0-9a-f]+))?\]$")
PUSHI = re.compile(r"^push\s+0x([0-9a-f]+)$")
PUSHR = re.compile(r"^push\s+(e[a-z]{2})$")
CALL = re.compile(r"^call\s+0x([0-9a-f]+)$")
KEYRE = re.compile(r"[A-Za-z][A-Za-z0-9_.%]*")
FULL = {"al": "eax", "ax": "eax", "eax": "eax", "cl": "ecx", "cx": "ecx", "ecx": "ecx", "dl": "edx", "dx": "edx", "edx": "edx",
        "bl": "ebx", "bx": "ebx", "ebx": "ebx", "esi": "esi", "si": "esi", "edi": "edi", "di": "edi", "ebp": "ebp", "bp": "ebp",
        "ah": "eax", "ch": "ecx", "dh": "edx", "bh": "ebx"}


class Image:
    def __init__(self, path):
        self.data = open(path, "rb").read()
        d = self.data
        pe = struct.unpack_from("<I", d, 0x3C)[0]
        nsec, optsz = struct.unpack_from("<H", d, pe + 6)[0], struct.unpack_from("<H", d, pe + 20)[0]
        self.base = struct.unpack_from("<I", d, pe + 52)[0]
        self.secs = []
        for i in range(nsec):
            o = pe + 24 + optsz + 40 * i
            vsz, va, rsz, roff = struct.unpack_from("<IIII", d, o + 8)
            self.secs.append((self.base + va, vsz, roff, rsz, struct.unpack_from("<I", d, o + 36)[0]))

    def read(self, va, n):
        for s, vsz, roff, rsz, ch in self.secs:
            if s <= va < s + rsz:
                return self.data[roff + va - s: roff + va - s + n]
        return b""

    def cstr(self, va):
        b = self.read(va, 96)
        e = b.find(b"\0")
        if e <= 0:
            return None
        t = b[:e]
        return t.decode() if all(32 <= c < 127 for c in t) else None

    def dword(self, va):
        b = self.read(va, 4)
        return struct.unpack("<I", b)[0] if len(b) == 4 else None

    def is_code(self, va):
        return any(s <= va < s + vsz and ch & 0x20 for s, vsz, _, _, ch in self.secs)


def disassemble(exe):
    out = subprocess.run(["objdump", "-d", "-M", "intel", "--no-show-raw-insn", exe], capture_output=True, text=True, check=True).stdout
    ins = []
    for l in out.split("\n"):
        m = re.match(r"\s+([0-9a-f]+):\t(.*)", l)
        if m:
            ins.append((int(m.group(1), 16), re.sub(r"\s+", " ", m.group(2).strip()).replace(", ", ",")))
    return ins


def vtable_holders(img, rtti):
    """function VA -> {class: slot} over primary RTTI vtables, and class -> base chain."""
    chain, holders = {}, collections.defaultdict(dict)
    starts = {int(l["vtable_va"], 16) for c in rtti.values() for l in c.get("locators", []) if l.get("vtable_va")}
    for c in rtti.values():
        name = c.get("demangled_name")
        if not name:
            continue
        chain[name] = c.get("base_chain") or [name]
        for loc in c.get("locators", []):
            if not loc.get("vtable_va") or loc.get("base_offset", 0):
                continue
            v = int(loc["vtable_va"], 16)
            for k in range(1024):
                w = img.dword(v + 4 * k)
                if w is None or not img.is_code(w) or (k and v + 4 * k in starts):
                    break
                holders[w].setdefault(name, k)
    return holders, chain


def short(n):
    return n.split("<")[0].split("::")[-1]


def owner_of(sym):
    if not sym or not sym.startswith("?"):
        return None
    m = re.match(r"\?\?(?:_[0-9A-Z]|[0-9A-Z])(\?\$)?(\w+)@", sym) or re.match(r"\?[^@?]+@(\w+)@", sym)
    return m.group(m.lastindex) if m else None


def near_call(body, k, j):
    return any(CALL.match(body[x][1]) for x in range(k + 1, j))


def extract(exe, repo):
    img = Image(exe)
    ins = disassemble(exe)
    addrs = [a for a, _ in ins]
    ext = json.load(open(os.path.join(repo, "scripts/data/function_extents.json")))["entries"]
    starts = sorted(int(e[0], 16) for e in ext)
    rtti = json.load(open(os.path.join(repo, "scripts/data/rtti_classes.json")))["classes"]
    holders, chain = vtable_holders(img, rtti)
    man = {int(r["addr"], 16): r for r in json.load(open(os.path.join(repo, "scripts/data/match_manifest.json")))}
    recs = []
    reader_sites = collections.Counter()
    for fi, f0 in enumerate(starts):
        f1 = starts[fi + 1] if fi + 1 < len(starts) else f0 + 0x10000
        i0 = bisect.bisect_left(addrs, f0)
        i1 = bisect.bisect_left(addrs, f1)
        body = ins[i0:i1]
        if len(body) < 8:
            continue
        calls = [k for k, (a, t) in enumerate(body) if CALL.match(t) and int(CALL.match(t).group(1), 16) in READERS | WRITERS]
        if not calls:
            continue
        # the `this` register: the first `mov REG,ecx` before any call
        this = None
        for a, t in body[:8]:
            m = re.match(r"^mov (e[sd]i|ebx|ebp),ecx$", t)
            if m:
                this = m.group(1)
                break
            if CALL.match(t):
                break
        if this is None:
            continue
        row = man.get(f0)
        hs = holders.get(f0, {})
        for k in calls:
            tgt = int(CALL.match(body[k][1]).group(1), 16)
            kind = (READERS.get(tgt) or (WRITERS[tgt], 0))[0]
            width = (READERS.get(tgt) or (0, 0))[1]
            key = None
            lea_before = None
            npush = 0
            argoff = []     # offsets of [this+off] loaded as arguments (the member's old value)
            for j in range(k - 1, max(k - 24, -1), -1):
                a, t = body[j]
                if CALL.match(t) or t.startswith(("ret", "j")):
                    break
                if t.startswith("push "):
                    npush += 1
                    if npush == 2:      # arguments are pushed last-to-first: section is the nearest push, key the next
                        mi = PUSHI.match(t)
                        if mi and int(mi.group(1), 16) >= 0x800000:
                            s_ = img.cstr(int(mi.group(1), 16))
                            if s_ and KEYRE.fullmatch(s_):
                                key = s_
                m = PUSHM.match(t) or FLD.match(t)
                if m and m.group(1) == this:
                    argoff.append(int(m.group(2) or "0", 16))
                m = LEA.match(t)
                if m and m.group(2) == this and m.group(1) in ("eax", "ecx", "edx") and lea_before is None:
                    lea_before = int(m.group(3) or "0", 16)
                m = LOAD.match(t)
                if m and m.group(3) == this:
                    argoff.append(int(m.group(4) or "0", 16))
            if key is None:
                continue
            nxt = calls[calls.index(k) + 1] if calls.index(k) + 1 < len(calls) else min(len(body), k + 60)
            store = None
            for j in range(k + 1, min(nxt, k + 60)):
                a, t = body[j]
                m = STORE.match(t)
                if m and m.group(2) == this:
                    off, w, how = int(m.group(3) or "0", 16), {"BYTE": 1, "WORD": 2, "DWORD": 4}[m.group(1)], "store"
                else:
                    m = FSTP.match(t)
                    if not (m and m.group(2) == this):
                        if t.startswith("ret"):
                            break
                        continue
                    off, w, how = int(m.group(3) or "0", 16), 8 if m.group(1) == "QWORD" else 4, "fstp"
                if argoff:
                    if off in argoff:
                        store = (off, w, how)
                        break
                else:
                    if j - k <= 12 and not near_call(body, k, j):
                        store = (off, w, how)
                    break
            lea = lea_before if kind == "ReadString" else None
            if store is None and lea is None:
                for j in range(k + 1, min(nxt, k + 40)):
                    m = LEA.match(body[j][1])
                    if m and m.group(2) == this and m.group(1) in ("eax", "ecx", "edx"):
                        lea = int(m.group(3) or "0", 16)
                        break
            rec = dict(func="0x%X" % f0, call="0x%X" % body[k][0], reader="0x%X" % tgt, kind=kind, key=key,
                       store=("0x%X" % store[0]) if store else None, width=store[1] if store else None, how=store[2] if store else None,
                       args=sorted({"0x%X" % o for o in argoff}), declared=sorted(width and [width] or []))
            rec["lea"] = ("0x%X" % lea) if lea is not None else None
            rec["near"] = bool(store and not argoff)
            rec["sym"] = row["sym"] if row else None
            rec["status"] = row["status"] if row else None
            rec["owner"] = owner_of(row["sym"]) if row else None
            rec["holders"] = {h: s for h, s in hs.items()}
            recs.append(rec)
    return recs



# ------------------------------------------------------------------ header side
PLACEHOLDER = re.compile(r"^(?:unknown\w*|unk\w*|field_\w+|DAT_\w+|FUN_\w+|vf_\w+|Unknown\w*)$")


def placeholder(name, off):
    """unknown_XX style, or any `<word>_<hex offset>` name (Flag_A4, Ptr_D0, Smoke_BB0) whose suffix is the member's offset"""
    if PLACEHOLDER.match(name):
        return True
    m = re.match(r"^[A-Za-z]+_0*([0-9A-Fa-f]+)$", name)
    return bool(m and int(m.group(1), 16) == off)
BLOCK = re.compile(r"^(?:align_\w+|_?pad\w*|_?filler\w*|bools_\w+|reserved\w*|gap_\w+)$")
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
MEMBER = re.compile(r"^\s*(?P<type>[A-Za-z_][\w:<>,\s\*&]*?)[\s\*&]+(?P<name>[A-Za-z_]\w*)\s*(?P<arr>(?:\[[^\]]*\]\s*)*);\s*(?://\s*\+0x(?P<off>[0-9A-Fa-f]+))?")
CLASS_RE = re.compile(r"^\s*(?:class|struct)\s+(?:__declspec\([^)]*\)\s*)?(\w+)\s*(?::\s*([^{;]*))?\{", re.M)
ASSERT_RE = re.compile(r"GG_STATIC_ASSERT\s*\(\s*offsetof\s*\(\s*(\w+)\s*,\s*(\w+)\s*\)\s*==\s*(0x[0-9A-Fa-f]+|\d+)\s*\)")
SIZES = {"bool": 1, "char": 1, "unsigned char": 1, "BYTE": 1, "short": 2, "unsigned short": 2, "int": 4, "unsigned int": 4,
         "long": 4, "unsigned long": 4, "float": 4, "double": 8, "DWORD": 4, "WORD": 2}


def ctype_size(t, arr):
    t = " ".join(t.replace("const", "").replace("volatile", "").split())
    if arr:
        return None
    if "*" in t:
        return 4
    return SIZES.get(t)


def header_classes(tree):
    """class -> [dict(file, line, bases, members={name: dict(off, type, line, size)}, end)] over match/**/*.h"""
    out = collections.defaultdict(list)
    root = os.path.join(tree, "match")
    for dp, _, fs in os.walk(root):
        for f in fs:
            if not f.endswith(".h"):
                continue
            p = os.path.join(dp, f)
            text = open(p, errors="replace").read()
            lines = text.split("\n")
            asserts = {}
            for m in ASSERT_RE.finditer(text):
                asserts[(m.group(1), m.group(2))] = int(m.group(3), 0)
            for m in CLASS_RE.finditer(text):
                name = m.group(1)
                l0 = text.count("\n", 0, m.start())
                # brace match from the opening brace on comment-stripped text
                stripped = re.sub(r"//[^\n]*", lambda x: " " * len(x.group(0)), text)
                depth, i = 1, m.end()
                while i < len(stripped) and depth:
                    depth += (stripped[i] == "{") - (stripped[i] == "}")
                    i += 1
                l1 = text.count("\n", 0, i)
                mem, d = {}, 0
                for ln in range(l0 + 1, l1):
                    raw = lines[ln]
                    code = re.sub(r"//.*", "", raw)
                    mm = MEMBER.match(raw) if "(" not in code else None
                    if mm and not re.match(r"\s*(typedef|static|friend|enum|using|return|class|struct|union)\b", raw) and code.rstrip().endswith(";"):
                        nm = mm.group("name")
                        off = int(mm.group("off"), 16) if mm.group("off") else asserts.get((name, nm))
                        if off is not None:
                            mem[nm] = dict(off=off, type=" ".join(mm.group("type").split()), line=ln + 1, arr=bool(mm.group("arr")),
                                           size=ctype_size(mm.group("type"), mm.group("arr")), file=os.path.relpath(p, tree))
                methods = set(re.findall(r"\b([A-Za-z_]\w*)\s*\(", re.sub(r"//[^\n]*", "", "\n".join(lines[l0 + 1:l1]))))
                bases = [re.sub(r"^(public|private|protected)\s+", "", b.strip()) for b in (m.group(2) or "").split(",") if b.strip()]
                out[name].append(dict(file=os.path.relpath(p, tree), line=l0 + 1, end=l1, bases=[b.split("<")[0] for b in bases], members=mem, methods=methods))
    return out


def declaring(hs, chain):
    common = None
    for h in hs:
        ch = [short(x) for x in chain.get(h, [h])]
        common = ch if common is None else [x for x in common if x in ch]
    return common[0] if common else None


def class_of(rec, chain, forced):
    if rec["func"] in forced:
        return forced[rec["func"]]
    if rec["holders"]:
        return declaring(list(rec["holders"]), chain)
    o = rec["owner"]
    if o and not re.search(r"View|_[0-9A-Fa-f]{6,8}$", o):
        return o
    return None


FORCED = {"0x6691E0": "RulesClass", "0x66CF70": "RulesClass"}


def lookup(classes, chain, cls, off):
    """find the header member at `off` walking cls and its bases (RTTI chain order, most derived first)"""
    names = [short(x) for x in chain.get(cls, [cls])] if cls in chain or any(short(k) == cls for k in chain) else [cls]
    if cls not in names:
        names = [cls] + names
    for n in names:
        for d in classes.get(n, []):
            for nm, mem in d["members"].items():
                if mem["off"] == off:
                    return n, d, nm, mem
    return None


def build_plan(tree, recs, chain):
    classes = header_classes(tree)
    byclass = collections.defaultdict(lambda: collections.defaultdict(list))   # (cls) -> off -> [rec]
    unattributed = collections.Counter()
    for r in recs:
        cls = class_of(r, chain, FORCED)
        if not cls:
            unattributed[r["func"]] += 1
            continue
        off = r["store"] or r["args"][0] if (r["store"] or len(r["args"]) == 1) else None
        strength = "store" if r["store"] else ("arg" if len(r["args"]) == 1 and r["kind"].startswith(("Write", "ReadString", "ReadInteger", "ReadBool", "ReadDouble")) else None)
        if r["lea"] and not strength:
            off, strength = r["lea"], "lea"
        if off is None or strength is None:
            continue
        r = dict(r, cls=cls, off=int(off, 16), strength=strength)
        byclass[cls][r["off"]].append(r)
    plan = dict(renames=[], conflicts=[], agree=[], blocks=[], missing=[], ambiguous=[], unattributed=dict(unattributed))
    for cls, offs in sorted(byclass.items()):
        for off, rs in sorted(offs.items()):
            keys = sorted({x["key"] for x in rs})
            hit = lookup(classes, chain, cls, off)
            base = dict(cls=cls, off="0x%X" % off, keys=keys, funcs=sorted({x["func"] for x in rs}), kinds=sorted({x["kind"] for x in rs}),
                        strength=sorted({x["strength"] for x in rs}), near=any(x["near"] for x in rs),
                        widths=sorted({x["width"] for x in rs if x["width"]}))
            if not hit:
                plan["missing"].append(base)
                continue
            owner, d, nm, mem = hit
            base.update(owner=owner, member=nm, file=mem["file"], line=mem["line"], htype=mem["type"], hsize=mem["size"])
            if len(keys) != 1 or not IDENT.match(keys[0]):
                plan["ambiguous"].append(base)
            elif nm == keys[0]:
                plan["agree"].append(base)
            elif BLOCK.match(nm) or mem["arr"]:
                plan["blocks"].append(base)
            elif placeholder(nm, off):
                base["new"] = keys[0]
                plan["renames"].append(base)
            elif BLOCK.match(nm) or mem["arr"]:
                plan["blocks"].append(base)
            else:
                plan["conflicts"].append(base)
    # eligibility: the evidence must be strong and the new name free
    perclass = collections.defaultdict(collections.Counter)
    for r in plan["renames"]:
        perclass[r["cls"]][r["new"]] += 1
    for r in plan["renames"]:
        why = []
        st = set(r["strength"])
        if "store" not in st:
            why.append("no store evidence (%s)" % "/".join(sorted(st)))
        elif r["near"] and "arg" not in st:
            why.append("store found only by proximity (no argument/writer corroboration)")
        if perclass[r["cls"]][r["new"]] > 1:
            why.append("key %s names more than one offset in %s" % (r["new"], r["cls"]))
        used, meth = set(), set()
        for n in [r["owner"]] + [short(x) for x in chain.get(r["owner"], [])]:
            for d in classes.get(n, []):
                used |= set(d["members"])
                meth |= d["methods"]
        if r["new"] in used:
            why.append("name already a member in the class chain")
        if r["new"] in meth:
            why.append("name is a method of the class chain")
        if r["hsize"] and r["widths"] and r["hsize"] != r["widths"][0] and r["kinds"][0] != "ReadString":
            r["type_note"] = "header type %s is %d bytes, reader stores %d" % (r["htype"], r["hsize"], r["widths"][0])
        elif r["kinds"][0] == "ReadDouble" and r["htype"] in ("int", "unsigned int", "long", "unsigned long"):
            r["type_note"] = "header type %s, reader stores a %s" % (r["htype"], "double" if r["widths"][:1] == [8] else "float")
        r["eligible"] = not why
        r["why_not"] = why
    return plan


# ------------------------------------------------------------------ apply
ERR = re.compile(r"([^\s(][^()]*)\((\d+)\)\s*:\s*(?:fatal\s+)?error\s+(C\d+)\s*:\s*(.*)")
CODE_LINE = re.compile(r"^(?P<code>[^\n]*?)(?P<cmt>//.*)?$")


def code_part(line):
    """(code, comment) of a source line; a // inside a string literal is left in the code part"""
    instr, i = False, 0
    while i < len(line):
        c = line[i]
        if instr:
            if c == "\\":
                i += 1
            elif c == '"':
                instr = False
        elif c == '"':
            instr = True
        elif line.startswith("//", i):
            return line[:i], line[i:]
        i += 1
    return line, ""


def tok(name):
    return re.compile(r"(?<![\w])%s(?![\w])" % re.escape(name))


def derived_of(chain, owner):
    return {short(c) for c, ch in chain.items() if owner in [short(x) for x in ch]} | {owner}


def candidate_edits(tree, files, rn, derived):
    """[(rel, lineno0, newline)] replacing rn['member'] -> rn['new'] where it can be a use of the owner's member."""
    import cppscan
    old, new, owner = rn["member"], rn["new"], rn["owner"]
    pat_old = tok(old)
    out = {}
    for rel, lines in files.items():
        text = "\n".join(lines)
        if old not in text:
            continue
        # regions where a bare use denotes the owner's member: methods of owner/derived, and the class bodies in headers
        bare = set()
        if rel.endswith((".cpp", ".c", ".inl", ".h")):
            for header, body, l0, l1 in cppscan.function_bodies(text):
                m = re.findall(r"(\w+)\s*::\s*~?\w+\s*$", header.split("(")[0].strip())
                if m and m[-1] in derived:
                    bare.update(range(l0 - 1, l1))
            for m in CLASS_RE.finditer(text):
                if m.group(1) in derived:
                    stripped = cppscan.strip_code(text)
                    depth, i = 1, m.end()
                    while i < len(stripped) and depth:
                        depth += (stripped[i] == "{") - (stripped[i] == "}")
                        i += 1
                    bare.update(range(text.count("\n", 0, m.start()), text.count("\n", 0, i)))
        for k, ln in enumerate(lines):
            code, cmt = code_part(ln)
            if not pat_old.search(code):
                continue
            ctor_init = bool(re.match(r"^\s*[:,]?\s*%s\s*\(" % re.escape(old), code)) and any(("%s::%s" % (d, d)) in text for d in derived) \
                and code.rstrip().endswith((",", ")"))

            def sub(m):
                before = code[:m.start()].rstrip()
                if ctor_init and (not before or before in (",", ":")):
                    return new
                if before.endswith(("->", ".")):
                    return new
                if before.endswith("::"):
                    q = re.search(r"(\w+)\s*::$", before)
                    return new if q and q.group(1) in derived else m.group(0)
                if re.search(r"offsetof\s*\(\s*(\w+)\s*,\s*$", before):
                    q = re.search(r"offsetof\s*\(\s*(\w+)\s*,\s*$", before)
                    return new if q.group(1) in derived else m.group(0)
                if k in bare and not re.search(r"[\w\*&>\]]\s*$", before):    # bare statement-level use, not a declaration
                    return new
                if k in bare and re.search(r"[\(,=!<>+\-*/%&|^?:\[]\s*$", before):
                    return new
                return m.group(0)
            nc = pat_old.sub(sub, code)
            if nc != code:
                out.setdefault(rel, []).append((k, nc + cmt))
    return out


def load_files(tree):
    files = {}
    for dp, _, fs in os.walk(os.path.join(tree, "match")):
        for f in fs:
            if f.lower().endswith((".cpp", ".h", ".inl", ".c")):
                p = os.path.join(dp, f)
                files[os.path.relpath(p, tree).replace(os.sep, "/")] = open(p, errors="replace", newline="").read().split("\n")
    return files


def compile_tu(tree, tu, tmp, n):
    obj = os.path.join(tmp, "%d_%s.obj" % (n, os.path.basename(tu)))
    with open(obj + ".log", "w+", errors="replace") as log:
        proc = subprocess.run(["bash", os.path.join(tree, "scripts/vc6/vc6cl.sh"), "/Fo" + obj, os.path.basename(tu)],
                              cwd=os.path.join(tree, os.path.dirname(tu)), stdin=subprocess.DEVNULL, stdout=log, stderr=subprocess.STDOUT)
        log.seek(0)
        out = log.read()
    return proc.returncode == 0 and os.path.isfile(obj), out


def compile_set(tree, tus, jobs=4):
    import concurrent.futures
    import tempfile
    res = {}
    with tempfile.TemporaryDirectory(prefix="inif_") as tmp, concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as pool:
        futs = {pool.submit(compile_tu, tree, tu, tmp, n): tu for n, tu in enumerate(tus)}
        for f, tu in futs.items():
            res[tu] = f.result()
    return res


def resolve_path(tree, files, raw):
    parts = re.split(r"[\\/]", raw.strip())
    if "match" in parts:
        rel = "/".join(parts[len(parts) - 1 - parts[::-1].index("match"):])
        if rel in files:
            return rel
    base = parts[-1]
    c = [r for r in files if r.endswith("/" + base) and "/".join(parts[-2:]) in r]
    c = c or [r for r in files if r.endswith("/" + base)]
    return c[0] if len(c) >= 1 else None


def apply_plan(tree, plan, chain, only, dry=False, jobs=4, log=print):
    sys.path.insert(0, os.path.join(tree, "scripts/vc6"))
    import changed_tus  # noqa: E402
    import compile_all  # noqa: E402
    rns = [r for r in plan["renames"] if r["eligible"] and r["cls"] in only]
    files = load_files(tree)
    edits = {}      # (rel, k, rename index) -> original line pieces, recorded for reverts
    applied = collections.defaultdict(list)     # rel -> [(k, rn index)]
    orig = {rel: list(l) for rel, l in files.items()}
    # 1. the declaration in the owner's header and every candidate use
    for i, rn in enumerate(rns):
        derived = derived_of(chain, rn["owner"])
        fl = files[rn["file"]]
        k = rn["line"] - 1
        code, cmt = code_part(fl[k])
        if not tok(rn["member"]).search(code):
            raise SystemExit("declaration of %s not on %s:%d" % (rn["member"], rn["file"], rn["line"]))
        fl[k] = tok(rn["member"]).sub(rn["new"], code, count=1) + cmt
        applied[rn["file"]].append((k, i))
        cand = candidate_edits(tree, files, rn, derived)
        for rel, lst in cand.items():
            for k, nl in lst:
                if rel == rn["file"] and k == rn["line"] - 1:
                    continue
                files[rel][k] = nl
                applied[rel].append((k, i))
        log("  %s::%s -> %s: %d use lines in %d files" % (rn["owner"], rn["member"], rn["new"], sum(len(v) for v in cand.values()), len(cand)))
    changed = sorted({rel for rel in files if files[rel] != orig[rel]})
    if dry:
        log("dry run: %d files would change" % len(changed))
        return rns, changed, {}
    write = lambda rel: open(os.path.join(tree, rel), "w", newline="").write("\n".join(files[rel]))
    for rel in changed:
        write(rel)
    # 2. compile; revert the uses that belong to some other class
    reverted = collections.defaultdict(list)
    tus_all = compile_all.list_tus(tree)
    hdrs = compile_all.list_headers(tree)
    keep = changed_tus.select_changed(tree, tus_all + hdrs, "HEAD")
    todo = [t for t in tus_all if t in keep and not t.lower().endswith(".asm")]
    log("compiling %d affected TUs" % len(todo))
    for rnd in range(1, 14):
        res = compile_set(tree, todo, jobs)
        bad = {tu: out for tu, (ok, out) in res.items() if not ok}
        if not bad:
            log("round %d: all %d TUs compile" % (rnd, len(todo)))
            break
        touched, unexplained = set(), []
        newnames = {r["new"]: i for i, r in enumerate(rns)}
        for tu, out in bad.items():
            for m in ERR.finditer(out):
                raw, ln, code, msg = m.groups()
                rel = resolve_path(tree, files, raw)
                if not rel:
                    unexplained.append((tu, raw, ln, msg))
                    continue
                k = int(ln) - 1
                names = [n for n in newnames if "'%s'" % n in msg]
                fixed = False
                # an unrenamed use the scanner could not classify (constructor initialiser lists): rename it forward
                for i_, rn_ in enumerate(rns):
                    if "'%s'" % rn_["member"] in msg and not names:
                        for kk in range(max(k - 1, 0), min(k + 2, len(files[rel]))):
                            c_, m_ = code_part(files[rel][kk])
                            if tok(rn_["member"]).search(c_):
                                files[rel][kk] = tok(rn_["member"]).sub(rn_["new"], c_) + m_
                                applied[rel].append((kk, i_))
                                touched.add(rel)
                                fixed = True
                if fixed:
                    continue
                for kk in range(max(k - 3, 0), min(k + 4, len(files[rel]))):
                    code_, cmt_ = code_part(files[rel][kk])
                    for n in (names or list(newnames)):
                        if not names and kk != k:
                            continue
                        if tok(n).search(code_) and (rel, kk) in {(r_, k_) for r_, l_ in applied.items() for k_, i_ in l_ if i_ == newnames[n]}:
                            rn = rns[newnames[n]]
                            if rel == rn["file"] and kk == rn["line"] - 1:
                                continue
                            files[rel][kk] = tok(n).sub(rn["member"], code_) + cmt_
                            reverted[rn["member"]].append((rel, kk + 1))
                            touched.add(rel)
                            fixed = True
                if not fixed:
                    unexplained.append((tu, rel, ln, msg))
        for rel in touched:
            write(rel)
        log("round %d: %d TUs failed, reverted lines in %d files, %d unexplained" % (rnd, len(bad), len(touched), len(unexplained)))
        if unexplained and not touched:
            for u in unexplained[:10]:
                log("  UNEXPLAINED %s" % (u,))
            raise SystemExit("compile errors not caused by a renamed use")
        todo = sorted(bad)
        if not todo:
            break
    else:
        raise SystemExit("did not converge")
    # final full pass over the affected set (reverts may have changed headers)
    changed = sorted({rel for rel in files if files[rel] != orig[rel]})
    return rns, changed, reverted

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    e = sub.add_parser("extract")
    e.add_argument("--out")
    e.add_argument("--repo", default=os.environ.get("GAG_WORKTREE") or REPO)
    pl = sub.add_parser("plan")
    pl.add_argument("--tree", default=os.environ.get("GAG_WORKTREE") or REPO)
    pl.add_argument("--evidence")
    pl.add_argument("--json")
    ap2 = sub.add_parser("apply")
    ap2.add_argument("--tree", default=os.environ.get("GAG_WORKTREE") or REPO)
    ap2.add_argument("--plan", required=True)
    ap2.add_argument("--class", dest="classes", action="append", required=True, help="owner classes to rename (one family per packet)")
    ap2.add_argument("--dry-run", action="store_true")
    ap2.add_argument("--jobs", type=int, default=4)
    a = ap.parse_args(argv)
    exe = os.environ.get("GAMEMD_BINARY") or sys.exit("set GAMEMD_BINARY")
    if a.cmd == "extract":
        recs = extract(exe, a.repo)
        print("%d INI sites in %d functions" % (len(recs), len({r["func"] for r in recs})))
        if a.out:
            json.dump(recs, open(a.out, "w"), indent=1)
    if a.cmd == "plan":
        recs = json.load(open(a.evidence)) if a.evidence else extract(exe, a.tree)
        rtti = json.load(open(os.path.join(a.tree, "scripts/data/rtti_classes.json")))["classes"]
        chain = {c["demangled_name"]: c.get("base_chain") or [c["demangled_name"]] for c in rtti.values() if c.get("demangled_name")}
        plan = build_plan(a.tree, recs, chain)
        for k, v in plan.items():
            print("%-13s %d" % (k, len(v)))
        if a.json:
            json.dump(plan, open(a.json, "w"), indent=1)
    if a.cmd == "apply":
        plan = json.load(open(a.plan))
        rtti = json.load(open(os.path.join(a.tree, "scripts/data/rtti_classes.json")))["classes"]
        chain = {c["demangled_name"]: c.get("base_chain") or [c["demangled_name"]] for c in rtti.values() if c.get("demangled_name")}
        rns, changed, reverted = apply_plan(a.tree, plan, chain, set(a.classes), a.dry_run, a.jobs)
        print("%d renames, %d files changed, %d use lines left alone (other classes)" % (len(rns), len(changed), sum(len(v) for v in reverted.values())))
        for f in changed:
            print("  " + f)
    return 0


if __name__ == "__main__":
    sys.exit(main())

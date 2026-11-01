#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original. Reads developer-supplied PE images; stores no retail bytes.
"""x86scan: a dependency-free 32-bit x86 length decoder, PE image reader and CFG walker.

Shared by twinpair.py and extent_recall.py. It is deliberately small: it knows the instruction
lengths, the control-flow kind and which 32-bit fields are addresses, which is all that function
discovery, relocation masking and call-graph pairing need. It does not produce mnemonics.

  Image(path)            sections, reads, text range, SHA-256 (no pin: the caller decides)
  decode(buf, off, va)   (n, kind, target, fields, op, pre, tbl) or None for an invalid encoding
  walk(img, entry, ...)  CFG-closed walk from an entry: instructions, calls, tail jumps, tables
  rtti_vtables(img)      MSVC RTTI vtables: {(class, col_offset): [slot targets]}
  data_code_pointers(img) aligned dwords in the data sections that point into .text

Jump-table rule. `jmp [reg*4+T]` reads dwords at T while they point into .text; the count is taken
from the nearest preceding `cmp reg, N` in the same straight-line run (N+1 entries) and from a
byte index table (`mov r8,[reg+B]`) when one feeds the jump (max byte + 1 entries). Without a
bound the read stops at the first dword that is not a code pointer.
"""
import hashlib
import struct
from array import array
from pathlib import Path

# control-flow kinds
OTHER, RET, JMP, JCC, CALL, JMPIND, CALLIND, INT3, HALT = range(9)
KIND_NAME = ("other", "ret", "jmp", "jcc", "call", "jmpind", "callind", "int3", "halt")

# field roles
REL, IMM, DISP = "rel", "imm", "disp"

# opcode flag bits
M, I8, IZ, I16, R8, R32, MOFFS = 1, 2, 4, 8, 16, 32, 64

PREFIXES = frozenset((0x26, 0x2E, 0x36, 0x3E, 0x64, 0x65, 0x66, 0x67, 0xF0, 0xF2, 0xF3))


def _build_one():
    t = [0] * 256
    for op in range(0x40):
        lo = op & 7
        if op in PREFIXES or op == 0x0F:
            continue
        if lo < 4:
            t[op] = M
        elif lo == 4:
            t[op] = I8
        elif lo == 5:
            t[op] = IZ
    for op in (0x62, 0x63, 0xC4, 0xC5, 0xD0, 0xD1, 0xD2, 0xD3, 0xFE, 0xFF, 0xF6, 0xF7):
        t[op] = M
    for op in range(0x84, 0x90):
        t[op] = M
    for op in range(0xD8, 0xE0):
        t[op] = M
    t[0x68] = IZ
    t[0x69] = M | IZ
    t[0x6A] = I8
    t[0x6B] = M | I8
    for op in range(0x70, 0x80):
        t[op] = R8
    t[0x80] = t[0x82] = t[0x83] = M | I8
    t[0x81] = M | IZ
    for op in range(0xA0, 0xA4):
        t[op] = MOFFS
    t[0xA8] = I8
    t[0xA9] = IZ
    for op in range(0xB0, 0xB8):
        t[op] = I8
    for op in range(0xB8, 0xC0):
        t[op] = IZ
    t[0xC0] = t[0xC1] = M | I8
    t[0xC2] = I16
    t[0xC6] = M | I8
    t[0xC7] = M | IZ
    t[0xC8] = I16 | I8
    t[0xCA] = I16
    t[0xCD] = I8
    t[0xD4] = t[0xD5] = I8
    for op in (0xE0, 0xE1, 0xE2, 0xE3, 0xEB):
        t[op] = R8
    for op in (0xE4, 0xE5, 0xE6, 0xE7):
        t[op] = I8
    t[0xE8] = t[0xE9] = R32
    return t


def _build_two():
    t = [M] * 256
    for op in (0x05, 0x06, 0x07, 0x08, 0x09, 0x0B, 0x0E, 0x77, 0xA0, 0xA1, 0xA2, 0xA8, 0xA9, 0xAA):
        t[op] = 0
    for op in range(0x30, 0x38):
        t[op] = 0
    for op in range(0xC8, 0xD0):
        t[op] = 0
    for op in range(0x80, 0x90):
        t[op] = R32
    for op in (0x70, 0x71, 0x72, 0x73, 0xA4, 0xAC, 0xBA, 0xC2, 0xC4, 0xC5, 0xC6, 0x0F, 0x3A):
        t[op] = M | I8
    return t


ONE = _build_one()
TWO = _build_two()
# opcodes that VC6 never emits for code and that mean "this is data" when a walk meets them
SUSPICIOUS = frozenset((0x6C, 0x6D, 0x6E, 0x6F, 0xE4, 0xE5, 0xE6, 0xE7, 0xEC, 0xED, 0xEE, 0xEF, 0xCE, 0xCF,
                        0xF4, 0x9A, 0xEA, 0xC4, 0xC5, 0x62, 0x63, 0x27, 0x2F, 0x37, 0x3F, 0xD6, 0xF1, 0xCA,
                        0xCB, 0x60, 0x61, 0x9B, 0xD4, 0xD5, 0xD7, 0x06, 0x07, 0x0E, 0x16, 0x17, 0x1E, 0x1F))
INVALID = frozenset((0x9A, 0xEA))


def decode(b, o, va):
    """Decode one instruction at b[o]. Returns (n, kind, target, fields, op, pre, tbl) or None.

    fields: tuple of (offset_in_insn, role) for each 32-bit address-like field (rel/imm/disp).
    op: the opcode byte (0x0F00|byte for two-byte opcodes). pre: prefix byte count.
    tbl: the disp32 of a `jmp [reg*4+disp32]` (jump table) else None.
    """
    try:
        s = o
        opsz16 = False
        while b[o] in PREFIXES:
            if b[o] == 0x66:
                opsz16 = True
            o += 1
            if o - s > 4:
                return None
        pre = o - s
        c = b[o]
        o += 1
        if c == 0x0F:
            c2 = b[o]
            o += 1
            fl = TWO[c2]
            if c2 == 0x38:
                fl = M
            opv = 0x0F00 | c2
        else:
            fl = ONE[c]
            opv = c
        if opv in INVALID:
            return None
        fields = []
        tbl = None
        modrm = None
        if fl & M:
            modrm = b[o]
            o += 1
            mod, rm = modrm >> 6, modrm & 7
            if mod != 3:
                base_is_disp = False
                if rm == 4:
                    sib = b[o]
                    o += 1
                    if mod == 0 and (sib & 7) == 5:
                        base_is_disp = True
                        if (sib >> 6) == 2 and (sib >> 3) & 7 != 4 and opv == 0xFF and ((modrm >> 3) & 7) == 4:
                            tbl = struct.unpack_from("<I", b, o)[0]
                elif mod == 0 and rm == 5:
                    base_is_disp = True
                if base_is_disp or mod == 2:
                    fields.append((o - s, DISP))
                    o += 4
                elif mod == 1:
                    o += 1
            if opv in (0xF6, 0xF7) and ((modrm >> 3) & 7) < 2:
                fl |= I8 if opv == 0xF6 else IZ
        if fl & MOFFS:
            fields.append((o - s, DISP))
            o += 4
        if fl & I8:
            o += 1
        if fl & IZ:
            if opsz16:
                o += 2
            else:
                fields.append((o - s, IMM))
                o += 4
        if fl & I16:
            o += 2
        if opv == 0x0F3A:
            o += 1
        target = None
        kind = OTHER
        if fl & R8:
            rel = b[o] - 256 if b[o] >= 128 else b[o]
            o += 1
            target = (va + (o - s) + rel) & 0xFFFFFFFF
            kind = JMP if opv == 0xEB else JCC
        elif fl & R32:
            rel = struct.unpack_from("<i", b, o)[0]
            fields.append((o - s, REL))
            o += 4
            target = (va + (o - s) + rel) & 0xFFFFFFFF
            if opv == 0xE8:
                kind = CALL
            elif opv == 0xE9:
                kind = JMP
            else:
                kind = JCC
        elif opv in (0xC3, 0xC2, 0xCA, 0xCB):
            kind = RET
        elif opv == 0xCC:
            kind = INT3
        elif opv in (0xF4, 0x0F0B):
            kind = HALT
        elif opv == 0xFF:
            r = (modrm >> 3) & 7
            if r in (2, 3):
                kind = CALLIND
            elif r in (4, 5):
                kind = JMPIND
        if o > len(b):
            return None
        return (o - s, kind, target, tuple(fields), opv, pre, tbl)
    except (IndexError, struct.error):
        return None


class Image:
    """A 32-bit PE image: sections, reads by VA, text range. Does not pin a hash."""

    def __init__(self, path=None, data=None):
        self.path = str(path) if path else ""
        self.data = data if data is not None else Path(path).read_bytes()
        self._blobs = None
        self.sha256 = hashlib.sha256(self.data).hexdigest()
        d = self.data
        pe = struct.unpack_from("<I", d, 0x3C)[0]
        nsec = struct.unpack_from("<H", d, pe + 6)[0]
        opt = struct.unpack_from("<H", d, pe + 20)[0]
        self.base = struct.unpack_from("<I", d, pe + 24 + 28)[0]
        self.entry = self.base + struct.unpack_from("<I", d, pe + 24 + 16)[0]
        self.sections = []
        for i in range(nsec):
            name, vsize, va, rsize, roff = struct.unpack_from("<8sIIII", d, pe + 24 + opt + 40 * i)
            self.sections.append((name.rstrip(b"\0").decode("latin-1"), self.base + va, vsize, roff, rsize))
        self.end = max(s[1] + max(s[2], s[4]) for s in self.sections)
        t = self.section(".text")
        self.text_lo, self.text_hi = t[1], t[1] + min(t[2], t[4])
        self._text = d[t[3]: t[3] + min(t[2], t[4])]

    @classmethod
    def from_sections(cls, base, sections, entry=0):
        """Synthetic image for tests: sections = [(name, va, bytes)]."""
        img = object.__new__(cls)
        img.path = ""
        img.data = b""
        img.sha256 = ""
        img.base = base
        img.entry = entry
        img.sections = []
        img._blobs = {}
        for name, va, blob in sections:
            img.sections.append((name, va, len(blob), 0, len(blob)))
            img._blobs[name] = bytes(blob)
        img.end = max(s[1] + s[2] for s in img.sections)
        t = img.section(".text")
        img.text_lo, img.text_hi = t[1], t[1] + t[2]
        img._text = img._blobs[".text"]
        return img

    def section(self, name):
        for s in self.sections:
            if s[0] == name:
                return s
        raise KeyError(name)

    def has_section(self, name):
        return any(s[0] == name for s in self.sections)

    def sect_bytes(self, name):
        s = self.section(name)
        if self._blobs is not None:
            return s[1], self._blobs[name]
        return s[1], self.data[s[3]: s[3] + min(s[2], s[4])]

    def read(self, va, n):
        for name, start, vsize, _, rsize in self.sections:
            if start <= va and va + n <= start + min(vsize, rsize):
                blob = self.sect_bytes(name)[1]
                return blob[va - start: va - start + n]
        return None

    def u32(self, va):
        b = self.read(va, 4)
        return struct.unpack("<I", b)[0] if b else None

    def in_text(self, va):
        return self.text_lo <= va < self.text_hi

    def in_image(self, va):
        return self.base <= va < self.end

    def cstring(self, va, minlen=4, maxlen=200):
        """Printable ASCII NUL-terminated string at va (outside .text) or None."""
        if self.in_text(va) or not self.in_image(va):
            return None
        for name, start, vsize, _, rsize in self.sections:
            if start <= va < start + min(vsize, rsize):
                blob = self.sect_bytes(name)[1]
                o = va - start
                e = blob.find(b"\0", o, o + maxlen + 1)
                if e < 0 or e - o < minlen:
                    return None
                s = blob[o:e]
                if all(32 <= c < 127 or c in (9, 10, 13) for c in s):
                    return s.decode("latin-1")
                return None
        return None

    def padding_before(self, va):
        """True when va is 4-aligned and the byte before it is CC/90 padding (a function-boundary signature)."""
        o = va - self.text_lo
        return va & 3 == 0 and 0 < o <= len(self._text) and self._text[o - 1] in (0xCC, 0x90)


class Walk:
    __slots__ = ("entry", "insns", "calls", "tail", "ptrs", "refs", "tables", "suspicious", "bad", "end", "out_of_text")

    def __init__(self, entry):
        self.entry = entry
        self.insns = {}       # va -> decode tuple
        self.calls = []       # (site, target) direct calls
        self.tail = []        # (site, target) jumps that leave the function
        self.ptrs = []        # (site, value, op) code pointers stored via imm into .text
        self.refs = []        # (site, value) image addresses outside .text referenced by imm/disp
        self.tables = []      # (table_va, targets, byte_table_va or None, byte_count)
        self.suspicious = 0
        self.bad = []         # va of undecodable bytes reached
        self.end = entry
        self.out_of_text = []


def _cmp_bound(img, site, pre):
    """cmp reg, imm at site -> imm (0 <= imm < 4096), else None."""
    off = site - img.text_lo + pre
    t = img._text
    op = t[off]
    if op == 0x83 and (t[off + 1] >> 3) & 7 == 7 and t[off + 1] >> 6 == 3:
        v = t[off + 2]
        return v if v < 128 else None
    if op == 0x81 and (t[off + 1] >> 3) & 7 == 7 and t[off + 1] >> 6 == 3:
        v = struct.unpack_from("<I", t, off + 2)[0]
        return v if v < 4096 else None
    if op == 0x3C:
        return t[off + 1]
    if op == 0x3D:
        v = struct.unpack_from("<I", t, off + 1)[0]
        return v if v < 4096 else None
    return None


def _read_table(img, tva, count, limit=4096):
    """Read up to `count` (or greedily) code pointers at tva."""
    out = []
    while len(out) < (count if count is not None else limit):
        v = img.u32(tva + 4 * len(out))
        if v is None or not img.in_text(v):
            break
        out.append(v)
    return out


def walk(img, entry, starts=(), max_insns=60000):
    """CFG-closed walk from `entry`. `starts` are other known function entries (tail-jump targets).

    A jump is followed unless it leaves the function: it targets another known start, lies before
    the entry, or is a forward unconditional jump of more than 0x20 bytes to padding-aligned code (a
    tail call). Calls are recorded, not followed. Jump tables are read and their targets followed.
    """
    w = Walk(entry)
    text, tlo, thi = img._text, img.text_lo, img.text_hi
    stack = [entry]
    ins = w.insns
    while stack:
        a = stack.pop()
        recent = []                  # (site, n, pre, op) of the current straight-line run
        while True:
            if a in ins:
                break
            if not (tlo <= a < thi):
                w.out_of_text.append(a)
                break
            r = decode(text, a - tlo, a)
            if r is None:
                w.bad.append(a)
                break
            ins[a] = r
            n, kind, tgt, fields, op, pre, tbl = r
            if len(ins) > max_insns:
                w.bad.append(a)
                return w
            if op in SUSPICIOUS:
                w.suspicious += 1
            for off, role in fields:
                if role == REL:
                    continue
                v = struct.unpack_from("<I", text, a - tlo + off)[0]
                if tlo <= v < thi:
                    if role == IMM and (op == 0x68 or 0xB8 <= op <= 0xBF or op == 0xC7):
                        w.ptrs.append((a, v, op))
                elif img.in_image(v):
                    w.refs.append((a, v))
            nxt = a + n
            if nxt > w.end:
                w.end = nxt
            if kind in (RET, INT3, HALT):
                break
            if kind == CALL:
                w.calls.append((a, tgt))
            elif kind in (JMP, JCC):
                internal = True
                if not (tlo <= tgt < thi):
                    w.out_of_text.append(tgt)
                    internal = False
                elif tgt != entry and tgt in starts:
                    internal = False
                elif tgt < entry:
                    internal = False
                elif kind == JMP and tgt > a and img.padding_before(tgt) and tgt - a > 0x20:
                    internal = False
                if internal:
                    stack.append(tgt)
                else:
                    w.tail.append((a, tgt))
                if kind == JMP:
                    break
            elif kind == JMPIND:
                if tbl is not None and img.in_image(tbl):
                    bound = None
                    for site, rn, rpre, rop in reversed(recent[-6:]):
                        b = _cmp_bound(img, site, rpre) if rop in (0x83, 0x81, 0x3C, 0x3D) else None
                        if b is not None:
                            bound = b + 1
                            break
                    btab = None
                    for site, rn, rpre, rop in reversed(recent[-4:]):
                        if rop in (0x8A, 0x0FB6):   # mov r8,[reg+B] / movzx r,[reg+B]
                            for off, role in ins[site][3]:
                                if role == DISP:
                                    btab = struct.unpack_from("<I", text, site - tlo + off)[0]
                            break
                    if btab is not None and img.in_image(btab):
                        bt = img.read(btab, bound if bound is not None else 256) or b""
                        targets = _read_table(img, tbl, (max(bt) + 1) if bt else 0)
                        w.tables.append((tbl, targets, btab, len(bt)))
                    else:
                        w.tables.append((tbl, _read_table(img, tbl, bound), None, 0))
                    for t in w.tables[-1][1]:
                        if t not in ins:
                            stack.append(t)
                break
            recent.append((a, n, pre, op))
            if len(recent) > 12:
                del recent[:6]
            a = nxt
    for tva, targets, btab, bcount in w.tables:
        e = tva + 4 * len(targets)
        if btab is not None:
            e = max(e, btab + bcount)
        if e > w.end:
            w.end = e
    return w


def mask_bytes(img, w):
    """Relocation-masked bytes of a walk's instructions in address order.

    Absolute fields that point into the image and calls are zeroed; jumps are zeroed when they
    leave the function. Returns a list of per-instruction byte strings."""
    text, tlo = img._text, img.text_lo
    toks = []
    for a in sorted(w.insns):
        n, kind, tgt, fields, op, pre, tbl = w.insns[a]
        raw = bytearray(text[a - tlo: a - tlo + n])
        leaves = kind in (JMP, JCC) and not (w.entry <= tgt < w.end)
        for off, role in fields:
            if role == REL:
                if kind == CALL or leaves:
                    raw[off:off + 4] = b"\0\0\0\0"
            else:
                v = struct.unpack_from("<I", raw, off)[0]
                if img.in_image(v):
                    raw[off:off + 4] = b"\0\0\0\0"
        if leaves and not fields:
            raw[-1] = 0
        toks.append(bytes(raw))
    return toks


def rtti_vtables(img):
    """MSVC RTTI sweep. Returns {(class_name, col_offset): [slot targets]} (first vtable per key)."""
    out = {}
    for sec in (".rdata", ".data"):
        if not img.has_section(sec):
            continue
        start, blob = img.sect_bytes(sec)
        n = len(blob) // 4
        dw = array("I")
        dw.frombytes(blob[: n * 4])
        lo, hi = img.base, img.end
        for i in [i for i, v in enumerate(dw) if lo <= v < hi and not v & 3]:
            if i >= n - 1:
                break
            col = dw[i]
            f = img.read(col, 20)
            if not f or len(f) < 20:
                continue
            sig, off, cdoff, td, chd = struct.unpack("<IiIII", f)
            if sig != 0 or not img.in_image(td) or not img.in_image(chd):
                continue
            nm = img.cstring(td + 8, minlen=4)
            if nm is None or not nm.startswith((".?AV", ".?AU")):
                continue
            slots = []
            j = i + 1
            while j < n and img.in_text(dw[j]):
                slots.append(dw[j])
                j += 1
            if slots:
                out.setdefault((nm, off), slots)
    return out


def data_code_pointers(img):
    """{target: [source_va]} for aligned dwords in .rdata/.data that point into .text."""
    out = {}
    for sec in (".rdata", ".data"):
        if not img.has_section(sec):
            continue
        start, blob = img.sect_bytes(sec)
        n = len(blob) // 4
        dw = array("I")
        dw.frombytes(blob[: n * 4])
        lo, hi = img.text_lo, img.text_hi
        for i in [i for i, v in enumerate(dw) if lo <= v < hi]:
            out.setdefault(dw[i], []).append(start + 4 * i)
    return out


def padding_starts(img):
    """16-aligned .text addresses preceded by CC/90 padding that are not themselves CC/90."""
    t = img._text
    return [img.text_lo + o for o in range(16, len(t), 16) if t[o] not in (0xCC, 0x90) and t[o - 1] in (0xCC, 0x90)]


def discover(img, roots, max_rounds=4):
    """Recursive-descent discovery. Returns (walks, starts, evidence).

    walks:    {start: Walk}
    starts:   set of function starts (roots plus every direct call target and tail-jump target
              reached from a clean walk)
    evidence: {target: {"call": [site], "jmp": [site], "codeptr": [site]}} from clean walks only
              (a walk that hit undecodable bytes or data-like opcodes is not trusted to name callees)
    A function whose walk swallowed a later-discovered start is walked again with the grown set.
    """
    starts = set(roots)
    walks = {}
    evidence = {}
    pending = list(roots)

    def note(t, kind, site):
        evidence.setdefault(t, {}).setdefault(kind, []).append(site)

    def clean(w):
        return not w.bad and not w.suspicious and not w.out_of_text

    for _ in range(max_rounds):
        while pending:
            s = pending.pop()
            if s in walks or not img.in_text(s):
                continue
            w = walk(img, s, starts)
            walks[s] = w
            if not clean(w):
                continue
            for site, t in w.calls:
                if img.in_text(t):
                    note(t, "call", site)
                    if t not in starts:
                        starts.add(t)
                        pending.append(t)
            for site, t in w.tail:
                if img.in_text(t):
                    note(t, "jmp", site)
                    if t not in starts:
                        starts.add(t)
                        pending.append(t)
            for site, v, op in w.ptrs:
                note(v, "codeptr", site)
        redo = [s for s, w in walks.items() if any(o != s and o in starts for o in w.insns)]
        if not redo:
            break
        for s in redo:
            del walks[s]
            pending.append(s)
        # evidence from the discarded walks is recomputed; rebuild it from scratch for simplicity
        evidence.clear()
        for s, w in walks.items():
            if clean(w):
                for site, t in w.calls:
                    note(t, "call", site)
                for site, t in w.tail:
                    note(t, "jmp", site)
                for site, v, op in w.ptrs:
                    note(v, "codeptr", site)
    return walks, starts, evidence

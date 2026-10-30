#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# Provenance: original project tooling; reads the developer-supplied pinned PE ($GAMEMD_BINARY) at run
# time only. The committed match/rsrc/gamemd.rc is the reconstruction this script started; the script
# is the starting point, the .rc is the source.
"""Decompile the resource directory of the pinned image into an .rc script (dialogs, menu, version).

Reads the resource tree of $GAMEMD_BINARY and writes
  match/rsrc/gamemd.rc   DIALOGEX templates, the MENU, the VERSIONINFO, and ICON/CURSOR statements that
                         name the blank placeholder files (never the retail artwork)
  match/rsrc/resource.h  the resource ids
  match/rsrc/placeholder_*.ico / *.cur  blank images with the retail groups' image count and dimensions
Icon and cursor image data is never written: the placeholders are generated here from the group
directories (sizes and bit depths only) and filled with zeros / a single colour.

Also exposes the tree parser and the dialog / menu / version readers for scripts/vc6/rsrc_check.py.

Usage:  GAMEMD_BINARY=gamemd.exe scripts/vc6/rsrc_decompile.py [--out match/rsrc]
"""
import argparse
import os
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

RT_CURSOR, RT_BITMAP, RT_ICON, RT_MENU, RT_DIALOG = 1, 2, 3, 4, 5
RT_GROUP_CURSOR, RT_GROUP_ICON, RT_VERSION = 12, 14, 16


# ---------------------------------------------------------------- resource tree

def read_resources(path, locations=None, data=None):
    """[(type, name, lang, bytes)] in directory order, plus the .rsrc section's (rva, raw bytes).
    locations: a list to append (type, name, RVA, size) of every data entry to; data: the image bytes instead of path."""
    d = Path(path).read_bytes() if data is None else data
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    nsec = struct.unpack_from("<H", d, pe + 6)[0]
    rva = raw = None
    for i in range(nsec):
        o = pe + 0xF8 + 40 * i
        if d[o:o + 8].rstrip(b"\0") == b".rsrc":
            vsize, rva, rsize, rptr = struct.unpack_from("<IIII", d, o + 8)
            raw = d[rptr:rptr + min(vsize, rsize)]
    if raw is None:
        raise SystemExit("no .rsrc section")

    def entries(off):
        nn, ni = struct.unpack_from("<HH", raw, off + 12)
        return [struct.unpack_from("<II", raw, off + 16 + 8 * k) for k in range(nn + ni)]

    def ident(x):
        if x & 0x80000000:
            o = x & 0x7FFFFFFF
            n = struct.unpack_from("<H", raw, o)[0]
            return raw[o + 2:o + 2 + 2 * n].decode("utf-16-le")
        return x

    out = []
    for t, o1 in entries(0):
        for n, o2 in entries(o1 & 0x7FFFFFFF):
            for lang, o3 in entries(o2 & 0x7FFFFFFF):
                drva, size, _, _ = struct.unpack_from("<IIII", raw, o3)
                out.append((ident(t), ident(n), ident(lang), raw[drva - rva:drva - rva + size]))
                if locations is not None:
                    locations.append((out[-1][0], out[-1][1], drva, size))
    return out, rva, raw


# ---------------------------------------------------------------- readers

class Cursor:
    def __init__(self, data):
        self.d, self.p = data, 0

    def u8(self):
        v = self.d[self.p]; self.p += 1; return v

    def u16(self):
        v = struct.unpack_from("<H", self.d, self.p)[0]; self.p += 2; return v

    def i16(self):
        v = struct.unpack_from("<h", self.d, self.p)[0]; self.p += 2; return v

    def u32(self):
        v = struct.unpack_from("<I", self.d, self.p)[0]; self.p += 4; return v

    def sz(self):
        s = self.p
        while self.d[self.p:self.p + 2] != b"\0\0":
            self.p += 2
        v = self.d[s:self.p].decode("utf-16-le"); self.p += 2; return v

    def align(self, n=4):
        self.p = (self.p + n - 1) & ~(n - 1)

    def ord_or_sz(self):
        """None for an empty entry, an int for an ordinal, a str otherwise."""
        first = self.u16()
        if first == 0:
            return None
        if first == 0xFFFF:
            return self.u16()
        self.p -= 2
        return self.sz()


def read_dialog(data):
    """Dialog template as a dict; "ex" tells DLGTEMPLATEEX (DIALOGEX) from DLGTEMPLATE (DIALOG)."""
    c = Cursor(data)
    ex = struct.unpack_from("<HH", data, 0) == (1, 0xFFFF)
    if ex:
        c.p = 4
        dlg = {"ex": True, "help": c.u32(), "exstyle": c.u32(), "style": c.u32()}
    else:
        dlg = {"ex": False, "help": 0, "style": c.u32(), "exstyle": c.u32()}
    count = c.u16()
    dlg.update(x=c.i16(), y=c.i16(), cx=c.i16(), cy=c.i16())
    dlg["menu"], dlg["class"] = c.ord_or_sz(), c.ord_or_sz()
    dlg["caption"] = c.sz()
    dlg["font"] = None
    if dlg["style"] & 0x40:
        pt = c.u16()
        if ex:
            weight, italic, charset = c.u16(), c.u8(), c.u8()
        else:
            weight = italic = charset = None
        dlg["font"] = (pt, c.sz(), weight, italic, charset)
    items = []
    for _ in range(count):
        c.align()
        if ex:
            it = {"help": c.u32(), "exstyle": c.u32(), "style": c.u32()}
        else:
            it = {"help": 0, "style": c.u32(), "exstyle": c.u32()}
        it.update(x=c.i16(), y=c.i16(), cx=c.i16(), cy=c.i16())
        if ex:
            it["id"] = struct.unpack_from("<i", c.d, c.p)[0]; c.p += 4
        else:
            it["id"] = c.i16()
        it["class"], it["title"] = c.ord_or_sz(), c.ord_or_sz()
        extra = c.u16()
        it["extra"] = c.d[c.p:c.p + extra]; c.p += extra
        items.append(it)
    dlg["items"] = items
    if len(data) - c.p >= 4:
        raise ValueError(f"dialog: {len(data) - c.p} bytes left")
    return dlg


def read_menu(data):
    """[(flags, id, text, children)] for a plain (non-EX) MENUHEADER menu."""
    c = Cursor(data)
    if (c.u16(), c.u16()) != (0, 0):
        raise ValueError("menu header")

    def items():
        out = []
        while True:
            flags = c.u16()
            if flags & 0x10:   # MF_POPUP
                text = c.sz()
                out.append((flags & ~0x80, None, text, items()))
            else:
                mid = c.u16()
                out.append((flags & ~0x80, mid, c.sz(), None))
            if flags & 0x80:
                return out
    return items()


def read_version(data):
    """(fixed dict, [(block name, [(key, value)])], translation) of a VS_VERSION_INFO resource."""
    c = Cursor(data)
    length, vlen, vtype = c.u16(), c.u16(), c.u16()
    key = c.sz()
    if key != "VS_VERSION_INFO":
        raise ValueError("version key")
    c.align()
    fixed = dict(zip(("sig", "strucver", "fvms", "fvls", "pvms", "pvls", "mask", "flags", "os", "type", "subtype",
                      "dms", "dls"), struct.unpack_from("<13I", c.d, c.p)))
    c.p += vlen
    blocks, trans = [], None
    while c.p < length:
        c.align()
        start = c.p
        blen, bvlen, btype = c.u16(), c.u16(), c.u16()
        name = c.sz()
        c.align()
        end = start + blen
        if name == "StringFileInfo":
            tables = []
            while c.p < end:
                c.align()
                tstart = c.p
                tlen = c.u16(); c.u16(); c.u16()
                lang = c.sz()
                c.align()
                strs = []
                while c.p < tstart + tlen:
                    c.align()
                    sstart = c.p
                    slen, svlen, stype = c.u16(), c.u16(), c.u16()
                    k = c.sz()
                    c.align()
                    v = c.sz() if svlen else None
                    strs.append((k, v, svlen))
                    c.p = sstart + slen
                tables.append((lang, strs))
                c.p = tstart + tlen
            blocks.append((name, tables))
        else:   # VarFileInfo
            while c.p < end:
                c.align()
                vstart = c.p
                vl, vvl, _ = c.u16(), c.u16(), c.u16()
                k = c.sz()
                c.align()
                trans = struct.unpack_from("<HH", c.d, c.p)
                c.p = vstart + vl
        c.p = end
    return fixed, blocks, trans


# ---------------------------------------------------------------- symbolic names

WS = [(0x80000000, "WS_POPUP"), (0x40000000, "WS_CHILD"), (0x20000000, "WS_MINIMIZE"), (0x10000000, "WS_VISIBLE"),
      (0x08000000, "WS_DISABLED"), (0x04000000, "WS_CLIPSIBLINGS"), (0x02000000, "WS_CLIPCHILDREN"),
      (0x01000000, "WS_MAXIMIZE"), (0x00C00000, "WS_CAPTION"), (0x00800000, "WS_BORDER"), (0x00400000, "WS_DLGFRAME"),
      (0x00200000, "WS_VSCROLL"), (0x00100000, "WS_HSCROLL"), (0x00080000, "WS_SYSMENU"), (0x00040000, "WS_THICKFRAME"),
      (0x00020000, "WS_GROUP"), (0x00010000, "WS_TABSTOP")]
WS_DLG = [(v, "WS_MINIMIZEBOX" if v == 0x20000 else "WS_MAXIMIZEBOX" if v == 0x10000 else n) for v, n in WS]
DS = [(0x1, "DS_ABSALIGN"), (0x2, "DS_SYSMODAL"), (0x4, "DS_3DLOOK"), (0x8, "DS_FIXEDSYS"), (0x10, "DS_NOFAILCREATE"),
      (0x20, "DS_LOCALEDIT"), (0x40, "DS_SETFONT"), (0x80, "DS_MODALFRAME"), (0x100, "DS_NOIDLEMSG"),
      (0x200, "DS_SETFOREGROUND"), (0x400, "DS_CONTROL"), (0x800, "DS_CENTER"), (0x1000, "DS_CENTERMOUSE"),
      (0x2000, "DS_CONTEXTHELP")]
WSEX = [(0x1, "WS_EX_DLGMODALFRAME"), (0x4, "WS_EX_NOPARENTNOTIFY"), (0x8, "WS_EX_TOPMOST"), (0x10, "WS_EX_ACCEPTFILES"),
        (0x20, "WS_EX_TRANSPARENT"), (0x40, "WS_EX_MDICHILD"), (0x80, "WS_EX_TOOLWINDOW"), (0x100, "WS_EX_WINDOWEDGE"),
        (0x200, "WS_EX_CLIENTEDGE"), (0x400, "WS_EX_CONTEXTHELP"), (0x1000, "WS_EX_RIGHT"), (0x2000, "WS_EX_RTLREADING"),
        (0x4000, "WS_EX_LEFTSCROLLBAR"), (0x10000, "WS_EX_CONTROLPARENT"), (0x20000, "WS_EX_STATICEDGE"),
        (0x40000, "WS_EX_APPWINDOW")]

# class -> (enum mask, {value: name}, [(flag, name)]) for the low 16 style bits
BUTTON = (0xF, {0: "BS_PUSHBUTTON", 1: "BS_DEFPUSHBUTTON", 2: "BS_CHECKBOX", 3: "BS_AUTOCHECKBOX", 4: "BS_RADIOBUTTON",
                5: "BS_3STATE", 6: "BS_AUTO3STATE", 7: "BS_GROUPBOX", 8: "BS_USERBUTTON", 9: "BS_AUTORADIOBUTTON",
                0xB: "BS_OWNERDRAW"},
          [(0x20, "BS_LEFTTEXT"), (0x40, "BS_ICON"), (0x80, "BS_BITMAP"), (0xC00, "BS_VCENTER"), (0x300, "BS_CENTER"),
           (0x100, "BS_LEFT"), (0x200, "BS_RIGHT"), (0x400, "BS_TOP"), (0x800, "BS_BOTTOM"), (0x1000, "BS_PUSHLIKE"),
           (0x2000, "BS_MULTILINE"), (0x4000, "BS_NOTIFY"), (0x8000, "BS_FLAT")])
STATIC = (0x1F, {0: "SS_LEFT", 1: "SS_CENTER", 2: "SS_RIGHT", 3: "SS_ICON", 4: "SS_BLACKRECT", 5: "SS_GRAYRECT",
                 6: "SS_WHITERECT", 7: "SS_BLACKFRAME", 8: "SS_GRAYFRAME", 9: "SS_WHITEFRAME", 0xA: "SS_USERITEM",
                 0xB: "SS_SIMPLE", 0xC: "SS_LEFTNOWORDWRAP", 0xD: "SS_OWNERDRAW", 0xE: "SS_BITMAP",
                 0xF: "SS_ENHMETAFILE", 0x10: "SS_ETCHEDHORZ", 0x11: "SS_ETCHEDVERT", 0x12: "SS_ETCHEDFRAME"},
          [(0x80, "SS_NOPREFIX"), (0x100, "SS_NOTIFY"), (0x200, "SS_CENTERIMAGE"), (0x400, "SS_RIGHTJUST"),
           (0x800, "SS_REALSIZEIMAGE"), (0x1000, "SS_SUNKEN"), (0xC000, "SS_WORDELLIPSIS"), (0x4000, "SS_ENDELLIPSIS"),
           (0x8000, "SS_PATHELLIPSIS")])
EDIT = (0x3, {0: "ES_LEFT", 1: "ES_CENTER", 2: "ES_RIGHT"},
        [(0x4, "ES_MULTILINE"), (0x8, "ES_UPPERCASE"), (0x10, "ES_LOWERCASE"), (0x20, "ES_PASSWORD"),
         (0x40, "ES_AUTOVSCROLL"), (0x80, "ES_AUTOHSCROLL"), (0x100, "ES_NOHIDESEL"), (0x400, "ES_OEMCONVERT"),
         (0x800, "ES_READONLY"), (0x1000, "ES_WANTRETURN"), (0x2000, "ES_NUMBER")])
LISTBOX = (0, {}, [(0x1, "LBS_NOTIFY"), (0x2, "LBS_SORT"), (0x4, "LBS_NOREDRAW"), (0x8, "LBS_MULTIPLESEL"),
                   (0x10, "LBS_OWNERDRAWFIXED"), (0x20, "LBS_OWNERDRAWVARIABLE"), (0x40, "LBS_HASSTRINGS"),
                   (0x80, "LBS_USETABSTOPS"), (0x100, "LBS_NOINTEGRALHEIGHT"), (0x200, "LBS_MULTICOLUMN"),
                   (0x400, "LBS_WANTKEYBOARDINPUT"), (0x800, "LBS_EXTENDEDSEL"), (0x1000, "LBS_DISABLENOSCROLL"),
                   (0x2000, "LBS_NODATA"), (0x4000, "LBS_NOSEL")])
COMBO = (0x3, {1: "CBS_SIMPLE", 2: "CBS_DROPDOWN", 3: "CBS_DROPDOWNLIST"},
         [(0x10, "CBS_OWNERDRAWFIXED"), (0x20, "CBS_OWNERDRAWVARIABLE"), (0x40, "CBS_AUTOHSCROLL"),
          (0x80, "CBS_OEMCONVERT"), (0x100, "CBS_SORT"), (0x200, "CBS_HASSTRINGS"), (0x400, "CBS_NOINTEGRALHEIGHT"),
          (0x800, "CBS_DISABLENOSCROLL"), (0x2000, "CBS_UPPERCASE"), (0x4000, "CBS_LOWERCASE")])
SCROLL = (0x1, {0: "SBS_HORZ", 1: "SBS_VERT"},
          [(0x2, "SBS_TOPALIGN"), (0x4, "SBS_BOTTOMALIGN"), (0x8, "SBS_SIZEBOX"), (0x10, "SBS_SIZEGRIP")])
TRACKBAR = (0, {}, [(0x1, "TBS_AUTOTICKS"), (0x2, "TBS_VERT"), (0x4, "TBS_TOP"), (0x8, "TBS_BOTH"),
                    (0x10, "TBS_NOTICKS"), (0x20, "TBS_ENABLESELRANGE"), (0x40, "TBS_FIXEDLENGTH"),
                    (0x80, "TBS_NOTHUMB"), (0x100, "TBS_TOOLTIPS")])
LISTVIEW = (0x3, {0: "LVS_ICON", 1: "LVS_REPORT", 2: "LVS_SMALLICON", 3: "LVS_LIST"},
            [(0x4, "LVS_SINGLESEL"), (0x8, "LVS_SHOWSELALWAYS"), (0x10, "LVS_SORTASCENDING"),
             (0x20, "LVS_SORTDESCENDING"), (0x40, "LVS_SHAREIMAGELISTS"), (0x80, "LVS_NOLABELWRAP"),
             (0x100, "LVS_AUTOARRANGE"), (0x200, "LVS_EDITLABELS"), (0x400, "LVS_OWNERDRAWFIXED"),
             (0x800, "LVS_ALIGNLEFT"), (0x1000, "LVS_OWNERDATA"), (0x2000, "LVS_NOSCROLL"),
             (0x4000, "LVS_NOCOLUMNHEADER"), (0x8000, "LVS_NOSORTHEADER")])
CLASSES = {128: ("Button", BUTTON), 129: ("Edit", EDIT), 130: ("Static", STATIC), 131: ("ListBox", LISTBOX),
           132: ("ScrollBar", SCROLL), 133: ("ComboBox", COMBO)}
NAMED = {"msctls_trackbar32": TRACKBAR, "SysListView32": LISTVIEW}
# default style bits of each RC control statement (RC.EXE 5.x/VC6, measured: probe in the history of this
# file), on top of WS_CHILD | WS_VISIBLE; a statement may add bits, `NOT` removes a default
CHILD_VISIBLE = 0x50000000
STATEMENTS = {   # (class atom, type value) -> (keyword, default bits, has text)
    (128, 6): ("AUTO3STATE", 0x10006, True), (128, 3): ("AUTOCHECKBOX", 0x10003, True),
    (128, 9): ("AUTORADIOBUTTON", 0x9, True), (128, 2): ("CHECKBOX", 0x10002, True),
    (128, 1): ("DEFPUSHBUTTON", 0x10001, True), (128, 7): ("GROUPBOX", 0x7, True),
    (128, 0): ("PUSHBUTTON", 0x10000, True), (128, 4): ("RADIOBUTTON", 0x4, True), (128, 5): ("STATE3", 0x10005, True),
    (130, 1): ("CTEXT", 0x20001, True), (130, 0): ("LTEXT", 0x20000, True), (130, 2): ("RTEXT", 0x20002, True),
    (129, None): ("EDITTEXT", 0x810000, False), (131, None): ("LISTBOX", 0x800001, False),
    (133, None): ("COMBOBOX", 0x0, False), (132, None): ("SCROLLBAR", 0x0, False),
}


def names(value, table):
    """Symbolic OR-expression pieces for the bits of value covered by table; returns (pieces, remainder)."""
    pieces = []
    for bit, name in table:
        if value & bit == bit and bit:
            pieces.append(name)
            value &= ~bit
    return pieces, value


def style_pieces(style, cls, dialog=False, zero=True):
    """Symbolic pieces for a style word: window bits by name, the low 16 bits by the class table."""
    pieces, rest = names(style & 0xFFFF0000, WS_DLG if dialog else WS)
    low, lowp = style & 0xFFFF, []
    if dialog:
        lowp, low = names(low, DS)
    else:
        spec = CLASSES[cls][1] if isinstance(cls, int) and cls in CLASSES else NAMED.get(cls)
        if spec:
            mask, enum, flags = spec
            if mask and (low & mask) in enum:
                if low & mask or zero:
                    lowp.append(enum[low & mask])
                low &= ~mask
            more, low = names(low, flags)
            lowp += more
    if low:
        lowp.append("0x%X" % low)
    if rest:
        lowp.append("0x%X" % rest)
    return pieces + lowp if dialog else lowp + pieces


def style_expr(style, defaults, cls, zero=False):
    """Style parameter of a control statement whose implicit bits are `defaults`: the extra bits by name and
    NOT for each implicit window bit the control lacks."""
    pieces = style_pieces(style & ~defaults, cls, zero=zero)
    for bit, name in WS:
        if bin(bit).count("1") == 1 and defaults & bit and not style & bit:
            pieces.append("NOT " + name)
    return " | ".join(pieces) if pieces else None


def esc(s):
    out = []
    for ch in s:
        o = ord(ch)
        if ch == '"':
            out.append('""')
        elif ch == "\\":
            out.append("\\\\")
        elif ch == "\n":
            out.append("\\n")
        elif ch == "\t":
            out.append("\\t")
        elif ch == "\r":
            out.append("\\r")
        elif 0x20 <= o < 0x7F:
            out.append(ch)
        elif o < 0x100:
            out.append("\\%03o" % o)
        else:
            raise ValueError(f"character U+{o:04X} outside code page 1252 needs a wide string")
    return '"' + "".join(out) + '"'


def control_line(it):
    """One control as an RC statement; the keyword statements when the implicit bits fit, else CONTROL."""
    cls, title = it["class"], it["title"]
    style, ex, hid = it["style"], it["exstyle"], it["help"]
    id_ = "IDC_STATIC" if it["id"] == -1 else str(it["id"])
    geom = f"{it['x']}, {it['y']}, {it['cx']}, {it['cy']}"
    trailer = []
    if ex or hid:
        trailer.append(" | ".join(n for b, n in WSEX if ex & b) if ex else "0")
        if ex & ~sum(b for b, _ in WSEX):
            raise ValueError("unnamed extended style bits")
    if hid:
        trailer.append(str(hid))
    spec = None
    if isinstance(cls, int) and cls in CLASSES and (title is None or isinstance(title, str)):
        key = (cls, style & CLASSES[cls][1][0] if cls in (128, 130) else None)
        spec = STATEMENTS.get(key)
        if spec:
            kw, defaults, has_text = spec
            full = defaults | CHILD_VISIBLE
            if full & 0xFFFF & ~style or (not has_text and title) or bin(full & ~style).count("1") > 1:
                spec = None
    if spec:
        expression = style_expr(style, full, cls)
        params = [expression] if expression else ["0"] if trailer else []
        text = (esc(title or "") + ", ") if has_text else ""
        return f"{kw:<14}{text}{id_}, {geom}" + "".join(", " + q for q in params + trailer)
    cname = CLASSES[cls][0] if isinstance(cls, int) and cls in CLASSES else cls
    if isinstance(cname, int):
        raise ValueError(f"unnamed class atom {cname}")
    text = esc(title) if isinstance(title, str) else (str(title) if title is not None else '""')
    expression = style_expr(style, CHILD_VISIBLE, cls, zero=True) or "0"
    return f'{"CONTROL":<14}{text}, {id_}, "{cname}", {expression}, {geom}' + "".join(", " + q for q in trailer)


# ---------------------------------------------------------------- emitters

def dialog_text(name, dlg):
    kw = "DIALOGEX" if dlg["ex"] else "DIALOG"
    head = f"{name} {kw} {dlg['x']}, {dlg['y']}, {dlg['cx']}, {dlg['cy']}"
    if dlg["help"]:
        head += f", {dlg['help']}"
    style = dlg["style"] & ~0x40 if dlg["font"] else dlg["style"]
    if dlg["caption"]:
        if style & 0xC00000 != 0xC00000:
            raise ValueError("caption without WS_CAPTION")
        style &= ~0xC00000
    lines = [head, "STYLE " + (" | ".join(style_pieces(style, None, dialog=True)) or "0")]
    if dlg["exstyle"]:
        lines.append("EXSTYLE " + (" | ".join(n for b, n in WSEX if dlg["exstyle"] & b) or "0"))
        left = dlg["exstyle"] & ~sum(b for b, _ in WSEX)
        if left:
            raise ValueError("unnamed extended style bits")
    if dlg["caption"]:
        lines.append("CAPTION " + esc(dlg["caption"]))
    if dlg["menu"] is not None:
        lines.append(f"MENU {dlg['menu']}")
    if dlg["class"] is not None:
        lines.append("CLASS " + (esc(dlg["class"]) if isinstance(dlg["class"], str) else str(dlg["class"])))
    if dlg["font"]:
        pt, face, weight, italic, charset = dlg["font"]
        extra = f", {weight}, {italic}, 0x{charset:X}" if dlg["ex"] else ""
        lines.append(f"FONT {pt}, {esc(face)}{extra}")
    lines.append("BEGIN")
    lines += ["    " + control_line(it) for it in dlg["items"]]
    lines.append("END")
    return "\n".join(lines)


MENU_FLAGS = [(0x1, "GRAYED"), (0x2, "INACTIVE"), (0x4, "BITMAP"), (0x8, "CHECKED"), (0x20, "MENUBARBREAK"),
              (0x40, "MENUBREAK"), (0x100, "OWNERDRAW"), (0x4000, "HELP")]


def menu_text(name, items, depth=0):
    pad = "    " * (depth + 1)
    out = []
    for flags, mid, text, children in items:
        opts = ""
        left = flags & ~0x10
        for bit, n in MENU_FLAGS:
            if left & bit:
                opts += ", " + n
                left &= ~bit
        if left:
            raise ValueError(f"menu flags 0x{left:X}")
        if children is not None:
            out.append(f"{pad}POPUP {esc(text)}{opts}")
            out.append(pad + "BEGIN")
            out += menu_text(None, children, depth + 1)
            out.append(pad + "END")
        elif flags == 0 and mid == 0 and text == "":
            out.append(f"{pad}MENUITEM SEPARATOR")
        else:
            out.append(f"{pad}MENUITEM {esc(text)}, {mid}{opts}")
    if name is None:
        return out
    return "\n".join([f"{name} MENU", "BEGIN"] + out + ["END"])


def version_text(fixed, blocks, trans):
    def quad(hi, lo):
        return f"{hi >> 16},{hi & 0xFFFF},{lo >> 16},{lo & 0xFFFF}"
    if fixed["strucver"] != 0x10000 or fixed["dms"] or fixed["dls"]:
        raise ValueError("version header")
    lines = ["VS_VERSION_INFO VERSIONINFO",
             f" FILEVERSION {quad(fixed['fvms'], fixed['fvls'])}",
             f" PRODUCTVERSION {quad(fixed['pvms'], fixed['pvls'])}",
             f" FILEFLAGSMASK 0x{fixed['mask']:X}L", f" FILEFLAGS 0x{fixed['flags']:X}L",
             f" FILEOS 0x{fixed['os']:X}L", f" FILETYPE 0x{fixed['type']:X}L", f" FILESUBTYPE 0x{fixed['subtype']:X}L",
             "BEGIN", '    BLOCK "StringFileInfo"', "    BEGIN"]
    for _, tables in blocks:
        for lang, strs in tables:
            lines += [f'        BLOCK "{lang}"', "        BEGIN"]
            for k, v, _ in strs:
                lines.append(f'            VALUE "{k}", {esc(v) if v is not None else chr(34) * 2}')
            lines.append("        END")
    lines += ["    END", '    BLOCK "VarFileInfo"', "    BEGIN",
              f'        VALUE "Translation", 0x{trans[0]:X}, {trans[1]}', "    END", "END"]
    return "\n".join(lines)


# ---------------------------------------------------------------- placeholders and main

def write_placeholders(res, out):
    """Blank placeholder files and art_images.txt for the icon / cursor groups of `res`."""
    import rsrc_pack
    images = {(t, n): d for t, n, l, d in res if t in (RT_CURSOR, RT_ICON)}
    rows = ["# Icon and cursor groups of gamemd, in the form scripts/vc6/rsrc_pack.py reads.",
            "# kind group-id file image-ids (in the file's image order). The files are blank placeholders.",
            "# RC.EXE cannot number the images or read PNG-compressed ones, so the packer writes these.", ""]
    for t, gid, lang, d in res:
        if t not in (RT_GROUP_ICON, RT_GROUP_CURSOR):
            continue
        _, _, count = struct.unpack_from("<HHH", d, 0)
        entries, ids = [], []
        for i in range(count):
            e = d[6 + 14 * i:20 + 14 * i]
            if t == RT_GROUP_ICON:
                w, h, cc, _, planes, bpp, size, iid = struct.unpack("<BBBBHHIH", e)
                w, h = w or 256, h or 256
                src = images[(RT_ICON, iid)]
                png = src[:4] == b"\x89PNG"
                data = rsrc_pack.blank_png(w, h, size) if png else rsrc_pack.blank_dib(w, h, bpp)
                if len(data) != size:
                    raise ValueError(f"icon {iid}: blank image is {len(data)} bytes, retail has {size}")
                entries.append((w, h, cc, planes, bpp, data))
            else:
                w, h, planes, bpp, size, iid = struct.unpack("<HHHHIH", e)
                src = images[(RT_CURSOR, iid)]
                hot = struct.unpack_from("<HH", src, 0)
                data = rsrc_pack.blank_dib(w, h // 2, bpp)
                data = data[:40 + (4 << bpp)] + bytes(len(data) - 40 - (4 << bpp) - (w + 31) // 32 * 4 * (h // 2)) \
                    + b"\xff" * ((w + 31) // 32 * 4 * (h // 2))
                data = struct.pack("<IiiHHIIiiII", 40, w, h, planes, bpp, 0, len(data) - 48, 0, 0, 2, 0) + data[40:]
                if len(data) + 4 != size:
                    raise ValueError(f"cursor {iid}: blank image is {len(data) + 4} bytes, retail has {size}")
            ids.append(iid)
        if t == RT_GROUP_ICON:
            fname = f"placeholder_icon_{gid}.ico"
            rsrc_pack.write_ico(out / fname, entries)
            rows.append(f"icon   {gid:<4} {fname:<28} " + " ".join(map(str, ids)))
        else:
            fname = f"placeholder_cursor_{gid}.cur"
            rsrc_pack.write_cur(out / fname, w, h // 2, planes, bpp, hot, data)
            rows.append(f"cursor {gid:<4} {fname:<28} " + " ".join(map(str, ids)))
    (out / "art_images.txt").write_text("\n".join(rows) + "\n")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out", type=Path, default=ROOT / "match/rsrc")
    ap.add_argument("--rc", action="store_true", help="also (re)write gamemd.rc and resource.h")
    args = ap.parse_args(argv)
    binary = os.environ.get("GAMEMD_BINARY")
    if not binary:
        raise SystemExit("rsrc_decompile: GAMEMD_BINARY is not set")
    res, _, _ = read_resources(binary)
    args.out.mkdir(parents=True, exist_ok=True)
    ids = []
    body = []
    for t, n, lang, d in sorted((r for r in res if r[0] in (RT_MENU, RT_DIALOG, RT_VERSION)), key=lambda r: (r[0], r[1])):
        if t == RT_DIALOG:
            name = f"IDD_DLG_{n}"
            ids.append((name, n))
            body.append(dialog_text(name, read_dialog(d)))
        elif t == RT_MENU:
            name = f"IDR_MENU_{n}"
            ids.append((name, n))
            body.append(menu_text(name, read_menu(d)))
        else:
            body.append(version_text(*read_version(d)))
    for t, n, lang, d in res:
        if t == RT_GROUP_ICON:
            ids.append((f"IDI_ICON_{n}", n))
        elif t == RT_GROUP_CURSOR:
            ids.append((f"IDC_CURSOR_{n}", n))
    write_placeholders(res, args.out)
    if args.rc:
        header = ["// SPDX-License-Identifier: GPL-3.0-or-later",
                  "// Provenance: own-binary-via-resource-directory",
                  "// Reconstructed resource script: dialogs, the menu and the version information of gamemd.",
                  "// Icon and cursor groups are not here: see art_images.txt and scripts/vc6/rsrc_pack.py.",
                  "#include <windows.h>", "#include <commctrl.h>", '#include "resource.h"', "",
                  "#pragma code_page(1252)", "LANGUAGE LANG_ENGLISH, SUBLANG_ENGLISH_US", ""]
        (args.out / "gamemd.rc").write_text("\n".join(header) + "\n\n".join(body) + "\n", encoding="latin-1")
        rh = ["// SPDX-License-Identifier: GPL-3.0-or-later", "// Provenance: own-binary-via-resource-directory",
              "// Resource ids of gamemd.rc and art_images.txt.", "#define IDC_STATIC -1", ""]
        rh += [f"#define {name:<16} {n}" for name, n in ids]
        (args.out / "resource.h").write_text("\n".join(rh) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())

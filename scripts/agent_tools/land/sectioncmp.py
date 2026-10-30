#!/usr/bin/env python3
"""sectioncmp.py: COFF section comparison, base objects vs new objects.

Merges the landers' sections.py and secmatch.py. Every section (keyed by name
plus the first external symbol defined in it) is compared on bytes and on the
relocation list (offset, symbol name, type). Section timestamps in the COFF
header are ignored. Sections that disappear and reappear byte-for-byte under a
different key (a function renamed or moved) are paired as MOVED.

CLI:  sectioncmp.py BASE_DIR NEW_DIR OUT.json [--tus a.cpp,b.cpp]
      (dirs are build_project-style trees: <dir>/objects.json is not needed when
      --tus is given; objects are found at <dir>/<tu minus its extension>.obj)
"""
import hashlib
import json
import os
import struct
import sys


def coff(path):
    return _parse(path, False)


def coff_full(path):
    """{section key: (bytes, [(offset, symbol, type)])}; the keys coff() uses."""
    return _parse(path, True)


def _parse(path, full):
    d = open(path, "rb").read()
    nsec = struct.unpack_from("<H", d, 2)[0]
    symoff, nsym = struct.unpack_from("<II", d, 8)
    strtab = symoff + nsym * 18

    def name(raw):
        if raw[:4] == b"\0\0\0\0":
            o = struct.unpack_from("<I", raw, 4)[0]
            return d[strtab + o:d.index(b"\0", strtab + o)].decode("latin1")
        return raw.rstrip(b"\0").decode("latin1")

    syms, secsym = {}, {}
    i = 0
    while i < nsym:
        raw = d[symoff + i * 18: symoff + i * 18 + 18]
        n = name(raw[:8])
        val, sec, typ, cls, aux = struct.unpack_from("<IhHBB", raw, 8)
        syms[i] = n
        if sec > 0 and cls == 2 and sec not in secsym:
            secsym[sec] = n
        i += 1 + aux
        for k in range(1, aux + 1):
            syms[i - k] = ""
    out = {}
    for s in range(nsec):
        h = 20 + s * 40
        sn = name(d[h:h + 8])
        size, ptr, rptr, _, nrel = struct.unpack_from("<IIIIH", d, h + 16)
        if sn.startswith(".debug") or sn == ".drectve":
            continue
        data = d[ptr:ptr + size] if ptr else b"\0" * size
        rel = [struct.unpack_from("<IIH", d, rptr + r * 10) for r in range(nrel)]
        rel = [(o, syms.get(si, "?"), t) for o, si, t in rel]
        key = sn + "|" + secsym.get(s + 1, "")
        k2, c = key, 1
        while k2 in out:
            c += 1
            k2 = "%s#%d" % (key, c)
        out[k2] = (data, rel) if full else (hashlib.sha1(data).hexdigest(), tuple(rel))
    return out


DIR32 = 6


def resolved_equal(base_section, new_section, resolve):
    """True when two (bytes, relocs) sections link to identical bytes once every absolute (DIR32) relocation
    target is resolved to an address: an immediate 0x87F7E8 with no relocation equals a relocation to a symbol
    bound to 0x87F7E8 (the linked bytes are the same). RESOLVE(symbol) -> address or None. Any other
    difference (other bytes, other relocation kinds, unresolvable or different targets) is not equal."""
    (db, rb), (dn, rn) = base_section, new_section
    if len(db) != len(dn):
        return False
    slots = {o for o, _, t in list(rb) + list(rn) if t == DIR32}
    if {x for x in rb if x[0] not in slots} != {x for x in rn if x[0] not in slots}:
        return False
    mb, mn = bytearray(db), bytearray(dn)
    for o in slots:
        if o + 4 > len(db):
            return False
        mb[o:o + 4] = mn[o:o + 4] = b"\0\0\0\0"
    if mb != mn:
        return False

    def value(data, rel, o):
        imm = struct.unpack_from("<I", data, o)[0]
        for ro, sym, t in rel:
            if ro == o and t == DIR32:
                a = resolve(sym)
                return ("abs", (a + imm) & 0xFFFFFFFF) if a is not None else ("sym", sym, imm)
        return ("abs", imm)
    return all(value(db, rb, o) == value(dn, rn, o) for o in slots)


def sections_resolved_equal(base_obj, new_obj, key, resolve):
    x, y = coff_full(base_obj), coff_full(new_obj)
    return key in x and key in y and resolved_equal(x[key], y[key], resolve)


def compare_object(bpath, npath):
    x, y = coff(bpath), coff(npath)
    removed = sorted(set(x) - set(y))
    added = sorted(set(y) - set(x))
    differ = sorted(k for k in set(x) & set(y) if x[k] != y[k])
    if not (removed or added or differ):
        return None
    rec = {"removed": removed, "added": added, "differ": []}
    for k in differ:
        rec["differ"].append({
            "section": k,
            "bytes_same": x[k][0] == y[k][0],
            "reloc_diff": [[list(a), list(b)] for a, b in zip(x[k][1], y[k][1]) if a != b][:3],
            "reloc_count": [len(x[k][1]), len(y[k][1])]})
    # pair removed with added by identical content
    gone = {k: x[k] for k in removed}
    new = {k: y[k] for k in added}
    moved, used = [], set()
    for g, gv in gone.items():
        m = [a for a, av in new.items() if av == gv and a not in used]
        if m:
            moved.append([g, m[0]])
            used.add(m[0])
    pairedg = {g for g, _ in moved}
    rec["moved"] = moved
    rec["removed_unpaired"] = [k for k in removed if k not in pairedg]
    rec["added_unpaired"] = [k for k in added if k not in used]
    return rec


def obj_path(root, tu):
    return os.path.join(root, os.path.splitext(tu)[0] + ".obj")


def compare_trees(base_dir, new_dir, tus):
    """Return {'identical': n, 'changed': {tu: rec}, 'missing_base': [...], 'missing_new': [...]}"""
    rep = {"identical": 0, "changed": {}, "missing_base": [], "missing_new": []}
    for tu in sorted(tus):
        b, n = obj_path(base_dir, tu), obj_path(new_dir, tu)
        if not os.path.isfile(b):
            rep["missing_base"].append(tu)
            continue
        if not os.path.isfile(n):
            rep["missing_new"].append(tu)
            continue
        r = compare_object(b, n)
        if r is None:
            rep["identical"] += 1
        else:
            rep["changed"][tu] = r
    return rep


def summarize(rep, explained=None):
    """Text lines. `explained`: {tu: set(symbol substrings)} sections whose symbol is expected to move."""
    lines = []
    for tu, r in sorted(rep["changed"].items()):
        lines.append("%s removed %d added %d differ %d moved %d" % (
            tu, len(r["removed"]), len(r["added"]), len(r["differ"]), len(r["moved"])))
        for d in r["differ"][:8]:
            lines.append("  DIFFER %s %s" % (d["section"], "bytes same (relocs differ)" if d["bytes_same"] else "BYTES DIFFER"))
        for k in r["removed_unpaired"][:8]:
            lines.append("  REMOVED %s -> no byte-identical section" % k)
        for k in r["added_unpaired"][:8]:
            lines.append("  NEW-ONLY %s" % k)
    return lines


def digest(rep):
    """Order-independent, comparable form: set of (tu, kind, section)."""
    s = set()
    for tu, r in rep["changed"].items():
        for k in r["removed"]:
            s.add((tu, "removed", k))
        for k in r["added"]:
            s.add((tu, "added", k))
        for d in r["differ"]:
            s.add((tu, "differ-bytes" if not d["bytes_same"] else "differ-reloc", d["section"]))
    return s


if __name__ == "__main__":
    base, new, out = sys.argv[1:4]
    tus = None
    if "--tus" in sys.argv:
        tus = sys.argv[sys.argv.index("--tus") + 1].split(",")
    if tus is None:
        tus = [o["source"] for o in json.load(open(new + "/objects.json"))["objects"] if o.get("success")]
    rep = compare_trees(base, new, tus)
    json.dump(rep, open(out, "w"), indent=1)
    print("identical", rep["identical"], "changed", len(rep["changed"]),
          "missing_base", len(rep["missing_base"]), "missing_new", len(rep["missing_new"]))
    print("\n".join(summarize(rep)))

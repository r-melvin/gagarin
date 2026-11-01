#!/usr/bin/env python3
"""Dynamic-initialiser order of a merged TU.

VC6 numbers the `_$E<n>` / `_$S<n>` initialiser symbols of an object from its internal counter and emits them
in source order. A merge changes the counter (more declarations are parsed) but, when the global definitions
are in retail order, not the sequence: the n-th initialiser row of the TU by retail address is the n-th `_$E`
symbol of the object. This module

  * pairs the TU's `_$E` manifest rows with the new object's symbols (order and section bytes both have to
    agree with the rows' bytes in the base object, otherwise the merged source order is not the retail order and
    the pairing is refused with the first row that disagrees);
  * rewrites the rows' `sym` (and the file-scoped `DEST::_$E<n>` bindings) to the new numbers.

  initorder.py renumber --tree WT --dest match/X.cpp --objdir DIR [--base-objs DIR --base-manifest FILE]
"""
import argparse, hashlib, json, os, re, sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', 'wwstruct'))
E_RE = re.compile(r'^_\$E\d+$')


class OrderError(Exception):
    pass


def object_inits(path):
    """[(section number, offset, name, digest)] of the `_$E` symbols of an object, in emission (section) order. The digest is of
    the section bytes only (relocation fields hold addends, the targets are proved by the identity gate)."""
    import wwlib
    data = open(path, 'rb').read()
    secs = wwlib.sections(data)
    out = []
    for name, sec, value, scl in wwlib.defined_symbols(data):
        if E_RE.match(name):
            raw = wwlib.section_bytes(data, secs, sec)
            out.append((sec, value, name, hashlib.sha256(raw).hexdigest()[:12]))
    return sorted(out)


def symbol_digest(path, sym):
    """Digest (as object_inits) of any text symbol of an object, or None."""
    import wwlib
    if not os.path.isfile(path):
        return None
    data = open(path, 'rb').read()
    secs = wwlib.sections(data)
    for name, sec, value, scl in wwlib.defined_symbols(data):
        if name == sym:
            return hashlib.sha256(wwlib.section_bytes(data, secs, sec)).hexdigest()[:12]
    return None


def pair(rows, syms, want=None):
    """rows: [(addr, old_sym)]; syms: [(section number, offset, name, digest)] in emission order; want: {addr: digest of the
    row's bytes in the base object} or None. The n-th row by retail address is the n-th symbol. When the object holds
    more initialisers than rows (unmatched ones have no row) the rows are matched as a subsequence by digest.
    Returns {addr: new_sym}; raises OrderError."""
    rows = sorted(rows)
    if len(rows) == len(syms) and (not want or all(want.get(a) in (None, s[3]) for (a, _), s in zip(rows, syms))):
        return {a: s[2] for (a, _), s in zip(rows, syms)}
    if len(rows) > len(syms):
        raise OrderError('%d initialiser rows but only %d _$E symbols' % (len(rows), len(syms)))
    if not want:
        raise OrderError('%d initialiser rows but %d _$E symbols and no base digests to align them' % (len(rows), len(syms)))
    out, pos = {}, 0
    for a, _ in rows:
        hit = next((k for k in range(pos, len(syms)) if syms[k][3] == want.get(a)), None)
        if hit is None:
            raise OrderError('initialiser 0x%X (%s) is not in retail order in the merged object: no later _$E has its bytes'
                             % (a, rows[[r[0] for r in rows].index(a)][1]))
        out[a] = syms[hit][2]
        pos = hit + 1
    return out


def renumber_text(manifest_text, mapping):
    """Textual edit of the `sym` of the row at each address text, e.g. {"0x63F4F0": "_$E19"} (keeps the file's formatting)."""
    import init_interleave
    return init_interleave.renumber_rows_text(manifest_text, mapping)


def rekey_bindings(bindings, dest, mapping):
    """File-scoped `DEST::_$E<n>` keys follow their row (mapping: address text -> new sym). Returns [{old,new,addr}]."""
    import init_interleave
    return init_interleave.initialiser_rekeys(bindings, dest, mapping)


def renumber(tree, dest, objdir, base_objs=None, base_manifest=None):
    """Renumber the `_$E` rows (and bindings) of `dest` from its freshly built object. Returns {addr: (old, new)}."""
    import init_interleave
    mp = os.path.join(tree, 'scripts/data/match_manifest.json')
    text = open(mp).read()
    man = json.loads(text)
    rows = [(int(r['addr'], 16), r['sym']) for r in man if r['tu'] == dest and E_RE.match(r['sym'])]
    if not rows:
        return {}
    obj = os.path.join(objdir, dest[:-4] + '.obj')
    syms = object_inits(obj)
    want = None
    if base_objs and base_manifest:
        base = {int(r['addr'], 16): r for r in json.load(open(base_manifest))}
        want = {}
        for a, _ in rows:
            b = base.get(a)
            if b:
                want[a] = symbol_digest(os.path.join(base_objs, b['tu'][:-4] + '.obj'), b['sym'])
    by_addr = {int(r['addr'], 16): r['addr'] for r in man if r['tu'] == dest}
    mapping = {by_addr[a]: v for a, v in pair(rows, syms, want).items()}
    new_text, changes = renumber_text(text, mapping)
    open(mp, 'w').write(new_text)
    bp = os.path.join(tree, 'scripts/data/symbol_bindings.json')
    if os.path.isfile(bp):
        bt = open(bp).read()
        rk = rekey_bindings(json.loads(bt), dest, mapping)
        if rk:
            open(bp, 'w').write(init_interleave.apply_rekeys_text(bt, rk))
    return {int(a, 16): (o, n) for a, o, n in changes}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('cmd', choices=['renumber'])
    ap.add_argument('--tree', required=True)
    ap.add_argument('--dest', required=True)
    ap.add_argument('--objdir', required=True)
    ap.add_argument('--base-objs')
    ap.add_argument('--base-manifest')
    a = ap.parse_args(argv)
    try:
        ch = renumber(os.path.abspath(a.tree), a.dest, a.objdir, a.base_objs, a.base_manifest)
    except OrderError as e:
        raise SystemExit('initialiser order: %s' % e)
    for addr, (o, n) in sorted(ch.items()):
        print('0x%X %s -> %s' % (addr, o, n))
    print('renumbered %d initialiser rows' % len(ch))


if __name__ == '__main__':
    main()

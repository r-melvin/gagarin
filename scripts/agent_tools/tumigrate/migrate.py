#!/usr/bin/env python3
"""Move matched function bodies into their original translation unit.

  migrate.py plan  --tree WT --tu TU095 [--exclude FILE ...] [--dest PATH] > plan.json
  migrate.py apply --tree WT --plan plan.json

The mover never rewrites a function body. A source file is split by cppsplit into
its preamble (everything before the first annotated chunk), annotated chunks and
the code between chunks (interstitials). The new TU gets, per contributing file,
the preamble and all code interstitials (hoisted, file order kept), then every
moved chunk in ascending retail address. A file whose every row moves is deleted;
a split file keeps its preamble, interstitials and unmoved chunks.

Initialiser sources (trivgen's trivial_tuNNN_init_methods.*) are folded in the
same way; their header's declarations are inlined because they are this TU's
own globals.
"""
import argparse, csv, json, os, re, subprocess, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cppsplit

SR = os.environ.get('GAG_SCRATCH_ROOT') or os.path.join(os.path.dirname(os.environ.get('GAG_MAIN') or os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..'))), 'gagarin-scratch')
TUMAP = ASSERTS = INIT_DELTA = INIT_SRC = None


def set_inputs(root):
    """Point the scratch inputs (tumap2/, tumig1/, trivgen/) at ROOT."""
    global SR, TUMAP, ASSERTS, INIT_DELTA, INIT_SRC
    SR = os.path.abspath(root)
    TUMAP = SR + '/tumap2/tu_map_v2.csv'
    ASSERTS = SR + '/tumig1/assert_sites.json'
    INIT_DELTA = SR + '/trivgen/READY/manifest_delta_initialisers.json'
    INIT_SRC = SR + '/tumig1/initsrc'


def check_inputs():
    """Exit with a clear message when the required scratch inputs are missing."""
    missing = [p for p in (TUMAP, ASSERTS) if not os.path.isfile(p)]
    if missing:
        raise SystemExit('tumigrate inputs not found under %s:\n  %s\n'
                         'They are untracked scratch data (tumap2/tu_map_v2.csv, tumig1/assert_sites.json). '
                         'Pass --inputs DIR (or set GAG_SCRATCH_ROOT) to the directory that holds tumap2/ and tumig1/.'
                         % (SR, '\n  '.join(missing)))


set_inputs(SR)
DEFAULT_FLAGS = '/nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob2'
FLAG_RE = re.compile(r'^\s*//\s*VC6FLAGS:\s*(.*?)\s*$')
INC_RE = re.compile(r'^(\s*#\s*include\s*")([^"]+)(".*)$')
PROV_RE = re.compile(r'^//\s*Provenance:\s*(.*)$')


def tu_row(tu):
    for t in csv.DictReader(open(TUMAP)):
        if t['tu_id'] == tu:
            return t
    raise SystemExit('no such tu ' + tu)


def flags_of(text):
    for ln in text.split('\n'):
        m = FLAG_RE.match(ln)
        if m:
            return ' '.join(sorted(m.group(1).split()))
    return ' '.join(sorted(DEFAULT_FLAGS.split()))


def header_block(lines):
    """Leading comment block (SPDX/provenance notes)."""
    i = 0
    while i < len(lines) and lines[i].startswith('//'):
        i += 1
    return i


def plan(tree, tu, excludes, dest):
    t = tu_row(tu)
    lo, hi = int(t['text_lo'], 16), int(t['text_hi'], 16)
    hi_e, lo_l = int(t['hi_earliest'], 16), int(t['lo_latest'], 16)
    man = json.load(open(os.path.join(tree, 'scripts/data/match_manifest.json')))
    byfile = collections.defaultdict(list)
    for r in man:
        byfile[r['tu']].append(r)
    inr = lambda a: lo <= a <= hi
    srcs = sorted({r['tu'] for r in man if inr(int(r['addr'], 16))})
    files, skipped = [], []
    for f in srcs:
        if f in excludes:
            skipped.append(dict(file=f, why=excludes[f]))
            continue
        text = open(os.path.join(tree, f), errors='strict').read()
        lines, pre_end, chunks, inters = cppsplit.split(text)
        rows = {int(r['addr'], 16): r for r in byfile[f]}
        found = set()
        move, stay, why = [], [], []
        for ci, c in enumerate(chunks):
            ra = [a for a in c['addrs'] if a in rows]
            if not ra:
                continue  # not a row chunk (e.g. a LIBRARY note); stays as code
            found.update(ra)
            if all(inr(a) for a in ra):
                move.append(ci)
            else:
                stay.append(ci)
                if any(inr(a) for a in ra):
                    why.append('chunk with rows %s straddles the TU bound' % [hex(a) for a in ra])
        missing = [a for a in rows if a not in found]
        whole = not stay and all(inr(a) for a in missing)
        if not whole and any(inr(a) for a in missing):
            why.append('rows %s have no chunk in the file (header/template emitted)' %
                       [hex(a) for a in missing if inr(a)])
        if not move and not (whole and missing):
            skipped.append(dict(file=f, why='; '.join(why) or 'no movable chunk'))
            continue
        moved_rows = [a for ci in move for a in chunks[ci]['addrs'] if a in rows]
        if whole:
            moved_rows += missing
        files.append(dict(file=f, flags=flags_of(text), whole=whole, move=move, all_rows=sorted(rows),
                          rows=sorted(moved_rows), notes=why))
    # initialisers
    inits = []
    for r in ([] if '(initialisers)' in excludes else json.load(open(INIT_DELTA))):
        a = int(r['addr'], 16)
        if inr(a):
            inits.append(r)
    # flags: the set of the largest contributor wins; others are skipped
    cnt = collections.Counter()
    for f in files:
        cnt[f['flags']] += len(f['rows'])
    if inits:
        cnt[' '.join(sorted(DEFAULT_FLAGS.split()))] += 0
    chosen = cnt.most_common(1)[0][0] if cnt else ' '.join(sorted(DEFAULT_FLAGS.split()))
    keep = []
    for f in files:
        if f['flags'] != chosen:
            skipped.append(dict(file=f['file'], why='VC6FLAGS %s differ from the TU set %s' % (f['flags'], chosen)))
        else:
            keep.append(f)
    files = keep
    if dest is None:
        dirs = collections.Counter()
        for f in files:
            dirs[os.path.dirname(f['file'])] += len(f['rows'])
        d = dirs.most_common(1)[0][0] if dirs else 'match/core'
        stem = t['name_or_bound']
        dest = os.path.join(d, stem[:-4] + '.cpp')
    return dict(tu=tu, name=t['name_or_bound'], lo=lo, hi=hi, hi_earliest=hi_e, lo_latest=lo_l,
                sub=int(t['sub_index']), dest=dest, flags=chosen, files=files, skipped=skipped,
                inits=[r['addr'] for r in inits])


def rewrite_includes(lines, srcdir, destdir, tree):
    out = []
    for ln in lines:
        m = INC_RE.match(ln)
        if m:
            p = os.path.normpath(os.path.join(srcdir, m.group(2)))
            if os.path.exists(os.path.join(tree, p)):
                ln = m.group(1) + os.path.relpath(p, destdir) + m.group(3)
        out.append(ln)
    return out


def strip_markers(lines):
    """Drop SPDX, Provenance tag and VC6FLAGS marker lines from a leading block."""
    out, tags = [], []
    for ln in lines:
        if ln.startswith('// SPDX-License-Identifier'):
            continue
        m = PROV_RE.match(ln)
        if m:
            parts = [x.strip() for x in m.group(1).split('|') if x.strip()]
            good = [x for x in parts if re.fullmatch(r'[A-Za-z0-9:@/._-]+', x)]
            tags += good
            if len(good) != len(parts):
                out.append('//   Provenance note: ' + ' | '.join(x for x in parts if x not in good))
            continue
        if FLAG_RE.match(ln):
            continue
        out.append(ln)
    return out, tags


BOILER = re.compile(r'^//\s*(Bytes (matched|diffed) against retail|Ordered ascending|\(?[Oo]rdered ascending|'
                    r'reccmp annotations \(|(FUNCTION|STUB|TEMPLATE|SYNTHETIC): GAMEMD 0x|Target bytes: user)')


def clean_notes(lines):
    out = []
    for ln in lines:
        if BOILER.match(ln):
            continue
        if ln.strip() == '//' and (not out or out[-1].strip() == '//'):
            continue
        out.append(ln)
    while out and out[-1].strip() == '//':
        out.pop()
    return out


def trim_blank(lines):
    while lines and not lines[0].strip():
        lines = lines[1:]
    while lines and not lines[-1].strip():
        lines = lines[:-1]
    return lines


_NOT_DATA = re.compile(r'^(typedef|struct|class|union|enum|template|namespace|using|extern|friend|return|static|const|#)\b|^#')


def externalise(lines):
    """Global data definitions at depth 0 become `extern` declarations (initialiser dropped); the
    definition stays in the file it came from. Statics, consts, functions, prototypes, typedefs and
    aggregate definitions are left as they are."""
    dep = cppsplit.depth_scan(lines)
    out, i, n = [], 0, len(lines)
    while i < n:
        ln = lines[i]
        t = re.sub(r'//.*', '', ln).strip()
        if dep[i][0] != 0 or not t or t.startswith('#') or _NOT_DATA.match(t):
            out.append(ln)
            i += 1
            continue
        # one logical statement: to the line that ends at depth 0 with ';'
        j = i
        while j < n and not (dep[j][1] == 0 and re.sub(r'//.*', '', lines[j]).rstrip().endswith(';')):
            if dep[j][1] == 0 and j > i and not lines[j].strip():
                break
            j += 1
        if j >= n or not re.sub(r'//.*', '', lines[j]).rstrip().endswith(';'):
            out.extend(lines[i:j + 1])
            i = j + 1
            continue
        stmt = ' '.join(re.sub(r'//.*', '', x).strip() for x in lines[i:j + 1])
        decl = stmt[:-1].split('=', 1)[0].strip() if '=' in stmt else stmt[:-1].strip()
        single = ',' not in decl and '{' not in decl and '}' not in decl
        is_data = '(' not in decl and single and re.search(r'[A-Za-z_]\w*\s*(\[[^\]]*\])*$', decl) and ' ' in decl.replace('*', ' * ')
        if is_data and re.match(r'^[A-Za-z_][\w:<>\s\*&]*[\s\*&]\s*[A-Za-z_]\w*\s*(\[[^\]]*\])*$', decl):
            out.append('extern ' + decl + ';')
        else:
            out.extend(lines[i:j + 1])
        i = j + 1
    return out


def compose(tree, p, sites):
    """Pure: returns (dest_text, {rewritten path: text}, deleted)."""
    rewrites = {}
    dest = p['dest']
    destdir = os.path.dirname(dest)
    tags = ['own-binary-via-Ghidra']
    decl_blocks, notes, chunks = [], [], []
    deleted, rewritten, init_files = [], [], []
    tail = []        # unmoved chunks of the destination itself, kept in place
    for f in p['files']:
        is_dest = f['file'] == dest
        path = os.path.join(tree, f['file'])
        text = open(path).read()
        lines, pre_end, chs, inters = cppsplit.split(text)
        hb = header_block(lines[:pre_end])
        head, tg = strip_markers(lines[:hb])
        tags += tg
        head = clean_notes(trim_blank(head))
        pre = [ln for ln in lines[hb:pre_end] if not FLAG_RE.match(ln)]
        pre = rewrite_includes(pre, os.path.dirname(f['file']), destdir, tree)
        block = []
        if head:
            notes.append(head)
        block += trim_blank(pre)
        keeps_defs = not f['whole'] and not is_dest
        rowset = set(f['rows']) | set(f.get('all_rows', []))
        spans = list(inters) + [(c['start'], c['end']) for c in chs
                                if not any(x in f.get('all_rows', f['rows']) for x in c['addrs'])]
        for a, b in sorted(spans):
            if cppsplit.code_only(lines[a:b]) or re.search(r'^//\s?(FUNCTION|STUB|TEMPLATE|SYNTHETIC|LIBRARY):', '\n'.join(lines[a:b]), re.M):
                block += [''] + trim_blank(rewrite_includes(lines[a:b], os.path.dirname(f['file']), destdir, tree))
        if keeps_defs:
            # the source file keeps its definitions; the new TU only sees extern declarations
            block = externalise(block)
        decl_blocks.append(block)
        mv = set(f['move'])
        for ci in sorted(mv):
            c = chs[ci]
            body = trim_blank(lines[c['start']:c['end']])
            key = min(a for a in c['addrs'] if a in set(f['rows']) or True)
            rowsin = [a for a in c['addrs'] if a in set(f['rows'])]
            key = min(rowsin)
            chunks.append((key, body))
        if is_dest:
            # destination already exists and contributes: merge into it (it is rewritten as the new
            # TU; its unmoved chunks follow the moved ones, in place)
            for ci, c in enumerate(chs):
                if ci not in mv and any(a in set(f['all_rows']) for a in c['addrs']):
                    tail.append(trim_blank(lines[c['start']:c['end']]))
        elif f['whole']:
            deleted.append(f['file'])
        else:
            keep, i = [], 0
            drop = set()
            for ci in mv:
                drop.update(range(chs[ci]['start'], chs[ci]['end']))
            for i, ln in enumerate(lines):
                if i not in drop:
                    keep.append(ln)
            # collapse runs of >2 blank lines created by the removal
            out, blank = [], 0
            for ln in keep:
                blank = blank + 1 if not ln.strip() else 0
                if blank <= 2:
                    out.append(ln)
            rewrites[f['file']] = '\n'.join(out)
            rewritten.append(f['file'])
    # initialisers
    init_rows = set(int(a, 16) for a in p['inits'])
    if init_rows:
        delta = {int(r['addr'], 16): r for r in json.load(open(INIT_DELTA))}
        srcs = sorted({delta[a]['tu'] for a in init_rows})
        for s in srcs:
            text = open(os.path.join(INIT_SRC, s)).read()
            lines, pre_end, chs, inters = cppsplit.split(text)
            hpath = os.path.join(INIT_SRC, s[:-4] + '.h')
            htext = open(hpath).read().split('\n')
            # the header's declarations, without guard, provenance and the FUNCTION prototypes
            body = []
            hl = header_block(htext)
            skip_next = False
            for ln in htext[hl:]:
                if ln.startswith('#ifndef GG_') or ln.startswith('#define GG_') or ln.startswith('#endif  // GG_'):
                    continue
                if cppsplit.ANN.match(ln):
                    skip_next = True
                    continue
                if skip_next:
                    skip_next = False
                    continue
                body.append(ln)
            body = rewrite_includes(body, os.path.dirname(s), destdir, tree)
            decl_blocks.append(['// Globals written by this TU\'s static initialisers (placeholder names; no',
                                '// canonical header declares them yet).'] + trim_blank(body))
            for c in chs:
                ra = [a for a in c['addrs'] if a in init_rows]
                if ra:
                    chunks.append((min(ra), trim_blank(lines[c['start']:c['end']])))
            init_files.append(s)
    chunks.sort(key=lambda x: x[0])
    # TU-window marks
    out_chunks = []
    for key, body in chunks:
        win = (p['sub'] == 0 and key > p['hi_earliest']) or (p['sub'] > 0 and key < p['lo_latest'])
        if win:
            body = ['// TU-WINDOW: past the proven bound of this TU; it may belong to a later'
                    ' header-less object.' if p['sub'] == 0 else
                    '// TU-WINDOW: before the proven start of this TU; it may belong to the'
                    ' previous object.'] + body
        out_chunks.append(body)
    utags = []
    for x in tags:
        if x not in utags:
            utags.append(x)
    s = sites[p['tu']]
    push = s['push_sites'][0] if s['push_sites'] else None
    hdr = ['// SPDX-License-Identifier: GPL-3.0-or-later',
           '// Provenance: ' + ' | '.join(utags),
           '//   Original translation unit %s. The name is the source-file string at %s' % (p['name'], s['strings'][0]),
           '//   in retail gamemd.exe v1.001, passed by the assert at %s inside this object\'s' % push,
           '//   code range (%s-%s). Functions are in ascending retail address order.' % (hex(p['lo']), hex(p['hi']))]
    if p['flags'] != ' '.join(sorted(DEFAULT_FLAGS.split())):
        fl = p['flags'].split()
        order = DEFAULT_FLAGS.split()
        extra = [x for x in fl if x not in order]
        hdr.append('// VC6FLAGS: ' + ' '.join([x for x in order if x in fl] + extra))
    body_text = '\n'.join('\n'.join(b) for b in decl_blocks + out_chunks)
    if re.search(r'\b(Obj|Gbl)_[0-9A-F]{8}\b', body_text):
        hdr += ['//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing',
                '//   them with the canonical class re-mangles their symbols, so that is left to',
                '//   a separate rename-only change.']
    text = hdr
    for n in notes:
        text += ['//'] + n
    for b in decl_blocks:
        if b:
            text += [''] + b
    for b in out_chunks + tail:
        text += [''] + b
    return '\n'.join(text) + '\n', rewrites, deleted


def apply(tree, p, sites):
    dest = p['dest']
    if os.path.exists(os.path.join(tree, dest)) and dest not in {f['file'] for f in p['files']}:
        raise SystemExit('destination %s already exists and is not a contributor; refusing to overwrite it' % dest)
    dtext, rewrites, deleted = compose(tree, p, sites)
    for f, t in rewrites.items():
        open(os.path.join(tree, f), 'w').write(t)
    open(os.path.join(tree, dest), 'w').write(dtext)
    init_rows = set(int(a, 16) for a in p['inits'])
    # manifest
    mp = os.path.join(tree, 'scripts/data/match_manifest.json')
    man = json.load(open(mp))
    moved = set()
    for f in p['files']:
        moved.update(f['rows'])
    n = 0
    for r in man:
        if int(r['addr'], 16) in moved:
            r['tu'] = dest
            n += 1
    if init_rows:
        delta = {int(r['addr'], 16): r for r in json.load(open(INIT_DELTA))}
        for a in sorted(init_rows):
            r = dict(delta[a]); r['tu'] = dest
            man.append(r)
    open(mp, 'w').write(json.dumps(man, indent=1))
    for f in deleted:
        subprocess.run(['git', '-C', tree, 'rm', '-q', '-f', f], check=True)
    subprocess.run(['git', '-C', tree, 'add', '--', dest], check=True)
    return dict(dest=dest, moved_rows=n, init_rows=len(init_rows), deleted=deleted, rewritten=sorted(rewrites))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('cmd')
    ap.add_argument('--tree', required=True)
    ap.add_argument('--tu')
    ap.add_argument('--exclude', action='append', default=[], help='FILE=reason')
    ap.add_argument('--dest')
    ap.add_argument('--plan')
    ap.add_argument('--inputs', help='directory holding tumap2/, tumig1/ (and trivgen/); default $GAG_SCRATCH_ROOT or ../gagarin-scratch')
    a = ap.parse_args()
    if a.inputs:
        set_inputs(a.inputs)
    check_inputs()
    if a.cmd == 'plan':
        ex = dict(x.split('=', 1) if '=' in x else (x, 'excluded') for x in a.exclude)
        print(json.dumps(plan(a.tree, a.tu, ex, a.dest), indent=1))
    elif a.cmd == 'apply':
        p = json.load(open(a.plan))
        print(json.dumps(apply(a.tree, p, json.load(open(ASSERTS))), indent=1))


if __name__ == '__main__':
    main()

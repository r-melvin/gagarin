#!/usr/bin/env python3
"""Split a gagarin .cpp into preamble, annotated function chunks and interstitial code.

Chunk = the contiguous // comment block holding one or more reccmp FUNCTION-like
annotations at brace depth 0, plus the definition that follows (to the closing
brace at depth 0, or a ';' at depth 0 for declaration-only emitters).
"""
import re, sys
ANN = re.compile(r'^//\s?(FUNCTION|STUB|TEMPLATE|SYNTHETIC):\s*GAMEMD\s+(0x[0-9A-Fa-f]+)')

def depth_scan(lines):
    """Return per-line (depth_at_start, depth_at_end), ignoring comments/strings."""
    out = []; d = 0; inblock = False
    for ln in lines:
        start = d; i = 0; n = len(ln)
        while i < n:
            c = ln[i]
            if inblock:
                if ln.startswith('*/', i): inblock = False; i += 2; continue
                i += 1; continue
            if ln.startswith('//', i): break
            if ln.startswith('/*', i): inblock = True; i += 2; continue
            if c in '"\'':
                q = c; i += 1
                while i < n and ln[i] != q:
                    i += 2 if ln[i] == '\\' else 1
                i += 1; continue
            if c == '{': d += 1
            elif c == '}': d -= 1
            i += 1
        out.append((start, d))
    return out

def is_comment(ln): return ln.lstrip().startswith('//')

def split(text):
    lines = text.split('\n')
    dep = depth_scan(lines)
    chunks = []  # dict(start,end,addrs,kinds)
    i = 0; n = len(lines)
    while i < n:
        m = ANN.match(lines[i])
        if not (m and dep[i][0] == 0):
            i += 1; continue
        # comment block start
        s = i
        while s > 0 and is_comment(lines[s-1]) and dep[s-1][0] == 0:
            s -= 1
        # don't swallow a previous chunk's lines
        if chunks and s < chunks[-1]['end']: s = chunks[-1]['end']
        addrs = []; kinds = []
        j = s
        # gather annotations in the comment run(s), allowing blank lines between stacked annotation blocks
        while j < n and (is_comment(lines[j]) or lines[j].strip() == ''):
            mm = ANN.match(lines[j])
            if mm: addrs.append(int(mm.group(2), 16)); kinds.append(mm.group(1))
            j += 1
        # definition
        k = j; opened = False
        while k < n:
            if dep[k][1] > 0 or (dep[k][0] > 0): opened = True
            if opened and dep[k][1] == 0:
                k += 1; break
            code = re.sub(r'//.*', '', lines[k]).strip()
            if not opened and code.endswith(';') and dep[k][1] == 0:
                k += 1; break
            k += 1
        chunks.append(dict(start=s, end=k, addrs=addrs, kinds=kinds))
        i = k
    # interstitials
    pre_end = chunks[0]['start'] if chunks else n
    inters = []
    prev = pre_end
    for c in chunks:
        if c['start'] > prev:
            inters.append((prev, c['start']))
        prev = c['end']
    if prev < n: inters.append((prev, n))
    return lines, pre_end, chunks, inters

def code_only(lines):
    """Lines that are not blank, comments or preprocessor-free noise."""
    out = []; inblock = False
    for ln in lines:
        t = ln.strip()
        if not t or t.startswith('//'): continue
        out.append(ln)
    return out

if __name__ == '__main__':
    for p in sys.argv[1:]:
        lines, pre_end, chunks, inters = split(open(p, errors='replace').read())
        ic = [(a, b) for a, b in inters if code_only(lines[a:b])]
        print(p, 'pre', pre_end, 'chunks', len(chunks), 'code-interstitials', len(ic))
        for a, b in ic: print('   ', a+1, b, code_only(lines[a:b])[:2])

#!/usr/bin/env python3
"""Greedy fit of one original TU: move as many contributing files as compile together
and stay byte-identical; leave the rest where they are, with the reason.

  fit.py --tree WT --tu TU095 --base-objs DIR --base-manifest FILE --out DIR [--exclude F=why ...]

1. plan (migrate.plan) and order contributors by moved-row count, largest first;
2. initialisers first (alone), then each contributor: accepted if the new TU still compiles
   and the contributor's split remainder (if any) compiles;
3. apply, compile the touched TUs, run the per-function identity check against the base
   objects; a contributor with a differing row is excluded, the change reverted and the fit
   repeated.
Writes OUT/<tu>.fit.json (accepted, skipped with reasons, identity result).
"""
import argparse, json, os, re, subprocess, sys, shutil, tempfile
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import migrate
import initorder

SITES = None   # loaded in main() once the inputs directory is known


def cl(tree, relpath, text, objdir):
    """Compile text as if it were tree/relpath. Returns (ok, log)."""
    d = os.path.join(tree, os.path.dirname(relpath))
    base = os.path.basename(relpath)
    tmpname = '_tumig_%d_%s' % (os.getpid(), base)
    src = os.path.join(d, tmpname)
    open(src, 'w').write(text)
    obj = os.path.join(objdir, tmpname[:-4] + '.obj')
    try:
        r = subprocess.run(['bash', os.path.join(tree, 'scripts/vc6/vc6cl.sh'), '/Fo' + obj, tmpname],
                           cwd=d, capture_output=True, text=True, errors='replace')
        ok = r.returncode == 0 and os.path.exists(obj)
        return ok, r.stdout + r.stderr
    finally:
        os.remove(src)
        if os.path.exists(obj):
            os.remove(obj)


def first_errors(log, n=3):
    return [l.strip() for l in log.split('\n') if ' error ' in l][:n]


# C2371 redefinition; different basic types   C2086 redefinition   C2040 differs in levels of indirection
# C2373 redefinition; different type modifiers   C2374 redefinition; multiple initialization
CONFLICT_CODES = ('C2371', 'C2086', 'C2040', 'C2373', 'C2374')


def conflicts(log):
    """Compiler errors that say two contributors declare one name with different types. They are reported as such:
    the binary decides the type, and the fix is a separate change to the sources, never a silent pick here."""
    return [l.strip() for l in log.split('\n') if any(' error %s' % c in l for c in CONFLICT_CODES)]


def why_failed(prefix, log):
    c = conflicts(log)
    if c:
        return 'TYPE CONFLICT (settle it against the binary first, as its own change): ' + ' | '.join(c[:3])
    return prefix + ' | '.join(first_errors(log))


def trial(tree, p, files, inits, tmp):
    q = dict(p, files=files, inits=inits)
    dtext, rew, _ = migrate.compose(tree, q, SITES)
    ok, log = cl(tree, p['dest'], dtext, tmp)
    return ok, log


def fit(tree, tu, excludes, tmp):
    p = migrate.plan(tree, tu, excludes, None)
    skipped = list(p['skipped'])
    inits = p['inits']
    # an existing destination is rewritten as the merged TU, so it always takes part and is never skipped
    dest = [c for c in p['files'] if c['file'] == p['dest']]
    cands = sorted([c for c in p['files'] if c['file'] != p['dest']], key=lambda f: (-len(f['rows']), f['file']))
    if inits:
        ok, log = trial(tree, p, dest, [], tmp) if dest else (True, '')
        ok2, log2 = trial(tree, p, dest, inits, tmp)
        if not (ok and ok2):
            skipped.append(dict(file='(initialisers)', why=why_failed('do not compile: ', log2 or log)))
            inits = []
    if dest:
        ok, log = trial(tree, p, dest, inits, tmp)
        if not ok:
            skipped.append(dict(file=p['dest'], why=why_failed('existing destination does not compile as the merged TU: ', log)))
            p['files'] = []
            p['inits'] = []
            p['skipped'] = skipped
            return p
    acc = list(dest)
    # fast path: everything at once, when no split remainder is involved
    if all(c['whole'] for c in cands):
        ok, log = trial(tree, p, acc + cands, inits, tmp)
        if ok:
            p['files'] = sorted(acc + cands, key=lambda f: f['file'])
            p['inits'] = inits
            p['skipped'] = skipped
            return p
    for c in cands:
        # remainder of a split file must still compile on its own
        if not c['whole']:
            q = dict(p, files=[c], inits=[])
            _, rew, _ = migrate.compose(tree, q, SITES)
            ok, log = cl(tree, c['file'], rew[c['file']], tmp)
            if not ok:
                skipped.append(dict(file=c['file'], why=why_failed('split remainder does not compile: ', log)))
                continue
        ok, log = trial(tree, p, acc + [c], inits, tmp)
        if ok:
            acc.append(c)
        else:
            skipped.append(dict(file=c['file'], why=why_failed('conflicts in the merged TU: ', log)))
    p['files'] = sorted(acc, key=lambda f: f['file'])
    p['inits'] = inits
    p['skipped'] = skipped
    return p


def git(tree, *a, check=True):
    return subprocess.run(['git', '-C', tree] + list(a), check=check, capture_output=True, text=True).stdout


def revert(tree, res):
    """Undo apply() in the own worktree (explicit paths only)."""
    paths = [res['dest']] + res['deleted'] + res['rewritten'] + ['scripts/data/match_manifest.json', 'scripts/data/symbol_bindings.json']
    # a destination that existed at HEAD (merged into) is restored; a new one is removed
    if subprocess.run(['git', '-C', tree, 'cat-file', '-e', 'HEAD:' + res['dest']], capture_output=True).returncode == 0:
        git(tree, 'checkout', 'HEAD', '--', *paths)
    else:
        git(tree, 'rm', '-q', '--cached', '-f', '--', res['dest'], check=False)
        os.remove(os.path.join(tree, res['dest']))
        git(tree, 'checkout', 'HEAD', '--', *[x for x in paths if x != res['dest']])


def build_one(tree, tu_path, objdir):
    out = os.path.join(objdir, tu_path[:-4] + '.obj')
    os.makedirs(os.path.dirname(out), exist_ok=True)
    r = subprocess.run(['bash', os.path.join(tree, 'scripts/vc6/vc6cl.sh'), '/Fo' + out, os.path.basename(tu_path)],
                       cwd=os.path.join(tree, os.path.dirname(tu_path)), capture_output=True, text=True, errors='replace')
    return r.returncode == 0, r.stdout


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--tree', required=True)
    ap.add_argument('--tu', required=True)
    ap.add_argument('--base-objs', required=True)
    ap.add_argument('--base-manifest', required=True)
    ap.add_argument('--out', required=True)
    ap.add_argument('--exclude', action='append', default=[])
    ap.add_argument('--inputs', help='directory holding tumap2/ and tumig1/ (default $GAG_SCRATCH_ROOT or ../gagarin-scratch)')
    a = ap.parse_args()
    global SITES
    if a.inputs:
        migrate.set_inputs(a.inputs)
    migrate.check_inputs()
    SITES = json.load(open(migrate.ASSERTS))
    tree = os.path.abspath(a.tree)
    dirty = git(tree, 'status', '--porcelain', '--untracked-files=no').strip()
    if dirty:
        raise SystemExit('refusing to run: %s has uncommitted changes to tracked files (a failed fit reverts '
                         'with git checkout, which would discard them). Commit or move them first:\n%s' % (tree, dirty))
    ex = dict(x.split('=', 1) if '=' in x else (x, 'excluded') for x in a.exclude)
    os.makedirs(a.out, exist_ok=True)
    tmp = tempfile.mkdtemp(prefix='tumig_')
    for rnd in range(6):
        p = fit(tree, a.tu, ex, tmp)
        if not p['files'] and not p['inits']:
            json.dump(dict(plan=p, applied=None), open(os.path.join(a.out, a.tu + '.fit.json'), 'w'), indent=1)
            print(a.tu, 'nothing movable')
            return
        res = migrate.apply(tree, p, SITES)
        # compile touched TUs into a scratch object tree and compare with the base objects
        objdir = os.path.join(tmp, 'objs%d' % rnd)
        touched = [res['dest']] + res['rewritten']
        bad = []
        for t in touched:
            ok, log = build_one(tree, t, objdir)
            if not ok:
                bad.append((t, 'compile failed: ' + ' | '.join(first_errors(log))))
        if bad:
            raise SystemExit('unexpected compile failure after apply: %s' % bad)
        # the merge renumbers the TU's _$E initialisers: follow them, in retail order, before comparing
        try:
            renum = initorder.renumber(tree, res['dest'], objdir, a.base_objs, a.base_manifest)
        except initorder.OrderError as e:
            revert(tree, res)
            raise SystemExit('initialiser order of %s differs from retail: %s' % (res['dest'], e))
        if renum:
            print('renumbered %d initialiser rows' % len(renum))
        cur = json.load(open(os.path.join(tree, 'scripts/data/match_manifest.json')))
        tset = set(touched)
        onlyf = os.path.join(tmp, 'only.txt')
        open(onlyf, 'w').write('\n'.join(r2['addr'] for r2 in cur if r2['tu'] in tset))
        r = subprocess.run([sys.executable, os.path.join(os.path.dirname(__file__), 'identity.py'),
                            a.base_objs, objdir, a.base_manifest,
                            os.path.join(tree, 'scripts/data/match_manifest.json'), '--all-touched'] + touched,
                           capture_output=True, text=True,
                           env=dict(os.environ, TUMIG_ONLY=onlyf,
                                    GAG_LAND_DIR=os.path.join(tree, 'scripts/agent_tools/land')))
        print(r.stdout.strip())
        diffs = [l.split() for l in r.stdout.split('\n') if l.strip().startswith('DIFF')]
        mine = diffs
        if r.returncode not in (0, 1) or not re.search(r'^identity: \d+ identical', r.stdout, re.M):
            raise SystemExit('identity did not run (exit %d, no result line); nothing was compared:\n%s'
                             % (r.returncode, r.stderr[-2000:]))
        if not mine:
            git(tree, 'add', '--', res['dest'], 'scripts/data/match_manifest.json', 'scripts/data/symbol_bindings.json', *res['rewritten'])
            git(tree, 'commit', '-q', '-m', 'WIP tumig %s' % a.tu)
            json.dump(dict(plan=p, applied=res, identity=r.stdout), open(os.path.join(a.out, a.tu + '.fit.json'), 'w'), indent=1)
            print(a.tu, 'OK', res['dest'], 'rows', res['moved_rows'], 'inits', res['init_rows'],
                  'skipped', len(p['skipped']))
            shutil.rmtree(tmp, ignore_errors=True)
            return
        revert(tree, res)
        basetu = {int(r2['addr'], 16): r2['tu'] for r2 in json.load(open(a.base_manifest))}
        mine_files = {f['file'] for f in p['files']}
        for d in mine:
            f = basetu.get(int(d[1], 16))
            if f in mine_files:
                ex[f] = 'moved bytes differ at %s (%s)' % (d[1], d[2])
            else:
                raise SystemExit('unattributed identity difference: %s' % d)
        print('round', rnd, 'excluding', [k for k in ex])
    raise SystemExit('no convergence')


if __name__ == '__main__':
    main()

#!/usr/bin/env python3
"""landlib.py: shared helpers for the gagarin landing tools.

Nothing in here edits a tracked file of the repo it is pointed at, except
through the explicit apply helpers used by land_bundle.py on its own scratch
worktree.
"""
import hashlib
import json
import os
import re
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
# The repo these tools ship in: scripts/agent_tools/land -> repo root. In a linked worktree the main
# checkout (toolchain, untracked local files) is the parent of the git common dir.
REPO_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(HERE)))


def _main_checkout(root):
    try:
        cd = subprocess.run(["git", "-C", root, "rev-parse", "--path-format=absolute", "--git-common-dir"],
                            capture_output=True, text=True, check=True).stdout.strip()
        return os.path.dirname(cd) if os.path.basename(cd) == ".git" else root
    except Exception:
        return root


MAIN_REPO = os.environ.get("LAND_MAIN_REPO") or os.environ.get("GAG_MAIN") or _main_checkout(REPO_ROOT)
TOOLCHAIN = os.environ.get("LAND_TOOLCHAIN", MAIN_REPO + "/toolchain")
# The retail image is never shipped or defaulted: set GAMEMD_BINARY (SHA-256 checked by the gates).
BINARY = os.environ.get("GAMEMD_BINARY", "")
CACHE = os.environ.get("LAND_CACHE", os.path.expanduser("~/.cache/gagarin-land"))
# Disk-backed scratch next to the main checkout (never /tmp: RAM-backed, OOM-killable).
SCRATCH_ROOT = os.environ.get("GAG_SCRATCH_ROOT", os.path.join(os.path.dirname(MAIN_REPO), "gagarin-scratch"))
RUNS = os.environ.get("LAND_RUNS", os.path.join(SCRATCH_ROOT, "land-runs"))
MANIFEST = "scripts/data/match_manifest.json"
WORDS_NEVER_MATCH = re.compile(r"(?!x)x")
_WARNED = []


def forbidden_words_path():
    """Local, untracked word list (one regex per line, # comments). Never committed: it names private
    sources. GAG_FORBIDDEN_WORDS, else .coordination/forbidden_words.txt in this repo or the main checkout."""
    cands = [os.environ.get("GAG_FORBIDDEN_WORDS", "")]
    for root in (REPO_ROOT, MAIN_REPO):
        cands.append(os.path.join(root, ".coordination", "forbidden_words.txt"))
    for c in cands:
        if c and os.path.isfile(c):
            return c
    return None


def load_forbid_re():
    p = forbidden_words_path()
    pats = []
    if p:
        for ln in open(p, errors="replace"):
            ln = ln.strip()
            if ln and not ln.startswith("#"):
                pats.append(ln)
    if not pats:
        if not _WARNED:
            _WARNED.append(1)
            print("WARNING: forbidden-word rule DISABLED: no word list found (set GAG_FORBIDDEN_WORDS or create "
                  ".coordination/forbidden_words.txt, one regex per line)", file=sys.stderr)
        return WORDS_NEVER_MATCH
    return re.compile("|".join("(?:%s)" % x for x in pats), re.I)


FORBID_RE = load_forbid_re()
BINDINGS = "scripts/data/symbol_bindings.json"
ALLOWED_PATHS = [r"^match/", r"^scripts/data/[^/]+\.json$", r"^STATUS\.md$", r"^\.github/assets/progress\.svg$"]


def toolenv(extra=None):
    e = dict(os.environ)
    e.setdefault("VC6_ROOT", TOOLCHAIN + "/MSVC600")
    e.setdefault("WINEPREFIX", TOOLCHAIN + "/wineprefix")
    e["GAMEMD_BINARY"] = BINARY
    e.update(extra or {})
    return e


def run(cmd, cwd=None, env=None, log=None, check=False, timeout=None):
    """Run cmd, send stdout+stderr to the log file (never a pipe: Wine children
    can hold a pipe open after cl exits), return (rc, text)."""
    fd, tmp = (None, None)
    if log is None:
        fd, tmp = tempfile.mkstemp(prefix="landrun_")
        out = os.fdopen(fd, "w+b")
    else:
        out = open(log, "wb")
    try:
        p = subprocess.run(cmd, cwd=cwd, env=env or toolenv(), stdout=out,
                           stderr=subprocess.STDOUT, timeout=timeout)
        rc = p.returncode
    except subprocess.TimeoutExpired:
        rc = 124
    out.close()
    path = log or tmp
    text = open(path, errors="replace").read()
    if tmp:
        os.unlink(tmp)
    if check and rc:
        raise RuntimeError("command failed (%d): %s\n%s" % (rc, cmd, text[-2000:]))
    return rc, text


def git(tree, *args, check=True, text=True, input=None):
    p = subprocess.run(["git", "-C", tree, *args], capture_output=True, input=input)
    if check and p.returncode:
        raise RuntimeError("git %s failed: %s" % (" ".join(args), p.stderr.decode(errors="replace")))
    return (p.stdout.decode(errors="replace") if text else p.stdout) if check else p


def sha(b):
    if isinstance(b, str):
        b = b.encode("utf-8", "surrogateescape")
    return hashlib.sha256(b).hexdigest()


def rev_parse(tree, rev):
    return git(tree, "rev-parse", "--verify", rev + "^{commit}").strip()


# ---------------------------------------------------------------- file providers
INCLUDE_ROOTS = ("match", "third_party")      # tracked roots a quoted include may resolve into
VENDORED_PATHS = [r"^third_party/lzo/"]       # upstream text kept as shipped: exempt from the words gate


def _prefixes(prefix):
    return (prefix,) if isinstance(prefix, str) else tuple(prefix)


def word_hits(diff_text, allow=(), vendored=()):
    """Added-line forbidden-word hits of a unified diff -> (hits, n_exempt). Lines in files matching a
    `vendored` regex (upstream text kept as shipped) are counted as exempt, not hits."""
    hits, cur, nvend = [], None, 0
    for ln in diff_text.splitlines():
        if ln.startswith("diff --git "):
            m = re.match(r"diff --git a/(\S+) b/(\S+)", ln)
            cur = m.group(2) if m else None
        elif ln.startswith("+") and not ln.startswith("+++") and FORBID_RE.search(ln) and not any(o.search(ln) for o in allow):
            if cur and any(v.search(cur) for v in vendored):
                nvend += 1
            else:
                hits.append(ln)
    return hits, nvend


class TreeFiles:
    """Tracked (index) files of a working tree, read from the file system."""

    def __init__(self, tree, prefix="match"):
        self.tree = tree
        out = git(tree, "ls-files", "-z", "--", *_prefixes(prefix), text=False)
        self.paths = sorted(p.decode() for p in out.split(b"\0") if p)

    def read(self, path):
        full = os.path.join(self.tree, path)
        if os.path.islink(full):
            raise RuntimeError("tracked symlink input: " + path)
        try:
            with open(full, "rb") as f:
                return f.read()
        except OSError:
            return None


class RevFiles:
    """Files of a git revision, read with one `git cat-file --batch` pass."""

    def __init__(self, tree, rev, prefix="match", extra=()):
        self.tree, self.rev = tree, rev
        out = git(tree, "ls-tree", "-r", "-z", rev, "--", *_prefixes(prefix), *extra, text=False)
        ents = [e for e in out.split(b"\0") if e]
        self.paths, shas = [], []
        for e in ents:
            meta, name = e.split(b"\t", 1)
            mode, typ, osha = meta.split()
            if typ != b"blob":
                continue
            self.paths.append(name.decode())
            shas.append(osha.decode())
        self.paths_sorted = sorted(self.paths)
        self._data = {}
        if shas:
            p = subprocess.run(["git", "-C", tree, "cat-file", "--batch"],
                               input=("\n".join(shas) + "\n").encode(), capture_output=True)
            buf, i = p.stdout, 0
            for name, osha in zip(self.paths, shas):
                nl = buf.index(b"\n", i)
                hdr = buf[i:nl].split()
                size = int(hdr[2])
                self._data[name] = buf[nl + 1:nl + 1 + size]
                i = nl + 1 + size + 1
        self.paths = self.paths_sorted

    def read(self, path):
        return self._data.get(path)


# ---------------------------------------------------------------- include index
INC_RE = re.compile(rb'^[ \t]*#[ \t]*include[ \t]*"([^"\n]+)"', re.M)
SRC_EXT = (".cpp", ".c", ".cxx", ".cc")
HDR_EXT = (".h", ".hpp", ".inl")
FLAG_RE = re.compile(rb'^[ \t]*//[ \t]*VC6FLAGS:[ \t]*(.*?)[ \t]*$', re.M)


def _norm(p):
    return os.path.normpath(p).replace("\\", "/")


class IncludeIndex:
    """Include-dependency index.

    Quoted includes resolve like MSVC: the directory of the including file,
    then the directories of each file that (transitively) included it, nearest
    first. <...> includes are system headers and are ignored. Includes in
    comments or #if 0 are over-approximated (they count as dependencies),
    which can only widen the affected set, never narrow it.
    """

    def __init__(self, files):
        self.files = files
        self.known = set(files.paths)
        self.direct = {}          # path -> [raw include strings]
        self.unresolved = {}      # path -> [raw strings]
        self._closure = {}

    def _includes(self, path):
        if path not in self.direct:
            data = self.files.read(path) or b""
            self.direct[path] = [m.group(1).decode("latin1") for m in INC_RE.finditer(data)]
        return self.direct[path]

    def tus(self):
        # only match/ sources are translation units; vendored sources are reached by include
        return [p for p in self.files.paths if p.endswith(SRC_EXT) and p.startswith("match/")]

    def closure(self, tu):
        """Ordered list of files (TU first) that influence the TU's object."""
        if tu in self._closure:
            return self._closure[tu]
        seen, order = {tu}, [tu]
        stack = [(tu, [os.path.dirname(tu)])]
        unresolved = []
        while stack:
            f, chain = stack.pop()
            for inc in self._includes(f):
                hit = None
                for d in [os.path.dirname(f)] + chain[::-1]:
                    cand = _norm(os.path.join(d, inc))
                    if cand in self.known:
                        hit = cand
                        break
                if hit is None:
                    unresolved.append((f, inc))
                    continue
                if hit not in seen:
                    seen.add(hit)
                    order.append(hit)
                    stack.append((hit, chain + [os.path.dirname(hit)]))
        self._closure[tu] = order
        if unresolved:
            self.unresolved.setdefault(tu, []).extend(unresolved)
        return order

    def flags_marker(self, tu):
        m = FLAG_RE.search(self.files.read(tu) or b"")
        return m.group(1).decode("latin1") if m else ""

    def key(self, tu, salt):
        h = hashlib.sha256()
        h.update(salt.encode())
        h.update(b"\0" + tu.encode() + b"\0" + self.flags_marker(tu).encode())
        for f in sorted(self.closure(tu)):
            h.update(b"\0" + f.encode() + b"\0" + hashlib.sha256(self.files.read(f) or b"").digest())
        return h.hexdigest()

    def dependents(self):
        """header/source -> set of TUs whose closure contains it."""
        rev = {}
        for tu in self.tus():
            for f in self.closure(tu):
                rev.setdefault(f, set()).add(tu)
        return rev

    def all_unresolved(self):
        for tu in self.tus():
            self.closure(tu)
        return self.unresolved


def layout_headers(files):
    return [p for p in files.paths if p.startswith("match/_layout/") and p.endswith(".h")
            and not os.path.basename(p).startswith("_ca_")]


def layout_closure(index, header):
    """Files a layout header drags in when compiled through a throwaway includer in its dir."""
    return index.closure(header)


def toolchain_salt(tree):
    """Everything besides sources that can change an object: compiler binary, wrapper, env flags."""
    cl = os.path.join(toolenv()["VC6_ROOT"], "VC98/Bin/CL.EXE")
    try:
        st = os.stat(cl)
        clid = "%d:%d" % (st.st_size, int(st.st_mtime))
    except OSError:
        clid = "nocl"
    wrap = open(os.path.join(tree, "scripts/vc6/vc6cl.sh"), "rb").read()
    return "|".join([clid, sha(wrap), os.environ.get("VC6_FLAGS", "")])


# ---------------------------------------------------------------- manifest
def load_manifest(path):
    raw = open(path).read()
    return json.loads(raw), raw


def dump_manifest(man):
    # Byte-identical with the tracked file: indent=1, no trailing newline.
    return json.dumps(man, indent=1)


def A(row):
    return int(row["addr"], 16)


def parse_delta(d):
    """Return a list of (op, row, old) from the delta formats seen in packets.

    list of rows: op from row['op'], else 'change' if row has a `_change` key
    or `_op`=='change', else add-or-change decided against the manifest.
    {add, modify, remove}: modify entries are {old_sym, row}.
    Keys starting with '_' and 'op'/'old' are stripped from the written row.
    """
    ops = []
    if isinstance(d, list):
        for r in d:
            op = r.get("op") or ("change" if "_change" in r else None)
            row = {k: v for k, v in r.items() if k not in ("op", "old") and not k.startswith("_")}
            ops.append((op, row, r.get("old")))
    elif isinstance(d, dict):
        ops += [("remove", r, None) for r in d.get("remove", [])]
        ops += [("change", m["row"], {"sym": m.get("old_sym")}) for m in d.get("modify", [])]
        ops += [("add", r, None) for r in d.get("add", [])]
    else:
        raise ValueError("unrecognised manifest delta format")
    return ops


def merge_deltas(man, deltas, sort=False, touched=None):
    """Apply several (name, delta) in order with collision checks.

    Returns (new_manifest, errors, warnings). Errors are collisions: the same address
    added by two packets, an address changed/removed by a packet after another packet
    already modified it differently, explicit add over an existing address, change or
    remove of a missing address, old-symbol mismatch, malformed rows, an op repeated
    for one address within a packet. Nothing is applied when there are errors.
    `touched` may be passed in to carry that state across successive calls (one packet at a time).
    Warnings: a row without an op marker that silently replaces an existing row with a
    different tu or symbol (the landers' apply_delta default: add if new else change).
    """
    man = [dict(r) for r in man]
    errs, warns = [], []
    idx = {A(r): i for i, r in enumerate(man)}
    gone = set()
    touched = {} if touched is None else touched   # addr -> (packet, final row or None for removed); shared across calls
    for name, d in deltas:
        try:
            ops = parse_delta(d)
        except Exception as ex:
            errs.append("%s: %s" % (name, ex))
            continue
        removed_here = {A(r) for op, r, _ in ops if op == "remove"}
        seen = set()
        for op, row, old in ops:
            n0 = len(errs)
            try:
                a = A(row)
            except Exception:
                errs.append("%s: row without a valid addr: %r" % (name, row))
                continue
            for need in ("tu", "sym", "len", "status"):
                if need not in row:
                    errs.append("%s: row %#x missing %s" % (name, a, need))
            implicit = op is None
            if implicit:
                op = "add" if a not in idx else "change"
            if (a, op) in seen:
                errs.append("%s: %s twice for %#x" % (name, op, a))
            seen.add((a, op))
            prev = touched.get(a)
            other = prev is not None and prev[0] != name
            if op == "add" and a in idx and a not in removed_here:
                errs.append("%s: add of present address %#x%s" % (name, a, " (added by " + prev[0] + ")" if other else ""))
            elif op == "add" and other and prev[1] is not None:
                errs.append("%s: address %#x also added by %s" % (name, a, prev[0]))
            if op in ("change", "remove") and a not in idx:
                errs.append("%s: %s of missing address %#x" % (name, op, a))
            if op in ("change", "remove") and other and prev[1] != (row if op == "change" else None):
                errs.append("%s: %s of %#x which %s already modified differently" % (name, op, a, prev[0]))
            if op == "change" and old and a in idx and man[idx[a]]["sym"] != old.get("sym"):
                errs.append("%s: old symbol mismatch at %#x (manifest has %s)" % (name, a, man[idx[a]]["sym"]))
            if implicit and op == "change" and a in idx:
                cur = man[idx[a]]
                if cur.get("tu") != row.get("tu") or cur.get("sym") != row.get("sym"):
                    warns.append("%s: row %#x replaces an existing row (tu/sym differ) without an op/_change marker" % (name, a))
            if len(errs) > n0:
                continue
            if op == "remove":
                gone.add(idx.pop(a))
                touched[a] = (name, None)
            elif op == "change":
                man[idx[a]] = row
                touched[a] = (name, row)
            else:
                man.append(row)
                idx[a] = len(man) - 1
                touched[a] = (name, row)
    if errs:
        return None, errs, warns
    man = [r for i, r in enumerate(man) if i not in gone]
    if len({A(r) for r in man}) != len(man):
        return None, ["duplicate addresses after merge"], warns
    if sort:
        man.sort(key=lambda r: (r["tu"], A(r)))
    return man, [], warns


def manifest_diff(old, new):
    """(added, changed, removed) rows between two manifests, keyed by address."""
    o = {A(r): r for r in old}
    n = {A(r): r for r in new}
    added = [n[a] for a in n if a not in o]
    removed = [o[a] for a in o if a not in n]
    changed = [n[a] for a in n if a in o and n[a] != o[a]]
    return added, changed, removed


# ---------------------------------------------------------------- packet
CODEX_TRAILER = "Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>"


def parse_commit_message(txt):
    m = re.search(r"(?im)^[#*\s]*proposed commit message[^\n]*\n", txt)
    if not m:
        # Codex packets: a single line "Proposed commit: <title>" (title optionally in backticks).
        one = re.search(r"(?im)^[#*\s]*proposed\s*commit\s*:\s*`?([^`\n]+?)`?\s*$", txt)
        if one:
            # a fenced block right after the line is the full message; else the line is the title
            rest = txt[one.end():].lstrip("\n").split("\n")
            if rest and rest[0].startswith("```"):
                blk = []
                for ln in rest[1:]:
                    if ln.startswith("```"):
                        break
                    blk.append(ln)
                body = "\n".join(blk).strip()
                if body.split("\n", 1)[0].strip() == one.group(1).strip():     # block repeats the title line
                    body = body.split("\n", 1)[1].strip() if "\n" in body else ""
                if body:
                    return one.group(1).strip() + "\n\n" + body + ("\n" if "Co-Authored-By:" in body else "\n\n" + CODEX_TRAILER + "\n")
            return one.group(1).strip() + "\n\n" + CODEX_TRAILER + "\n"
        return None
    lines = txt[m.end():].split("\n")
    i = 0
    while i < len(lines) and not lines[i].strip():
        i += 1
    if i >= len(lines):
        return None
    out = []
    if lines[i].startswith("```"):
        for ln in lines[i + 1:]:
            if ln.startswith("```"):
                break
            out.append(ln)
    elif lines[i].startswith(("  ", "\t")):
        blk = []
        for ln in lines[i:]:
            if ln.strip() and not ln.startswith(("  ", "\t")):
                break
            blk.append(ln)
        ind = min((len(x) - len(x.lstrip()) for x in blk if x.strip()), default=0)
        out = [x[ind:] if x.strip() else "" for x in blk]
    else:
        for ln in lines[i:]:
            if re.match(r"^(#+ |---)", ln):
                break
            out.append(ln)
    for j, ln in enumerate(out):
        if ln.startswith("Co-Authored-By:"):
            out = out[:j + 1]
            break
    msg = "\n".join(out).strip()
    return msg + "\n" if msg else None


class Packet:
    """A READY directory: patch.diff, manifest_delta.json, README.md (+ symbol maps)."""

    def __init__(self, path):
        self.dir = os.path.abspath(path)
        self.name = os.path.basename(os.path.dirname(self.dir)) if os.path.basename(self.dir) == "READY" \
            else os.path.basename(self.dir)
        self.name = re.sub(r"^gagarin-", "", self.name)
        self.patch = os.path.join(self.dir, "patch.diff")
        self.delta_path = os.path.join(self.dir, "manifest_delta.json")
        self.readme = os.path.join(self.dir, "README.md")

    def validate(self):
        errs = []
        if not os.path.isfile(self.patch):
            errs.append("no patch.diff")
        if not os.path.isfile(self.delta_path):
            errs.append("no manifest_delta.json")
        if not os.path.isfile(self.readme) and not self.commit_msg_file():
            errs.append("no README.md or commit_msg.txt (commit message source)")
        return errs

    @staticmethod
    def _hexrow(r):
        r = dict(r)
        if isinstance(r.get("addr"), int):
            r["addr"] = "0x%X" % r["addr"]
        if isinstance(r.get("len"), int):
            r["len"] = "0x%x" % r["len"]
        return r

    def delta(self):
        """The manifest delta, normalised: integer addr/len (Codex packets) become the tracked hex
        strings, and manifest_rekeys.json (Codex: whole replacement rows keyed by address, or
        {addr, old_sym, new}) is appended as explicit 'change' ops."""
        d = json.load(open(self.delta_path)) if os.path.isfile(self.delta_path) else []
        if isinstance(d, list):
            d = [self._hexrow(r) if isinstance(r, dict) else r for r in d]
        elif isinstance(d, dict):
            d = dict(d)
            for k in ("add", "remove"):
                d[k] = [self._hexrow(r) for r in d.get(k, [])]
            d["modify"] = [dict(m, row=self._hexrow(m["row"])) for m in d.get("modify", [])]
        rk = os.path.join(self.dir, "manifest_rekeys.json")
        if os.path.isfile(rk):
            extra = []
            for r in json.load(open(rk)):
                row = self._hexrow(r.get("new", r))
                row = {k: v for k, v in row.items() if k not in ("old_sym",)}
                op = {"op": "change"}
                if r.get("old_sym"):
                    op["old"] = {"sym": r["old_sym"]}
                extra.append(dict(row, **op))
            if isinstance(d, list):
                d = d + extra
            else:
                d.setdefault("modify", []).extend({"old_sym": (x.get("old") or {}).get("sym"), "row": {k: v for k, v in x.items() if k not in ("op", "old")}} for x in extra)
        return d

    BINDING_DELTA_NAMES = ("symbol_bindings_delta.json", "binding_delta.json")
    CORRECTIONS_NAME = "binding_corrections.json"

    def binding_corrections(self):
        """(entries, errors) from the packet's binding_corrections.json (see parse_binding_corrections)."""
        return parse_binding_corrections(os.path.join(self.dir, self.CORRECTIONS_NAME))

    def bindings_delta(self):
        """{symbol: address} additions for the central scripts/data/symbol_bindings.json, from
        symbol_bindings_delta.json or binding_delta.json (Codex) and from lines the packet's patch.diff
        appends to the central file itself. Contradictions (same symbol, two addresses; a patch hunk
        changing an existing entry) are listed in self.binding_conflicts; callers refuse on them.
        Returns {} when there is nothing."""
        self.binding_conflicts = []
        out = {}
        corr = {c["symbol"]: c for c in self.binding_corrections()[0]}

        def put(k, v, src):
            v = "0x%08X" % (v if isinstance(v, int) else int(v, 16))
            if k in out and out[k] != v:
                self.binding_conflicts.append("%s: %s in %s, %s elsewhere in the packet" % (k, v, src, out[k]))
            else:
                out[k] = v
        for n in self.BINDING_DELTA_NAMES:
            p = os.path.join(self.dir, n)
            if not os.path.isfile(p):
                continue
            d = json.load(open(p))
            if isinstance(d, dict) and isinstance(d.get("add"), dict):
                d = d["add"]
            for k, v in d.items():
                if isinstance(v, (str, int)):
                    put(k, v, n)
        for k, c in corr.items():
            put(k, c["new_addr"], self.CORRECTIONS_NAME)
        added, removed = self.patch_bindings()
        for k, v in removed.items():
            if k in corr and v == corr[k]["old_addr"] and added.get(k) == corr[k]["new_addr"]:
                continue        # the patch hunk is exactly the sanctioned correction
            if k not in added or added[k] != v:
                self.binding_conflicts.append("%s: patch.diff changes or removes the existing central entry %s" % (k, v))
        for k, v in added.items():
            if k in corr and v == corr[k]["new_addr"]:
                continue
            if removed.get(k) != v:       # a re-added unchanged line (comma fix-up) is formatting only
                put(k, v, "patch.diff")
        return out

    def patch_bindings(self):
        """(added, removed) {symbol: address} from the hunks patch.diff holds for scripts/data/symbol_bindings.json."""
        added, removed = {}, {}
        if not os.path.isfile(self.patch):
            return added, removed
        cur = None
        ent = re.compile(r'^\s*"([^"]+)"\s*:\s*"?(0x[0-9A-Fa-f]+|\d+)"?\s*,?\s*$')
        for ln in open(self.patch, errors="replace").read().split("\n"):
            if ln.startswith("diff --git "):
                m = re.match(r"diff --git a/(\S+) b/(\S+)", ln)
                cur = m.group(2) if m else None
            elif cur == BINDINGS and ln[:1] in "+-" and not ln.startswith(("+++", "---")):
                m = ent.match(ln[1:])
                if m:
                    v = m.group(2)
                    (added if ln[0] == "+" else removed)[m.group(1)] = "0x%08X" % (int(v, 16) if v.lower().startswith("0x") else int(v))
        return added, removed

    def patch_files(self):
        out = subprocess.run(["git", "apply", "--numstat", "-z", self.patch],
                             capture_output=True)
        if out.returncode:
            # --numstat -z is awkward with renames; fall back to diff headers
            names = re.findall(r"^diff --git a/(\S+) b/(\S+)$",
                               open(self.patch, errors="replace").read(), re.M)
            return sorted({b for _, b in names})
        files = []
        for rec in out.stdout.split(b"\0"):
            if rec:
                files.append(rec.split(b"\t", 2)[-1].decode())
        return sorted(set(files))

    def commit_msg_file(self):
        for fn in ("commit_msg.txt", "COMMIT_MSG.txt"):
            p = os.path.join(self.dir, fn)
            if os.path.isfile(p) and open(p, errors="replace").read().strip():
                return p
        return None

    def base_sha(self):
        """Base revision: a base_sha / BASE_SHA (.txt) file (any case), else a README line
        'Base <sha>' ('Base: `<sha>`', 'base sha = <sha>', 'Base<sha>'), else any 'base ... <sha>'."""
        try:
            names = sorted(os.listdir(self.dir))
        except OSError:
            names = []
        for n in names:
            if re.fullmatch(r"(?i)base_sha(\.txt)?", n) and os.path.isfile(os.path.join(self.dir, n)):
                m = re.search(r"(?<![0-9a-fA-F])([0-9a-fA-F]{7,40})(?![0-9a-fA-F])", open(os.path.join(self.dir, n), errors="replace").read())
                if m:
                    return m.group(1).lower()
        txt = open(self.readme, errors="replace").read() if os.path.isfile(self.readme) else ""
        m = re.search(r"(?im)^[\s#*>`_-]*base(?:[\s_]*(?:sha|rev|revision|commit))?[\s:=`*_]*([0-9a-f]{7,40})\b", txt)
        if not m:
            m = re.search(r"(?i)\bbase\b[^\n]{0,30}?(?<![0-9a-f])([0-9a-f]{7,40})\b", txt)
        return m.group(1).lower() if m else None

    def commit_message(self):
        """Commit message: commit_msg.txt, else the block after 'Proposed commit message' (or the
        'Proposed commit:' line/block) in README.md.

        Accepted layouts: a fenced block, an indented block (2+ spaces or a tab, any
        depth) or plain paragraphs up to the next heading. The message ends after its
        first Co-Authored-By line when it has one.
        """
        p = self.commit_msg_file()
        if p:
            return open(p).read().strip() + "\n"
        if not os.path.isfile(self.readme):
            return None
        return parse_commit_message(open(self.readme, errors="replace").read())

    def symbol_map_files(self):
        """Every symbol_map*/symmap*/map_* JSON file under the packet dir that is a {symbol: address} object."""
        out = []
        for root, _, names in os.walk(self.dir):
            for n in sorted(names):
                if re.match(r"(symbol_map|symmap|map_|symbol_bindings_delta|binding_delta)[^/]*\.json$", n):
                    p = os.path.join(root, n)
                    try:
                        d = json.load(open(p))
                    except Exception:
                        continue
                    if isinstance(d, dict) and d and all(isinstance(v, (str, int)) for v in d.values()):
                        out.append(p)
        return out

    def allowed_words(self):
        """words_ok.txt in the packet: one regex per line for added lines the word check should ignore."""
        p = os.path.join(self.dir, "words_ok.txt")
        if not os.path.isfile(p):
            return []
        return [x.rstrip("\n") for x in open(p) if x.strip() and not x.startswith("#")]

    def waived_strict(self):
        p = os.path.join(self.dir, "waive_strict.txt")
        if not os.path.isfile(p):
            return set()
        return {int(x.split()[0], 16) for x in open(p) if x.strip() and not x.startswith("#")}


def norm_addr(v):
    return "0x%08X" % (v if isinstance(v, int) else int(v, 16))


def parse_binding_corrections(path):
    """Read a packet's binding_corrections.json: a list of {symbol, old_addr, new_addr, evidence}.
    Returns (entries, errors); entries carry normalised 0x%08X addresses. Shape only; whether old_addr
    matches the central file is checked where the central file is at hand (merge_bindings, pktlint)."""
    if not os.path.isfile(path):
        return [], []
    try:
        d = json.load(open(path))
    except Exception as ex:
        return [], ["binding_corrections.json unreadable: %s" % ex]
    if isinstance(d, dict) and isinstance(d.get("corrections"), list):
        d = d["corrections"]
    if not isinstance(d, list):
        return [], ["binding_corrections.json must be a list of {symbol, old_addr, new_addr, evidence}"]
    out, errs, seen = [], [], set()
    for i, e in enumerate(d):
        if not isinstance(e, dict):
            errs.append("binding_corrections.json[%d]: not an object" % i)
            continue
        sym = e.get("symbol")
        bad = False
        if not isinstance(sym, str) or not sym:
            errs.append("binding_corrections.json[%d]: missing 'symbol'" % i)
            bad = True
        addrs = {}
        for f in ("old_addr", "new_addr"):
            try:
                if isinstance(e.get(f), bool):
                    raise ValueError
                addrs[f] = norm_addr(e[f])
            except Exception:
                errs.append("binding_corrections.json[%d] (%s): '%s' missing or not an address" % (i, sym, f))
                bad = True
        ev = e.get("evidence")
        if not isinstance(ev, str) or not ev.strip():
            errs.append("binding_corrections.json[%d] (%s): 'evidence' is empty (say why the central address is wrong)" % (i, sym))
            bad = True
        if bad:
            continue
        if addrs["old_addr"] == addrs["new_addr"]:
            errs.append("binding_corrections.json[%d] (%s): old_addr equals new_addr" % (i, sym))
            continue
        if sym in seen:
            errs.append("binding_corrections.json[%d]: duplicate symbol %s" % (i, sym))
            continue
        seen.add(sym)
        out.append(dict(symbol=sym, old_addr=addrs["old_addr"], new_addr=addrs["new_addr"], evidence=ev.strip()))
    return out, errs


def merge_bindings(tree, add, corrections=()):
    """Merge {symbol: address} into TREE's central bindings file in its tracked format
    (sorted keys, 0x%08X, indent=1). Returns (added, conflicts); nothing is written on a conflict.
    CORRECTIONS (parse_binding_corrections entries) are the one sanctioned way to change an existing
    entry: each applies only when the central value still equals its old_addr; they count in `added`."""
    p = os.path.join(tree, BINDINGS)
    corr = {c["symbol"]: c for c in corrections}
    if (not add and not corr) or not os.path.isfile(p):
        return 0, []
    raw = open(p).read()
    cur = json.loads(raw)
    n, bad = 0, []
    for k, c in corr.items():
        if k not in cur:
            bad.append("%s: correction names a symbol absent from the central bindings" % k)
        elif cur[k] != c["old_addr"]:
            bad.append("%s: correction expects central %s, central is %s" % (k, c["old_addr"], cur[k]))
        else:
            cur[k] = c["new_addr"]
            n += 1
    for k, v in add.items():
        if k.startswith("$L"):
            continue
        v = norm_addr(v)
        if k in corr:
            if v != corr[k]["new_addr"]:
                bad.append("%s: packet %s contradicts its own correction to %s" % (k, v, corr[k]["new_addr"]))
        elif k in cur and cur[k] != v:
            bad.append("%s: central %s, packet %s" % (k, cur[k], v))
        elif k not in cur:
            cur[k] = v
            n += 1
    if bad:
        return 0, bad
    open(p, "w").write(json.dumps(dict(sorted(cur.items())), indent=1) + ("\n" if raw.endswith("\n") else ""))
    return n, []

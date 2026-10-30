#!/usr/bin/env python3
"""dlib.py: shared model for the delivery tools (pktlint, pktrebase, batchland, pkt).

Everything here reads; the only writers are pktrebase/batchland on scratch worktrees
they created themselves. Reuses the proven pieces of the sibling tools:
land/landlib.py (packets, manifest deltas, include index, git), tumigrate/cppsplit.py
and migrate.py (annotated-chunk splitting and preamble hoisting), common.py/ctx.py
(pinned PE, objdump, CFG-closed spans) and trivgen/pe_imports.py (retail IAT).
"""
import json
import os
import re
import struct
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
TOOLS = os.path.dirname(HERE)
for sub in ("land", "tumigrate", "trivgen", ""):
    p = os.path.join(TOOLS, sub) if sub else TOOLS
    if p not in sys.path:
        sys.path.insert(0, p)
import landlib as L  # noqa: E402
import cppsplit  # noqa: E402
import migrate  # noqa: E402

MAIN_REPO = L.MAIN_REPO
MANIFEST = L.MANIFEST
BACKUPS = os.environ.get("GAG_BACKUPS", os.path.join(os.path.dirname(L.MAIN_REPO), "backups", "int-evidence"))
# Disk-backed scratch (never /tmp: it can be RAM-backed and the OOM killer ends sessions). Worktrees, objects and run logs of these tools go here.
SCRATCH = os.environ.get("GAG_SCRATCH", os.path.join(L.SCRATCH_ROOT, "delivery"))
os.makedirs(SCRATCH, exist_ok=True)
os.environ.setdefault("LAND_RUNS", os.path.join(SCRATCH, "runs"))
L.RUNS = os.environ["LAND_RUNS"]
MAX_JOBS = int(os.environ.get("GAG_JOBS", "4"))
# Static-initialiser rows: standalone initialiser files are the structural fake the
# user rejected (standing directions, TRIVGEN); they land with the TU migration only.
INIT_DELTA_CANDIDATES = [
    os.environ.get("GAG_INIT_DELTA", ""),
    os.path.join(L.SCRATCH_ROOT, "trivgen/READY/manifest_delta_initialisers.json"),
    os.path.join(BACKUPS, "w6-trivgen/READY/manifest_delta_initialisers.json"),
]
# Central bindings (fu-symmap). Tracked once the packet lands; the READY copy serves until then.
BINDINGS_CANDIDATES = [
    os.environ.get("GAG_BINDINGS", ""),
    "scripts/data/symbol_bindings.json",                # relative to the tree under test
    os.path.join(L.SCRATCH_ROOT, "fu-symmap/READY/symbol_bindings.json"),
    os.path.join(BACKUPS, "fu-symmap/READY/symbol_bindings.json"),
]

ANN = re.compile(r"^//\s?(FUNCTION|STUB|TEMPLATE|SYNTHETIC|LIBRARY):\s*GAMEMD\s+(0x[0-9A-Fa-f]+)(.*)$")
CLAIM = re.compile(r"(?m)^// (?:FUNCTION|SYNTHETIC|TEMPLATE): GAMEMD (0x[0-9A-Fa-f]+)(.*)$")
TU_WINDOW = re.compile(r"Original translation unit (\S+)\..*?code range \((0x[0-9a-fA-F]+)-(0x[0-9a-fA-F]+)\)", re.S)
CLASS_DEF = re.compile(r"^[ \t]*(?:template\s*<[^>]*>\s*)?(class|struct)\s+(?:__declspec\([^)]*\)\s+)?([A-Za-z_]\w*)\b([^;{]*)\{", re.M)
DECL_CONT = re.compile(r"^\s*//\s*\(\s*decl\b")


def is_decl_marker(rest, nxt):
    """A claim marker is a declaration, not a body, when 'decl;' is on its line or its
    '(decl; reloc)' parenthetical continues on the next line."""
    return "decl;" in rest or bool(nxt is not None and DECL_CONT.match(nxt))


def body_claims(text):
    """[(addr, 1-based line)] of column-zero FUNCTION/SYNTHETIC/TEMPLATE body claims."""
    lines = text.split("\n")
    out = []
    for i, ln in enumerate(lines):
        m = CLAIM.match(ln)
        if m and not is_decl_marker(m.group(2), lines[i + 1] if i + 1 < len(lines) else None):
            out.append((int(m.group(1), 16), i + 1))
    return out


CLASS_FWD = re.compile(r"^[ \t]*(class|struct)\s+([A-Za-z_]\w*)\s*;", re.M)
FORBID_RE = L.FORBID_RE
# Steering constructs ruled out by AGENTS.md; see the rule text there.
STEER = [
    ("inline-asm", re.compile(r"\b__asm\b|\b_asm\b")),
    ("naked", re.compile(r"__declspec\s*\(\s*naked\s*\)")),
    ("pragma-optimize", re.compile(r"#\s*pragma\s+optimize")),
    ("const-condition", re.compile(r"\bif\s*\(\s*(1|0|true|false)\s*\)|\bwhile\s*\(\s*0\s*\)")),
    ("volatile", re.compile(r"\bvolatile\b")),
]
VOLATILE_EVIDENCE = re.compile(r"CreateThread|thread|callback|timer|critical section|timeSetEvent|waveOut|IDirectSound", re.I)


def parse_delta(d):
    """landlib.parse_delta plus the re-key form {addr:int, old_sym, new:{row}} (fu-classfix2):
    returns [(op, row, old)] with op in add/change/remove/None."""
    if isinstance(d, list) and any(isinstance(r, dict) and "new" in r and "old_sym" in r for r in d):
        out = []
        for r in d:
            if "new" in r and "old_sym" in r:
                out.append(("change", dict(r["new"]), {"sym": r["old_sym"]}))
            else:
                out += L.parse_delta([r])
        return out
    return L.parse_delta(d)


def normalise_delta(d):
    """Re-key/explicit forms -> plain list of rows with op/old markers (what landlib merges)."""
    out = []
    for op, row, old in parse_delta(d):
        r = dict(row)
        if op:
            r["op"] = op
        if old and old.get("sym"):
            r["old"] = {"sym": old["sym"]}
        out.append(r)
    return out


# ---------------------------------------------------------------- created-path ledger
# Rule (incident 2026-10-22): a tool removes ONLY what it created. Every worktree and scratch
# directory made here is recorded in LEDGER; remove_worktree/remove_dir refuse anything else
# and never prune, sweep or --force a path they did not make.
LEDGER = os.path.join(SCRATCH, ".created_paths")


def _ledger():
    try:
        return {l.rstrip("\n") for l in open(LEDGER) if l.strip()}
    except OSError:
        return set()


def register_created(path):
    path = os.path.abspath(path)
    with open(LEDGER, "a") as f:
        f.write(path + "\n")
    return path


def created_by_us(path):
    return os.path.abspath(path) in _ledger()


class NotOursError(RuntimeError):
    pass


def scratch_dir(prefix):
    import tempfile
    return register_created(tempfile.mkdtemp(prefix=prefix, dir=SCRATCH))


def add_worktree(repo, path, rev, toolchain=True):
    """git worktree add --detach at PATH (which must not exist), recorded in the ledger."""
    path = os.path.abspath(path)
    if os.path.lexists(path):
        raise NotOursError("refusing to create a worktree over an existing path: " + path)
    L.git(repo, "worktree", "add", "--detach", "-q", path, rev)
    register_created(path)
    if toolchain:
        os.symlink(L.TOOLCHAIN, os.path.join(path, "toolchain"))
    return path


def remove_worktree(repo, path):
    """Remove a worktree this process family created; refuse (and report) anything else."""
    path = os.path.abspath(path)
    if not created_by_us(path):
        raise NotOursError("refusing to remove a worktree not in the created-list: " + path)
    tl = os.path.join(path, "toolchain")
    if os.path.islink(tl):
        os.unlink(tl)
    L.git(repo, "worktree", "remove", "--force", path, check=False)
    if os.path.isdir(path):
        import shutil
        shutil.rmtree(path, ignore_errors=True)


def remove_dir(path):
    import shutil
    path = os.path.abspath(path)
    if not created_by_us(path):
        raise NotOursError("refusing to remove a directory not in the created-list: " + path)
    shutil.rmtree(path, ignore_errors=True)


def hx(a):
    return int(a, 16) if isinstance(a, str) else int(a)


def read_json(path):
    with open(path) as f:
        return json.load(f)


def first_existing(cands, root=None):
    for c in cands:
        if not c:
            continue
        p = c if os.path.isabs(c) or root is None else os.path.join(root, c)
        if os.path.isfile(p):
            return p
    return None


# ---------------------------------------------------------------- patch parsing
class FileDiff:
    """One `diff --git` block of a patch."""

    def __init__(self, text):
        self.text = text
        m = re.match(r"diff --git a/(\S+) b/(\S+)", text)
        self.old, self.new = m.group(1), m.group(2)
        self.is_new = bool(re.search(r"^new file mode", text, re.M)) or "\n--- /dev/null" in text
        self.is_delete = bool(re.search(r"^deleted file mode", text, re.M)) or "\n+++ /dev/null" in text
        self.mode_symlink = bool(re.search(r"^(new|old|deleted file) mode 120000", text, re.M))
        self.path = self.old if self.is_delete else self.new

    def added_lines(self):
        """[(hunk_new_lineno, text)] of added lines."""
        out, ln = [], 0
        for line in self.text.split("\n"):
            if line.startswith("@@"):
                m = re.match(r"@@ -\d+(?:,\d+)? \+(\d+)", line)
                ln = int(m.group(1)) if m else 0
                continue
            if line.startswith("+++") or line.startswith("---") and not out and ln == 0:
                continue
            if line.startswith("+"):
                out.append((ln, line[1:]))
                ln += 1
            elif line.startswith("-"):
                continue
            elif line.startswith(("diff ", "index ", "new file", "deleted file", "similarity", "rename ", "old mode", "new mode", "\\")):
                continue
            else:
                ln += 1
        return out

    def new_content(self):
        """Full content of a newly created file (None for modifications)."""
        if not self.is_new:
            return None
        return "\n".join(t for _, t in self.added_lines())


def _plain_path(hdr):
    """Path from a `--- X` / `+++ X` header line body (timestamp dropped, a/ b/ prefix stripped)."""
    p = hdr.split("\t")[0].strip()
    if p == "/dev/null":
        return p
    return p[2:] if p[:2] in ("a/", "b/") else p


def _split_plain(text):
    """Split a plain `diff -u` patch (no `diff --git` headers) into FileDiffs by synthesising the git header."""
    lines = text.split("\n")
    starts = [i for i in range(len(lines) - 1) if lines[i].startswith("--- ") and lines[i + 1].startswith("+++ ")]
    out = []
    for n, i in enumerate(starts):
        end = starts[n + 1] if n + 1 < len(starts) else len(lines)
        old, new = _plain_path(lines[i][4:]), _plain_path(lines[i + 1][4:])
        path = new if new != "/dev/null" else old
        head = "diff --git a/%s b/%s\n" % (old if old != "/dev/null" else path, path)
        if old == "/dev/null":
            head += "new file mode 100644\n"
        elif new == "/dev/null":
            head += "deleted file mode 100644\n"
        out.append(FileDiff(head + "\n".join(lines[i:end]).rstrip("\n") + "\n"))
    return out


def split_patch(text):
    """Split a patch into per-file FileDiffs. Accepts `diff --git` patches and plain unified diffs
    (---/+++ headers only); raises ValueError for a non-blank text that yields no files."""
    parts = re.split(r"(?m)^(?=diff --git )", text)
    out = [FileDiff(p) for p in parts if p.startswith("diff --git ")]
    if not out:
        out = _split_plain(text)
    if not out and text.strip():
        raise ValueError("patch text is not empty but contains no recognisable file diffs "
                         "(expected `diff --git` blocks or ---/+++ unified headers)")
    return out


# ---------------------------------------------------------------- tree model
class Tree:
    """A tracked tree at a worktree path (index contents) or at a revision."""

    def __init__(self, repo, rev=None):
        self.repo = os.path.abspath(repo)
        self.rev = rev
        if rev is None:
            self.files = L.TreeFiles(self.repo)
            raw = open(os.path.join(self.repo, MANIFEST)).read()
        else:
            self.rev = L.rev_parse(self.repo, rev)
            self.files = L.RevFiles(self.repo, self.rev)
            raw = L.git(self.repo, "show", "%s:%s" % (self.rev, MANIFEST))
        self.manifest = json.loads(raw)
        self.by_addr = {hx(r["addr"]): r for r in self.manifest}
        # every tracked path (existence checks); class/claim scans stay within match/
        if rev is None:
            allp = L.git(self.repo, "ls-files", "-z", text=False)
        else:
            allp = L.git(self.repo, "ls-tree", "-r", "-z", "--name-only", self.rev, text=False)
        self.paths = {p.decode() for p in allp.split(b"\0") if p}
        self._windows = self._classes = self._claims = None

    def read(self, path):
        return self.files.read(path)

    def text(self, path):
        b = self.read(path)
        return b.decode("utf-8", "replace") if b is not None else None

    def cpps(self):
        return [p for p in self.files.paths if p.endswith(L.SRC_EXT)]

    def headers(self):
        return [p for p in self.files.paths if p.endswith(L.HDR_EXT)]

    # migrated original TUs: file -> (name, lo, hi)
    def tu_windows(self):
        if self._windows is None:
            w = {}
            for p in self.cpps():
                head = (self.read(p) or b"")[:1200].decode("latin1")
                if "Original translation unit" not in head:
                    continue
                m = TU_WINDOW.search(head)
                if m:
                    w[p] = (m.group(1), int(m.group(2), 16), int(m.group(3), 16))
            self._windows = w
        return self._windows

    def tu_for_addr(self, a):
        """The migrated TU file whose proven code range holds address a, if any."""
        for p, (name, lo, hi) in self.tu_windows().items():
            if lo <= a <= hi:
                return p
        return None

    # class definitions: name -> [(path, keyword)]
    def class_defs(self):
        if self._classes is None:
            d = {}
            for p in self.files.paths:
                if not p.endswith(L.HDR_EXT + L.SRC_EXT):
                    continue
                for m in CLASS_DEF.finditer(self.text(p) or ""):
                    d.setdefault(m.group(2), []).append((p, m.group(1)))
            self._classes = d
        return self._classes

    def canonical_classes(self):
        """Classes with a canonical header: defined under match/_layout/ or in a header
        that carries an RTTI TypeDescriptor block (hcfix convention)."""
        out = {}
        for name, defs in self.class_defs().items():
            for p, kw in defs:
                if not p.endswith(L.HDR_EXT):
                    continue
                if p.startswith("match/_layout/") or b"TypeDescriptor 0x" in (self.read(p) or b""):
                    out.setdefault(name, []).append(p)
        return out

    def claims(self):
        """addr -> [paths] of body claims in .cpp/.c (check_duplicates semantics)."""
        if self._claims is None:
            d = {}
            for p in self.cpps():
                for a, _ in body_claims(self.text(p) or ""):
                    d.setdefault(a, []).append(p)
            self._claims = d
        return self._claims


# ---------------------------------------------------------------- data sets
def init_addresses():
    p = first_existing(INIT_DELTA_CANDIDATES)
    if not p:
        return set(), None
    return {hx(r["addr"]) for r in read_json(p)}, p


def rtti_kinds(repo):
    """class name -> 'class'|'struct' from scripts/data/rtti_classes.json (.?AV / .?AU)."""
    p = os.path.join(repo, "scripts/data/rtti_classes.json")
    if not os.path.isfile(p):
        return {}
    out = {}
    for mangled in read_json(p)["classes"]:
        m = re.match(r"\.\?A([UV])(\w+)@", mangled)
        if m and "@" not in mangled[len(m.group(0)):-2]:   # top-level names only
            out[m.group(2)] = "class" if m.group(1) == "V" else "struct"
    return out


def retail_bytes(va, n):
    """n retail bytes at VA from the pinned PE (None if not file-backed)."""
    try:
        import common
        return common.pe().read(va, n)
    except Exception:
        return None


def cfg_span(addr):
    """CFG-closed span from the pinned PE (ctx.py), with the extent-audit override."""
    import ctx  # lazy: needs the PE and the ghidra function cache
    au = ctx.audit_extent(addr)
    if au:
        return au[0], au[1]
    return ctx.cfg_extent(addr)


# ---------------------------------------------------------------- per-TU guard symbols
GUARD_SYM = re.compile(r"(?:^|::)(_?\$[SE]\d+)$")


def guard_key_problem(key):
    """Why a rekey / packet-map key naming a per-TU guard or atexit symbol (_$S<n>, _$E<n>) cannot work, else None.
    Such names repeat in every TU: an unscoped key is not a usable binding, and a scoped 'tu::sym' key is
    honoured only from the central scripts/data/symbol_bindings.json (verify_relocations._scoped), never
    from a packet map or a rekey file."""
    m = GUARD_SYM.search(key) if isinstance(key, str) else None
    if not m:
        return None
    if "::" in key:
        return "scoped guard key %s is honoured only from the central symbol_bindings.json" % key
    return "per-TU guard symbol %s is ignored unless scoped as 'tu::%s' in the central symbol_bindings.json" % (key, m.group(1))


# ---------------------------------------------------------------- COFF symbols
def coff_symbols(obj):
    """[(name, section, value, storage_class)] of an i386 COFF object."""
    d = open(obj, "rb").read()
    nsec, symptr, nsyms = struct.unpack("<H", d[2:4])[0], struct.unpack("<I", d[8:12])[0], struct.unpack("<I", d[12:16])[0]
    strtab = symptr + nsyms * 18
    out, i = [], 0
    while i < nsyms:
        e = d[symptr + i * 18: symptr + i * 18 + 18]
        if e[:4] == b"\0\0\0\0":
            off = struct.unpack("<I", e[4:8])[0]
            name = d[strtab + off: d.index(b"\0", strtab + off)].decode("latin1")
        else:
            name = e[:8].rstrip(b"\0").decode("latin1")
        value, section, _, scl, naux = struct.unpack("<IhHBB", e[8:18])
        out.append((name, section, value, scl))
        i += 1 + naux
    return out


def defined_names(obj):
    return {n for n, sec, v, scl in coff_symbols(obj) if sec > 0 and scl in (2, 3)}


# ---------------------------------------------------------------- symbol derivation
IMP_RE = re.compile(r"^__imp__?(\w+?)(?:@\d+)?$")
DAT_RE = re.compile(r"DAT_0*([0-9A-Fa-f]{6,8})")
FUN_RE = re.compile(r"(?:\?|^_?)FUN_0*([0-9A-Fa-f]{6,8})(?:@|$)")
NAMED_RE = re.compile(r"_0*([0-9A-F]{8})(?:@|$|_)")


def iat_by_name():
    try:
        import pe_imports
        return {name: va for va, (dll, name) in pe_imports.iat().items()}
    except Exception:
        return {}


def derive_binding(sym, iat=None):
    """Retail VA a symbol name itself attests (FUN_/DAT_/Obj_... address in the name,
    or an import through the retail IAT). The strict verifier still checks the
    relocation field against it, so a wrong derivation fails, never passes."""
    m = IMP_RE.match(sym)
    if m:
        return (iat or {}).get(m.group(1))
    m = FUN_RE.search(sym) or DAT_RE.search(sym)
    if m:
        return int(m.group(1), 16)
    if sym.startswith("?") and (m := NAMED_RE.search(sym.split("@@")[0])):
        # ?Reset@Obj_007B4620@@...: the receiver carries its own address, not the method's.
        return None
    return None


def label_bindings(obj, manifest_rows):
    """$L labels of a COFF object bound by position: row function VA + label offset,
    for labels in the same section as a row's function symbol (lander's lbind.py)."""
    syms = coff_symbols(obj)
    fn_by_sec = {}
    rows = {r["sym"]: hx(r["addr"]) for r in manifest_rows}
    for name, sec, val, scl in syms:
        if name in rows and val == 0 and sec > 0:
            fn_by_sec[sec] = rows[name]
    out = {}
    for name, sec, val, scl in syms:
        if name.startswith("$L") and sec in fn_by_sec:
            out[name] = "0x%X" % (fn_by_sec[sec] + val)
    return out


# ---------------------------------------------------------------- compile / score
def toolenv():
    return L.toolenv()


def compile_tu(tree, tu, obj, log=None):
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    if os.path.exists(obj):
        os.unlink(obj)
    rc, text = L.run(["bash", os.path.join(tree, "scripts/vc6/vc6cl.sh"), "/Fo" + obj, os.path.basename(tu)],
                     cwd=os.path.join(tree, os.path.dirname(tu)), env=toolenv(), log=log)
    text = "\n".join(l for l in text.splitlines() if not re.search(r"libEGL|pci id|dri2|wineusb|fixme:", l, re.I))
    return (rc == 0 and os.path.isfile(obj)), text


def raw_match(tree, obj, row):
    p = subprocess.run([sys.executable, "scripts/vc6/raw_match.py", "--obj", obj, "--sym", row["sym"],
                        "--addr", row["addr"], "--len", row["len"]], cwd=tree, env=toolenv(), capture_output=True, text=True)
    return p.returncode == 0 and "match: 100.0%" in p.stdout, (p.stdout + p.stderr).strip()


def diff_retail_pct(tree, obj, row):
    p = subprocess.run([sys.executable, "scripts/vc6/diff_retail.py", "--obj", obj, "--sym", row["sym"],
                        "--addr", row["addr"], "--len", row["len"]], cwd=tree, env=toolenv(), capture_output=True, text=True)
    m = re.findall(r"^match: ([0-9.]+)%", p.stdout, re.M)
    return (float(m[-1]) if m else None), (p.stdout + p.stderr)


def strict(tree, obj, row, mapfile, manifest=None):
    cmd = [sys.executable, "scripts/vc6/verify_relocations.py", "--obj", obj, "--sym", row["sym"], "--addr", row["addr"],
           "--len", row["len"], "--binary", L.BINARY, "--manifest", manifest or MANIFEST, "--json"]
    if mapfile:
        cmd += ["--symbol-map", mapfile]
    p = subprocess.run(cmd, cwd=tree, env=toolenv(), capture_output=True, text=True)
    text = p.stdout + p.stderr
    m = re.search(r"target (\S+) has no unique", text)
    return p.returncode == 0, (m.group(1) if m else None), text.strip()


def merge_maps(files):
    """Merge {sym: va} JSON maps; entries that disagree are dropped (strict retries singly)."""
    merged, clash = {}, set()
    for f in files:
        d = read_json(f) if isinstance(f, str) else f
        if not isinstance(d, dict):
            continue
        for k, v in d.items():
            if not isinstance(v, (str, int)):
                continue
            if k in merged and hx(str(merged[k])) != hx(str(v)):
                clash.add(k)
            merged.setdefault(k, v)
    for k in clash:
        merged.pop(k, None)
    return merged, clash


# ---------------------------------------------------------------- chunk split
def split(text):
    """cppsplit.split with one fix: a definition whose body opens and closes on one line
    (`void f() {}`) ends there instead of swallowing the rest of the file."""
    lines = text.split("\n")
    dep = cppsplit.depth_scan(lines)
    chunks, i, n = [], 0, len(lines)
    while i < n:
        m = cppsplit.ANN.match(lines[i])
        if not (m and dep[i][0] == 0):
            i += 1
            continue
        s = i
        while s > 0 and cppsplit.is_comment(lines[s - 1]) and dep[s - 1][0] == 0:
            s -= 1
        if chunks and s < chunks[-1]["end"]:
            s = chunks[-1]["end"]
        addrs, kinds, j = [], [], s
        while j < n and (cppsplit.is_comment(lines[j]) or lines[j].strip() == ""):
            mm = cppsplit.ANN.match(lines[j])
            if mm:
                addrs.append(int(mm.group(2), 16))
                kinds.append(mm.group(1))
            j += 1
        k, opened = j, False
        while k < n:
            code = re.sub(r"//.*", "", lines[k]).strip()
            if dep[k][1] > 0 or dep[k][0] > 0:
                opened = True
            if opened and dep[k][1] == 0:
                k += 1
                break
            if not opened and dep[k] == (0, 0) and "{" in code and "}" in code and not code.endswith(";"):
                k += 1
                break
            if not opened and code.endswith(";") and dep[k][1] == 0:
                k += 1
                break
            k += 1
        chunks.append(dict(start=s, end=k, addrs=addrs, kinds=kinds))
        i = k
    pre_end = chunks[0]["start"] if chunks else n
    inters, prev = [], pre_end
    for c in chunks:
        if c["start"] > prev:
            inters.append((prev, c["start"]))
        prev = c["end"]
    if prev < n:
        inters.append((prev, n))
    return lines, pre_end, chunks, inters


# ---------------------------------------------------------------- chunk merge (tumerge)
def merge_into_tu(tree, dest, srcs, rows_by_file):
    """Merge packet source files into an already-migrated TU file (the b7 lander's
    tumerge.py, made a function). DEST keeps its header and preamble; each SRC adds
    its preamble (SPDX/Provenance/VC6FLAGS stripped, tags joining DEST's) and its
    non-row code after DEST's; every row chunk of DEST and the SRCs is then emitted in
    ascending retail address order. Function bodies are never rewritten.

    rows_by_file: file -> set of row addresses that belong to it (manifest + delta).
    Returns (dest_text, provenance_tags_added)."""

    def parts(path, text):
        lines, pre_end, chs, inters = split(text)
        rs = rows_by_file.get(path, set())
        rowch = [c for c in chs if any(a in rs for a in c["addrs"])]
        other = [(c["start"], c["end"]) for c in chs if c not in rowch]
        return lines, pre_end, rowch, sorted(list(inters) + other)

    keep_re = re.compile(r"^//\s?(FUNCTION|STUB|TEMPLATE|SYNTHETIC|LIBRARY|GLOBAL|VTABLE|STRING):", re.M)
    dtext = open(os.path.join(tree, dest)).read()
    dl, dpre, dch, dspans = parts(dest, dtext)
    hb = migrate.header_block(dl[:dpre])
    dhead = dl[:hb]
    pre = [dl[hb:dpre]]
    for a, b in dspans:
        if cppsplit.code_only(dl[a:b]) or keep_re.search("\n".join(dl[a:b])):
            pre.append([""] + migrate.trim_blank(dl[a:b]))
    chunks = [(min(a for a in c["addrs"] if a in rows_by_file.get(dest, ())), migrate.trim_blank(dl[c["start"]:c["end"]]))
              for c in dch]
    tags = []
    for f, ftext in srcs.items():
        sl, spre, sch, sspans = parts(f, ftext)
        shb = migrate.header_block(sl[:spre])
        head, tg = migrate.strip_markers(sl[:shb])
        tags += tg
        head = migrate.clean_notes(migrate.trim_blank(head))
        p = [ln for ln in sl[shb:spre] if not migrate.FLAG_RE.match(ln)]
        p = migrate.rewrite_includes(p, os.path.dirname(f), os.path.dirname(dest), tree)
        blk = ["", "// ---- from the former %s ----" % os.path.basename(f)] + (head + [""] if head else []) + migrate.trim_blank(p)
        for a, b in sspans:
            if cppsplit.code_only(sl[a:b]) or keep_re.search("\n".join(sl[a:b])):
                blk += [""] + migrate.trim_blank(migrate.rewrite_includes(sl[a:b], os.path.dirname(f), os.path.dirname(dest), tree))
        pre.append(blk)
        for c in sch:
            chunks.append((min(a for a in c["addrs"] if a in rows_by_file[f]), migrate.trim_blank(sl[c["start"]:c["end"]])))
    chunks.sort(key=lambda x: x[0])
    added = []
    for i, ln in enumerate(dhead):
        m = migrate.PROV_RE.match(ln)
        if m:
            cur = [x.strip() for x in m.group(1).split("|")]
            for t in tags:
                if t not in cur:
                    cur.append(t)
                    added.append(t)
            dhead[i] = "// Provenance: " + " | ".join(cur)
    out = migrate.trim_blank(dhead + [ln for b in pre for ln in b])
    for k, b in chunks:
        out += [""] + b
    return "\n".join(out) + "\n", added


def rows_in_order(text):
    """Addresses of column-zero FUNCTION/SYNTHETIC/TEMPLATE claims in file order (bodies only)."""
    return [a for a, _ in body_claims(text)]

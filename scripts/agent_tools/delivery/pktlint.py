#!/usr/bin/env python3
"""pktlint.py: lint a READY packet against a tree in seconds, before a lander spends
minutes on it.

    pktlint.py READY_DIR [--tree PATH | --rev REV] [--repo REPO] [--json OUT]
               [--strict] [--jobs N] [--allow-word REGEX]...

Checks (E = error, W = warning). Every rule names the standing direction or brief it
enforces; nothing here needs a compiler except --strict.

  shape        E patch.diff / manifest_delta.json present, commit message parseable (commit_msg.txt, or README
                 'Proposed commit message' block / 'Proposed commit:' line); base sha: base_sha|BASE_SHA file or README 'Base <sha>'
  paths        E paths outside match/, scripts/data/*.json, STATUS.md, progress.svg; symlinks
  stale        E patch does not apply on the tree (3-way, temporary GIT_INDEX_FILE; writes no git metadata)
  words        E forbidden words in added lines / commit message (shipping hygiene)
  steering     E __asm, naked, #pragma optimize, constant conditions; volatile on a non-declaration
               W volatile on a declaration without thread/callback evidence beside it
  sdd          E a hand-written scalar deleting destructor (a function body that tests a flags bit with `& 1` and
                 deletes `this`, or one named like one); the compiler emits ??_G from the declared virtual destructor.
                 E/W a FUNCTION annotation on a ??_G-like method inside an Obj_/view struct
  flags        E a `// VC6FLAGS:` line whose set equals the project default (delete the line)
  thisnull     E a `this &&` null test (steering; the retail code does not test `this`)
  views        E a NEW definition of a class that has a canonical header (w6 brief: never a
                 new per-TU view); W a new definition of a class already defined elsewhere (ODR debt); judged on the POST-patch tree
  classkey     E class/struct keyword differs from the RTTI TypeDescriptor (hcfix rule)
  migrated     E a new .cpp whose rows fall inside an already-migrated original TU window
                 (one TU, one file: the lander would have to merge by hand; use pktrebase --merge)
  inits        E rows that are static-initialiser shapes (held for the TU migration)
  delta        E delta rows malformed, unsorted, colliding with the tree, naming TUs the patch does
                 not create or touch, matched without 100, claiming addresses with no body in the patch; rows already in the manifest
                 (carry-over) or whose len conflicts with an exact row unless marked as a change
  dupclaims    E a body claim for an address that already has a body in the tree
  order        E FUNCTION claims not in ascending address order within a .cpp
  provenance   E new file without SPDX + Provenance header
  spans        E manifest len differs from the CFG-closed span (worklist sizes are padded; use CFG
                 spans) unless listed in spans_ok.txt; extent-audit overrides are honoured
  rea          E/W no REA Evidence IDs (ev_xxxxxxxx) in the packet's README/evidence (brief: REA primary)
  strict       (--strict) compile the touched TUs, raw_match + strict verify_relocations on every
                 matched row with the packet maps + derivable bindings; lists unbound targets;
                 E a partial row whose recorded pct differs from the compiled score (diff_retail, tolerance 0.05)

Exit 0 when there are no errors. --json writes the findings.
"""
import argparse
import concurrent.futures as cf
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dlib as D  # noqa: E402
import landlib as L  # noqa: E402
import cppscan  # noqa: E402

PROJECT_FLAGS = {"/nologo", "/c", "/O2", "/Gr", "/DNDEBUG", "/Gy", "/MT", "/Ob2"}   # scripts/vc6/vc6cl.sh
SDD_NAME = re.compile(r"scalar[ _]*deleting|deleting[ _]*d(?:e)?(?:structor|tor)|\?\?_G|vec(?:tor)?[ _]*deleting", re.I)
SDD_DELETE = re.compile(r"\bdelete\s+this\b|\boperator\s+delete\s*\(\s*this\b|\b(?:free|FreeMem|GameMemFree\w*)\s*\(\s*this\b")
SDD_FLAG = re.compile(r"&\s*1\b")
SDD_DTOR = re.compile(r"(?:->|\.|::)\s*~\s*\w+\s*\(")
SDD_SIG = re.compile(r"void\s*\*\s*(?:__\w+\s+)?\w+\s*\(\s*(?:unsigned(?:\s+int)?|int)\b")
VIEW_STRUCT = re.compile(r"^\s*(?:struct|class)\s+(Obj_\w+|\w*View\w*|\w+_view\w*)\b")


def apply_outside_repo(work, patch_text):
    """`git apply` of PATCH_TEXT in the plain directory WORK, whatever encloses it. Inside a repository
    git apply works relative to the cwd prefix and silently skips paths it considers outside it, leaving
    the pre-patch text with exit status 0; GIT_CEILING_DIRECTORIES (the parent of WORK) stops the
    repository search, and GIT_DIR/GIT_WORK_TREE are dropped."""
    env = {k: v for k, v in os.environ.items() if k not in ("GIT_DIR", "GIT_WORK_TREE", "GIT_INDEX_FILE")}
    env["GIT_CEILING_DIRECTORIES"] = os.path.dirname(os.path.abspath(work))
    return subprocess.run(["git", "apply", "--whitespace=nowarn", "-"], cwd=work, input=patch_text, text=True,
                          capture_output=True, env=env)


class Lint:
    def __init__(self, packet, tree, repo, allow_words=()):
        self.p = packet
        self.t = tree
        self.repo = repo
        self.findings = []
        self.allow = [re.compile(x) for x in allow_words]
        self.ptext = open(packet.patch, errors="replace").read() if os.path.isfile(packet.patch) else ""
        self.diffs = D.split_patch(self.ptext)
        self.delta = None
        self.rows = []
        try:
            self.delta = packet.delta()
            self.ops = D.parse_delta(self.delta)
            self.rows = [r for op, r, old in self.ops]
            self.changed_addrs = {D.hx(r["addr"]) for op, r, old in self.ops if op == "change" or "_change" in r}
        except Exception as ex:
            self.ops = []
            self.err("shape", "manifest_delta.json unreadable: %s" % ex)

    def err(self, rule, msg, **kw):
        self.findings.append(dict(level="E", rule=rule, msg=msg, **kw))

    def warn(self, rule, msg, **kw):
        self.findings.append(dict(level="W", rule=rule, msg=msg, **kw))

    # ------------------------------------------------------------ rules
    def shape(self):
        for e in self.p.validate():
            self.err("shape", e)
        if (os.path.isfile(self.p.readme) or self.p.commit_msg_file()) and not self.p.commit_message():
            self.err("shape", "no commit message: add commit_msg.txt, or a README.md 'Proposed commit message' block / 'Proposed commit: <title>' line")
        if not self.p.base_sha():
            self.warn("shape", "no base sha recorded (base_sha/BASE_SHA file or a README 'Base <sha>' line)")
        if any(d.path == D.MANIFEST for d in self.diffs):
            self.warn("shape", "patch.diff carries match_manifest.json hunks (the lander ignores them; the delta is authoritative)")

    def paths(self):
        allowed = [re.compile(x) for x in L.ALLOWED_PATHS]
        for d in self.diffs:
            if d.mode_symlink:
                self.err("paths", "patch creates/changes a symlink", file=d.path)
            if not any(a.search(d.path) for a in allowed):
                self.err("paths", "path outside the allowed set", file=d.path)
            if d.path in ("STATUS.md", ".github/assets/progress.svg"):
                self.warn("paths", "%s is regenerated by the lander; drop it from the patch" % d.path)

    def stale(self):
        """`git apply --check --3way --cached` against a temporary index file (GIT_INDEX_FILE in a
        scratch dir). Nothing under .git is written: no worktree, no index, no objects."""
        if not self.diffs:
            return
        body = "".join(d.text for d in self.diffs if d.path != D.MANIFEST)
        if not body:
            return
        tmp = D.scratch_dir("pktlint_")
        try:
            idx = os.path.join(tmp, "index")
            env = dict(os.environ, GIT_INDEX_FILE=idx)
            if self.t.rev is None:
                gp = subprocess.run(["git", "-C", self.t.repo, "rev-parse", "--path-format=absolute", "--git-path", "index"],
                                    text=True, capture_output=True).stdout.strip()
                shutil.copyfile(gp, idx)
            else:
                rt = subprocess.run(["git", "-C", self.repo, "read-tree", self.t.rev], env=env, text=True, capture_output=True)
                if rt.returncode:
                    self.err("stale", "cannot read tree %s into a temporary index: %s" % (self.t.rev[:10], rt.stderr.strip()[:200]))
                    return
            r = subprocess.run(["git", "-C", self.repo if self.t.rev else self.t.repo, "apply", "--check", "--cached", "--3way", "--whitespace=nowarn", "-"],
                               input=body, text=True, capture_output=True, env=env)
            if r.returncode:
                files = sorted(set(re.findall(r"error: (?:patch failed: |)([^\s:]+?)(?::\d+)?(?:: (?:does not exist|already exists|patch does not apply|No such file))", r.stderr)))
                files += sorted(set(re.findall(r"error: ([^\s]+): (?:does not exist in index|already exists in working directory)", r.stderr)))
                self.err("stale", "patch does not apply on %s (3-way): %s" % (
                    (self.t.rev or "tree")[:10], "; ".join(x for x in r.stderr.splitlines() if x.startswith("error"))[:400]),
                    files=sorted(set(files)))
                for d in self.diffs:
                    if not d.is_new and d.path not in self.t.paths and d.path != D.MANIFEST:
                        moved = self.moved_to(d.path)
                        self.err("stale", "modifies %s which is gone from the tree%s" % (
                            d.path, " (its rows now live in %s)" % moved if moved else ""), file=d.path)
                    if d.is_new and d.path in self.t.paths:
                        self.err("stale", "creates %s which already exists in the tree" % d.path, file=d.path)
        finally:
            D.remove_dir(tmp)

    def post_files(self):
        """{path: text or None (deleted)} of every file the patch touches, AFTER the patch: the
        tree's file with the diff applied by plain `git apply` on copies in a scratch dir (no
        repository involved). A file whose diff does not apply keeps its pre-patch text."""
        if getattr(self, "_post", None) is not None:
            return self._post
        out = {}
        tmp = D.scratch_dir("pktlint_post_")
        try:
            for i, d in enumerate(self.diffs):
                if d.path == D.MANIFEST:
                    continue
                if d.is_delete:
                    out[d.path] = None
                elif d.is_new:
                    out[d.path] = d.new_content()
                else:
                    work = os.path.join(tmp, str(i))
                    old = self.t.text(d.old)
                    if old is None:
                        continue
                    os.makedirs(os.path.join(work, os.path.dirname(d.old)), exist_ok=True)
                    with open(os.path.join(work, d.old), "w", newline="") as f:
                        f.write(old)
                    r = apply_outside_repo(work, d.text)
                    if r.returncode == 0 and os.path.isfile(os.path.join(work, d.path)):
                        out[d.path] = open(os.path.join(work, d.path), errors="replace").read()
                    else:
                        out[d.path] = old
        finally:
            D.remove_dir(tmp)
        self._post = out
        return out

    def moved_to(self, old_tu):
        """Where a packet-base TU's rows live now, from the packet's base manifest."""
        base = self.p.base_sha()
        if not base:
            return None
        try:
            bm = json.loads(L.git(self.repo, "show", "%s:%s" % (base, D.MANIFEST)))
        except Exception:
            return None
        dests = {self.t.by_addr[D.hx(r["addr"])]["tu"] for r in bm if r["tu"] == old_tu and D.hx(r["addr"]) in self.t.by_addr}
        return ", ".join(sorted(dests)) if dests else None

    def words(self):
        for d in self.diffs:
            if d.path == D.MANIFEST:
                continue
            for ln, text in d.added_lines():
                if D.FORBID_RE.search(text) and not any(a.search(text) for a in self.allow):
                    self.err("words", "forbidden word: %s" % text.strip()[:120], file=d.path, line=ln)
        msg = self.p.commit_message() or ""
        for m in D.FORBID_RE.finditer(msg):
            self.err("words", "forbidden word in the commit message: %r" % m.group(0))
        if re.search(r"git add -A|git add \.", msg):
            self.err("words", "commit message mentions git add -A/.")

    def steering(self):
        for d in self.diffs:
            if not d.path.startswith("match/"):
                continue
            added = d.added_lines()
            text_by_ln = dict(added)
            for ln, text in added:
                code = re.sub(r"//.*$", "", text)
                for kind, rx in D.STEER:
                    if not rx.search(code):
                        continue
                    if kind == "volatile":
                        decl = bool(re.match(r"\s*(extern\s+)?(static\s+)?(const\s+)?volatile\b|\s*volatile\b", code)) and \
                            not re.search(r"[=(]", code.split("volatile", 1)[0]) and d.path.endswith(L.HDR_EXT + L.SRC_EXT)
                        indented = text[:1] in (" ", "\t")
                        is_field_or_global = decl and (re.search(r";\s*$", code) and "(" not in code.split("volatile")[1].split(";")[0])
                        if is_field_or_global:
                            ctx = "\n".join(text_by_ln.get(k, "") for k in range(ln - 6, ln + 2))
                            if not D.VOLATILE_EVIDENCE.search(ctx):
                                self.warn("steering", "volatile declaration without thread/callback evidence in the comment beside it", file=d.path, line=ln)
                        else:
                            self.err("steering", "volatile on an access, cast or local: %s" % text.strip()[:100], file=d.path, line=ln)
                        continue
                    if kind == "const-condition" and re.search(r"\bwhile\s*\(\s*0\s*\)", code) and ln > 1:
                        continue   # do {...} while (0) macro idiom
                    self.err("steering", "%s: %s" % (kind, text.strip()[:100]), file=d.path, line=ln)

    def _added_post(self):
        """[(path, post_text, {added line numbers})] for added/changed C++ files under match/."""
        post = self.post_files()
        for d in self.diffs:
            if not d.path.startswith("match/") or d.is_delete or not d.path.endswith(L.HDR_EXT + L.SRC_EXT):
                continue
            text = post.get(d.path)
            if text is None:
                continue
            yield d, text, {ln for ln, _ in d.added_lines()}

    def sdd(self):
        for d, text, added in self._added_post():
            for header, body, l0, l1 in cppscan.function_bodies(text):
                if not any(l0 <= ln <= l1 for ln in added):
                    continue
                if SDD_DELETE.search(body) and SDD_FLAG.search(body):
                    self.err("sdd", "hand-written scalar deleting destructor shape (%s%s-test, delete this): declare the virtual destructor "
                             "and let the compiler emit ??_G" % ("dtor call, " if SDD_DTOR.search(body) else "", "flag"),
                             file=d.path, line=l0, fn=header[-80:])
                elif SDD_NAME.search(header.split("(")[0]):
                    self.err("sdd", "function named like a scalar deleting destructor: %s" % header[-80:], file=d.path, line=l0)
            # FUNCTION annotations on ??_G-like methods inside Obj_/view structs
            lines = text.split("\n")
            cur, depth = None, 0
            for i, ln in enumerate(lines, 1):
                if cur is None:
                    m = VIEW_STRUCT.match(ln)
                    if m and "{" in ln and ";" not in ln.split("{")[0]:
                        cur, depth = m.group(1), ln.count("{") - ln.count("}")
                        if depth <= 0:
                            cur = None
                    continue
                depth += ln.count("{") - ln.count("}")
                if depth <= 0:
                    cur = None
                    continue
                if re.match(r"\s*//\s*FUNCTION:\s*GAMEMD\s+0x", ln):
                    j = i
                    while j < len(lines) and re.match(r"\s*(//.*)?$", lines[j]):
                        j += 1
                    decl = lines[j] if j < len(lines) else ""
                    if not ({i, j + 1} & added):
                        continue
                    if SDD_NAME.search(decl.split("(")[0]):
                        self.err("sdd", "FUNCTION annotation on a scalar-deleting-destructor-like method inside %s: annotate the virtual "
                                 "destructor in the canonical class instead" % cur, file=d.path, line=i)
                    elif SDD_SIG.search(decl):
                        self.warn("sdd", "FUNCTION annotation on a void*(unsigned) method inside %s (a ??_G shape?): %s" % (cur, decl.strip()[:80]),
                                  file=d.path, line=i)

    def flags(self):
        for d in self.diffs:
            if not d.path.startswith("match/"):
                continue
            for ln, text in d.added_lines():
                m = re.match(r"\s*//\s*VC6FLAGS:(.*)$", text)
                if m and set(m.group(1).split()) == PROJECT_FLAGS:
                    self.err("flags", "VC6FLAGS line equals the project default; delete it (a flag line is only for a bisected deviation)",
                             file=d.path, line=ln)

    def thisnull(self):
        for d in self.diffs:
            if not d.path.startswith("match/"):
                continue
            for ln, text in d.added_lines():
                code = re.sub(r"//.*$", "", text)
                if re.search(r"\bthis\s*&&", code):
                    self.err("thisnull", "`this &&` null test: %s" % text.strip()[:100], file=d.path, line=ln)

    def views(self):
        """Class-view duplication is judged on the POST-patch tree: a class moved to a new
        (canonical) header, with the old definition removed, is not a duplicate."""
        defs = {n: list(v) for n, v in self.t.class_defs().items()}
        post = self.post_files()
        touched = set(post)
        for n in list(defs):
            defs[n] = [(p, k) for p, k in defs[n] if p not in touched]
            if not defs[n]:
                del defs[n]
        for path, text in post.items():
            if text is None or not path.endswith(L.HDR_EXT + L.SRC_EXT) or not path.startswith("match/"):
                continue
            for m in D.CLASS_DEF.finditer(text):
                defs.setdefault(m.group(2), []).append((path, m.group(1)))

        def canonical(path):
            if not path.endswith(L.HDR_EXT):
                return False
            if path.startswith("match/_layout/"):
                return True
            txt = post[path] if path in post else self.t.text(path)
            return "TypeDescriptor 0x" in (txt or "")

        kinds = D.rtti_kinds(self.repo)
        for d in self.diffs:
            if not d.path.startswith("match/") or d.is_delete:
                continue
            added = "\n".join(t for _, t in d.added_lines())
            for m in D.CLASS_DEF.finditer(added):
                kw, name = m.group(1), m.group(2)
                if name in kinds and kinds[name] != kw:
                    self.err("classkey", "%s %s: RTTI records it as a %s" % (kw, name, kinds[name]), file=d.path)
                others = sorted({p for p, _ in defs.get(name, []) if p != d.path})
                if not others:
                    continue
                canon_others = [p for p in others if canonical(p)]
                if canon_others and not canonical(d.path):
                    self.err("views", "new definition of %s, which has a canonical header (%s): include it instead" % (
                        name, ", ".join(canon_others)), file=d.path)
                elif canon_others:
                    self.err("views", "%s would have two canonical definitions (%s and %s)" % (name, d.path, ", ".join(canon_others)), file=d.path)
                else:
                    self.warn("views", "new definition of %s duplicates %s" % (name, ", ".join(others[:3])), file=d.path)

    def migrated(self):
        windows = self.t.tu_windows()
        if not windows:
            return
        new_cpps = {d.path for d in self.diffs if d.is_new and d.path.endswith(L.SRC_EXT)}
        hits = {}
        for r in self.rows:
            if r.get("tu") in new_cpps:
                dest = self.t.tu_for_addr(D.hx(r["addr"]))
                if dest and dest != r["tu"]:
                    hits.setdefault((r["tu"], dest), []).append(r["addr"])
        for (src, dest), addrs in sorted(hits.items()):
            self.err("migrated", "%s: %d rows (%s...) lie in the window of migrated %s (%s); one TU = one file" % (
                src, len(addrs), ", ".join(addrs[:3]), dest, windows[dest][0]), file=src, dest=dest, addrs=addrs)

    def inits(self):
        ini, src = D.init_addresses()
        if not ini:
            self.warn("inits", "no initialiser list found (GAG_INIT_DELTA); rule skipped")
            return
        bad = [r["addr"] for r in self.rows if D.hx(r["addr"]) in ini and D.hx(r["addr"]) not in self.t.by_addr
               and r.get("tu") not in self.t.tu_windows()]
        if bad:
            self.err("inits", "%d static-initialiser rows (held for the TU migration): %s" % (len(bad), ", ".join(bad[:8])), addrs=bad)
        for d in self.diffs:
            for ln, text in d.added_lines():
                if re.search(r"Static-initialiser shape|header-initialiser", text) and d.is_new:
                    self.warn("inits", "initialiser shape comment in a new file", file=d.path, line=ln)
                    break

    def delta_rules(self):
        if self.delta is None:
            return
        if not isinstance(self.delta, list):
            self.warn("delta", "delta is a dict (add/modify/remove); list-of-rows is the convention")
        touched = {d.path for d in self.diffs}
        prev = -1
        sorted_ok = True
        claims_in_patch = self.patch_claims()
        for op, r, old in self.ops:
            a = r.get("addr")
            try:
                ai = D.hx(a)
            except Exception:
                self.err("delta", "row without a valid addr: %r" % r)
                continue
            if ai < prev:
                sorted_ok = False
            prev = ai
            for k in ("tu", "sym", "len", "status"):
                if k not in r:
                    self.err("delta", "row %s missing %s" % (a, k))
            if not re.fullmatch(r"0x[0-9A-F]+", str(a)):
                self.warn("delta", "addr %s not in 0xUPPER form" % a)
            if "len" in r and not re.fullmatch(r"0x[0-9a-fA-F]+", str(r["len"])):
                self.err("delta", "row %s len %r is not hex" % (a, r["len"]))
            if r.get("status") == "matched" and r.get("pct") not in (100, 100.0):
                self.err("delta", "row %s matched with pct %r" % (a, r.get("pct")))
            if r.get("status") == "partial" and r.get("pct") in (100, 100.0):
                self.warn("delta", "row %s partial at 100" % a)
            extra = set(r) - {"tu", "addr", "sym", "len", "name", "status", "pct", "note", "qualification", "metric", "pct_metric", "op", "old"}
            if extra:
                self.err("delta", "row %s has unexpected keys %s" % (a, sorted(extra)))
            tu = r.get("tu")
            cur = self.t.by_addr.get(ai)
            implicit = op is None
            if (op == "add" or (implicit and cur is None)) and cur is not None:
                self.err("delta", "row %s adds an address already in the tree (%s %s)" % (a, cur["tu"], cur["status"]))
            claimed_anywhere = any(ai in v for v in claims_in_patch.values())
            if op != "change" and op != "remove" and "_change" not in r and cur is not None and not self.is_change_row(r):
                if self.same_row(cur, r):
                    self.err("delta", "row %s is already in the manifest (%s %s, len %s): carried-over row, not a result of this packet" % (
                        a, cur["tu"], cur["status"], cur.get("len")), addr=a)
                    continue
                if cur.get("status") == "matched" and cur.get("len") and r.get("len") and D.hx(cur["len"]) != D.hx(r["len"]):
                    self.err("delta", "row %s len %s conflicts with the existing exact row (len %s) and is not marked as a change" % (a, r["len"], cur["len"]), addr=a)
                    continue
            base_row = self.base_rows().get(ai)
            if op is None and cur is None and base_row is not None and self.same_row(base_row, r) and not claimed_anywhere:
                self.err("delta", "row %s is already in the packet's base manifest (carried over)" % a, addr=a)
                continue
            if op != "change" and op != "remove" and "_change" not in r and not claimed_anywhere and not self.is_change_row(r):
                self.err("delta", "row %s: no FUNCTION/SYNTHETIC/TEMPLATE body claim for it in the patch (delta rows must be this packet's new claims/results)" % a, addr=a)
                continue
            if implicit and cur is not None and (cur.get("tu") != tu or cur.get("sym") != r.get("sym")):
                self.warn("delta", "row %s replaces an existing row (tu/sym differ) without an op marker" % a)
            if op in ("change", "remove") and cur is None:
                self.err("delta", "%s of %s which is not in the tree" % (op, a))
            if tu and tu not in touched and tu not in self.t.paths:
                self.err("delta", "row %s names TU %s which the patch neither creates nor the tree has" % (a, tu))
            if tu and op != "remove" and tu in touched and ai not in claims_in_patch.get(tu, set()) and cur is None:
                self.err("delta", "row %s: no FUNCTION/SYNTHETIC/TEMPLATE body claim for it in the patch's %s" % (a, tu))
        if not sorted_ok:
            self.err("delta", "rows are not sorted by address")
        have = {D.hx(r["addr"]) for r in self.rows if "addr" in r}
        for tu, addrs in sorted(claims_in_patch.items()):
            miss = sorted(a for a in addrs if a not in have and a not in self.t.by_addr)
            if miss:
                self.warn("delta", "%s: %d new body claims have no delta row (%s)" % (tu, len(miss), ", ".join("0x%X" % a for a in miss[:4])), file=tu)

    @staticmethod
    def is_change_row(r):
        return bool(r.get("op") in ("change", "remove") or r.get("_change"))

    @staticmethod
    def same_row(cur, r):
        def n(x):
            return (x.get("tu"), x.get("sym"), D.hx(x["len"]) if x.get("len") else None, x.get("status"),
                    float(x["pct"]) if x.get("pct") is not None else None)
        try:
            return n(cur) == n(r)
        except Exception:
            return False

    def base_rows(self):
        """addr -> row of the manifest at the packet's base revision ({} when unknown)."""
        if getattr(self, "_base_rows", None) is None:
            self._base_rows = {}
            base = self.p.base_sha()
            if base:
                try:
                    bm = json.loads(L.git(self.repo, "show", "%s:%s" % (base, D.MANIFEST)))
                    self._base_rows = {D.hx(x["addr"]): x for x in bm}
                except Exception:
                    pass
        return self._base_rows

    def patch_claims(self):
        out = {}
        for d in self.diffs:
            if not d.path.endswith(L.SRC_EXT):
                continue
            added = d.added_lines()
            for i, (ln, text) in enumerate(added):
                m = D.CLAIM.match(text)
                nxt = added[i + 1][1] if i + 1 < len(added) and added[i + 1][0] == ln + 1 else None
                if m and not D.is_decl_marker(m.group(2), nxt):
                    out.setdefault(d.path, set()).add(int(m.group(1), 16))
        return out

    def dupclaims(self):
        claims = self.t.claims()
        for tu, addrs in self.patch_claims().items():
            for a in sorted(addrs):
                owners = [p for p in claims.get(a, []) if p != tu]
                if owners and a in getattr(self, "changed_addrs", set()):
                    self.warn("dupclaims", "0x%X moves here from %s (delta marks the change; the patch must remove the old body)" % (a, ", ".join(owners)), file=tu)
                elif owners:
                    self.err("dupclaims", "0x%X already has a body in %s" % (a, ", ".join(owners)), file=tu)

    def order(self):
        for d in self.diffs:
            if not d.path.endswith(L.SRC_EXT) or d.is_delete:
                continue
            text = d.new_content()
            if text is None:
                if self.t.rev is None:
                    continue
                text = None
            if text is None:
                continue
            seq = D.rows_in_order(text)
            if seq != sorted(seq):
                bad = [hex(seq[i]) for i in range(1, len(seq)) if seq[i] < seq[i - 1]][:5]
                self.err("order", "FUNCTION claims not in ascending address order (first out of order: %s)" % ", ".join(bad), file=d.path)

    def provenance(self):
        for d in self.diffs:
            if d.is_new and d.path.startswith("match/") and d.path.endswith(L.SRC_EXT + L.HDR_EXT):
                head = "\n".join(t for _, t in d.added_lines()[:8])
                if "SPDX-License-Identifier" not in head:
                    self.err("provenance", "new file without an SPDX line in its header", file=d.path)
                if "Provenance:" not in head:
                    self.err("provenance", "new file without a Provenance header", file=d.path)

    def spans(self):
        ok = set()
        f = os.path.join(self.p.dir, "spans_ok.txt")
        if os.path.isfile(f):
            ok = {D.hx(x.split()[0]) for x in open(f) if x.strip() and not x.startswith("#")}
        rows = [r for r in self.rows if "len" in r and r.get("status") in ("matched", "partial")]
        if not rows:
            return
        try:
            for r in rows:
                a = D.hx(r["addr"])
                if a in ok:
                    continue
                span, why = D.cfg_span(a)
                ln = D.hx(r["len"])
                if span and ln < span and r.get("status") == "matched":
                    self.err("spans", "row %s len %s is SHORTER than the %s span 0x%x (unproven tail)" % (r["addr"], r["len"], why, span), addr=r["addr"])
                elif span and ln > span:
                    tail = D.retail_bytes(a + span, ln - span)
                    if tail is not None and tail and all(b in (0x90, 0xCC) for b in tail):
                        self.err("spans", "row %s len %s counts 0x%x bytes of NOP/INT3 padding after the %s span 0x%x (worklist size column; use the CFG span)" % (
                            r["addr"], r["len"], ln - span, why.split(" (")[0], span), addr=r["addr"], cfg_len="0x%x" % span)
                    else:
                        self.warn("spans", "row %s len %s but %s gives 0x%x (jump-table tail?)" % (r["addr"], r["len"], why, span), addr=r["addr"])
                elif span and ln != span:
                    self.warn("spans", "row %s len %s but %s gives 0x%x" % (r["addr"], r["len"], why, span), addr=r["addr"])
        except SystemExit as ex:
            self.warn("spans", "span check unavailable: %s" % ex)
        except Exception as ex:
            self.warn("spans", "span check failed: %r" % (ex,))

    def rea(self):
        """The briefs require the REA skill/MCP as primary ground truth (ghidra CLI fallback,
        stated). Evidence IDs look like ev_18a3f84f; a packet citing none is flagged."""
        texts = []
        for root, _, names in os.walk(self.p.dir):
            for n in names:
                if n.endswith((".md", ".txt", ".log", ".tsv")):
                    try:
                        texts.append(open(os.path.join(root, n), errors="replace").read())
                    except OSError:
                        pass
        blob = "\n".join(texts)
        ids = set(re.findall(r"\bev_[0-9a-f]{6,}\b", blob))
        if ids:
            return
        mentions_rea = re.search(r"\bREA\b|mcp__rea|reverse-engineer-anything", blob)
        mentions_ghidra = re.search(r"ghidra", blob, re.I)
        if mentions_rea:
            self.warn("rea", "README mentions REA but cites no Evidence IDs (ev_xxxxxxxx)")
        elif mentions_ghidra:
            self.warn("rea", "no REA Evidence IDs; only the ghidra CLI fallback is mentioned (the brief wants REA primary, fallback stated)")
        else:
            self.err("rea", "no REA Evidence IDs and no statement of the RE tool used (brief: REA primary, ghidra fallback stated)")

    # ------------------------------------------------------------ --strict
    def strict(self, jobs):
        """Compile the touched TUs in a scratch worktree with the patch applied and prove every
        matched delta row: raw_match, then strict verify_relocations with the packet maps,
        the central bindings (if present) and name-derived bindings."""
        rows = [r for r in self.rows if r.get("status") == "matched" and r.get("tu")]
        prows = [r for r in self.rows if r.get("status") == "partial" and r.get("tu") and r.get("sym") and r.get("len")
                 and isinstance(r.get("pct"), (int, float))]
        if not rows and not prows:
            return
        work = D.scratch_dir("pktlint_strict_")
        wt = D.add_worktree(self.repo, os.path.join(work, "wt"), self.t.rev or "HEAD")
        try:
            body = "".join(d.text for d in self.diffs if d.path != D.MANIFEST)
            r = subprocess.run(["git", "-C", wt, "apply", "--3way", "--index", "--whitespace=nowarn", "-"], input=body, text=True, capture_output=True)
            if r.returncode:
                self.err("strict", "cannot apply the patch for the strict check: " + r.stderr.strip()[:200])
                return
            man, _ = L.load_manifest(os.path.join(wt, D.MANIFEST))
            merged, errs, _ = L.merge_deltas(man, [(self.p.name, self.delta)])
            if errs:
                self.err("strict", "delta does not merge: " + "; ".join(errs[:3]))
                return
            open(os.path.join(wt, D.MANIFEST), "w").write(L.dump_manifest(merged))
            tus = sorted({r["tu"] for r in rows + prows})
            objs = {}
            with cf.ThreadPoolExecutor(jobs) as ex:
                res = list(ex.map(lambda tu: (tu, D.compile_tu(wt, tu, os.path.join(work, "obj", os.path.splitext(tu)[0] + ".obj"))), tus))
            for tu, (ok, text) in res:
                if not ok:
                    errl = [l for l in text.splitlines() if re.search(r"error|fatal", l, re.I)][:3]
                    self.err("strict", "%s does not compile: %s" % (tu, " | ".join(errl)), file=tu)
                else:
                    objs[tu] = os.path.join(work, "obj", os.path.splitext(tu)[0] + ".obj")
            for r in prows:         # a partial's recorded pct must be the score the compiler gives now
                obj = objs.get(r["tu"])
                if not obj:
                    continue
                pct, text = D.diff_retail_pct(wt, obj, r)
                if pct is None:
                    self.warn("strict", "partial row %s: no score from diff_retail (%s)" % (r["addr"], text[-100:].replace("\n", " ")), addr=r["addr"])
                elif abs(pct - float(r["pct"])) > 0.05:
                    self.err("strict", "partial row %s records pct %s but the compiled score is %s" % (r["addr"], r["pct"], pct),
                             addr=r["addr"], recorded=r["pct"], compiled=pct)
            if not rows:
                return
            maps = list(self.p.symbol_map_files())
            central = D.first_existing(D.BINDINGS_CANDIDATES, wt)
            if central:
                maps.append(central)
            merged_map, clash = D.merge_maps(maps)
            iat = D.iat_by_name()
            for tu, obj in objs.items():
                merged_map.update(D.label_bindings(obj, [r for r in rows if r["tu"] == tu]))
            mapfile = os.path.join(work, "map.json")
            json.dump(merged_map, open(mapfile, "w"))

            def one(r):
                obj = objs.get(r["tu"])
                if not obj:
                    return r, None, None, "no object"
                ok, text = D.raw_match(wt, obj, r)
                if not ok:
                    return r, False, None, text[-200:]
                for _ in range(8):      # derive a binding per unbound target and retry
                    sok, target, text = D.strict(wt, obj, r, mapfile)
                    if sok or not target:
                        return r, True, sok, (text[-200:] if not sok else "")
                    va = D.derive_binding(target, iat)
                    if va is None or target in merged_map:
                        return r, True, False, "unbound target %s" % target
                    merged_map[target] = "0x%X" % va
                    json.dump(merged_map, open(mapfile, "w"))
                return r, True, False, text[-200:]

            with cf.ThreadPoolExecutor(jobs) as ex:
                out = list(ex.map(one, rows))
            derived = {k: v for k, v in merged_map.items() if not any(k in (D.read_json(m) if isinstance(m, str) else m) for m in maps)}
            self.derived_bindings = derived
            for r, raw, st, text in out:
                if raw is None:
                    continue
                if raw is False:
                    self.err("strict", "row %s raw_match fails: %s" % (r["addr"], text.replace("\n", " ")), addr=r["addr"])
                elif st is False:
                    self.err("strict", "row %s strict verify_relocations fails: %s" % (r["addr"], text.replace("\n", " ")), addr=r["addr"])
            if derived:
                self.findings.append(dict(level="I", rule="strict", msg="%d bindings derived from symbol names/IAT/$L positions (not in the packet maps)" % len(derived), derived=derived))
        finally:
            D.remove_worktree(self.repo, wt)
            D.remove_dir(work)

    def run(self, do_strict=False, jobs=8, rules=None):
        order = ["shape", "paths", "stale", "words", "steering", "sdd", "flags", "thisnull", "views", "migrated", "inits", "delta_rules",
                 "dupclaims", "order", "provenance", "spans", "rea"]
        for name in order:
            if rules and name.replace("_rules", "") not in rules:
                continue
            try:
                getattr(self, name)()
            except Exception as ex:
                import traceback
                self.err(name.replace("_rules", ""), "rule crashed: %r (%s)" % (ex, traceback.format_exc().splitlines()[-2]))
        if do_strict:
            self.strict(jobs)
        return self.findings


def resolve_packet(path):
    path = os.path.abspath(path)
    if os.path.isfile(os.path.join(path, "patch.diff")):
        return L.Packet(path)
    if os.path.isfile(os.path.join(path, "READY", "patch.diff")):
        return L.Packet(os.path.join(path, "READY"))
    return L.Packet(path)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("packet")
    ap.add_argument("--repo", default=D.MAIN_REPO)
    ap.add_argument("--tree", help="worktree to lint against (index contents); default: --rev")
    ap.add_argument("--rev", default="HEAD", help="revision of --repo to lint against (default HEAD)")
    ap.add_argument("--strict", action="store_true")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--json")
    ap.add_argument("--allow-word", action="append", default=[])
    ap.add_argument("--rules", help="comma list of rules to run")
    a = ap.parse_args(argv)
    t0 = time.time()
    p = resolve_packet(a.packet)
    tree = D.Tree(a.tree, None) if a.tree else D.Tree(a.repo, a.rev)
    lint = Lint(p, tree, a.repo, a.allow_word)
    f = lint.run(a.strict, a.jobs, set(a.rules.split(",")) if a.rules else None)
    errs = [x for x in f if x["level"] == "E"]
    for x in f:
        loc = x.get("file", "")
        if x.get("line"):
            loc += ":%d" % x["line"]
        print("%s %-10s %s%s" % (x["level"], x["rule"], (loc + ": ") if loc else "", x["msg"]))
    print("pktlint %s: %d errors, %d warnings on %s (%.1fs)" % (p.name, len(errs), len(f) - len(errs) - sum(x["level"] == "I" for x in f),
                                                                (tree.rev or tree.repo)[:10], time.time() - t0))
    if a.json:
        json.dump({"packet": p.name, "tree": tree.rev or tree.repo, "findings": f, "secs": round(time.time() - t0, 1)},
                  open(a.json, "w"), indent=1)
    return 1 if errs else 0


if __name__ == "__main__":
    sys.exit(main())

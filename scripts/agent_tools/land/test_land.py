#!/usr/bin/env python3
"""Fast unit tests for the landing tools (no Wine, no retail binary).

    python3 -m unittest test_land        (from this directory)
"""
import json
import os
import re
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
# Tests use a neutral stand-in word; the real list is local-only (see landlib.load_forbid_re).
import tempfile as _tf
_wf = _tf.NamedTemporaryFile("w", suffix=".txt", delete=False)
_wf.write("zzforbidden\n"); _wf.close()
os.environ["GAG_FORBIDDEN_WORDS"] = _wf.name
import atexit as _ax
_ax.register(os.unlink, _wf.name)
import landlib as L  # noqa: E402


class FakeFiles:
    def __init__(self, files):
        self._f = {k: v.encode() for k, v in files.items()}
        self.paths = sorted(self._f)

    def read(self, p):
        return self._f.get(p)


def row(addr, tu="match/a/x.cpp", sym=None, status="matched", pct=100):
    return {"tu": tu, "addr": addr, "sym": sym or "?f%s@@YAXXZ" % addr, "len": "0x10",
            "name": "f" + addr, "status": status, "pct": pct}


class CommitMessage(unittest.TestCase):
    def test_plain_paragraphs_until_trailer(self):
        t = "## Proposed commit message\nTitle line\n\nBody.\n\nCo-Authored-By: X <x@y>\n\nMore prose that is not the message.\n"
        self.assertEqual(L.parse_commit_message(t), "Title line\n\nBody.\n\nCo-Authored-By: X <x@y>\n")

    def test_plain_stops_at_heading(self):
        t = "## Proposed commit message\nTitle\n\nBody\n## Next\nignored\n"
        self.assertEqual(L.parse_commit_message(t), "Title\n\nBody\n")

    def test_two_space_indent(self):
        t = "Proposed commit message:\n  Title\n  \n  Body line\n\nLander review points:\n- x\n"
        self.assertEqual(L.parse_commit_message(t), "Title\n\nBody line\n")

    def test_four_space_indent_after_blank(self):
        t = "Proposed commit message:\n\n    Title\n\n    Body\n\nManifest delta: none\n"
        self.assertEqual(L.parse_commit_message(t), "Title\n\nBody\n")

    def test_fenced(self):
        t = "## Proposed commit message\n```\nTitle\n\nBody\n```\nafter\n"
        self.assertEqual(L.parse_commit_message(t), "Title\n\nBody\n")

    def test_missing(self):
        self.assertIsNone(L.parse_commit_message("# nothing here\n"))


class DeltaMerge(unittest.TestCase):
    def setUp(self):
        self.man = [row("0x401000"), row("0x401010")]

    def test_add_and_change_and_underscore_keys_stripped(self):
        d = [dict(row("0x401020"), _note="x"), dict(row("0x401010", sym="?g@@YAXXZ"), _change="sym only")]
        m, e, w = L.merge_deltas(self.man, [("p", d)])
        self.assertEqual(e, [])
        self.assertEqual([r["addr"] for r in m], ["0x401000", "0x401010", "0x401020"])
        self.assertEqual(m[1]["sym"], "?g@@YAXXZ")
        self.assertFalse(any(k.startswith("_") for r in m for k in r))

    def test_add_present_is_collision(self):
        m, e, w = L.merge_deltas(self.man, [("p", [dict(row("0x401000"), op="add")])])
        self.assertIsNone(m)
        self.assertIn("add of present address", e[0])

    def test_two_packets_add_same_address(self):
        m, e, w = L.merge_deltas(self.man, [("p1", [row("0x401020")]), ("p2", [dict(row("0x401020"), op="add")])])
        self.assertIsNone(m)
        self.assertTrue(any("0x401020" in x for x in e))

    def test_second_packet_changing_what_first_changed_differently(self):
        p1 = [dict(row("0x401010", sym="?g@@YAXXZ"), op="change")]
        p2 = [dict(row("0x401010", sym="?h@@YAXXZ"), op="change")]
        m, e, w = L.merge_deltas(self.man, [("p1", p1), ("p2", p2)])
        self.assertIsNone(m)
        self.assertIn("already modified differently", e[0])

    def test_touched_carries_across_calls(self):
        t = {}
        m, e, w = L.merge_deltas(self.man, [("p1", [row("0x401020")])], touched=t)
        self.assertEqual(e, [])
        m2, e2, w2 = L.merge_deltas(m, [("p2", [dict(row("0x401020"), op="add")])], touched=t)
        self.assertIsNone(m2)

    def test_implicit_change_of_other_symbol_warns(self):
        m, e, w = L.merge_deltas(self.man, [("p", [row("0x401010", sym="?other@@YAXXZ")])])
        self.assertEqual(e, [])
        self.assertTrue(w and "without an op" in w[0])

    def test_change_of_missing(self):
        m, e, w = L.merge_deltas(self.man, [("p", [dict(row("0x409999"), op="change")])])
        self.assertIsNone(m)
        self.assertIn("missing address", e[0])

    def test_old_symbol_mismatch(self):
        d = [dict(row("0x401010"), op="change", old={"sym": "?wrong@@YAXXZ"})]
        m, e, w = L.merge_deltas(self.man, [("p", d)])
        self.assertIsNone(m)
        self.assertIn("old symbol mismatch", e[0])

    def test_dict_format_remove_modify_add(self):
        d = {"remove": [row("0x401000")],
             "modify": [{"old_sym": self.man[1]["sym"], "row": row("0x401010", sym="?h@@YAXXZ")}],
             "add": [row("0x401030")]}
        m, e, w = L.merge_deltas(self.man, [("p", d)])
        self.assertEqual(e, [])
        self.assertEqual([r["addr"] for r in m], ["0x401010", "0x401030"])

    def test_nothing_applied_on_error(self):
        m, e, w = L.merge_deltas(self.man, [("p", [row("0x401040"), dict(row("0x409999"), op="change")])])
        self.assertIsNone(m)
        self.assertEqual(len(self.man), 2)

    def test_missing_required_key(self):
        bad = row("0x401050")
        del bad["len"]
        m, e, w = L.merge_deltas(self.man, [("p", [bad])])
        self.assertIsNone(m)

    def test_dump_matches_tracked_format(self):
        txt = json.dumps(self.man, indent=1)
        self.assertEqual(L.dump_manifest(json.loads(txt)), txt)

    def test_manifest_diff(self):
        new = [row("0x401000"), row("0x401010", pct=50), row("0x401020")]
        a, c, r = L.manifest_diff(self.man, new)
        self.assertEqual([x["addr"] for x in a], ["0x401020"])
        self.assertEqual([x["addr"] for x in c], ["0x401010"])
        self.assertEqual(r, [])


class Includes(unittest.TestCase):
    def make(self):
        return L.IncludeIndex(FakeFiles({
            "match/a/x.cpp": '#include "../_layout/h.h"\n#include <stddef.h>\n',
            "match/a/y.cpp": '#include "y.h"\n',
            "match/a/y.h": '#include "../_rt/g.h"\n',
            "match/_layout/h.h": '#include "k.h"\n#include "../_rt/g.h"\n',
            "match/_layout/k.h": "",
            "match/_rt/g.h": "",
            "match/b/z.cpp": "// no includes\n",
        }))

    def test_closure_and_dependents(self):
        ix = self.make()
        self.assertEqual(set(ix.closure("match/a/x.cpp")), {"match/a/x.cpp", "match/_layout/h.h", "match/_layout/k.h", "match/_rt/g.h"})
        dep = ix.dependents()
        self.assertEqual(dep["match/_rt/g.h"], {"match/a/x.cpp", "match/a/y.cpp"})
        self.assertEqual(dep["match/_layout/k.h"], {"match/a/x.cpp"})
        self.assertNotIn("match/b/z.cpp", dep["match/_rt/g.h"])
        self.assertEqual(ix.unresolved, {})

    def test_parent_directory_search_like_msvc(self):
        # k.h is included from h.h by bare name; also reachable when the includer lives elsewhere
        ix = L.IncludeIndex(FakeFiles({"match/a/t.cpp": '#include "../c/p.h"\n', "match/c/p.h": '#include "q.h"\n',
                                       "match/a/q.h": ""}))
        # q.h is not next to p.h; MSVC then tries the directory of the including TU
        self.assertIn("match/a/q.h", ix.closure("match/a/t.cpp"))

    def test_unresolved_reported(self):
        ix = L.IncludeIndex(FakeFiles({"match/a/t.cpp": '#include "gone.h"\n'}))
        ix.closure("match/a/t.cpp")
        self.assertIn("match/a/t.cpp", ix.unresolved)

    def test_key_changes_with_closure_content_only(self):
        a = self.make()
        k1 = a.key("match/a/x.cpp", "salt")
        b = self.make()
        b.files._f["match/_rt/g.h"] = b"changed"
        self.assertNotEqual(k1, b.key("match/a/x.cpp", "salt"))
        self.assertEqual(a.key("match/b/z.cpp", "salt"), b.key("match/b/z.cpp", "salt"))
        self.assertNotEqual(k1, a.key("match/a/x.cpp", "salt2"))

    def test_flags_marker_in_key(self):
        a = L.IncludeIndex(FakeFiles({"match/a/t.cpp": "// VC6FLAGS: /O2 /Ob2\n"}))
        b = L.IncludeIndex(FakeFiles({"match/a/t.cpp": "// VC6FLAGS: /O2\n"}))
        self.assertNotEqual(a.key("match/a/t.cpp", "s"), b.key("match/a/t.cpp", "s"))


class VendoredIncludes(unittest.TestCase):
    FILES = {
        "match/lib/lzo/lzo1x.c": '#include "../../../third_party/lzo/lzo-1.00/src/lzo1x_1.c"\n',
        "third_party/lzo/lzo-1.00/src/lzo1x_1.c": '#include "lzo_conf.h"\n#include <stddef.h>\n',
        "third_party/lzo/lzo-1.00/src/lzo_conf.h": "",
    }

    def test_third_party_include_resolves_and_is_not_a_tu(self):
        ix = L.IncludeIndex(FakeFiles(self.FILES))
        self.assertEqual(ix.tus(), ["match/lib/lzo/lzo1x.c"])
        self.assertEqual(ix.all_unresolved(), {})
        self.assertIn("third_party/lzo/lzo-1.00/src/lzo_conf.h", ix.dependents())

    def test_match_only_index_leaves_it_unresolved(self):
        ix = L.IncludeIndex(FakeFiles({k: v for k, v in self.FILES.items() if k.startswith("match/")}))
        self.assertIn("match/lib/lzo/lzo1x.c", ix.all_unresolved())

    def test_word_hits_vendored_exempt(self):
        d = ("diff --git a/third_party/lzo/a.c b/third_party/lzo/a.c\n+++ b/third_party/lzo/a.c\n+/* zzforbidden text */\n"
             "diff --git a/match/x.cpp b/match/x.cpp\n+++ b/match/x.cpp\n+// zzforbidden\n")
        hits, n = L.word_hits(d, [], [re.compile(x) for x in L.VENDORED_PATHS])
        self.assertEqual(hits, ["+// zzforbidden"])
        self.assertEqual(n, 1)
        hits, n = L.word_hits(d, [], [])
        self.assertEqual(len(hits), 2)

    def test_tree_files_accept_several_roots(self):
        import subprocess
        with tempfile.TemporaryDirectory() as d:
            subprocess.run(["git", "init", "-q", d], check=True)
            for f in ("match/a.cpp", "third_party/t.h", "docs/x.md"):
                os.makedirs(os.path.dirname(os.path.join(d, f)), exist_ok=True)
                open(os.path.join(d, f), "w").write("x")
            subprocess.run(["git", "-C", d, "add", "-A"], check=True)
            self.assertEqual(L.TreeFiles(d, L.INCLUDE_ROOTS).paths, ["match/a.cpp", "third_party/t.h"])
            self.assertEqual(L.TreeFiles(d).paths, ["match/a.cpp"])


class PacketFiles(unittest.TestCase):
    def test_symbol_map_files_found_and_filtered(self):
        with tempfile.TemporaryDirectory() as d:
            os.makedirs(os.path.join(d, "READY", "sub"))
            json.dump({"?a@@YAXXZ": "0x401000"}, open(os.path.join(d, "READY", "symbol_map.json"), "w"))
            json.dump({"?b@@YAXXZ": "0x401010"}, open(os.path.join(d, "READY", "sub", "map_C1.json"), "w"))
            json.dump([1, 2], open(os.path.join(d, "READY", "symmap_list.json"), "w"))
            json.dump({"x": {"nested": 1}}, open(os.path.join(d, "READY", "symmap_nested.json"), "w"))
            p = L.Packet(os.path.join(d, "READY"))
            self.assertEqual(sorted(os.path.basename(x) for x in p.symbol_map_files()), ["map_C1.json", "symbol_map.json"])

    def test_validate(self):
        with tempfile.TemporaryDirectory() as d:
            self.assertEqual(len(L.Packet(d).validate()), 3)


def mkpacket(d, files):
    r = os.path.join(d, "READY")
    os.makedirs(r, exist_ok=True)
    for k, v in files.items():
        with open(os.path.join(r, k), "w") as f:
            f.write(v if isinstance(v, str) else json.dumps(v))
    return L.Packet(r)


def bind_patch(lines, removed=()):
    body = "".join("-%s\n" % x for x in removed) + "".join("+%s\n" % x for x in lines)
    return ("diff --git a/scripts/data/symbol_bindings.json b/scripts/data/symbol_bindings.json\n"
            "--- a/scripts/data/symbol_bindings.json\n+++ b/scripts/data/symbol_bindings.json\n@@ -1,2 +1,3 @@\n" + body +
            "diff --git a/match/a.cpp b/match/a.cpp\n--- a/match/a.cpp\n+++ b/match/a.cpp\n@@ -1 +1 @@\n+  \"zz\": \"0x1\",\n")


class PacketNormalisation(unittest.TestCase):
    """Behaviour added for the b8 landing (Codex packet forms)."""

    def test_integer_addr_len_become_hex(self):
        with tempfile.TemporaryDirectory() as d:
            p = mkpacket(d, {"manifest_delta.json": [{"tu": "t", "addr": 0x401000, "len": 16, "sym": "s", "status": "matched"}]})
            r = p.delta()[0]
            self.assertEqual((r["addr"], r["len"]), ("0x401000", "0x10"))
            q = mkpacket(os.path.join(d, "q"), {"manifest_delta.json": {"add": [{"addr": 4198400, "len": 255}], "modify": [{"old_sym": "o", "row": {"addr": 4198416, "len": 8}}]}})
            dd = q.delta()
            self.assertEqual((dd["add"][0]["addr"], dd["add"][0]["len"]), ("0x401000", "0xff"))
            self.assertEqual((dd["modify"][0]["row"]["addr"], dd["modify"][0]["row"]["len"]), ("0x401010", "0x8"))

    def test_manifest_rekeys_become_change_ops(self):
        with tempfile.TemporaryDirectory() as d:
            p = mkpacket(d, {"manifest_delta.json": [row("0x401000")],
                             "manifest_rekeys.json": [{"addr": 0x401010, "old_sym": "?old@@YAXXZ", "new": {"tu": "t", "addr": 0x401010, "len": 16, "sym": "?new@@YAXXZ", "status": "matched"}},
                                                      {"tu": "t", "addr": "0x401020", "len": "0x4", "sym": "?w@@YAXXZ", "status": "matched"}]})
            ops = L.parse_delta(p.delta())
            self.assertEqual([o for o, _, _ in ops], [None, "change", "change"])
            self.assertEqual(ops[1][1]["addr"], "0x401010")
            self.assertEqual(ops[1][1]["len"], "0x10")
            self.assertEqual(ops[1][2], {"sym": "?old@@YAXXZ"})
            self.assertIsNone(ops[2][2])
            self.assertNotIn("old_sym", ops[1][1])
            # dict-form delta: rekeys land in modify
            q = mkpacket(os.path.join(d, "q"), {"manifest_delta.json": {"add": []},
                                                "manifest_rekeys.json": [{"addr": 1, "old_sym": "o", "new": {"tu": "t", "addr": 0x401010, "len": 1, "sym": "n", "status": "matched"}}]})
            m = q.delta()["modify"]
            self.assertEqual((m[0]["old_sym"], m[0]["row"]["sym"]), ("o", "n"))

    def test_proposed_commit_line_forms(self):
        self.assertEqual(L.parse_commit_message("Proposed commit: Recover X\n"), "Recover X\n\n" + L.CODEX_TRAILER + "\n")
        self.assertEqual(L.parse_commit_message("Proposed commit: `Title here`\n").splitlines()[0], "Title here")
        t = "Proposed commit: Title\n```\nTitle\n\nBody\n```\n"
        self.assertEqual(L.parse_commit_message(t), "Title\n\nBody\n\n" + L.CODEX_TRAILER + "\n")
        t2 = "Proposed commit: T\n```\nT\n\nBody\n\nCo-Authored-By: A <a@b>\n```\n"
        self.assertEqual(L.parse_commit_message(t2), "T\n\nBody\n\nCo-Authored-By: A <a@b>\n")

    def test_base_sha_forms(self):
        sha = "8dd6a8de574785d7ab0bcd8e23d3e07cf469e572"
        cases = [{"base_sha": sha + "\n"}, {"BASE_SHA": sha.upper() + "\n"}, {"base_sha.txt": "base " + sha},
                 {"README.md": "Base: `%s`.\n" % sha}, {"README.md": "Base%s, checkpoint d08f92b\n" % sha},
                 {"README.md": "## Base\nbase sha = %s\n" % sha}]
        for i, c in enumerate(cases):
            with tempfile.TemporaryDirectory() as d:
                self.assertEqual(mkpacket(d, c).base_sha(), sha, c)
        with tempfile.TemporaryDirectory() as d:
            self.assertIsNone(mkpacket(d, {"README.md": "Based on prior work, see d08f92b\n"}).base_sha())


class MergeBindings(unittest.TestCase):
    def tree(self, d, content):
        os.makedirs(os.path.join(d, "scripts/data"))
        open(os.path.join(d, L.BINDINGS), "w").write(content)

    def test_sorted_hex_format_and_trailing_newline(self):
        with tempfile.TemporaryDirectory() as d:
            self.tree(d, json.dumps({"b": "0x00000002", "d": "0x00000004"}, indent=1) + "\n")
            n, bad = L.merge_bindings(d, {"c": 3, "a": "0x1", "$Lx": "0x9", "b": "0x00000002"})
            self.assertEqual((n, bad), (2, []))
            raw = open(os.path.join(d, L.BINDINGS)).read()
            self.assertTrue(raw.endswith("}\n"))
            self.assertEqual(list(json.loads(raw)), ["a", "b", "c", "d"])
            self.assertEqual(json.loads(raw)["c"], "0x00000003")

    def test_no_trailing_newline_preserved(self):
        with tempfile.TemporaryDirectory() as d:
            self.tree(d, json.dumps({"b": "0x00000002"}, indent=1))
            L.merge_bindings(d, {"a": 1})
            self.assertFalse(open(os.path.join(d, L.BINDINGS)).read().endswith("\n"))

    def test_conflict_refused_and_nothing_written(self):
        with tempfile.TemporaryDirectory() as d:
            orig = json.dumps({"b": "0x00000002"}, indent=1)
            self.tree(d, orig)
            n, bad = L.merge_bindings(d, {"new": 5, "b": "0x3"})
            self.assertEqual(n, 0)
            self.assertEqual(len(bad), 1)
            self.assertIn("b:", bad[0])
            self.assertEqual(open(os.path.join(d, L.BINDINGS)).read(), orig)

    def test_empty_or_missing(self):
        with tempfile.TemporaryDirectory() as d:
            self.assertEqual(L.merge_bindings(d, {"a": 1}), (0, []))


class PacketBindings(unittest.TestCase):
    def test_binding_delta_json_name_and_add_form(self):
        with tempfile.TemporaryDirectory() as d:
            self.assertEqual(mkpacket(d, {"binding_delta.json": {"a": "0x401000", "b": 4198416}}).bindings_delta(),
                             {"a": "0x00401000", "b": "0x00401010"})
            q = mkpacket(os.path.join(d, "q"), {"symbol_bindings_delta.json": {"add": {"a": "0x1"}}})
            self.assertEqual(q.bindings_delta(), {"a": "0x00000001"})
            self.assertEqual(q.binding_conflicts, [])
            self.assertEqual(mkpacket(os.path.join(d, "r"), {}).bindings_delta(), {})
            self.assertIn("binding_delta.json", [os.path.basename(x) for x in mkpacket(os.path.join(d, "s"), {"binding_delta.json": {"a": "0x1"}}).symbol_map_files()])

    def test_hunks_in_patch_are_extracted(self):
        with tempfile.TemporaryDirectory() as d:
            patch = bind_patch(['  "?x@@YAXXZ": "0x00401000",', '  "y": "0x00401010"'], removed=['  "w": "0x00000001"'])
            p = mkpacket(d, {"patch.diff": patch.replace('-  "w": "0x00000001"\n', '-  "w": "0x00000001"\n+  "w": "0x00000001",\n')})
            self.assertEqual(p.bindings_delta(), {"?x@@YAXXZ": "0x00401000", "y": "0x00401010"})
            self.assertEqual(p.binding_conflicts, [])   # the comma fix-up of w is formatting, and match/a.cpp lines are ignored

    def test_patch_and_delta_file_agree_or_conflict(self):
        with tempfile.TemporaryDirectory() as d:
            patch = bind_patch(['  "x": "0x00401000"'])
            ok = mkpacket(d, {"patch.diff": patch, "binding_delta.json": {"x": "0x401000"}})
            self.assertEqual(ok.bindings_delta(), {"x": "0x00401000"})
            self.assertEqual(ok.binding_conflicts, [])
            bad = mkpacket(os.path.join(d, "b"), {"patch.diff": patch, "binding_delta.json": {"x": "0x401004"}})
            bad.bindings_delta()
            self.assertEqual(len(bad.binding_conflicts), 1)

    def test_patch_changing_existing_entry_conflicts(self):
        with tempfile.TemporaryDirectory() as d:
            p = mkpacket(d, {"patch.diff": bind_patch(['  "w": "0x00000002"'], removed=['  "w": "0x00000001"'])})
            p.bindings_delta()
            self.assertEqual(len(p.binding_conflicts), 1)
            self.assertIn("existing central entry", p.binding_conflicts[0])

    def test_extracted_bindings_merge_and_conflict_with_central(self):
        with tempfile.TemporaryDirectory() as d:
            os.makedirs(os.path.join(d, "t/scripts/data"))
            open(os.path.join(d, "t", L.BINDINGS), "w").write(json.dumps({"x": "0x00000009"}, indent=1))
            p = mkpacket(os.path.join(d, "p"), {"patch.diff": bind_patch(['  "x": "0x00000001"', '  "n": "0x00000002"'])})
            n, bad = L.merge_bindings(os.path.join(d, "t"), p.bindings_delta())
            self.assertEqual(n, 0)
            self.assertEqual(len(bad), 1)


class GatesFixes(unittest.TestCase):
    def test_objpath_keeps_stem_for_any_extension(self):
        import gates
        import sectioncmp
        for tu, stem in (("match/x/lzo1x.c", "match/x/lzo1x"), ("match/x/a.cpp", "match/x/a"), ("match/x/b.cxx", "match/x/b")):
            self.assertEqual(gates.objpath("/r", tu), "/r/" + stem + ".obj")
            self.assertEqual(sectioncmp.obj_path("/r", tu), "/r/" + stem + ".obj")

    def sec(self, name, same=False):
        return {"section": name, "bytes_same": same, "reloc_diff": [], "reloc_count": [0, 0]}

    def run_sections(self, results, same=False, touched=()):
        import gates
        rows = {"?f@@YAXXZ": {"sym": "?f@@YAXXZ", "addr": "0x5D0850", "len": "0x10", "status": "matched"}}
        rep = {"changed": {"match/v.cpp": {"differ": [self.sec(".text|?f@@YAXXZ", same)]}}}
        return gates.unexplained_sections(rep, rows, set(touched), lambda obj, row: results[obj], lambda tu: "old", lambda tu: "new")

    def test_move_to_retail_is_an_improvement(self):
        un, imp = self.run_sections({"old": (False, 62.5), "new": (True, 100.0)})
        self.assertEqual(un, [])
        self.assertEqual(imp, [("match/v.cpp", ".text|?f@@YAXXZ", 62.5, 100.0)])

    def test_move_away_from_retail_fails(self):
        un, imp = self.run_sections({"old": (True, 100.0), "new": (False, 80.0)})
        self.assertEqual((len(un), imp), (1, []))

    def test_neither_matches_or_both_match_still_fail(self):
        self.assertEqual(len(self.run_sections({"old": (False, 10.0), "new": (False, 20.0)})[0]), 1)
        self.assertEqual(len(self.run_sections({"old": (True, 100.0), "new": (True, 100.0)})[0]), 1)

    def test_reloc_only_and_touched_not_examined(self):
        def boom(obj, row):
            raise AssertionError("not examined")
        import gates
        rows = {"?f@@YAXXZ": {"sym": "?f@@YAXXZ", "addr": "0x1", "len": "0x1", "status": "matched"}}
        rep = {"changed": {"t.cpp": {"differ": [self.sec(".text|?f@@YAXXZ", True)]}}}
        self.assertEqual(gates.unexplained_sections(rep, rows, set(), boom, str, str), ([], []))
        rep = {"changed": {"t.cpp": {"differ": [self.sec(".text|?f@@YAXXZ", False)]}}}
        self.assertEqual(gates.unexplained_sections(rep, rows, {"?f@@YAXXZ"}, boom, str, str), ([], []))


class ResolvedSections(unittest.TestCase):
    """An absolute immediate that becomes a relocation to a symbol bound to that address is not a byte change."""
    import struct as _st

    def sec(self, imm, rel=(), tail=b"\xc3"):
        import struct
        return (b"\xb9" + struct.pack("<I", imm) + tail, list(rel))

    def test_imm_equals_bound_reloc(self):
        import sectioncmp as S
        res = {"?DAT_0087F7E8@@3PADA": 0x87F7E8}.get
        base = self.sec(0x87F7E8)
        new = self.sec(0, [(1, "?DAT_0087F7E8@@3PADA", 6)])
        self.assertTrue(S.resolved_equal(base, new, res))
        self.assertTrue(S.resolved_equal(new, base, res))
        self.assertTrue(S.resolved_equal(self.sec(0x10, [(1, "?DAT_0087F7E8@@3PADA", 6)]), self.sec(0x87F7F8), res))   # addend

    def test_other_changes_fail(self):
        import sectioncmp as S
        res = {"?a@@3HA": 0x87F7E8}.get
        new = self.sec(0, [(1, "?a@@3HA", 6)])
        self.assertFalse(S.resolved_equal(self.sec(0x87F7EC), new, res))                        # different address
        self.assertFalse(S.resolved_equal(self.sec(0x87F7E8, tail=b"\x90"), new, res))          # other byte differs
        self.assertFalse(S.resolved_equal(self.sec(0x87F7E8), self.sec(0, [(1, "?unbound", 6)]), res))   # unresolvable
        self.assertFalse(S.resolved_equal(self.sec(0x87F7E8), self.sec(0, [(1, "?a@@3HA", 0x14)]), res))   # not an absolute reloc
        self.assertFalse(S.resolved_equal(self.sec(0x87F7E8), (new[0] + b"\0", new[1]), res))   # size

    def test_two_relocs_to_same_address_equal(self):
        import sectioncmp as S
        res = {"a": 0x401000, "b": 0x401000}.get
        self.assertTrue(S.resolved_equal(self.sec(0, [(1, "a", 6)]), self.sec(0, [(1, "b", 6)]), res))

    def test_gate_uses_resolver(self):
        import gates
        rows = {"?f@@YAXXZ": {"sym": "?f@@YAXXZ", "addr": "0x5D0850", "len": "0x10", "status": "matched"}}
        rep = {"changed": {"t.cpp": {"differ": [{"section": ".text|?f@@YAXXZ", "bytes_same": False, "reloc_diff": [], "reloc_count": [0, 1]}]}}}
        def boom(obj, row):
            return (False, 0.0)
        self.assertEqual(len(gates.unexplained_sections(rep, rows, set(), boom, str, str)[0]), 1)
        self.assertEqual(gates.unexplained_sections(rep, rows, set(), boom, str, str, lambda tu, k: True), ([], []))

    def test_make_resolver_scoping(self):
        import gates
        with tempfile.TemporaryDirectory() as d:
            os.makedirs(os.path.join(d, "scripts/data"))
            json.dump({"x": "0x00000010", "a.cpp::_$S1": "0x00000020", "b.cpp::_$S1": "0x00000030"}, open(os.path.join(d, L.BINDINGS), "w"))
            r = gates.make_resolver(d, ([{"sym": "m", "addr": "0x40"}],), "a.cpp")
            self.assertEqual((r("x"), r("_$S1"), r("m"), r("zz")), (0x10, 0x20, 0x40, None))


class BindingCorrections(unittest.TestCase):
    def tree(self, d, cur):
        os.makedirs(os.path.join(d, "t/scripts/data"))
        open(os.path.join(d, "t", L.BINDINGS), "w").write(json.dumps(cur, indent=1))
        return os.path.join(d, "t")

    GOOD = [{"symbol": "w", "old_addr": "0x1", "new_addr": "0x2", "evidence": "disasm of 0x401000 shows the load from 0x2"}]

    def test_parse_validates(self):
        with tempfile.TemporaryDirectory() as d:
            f = os.path.join(d, "c.json")
            self.assertEqual(L.parse_binding_corrections(f), ([], []))
            for bad in ([{"symbol": "w", "old_addr": "0x1", "new_addr": "0x2", "evidence": " "}],
                        [{"symbol": "w", "old_addr": "0x1", "new_addr": "0x2"}],
                        [{"symbol": "w", "old_addr": "zz", "new_addr": "0x2", "evidence": "e"}],
                        [{"old_addr": "0x1", "new_addr": "0x2", "evidence": "e"}],
                        [{"symbol": "w", "old_addr": "0x1", "new_addr": "0x1", "evidence": "e"}], {"a": 1}):
                json.dump(bad, open(f, "w"))
                e, errs = L.parse_binding_corrections(f)
                self.assertEqual((e, bool(errs)), ([], True), bad)
            json.dump(self.GOOD, open(f, "w"))
            e, errs = L.parse_binding_corrections(f)
            self.assertEqual((errs, e[0]["old_addr"], e[0]["new_addr"]), ([], "0x00000001", "0x00000002"))

    def test_merge_applies_only_when_old_matches(self):
        with tempfile.TemporaryDirectory() as d:
            t = self.tree(d, {"w": "0x00000001", "z": "0x00000009"})
            c = L.parse_binding_corrections(self._write(d, self.GOOD))[0]
            self.assertEqual(L.merge_bindings(t, {"w": "0x2"}, c), (1, []))
            self.assertEqual(json.load(open(os.path.join(t, L.BINDINGS)))["w"], "0x00000002")
            n, bad = L.merge_bindings(t, {"w": "0x2"}, c)     # central is now 0x2, not old_addr
            self.assertEqual((n, len(bad)), (0, 1))
            self.assertIn("expects central", bad[0])

    def test_merge_rejects_missing_symbol_and_inconsistent_add(self):
        with tempfile.TemporaryDirectory() as d:
            t = self.tree(d, {"w": "0x00000001"})
            c = L.parse_binding_corrections(self._write(d, self.GOOD))[0]
            self.assertEqual(L.merge_bindings(t, {"w": "0x3"}, c)[0], 0)
            c2 = [dict(c[0], symbol="nope")]
            self.assertEqual(len(L.merge_bindings(t, {}, c2)[1]), 1)
            self.assertEqual(open(os.path.join(t, L.BINDINGS)).read(), json.dumps({"w": "0x00000001"}, indent=1))

    def test_silent_contradiction_still_refused(self):
        with tempfile.TemporaryDirectory() as d:
            t = self.tree(d, {"w": "0x00000001"})
            n, bad = L.merge_bindings(t, {"w": "0x2"})
            self.assertEqual((n, len(bad)), (0, 1))
            p = mkpacket(os.path.join(d, "p"), {"binding_delta.json": {"w": "0x2"}})
            n, bad = L.merge_bindings(t, p.bindings_delta(), p.binding_corrections()[0])
            self.assertEqual((n, len(bad)), (0, 1))

    def _write(self, d, entries):
        f = os.path.join(d, "bc.json")
        json.dump(entries, open(f, "w"))
        return f

    def test_packet_patch_hunk_allowed_only_as_the_correction(self):
        with tempfile.TemporaryDirectory() as d:
            files = {"binding_corrections.json": self.GOOD,
                     "patch.diff": bind_patch(['  "w": "0x00000002"'], removed=['  "w": "0x00000001"'])}
            p = mkpacket(os.path.join(d, "a"), files)
            self.assertEqual(p.bindings_delta(), {"w": "0x00000002"})
            self.assertEqual(p.binding_conflicts, [])
            files["patch.diff"] = bind_patch(['  "w": "0x00000007"'], removed=['  "w": "0x00000001"'])
            q = mkpacket(os.path.join(d, "b"), files)
            q.bindings_delta()
            self.assertTrue(q.binding_conflicts)
            r = mkpacket(os.path.join(d, "c"), {"patch.diff": bind_patch(['  "w": "0x00000002"'], removed=['  "w": "0x00000001"'])})
            r.bindings_delta()
            self.assertTrue(r.binding_conflicts)      # no corrections file: still refused


if __name__ == "__main__":
    unittest.main()

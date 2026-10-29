# delivery: packet linter, auto-rebase/merge, batch landing, worker bootstrap

Tools that shorten match -> packet -> landed-on-main without weakening any proof. They are
deterministic scripts; the one thing they never do is decide a binary fact. Shell is bash,
Python 3, no new dependencies. They reuse the sibling tools (`../land/` gates and bundle
lander, `../tumigrate/cppsplit.py`, `../common.py`/`ctx.py` for the pinned PE and CFG spans,
`../trivgen/pe_imports.py` for the retail IAT).

| file | role |
|---|---|
| `dlib.py` | shared model: patch splitting, tree facts (migrated TU windows, canonical classes, claims), delta forms incl. re-key deltas, chunk split/merge, binding derivation, compile/score helpers, the created-path ledger |
| `pktlint.py` | READY-packet linter, 0.2-0.5 s per packet (`--strict` adds a compile + raw/strict proof of every matched row) |
| `pktrebase.py` | re-apply a packet onto the tip: remap moved files, merge new files into migrated TU files in address order, retire clashing local views under byte identity, re-key, re-point the delta, derive bindings, prove rows, precise conflict report |
| `batchland.py` | lint -> rebase onto the growing prefix -> `land_bundle.py` (one full gate per batch, bisect, one commit per packet) -> optional incremental gate per commit |
| `pkt.py` | worker CLI: `budget`, `init`, `span`, `score`, `bind`, `finish`, `done` |
| `flagsweep.py` | /Ob and /Op variants over every TU with partials (via `../cheap-near/flagprobe.py`); proposes VC6FLAGS changes only where no row drops; writes patch + pct delta |
| `permute_queue.py` | ranks partial rows for the permuter (multiset-identical, RA2-twin-identical) and scaffolds `scripts/permuter/new_run.sh` dirs with the current body |
| `skeleton.py` | compilable first draft per address from binary facts (receiver class and slot from RTTI vtables, convention, RET n, offset asserts, callee/global/string decls, disassembly comment); rows.tsv lines for `pkt.py score` |
| `branch2packet.py` | branch + rows JSON (+ removed rows) -> READY packet (patch over allowed paths, sorted delta with add/change/remove ops decided against the base manifest, base_sha, README with the commit message); `--lint` runs pktlint |
| `placement_leads.py` | report: files pinned without `/Ob2` and, from `scripts/data/original_tu_map.json`, the rows whose position in the witnessed link order differs from the file's home (definitions that probably belong in another original file) |
| `ini_names.py` | report: member names established by matched `Field = ini->ReadX(ID, "Key", Field)` readers, with class and offset, and the places that still use `unknown_XX` at those offsets |
| `cppscan.py` | comment/string stripping and function-body discovery used by the lint rules and ini_names |
| `dispatch.py` | refilters the worklist against the tip (manifest + body claims), clusters by original TU, writes one brief per cluster with the migrated TU file, canonical headers and CFG spans |
| `../agents/` | `gagarin-worker` (sonnet), `gagarin-lander`, `gagarin-orchestrator` agent templates (frontmatter + system prompt) pointing at the skills |
| `../skills/` | `gagarin-packet-worker`, `gagarin-lander`, `gagarin-orchestrator` SKILL.md; `../skills/install.sh` links skills into `~/.claude/skills` and the agent templates into `~/.claude/agents` |
| `tests/test_delivery.py` | fast tests (`python3 -m unittest tests.test_delivery`) |
| `tests/prove_rebase.py` | rebases real packets onto the tree the lander had and compares with the landed commit |
| `tests/prove_batch.py` | one full gate on a landing range vs the per-packet full gates (regenerated if the lander's run dirs are gone) |
| `ADOPTION.md` | what briefs and landers change |

Scratch: `<scratch>/delivery/` (disk; `/tmp` is RAM-backed and the
OOM killer has ended sessions). Jobs cap `GAG_JOBS` (default 4). Every worktree or directory a
tool creates is recorded in `.created_paths`; `remove_worktree`/`remove_dir` refuse anything
not in that list and nothing calls `worktree prune` (incident 2026-10-22, see
`../INCIDENT_20261022_worktrees_removed.md`).

## What was measured (before)

b7 landing, 2026-10-22 21:31-22:12 (`<scratch>/land-b7`, now gone; commit times on main):
11 commits in 41 min, 3.7 min per packet. 18 `gates.py --mode full` runs at 41-48 s each
(12.6 min: eight packets were gated twice after a strict or sections failure). The rest was
hand work the lander scripted ad hoc per packet: `tumerge.py` (merge the packet's new file into
the migrated TU), `remap_apply.py` (hunks on files the migration moved), `mdelta.py` (re-point the
delta), `lbind.py` + `symmap_*_extra.json` (40 bindings per packet, mostly FUN_/DAT_/`__imp__`
names and `$L` labels), `drop_clsid_block.py`, plus the one-view-per-object unification. Wave 5,
before the land tool: 4 packets in 70 min (17 min each).

Workers: six wave-6 packets each shipped their own `score.py`, `symres.py`, `relocs.py`,
`fin.py`, `mkresults.py`, `d.sh` (225 lines in w6-tu095, none identical between workers).
Rule breaches the landers caught late: House.h per-TU view (tu095), held initialiser rows
(tu161), functions out of address order (c027, landed anyway), padded lengths, missing REA
evidence.

## What was measured (after)

- `pktlint`: 0.2-0.5 s per packet on six historical packets. It flags, against the right
  revision, every defect the b7 lander found by hand: tu095 House.h (4 canonical-class views,
  E), tu161's 3 initialiser rows (dupclaims, E) and 13 new files for migrated netshare.cpp
  (migrated, E), tu237/tu171/tu130/tu288 files for migrated TUs (E), c027's 3 out-of-order TUs
  (E), padded lengths (E when the tail is NOP/INT3, W when it is a jump table), no REA Evidence
  IDs (E/W). A fresh packet on its own base (tu237 @ 3a8adb6) lints clean.
- `pktrebase`: 1-3 s per packet. Clean cases (fablefix, nearmiss, tu237 and tu171 on their own
  bases, fu-classfix2 on 935745b): every matched row proved raw + strict (33/33, 59/59, 28/28,
  9/9, 5/5), the resulting trees equal the landed commits except the files the lander changed
  by decision (nearmiss: the `rnd` alias removal ordered in standing directions;
  padding_scan.json, which the lander regenerates). Merged cases (tu288, tu171, tu099, tu180 onto
  the tree the lander had): the merged TU file has the same body-claim sequence as the landed
  file (105/105, 109/109, 47/47, 155/155 claims), every delta row has the same tu/len/status as
  landed, and the residual conflicts are exactly the semantic view decisions the lander made by
  hand (int vs pointer globals, char vs wchar, a header hunk conflicting with a later header
  change): tu288 2, tu171 2, tu099 3, tu180 9 items, each with both declaration sites.
  See `tests/prove_rebase.py` and `<scratch>/delivery/prove_rebase/report.json`.
- batch gates: `tests/prove_batch.py` on the b7 range d2682f0..935745b (8 commits): one full gate at
  the tip (130 s) vs eight per-packet full gates (947 s): identical verdicts, 0 regressed both ways,
  the same 356 strict rows all passing, the same 34 changed TUs, and the same single sections
  finding (PlanMgr 0x63AB00 addend change, accepted by the lander). Details in tests/MEASUREMENTS.md.

## Proof strength

Nothing here replaces an oracle. Rebased rows are proved by `raw_match.py` and
`verify_relocations.py` exactly as before; a binding derived from a symbol name or the IAT is
still checked against the relocation field, so a wrong derivation fails. View retirement is
accepted only when the TU compiles and every matched row of that TU (tip and packet) stays
byte-identical; otherwise everything is reverted and reported. Batch landing runs the full
gate (every matched row of the tree re-proved, strict on every added/changed row, section
comparison of every object) once at the tip, and `--gate-each` adds the incremental gate on
every intermediate commit, so each commit on main is individually gated as before.

# Adoption note: what briefs, workers and landers change

## Briefs (match_brief / w6_brief / followup_brief / prep_brief)

Replace the "Setup" and "Deliverable" paragraphs with the worker skill (`skills/gagarin-packet-worker/SKILL.md`):

- `pkt.py init NAME` instead of hand-made worktrees and toolchain links (disk scratch, budget check,
  `-j4`, READY skeleton, rule checklist printed). No helper scripts in the packet dir: `pkt.py span /
  score / bind / finish` replace score.py, symres.py, relocs.py, fin.py, mkresults.py, d.sh.
- The packet must pass `pktlint.py` with 0 errors before it is reported READY; the worker fixes
  lint errors, not the lander. `finish` runs it.
- Cite REA Evidence IDs in README.md (rule `rea`); lengths are CFG spans (rule `spans`).
- Keep: no steering, canonical headers, one TU = one file, address order, forbidden words, no
  `git add -A`, no watch loops, REA primary. The linter enforces each of them mechanically.

## Landers

- Run `pktlint` on every READY packet on arrival (seconds) and send errors back; do not fix them by hand.
- Run `pktrebase` instead of writing `tumerge.py`/`remap_apply.py`/`mdelta.py`/`lbind.py` again: it merges
  into migrated TU files, re-points deltas, derives the `$L`/FUN_/DAT_/`__imp__` bindings and proves
  every row. Act only on its conflict list (declaration sites are given). Fix residuals in the REBASED
  packet, re-run pktrebase on it, then land.
- Land with `batchland.py PKT... --gate-each` (one full gate per batch + an incremental gate per commit)
  instead of one full gate per packet. Use `--ff` only after the branch has been inspected.
- Drop each landed packet's `symbol_rekeys.json` into `delivery/rekeys/` so later packets re-key automatically.
- Cleanup rule (incident 2026-10-22): never remove, prune or `--force` a worktree or directory you did not
  create. The tools keep `<scratch>/delivery/.created_paths` and refuse anything else.

## Standing directions to add

- `pktlint` errors block a packet from landing; `words_ok.txt`, `spans_ok.txt`, `waive_strict.txt` in READY/
  carry explicit, written overrides.
- Central bindings (fu-symmap) landing makes `strict` need no per-packet maps for shared symbols; until then
  `pkt.py bind` builds a minimal complete packet map (central entries copied, the rest derived and checked).

## Where the tools live

They are tracked under `scripts/agent_tools/` (see its README.md). The forbidden-word list is not
tracked: it names private sources, so it is read at run time from `.coordination/forbidden_words.txt`
(or `$GAG_FORBIDDEN_WORDS`), one regex per line; with no file the `words` rule is disabled with a
warning. `skills/install.sh` links the skills into `~/.claude/skills` (user level).

## What else can be automated (ranked by measured time, with the proof that keeps it honest)

1. Header-member adoption. Most residual rebase conflicts are `C2039 'X' is not a member of Class` after a
   local view is retired: the member exists in the retired view with an offset assert. A tool can copy the
   member declaration (type, name, offset) into the canonical header at the asserted offset, then accept
   only if the canonical header still compiles standalone (layout gate), the TU compiles and every row's
   bytes hold. This closes most of the tu237/tu180/tu230 lists without a human.
2. Global-view unification by bytes. `extern int DAT_x` vs `extern CountedBlock DAT_x`: generate the body
   rewrite `DAT_x` -> `DAT_x.count`, `DAT_x+8[i]` -> `DAT_x.data[i]` only for the exact access shapes seen,
   accept under byte identity. Riskier; keep it as a proposal the lander approves per site.
3. Bindings regeneration after each landing (`symmap/sweep.py derive` + `build_bindings.py`) as a batchland
   post-step, once fu-symmap is on main, so no packet ships a map at all.
4. Worklist refresh against the tip manifest after each batch (filter `worklist_live.csv`, re-check claims),
   and cluster dispatch files per worker (addresses, TU file, canonical headers to include) produced by script.
5. STATUS.md paragraph and commit-message counts generated from the manifest diff of the batch (the counts and
   the lists of addresses are mechanical; only the one-sentence summary stays human).
6. Class-key fixes (`hcfix/rekey.py`) and the padded-length fix are already mechanical; wire the class-key fix
   into pktrebase under the same compile + bytes gate.
7. Demotion packets: rows that fail strict with wrong targets (class B) become a manifest patch (status
   partial, pct re-measured) by script, with the strict reason in the note field.

## More generators and permuters (what the evidence says is worth building)

Ranked by (addresses reachable) x (how mechanical), with the oracle that keeps each honest.

1. Skeleton generator (biggest LLM-cost lever). For a cluster of addresses, emit a compilable first
   draft per function from binary facts only: signature (convention from ECX/EDX use and RET n, as
   convention_census does), vtable slot and override declaration (cache/vtable_slots.json), every
   `[reg+off]` access as a member of the canonical class with a GG_STATIC_ASSERT, callees declared from
   the manifest/bindings, globals as DAT_ externs, strings as STRING markers, and the REA pseudo-code as
   a comment. `pkt.py score` then gives the starting percentage; the model edits a scored draft instead
   of typing from a listing. trivgen already does this for the leaf shapes (774 exact); the skeleton is
   the same pipeline without the "exact or nothing" filter.
2. Batch permuter over the 163 multiset-identical partials (fable-partials census: same instruction
   multiset = ordering/register allocation, not a missing statement) and the 141 partials whose RA2 twin
   is identical (compile problem, not an edit). scripts/permuter exists; a driver that runs it per row
   with a time budget, in the background, and turns any 100% result into a packet row through
   `pkt.py bind/finish` needs no model at all.
3. Flag sweep per TU (cheap-near/flagprobe.py): /Ob1, /Ob2, /Op, /Oi variants compiled for every TU
   holding partials, rows re-scored, a manifest patch proposed for TUs where a flag set lifts rows with
   zero regressions. One compile per variant per TU (~0.13 s each): the whole tree in minutes.
4. Family generators still open (leads12 / remaining_families.csv: 302 families, 678 addresses):
   adjustor thunks (~34, mechanical once the COM bases are real classes), deleting destructors by
   pattern, VectorClass/DynamicVectorClass/HashTable instantiations for element types not yet covered
   (families covered 27 types), TClassFactory/GetClassID per RTTI class (done for 77 and 539 rows:
   re-run the same generator after each RTTI header batch).
5. Static-initialiser placement: the 590 held trivgen shapes (178 landed with the migration) become a
   deterministic pass once every TU file exists: place by __xc table order into the TU file, prove
   bytes, done.
6. Callee-declaration unifier: 217 callees with more than one declaration (29 with differing
   conventions). Generate the one declaration the binary supports (RET n, ECX/EDX) per callee, rewrite
   every per-file copy to it, accept only with zero regressed rows (tu_score.py over includers).
7. Header-member adoption and global-view unification (items 1-2 of the list above): they turn most of
   the residual rebase conflicts into byte-gated edits.
8. Worklist and dispatch by script: refilter after each batch, cluster by owning class/TU window, write
   one brief per cluster with the canonical headers to include and the addresses' CFG spans, claimed
   check included. The model only matches.

# Agent tools

Workflow tools for working, packaging and landing matched functions. Everything is written
against this repo's own data: the pinned retail `gamemd.exe` (read at run time, never stored), the
manifest and annotations, `scripts/data/*.json`, the VC6 toolchain and the `build-vc6` objects. They
decide no binary fact; the match/verify gates stay the oracle.

Requirements: python3, binutils `objdump`, the `ghidra` CLI project over the exe (ctx callers
only), the VC6 toolchain (classcheck, gates).

Environment (all optional except the binary):
`GAMEMD_BINARY` (your retail exe; SHA-256 checked; there is no default),
`GAG_RA2_BINARY` (your own RA2 `game.exe`, twinpair only; `GAG_RA2_PAIRS` overrides the twin file the delivery tools read),
`GAG_WORKTREE` (match/ to read; default the repo these tools are in),
`GAG_MAIN` (main checkout: toolchain, untracked local files and data missing from the worktree;
default derived from the git common dir), `GAG_SCRATCH_ROOT` (disk scratch for worktrees, run dirs
and READY packets; default `../gagarin-scratch` next to the main checkout, never `/tmp`),
`GAG_FORBIDDEN_WORDS` (see below).

Forbidden words. The word list the linter and the land gates check added lines against names private
sources, so it is not tracked. Put one regex per line (`#` comments) in
`.coordination/forbidden_words.txt` of the main checkout (or point `GAG_FORBIDDEN_WORDS` at a file).
With no file the `words` rule is disabled and a warning is printed on every run.

## What to run

| job | tool |
|---|---|
| partial best scores | `best_score.py backfill` stamps `best_pct`/`best_at` on partial rows (max of pct and the attempts ledger); the lander keeps them rising |
| work one function | `ctx.py ADDR` (extent, claims, flags, named listing, callers, vtable slots), `trivgen/` (exact leaf shapes), `../vc6/idiom_lift.py`, `attempts.py` (what was already tried), `aligned_diff.py` (how close a partial is) |
| layout | `classcheck.py CLASS` (header vs binary, conflicting views) |
| package | `delivery/pkt.py init/span/score/bind/finish`, or `delivery/branch2packet.py` for a branch-style worker |
| land | `delivery/pktlint.py`, `delivery/pktrebase.py`, `delivery/batchland.py` / `land/land_bundle.sh`, `land/inc_gates.sh`, `land/verify_safe.sh` |
| full M3 gate for one worktree | `land/m3_gate.sh WORKTREE [--full]` (JSON summary: matched, partials, differing bytes per section, project bytes, placement.json); `land/placement_diff.py OLD NEW` classifies changed pieces |
| reccmp over the M3 link | `../vc6/reccmp_image.py [--out build-vc6/reccmp] [--queue permq queue.tsv] [--reuse]`: builds the plain and `/Z7` objects, links both (the `/Z7` link adds `/DEBUG /PDB`), proves debug info leaves code, data and relocations unchanged (`../vc6/debug_neutral.py`), then runs reccmp-reccmp (`--json`), -vtable, -datacmp, -roadmap, audits reccmp's function matching against the manifest (`../vc6/reccmp_audit.py`) and runs -stackcmp on the near-miss partials (`../vc6/reccmp_stack.py`, an M1-style analysis image from `link_m1.py --promote`); `summary.json` holds the numbers. Needs `GAMEMD_BINARY` and the `reccmp-*` tools in PATH; tests `../vc6/test_reccmp_image.py` |
| structure migration (measure only) | `wwstruct/chd_census.py OBJDIR [--base OBJDIR]` (RTTI `??_R3` attributes per object vs retail), `wwstruct/emitter_map.py OBJDIR [--against OBJDIR]` (which object the link keeps per shared COMDAT), `wwstruct/static_init_dump.py OBJDIR [--against OBJDIR]` (`_$E`/`_$S` per TU), `wwstruct/tu_mapping.py` (current file -> target `<Name>.CPP`, report only); tests: `wwstruct/test_wwstruct.py` |
| triage the partials | `partial_triage.py` (class, delta and routing per partial row: register-only, order-only/parked B16, stack-only, inline-shape, structural), then `../permuter/source_perm.py` for the permuter/commute rows; `regmine.py` for what edits did to which diff patterns |
| group partials by residual (report only) | `residual_signatures.py TRIAGE_DIR [--tsv OUT]` over `partial_triage.py` output: rows sharing one `retail => compiled` hunk; substitutions are the useful ones, lone mov/push hunks are mostly scheduling |
| permuter batch | `../permuter/perm_batch.py TRIAGE_DIR --tree WT --out DIR`: runs `source_perm.py` over the permuter-routed rows, best first, resumable, keeps only best.txt/best.cpp, stops below 50 GB free; applies nothing |
| cross-build twins (report only) | `twinpair.py` (YR to RA2 1.006 function pairs by strings, RTTI slots, masked hashes and callee order to a fixed point, with agreement and conflicts; writes `scripts/data/twin_map.json`, `--csv` keeps the old `pairs.csv` layout; `delivery/permute_queue.py` and `delivery/dispatch.py` read it); needs `GAG_RA2_BINARY` (your own RA2 `game.exe`); `x86scan.py` is its dependency-free decoder / CFG walker; tests: `python3 -m unittest test_twin_extent` |
| census recall (report only) | `extent_recall.py` (candidate starts from calls, jumps, vtables, stored and table code pointers, classed real missed / alternate entry / shared tail / data / padding-thunk against `function_extents.json`; proposals for review only, the census is never edited) |
| INI-key member names | `delivery/ini_fields.py extract/plan/apply`: reads every INI reader call site in the retail image (key string, member offset, width; matched or not), joins them with the canonical headers, lists placeholder members that can take the key as name (and conflicts with existing names), and `apply` renames declaration, asserts and uses with a compile-guided revert of lookalike uses in other classes (byte identity then proved by the gates) |
| lead lists (report only) | `delivery/placement_leads.py`, `delivery/ini_names.py`, `delivery/flagsweep.py`, `delivery/permute_queue.py` |

Skills (`skills/`, installed with `skills/install.sh`): `gagarin-packet-worker`, `gagarin-lander`,
`gagarin-orchestrator`; the agent templates are in `agent_defs/`. The install script symlinks into
`~/.claude/skills` and `~/.claude/agents`; copies already there are left alone.

Background shells. Never wait with `pgrep -f <pattern>` when your own command line contains the
pattern: it matches the waiting shell itself and the wait never ends. Wait on the job's exit status
(`m3_gate.sh` exits 0 iff every step passed) or on the PID you saved from `$!`.

Tests: `delivery` (`python3 -m unittest tests.test_delivery`), `land` (`python3 -m unittest test_land`,
`python3 selftest.py`), `trivgen` (`python3 -m unittest test_trivgen`), `partial_triage`/`regmine`/`attempts` (`python3 -m unittest test_partial_triage test_regmine test_attempts` here), `regpredict`/`residual_classify` (`scripts/vc6`), `source_perm` (`scripts/permuter`, `python3 -m unittest test_source_perm`), all from their own directory.

Not shipped: `cache/` (rebuilt: `ghidra_functions.json` from the ghidra CLI, `vtable_slots.json` from
`../vc6/vtable_slots.py`), caches, run outputs, one-off scripts of past migrations.

`<state>` is the untracked, local `state/` folder (the main checkout's when the worktree has none).

| tool | what it answers | output |
|---|---|---|
| `ctx.py ADDR [--json]` | everything about one function before you draft it | stdout |
| `vslot_owners.py [--tsv OUT] [--class C]` | which class does each virtual function belong to by the RTTI vtables holding it, and which manifest rows sit under a stand-in, a class outside that chain or no class (the rehoming worklist)? | stdout / TSV / JSON |
| `bindings_prune.py --objs DIR [--apply]` | which `scripts/data/symbol_bindings.json` entries name a symbol that no compiled object of the tree defines or references (stale)? `--apply` removes them; refuses an incomplete object set (< 100 objects). DIR = a gate run's `new/` or the project build | stdout / `--json` |
| `land/dupaddr.py --objs DIR [--baseline F] [--write-baseline F]` | which retail addresses have two or more strong definitions, whatever the mangling (the `dupaddr` gate; ratchet against `scripts/data/dupaddr_baseline.json`)? | stdout |
| `global_decls.py [--addr A..] [--flagged] [--multi-file] [--canon F] [--summary]` | for every retail global (a namespace-scope data object bound to an address by its Ghidra-style name, the bindings or its `// GLOBAL: GAMEMD` annotation): the definition and every declaration site (file:line, name, type), and which addresses are used under more than one (name, type) or declared `extern` in more than one file? | stdout / `--json` |
| `global_unify.py plan/apply/check/bisect/bindings/rekeys` | declare a global once, in one shared header, and make every TU include it: `plan` picks one canonical name (canon map, agreed name, the single attested name, else `DAT_/STR_<ADDR>`) and the definition's type per address and skips what it cannot (two definitions, class-static members, ambiguous names, types only a `.cpp` defines); `apply` deletes the per-TU externs and their annotations, renames old spellings everywhere, adds the header and the includes; `check` compares a build with the base objects section by section with relocations resolved to addresses; `bisect` finds the minimal address set behind one TU that changed (VC6 scheduling and RTTI attribute bytes can depend on the declarations in scope); `bindings` / `rekeys` update `symbol_bindings.json` and write the packet's `binding_rekeys.json` / `symbol_map.json`; tests `python3 -m unittest test_global_decls` | JSON plan, edited tree |
| `classcheck.py CLASS [--header H]` | does this header's layout agree with the binary, and which other headers define the class? | `<state>/orchestration/class_reports/CLASS.json` |
| `attempts.py add/show/search/best/import/check/defer` | what has already been tried at this address, and may another attempt run (cap 12, patience 4, no identical source, defer is an outcome)? | `<state>/orchestration/attempts.jsonl` |
| `partial_triage.py [--out DIR] [-j 4]` | which class (register-only, order-only, stack-only, inline-shape, structural) is each partial row, how many instructions must change, and where does it route (permuter, `source_perm --only commute`, parked B16, reccmp-stackcmp, inline library, manual)? | `DIR/triage.tsv`, `summary.json` (absolute paths; each TU compiled once, 4 parallel) |
| `regmine.py [--ledger L] [--ready-glob G]` | which source edit fixed or failed to fix which diff pattern, from the attempts ledger and held-packet notes? | markdown rulebook under the main checkout's untracked `.scratch/regmine/` |
| `libmatch.py [LIB...]` | which .text functions are VC6 CRT, by bytes? | `<state>/orchestration/library_map.json` |
| `refaudit.py [--json OUT]` | do unbound global references agree across TUs? | stdout / JSON |
| `tpl_audit.py OBJDIR [--instances\|--divergent\|--multi-g]` | which objects define each template COMDAT, which one the link keeps (link order), does it equal retail, which COMDATs diverge, and are the multi-address `??_G` reached by direct calls? | stdout / JSON |
| `aligned_diff.py --obj O --sym S --addr A --len L [--hunks]` | how close is a partial once insertions/deletions are aligned (LCS under diff_retail's reloc-normalised equality), and where are the mismatching runs? | stdout |
| `inline_sites.py [--top N] [--touch TEXT] [--func ADDR] [--label L] [--json OUT]` | which instruction sequences does the retail .text repeat (register-abstracted, displacements/immediates/call targets kept), how many sites and functions, which functions are still unmatched, and is there an out-of-line copy of the body (the strongest evidence of the real source form)? | stdout / JSON |
| `vector_census.py [--member M] [--sites]` | for each VectorClass/DynamicVectorClass member (Delete, AddItem, FindItemIndex dispatch, ctor bodies, Clear): the out-of-line instances, the direct calls reaching them and the inline expansion sites | stdout / JSON |
| `lever_sweep.py --tree WT [--rules R] [--matched] [--skip-addr A..]` | does a source rewrite rule (default `vec-count`: raw `.Count` read to the vector's inline `GetCount()`) improve a partial row without changing any other row of its TU? Rewrites in place in a linked worktree, recompiles, rescores with diff_retail, keeps only improvements with no regression, writes a TSV (addr, before, after, kept) and attempts-ledger rows (kept: `recorded`, rejected: `swept`); rules are data, disabled when the real accessor is missing; tests `python3 -m unittest test_lever_sweep` | stdout / TSV / ledger |

## partial_triage.py
Reuses `scripts/vc6/residual_classify.py` (labels, now including `commutative-swap` and `cmp-swap`, the
reccmp operand-swap patches) and `scripts/vc6/regpredict.py` (the homm3 first-fit register model for C2 12.00.8447:
EAX, ECX, EDX, ESI, EDI, EBX, EBP; call-crossing values lose EAX/ECX/EDX; labels B1 role swap/rebind/call-crossing,
B8 zero-CSE, B16 schedule, with a lever hint; a minimal model, so expect labels, not matches). Classes: `register-only`,
`order-only` (identical instruction multiset transposed = B16, no known lever: routed `parked (B16)` so workers stop
spending on it; a branch-layout-only difference stays with the permuter), `stack-only`, `inline-shape` (the length delta
sits >= 60% in call-vs-inlined alignment hunks), `structural`; plus `reloc-only`, `compile-fail`, `no-score`.
`delta` = max(retail, compiled) minus the LCS of the masked instructions. A relative `--out` is made absolute, an object
the compiler did not write is `compile-fail`, never skipped. `permute_queue.py --triage triage.tsv` leaves parked rows
out. Tests: `python3 -m unittest test_partial_triage` here, `test_regpredict test_residual_classify` in `scripts/vc6`.

## source_perm.py (scripts/permuter)
Non-steering permuter on the real TU. A readability/anti-steering filter is always on: mutations are built to preserve semantics (statements only move when a
conservative effects model proves they commute), and every candidate is linted against the base body (no new casts,
`volatile`, `register`, pragmas, asm, pointer aliases, locals the base does not declare, dummy locals or self-assignments,
scope-only blocks, duplicated statements or helpers, unreadable statements). Passes: swap, move, declorder, hoist, sink,
inline, split (name a temporary: restores base names, or `--temp 'TYPE NAME = EXPR'` hints that the worker names),
ifelse, earlyret/unelse, forwhile, commute, marker (`--markers FILE` with `PERM_GENERAL(a, b)` / `PERM_LINESWAP(...)`
alternatives, decomp-permuter style; landed text never has markers). `--only commute,swap` / `--skip` pick passes. The
certified diff is classified (stmt-reorder, decl-order, named-local-split/merge, loop-form, if-else-arms,
early-return-shape, operand-order) and printed with the mutation chain. Tests: `python3 -m unittest test_source_perm`.

## ctx.py
`ctx.py 0x552060` prints the extent (`function_extent_audit.json` if listed,
else the CFG-closed span up to the next known entry; manifest length and Ghidra
size are shown beside it), manifest rows, annotations and `claimed.py` output,
each owning TU's `// VC6FLAGS`, an objdump listing whose call/jmp targets and
absolute operands are named (manifest > annotation incl. LIBRARY >
`library_map.json` > Ghidra), the globals and strings referenced, Ghidra callers,
every RTTI vtable slot that holds the address, and ledger rows. `--json` returns the same data.

## classcheck.py
Compiles a probe TU through the worktree's `scripts/vc6/vc6cl.sh` (with
`VC6_FLAGS=/nologo /c /Od /DNDEBUG`; /Od keeps the probe destructor's vptr store, and layout does not
depend on optimisation). The probe stores `sizeof` and each member's
`offsetof` in initialised globals, and those values are read back from the .obj.
A derived probe class with one extra virtual gives the declared primary vtable slot count.
It then checks the class against allocation sizes, constructor field stores, RTTI and the retail vtable slot
counts, and lists the manifest name and status of every retail slot. Every
other definition of the class under `match/` is probed too: same-named
members at different offsets, or a larger `sizeof`, are reported as a
CONFLICT, and smaller views are listed for information.

## attempts.py
`add` records an attempt: address, TU, flags (read from the TU when not given), variant,
raw/positional/multiset score, delta, agent, date and the source sha256.
`import` seeds the ledger from `CAPPED at / RESIDUAL / PARTIAL / best … N%`
comments in `match/**/*.cpp` (attributed to the next FUNCTION annotation) and
from the `| 0xADDR | … | N% |` tables in `$GAG_ATTEMPT_REPORTS/**/report.md`.
Imported rows carry `status: "imported, unverified"` and the `file:line` they
came from. Re-running `import` adds nothing new.

## libmatch.py
Cuts every code section of every LIBCMT.LIB member at its function symbols,
then searches .text for each function with its relocation fields as wildcards.
It keeps functions that are 8 bytes or longer and found exactly once. The manifest has no LIBRARY
rows, so the diff is taken against the `// LIBRARY:` annotations and against body claims.

## refaudit.py
For each matched row it reads `<tu-stem>.obj` from `build-vc6` (worktree first, then
main) and skips the row if the bytes outside relocation fields differ from retail. For each DIR32 field to an
external symbol with no manifest address it records retail dword − our addend. A symbol
with two or more implied bases is listed with the fields and objects behind each base.

## tpl_audit.py
Read-only audit of template-instance COMDATs over a built objdir (`build-vc6/gate`). Link order is
`stubgen.link_order` (the lowest retail address any manifest row of the TU claims), and LINK keeps
the first definition of a COMDAT, so the first definer is the winner. `tpl_audit.py build-vc6/gate`
prints one line per template symbol that two or more objects define (`>` marks the winner, `Y/N/?/-`
is "winner equals retail at the symbol's first manifest address", size in hex) and then the divergent
list (definers differing in size or relocation-normalised bytes). `--instances` groups per template
class, `--instance SUBSTR` filters, `--all` adds non-template COMDATs, `--json OUT` saves the rows.
`--multi-g` lists template `??_G` symbols the manifest places at 2+ retail addresses and runs
`ghidra x-ref to` on each (CALL vs DATA references and the calling functions); `--no-ghidra` skips that.
Equality needs `GAMEMD_BINARY`. Test: `python3 -m unittest test_tpl_audit` from this directory.

## Known limits
- tpl_audit: instance names come from the repo's own demangler (`idiom_lift.demangle`); a symbol it cannot parse
  falls back to the leading part of the template id. Equality compares only the symbol's first manifest address.
- ctx: the CFG extent is only a lead (an indirect `jmp [table]` ends the walk, so a
  switch body can be cut short). Disassembly is linear objdump over that span.
- classcheck: the member parser uses regular expressions (no bitfields, no commas inside template arguments,
  no nested bodies). Private members are reached with `#define private public`
  in the probe only. Mined constructor offsets below the first own member are
  attributed to the base and not checked. A class that models its vptrs as
  fields (the `_layout` style) has no C++ virtuals, so its slots are not
  checked. An "interior" store only means the offset lies after a member's start, not that it lies inside the member's extent.
- libmatch: it only knows LIBCMT; anything ambiguous (for example memcpy and memmove, which are
  identical) or shorter than 8 bytes is skipped. A unique byte match can still be a
  different routine with the same bytes. Name disagreements with annotations are leads, not facts.
- refaudit: it only sees objects already built under the canonical
  `<tu-stem>.obj` name (76 objects, 445 functions at the time of writing). Other names are treated as
  experiments and ignored.

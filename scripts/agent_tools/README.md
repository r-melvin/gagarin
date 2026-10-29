# Agent tools

Workflow tools for working, packaging and landing matched functions. Everything is written
against this repo's own data: the pinned retail `gamemd.exe` (read at run time, never stored), the
manifest and annotations, `scripts/data/*.json`, the VC6 toolchain and the `build-vc6` objects. They
decide no binary fact; the match/verify gates stay the oracle.

Requirements: python3, binutils `objdump`, the `ghidra` CLI project over the exe (ctx callers
only), the VC6 toolchain (classcheck, gates).

Environment (all optional except the binary):
`GAMEMD_BINARY` (your retail exe; SHA-256 checked; there is no default),
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
| work one function | `ctx.py ADDR` (extent, claims, flags, named listing, callers, vtable slots), `trivgen/` (exact leaf shapes), `../vc6/idiom_lift.py`, `attempts.py` (what was already tried), `aligned_diff.py` (how close a partial is) |
| layout | `classcheck.py CLASS` (header vs binary, conflicting views) |
| package | `delivery/pkt.py init/span/score/bind/finish`, or `delivery/branch2packet.py` for a branch-style worker |
| land | `delivery/pktlint.py`, `delivery/pktrebase.py`, `delivery/batchland.py` / `land/land_bundle.sh`, `land/inc_gates.sh`, `land/verify_safe.sh` |
| lead lists (report only) | `delivery/placement_leads.py`, `delivery/ini_names.py`, `delivery/flagsweep.py`, `delivery/permute_queue.py` |

Skills (`skills/`, installed with `skills/install.sh`): `gagarin-packet-worker`, `gagarin-lander`,
`gagarin-orchestrator`; the agent templates are in `agents/`. The install script symlinks into
`~/.claude/skills` and `~/.claude/agents`; copies already there are left alone.

Tests: `delivery` (`python3 -m unittest tests.test_delivery`), `land` (`python3 -m unittest test_land`,
`python3 selftest.py`), `trivgen` (`python3 -m unittest test_trivgen`), all from their own directory.

Not shipped: `cache/` (rebuilt: `ghidra_functions.json` from the ghidra CLI, `vtable_slots.json` from
`../vc6/vtable_slots.py`), caches, run outputs, one-off scripts of past migrations.

`<state>` is the untracked, local `state/` folder (the main checkout's when the worktree has none).

| tool | what it answers | output |
|---|---|---|
| `ctx.py ADDR [--json]` | everything about one function before you draft it | stdout |
| `classcheck.py CLASS [--header H]` | does this header's layout agree with the binary, and which other headers define the class? | `<state>/orchestration/class_reports/CLASS.json` |
| `attempts.py add/show/search/best/import` | what has already been tried at this address? | `<state>/orchestration/attempts.jsonl` |
| `libmatch.py [LIB...]` | which .text functions are VC6 CRT, by bytes? | `<state>/orchestration/library_map.json` |
| `refaudit.py [--json OUT]` | do unbound global references agree across TUs? | stdout / JSON |
| `aligned_diff.py --obj O --sym S --addr A --len L [--hunks]` | how close is a partial once insertions/deletions are aligned (LCS under diff_retail's reloc-normalised equality), and where are the mismatching runs? | stdout |

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

## Known limits
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

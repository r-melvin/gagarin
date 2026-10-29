# Landing tools

Faster landing of READY packets on main. Everything here is local tooling; it edits no
tracked file of the repo it is pointed at (it works in scratch worktrees) and the one
tracked-script change it proposes is a patch, not applied (`verify_all_tmpdir.patch`).

Shell is bash. Python 3 only; no new dependencies. Needs the usual local pieces: the
VC6 toolchain (`toolchain/` symlink is added to scratch worktrees automatically), Wine,
the retail `gamemd.exe` (`GAMEMD_BINARY`, default is the path the landers use) and
`reccmp-decomplint` on PATH (the lint gate is skipped if it is missing).

## Quick use

```bash
L=scripts/agent_tools/land

# 1. Land several READY packets: apply, full gates once, bisect+drop culprits, one commit per packet.
$L/land_bundle.sh <scratch>/w5-c027 <scratch>/w5-nearmiss <scratch>/w5-vecdel \
    --symmap <scratch>/w5-c027/gate/map_C027.json          # extra symbol maps if not inside READY/
#    ... prints the branch; add --ff to fast-forward the repo's checked-out branch (guarded).

# 2. Packet prep / bisecting: incremental gates on the current worktree (change = tracked diff vs HEAD).
cd <scratch>/prep-x/wt && $L/inc_gates.sh --symmap READY/symbol_map.json

# 3. The same checks, everything, from scratch:
$L/full_gates.sh --base main

# 4. verify_all without the shared /tmp/va_*.obj files:
$L/verify_safe.sh --shard 0/8 --jobs 4        # or --tu match/x/y.cpp ... ; run from (or --tree) a worktree
```

## What is here

| file | role |
|---|---|
| `land_bundle.sh` / `land_bundle.py` | the bundle lander (below) |
| `gates.py` (+ `inc_gates.sh`, `full_gates.sh`) | all gates, `--mode inc` (default for prep/bisect) or `--mode full` (the bundle gate) |
| `landlib.py` | packet parsing, manifest-delta merge with collision checks, include index, git helpers |
| `sectioncmp.py` | sections.py + secmatch.py merged: per-object COFF section comparison (header timestamps ignored) |
| `verify_safe.py` / `.sh` | verify_all wrapper with a private temp dir per run and per TU, `--tu/--shard/--jobs` |
| `verify_all_tmpdir.patch` | proposed fix for `scripts/vc6/verify_all.py` itself, with 3 tests (NOT applied) |
| `check_index.py` | proves the include index against the real VC6 preprocessor (`cl /E`) |
| `compare_modes.py` | runs inc and full on a historical commit with independent cold caches and compares them |
| `selftest.py` | end-to-end scenarios for the lander (good, colliding, regressing, forbidden-word, layout-breaking, duplicate-claim packets; ff guards) |
| `test_land.py` | fast unit tests (`python3 -W ignore -m unittest test_land`) |
| `status_rotate.py` | port of the landers' status.py (STATUS.md rotation), optional via `--status-para` |
| `cache_tool.py` | `stats` / `gc --days N` / `clear` for the object cache |
| `bench_old_flow.py` | times the landers' manual sequence, for comparison |
| `legacy/` | the w4 scripts these replace, kept for reference |

## land_bundle

`land_bundle.sh [options] PACKET...` (PACKET is a READY dir or its parent).

1. **Apply.** A scratch worktree is cut from `--base` (default: HEAD of `--repo`). Per packet, in order:
   `git apply --3way --index` of `patch.diff` with the `scripts/data/match_manifest.json` hunks
   excluded (the delta is authoritative; some packets' patch.diff also carries manifest hunks, and
   some of those contain the `_change` bookkeeping key that must not reach the manifest), then
   `manifest_delta.json` merged into the manifest as the previous packets left it (written
   byte-identically to the tracked format: `indent=1`, no trailing newline). Rejected at this stage,
   packet dropped and reported, bundle continues:
   - no READY files / no parseable "Proposed commit message" (fenced, 2-space, 4-space or plain);
   - patch touches a symlink (mode 120000) or a path outside `match/`, `scripts/data/*.json`,
     `STATUS.md`, `progress.svg` (`--allow-path REGEX` to permit, e.g. a tooling packet);
   - patch does not apply with `--3way`;
   - delta collisions: explicit add over an existing row; two packets adding one address; a packet
     changing/removing a row an earlier packet already changed differently; change/remove of a missing
     row; old-symbol mismatch; rows missing tu/sym/len/status; rows naming a TU that is not in the tree.
   Warning only: a row with no op marker that replaces an existing row with a different tu/sym.
   A throwaway commit records each prefix state (refs under `refs/land-wip/`, deleted at the end).
2. **Full gates once** on the whole bundle (`gates.py --mode full`).
3. **Bisect.** If a gate fails, the failing gates are run in incremental mode on prefixes (binary
   search, assuming a failing prefix stays failing) to find the first packet at which they fail. That
   packet is dropped, then run **alone** against the base to say whether it is broken by itself or only
   interacts with earlier packets (`--no-solo` to skip). The bundle is re-applied from scratch without
   it and the full gates run again, up to `--max-rounds` (4). A failure that does not reproduce in
   incremental mode is reported as unattributable and nothing lands.
4. **Commits, only after a pass.** One commit per packet (message from the packet README, tree of that
   prefix, `.github/assets/progress.svg` regenerated from that prefix's manifest, which is what
   `scripts/hooks/pre-commit` does and `commit-tree` would skip), on branch `--branch`
   (default `land/<timestamp>`). Optionally STATUS.md is rotated into the last commit
   (`--status-para FILE --status-prev-title T`).
5. **Fast-forward** only with `--ff`: a single `git merge --ff-only`. Refused (exit 3, branch left in
   place, repo untouched) unless the repo HEAD still equals the base, no touched tracked file has local
   changes, no incoming path lands on an untracked or **ignored** file or directory, and no incoming
   path goes through or onto a symlink. This is the no-data-loss rule made executable: git itself
   silently replaces ignored files.

Symbol maps for the strict relocation check are every `symbol_map*.json`, `symmap*.json` or `map_*.json`
(a `{symbol: address}` object) found under the packet's READY dir, plus `--symmap`. Entries that agree
are merged; a row that fails with the merged map is retried with each file alone (TU-local `$L` labels
differ between clusters). `waive_strict.txt` in a packet (one hex address per line) or `--waive` skips
a known-acceptable strict failure (listed as waived, never silent). Likewise `words_ok.txt` in a packet (one
regex per line) or `--allow-word` marks added lines the word check should ignore, for names the binary attests.

Not done by the bundle: the padding_scan.json refresh (needs a Ghidra function export), commit-message
editing, and pushing.

## gates.py

Gates, in order; each prints `GATE name PASS|FAIL|SKIP secs detail`; logs and `summary.json` are in the
run dir (`--run`, default `<scratch>/land-runs/run-*`).

| gate | full | inc |
|---|---|---|
| static | include index of the whole tree resolves every quoted include, no tracked symlinks, manifest TUs tracked, no unknown manifest keys | same |
| compile | `build_project.py --jobs N` + `--check` into the run dir: ONE compile pass that replaces compile_all.sh's TU loop, verify_all's compiles and the separate project build | whole tree through the object cache: hit = copy, miss = compile |
| layout | every `match/_layout/*.h` compiled standalone via an includer outside the tree (compile_all.sh wrote `_ca_*.cpp` into the tree) | only layout headers whose closure holds a changed file |
| verify | every `matched` row (raw_match, then diff_retail), run in parallel from the built objects | same, affected TUs only |
| strict | `raw_match` + strict `verify_relocations` on rows added/changed in the manifest (diff vs base, so no packet needed) | same |
| tests | unittest discover | only if something under `scripts/` changed (the manifest counts, so effectively always; it takes 0.2 s) |
| dups, naked | `check_duplicates.py`, `check_naked.py` (whole tree, seconds) | same |
| dupdefs | strong duplicate external symbols across all objects | same (unaffected objects from the cache; per-object symbol lists cached) |
| sections | all objects vs base objects | affected objects only |
| lint | `reccmp-decomplint` on touched files, new error types vs the base file | same |
| words | added lines + commit message vs the forbidden-word list; paths outside the allowed set | same |

**Affected set (inc).** Changed `.cpp`; every TU whose include closure holds a changed header, taken
in the NEW tree and the BASE tree (so deleted/moved headers count); TUs of added/changed/removed manifest
rows (old and new TU); everything if `scripts/vc6/vc6cl.sh` or a non-test script under `scripts/vc6/`
changed. The include index follows MSVC's lookup (including file's directory, then each includer's),
over-approximates (an include in a dead `#if` branch counts) and is checked against `cl /E`
on all 1,318 TUs: `check_index.py` reported 0 gaps and 0 over-approximated entries.

**Object cache** (`$LAND_CACHE`, default `~/.cache/gagarin-land`). Content-addressed: key = sha256 of
the compiler id, `vc6cl.sh`, `VC6_FLAGS`, TU path, its `VC6FLAGS` marker and the content of every
file in its closure, so it cannot go stale; it only grows (~10 MB per full set, `cache_tool.py gc`).
COFF headers carry a timestamp, so objects are compared by section, never by file hash.
`full` never reads the cache for the new side (fresh `build_project`); its base side is read from the
cache (objects from an earlier run: independent of this run) and only built from a scratch base worktree
on a miss. After a passing full run the new objects are added to the cache, so the next packet's base is
already there.

**Whole-tree compile check in inc mode is a cache lookup, not a shortcut:** a TU whose key is not in the
cache is compiled. The first inc run on a cold cache costs one full compile (about 15-25 s with 16 jobs).

## Measured (results/measurements_2026-10-22.txt)

Change under test: packet w5-c027 on 2ab281c (47 files, 93 manifest rows). Machine load average 8-17
from other agents during every run, old and new alike.

| | wall |
|---|---|
| landers' sequence, run one stage after another (verify_all in 8 parallel shards): compile_all 98 s, verify_all 69 s, build 15 s, base build 16 s, lint 5 s, rest < 1 s | **204 s** |
| `gates.py --mode full`, base objects in the cache (steady state) | **30 s** (6.7x) |
| `gates.py --mode full`, cold cache (base built from scratch too) | **43 s** (4.8x) |
| `gates.py --mode inc`, warm cache (steady state; includes the whole-tree compile check) | **2.6 s** (79x) |
| `gates.py --mode inc`, cold cache (first ever run: compiles the whole tree) | **12 s** (17x) |
| `land_bundle.sh`, 3 packets, apply + full gates + 3 commits | **33 s** for all three (old: that sequence per packet) |

Caveat: this old-sequence figure is machine time for the scripted stages (3.4 min). The 15-30 minutes
quoted for a landing includes waiting for contended shards and hand steps that a script does not
reproduce; the bundle removes them, and divides the full-gate cost by the number of packets.
Original serial `verify_all.py` alone took 5 min 35 s on this tree.

## Agreement of inc and full

`compare_modes.py --commit C` runs both modes with separate cold caches and compares gate verdicts, the
regressed-row set, the failing strict-row set and the exact set of changed/added/removed sections.
Result on four historical commits against their parents: AGREE on all four (2fc2deb, 2ab281c, 1a6c77b,
ccff209): identical gate verdicts, identical (empty) regressed sets, identical strict-failure sets,
identical changed-section sets (8, 19, 42 and 25 sections in 7, 11, 8 and 18 TUs), and full found no
changed object outside the affected set. The strict gate FAILs on the three historical commits whose
packets' symbol maps are gone (`no unique matched or explicit binding`), identically in both modes;
1a6c77b's words gate also fails in both modes on a binary-attested RTTI class name that matches a word-list entry
(a human override, see `--allow-word` and `words_ok.txt` below).

```bash
python3 $L/compare_modes.py --repo . --commit 2ab281c
```

## Differences from the landers' sequence (read before trusting a green run)

- compile_all.sh is not run. Its TU loop is the same compile as `build_project` (same wrapper, same
  cwd, same flags); the layout loop is reproduced by the `layout` gate. compile_all also compiled
  untracked `.cpp` files in the tree; a bundle worktree has none.
- verify_all.py is not run as a program; `verify_all.verify()` (its oracle) is imported from the tree
  under test and applied to the objects `build_project` produced. The verdict logic is the same code.
  "Partial rows are not re-measured" is inherited.
- The section gate FAILS only if a function that is `matched` in the base, whose row the change does not
  touch, has different section bytes (relocation-only differences are listed, not failed). The landers'
  secmatch pairing is kept as `moved`.
- Lint uses the base file content written to a temp file rather than a second worktree.
- check_duplicates.py globs the tree's files, tracked or not; in a bundle worktree that is the tracked set.
- STATUS.md text: `status_rotate.py` keeps the landers' fixed sentence about the last diagnostic link.

## Housekeeping

Run dirs (`<scratch>/land-runs/`) keep logs, objects and summaries; delete old ones freely. Scratch
worktrees are removed at the end of a bundle (`--keep` to inspect them). A crashed bundle can leave a
worktree under its `--work` dir and refs under `refs/land-wip/`: `git worktree prune` and
`git for-each-ref refs/land-wip` show them.

## Tests

`python3 -W ignore -m unittest test_land` (26 fast tests), `selftest.py` (about 6 minutes: nine
bundle scenarios on a throwaway clone, including the fast-forward guards against untracked and
ignored files), `check_index.py TREE`, `compare_modes.py`.

## Environment

`LAND_MAIN_REPO` (default the main checkout), `LAND_TOOLCHAIN`, `GAMEMD_BINARY`, `LAND_CACHE`, `LAND_RUNS`
(run dirs). Wine parallelism is `--jobs` (default min(16, cpus/2)); lower it when other agents are running.

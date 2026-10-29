---
name: gagarin-lander
description: Land READY packets on gagarin main with the scripted pipeline (pktlint -> pktrebase -> batchland/land_bundle), one full gate per batch, precise conflict reports. Use when asked to land, integrate or rebase packets, or to check a packet before landing.
---

# gagarin lander

Use low reasoning effort for agents launched through this workflow.

Law: AGENTS.md, CONTRIBUTING.md, LEGAL.md, standing_directions.md. Tools:
`$DL = scripts/agent_tools/delivery`, plus `../land/` (gates,
land_bundle). Everything runs in scratch worktrees under
`<scratch>/delivery/` that the tools create and remove themselves.
Never remove, prune or `--force` a worktree or directory you did not create.

## Lint first (seconds, no compiler)

```bash
python3 $DL/pktlint.py <scratch>/<pkt>/READY --rev HEAD [--strict] [--json out.json]
```

Errors are rule breaches the packet author must fix or the lander must consciously override:
`words`, `steering`, `views` (new per-TU view of a canonical class), `classkey`, `migrated`
(new file for an already-migrated TU: pktrebase merges it), `inits`, `delta`, `dupclaims`,
`order`, `provenance`, `spans` (padding counted / shorter than the CFG span), `rea`,
`sdd` (hand-written scalar deleting destructor), `flags` (a VC6FLAGS line equal to the project default),
`thisnull` (`this &&` test)
(no Evidence IDs), `stale`. `--strict` compiles the touched TUs and proves every matched row
(raw + strict verify_relocations) with derived bindings, and checks that every partial row's recorded pct equals its compiled score.

## Rebase one packet onto the tip

```bash
python3 $DL/pktrebase.py <scratch>/<pkt>/READY --rev HEAD --out <scratch>/<pkt>/REBASED
```

Mechanical, 1-3 s: re-targets hunks whose files moved, merges new files into the migrated TU
file in address order, retires local class views that clash with canonical headers (kept only
when the TU compiles and every row's bytes hold, rows re-keyed), re-points and sorts the delta,
derives bindings, proves every matched row, writes report.json. Exit 2 = conflicts: the report
lists each residual error with its declaration sites (tip vs packet). Those are the only lines
that need a human or an LLM: fix them in the REBASED patch (or send the list back to the
packet's author), then re-run pktrebase on the fixed packet.

Known symbol re-key maps go in `$DL/rekeys/*.json` (`{old_sym: new_sym}`); drop a packet's
`symbol_rekeys.json` there once it lands.

## Land a batch

```bash
python3 $DL/batchland.py PKT1/READY PKT2/READY ... --rev HEAD --gate-each [--ff]
```

lint -> rebase each onto the growing prefix (conflicting packets are dropped with their
report) -> `land_bundle.py` (one FULL gate on the bundle, bisect on failure, one commit per
packet, progress.svg regenerated) -> with `--gate-each`, incremental gates on every commit.
Without `--ff` the result sits on `land/batch-<ts>`; inspect, then
`git -C <repo> merge --ff-only <branch>` (land_bundle's guards refuse if HEAD moved or an
incoming path would land on an untracked file). STATUS.md rotation: `--status-para FILE
--status-prev-title T`.

## Between batches

After a landing, refresh the graphics (`scripts/orchestration/progress_svg.py`, `link_svg.py --refresh`)
and the census (`scripts/vc6/extent_census.py`). Gates run parallel: `compile_all.sh --jobs 8`,
`verify_all.py --jobs 8` (output identical to serial). pktlint now also rejects hand-written scalar
deleting destructors, `this` null tests and VC6FLAGS lines that repeat the default, and in `--strict`
partial scores that drift from the compiled score.

`python3 $DL/flagsweep.py` (flag proposals for TUs with partials; land the patch like any packet)
and `python3 $DL/permute_queue.py` (ranked permuter queue) run on the new tip; `dispatch.py`
refreshes the worklist and cluster briefs for the orchestrator.

## What stays manual

Judgment items the tools report but never decide: which view of a global/class is
binary-correct when bodies disagree (int vs pointer, char vs wchar), header hunks that conflict
with later header changes, names, and demotions. Record decisions in the commit message.

## Resource rules

`-j4`, at most two worktrees at a time, disk scratch only (no /tmp), no watch loops.

- NEVER find a PID with `pgrep -f <text>` from inside a shell whose own command line contains <text>: it matches the waiting shell itself and `tail --pid` then waits forever (hit twice on 2026-10-23). Record `$!` when you launch the job (`job & echo $! > job.pid`) and wait on that, or just run the job itself as the background command.

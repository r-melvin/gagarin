---
name: gagarin-packet-worker
description: Produce a READY packet for the gagarin VC6 byte-matching decomp with the scripted worker loop (pkt.py init/span/score/bind/finish) instead of ad-hoc helpers. Use when a brief asks you to match functions and deliver patch.diff + manifest_delta.json + symbol maps + README for a lander.
---

# gagarin packet worker

Use low reasoning effort for agents launched through this workflow.

Law first: AGENTS.md, CONTRIBUTING.md, LEGAL.md, then the brief and
`the standing directions in your brief`. This skill only removes the mechanical work;
it decides nothing about bytes or names.

Tools live in `scripts/agent_tools/delivery/` (call it `$DL`).
Everything below is deterministic; do not rewrite these scripts in your packet dir.

## 1. Start (one command)

```bash
python3 $DL/pkt.py budget                 # refuses when RAM/swap/worktrees/compilers are over budget
python3 $DL/pkt.py init <name> --base HEAD
cd <scratch>/<name>     # pkt.env lives here; all later commands run here
```

`init` makes the worktree at `wt/` (disk-backed, never /tmp), links the toolchain, writes
`READY/base_sha` and `READY/rows.tsv`, and prints the rule checklist. `-j4` is the cap.
Never `git add -A`/`.`/`-N`; never stash, clean or reset in any tree you did not make; never
touch the main checkout.

## 2. Spans and status before you write code

```bash
python3 $DL/pkt.py span 0x6F4A40 0x6F7930 ...
```

Prints the CFG-closed span (the manifest `len`), the extent-audit override when one exists,
Ghidra's size, the current manifest row and who already claims the address. Worklist size
columns are padded with NOP/INT3; the linter rejects rows that count padding.

Ground truth is the REA MCP (`mcp__rea__*`: analyze_function, procedure_assembly,
read_function_instructions, xrefs, read_bytes) with the ghidra CLI as the stated fallback.
Cite REA Evidence IDs (`ev_xxxxxxxx`) in README.md; the linter flags packets without them.

## 2b. Start from a generated skeleton

```bash
python3 $DL/skeleton.py 0xADDR ... --out wt/match/<module>/<file>.cpp --rows READY/rows.tsv
```

The draft has the receiver class and vtable slot (from RTTI), the calling convention and RET n,
one GG_STATIC_ASSERT per member access seen in the instructions, callee/global/string
declarations named from the manifest, and the disassembly as a comment; the body is TODO. Edit
the body, never the facts (if a fact is wrong, say so in the README with the instruction).

## 3. Write code, then score

```bash
python3 $DL/pkt.py score wt/match/<module>/<file>.cpp [0xADDR ...]
```

Compiles the TU with the project wrapper (VC6FLAGS honoured), finds each `// FUNCTION:` claim,
fills `READY/rows.tsv` (symbol from `FUN_<addr>` names, len from the CFG span), and prints
`100.0 raw` or the diff_retail percentage. For named symbols put the mangled symbol in
`rows.tsv` yourself. Three materially different attempts, then cap and record the delta.

Rules the linter will enforce on your packet (fix them as you go):
- include canonical headers (`match/_layout/*.h`, RTTI headers); never a new per-TU view of
  such a class; add binary-proven members (with offset asserts) to the canonical header instead;
- `class`/`struct` keyword as RTTI records it;
- new code for an already-migrated original TU goes into that TU file (`// Original translation unit`);
- functions in ascending address order; SPDX + Provenance header on every new file;
- no volatile on accesses/locals, no aliases, no steering casts, no asm, no `#pragma optimize`,
  no `if (1)`; no forbidden words (the local list, see README; pktlint `words`) and no private-source names;
- static-initialiser shapes are held for the migration.

## 4. Prove bindings

```bash
python3 $DL/pkt.py bind
```

Runs raw_match + strict verify_relocations on every exact row, derives bindings from symbol
names (FUN_/DAT_), the retail IAT (`__imp__`), `$L` positions and the central bindings file,
and writes `READY/symbol_map.json`. Anything still `UNBOUND` needs a real binding or a demotion.

## 5. Finish

```bash
python3 $DL/pkt.py finish        # results.tsv, manifest_delta.json, README skeleton, gates.log, pktlint, backup
```

Fill the README's "Held" section and the proposed commit message (trailer
`Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>`), then re-run `finish` until pktlint
reports 0 errors. The packet is backed up to `~/Projects/backups/int-evidence/<name>/`.
`python3 $DL/pkt.py done` removes only the worktree `init` created.

## Waiting on long jobs

No watch loops. Run the long job itself in the background and let the harness notify you, or
`tail --pid=<pid> -f /dev/null`.

- NEVER find a PID with `pgrep -f <text>` from inside a shell whose own command line contains <text>: it matches the waiting shell itself and `tail --pid` then waits forever (hit twice on 2026-10-23). Record `$!` when you launch the job (`job & echo $! > job.pid`) and wait on that, or just run the job itself as the background command.

## Branch-style work

If you commit on a branch instead of using `pkt.py`, build the packet with
`python3 $DL/branch2packet.py BRANCH --rows rows.json [--removed removed.json] --evidence "<REA ids / tool>" --lint`
and fix what pktlint reports before handing it over.

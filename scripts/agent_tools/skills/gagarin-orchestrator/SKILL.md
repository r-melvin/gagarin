---
name: gagarin-orchestrator
description: Run the gagarin delivery loop end to end with scripts, not inference — refilter the worklist, dispatch clusters, sweep flags and queue the permuter, lint and rebase incoming packets, land batches with one full gate, and keep the proofs. Use when coordinating workers and landers or deciding what to automate next.
---

# gagarin orchestrator

Use low reasoning effort for agents launched through this workflow.

Law: AGENTS.md, CONTRIBUTING.md, LEGAL.md, `the standing directions in your brief`.
`$DL = scripts/agent_tools/delivery`. Every tool below is
deterministic and byte-gated; the model's work is only what the tools report back. Resource rules
for every agent: `-j4`, two worktrees, disk scratch (`gagarin-scratch/`), no watch loops, and never
remove/prune/`--force` anything you did not create (the tools keep a created-path ledger).

## The loop

```
dispatch.py  ->  worker (pkt.py, skeleton.py)  ->  READY  ->  pktlint  ->  pktrebase  ->  batchland  ->  main
     ^                                                                                        |
     +------------------- flagsweep.py / permute_queue.py on the partials of the new tip  <---+
```

### 1. Decide what to work on (no model)

```bash
python3 $DL/dispatch.py --top 30            # worklist refiltered vs tip; clusters.tsv; briefs/cluster_<TU>.md
```

Each brief names the migrated TU file to write into, the canonical headers, the addresses with CFG
spans, RA2-twin and family hints. Hand one brief per worker (one cluster, never two workers on one
address). For the partials of the tip:

```bash
python3 $DL/flagsweep.py                    # VC6FLAGS proposals where rows rise and none drops -> packet
python3 $DL/permute_queue.py --scaffold 20  # permuter queue: multiset-identical / RA2-identical first
```

Flags are project-wide: treat `flagsweep.py` output as placement evidence, not as VC6FLAGS proposals.
`python3 scripts/agent_tools/delivery/placement_leads.py` lists files pinned off the default and where
their definitions probably belong. Other worklists: `scripts/data/large_function_shapes.json` (shape class
and idioms of large unrecovered functions; its ctor-dtor and string-lookup labels are hints only),
`scripts/data/partial_residuals.json` (residual labels of partials), `scripts/data/shape_families.json`
(unmatched functions with a matched lookalike), `ini_names.py` (field names from INI readers),
`.coordination/claude-orch/wl/m3_data_worklist.tsv` if present (globals/literals/vtables for M3 data).
Branch-style workers: convert with `branch2packet.py BRANCH --rows rows.json [--removed x.json] --lint`.

### 2. Workers

Give them the `gagarin-packet-worker` skill. Their first draft can come from
`python3 $DL/skeleton.py ADDR... --out wt/match/<mod>/<file>.cpp --rows READY/rows.tsv`
(signature, slot, offset asserts, callee/global decls, disassembly comment; body TODO), then
`pkt.py score/bind/finish`. A packet is READY only with `pktlint` at 0 errors.

### 3. Landers

Give them the `gagarin-lander` skill: `pktlint` on arrival, `pktrebase` for stale packets (merge
into migrated TUs, view retirement under byte identity, derived bindings), `batchland --gate-each`
for the batch, fast-forward only after inspection. Act on the conflict lists; do not re-do the
mechanical steps by hand.

### 4. Keep the proofs

- `tests/test_delivery.py` fast; `tests/prove_rebase.py` (tool output vs landed commits);
  `tests/prove_batch.py` (one full gate on a landed range vs the per-packet gates).
- After each batch: drop landed `symbol_rekeys.json` into `$DL/rekeys/`; when fu-symmap is on main,
  regenerate `scripts/data/symbol_bindings.json` (`symmap/sweep.py derive` + `build_bindings.py`).

### 5. What to automate next (ADOPTION.md has the ranked list)

Header-member adoption (closes most residual rebase conflicts), global-view unification under byte
identity, bindings regeneration as a batchland post-step, callee-declaration unifier, family
generators for the remaining 302 families, static-initialiser placement once every TU file exists.

## Incident rule

2026-10-22: a cleanup sweep removed other agents' worktrees. Tools refuse to remove paths they did
not create; agents do the same by hand. When a cleanup is ambiguous, stop and report.

- NEVER find a PID with `pgrep -f <text>` from inside a shell whose own command line contains <text>: it matches the waiting shell itself and `tail --pid` then waits forever (hit twice on 2026-10-23). Record `$!` when you launch the job (`job & echo $! > job.pid`) and wait on that, or just run the job itself as the background command.

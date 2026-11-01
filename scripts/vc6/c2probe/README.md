# c2probe: decision-forcing probe for the pinned back end (diagnostic only)

Concept and hook map after sushi-shi/homm3-decomp (CC0 1.0), the vc6 notes on the shim and
decision forcing. Same back end: `c2.dll` 12.00.8447, sha256 `a0cc45f8...`.

What it answers: for a held near-miss, which single compiler decision differs from
retail? It replays one captured front-end result (`/d1il` once, `/d2il` per run) through a
copy of the toolchain whose `c2.dll` is a shim, forces one back-end decision, and scores the
function against retail. The output is a report: "function X: forcing decision D at site S
reproduces retail". It is never a manifest change and never a source change; reasoning back
to a natural source form that the real compiler turns into the same decision is a separate,
manual step, always verified under the real compiler.

## Fences

* The shim lives only in `toolchain/c2probe/` (ignored, fetched-toolchain side; never committed,
  see LEGAL.md). `scripts/vc6/vc6cl.sh`, `match.sh`, `compile_all`, `verify_all`, `m3_gate`
  and the land gates never see it. Only `c2probe.py` selects it (`VC6_ROOT=...`).
* The shim returns 4 and compiles nothing unless `C2PROBE_DRIVER=1`, which only `c2probe.py`
  sets. A stray build that picks up the probe toolchain fails closed.
* `guard.py` (wired into `pktlint` rule `c2probe` and land gate `c2probe`) fails if the env
  vars are set, the real toolchain `c2.dll` is not the pinned image, an object hashes like one
  the driver produced (`toolchain/c2probe/ledger.tsv`), or a packet file names the marker or
  the probe paths.

## Commands

```
python3 scripts/vc6/c2probe/c2probe.py build                 # overlay + shim (built by the period compiler)
python3 scripts/vc6/c2probe/c2probe.py gate --n 400          # inertness proof (see below)
python3 scripts/vc6/c2probe/c2probe.py gate --negative       # the gate can go red
python3 scripts/vc6/c2probe/c2probe.py probe 0x5A0700 ...    # report to build/c2probe/report.md
python3 scripts/vc6/c2probe/test_guard.py
```

## Inertness gate

For each sampled TU (seeded shuffle of `match/**`): two real compiles must agree outside the
four COFF `TimeDateStamp` bytes (else the TU is skipped as non-deterministic), then the
object built through the shim with no hook installed and the object built with every hook
live (`C2PROBE_FILTER=*`, empty rule sets, logging every decision) must both equal the real
object outside those four bytes. `gate --negative` forces registers and scratch starts with the
hooks live and requires differing objects, so the comparison is known to be able to fail.

## Hooks (C2 RVAs in the pinned image; every site is byte-guarded before patching)

| decision | RVA | forced by |
|---|---|---|
| inline admit/reject at the budget test | 0x19f8c | `C2PROBE_INLINE_FORCE` rule file |
| global register choice per live-range group | 0x24748 | `C2PROBE_REG_FORCE=k:reg` |
| local scratch selector rotation start | 0x33273 | `C2PROBE_SCRATCH_FORCE=k:reg` (EAX/ECX/EDX) |
| tail-merge match count | 0x36afa, 0x3e3e0 | `C2PROBE_MERGE_VETO=k` |
| function entry (root selection) | 0x1995c | `C2PROBE_FILTER` |

A forced object shows what the compiler emits when that decision goes the other way. It does not
show that any source reaches it; the forced decision only states the target for the source search.

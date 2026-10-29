# trivgen: generate and verify C++ for trivial retail functions

Untracked proposal (nothing here edits a tracked file). Written against our own data only: the pinned
retail `gamemd.exe`, the repo's `scripts/vc6/*` gates, `scripts/data/*.json`, the ghidra CLI project over the
exe, and the VC6 toolchain. Disassembly comes from `objdump` over the PE bytes (capstone is not installed);
callers and function bounds come from Ghidra.

## What it does

```
worklist.csv (size <= 32) --> re-filter --> lift --> classify --> emit C++ --> compile --> gates --> READY packet
```

1. **Re-filter** (`data.py`). Start from `<scratch>/worklist/worklist.csv`. Drop anything already in the
   isolated worktree's manifest (main HEAD), anything with a body claim (column-zero `FUNCTION/SYNTHETIC/TEMPLATE/
   LIBRARY/STUB` marker, not a `decl;` one) in main's working tree (including other sessions' untracked files) or
   in the worktree, and anything claimed by in-flight packets (`<scratch>/w5-*/READY`, `w4-*`, `w2-*`,
   `prep-*`, and `<scratch>/w5-mgm`: manifest deltas, `+// FUNCTION` lines of patches, results.tsv rows).
   Statically linked CRT (the span of libmatch's `library_map.json`) is classified `library-region` and not generated.
2. **Lift** (`lift.py`, `x86.py`). The extent is CFG-closed and bounded by the next known function entry (a `jmp`
   to it is a tail call). Straight-line code and forward branches are lifted symbolically: registers hold
   expressions over `ECX`/`EDX` at entry, stack arguments, loads, constants and call results. Loads that a later
   store would change, or that a branch tests and keeps live, become locals. Forward conditional jumps become a tree
   of blocks (no loops).
3. **Classify** (`patterns.py`). Each lifted function gets a pattern name (counts are printed by `trivgen.py patterns`):
   `empty`, `empty-retn`, `const-int`, `const-zero`, `const-bool`, `const-address`, `member-getter-{dword,word,byte}`
   (also `-zx`/`-sx`), `global-getter-*`, `member-setter`, `member-multi-store`, `member-rmw`, `global-setter`,
   `return-this`, `address-of-member`, `bool-test`, `arith`, `thunk`, `global-receiver-thunk`, `member-forwarder`,
   `vtable-thunk`, `import-thunk`, `call-wrapper`, `store-then-tail-call`, `static-init-fp`, `static-init-stores`,
   `branching`, plus `unsupported:<reason>` and `library-region`.
4. **Calling convention and receiver** (`emit.py`, `calleesig.py`, `callers.py`), from evidence only:
   - vtable membership (`scripts/agent_tools/cache/vtable_slots.json`, from the binary's RTTI): a function in any vtable is a
     `__thiscall` member (receiver view), and the owning RTTI class and slot are recorded in the comment and in
     results.tsv. Names stay placeholders (`FUN_<addr>`, `vf_<slot>` for virtual calls, `unknown_<off>`, `DAT_<addr>`).
   - entry-register use: ECX used as a pointer = member of the address-scoped view `Obj_<addr>`; ECX as a scalar =
     fastcall free function; EDX also read = fastcall; `ret n` with neither = `__stdcall`; otherwise `__cdecl`.
     /Gr is the default so free functions carry no explicit `__fastcall`.
   - callee conventions at call sites come from the callee's own bytes: the `ret n` values, and a forward dataflow over
     its CFG for ECX/EDX read before write (calls clobber them). `add esp,n` / `pop ecx` after the call means cdecl.
     Imports are resolved through the PE import table (`__declspec(dllimport)`, name attested by the image).
   - caller patterns (`callers.py`, Ghidra x-refs plus the bytes before each call site) are reported per row in
     results.tsv (`callers=N ecx_set=.. edx_set=.. push=..`) as corroboration; they do not override the above.
   - When the owning RTTI class has a canonical header, the tool still emits an address-scoped view and does not touch
     the header: the canonical `_layout` headers declare no virtuals for most owners, so adding `vf_k` members would
     shift their vtables. See "Header patches" below.
5. **Emit** (`emit.py`, `gen.py`). One `.h/.cpp` pair per original TU id (`trivial_tuNNN_methods.*`; static-initialiser
   shapes go to `trivial_tuNNN_init_methods.*`), module directory voted from `func_to_tu.csv` (default `core`), functions in
   ascending address order, `// FUNCTION: GAMEMD 0x..`, provenance `own-binary-via-Ghidra`, views with `unknown_XX` gap
   members and a `GG_STATIC_ASSERT(offsetof(..))` per member, `// GLOBAL:` markers on externs. A TU that would need two
   incompatible declarations of one global spills into the next file (`_a`, `_b`, ...).
   Several source spellings are tried per function (`emit.variants`): narrow integer type (`unsigned char`/`bool`/`char`),
   comparison result as expression / `? true : false` / `int`, void vs value return when EAX is only a helper register,
   branch layout (`if (!c) {fallthrough}` / `if (c) {taken}` / `a && b` boolean expression / `if (expr) return A; return B;`),
   snapshot locals inlined or kept, narrow stack parameters. Variants that compile to identical text are dropped. No
   `volatile`, no alias pointers, no asm; the only casts are `(unsigned char)`/`(unsigned short)` narrowing views of a
   wider register that the binary compares at byte or word width.
6. **Verify** (`verify.py`, `trivgen.py run`). Every generated TU is compiled with the worktree's `scripts/vc6/vc6cl.sh`
   (flags from the TU, default `/O2 /Gr /DNDEBUG /Gy /MT /Ob2`). A compile error is attributed to its function and that function
   is dropped from the probe TU. For each function: `raw_match.py` must report 100% with zero real diffs, then
   `verify_relocations.py` runs strictly with a symbol map built from the object itself (every symbol whose decorated
   name carries `DAT_`/`FUN_` plus its address, and `__imp__name` resolved through the PE import table). Only
   verified-exact functions are kept; the rest are logged with pattern and reason. The final TUs are rebuilt from the
   exact set only and re-verified by `packet.py` before anything is written.

## Usage

```
python3 trivgen.py setup           # detached worktree at main HEAD in <scratch>/trivgen/wt (+ toolchain symlink)
python3 trivgen.py scan            # candidates.json (re-filtered worklist)
python3 trivgen.py patterns        # pattern counts (pattern_counts.tsv)
python3 trivgen.py run             # generate, compile, verify; keep exact; writes TUs into the worktree
python3 trivgen.py run --only 'member-getter' --limit 50     # subset while developing
python3 trivgen.py diag 0xADDR [--var N] [--brief]            # emit one function, compile, show the aligned diff
python3 trivgen.py packet          # final re-verification, gates, READY packet in <scratch>/trivgen/READY
python3 trivgen.py all             # scan + run + packet
python3 trivgen.py teardown        # remove the worktree
python3 test_trivgen.py            # self-tests (TRIVGEN_COMPILE_TEST=1 adds a compile/negative-verify test)
```

Environment: `TRIVGEN_WT` (worktree), `TRIVGEN_WORK`, `TRIVGEN_READY`, `TRIVGEN_WORKLIST`, `TRIVGEN_TUMAP`,
`TRIVGEN_FUNC_TO_TU`, `TRIVGEN_JOBS` (Wine parallelism, default 4), `GAMEMD_BINARY` (retail exe; SHA-256 is checked).
Run it from a shell with the toolchain symlinked into the worktree; never against main.

## READY packet

`patch.diff` (new files only, explicit paths, base = worktree HEAD), `manifest_delta.json` (rows to add, sorted by
address), `results.tsv` (addr, symbol, %, raw, relocs, status, convention, pattern, evidence), `gates.log`,
`README.md` (proposed commit message, counts, words check), `held.tsv` (every candidate not emitted, with pattern and
reason, for improving the generator), `pattern_counts.tsv`. The packet is also split into `patch_functions.diff` +
`manifest_delta_functions.json` and `patch_initialisers.diff` + `manifest_delta_initialisers.json`: the latter are the
static-initialiser (`__xc` table) shapes that the standing directions defer to the header-initialiser milestone.
`packet.py` runs `check_duplicates.py` and `verify_all.py` (new TUs only, i.e. per-TU) in the isolated worktree with the
manifest delta applied, then restores the manifest.

## Header patches

The tool never edits an existing header. Where an RTTI owner has a canonical header, the lander can fold a function in by
moving its body into the canonical class: for classes whose header declares `vf_<slot>` already (ObjectClass,
MissionClass, the locomotion classes), the member signature to declare is the one printed in the function's view; for
the rest, the canonical headers declare no virtuals, so the view is kept until the vtable is declared. Each generated
`Obj_<addr>` view lists exactly the members and offsets the binary proves.

## Failure taxonomy (what is not generated, and why)

`unsupported:indexed-operand` / `lea-indexed` (scaled index addressing), `branch-target`/loops, `stack-local`, `rep`
string moves, `imul/div/cdq`, x87 integer loads and compares, `undef-reg-read` (register-input helpers),
`library-region` (CRT), plus emit refusals (`pointer-from-call`, `virtual-receiver-mismatch`, `negative-offset`,
`thiscall-on-member-address`, `global-type-conflict`, `mixed-leaf-types`) and verified mismatches (compiler picks another
instruction sequence than the source spellings tried: struct copies through `add ecx,n`, constructor-shaped base calls,
`xor r8,r8` encodings, branch-free clamps).

#!/usr/bin/env bash
# new_run.sh — scaffold a decomp-permuter run directory for one retail address.
#
#   scripts/permuter/new_run.sh <addr> <c-func-name> <mangled-sym> <rundir> <length>
#
# e.g. scripts/permuter/new_run.sh 0x5B2990 gg_IsWithin \
#          '?IsWithin@Dir16@@QBE_NABU1@0@Z' /tmp/iswithin 0x2a
#
# Creates <rundir>/{target.o,compile.sh,settings.toml} and stub base.c /
# shim.cpp.in for you to fill in. The permuter itself is NOT part of this
# repository (MIT, github.com/simonlindholm/decomp-permuter); clone it outside
# the tree and run `permuter.py <rundir>`. See CONTRIBUTING.md (Matching a function).
set -euo pipefail
if [[ $# -ne 5 ]]; then
  echo "usage: new_run.sh <addr> <c-func-name> <mangled-sym> <rundir> <validated-length>" >&2
  exit 2
fi
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ADDR="$1"; FUNC="$2"; SYM="$3"; RUNDIR="$4"
mkdir -p "$RUNDIR"
# Require the full entry-origin span validated against retail: the analysis
# function size may omit a post-call tail or the final bytes of RET.
python3 "$REPO/scripts/permuter/make_target.py" --addr "$ADDR" --len "$5" --out "$RUNDIR/target.o"

cat > "$RUNDIR/compile.sh" <<INNER
#!/usr/bin/env bash
export GG_RUNDIR="\$(cd "\$(dirname "\$0")" && pwd)"
export GG_FUNC=$FUNC
export GG_SYM='$SYM'
exec bash $REPO/scripts/permuter/vc6_compile.sh "\$@"
INNER
chmod +x "$RUNDIR/compile.sh"

printf 'func_name = "%s"\ncompiler_type = "base"\n' "$FUNC" > "$RUNDIR/settings.toml"

[ -f "$RUNDIR/base.c" ] || cat > "$RUNDIR/base.c" <<INNER
/* Plain C restatement of the body, over explicit pointers. pycparser must be
   able to parse this; it is never compiled as written — splice.py lifts the
   body into shim.cpp.in. */
typedef struct Dir16 { short Raw; short Spare; } Dir16;
int gg_abs(int x);

int $FUNC(Dir16 *self)
{
    return self->Raw;
}
INNER

[ -f "$RUNDIR/shim.cpp.in" ] || cat > "$RUNDIR/shim.cpp.in" <<'INNER'
/* The real C++ this project must commit. @BODY@ is replaced by the permuted
   body from base.c; the aliases below bind that body's C names to the real
   C++ receiver and reference parameters. Verify once, by hand, that the alias
   form compiles byte-identically to the committed spelling before trusting a
   score from it. */
struct Dir16 { short Raw; short Spare; };

extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)
#define gg_abs abs

/* ... the real signature ... */
@BODY@
INNER
echo "new_run: scaffolded $RUNDIR — now fill in base.c and shim.cpp.in"

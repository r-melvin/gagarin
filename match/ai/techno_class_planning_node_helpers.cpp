// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x634290 and 0x639F80.

#include "techno_class_planning_node_helpers.h"

int DAT_00AC4B84[24];

// FUNCTION: GAMEMD 0x634290
//
// Node_006386E0::FUN_00634290 -- linear scan of this node's entry array for
// the one whose owner word matches `owner`; returns its index, or -1 when the
// node is empty or nothing matches. The search sits under `if (count > 0)`
// (retail's `OR EAX,0xffffffff` seeds the -1 answer before the guard) rather
// than folding the empty case into the loop test, so an empty node returns -1
// without ever touching `Entries`.
// PARTIAL (42.3%, 11/26 by position; multiset otherwise identical apart from
// register colouring): register roles and every load/compare/increment match
// once the walk is written as a raw pointer increment over `Entries` (retail
// never re-indexes; `ADD ECX,0x4` walks the entry pointer directly) rather
// than `entries[i]`, which is what took this from 3.8% to here. The residual
// is retail's single guarded do-while (`test; jle skip; LOOP: body; inc; cmp;
// JL LOOP`) against cl 8804's loop-rotated form, which peels the first
// comparison out of the loop and runs the remainder as a tighter body that
// falls through to the found case instead of testing it explicitly. Every
// materially different loop spelling tried gives one of these two shapes:
// a `while` with an internal early `return -1` re-tests the guard a second
// time at the loop head (3.8%, both `entries[i]` and pointer-walk); a `do
// {...} while` or an equivalent `goto`-loop with the match test as the body's
// first statement is what cl rotates/peels (this 42.3%, both index and
// pointer forms). No spelling reproduces retail's unrotated single-test loop
// under the locked flags; recorded here rather than spent further.
int Node_006386E0::FUN_00634290(void* owner)
{
    int index = -1;
    int count = this->At_010;
    if (count > 0) {
        Entry_006386E0** entries = this->Entries;
        int i = 0;
    loop:
        if (*(int*)*entries == (int)owner) {
            index = i;
            goto done;
        }
        i++;
        entries++;
        if (i < count) {
            goto loop;
        }
    }
done:
    return index;
}

// FUNCTION: GAMEMD 0x639F80
//
// MATCHED (100.0%, 12/12). Scene_006386E0::FUN_00639F80 -- decrement the
// pending-request counter for this house index, clamped at 0 (not -1: the
// retail formula is `(v-1)<0 ? 0 : v-1`, i.e. `max(v-1, 0)`). Called as
// `scene->FUN_00639F80()` from TechnoClass::ClearPlanningTokens
// (match/ai/techno_class_clear_tokens_methods.cpp, read not edited), where
// the "scene" pointer is really a small house index carried in the receiver
// register rather than a dereferenced object -- this function never reads
// through `this`, only compares and indexes with its bit pattern. Out of
// [0, 24) it is a no-op. The branchless clamp (`DEC`/`SETS`/`DEC`/`AND`)
// reproduces once the ternary's answer (0, not -1) is right and it lands in
// a fresh local rather than back into the variable that fed the comparison.
void Scene_006386E0::FUN_00639F80()
{
    if ((int)this >= 0 && (int)this < 24) {
        int dec = DAT_00AC4B84[(int)this] - 1;
        int clamped = (dec < 0) ? 0 : dec;
        DAT_00AC4B84[(int)this] = clamped;
    }
}

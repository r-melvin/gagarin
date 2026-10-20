// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4072E0.

#include "sorted_list_insert_methods.h"

// FUNCTION: GAMEMD 0x4072E0
//
// Insert a node into a key-ordered circular list and return how many nodes it
// was placed behind.
//
// PARTIAL (26.3%, 10/38; was 7.7%) — the loop rotation is solved and the only
// residual is one dominated null test cl 8804 folds away. Two levers fired:
//
//   * The loop-rotation lever: `while (1) { advance; if (!(whole conjunction))
//     break; body }`, with the negation wrapping the WHOLE conjunction rather
//     than one `if` per clause, gives retail's unconditional `JMP 0x4072EA`
//     back to the advance instead of a bottom-tested copy. That alone moved
//     7.7% -> 13.2% and made everything from the pushes to the `JLE` line up.
//     The earlier spellings recorded below (a `while` with the advance in the
//     condition, a `for (;;)` with per-clause breaks, hand-written `goto`s,
//     `do { } while (1)`, a shared post-loop splice, an inline `Splice`
//     helper, a volatile advance load) all rotate; the negation has to wrap
//     the conjunction. Same lever as 0x40E3E0 / 0x40E4C0 and 0x5B46E0.
//
//   * Reading the cursor's key through a volatile-qualified load in the guard
//     fixes the register naming the earlier passes recorded as a tie-break:
//     with it, EDI holds the node's key and EBX the cursor's, as retail has
//     them, and the node-key load sits below all three pushes. 13.2% -> 26.3%,
//     and the first fourteen bytes are then byte-exact.
//
// Retail loads the neighbour's `Prev` before the first store in both splices;
// writing that load as its own statement reproduces it (no score change on its
// own, the 4-byte shift below dominates, but the block is then exact).
//
// The residual is exactly two instructions: retail's second `TEST ESI,ESI` /
// `JZ` at 0x4072F7, which is dominated by the first one and which cl 8804
// deletes. Ten spellings were measured against it and every one is folded: a
// local `int zero` compared as `(N*)zero`, `((unsigned)cur | 0u) != 0u`, a
// `__forceinline` predicate by value and by const reference, a second name
// copied from the cursor, the clause hoisted out of the conjunction into its
// own `if`, a volatile-qualified read of the cursor variable itself (0.0%, it
// homes the cursor to the stack), and advancing through a second name (2.4%).
// Binding the cursor key to a plain local instead of leaving the volatile read
// in the guard costs the register naming again (18.4%), and doing so without
// the volatile node-key read costs it twice over (7.9%). Treated as the
// dominated-test-folding difference between cl 8447 and 8804.
int __fastcall FUN_004072E0(Node_004072E0* list, Node_004072E0* node)
{
    // The inserted node's key is read once, before the walk; left as
    // `node->Key` inside the comparison VC6 re-reads `[EDX+8]` every
    // iteration, where retail holds it in EDI from entry.
    int key = node->Key;
    int index = 0;
    Node_004072E0* cur = list;

    // The guard tests the cursor for null twice — once before the key read and
    // once after (`TEST ESI,ESI` at 0x4072EC and again at 0x4072F7). The second
    // is unreachable, so it is not a check the compiler invented; it is in the
    // source and is kept even though cl folds it away.
    while (1) {
        cur = cur->Next;
        if (!(cur != 0
              && cur != (Node_004072E0*)*(volatile int*)&cur->Key
              && cur != 0)) {
            break;
        }

        if (key <= cur->Key) {
            Node_004072E0* prev = cur->Prev;
            node->Next = cur;
            node->Prev = prev;
            cur->Prev = node;
            node->Prev->Next = node;
            return index;
        }
        index++;
    }

    // The loop exit splices before the list head instead of before the cursor,
    // which puts the node at the tail. The same four stores either way.
    {
        Node_004072E0* prev = list->Prev;
        node->Next = list;
        node->Prev = prev;
        list->Prev = node;
        node->Prev->Next = node;
    }
    return index;
}

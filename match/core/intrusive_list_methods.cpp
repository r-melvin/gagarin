// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Intrusive-list helpers, ordered ascending by retail address.

#include "intrusive_list_methods.h"

// FUNCTION: GAMEMD 0x4073B0
// Length of the circular list, not counting the header. The walk terminates on
// coming back to `this`, so an empty list is one whose link points at itself.
int ListNode::FUN_004073B0() const
{
    int count = 0;

    for (const ListNode* node = Prev; node != this; node = node->Prev) {
        count++;
    }

    return count;
}

// MATCHED 100% (0x4073C0, and identically 0x4073E0).
// The earlier 88.9% came from spelling the null-link exit as `return link`
// inside the `if (node)` arm, which cl folds into the shared zero-return block:
// retail instead jumps the *node*-null case to the `XOR EAX,EAX` and lets the
// link-null case fall through to the bare `RET` with EAX already zero. The
// lever is to hoist the node guard into its own early `return 0` and leave
// `return link` as the function's trailing block, so cl has a genuine
// zero-returning predecessor to merge the constant into and the link-null test
// can reach the RET directly. Variants measured in one match_all batch: the
// previous nested spelling 88.9%, a `link = 0` mutation with the node guard as
// an `if` 0.0%, the same nested 0.0%, and an early node guard followed by two
// explicit `return link`/`return 0` arms 18.8%. Only the form below reaches
// 100%.
// FUNCTION: GAMEMD 0x4073C0
ListNode* ListNode::FUN_004073C0()
{
    if (this == 0) {
        return 0;
    }

    ListNode* link = this->Prev;

    if (link != 0 && link == link->Owner) {
        return 0;
    }

    return link;
}

// FUNCTION: GAMEMD 0x4073E0
ListNode* ListNode::FUN_004073E0()
{
    if (this == 0) {
        return 0;
    }

    ListNode* link = this->Prev;

    if (link != 0 && link == link->Owner) {
        return 0;
    }

    return link;
}

// FUNCTION: GAMEMD 0x407420
// MATCHED 100%. Splice `node` in after `anchor`.
//
// The two stores into `node` go in the order Next, then Prev. Retail loads
// `anchor->Next` before storing `node->Prev` (`MOV EAX,[ECX+4]` ahead of
// `MOV [EDX],ECX`), and writing the forward link first is the only spelling
// that reaches it: with `Prev` first cl issues the load second, and no amount
// of hoisting moves it (71.4%). Variants measured in one match_all batch:
// Prev-first 71.4%, Prev-first with the anchor's Next hoisted into a local
// 71.4%, the same with the tail written through that local 57.1%, Next-first
// 100%, and the whole thing as a member on the anchor 0.0%. That last entry
// was a *__thiscall* member: it pushes the node and returns `RET 4`, which is
// why it scored zero. Spelled `__fastcall` on the member the node stays in EDX
// and the body below is byte-identical to the free-function form, so the class
// membership costs nothing.
void __fastcall ListNode::FUN_00407420(ListNode* node)
{
    node->Next = this->Next;
    node->Prev = this;
    this->Next = node;
    node->Next->Prev = node;
}

// FUNCTION: GAMEMD 0x407440
// Splice `node` in before `anchor`.
void __fastcall ListNode::FUN_00407440(ListNode* node)
{
    node->Next = this;

    ListNode* prev = this->Prev;

    node->Prev = prev;
    this->Prev = node;
    node->Prev->Next = node;
}

// FUNCTION: GAMEMD 0x407450
// Unlink and re-close the node onto itself, so an unlinked node is a valid
// empty list rather than a dangling one.
void ListNode::FUN_00407450()
{
    this->Next->Prev = this->Prev;
    this->Prev->Next = this->Next;

    this->Prev = this;
    this->Next = this;
}

// FUNCTION: GAMEMD 0x407470
// MATCHED 100%. The two tests are one `&&` rather than two separate `if`s on
// purpose: split into `if (link == 0) return link;` followed by
// `if (link != link->Owner) return link;`, VC6 stops branching entirely and
// emits the branchless `SUB/NEG/SBB/AND` select, which shares nothing with
// retail and scores 0%. The remaining instruction — retail's link-null exit
// jumping straight to the `RET` rather than through the `XOR EAX,EAX` — comes
// from writing the null result as a *mutation of the link*, not as a second
// `return 0`: the zeroing then belongs only to the owner-equal case, which is
// where retail's `XOR` sits, and the null link is returned as itself. Measured
// in one match_all batch: the previous `return link`/`return 0` pair 85.7%,
// this mutation 100%, the same mutation with the tests nested 100%, the
// equivalent ternary 100%, and an early `return link` guard 0.0%.
ListNode* ListNode::FUN_00407470() const
{
    ListNode* link = Prev;

    if (link != 0 && link == link->Owner) {
        link = 0;
    }

    return link;
}

// FUNCTION: GAMEMD 0x407520
// Pop the head block. The returned pointer skips the eight-byte link header, so
// the caller sees the payload; an empty list yields null.
void* FreeListHead::FUN_00407520()
{
    ListNode* node = First;

    if (node == 0) {
        return node;
    }

    First = node->Prev;
    return (char*)node + 8;
}

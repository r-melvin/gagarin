// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4036F0 and 0x403730.

#include "tagged_list_sweep_methods.h"

// FUNCTION: GAMEMD 0x4036F0
//
// The successor is taken before the action runs, because the action can unlink
// the node it is given - retail holds the node in EDI and its successor in ESI
// across the whole body, which is what that ordering costs.
//
// The walk is driven by the *successor* variable, with the current node copied
// out of it at the top of the body. That copy is what retail's `MOV EDI,ESI`
// before both the entry `JZ` and the back-edge `JNZ` is, and it is also why all
// three callee-saved registers are pushed in the prologue: driving the loop on
// the node instead leaves EDI dead until after the first test, and VC6 then
// shrink-wraps `PUSH EDI` past the early exit and shifts the whole function.
//
// A key of -1 means "every node": retail's `CMP EBX,-1; JZ` jumps straight onto
// the action, past the tag comparison.
int Owner_004036F0::FUN_004036F0(int key)
{
    ListNode* next = (&this->Items)->FUN_004073C0();
    ListNode* node = next;

    while (next) {
        next = (node)->FUN_004073E0();

        if (key == -1 || ((TaggedNode*)node)->Tag == key) {
            FUN_00402550(node);
        }

        node = next;
    }

    return 0;
}

// FUNCTION: GAMEMD 0x403730
//
// The same sweep with the other action and no return value.
void Owner_004036F0::FUN_00403730(int key)
{
    ListNode* next = (&this->Items)->FUN_004073C0();
    ListNode* node = next;

    while (next) {
        next = (node)->FUN_004073E0();

        if (key == -1 || ((TaggedNode*)node)->Tag == key) {
            FUN_004025B0(node);
        }

        node = next;
    }
}

// FUNCTION: GAMEMD 0x403770
//
// The same sweep with one extra gate in front of the tag test: only nodes with
// bit 0 of the flag byte at +0xA4 set are considered at all.
//
// The advance is guarded. Retail tests the node again at 0x40379F, immediately
// before calling the successor helper, even though nothing inside the loop can
// have cleared it - and both `continue` paths land on that test rather than on
// the call. An unguarded `node = Next(node)` is four bytes shorter and scores
// 57.7%. The guarded form reproduces it exactly: VC6 folds "advance to null,
// then fail the loop test" into a direct jump to the epilogue, which is where
// retail's `JZ 0x4037B0` goes. The sibling pair at 0x4036F0 does *not* have
// this test, so it is a real difference between the two pairs, not a shared
// idiom - which is why they are written out separately.
void Owner_004036F0::FUN_00403770(int key)
{
    ListNode* node = (&this->Items)->FUN_004073C0();

    while (node) {
        if ((((FlaggedNode*)node)->Flags & 1)
            && (key == -1 || ((FlaggedNode*)node)->Tag == key)) {
            FUN_00402600(node);
        }

        if (node == 0) {
            return;
        }

        node = (node)->FUN_004073E0();
    }
}

// FUNCTION: GAMEMD 0x4037C0
//
// The bit-2 counterpart, with its own action. Written out rather than shared.
void Owner_004036F0::FUN_004037C0(int key)
{
    ListNode* node = (&this->Items)->FUN_004073C0();

    while (node) {
        if ((((FlaggedNode*)node)->Flags & 4)
            && (key == -1 || ((FlaggedNode*)node)->Tag == key)) {
            FUN_00402650(node);
        }

        if (node == 0) {
            return;
        }

        node = (node)->FUN_004073E0();
    }
}

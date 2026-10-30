// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Link offsets read numerically off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x4073B0 / 0x4073C0 / 0x4073E0 / 0x407520. None of
//   these addresses is bound by YRpp.
//
// A small intrusive-list toolkit. The list is circular: 0x4073B0 walks it until
// the link comes back around to the header rather than until it hits null,
// which is what identifies the structure.
#ifndef GG_MATCH_CORE_INTRUSIVE_LIST_METHODS_H
#define GG_MATCH_CORE_INTRUSIVE_LIST_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The link words are Prev at +0x00 and Next at +0x04. 0x407450 pins the pair:
// it writes `self->Next->Prev` and `self->Prev->Next` and then resets both of
// its own links to itself, which is the circular-list unlink.
struct ListNode
{
    // FUNCTION: GAMEMD 0x407400
    ListNode* __fastcall FUN_00407400(int index);
    // FUNCTION: GAMEMD 0x407490
    ListNode* FUN_00407490();
    // FUNCTION: GAMEMD 0x4074B0
    ListNode* FUN_004074B0();
    ListNode* Prev;    // +0x0000
    ListNode* Next;    // +0x0004
    ListNode* Owner;   // +0x0008

    // Declared ascending by retail address. Every one of these is a member
    // rather than a free function taking the node: retail passes the node in
    // ECX, and where a second argument exists it arrives in EDX, which is
    // `__fastcall` on a member (this in ECX, the first explicit argument in
    // EDX, nothing cleaned). A plain __thiscall member would push that second
    // argument and return `RET 4`, so the splices keep __fastcall while the
    // one-operand routines are ordinary __thiscall members.
    // FUNCTION: GAMEMD 0x4072C0 -- initialise a list head
    void FUN_004072C0();
    // FUNCTION: GAMEMD 0x4072D0 -- re-arm: Prev = Next = self, Owner = 0
    void FUN_004072D0();
    // FUNCTION: GAMEMD 0x4073B0
    int FUN_004073B0() const;
    // FUNCTION: GAMEMD 0x4073C0
    ListNode* FUN_004073C0();
    // FUNCTION: GAMEMD 0x4073E0
    ListNode* FUN_004073E0();
    // FUNCTION: GAMEMD 0x407420 — splice `node` in after this anchor.
    void __fastcall FUN_00407420(ListNode* node);
    // FUNCTION: GAMEMD 0x407440 — splice `node` in before this anchor.
    void __fastcall FUN_00407440(ListNode* node);
    // FUNCTION: GAMEMD 0x407450
    void FUN_00407450();
    // FUNCTION: GAMEMD 0x407470
    ListNode* FUN_00407470() const;
};
GG_STATIC_ASSERT(offsetof(ListNode, Next) == 0x4);
GG_STATIC_ASSERT(offsetof(ListNode, Owner) == 0x8);

// 0x4073C0 and 0x4073E0 are byte-identical. They are written out separately
// rather than aliased, per the family rule.

// A free-list head. Popping hands back the block *past* the link word, so the
// link is stored in the eight bytes preceding the payload.
struct Obj_00407520
{
    // FUNCTION: GAMEMD 0x407540
    int FUN_00407540() const;
    ListNode* First;   // +0x0000

    // FUNCTION: GAMEMD 0x407520
    void* FUN_00407520();
    // FUNCTION: GAMEMD 0x407510 -- release the pool's block
    void FUN_00407510();
    // FUNCTION: GAMEMD 0x407530 -- hand a block back to the pool (this in ECX, the block in EDX)
    void __fastcall FUN_00407530(void* block);
};

#endif  // GG_MATCH_CORE_INTRUSIVE_LIST_METHODS_H

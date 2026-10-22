// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The +0xF8 header displacement, the +0x0C tag and both per-node call targets
//   are read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4036F0 and 0x403730.
//
// A pair of sweeps over the intrusive list embedded at +0xF8: walk every node,
// and for each one whose tag matches - or unconditionally when the key is -1 -
// run one per-node action. The two differ only in that action (0x402550 against
// 0x4025B0) and in the return: 0x4036F0 ends `XOR EAX,EAX` and 0x403730 does
// not, so the first returns zero and the second is void.
//
// `MOV EBX,EDX` at entry with the owner still in ECX means the key travels in
// EDX, so these are `__fastcall` *members* — this in ECX, the first explicit
// argument in EDX, nothing cleaned — and not __thiscall members, which would
// push the key and return `RET 4`.
#ifndef GG_MATCH_CORE_TAGGED_LIST_SWEEP_METHODS_H
#define GG_MATCH_CORE_TAGGED_LIST_SWEEP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"

// The list nodes carry a 4-byte tag straight after the three link words.
struct TaggedNode
{
    ListNode Link;   // +0x0000
    int      Tag;    // +0x000C
};
GG_STATIC_ASSERT(offsetof(TaggedNode, Tag) == 0xC);

// The 0x403770 pair additionally gates on a bit in the flag byte at +0xA4, each
// testing a different bit (1 and 4).
struct FlaggedNode
{
    ListNode Link;         // +0x0000
    int      Tag;          // +0x000C
    char     _pad010[0xA4 - 0x10];
    char     Flags;        // +0x00A4
};
GG_STATIC_ASSERT(offsetof(FlaggedNode, Tag) == 0xC);
GG_STATIC_ASSERT(offsetof(FlaggedNode, Flags) == 0xA4);

// FUNCTION: GAMEMD 0x402550 — the action 0x4036F0 runs.
void FUN_00402550(ListNode* node);
// FUNCTION: GAMEMD 0x4025B0 — the action 0x403730 runs.
void FUN_004025B0(ListNode* node);
// FUNCTION: GAMEMD 0x402600 — the action 0x403770 runs.
void FUN_00402600(ListNode* node);
// FUNCTION: GAMEMD 0x402650 — the action 0x4037C0 runs.
void FUN_00402650(ListNode* node);

struct Owner_004036F0
{
    char     _pad000[0xF8];
    ListNode Items;   // +0x00F8

    // Declared ascending by retail address.
    // FUNCTION: GAMEMD 0x4036F0
    int  __fastcall FUN_004036F0(int key);
    // FUNCTION: GAMEMD 0x403730
    void __fastcall FUN_00403730(int key);
    // FUNCTION: GAMEMD 0x403770
    void __fastcall FUN_00403770(int key);
    // FUNCTION: GAMEMD 0x4037C0
    void __fastcall FUN_004037C0(int key);
};
GG_STATIC_ASSERT(offsetof(Owner_004036F0, Items) == 0xF8);


#endif  // GG_MATCH_CORE_TAGGED_LIST_SWEEP_METHODS_H

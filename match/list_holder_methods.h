// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x402C00 / 0x402C20 / 0x4031F0 / 0x4035B0 / 0x4035D0. None is
//   bound by YRpp.
//
// Holders that cache a list node and refresh it through the validity filters in
// intrusive_list_methods.h. Three of these (0x402C20, 0x4031F0, 0x4035D0) are
// byte-identical on three different holder types and are written out longhand.
#ifndef GG_MATCH_CORE_LIST_HOLDER_METHODS_H
#define GG_MATCH_CORE_LIST_HOLDER_METHODS_H

#include "intrusive_list_methods.h"

// GLOBAL: GAMEMD 0x815E98 — a *pointer* to the node 0x402C00 seeds its holder
// from. Retail passes its value (`MOV ECX,[0x815E98]`), not its address.
extern ListNode* DAT_00815E98;

struct Holder_00402C00
{
    ListNode* Node;   // +0x0000

    // FUNCTION: GAMEMD 0x402C00
    ListNode* FUN_00402C00();
    // FUNCTION: GAMEMD 0x402C20
    ListNode* FUN_00402C20();
};

struct Holder_004031F0
{
    ListNode* Node;   // +0x0000

    // FUNCTION: GAMEMD 0x4031F0
    ListNode* FUN_004031F0();
};

struct Holder_004035D0
{
    ListNode* Node;   // +0x0000

    // FUNCTION: GAMEMD 0x4035D0
    ListNode* FUN_004035D0();
};

// FUNCTION: GAMEMD 0x4035B0 — the node lives at +0xF8 of the owner, and the
// result is written through a caller-supplied slot rather than returned.
ListNode* FUN_004035B0(void* owner, ListNode** out);

#endif  // GG_MATCH_CORE_LIST_HOLDER_METHODS_H

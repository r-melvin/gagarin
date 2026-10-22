// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x402AF0. The two calls through `[EBX+0x14]` and
//   `[EAX+0x18]` take the *node* in ECX while the pointer itself comes from the
//   owner, so those slots are per-owner hooks invoked on the node — not virtuals
//   of either class.
#ifndef GG_MATCH_CORE_HOOKED_NODE_CREATE_METHODS_H
#define GG_MATCH_CORE_HOOKED_NODE_CREATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size);   // GAMEMD 0x7C8E17
extern "C" void  __cdecl FUN_007C8B3D(void* block);         // GAMEMD 0x7C8B3D

struct Node_00402AF0;

// Declaration order per match/_rt/gg_vslot.h: the node must be complete before
// the member-pointer typedefs.
struct Owner_00402AF0;

struct Node_00402AF0
{
    char _pad000[0xC];         // +0x0000
    Owner_00402AF0* Owner;     // +0x000C
    int  At_10;                // +0x0010
    char _pad014[0x4C];        // +0x0014
};
GG_STATIC_ASSERT(offsetof(Node_00402AF0, Owner) == 0xC);
GG_STATIC_ASSERT(sizeof(Node_00402AF0) == 0x60);

typedef int (Node_00402AF0::*Hook_00402AF0)();

struct Owner_00402AF0
{
    char _pad000[0x8];         // +0x0000
    unsigned char Flags08;     // +0x0008  bit 1 asks for the global to be set
    char _pad009[0x3];         // +0x0009
    unsigned int Flags0C;      // +0x000C  bit 0 marks the node attached
    char _pad010[0x4];         // +0x0010
    Hook_00402AF0 Attach;      // +0x0014
    Hook_00402AF0 Detach;      // +0x0018
};
GG_STATIC_ASSERT(offsetof(Owner_00402AF0, Flags0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Owner_00402AF0, Attach) == 0x14);
GG_STATIC_ASSERT(offsetof(Owner_00402AF0, Detach) == 0x18);

struct List_00402AF0 { char opaque[4]; };
// GLOBAL: GAMEMD 0x815E98 — the list the node is appended to.
extern List_00402AF0* DAT_00815E98;
// GLOBAL: GAMEMD 0x87DE28
extern int DAT_0087DE28;

// FUNCTION: GAMEMD 0x4072D0 — initialise the fresh node.
void __fastcall FUN_004072D0(Node_00402AF0* node);
// FUNCTION: GAMEMD 0x407420 — append the node to the list.
void __fastcall FUN_00407420(List_00402AF0* list, Node_00402AF0* node);

// FUNCTION: GAMEMD 0x402AF0
Node_00402AF0* __fastcall FUN_00402AF0(Owner_00402AF0* owner);

#endif  // GG_MATCH_CORE_HOOKED_NODE_CREATE_METHODS_H

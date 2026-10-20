// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x401FC0: the self-comparison at +0x4, the two embedded
//   sub-objects at +0x1C and +0x24, and the context pointer at +0x3C whose +0x4
//   and +0x8 are the two lists things are returned to.
#ifndef GG_MATCH_CORE_DRAIN_AND_UNLINK_METHODS_H
#define GG_MATCH_CORE_DRAIN_AND_UNLINK_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Node_00401FC0;
struct Obj_00401FC0;

struct Ctx_00401FC0
{
    char _pad000[0x4];        // +0x0000
    void* NodeList;           // +0x0004
    void* ObjList;            // +0x0008
};
GG_STATIC_ASSERT(offsetof(Ctx_00401FC0, ObjList) == 0x8);

// FUNCTION: GAMEMD 0x407450 — splice out of whatever list it is in.
void __fastcall FUN_00407450(void* link);
// FUNCTION: GAMEMD 0x407470 — first element, or null.
Node_00401FC0* __fastcall FUN_00407470(void* head);
// FUNCTION: GAMEMD 0x407530 — return something to a free list.
void __fastcall FUN_00407530(void* list, void* item);
// FUNCTION: GAMEMD 0x408530 — tear down the sub-object at +0x1C.
void __fastcall FUN_00408530(void* sub);
// FUNCTION: GAMEMD 0x408600 — tear down one node.
void __fastcall FUN_00408600(Node_00401FC0* node);

struct Obj_00401FC0
{
    char _pad000[0x4];        // +0x0000
    void* Link;               // +0x0004  points at the object itself when unlinked
    char _pad008[0x14];       // +0x0008
    char At_1C[0x8];          // +0x001C
    char At_24[0x18];         // +0x0024
    Ctx_00401FC0* Ctx;        // +0x003C

    // FUNCTION: GAMEMD 0x401FC0
    void FUN_00401FC0();
};
GG_STATIC_ASSERT(offsetof(Obj_00401FC0, At_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(Obj_00401FC0, At_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_00401FC0, Ctx) == 0x3C);

#endif  // GG_MATCH_CORE_DRAIN_AND_UNLINK_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x472330: the global list at 0xA8022C with its count at
//   0xA80238, the item's type at +0x34 whose +0xBC is compared, and this
//   object's slot array at +0x28 with its count at +0x34.
#ifndef GG_MATCH_AI_REBIND_SLOTS_METHODS_H
#define GG_MATCH_AI_REBIND_SLOTS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Type_00472330
{
    char _pad000[0xBC];       // +0x0000
    int  At_BC;               // +0x00BC
};
GG_STATIC_ASSERT(offsetof(Type_00472330, At_BC) == 0xBC);

struct Item_00472330
{
    char _pad000[0x34];       // +0x0000
    Type_00472330* Type;      // +0x0034
};
GG_STATIC_ASSERT(offsetof(Item_00472330, Type) == 0x34);

class TechnoClass;

struct Slot_00472330
{
    TechnoClass* Key;         // +0x0000; native 0x471DF0 stores captured unit
    Item_00472330* Value;     // +0x0004
};

// Native 0x472392 compares the unit pointer and 0x472396 writes the selected house.
GG_STATIC_ASSERT(offsetof(Slot_00472330, Key) == 0x00);
GG_STATIC_ASSERT(offsetof(Slot_00472330, Value) == 0x04);
GG_STATIC_ASSERT(sizeof(((Slot_00472330*)0)->Key) == 4);
GG_STATIC_ASSERT(sizeof(((Slot_00472330*)0)->Value) == 4);
GG_STATIC_ASSERT(sizeof(((Item_00472330*)0)->Type) == 4);
GG_STATIC_ASSERT(sizeof(((Type_00472330*)0)->At_BC) == 4);

// GLOBAL: GAMEMD 0xA8022C — the item list.
extern Item_00472330** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA80238 — how many items it holds.
extern int DAT_00A80238;

struct Source_00472330
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x6A46D0 — the value every item's type is matched against.
    int FUN_006A46D0();
};
// GLOBAL: GAMEMD 0x818164
extern Source_00472330 DAT_00818164;

struct Obj_00472330
{
    char _pad000[0x28];       // +0x0000
    Slot_00472330** Slots;    // +0x0028
    char _pad02C[0x8];        // +0x002C
    int  SlotCount;           // +0x0034

    // FUNCTION: GAMEMD 0x472330
    bool FUN_00472330(int key);
};
GG_STATIC_ASSERT(offsetof(Obj_00472330, Slots) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_00472330, SlotCount) == 0x34);

#endif  // GG_MATCH_AI_REBIND_SLOTS_METHODS_H

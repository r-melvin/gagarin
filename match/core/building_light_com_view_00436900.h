// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI at 0x7E3ACC resolves through COL 0x7FC040 to type descriptor
//   0x818BE0, `.?AVBuildingLightClass@@`. Its constructor at 0x435820 stores
//   IPersistStream vptr 0x7E3AD0 and confirms the object prefix through +0xE7.
//   Raw table words at 0x7E3AD0 confirm target slots 3, 6, 10, 12, 30, and 34.
#ifndef GG_MATCH_CORE_BUILDING_LIGHT_COM_VIEW_00436900_H
#define GG_MATCH_CORE_BUILDING_LIGHT_COM_VIEW_00436900_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Prefix view through slot 34; no end of the retail vtable is inferred.
// VTABLE: GAMEMD 0x007E3AD0 — BuildingLightClass IPersistStream view.
struct BuildingLightIpersistVtable_00436900
{
    void* slots[35];
};
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(offsetof(BuildingLightIpersistVtable_00436900, slots) == 0x00);
GG_STATIC_ASSERT(offsetof(BuildingLightIpersistVtable_00436900, slots) + 3 * 4 == 0x0C);  // 0x436910
GG_STATIC_ASSERT(offsetof(BuildingLightIpersistVtable_00436900, slots) + 6 * 4 == 0x18);  // 0x4369C0
GG_STATIC_ASSERT(offsetof(BuildingLightIpersistVtable_00436900, slots) + 10 * 4 == 0x28); // 0x436A00
GG_STATIC_ASSERT(offsetof(BuildingLightIpersistVtable_00436900, slots) + 12 * 4 == 0x30); // 0x436900
GG_STATIC_ASSERT(offsetof(BuildingLightIpersistVtable_00436900, slots) + 30 * 4 == 0x78); // 0x4369F0
GG_STATIC_ASSERT(offsetof(BuildingLightIpersistVtable_00436900, slots) + 34 * 4 == 0x88); // 0x4369E0
GG_STATIC_ASSERT(sizeof(BuildingLightIpersistVtable_00436900) == 0x8C);

// The constructor 0x435820 writes the last two fields; 0x436A00 compares and
// clears them. This view intentionally leaves earlier base fields unknown.
struct BuildingLightMethodView_00436900
{
    char unknown_00[0xE0];
    unsigned int unknown_E0;
    unsigned int unknown_E4;

    // FUNCTION: GAMEMD 0x436900 — vtable slot 12, ECX=this, no stack args.
    int FUN_00436900();
    // FUNCTION: GAMEMD 0x4369E0 — vtable slot 34, ECX=this, no stack args.
    int FUN_004369E0();
    // FUNCTION: GAMEMD 0x4369F0 — vtable slot 30, ECX=this, no stack args.
    int FUN_004369F0();
    // FUNCTION: GAMEMD 0x436A00 — vtable slot 10, ECX=this, two stack args.
    void FUN_00436A00(int unknownArg0, char unknownArg1);
};
GG_STATIC_ASSERT(offsetof(BuildingLightMethodView_00436900, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BuildingLightMethodView_00436900, unknown_E0) == 0xE0);
GG_STATIC_ASSERT(offsetof(BuildingLightMethodView_00436900, unknown_E4) == 0xE4);
GG_STATIC_ASSERT(sizeof(BuildingLightMethodView_00436900) == 0xE8);

// GLOBAL: GAMEMD 0x007E9730
extern unsigned int DAT_007E9730;
// GLOBAL: GAMEMD 0x007E9734
extern unsigned int DAT_007E9734;
// GLOBAL: GAMEMD 0x007E9738
extern unsigned int DAT_007E9738;
// GLOBAL: GAMEMD 0x007E973C
extern unsigned int DAT_007E973C;

// FUNCTION: GAMEMD 0x436910 — IPersistStream slot 3 (GetClassID), __stdcall.
int __stdcall FUN_00436910(void* self, unsigned int* outWords);
// FUNCTION: GAMEMD 0x4369C0 — IPersistStream slot 6 (Save), __stdcall.
int __stdcall FUN_004369C0(void* self, void* stream, int clearDirty);

// FUNCTION: GAMEMD 0x00410320 (decl; reloc) — three stack arguments, RET 0xC.
extern "C" int __stdcall FUN_00410320(void* arg0, void* arg1, int arg2);

struct ThiscallTarget_005F5230
{
    // FUNCTION: GAMEMD 0x005F5230 (decl; reloc) — thiscall, int + byte stack args.
    void Call(int arg0, char arg1);
};

#endif  // GG_MATCH_CORE_BUILDING_LIGHT_COM_VIEW_00436900_H

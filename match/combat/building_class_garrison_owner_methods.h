// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, slots, globals and strings read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x458200:
//     * `[ESI+0x520]` the building type, gated on `CMP [EAX+0x634],-1`;
//     * `[ESI+0x21C]` the owner house (the same offset 0x457CE0 pins), and
//       `[EBP+0x34]` the house's type with `[EBP+0xBC]` the int the side
//       lookup's result is compared against;
//     * `[ESI+0x688]` the occupant vector's item pointer, dereferenced once
//       to reach the first occupant and then `[ECX+0x21C]` for its owner;
//     * the house array as two absolute loads, `MOV EDI,[0xA80238]` (count)
//       and `MOV EDX,[0xA8022C]` (items), i.e. +0x10 and +0x4 of the vector
//       object at 0xA80228;
//     * `MOV ECX,[0x8871E0]` then `[ECX+0x1C0]` — the rules singleton and the
//       sound index it hands to VocClass::PlayGlobal;
//     * vtable slots `[EAX+0x408]` (occupant count, as at 0x457CE0),
//       `[EDX+0x1B8]` (map coords, as at 0x457A10) and `[EDX+0x3D4]`, called
//       with a house and a pushed 0;
//     * callees 0x5F5CD0 ObjectClass::IsRedHP, 0x457DE0 (__thiscall, two
//       pushed zeroes), 0x6A46D0 (__fastcall, a name in ECX, answering an
//       index), 0x50B6F0 HouseClass::IsControlledByCurrentPlayer, 0x750920
//       VocClass::PlayGlobal, 0x65FA70 RadarEventClass::Create and 0x752700
//       VoxClass::Play;
//     * strings 0x818164 "Civilian" and 0x81926C "EVA_StructureAbandoned".
//   Names cross-checked against YRpp (Array at 0xA80228, Instance at
//   0x8871E0, Occupants); every offset above is re-derived from the user's binary. The two
//   members whose meaning the bytes do not fix are left as `unknown_XX`.
//   At 0x458218, retail passes the receiver in ECX directly to 0x5F5CD0.
//   The canonical ObjectClass declaration is used through this offset-zero
//   ABI view, without claiming a complete class hierarchy here.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_GARRISON_OWNER_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_GARRISON_OWNER_METHODS_H

#include <stddef.h>
#include "../_layout/object_class.h"
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../audio/voc_class_play_global_methods.h"

// 2D short cell coordinate, passed to the radar event by value.
struct CellStruct_00458200
{
    short X;  // +0x00
    short Y;  // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct_00458200) == 4);

// HouseTypeClass — only the side index the Civilian lookup matches on.
struct HouseType_00458200
{
    char _pad000[0xBC];   // +0x0000
    int  SideIndex;       // +0x00BC
};
GG_STATIC_ASSERT(offsetof(HouseType_00458200, SideIndex) == 0xBC);

struct House_00458200
{
    char                _pad000[0x34];   // +0x0000
    HouseType_00458200* Type;            // +0x0034

    // FUNCTION: GAMEMD 0x50B6F0 (decl; reloc) — HouseClass::IsControlledByCurrentPlayer.
    bool IsControlledByCurrentPlayer();
};
GG_STATIC_ASSERT(offsetof(House_00458200, Type) == 0x34);

// DynamicVectorClass<HouseClass*>: the vptr, the item block, the capacity and
// the allocation flag, then the count at +0x10.
struct HouseVector_00458200
{
    void*             Vtbl;        // +0x0000
    House_00458200**  Items;       // +0x0004
    int               Capacity;    // +0x0008
    int               IsAllocated; // +0x000C
    int               Count;       // +0x0010
};
GG_STATIC_ASSERT(offsetof(HouseVector_00458200, Items) == 0x4 &&
                 offsetof(HouseVector_00458200, Count) == 0x10);

// GLOBAL: GAMEMD 0xA80228 — HouseClass::Array.
extern HouseVector_00458200 HouseArray_00458200;

// RulesClass — only the sound index this method plays.
struct Rules_00458200
{
    char _pad000[0x1C0];   // +0x0000
    int  unknown_1C0;      // +0x01C0  a VocClass index
};
GG_STATIC_ASSERT(offsetof(Rules_00458200, unknown_1C0) == 0x1C0);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance (a pointer, loaded with
// `MOV ECX,dword ptr [0x8871E0]`).
extern Rules_00458200* RulesInstance_00458200;

// BuildingTypeClass — only the int this method gates on.
struct BuildingType_00458200
{
    char _pad000[0x634];   // +0x0000
    int  unknown_634;      // +0x0634
};
GG_STATIC_ASSERT(offsetof(BuildingType_00458200, unknown_634) == 0x634);

struct Infantry_00458200
{
    char             _pad000[0x21C];   // +0x0000
    House_00458200*  Owner;            // +0x021C
};
GG_STATIC_ASSERT(offsetof(Infantry_00458200, Owner) == 0x21C);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_00458200;

struct BuildingClass_00458200
{
    Vtbl_00458200*          Vtbl;             // +0x0000
    char                    _pad004[0x218];   // +0x0004
    House_00458200*         Owner;            // +0x021C
    char                    _pad220[0x300];   // +0x0220
    BuildingType_00458200*  Type;             // +0x0520
    char                    _pad524[0x164];   // +0x0524
    Infantry_00458200**     OccupantItems;    // +0x0688

    // FUNCTION: GAMEMD 0x457DE0 (decl; reloc) — unnamed __thiscall neighbour.
    void FUN_00457DE0(int a, int b);

    // FUNCTION: GAMEMD 0x458330 (decl; reloc) — the occupant-anim refresh.
    void UpdateOccupantAnims();

    // FUNCTION: GAMEMD 0x458200
    void UpdateGarrisonOwner();
};
// The binary confirms the primary object vptr at +0. ObjectClass is used as
// a method-call prefix view, not as a claim about the complete class chain.
GG_STATIC_ASSERT(offsetof(BuildingClass_00458200, Vtbl) == 0);
GG_STATIC_ASSERT(offsetof(BuildingClass_00458200, Owner)         == 0x21C &&
                 offsetof(BuildingClass_00458200, Type)          == 0x520 &&
                 offsetof(BuildingClass_00458200, OccupantItems) == 0x688);

typedef CellStruct_00458200* (BuildingClass_00458200::*Fn1B8_00458200)(
    CellStruct_00458200* out);
typedef void (BuildingClass_00458200::*Fn3D4_00458200)(House_00458200* house,
                                                       int announce);
typedef int  (BuildingClass_00458200::*Fn408_00458200)();

struct Vtbl_00458200
{
    char            _pad000[0x1B8];          // +0x0000
    Fn1B8_00458200  GetMapCoords;            // +0x01B8
    char            _pad1BC[0x3D4 - 0x1BC];  // +0x01BC
    Fn3D4_00458200  SetOwningHouse;          // +0x03D4
    char            _pad3D8[0x408 - 0x3D8];  // +0x03D8
    Fn408_00458200  GetOccupantCount;        // +0x0408
};
GG_STATIC_ASSERT(offsetof(Vtbl_00458200, GetMapCoords)     == 0x1B8 &&
                 offsetof(Vtbl_00458200, SetOwningHouse)   == 0x3D4 &&
                 offsetof(Vtbl_00458200, GetOccupantCount) == 0x408);

// FUNCTION: GAMEMD 0x6A46D0 (decl; reloc) — the side lookup by name.
int FindSideIndex_00458200(const char* name);

struct VoxClass_00458200
{
    // FUNCTION: GAMEMD 0x752700 (decl; reloc) — VoxClass::Play.
    static void Play(const char* name, int a, int b);
};

struct RadarEventClass_00458200
{
    // FUNCTION: GAMEMD 0x65FA70 (decl; reloc) — RadarEventClass::Create
    // (the cell goes on the stack; only the type reaches ECX).
    static bool Create(int type, CellStruct_00458200 mapCoords);
};

// STRING: GAMEMD 0x818164 — "Civilian".
extern const char CivilianSideName_00458200[];
// STRING: GAMEMD 0x81926C — "EVA_StructureAbandoned".
extern const char EvaStructureAbandoned_00458200[];

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_GARRISON_OWNER_METHODS_H

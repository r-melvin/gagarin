// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x457CE0: on the building `[ESI+0x520]` (Type),
//   `[ESI+0xAC]` (current mission, 0x12 / 0x13 rejected), `[ESI+0x21C]`
//   (Owner); on the building type `[EAX+0x157B]` (CanBeOccupied) and
//   `[ECX+0x1580]` (MaxNumberOccupants); on the infantry `[EDI+0x6C0]`
//   (Type) and `[EDI+0x21C]` (Owner); on the infantry type `[EAX+0xEB4]`
//   (Occupier) and `[EAX+0xEB5]` (Assaulter); on the house `[EAX+0x34]`
//   (Type) and the house type `[EAX+0x1A6]` (MultiplayPassive); vtable slots
//   `[EDX+0x48]` GetCoords (hidden pointer), `[EDX+0x1D4]` IsBeingWarpedOut,
//   `[EDX+0x408]` GetOccupantCount; callees 0x5785F0 (map usable-area on a
//   coord, map object 0x87F7E8), 0x5F5CD0 ObjectClass::IsRedHP, 0x7105E0
//   TechnoClass::IsMindControlled, 0x4F9A90 HouseClass::IsAlliedWith(object).
//   At 0x457D8F, retail passes the same receiver in ECX directly to 0x5F5CD0;
//   the canonical ObjectClass declaration is used through this offset-zero
//   ABI view, without claiming a complete class hierarchy here.
//   Names cross-checked against YRpp.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_OCCUPY_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_OCCUPY_METHODS_H

#include <stddef.h>
#include "../_layout/object_class.h"
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Coord_00457CE0
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_00457CE0) == 0xC);

// HouseTypeClass — only MultiplayPassive.
struct HouseType_00457CE0
{
    char _pad000[0x1A6];   // +0x0000
    char MultiplayPassive; // +0x01A6
};
GG_STATIC_ASSERT(offsetof(HouseType_00457CE0, MultiplayPassive) == 0x1A6);

struct Obj_00457CE0;

// HouseClass — Type and the object-overload alliance test.
struct House_00457CE0
{
    char                _pad000[0x34];   // +0x0000
    HouseType_00457CE0* Type;            // +0x0034

    // FUNCTION: GAMEMD 0x4F9A90 (decl; reloc) — HouseClass::IsAlliedWith(ObjectClass const*).
    bool IsAlliedWith(Obj_00457CE0 const* object) const;
};
GG_STATIC_ASSERT(offsetof(House_00457CE0, Type) == 0x34);

// BuildingTypeClass — CanBeOccupied and MaxNumberOccupants.
struct BuildingType_00457CE0
{
    char _pad000[0x157B];         // +0x0000
    char CanBeOccupied;           // +0x157B
    char _pad157C[0x1580 - 0x157C]; // +0x157C
    int  MaxNumberOccupants;      // +0x1580
};
GG_STATIC_ASSERT(offsetof(BuildingType_00457CE0, CanBeOccupied)      == 0x157B);
GG_STATIC_ASSERT(offsetof(BuildingType_00457CE0, MaxNumberOccupants) == 0x1580);

// InfantryTypeClass — Occupier and Assaulter.
struct InfantryType_00457CE0
{
    char _pad000[0xEB4];   // +0x0000
    char Occupier;         // +0x0EB4
    char Assaulter;        // +0x0EB5
};
GG_STATIC_ASSERT(offsetof(InfantryType_00457CE0, Occupier)  == 0xEB4);
GG_STATIC_ASSERT(offsetof(InfantryType_00457CE0, Assaulter) == 0xEB5);

struct Vtbl_00457CE0;

// TechnoClass as seen from both sides: the building's mission, owner and
// type, the infantry's owner and type.
struct Obj_00457CE0
{
    Vtbl_00457CE0*          Vptr;              // +0x0000
    char                    _pad004[0xA8];     // +0x0004
    int                     CurrentMission;    // +0x00AC
    char                    _pad0B0[0x16C];    // +0x00B0
    House_00457CE0*         Owner;             // +0x021C
    char                    _pad220[0x300];    // +0x0220
    BuildingType_00457CE0*  BuildingType;      // +0x0520
    char                    _pad524[0x19C];    // +0x0524
    InfantryType_00457CE0*  InfantryType;      // +0x06C0

    // FUNCTION: GAMEMD 0x7105E0 (decl; reloc) — TechnoClass::IsMindControlled.
    bool IsMindControlled();

    // FUNCTION: GAMEMD 0x457CE0 — BuildingClass::CanBeOccupiedBy.
    bool CanBeOccupiedBy(Obj_00457CE0* infantry);
};
// The binary puts the primary object vptr at +0; the ObjectClass view is
// used only for its confirmed prefix method call below.
GG_STATIC_ASSERT(offsetof(Obj_00457CE0, Vptr) == 0);
GG_STATIC_ASSERT(offsetof(Obj_00457CE0, CurrentMission) == 0xAC);
GG_STATIC_ASSERT(offsetof(Obj_00457CE0, Owner)          == 0x21C);
GG_STATIC_ASSERT(offsetof(Obj_00457CE0, BuildingType)   == 0x520);
GG_STATIC_ASSERT(offsetof(Obj_00457CE0, InfantryType)   == 0x6C0);

typedef Coord_00457CE0* (Obj_00457CE0::*Fn48_00457CE0)(Coord_00457CE0* out);
typedef bool (Obj_00457CE0::*Fn1D4_00457CE0)();
typedef int  (Obj_00457CE0::*Fn408_00457CE0)();

struct Vtbl_00457CE0
{
    char            _pad000[0x48];           // +0x0000
    Fn48_00457CE0   GetCoords;               // +0x0048
    char            _pad04C[0x1D4 - 0x4C];   // +0x004C
    Fn1D4_00457CE0  IsBeingWarpedOut;        // +0x01D4
    char            _pad1D8[0x408 - 0x1D8];  // +0x01D8
    Fn408_00457CE0  GetOccupantCount;        // +0x0408
};
GG_STATIC_ASSERT(offsetof(Vtbl_00457CE0, GetCoords)        == 0x48);
GG_STATIC_ASSERT(offsetof(Vtbl_00457CE0, IsBeingWarpedOut) == 0x1D4);
GG_STATIC_ASSERT(offsetof(Vtbl_00457CE0, GetOccupantCount) == 0x408);

// MapClass — only the coordinate usable-area test.
struct Map_00457CE0
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5785F0 (decl; reloc) — MapClass::IsWithinUsableArea(CoordStruct const&).
    bool IsWithinUsableArea(const Coord_00457CE0* coords);
};
// GLOBAL: GAMEMD 0x87F7E8 — the map instance.
extern Map_00457CE0 MapInstance_00457CE0;

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_OCCUPY_METHODS_H

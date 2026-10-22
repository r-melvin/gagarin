// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5051E0: the house Type `[EBP+0x34]` whose
//   ParentCountry name at +0x98 goes to 0x5117D0 in ECX, the house type's
//   `[ECX+0xB8]` (ArrayIndex, shift count) and `[EDX+0xBC]` (ArrayIndex2),
//   the house Supers items `[EBP+0x258]`; on the techno type `[EAX+0x6CC]`
//   (OwnerFlags), `[EAX+0x6D0]` (AIBasePlanningSide), `[EAX+0xDA0]` /
//   `[EAX+0xDA4]` (Required / ForbiddenHouses), `[EAX+0x16F0]`
//   (BuildingTypeClass::SuperWeapon); the super's Type `[EDX+0x28]` and its
//   `[ECX+0xE7]` (DisableableFromShell); the array argument's Items +0x4 and
//   Count +0x10; RulesClass 0x8871E0 BuildConst Items +0x920 / Count +0x92C;
//   the byte gate 0xA8B263 (SWAllowed). Names cross-checked against YRpp.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_FIRST_BUILDABLE_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_FIRST_BUILDABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x5117D0 (decl; reloc) — HouseTypeClass::FindIndexOfName, name in ECX.
int HouseType_FindIndexOfName_005051E0(const char* name);

// HouseTypeClass — ParentCountry name, ArrayIndex, ArrayIndex2.
struct HouseType_005051E0
{
    char _pad000[0x98];   // +0x0000
    char ParentCountry[0x20]; // +0x0098
    int  ArrayIndex;      // +0x00B8
    int  ArrayIndex2;     // +0x00BC
};
GG_STATIC_ASSERT(offsetof(HouseType_005051E0, ParentCountry) == 0x98);
GG_STATIC_ASSERT(offsetof(HouseType_005051E0, ArrayIndex)    == 0xB8);
GG_STATIC_ASSERT(offsetof(HouseType_005051E0, ArrayIndex2)   == 0xBC);

// TechnoTypeClass (building types reach into the SuperWeapon slot).
struct TechnoType_005051E0
{
    char         _pad000[0x6CC];            // +0x0000
    unsigned int OwnerFlags;                // +0x06CC
    int          AIBasePlanningSide;        // +0x06D0
    char         _pad6D4[0xDA0 - 0x6D4];    // +0x06D4
    unsigned int RequiredHouses;            // +0x0DA0
    unsigned int ForbiddenHouses;           // +0x0DA4
    char         _padDA8[0x16F0 - 0xDA8];   // +0x0DA8
    int          SuperWeapon;               // +0x16F0 (BuildingTypeClass)
};
GG_STATIC_ASSERT(offsetof(TechnoType_005051E0, OwnerFlags)         == 0x6CC);
GG_STATIC_ASSERT(offsetof(TechnoType_005051E0, AIBasePlanningSide) == 0x6D0);
GG_STATIC_ASSERT(offsetof(TechnoType_005051E0, RequiredHouses)     == 0xDA0);
GG_STATIC_ASSERT(offsetof(TechnoType_005051E0, ForbiddenHouses)    == 0xDA4);
GG_STATIC_ASSERT(offsetof(TechnoType_005051E0, SuperWeapon)        == 0x16F0);

// SuperWeaponTypeClass — only DisableableFromShell.
struct SuperType_005051E0
{
    char _pad000[0xE7];        // +0x0000
    char DisableableFromShell; // +0x00E7
};
GG_STATIC_ASSERT(offsetof(SuperType_005051E0, DisableableFromShell) == 0xE7);

// SuperClass — only Type.
struct Super_005051E0
{
    char                _pad000[0x28];   // +0x0000
    SuperType_005051E0* Type;            // +0x0028
};
GG_STATIC_ASSERT(offsetof(Super_005051E0, Type) == 0x28);

// DynamicVectorClass<TechnoTypeClass*> — Items and Count.
struct TypeVector_005051E0
{
    void*                  Vptr;      // +0x0000
    TechnoType_005051E0**  Items;     // +0x0004
    char                   _pad008[8]; // +0x0008
    int                    Count;     // +0x0010
};
GG_STATIC_ASSERT(offsetof(TypeVector_005051E0, Items) == 0x4);
GG_STATIC_ASSERT(offsetof(TypeVector_005051E0, Count) == 0x10);

// RulesClass — BuildConst Items / Count.
struct Rules_005051E0
{
    char                   _pad000[0x920];   // +0x0000
    TechnoType_005051E0**  BuildConstItems;  // +0x0920
    char                   _pad924[8];       // +0x0924
    int                    BuildConstCount;  // +0x092C
};
GG_STATIC_ASSERT(offsetof(Rules_005051E0, BuildConstItems) == 0x920);
GG_STATIC_ASSERT(offsetof(Rules_005051E0, BuildConstCount) == 0x92C);
// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_005051E0* DAT_008871E0;

// GLOBAL: GAMEMD 0xA8B263 — SWAllowed.
extern char DAT_00A8B263;

// HouseClass — Type and the Supers items.
struct House_005051E0
{
    char                 _pad000[0x34];           // +0x0000
    HouseType_005051E0*  Type;                    // +0x0034
    char                 _pad038[0x258 - 0x38];   // +0x0038
    Super_005051E0**     SupersItems;             // +0x0258 (Supers.Items)

    // FUNCTION: GAMEMD 0x5051E0 — HouseClass::FirstBuildableFromArray.
    TechnoType_005051E0* FirstBuildableFromArray(TypeVector_005051E0* items);
};
GG_STATIC_ASSERT(offsetof(House_005051E0, Type)        == 0x34);
GG_STATIC_ASSERT(offsetof(House_005051E0, SupersItems) == 0x258);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_FIRST_BUILDABLE_METHODS_H

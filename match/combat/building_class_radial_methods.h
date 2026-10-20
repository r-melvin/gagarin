// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4566B0: the type at `[ESI+0x520]`, on it
//   `[ECX+0x170C]` (int), the bytes `[ECX+0xCD1]`, `[ECX+0xCD2]`,
//   `[ECX+0xCD3]`, `[ECX+0x16C8]`, `[ECX+0x16C7]` and the sign-extended
//   `[ECX+0x1707]`; on the building the byte `[ESI+0x268]`; on the weapon
//   struct `[EDI]` and on its type `[EAX+0xB4]` (range, divided by 256).
//   Callees 0x70E1A0 (TechnoClass::GetPrimaryWeapon) and 0x70E240 (a
//   weapon-validity predicate) are __thiscall on the building. Names
//   cross-checked against YRpp BuildingClass::GetRadialIndicatorRange and the
//   committed spines match/_layout/techno_class.h (GapSuperCharged @0x268),
//   techno_type_class.h (GapGenerator @0xCD1, GapRadiusInCells @0xCD2,
//   SuperGapRadiusInCells @0xCD3), building_type_class_layout.h
//   (CloakRadiusInCells @0x1707, PsychicDetectionRadius @0x170C) and
//   match/combat/weapon_type_class.h (Range @0xB4) — all re-derived here.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_RADIAL_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_RADIAL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct WeaponTypeClass_004566B0
{
    char _pad000[0xB4];   // +0x0000
    int  Range;           // +0x00B4  leptons
};
GG_STATIC_ASSERT(offsetof(WeaponTypeClass_004566B0, Range) == 0xB4);

struct WeaponStruct_004566B0
{
    WeaponTypeClass_004566B0* WeaponType;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(WeaponStruct_004566B0, WeaponType) == 0x0);

struct Type_004566B0
{
    char        _pad000[0xCD1];               // +0x0000
    char        GapGenerator;                 // +0x0CD1
    char        GapRadiusInCells;             // +0x0CD2
    char        SuperGapRadiusInCells;        // +0x0CD3
    char        _padCD4[0x16C7 - 0xCD4];      // +0x0CD4
    char        CloakGenerator;               // +0x16C7
    char        SensorArray;                  // +0x16C8
    char        _pad16C9[0x1707 - 0x16C9];    // +0x16C9
    char        CloakRadiusInCells;           // +0x1707  (sign-extended)
    char        _pad1708[4];                  // +0x1708
    int         PsychicDetectionRadius;       // +0x170C
};
GG_STATIC_ASSERT(offsetof(Type_004566B0, GapGenerator) == 0xCD1);
GG_STATIC_ASSERT(offsetof(Type_004566B0, GapRadiusInCells) == 0xCD2);
GG_STATIC_ASSERT(offsetof(Type_004566B0, SuperGapRadiusInCells) == 0xCD3);
GG_STATIC_ASSERT(offsetof(Type_004566B0, CloakGenerator) == 0x16C7);
GG_STATIC_ASSERT(offsetof(Type_004566B0, SensorArray) == 0x16C8);
GG_STATIC_ASSERT(offsetof(Type_004566B0, CloakRadiusInCells) == 0x1707);
GG_STATIC_ASSERT(offsetof(Type_004566B0, PsychicDetectionRadius) == 0x170C);

struct BuildingClass_004566B0
{
    char             _pad000[0x268];          // +0x0000
    char             GapSuperCharged;         // +0x0268
    char             _pad269[0x520 - 0x269];  // +0x0269
    Type_004566B0*   Type;                    // +0x0520

    // FUNCTION: GAMEMD 0x70E1A0 (decl; reloc) — TechnoClass::GetPrimaryWeapon.
    WeaponStruct_004566B0* GetPrimaryWeapon();
    // FUNCTION: GAMEMD 0x70E240 (decl; reloc) — weapon-validity predicate
    // (non-null weapon with a non-null type).
    bool FUN_0070E240(WeaponStruct_004566B0* weapon);

    // FUNCTION: GAMEMD 0x4566B0
    int GetRadialIndicatorRange();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_004566B0, GapSuperCharged) == 0x268);
GG_STATIC_ASSERT(offsetof(BuildingClass_004566B0, Type) == 0x520);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_RADIAL_METHODS_H

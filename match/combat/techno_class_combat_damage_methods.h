// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x6F3970: the weapon slot `[EDX+0x3F8]` (one pushed
//   index, returning the weapon struct whose weapon type sits at +0),
//   the type slot `[EAX+0x84]`, the gattling probe 0x717880 with the type
//   in ECX and the type's byte at `+0xCD5`, the gattling stage at
//   `[ESI+0x138]`, and the weapon type's damage at `+0xA4` and its second
//   term at `+0x98`. Names cross-checked against YRpp.
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_COMBAT_DAMAGE_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_COMBAT_DAMAGE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct WeaponType_006F3970
{
    char _pad000[0x98];   // +0x0000
    int  At_98;           // +0x0098
    char _pad09C[8];      // +0x009C
    int  Damage;          // +0x00A4
};
GG_STATIC_ASSERT(offsetof(WeaponType_006F3970, At_98)  == 0x98);
GG_STATIC_ASSERT(offsetof(WeaponType_006F3970, Damage) == 0xA4);

struct Weapon_006F3970
{
    WeaponType_006F3970* Type;   // +0x0000
};

struct TechnoType_006F3970
{
    char _pad000[0xCD5];   // +0x0000
    char IsGattling;       // +0x0CD5
};
GG_STATIC_ASSERT(offsetof(TechnoType_006F3970, IsGattling) == 0xCD5);

// FUNCTION: GAMEMD 0x717880 (decl; reloc) — does this type fire in bursts.
bool FUN_00717880(TechnoType_006F3970* type);

struct Vtbl_006F3970;

struct Techno_006F3970
{
    Vtbl_006F3970* Vptr;            // +0x0000
    char           _pad004[0x134];  // +0x0004
    int            GattlingStage;   // +0x0138

    // FUNCTION: GAMEMD 0x6F3970 — TechnoClass::CombatDamage.
    int CombatDamage(int which);
};
GG_STATIC_ASSERT(offsetof(Techno_006F3970, GattlingStage) == 0x138);

typedef TechnoType_006F3970* (Techno_006F3970::*Fn84_006F3970)();
typedef Weapon_006F3970*     (Techno_006F3970::*Fn3F8_006F3970)(int index);

struct Vtbl_006F3970
{
    char             _pad000[0x84];          // +0x0000
    Fn84_006F3970    GetTechnoType;          // +0x0084
    char             _pad088[0x3F8 - 0x88];  // +0x0088
    Fn3F8_006F3970   GetWeapon;              // +0x03F8
};
GG_STATIC_ASSERT(offsetof(Vtbl_006F3970, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_006F3970, GetWeapon)     == 0x3F8);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_COMBAT_DAMAGE_METHODS_H

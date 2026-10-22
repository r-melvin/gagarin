// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x70D690: the techno vtable slots
//   `CALL [EAX+0x84]` (GetTechnoType), `CALL [EDX+0x3F4]` (GetTurretWeapon,
//   returns a WeaponStruct whose +0 is the WeaponTypeClass*) and
//   `CALL [EAX+0x48]` (GetCoords, out-pointer pushed, pointer returned); on the
//   techno type `[EAX+0xD18]` (DeathWeapon), `FMUL dword [EAX+0xD1C]`
//   (DeathWeaponDamageModifier), `FILD [EAX+0xA0]` (Strength); on the weapon
//   `[EDI+0xA0]` (Projectile, into ECX), `FILD [EDI+0xA4]` (Damage),
//   `[EDI+0xAC]` (Warhead), `MOV AL,[EDI+0x12F]` (Bright); on the rules
//   object `[0x8871E0]` the weapon `[EAX+0xFDC]`; `FMUL qword [0x7E1738]`
//   (0.5). Callees: `CALL 0x46B050` (__fastcall bullet creation, ECX =
//   projectile, EDX = owner, five stack args), `CALL 0x46B260` (__thiscall,
//   one arg), bullet slots `[EDX+0xD4]` (no args) and `[EDX+0x8]` (COM
//   Release, receiver pushed), `CALL 0x4690B0` (BulletClass::Detonate), and
//   `CALL 0x7C5F00` (__ftol). Names from the YRpp method map / the vtable
//   map; the type offsets agree with match/_layout/
//   techno_type_class.h and object_type_class.h, the weapon offsets with
//   match/combat/weapon_type_class.h (Bright @0x12F is local to this TU).
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_DEATH_WEAPON_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_DEATH_WEAPON_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct CoordStruct_0070D690
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(CoordStruct_0070D690) == 0xC);

struct BulletType_0070D690;
struct Warhead_0070D690;

// WeaponTypeClass — only the members FireDeathWeapon reads.
struct Weapon_0070D690
{
    char                _pad000[0xA0];        // +0x0000
    BulletType_0070D690* Projectile;          // +0x00A0
    int                 Damage;               // +0x00A4
    char                _pad0A8[4];           // +0x00A8
    Warhead_0070D690*   Warhead;              // +0x00AC
    char                _pad0B0[0x12F - 0xB0];// +0x00B0
    bool                Bright;               // +0x012F
};
GG_STATIC_ASSERT(offsetof(Weapon_0070D690, Projectile) == 0xA0);
GG_STATIC_ASSERT(offsetof(Weapon_0070D690, Damage)     == 0xA4);
GG_STATIC_ASSERT(offsetof(Weapon_0070D690, Warhead)    == 0xAC);
GG_STATIC_ASSERT(offsetof(Weapon_0070D690, Bright)     == 0x12F);

// WeaponStruct — the turret weapon record; its first member is the type.
struct WeaponStruct_0070D690
{
    Weapon_0070D690* WeaponType;   // +0x0000
};

// TechnoTypeClass — only the members FireDeathWeapon reads.
struct TechnoType_0070D690
{
    char             _pad000[0xA0];            // +0x0000
    int              Strength;                 // +0x00A0
    char             _pad0A4[0xD18 - 0xA4];    // +0x00A4
    Weapon_0070D690* DeathWeapon;              // +0x0D18
    float            DeathWeaponDamageModifier;// +0x0D1C
};
GG_STATIC_ASSERT(offsetof(TechnoType_0070D690, Strength)                  == 0xA0);
GG_STATIC_ASSERT(offsetof(TechnoType_0070D690, DeathWeapon)               == 0xD18);
GG_STATIC_ASSERT(offsetof(TechnoType_0070D690, DeathWeaponDamageModifier) == 0xD1C);

// RulesClass — only the fallback weapon.
struct Rules_0070D690
{
    char             _pad000[0xFDC];   // +0x0000
    Weapon_0070D690* At_FDC;           // +0x0FDC  fallback death weapon
};
GG_STATIC_ASSERT(offsetof(Rules_0070D690, At_FDC) == 0xFDC);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_0070D690* RulesInstance_0070D690;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct TechnoVtbl_0070D690;

// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
class TechnoClass
{
public:
    TechnoVtbl_0070D690* Vtbl;   // +0x0000

    // FUNCTION: GAMEMD 0x70D690  TechnoClass::FireDeathWeapon (__thiscall)
    int FireDeathWeapon(int extraDamage);
};

typedef TechnoType_0070D690*   (TechnoClass::*Fn84_0070D690)();
typedef WeaponStruct_0070D690* (TechnoClass::*Fn3F4_0070D690)();
typedef CoordStruct_0070D690*  (TechnoClass::*Fn48_0070D690)(CoordStruct_0070D690* out);

struct TechnoVtbl_0070D690
{
    char           _pad000[0x48];            // +0x0000
    Fn48_0070D690  GetCoords;                // +0x0048
    char           _pad04C[0x84 - 0x4C];     // +0x004C
    Fn84_0070D690  GetTechnoType;            // +0x0084
    char           _pad088[0x3F4 - 0x88];    // +0x0088
    Fn3F4_0070D690 GetTurretWeapon;          // +0x03F4
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl_0070D690, GetCoords)       == 0x48);
GG_STATIC_ASSERT(offsetof(TechnoVtbl_0070D690, GetTechnoType)   == 0x84);
GG_STATIC_ASSERT(offsetof(TechnoVtbl_0070D690, GetTurretWeapon) == 0x3F4);

struct BulletVtbl_0070D690;

// BulletClass — the freshly created projectile; dispatched through two slots
// and two non-virtual members.
struct Bullet_0070D690
{
    BulletVtbl_0070D690* Vtbl;   // +0x0000

    // FUNCTION: GAMEMD 0x46B260 (decl; reloc) — attach the weapon type.
    void FUN_0046B260(Weapon_0070D690* weapon);
    // FUNCTION: GAMEMD 0x4690B0 (decl; reloc) — BulletClass::Detonate.
    void Detonate(CoordStruct_0070D690* coord);
};

typedef unsigned long (__stdcall* FnRelease_0070D690)(Bullet_0070D690* self);
typedef void (Bullet_0070D690::*FnD4_0070D690)();

struct BulletVtbl_0070D690
{
    char               _pad000[0x8];           // +0x0000
    FnRelease_0070D690 Release;                // +0x0008  IUnknown::Release
    char               _pad00C[0xD4 - 0xC];    // +0x000C
    FnD4_0070D690      At_D4;                  // +0x00D4
};
GG_STATIC_ASSERT(offsetof(BulletVtbl_0070D690, Release) == 0x8);
GG_STATIC_ASSERT(offsetof(BulletVtbl_0070D690, At_D4)   == 0xD4);

// FUNCTION: GAMEMD 0x46B050 (decl; reloc) — create a bullet of the projectile
// type: __fastcall with the projectile in ECX and the owner in EDX, then
// target, damage, warhead, speed and the bright flag on the stack.
Bullet_0070D690* __fastcall FUN_0046B050(BulletType_0070D690* projectile,
                                          TechnoClass* owner,
                                          TechnoClass* target,
                                          int damage,
                                          Warhead_0070D690* warhead,
                                          int speed,
                                          bool bright);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_DEATH_WEAPON_METHODS_H

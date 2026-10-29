// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x70D690.
//   LIBRARY: GAMEMD 0x7C5F00  __ftol (CRT double->long; the (int) casts; reloc)

#include "techno_class_death_weapon_methods.h"

// FUNCTION: GAMEMD 0x70D690
//
// Fire the object's death weapon at its own position. The weapon is the type's
// DeathWeapon, else the turret weapon, else the rules fallback; the damage is
// the weapon's damage scaled by the type's death-weapon modifier (half the
// type's strength for the fallback), plus the caller's extra. A bullet is
// created on this object, given the weapon, detonated at our coordinates and
// released. Returns the damage dealt, or zero when there was no weapon.
//
// The turret-weapon test binds one call result to a local (retail tests
// `EAX` and then `[EAX]` off a single `CALL [EDX+0x3F4]`), while the weapon
// itself is read through a second call; the death-weapon branch instead
// calls GetTechnoType three times. Phrasing the test as two calls scored
// 81.3%; binding the type or turret result for the damage line 21.1%.
int TechnoView_0070D690::FireDeathWeapon(int extraDamage)
{
    Weapon_0070D690* weapon;
    int damage;

    if ((this->*this->Vtbl->GetTechnoType)()->DeathWeapon != 0) {
        weapon = (this->*this->Vtbl->GetTechnoType)()->DeathWeapon;
        damage = (int)(weapon->Damage * (this->*this->Vtbl->GetTechnoType)()->DeathWeaponDamageModifier);
    } else {
        WeaponStruct_0070D690* turret = (this->*this->Vtbl->GetTurretWeapon)();
        if (turret != 0 && turret->WeaponType != 0) {
            weapon = (this->*this->Vtbl->GetTurretWeapon)()->WeaponType;
            damage = (int)(weapon->Damage * (this->*this->Vtbl->GetTechnoType)()->DeathWeaponDamageModifier);
        } else {
            weapon = RulesInstance_0070D690->At_FDC;
            damage = (int)((this->*this->Vtbl->GetTechnoType)()->Strength * 0.5);
        }
    }

    if (weapon == 0) {
        return 0;
    }

    damage += extraDamage;

    Bullet_0070D690* bullet = FUN_0046B050(weapon->Projectile, this, this, damage,
                                           weapon->Warhead, 0, weapon->Bright);
    if (bullet != 0) {
        bullet->FUN_0046B260(weapon);
        (bullet->*bullet->Vtbl->At_D4)();
        CoordStruct_0070D690 coord;
        bullet->Detonate((this->*this->Vtbl->GetCoords)(&coord));
        bullet->Vtbl->Release(bullet);
    }

    return damage;
}

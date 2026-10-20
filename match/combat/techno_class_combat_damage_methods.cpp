// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6F3970.

#include "techno_class_combat_damage_methods.h"

// FUNCTION: GAMEMD 0x6F3970
//
// The damage one weapon does, or, asked about no weapon in particular, the
// average over the weapons this object actually carries. A burst-firing
// type that is not itself a gattling reports only the weapon its current
// stage selects.
//
// PARTIAL (24.4%, up from 6.5%; 120 instructions against retail's 123).
// The lever was block placement, not phrasing: retail tests `which != -1`
// and jumps AWAY to the single-weapon path, so the all-weapons body is the
// fallthrough and the single-weapon body sits at the end of the function.
// Writing the guard the other way round (`if (which != -1) { ...; return
// total; }` first) puts the short arm inline and shifts all 120 instructions.
// Inverting it to `if (which == -1) { ...big...} ` with the single-weapon
// tail trailing reproduces retail's own layout and every call, guard and
// accumulation lines up.
//
// Residual, and it is two separate 8447-vs-8804 backend differences:
//   * retail DUPLICATES the averaging tail into the burst arm and divides by
//     a register holding one (`MOV EBX,1; ... CDQ; IDIV EBX`); cl 8804
//     propagates the constant into the division and deletes it. Measured:
//     a per-arm `return total / count;` costs an extra zero-return block and
//     scores 23.4%; one shared tail keeps 24.4% and is kept.
//   * retail reaches the zero return with `TEST EBX,EBX; JLE` backwards to a
//     shared `XOR EAX,EAX` block placed inline in the burst arm; cl inlines
//     its own zero return at the test and jumps over it with `JG`. Routing
//     both zero exits through one `goto zero;` label makes cl merge the burst
//     arm's two zero blocks as well and loses three more instructions
//     (21.1% / 22.0% over three label placements), so the guards stay
//     separate.
int Techno_006F3970::CombatDamage(int which)
{
    int total = 0;

    if (which == -1) {
        int count = 0;
        if (FUN_00717880((this->*Vptr->GetTechnoType)())
            && (this->*Vptr->GetTechnoType)()->IsGattling == 0) {
            Weapon_006F3970* weapon = (this->*Vptr->GetWeapon)(GattlingStage);
            if (weapon == 0) {
                return 0;
            }
            WeaponType_006F3970* type = weapon->Type;
            if (type == 0) {
                return 0;
            }
            total = type->Damage + type->At_98;
            count = 1;
        } else {
            if ((this->*Vptr->GetWeapon)(0)->Type != 0) {
                total = (this->*Vptr->GetWeapon)(0)->Type->Damage;
                count = 1;
                total += (this->*Vptr->GetWeapon)(0)->Type->At_98;
            }
            if ((this->*Vptr->GetWeapon)(1)->Type != 0) {
                total += (this->*Vptr->GetWeapon)(1)->Type->Damage;
                total += (this->*Vptr->GetWeapon)(1)->Type->At_98;
                count++;
            }
            if (count <= 0) {
                return 0;
            }
        }
        return total / count;
    }

    if ((this->*Vptr->GetWeapon)(which)->Type != 0) {
        total = (this->*Vptr->GetWeapon)(which)->Type->Damage;
        total += (this->*Vptr->GetWeapon)(which)->Type->At_98;
    }
    return total;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x489180.
//   LIBRARY: GAMEMD 0x7C5F00 __ftol (CRT float->long; excluded from match).

#include "map_class_total_damage_methods.h"

// FUNCTION: GAMEMD 0x489180
//
// Total damage a warhead does at `distance` leptons from its impact point.
// Zero when there is no damage, no warhead, or the scenario is Inert. Negative
// damage (healing) applies only within 8 leptons and is not scaled. Otherwise
// the damage falls off linearly from full at the centre to PercentAtMax at the
// edge of CellSpread (converted to leptons), is clamped at zero, multiplied by
// the Verses entry for the target armor, and capped at Rules MaxDamage.
//
// Phrasing note: the three zero guards are one `||` chain so they share the
// single `XOR EAX,EAX` tail at the end of the function; three separate
// `return 0;` blocks each get their own epilogue (8.2%). The `cond ? x : 0`
// forms reproduce the SETcc/DEC/AND idiom, and the int operands stay inline
// in the float expression so they reach FIMUL/FIDIV from their spill slots.
int MapClass::GetTotalDamage(int damage, WarheadType_00489180* warhead,
                             int armor, int distance)
{
    if (damage == 0 || (ScenarioInstance->SpecialFlags & 0x20) || warhead == 0) {
        return 0;
    }
    if (damage < 0) {
        return (distance < 8) ? damage : 0;
    }

    float fdamage = (float)damage;
    float scaled = fdamage * warhead->PercentAtMax;
    int spread = (int)(warhead->CellSpread * 256.0f);

    if (scaled != fdamage && spread != 0) {
        damage = (int)((fdamage - scaled) * (spread - distance) / spread + scaled);
    }

    int positive = (damage > 0) ? damage : 0;
    int result = (int)(positive * warhead->Verses[armor]);

    if (result < RulesInstance->MaxDamage) {
        return result;
    }
    return RulesInstance->MaxDamage;
}

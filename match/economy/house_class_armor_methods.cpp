// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x50BD30.

#include "house_class_armor_methods.h"

// FUNCTION: GAMEMD 0x50BD30  HouseClass::GetArmorMultiplier (__thiscall, ret 0x4)
// Pick the armour multiplier that applies to a given subject. Retail lowers
// this to a byte index table plus a jump table rather than a compare chain —
// the labels 3, 7, 0x10 and 0x28 span a range dense enough for VC6 to prefer
// it — so a `switch` is the construct that reproduces it (§4.6).
float HouseClass::GetArmorMultiplier(TechnoClass* subject)
{
    switch (TECHNO_WHAT_AM_I(subject))
    {
    case ABS_KIND_10:
        return Armor->Mult_100;

    case ABS_KIND_28:
        return Armor->Mult_104;

    case ABS_UNIT_3:
        return Armor->Mult_108;

    case ABS_KIND_7:
        if (subject->unknown_E08 == 5)
            return Armor->Mult_110;

        return Armor->Mult_10C;
    }

    return DefaultArmorMultiplier;
}

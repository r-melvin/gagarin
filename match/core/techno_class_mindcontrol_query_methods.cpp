// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x53C450.

#include "techno_class_mindcontrol_query_methods.h"

// FUNCTION: GAMEMD 0x53C450  TechnoClass::CanBePermaMindControlled (__thiscall)
// A chain of disqualifiers, each returning early — which is why retail carries
// five separate `XOR AL,AL; POP ESI; RET` epilogues rather than one shared exit.
// It opens by testing `this` itself, so retail expects to be called on a
// possibly-null pointer.
//
// The final disqualifier is written as a branch, not a negation. `return !x;`,
// `x == 0` and `x == false` all compile to the full-width bool idiom
// `NEG AL; SBB EAX,EAX; INC EAX` regardless of whether the slot is typed bool,
// unsigned char or int — a standalone probe confirmed all six combinations.
// Writing it as a branch instead (`if (x) return false; return true;`, or the
// equivalent ternary) gives retail's `TEST AL,AL; SETE AL`. That is the whole
// difference between the earlier 91.8% and byte parity here.
bool TechnoClass::CanBePermaMindControlled()
{
    if (this == 0)
        return false;

    if (TECHNO_WHAT_AM_I(this) == ABS_BUILDING)
        return false;

    if (TECHNO_GET_TYPE(this)->unknown_D35)
        return false;

    if (TECHNO_SLOT_160(this))
        return false;

    if (TECHNO_GET_TYPE(this)->unknown_D6A)
        return false;

    if (TECHNO_SLOT_54(this))
        return false;

    return true;
}

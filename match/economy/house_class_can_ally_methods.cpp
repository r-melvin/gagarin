// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x501540.

#include "house_class_can_ally_methods.h"
#include "../_layout/session_class.h"

// FUNCTION: GAMEMD 0x501540
//
// May this house propose an alliance with `other`? Not with itself, an ally,
// or nobody; not with the civilian house outside a campaign; always during
// scenario setup; never once defeated. Otherwise only while at least one
// other live, non-passive house is still outside the alliance.
bool House_00501540::CanAlly(House_00501540* other)
{
    if (IsAlliedWith(other)) {
        return false;
    }
    if (other->Type->ArrayIndex2 == DAT_00818164.FindIndex() && Session_00A8B238.GameMode != 0) {
        return false;
    }
    if (DAT_00A8E7AC != 0) {
        return true;
    }
    if (Defeated) {
        return false;
    }

    int alive = 0;
    int allied = 0;
    for (int i = 0; i < DAT_00A80238; i++) {
        House_00501540* house = DAT_00A8022C[i];
        if (!house->Defeated && !house->Type->MultiplayPassive) {
            alive++;
            if (IsAlliedWith(house)) {
                allied++;
            }
        }
    }
    bool others = alive != allied + 1;
    return others;
}

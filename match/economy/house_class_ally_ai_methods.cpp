// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x501640.

#include "house_class_ally_ai_methods.h"

// FUNCTION: GAMEMD 0x501640
//
// Line the AI houses up against the humans. When the game-mode object (or the
// rules override) asks for it, and the scenario does not forbid it, every live
// computer house is marked and then made an ally of every other live computer
// house and an enemy of every live human-controlled one.
void House_00501640::AllyAIHouses()
{
    bool forced = DAT_008871E0->unknown_14B5;
    if ((DAT_00A8B23C != 0 && (DAT_00A8B23C->*DAT_00A8B23C->Vtbl->At_4)()) || forced) {
        if (!DAT_00A8B230->unknown_1180.unknown_60) {
            for (int i = 0; i < DAT_00A80238; i++) {
                House_00501640* house = DAT_00A8022C[i];
                if (house != 0 && !house->Defeated && !house->IsControlledByHuman()) {
                    house->At_24A = true;
                    for (int j = 0; j < DAT_00A80238; j++) {
                        House_00501640* other = DAT_00A8022C[j];
                        if (other != 0 && !other->Defeated) {
                            if (other->IsControlledByHuman()) {
                                house->MakeEnemy(other, false);
                            } else {
                                house->MakeAlly(other, false);
                            }
                        }
                    }
                }
            }
        }
    }
}

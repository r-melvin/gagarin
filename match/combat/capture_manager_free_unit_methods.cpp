// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 at 0x471FF0.

#include "capture_manager_free_unit_methods.h"

// FUNCTION: GAMEMD 0x471FF0
//
// CaptureManagerClass::FreeUnit — release one mind-controlled unit.
//
// The ControlNodes vector is walked back to front looking for the node whose
// Unit is the argument. On a hit the mind-control ring animation is killed
// (slot 0xF8) and unlinked, the "control lost" voice is played at the unit's
// coordinates (the unit type's own sound if it has one, otherwise the rules
// fallback, and nothing at all if neither is set), the unit is handed back to
// the house recorded in the node, the manager's owner bookkeeping is updated,
// the back-pointer at +0x2C0 is cleared, the node is freed and the vector is
// closed up over the hole. A null unit reports false; anything else reports
// true, hit or not.
bool CaptureManager_00471FF0::FreeUnit(Techno_00471FF0* unit)
{
    if (unit == 0) {
        return false;
    }

    for (int i = this->Count - 1; i >= 0; i--) {
        ControlNode_00471FF0* node = this->Items[i];
        if (node->Unit == unit) {
            if (unit->MindControlRingAnim != 0) {
                Anim_00471FF0* anim = unit->MindControlRingAnim;
                (anim->*anim->Vtbl->At_F8)();
                unit->MindControlRingAnim = 0;
            }

            if ((unit->*unit->Vtbl->At_84)()->At_5B0 != -1) {
                VocClass_PlayAt_00471FF0(
                    (unit->*unit->Vtbl->At_84)()->At_5B0, unit->GetCoords(), 0);
            } else if (RulesInstance_00471FF0->At_264 != -1) {
                VocClass_PlayAt_00471FF0(
                    RulesInstance_00471FF0->At_264, unit->GetCoords(), 0);
            }

            (unit->*unit->Vtbl->At_3D4)(node->OriginalOwner, 1);
            this->FUN_004723B0(unit);
            unit->MindControlledBy = 0;

            ControlNode_00471FF0* dead = this->Items[i];
            if (dead != 0) {
                GameDelete_00471FF0(dead);
            }

            if (i < this->Count) {
                this->Count = this->Count - 1;
                for (int j = i; j < this->Count; j++) {
                    this->Items[j] = this->Items[j + 1];
                }
            }
        }
    }

    return true;
}

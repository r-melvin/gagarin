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
bool CaptureManagerClass::FreeUnit(TechnoClass* unit)
{
    if (unit == 0) {
        return false;
    }

    Techno_00471FF0* unitView = (Techno_00471FF0*)unit;

    for (int i = ControlNodes.Count - 1; i >= 0; i--) {
        ControlNode* node = ((ControlNode**)ControlNodes.Items)[i];
        if (node->Unit == unit) {
            if (unitView->MindControlRingAnim != 0) {
                Anim_00471FF0* anim = unitView->MindControlRingAnim;
                (anim->*anim->Vtbl->At_F8)();
                unitView->MindControlRingAnim = 0;
            }

            if ((unitView->*unitView->Vtbl->At_84)()->At_5B0 != -1) {
                VocClass_PlayAt_00471FF0(
                    (unitView->*unitView->Vtbl->At_84)()->At_5B0, unitView->GetCoords(), 0);
            } else if (RulesInstance_00471FF0->At_264 != -1) {
                VocClass_PlayAt_00471FF0(
                    RulesInstance_00471FF0->At_264, unitView->GetCoords(), 0);
            }

            (unitView->*unitView->Vtbl->At_3D4)(node->OriginalOwner, 1);
            FUN_004723B0(unit);
            unitView->MindControlledBy = 0;

            ControlNode* dead = ((ControlNode**)ControlNodes.Items)[i];
            if (dead != 0) {
                GameDelete_00471FF0(dead);
            }

            if (i < ControlNodes.Count) {
                ControlNodes.Count = ControlNodes.Count - 1;
                for (int j = i; j < ControlNodes.Count; j++) {
                    ((ControlNode**)ControlNodes.Items)[j] = ((ControlNode**)ControlNodes.Items)[j + 1];
                }
            }
        }
    }

    return true;
}

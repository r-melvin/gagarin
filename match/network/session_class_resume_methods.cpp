// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x69BAB0.

#include "session_class_resume_methods.h"

// FUNCTION: GAMEMD 0x69BAB0
//
// Resume an in-game frame after a pause: mark the frame active, restore the
// saved game speed (campaign games are forced back to speed 2), re-arm the
// frame deadline when the provider flag is clear, make sure the mouse is
// captured, and finally set 0x4000 on the shared flags object — a __fastcall
// in tail position, which is why retail ends in a JMP.
void SessionClass::Resume()
{
    if (this->InGameFrameActive == 0 && DAT_00A8E9A0 != 0) {
        this->InGameFrameActive = 1;

        if (DAT_0083ED20 == -1) {
            DAT_0083ED20 = DAT_00A8EB60;
        }
        if (this->GameMode == 0) {
            DAT_00A8EB60 = 2;
        }
        if (DAT_00A8B230->At_35A2 == 0) {
            FUN_00684240();
            DAT_00B07784 = DAT_00A8ED84 + 3;
        }
        if (!(DAT_00887640->*DAT_00887640->Vtbl->At_1C)()) {
            (DAT_00887640->*DAT_00887640->Vtbl->At_18)();
        }
        DAT_0087E758->FUN_00407150(0x4000);
    }
}

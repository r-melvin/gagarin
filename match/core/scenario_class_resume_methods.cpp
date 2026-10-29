// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x683FB0.

#include "scenario_class_resume_methods.h"

// FUNCTION: GAMEMD 0x683FB0
//
// Bring a paused game back: restart the map, resume the elapsed-time clock and
// log its reading, restore the tooltip state, hand the saved level back to the
// 0x87E758 object and reset the saved value, drop the 0x5BF500 flag, and end
// with the resume-all leaf as a tail jump.
void ScenarioClass::ResumeGame()
{
    MapInstance.FUN_005BDAA0();

    ScenarioInstance->ElapsedTimer.Resume();
    FUN_004068E0(DAT_0083D908, ScenarioInstance->ElapsedTimer.GetElapsed());

    if (DAT_00887368 != 0) {
        DAT_00887368->SetState(DAT_00A8EB80);
    }

    FUN_00407150(&DAT_0087E758->First, DAT_0083D834);
    DAT_0083D834 = 0x4000;
    FUN_005BF500(false);
    FUN_00406F40();
}

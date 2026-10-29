// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x683EB0.

#include "scenario_class_pause_methods.h"

// FUNCTION: GAMEMD 0x683EB0
//
// Freeze a running game: run the shutdown-path leaf, save the 0x87E758
// object's level and drop it to 0x4000, then (in a campaign or skirmish
// session only) log the elapsed-time reading and stop the clock. The 0x5BF500
// flag is raised, the tooltips are switched off, the map is told to pause and
// redraw its sidebar and render, and the mouse gets its slot-3 call plus the
// slot-4 tail jump.
//
// Exact under the project default /Gr (static member, so fastcall). The
// cdecl build of this body left two pure ordering deltas (91.0%): the POP ESI
// position around the tooltip test, and ECX loaded after rather than before
// the pushes for the two map calls. Neither moved under any source spelling.
void ScenarioClass::PauseGame()
{
    FUN_00406F00();
    DAT_0083D834 = FUN_004072B0(&DAT_0087E758->First);
    FUN_00407150(&DAT_0087E758->First, 0x4000);

    if (SessionInstance.GameMode == 0 || SessionInstance.GameMode == 5) {
        FUN_004068E0(DAT_0083D8EC, ScenarioInstance->ElapsedTimer.GetElapsed());
        ScenarioInstance->ElapsedTimer.Pause();
    }

    FUN_005BF500(true);

    if (DAT_00887368 != 0) {
        DAT_00887368->SetState(false);
    }

    MapInstance.FUN_006938C0();
    MapInstance.FUN_005BDC80(0, 0);
    (DAT_00887640->*DAT_00887640->Vtbl->At_0C)();
    MapInstance.FlagToRedraw(2);
    MapInstance.Render();
    (DAT_00887640->*DAT_00887640->Vtbl->At_10)();
}

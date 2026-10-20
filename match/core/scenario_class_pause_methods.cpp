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
// PARTIAL (91.0%, 61/67): the instruction multiset is identical; two pure
// ordering deltas remain. (1) `MOV ECX,[0x887368]; TEST ECX,ECX; POP ESI; JZ`
// in retail is emitted here as `MOV; POP ESI; TEST; JZ` (the POP moves one
// slot). (2) Both calls on the static map object that take immediate
// arguments — `PUSH 0; PUSH 0; CALL 0x5BDC80` and `PUSH 2; CALL 0x4F42F0` —
// have retail's `MOV ECX,0x87F7E8` ahead of the pushes where cl 8804 pushes
// first; this is the open "`this`-load / argument-push order in a call run"
// class in docs/matching_methodology_and_toolchain.md (retail loads ECX
// first once the constant object has already been used earlier in the
// function, as it has here by the argument-less 0x6938C0 call). Variants
// tried, all byte-identical to this one: a ternary object expression on the
// two calls; a pointer local to the map; a reference/pointer helper; the
// two-arg call wrapped in an inline member of a derived view; the whole
// tail as one inline member; a static inline free helper taking the map
// pointer; the tooltip pointer read into a local; the tooltip test as a
// named bool; the session mode read into a local int; the timer taken
// through a pointer local. Kept the plain phrasing.
void ScenarioClass::PauseGame()
{
    FUN_00406F00();
    DAT_0083D834 = DAT_0087E758->FUN_004072B0();
    DAT_0087E758->FUN_00407150(0x4000);

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
    MapInstance.RedrawSidebar(2);
    MapInstance.Render();
    (DAT_00887640->*DAT_00887640->Vtbl->At_10)();
}

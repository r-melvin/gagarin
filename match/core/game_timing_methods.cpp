// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6C87F0 and 0x6C8820.

#include "game_timing_methods.h"

// FUNCTION: GAMEMD 0x6C87F0  Unsorted::RegisterGameStartTime (__fastcall)
// Restart the clock: a fresh timer temporary (start tick sampled through the
// clock member) is copied over the global, and the running flag is raised.
void __fastcall Unsorted_RegisterGameStartTime()
{
    GameTimer = GameTimerClass();
    GameTimerRunning = true;
}

// FUNCTION: GAMEMD 0x6C8820  Unsorted::RegisterGameEndTime (__fastcall)
// Stop the clock and bank how long the game ran. Retail loads the start tick
// and clears the running flag *between* the call and the subtraction, which is
// what reading the start into a local before clearing the flag produces.
void __fastcall Unsorted_RegisterGameEndTime()
{
    int now = GameTimer.Clock.GetTime();
    int start = GameTimer.StartTime;
    GameTimerRunning = false;
    GameElapsedTime = now - start;
}

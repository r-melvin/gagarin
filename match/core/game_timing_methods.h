// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and the call shape read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x6C87F0 and 0x6C8820. Names
//   cross-checked against YRpp (`Unsorted::RegisterGameStartTime` /
//   `RegisterGameEndTime`, consult-only, no LICENSE).
//
// The game clock is an 8-byte timer object at 0x00B0BD28: the start tick at
// +0 and an empty clock member at +4. Retail reaches the clock's GetTime with
// `MOV ECX,0xB0BD2C; CALL 0x6C8C40` (0x6C8820) and, when re-arming the timer,
// with `LEA ECX,[ESP+4]` on a stack temporary (0x6C87F0) — so the clock is a
// member object rather than a pointer, and its GetTime is a __thiscall whose
// `this` the callee ignores (the timeGetTime()>>4 leaf matched in
// match/platform/system_query_methods.cpp).
//
// The constructor writes only the start tick; the clock member is never
// initialised, and the 8-byte copy at 0x6C8801 carries it out of the dead
// stack slot exactly as retail does.
#ifndef GG_MATCH_CORE_GAME_TIMING_METHODS_H
#define GG_MATCH_CORE_GAME_TIMING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct GameClockClass
{
    int GetTime();   // GAMEMD 0x6C8C40 __thiscall (declared; reloc)
};

struct GameTimerClass
{
    int            StartTime;   // +0x00
    GameClockClass Clock;       // +0x04

    GameTimerClass()
    {
        StartTime = Clock.GetTime();
    }
};
GG_STATIC_ASSERT(offsetof(GameTimerClass, Clock) == 0x04);
GG_STATIC_ASSERT(sizeof(GameTimerClass) == 0x08);

// GLOBAL: GAMEMD 0x00B0BD28 — the game timer (start tick at 0xB0BD28, clock
// object at 0xB0BD2C).
extern GameTimerClass GameTimer;
// GLOBAL: GAMEMD 0x00B0BD48 — elapsed ticks, stamped when the game ends.
extern int  GameElapsedTime;
// GLOBAL: GAMEMD 0x00B0BDB4 — true while the game clock is running.
extern bool GameTimerRunning;

void __fastcall Unsorted_RegisterGameStartTime();  // GAMEMD 0x6C87F0
void __fastcall Unsorted_RegisterGameEndTime();    // GAMEMD 0x6C8820

#endif  // GG_MATCH_CORE_GAME_TIMING_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and call shapes read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x683FB0: `MOV ECX,
//   0x87F7E8; CALL 0x5BDAA0` (a __thiscall on the static map object), the
//   scenario pointer `[0xA8B230]` with `LEA ESI,[EAX+0x614]` and the timer
//   run `[ESI]` (start tick, -1 when stopped), `LEA ECX,[ESI+4]; CALL
//   0x6C8C40` (the clock member's GetTime) and `[ECX+0x61C]` (accumulated
//   ticks), the log string 0x83D908 ("Resume ElapsedTimer = %l...", pushed
//   with the value into the __cdecl 0x4068E0 and popped with `ADD ESP,8`),
//   the pointer global `[0x887368]` tested and then given the byte
//   `[0xA8EB80]` through the __thiscall 0x7241A0, the __fastcall 0x407150 on
//   `[0x87E758]` with `[0x83D834]` in EDX, the store of 0x4000 back into
//   0x83D834, the __fastcall 0x5BF500 with `XOR CL,CL`, and the tail `JMP
//   0x406F40`. The timer layout (start@+0, clock@+4, base@+8) matches
//   match/core/small_misc42_methods.h and match/core/game_timing_methods.h
//   (not edited). YRpp names only:
//   ScenarioClass::ResumeGame (static), ScenarioClass::Instance @0xA8B230,
//   CCToolTip::Instance @0x887368, ToolTipManager::SetState @0x7241A0.
#ifndef GG_MATCH_CORE_SCENARIO_CLASS_RESUME_METHODS_H
#define GG_MATCH_CORE_SCENARIO_CLASS_RESUME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The clock object embedded in a timer; its GetTime ignores `this`.
struct Clock_00683FB0
{
    // FUNCTION: GAMEMD 0x6C8C40 (decl; reloc)
    int GetTime();
};

// A count-up timer: ticks accumulated while stopped plus, while running, the
// span since the start tick.
struct Timer_00683FB0
{
    int            StartTime;     // +0x00  -1 == stopped
    Clock_00683FB0 Clock;         // +0x04
    int            Accumulated;   // +0x08

    // Start the clock if it is stopped.
    void Resume()
    {
        if (this->StartTime == -1) {
            this->StartTime = this->Clock.GetTime();
        }
    }

    // Total ticks so far.
    int GetElapsed()
    {
        int total = this->Accumulated;
        if (this->StartTime != -1) {
            total += this->Clock.GetTime() - this->StartTime;
        }
        return total;
    }
};
GG_STATIC_ASSERT(offsetof(Timer_00683FB0, Clock)       == 0x4);
GG_STATIC_ASSERT(offsetof(Timer_00683FB0, Accumulated) == 0x8);
GG_STATIC_ASSERT(sizeof(Timer_00683FB0) == 0xC);

// The map singleton is a static object at 0x87F7E8.
struct Map_00683FB0
{
    // FUNCTION: GAMEMD 0x5BDAA0 (decl; reloc)
    void FUN_005BDAA0();
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_00683FB0 MapInstance;

// The tooltip manager hung off 0x887368 (YRpp: CCToolTip::Instance).
struct ToolTip_00683FB0
{
    // FUNCTION: GAMEMD 0x7241A0 (decl; reloc) — ToolTipManager::SetState.
    void SetState(bool state);
};
// GLOBAL: GAMEMD 0x887368
extern ToolTip_00683FB0* DAT_00887368;
// GLOBAL: GAMEMD 0xA8EB80 — the tooltip state restored on resume.
extern bool DAT_00A8EB80;

// The object 0x407150 is called on (see match/core/small_misc2_methods.h);
// redeclared locally so this TU stands alone.
struct Obj_0087E758
{
    int Flags;   // +0x0000

    // FUNCTION: GAMEMD 0x407150 (decl; reloc) — __fastcall: this=ECX, value=EDX.
    void __fastcall FUN_00407150(int value);
};
// GLOBAL: GAMEMD 0x87E758
extern Obj_0087E758* DAT_0087E758;
// GLOBAL: GAMEMD 0x83D834 — the level handed to 0x407150, reset to 0x4000.
extern int DAT_0083D834;

// STRING: GAMEMD 0x83D908 — "Resume ElapsedTimer = %l..." log format.
extern const char DAT_0083D908[];
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x5BF500 (decl; reloc) — __fastcall, flag in CL.
void __fastcall FUN_005BF500(bool flag);
// FUNCTION: GAMEMD 0x406F40 (decl; reloc) — no arguments, no cleanup.
void __cdecl FUN_00406F40();

struct ScenarioClass
{
    char           _pad000[0x614];   // +0x0000
    Timer_00683FB0 ElapsedTimer;     // +0x0614

    // FUNCTION: GAMEMD 0x683FB0
    static void ResumeGame();
};
GG_STATIC_ASSERT(offsetof(ScenarioClass, ElapsedTimer) == 0x614);
// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern ScenarioClass* ScenarioInstance;

#endif  // GG_MATCH_CORE_SCENARIO_CLASS_RESUME_METHODS_H

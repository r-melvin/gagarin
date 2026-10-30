// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets, globals and call shapes read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x683EB0: the __cdecl
//   0x406F00 with no arguments; `MOV ECX,[0x87E758]; CALL 0x4072B0` (a
//   __thiscall getter) whose result is stored to `[0x83D834]`; `MOV
//   ECX,[0x87E758]; MOV EDX,0x4000; CALL 0x407150` (__fastcall); the session
//   mode `[0xA8B238]` tested against 0 and 5; the scenario pointer
//   `[0xA8B230]` with `LEA ESI,[EAX+0x614]`, the timer run `[ESI]` (start
//   tick, -1 when stopped), `LEA ECX,[ESI+4]; CALL 0x6C8C40` (the clock
//   member's GetTime) and `[ESI+0x8]`/`[EAX+0x61C]` (accumulated ticks); the
//   log string 0x83D8EC ("Paused ElapsedTimer = %ld\n") pushed with the value
//   into the __cdecl 0x4068E0 and popped with `ADD ESP,8`; `MOV CL,1; CALL
//   0x5BF500` (__fastcall flag); `[0x887368]` tested then `PUSH 0; CALL
//   0x7241A0`; `MOV ECX,0x87F7E8` feeding CALL 0x6938C0, `PUSH 0; PUSH 0;
//   CALL 0x5BDC80`, `PUSH 2; CALL 0x4F42F0` and CALL 0x4F4480; and the mouse
//   singleton `[0x887640]` with `CALL [EDX+0xC]` and the tail `JMP
//   [EAX+0x10]`. The timer layout (start@+0, clock@+4, base@+8) is the one
//   already proven in match/core/scenario_class_resume_methods.h (not edited).
//   YRpp names only: ScenarioClass::PauseGame
//   (static), ScenarioClass::Instance @0xA8B230, SessionClass::Instance
//   @0xA8B238, CCToolTip::Instance @0x887368, ToolTipManager::SetState
//   @0x7241A0, WWMouseClass::Instance @0x887640, GScreenClass::Render
//   @0x4F4480. 0x4F42F0 is GScreenClass::FlagToRedraw, slot 14 of
//   GScreenClass's vtable 0x7EA6FC.
#ifndef GG_MATCH_CORE_SCENARIO_CLASS_PAUSE_METHODS_H
#define GG_MATCH_CORE_SCENARIO_CLASS_PAUSE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// The clock object embedded in a timer; its GetTime ignores `this`.
struct Clock_00683EB0
{
    // FUNCTION: GAMEMD 0x6C8C40 (decl; reloc)
    int GetTime();
};

// A count-up timer: ticks accumulated while stopped plus, while running, the
// span since the start tick.
struct Timer_00683EB0
{
    int            StartTime;     // +0x00  -1 == stopped
    Clock_00683EB0 Clock;         // +0x04
    int            Accumulated;   // +0x08

    // Total ticks so far.
    int GetElapsed()
    {
        int total = this->Accumulated;
        if (this->StartTime != -1) {
            total += this->Clock.GetTime() - this->StartTime;
        }
        return total;
    }

    // Fold the running span into the accumulator and stop the clock.
    void Pause()
    {
        if (this->StartTime != -1) {
            this->Accumulated += this->Clock.GetTime() - this->StartTime;
            this->StartTime = -1;
        }
    }
};
GG_STATIC_ASSERT(offsetof(Timer_00683EB0, Clock)       == 0x4);
GG_STATIC_ASSERT(offsetof(Timer_00683EB0, Accumulated) == 0x8);
GG_STATIC_ASSERT(sizeof(Timer_00683EB0) == 0xC);

// The map singleton is a static object at 0x87F7E8.
struct Map_00683EB0
{
    // FUNCTION: GAMEMD 0x4F42F0 (decl; reloc) — GScreenClass::FlagToRedraw.
    void FlagToRedraw(int mode);
    // FUNCTION: GAMEMD 0x4F4480 (decl; reloc) — GScreenClass::Render.
    void Render();
    // FUNCTION: GAMEMD 0x5BDC80 (decl; reloc) — MouseClass vtable slot 19, called
    // directly on the map object: (cursor, flag), returns bool, RET 8.
    bool FUN_005BDC80(int cursor, bool flag);
    // FUNCTION: GAMEMD 0x6938C0 (decl; reloc)
    void FUN_006938C0();
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_00683EB0 MapInstance;

// The tooltip manager hung off 0x887368 (YRpp: CCToolTip::Instance).
struct ToolTip_00683EB0
{
    // FUNCTION: GAMEMD 0x7241A0 (decl; reloc) — ToolTipManager::SetState.
    void SetState(bool state);
};
// GLOBAL: GAMEMD 0x887368
extern ToolTip_00683EB0* DAT_00887368;

// The object 0x4072B0 / 0x407150 are called on (see
// match/core/leaf_accessor_methods.h and match/core/small_misc2_methods.h);
// redeclared locally so this TU stands alone.
#include "triple_timer_init_methods.h"
// GLOBAL: GAMEMD 0x87E758

// GLOBAL: GAMEMD 0x83D834 — the level saved across the pause.
extern unsigned int DAT_0083D834;

// WWMouseClass (YRpp name): two zero-argument __thiscall slots, 3 and 4.
struct MouseVtbl_00683EB0;
struct Mouse_00683EB0
{
    MouseVtbl_00683EB0* Vtbl;   // +0x0000
};
typedef void (Mouse_00683EB0::*FnMouse0C_00683EB0)();
typedef void (Mouse_00683EB0::*FnMouse10_00683EB0)();
struct MouseVtbl_00683EB0
{
    char _pad00[0xC];               // +0x0000
    FnMouse0C_00683EB0 At_0C;       // +0x000C
    FnMouse10_00683EB0 At_10;       // +0x0010
};
GG_STATIC_ASSERT(offsetof(MouseVtbl_00683EB0, At_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(MouseVtbl_00683EB0, At_10) == 0x10);
// GLOBAL: GAMEMD 0x887640 — WWMouseClass::Instance.
extern Mouse_00683EB0* DAT_00887640;

// SessionClass::Instance — only the game mode word at +0 is read here.
struct Session_00683EB0
{
    int GameMode;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Session_00683EB0, GameMode) == 0x0);
// GLOBAL: GAMEMD 0xA8B238
extern Session_00683EB0 SessionInstance;

// STRING: GAMEMD 0x83D8EC — "Paused ElapsedTimer = %ld\n" log format.
extern const char DAT_0083D8EC[];
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x406F00 (decl; reloc) — no arguments, no cleanup.
void __cdecl FUN_00406F00();
// FUNCTION: GAMEMD 0x5BF500 (decl; reloc) — __fastcall, flag in CL.
void FUN_005BF500(bool flag);

#include "scenario_class.h"
// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern ScenarioClass* ScenarioInstance;

#endif  // GG_MATCH_CORE_SCENARIO_CLASS_PAUSE_METHODS_H

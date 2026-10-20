// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4C6210: the 50-byte loop `MOV AL,[ESI+EDI]` with
//   `CMP ESI,0x32`, `FILD [EDI+0x34]`, `[EDI+0x38]`, `[EDI+0x3C]`,
//   `MOV DX,[EDI+0x40]`; on the scenario object `[0xA8B230]`:
//   `FMUL qword [EAX+0x1C78]`, `[EAX+0x1C80]` (CMP -1), `[EAX+0x34AD]`
//   (byte), the 12-byte timer at `EAX+0x11E8` (its +0 compared with -1 and
//   written from `[0xA8ED84]`), `[EAX+0x35A0]` (word); on the player house
//   `[0xA83D4C]`: `ADD [EAX+0x1DC]`. Callees: `CALL 0x689670` (__thiscall on
//   the scenario, two stack args), `CALL 0x7C5F00` (__ftol), `CALL 0x4F9950`
//   (HouseClass::GiveMoney), `CALL 0x4F6EC0` (HouseClass::AssignHandicap).
//   Names from the YRpp method map (consult-only): EvadeClass::Do,
//   ScenarioClass::Instance, HouseClass::CurrentPlayer, Unsorted::CurrentFrame.
#ifndef GG_MATCH_COMBAT_EVADE_CLASS_DO_METHODS_H
#define GG_MATCH_COMBAT_EVADE_CLASS_DO_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame, the engine frame counter.
#include "../core/frame_counter.h"

// CDTimerClass — StartTime, the frame-clock functor cell, TimeLeft (0xC bytes).
// Constructing one from a duration stamps the current frame and the duration
// but leaves the functor cell untouched; Start() re-arms a stopped (-1) timer.
struct CDTimer_004C6210
{
    int StartTime;     // +0x00  -1 == stopped
    int CurrentTime;   // +0x04  (functor cell; never written here)
    int TimeLeft;      // +0x08

    CDTimer_004C6210() {}
    CDTimer_004C6210(int duration)
    {
        this->StartTime = CurrentFrame;
        this->TimeLeft  = duration;
    }

    void Start()
    {
        if (this->StartTime == -1) {
            this->StartTime = CurrentFrame;
        }
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_004C6210, TimeLeft) == 0x8);
GG_STATIC_ASSERT(sizeof(CDTimer_004C6210)             == 0xC);

// ScenarioClass — only the members Do() touches.
struct Scenario_004C6210
{
    char             _pad0000[0x11E8];             // +0x0000
    CDTimer_004C6210 Timer_11E8;                   // +0x11E8
    char             _pad11F4[0x1C78 - 0x11F4];    // +0x11F4
    double           At_1C78;                      // +0x1C78  carry-over money multiplier
    int              At_1C80;                      // +0x1C80  carry-over money cap, -1 == none
    char             _pad1C84[0x34AD - 0x1C84];    // +0x1C84
    char             At_34AD;                      // +0x34AD  (bool)
    char             _pad34AE[0x35A0 - 0x34AE];    // +0x34AE
    short            At_35A0;                      // +0x35A0

    // FUNCTION: GAMEMD 0x689670 (decl; reloc) — store one carried-over global.
    void FUN_00689670(int index, char value);
};
GG_STATIC_ASSERT(offsetof(Scenario_004C6210, Timer_11E8) == 0x11E8);
GG_STATIC_ASSERT(offsetof(Scenario_004C6210, At_1C78)    == 0x1C78);
GG_STATIC_ASSERT(offsetof(Scenario_004C6210, At_1C80)    == 0x1C80);
GG_STATIC_ASSERT(offsetof(Scenario_004C6210, At_34AD)    == 0x34AD);
GG_STATIC_ASSERT(offsetof(Scenario_004C6210, At_35A0)    == 0x35A0);

// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern Scenario_004C6210* ScenarioInstance_004C6210;

// HouseClass — only the members Do() touches.
struct House_004C6210
{
    char _pad000[0x1DC];   // +0x0000
    int  At_1DC;           // +0x01DC  running total of carried-over credits

    // FUNCTION: GAMEMD 0x4F6EC0 (decl; reloc) — HouseClass::AssignHandicap.
    void AssignHandicap(int difficulty);
    // FUNCTION: GAMEMD 0x4F9950 (decl; reloc) — HouseClass::GiveMoney.
    void GiveMoney(int amount);
};
GG_STATIC_ASSERT(offsetof(House_004C6210, At_1DC) == 0x1DC);

// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern House_004C6210* CurrentPlayer_004C6210;

// EvadeClass — the carry-over state handed from one campaign map to the next.
struct EvadeClass
{
    char  CarryOverGlobals[50];   // +0x00
    short _pad32;                 // +0x32
    int   CarryOverMoney;         // +0x34
    int   CarryOverTimer;         // +0x38
    int   CarryOverDifficulty;    // +0x3C
    short CarryOverStage;         // +0x40

    // FUNCTION: GAMEMD 0x4C6210  EvadeClass::Do (__thiscall)
    void Do();
};
GG_STATIC_ASSERT(offsetof(EvadeClass, CarryOverMoney)      == 0x34);
GG_STATIC_ASSERT(offsetof(EvadeClass, CarryOverTimer)      == 0x38);
GG_STATIC_ASSERT(offsetof(EvadeClass, CarryOverDifficulty) == 0x3C);
GG_STATIC_ASSERT(offsetof(EvadeClass, CarryOverStage)      == 0x40);

#endif  // GG_MATCH_COMBAT_EVADE_CLASS_DO_METHODS_H

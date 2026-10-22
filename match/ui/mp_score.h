// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The multiplayer score screen's data, read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI. The entry table at 0xA8D1FC has stride
//   0x70 (`LEA ESI,[EBP*8]; SUB ESI,EBP; SHL ESI,4` at 0x5C9904 and the
//   `ADD EAX,0x70` walk at 0x5C9AB9); 0x5C98A0 copies the house's UI name to
//   +0x00 (wcscpy), stores the colour scheme at +0x28, the winner count at
//   +0x2C and the first dword of each of the four 0x10-byte blocks at
//   +0x30/+0x40/+0x50/+0x60 (losses, kills, production, score; the debug trace
//   0x82FE40 labels them). The filled count is 0xA8D580, the last survivor's
//   index 0xA8D584 (all three inside the session object below). The sort table 0xABF958 holds eight entry pointers
//   (`MOV ECX,8; REP STOSD` at 0x5C9705) and is ordered by +0x60 (0x5C9AE0).
#ifndef GG_MATCH_UI_MP_SCORE_H
#define GG_MATCH_UI_MP_SCORE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ScoreEntry_00A8D1FC
{
    wchar_t Name[0x14];       // +0x00
    int     unknown_28;       // +0x28 colour scheme
    int     unknown_2C;       // +0x2C winner count
    int     unknown_30[4];    // +0x30 losses
    int     unknown_40[4];    // +0x40 kills
    int     unknown_50[4];    // +0x50 production
    int     unknown_60[4];    // +0x60 score
};
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_60) == 0x60);
GG_STATIC_ASSERT(sizeof(ScoreEntry_00A8D1FC) == 0x70);

// The session object at 0xA8B238 (its first dword is the game mode that
// 0x5C9B10 tests against 4 and 5). The score table is part of it: the eight
// entries run 0xA8D1FC..0xA8D57B (+0x1FC4), followed by the dword 0xA8D57C,
// the filled count 0xA8D580 and the survivor's index 0xA8D584. Treating them
// as one object is what keeps 0x5C98A0's store to the index after its store
// to the entry, as retail has it; separate globals let VC6 hoist it.
struct Session_00A8B238
{
    int                 unknown_0000;               // +0x0000 game mode
    char                _pad0004[0x1FC4 - 0x4];     // +0x0004
    ScoreEntry_00A8D1FC ScoreEntries[8];            // +0x1FC4 (0xA8D1FC)
    int                 unknown_2344;               // +0x2344 (0xA8D57C)
    int                 ScoreCount;                 // +0x2348 (0xA8D580)
    int                 ScoreSurvivor;              // +0x234C (0xA8D584)
};
GG_STATIC_ASSERT(offsetof(Session_00A8B238, ScoreEntries) == 0x1FC4);
GG_STATIC_ASSERT(offsetof(Session_00A8B238, ScoreCount) == 0x2348);
GG_STATIC_ASSERT(offsetof(Session_00A8B238, ScoreSurvivor) == 0x234C);
// GLOBAL: GAMEMD 0xA8B238
extern Session_00A8B238 DAT_00A8B238;

// GLOBAL: GAMEMD 0xABF958 -- the entries in score order.
extern ScoreEntry_00A8D1FC* DAT_00ABF958[8];
// GLOBAL: GAMEMD 0xABF9F4
extern int DAT_00ABF9F4;
// GLOBAL: GAMEMD 0xABF9F8
extern int DAT_00ABF9F8;

// The score screen object: a single stack byte at its call sites (0x685884,
// 0x685FCE), constructed and then run.
struct Obj_005C9700
{
    // FUNCTION: GAMEMD 0x5C9700 (declaration)
    Obj_005C9700();
    // FUNCTION: GAMEMD 0x5C9720 (declaration)
    void FUN_005C9720();
};

// FUNCTION: GAMEMD 0x5C97B0 (declaration)
void FUN_005C97B0(wchar_t* buffer, int seconds);
// FUNCTION: GAMEMD 0x5C98A0 (declaration)
void __cdecl FUN_005C98A0();
// FUNCTION: GAMEMD 0x5C9AA0 (declaration)
void __cdecl FUN_005C9AA0();
// FUNCTION: GAMEMD 0x5C9AE0 (declaration)
int __cdecl FUN_005C9AE0(const void* a, const void* b);
// FUNCTION: GAMEMD 0x5CA110 (declaration)
void* FUN_005CA110(int index);
// FUNCTION: GAMEMD 0x5C9B10 (declaration) -- the score dialog's procedure.
struct HWND__;
int __stdcall FUN_005C9B10(HWND__* dialog, unsigned int message, unsigned int wParam, long lParam);

#endif  // GG_MATCH_UI_MP_SCORE_H

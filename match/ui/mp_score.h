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

#include "../_layout/session_class.h"
#include "../_layout/score_entry_00a8d1fc.h"

// The score table is part of the session object at 0xA8B238 (SessionClass, +0x1FC4): the eight
// entries run 0xA8D1FC..0xA8D57B, followed by the dword 0xA8D57C, the filled count 0xA8D580 and
// the survivor's index 0xA8D584. Treating them as one object is what keeps 0x5C98A0's store to
// the index after its store to the entry, as retail has it; separate globals let VC6 hoist it.

// GLOBAL: GAMEMD 0xABF958 -- the entries in score order.
extern ScoreEntry_00A8D1FC* DAT_00ABF958[8];
// GLOBAL: GAMEMD 0xABF9F4
extern int DAT_00ABF9F4;
// GLOBAL: GAMEMD 0xABF9F8
extern int DAT_00ABF9F8;

// The score screen object: a single stack byte at its call sites (0x685884,
// 0x685FCE), constructed and then run.
#include "../_layout/mp_score_runner.h"

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

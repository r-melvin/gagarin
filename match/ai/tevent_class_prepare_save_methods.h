// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x71F390: `MOV EDX,[ECX+0x2C]` (the event kind, the
//   switch value), `MOV EDI,[ECX+0x34]` (the value), `MOV ESI,[ECX+0x30]`
//   (the team type, tested for null) with `ADD ESI,0x24` (its ID string),
//   and `ADD ECX,0x38` (the event's own name string). The three format
//   strings are 0x844714 "%d,%d,%s", 0x8258DC "%d,%d,%d,%s" and 0x8189B0
//   "%d,%d,%d"; the printf is the USER32 import wsprintfA at IAT 0x7E14B0
//   (`CALL [0x7E14B0]`, cdecl, `ADD ESP,0x18` / `0x14`). The name is YRpp's
//   TEventClass::PrepareSaveToINI; the layout is
//   the one match/ai/tevent_class_methods.h already pins, redefined here
//   under its own tag.
#ifndef GG_MATCH_AI_TEVENT_CLASS_PREPARE_SAVE_METHODS_H
#define GG_MATCH_AI_TEVENT_CLASS_PREPARE_SAVE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The team type referenced by a "team" parameter; only its ID string at
// +0x24 is read.
struct TeamType_0071F390
{
    char _pad000[0x24];   // +0x0000
    char ID[24];          // +0x0024
};
GG_STATIC_ASSERT(offsetof(TeamType_0071F390, ID) == 0x24);

struct TEvent_0071F390
{
    char               _pad000[0x2C];   // +0x0000
    int                EventKind;       // +0x002C
    TeamType_0071F390* TeamType;        // +0x0030
    int                Value;           // +0x0034
    char               String[25];      // +0x0038

    // FUNCTION: GAMEMD 0x71F390
    void PrepareSaveToINI(char* buffer);
};
GG_STATIC_ASSERT(offsetof(TEvent_0071F390, EventKind) == 0x2C);
GG_STATIC_ASSERT(offsetof(TEvent_0071F390, TeamType)  == 0x30);
GG_STATIC_ASSERT(offsetof(TEvent_0071F390, Value)     == 0x34);
GG_STATIC_ASSERT(offsetof(TEvent_0071F390, String)    == 0x38);

#endif  // GG_MATCH_AI_TEVENT_CLASS_PREPARE_SAVE_METHODS_H

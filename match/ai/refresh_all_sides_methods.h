// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x452D40. The four calls take 0, 2, 4 and 6 — even values only,
//   so the argument is a side/facing pair index rather than a count.
#ifndef GG_MATCH_AI_REFRESH_ALL_SIDES_METHODS_H
#define GG_MATCH_AI_REFRESH_ALL_SIDES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Owner_00452D40
{
    char _pad0000[0x16BE];    // +0x0000
    char At_16BE;             // +0x16BE
};
GG_STATIC_ASSERT(offsetof(Owner_00452D40, At_16BE) == 0x16BE);

struct Obj_00452D40
{
    char _pad0000[0x81];      // +0x0000
    char At_81;               // +0x0081
    char _pad0082[0xE];       // +0x0082
    char At_90;               // +0x0090
    char _pad0091[0x48F];     // +0x0091
    Owner_00452D40* Owner;    // +0x0520

    // FUNCTION: GAMEMD 0x452DC0
    void FUN_00452DC0(int which);
    // FUNCTION: GAMEMD 0x4533A0
    void FUN_004533A0(char flag);
};
GG_STATIC_ASSERT(offsetof(Obj_00452D40, At_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Obj_00452D40, Owner) == 0x520);

// GLOBAL: GAMEMD 0xA8EB44 — the object array.
extern Obj_00452D40** DAT_00A8EB44;
// GLOBAL: GAMEMD 0xA8EB50 — how many it holds.
extern int DAT_00A8EB50;
// GLOBAL: GAMEMD 0xA8E7AC — nonzero suppresses the whole pass.
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x452D40
void FUN_00452D40();

#endif  // GG_MATCH_AI_REFRESH_ALL_SIDES_METHODS_H

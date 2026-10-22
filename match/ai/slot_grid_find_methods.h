// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x431170. The nested loops step 4 bytes three times and 0xC
//   bytes eight times, so the object opens with an 8x3 array of pointers; the
//   guard field at +0x60 sits immediately after it (8 * 0xC = 0x60).
#ifndef GG_MATCH_AI_SLOT_GRID_FIND_METHODS_H
#define GG_MATCH_AI_SLOT_GRID_FIND_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Entry_00431170
{
    char _pad000[0xC];       // +0x0000
    unsigned char Flags;     // +0x000C  bit 1 marks it eligible
    char _pad00D[0x103];     // +0x000D
    int  Key;                // +0x0110
};
GG_STATIC_ASSERT(offsetof(Entry_00431170, Flags) == 0xC);
GG_STATIC_ASSERT(offsetof(Entry_00431170, Key) == 0x110);

struct Grid_00431170
{
    Entry_00431170* Slots[8][3];   // +0x0000
    int At_60;                     // +0x0060

    // FUNCTION: GAMEMD 0x431170
    Entry_00431170* FUN_00431170(int key);
};
GG_STATIC_ASSERT(offsetof(Grid_00431170, At_60) == 0x60);

#endif  // GG_MATCH_AI_SLOT_GRID_FIND_METHODS_H

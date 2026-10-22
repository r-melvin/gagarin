// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x50C170: the global list `MOV EBP,[0xA8022C]` with its
//   count `MOV EAX,[0xA80238]`, and the per-item name at `ADD EDI,0x15FF4`
//   (the string an inlined strcpy copies into the 20-byte frame buffer).
//   Method name from YRpp (name only).
#ifndef GG_MATCH_AI_HOUSE_CLASS_FIND_INDEX_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_FIND_INDEX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Only the name string at +0x15FF4 is touched; everything before it is
// opaque padding (the full HouseClass layout is P2 work).
struct House_0050C170
{
    char _pad000[0x15FF4];    // +0x00000
    char PlainName[21];       // +0x15FF4

    // FUNCTION: GAMEMD 0x50C170 — index of the house whose name matches.
    static int FindIndexByName(const char* name);
};
GG_STATIC_ASSERT(offsetof(House_0050C170, PlainName) == 0x15FF4);

// GLOBAL: GAMEMD 0xA8022C — HouseClass::Array.Items.
extern House_0050C170** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA80238 — HouseClass::Array.Count.
extern int DAT_00A80238;

#endif  // GG_MATCH_AI_HOUSE_CLASS_FIND_INDEX_METHODS_H

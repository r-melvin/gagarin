// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
//   Twelve-byte lobby colour record: the caption pointer at +0 and the colour value at +4 are
//   written by 0x4E43C0 (nine records from 0x8B4038); the key sits at +8 (0x8B4040 + 12 * n).
#ifndef GG_MATCH__LAYOUT_REC12_008B4038_H_H
#define GG_MATCH__LAYOUT_REC12_008B4038_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Rec12_008B4038 { const wchar_t* name; int colour; int key; };
GG_STATIC_ASSERT(offsetof(Rec12_008B4038, colour) == 0x4);
GG_STATIC_ASSERT(offsetof(Rec12_008B4038, key) == 0x8);
GG_STATIC_ASSERT(sizeof(Rec12_008B4038) == 0xC);
#endif

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
//   Twelve-byte lobby choice record: the wide caption pointer is written at +0 by 0x4E4F50
//   (nine records from 0x8B3F30), and the key at +8 by 0x4E4FC0/0x4E4F50 (0x8B3F38 + 12 * n).
#ifndef GG_MATCH__LAYOUT_REC12_008B3F30_H_H
#define GG_MATCH__LAYOUT_REC12_008B3F30_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Rec12_008B3F30 { const wchar_t* name; int unknown_04; int key; };
GG_STATIC_ASSERT(offsetof(Rec12_008B3F30, name) == 0x0);
GG_STATIC_ASSERT(offsetof(Rec12_008B3F30, key) == 0x8);
GG_STATIC_ASSERT(sizeof(Rec12_008B3F30) == 0xC);
#endif

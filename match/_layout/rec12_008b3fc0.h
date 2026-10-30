// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
//   Twelve-byte lobby choice record: the wide caption pointer is written at +0 by 0x4E5AC0
//   (five records from 0x8B3FC0); the key sits at +8 (0x8B3FC8 + 12 * n).
#ifndef GG_MATCH__LAYOUT_REC12_008B3FC0_H_H
#define GG_MATCH__LAYOUT_REC12_008B3FC0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Rec12_008B3FC0 { const wchar_t* name; int unknown_04; int key; };
GG_STATIC_ASSERT(offsetof(Rec12_008B3FC0, name) == 0x0);
GG_STATIC_ASSERT(offsetof(Rec12_008B3FC0, key) == 0x8);
GG_STATIC_ASSERT(sizeof(Rec12_008B3FC0) == 0xC);
#endif

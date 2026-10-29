// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Member offsets and
//   globals reconfirmed numerically from the disasm at each method address;
//   field names cross-checked against YRpp.
//
//   Confirmed from disasm:
//     MapClass::Bitfield       @ 0x0c (int)   -- FUN_004F42D0 [ECX+0xc]
//     MapClass::MapRect.Width  @ 0xf4 (int)   -- CoordinatesLegal [ECX+0xf4]
//     MapClass::MapRect.Height @ 0xf8 (int)   -- CoordinatesLegal [ECX+0xf8]
//   MapClass derives GScreenClass (vptr@0,ScreenShakeX@4,ScreenShakeY@8,
//   Bitfield@0xc -> sizeof 0x10); MapRect lands at 0xEC, so Width@0xF4 /
//   Height@0xF8 (RectangleStruct = {X,Y,Width,Height}).
#ifndef GG_MATCH_MAP_MAP_CLASS_MORE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CellStruct — packed cell coordinate (two signed shorts). Self-guarded so
// other map TUs can reuse it.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 0x4);

#include "../ui/input_controls/ui_display_chain.h"


#endif  // GG_MATCH_MAP_MAP_CLASS_MORE_METHODS_H

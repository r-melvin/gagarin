// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump). ToolTip.cpp is verified under the
//   default /Ob1, which turns these into jumps, so the two globals live here.
// Provenance: own-binary-via-Ghidra
//   Static initialisers at 0x723E40 and 0x723FE0, inside the ToolTip.cpp code
//   range 0x723A90-0x7250BF of retail gamemd.exe v1.001. Each is a four-word
//   global whose constructor stores zero to every word.

#include "../core/mathtbl_init_shapes.h"

// SYNTHETIC: GAMEMD 0x723E40
// GLOBAL: GAMEMD 0xB0F598
MathTblZero4 DAT_00B0F598;

// SYNTHETIC: GAMEMD 0x723FE0
// GLOBAL: GAMEMD 0xB0F5A8
MathTblZero4 DAT_00B0F5A8;

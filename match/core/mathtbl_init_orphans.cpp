// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6302f0-0x6c99c7 (disassembled from the user's gamemd.exe v1.001).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
#include "mathtbl_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x6302F0
// GLOBAL: GAMEMD 0xAC4AA0
MathTblZero4 DAT_00AC4AA0;
// SYNTHETIC: GAMEMD 0x6333D0
// GLOBAL: GAMEMD 0xAC4BE8
double DAT_00AC4BE8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x69DCD0
// GLOBAL: GAMEMD 0xB07790
MathTblZero4 DAT_00B07790;
// SYNTHETIC: GAMEMD 0x6B1B00
// GLOBAL: GAMEMD 0xB0B638
MathTblZero4 DAT_00B0B638;
// SYNTHETIC: GAMEMD 0x6B6210
// GLOBAL: GAMEMD 0xB0B7F0
MathTblZero4 DAT_00B0B7F0;
// SYNTHETIC: GAMEMD 0x6B8EE0
// GLOBAL: GAMEMD 0xB0B920
MathTblZero4 DAT_00B0B920;
// SYNTHETIC: GAMEMD 0x6B9350
// GLOBAL: GAMEMD 0xB0B938
MathTblZero4 DAT_00B0B938;
// SYNTHETIC: GAMEMD 0x6C6520
// GLOBAL: GAMEMD 0xB0BCF8
MathTblZero4 DAT_00B0BCF8;
// SYNTHETIC: GAMEMD 0x6C8990
// GLOBAL: GAMEMD 0xB0BDC0
MathTblZero4 DAT_00B0BDC0;
// SYNTHETIC: GAMEMD 0x6C99B0
// GLOBAL: GAMEMD 0xB0BFD8
MathTblZero4 DAT_00B0BFD8;

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6e6840-0x6e6a47 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7E1720
extern const double DAT_007E1720;
// GLOBAL: GAMEMD 0x7E1728
extern const double DAT_007E1728;
// GLOBAL: GAMEMD 0x7E1730
extern const double DAT_007E1730;
// GLOBAL: GAMEMD 0x7E1738
extern const double DAT_007E1738;
// GLOBAL: GAMEMD 0x7F4638
extern const double DAT_007F4638;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x6E6840
// GLOBAL: GAMEMD 0xB0E838
double DAT_00B0E838 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6E68B0
// GLOBAL: GAMEMD 0xB0E880
double DAT_00B0E880 = DAT_007E1720 * DAT_007F4638;
// SYNTHETIC: GAMEMD 0x6E68D0
// GLOBAL: GAMEMD 0xB0E858
double DAT_00B0E858 = DAT_007E1728 * DAT_007F4638;
// SYNTHETIC: GAMEMD 0x6E68F0
// GLOBAL: GAMEMD 0xB0E818
double DAT_00B0E818 = DAT_007E1730 * DAT_007F4638;
// SYNTHETIC: GAMEMD 0x6E6910
// GLOBAL: GAMEMD 0xB0E8A8
int DAT_00B0E8A8 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B0E818 - DAT_00B0E858) * DAT_00B0E838));
// SYNTHETIC: GAMEMD 0x6E6980
// GLOBAL: GAMEMD 0xB0E878
double DAT_00B0E878 = FUN_004CADE0((double)(DAT_00B0E8A8 * 2) / DAT_00B0E838);
// SYNTHETIC: GAMEMD 0x6E69B0
// GLOBAL: GAMEMD 0xB0E89C
int DAT_00B0E89C = (int)((double)(DAT_00B0E8A8 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x6E69E0
// GLOBAL: GAMEMD 0xB0E830
MathTblShortPair DAT_00B0E830;
// SYNTHETIC: GAMEMD 0x6E69F0
// GLOBAL: GAMEMD 0xB0E868
MathTblZero3 DAT_00B0E868;
// SYNTHETIC: GAMEMD 0x6E6A30
// GLOBAL: GAMEMD 0xB0E820
MathTblZero4 DAT_00B0E820;

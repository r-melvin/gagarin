// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra; access addresses and widths were confirmed
// from each complete retail entry. The original owners and function names are
// unresolved; C linkage and void results are candidate ABI bindings only.
// Address grouping does not establish an original TU or startup role.
#include "../_rt/gg_static_assert.h"
#include "mathtbl_init_shapes.h"
GG_STATIC_ASSERT(sizeof(double) == 8);
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(unsigned int) == 4);
GG_STATIC_ASSERT(sizeof(unsigned short) == 2);

// GLOBAL: GAMEMD 0x0089E220 (read as qword by 0x473570; .data)
extern "C" double DAT_0089E220;
// GLOBAL: GAMEMD 0x0089E270 (written/read as qword by 0x473570/0x473590; .data)
// GLOBAL: GAMEMD 0x0089E258 (written as qword by 0x473590; .data)
// GLOBAL: GAMEMD 0x0089E250 (written as qword by 0x4735B0; .data)
// GLOBAL: GAMEMD 0x0089E228 (written as qword by 0x4735D0; .data)
// GLOBAL: GAMEMD 0x0089E200 (written as qword by 0x4735F0; .data)

// GLOBAL: GAMEMD 0x007E4BF0 (read-only .rdata double 60.0)
extern "C" const double DAT_007E4BF0;
// GLOBAL: GAMEMD 0x007E4BF8 (read-only .rdata double 0.017453292519943295)
extern "C" const double DAT_007E4BF8;
// GLOBAL: GAMEMD 0x007E1720 (read-only .rdata double 45.0)
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1728 (read-only .rdata double 60.0)
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730 (read-only .rdata double 90.0)
extern "C" const double DAT_007E1730;

// GLOBAL: GAMEMD 0x0089E278 (written by 0x47363B; read by 0x473650/680/6B0; .data dword)
// GLOBAL: GAMEMD 0x0089E230 (written by 0x473667; .data qword)
// GLOBAL: GAMEMD 0x0089E248 (written by 0x4736A2; .data qword)
// GLOBAL: GAMEMD 0x0089E26C (written by 0x4736D0; .data dword)
// GLOBAL: GAMEMD 0x007E1738 (read-only .rdata double 0.5)
extern "C" const double DAT_007E1738;
// GLOBAL: GAMEMD 0x007E1740 (read-only .rdata double 0.00390625)
extern "C" const double DAT_007E1740;
// FUNCTION: GAMEMD 0x004CAD50 (decl; reloc; 8-byte argument, x87 result; return type is an ABI view)
extern "C" double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x004CADE0 (decl; reloc; 8-byte argument, x87 result; return type is an ABI view)
extern "C" double __cdecl FUN_004CADE0(double value);
// LIBRARY: GAMEMD 0x007C5F00 -- VC6 __ftol conversion helper.
// GLOBAL: GAMEMD 0x0089E218 (word cleared at 0x4736E2)
extern "C" unsigned short DAT_0089E218;
// GLOBAL: GAMEMD 0x0089E21A (word cleared at 0x4736E8)
extern "C" unsigned short DAT_0089E21A;
// GLOBAL: GAMEMD 0x0089E238 (dword cleared at 0x4736F2)
// GLOBAL: GAMEMD 0x0089E23C (dword cleared at 0x4736F7)
// GLOBAL: GAMEMD 0x0089E240 (dword cleared at 0x4736FC)
// GLOBAL: GAMEMD 0x0089E268 (dword set to 0 at 0x473715)
// GLOBAL: GAMEMD 0x0089E260 (dword set to 0x80 at 0x47371F)
// GLOBAL: GAMEMD 0x0089E264 (dword set to 0x80 at 0x473724)
// GLOBAL: GAMEMD 0x0089E208 (dword cleared at 0x473732)
// GLOBAL: GAMEMD 0x0089E20C (dword cleared at 0x473737)
// GLOBAL: GAMEMD 0x0089E210 (dword cleared at 0x47373C)
// GLOBAL: GAMEMD 0x0089E214 (dword cleared at 0x473741)

// SYNTHETIC: GAMEMD 0x00473570
// GLOBAL: GAMEMD 0x0089E270
double DAT_0089E270 = DAT_0089E220 / DAT_007E4BF0;

// SYNTHETIC: GAMEMD 0x00473590
// GLOBAL: GAMEMD 0x0089E258
double DAT_0089E258 = 1.0 / DAT_0089E270;

// SYNTHETIC: GAMEMD 0x004735B0
// GLOBAL: GAMEMD 0x0089E250
double DAT_0089E250 = DAT_007E1720 * DAT_007E4BF8;

// SYNTHETIC: GAMEMD 0x004735D0
// GLOBAL: GAMEMD 0x0089E228
double DAT_0089E228 = DAT_007E1728 * DAT_007E4BF8;

// SYNTHETIC: GAMEMD 0x004735F0
// GLOBAL: GAMEMD 0x0089E200
double DAT_0089E200 = DAT_007E1730 * DAT_007E4BF8;

// SYNTHETIC: GAMEMD 0x00473610
// GLOBAL: GAMEMD 0x0089E278
int DAT_0089E278 = (int)(FUN_004CAD50(DAT_0089E200 - DAT_0089E228) * DAT_007E1738 * DAT_0089E220);

// SYNTHETIC: GAMEMD 0x00473650
// GLOBAL: GAMEMD 0x0089E230
double DAT_0089E230 = FUN_004CADE0((double)DAT_0089E278 * DAT_007E1740);

// SYNTHETIC: GAMEMD 0x00473680
// GLOBAL: GAMEMD 0x0089E248
double DAT_0089E248 = FUN_004CADE0((double)(DAT_0089E278 * 2) / DAT_0089E220);

// SYNTHETIC: GAMEMD 0x004736B0
// GLOBAL: GAMEMD 0x0089E26C
int DAT_0089E26C = (int)(DAT_0089E278 * 4 + DAT_007E1738);

// FUNCTION: GAMEMD 0x004736E0
extern "C" void FUN_004736E0()
{
    DAT_0089E218 = 0;
    DAT_0089E21A = 0;
}

// SYNTHETIC: GAMEMD 0x004736F0
// GLOBAL: GAMEMD 0x0089E238
MathTblZero3 DAT_0089E238;

// SYNTHETIC: GAMEMD 0x00473710
// GLOBAL: GAMEMD 0x0089E260
MathTblCoord DAT_0089E260;

// SYNTHETIC: GAMEMD 0x00473730
// GLOBAL: GAMEMD 0x0089E208
MathTblZero4 DAT_0089E208;

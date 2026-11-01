// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
// Complete bodies are confirmed from each retail entry. The reset uses four
// absolute dword stores; the remaining routines are x87 qword loads, arithmetic
// and stores, with calls only where the retail instructions show them.
#include "periodic_state_updates_00439480.h"
#include "mathtbl_init_shapes.h"

// FUNCTION: GAMEMD 0x004CAD50 (decl; reloc)
extern "C" double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x004CADE0 (decl; reloc)
extern "C" double __cdecl FUN_004CADE0(double value);
// LIBRARY: GAMEMD 0x007C5F00 — VC6 __ftol runtime
// VC6 emits this retail x87-control-word rounding helper for __int64 conversion.

// SYNTHETIC: GAMEMD 0x00439480
// GLOBAL: GAMEMD 0x0089C708
MathTblZero4 DAT_0089C708;

// SYNTHETIC: GAMEMD 0x004394D0
// GLOBAL: GAMEMD 0x0089C770
double DAT_0089C770 = DAT_0089C720 / DAT_007E3D70;

// SYNTHETIC: GAMEMD 0x004394F0
// GLOBAL: GAMEMD 0x0089C758
double DAT_0089C758 = 1.0 / DAT_0089C770;

// SYNTHETIC: GAMEMD 0x00439510
// GLOBAL: GAMEMD 0x0089C750
double DAT_0089C750 = DAT_007E1720 * DAT_007E3D78;

// SYNTHETIC: GAMEMD 0x00439530
// GLOBAL: GAMEMD 0x0089C728
double DAT_0089C728 = DAT_007E1728 * DAT_007E3D78;

// SYNTHETIC: GAMEMD 0x00439550
// GLOBAL: GAMEMD 0x0089C700
double DAT_0089C700 = DAT_007E1730 * DAT_007E3D78;

// SYNTHETIC: GAMEMD 0x00439570
// GLOBAL: GAMEMD 0x0089C778
int DAT_0089C778 = static_cast<int>(static_cast<__int64>( FUN_004CAD50(DAT_0089C700 - DAT_0089C728) * DAT_007E1738 * DAT_0089C720));

// SYNTHETIC: GAMEMD 0x004395B0
// GLOBAL: GAMEMD 0x0089C730
double DAT_0089C730 = FUN_004CADE0( static_cast<double>(DAT_0089C778) * DAT_007E1740);

// SYNTHETIC: GAMEMD 0x004395E0
// GLOBAL: GAMEMD 0x0089C748
double DAT_0089C748 = FUN_004CADE0( static_cast<double>(DAT_0089C778 * 2) / DAT_0089C720);

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E3D70
double DAT_007E3D70 = 60.0;
// GLOBAL: GAMEMD 0x7E3D78
double DAT_007E3D78 = 0.017453292519943295;
// GLOBAL: GAMEMD 0x7E1720
double DAT_007E1720 = 45.0;
// GLOBAL: GAMEMD 0x7E1728
double DAT_007E1728 = 60.0;
// GLOBAL: GAMEMD 0x7E1730
double DAT_007E1730 = 90.0;
// GLOBAL: GAMEMD 0x7E1738
double DAT_007E1738 = 0.5;
// GLOBAL: GAMEMD 0x7E1740
double DAT_007E1740 = 0.00390625;
// END defined globals

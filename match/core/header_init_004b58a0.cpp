// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x4B58D0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E8240
const double DAT_007E8240 = 60.0;
// GLOBAL: GAMEMD 0x7E8248 -- degrees to radians
const double DAT_007E8248 = 0.017453292519943295;

// GLOBAL: GAMEMD 0x8A07E8
extern double DAT_008A07E8;
// GLOBAL: GAMEMD 0x8A0810
extern double DAT_008A0810;
// GLOBAL: GAMEMD 0x8A0808
extern double DAT_008A0808;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4B5970
// GLOBAL: GAMEMD 0x8A0860
int DAT_008A0860 = (int)(FUN_004CAD50(DAT_008A07E8 - DAT_008A0810) * DAT_008A0808 * 0.5);
// SYNTHETIC: GAMEMD 0x4B5A10
// GLOBAL: GAMEMD 0x8A0854
int DAT_008A0854 = (int)(DAT_008A0860 * 4 + 0.5);

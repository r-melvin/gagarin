// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x40A900. Not bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC29_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC29_METHODS_H

// GLOBAL: GAMEMD 0x816380 — a 101-entry table indexed by percentage.
extern int DAT_00816380[101];

// FUNCTION: GAMEMD 0x40A900 — convert a 0..256 fraction to a percentage and
// look it up. The multiply by 100 is done with two LEAs and a shift
// (x*5*5*4), and the divide by 256 uses the signed-shift idiom
// `CDQ; AND EDX,0xFF; ADD; SAR 8` rather than a bare shift.
int __fastcall FUN_0040A900(int value);

#endif  // GG_MATCH_CORE_SMALL_MISC29_METHODS_H

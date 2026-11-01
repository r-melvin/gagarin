// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Declarations of the table-driven trigonometry and square-root helpers at 0x4CAC40-0x4CAE30, as
//   their callers see them. Every matched caller was compiled against a double result in ST0: with
//   a float declaration the callers' register allocation changes and they no longer match. The
//   definitions in trig_table_functions_004cac40.cpp store the result through a float and also
//   match, so the callee bytes cannot tell the two apart; this header therefore follows the callers
//   and is not included by that file.
#ifndef GG_MATCH_TRIG_TABLE_FUNCTIONS_004CAC40_H
#define GG_MATCH_TRIG_TABLE_FUNCTIONS_004CAC40_H

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- square root, __cdecl.
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- table lookup, __cdecl.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- odd arc table, __cdecl.
double __cdecl FUN_004CADE0(double value);
// FUNCTION: GAMEMD 0x4CAE30 (decl; reloc) -- two-argument arc, __cdecl.
double __cdecl FUN_004CAE30(double y, double x);

#endif  // GG_MATCH_TRIG_TABLE_FUNCTIONS_004CAC40_H

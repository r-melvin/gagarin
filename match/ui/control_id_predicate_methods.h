// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 at 0x601360 and
//   0x602AE0. In both the identifier arrives in ECX and there is no stack
//   cleanup at the call sites (0x60261D, 0x60699B, 0x60BB50 for the second), so
//   both are __fastcall.
//
//   The two differ in return width, and the exit instruction is the only place
//   that says so: 0x602AE0 ends `MOV EAX,1` / `XOR EAX,EAX`, a full-dword
//   result, while 0x601360 ends `MOV AL,1` / `XOR AL,AL`, a one-byte bool.
//
//   The body is a flat chain of `CMP ECX,imm32; JZ` in source order, with no
//   jump table and no binary search, so the source is a single disjunction of
//   equality tests rather than a switch. The eighteen accepted identifiers, in
//   retail's own order, are the constant list below.
//
//   Nothing in the body touches audio state; the placeholder name is kept.
#ifndef GG_MATCH_UI_CONTROL_ID_PREDICATE_METHODS_H
#define GG_MATCH_UI_CONTROL_ID_PREDICATE_METHODS_H

// FUNCTION: GAMEMD 0x601360 (__fastcall)
bool __fastcall FUN_00601360(int nID);

// FUNCTION: GAMEMD 0x602AE0 (__fastcall)
int __fastcall FUN_00602AE0(int nID);

#endif  // GG_MATCH_UI_CONTROL_ID_PREDICATE_METHODS_H

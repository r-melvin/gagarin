// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Slots, argument slots and constants read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x5F3DB0: the
//   `[EAX+0x48]` slot on both the target and `this` (each handed a 12-byte
//   stack buffer), the X/Y reads at +0x0/+0x4 of the returned pointers, the
//   doubles at 0x7E2820 (1.5707963267948966) and 0x7E2818
//   (-10430.060040584269) via `ghidra memory read`, and the dword copy out
//   through the first stack argument. YRpp names the function
//   (AbstractClass::GetTargetDirection) and slot 18 (GetCoords) - name-only
//   cross-check. The AbstractClass base layout is match/_layout/abstract_class.h.
#ifndef GG_MATCH_CORE_ABSTRACT_CLASS_TARGET_DIRECTION_METHODS_H
#define GG_MATCH_CORE_ABSTRACT_CLASS_TARGET_DIRECTION_METHODS_H

// FUNCTION: GAMEMD 0x4CAE30 (decl; reloc) — two-argument arctangent, __cdecl.
double __cdecl FUN_004CAE30(double y, double x);

#endif  // GG_MATCH_CORE_ABSTRACT_CLASS_TARGET_DIRECTION_METHODS_H

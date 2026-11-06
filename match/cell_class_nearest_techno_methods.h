// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x47C3D0: the two occupier list heads `[ECX+0xE4]` /
//   `[ECX+0xE8]` (FirstObject / AltObject), the list link `[ESI+0x30]`
//   (ObjectClass::NextObject), the AbstractClass flag byte `[ESI+0x14]` bit 0
//   (techno), the hidden-pointer GetCoords slot `[EDX+0x48]`, sqrt via
//   0x4CAC40 and __ftol 0x7C5F00. The method name is YRpp's
//   CellClass::FindTechnoNearestTo (name only; every offset re-derived here).
#ifndef GG_MATCH_MAP_CELL_CLASS_NEAREST_TECHNO_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_NEAREST_TECHNO_METHODS_H

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) — square root, __cdecl.
double __cdecl FUN_004CAC40(double value);

#endif  // GG_MATCH_MAP_CELL_CLASS_NEAREST_TECHNO_METHODS_H

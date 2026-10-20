// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x412A40. The grid stride is 0x14 (the IDIV divisor and the
//   `LEA EAX,[EAX+EAX*4]` / `LEA EAX,[ECX+EAX*4]` pair that multiplies by 20),
//   and both clamps are signed against 0 and 0x13.
#ifndef GG_MATCH_MAP_GRID_OFFSET_METHODS_H
#define GG_MATCH_MAP_GRID_OFFSET_METHODS_H

// FUNCTION: GAMEMD 0x412A40
int __stdcall FUN_00412A40(int cell, int dx, int dy);

#endif  // GG_MATCH_MAP_GRID_OFFSET_METHODS_H

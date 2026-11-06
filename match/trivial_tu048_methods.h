// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU048_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU048_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x89E414
extern unsigned int DAT_0089E414;

// FUNCTION: GAMEMD 0x4A80D0 (declaration)
int __fastcall CD_GetCDNumber(int drive, int timeout);

// FUNCTION: GAMEMD 0x4790A0 (declaration)
int __fastcall FUN_004790A0(int timeout);

#endif  // GG_MATCH_CORE_TRIVIAL_TU048_METHODS_H

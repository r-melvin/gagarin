// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Both distinct 4-byte cells lie in the pinned PE .data loader-zero tail.
// These definitions bind initial storage, not later runtime contents or owner.
#include "../_layout/ini_index_defaults.h"
GG_STATIC_ASSERT(sizeof(INIClass::INISection*) == 4);
GG_STATIC_ASSERT(sizeof(INIClass::INIEntry*) == 4);
// GLOBAL: GAMEMD 0xB7882C
INIClass::INISection* DAT_00B7882C;
// GLOBAL: GAMEMD 0xB78830
INIClass::INIEntry* DAT_00B78830;

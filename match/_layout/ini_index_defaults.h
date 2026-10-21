// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// FetchIndex 0x52B210 returns the address of entry default 0xB78830;
// FetchIndex 0x52B430 returns section default 0xB7882C. Callers dereference
// these cells as the corresponding nested-node pointers. Template ownership
// and original member names are not established by this data flow.
#ifndef GG_MATCH_LAYOUT_INI_INDEX_DEFAULTS_H
#define GG_MATCH_LAYOUT_INI_INDEX_DEFAULTS_H
#include "ini_class.h"
// GLOBAL: GAMEMD 0xB7882C
extern INIClass::INISection* DAT_00B7882C;
// GLOBAL: GAMEMD 0xB78830
extern INIClass::INIEntry* DAT_00B78830;
#endif

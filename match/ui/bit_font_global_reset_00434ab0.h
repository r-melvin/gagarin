// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The complete 0x434AB0 entry writes zero to four consecutive dword globals
//   at 0x89C4C0, 0x89C4C4, 0x89C4C8, and 0x89C4CC. Ghidra's xrefs show only
//   these writes; no names or narrower semantics are inferred.
#ifndef GG_MATCH_UI_BIT_FONT_GLOBAL_RESET_00434AB0_H
#define GG_MATCH_UI_BIT_FONT_GLOBAL_RESET_00434AB0_H

// GLOBAL: GAMEMD 0x0089C4C0
extern unsigned int DAT_0089C4C0;
// GLOBAL: GAMEMD 0x0089C4C4
extern unsigned int DAT_0089C4C4;
// GLOBAL: GAMEMD 0x0089C4C8
extern unsigned int DAT_0089C4C8;
// GLOBAL: GAMEMD 0x0089C4CC
extern unsigned int DAT_0089C4CC;

// FUNCTION: GAMEMD 0x434AB0
void __stdcall FUN_00434AB0();

#endif  // GG_MATCH_UI_BIT_FONT_GLOBAL_RESET_00434AB0_H

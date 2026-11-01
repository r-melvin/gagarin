// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Palette, shape and screen-resource globals in the 0xB0F000 data block.
#ifndef GG_MATCH_PALETTE_SCREEN_GLOBALS_H
#define GG_MATCH_PALETTE_SCREEN_GLOBALS_H

struct WholeFileBlock;


struct SidebarShapeFile;


// GLOBAL: GAMEMD 0xB0FBE0
extern char DAT_00B0FBE0;
// GLOBAL: GAMEMD 0xB0FC0C
extern char DAT_00B0FC0C;
// GLOBAL: GAMEMD 0xB0FA90 -- the shape both buttons display.
extern SidebarShapeFile* DAT_00B0FA90;
// GLOBAL: GAMEMD 0xB0FB00
extern WholeFileBlock* DAT_00B0FB00;
// GLOBAL: GAMEMD 0x00B0FE58
extern unsigned char DAT_00B0FE58;
// GLOBAL: GAMEMD 0xB0FE65
extern bool IsTypeSelectingFlag;

#endif  // GG_MATCH_PALETTE_SCREEN_GLOBALS_H

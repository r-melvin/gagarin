// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Cell and coordinate constants the math-table initialisers define.
#ifndef GG_MATCH_CELL_COORD_GLOBALS_H
#define GG_MATCH_CELL_COORD_GLOBALS_H

struct SidebarShapeFile;


struct MathTblShortPair;


// GLOBAL: GAMEMD 0xB0E700
extern MathTblShortPair DAT_00B0E700;
// GLOBAL: GAMEMD 0x00B0E9C8
extern MathTblShortPair DefaultWaypointCell;
// GLOBAL: GAMEMD 0xB04BEC
extern bool IsReadingAudioFile;
// GLOBAL: GAMEMD 0xB0B518
extern unsigned char DAT_00B0B518;
// GLOBAL: GAMEMD 0xB0C000
extern MathTblShortPair DAT_00B0C000;
// GLOBAL: GAMEMD 0xB0C148
extern SidebarShapeFile* CommandShapes_00B0C148[25];
// GLOBAL: GAMEMD 0xB0CB78
extern int ButtonIndexTable[25];
// GLOBAL: GAMEMD 0xB0CBDC
extern bool CommandShapeOwned_00B0CBDC[25];
// GLOBAL: GAMEMD 0xB0CC20
extern int DAT_00B0CC20;
// GLOBAL: GAMEMD 0xB0CC28
extern int DAT_00B0CC28;
// GLOBAL: GAMEMD 0xB0CD28
extern int DAT_00B0CD28;

#endif  // GG_MATCH_CELL_COORD_GLOBALS_H

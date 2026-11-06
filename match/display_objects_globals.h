// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Type arrays, coordinates, fonts and the beacon manager in the 0x887400 data block.
#ifndef GG_MATCH_DISPLAY_OBJECTS_GLOBALS_H
#define GG_MATCH_DISPLAY_OBJECTS_GLOBALS_H

class ApplicationClass;




struct CoordStruct;
struct CellStruct;


// GLOBAL: GAMEMD 0x887680 -- the coordinate slot 18 returns.
extern CoordStruct DAT_00887680;
// GLOBAL: GAMEMD 0x887850
extern CellStruct DAT_00887850;
// GLOBAL: GAMEMD 0x89A29C
extern ApplicationClass HouseMainObject;
// GLOBAL: GAMEMD 0x89DDB8
extern int TypesLevelHeight;
// GLOBAL: GAMEMD 0x89E000
extern char DAT_0089E000[8];
// GLOBAL: GAMEMD 0x89E3A0
extern char DAT_0089E3A0;
// GLOBAL: GAMEMD 0x89F978 -- selects the cooperative-level flags.
extern bool DAT_0089F978;

#endif  // GG_MATCH_DISPLAY_OBJECTS_GLOBALS_H

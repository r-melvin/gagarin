// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Miscellaneous runtime globals in the 0xA90000 data block (debug window, overlay and loco statics, hash tables).
#ifndef GG_MATCH_RUNTIME_MISC_GLOBALS_H
#define GG_MATCH_RUNTIME_MISC_GLOBALS_H

struct Owner_00626C60;


class CellOffset;


struct MapObjCell;


// GLOBAL: GAMEMD 0xA9F9F8
struct CellStruct;
extern CellStruct DAT_00A9F9F8;
// GLOBAL: GAMEMD 0xAA0374
extern int DebugWindowListCapacity;
// GLOBAL: GAMEMD 0xAA0448
extern int DebugWindowListActive;
// GLOBAL: GAMEMD 0xAA06D0 - the cell value meaning "no placement" for the constructor.
extern MapObjCell DAT_00AA06D0;
// GLOBAL: GAMEMD 0xABF239
extern bool DAT_00ABF239;
// GLOBAL: GAMEMD 0xAC13C8
extern int FlightLevel;
// GLOBAL: GAMEMD 0xA9FAB4
extern unsigned char DAT_00A9FAB4;
// GLOBAL: GAMEMD 0xAA0738
extern int DAT_00AA0738;
// GLOBAL: GAMEMD 0xABCD58
extern unsigned char DAT_00ABCD58;
// GLOBAL: GAMEMD 0xABD490
extern CellOffset DAT_00ABD490[369];
// GLOBAL: GAMEMD 0xABEF44
extern int GG_BridgeRise;
// GLOBAL: GAMEMD 0xABEF50
extern int GG_LevelHeight;
// GLOBAL: GAMEMD 0xABF23A
extern bool DAT_00ABF23A;
// GLOBAL: GAMEMD 0xABF394
extern char** DAT_00ABF394;
// GLOBAL: GAMEMD 0xABF3A0
extern int DAT_00ABF3A0;
// GLOBAL: GAMEMD 0xAC48F0 — the palette-table owner.
extern Owner_00626C60* DAT_00AC48F0;
// GLOBAL: GAMEMD 0xAC4CF4
extern bool DAT_00AC4CF4;

#endif  // GG_MATCH_RUNTIME_MISC_GLOBALS_H

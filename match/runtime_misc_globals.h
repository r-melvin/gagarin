// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Miscellaneous runtime globals in the 0xA90000 data block (debug window, overlay and loco statics, hash tables).
#ifndef GG_MATCH_RUNTIME_MISC_GLOBALS_H
#define GG_MATCH_RUNTIME_MISC_GLOBALS_H

struct MapObjCell;


// GLOBAL: GAMEMD 0xA9F9F8
extern int DAT_00A9F9F8;
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

#endif  // GG_MATCH_RUNTIME_MISC_GLOBALS_H

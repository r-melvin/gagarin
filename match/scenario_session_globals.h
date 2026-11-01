// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Scenario, session and multiplayer-lobby globals in the 0xA8B000 data block.
#ifndef GG_MATCH_SCENARIO_SESSION_GLOBALS_H
#define GG_MATCH_SCENARIO_SESSION_GLOBALS_H

class IPXAddressClass;


// GLOBAL: GAMEMD 0xA8B258
extern char DAT_00A8B258;
// GLOBAL: GAMEMD 0xA8B262
extern unsigned char DAT_00A8B262;
// GLOBAL: GAMEMD 0xA8B263
extern unsigned char DAT_00A8B263;
// GLOBAL: GAMEMD 0xA8BB0C
extern int SessionPlayerLimit;
// GLOBAL: GAMEMD 0xA8DA8C
extern int SelectedSlotIndex;
// GLOBAL: GAMEMD 0xA8E378
extern bool MenusLoadFlagB;
// GLOBAL: GAMEMD 0xA8EB7C
extern unsigned char MouseDrawFlag;
// GLOBAL: GAMEMD 0xA8EB84
extern int DAT_00A8EB84;
// GLOBAL: GAMEMD 0xA8EB88
extern int DAT_00A8EB88;
// GLOBAL: GAMEMD 0xA8EC74
extern bool DAT_00A8EC74;
// GLOBAL: GAMEMD 0xA8ED9C
extern bool DAT_00A8ED9C;
// GLOBAL: GAMEMD 0xA8B27C
extern int DAT_00A8B27C[8];
// GLOBAL: GAMEMD 0xA8B394
extern int PlayerColor;
// GLOBAL: GAMEMD 0xA8B538
extern int DAT_00A8B538;
// GLOBAL: GAMEMD 0xA8BB1C
extern IPXAddressClass DAT_00A8BB1C;
// GLOBAL: GAMEMD 0xA8D60E
extern unsigned char InhibitFlag;
// GLOBAL: GAMEMD 0xA8E340
extern int HouseSuperTypeCount;
// GLOBAL: GAMEMD 0xA8EC88
extern int DAT_00A8EC88;
// GLOBAL: GAMEMD 0xA8ED5D
extern unsigned char DAT_00A8ED5D;
// GLOBAL: GAMEMD 0xA8ED9D
extern bool DAT_00A8ED9D;
// GLOBAL: GAMEMD 0xA8F7D8
extern bool DAT_00A8F7D8;

#endif  // GG_MATCH_SCENARIO_SESSION_GLOBALS_H

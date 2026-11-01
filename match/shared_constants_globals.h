// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read-only constants, string literals and small tables that several retail translation units share.
#ifndef GG_MATCH_SHARED_CONSTANTS_GLOBALS_H
#define GG_MATCH_SHARED_CONSTANTS_GLOBALS_H

struct Guid_006805F0;


// GLOBAL: GAMEMD 0x81834C
extern const char TypesShpExtension[];
// GLOBAL: GAMEMD 0x829FF4
extern int MinFrameRate;
// GLOBAL: GAMEMD 0x829FF8
extern int BufferZoneWidth;
// GLOBAL: GAMEMD 0x8370BC
extern const char* const ParticleBehavesLikeNames[5];
// GLOBAL: GAMEMD 0xABFBB0
extern char DAT_007E1668;
// GLOBAL: GAMEMD 0x007E1B60 (five string pointers)
extern const char* const DAT_007E1B60[5];
// STRING: GAMEMD 0x7E2198
extern char DAT_007E2198[];
// GLOBAL: GAMEMD 0x7E2800
extern const double GG_ZERO;
// GLOBAL: GAMEMD 0x7E2818
extern const double GG_RADIANS_TO_DIR16;
// GLOBAL: GAMEMD 0x7E2820
extern const double GG_QUARTER_TURN;
// STRING: GAMEMD 0x7E38D0
extern char DAT_007E38D0[];
// STRING: GAMEMD 0x7E38F0
extern char DAT_007E38F0[];
// GLOBAL: GAMEMD 0x7E4408
extern const double gg_locomotion_facing_step;
// GLOBAL: GAMEMD 0x007E5210 (eleven string pointers)
extern const char* const DAT_007E5210[11];
// GLOBAL: GAMEMD 0x007E523C (nineteen string pointers)
extern const char* const DAT_007E523C[19];
// GLOBAL: GAMEMD 0x7E61E0
extern char DAT_007E61E0;
// GLOBAL: GAMEMD 0x7E61F0
extern char DAT_007E61F0;
// GLOBAL: GAMEMD 0x7F7C80
extern const Guid_006805F0 IID_IPersistStream_007F7C80;
// GLOBAL: GAMEMD 0x816380 — the volume curve.
extern int DAT_00816380[];
// GLOBAL: GAMEMD 0x817F64
extern const char STR_00817F64[];
// STRING: GAMEMD 0x819088
extern const unsigned char DAT_00819088[16];
// GLOBAL: GAMEMD 0x81BA88
extern const char* DAT_0081BA88[13];
// GLOBAL: GAMEMD 0x81DA28
extern const char* const LandTypeName[12];
// GLOBAL: GAMEMD 0x81DA58
extern const char* const DAT_0081DA58[8];
// GLOBAL: GAMEMD 0x8316A8
extern const unsigned long DAT_008316A8[8];
// GLOBAL: GAMEMD 0x8469F4
extern const int DAT_008469F4[5];
// GLOBAL: GAMEMD 0x8497A4
extern const char STR_008497A4[];

#endif  // GG_MATCH_SHARED_CONSTANTS_GLOBALS_H

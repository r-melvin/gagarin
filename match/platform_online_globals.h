// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Window handles and online-lobby lists in the 0xB30000 data block.
#ifndef GG_MATCH_PLATFORM_ONLINE_GLOBALS_H
#define GG_MATCH_PLATFORM_ONLINE_GLOBALS_H
#include "wdt_rc_ptr_base.h"

struct Vec_00B77900;


struct Vec_00B778D8;


struct Vec_00B76AE0;


struct Matrix3D;


struct QuaternionEntry;


class WDTState;


// GLOBAL: GAMEMD 0xB77F58
extern rc_ptr<WDTState> DAT_00B77F58;
// GLOBAL: GAMEMD 0xB43188
extern QuaternionEntry DAT_00B43188[21];
// GLOBAL: GAMEMD 0xB44348
extern QuaternionEntry DAT_00B44348[21];
// GLOBAL: GAMEMD 0x00B45188 (48-byte records)
extern Matrix3D DAT_00B45188[];
// GLOBAL: GAMEMD 0xB45990
extern unsigned char DAT_00B45990[256];
// GLOBAL: GAMEMD 0xB7355C
extern int DAT_00B7355C;
// GLOBAL: GAMEMD 0x00B76AE0
extern Vec_00B76AE0 DAT_00B76AE0;
// GLOBAL: GAMEMD 0x00B778D8
extern Vec_00B778D8 DAT_00B778D8;
// GLOBAL: GAMEMD 0x00B77900
extern Vec_00B77900 DAT_00B77900;

#endif  // GG_MATCH_PLATFORM_ONLINE_GLOBALS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x465CC0. The INI read's five pushed arguments and the 0x3C
//   buffer size give the call shape; the string at 0x81AEF0 is "ToTile", which
//   names what the loop resolves.
#ifndef GG_MATCH_MAP_TILE_LINK_RESOLVE_METHODS_H
#define GG_MATCH_MAP_TILE_LINK_RESOLVE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Entry_00465CC0
{
    char _pad000[0x24];       // +0x0000
    char Name[0x20];          // +0x0024  the INI section this entry reads from
    char _pad044[0xE14];      // +0x0044
    int  ToTile;              // +0x0E58
};
GG_STATIC_ASSERT(offsetof(Entry_00465CC0, Name) == 0x24);
GG_STATIC_ASSERT(offsetof(Entry_00465CC0, ToTile) == 0xE58);

struct Ini_00465CC0
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x528A10 — read a string value, or the default.
    int ReadString(const char* section, const char* key, const char* fallback,
                   char* buffer, int size);
};
// GLOBAL: GAMEMD 0x887048 — the INI being read.
extern Ini_00465CC0* DAT_00887048;

// GLOBAL: GAMEMD 0xA83C6C — the entry array.
extern Entry_00465CC0** DAT_00A83C6C;
// GLOBAL: GAMEMD 0xA83C78 — how many entries it holds.
extern int DAT_00A83C78;
// GLOBAL: GAMEMD 0xA8ED2C — the tile table.
extern int* DAT_00A8ED2C;
// GLOBAL: GAMEMD 0xA8ED38 — how many tiles it holds.
extern int DAT_00A8ED38;

// FUNCTION: GAMEMD 0x544CE0 — resolve a tile name to its index, or negative.
int __fastcall FUN_00544CE0(const char* name);

// FUNCTION: GAMEMD 0x465CC0
void FUN_00465CC0();

#endif  // GG_MATCH_MAP_TILE_LINK_RESOLVE_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x56D460: `[ECX+0xF4]` / `[ECX+0xF8]` summed with 1
//   (`LEA EAX,[EAX+EDX+1]`) as the zone-grid row stride, `[ECX+0x6C]` (the
//   zone count the index is clamped against), `[ECX+0x68]` with `LEA
//   EBP,[EDX+EAX*4]` (the 4-byte zone records: type byte at +0, id word at
//   +2) and `[ECX+0x18]` indexed by that id as a word array. The eight
//   neighbour offsets are built from the globals `[0x87F8DC]` and
//   `[0x87F8E0]` (again summed with 1), and the fallback recalculation is
//   invoked on the fixed instance `MOV ECX,0x87F7E8`. MapClass::ResetZones
//   is YRpp's name (consult-only, no LICENSE) and matches the declaration
//   already carried by match/map/veinhole_monster_recalculate_methods.h;
//   every offset is reconfirmed here.
#ifndef GG_MATCH_MAP_MAP_CLASS_RESET_ZONES_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_RESET_ZONES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Cell_0056D460 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(Cell_0056D460) == 4);

// One zone-grid record (4 bytes).
struct Zone_0056D460
{
    char           Type;        // +0x00  7 = impassable, 0 = unassigned
    char           unknown_01;  // +0x01
    unsigned short Id;          // +0x02
};
GG_STATIC_ASSERT(offsetof(Zone_0056D460, Id) == 0x2);
GG_STATIC_ASSERT(sizeof(Zone_0056D460)       == 4);

// GLOBAL: GAMEMD 0x87F8DC / 0x87F8E0 -- the two map extents the neighbour
// stride is built from.
extern int DAT_0087F8DC;
extern int DAT_0087F8E0;

struct Map_0056D460
{
    char           _pad0000[0x18];             // +0x0000
    short*         ZoneConnections;            // +0x0018
    char           _pad001C[0x68 - 0x1C];      // +0x001C
    Zone_0056D460* Zones;                      // +0x0068
    int            ZoneCount;                  // +0x006C
    char           _pad0070[0xF4 - 0x70];      // +0x0070
    int            unknown_F4;                 // +0x00F4
    int            unknown_F8;                 // +0x00F8

    // FUNCTION: GAMEMD 0x56C510 (decl; reloc) -- the full zone recalculation.
    void FUN_0056C510();

    // FUNCTION: GAMEMD 0x56D460 -- MapClass::ResetZones.
    void ResetZones(const Cell_0056D460& cell);
};
GG_STATIC_ASSERT(offsetof(Map_0056D460, ZoneConnections) == 0x18);
GG_STATIC_ASSERT(offsetof(Map_0056D460, Zones)           == 0x68);
GG_STATIC_ASSERT(offsetof(Map_0056D460, ZoneCount)       == 0x6C);
GG_STATIC_ASSERT(offsetof(Map_0056D460, unknown_F4)      == 0xF4);
GG_STATIC_ASSERT(offsetof(Map_0056D460, unknown_F8)      == 0xF8);

// GLOBAL: GAMEMD 0x87F7E8 -- MapClass::Instance (used by address, ECX).
extern Map_0056D460 DAT_0087F7E8;

#endif  // GG_MATCH_MAP_MAP_CLASS_RESET_ZONES_METHODS_H

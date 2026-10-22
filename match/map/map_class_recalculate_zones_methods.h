// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x56D5A0:
//     MapClass  [ECX+0x18] the zone-remap table (word-indexed:
//               `MOV BP,word ptr [EDX+EAX*2]`), [ECX+0x68] the zone array base
//               and [ECX+0x6C] its entry count (`LEA ESI,[EDX+EAX*4]` — four
//               bytes per entry), [ECX+0xF4] and [ECX+0xF8] the two map
//               dimensions summed with 1 for the row stride
//               (`LEA EAX,[EAX+EDX+1]`).
//     the zone entry  byte Type at +0 (`MOV DL,byte ptr [ESI]`, compared to 7)
//               and unsigned short Index at +2 (`MOV AX,word ptr
//               [ESI+ECX*4+2]`, `MOV word ptr [ESI+2],AX`).
//     the argument arrives by address (`MOV EDX,[ESP+0x2C]`, then
//               `MOVSX ESI,word ptr [EDX+2]` / `MOVSX EDX,word ptr [EDX]`;
//               RET 0x4), so it is a CellStruct reference: X at +0, Y at +2.
//     globals   0x87F8DC and 0x87F8E0 summed with 1 give the neighbour stride
//               (`MOV EDI,[0x87F8E0]; MOV EAX,[0x87F8DC]; LEA EAX,[EDI+EAX+1]`)
//               and 0x87F7E8 is MapClass::Instance, the receiver of the
//               0x56C510 fallback (`MOV ECX,0x87F7E8`).
//   0x87F7E8 as an object (not a pointer) agrees with
//   match/economy/house_class_flag_coords_methods.h (not edited). Names
//   cross-checked against YRpp (every
//   offset reconfirmed above).
#ifndef GG_MATCH_MAP_MAP_CLASS_RECALCULATE_ZONES_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_RECALCULATE_ZONES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellStruct_0056D5A0
{
    short X;                  // +0x0000
    short Y;                  // +0x0002
};
GG_STATIC_ASSERT(sizeof(CellStruct_0056D5A0) == 4);

// One entry of the zone array at MapClass +0x68.
struct Zone_0056D5A0
{
    unsigned char  Type;      // +0x0000  7 marks an impassable/unset entry
    char           _pad001;   // +0x0001
    unsigned short Index;     // +0x0002
};
GG_STATIC_ASSERT(offsetof(Zone_0056D5A0, Index) == 0x2);
GG_STATIC_ASSERT(sizeof(Zone_0056D5A0) == 4);

// GLOBAL: GAMEMD 0x87F8DC — the first neighbour-stride term.
extern int DAT_0087F8DC;
// GLOBAL: GAMEMD 0x87F8E0 — the second neighbour-stride term.
extern int DAT_0087F8E0;

struct Map_0056D5A0
{
    char           _pad000[0x18];       // +0x0000
    short*         ZoneRemap;           // +0x0018
    char           _pad01C[0x68 - 0x1C];
    Zone_0056D5A0* Zones;               // +0x0068
    int            ZoneCount;           // +0x006C
    char           _pad070[0xF4 - 0x70];
    int            At_F4;               // +0x00F4
    int            At_F8;               // +0x00F8

    // FUNCTION: GAMEMD 0x56C510 (decl; reloc) — the full zone rebuild.
    unsigned int FUN_0056C510();

    // FUNCTION: GAMEMD 0x56D5A0
    void RecalculateZones(CellStruct_0056D5A0& cell);
};
GG_STATIC_ASSERT(offsetof(Map_0056D5A0, ZoneRemap) == 0x18);
GG_STATIC_ASSERT(offsetof(Map_0056D5A0, Zones) == 0x68);
GG_STATIC_ASSERT(offsetof(Map_0056D5A0, ZoneCount) == 0x6C);
GG_STATIC_ASSERT(offsetof(Map_0056D5A0, At_F4) == 0xF4);
GG_STATIC_ASSERT(offsetof(Map_0056D5A0, At_F8) == 0xF8);

// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer).
extern Map_0056D5A0 DAT_0087F7E8;

#endif  // GG_MATCH_MAP_MAP_CLASS_RECALCULATE_ZONES_METHODS_H

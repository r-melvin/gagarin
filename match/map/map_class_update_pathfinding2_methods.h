// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every offset read numerically off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x586990:
//     * the parameter is a DynamicVectorClass<CellStruct>*: `[EBX+0x10]` is
//       the count (`MOV EBP,[EBX+0x10]; DEC EBP; JS`) and `[EBX+4]` the item
//       base (`MOV EAX,[EBX+4]; ADD EAX,EDI` with `LEA EDI,[EBP*4]`).
//     * `[ESI+0xF8]` + `[ESI+0xF4]` + 1 is the zone-row stride
//       (`LEA EAX,[EDX+EAX*1+1]`), `[ESI+0x6C]` the clamp bound
//       (`LEA EAX,[ECX-1]`) and `[ESI+0x70]` a 10-byte-stride array
//       (`LEA EDX,[EAX+EAX*4]; MOV word ptr [EAX+EDX*2],0`) whose first word
//       is the field written/tested.
//     * the flat cell index is `Y*512 + X` (`SHL ECX,9; ADD ECX,EDX`) bounds
//       checked against 0.. 0x40000 and read from `[0x87F924]`, with the
//       miss stamping the packed coord into `[0xABDC74]` (InvalidCell at
//       0xABDC50, MapCoords @ +0x24) — the same fallback shape already
//       confirmed in match/map/map_class_location_shrouded_methods.h.
//   0x578460 is MapClass::IsWithinUsableArea(CellStruct const&, bool), already
//   matched in match/map/map_class_local_radar_methods.cpp. Names cross-checked
//   against YRpp; offsets reconfirmed
//   here from the disassembly.
#ifndef GG_MATCH_MAP_MAP_CLASS_UPDATE_PATHFINDING2_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_UPDATE_PATHFINDING2_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellStruct { short X; short Y; };
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// DynamicVectorClass<CellStruct> — only Items/Count are touched.
struct CellVector_00586990
{
    char        _pad000[4];   // +0x00  vtable
    CellStruct* Items;        // +0x04
    char        _pad008[8];   // +0x08  Capacity / IsAllocated
    int         Count;        // +0x10
};
GG_STATIC_ASSERT(offsetof(CellVector_00586990, Items) == 0x4);
GG_STATIC_ASSERT(offsetof(CellVector_00586990, Count) == 0x10);

// One 10-byte record of the array at MapClass+0x70. Only the leading word is
// read/written here (`MOV word ptr [EAX+EDX*2],0` / `CMP word ptr .. ,0`).
struct SubzoneRecord_00586990
{
    unsigned short Value;        // +0x00
    char           unknown_02[8];// +0x02
};
GG_STATIC_ASSERT(sizeof(SubzoneRecord_00586990) == 10);

class CellClass
{
public:
    char       _pad000[0x24];   // +0x0000
    CellStruct MapCoords;       // +0x0024

    // FUNCTION: GAMEMD 0x47D2B0 (decl; reloc) — the per-cell redraw request.
    void FUN_0047D2B0(int what);
};
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);

// GLOBAL: GAMEMD 0x87F924 — MapClass::Instance.Cells item base.
extern CellClass** Cells_00586990;
// GLOBAL: GAMEMD 0xABDC50 — MapClass::InvalidCell (MapCoords at 0xABDC74).
extern CellClass   InvalidCell_00586990;

struct Map_00586990
{
    char                    _pad000[0x6C];             // +0x0000
    int                     unknown_6C;              // +0x006C
    SubzoneRecord_00586990* Subzones;                  // +0x0070
    char                    _pad074[0xF4 - 0x74];      // +0x0074
    int                     unknown_F4;                // +0x00F4
    int                     unknown_F8;                // +0x00F8

    // FUNCTION: GAMEMD 0x578460 (decl; reloc) — MapClass::IsWithinUsableArea.
    bool IsWithinUsableArea(CellStruct const& cell, bool checkLevel);
    // FUNCTION: GAMEMD 0x584550 (decl; reloc) — the per-cell zone rebuild.
    void FUN_00584550(CellStruct const& cell);

    // FUNCTION: GAMEMD 0x586990 — MapClass::Update_Pathfinding_2.
    void Update_Pathfinding_2(CellVector_00586990* cells);
};
GG_STATIC_ASSERT(offsetof(Map_00586990, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(Map_00586990, Subzones)     == 0x70);
GG_STATIC_ASSERT(offsetof(Map_00586990, unknown_F4)   == 0xF4);
GG_STATIC_ASSERT(offsetof(Map_00586990, unknown_F8)   == 0xF8);

#endif  // GG_MATCH_MAP_MAP_CLASS_UPDATE_PATHFINDING2_METHODS_H

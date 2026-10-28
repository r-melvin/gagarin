// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x56D3A0. MapClass keeps its map size at
//   +0xF4/+0xF8 and a table of four-byte word entries at +0x68 with the entry count at +0x6C.
//
// Address index: 0x56D3A0

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"

struct MapWordView_0056D3A0
{
    short          unknown_0;
    unsigned short Value;     // +0x02
};
GG_STATIC_ASSERT(sizeof(MapWordView_0056D3A0) == 4);

// Minimal MapClass view: the size members and the word table.
class MapClass
{
public:
    char                  unknown_000[0x68];
    MapWordView_0056D3A0* Words;       // +0x68
    int                   WordCount;   // +0x6C
    char                  unknown_70[0xF4 - 0x70];
    int                   Width;       // +0xF4
    int                   Height;      // +0xF8

    unsigned int FUN_0056D3A0(const CellStruct* cell) const;
};
GG_STATIC_ASSERT(offsetof(MapClass, Words) == 0x68);
GG_STATIC_ASSERT(offsetof(MapClass, WordCount) == 0x6C);
GG_STATIC_ASSERT(offsetof(MapClass, Width) == 0xF4);
GG_STATIC_ASSERT(offsetof(MapClass, Height) == 0xF8);

// FUNCTION: GAMEMD 0x56D3A0
// The word value for a cell, indexed row-major over (Width + Height + 1) columns and
// clamped to the table (the sum of the size members, plus one, is the row width).
unsigned int MapClass::FUN_0056D3A0(const CellStruct* cell) const
{
    int index = (Height + Width + 1) * cell->Y + cell->X;
    if (index < 0) {
        index = 0;
    } else if (index >= WordCount) {
        index = WordCount - 1;
    }
    return Words[index].Value;
}

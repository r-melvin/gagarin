// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Small leaf routines read from retail gamemd.exe v1.001; each owner is a placeholder
// `Obj_<ADDR>` pinned by offsetof asserts. Each address is verified separately.

#include <stddef.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x0054EFC0
// True for the three kinds 1, 2 and 4.
bool FUN_0054EFC0(unsigned short kind)
{
    kind &= 0xFF;
    return kind == 1 || kind == 4 || kind == 2;
}

// 256-entry ring of shorts, tail at +0x314 and head at +0x318.
struct Obj_0054F650 {
    unsigned char unknown_00[0x114];
    unsigned short Ring[256];       // +0x114
    int Tail;                       // +0x314
    int Head;                       // +0x318
    unsigned short FUN_0054F610();
    unsigned short FUN_0054F650();
    bool FUN_0054F6B0();
    bool FUN_0054F6D0();
    int FUN_0054FB90();
};
GG_STATIC_ASSERT(offsetof(Obj_0054F650, Ring) == 0x114);
GG_STATIC_ASSERT(offsetof(Obj_0054F650, Tail) == 0x314);
GG_STATIC_ASSERT(offsetof(Obj_0054F650, Head) == 0x318);

// FUNCTION: GAMEMD 0x0054F610
// Remove and return the oldest queued entry, or 0 when empty.
unsigned short Obj_0054F650::FUN_0054F610()
{
    unsigned short value = 0;
    if (Tail != Head) {
        value = Ring[Tail];
        Tail = (Tail + 1) % 256;
    }
    return value;
}

// FUNCTION: GAMEMD 0x0054F650
// The oldest queued entry, or 0 when empty.
unsigned short Obj_0054F650::FUN_0054F650()
{
    if (Tail != Head) {
        return Ring[Tail];
    }
    return 0;
}

// FUNCTION: GAMEMD 0x0054F6B0
// True when advancing the head would meet the tail.
bool Obj_0054F650::FUN_0054F6B0()
{
    bool full = (Head + 1) % 256 == Tail;
    return full;
}

// FUNCTION: GAMEMD 0x0054F6D0
bool Obj_0054F650::FUN_0054F6D0()
{
    bool empty = Tail == Head;
    return empty;
}

// FUNCTION: GAMEMD 0x0054FB90
// Free slots remaining.
int Obj_0054F650::FUN_0054FB90()
{
    return 256 - abs(Head - Tail);
}

struct Obj_0056CB80 {
    unsigned int Packed;        // +0x00
    int FUN_0056CB80();
};

// FUNCTION: GAMEMD 0x0056CB80
// Combine the low nibble with the nibble at bit 12.
int Obj_0056CB80::FUN_0056CB80()
{
    return ((Packed >> 12) & 0xF) | (Packed & 0xF);
}

struct CellXY_0056D430 {
    short X;
    short Y;
};

struct Obj_0056D430 {
    unsigned char unknown_00[0xF4];
    int MinX;                   // +0xF4
    int MaxX;                   // +0xF8
    int FUN_0056D430(const CellXY_0056D430* cell);
};
GG_STATIC_ASSERT(offsetof(Obj_0056D430, MinX) == 0xF4);
GG_STATIC_ASSERT(offsetof(Obj_0056D430, MaxX) == 0xF8);

// FUNCTION: GAMEMD 0x0056D430
// Linear cell index: row * (width) + column.
int Obj_0056D430::FUN_0056D430(const CellXY_0056D430* cell)
{
    return (MaxX + MinX + 1) * cell->Y + cell->X;
}

struct Obj_005657E0 {
    unsigned char unknown_00[0x13C];
    int* Grid;                  // +0x13C
    bool FUN_005657E0(const CellXY_0056D430* cell);
};
GG_STATIC_ASSERT(offsetof(Obj_005657E0, Grid) == 0x13C);

// FUNCTION: GAMEMD 0x005657E0
// Whether the 512-wide grid has a non-zero entry at the cell.
bool Obj_005657E0::FUN_005657E0(const CellXY_0056D430* cell)
{
    bool set = Grid[(cell->Y << 9) + cell->X] != 0;
    return set;
}

struct Obj_005AC370 {
    short X;
    short Y;
    bool FUN_005AC370(const Obj_005AC370* other) const;
};

// FUNCTION: GAMEMD 0x005AC370
// True when the two cells differ.
bool Obj_005AC370::FUN_005AC370(const Obj_005AC370* other) const
{
    return X != other->X || Y != other->Y;
}

struct Obj_0062D780 {
    int A;
    int B;
    int FUN_0062D780();
};

// FUNCTION: GAMEMD 0x0062D780
// Half the sum of the absolute components.
int Obj_0062D780::FUN_0062D780()
{
    return (abs(B) + abs(A)) >> 1;
}

struct Obj_0056D3F0 {
    unsigned char unknown_00[0x6C];
    int Count;                      // +0x6C
    unsigned char unknown_70[0x84];
    int MinX;                       // +0xF4
    int MaxX;                       // +0xF8
    int FUN_0056D3F0(const CellXY_0056D430* cell);
};
GG_STATIC_ASSERT(offsetof(Obj_0056D3F0, Count) == 0x6C);
GG_STATIC_ASSERT(offsetof(Obj_0056D3F0, MinX) == 0xF4);
GG_STATIC_ASSERT(offsetof(Obj_0056D3F0, MaxX) == 0xF8);

// FUNCTION: GAMEMD 0x0056D3F0
// Linear cell index clamped into [0, Count - 1].
int Obj_0056D3F0::FUN_0056D3F0(const CellXY_0056D430* cell)
{
    int index = (MaxX + MinX + 1) * cell->Y + cell->X;
    if (index < 0) {
        return 0;
    }
    if (index >= Count) {
        return Count - 1;
    }
    return index;
}

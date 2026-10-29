// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu127_methods.h"
#include "../_layout/cell_class.h"
#include "../_layout/cell.h"
#include "../_layout/cell_offset.h"

// SYNTHETIC: GAMEMD 0x561900 -- dynamic initialiser for DAT_00ABD490: tail-jumps to the aggregate fill at 0x561910
// SYNTHETIC: GAMEMD 0x561910 -- aggregate fill of the offset table
// GLOBAL: GAMEMD 0xABD490
// Cell offsets sorted by growing radius, 369 entries.
CellOffset DAT_00ABD490[369] = {
    CellOffset(0, 0), CellOffset(1, -1), CellOffset(0, -1), CellOffset(-1, -1), CellOffset(-1, 0),
    CellOffset(1, 0), CellOffset(-1, 1), CellOffset(0, 1), CellOffset(1, 1), CellOffset(-1, -2),
    CellOffset(0, -2), CellOffset(1, -2), CellOffset(-2, -1), CellOffset(2, -1), CellOffset(-2, 0),
    CellOffset(2, 0), CellOffset(-2, 1), CellOffset(2, 1), CellOffset(-1, 2), CellOffset(0, 2),
    CellOffset(1, 2), CellOffset(-1, -3), CellOffset(0, -3), CellOffset(1, -3), CellOffset(-2, -2),
    CellOffset(2, -2), CellOffset(-3, -1), CellOffset(3, -1), CellOffset(-3, 0), CellOffset(3, 0),
    CellOffset(-3, 1), CellOffset(3, 1), CellOffset(-2, 2), CellOffset(2, 2), CellOffset(-1, 3),
    CellOffset(0, 3), CellOffset(1, 3), CellOffset(-1, -4), CellOffset(0, -4), CellOffset(1, -4),
    CellOffset(-3, -3), CellOffset(-2, -3), CellOffset(2, -3), CellOffset(3, -3), CellOffset(-3, -2),
    CellOffset(3, -2), CellOffset(-4, -1), CellOffset(4, -1), CellOffset(-4, 0), CellOffset(4, 0),
    CellOffset(-4, 1), CellOffset(4, 1), CellOffset(-3, 2), CellOffset(3, 2), CellOffset(-3, 3),
    CellOffset(-2, 3), CellOffset(2, 3), CellOffset(3, 3), CellOffset(-1, 4), CellOffset(0, 4),
    CellOffset(1, 4), CellOffset(-1, -5), CellOffset(0, -5), CellOffset(1, -5), CellOffset(-3, -4),
    CellOffset(-2, -4), CellOffset(2, -4), CellOffset(3, -4), CellOffset(-4, -3), CellOffset(4, -3),
    CellOffset(-4, -2), CellOffset(4, -2), CellOffset(-5, -1), CellOffset(5, -1), CellOffset(-5, 0),
    CellOffset(5, 0), CellOffset(-5, 1), CellOffset(5, 1), CellOffset(-4, 2), CellOffset(4, 2),
    CellOffset(-4, 3), CellOffset(4, 3), CellOffset(-3, 4), CellOffset(-2, 4), CellOffset(2, 4),
    CellOffset(3, 4), CellOffset(-1, 5), CellOffset(0, 5), CellOffset(1, 5), CellOffset(-1, -6),
    CellOffset(0, -6), CellOffset(1, -6), CellOffset(-3, -5), CellOffset(-2, -5), CellOffset(2, -5),
    CellOffset(3, -5), CellOffset(-4, -4), CellOffset(4, -4), CellOffset(-5, -3), CellOffset(5, -3),
    CellOffset(-5, -2), CellOffset(5, -2), CellOffset(-6, -1), CellOffset(6, -1), CellOffset(-6, 0),
    CellOffset(6, 0), CellOffset(-6, 1), CellOffset(6, 1), CellOffset(-5, 2), CellOffset(5, 2),
    CellOffset(-5, 3), CellOffset(5, 3), CellOffset(-4, 4), CellOffset(4, 4), CellOffset(-3, 5),
    CellOffset(-2, 5), CellOffset(2, 5), CellOffset(3, 5), CellOffset(-1, 6), CellOffset(0, 6),
    CellOffset(1, 6), CellOffset(-1, -7), CellOffset(0, -7), CellOffset(1, -7), CellOffset(-3, -6),
    CellOffset(-2, -6), CellOffset(2, -6), CellOffset(3, -6), CellOffset(-5, -5), CellOffset(-4, -5),
    CellOffset(4, -5), CellOffset(5, -5), CellOffset(-5, -4), CellOffset(5, -4), CellOffset(-6, -3),
    CellOffset(6, -3), CellOffset(-6, -2), CellOffset(6, -2), CellOffset(-7, -1), CellOffset(7, -1),
    CellOffset(-7, 0), CellOffset(7, 0), CellOffset(-7, 1), CellOffset(7, 1), CellOffset(-6, 2),
    CellOffset(6, 2), CellOffset(-6, 3), CellOffset(6, 3), CellOffset(-5, 4), CellOffset(5, 4),
    CellOffset(-5, 5), CellOffset(-4, 5), CellOffset(4, 5), CellOffset(5, 5), CellOffset(-3, 6),
    CellOffset(-2, 6), CellOffset(2, 6), CellOffset(3, 6), CellOffset(-1, 7), CellOffset(0, 7),
    CellOffset(1, 7), CellOffset(-1, -8), CellOffset(0, -8), CellOffset(1, -8), CellOffset(-3, -7),
    CellOffset(-2, -7), CellOffset(2, -7), CellOffset(3, -7), CellOffset(-5, -6), CellOffset(-4, -6),
    CellOffset(4, -6), CellOffset(5, -6), CellOffset(-6, -5), CellOffset(6, -5), CellOffset(-6, -4),
    CellOffset(6, -4), CellOffset(-7, -3), CellOffset(7, -3), CellOffset(-7, -2), CellOffset(7, -2),
    CellOffset(-8, -1), CellOffset(8, -1), CellOffset(-8, 0), CellOffset(8, 0), CellOffset(-8, 1),
    CellOffset(8, 1), CellOffset(-7, 2), CellOffset(7, 2), CellOffset(-7, 3), CellOffset(7, 3),
    CellOffset(-6, 4), CellOffset(6, 4), CellOffset(-6, 5), CellOffset(6, 5), CellOffset(-5, 6),
    CellOffset(-4, 6), CellOffset(4, 6), CellOffset(5, 6), CellOffset(-3, 7), CellOffset(-2, 7),
    CellOffset(2, 7), CellOffset(3, 7), CellOffset(-1, 8), CellOffset(0, 8), CellOffset(1, 8),
    CellOffset(-1, -9), CellOffset(0, -9), CellOffset(1, -9), CellOffset(-3, -8), CellOffset(-2, -8),
    CellOffset(2, -8), CellOffset(3, -8), CellOffset(-5, -7), CellOffset(-4, -7), CellOffset(4, -7),
    CellOffset(5, -7), CellOffset(-6, -6), CellOffset(6, -6), CellOffset(-7, -5), CellOffset(7, -5),
    CellOffset(-7, -4), CellOffset(7, -4), CellOffset(-8, -3), CellOffset(8, -3), CellOffset(-8, -2),
    CellOffset(8, -2), CellOffset(-9, -1), CellOffset(9, -1), CellOffset(-9, 0), CellOffset(9, 0),
    CellOffset(-9, 1), CellOffset(9, 1), CellOffset(-8, 2), CellOffset(8, 2), CellOffset(-8, 3),
    CellOffset(8, 3), CellOffset(-7, 4), CellOffset(7, 4), CellOffset(-7, 5), CellOffset(7, 5),
    CellOffset(-6, 6), CellOffset(6, 6), CellOffset(-5, 7), CellOffset(-4, 7), CellOffset(4, 7),
    CellOffset(5, 7), CellOffset(-3, 8), CellOffset(-2, 8), CellOffset(2, 8), CellOffset(3, 8),
    CellOffset(-1, 9), CellOffset(0, 9), CellOffset(1, 9), CellOffset(-1, -10), CellOffset(0, -10),
    CellOffset(1, -10), CellOffset(-3, -9), CellOffset(-2, -9), CellOffset(2, -9), CellOffset(3, -9),
    CellOffset(-5, -8), CellOffset(-4, -8), CellOffset(4, -8), CellOffset(5, -8), CellOffset(-7, -7),
    CellOffset(-6, -7), CellOffset(6, -7), CellOffset(7, -7), CellOffset(-7, -6), CellOffset(7, -6),
    CellOffset(-8, -5), CellOffset(8, -5), CellOffset(-8, -4), CellOffset(8, -4), CellOffset(-9, -3),
    CellOffset(9, -3), CellOffset(-9, -2), CellOffset(9, -2), CellOffset(-10, -1), CellOffset(10, -1),
    CellOffset(-10, 0), CellOffset(10, 0), CellOffset(-10, 1), CellOffset(10, 1), CellOffset(-9, 2),
    CellOffset(9, 2), CellOffset(-9, 3), CellOffset(9, 3), CellOffset(-8, 4), CellOffset(8, 4),
    CellOffset(-8, 5), CellOffset(8, 5), CellOffset(-7, 6), CellOffset(7, 6), CellOffset(-7, 7),
    CellOffset(-6, 7), CellOffset(6, 7), CellOffset(7, 7), CellOffset(-5, 8), CellOffset(-4, 8),
    CellOffset(4, 8), CellOffset(5, 8), CellOffset(-3, 9), CellOffset(-2, 9), CellOffset(2, 9),
    CellOffset(3, 9), CellOffset(-1, 10), CellOffset(0, 10), CellOffset(1, 10), CellOffset(0, 11),
    CellOffset(0, -11), CellOffset(-1, 11), CellOffset(1, 11), CellOffset(-1, -11), CellOffset(1, -11),
    CellOffset(-2, 11), CellOffset(2, 11), CellOffset(-2, -11), CellOffset(2, -11), CellOffset(-3, 11),
    CellOffset(3, 11), CellOffset(-3, -11), CellOffset(-3, 11), CellOffset(-4, 9), CellOffset(4, 9),
    CellOffset(-4, -9), CellOffset(4, -9), CellOffset(-5, 9), CellOffset(5, 9), CellOffset(-5, -9),
    CellOffset(5, -9), CellOffset(-6, 8), CellOffset(6, 8), CellOffset(-6, -8), CellOffset(6, -8),
    CellOffset(-7, 8), CellOffset(7, 8), CellOffset(-7, -8), CellOffset(7, -8), CellOffset(-8, 7),
    CellOffset(8, 7), CellOffset(-8, -7), CellOffset(8, -7), CellOffset(-8, 6), CellOffset(8, 6),
    CellOffset(-8, -6), CellOffset(8, -6), CellOffset(-9, 5), CellOffset(9, 5), CellOffset(-9, -5),
    CellOffset(9, -5), CellOffset(-9, 4), CellOffset(9, 4), CellOffset(-9, -4), CellOffset(9, -4),
    CellOffset(-10, 3), CellOffset(10, 3), CellOffset(-10, -3), CellOffset(10, -3), CellOffset(-10, 2),
    CellOffset(10, 2), CellOffset(-10, -2), CellOffset(10, -2), CellOffset(-11, 1), CellOffset(11, 1),
    CellOffset(-11, -1), CellOffset(11, -1), CellOffset(11, 0), CellOffset(-11, 0)
};

// FUNCTION: GAMEMD 0x5638C0
// Tail-forwards to another function.
void Obj_005638C0::FUN_005638C0()
{
    FUN_005638D0();
}

// SYNTHETIC: GAMEMD 0x565060 -- CellClass constructor + atexit registration
// SYNTHETIC: GAMEMD 0x565080 -- exit-time stub: tail-jumps to ~CellClass
// GLOBAL: GAMEMD 0xABDC50
// The map's "invalid cell" sentinel.
CellClass InvalidCell;

// FUNCTION: GAMEMD 0x56C200
// Returns a constant.
int __cdecl FUN_0056C200()
{
    return 1;
}

// FUNCTION: GAMEMD 0x56C500
// Empty function.
void __cdecl FUN_0056C500()
{
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small leaf bodies
//   from the 0x54E000-0x6AC000 range; receivers are placeholder views of the members touched.
//
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Address index: 0x61F190 0x65C8B0 0x642740

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "global_getter_family_methods.h"
#include "../_layout/cell.h"
#include "header_init_shapes.h"

// Four adjacent cell-offset pairs, built with (0,0) (4,0) (0,4) (4,4).
// SYNTHETIC: GAMEMD 0x585EE0
// GLOBAL: GAMEMD 0xABD460
HeaderCellInit DAT_00ABD460[4] = {
    HeaderCellInit(0, 0), HeaderCellInit(4, 0), HeaderCellInit(0, 4), HeaderCellInit(4, 4)
};

// GLOBAL: GAMEMD 0xAC48B8
extern unsigned short DAT_00AC48B8;
// GLOBAL: GAMEMD 0xAC48BA
extern unsigned short DAT_00AC48BA;
// GLOBAL: GAMEMD 0xAC48BC
extern unsigned short DAT_00AC48BC;

// FUNCTION: GAMEMD 0x61F190
// Build the three colour-channel masks of the display's pixel format from its bit counts and shifts.
void __cdecl FUN_0061F190()
{
    DAT_00AC48B8 = 0xFF;
    DAT_00AC48B8 >>= FUN_004BBC40();
    DAT_00AC48B8 <<= FUN_004BBC30();
    DAT_00AC48BA = 0xFF;
    DAT_00AC48BA >>= FUN_004BBC60();
    DAT_00AC48BA <<= FUN_004BBC50();
    DAT_00AC48BC = 0xFF;
    DAT_00AC48BC >>= FUN_004BBC80();
    DAT_00AC48BC <<= FUN_004BBC70();
}

// Seeded generator state: the previous output and a running counter (the Pair at 0x65C890).
struct Random3_0065C8B0
{
    int Left;       // +0x0000
    int Counter;    // +0x0004

    int FUN_0065C8B0();
};
GG_STATIC_ASSERT(offsetof(Random3_0065C8B0, Counter) == 4);

// GLOBAL: GAMEMD 0x839644 -- first key table
extern int DAT_00839644[4];
// GLOBAL: GAMEMD 0x839694 -- second key table
extern int DAT_00839694[4];

// FUNCTION: GAMEMD 0x65C8B0
// One four-round mixing step over the counter and the previous output.
int Random3_0065C8B0::FUN_0065C8B0()
{
    int right = Counter;
    int left = Left;
    Counter = right + 1;
    for (int i = 0; i < 4; i++) {
        int saved = right;
        int x = DAT_00839644[i] ^ right;
        int lo = x & 0xFFFF;
        int hi = x >> 16;
        int m = ~(hi * hi) + lo * lo;
        right = (m >> 16) | (m << 16);
        right ^= DAT_00839694[i];
        right += hi * lo;
        right ^= left;
        left = saved;
    }
    return right;
}

// Lepton coordinate triple written by FUN_00642740.
struct Coord_00642740
{
    int X;      // +0x0000
    int Y;      // +0x0004
    int Z;      // +0x0008

    Coord_00642740* FUN_00642740(const CellStruct* cell, int z);
};

// FUNCTION: GAMEMD 0x642740
// Set this to the centre of a cell (X and Y in 256ths plus half a cell) at the given height.
Coord_00642740* Coord_00642740::FUN_00642740(const CellStruct* cell, int z)
{
    int y = cell->Y * 256 + 128;
    X = cell->X * 256 + 128;
    Y = y;
    Z = z;
    return this;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAC48B8
unsigned short DAT_00AC48B8;
// GLOBAL: GAMEMD 0xAC48BA
unsigned short DAT_00AC48BA;
// GLOBAL: GAMEMD 0xAC48BC
unsigned short DAT_00AC48BC;
// END defined globals

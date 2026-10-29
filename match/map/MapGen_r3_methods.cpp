// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Functions of the
//   random-map generator (original translation unit MapGen.cpp, see MapGen.cpp) that are
//   matched in this sibling file; the types and helpers come from MapGen.h.
//
// Address index: 0x58BE20 0x58CF90 0x598030
#include "MapGen.h"
#include "../_layout/cell_class.h"

// GLOBAL: GAMEMD 0x89C2DC -- map side length in cells.
extern int DAT_0089C2DC;

// FUNCTION: GAMEMD 0x58BE20
// Draws record cells at random until one is not the origin and returns it.
// PARTIAL: 88.1% -- same instructions as retail (multiset identical); the final index/base
// address arithmetic before the dword copy is scheduled differently (lea/shl target register).
Cell FUN_0058BE20()
{
    int count = DAT_0089C2DC * DAT_0089C2DC;
    unsigned int idx;
    do {
        idx = Inline_0058C320(count - 1);
    } while (DAT_00ABED10[idx].unknown_00.X == 0 && DAT_00ABED10[idx].unknown_00.Y == 0);
    Cell result = DAT_00ABED10[idx].unknown_00;
    return result;
}

// FUNCTION: GAMEMD 0x598030
// A random integer in [min, max] drawn from the generator's stream.
int FUN_00598030(int min, int max)
{
    int value;
    do {
        value = (int)((double)(unsigned int)DAT_00ABE890.FUN_0065C780() * (double)(unsigned int)(max - min + 1) *
                          2.3283064370807974e-10 +
                      (double)(unsigned int)min);
    } while ((unsigned int)value > (unsigned int)max);
    return value;
}

// FUNCTION: GAMEMD 0x58CF90
// For every unassigned non-origin record cell that passes the 0x4865D0 or 0x4867B0 test, fetches
// the cell's record (0x58C800).
void FUN_0058CF90()
{
    int n = DAT_0089C2DC * DAT_0089C2DC;
    for (int i = 0; i < n; i++) {
        CellStruct c = DAT_00ABED10[i].unknown_00;
        CellClass* cell = DAT_0087F7E8.FUN_005657A0(&c);
        Rec_50* r = &DAT_00ABED10[i];
        if (r->unknown_38 == -1 && (r->unknown_00.X || r->unknown_00.Y)) {
            if (cell->FUN_004865D0() || cell->FUN_004867B0())
                cell->FUN_0058C800();
        }
    }
}

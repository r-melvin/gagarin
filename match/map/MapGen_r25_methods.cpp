// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Functions of the
//   random-map generator (original translation unit MapGen.cpp, see MapGen.cpp) that are
//   matched in this sibling file; the types and helpers come from MapGen.h.
//
// Address index: 0x58BEA0
#include "MapGen.h"
#include "../_layout/cell_class.h"

// GLOBAL: GAMEMD 0x89C2DC -- map side length in cells.
extern int DAT_0089C2DC;

// FUNCTION: GAMEMD 0x58BEA0
// Draws record cells at random until one is a non-origin cell that passes the 0x486380 test; gives up
// with the origin after 200 draws. The result is written through the pointer, which is also returned.
// PARTIAL: 94.3% -- same instructions as retail (multiset identical); the index scratch register for the
// record copy is eax where retail uses ecx.
CellStruct* __fastcall FUN_0058BEA0(CellStruct* out)
{
    int tries = 0;
    for (;;) {
        unsigned int n = DAT_0089C2DC * DAT_0089C2DC;
        unsigned int idx;
        do {
            idx = Inline_0058C320(n - 1);
        } while (DAT_00ABED10[idx].unknown_00.X == 0 && DAT_00ABED10[idx].unknown_00.Y == 0);
        CellStruct c = DAT_00ABED10[idx].unknown_00;
        tries++;
        if (tries > 200)
            break;
        if (DAT_0087F7E8.FUN_005657A0(&c)->FUN_00486380()) {
            *out = c;
            return out;
        }
    }
    CellStruct z;
    z.X = 0;
    z.Y = 0;
    *out = z;
    return out;
}

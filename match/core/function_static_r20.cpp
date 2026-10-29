// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the addresses below.
//
// A function-local static with a destructor: first use constructs it and
// registers the exit-time stub (0x41CBD0, emitted by the compiler as _$E2).
// Address index: 0x41CB70, 0x41CBD0.

#include "header_init_shapes.h"

// Two cell values: an empty cell and the 0x7FFF "no cell" marker.
struct CellPairStatic_00889F20
{
    CellStruct First;
    CellStruct Second;
    CellPairStatic_00889F20()
    {
        First = HeaderCellInit(0, 0);
        Second = HeaderCellInit(0x7FFF, 0x7FFF);
    }
    ~CellPairStatic_00889F20() {}
};

// FUNCTION: GAMEMD 0x41CB70
// SYNTHETIC: GAMEMD 0x41CBD0 -- exit-time destructor stub of the static below
// GLOBAL: GAMEMD 0x889F20
// Return the lazily constructed pair; the argument is ignored.
CellPairStatic_00889F20* __stdcall FUN_0041CB70(int unused)
{
    static CellPairStatic_00889F20 instance;
    return &instance;
}

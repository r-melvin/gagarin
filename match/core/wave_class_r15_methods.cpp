// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   More WaveClass methods read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at
//   the address in each annotation. The methods hang off a view derived from the canonical WaveClass
//   (the canonical header is shared by several translation units and is left alone).
//   Address index: 0x75F4C0, 0x761030, 0x7610A0.

#include "../_layout/wave_class.h"
#include "../_layout/cell.h"
#include "../_layout/coord_struct.h"
#include "vector_class_operations.h"

class CellClass;

// A cell, as far as the coordinate query 0x480A30.
struct WaveCell_00480A30
{
    // FUNCTION: GAMEMD 0x480A30 (decl; reloc)
    CoordStruct* FUN_00480A30(CoordStruct* out);
};

// The map (GLOBAL 0x87F7E8): 0x5657A0 returns the cell at a cell coordinate.
struct WaveMap_0087F7E8
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    CellClass* FUN_005657A0(const CellStruct* cell);
};
// GLOBAL: GAMEMD 0x87F7E8
extern WaveMap_0087F7E8 DAT_0087F7E8_WaveR15;

class WaveView_R15 : public WaveClass
{
public:
    // FUNCTION: GAMEMD 0x762AF0 (decl; reloc)
    void FUN_00762AF0();
    // FUNCTION: GAMEMD 0x75F330 (decl; reloc) -- one stack argument.
    void FUN_0075F330(CoordStruct* coord);

    void AddCell(const CellStruct* cell);   // 0x75F4C0
    void Step();                            // 0x7610A0
    void StepCells();                       // 0x761030
};

// FUNCTION: GAMEMD 0x75F4C0
// Add the cell under a cell coordinate to the wave's cell list, once.
void WaveView_R15::AddCell(const CellStruct* cell)
{
    CellClass* c = DAT_0087F7E8_WaveR15.FUN_005657A0(cell);
    if (unknown_1F0.FindItemIndex(c) == -1) {
        unknown_1F0.AddItem(c);
    }
}

// FUNCTION: GAMEMD 0x7610A0
// Advance the wave one step: when its life runs out call slot 62, else the base step.
void WaveView_R15::Step()
{
    FUN_00762AF0();
    if (--unknown_130 < 0) {
        vf_62();
    } else {
        ObjectClass::vf_23();
    }
}

// FUNCTION: GAMEMD 0x761030
// Advance the wave one step, first feeding the centre of every listed cell to 0x75F330.
void WaveView_R15::StepCells()
{
    FUN_00762AF0();
    for (int i = 0; i < unknown_1F0.Count; i++) {
        CoordStruct tmp;
        FUN_0075F330(((WaveCell_00480A30*)unknown_1F0.Items[i])->FUN_00480A30(&tmp));
    }
    if (--unknown_130 < 0) {
        vf_62();
    } else {
        ObjectClass::vf_23();
    }
}

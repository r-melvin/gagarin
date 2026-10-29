// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//   Bodies matched against retail gamemd.exe v1.001 at each address below.
//
// MapClass cell-table virtuals (vtable slots 22..24): (re)build, release and
// construct the cell pointer table at +0x138.
//
// Address index: 0x565AA0 0x565B00 0x565BC0

#include <new.h>
#include "../ui/input_controls/ui_display_chain.h"
#include "../core/vector_class_operations.h"
#include "../_layout/cell_class.h"

// FUNCTION: GAMEMD 0x565AA0
// Reseats the cell pointer table and sizes it for the map's cell count, every slot empty.
void MapClass::vf_22()
{
    new (&Owned) VectorClass<CellClass*>();
    Owned.SetCapacity(unknown_154, 0);
    for (int i = 0; i < unknown_154; i++)
        Owned.Items[i] = 0;
}

// FUNCTION: GAMEMD 0x544FF0 (decl; reloc)
bool FUN_00544FF0(int value, bool flag);

// FUNCTION: GAMEMD 0x565B00
// Empties the cell table: drops every cell's bridge-owner link, deletes the cells, and grows the table to full size.
void MapClass::vf_23()
{
    for (int i = 0; i < Owned.Capacity; i++) {
        CellClass* cell = Owned.Items[i];
        if (cell != 0) {
            cell->BridgeOwnerCell = 0;
            cell->unknown_30 = 0;
        }
    }
    for (int j = 0; j < Owned.Capacity; j++) {
        CellClass* cell = Owned.Items[j];
        if (cell != 0) {
            delete cell;
            Owned.Items[j] = 0;
        }
    }
    FUN_00544FF0(0, true);
    if (Owned.Capacity < 0x40000) {
        Owned.SetCapacity(0x40000, 0);
        for (int k = 0; k < Owned.Capacity; k++)
            Owned.Items[k] = 0;
    }
}

// FUNCTION: GAMEMD 0x565BC0
// Runs the cell constructor over every allocated slot of the 512 x 512 table.
void MapClass::vf_24()
{
    unknown_134 = 0;
    for (int y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            int index = y * 512 + x;
            if (index < Owned.Capacity && Owned.Items[index] != 0)
                new (Owned.Items[index]) CellClass();
        }
    }
}

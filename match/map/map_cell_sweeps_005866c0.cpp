// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001. Complete control flow
// and call/field ABIs are confirmed by the Evidence IDs in the paired header.
#include "map_cell_sweeps_005866c0.h"

// PARTIAL: 20/25 instructions (80.0%; 17 exact, 3 relocation-normalised,
// 5 differing). Retail stores the iterator state/count/last values before it
// reads the cursor base and shifts the count; VC6 hoists the base load and
// schedules those register values differently. The instruction multiset is
// identical. Commuted/nested cursor expressions did not alter this form; /O1
// scored lower. An experimental volatile-qualified view reached 96%, but was
// excluded because retail evidence does not establish volatile semantics and
// it still did not produce exact bytes. A validated 90-second permuter run on
// that experimental form found no better candidate.
// FUNCTION: GAMEMD 0x5866C0
void MapScan_005866C0::FUN_005866C0()
{
    int count = cellCount;
    iterState = 1;
    iterCount = count;
    iterLast = count - 1;
    iterCursor = cellBase + count * 0x800 + 4;
    CellScan_005866C0* cell = FUN_00578290();
    while (cell) {
        if ((cell->flags & 2) == 0) cell->FUN_00486A70();
        cell = FUN_00578290();
    }
}

// PARTIAL: 18/23 instructions (78.3%; 15 exact, 3 relocation-normalised,
// 5 differing). The same iterator-setup scheduling delta described above is
// present here; the loop and call sequence match after initialization.
// FUNCTION: GAMEMD 0x586720
void MapScan_005866C0::FUN_00586720()
{
    int count = cellCount;
    iterState = 1;
    iterCount = count;
    iterLast = count - 1;
    iterCursor = cellBase + count * 0x800 + 4;
    CellScan_005866C0* cell = FUN_00578290();
    while (cell) {
        cell->FUN_00486BF0();
        cell = FUN_00578290();
    }
}

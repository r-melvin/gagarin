// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of gamemd.exe v1.001 at 0x4AE450; the redraw call is GScreenClass slot 14 (+0x38).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4AE450  MapClass::FUN_004AE450

#include "../ui/input_controls/ui_display_chain.h"
#include "../ui/input_controls/display_scenario.h"

// FUNCTION: GAMEMD 0x545000 (decl; reloc) -- rebuilds the global light record and clears every cell's +0x34.
void FUN_00545000();
// GLOBAL: GAMEMD 0xABDC84
extern int DAT_00ABDC84;

// FUNCTION: GAMEMD 0x4AE450
// Rebuilds the light record, then resets every cell's light values to the neutral level and asks for a redraw.
void MapClass::FUN_004AE450()
{
    FUN_00545000();
    Map_0087F7E8.FUN_00578350();
    DisplayScCellObject* cell = Map_0087F7E8.FUN_00578290();
    DAT_00ABDC84 = 0;
    while (cell != 0)
    {
        cell->FUN_00483E30(0, 0x10000, 0, 1000, 1000, 1000);
        cell = Map_0087F7E8.FUN_00578290();
    }
    FlagToRedraw(1);
}

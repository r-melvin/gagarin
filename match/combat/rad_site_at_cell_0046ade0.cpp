// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of gamemd.exe v1.001 at 0x46ADE0 (RET 0xC, new RadSiteClass at PUSH 0x74).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x46ADE0

#include "../_layout/rad_site_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"

// FUNCTION: GAMEMD 0x46ADE0
// PARTIAL: 91.5% (only the edx/ecx load order of the two setter calls differs)
// Adds radiation at a cell: raises the cell's existing RadSite, or makes and activates a new one.
void __stdcall FUN_0046ADE0(CellStruct cell, int spread, int radLevel)
{
    CellClass* target = DAT_0087F7E8.FUN_005657A0(&cell);
    RadSiteClass* existing = static_cast<RadSiteClass*>(target->FUN_00487C80());
    if (existing == 0)
    {
        RadSiteClass* site = new RadSiteClass();
        site->SetBaseCell(&cell);
        site->SetSpread(spread);
        site->SetRadLevel(radLevel);
        site->Activate();
        target->FUN_00487C70(site);
        return;
    }
    existing->Add(radLevel);
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at 0x6B0260 and 0x6B02C0: the owner's
//   slot-0x338 nearby-cell search called with a rules range / 256.
//
//   Address index: 0x6B0260 0x6B02C0

#include "slave_manager_class_wake_methods.h"

// FUNCTION: GAMEMD 0x6B0260
// Is there a real cell within the rules range of the owner? (search flag 0)
bool SlaveManagerView_006B1020::HasNearbyCell()
{
    CellStruct cell = (this->Owner->*this->Owner->Vtbl->At_338)(
        RulesInstance->At_1780 / 256, 0);
    return cell.X != DAT_00B0B5B8.X || cell.Y != DAT_00B0B5B8.Y;
}

// FUNCTION: GAMEMD 0x6B02C0
// The cell found within the second rules range (search flag 1).
CellStruct SlaveManagerView_006B1020::GetNearbyCell()
{
    return (this->Owner->*this->Owner->Vtbl->At_338)(
        RulesInstance->At_1788 / 256, 1);
}

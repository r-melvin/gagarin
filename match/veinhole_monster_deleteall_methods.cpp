// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 at GAMEMD
//   0x74D760 (VeinholeMonsterClass::DeleteAll). All offsets/globals reconfirmed
//   from the local Ghidra disassembly; YRpp consulted, not copied.
//
// DeleteAll deletes every registered VeinholeMonster (highest index first) via
// its virtual destructor, then clears the backing vector: Count=0, free the
// Items block if owned, then drop IsAllocated and Capacity.
#include "veinhole_monster_deleteall_methods.h"

// FUNCTION: GAMEMD 0x74D760  VeinholeMonsterClass::DeleteAll (static)
void VeinholeMonsterClass::DeleteAll()
{
    for (int i = VeinholeArray.Count - 1; i >= 0; --i) {
        VeinholeMonsterClass* pMonster =
            ((VeinholeMonsterClass**)VeinholeArray.Items)[i];
        if (pMonster) {
            delete pMonster;
        }
    }

    VeinholeArray.Count = 0;
    if (VeinholeArray.Items != 0 && VeinholeArray.IsAllocated) {
        GameDeallocate(VeinholeArray.Items);
        VeinholeArray.Items = 0;
    }
    VeinholeArray.IsAllocated = false;
    VeinholeArray.Capacity = 0;
}

// FUNCTION: GAMEMD 0x74E880  VeinholeMonsterClass::DeleteVeinholeGrowthData (__fastcall, static)
void VeinholeMonsterClass::DeleteVeinholeGrowthData()
{
    if (VeinholeGrowthData != 0) {
        GameDeallocate(VeinholeGrowthData);
        VeinholeGrowthData = 0;
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB1D2F0
void* VeinholeGrowthData;
// END defined globals

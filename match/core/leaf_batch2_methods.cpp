// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "leaf_batch2_methods.h"

// FUNCTION: GAMEMD 0x004C2C10
//
// WaveEntry cleanup: if OwnerPtr is non-null, clear a field within the owner
// object (at offset 0x6dc), then clear the OwnerPtr member itself.
void WaveEntry_004C2C10::DetachOwner()
{
    void* owner = this->OwnerPtr;
    if (owner != 0) {
        *(int*)((char*)owner + 0x6dc) = 0;
        this->OwnerPtr = 0;
    }
}

// FUNCTION: GAMEMD 0x004CA170
//
// FactoryClass getter: return the OriginalBalance field at offset 0x68
int FactoryClass_004CA170::GetOriginalBalance() const
{
    return this->OriginalBalance;
}

// FUNCTION: GAMEMD 0x004E2450
//
// Timer constructor: call GetTickCount and store in Snapshot
typedef int (*GetTickCountFunc)();
Timer_004E2450::Timer_004E2450()
{
    // Calls extern function at 0x7e1530
    extern GetTickCountFunc g_getTickCountFunc;
    this->Snapshot = g_getTickCountFunc();
}

// 0x004F42D0 is NOT defined here. It was drafted in this batch as a
// "SessionInputCursor" setter, but the address already had a body in
// match/map/map_class_more_methods.cpp as MapClass::FUN_004F42D0, whose
// neighbour at 0x4F42F0 identifies the class properly. The
// collision survived because the pre-flight grep used the zero-padded spelling
// 0x004F42D0 while the existing annotation is written 0x4F42D0. Use
// scripts/vc6/claimed.py, which checks every spelling, rather than a bare grep.

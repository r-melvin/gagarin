// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "leaf_batch2_methods.h"

// IMPORT: GAMEMD 0x007E1530 (WINMM timeGetTime)
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// FUNCTION: GAMEMD 0x004CA170
//
// FactoryClass getter: return the OriginalBalance field at offset 0x68
int FactoryClass_004CA170::GetOriginalBalance() const
{
    return this->OriginalBalance;
}

// FUNCTION: GAMEMD 0x004E2450
//
// Timer constructor: call timeGetTime and store its DWORD result in Snapshot
Timer_004E2450::Timer_004E2450()
{
    this->Snapshot = timeGetTime();
}

// 0x004F42D0 is NOT defined here. It was drafted in this batch as a
// "SessionInputCursor" setter, but the address already had a body in
// match/map/map_class_more_methods.cpp as MapClass::FUN_004F42D0, whose
// neighbour at 0x4F42F0 identifies the class properly. The
// collision survived because the pre-flight grep used the zero-padded spelling
// 0x004F42D0 while the existing annotation is written 0x4F42D0. Use
// scripts/vc6/claimed.py, which checks every spelling, rather than a bare grep.

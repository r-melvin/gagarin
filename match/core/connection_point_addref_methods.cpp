// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// ConnectionPointClass::AddRef (IUnknown slot 1 of its IConnectionPoint
// table): a global count of live connection points goes up, then the
// object's own interlocked reference count (+0x14) is raised and returned.

#include "../_layout/connection_point_class.h"

// GLOBAL: GAMEMD 0xABCD3C
extern int DAT_00ABCD3C;

// FUNCTION: GAMEMD 0x004A0520
ULONG __stdcall ConnectionPointClass::AddRef()
{
    DAT_00ABCD3C++;
    return InterlockedIncrement((LONG*)&unknown_14);
}

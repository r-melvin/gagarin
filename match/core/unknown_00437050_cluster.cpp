// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail gamemd.exe v1.001 instructions and relocation targets were confirmed
// from full entry-bounded disassembly, raw memory reads and focused REA records.

#include "unknown_00437050_cluster.h"

// FUNCTION: GAMEMD 0x00437050
bool UnknownObject_00437050::FUN_00437050(const void* location, int flag)
{
    if (FUN_005F4EC0(location, flag)) {
        // The binary passes this pointer as an opaque object address; the cast
        // only matches the existing LogicClass::AddObject declaration.
        LogicInstance.AddObject((TechnoClass*)this, false);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x004370B0
extern "C" int __cdecl FUN_004370B0()
{
    return 0x13;
}

// FUNCTION: GAMEMD 0x00437190
extern "C" void __cdecl FUN_00437190()
{
    DAT_0089C558 = 0;
    DAT_0089C55C = 0;
    DAT_0089C560 = 0;
    DAT_0089C564 = 0;
}

// FUNCTION: GAMEMD 0x004371B0
extern "C" int __fastcall FUN_004371B0(
    UnknownObject_004371B0* object, int factor, int count)
{
    return object->vtable->slot_1C(object) * factor * count;
}

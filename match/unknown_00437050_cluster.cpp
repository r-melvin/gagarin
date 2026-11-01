// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
// Retail gamemd.exe v1.001 instructions and relocation targets were confirmed
// from full entry-bounded disassembly, raw memory reads and focused REA records.

#include "unknown_00437050_cluster.h"
#include "mathtbl_init_shapes.h"

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

// SYNTHETIC: GAMEMD 0x00437190
// GLOBAL: GAMEMD 0x0089C558
MathTblZero4 DAT_0089C558;

// FUNCTION: GAMEMD 0x004371B0
extern "C" int FUN_004371B0(
    UnknownObject_004371B0* object, int factor, int count)
{
    return object->vtable->slot_1C(object) * factor * count;
}

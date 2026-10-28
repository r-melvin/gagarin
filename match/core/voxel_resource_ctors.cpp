// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob1
// /Ob1 and /Ob2 both reproduce these constructor bodies.
// Native entries initialize the aligned fields, load through the supplied
// FileClass, and set byte +0 only when the loader returns zero.
#include "../_layout/voxel_resource_data.h"

// FUNCTION: GAMEMD 0x5BD570
Obj_005BD5A0::Obj_005BD5A0(FileClass* file)
    : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0C(0)
{
    if (FUN_005BD5C0(file) == 0) unknown_00 = 1;
}

// FUNCTION: GAMEMD 0x755CD0
Obj_00755D10::Obj_00755D10(FileClass* file, int unknown)
    : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0C(0),
      Block0(0), Block1(0), Block2(0)
{
    if (FUN_00755DB0(file, unknown) == 0) unknown_00 = 1;
}

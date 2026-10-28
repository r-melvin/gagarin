// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Target bytes: user's retail gamemd.exe v1.001 (disasm 0x5F5930).
#include "../_layout/object_class.h"

// FUNCTION: GAMEMD 0x5F5930
// True when the house argument is non-null.
bool ObjectClass::vf_102(HouseClass* house)
{
    return house != 0;
}

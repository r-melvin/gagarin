// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// TechnoClass body for primary-table (0x7F4960) slot 170, emitted at 0x4E0150
// inside the foot code. The slot number comes from the RTTI-located table; the
// name is a placeholder (techno_class.h).
#include "../_layout/techno_class.h"

// FUNCTION: GAMEMD 0x4E0150
// The current heading of PrimaryFacing (+0x388), by value.
DirStruct TechnoClass::vf_170()
{
    return PrimaryFacing.FUN_004C93D0();
}

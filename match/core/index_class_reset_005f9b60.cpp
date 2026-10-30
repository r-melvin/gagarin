// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Out-of-line IndexClass storage reset (0x5F9B60). It is kept apart from
// ObjectTypeClass::Load, which calls it, so the call is not expanded inline.
#include "../_layout/object_type_class.h"

// FUNCTION: GAMEMD 0x5F9B60
void IndexClass::FUN_005F9B60()
{
    ResetStorage();
}

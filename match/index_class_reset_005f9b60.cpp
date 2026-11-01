// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Out-of-line copy of IndexClass<int, void*>::Clear (0x5F9B60): free the table, zero the five fields.
// It is kept apart from ObjectTypeClass::Load, which calls it, so the call is not expanded inline.
#include "_layout/object_type_class.h"

// FUNCTION: GAMEMD 0x5F9B60
template<>
void IndexClass<int, void*>::FUN_005F9B60()
{
    Clear();
}

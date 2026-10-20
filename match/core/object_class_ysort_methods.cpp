// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Retail 0x5F6BD0 calls the primary coordinate slot +0xAC twice, then sums
// Y from the first result and X from the second. The method name is a
// consult-only naming hypothesis. This uses the shared explicit-vptr layout;
// the slot-call view does not establish the original virtual declaring class.
#include "../_layout/object_class.h"

typedef CoordStruct* (ObjectClass::*ObjectYSortGetCoords)(CoordStruct*) const;
struct ObjectYSortVtablePrefix
{
    char unknown_00[0xAC];
    ObjectYSortGetCoords GetTargetCoords;
};
GG_STATIC_ASSERT(offsetof(ObjectClass, _vtable_IPersistStream) == 0);
GG_STATIC_ASSERT(offsetof(ObjectYSortVtablePrefix, GetTargetCoords) == 0xAC);
GG_STATIC_ASSERT(sizeof(ObjectYSortGetCoords) == 4);
GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0);
GG_STATIC_ASSERT(offsetof(CoordStruct, Y) == 4);
GG_STATIC_ASSERT(sizeof(CoordStruct) == 12);

// FUNCTION: GAMEMD 0x5F6BD0
int ObjectClass::GetYSort() const
{
    CoordStruct coord1;
    CoordStruct coord2;
    return (this->*static_cast<const ObjectYSortVtablePrefix*>(
                _vtable_IPersistStream)->GetTargetCoords)(&coord1)->Y
        + (this->*static_cast<const ObjectYSortVtablePrefix*>(
                _vtable_IPersistStream)->GetTargetCoords)(&coord2)->X;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-pinned-retail-PE
//   Entry-origin bytes at 0x5F5F30 load the dword at ObjectClass+0xA4 and
//   return. ObjectClass::Location is at +0x9C and CoordStruct::Z at +8.

#include <stddef.h>
#include "../_layout/object_class.h"

GG_STATIC_ASSERT(offsetof(ObjectClass, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(CoordStruct, Z) == 0x08);
typedef int (ObjectClass::*ObjectCellGetter)() const;
GG_STATIC_ASSERT(sizeof(ObjectCellGetter) == 4);

// FUNCTION: GAMEMD 0x5F5F30
int ObjectClass::FUN_005F5F30() const
{
    return Location.Z;
}

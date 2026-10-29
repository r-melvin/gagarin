// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x47EA90: the occupier heads `[EDI+0xE4]` / `[EDI+0xE8]`,
//   the list spine `[ESI+0x30]`, the cell coordinate `MOVSX ECX,[EDI+0x24]` /
//   `MOVSX EDX,[EDI+0x26]`, the object location `LEA EDX,[ESI+0x9C]`, and the
//   three primary-vtable slots `CALL [EAX+0x2C]`, `CALL [EDX+0xC0]`,
//   `CALL [EAX+0xF4]`. Name from the YRpp method map (CellClass::RemoveContent
//   ).
#ifndef GG_MATCH_MAP_CELL_CLASS_REMOVE_CONTENT_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_REMOVE_CONTENT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/object_class.h"   // ObjectClass: NextObject@0x30, Location@0x9C

GG_STATIC_ASSERT(offsetof(ObjectClass, NextObject) == 0x30);
GG_STATIC_ASSERT(offsetof(ObjectClass, Location)   == 0x9C);

// ObjectClass is complete (from the layout header), so these member-function
// pointers take the 4-byte single-inheritance form — see match/_rt/gg_vslot.h.
typedef int  (IPersistStream::*FnWhatAmI_0047EA90)();
typedef bool (IPersistStream::*FnC0_0047EA90)();
typedef void (IPersistStream::*FnF4_0047EA90)(CoordStruct* coord);

// The primary (IPersistStream-side) vtable of ObjectClass, only the three slots
// RemoveContent dispatches through.
struct Vtbl_0047EA90
{
    char              _pad000[0x2C];          // +0x0000
    FnWhatAmI_0047EA90 WhatAmI;               // +0x002C  AbstractClass::WhatAmI
    char              _pad030[0xC0 - 0x30];   // +0x0030
    FnC0_0047EA90     At_C0;                  // +0x00C0  bool query
    char              _padC4[0xF4 - 0xC4];    // +0x00C4
    FnF4_0047EA90     At_F4;                  // +0x00F4  takes a CoordStruct*
};
GG_STATIC_ASSERT(offsetof(Vtbl_0047EA90, WhatAmI) == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_0047EA90, At_C0)   == 0xC0);
GG_STATIC_ASSERT(offsetof(Vtbl_0047EA90, At_F4)   == 0xF4);

// CellStruct — a 16-bit map cell coordinate pair.
struct CellStruct_0047EA90
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct_0047EA90) == 4);

// CellClass — only the members RemoveContent touches.
#include "../_layout/cell_class.h"
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords)   == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, FirstObject) == 0xE4);
GG_STATIC_ASSERT(offsetof(CellClass, AltObject)   == 0xE8);

#endif  // GG_MATCH_MAP_CELL_CLASS_REMOVE_CONTENT_METHODS_H

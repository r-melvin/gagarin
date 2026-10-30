// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x486C50: `[EBX+0x28]` (the cell's fogged-object
//   vector, re-read every iteration and finally zeroed), the vector's
//   `[EAX+0x4]` Items / `[EAX+0x10]` Count and its slots `[EDX+0x0]`
//   (scalar-deleting destructor, PUSH 1), `[EDX+0xC]` (Clear, no args) and
//   `[EDX+0x10]` (index-of, address of the element pushed), the fogged
//   object's `ADD EDX,0x34` coordinate triple and its `[EAX+0x20]` scalar
//   deleting destructor, and the 0x7FFF/0x7FFF sentinel pair walked two
//   shorts at a time out of 0x4D2790. The cell coordinate is the inlined
//   signed divide by 256 (`CDQ; AND EDX,0xFF; ADD; SAR 8`) and the
//   MapClass::GetCellAt receiver is the fixed instance `MOV ECX,0x87F7E8`.
//   CellClass::ClearFoggedObjects and MapClass::GetCellAt are YRpp names;
//   every offset is reconfirmed here.
#ifndef GG_MATCH_MAP_CELL_CLASS_FOGGED_OBJECTS_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_FOGGED_OBJECTS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"
#include "../_layout/cell_class.h"
#include "../_layout/fogged_object_class.h"
#include "../_layout/map_0087f7e8.h"

// FUNCTION: GAMEMD 0x4D2790 (decl; reloc) -- the record's occupy list, or 0.
short* FUN_004D2790(FoggedObjectClass* object);

#endif  // GG_MATCH_MAP_CELL_CLASS_FOGGED_OBJECTS_METHODS_H

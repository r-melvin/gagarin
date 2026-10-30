// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x457A10: the map-coords slot `[EAX+0x1B8]`
//   on the building, the type at `[ESI+0x520]` and its foundation slot
//   `[EDX+0x90]` (called with a pushed 0), the foundation terminator
//   `CMP AX,0x7FFF` on X and Y, the map singleton as the immediate
//   `MOV ECX,0x87F7E8` feeding CALL 0x5657A0 (MapClass::GetCellAt), and the
//   cell flag word `TEST [EAX+0x140],0x400000`. Names cross-checked against
//   YRpp BuildingClass::CheckFog / ObjectClass::GetMapCoords /
//   GetFoundationData (re-derived here).
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_FOG_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_FOG_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// 2D short cell coordinate (sizeof == 4): X@0, Y@2.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"

// BuildingTypeClass — only its vtable is reached (slot 0x90, GetFoundationData).
struct TypeVtbl_00457A10;
struct Type_00457A10
{
    TypeVtbl_00457A10* Vtbl;   // +0x0000
};
typedef CellStruct const* (Type_00457A10::*Fn90_00457A10)(bool includeBib);
struct TypeVtbl_00457A10
{
    char           _pad000[0x90];       // +0x0000
    Fn90_00457A10  GetFoundationData;   // +0x0090
};
GG_STATIC_ASSERT(offsetof(TypeVtbl_00457A10, GetFoundationData) == 0x90);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_00457A10;

struct BuildingClass_00457A10
{
    Vtbl_00457A10*   Vtbl;              // +0x0000
    char             _pad004[0x51C];    // +0x0004
    Type_00457A10*   Type;              // +0x0520

    // FUNCTION: GAMEMD 0x457A10
    bool CheckFog();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00457A10, Type) == 0x520);

typedef CellStruct* (BuildingClass_00457A10::*Fn1B8_00457A10)(CellStruct* out);

struct Vtbl_00457A10
{
    char            _pad000[0x1B8];   // +0x0000
    Fn1B8_00457A10  GetMapCoords;     // +0x01B8
};
GG_STATIC_ASSERT(offsetof(Vtbl_00457A10, GetMapCoords) == 0x1B8);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_FOG_METHODS_H

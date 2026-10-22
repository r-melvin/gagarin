// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5F5F00 / 0x5F6B60 / 0x5F6B90. ObjectClass member
//   offsets come from the committed P2 spine (match/_layout/object_class.h):
//   IsOnMap @0x74 (`MOV AL,[ECX+0x74]`) and OnBridge @0x8C
//   (`MOV CL,[ESI+0x8C]`). Method names cross-checked against YRpp
//   (consult-only, no LICENSE).
//
// ObjectClass height/level accessors — the three leaves that decide whether an
// object counts as on the ground, in the air, or how high its cell sits.
#ifndef GG_MATCH_CORE_OBJECT_CLASS_LEVEL_METHODS_H
#define GG_MATCH_CORE_OBJECT_CLASS_LEVEL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"

#include "../_layout/cell_class.h"
#include "flight_level.h"

// Reuse the shared CellClass layout for the signed terrain-level byte read
// by 0x5F5F00. The primary slot views model only the observed call ABI.
GG_STATIC_ASSERT(offsetof(CellClass, Level) == 0x11B);
GG_STATIC_ASSERT(offsetof(ObjectClass, OnBridge) == 0x8C);
GG_STATIC_ASSERT(offsetof(ObjectClass, IsOnMap) == 0x74);
typedef CellClass* (__fastcall* ObjectLevelGetCell)(const ObjectClass*);
typedef int (__fastcall* ObjectLevelGetHeight)(const ObjectClass*);
struct ObjectLevelVtablePrefix
{
    char unknown_00[0x1BC];
    ObjectLevelGetCell GetCell;
    char unknown_1C0[0x1C8 - 0x1C0];
    ObjectLevelGetHeight GetHeight;
};
GG_STATIC_ASSERT(sizeof(ObjectLevelGetCell) == 4);
GG_STATIC_ASSERT(sizeof(ObjectLevelGetHeight) == 4);
GG_STATIC_ASSERT(offsetof(ObjectLevelVtablePrefix, GetCell) == 0x1BC);
GG_STATIC_ASSERT(offsetof(ObjectLevelVtablePrefix, GetHeight) == 0x1C8);

#endif  // GG_MATCH_CORE_OBJECT_CLASS_LEVEL_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5F5F00 / 0x5F6B60 / 0x5F6B90. ObjectClass member
//   offsets come from the committed P2 spine (match/_layout/object_class.h):
//   IsOnMap @0x74 (`MOV AL,[ECX+0x74]`) and OnBridge @0x8C
//   (`MOV CL,[ESI+0x8C]`). Method names cross-checked against YRpp
//   ObjectClass.h (consult-only, no LICENSE).
//
// ObjectClass height/level accessors — the three leaves that decide whether an
// object counts as on the ground, in the air, or how high its cell sits.
#ifndef GG_MATCH_CORE_OBJECT_CLASS_LEVEL_METHODS_H
#define GG_MATCH_CORE_OBJECT_CLASS_LEVEL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"

// CellClass — only the terrain level byte is needed here. GetCellLevel reads it
// with `MOVSX EDX,byte ptr [EAX+0x11B]`, so it is a *signed* char.
struct CellClass
{
    char _pad00[0x11B];   // +0x0000
    char Level;           // +0x011B  (signed; MOVSX)
};
GG_STATIC_ASSERT(offsetof(CellClass, Level) == 0x11B);

// GLOBAL: GAMEMD 0x00AC13C8 — the flight-level constant in Leptons. Both
// predicates below compare an object's height against *twice* this value
// (`MOV ECX,[0xAC13C8]; LEA EDX,[ECX+ECX*1]`), which is the boundary between
// "on the floor" and "in the air".
extern int FlightLevel;

// Two ObjectClass virtuals are dispatched through the primary vtable rather
// than implemented here. Both are modelled as __fastcall function pointers so
// VC6 reproduces the indirect __thiscall (ECX = this, no stack args) exactly,
// matching `MOV EAX,[ECX]; CALL [EAX+slot]`.
//   +0x1BC  GetCell()   -> CellClass*   (CALL [EAX+0x1BC] @0x5F5F05)
//   +0x1C8  GetHeight() -> int          (CALL [EAX+0x1C8] @0x5F6B69)
typedef CellClass* (__fastcall* GetCellFunc)(const ObjectClass*);
typedef int        (__fastcall* GetHeightFunc)(const ObjectClass*);

#define OBJ_GET_CELL(obj)   ((*(GetCellFunc*)(*(char**)(obj) + 0x1bc))(obj))
#define OBJ_GET_HEIGHT(obj) ((*(GetHeightFunc*)(*(char**)(obj) + 0x1c8))(obj))

// The three matched leaves are declared on ObjectClass itself, in the committed
// P2 spine (match/_layout/object_class.h): GetCellLevel @0x5F5F00,
// IsOnFloor @0x5F6B60, IsInAir @0x5F6B90.

#endif  // GG_MATCH_CORE_OBJECT_CLASS_LEVEL_METHODS_H

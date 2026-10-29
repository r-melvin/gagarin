// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x578AD0: the cell index is `MOVSX [ECX+2] << 9 +
//   MOVSX [ECX]` bounded by the constant 0x40000 and looked up through the
//   global cell array at 0x87F924 (= Map instance 0x87F7E8 + 0x13C); the
//   fallback cell is the global at 0xABDC50 whose coords sit at 0xABDC74
//   (+0x24). On the cell, `[EAX+0xE4]` is the first object; on each object
//   `[EDX+0x2C]` is the WhatAmI slot, `[ESI+0x30]` the next-object link,
//   `[ESI+0x21C]` the owning house and `[ESI+0x520]` the type, whose byte
//   at +0x16B7 gates the whole check. Names cross-checked against YRpp
//   MapClass::MakeTraversable / BuildingClass::MakeTraversable.
#ifndef GG_MATCH_MAP_MAP_CLASS_TRAVERSABLE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_TRAVERSABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../movement/loco_interfaces.h"

struct DropPodObjectView;

// 2D short cell coordinate (sizeof == 4): X@0, Y@2.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

struct Vtbl_00578AD0;

// The object view: vtable, the next-object chain link, the owning house and
// the type (the last two are only read once WhatAmI says "building").
struct HouseClass_00578AD0;
struct Type_00578AD0
{
    char _pad000[0x16B7];         // +0x0000
    char At_16B7;                 // +0x16B7  gate-like flag
};
GG_STATIC_ASSERT(offsetof(Type_00578AD0, At_16B7) == 0x16B7);

struct Obj_00578AD0
{
    Vtbl_00578AD0*      Vtbl;     // +0x0000
    char                _pad004[0x2C];   // +0x0004
    Obj_00578AD0*       NextObject;      // +0x0030
    char                _pad034[0x1E8];  // +0x0034
    HouseClass_00578AD0* Owner;          // +0x021C
    char                _pad220[0x300];  // +0x0220
    Type_00578AD0*      Type;            // +0x0520

    // FUNCTION: GAMEMD 0x452540 (decl; reloc) — BuildingClass::MakeTraversable.
    bool MakeTraversable();
    // FUNCTION: GAMEMD 0x4525F0 (decl; reloc) — BuildingClass::IsTraversable.
    bool IsTraversable();
};
GG_STATIC_ASSERT(offsetof(Obj_00578AD0, NextObject) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_00578AD0, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(Obj_00578AD0, Type) == 0x520);

typedef int (Obj_00578AD0::*Fn2C_00578AD0)();

struct Vtbl_00578AD0
{
    char _pad000[0x2C];           // +0x0000
    Fn2C_00578AD0 WhatAmI;        // +0x002C
};
GG_STATIC_ASSERT(offsetof(Vtbl_00578AD0, WhatAmI) == 0x2C);

struct HouseClass_00578AD0
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x4F9A90 (decl; reloc) — HouseClass::IsAlliedWith(ObjectClass const*).
    bool IsAlliedWith(Obj_00578AD0 const* object) const;
};

struct CellClass_00578AD0
{
    char           _pad000[0x24];   // +0x0000
    CellStruct     MapCoords;       // +0x0024
    char           _pad028[0xBC];   // +0x0028
    Obj_00578AD0*  FirstObject;     // +0x00E4
};
GG_STATIC_ASSERT(offsetof(CellClass_00578AD0, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass_00578AD0, FirstObject) == 0xE4);

// GLOBAL: GAMEMD 0xABDC50 — MapClass::InvalidCell (its MapCoords is 0xABDC74).
extern CellClass_00578AD0 InvalidCell;

class MapView_578AD0
{
public:
    char                 _pad000[0x13C];   // +0x0000
    CellClass_00578AD0** Cells;            // +0x013C

    // FUNCTION: GAMEMD 0x578AD0
    bool MakeTraversable(Obj_00578AD0 const* visitor, CellStruct const& cell) const;
    // Address-bound method declarations used by DropPod's exact call sites.
    // Signatures are ABI views for those calls, not a complete MapClass API.
    // FUNCTION: GAMEMD 0x578080 (decl; reloc)
    int GetHeightAt(const LocoCoord* coord);
    // FUNCTION: GAMEMD 0x5785F0 (decl; reloc)
    bool IsWithinUsableArea(LocoCoord* coord);
    // FUNCTION: GAMEMD 0x565730 (decl; reloc)
    DropPodObjectView* GetCellAt(const LocoCoord& coord);
    DropPodObjectView* GetCellAt(const LocoCoord* coord);
};
GG_STATIC_ASSERT(offsetof(MapView_578AD0, Cells) == 0x13C);

// GLOBAL: GAMEMD 0x87F7E8 — the map instance; its Cells member is 0x87F924.
extern MapView_578AD0 MapInstance;

#endif  // GG_MATCH_MAP_MAP_CLASS_TRAVERSABLE_METHODS_H

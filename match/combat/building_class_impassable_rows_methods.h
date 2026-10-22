// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x458A00:
//     * the cell argument is handed to CALL 0x47C520 in ECX and its result
//       compared against `this` (`CMP EAX,ESI`), which types the argument as
//       a CellClass and `this` as a BuildingClass;
//     * `[ESI+0x520]` is the building's type pointer (sizeof(TechnoClass) is
//       0x520, so it is BuildingClass's first own member);
//     * `CMP dword ptr [EAX+0x1620],-1` — an int on the building type;
//     * `MOV CL,byte ptr [EAX+0x16AB]` — a bool on the building type;
//     * `MOV EAX,dword ptr [ESI+0x2E4]` — a pointer on TechnoClass, tested
//       for non-null only;
//     * `CALL dword ptr [EAX+0x1B8]` with a pushed out-pointer — the
//       map-coords slot already pinned by 0x457A10 and 0x43E7B0 in this tree;
//     * `MOVSX EDI,word ptr [EDI+0x24]` — the cell's own map coordinate,
//       AbstractClass being 0x24 bytes so MapCoords is CellClass's first own
//       member, and the X half is the low word.
//   The type-member names (NumberImpassableRows at 0x1620, Bunker at 0x16AB)
//   and TechnoClass::BunkerLinkedItem at 0x2E4 were cross-checked against
//   YRpp
//   (every offset above is re-derived from the user's binary).
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_IMPASSABLE_ROWS_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_IMPASSABLE_ROWS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// 2D short cell coordinate (sizeof == 4): X@0, Y@2.
struct CellStruct_00458A00
{
    short X;  // +0x00
    short Y;  // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct_00458A00) == 4);

struct BuildingClass_00458A00;

// CellClass — its own map coordinate and the building-content lookup.
struct CellClass_00458A00
{
    char                _pad000[0x24];   // +0x0000  AbstractClass
    CellStruct_00458A00 MapCoords;       // +0x0024

    // FUNCTION: GAMEMD 0x47C520 (decl; reloc) — CellClass::GetBuilding.
    BuildingClass_00458A00* GetBuilding() const;
};
GG_STATIC_ASSERT(offsetof(CellClass_00458A00, MapCoords) == 0x24);

// BuildingTypeClass — only the two members this predicate reads.
struct BuildingType_00458A00
{
    char _pad000[0x1620];                 // +0x0000
    int  NumberImpassableRows;            // +0x1620
    char _pad1624[0x16AB - 0x1624];       // +0x1624
    char Bunker;                          // +0x16AB
};
GG_STATIC_ASSERT(offsetof(BuildingType_00458A00, NumberImpassableRows) == 0x1620);
GG_STATIC_ASSERT(offsetof(BuildingType_00458A00, Bunker)               == 0x16AB);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_00458A00;

struct BuildingClass_00458A00
{
    Vtbl_00458A00*          Vtbl;              // +0x0000
    char                    _pad004[0x2E0];    // +0x0004
    BuildingClass_00458A00* BunkerLinkedItem;  // +0x02E4
    char                    _pad2E8[0x238];    // +0x02E8
    BuildingType_00458A00*  Type;              // +0x0520

    // FUNCTION: GAMEMD 0x458A00
    bool IsCellImpassable(CellClass_00458A00* cell);
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00458A00, BunkerLinkedItem) == 0x2E4);
GG_STATIC_ASSERT(offsetof(BuildingClass_00458A00, Type)             == 0x520);

typedef CellStruct_00458A00* (BuildingClass_00458A00::*Fn1B8_00458A00)(
    CellStruct_00458A00* out);

struct Vtbl_00458A00
{
    char            _pad000[0x1B8];   // +0x0000
    Fn1B8_00458A00  GetMapCoords;     // +0x01B8
};
GG_STATIC_ASSERT(offsetof(Vtbl_00458A00, GetMapCoords) == 0x1B8);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_IMPASSABLE_ROWS_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x487D70 (derivation in the RE dossier,
//   docs/decomp_spec/re_findings/next_targets_2026-08-07.md §9). The jumpjet
//   occupant slot is CellClass +0xE0; 0x4E00B0 is FootClass::Jumpjet_OccupyCell
//   and 0x0089E748 the coordinate global used when clearing.
#ifndef GG_MATCH_MAP_CELL_CLASS_JUMPJET_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_JUMPJET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4); passed by value as a single dword.
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// The AbstractClass flag word at +0x14 (an int, as in match/_layout/
// abstract_class.h). Bit 2 (mask 4) marks a FootClass-derived object.
#define ABSFLAGS_ISFOOT 4
// Retail RTTI 0x817AF8 establishes the class key; public access preserves this ABI view.
class ObjectClass
{
public:
    char _pad00[0x14];                 // +0x0000
    int  AbstractFlags;                // +0x0014
};
GG_STATIC_ASSERT(offsetof(ObjectClass, AbstractFlags) == 0x14);
// FootClass::Jumpjet_OccupyCell @0x4E00B0 — __fastcall with the object in ECX
// and the cell coordinate pushed. Declared only; relocation-normalised.
void __fastcall Jumpjet_OccupyCell(ObjectClass* object, CellStruct coords);

// GLOBAL: GAMEMD 0x0089E748 — the coordinate handed over when a cell releases
// its jumpjet occupant.
extern CellStruct JumpjetClearCoords;

struct CellClass
{
    char         _pad00[0x24];          // +0x0000
    CellStruct   MapCoords;             // +0x0024
    char         _pad28[0xE0 - 0x28];   // +0x0028
    ObjectClass* Jumpjet;               // +0x00E0

    bool TryAssignJumpjet(ObjectClass* object);   // GAMEMD 0x487D70
};
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, Jumpjet)   == 0xE0);

#endif  // GG_MATCH_MAP_CELL_CLASS_JUMPJET_METHODS_H

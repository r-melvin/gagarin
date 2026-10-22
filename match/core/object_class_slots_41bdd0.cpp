// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// ObjectClass bodies for primary-table (0x7EF060) slots 41, 43, 45, 51, 52,
// 76, 98 and 110, emitted together at 0x41BDD0..0x41BEDC. Slot numbers come from
// the RTTI-located table; names are placeholders (object_class.h).
#include "../_layout/object_class.h"

// CellStruct — 2D short cell coordinate (sizeof = 4). Self-guarded for reuse.
#ifndef GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);
#endif  // GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED


// FUNCTION: GAMEMD 0x41BDD0
CoordStruct ObjectClass::vf_41()
{
    return vf_18();
}

// FUNCTION: GAMEMD 0x41BE00
CoordStruct ObjectClass::vf_43()
{
    return vf_18();
}

// FUNCTION: GAMEMD 0x41BE30
CoordStruct ObjectClass::vf_45(int a1)
{
    return vf_18();
}

// FUNCTION: GAMEMD 0x41BE60
int ObjectClass::vf_51(int a1)
{
    return 0;
}

// FUNCTION: GAMEMD 0x41BE70
int ObjectClass::vf_52(int a1)
{
    return 0;
}

// FUNCTION: GAMEMD 0x41BE80
void ObjectClass::vf_76(int a1)
{
}

// FUNCTION: GAMEMD 0x41BE90
void ObjectClass::vf_98(int a1)
{
}

// FUNCTION: GAMEMD 0x41BEA0
// The cell under Location: each lepton coordinate divided by 256.
CellStruct ObjectClass::vf_110()
{
    CellStruct cell;
    cell.X = (short)(Location.X / 256);
    cell.Y = (short)(Location.Y / 256);
    return cell;
}

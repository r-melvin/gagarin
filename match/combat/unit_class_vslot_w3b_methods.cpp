// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   More UnitClass virtual overrides read off retail gamemd.exe v1.001 (vtable 0x7F5C70).
//   Functions are in ascending retail address order.

#include "../_layout/unit_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/house_class.h"

// A house seen only through the dropped-flag handler the unit calls when it lets go of a flag.
struct UnitFlagHouse
{
    // FUNCTION: GAMEMD 0x4FBF60 (decl; reloc) -- put the dropped flag down at a cell.
    void FUN_004FBF60(const CellStruct& cell, int closeTo);
};
// GLOBAL: GAMEMD 0xA8022C -- HouseClass::Array.Items.
extern UnitFlagHouse** DAT_00A8022C;

// FUNCTION: GAMEMD 0x738890
// Maps the object kind in question to a target class, then defers to the foot test unless
// the unit is aimed at itself in a way that makes no sense or is berserk.
bool UnitClass::vf_81(int a1, int a2, int a3)
{
    int type = vf_29(a2, a3);
    int m = a1;
    if (a1 != type) {
        m = type;
        switch (type) {
        case 3:
            m = 1;
            goto done;
        case 9:
        case 0x10:
            goto five;
        }
    }
    if (m == 0x1b || m == 0x1d) {
five:
        m = 5;
    }
done:
    if (a2 == (int)this && (m == 2 || m == 5)) {
        return false;
    }
    if (Berzerk) {
        return false;
    }
    return FootClass::vf_81(m, a2, a3);
}

// FUNCTION: GAMEMD 0x738910
// PARTIAL: 85.4% -- identical instruction multiset; retail keeps the third and fourth
// arguments in EBX/EDI the other way round (variants with locals and nested ifs tried).
// Refuses when deployed and the unit's own check says 2, or when berserk.
bool UnitClass::vf_80(int a1, int a2, int a3, int a4)
{
    if (Deployed && vf_28(a2, 0, a4) == 2) {
        return false;
    }
    if (Berzerk) {
        return false;
    }
    return FootClass::vf_80(a1, a2, a3, a4);
}

// FUNCTION: GAMEMD 0x7440B0
// Lets go of a carried flag, dropping it at the unit's cell.
bool UnitClass::vf_53()
{
    if (FootClass::vf_53()) {
        if (FlagHouseIndex != -1) {
            UnitFlagHouse** slot = &DAT_00A8022C[FlagHouseIndex];
            (*slot)->FUN_004FBF60(vf_110(), 0);
            FlagHouseIndex = -1;
        }
        return true;
    }
    return false;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Small ObjectTypeClass slot bodies (retail table 0x7EF2D8), in retail address
// order. 0x428E40 sits in the address range of the AnimTypeClass unit, the
// others in the ObjectTypeClass unit (0x5F75B0..). ObjectTypeClass is declared
// in _layout/object_type_class.h.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy

#include "../_layout/object_type_class.h"

// GLOBAL: GAMEMD 0xAC1474 -- this unit's copy of a header height constant.
extern int DAT_00AC1474;

// FUNCTION: GAMEMD 0x428E40
int ObjectTypeClass::vf_28()
{
    return -1;
}

// FUNCTION: GAMEMD 0x5F75B0
int ObjectTypeClass::vf_29()
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F75E0
CoordStruct ObjectTypeClass::vf_31()
{
    CoordStruct coord;
    coord.X = 256;
    coord.Y = 256;
    coord.Z = DAT_00AC1474 * 2;
    return coord;
}

// FUNCTION: GAMEMD 0x5F7610
int ObjectTypeClass::vf_33(int a1)
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F7620
int ObjectTypeClass::vf_34()
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F7630
int ObjectTypeClass::vf_38()
{
    return 0;
}

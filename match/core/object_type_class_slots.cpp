// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Small ObjectTypeClass slot bodies (retail table 0x7EF2D8), in retail address
// order. 0x428E40 sits in the address range of the AnimTypeClass unit, the
// others in the ObjectTypeClass unit (0x5F75B0..). ObjectTypeClass is declared
// in _layout/object_type_class.h.

#include "../_layout/object_type_class.h"
#include "../_layout/cell.h"

// GLOBAL: GAMEMD 0xAC1474 -- this unit's copy of a header height constant.
extern int DAT_00AC1474;

// FUNCTION: GAMEMD 0x428E40
int ObjectTypeClass::vf_28()
{
    return -1;
}

// FUNCTION: GAMEMD 0x5F7320
ObjectTypeClass::ObjectTypeClass(const AbstractNoInit& noInit)
    : AbstractTypeClass(noInit), Image(0), MainVoxel(noInit), TurretVoxel(noInit), BarrelVoxel(noInit), ImageFile(noInit), AlphaImageFile(noInit)
{
}

// FUNCTION: GAMEMD 0x5F75B0
int ObjectTypeClass::vf_29()
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F75C0
CoordStruct ObjectTypeClass::vf_30()
{
    CoordStruct coord;
    coord.X = 10;
    coord.Y = 10;
    coord.Z = 10;
    return coord;
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
int ObjectTypeClass::vf_33(HouseClass*)
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F7620
int ObjectTypeClass::vf_34()
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F7630
SHPStruct* ObjectTypeClass::vf_38()
{
    return 0;
}

// Function-local static of slot 36: two cells, (0, 0) and (0x7FFF, 0x7FFF), built through temporaries; the
// empty destructor is registered with atexit (retail 0x5F76A0 is a lone RET).
struct Range_005F7640 {
    CellStruct cells[2];
    Range_005F7640()
    {
        CellStruct low;
        low.X = 0;
        low.Y = 0;
        cells[0] = low;
        CellStruct high;
        high.X = 0x7FFF;
        high.Y = 0x7FFF;
        cells[1] = high;
    }
    ~Range_005F7640() {}
};

// FUNCTION: GAMEMD 0x5F7640
CellStruct* ObjectTypeClass::vf_36(int a1)
{
    static Range_005F7640 range;
    return range.cells;
}

// FUNCTION: GAMEMD 0x5F9970
HRESULT __stdcall ObjectTypeClass::GetSizeMax(ULARGE_INTEGER* size)
{
    HRESULT result = AbstractClass::GetSizeMax(size);
    if (result >= 0)
        result = S_OK;
    return result;
}

// SYNTHETIC: GAMEMD 0x5F9AE0
// Compiler-generated scalar deleting destructor for ObjectTypeClass.

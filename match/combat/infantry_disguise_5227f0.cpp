// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x5227F0 in the user's gamemd.exe v1.001 (InfantryClass vtable slot 50),
//   instruction-for-instruction the same shape as the UnitClass slot 50 body at 0x746750.
//   Sibling of Infantry.CPP (code range 0x517840-0x52348f) so its address-named views stay local.
//   Address index: 0x5227F0.

#include "../_layout/infantry_class.h"
#include "../_layout/house_class.h"
#include "../_layout/geometry2d.h"

// A cell record, as far as the one test the disguise check makes.
struct CellView_005227F0
{
    // FUNCTION: GAMEMD 0x4870F0 (decl; reloc)
    bool FUN_004870F0(int houseIndex);
};

// The map object, as far as the cell lookup.
struct MapView_005227F0
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    CellView_005227F0* FUN_005657A0(CellStruct* cell);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern MapView_005227F0 DAT_0087F7E8_005227F0;

// A house, as far as its alliance test.
struct HouseView_005227F0
{
    // FUNCTION: GAMEMD 0x4F9A50 (decl; reloc)
    bool FUN_004F9A50(HouseClass* other);
};

inline CellStruct CoordToCell_005227F0(const CoordStruct& where)
{
    CellStruct result;
    result.X = where.X / 256;
    result.Y = where.Y / 256;
    return result;
}

// FUNCTION: GAMEMD 0x5227F0
// Whether the house is fooled by this infantryman's disguise at its current cell.
bool InfantryClass::vf_50(HouseClass* house)
{
    if (vf_49()) {
        CellStruct cell = CoordToCell_005227F0(vf_18());
        CellView_005227F0* cellRecord = DAT_0087F7E8_005227F0.FUN_005657A0(&cell);
        if (!reinterpret_cast<HouseView_005227F0*>(Owner)->FUN_004F9A50(house) &&
            !cellRecord->FUN_004870F0(house->ArrayIndex)) {
            HouseClass* disguised = DisguisedAsHouse;
            if (disguised == house || !disguised ||
                reinterpret_cast<HouseView_005227F0*>(house)->FUN_004F9A50(disguised))
                return true;
        }
    }
    return false;
}

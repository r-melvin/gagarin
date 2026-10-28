// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   UnitClass overrides read off retail gamemd.exe v1.001 (vtable 0x7F5C70), round 16. The
//   bodies sit on UnitView_r16, a plain derived view of the canonical UnitClass, so no shared
//   header changes. Functions are in ascending retail address order.
//   Address index: 0x744640 (slot 13), 0x746750 (slot 50).

#include "../_layout/unit_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../_layout/house_class.h"
#include "../_layout/object_type_class.h"

// A COM-style interface pointer called through its raw table with the pointer on the stack.
struct UnitComObj_r16;
struct UnitComVtbl_r16
{
    void* slots[4];
    int (__stdcall* Slot4)(UnitComObj_r16* self);   // +0x10
};
struct UnitComObj_r16
{
    UnitComVtbl_r16* lpVtbl;
};

// A type or unit object, as far as its primary table slot 11.
struct UnitKindView_r16
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual void vf_8();
    virtual void vf_9();
    virtual void vf_10();
    virtual int vf_11();
};

// The checksum sink, as far as the raw one-byte add (the byte goes through unchanged).
struct UnitCrcView_r16
{
    // FUNCTION: GAMEMD 0x4A1CA0 (decl; reloc)
    void FUN_004A1CA0(unsigned char value);
};

// A cell record, as far as the one test the disguise check makes.
struct UnitCellView_r16
{
    // FUNCTION: GAMEMD 0x4870F0 (decl; reloc)
    bool FUN_004870F0(int houseIndex);
};

// The map object, as far as the cell lookup.
struct UnitMapView_r16
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    UnitCellView_r16* FUN_005657A0(CellStruct* cell);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern UnitMapView_r16 DAT_0087F7E8_r16;

// A house, as far as its alliance test.
struct UnitHouseView_r16
{
    // FUNCTION: GAMEMD 0x4F9A50 (decl; reloc)
    bool FUN_004F9A50(HouseClass* other);
};

inline CellStruct UnitCoordToCell_r16(const CoordStruct& where)
{
    CellStruct result;
    result.X = where.X / 256;
    result.Y = where.Y / 256;
    return result;
}

class UnitView_r16 : public UnitClass
{
public:
    void FUN_00744640(Obj_004A1D30* crc);
    bool FUN_00746750(HouseClass* house);
};

// FUNCTION: GAMEMD 0x744640
// Feeds the unit's type, follower and flag state to the checksum.
void UnitView_r16::FUN_00744640(Obj_004A1D30* crc)
{
    FootClass::vf_13(crc);
    crc->FUN_004A1D50(static_cast<UnitKindView_r16*>(Type)->vf_11());
    UnitComObj_r16* typeIface = reinterpret_cast<UnitComObj_r16*>((char*)Type + 4);
    crc->FUN_004A1D50(typeIface->lpVtbl->Slot4(typeIface));
    if (FollowerCar) {
        UnitComObj_r16* followerIface = reinterpret_cast<UnitComObj_r16*>((char*)FollowerCar + 4);
        crc->FUN_004A1D50(followerIface->lpVtbl->Slot4(followerIface));
    }
    crc->FUN_004A1D50(FlagHouseIndex);
    UnitCrcView_r16* sink = reinterpret_cast<UnitCrcView_r16*>(crc);
    sink->FUN_004A1CA0(IsFollowerCar);
    sink->FUN_004A1CA0(Unloading);
    sink->FUN_004A1CA0(IsHarvesting);
    sink->FUN_004A1CA0(ShouldScatterInNextIdle);
}

// FUNCTION: GAMEMD 0x746750
// Whether the house is fooled by this unit's disguise at its current cell.
bool UnitView_r16::FUN_00746750(HouseClass* house)
{
    if (vf_49()) {
        CellStruct cell = UnitCoordToCell_r16(vf_18());
        UnitCellView_r16* cellRecord = DAT_0087F7E8_r16.FUN_005657A0(&cell);
        if (!reinterpret_cast<UnitHouseView_r16*>(Owner)->FUN_004F9A50(house) &&
            !cellRecord->FUN_004870F0(house->ArrayIndex)) {
            HouseClass* disguised = DisguisedAsHouse;
            if (disguised == house || !disguised ||
                reinterpret_cast<UnitHouseView_r16*>(house)->FUN_004F9A50(disguised))
                return true;
        }
    }
    return false;
}

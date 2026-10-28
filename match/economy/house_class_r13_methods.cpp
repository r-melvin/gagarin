// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, slot displacements and call targets read numerically off the
//   user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   addresses below.
//
// HouseClass members that walk the house's own vectors back to front, ordered
// ascending by retail address.
#include "../_layout/house_class.h"
#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../core/guarded_getter_methods.h"
#include "../_rt/gg_vslot.h"

// Vtable slot +0x3D4 of a building: run with the house and a flag. The receiver
// is a single-inheritance view so the member pointer keeps its 4-byte form.
struct BuildingVtbl_R13;
struct BuildingView_R13
{
    BuildingVtbl_R13* Vtbl;
    void Slot3D4(HouseClass* house, int flag);
};
typedef void (BuildingView_R13::*BuildingSlot3D4)(HouseClass* house, int flag);
struct BuildingVtbl_R13
{
    char            _pad[0x3D4];
    BuildingSlot3D4 At_3D4;
};

// FUNCTION: GAMEMD 0x50D250
void HouseClass::FUN_0050D250(unsigned delta)
{
    int count = *(int*)((char*)this + 0x5714);
    for (int i = count - 1; i >= 0; i--) {
        char* nodes = *(char**)((char*)this + 0x5708);
        ((Obj_0042E600*)(nodes + i * 16))->FUN_0042E6D0(*(ShortPair*)&delta);
    }
}

// FUNCTION: GAMEMD 0x50D290
// Hands every building of `other` to this house, remembering the original owner.
void HouseClass::FUN_0050D290(HouseClass* other)
{
    for (int i = other->Buildings.Count - 1; i >= 0; i--) {
        BuildingClass* building = other->Buildings.Items[i];
        BuildingView_R13* view = (BuildingView_R13*)building;
        (view->*view->Vtbl->At_3D4)(this, 0);
        building->OriginallyOwnedByHouse = other;
        building->MindControlledByHouse = this;
    }
}

// FUNCTION: GAMEMD 0x50D2D0
// Gives back every building that `other` originally owned.
void HouseClass::FUN_0050D2D0(HouseClass* other)
{
    for (int i = Buildings.Count - 1; i >= 0; i--) {
        BuildingClass* building = Buildings.Items[i];
        if (building->OriginallyOwnedByHouse == other) {
            BuildingView_R13* view = (BuildingView_R13*)building;
            (view->*view->Vtbl->At_3D4)(other, 0);
            building->OriginallyOwnedByHouse = 0;
            building->MindControlledByHouse = 0;
        }
    }
}

// GLOBAL: GAMEMD 0xA8022C -- HouseClass::Array.Items
extern HouseClass** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA80238 -- HouseClass::Array.Count
extern int DAT_00A80238;
// GLOBAL: GAMEMD 0x8243C8 -- cell offsets of the nine threat taps
extern int DAT_008243C8[9];
// GLOBAL: GAMEMD 0x8243EC -- falloff shifts of the nine threat taps
extern int DAT_008243EC[9];

// FUNCTION: GAMEMD 0x4FA2E0
// Adds (or removes, for a negative amount) a falloff share of `amount` to
// nine threat cells around `index`, never letting a cell go below zero.
void HouseClass::FUN_004FA2E0(int index, int amount)
{
    int negative;
    if (amount < 0) {
        amount = -amount;
        negative = 1;
    } else {
        negative = 0;
    }
    int k = 0;
    int taps = 9;
    do {
        int share = amount >> DAT_008243EC[k];
        int* cell = (int*)ThreatPosedEstimates + (DAT_008243C8[k] + index);
        if (negative)
            *cell -= share;
        else
            *cell += share;
        if (*cell < 0)
            *cell = 0;
        k++;
        taps--;
    } while (taps);
}

// HouseClass::IsAlliedWith (0x4F9A50), expanded inline here.
static inline bool IsAlliedWith_R13(const HouseClass* self, const HouseClass* house)
{
    if (house) {
        if (house == self) return true;
        if (house->ArrayIndex == self->ArrayIndex) return true;
        if (house->ArrayIndex != -1) {
            bool allied = (self->Allies & (1 << house->ArrayIndex)) != 0;
            return allied;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x4FBD00
bool HouseClass::FUN_004FBD00(int typeIndex)
{
    for (int i = 0; i < DAT_00A80238; i++) {
        HouseClass* house = DAT_00A8022C[i];
        if (house && house != this && !IsAlliedWith_R13(this, house)) {
            if (house->ActiveBuildingTypes.FUN_0049FAE0(typeIndex) > 0)
                return true;
        }
    }
    return false;
}

// GLOBAL: GAMEMD 0xA83CE4
extern void** DAT_00A83CE4;
// GLOBAL: GAMEMD 0xA8B21C
extern void** DAT_00A8B21C;
// GLOBAL: GAMEMD 0xA83C6C
extern void** DAT_00A83C6C;
// GLOBAL: GAMEMD 0xA8E34C
extern void** DAT_00A8E34C;

// FUNCTION: GAMEMD 0x4FBD80
// The type this house is currently producing, found through the per-class
// production index; null when nothing is being produced.
void* HouseClass::FUN_004FBD80(int rtti, int unused)
{
    switch (rtti) {
    case 2:
    case 3:
        if (ProducingAircraftTypeIndex != -1)
            return DAT_00A8B21C[ProducingAircraftTypeIndex];
        break;
    case 1:
    case 40:
        if (ProducingUnitTypeIndex != -1)
            return DAT_00A83CE4[ProducingUnitTypeIndex];
        break;
    case 15:
    case 16:
        if (ProducingInfantryTypeIndex != -1)
            return DAT_00A8E34C[ProducingInfantryTypeIndex];
        break;
    case 6:
    case 7:
        if (ProducingBuildingTypeIndex != -1)
            return DAT_00A83C6C[ProducingBuildingTypeIndex];
        break;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5005B0
// Marks the class of object `rtti` as needing a recheck. Infantry falls
// through into the vehicle case, exactly as the retail code does.
void HouseClass::FUN_005005B0(int rtti, bool naval, int kind)
{
    switch (rtti) {
    case 15:
    case 16:
        InfantryType_53D1 = 1;
    case 1:
    case 40:
        if (naval)
            ShipType_53D3 = 1;
        else
            VehicleType_53D2 = 1;
        break;
    case 6:
    case 7:
        if (kind == 5)
            DefenseType_53D8 = 1;
        else
            BuildingType_53D4 = 1;
        break;
    case 2:
    case 3:
        AircraftType_53D0 = 1;
        break;
    }
}

// FUNCTION: GAMEMD 0x500660
// As 0x5005B0 but clearing the flag.
void HouseClass::FUN_00500660(int rtti, bool naval, int kind)
{
    switch (rtti) {
    case 15:
    case 16:
        InfantryType_53D1 = 0;
    case 1:
    case 40:
        if (naval)
            ShipType_53D3 = 0;
        else
            VehicleType_53D2 = 0;
        break;
    case 6:
    case 7:
        if (kind == 5)
            DefenseType_53D8 = 0;
        else
            BuildingType_53D4 = 0;
        break;
    case 2:
    case 3:
        AircraftType_53D0 = 0;
        break;
    }
}

// FUNCTION: GAMEMD 0x500700
unsigned char HouseClass::FUN_00500700(int rtti, bool naval, int kind)
{
    switch (rtti) {
    case 15:
    case 16:
        return InfantryType_53D1;
    case 1:
    case 40:
        if (naval)
            return ShipType_53D3;
        return VehicleType_53D2;
    case 6:
    case 7:
        if (kind == 5)
            return DefenseType_53D8;
        return BuildingType_53D4;
    case 2:
    case 3:
        return AircraftType_53D0;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5007A0
void HouseClass::FUN_005007A0(int rtti, bool naval, int kind, bool value)
{
    switch (rtti) {
    case 15:
    case 16:
        InfantryType_53D1 = value;
    case 1:
    case 40:
        if (naval)
            ShipType_53D3 = value;
        else
            VehicleType_53D2 = value;
        break;
    case 6:
    case 7:
        if (kind == 5)
            DefenseType_53D8 = value;
        else
            BuildingType_53D4 = value;
        break;
    case 2:
    case 3:
        AircraftType_53D0 = value;
        break;
    }
}

// FUNCTION: GAMEMD 0x500910
int HouseClass::FUN_00500910(int rtti, bool naval)
{
    int* count = 0;
    switch (rtti) {
    case 1:
    case 40:
        if (naval)
            count = &NumShipyards;
        else
            count = &NumWarFactories;
        break;
    case 2:
    case 3:
        count = &NumAirpads;
        break;
    case 15:
    case 16:
        count = &NumBarracks;
        break;
    case 6:
    case 7:
        count = &NumConYards;
        break;
    }
    if (count)
        return *count;
    return 0;
}

// FUNCTION: GAMEMD 0x4FD940
// 0 when the house is in mode 3 or owns a live, placed building whose type has a
// factory; otherwise 4.
int HouseClass::FUN_004FD940()
{
    if (AIMode != 3) {
        for (int i = 0; i < Buildings.Count; i++) {
            BuildingClass* building = Buildings.Items[i];
            if (building && building->IsAlive && !building->InLimbo && building->Type->Factory != 0)
                return 0;
        }
        return 4;
    }
    return 0;
}

struct Rules_R13
{
    char Pad_00[0x17D0];
    int  unknown_17D0;
};
GG_STATIC_ASSERT(offsetof(Rules_R13, unknown_17D0) == 0x17D0);
// GLOBAL: GAMEMD 0x8871E0 -- the rules object
extern Rules_R13* DAT_008871E0;

// FUNCTION: GAMEMD 0x4F9700
// Adds one unit of the given tiberium type to the weed storage up to `count`
// times, stopping once the storage reaches the rules capacity.
void HouseClass::FUN_004F9700(int count, int index)
{
    while (count > 0) {
        float capacity = (float)DAT_008871E0->unknown_17D0;
        if (!(OwnedWeed.GetTotalAmount() < capacity))
            return;
        OwnedWeed.AddAmount(1.0f, index);
        count--;
    }
}

// FUNCTION: GAMEMD 0x4F9670
// PARTIAL: 98.2% - one instruction differs: retail stores the zero for the best-room float
// from EBX (mov [esp+0xc],ebx), ours uses an immediate (variants tried: init order, late assign).
// The placed building whose type has storage and the most room left in it
// (capacity minus what it holds); null if there is none.
BuildingClass* HouseClass::FUN_004F9670()
{
    BuildingClass* best = 0;
    int i = 0;
    float bestRoom;
    int count = Buildings.Count;
    bestRoom = 0.0f;
    if (count > 0) {
        do {
            BuildingClass* building = Buildings.Items[i];
            if (building && building->IsOnMap) {
                int capacity = *(int*)((char*)building->Type + 0x800);
                if (capacity > 0) {
                    float room = (float)capacity - building->Tiberium.GetTotalAmount();
                    if (!best || room > bestRoom) {
                        bestRoom = room;
                        best = building;
                    }
                }
            }
            i++;
        } while (i < count);
    }
    return best;
}

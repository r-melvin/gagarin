// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   UnitTypeClass construction for loading, destruction and stream loading, read off retail
//   gamemd.exe v1.001 (vtable 0x7F6218). /Ob2: the scalar deleting destructor carries the
//   destructor body inline.
//   Construction, lifetime, and virtual overrides are ordered by retail address below.

#include <new.h>
#include <stdlib.h>
#include "../_layout/unit_type_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../_layout/unit_class.h"
#include "../_layout/facing_class.h"
#include "../_layout/rules_class.h"
#include "../core/randomizer.h"
#include "../core/vector_class_operations.h"

GG_STATIC_ASSERT(offsetof(UnitTypeClass, ArrayIndex) == 0xDF8);
GG_STATIC_ASSERT(sizeof(((UnitTypeClass*)0)->ArrayIndex) == 4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, MaxDimension) == 0x1EC);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->MaxDimension) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, RepairStep) == 0x16CC);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->RepairStep) == 4);

// GLOBAL: GAMEMD 0xB1D138 -- run-time derived z extent used by vf_31.
extern int DAT_00B1D138;

// GLOBAL: GAMEMD 0xA83CE0 -- the unit type registry.
extern DynamicVectorClass<UnitTypeClass*> DAT_00A83CE0;
// STRING: GAMEMD 0x81834C -- ".SHP".
extern const char STR_0081834C[];

// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- loads a shape file by path.
void* __fastcall FUN_005B40B0(const char* name, bool flag);

// GLOBAL: GAMEMD 0xA8B230 -- the scenario.
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;


// FUNCTION: GAMEMD 0x7472C0
UnitTypeClass::UnitTypeClass(const AbstractNoInit& noInit) : TechnoTypeClass(noInit)
{
}

// FUNCTION: GAMEMD 0x7472F0
UnitTypeClass::~UnitTypeClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A83CE0.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x7474B0
// Makes a unit of this type and places it in the middle of the cell, facing a random way.
bool UnitTypeClass::vf_32(const CellStruct* cell, HouseClass* house)
{
    UnitClass* unit = new UnitClass(this, house);
    if (unit) {
        DirStruct facing;
        facing.Raw = 0;
        int random = DAT_00A8B230->unknown_0218.Random();
        unsigned int bits = (facing.Whole & 0xFFFF00FF) | ((unsigned char)random << 8);
        CoordStruct coord;
        coord.X = cell->X * 256 + 128;
        coord.Y = cell->Y * 256 + 128;
        coord.Z = 0;
        return unit->vf_54(coord, (((bits >> 7) + 1) >> 1) & 0xFF);
    }
    return false;
}

// FUNCTION: GAMEMD 0x747560
// Create a UnitClass of this type for the given house.
ObjectClass* UnitTypeClass::vf_35(HouseClass* house)
{
    return new UnitClass(this, house);
}

// FUNCTION: GAMEMD 0x747590
// Footprint extent from the type's largest dimension, clamped to 60.
CoordStruct UnitTypeClass::vf_30()
{
    int v = MaxDimension;
    int x = v - v / 4;
    int z = v - v / 4;
    if (x >= 60) x = 60;
    if (z >= 60) z = 60;
    CoordStruct r;
    r.X = x; r.Y = x; r.Z = z;
    return r;
}

// FUNCTION: GAMEMD 0x7475D0
CoordStruct UnitTypeClass::vf_31()
{
    CoordStruct result;
    result.X = 0x100;
    result.Y = 0x100;
    result.Z = DAT_00B1D138 * 2;
    return result;
}

// FUNCTION: GAMEMD 0x747F20
// Member getter (dword). Vtable slot 45 of UnitTypeClass (RTTI).
int UnitTypeClass::vf_45()
{
    return RulesInstance->RepairStep;
}

// FUNCTION: GAMEMD 0x748010
// Reads the stream, rebuilds the object in place and reloads the alternate image shape.
HRESULT __stdcall UnitTypeClass::Load(IStream* pStm)
{
    HRESULT hr = TechnoTypeClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) UnitTypeClass(AbstractNoInit());
    FUN_005F8110();
    FUN_005F9070();
    if (AltImage) {
        char path[260];
        _makepath(path, 0, 0, AltImageFile, STR_0081834C);
        AltImage = (SHPStruct*)FUN_005B40B0(path, false);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x748160
int UnitTypeClass::vf_12()
{
    return 0xE78;
}

// FUNCTION: GAMEMD 0x748170
int UnitTypeClass::vf_11()
{
    return 0x28;
}

// FUNCTION: GAMEMD 0x748180
int UnitTypeClass::vf_16()
{
    return ArrayIndex;
}

// SYNTHETIC: GAMEMD 0x748190
// UnitTypeClass scalar deleting destructor (primary slot 8), the destructor expanded in place.

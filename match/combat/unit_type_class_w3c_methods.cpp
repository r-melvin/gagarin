// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   UnitTypeClass construction for loading, destruction and stream loading, read off retail
//   gamemd.exe v1.001 (vtable 0x7F6218). /Ob2: the scalar deleting destructor carries the
//   destructor body inline.
//   Address index: 0x7472C0 no-init ctor, 0x7472F0 dtor, 0x7474B0 vf_32, 0x748010 Load, 0x748190 deleting dtor.

#include <new.h>
#include <stdlib.h>
#include "../_layout/unit_type_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../_layout/unit_class.h"
#include "../core/randomizer.h"
#include "../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0xA83CE0 -- the unit type registry.
extern DynamicVectorClass<UnitTypeClass*> DAT_00A83CE0;
// STRING: GAMEMD 0x81834C -- ".SHP".
extern const char STR_0081834C[];

// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- loads a shape file by path.
void* __fastcall FUN_005B40B0(const char* name, bool flag);

// The scenario object, as far as the random number generator it carries.
struct UnitTypeScenarioView
{
    char unknown_00[0x218];
    Randomizer Random;   // +0x218
};
GG_STATIC_ASSERT(offsetof(UnitTypeScenarioView, Random) == 0x218);
// GLOBAL: GAMEMD 0xA8B230 -- the scenario.
extern UnitTypeScenarioView* DAT_00A8B230;

// A facing built from one random byte in the high half of the word, and rounded to eight bits.
struct UnitTypeFacing
{
    unsigned short Raw;
    unsigned short Padding;
};

// FUNCTION: GAMEMD 0x7472C0
UnitTypeClass::UnitTypeClass(const AbstractNoInit& noInit) : TechnoTypeClass(noInit)
{
}

// FUNCTION: GAMEMD 0x7474B0
// Makes a unit of this type and places it in the middle of the cell, facing a random way.
bool UnitTypeClass::vf_32(const CellStruct* cell, HouseClass* house)
{
    UnitClass* unit = new UnitClass(this, house);
    if (unit) {
        UnitTypeFacing facing;
        facing.Raw = 0;
        int random = DAT_00A8B230->Random.Random();
        unsigned int bits = (*(unsigned int*)&facing & 0xFFFF00FF) | ((unsigned char)random << 8);
        CoordStruct coord;
        coord.X = cell->X * 256 + 128;
        coord.Y = cell->Y * 256 + 128;
        coord.Z = 0;
        return unit->vf_54(coord, (((bits >> 7) + 1) >> 1) & 0xFF);
    }
    return false;
}

// FUNCTION: GAMEMD 0x7472F0
UnitTypeClass::~UnitTypeClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A83CE0.RemoveItem(this);
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

// SYNTHETIC: GAMEMD 0x748190
// UnitTypeClass scalar deleting destructor (primary slot 8), the destructor expanded in place.

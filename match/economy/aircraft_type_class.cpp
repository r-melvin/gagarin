// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The AircraftTypeClass block of retail .text (0x41C6A0..0x41D06F): three of
// the unit's run-time initialisers, the constructors and destructor and the
// primary-table slots 5, 8, 11, 12, 13, 16, 25, 31, 32, 40 and 41, plus
// ObjectTypeClass slot 39 which the unit emits, in retail address order.
// AircraftTypeClass is declared in _layout/aircraft_type_class.h.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT

#include <new.h>
#include "../_layout/aircraft_type_class.h"
#include "../platform/ccini_class_methods.h"
#include "../_layout/obj_004a1d30.h"
#include "../core/vector_class_operations.h"
#include "../movement/locomotion_load_support.h"
#include "../core/header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0x889EF0
extern double DAT_00889EF0;
// GLOBAL: GAMEMD 0x7E2828
const double DAT_007E2828 = 60.0;

// SYNTHETIC: GAMEMD 0x41C6D0
// GLOBAL: GAMEMD 0x889F50
double DAT_00889F50 = DAT_00889EF0 / DAT_007E2828;
// SYNTHETIC: GAMEMD 0x41C6F0
// GLOBAL: GAMEMD 0x889F30
double DAT_00889F30 = 1.0 / DAT_00889F50;
// SYNTHETIC: GAMEMD 0x41C870
// GLOBAL: GAMEMD 0x889F40
TuningCoordInit DAT_00889F40(128, 128, 0);

// GLOBAL: GAMEMD 0x889F58 -- this unit's copy of a header height constant.
extern int DAT_00889F58;
// GLOBAL: GAMEMD 0x887180 -- the art INI.
extern CCINIClass DAT_00887180;
// GLOBAL: GAMEMD 0x889F64 -- the empty default string.
extern const char DAT_00889F64[];

// FUNCTION: GAMEMD 0x428B80 (decl; reloc) -- __fastcall, the anim type for a name.
AnimTypeClass* FUN_00428B80(const char* name);

// The append to AircraftTypeClass::Array, in the free-function shape of the inlined
// DynamicVectorClass::AddItem (as TagPtrVector_AddItem in tag_class_destroy_methods.h).
static inline bool AircraftType_AddItem(DynamicVectorClass<AircraftTypeClass*>& v, AircraftTypeClass* item)
{
    if (v.Count >= v.Capacity)
    {
        if (!v.IsAllocated && v.Capacity != 0)
            return false;
        if (v.CapacityIncrement <= 0)
            return false;
        if (!v.SetCapacity(v.Capacity + v.CapacityIncrement, 0))
            return false;
    }
    int i = v.Count++;
    v.Items[i] = item;
    return true;
}

// FUNCTION: GAMEMD 0x41C8B0
AircraftTypeClass::AircraftTypeClass(const char* id)
    : TechnoTypeClass(id, 4), ArrayIndex(-1), Carryall(false), Rotors(false), CustomRotor(false),
      Landable(false), FlyBy(false), FlyBack(false), AirportBound(false), Fighter(false)
{
    vf_rtti_5();
    AircraftType_AddItem(Array, this);
    ArrayIndex = Array.FindItemIndex(this);
    bools_D20[0x18] = true;
    bools_D94[2] = true;
    bools_C8C[1] = false;
    RotCount = 32;
    Trailer = 0;
    SpawnDelay = 3;
    bools_D20[0x15] = false;
    bools_D20[0x16] = false;
    bools_D20[0x1B] = false;
    bools_D94[3] = false;
    bools_D20[0x0E] = false;
}

// FUNCTION: GAMEMD 0x41C9F0
AircraftTypeClass::AircraftTypeClass(const AbstractNoInit& noInit) : TechnoTypeClass(noInit)
{
}

// FUNCTION: GAMEMD 0x41CA20
AircraftTypeClass::~AircraftTypeClass()
{
    AnnounceExpiredPointer(1);
    Array.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x41CB50
bool AircraftTypeClass::vf_40()
{
    return false;
}

// FUNCTION: GAMEMD 0x41CB60
bool AircraftTypeClass::vf_41()
{
    return false;
}

// FUNCTION: GAMEMD 0x41CBE0
bool AircraftTypeClass::vf_32(int a1, int a2)
{
    return false;
}

// FUNCTION: GAMEMD 0x41CBF0
CoordStruct AircraftTypeClass::vf_31()
{
    CoordStruct coord;
    coord.X = 256;
    coord.Y = 256;
    coord.Z = DAT_00889F58 * 2;
    return coord;
}

// FUNCTION: GAMEMD 0x41CC20
bool AircraftTypeClass::vf_25(CCINIClass* ini)
{
    char buffer[128];
    ini->Reset();
    if (TechnoTypeClass::vf_25(ini)) {
        const char* section = ID;
        Landable = ini->FUN_005295F0(section, "Landable", Landable);
        AirportBound = ini->FUN_005295F0(section, "AirportBound", AirportBound);
        Fighter = ini->FUN_005295F0(section, "Fighter", Fighter);
        Carryall = ini->FUN_005295F0(section, "Carryall", Carryall);
        const char* art = ImageFile;
        Rotors = DAT_00887180.FUN_005295F0(art, "Rotors", Rotors);
        CustomRotor = DAT_00887180.FUN_005295F0(art, "CustomRotor", CustomRotor);
        AnimTypeClass* trailer = Trailer;
        if (DAT_00887180.FUN_00528A10(art, "Trailer", DAT_00889F64, buffer, sizeof(buffer))) {
            trailer = FUN_00428B80(buffer);
        }
        Trailer = trailer;
        SpawnDelay = DAT_00887180.FUN_005276D0(art, "SpawnDelay", SpawnDelay);
        FlyBy = ini->FUN_005295F0(section, "FlyBy", FlyBy);
        FlyBack = ini->FUN_005295F0(section, "FlyBack", FlyBack);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x41CDB0
void AircraftTypeClass::vf_13(Obj_004A1D30* crc)
{
    TechnoTypeClass::vf_13(crc);
    crc->FUN_004A1CA0(Rotors);
    crc->FUN_004A1CA0(CustomRotor);
    crc->FUN_004A1CA0(Landable);
    crc->FUN_004A1CA0(AirportBound);
    crc->FUN_004A1CA0(Fighter);
    crc->FUN_004A1D50(ArrayIndex);
}

// FUNCTION: GAMEMD 0x41CE20
HRESULT __stdcall AircraftTypeClass::Load(IStream* pStm)
{
    HRESULT hr = TechnoTypeClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) AircraftTypeClass(AbstractNoInit());
    DAT_00B0C110.FUN_006CF240((void**)&Trailer);
    FUN_005F8110();
    FUN_005F9070();
    return 0;
}

// FUNCTION: GAMEMD 0x41CF80
CoordStruct ObjectTypeClass::vf_27(const CoordStruct& coord)
{
    return coord;
}

// FUNCTION: GAMEMD 0x41CFA0
void* ObjectTypeClass::vf_39()
{
    return Image;
}

// FUNCTION: GAMEMD 0x41CFB0
int AircraftTypeClass::vf_11()
{
    return 3;
}

// FUNCTION: GAMEMD 0x41CFC0
int AircraftTypeClass::vf_12()
{
    return sizeof(AircraftTypeClass);
}

// FUNCTION: GAMEMD 0x41CFD0
int AircraftTypeClass::vf_16()
{
    return ArrayIndex;
}

// FUNCTION: GAMEMD 0x41CFE0
// The scalar deleting destructor the compiler emits for ~AircraftTypeClass (slot 8).

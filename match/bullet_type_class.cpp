// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// Function claims in this TU are ordered by their retail entry addresses.
// /Ob2 inlines the derived no-init constructor in Load at 0x46C6B8,
// leaving the native direct ObjectTypeClass constructor call and four vptr stores.

#include "bullet_type_class.h"
#include "abstract_registry.h"
#include "vector_class_operations.h"
#include "_layout/swizzle_manager_class.h"
#include "_layout/obj_004a1d30.h"
#include "ui_display_chain.h"
#include <new.h>
#include "vector_add_item_free.h"

// GLOBAL: GAMEMD 0x7E95D0 -- native BulletTypeClass CLSID, copied at 0x46C760.
extern const CLSID DAT_007E95D0;

// FUNCTION: GAMEMD 0x46BBC0
BulletTypeClass::BulletTypeClass(const char* id)
    : ObjectTypeClass(id),
      Airburst(0),
      Floater(0),
      SubjectToCliffs(0),
      SubjectToElevation(0),
      SubjectToWalls(0),
      VeryHigh(0),
      Shadow(1),
      Arcing(0),
      Dropping(0),
      Level(0),
      Inviso(0),
      Proximity(0),
      Ranged(0),
      Rotates(1),
      Inaccurate(0),
      FlakScatter(0),
      AA(0),
      AG(1),
      Acceleration(3),
      SpawnDelay(3),
      Degenerates(0),
      Bouncy(0),
      AnimPalette(0),
      FirersPalette(0),
      Cluster(1),
      AirburstWeapon(0),
      ShrapnelWeapon(0),
      ShrapnelCount(0),
      DetonationAltitude(0),
      Vertical(0),
      Elasticity(0.75),
      Color(0),
      Trailer(0),
      ROT(0),
      CourseLockDuration(0),
      ScaledSpawnDelay(0),
      Scalable(0),
      Arm(0),
      AnimLow(0),
      AnimHigh(0),
      AnimRate(0),
      Flat(0)
{
    // The native call targets AbstractClass's RTTI-interface slot 5.
    AbstractClass::vf_rtti_5();

    IsLogic = true;
    RadarInvisible = true;
    Selectable = false;
    LegalTarget = false;
    Insignificant = true;
    Immune = true;
    AllowCellContent = false;

    DynamicVectorAddItemFree(&DAT_00A83C80, this);
    // Native instructions at 0x46BD84..0x46BDD4 treat 0xB0F670 as a
    // pointer-valued DynamicVectorClass and append this through slot +8.
    DynamicVectorAddItemFree(reinterpret_cast<DynamicVectorClass<void*>*>(&DAT_00B0F670), (void*)this);
}

// FUNCTION: GAMEMD 0x46BDE0
BulletTypeClass::BulletTypeClass(const AbstractNoInit& noInit)
    : ObjectTypeClass(noInit)
{
}

// FUNCTION: GAMEMD 0x46BE10
BulletTypeClass::~BulletTypeClass()
{
    AnnounceExpiredPointer(1);
    // Native 0x46BE36..0x46BE7D removes this pointer from the shared
    // AbstractClass registry at 0xB0F670 through its index-query slot.
    reinterpret_cast<DynamicVectorClass<AbstractClass*>*>(&DAT_00B0F670)->RemoveItem(this);
    DAT_00A83C80.RemoveItem(this);
}

// CRT case-insensitive compare (_strcmpi @ GAMEMD 0x7C8D20). Declared (no body)
// so the call is a reloc; excluded from the match target.
int __cdecl gg_strcmpi(const char* a, const char* b);

// FUNCTION: GAMEMD 0x46C440
// Native ECX input is an ID; returns its array index, creating a missing type.
int __fastcall FUN_0046C440(const char* id)
{
    // STRING: GAMEMD 0x817474
    if (gg_strcmpi(id, "<none>") == 0)
        return -1;
    for (int i = 0; i < DAT_00A83C80.Count; ++i)
    {
        if (gg_strcmpi(id, DAT_00A83C80.Items[i]->ID) == 0)
            return i;
    }
    BulletTypeClass* created = new BulletTypeClass(id);
    return DAT_00A83C80.DynamicVectorClass<BulletTypeClass*>::FindItemIndex(created);
}

// FUNCTION: GAMEMD 0x46C4D0
char* __fastcall FUN_0046C4D0(unsigned int index)
{
    if (index < DAT_00A83C80.Count)
        return DAT_00A83C80.Items[index]->ID;
    return 0;
}

// FUNCTION: GAMEMD 0x46C4F0
CoordStruct BulletTypeClass::vf_27(const CoordStruct& coord)
{
    CoordStruct result = coord;
    if (result.Z <= Map_0087F7E8.GetZPos(&result))
        result.Z = Map_0087F7E8.GetZPos(&result) + 1;
    return result;
}

// FUNCTION: GAMEMD 0x46C560
void BulletTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1CA0(Airburst);
    crc->FUN_004A1CA0(Shadow);
    crc->FUN_004A1CA0(Arcing);
    crc->FUN_004A1CA0(Dropping);
    crc->FUN_004A1CA0(Level);
    crc->FUN_004A1CA0(Inviso);
    crc->FUN_004A1CA0(Proximity);
    crc->FUN_004A1CA0(Ranged);
    crc->FUN_004A1CA0(Rotates);
    crc->FUN_004A1CA0(Inaccurate);
    crc->FUN_004A1CA0(FlakScatter);
    crc->FUN_004A1CA0(AA);
    crc->FUN_004A1CA0(AG);
    crc->FUN_004A1CA0(Degenerates);
    crc->FUN_004A1CA0(Bouncy);
    crc->FUN_004A1D90(Elasticity);
    crc->FUN_004A1D50(Acceleration);
    crc->FUN_004A1D50(ROT);
    crc->FUN_004A1D50(Arm);
    crc->FUN_004A1CA0(Flat);
}

// FUNCTION: GAMEMD 0x46C6A0
HRESULT __stdcall BulletTypeClass::Load(IStream* stream)
{
    HRESULT result = ObjectTypeClass::Load(stream);
    if (result < 0)
        return result;
    new (this) BulletTypeClass(AbstractNoInit());
    ObjectTypeClass::FUN_005F8110();
    ObjectTypeClass::FUN_005F9070();
    // Native direct calls to 0x6CF240 register these three DWORD slots.
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Trailer);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&AirburstWeapon);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&ShrapnelWeapon);
    return S_OK;
}

// FUNCTION: GAMEMD 0x46C730
HRESULT __stdcall BulletTypeClass::Save(IStream* stream, BOOL clearDirty)
{
    HRESULT result = ObjectTypeClass::Save(stream, clearDirty);
    if (result >= 0)
        result = S_OK;
    return result;
}

// FUNCTION: GAMEMD 0x46C750
HRESULT __stdcall BulletTypeClass::GetClassID(CLSID* classID)
{
    if (classID == 0)
        return E_POINTER;
    *classID = DAT_007E95D0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x46C790  (__fastcall)
// Find the bullet type named `id` in the global Array (case-insensitive); if it
// is not present, allocate and construct a fresh one. The reserved names
// "<none>" and "none" are rejected (return null).
BulletTypeClass* BulletTypeClass::FindOrAllocate(const char* id)
{
    // Single shared `return 0` tail (one `xor eax,eax` epilogue, reached by JZ
    // from both reserved-name rejects and the alloc-failure path) — the retail
    // shape. The two rejects are folded into one short-circuit `&&` so the
    // compiler merges the null exits instead of emitting a local zero-return at
    // each site.
    if (gg_strcmpi("<none>", id) != 0 && gg_strcmpi("none", id) != 0)
    {
        for (int i = 0; i < DAT_00A83C80.Count; ++i)
        {
            if (gg_strcmpi(DAT_00A83C80.Items[i]->ID, id) == 0)
                return DAT_00A83C80.Items[i];
        }

        return new BulletTypeClass(id);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x46C820
// The native entry compares the pointer at +0x2D8 and clears it on equality.
void BulletTypeClass::vf_10(void* target, bool removed)
{
    if (target == Trailer)
        Trailer = 0;
}

// FUNCTION: GAMEMD 0x46C840  (__thiscall)
void BulletTypeClass::SetScaledSpawnDelay(int delay)
{
    ScaledSpawnDelay = delay;
}

// FUNCTION: GAMEMD 0x46C850
int BulletTypeClass::vf_11()
{
    return 9;
}

// FUNCTION: GAMEMD 0x46C860
int BulletTypeClass::vf_12()
{
    return sizeof(BulletTypeClass);
}

// FUNCTION: GAMEMD 0x46C870
bool BulletTypeClass::vf_32(const CellStruct* cell, HouseClass* house)
{
    return false;
}

// FUNCTION: GAMEMD 0x46C880
ObjectClass* BulletTypeClass::vf_35(HouseClass* house)
{
    return 0;
}

// SYNTHETIC: GAMEMD 0x46C890
// Scalar deleting destructor emitted by VC6 from the ordinary destructor.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E95D0
extern const CLSID DAT_007E95D0 = {0x5AF2CE77, 0x0634, 0x11D2, {0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// END defined globals

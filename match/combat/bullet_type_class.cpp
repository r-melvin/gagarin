// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// Function claims in this TU are ordered by their retail entry addresses.
// /Ob2 inlines the derived no-init constructor in Load at 0x46C6B8,
// leaving the native direct ObjectTypeClass constructor call and four vptr stores.

#include "bullet_type_class.h"
#include "../core/abstract_registry.h"
#include "../core/vector_class_operations.h"
#include "../_layout/swizzle_manager_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../ui/input_controls/ui_display_chain.h"
#include <new.h>
#include "../core/vector_add_item_free.h"

// GLOBAL: GAMEMD 0x7E95D0 -- native BulletTypeClass CLSID, copied at 0x46C760.
extern const CLSID DAT_007E95D0;

// FUNCTION: GAMEMD 0x46BBC0
BulletTypeClass::BulletTypeClass(const char* id)
    : ObjectTypeClass(id),
      unknown_294(0),
      unknown_295(0),
      unknown_296(0),
      unknown_297(0),
      unknown_298(0),
      unknown_299(0),
      unknown_29A(1),
      unknown_29B(0),
      unknown_29C(0),
      unknown_29D(0),
      unknown_29E(0),
      unknown_29F(0),
      unknown_2A0(0),
      unknown_2A1(1),
      unknown_2A2(0),
      unknown_2A3(0),
      unknown_2A4(0),
      unknown_2A5(1),
      unknown_2D0(3),
      unknown_2E4(3),
      unknown_2A6(0),
      unknown_2A7(0),
      unknown_2A8(0),
      unknown_2A9(0),
      unknown_2AC(1),
      AirburstWeapon(0),
      ShrapnelWeapon(0),
      ShrapnelCount(0),
      unknown_2BC(0),
      unknown_2C0(0),
      unknown_2C8(0.75),
      unknown_2D4(0),
      unknown_2D8(0),
      unknown_2DC(0),
      unknown_2E0(0),
      ScaledSpawnDelay(0),
      unknown_2EC(0),
      unknown_2F0(0),
      unknown_2F4(0),
      unknown_2F5(0),
      unknown_2F6(0),
      unknown_2F7(0)
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
    if (result.Z <= Map_0087F7E8.FUN_00578080(&result))
        result.Z = Map_0087F7E8.FUN_00578080(&result) + 1;
    return result;
}

// FUNCTION: GAMEMD 0x46C560
void BulletTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1CA0(unknown_294);
    crc->FUN_004A1CA0(unknown_29A);
    crc->FUN_004A1CA0(unknown_29B);
    crc->FUN_004A1CA0(unknown_29C);
    crc->FUN_004A1CA0(unknown_29D);
    crc->FUN_004A1CA0(unknown_29E);
    crc->FUN_004A1CA0(unknown_29F);
    crc->FUN_004A1CA0(unknown_2A0);
    crc->FUN_004A1CA0(unknown_2A1);
    crc->FUN_004A1CA0(unknown_2A2);
    crc->FUN_004A1CA0(unknown_2A3);
    crc->FUN_004A1CA0(unknown_2A4);
    crc->FUN_004A1CA0(unknown_2A5);
    crc->FUN_004A1CA0(unknown_2A6);
    crc->FUN_004A1CA0(unknown_2A7);
    crc->FUN_004A1D90(unknown_2C8);
    crc->FUN_004A1D50(unknown_2D0);
    crc->FUN_004A1D50(unknown_2DC);
    crc->FUN_004A1D50(unknown_2F0);
    crc->FUN_004A1CA0(unknown_2F7);
}

// FUNCTION: GAMEMD 0x46C6A0
HRESULT __stdcall BulletTypeClass::Load(IStream* stream)
{
    HRESULT result = ObjectTypeClass::Load(stream);
    if (result < 0)
        return result;
    if (this != 0)
        new (this) BulletTypeClass(AbstractNoInit());
    ObjectTypeClass::FUN_005F8110();
    ObjectTypeClass::FUN_005F9070();
    // Native direct calls to 0x6CF240 register these three DWORD slots.
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_2D8);
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
    if (target == unknown_2D8)
        unknown_2D8 = 0;
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

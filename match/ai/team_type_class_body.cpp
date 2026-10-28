// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   TeamTypeClass construction, destruction and stream loading, read off retail
//   gamemd.exe v1.001 (vtable 0x7F47D0). The layout is match/_layout/team_type_class.h.
//   /Ob2: the registry AddItem/RemoveItem bodies are expanded in place, and the
//   scalar deleting destructor carries the destructor body inline.

#include <new.h>
#include "../_layout/team_type_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_class_operations.h"
#include "../_layout/obj_004a1d30.h"

// GLOBAL: GAMEMD 0xA8ECA0 -- the team type registry.
extern DynamicVectorClass<TeamTypeClass*> DAT_00A8ECA0;
// GLOBAL: GAMEMD 0xB0F670 -- the shared abstract-type registry.
extern DynamicVectorClass<TeamTypeClass*> DAT_00B0F670;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// Registry append, expanded in place: the growth increment is tested before the sum.
static inline bool TeamTypeRegistryAdd(DynamicVectorClass<TeamTypeClass*>* vector, TeamTypeClass* item)
{
    if (vector->Count >= vector->Capacity) {
        if (!vector->IsAllocated && vector->Capacity != 0)
            return false;
        if (vector->CapacityIncrement <= 0)
            return false;
        if (!vector->SetCapacity(vector->Capacity + vector->CapacityIncrement, 0))
            return false;
    }
    int index = vector->Count++;
    vector->Items[index] = item;
    return true;
}

// FUNCTION: GAMEMD 0x6F06E0
TeamTypeClass::TeamTypeClass(const char* id)
    : AbstractTypeClass(id),
      ArrayIndex(-1),
      Group(-1),
      unknown_A0(1),
      Flag_A4(false),
      Flag_A5(false),
      Flag_A6(false),
      Flag_A7(false),
      Flag_A8(false),
      Flag_A9(false),
      Flag_AA(false),
      Flag_AB(false),
      Flag_AC(false),
      Flag_AD(false),
      Flag_AE(false),
      Flag_AF(false),
      Flag_B0(false),
      Flag_B1(false),
      Flag_B2(false),
      Flag_B3(false),
      unknown_B4(7),
      unknown_B8(-1),
      unknown_BC(0),
      unknown_C0(0),
      Ptr_C4(0),
      unknown_C8(-1),
      unknown_CC(0),
      Ptr_D0(0),
      unknown_D4(-1),
      unknown_D8(-1),
      unknown_DC(0),
      Ptr_E0(0),
      Ptr_E4(0),
      unknown_E8(0),
      unknown_EC(9),
      Flag_F0(true),
      Flag_F1(false),
      Flag_F2(false),
      Flag_F3(false),
      Flag_F4(false),
      Flag_F5(true),
      Flag_F6(false),
      Flag_F7(false)
{
    TeamTypeRegistryAdd(&DAT_00A8ECA0, this);
    ArrayIndex = DAT_00A8ECA0.FindItemIndex(this);
    TeamTypeRegistryAdd(&DAT_00B0F670, this);
}

// FUNCTION: GAMEMD 0x6F08F0
TeamTypeClass::~TeamTypeClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A8ECA0.RemoveItem(this);
    DAT_00B0F670.RemoveItem(this);
}

// SYNTHETIC: GAMEMD 0x6F20D0
// TeamTypeClass scalar deleting destructor (primary slot 8), the destructor expanded in place.

// FUNCTION: GAMEMD 0x6F1BB0
HRESULT __stdcall TeamTypeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) TeamTypeClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Ptr_C4);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Ptr_D0);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Ptr_E0);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Ptr_E4);
    return 0;
}

// FUNCTION: GAMEMD 0x6F1C80
// Feeds the type's settings, and the identity of the objects it points at, to the checksum.
void TeamTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(Group);
    crc->FUN_004A1CA0(Flag_A8);
    crc->FUN_004A1CA0(Flag_A9);
    crc->FUN_004A1CA0(Flag_AA);
    crc->FUN_004A1CA0(Flag_AB);
    crc->FUN_004A1CA0(Flag_AC);
    crc->FUN_004A1CA0(Flag_AD);
    crc->FUN_004A1CA0(Flag_AE);
    crc->FUN_004A1CA0(Flag_AF);
    crc->FUN_004A1CA0(Flag_B0);
    crc->FUN_004A1CA0(Flag_B1);
    crc->FUN_004A1D50(unknown_B4);
    crc->FUN_004A1D50(unknown_B8);
    crc->FUN_004A1D50(unknown_BC);
    if (Ptr_C4) {
        crc->FUN_004A1D50(Ptr_C4->vf_11());
    }
    if (Ptr_C4) {
        crc->FUN_004A1D50(Ptr_C4->vf_rtti_4());
    }
    crc->FUN_004A1D50(unknown_CC);
    if (Ptr_D0) {
        crc->FUN_004A1D50(Ptr_D0->vf_rtti_4());
    }
    crc->FUN_004A1D50(unknown_D4);
    crc->FUN_004A1D50(unknown_D8);
    crc->FUN_004A1D50(unknown_DC);
    if (Ptr_E0) {
        crc->FUN_004A1D50(Ptr_E0->vf_rtti_4());
    }
    if (Ptr_E4) {
        crc->FUN_004A1D50(Ptr_E4->vf_rtti_4());
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The TriggerClass bodies of retail .text 0x726140..0x726A6C that the other
// trigger_class_* units leave open: the destructor, the event check, the
// small event-bit and flag accessors and the primary-table slots 5, 8, 10,
// 11, 12 and 13 (vtable 0x7F5858). Functions are in retail address order;
// TriggerClass itself is declared in _layout/trigger_class.h.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy
//   /Ob2: the scalar deleting destructor 0x726950 expands the destructor and
//   the destructor expands the vector RemoveItem bodies in place.

#include <new.h>
#include "../_layout/trigger_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../core/vector_class_operations.h"
#include "../movement/locomotion_load_support.h"
#include "../core/abstract_registry.h"
#include "tevent_class_methods.h"

// FUNCTION: GAMEMD 0x502D30 (decl; reloc) -- __fastcall, house for a country index.
HouseClass* __fastcall FUN_00502D30(int index);

// The registries the destructor removes `this` from (abstract_registry.h holds their storage).
static inline void Trigger_RemoveFrom(DynamicVectorClassLayout* list, TriggerClass* trigger)
{
    reinterpret_cast<DynamicVectorClass<TriggerClass*>*>(list)->RemoveItem(trigger);
}

// FUNCTION: GAMEMD 0x726140
TriggerClass::~TriggerClass()
{
    AnnounceExpiredPointer(1);
    Trigger_RemoveFrom(&TriggerClass::Array, this);
    Trigger_RemoveFrom(&DAT_00B0F670, this);
    Trigger_RemoveFrom(&DAT_00B0F708, this);
}

// FUNCTION: GAMEMD 0x7264C0
// Tests every event of the type against `event`; events whose bit is already
// set in OccuredEvents count as passed. An event that passes and whose kind
// is in both GetState buckets latches its bit when `persistent` is set.
bool TriggerClass::FUN_007264C0(int event, ObjectClass* object, bool flag, bool persistent, int arg)
{
    if (!Enabled || Destroyed) {
        return false;
    }
    bool result = true;
    if (!flag) {
        int index = 0;
        for (TEventClass* e = reinterpret_cast<TEventClass*>(Type->FirstEvent); e != 0;
             e = reinterpret_cast<TEventClass*>(e->NextEvent), index++) {
            int bit = 1 << index;
            if (!(OccuredEvents & bit)) {
                if (!e->FUN_0071E940(event, FUN_00502D30(Type->House->ArrayIndex), object,
                                     &Timer, &persistent, arg)) {
                    result = false;
                    continue;
                }
            }
            if (e->FUN_0071FA30()) {
                unknown_2C = e->FUN_0071FA30();
            }
            if (persistent && e->GetStateA() && e->GetStateB()) {
                OccuredEvents |= bit;
            }
        }
    }
    if (result && persistent) {
        ResetTimers();
    }
    return result;
}

// FUNCTION: GAMEMD 0x726690
void TriggerClass::vf_10(void* target, bool removed)
{
    if (Type == target) {
        Type = 0;
    }
    if (AttachedTrigger == target) {
        AttachedTrigger = AttachedTrigger->NextTrigger;
    }
    if (unknown_2C == target) {
        unknown_2C = 0;
    }
}

// FUNCTION: GAMEMD 0x7266C0
void TriggerClass::FUN_007266C0(int index)
{
    OccuredEvents |= 1 << index;
}

// FUNCTION: GAMEMD 0x7266E0
void TriggerClass::FUN_007266E0(int index)
{
    OccuredEvents &= ~(1 << index);
}

// FUNCTION: GAMEMD 0x726700
bool TriggerClass::FUN_00726700(int index) const
{
    return (OccuredEvents & (1 << index)) != 0;
}

// FUNCTION: GAMEMD 0x726780
bool TriggerClass::FUN_00726780() const
{
    return Destroyed;
}

// FUNCTION: GAMEMD 0x726790
void TriggerClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D50(Type->vf_rtti_4());
    if (NextTrigger) {
        crc->FUN_004A1D50(NextTrigger->vf_rtti_4());
    }
    crc->FUN_004A1CA0(Destroyed);
    crc->FUN_004A1CA0(Enabled);
    crc->FUN_004A1D50(Timer.GetTimeLeft());
    crc->FUN_004A1D50(OccuredEvents);
}

// FUNCTION: GAMEMD 0x726860
HRESULT __stdcall TriggerClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) TriggerClass(AbstractNoInit());
    DAT_00B0C110.FUN_006CF240((void**)&Type);
    DAT_00B0C110.FUN_006CF240((void**)&NextTrigger);
    DAT_00B0C110.FUN_006CF240((void**)&unknown_2C);
    return 0;
}

// FUNCTION: GAMEMD 0x7268F0
void TriggerClass::FUN_007268F0()
{
    Enabled = true;
    ResetTimers();
}

// FUNCTION: GAMEMD 0x726900
void TriggerClass::FUN_00726900()
{
    Enabled = false;
}

// FUNCTION: GAMEMD 0x726920
void TriggerClass::FUN_00726920(void* value)
{
    unknown_2C = value;
}

// FUNCTION: GAMEMD 0x726930
int TriggerClass::vf_12()
{
    return sizeof(TriggerClass);
}

// FUNCTION: GAMEMD 0x726940
int TriggerClass::vf_11()
{
    return 0x26;
}

// FUNCTION: GAMEMD 0x726950
// The scalar deleting destructor (slot 8), emitted with the vtable by Load's
// placement construction; it expands ~TriggerClass in place.

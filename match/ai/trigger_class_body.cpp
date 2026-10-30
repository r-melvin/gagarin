// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The TriggerClass bodies of retail .text 0x726140..0x726A6C that the other
// trigger_class_* units leave open: the destructor, the event check, the
// small event-bit and flag accessors and the primary-table slots 5, 8, 10,
// 11, 12 and 13 (vtable 0x7F5858). Functions are in retail address order;
// TriggerClass itself is declared in _layout/trigger_class.h.
//   /Ob2: the scalar deleting destructor 0x726950 expands the destructor and
//   the destructor expands the vector RemoveItem bodies in place.

#include "../FUNCTION.H"
#include "../movement/locomotion_load_support.h"
#include "../core/abstract_registry.h"
#include "tevent_class_methods.h"
#include "trigger_class_event_methods.h"
#include "trigger_class_methods.h"
#include "trigger_class_more_methods.h"
#include "trigger_class_destroy_methods.h"

// FUNCTION: GAMEMD 0x502D30 (decl; reloc) -- __fastcall, house for a country index.
HouseClass* FUN_00502D30(int index);

// The registries the destructor removes `this` from (abstract_registry.h holds their storage).
static inline void Trigger_RemoveFrom(DynamicVectorClassLayout* list, TriggerClass* trigger)
{
    reinterpret_cast<DynamicVectorClass<TriggerClass*>*>(list)->RemoveItem(trigger);
}

struct TriggerCtorTypeFlagsView
{
    unsigned char unknown_00[0x9C];
    unsigned char Flags[4];
};
GG_STATIC_ASSERT(offsetof(TriggerCtorTypeFlagsView, Flags) == 0x9C);


struct TriggerCtorPtrVector
{
    virtual ~TriggerCtorPtrVector();
    virtual bool Equals(const TriggerCtorPtrVector& other) const;
    virtual bool SetCapacity(int capacity, void* memory);

    void* Items;
    int Capacity;
    unsigned char IsInitialized;
    unsigned char IsAllocated;
    unsigned char unknown_0E[2];
    int Count;
    int CapacityIncrement;
};
GG_STATIC_ASSERT(offsetof(TriggerCtorPtrVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TriggerCtorPtrVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(TriggerCtorPtrVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(TriggerCtorPtrVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(TriggerCtorPtrVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(TriggerCtorPtrVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(TriggerCtorPtrVector) == 0x18);

inline bool TriggerCtorVectorAddItem(TriggerCtorPtrVector* vector,
                                     TriggerClass* item)
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
    ((TriggerClass**)vector->Items)[index] = item;
    return true;
}

// GLOBAL: GAMEMD 0x00A8B230 — ScenarioClass::Instance (pointer).
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;

// FUNCTION: GAMEMD 0x725FA0
TriggerClass::TriggerClass(TriggerTypeClass* type)
    : Type(type), AttachedTrigger(0), unknown_2C(0), Destroyed(0), Timer(0),
      OccuredEvents(0), Enabled(true)
{

    TriggerCtorVectorAddItem(
        reinterpret_cast<TriggerCtorPtrVector*>(&DAT_00B0F670), this);
    TriggerCtorVectorAddItem(
        reinterpret_cast<TriggerCtorPtrVector*>(&DAT_00B0F708), this);
    TriggerCtorVectorAddItem(
        reinterpret_cast<TriggerCtorPtrVector*>(&TriggerClass::Array), this);

    if (this->Type != 0) {
        this->ResetTimers();
        TriggerCtorTypeFlagsView* typeFlags =
            reinterpret_cast<TriggerCtorTypeFlagsView*>(this->Type);
        if (typeFlags->Flags[3] == 0
            || (DAT_00A8B230->Difficulty == 0 && typeFlags->Flags[0] == 0)
            || (DAT_00A8B230->Difficulty == 1 && typeFlags->Flags[1] == 0)
            || (DAT_00A8B230->Difficulty == 2 && typeFlags->Flags[2] == 0)) {
            this->Enabled = false;
        }
    }
}

// FUNCTION: GAMEMD 0x726140
TriggerClass::~TriggerClass()
{
    AnnounceExpiredPointer(1);
    Trigger_RemoveFrom(&TriggerClass::Array, this);
    Trigger_RemoveFrom(&DAT_00B0F670, this);
    Trigger_RemoveFrom(&DAT_00B0F708, this);
}

// FUNCTION: GAMEMD 0x726250  (__thiscall)
// True if this trigger (or any attached trigger) holds a Crosses-Horizontal-Line
// event.
bool TriggerClass::HasCrossesHorizontalLineEvent() const
{
    if (this->AttachedTrigger)
        return this->Type->HasCrossesHorizontalLineEvent()
            || this->AttachedTrigger->HasCrossesHorizontalLineEvent();

    return this->Type->HasCrossesHorizontalLineEvent();
}

// FUNCTION: GAMEMD 0x726290  (__thiscall)
// True if this trigger (or any attached trigger) holds a Crosses-Vertical-Line
// event.
bool TriggerClass::HasCrossesVerticalLineEvent() const
{
    if (this->AttachedTrigger)
        return this->Type->HasCrossesVerticalLineEvent()
            || this->AttachedTrigger->HasCrossesVerticalLineEvent();

    return this->Type->HasCrossesVerticalLineEvent();
}

// FUNCTION: GAMEMD 0x7262D0  (__thiscall)
// True if this trigger's type, or the attached trigger's type, holds a
// Zone-Entry-By event.
bool TriggerClass::HasZoneEntryByEvent() const
{
    if (this->AttachedTrigger)
        return this->Type->HasZoneEntryByEvent()
            || this->AttachedTrigger->Type->HasZoneEntryByEvent();

    return this->Type->HasZoneEntryByEvent();
}

// FUNCTION: GAMEMD 0x726310  (__thiscall)
// True if this trigger's type, or the attached trigger's type, holds an
// Allow-Win action.
bool TriggerClass::HasAllowWinAction() const
{
    if (this->AttachedTrigger)
        return this->Type->HasAllowWinAction()
            || this->AttachedTrigger->Type->HasAllowWinAction();

    return this->Type->HasAllowWinAction();
}

// FUNCTION: GAMEMD 0x726350  TriggerClass::HasGlobalSetOrClearedEvent (__thiscall)
//
// True if this trigger's Type — or, when an AttachedTrigger exists, either
// Type — contains the given global-set/cleared event. With no AttachedTrigger
// the lone Type predicate's bool is returned directly.
// ---------------------------------------------------------------------------
bool TriggerClass::HasGlobalSetOrClearedEvent(int idxGlobal) const
{
    if (this->AttachedTrigger)
    {
        return this->Type->HasGlobalSetOrClearedEvent(idxGlobal)
            || this->AttachedTrigger->Type->HasGlobalSetOrClearedEvent(idxGlobal);
    }
    return this->Type->HasGlobalSetOrClearedEvent(idxGlobal);
}

// FUNCTION: GAMEMD 0x7263A0  (__thiscall)
// Walk this trigger and its NextTrigger chain; for each trigger whose type has
// a Global Set/Cleared event referencing idxGlobal, reset that trigger's timers.
void TriggerClass::NotifyGlobalChanged(int idxGlobal)
{
    for (TriggerClass* trigger = this; trigger; trigger = trigger->NextTrigger)
    {
        if (trigger->Type->HasGlobalSetOrClearedEvent(idxGlobal))
            trigger->ResetTimers();
    }
}

// FUNCTION: GAMEMD 0x7263D0  (__thiscall)
// As NotifyGlobalChanged, but for Local Set/Cleared events.
void TriggerClass::NotifyLocalChanged(int idxLocal)
{
    for (TriggerClass* trigger = this; trigger; trigger = trigger->NextTrigger)
    {
        if (trigger->Type->HasLocalSetOrClearedEvent(idxLocal))
            trigger->ResetTimers();
    }
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

// FUNCTION: GAMEMD 0x7265C0  (__thiscall)
// Walks the trigger type's action list; each action is Execute()d against the
// trigger's owner house (HouseClass::FindByCountryIndex of the type's House).
// Returns whether at least one action executed.
bool TriggerClass::FireActions(ObjectClass* pObj, CellStruct location)
{
    if (this->Enabled && !this->Destroyed) {
        bool result = false;
        for (TActionClass* action = reinterpret_cast<TActionClass*>(this->Type->FirstAction); action != 0;
             action = action->unknown_28) {
            if (action->Execute(
                    HouseClass::FindByCountryIndex(this->Type->House->ArrayIndex),
                    pObj, this, location)) {
                result = true;
            }
        }
        return result;
    }
    return false;
}

// FUNCTION: GAMEMD 0x726630  TriggerClass::GetInstance (__fastcall — pType in ECX)
//
// The comparison is written with pType on the left. x86 has two encodings for a
// register/memory compare and VC6 picks by operand order: `pType == item->Type`
// gives retail's `3B` (`CMP ESI,[EBX+..]`), the other way round gives `39`
// (`CMP [EBX+..],ESI`). One byte, and the only thing that was keeping this
// function off byte parity.
//
// Returns the existing TriggerClass whose Type matches pType, scanning the
// global Array linearly; if none is found a fresh instance is allocated and
// constructed. A null pType (or a failed allocation) yields null.
// ---------------------------------------------------------------------------
TriggerClass* TriggerClass::GetInstance(TriggerTypeClass* pType)
{
    if (pType)
    {
        for (int i = 0; i < TriggerClass::Array.Count; ++i)
        {
            if (pType == ((TriggerClass**)TriggerClass::Array.Items)[i]->Type)
                return ((TriggerClass**)TriggerClass::Array.Items)[i];
        }

        return new TriggerClass(pType);
    }
    return 0;
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

// FUNCTION: GAMEMD 0x726720  (__thiscall)
// Marks the trigger as destroyed and appends it to the global destruction queue.
// The inlined AddItem reaches the virtual SetCapacity through the vector's own
// `this` (slot 2, [vtable+0x08]) on the constant global object; the header's
// AddItem carries the phrasing that keeps retail's register order (53.3% with
// the member re-read at each use and the split `index = Count; Count = index +
// 1;`, which sinks the vtable load below the pushes and emits an LEA).
void TriggerClass::Destroy()
{
    this->Destroyed = true;
    reinterpret_cast<TriggerPtrVector*>(&DAT_00B0F698)->AddItem(this);
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
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&NextTrigger);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_2C);
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

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (every
//   offset reconfirmed against the user's binary in factory_class_methods.h).
//
// Translation unit: FactoryClass production accessors.
//
// Functions below are annotated in ascending retail address order.

#include "factory_class_methods.h"
#include "factory_class_more_methods.h"
#include "factory_class_queue_methods.h"
#include "factory_class_start_methods.h"
#include "factory_class_completed_methods.h"

// FUNCTION: GAMEMD 0x4C9C60  (__thiscall)
// Read IsDifferent (this+0x5D), clear it, return the prior value.
//   MOV AL,[ECX+0x5D]; MOV byte[ECX+0x5D],0; RET
bool FactoryClass::HasProgressChanged()
{
    bool changed = this->IsDifferent;
    this->IsDifferent = false;
    return changed;
}

// FUNCTION: GAMEMD 0x4C9E10
// Abandons any current production, then makes `object` the finished item: no balance owed, the
// owner taken from the object, the progress timer restarted at 0 and the stage complete (0x36).
void FactoryClass::FUN_004C9E10(TechnoClass* object)
{
    AbandonProduction();
    Object = object;
    Owner = object->Owner;
    Balance = 0;
    Production.SetRate(0);
    Production.Value = 0x36;
    IsDifferent = true;
    IsSuspended = true;
}

// FUNCTION: GAMEMD 0x4C9E60  (__thiscall)
// Mark production as suspended (no-op if already suspended) and reset the
// progress timer.  Resetting goes Rate = 0 first, then a CDTimerClass(0)
// temporary copied into Production.Timer; the temporary's uninitialised
// CurrentTime slot is carried through as the MOV [ECX+0x30],<garbage> store.
bool FactoryClass::Suspend(bool manual)
{
    if (!this->IsSuspended) {
        this->IsManual = manual;
        this->IsSuspended = true;
        this->Production.SetRate(0);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4C9FB0  (__thiscall)
// Build time in frames: the produced object's TimeToBuild() (0 when none) scaled
// down by 54 (signed IMUL+SAR), then clamped to [1, 255].
int FactoryClass::GetBuildTimeFrames() const
{
    int cost = 0;
    if (this->Object)
        cost = this->Object->TimeToBuild();

    int frames = cost / 54;
    if (frames < 1)
        return 1;
    if (frames > 255)
        frames = 255;
    return frames;
}

// FUNCTION: GAMEMD 0x4CA120  (__thiscall)
// Return Production.Value (this+0x24).  MOV EAX,[ECX+0x24]; RET
int FactoryClass::GetProgress() const
{
    return this->Production.Value;
}

// FUNCTION: GAMEMD 0x4CA130  (__thiscall)
// Done when progress is complete (Production.Value == 54) and there is either a
// produced Object or a SpecialItem queued.
//   if (Object       && Production.Value == 54) return true;
//   if (SpecialItem != -1 && Production.Value == 54) return true;
//   return false;
bool FactoryClass::IsDone() const
{
    if (this->Object && this->Production.Value == 54)
        return true;
    if (this->SpecialItem != -1 && this->Production.Value == 54)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x4CA1A0
//
// Called once the produced item has been placed. If a real object is in
// production and the progress stage has reached its final step (0x36), the
// object slot is released, the factory is suspended and flagged changed, and
// the progress stage is reset (Value = 0, then Rate/Timer restarted at 0).
// The same happens for a special-weapon item, whose slot is cleared to -1
// instead. Reports whether anything was completed.
bool FactoryClass::CompletedProduction()
{
    if (this->Object != 0 && this->Production.Value == 0x36) {
        this->Object = 0;
        this->IsSuspended = true;
        this->IsDifferent = true;
        this->Production.Value = 0;
        this->Production.SetRate(0);
        return true;
    }

    if (this->SpecialItem != 0 && this->Production.Value == 0x36) {
        this->SpecialItem = -1;
        this->IsSuspended = true;
        this->IsDifferent = true;
        this->Production.Value = 0;
        this->Production.SetRate(0);
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x4CA5A0  FactoryClass::StartProduction (__thiscall)
// Pull the head of the production queue and hand it to the owning house. Bails
// if the queue is empty, if something is already being built, or if the factory
// is gated and not suspended. The unlink is the inline
// DynamicVectorClass::Delete(0): its bound test, the decrement and the shift
// loop that re-reads Count as its bound are all retail's.
void FactoryClass::StartProduction()
{
    if (QueuedObjects.GetCount() == 0)
        return;

    if (Object != 0)
        return;

    if (Production.Rate != 0 && !IsSuspended)
        return;

    TechnoTypeClass* type = const_cast<TechnoTypeClass*>(QueuedObjects.Items[0]);
    QueuedObjects.Delete(0);

    int result = type->Slot_40();
    if (result < 0)
        return;

    Owner->BeginProduction(type->Slot_2C(), result, type->unknown_CCE, 1);
}

// FUNCTION: GAMEMD 0x4CA620  (__thiscall)
// Find pItem in the queue (genuine virtual FindItemIndex via [vtbl+0x10]); if
// present, shift the tail down over its slot (inlined RemoveItem) and report
// true, otherwise false.
bool FactoryClass::RemoveOneFromQueue(TechnoTypeClass const* pItem)
{
    int idx = this->QueuedObjects.FindItemIndex(pItem);
    if (idx != -1)
        return this->QueuedObjects.Delete(idx);
    return false;
}

// FUNCTION: GAMEMD 0x4CA670  (__thiscall)
// Total of this type both in production and queued: one for the in-production
// Object whose GetTechnoType() matches, plus every queued entry equal to pType.
int FactoryClass::CountTotal(TechnoTypeClass const* pType) const
{
    int count = 0;
    if (this->Object && this->Object->vf_33() == pType)
        count = 1;
    for (int i = 0; i < this->QueuedObjects.Count; ++i)
    {
        if (this->QueuedObjects.Items[i] == pType)
            ++count;
    }
    return count;
}

// FUNCTION: GAMEMD 0x4CA6B0  (__thiscall)
// Linear search of QueuedObjects for pType.  RET 4.
bool FactoryClass::IsQueued(TechnoTypeClass* pType) const
{
    for (int i = 0; i < this->QueuedObjects.Count; ++i) {
        if (pType == this->QueuedObjects.Items[i])
            return true;
    }
    return false;
}


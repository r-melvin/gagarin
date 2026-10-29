// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA-and-pinned-PE | YRpp-cross-check
// Retail entry-origin evidence: 0x725FA0..0x726132 inclusive (0x193 bytes).
// It calls AbstractClass::AbstractClass at 0x410170 and TriggerClass::ResetTimers
// at 0x726400; writes the TriggerClass vptr prefix and fields at +0x24..+0x44;
// appends this pointer to the vector-shaped regions at 0xB0F670, 0xB0F708 and
// 0xA8EAE8; and reads the trigger-type bytes +0x9C..+0x9F and scenario mode
// +0x60C. The addresses and offsets below are taken from those instructions.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// /GX adds exception-cleanup code around ResetTimers/vector append calls that
// is absent from retail. The scenario mode is read through the global at
// each test rather than through a local: with a local, cl threads the failed
// mode==0 test straight to the return (one extra return block); retail keeps
// the compare chain and one shared return.

#include <stddef.h>
#include "../_layout/trigger_class.h"
#include "../core/abstract_registry.h"
#include "../core/frame_counter.h"

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

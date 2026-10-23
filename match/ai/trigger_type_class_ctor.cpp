// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Entry-origin retail span 0x726C80..0x726DF5: 374 bytes, RET 4.
// RTTI confirms AbstractTypeClass as zero-offset base and four vptr stores.
// Stores and vector dispatches establish the asserted offsets below.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// GX emits exception cleanup absent from retail; no GX matches the full body.
#include <stddef.h>
#include "../_layout/trigger_type_class.h"
#include "../core/abstract_registry.h"

struct TriggerTypeCtorVector
{
    virtual ~TriggerTypeCtorVector();
    virtual bool Equals(const TriggerTypeCtorVector& other) const;
    virtual bool SetCapacity(int capacity, void* memory);
    void* Items;
    int Capacity;
    unsigned char IsInitialized;
    unsigned char IsAllocated;
    unsigned char unknown_0E[2];
    int Count;
    int CapacityIncrement;
};
GG_STATIC_ASSERT(offsetof(TriggerTypeCtorVector, Items) == 4);
GG_STATIC_ASSERT(offsetof(TriggerTypeCtorVector, Capacity) == 8);
GG_STATIC_ASSERT(offsetof(TriggerTypeCtorVector, IsAllocated) == 0xD);
GG_STATIC_ASSERT(offsetof(TriggerTypeCtorVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(TriggerTypeCtorVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(TriggerTypeCtorVector) == 0x18);

static inline bool TriggerTypeCtorAdd(TriggerTypeCtorVector* vector,
                                      TriggerTypeClass* item)
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
    ((TriggerTypeClass**)vector->Items)[index] = item;
    return true;
}


// FUNCTION: GAMEMD 0x726C80
TriggerTypeClass::TriggerTypeClass(const char* id)
    : AbstractTypeClass(id), ArrayIndex(-1), Difficulty_9C(1), Difficulty_9D(1),
      Difficulty_9E(1), Enabled(1), unknown_A0(0), House(0), NextTrigger(0),
      FirstEvent(0), FirstAction(0)
{
    TriggerTypeCtorAdd(reinterpret_cast<TriggerTypeCtorVector*>(&DAT_00B0F658), this);
    TriggerTypeCtorAdd(reinterpret_cast<TriggerTypeCtorVector*>(&DAT_00B0F670), this);
    ArrayIndex = Array.Count;
    TriggerTypeCtorAdd(reinterpret_cast<TriggerTypeCtorVector*>(&Array), this);
}

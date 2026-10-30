// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   SuperClass virtuals read off retail gamemd.exe v1.001 (vtable 0x7F3FE8).
//   Functions are in ascending retail address order.

#include "../FUNCTION.H"

// GLOBAL: GAMEMD 0xB0F5B8 -- the registry of super weapons that carry an animation.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F5B8;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// Registry append, expanded in place: the growth increment is tested before the sum.
static inline bool SuperRegistryAdd(DynamicVectorClass<AbstractClass*>* vector, AbstractClass* item)
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

// FUNCTION: GAMEMD 0x6CDEF0
HRESULT __stdcall SuperClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) SuperClass(LoadTag());
    if (Animation) {
        SuperRegistryAdd(&DAT_00B0F5B8, this);
    }
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Owner);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Animation);
    BlinkTimer_Low = 0;
    BlinkTimer_High = 0;
    return 0;
}

// FUNCTION: GAMEMD 0x6CDFF0
// Forget a pointer that is going away: the type's owner or type slot, or the animation.
void SuperClass::vf_10(void* target, bool removed)
{
    if (target == Owner) {
        Owner = 0;
    }
    if (target == Type) {
        Type = 0;
    }
    if (target == Animation) {
        Animation = 0;
        AnimationGotInvalid = 1;
    }
}

// FUNCTION: GAMEMD 0x6CE1F0
// The RTTI id of a super weapon.
int __stdcall SuperClass::vf_rtti_3()
{
    return 0x39;
}

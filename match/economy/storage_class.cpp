// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x6C9600 (Ghidra disasm).
//   Names cross-checked against YRpp
//   (each offset/address reconfirmed against the user's binary below).
//
// Translation unit: StorageClass::GetTotalValue (the P0.4 "hello-world" leaf).
// Drives toolchain + flag locking.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6C9600   StorageClass::GetTotalValue    (__thiscall)
//   FUNCTION: GAMEMD 0x6C9650   StorageClass::GetTotalAmount   (__thiscall)
//   FUNCTION: GAMEMD 0x6C9680   StorageClass::GetAmount        (__thiscall)
//   FUNCTION: GAMEMD 0x6C9690   StorageClass::AddAmount        (__thiscall)
//   FUNCTION: GAMEMD 0x6C96B0   StorageClass::RemoveAmount     (__thiscall)
//   GLOBAL:   GAMEMD 0xB0F4E8   TiberiumClass::Array  (DynamicVectorClass<TiberiumClass*>)
//   GLOBAL:   GAMEMD 0x7E1748   float 0.0f  (FCOMP comparand)
//   LIBRARY:  GAMEMD 0x7C5F00   __ftol      (CRT float->long; excluded from match target)

#include "storage_class.h"

// ---------------------------------------------------------------------------
// Minimal, offset-pinned models of the two referenced types. Only the members
// 0x6C9600 actually touches are modelled here; the full TiberiumClass /
// VectorClass layouts (with the COM base + every member) are P2 work. Each
// offset asserted below is confirmed numerically from the 0x6C9600 disassembly.
// ---------------------------------------------------------------------------

class TiberiumClass;

// VectorClass<TiberiumClass*> head: vtable at +0, Items at +4 (confirmed by
// `MOV EDI,[0xB0F4EC]` == &Array.Items, Array @0xB0F4E8). YRpp.
struct DynamicVectorClass_TiberiumPtr
{
    void*           vtable;        // +0x00
    TiberiumClass** Items;         // +0x04
    int             Capacity;      // +0x08
    int             IsAllocated;   // +0x0C
    int             Count;         // +0x10
    int             CapacityIncrement;  // +0x14
};
// Items at +4 (== 0xB0F4EC for Array @0xB0F4E8). Pointer-width-sensitive, so
// guarded to the 32-bit match ABI (4-byte void*/T**); enforced by the VC6 build.
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_TiberiumPtr, Items) == 0x04);
#endif

// TiberiumClass: only Value @0xB8 is needed here. FILD dword[EAX+0xB8] in
// 0x6C9600 loads it as an int; YRpp names it `Value`.
class TiberiumClass
{
public:
    char _layout_pad_P2[0xB8];     // full AbstractTypeClass-derived layout = P2
    int  Value;                    // +0xB8
};
GG_STATIC_ASSERT(offsetof(TiberiumClass, Value) == 0xB8);  // pointer-free: holds on both ABIs

// GLOBAL: GAMEMD 0xB0F4E8 — the engine's global Tiberium type array.
extern DynamicVectorClass_TiberiumPtr TiberiumArray;

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6C9600  (__thiscall)
//
// Sum, over the 4 Tiberium types this object stores, of value = worth*amount,
// truncated to int, for every type whose stored amount is > 0.0f.
//
//   for (i=0; i<4; ++i)
//     if (amount[i] > 0.0f)
//       total = (int)(TiberiumArray.Items[i]->Value * amount[i] + total);
// ---------------------------------------------------------------------------
int StorageClass::GetTotalValue() const
{
    int total = 0;
    const float* amount = &this->Tiberium1;
    for (int i = 0; i < 4; ++i)
    {
        if (amount[i] > 0.0f)
            total = (int)(TiberiumArray.Items[i]->Value * amount[i] + total);
    }
    return total;
}

// FUNCTION: GAMEMD 0x6C9650  (__thiscall)
// Integer-truncating sum of the 4 stored amounts, returned as float. Each step
// is `total = (int)(total + amount[i])` (FILD total; FADD float[i]; __ftol),
// then `return (float)total` (FILD).
float StorageClass::GetTotalAmount() const
{
    int total = 0;
    const float* amount = &this->Tiberium1;
    for (int i = 0; i < 4; ++i)
        total = (int)(total + amount[i]);
    return (float)total;
}

// FUNCTION: GAMEMD 0x6C9680  (__thiscall)
// Return the stored amount of one Tiberium type. MOV EAX,[ESP+4]; FLD
// float[ECX+EAX*4]; RET 4.
float StorageClass::GetAmount(int index) const
{
    return (&this->Tiberium1)[index];
}

// FUNCTION: GAMEMD 0x6C9690  (__thiscall)
// Add to one type's stored amount, returning the new total. FLD amount; FADD
// float[i]; FST float[i] (FST keeps the value in st0 for the return); RET 8.
float StorageClass::AddAmount(float amount, int index)
{
    float* p = &(&this->Tiberium1)[index];
    return *p = amount + *p;
}

// FUNCTION: GAMEMD 0x6C96B0  (__thiscall)
// Remove up to `amount` from one type; return how much was actually removed.
// If less is stored than requested, drain it to zero and return what was there;
// otherwise subtract and return the full requested amount.
float StorageClass::RemoveAmount(float amount, int index)
{
    float* p = &(&this->Tiberium1)[index];
    float reduce = (*p < amount) ? *p : amount;
    *p = *p - reduce;
    return reduce;
}

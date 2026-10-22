// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI and seven-slot vtables at 0x7E4DB8/0x7E4E78 and
// 0x7F57E8/0x7F57C8 establish VectorClass<T> and its dynamic base split.
// Clear bodies 0x477D20/0x477840 and 0x724D80/0x724C30 confirm touched
// offsets. The ordinary destructor body is distinct from virtual Clear.
// Slot6 returns scalar/pointer T in EAX; aggregate targets 0x4D2980,
// 0x50E5B0, 0x5D05F0 and 0x769D30 use the hidden-result-pointer ABI.
// Original names for slots 5 and 6 and pointee const qualifiers in slot5
// remain unconfirmed. Actual-template offset/size assertions are compiled
// in vector_class_layout_asserts.cpp after explicit instantiation for VC6.
#ifndef GG_MATCH_CORE_VECTOR_CLASS_H
#define GG_MATCH_CORE_VECTOR_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// FUNCTION: GAMEMD 0x7C8B3D (reloc) -- the retail allocator used by the bodies.
// LIBRARY: GAMEMD 0x7C8B3D — CRT free.
extern "C" void __cdecl gg_free(void*);

// VectorClass<T> has seven 4-byte slots. In VectorClass<int>, the raw
// address point 0x7E4DB8 puts Clear at +0x0C; the ToolTip base address point
// 0x7F57E8 does the same. Unknown slot names are retained where bytes establish
// only an argument/result shape, not a source-level name.
template<class T> class VectorClass {
public:
    VectorClass(int capacity = 0, T* pMem = 0);
    VectorClass(const VectorClass<T>& other);
    VectorClass<T>& operator=(const VectorClass<T>& other);
    virtual ~VectorClass();
    virtual bool operator==(const VectorClass<T>&) const;
    virtual bool SetCapacity(int capacity, T* pMem);
    virtual void Clear();
    virtual int FindItemIndex(const T& item) const;
    virtual int Slot5(T* elementAddress) const;
    virtual T Slot6(int index) const;

    T* Items;                    // +0x04
    int Capacity;                // +0x08
    bool IsInitialized;          // +0x0C
    bool IsAllocated;            // +0x0D
    unsigned char unknown_0E[2]; // +0x0E
};

template<class T> VectorClass<T>::~VectorClass() {
    if (Items != 0 && IsAllocated) { gg_free(Items); Items = 0; }
    IsAllocated = false;
    Capacity = 0;
}

template<class T> void VectorClass<T>::Clear() {
    if (Items != 0 && IsAllocated) { gg_free(Items); Items = 0; }
    IsAllocated = false;
    Capacity = 0;
}

// RTTI proves DynamicVectorClass<T> : VectorClass<T> at offset zero. Its seven
// slots preserve the same order while slots 2–5 have dynamic-vector bodies;
// count and capacity increment occupy the two added dwords.
template<class T> class DynamicVectorClass : public VectorClass<T> {
public:
    DynamicVectorClass(int capacity = 0, T* pMem = 0);
    DynamicVectorClass(const DynamicVectorClass<T>& other);
    virtual bool SetCapacity(int capacity, T* pMem);
    virtual void Clear();
    virtual int FindItemIndex(const T& item) const;
    virtual int Slot5(T* elementAddress) const;
    int Count() const { return ActiveCount; }
    // Inline by-index removal (vector_class_operations.h).
    bool Delete(int index);
    // Defined in vector_class_operations.h when the element type is complete.
    bool RemoveItem(const T& item);
    int ActiveCount;       // +0x10
    int CapacityIncrement; // +0x14
};

template<class T> void DynamicVectorClass<T>::Clear() {
    ActiveCount = 0;
    if (this->Items != 0 && this->IsAllocated) {
        gg_free(this->Items);
        this->Items = 0;
    }
    this->IsAllocated = false;
    this->Capacity = 0;
}



#endif // GG_MATCH_CORE_VECTOR_CLASS_H

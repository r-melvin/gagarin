// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// ToolTip pointer methods at 0x724C60/80/90, 0x724CD0, 0x724DB0/F0,
// 0x724E10/C0 establish the operations below; raw RTTI binds this element
// specialization to VectorClass<const ToolTip*> and DynamicVectorClass.
// Pointer-array new[] lowers to operator new(size_t) at retail 0x7C8E17.
// These operations are verified for the ToolTip pointer specialization;
// other element types require their own binary confirmation.
// Pointer-element removal is inlined in ToolTipManager::Remove at 0x724730:
// find index via slot 4, decrement Count, then shift the remaining entries.
// This definition is separate so storage/Clear-only instantiations can use
// forward-declared aggregate types without instantiating element assignment.
#ifndef GG_MATCH_CORE_VECTOR_CLASS_OPERATIONS_H
#define GG_MATCH_CORE_VECTOR_CLASS_OPERATIONS_H
#include "vector_class.h"

// Capacity constructors at 0x477BE0/0x477DB0 and 0x478790/0x68C200 establish
// int and TechnoType pointer specializations. Unlike SetCapacity, the allocation
// path sets ownership without a null-result test. Further pointer specializations
// are verified individually in vector_capacity_constructors.cpp; other emitted
// constructors are unclaimed.
template<class T> VectorClass<T>::VectorClass(int capacity, T* pMem)
    : Items(0), Capacity(capacity), IsInitialized(true), IsAllocated(false)
{
    if (capacity != 0) {
        if (pMem != 0)
            Items = pMem;
        else {
            Items = new T[capacity];
            IsAllocated = true;
        }
    }
}

template<class T> DynamicVectorClass<T>::DynamicVectorClass(int capacity, T* pMem)
    : VectorClass<T>(capacity, pMem)
{
    this->CapacityIncrement = 10;
    this->Count = 0;
}

// The base copy/assignment path is expanded into DynamicVectorClass<int>'s
// copy constructor at 0x4779E0. It copies Capacity elements, not Count, and
// retains Capacity on allocation failure. Other copy specializations and a
// separate base assignment/copy entry have not been matched.
template<class T> inline VectorClass<T>::VectorClass(const VectorClass<T>& other)
    : Items(0), Capacity(0), IsInitialized(true), IsAllocated(false)
{
    *this = other;
}

template<class T> inline VectorClass<T>& VectorClass<T>::operator=(const VectorClass<T>& other)
{
    if (this != &other) {
        this->Clear();
        this->Capacity = other.Capacity;
        if (this->Capacity != 0) {
            this->Items = new T[this->Capacity];
            if (this->Items != 0) {
                this->IsAllocated = true;
                for (int i = 0; i < this->Capacity; ++i)
                    this->Items[i] = other.Items[i];
            }
        } else {
            this->Items = 0;
            this->IsAllocated = false;
        }
    }
    return *this;
}

template<class T> inline DynamicVectorClass<T>::DynamicVectorClass(const DynamicVectorClass<T>& other)
    : VectorClass<T>(other), Count(other.Count), CapacityIncrement(other.CapacityIncrement)
{
}

template<class T>
bool DynamicVectorClass<T>::RemoveItem(const T& item)
{
    int index = FindItemIndex(item);
    if (index != -1 && index < Count) {
        Count = Count - 1;
        for (; index < Count; ++index)
            this->Items[index] = this->Items[index + 1];
        return true;
    }
    return false;
}
template<class T> bool VectorClass<T>::operator==(const VectorClass<T>& other) const
{
    if (this->Capacity == other.Capacity) {
        for (int i = 0; i < this->Capacity; ++i) {
            if (this->Items[i] != other.Items[i]) return false;
        }
        return true;
    }
    return false;
}

template<class T> int VectorClass<T>::FindItemIndex(const T& item) const
{
    if (!this->IsInitialized) return 0;
    for (int i = 0; i < this->Capacity; ++i) {
        if (this->Items[i] == item) return i;
    }
    return -1;
}

template<class T> int VectorClass<T>::Slot5(T* elementAddress) const
{
    if (!this->IsInitialized) return 0;
    return (int)(((unsigned long)elementAddress - (unsigned long)this->Items) / sizeof(T));
}

template<class T> T VectorClass<T>::Slot6(int index) const
{
    return this->Items[index];
}

template<class T> int DynamicVectorClass<T>::FindItemIndex(const T& item) const
{
    for (int i = 0; i < this->Count; ++i) {
        if (this->Items[i] == item) return i;
    }
    return -1;
}

template<class T> int DynamicVectorClass<T>::Slot5(T* elementAddress) const
{
    if (!this->IsInitialized) return 0;
    return (int)(((unsigned long)elementAddress - (unsigned long)this->Items) / sizeof(T));
}


template<class T> bool VectorClass<T>::SetCapacity(int capacity, T* pMem) {
    if (capacity != 0) {
        T* newItems;
        this->IsInitialized = false;
        if (pMem == 0)
            newItems = new T[capacity];
        else
            newItems = pMem;
        this->IsInitialized = true;
        if (newItems == 0)
            return false;

        if (this->Items != 0) {
            int copyCount = this->Capacity;
            if (capacity < copyCount)
                copyCount = capacity;
            for (int i = 0; i < copyCount; ++i)
                newItems[i] = this->Items[i];
            if (this->IsAllocated) {
                gg_free(this->Items);
                this->Items = 0;
            }
        }

        this->Items = newItems;
        this->Capacity = capacity;
        this->IsAllocated = (this->Items != 0 && pMem == 0);
    } else {
        this->Clear();
    }
    return true;
}

template<class T> bool DynamicVectorClass<T>::SetCapacity(int capacity, T* pMem) {
    if (VectorClass<T>::SetCapacity(capacity, pMem)) {
        if (this->Capacity < this->Count)
            this->Count = this->Capacity;
        return true;
    }
    return false;
}


#endif

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
#include <new.h>
#include "vector_class.h"

// Capacity constructors at 0x477BE0/0x477DB0, 0x478790/0x68C200 and the
// eight-byte element family 0x5106E0/0x510780/0x58AC70/0x6CF8F0. Caller
// storage is constructed in place with placement array-new; otherwise the
// array is allocated and owned (ownership is set without a null test).
template<class T> VectorClass<T>::VectorClass(int capacity, T* pMem)
    : Items(0), Capacity(capacity), IsInitialized(true), IsAllocated(false)
{
    if (capacity != 0) {
        if (pMem != 0)
            Items = new((void*)pMem) T[capacity];
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

// By-index removal, inline: expanded in ListClass::RemoveItem at 0x557730
// (its bound test repeats the caller's). Out-of-line instances exist where
// cl declines to inline it.
template<class T>
inline bool DynamicVectorClass<T>::Delete(int index)
{
    if (index < Count) {
        Count--;
        for (int i = index; i < Count; i++)
            this->Items[i] = this->Items[i + 1];
        return true;
    }
    return false;
}

// Append, inline: expanded in ListClass::AddItem (0x5576A0). Growth by
// CapacityIncrement happens only when the vector owns its block or has none.
// The new index is taken before the store, so Count is loaded ahead of
// Items, which is retail's order.
template<class T>
inline bool DynamicVectorClass<T>::AddItem(const T& item)
{
    if (Count >= this->Capacity) {
        if ((this->IsAllocated || this->Capacity == 0) && CapacityIncrement > 0) {
            if (!this->SetCapacity(this->Capacity + CapacityIncrement, 0))
                return false;
        } else {
            return false;
        }
    }
    int index = Count;
    Count = index + 1;
    this->Items[index] = item;
    return true;
}

// By-value removal through the virtual FindItemIndex (slot +0x10). Inline in
// SuperClass::Lose (0x6CB7B0) and ToolTipManager::Remove (0x724730); the call
// through `this` inside the inlined body keeps the dispatch indirect.
template<class T>
inline bool DynamicVectorClass<T>::RemoveItem(const T& item)
{
    int index = FindItemIndex(item);
    if (index != -1)
        return Delete(index);
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


// Caller storage is constructed in place, as in the constructor: the
// eight-byte element instances 0x40B180, 0x50EEE0, 0x50F210 and 0x6CF5A0 run
// the element constructor loop over pMem as well as over newly allocated
// storage. For pointer and other trivially constructed elements the placement
// form emits no code.
template<class T> bool VectorClass<T>::SetCapacity(int capacity, T* pMem) {
    if (capacity != 0) {
        T* newItems;
        this->IsInitialized = false;
        if (pMem == 0)
            newItems = new T[capacity];
        else
            newItems = new((void*)pMem) T[capacity];
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
                delete[] this->Items;
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

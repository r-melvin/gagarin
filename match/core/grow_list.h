// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The growable array behind 0x7ACA00/0x7AD790/0x7ADB00/0x7AE5D0 (Insert),
//   0x7AF000 (Grow, out of line for the 4-byte handle element) and the handle
//   tables of 0x797C20/0x798140: {count, capacity, data}, no vtable, grown by
//   doubling with a minimum of 10.
#ifndef GG_MATCH_CORE_GROW_LIST_H
#define GG_MATCH_CORE_GROW_LIST_H

#include <stddef.h>
#include <string.h>
#include <new.h>

template<class Elem>
struct GrowList
{
    int   Count;      // +0x00
    int   Capacity;   // +0x04
    Elem* Data;       // +0x08

    bool Grow();
    bool Insert(const Elem& item, int index);
    // The inline front insertion 0x797C20 expands in place (Grow stays a call).
    bool InlineAdd_00797C20(const Elem& item)
    {
        int index = 0;
        if (Count < 0) {
            index = Count;
        }
        if (index >= Capacity) {
            Grow();
        }
        if (Count >= Capacity) {
            Grow();
        }
        if (index < Count) {
            memmove(&Data[index + 1], &Data[index], (Count - index) * sizeof(Elem));
        }
        new (&Data[index]) Elem(item);
        Count++;
        return true;
    }
};

#ifndef GG_GROW_LIST_INSERT_DECL_ONLY
template<class Elem>
inline bool GrowList<Elem>::Grow()
{
    if (Count < Capacity) {
        return false;
    }
    int size = Count * 2;
    if (size < 10) {
        size = 10;
    }
    Elem* data = (Elem*)operator new(size * sizeof(Elem));
    memset(data, 0, size * sizeof(Elem));
    if (Data) {
        memcpy(data, Data, Count * sizeof(Elem));
    }
    operator delete(Data);
    Data = data;
    Capacity = size;
    return true;
}

template<class Elem>
bool GrowList<Elem>::Insert(const Elem& item, int index)
{
    if (index > Count) {
        index = Count;
    }
    if (index >= Capacity) {
        Grow();
    }
    Grow();
    if (index < Count) {
        memmove(&Data[index + 1], &Data[index], (Count - index) * sizeof(Elem));
    }
    new (&Data[index]) Elem(item);
    Count++;
    return true;
}
#endif

#include "../_rt/gg_static_assert.h"

// The 4-byte handle element of the 0x7AE5D0 instance.
struct GrowListHandle
{
    // FUNCTION: GAMEMD 0x7B4620 (decl; reloc) -- default constructor.
    GrowListHandle();
    // FUNCTION: GAMEMD 0x7B4690 (decl; reloc) -- copy constructor.
    GrowListHandle(const GrowListHandle& other);
    // FUNCTION: GAMEMD 0x7AD330 (decl; reloc) -- destructor; retail calls the
    // scalar deleting form with a zero flag.
    ~GrowListHandle();
    // FUNCTION: GAMEMD 0x7B46F0 (decl; reloc) -- free the text.
    void Release();
    // FUNCTION: GAMEMD 0x7B5A40 (decl; reloc) -- assign from a C string.
    GrowListHandle& operator=(const char* text);

    void* unknown_00;   // +0x00
};
// `LEA ECX,[EAX+ESI*4]` addresses the slots in 0x7AE5D0.
GG_STATIC_ASSERT(sizeof(GrowListHandle) == 4);

#endif  // GG_MATCH_CORE_GROW_LIST_H

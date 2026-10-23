// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Remaining layout view for slot 3 at 0x69C4A0, reached through the
// TypeList<DiskID> vtable 0x7F12D4. Its Clear behavior/element type are
// confirmed; whether the declaring class is DynamicVectorClass or TypeList
// remains unresolved. This is not a recovered C++ destructor.
#ifndef GG_MATCH_CORE_VECTOR_COUNTED_DTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_COUNTED_DTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) -- CRT free.
extern "C" void __cdecl gg_free(void* block);

// The counted vector template. As in the plain family the vtable pointer is an
// explicit member rather than a compiler-managed one: this body never writes
// it, so nothing here depends on the template being polymorphic, and declaring
// it explicitly keeps the layout pinned at the offsets read off the binary.
template<class T>
struct CountedVector
{
    char* Vptr;         // +0x0000
    T*    Items;        // +0x0004
    int   Capacity;     // +0x0008
    char  _pad00C;      // +0x000C
    char  IsAllocated;  // +0x000D
    char  _pad00E[2];   // +0x000E
    int   Count;        // +0x0010

    void Destroy();
};

template<class T>
void CountedVector<T>::Destroy()
{
    this->Count = 0;
    if (this->Items != 0 && this->IsAllocated != 0) {
        gg_free(this->Items);
        this->Items = 0;
    }
    this->IsAllocated = 0;
    this->Capacity = 0;
}

#endif  // GG_MATCH_CORE_VECTOR_COUNTED_DTOR_FAMILY_METHODS_H

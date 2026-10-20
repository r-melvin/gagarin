// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x477840 and its 160 siblings: the plain (non-deleting)
//   destructor of the counted vector template. It is the plain vector teardown
//   of match/core/vector_plain_dtor_family_methods.h with one extra store, the
//   element count at +0x10 cleared from the same zero register, emitted before
//   the ownership test. Members touched: the items pointer at +4, the capacity
//   at +8, the allocated flag at +0xD and the count at +0x10.
//
//   THE ELEMENT TYPES ARE NO LONGER PLACEHOLDERS. The body stores no vtable,
//   so it is bound by vtable membership instead: each of the 161 addresses
//   occupies slot 3 of a retail vtable whose complete object locator names the
//   class. 160 come out `DynamicVectorClass<T>` -- which is exactly what the
//   extra store at +0x10 is: the element count. The remaining one is called
//   out at its instantiation. The enclosing name below stays `CountedVector`
//   because retail's symbol is `??1?$DynamicVectorClass@<T>@@UAE@XZ` and a
//   virtual destructor does not compile to these bytes (VC6 emits a vptr
//   store at its head; retail's body has none); it is a modelling stand-in
//   for `DynamicVectorClass<T>::~DynamicVectorClass`, not a retail name.
//
//   These 161 bodies are not 161 functions in retail's source. They are one
//   class template's plain destructor, emitted once per instantiation as its
//   own COMDAT. This header carries the template; the translation unit beside
//   it carries one explicit instantiation per retail address and the compiler
//   generates the body for each. Nothing in the body varies across the family
//   -- no vtable, no element size, no cleanup-shape difference -- so the
//   element type is the template's only parameter, and the 161 emitted COMDATs
//   are byte-identical to one another.
//
//   KNOWN LIMITATION -- this file is a staging ground, not a destination. The
//   TU-partition work established that MSVC6 emits each template instantiation
//   as a COMDAT into the translation unit that instantiated it. These 161
//   instantiations therefore belong to many different original Westwood
//   translation units, not to one. Grouping them in a single sweep file is
//   correct for matching bytes now and wrong for reproducing retail's link
//   order eventually; they will have to be redistributed to their owning TUs
//   when the partition is reconstructed.
#ifndef GG_MATCH_CORE_VECTOR_COUNTED_DTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_COUNTED_DTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) -- CRT free.
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

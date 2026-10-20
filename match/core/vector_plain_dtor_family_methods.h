// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x477D20 and its 161 siblings: the plain (non-deleting)
//   destructor of the vector template, one per instantiation and byte-identical
//   across all of them because it touches no vtable and nothing in it depends
//   on the element type beyond the pointer. Members touched: the items pointer
//   at +4, the capacity at +8 and the allocated flag at +0xD; zero is held in a
//   register and used for both compares and all three stores.
//
//   These 162 bodies are not 162 functions in retail's source. They are one
//   class template's plain destructor, emitted once per instantiation as its
//   own COMDAT. This header carries the template; the translation unit beside
//   it carries one explicit instantiation per retail address and the compiler
//   generates the body for each.
//
//   THE ELEMENT TYPES ARE NO LONGER OPAQUE. This body stores no vtable, so it
//   cannot be bound the way the scalar-deleting family is; it is bound by
//   vtable membership instead. Each of the 162 addresses occupies slot 3 of
//   exactly one retail vtable, and that vtable's complete object locator (the
//   dword four bytes below it, whose +0xC is the type descriptor, whose name
//   starts eight bytes in) names the class. All 162 come out `VectorClass<T>`
//   -- 162 addresses, 162 distinct classes, one-to-one -- and none appears in
//   a second table, so the inherited-slot ambiguity of batch fifty-seven does
//   not arise here (VectorClass has no base). The translation unit beside this
//   header instantiates each with that class's own element type, declared so
//   as to reproduce the RTTI mangling exactly.
//
//   The enclosing name stays `PlainVector`: retail's symbol is
//   `??1?$VectorClass@<T>@@UAE@XZ`, but spelling it as the class's own virtual
//   destructor does not compile to these bytes -- VC6 puts a vptr store at the
//   head of a virtual destructor and retail's body has none, scoring 26.3%
//   with the whole body shifted by one `mov`. `PlainVector<T>::Destroy` is a
//   modelling stand-in for `VectorClass<T>::~VectorClass`, recorded as such.
//
//   Unlike the scalar deleting destructor family in
//   vector_dtor_family_methods.{h,cpp}, this body names no vtable, so the 162
//   COMDATs are byte-identical to one another and carry the same single
//   relocation (the CRT free). The link-time identity that would let the linker
//   fold them is real; it does not affect the per-function object-level match,
//   which is what this file is scored on.
//
//   KNOWN LIMITATION -- this file is a staging ground, not a destination. The
//   TU-partition work established that MSVC6 emits each template instantiation
//   as a COMDAT into the translation unit that instantiated it. These 162
//   instantiations therefore belong to many different original Westwood
//   translation units, not to one. Grouping them in a single sweep file is
//   correct for matching bytes now and wrong for reproducing retail's link
//   order eventually; they will have to be redistributed to their owning TUs
//   when the partition is reconstructed.
#ifndef GG_MATCH_CORE_VECTOR_PLAIN_DTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_PLAIN_DTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) -- CRT free.
extern "C" void __cdecl gg_free(void* block);

// The vector template as this family sees it. The vtable pointer is an
// explicit member here rather than a compiler-managed one: the plain
// destructor never writes it, so nothing in these bodies depends on the
// template being polymorphic, and declaring it explicitly keeps the layout
// pinned at the offsets read off the binary.
template<class T>
struct PlainVector
{
    char* Vptr;         // +0x0000
    T*    Items;        // +0x0004
    int   Capacity;     // +0x0008
    char  _pad00C;      // +0x000C
    char  IsAllocated;  // +0x000D

    void Destroy();
};

template<class T>
void PlainVector<T>::Destroy()
{
    if (this->Items != 0 && this->IsAllocated != 0) {
        gg_free(this->Items);
        this->Items = 0;
    }
    this->IsAllocated = 0;
    this->Capacity = 0;
}

#endif  // GG_MATCH_CORE_VECTOR_PLAIN_DTOR_FAMILY_METHODS_H

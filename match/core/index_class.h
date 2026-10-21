// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference | YRpp-cross-check
//   Layout and every member offset were read numerically off the user's retail
//   gamemd.exe v1.001 through the local Ghidra CLI. EA's GPLv3 Red Alert 1
//   release (CODE/SEARCH.H) and the consult-only YRpp header IndexClass.h were
//   read for names and algorithm shape only; nothing is transcribed from either
//   and every offset below is re-derived from the binary.
//
// IndexClass is Westwood's small sorted-index container: a flat array of
// {ID, Data} pairs kept lazily sorted, searched by a hand-rolled binary search,
// with a one-element cache ("Archive") in front of it so a repeated lookup of
// the same ID costs one compare. It is the lookup behind INIClass and the type
// tables, and it is a pure utility class, the same one RA1 carries.
//
// Layout, confirmed numerically:
//   +0x00 IndexTable   the array         (`MOV EDX,dword ptr [ESI]` then
//                                         `MOV [EDX+ECX*8]` — 8-byte stride)
//   +0x04 IndexCount   entries in use    (`MOV ECX,[ESI+4]`, `INC ECX`)
//   +0x08 IndexSize    entries allocated (`MOV EAX,[ESI+8]`, `ADD EAX,EBX`)
//   +0x0C IsSorted     one byte          (`MOV byte ptr [ESI+0xC],0`)
//   +0x10 Archive      cached node       (`MOV dword ptr [EBX+0x10],EDX`)
// The element is 8 bytes: `LEA EDX,[EBP*8]` sizes the allocation and the
// qsort call pushes a literal 8 as the element width.
//
// Both the key and the value reach every entry point by address, never by
// value: the prologue does `MOV ESI,dword ptr [ESP+0x14]` and then
// `MOV EDX,dword ptr [ESI]`, and AddIndex reads its two arguments through two
// separate pointers. So the parameters are const references, which is also why
// AddIndex's `RET 8` carries two dwords while only one of them is ever read
// before the first POP shifts the frame.
//
// The retail binary carries two instantiations of this template side by side.
// Their bodies are byte-identical apart from the comparator address and the
// address of the default value, both of which are relocations the differ
// normalises. The second instantiation is modelled below as its own class
// rather than as a template argument: MSVC 6 template instantiation order is
// not something the match depends on, and two plain classes keep each body
// where the tree's address ordering wants it.
#ifndef GG_MATCH_CORE_INDEX_CLASS_H
#define GG_MATCH_CORE_INDEX_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Game heap and CRT primitives, declared so cl emits normalised call relocs.
// LIBRARY: GAMEMD 0x7C8E17  operator new[] / malloc (push size; call; add esp,4)
// LIBRARY: GAMEMD 0x7C8B3D  operator delete[] / free
// LIBRARY: GAMEMD 0x7C8B48  qsort (base, count, width, compare; cdecl)
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
extern "C" void  __cdecl FUN_007C8B3D(void* block);
extern "C" void  __cdecl FUN_007C8B48(void* base, unsigned int num,
                                      unsigned int width,
                                      int (__cdecl* compare)(const void*, const void*));

// Entry and section lookups use distinct binary-confirmed default cells.
#include "../_layout/ini_index_defaults.h"

// The primary instantiation. Data is modelled as a pointer; only its width
// (four bytes, giving the 8-byte node stride) reaches the code.
class IndexClass
{
public:
    struct NodeElement
    {
        int   ID;
        void* Data;
    };

    // FUNCTION: GAMEMD 0x52B080
    IndexClass();

    // FUNCTION: GAMEMD 0x52B0A0
    bool AddIndex(const int& id, void* const& data);
    // FUNCTION: GAMEMD 0x52B170
    bool IsPresent(const int& id) const;
    // FUNCTION: GAMEMD 0x52B210
    void* const& FetchIndex(const int& id) const;
    // FUNCTION: GAMEMD 0x52B2B0
    bool RemoveIndex(const int& id);

    // FUNCTION: GAMEMD 0x52B6A0
    static int __cdecl Comparator(const void* ptr1, const void* ptr2);

    // The two halves every public operation shares. Retail has both expanded
    // into their callers, so they are forced inline and declared here rather
    // than in the translation unit; `__forceinline` has to sit on the
    // declaration or cl leaves one of the copies as a call.
    __forceinline bool IncreaseTableSize(int amount);
    __forceinline NodeElement* SearchForNode(const int& id) const;
    __forceinline bool IsPresentImpl(const int& id) const;

    NodeElement* IndexTable;   // +0x00
    int          IndexCount;   // +0x04
    int          IndexSize;    // +0x08
    bool         IsSorted;     // +0x0C
    NodeElement* Archive;      // +0x10
};

GG_STATIC_ASSERT(offsetof(IndexClass, IndexTable) == 0x00 &&
                 offsetof(IndexClass, IndexCount) == 0x04 &&
                 offsetof(IndexClass, IndexSize) == 0x08 &&
                 offsetof(IndexClass, IsSorted) == 0x0C &&
                 offsetof(IndexClass, Archive) == 0x10 &&
                 sizeof(IndexClass) == 0x14 &&
                 sizeof(IndexClass::NodeElement) == 0x08 &&
                 offsetof(IndexClass::NodeElement, Data) == 0x04);

// The second retail instantiation. Same layout, same bodies; only the two
// lookups and the comparator have their own copies in the binary.
class IndexClassB
{
public:
    struct NodeElement
    {
        int   ID;
        void* Data;
    };

    // FUNCTION: GAMEMD 0x52B390
    bool IsPresent(const int& id) const;
    // FUNCTION: GAMEMD 0x52B430
    void* const& FetchIndex(const int& id) const;

    // FUNCTION: GAMEMD 0x52B720
    static int __cdecl Comparator(const void* ptr1, const void* ptr2);

    __forceinline NodeElement* SearchForNode(const int& id) const;
    __forceinline bool IsPresentImpl(const int& id) const;

    NodeElement* IndexTable;   // +0x00
    int          IndexCount;   // +0x04
    int          IndexSize;    // +0x08
    bool         IsSorted;     // +0x0C
    NodeElement* Archive;      // +0x10
};

GG_STATIC_ASSERT(offsetof(IndexClassB, Archive) == 0x10 &&
                 sizeof(IndexClassB) == 0x14);

#endif  // GG_MATCH_CORE_INDEX_CLASS_H

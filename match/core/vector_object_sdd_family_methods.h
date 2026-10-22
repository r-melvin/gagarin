// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4E0D80 and its seven siblings. Members come straight off
//   the instructions: the vtable pointer at +0 (`MOV dword ptr [ESI],imm32`),
//   the items pointer at +4 (`MOV EAX,[ESI+4]`, `MOV dword ptr [ESI+4],0`),
//   the capacity at +8 and the allocated flag at +0xD, with the deleting-bit
//   flags byte read from the stack at `[ESP+8]`.
//
//   This is the 73-byte scalar-deleting destructor of
//   match/core/vector_dtor_family_methods.cpp with one substitution: the
//   element block is released as a *cookied object array* rather than as a raw
//   block. Retail's `MOV ECX,[EAX-4]; ADD EAX,-4; DEC ECX; PUSH EAX; CALL
//   free` is VC6's vector destructor iterator inlined with an empty element
//   destructor — it loads the element count that `new T[n]` parked in the
//   dword below the array, steps the pointer back over it, decrements the
//   (now unused) counter because the destructor loop collapsed to nothing, and
//   frees the real block. The extra null test in front of it is the one
//   `delete[]` itself emits. 84 bytes against the raw family's 73.
//
//   BUILD NOTE: this TU must be compiled without /GX, which the project
//   default no longer has. Under /GX cl refuses to
//   inline the vector destructor iterator and emits an out-of-line
//   `??_M`-style call with four pushed arguments instead (25.7%); with
//   exception handling off it inlines exactly retail's five instructions and
//   the whole family reaches 100%. The element size does not reach the code —
//   1-, 4- and 8-byte elements all produce the same bytes — so the element
//   type is left opaque.
//
//   These entry points carry no name in the binary or in the YRpp map and keep
//   their placeholder names.
#ifndef GG_MATCH_CORE_VECTOR_OBJECT_SDD_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_OBJECT_SDD_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);

// VTABLE: GAMEMD 0x007E9264
extern char VT_007E9264;
// VTABLE: GAMEMD 0x007EAAA4
extern char VT_007EAAA4;
// VTABLE: GAMEMD 0x007F4840
extern char VT_007F4840;
// VTABLE: GAMEMD 0x007F6EF4
extern char VT_007F6EF4;

// The element type is opaque: all that reaches the code is that it has a
// destructor (hence the array cookie) whose body is empty.
struct ObjElem_004E0D80
{
    int Opaque;
    ~ObjElem_004E0D80() {}
};

struct ObjVector_004E0D80
{
    char*             Vptr;         // +0x0000
    ObjElem_004E0D80* Items;        // +0x0004
    int               Capacity;     // +0x0008
    char              _pad00C;      // +0x000C
    char              IsAllocated;  // +0x000D

    // FUNCTION: GAMEMD 0x004E0D80
    ObjVector_004E0D80* FUN_004E0D80(char flags);
    // FUNCTION: GAMEMD 0x004E0E20
    ObjVector_004E0D80* FUN_004E0E20(char flags);
    // FUNCTION: GAMEMD 0x00510400
    ObjVector_004E0D80* FUN_00510400(char flags);
    // FUNCTION: GAMEMD 0x005104A0
    ObjVector_004E0D80* FUN_005104A0(char flags);
    // FUNCTION: GAMEMD 0x006F2680
    ObjVector_004E0D80* FUN_006F2680(char flags);
    // FUNCTION: GAMEMD 0x006F2720
    ObjVector_004E0D80* FUN_006F2720(char flags);
    // FUNCTION: GAMEMD 0x00763FF0
    ObjVector_004E0D80* FUN_00763FF0(char flags);
    // FUNCTION: GAMEMD 0x00764050
    ObjVector_004E0D80* FUN_00764050(char flags);
};
GG_STATIC_ASSERT(offsetof(ObjVector_004E0D80, Vptr)        == 0x0);
GG_STATIC_ASSERT(offsetof(ObjVector_004E0D80, Items)       == 0x4);
GG_STATIC_ASSERT(offsetof(ObjVector_004E0D80, Capacity)    == 0x8);
GG_STATIC_ASSERT(offsetof(ObjVector_004E0D80, IsAllocated) == 0xD);

#define GG_VECTOR_OBJECT_SDD_BODY(ADDR, VT)                               \
ObjVector_004E0D80* ObjVector_004E0D80::FUN_##ADDR(char flags)            \
{                                                                         \
    this->Vptr = &VT_##VT;                                                \
    if (this->Items != 0 && this->IsAllocated) {                          \
        delete[] this->Items;                                             \
        this->Items = 0;                                                  \
    }                                                                     \
    this->IsAllocated = 0;                                                \
    this->Capacity = 0;                                                   \
    if (flags & 1) {                                                      \
        gg_free(this);                                                    \
    }                                                                     \
    return this;                                                          \
}

#endif  // GG_MATCH_CORE_VECTOR_OBJECT_SDD_FAMILY_METHODS_H

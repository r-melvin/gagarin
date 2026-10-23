// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x765B60 and its seven siblings. Members come straight off
//   the instructions: the vtable pointer at +0 (`MOV dword ptr [ESI],imm32`),
//   the items pointer at +4 (`MOV ECX,[ESI+4]`, `MOV dword ptr [ESI+4],0`),
//   the capacity at +8 and the allocated flag at +0xD, with the deleting-bit
//   flags byte read from the stack at `[ESP+8]`.
//
//   This is the 73-byte scalar-deleting destructor of
//   match/core/vector_dtor_family_methods.cpp with the element release
//   replaced by `MOV EAX,[ECX]; PUSH 3; CALL dword ptr [EAX]` — the element
//   type's own slot-0 deleting destructor invoked with MSVC's flag 3
//   (bit 0 = free the block, bit 1 = it is an array), which is what
//   `delete[] p` compiles to when the element type has a virtual destructor.
//   The receiver stays in ECX from the member load, so the element's
//   destructor is __thiscall, not __stdcall. 74 bytes against the raw
//   family's 73.
//
//   It is NOT the already-matched 74-byte family in
//   match/core/vector_ctor_pod_family_methods.cpp: same length, different
//   shape (that one has prefix 568BF18B4604, this one 568BF18B4E04, and the
//   difference is exactly that the items pointer is loaded into ECX here so
//   it can serve as the receiver of the virtual call).
//
//   These entry points carry no name in the binary or in the YRpp map and keep
//   their placeholder names.
#ifndef GG_MATCH_CORE_VECTOR_POLYMORPHIC_SDD_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_POLYMORPHIC_SDD_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);

// VTABLE: GAMEMD 0x007F6F7C
extern char VT_007F6F7C;
// VTABLE: GAMEMD 0x007F6FF4
extern char VT_007F6FF4;
// VTABLE: GAMEMD 0x007F7184
extern char VT_007F7184;
// VTABLE: GAMEMD 0x007F7230
extern char VT_007F7230;

// The element type is opaque apart from the one fact the code needs: its
// destructor is virtual and occupies slot 0, so `delete[]` routes through it.
struct PolyElem_00765B60
{
    virtual ~PolyElem_00765B60();
};

struct PolyVector_00765B60
{
    char*              Vptr;         // +0x0000
    PolyElem_00765B60* Items;        // +0x0004
    int                Capacity;     // +0x0008
    char               _pad00C;      // +0x000C
    char               IsAllocated;  // +0x000D

    // FUNCTION: GAMEMD 0x00765B60
    PolyVector_00765B60* FUN_00765B60(char flags);
    // FUNCTION: GAMEMD 0x00765C20
    PolyVector_00765B60* FUN_00765C20(char flags);
    // FUNCTION: GAMEMD 0x00766FC0
    PolyVector_00765B60* FUN_00766FC0(char flags);
    // FUNCTION: GAMEMD 0x00767080
    PolyVector_00765B60* FUN_00767080(char flags);
    // FUNCTION: GAMEMD 0x0076A5C0
    PolyVector_00765B60* FUN_0076A5C0(char flags);
    // FUNCTION: GAMEMD 0x0076A680
    PolyVector_00765B60* FUN_0076A680(char flags);
    // FUNCTION: GAMEMD 0x0076BBC0
    PolyVector_00765B60* FUN_0076BBC0(char flags);
    // FUNCTION: GAMEMD 0x0076BC10
    PolyVector_00765B60* FUN_0076BC10(char flags);
};
GG_STATIC_ASSERT(offsetof(PolyVector_00765B60, Vptr)        == 0x0);
GG_STATIC_ASSERT(offsetof(PolyVector_00765B60, Items)       == 0x4);
GG_STATIC_ASSERT(offsetof(PolyVector_00765B60, Capacity)    == 0x8);
GG_STATIC_ASSERT(offsetof(PolyVector_00765B60, IsAllocated) == 0xD);

#define GG_VECTOR_POLY_SDD_BODY(ADDR, VT)                                  \
PolyVector_00765B60* PolyVector_00765B60::FUN_##ADDR(char flags)           \
{                                                                          \
    this->Vptr = &VT_##VT;                                                 \
    if (this->Items != 0 && this->IsAllocated) {                           \
        delete[] this->Items;                                              \
        this->Items = 0;                                                   \
    }                                                                      \
    this->IsAllocated = 0;                                                 \
    this->Capacity = 0;                                                    \
    if (flags & 1) {                                                       \
        gg_free(this);                                                     \
    }                                                                      \
    return this;                                                           \
}

#endif  // GG_MATCH_CORE_VECTOR_POLYMORPHIC_SDD_FAMILY_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI at 0x4E0950 and 0x4E0AB0 and their six siblings. Members come
//   straight off the instructions: the items pointer at +4 (`MOV EAX,[ESI+4]`,
//   `MOV dword ptr [ESI+4],EBX`), the capacity at +8, the allocated flag at
//   +0xD (`CMP byte ptr [ESI+0xD],BL`) and, in the 53-byte shape only, the
//   live count at +0x10 zeroed before anything else.
//
//   These are the Clear() of the same growable vector whose scalar-deleting
//   destructor is already matched in
//   match/core/vector_object_sdd_family_methods.cpp, with the vtable seat and
//   the deleting tail removed: the element block is released as a *cookied
//   object array*, so retail's `MOV ECX,[EAX-4]; ADD EAX,-4; DEC ECX; PUSH
//   EAX; CALL free` is VC6's vector destructor iterator inlined with an empty
//   element destructor. The element type itself never reaches the code, so it
//   stays opaque. Unlike the polymorphic Clear() family, both early guards
//   here land on the IsAllocated reset, exactly as they do in the polymorphic
//   family, so only the Items reset lives inside the guarded block.
//
//   BUILD NOTE: the .cpp must be compiled WITHOUT /GX, for exactly the reason
//   recorded on vector_object_sdd_family_methods.h — under /GX cl declines to
//   inline the vector destructor iterator. The .cpp carries the VC6FLAGS line.
//
//   The entry points carry no name in the binary or in the YRpp map and keep
//   their placeholder names.
#ifndef GG_MATCH_CORE_OBJECT_VECTOR_CLEAR_FAMILY_METHODS_H
#define GG_MATCH_CORE_OBJECT_VECTOR_CLEAR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The element type is opaque: all that reaches the code is that it has a
// destructor (hence the array cookie) whose body is empty.
struct ClrElem_004E0950
{
    int Opaque;
    ~ClrElem_004E0950() {}
};

struct ClrVector_004E0950
{
    char*              _pad000;      // +0x0000  (vptr; never touched here)
    ClrElem_004E0950*  Items;        // +0x0004
    int                Capacity;     // +0x0008
    char               _pad00C;      // +0x000C
    char               IsAllocated;  // +0x000D
    char               _pad00E[2];   // +0x000E
    int                Count;        // +0x0010

    void Clear_004E0950();
    void Clear_0050FD70();
    void Clear_006F2400();
    void Clear_00764220();
    void Clear_004E0AB0();
    void Clear_0050E760();
    void Clear_006F21B0();
    void Clear_00763EF0();
};
GG_STATIC_ASSERT(offsetof(ClrVector_004E0950, Items)       == 0x4 &&
                 offsetof(ClrVector_004E0950, Capacity)    == 0x8 &&
                 offsetof(ClrVector_004E0950, IsAllocated) == 0xD &&
                 offsetof(ClrVector_004E0950, Count)       == 0x10 &&
                 sizeof(ClrVector_004E0950)                == 0x14);

// The 50-byte shape: release the block and reset the bookkeeping.
#define GG_OVEC_CLEAR_BODY(TAG)                                           \
void ClrVector_004E0950::Clear_##TAG()                                      \
{                                                                         \
    if (this->Items != 0 && this->IsAllocated) {                          \
        delete[] this->Items;                                             \
        this->Items = 0;                                                  \
    }                                                                     \
    this->IsAllocated = 0;                                                \
    this->Capacity = 0;                                                   \
}

// The 53-byte shape: the same, with the live count zeroed first.
#define GG_OVEC_CLEAR_COUNT_BODY(TAG)                                     \
void ClrVector_004E0950::Clear_##TAG()                                    \
{                                                                         \
    this->Count = 0;                                                      \
    if (this->Items != 0 && this->IsAllocated) {                          \
        delete[] this->Items;                                             \
        this->Items = 0;                                                  \
    }                                                                     \
    this->IsAllocated = 0;                                                \
    this->Capacity = 0;                                                   \
}

#endif  // GG_MATCH_CORE_OBJECT_VECTOR_CLEAR_FAMILY_METHODS_H

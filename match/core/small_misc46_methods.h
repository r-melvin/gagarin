// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, table extents, element strides and call targets read numerically
//   off the user's retail gamemd.exe v1.001 via the local Ghidra CLI at
//   0x42DD60, 0x433940 and 0x473980.
#ifndef GG_MATCH_CORE_SMALL_MISC46_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC46_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size);   // operator new
extern "C" void  __cdecl FUN_007C8B3D(void* block);         // operator delete
extern "C" void  __cdecl FUN_007C93E8(void* block);         // the other free
extern "C" int   __cdecl FUN_007C8D20(const char* a, const char* b);

// ---------------------------------------------------------------------------
// 0x42DD60 — VectorClass<unsigned short> constructor.
//
// `ADD EAX,EAX` before the allocation pins the element at two bytes. A supplied
// array is adopted as-is and leaves IsAllocated clear; only the allocating path
// sets it. A zero capacity does neither.
//
// Class identity RTTI-confirmed (Tier 1, re-verified independently against
// the binary): vtable 0x7E3824 -> complete object locator @0x7E3820 ->
// type descriptor 0x818868 -> name `.?AV?$VectorClass@G@@` (`G` = MSVC's
// mangling code for `unsigned short`). It is not
// `VectorClass<short>` (signed) — the RTTI name is unsigned. Note: the same vtable (0x7E3824) is also
// reseated by FUN_0042DBB0/FUN_0042DC00 in buffer_holder_dtor_methods.cpp -
// those are this same class's own scalar deleting destructors, still modelled
// there under the generic `BufferHolderDtor` shape; reconciling that naming is
// left as follow-up, out of this rename's scope.
// ---------------------------------------------------------------------------
extern char VT_007E3824;   // VTABLE: GAMEMD 0x7E3824

struct VectorClassUnsignedShort
{
    char* Vtable;        // +0x0000
    void* Items;         // +0x0004
    int   Capacity;      // +0x0008
    char  IsInitialized; // +0x000C
    char  IsAllocated;   // +0x000D

    // FUNCTION: GAMEMD 0x42DD60
    VectorClassUnsignedShort(int capacity, void* array);
};
GG_STATIC_ASSERT(offsetof(VectorClassUnsignedShort, IsAllocated) == 0xD);

// ---------------------------------------------------------------------------
// 0x433940 — destructor: release the block at +0x08 through 0x7C93E8, then the
// object at +0x04 together with its two buffers through 0x7C8B3D.
//
// The two frees are different functions, which is why they are declared
// separately rather than treated as one allocator.
// ---------------------------------------------------------------------------
extern char VT_007E3A78;   // VTABLE: GAMEMD 0x7E3A78

struct Sub_00433940
{
    char  _pad000[0x18];
    void* BufferA;   // +0x0018
    void* BufferB;   // +0x001C
};
GG_STATIC_ASSERT(offsetof(Sub_00433940, BufferB) == 0x1C);

struct Obj_00433940
{
    char*         Vtable;   // +0x0000
    Sub_00433940* Sub;      // +0x0004
    void*         Block;    // +0x0008
};
GG_STATIC_ASSERT(offsetof(Obj_00433940, Block) == 0x8);

// FUNCTION: GAMEMD 0x433940
void __fastcall FUN_00433940(Obj_00433940* self);

// ---------------------------------------------------------------------------
// 0x473980 — index of the first table entry either of whose two names matches.
//
// The table at 0x81B7C8 runs to 0x81B820, so 0x58 bytes at eight per entry:
// eleven entries of two `const char*`. A null argument, or no match, answers -1
// (`OR EAX,0xFFFFFFFF`).
// ---------------------------------------------------------------------------
struct NamePair_00473980
{
    const char* First;    // +0x0000
    const char* Second;   // +0x0004
};

// GLOBAL: GAMEMD 0x81B7C8 — eleven entries, ending at 0x81B820.
extern NamePair_00473980 DAT_0081B7C8[11];

// FUNCTION: GAMEMD 0x473980
int __fastcall FUN_00473980(const char* name);

#endif  // GG_MATCH_CORE_SMALL_MISC46_METHODS_H

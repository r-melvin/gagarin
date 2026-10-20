// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x42F1E0: the three embedded vectors sit at +0x4, +0x20
//   and +0x38, so the first is 0x1C bytes and the other two 0x18. Each is
//   constructed by a call to its VectorClass base (0x42FC40 for the first,
//   0x42FCB0 for the other two — the element sizes differ, 0x10 against 4) and
//   then finished inline with the DynamicVectorClass vptr, GrowthStep = 10 and
//   ActiveCount = 0. Field names follow RA1's VectorClass/DynamicVectorClass
//   (structure reference only).
#ifndef GG_MATCH_CORE_TRIPLE_VECTOR_HOST_METHODS_H
#define GG_MATCH_CORE_TRIPLE_VECTOR_HOST_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E3880 — the host.
extern void* const VTBL_007E3880[];
// VTABLE: GAMEMD 0x7E38B0 — the 0x10-byte-element vector.
extern void* const VTBL_007E38B0[];
// VTABLE: GAMEMD 0x7E3890 — the 4-byte-element vector.
extern void* const VTBL_007E3890[];

// The vptr is modelled as a plain member rather than by giving these classes
// virtual functions, because retail assigns the host's vptr *after* all three
// member constructions (0x42F24A). MSVC emits a compiler-generated vptr store
// before member construction, so the store has to be written explicitly to land
// where retail has it.
struct WideVector_0042F1E0
{
    const void* Vptr;        // +0x0000
    void* Vector;            // +0x0004
    int   VectorMax;         // +0x0008
    char  IsValid;           // +0x000C
    char  IsAllocated;       // +0x000D
    char  _pad00E[2];        // +0x000E
    int   ActiveCount;       // +0x0010
    int   GrowthStep;        // +0x0014
    int   _pad018;           // +0x0018

    // FUNCTION: GAMEMD 0x42FC40 — VectorClass base, 0x10-byte element.
    void BaseCtor(unsigned int size, const void* array);
};
GG_STATIC_ASSERT(sizeof(WideVector_0042F1E0) == 0x1C);
GG_STATIC_ASSERT(offsetof(WideVector_0042F1E0, GrowthStep) == 0x14);

struct NarrowVector_0042F1E0
{
    const void* Vptr;        // +0x0000
    void* Vector;            // +0x0004
    int   VectorMax;         // +0x0008
    char  IsValid;           // +0x000C
    char  IsAllocated;       // +0x000D
    char  _pad00E[2];        // +0x000E
    int   ActiveCount;       // +0x0010
    int   GrowthStep;        // +0x0014

    // FUNCTION: GAMEMD 0x42FCB0 — VectorClass base, 4-byte element.
    void BaseCtor(unsigned int size, const void* array);
};
GG_STATIC_ASSERT(sizeof(NarrowVector_0042F1E0) == 0x18);

// The larger host at 0x42E6F0 has the same three vectors and then a block of
// its own scalars: two shorts at +0x50/+0x52 and nine dwords from +0x54 to
// +0x74. It also zeroes the wide vector's trailing dword at +0x1C, which the
// smaller host leaves alone.
struct Host_0042F1E0
{
    const void* Vptr;                 // +0x0000
    WideVector_0042F1E0   Wide;       // +0x0004
    NarrowVector_0042F1E0 First;      // +0x0020
    NarrowVector_0042F1E0 Second;     // +0x0038
    unsigned short At_50;             // +0x0050
    unsigned short At_52;             // +0x0052
    int At_54;                        // +0x0054
    int At_58;                        // +0x0058
    int At_5C;                        // +0x005C
    int At_60;                        // +0x0060
    int At_64;                        // +0x0064
    int At_68;                        // +0x0068
    int At_6C;                        // +0x006C
    int At_70;                        // +0x0070
    int At_74;                        // +0x0074

    // FUNCTION: GAMEMD 0x42F1E0
    //
    // Retail ends with `RET 0x4`, so there is one stack parameter. Nothing in the
    // body reads it, so it keeps a placeholder name; without it the epilogue is
    // a bare `RET` and that is the whole residual.
    Host_0042F1E0* Ctor(int unused);

    // FUNCTION: GAMEMD 0x42E6F0 — the same three vectors plus this host's own
    // scalar block. A separate function, written out longhand rather than
    // derived from Ctor: the two differ in which stores they make and in where
    // the wide vector's trailing dword is written.
    //
    // No stack parameter on this one — it ends with a bare `RET` where 0x42F1E0
    // ends `RET 0x4`. The two constructors of the same shape differ in their
    // signatures, which is exactly why they are written out separately.
    Host_0042F1E0* CtorFull();
};
GG_STATIC_ASSERT(offsetof(Host_0042F1E0, At_50) == 0x50);
GG_STATIC_ASSERT(offsetof(Host_0042F1E0, At_74) == 0x74);
GG_STATIC_ASSERT(offsetof(Host_0042F1E0, Wide) == 0x4);
GG_STATIC_ASSERT(offsetof(Host_0042F1E0, First) == 0x20);
GG_STATIC_ASSERT(offsetof(Host_0042F1E0, Second) == 0x38);

#endif  // GG_MATCH_CORE_TRIPLE_VECTOR_HOST_METHODS_H

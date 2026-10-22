// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Queue.CPP. The name is the source-file string at 0x8374a0
//   in retail gamemd.exe v1.001, passed by the assert at 0x647990 inside this object's
//   code range (0x646a80-0x65267f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Leaf bodies that repeat at several addresses: the integer sort comparator
// (the same shape as IndexClass::Comparator, bound to other tables), release
// and replace of one global heap block, a 64 KiB global buffer clear, and
// three constant or global tests. Each address was verified separately.
//
// Six key/value-vector Grow instances, ordered ascending by retail address.
//
// Grow the vector by `extra` slots: allocate, copy the live elements across
// field by field, free the old block, and invalidate the cached lookup slot. A
// negative request and a failed allocation both report false without touching
// anything.
//
// The phrasing is the one already driven to 100% at 0x41C500 and is reproduced
// unchanged. The two details that matter are recorded there and hold here: the
// allocation is `new GrowPair[total]`, whose elided vector-constructor-iterator
// setup is retail's `DEC`/spill pair after the null check, and the copy is a
// whole-struct assignment through an explicit byte offset, which is what moves
// the pair as two dwords sharing one address computation and keeps the index a
// plain register. Count and Items are re-read every iteration rather than
// hoisted.

#include <string.h>

// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);

extern int DAT_00A9FABC;
extern void* DAT_00ABF3F4;
extern int DAT_00B2FF78[0x4000];
extern int DAT_00B1D5E0[0x4000];
extern void* DAT_00B77F54;
extern void* DAT_00B77F60;

#include "pair_vector_grow_sweep.h"

#include "trivial_tu186_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F0290
extern const double DAT_007F0290;
// GLOBAL: GAMEMD 0xAC6650
extern double DAT_00AC6650;
// GLOBAL: GAMEMD 0xAFA410
extern double DAT_00AFA410;
// GLOBAL: GAMEMD 0xAFA420
extern int DAT_00AFA420;
// GLOBAL: GAMEMD 0xAFA424
extern int DAT_00AFA424;
// GLOBAL: GAMEMD 0xAFA428
extern int DAT_00AFA428;
// GLOBAL: GAMEMD 0xAFA460
extern double DAT_00AFA460;
// GLOBAL: GAMEMD 0xB04878
extern unsigned char DAT_00B04878;
// GLOBAL: GAMEMD 0xB04884
extern int DAT_00B04884;
// GLOBAL: GAMEMD 0xB04888
extern int DAT_00B04888;
// GLOBAL: GAMEMD 0xB0488C
extern unsigned char DAT_00B0488C;
// GLOBAL: GAMEMD 0xB0488D
extern unsigned char DAT_00B0488D;

// FUNCTION: GAMEMD 0x646AB0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00646AB0()
{
    DAT_00AFA460 = DAT_00AC6650 / DAT_007F0290;
}

// FUNCTION: GAMEMD 0x646AD0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00646AD0()
{
    DAT_00AFA410 = DAT_007E1718 / DAT_00AFA460;
}

// FUNCTION: GAMEMD 0x646C50
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00646C50()
{
    DAT_00AFA428 = 0;
    DAT_00AFA420 = 0x80;
    DAT_00AFA424 = 0x80;
}

// FUNCTION: GAMEMD 0x646CE0
// Branching.
void Obj_00646CE0::FUN_00646CE0()
{
    if (unknown_334 != 0)
    {
        FUN_007C8B3D(unknown_334);
    }
}

// FUNCTION: GAMEMD 0x646D00
// Stores several members.
Obj_00646D00* Obj_00646D00::FUN_00646D00()
{
    unknown_00 = -1;
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    return this;
}

// FUNCTION: GAMEMD 0x646D50
// Branching.
void __cdecl FUN_00646D50()
{
    if (DAT_00A8B238 == 4)
    {
        DAT_00A8E9C0.FUN_00543090();
    }
}

// FUNCTION: GAMEMD 0x646DB0
// Empty function.
void __cdecl FUN_00646DB0()
{
}

// FUNCTION: GAMEMD 0x64AE30
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0064AE30()
{
    DAT_00B04884 = 0;
    DAT_00B04888 = 0;
    DAT_00B0488C = 0;
    DAT_00B0488D = 0;
    DAT_00B04878 = 0;
}

// FUNCTION: GAMEMD 0x652100
// Empty function.
void __cdecl FUN_00652100()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x652540
// Branching.
int Obj_00652540::FUN_00652540()
{
    if (unknown_00 != 0)
    {
        unknown_04 = (unknown_04 + 1) & 0x7F;
        unknown_00--;
    }
    return unknown_00;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6525A0
bool GrowPairVector::Grow_6525A0(int extra)
{
    GrowPair* grown;
    int total;
    int i;

    if (extra < 0) goto fail;

    total = Capacity + extra;
    grown = new GrowPair[total];
    if (grown == 0) goto fail;

    for (i = 0; i < Count; i++) {
        int off = i * 8;
        GrowPair* src = (GrowPair*)((char*)Items + off);
        *(GrowPair*)((char*)grown + off) = *src;
    }

    delete[] Items;

    Items    = grown;
    Capacity = Capacity + extra;
    Cached   = 0;
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00652630
int __cdecl FUN_00652630(const void* a, const void* b)
{
    if (*(const int*)a == *(const int*)b)
        return 0;
    if (*(const int*)a < *(const int*)b)
        return -1;
    return 1;
}

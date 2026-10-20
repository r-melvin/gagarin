// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC12_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC12_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"
#include "guarded_forward_methods.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);
void __stdcall FUN_007DC720(unsigned int hr);

// A COM slot taking two arguments. __stdcall pushes right to left and the
// object last, which is the order retail uses.
typedef long (__stdcall* Slot2)(IFace*, int, int);
#define IFACE_CALL2(p, slot, x, y) ((*(Slot2*)(*(char**)(p) + (slot)))(p, x, y))

// An owned buffer with its own release. Unlike the 53-instance template in
// buffer_release_methods.h there is no null check on the pointer - the flag
// alone decides whether to free - but it shares that template's contract of
// clearing the holder unconditionally.
struct Owned_0043AE50
{
    void*         Buffer;        // +0x0000
    int           Length;        // +0x0004
    unsigned char IsAllocated;   // +0x0008

    // FUNCTION: GAMEMD 0x43AE50
    void FUN_0043AE50();
};
GG_STATIC_ASSERT(offsetof(Owned_0043AE50, IsAllocated) == 0x8);

// VTABLE: GAMEMD 0x7E2198
extern char VT_007E2198[];

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BSurface's own vtable is 0x7E2070.
//   0x411650 -> BSurface slot 0 (byte-off 0x0).
// That table is the only table in the image that holds it, so the slot is
// declared on BSurface and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BSurface_00411650
{
    char             _pad00[0x14];
    Owned_0043AE50   Inner;   // +0x0014

    // FUNCTION: GAMEMD 0x411650
    void* FUN_00411650(unsigned int flags);
};
GG_STATIC_ASSERT(offsetof(BSurface_00411650, Inner) == 0x14);

struct Node_00408500 { char _pad[0x10]; int at10; void* at14; };
struct Obj_00408500d
{
    char _pad00[0x4];
    int  Total;   // +0x0004
    // +0x08 is a ListNode anchor.

    // FUNCTION: GAMEMD 0x408500
    void __fastcall FUN_00408500(Node_00408500* node);
};
GG_STATIC_ASSERT(offsetof(Obj_00408500d, Total) == 0x4);

struct Pair2ib { int x; int y; };
struct Obj_0045A130
{
    int a, b, c, d;   // +0x0000 .. +0x000C

    // FUNCTION: GAMEMD 0x45A130
    Obj_0045A130* FUN_0045A130(const Pair2ib* pair, int third, int fourth);
};

struct Obj_00437FD0
{
    IFace* Ptr;   // +0x0000

    // FUNCTION: GAMEMD 0x437FD0
    void FUN_00437FD0(int a, int b);
};

#endif  // GG_MATCH_CORE_SMALL_MISC12_METHODS_H

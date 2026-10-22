// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and slots read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x4272A0: `[ESI+0x84]`, `[ESI+0x88]`,
//   `[ESI+0x89]`, `[ESI+0xE0C]`, `[ESI+0xE10]`, and the two slots `[EAX+0x34]`
//   (no arguments) and `[EDX]` (one pushed argument).
#ifndef GG_MATCH_RENDERER_SCALAR_DELETING_DTOR_METHODS_H
#define GG_MATCH_RENDERER_SCALAR_DELETING_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// VTABLE: GAMEMD 0x7E3584 — this class's own.
extern void* const VTBL_007E3584[];
// VTABLE: GAMEMD 0x7E35A8 — the base's, restored before the object is freed.
extern void* const VTBL_007E35A8[];

extern "C" void __cdecl FUN_007C8B3D(void* block);   // GAMEMD 0x7C8B3D

// Declaration order per match/_rt/gg_vslot.h for both callees.
struct OwnerVtbl_004272A0;
struct Owner_004272A0 { OwnerVtbl_004272A0* Vptr; };
typedef int (Owner_004272A0::*Fn34_004272A0)();
struct OwnerVtbl_004272A0
{
    char _pad000[0x34];          // +0x0000
    Fn34_004272A0 At_34;         // +0x0034
};
GG_STATIC_ASSERT(offsetof(OwnerVtbl_004272A0, At_34) == 0x34);

struct SinkVtbl_004272A0;
struct Sink_004272A0 { SinkVtbl_004272A0* Vptr; };
typedef int (Sink_004272A0::*Fn00_004272A0)(int flags);
struct SinkVtbl_004272A0 { Fn00_004272A0 At_00; };

// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). AnimFile's own vtable is 0x7E3584.
//   0x4272A0 -> AnimFile slot 0 (byte-off 0x0).
// That table is the only table in the image that holds it, so the slot is
// declared on AnimFile and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct AnimFile_004272A0
{
    const void* Vptr;            // +0x0000
    char _pad004[0x80];          // +0x0004
    Owner_004272A0* Owner;       // +0x0084
    char At_88;                  // +0x0088
    char Attached;               // +0x0089
    char _pad08A[0xD82];         // +0x008A
    Sink_004272A0* Sink;         // +0x0E0C
    void* Buffer;                // +0x0E10

    // FUNCTION: GAMEMD 0x4272A0
    AnimFile_004272A0* Destroy(int flags);
};
GG_STATIC_ASSERT(offsetof(AnimFile_004272A0, Owner) == 0x84);
GG_STATIC_ASSERT(offsetof(AnimFile_004272A0, Attached) == 0x89);
GG_STATIC_ASSERT(offsetof(AnimFile_004272A0, Sink) == 0xE0C);
GG_STATIC_ASSERT(offsetof(AnimFile_004272A0, Buffer) == 0xE10);

#endif  // GG_MATCH_RENDERER_SCALAR_DELETING_DTOR_METHODS_H

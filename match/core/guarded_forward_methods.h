// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Slots and offsets extracted individually from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI, one disassembly per entry point. None of
//   these addresses is bound by YRpp.
//
// Two more templates found by shape clustering.
//
// The first is a guarded __stdcall virtual forward: if the held pointer is
// non-null, dispatch through its own vtable. `MOV ECX,[EAX]; PUSH EAX;
// CALL [ECX+slot]` pushes the object rather than passing it in ECX, which is
// the __stdcall COM convention this engine uses for its interface vtables, not
// the __thiscall one. The three instances differ only in the slot.
//
// The second is a conditional buffer release keyed on an ownership flag that is
// tested *before* the pointer, and where both fields are cleared only on the
// path that actually frees - unlike the buffer-release template in
// buffer_release_methods.h, which clears them unconditionally. Same idea,
// different contract; they are not interchangeable.
#ifndef GG_MATCH_CORE_GUARDED_FORWARD_METHODS_H
#define GG_MATCH_CORE_GUARDED_FORWARD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

// A COM-style interface: __stdcall virtuals, object pushed on the stack.
struct IFace;
typedef void (__stdcall* IFaceSlot)(IFace* self);
#define IFACE_CALL(p, slot) ((*(IFaceSlot*)(*(char**)(p) + (slot)))(p))

struct Obj_00437FC0
{
    IFace* Held;   // +0x0000
    // FUNCTION: GAMEMD 0x437FC0
    void FUN_00437FC0();
    // FUNCTION: GAMEMD 0x45A160
    void FUN_0045A160();
    // FUNCTION: GAMEMD 0x45A170
    void FUN_0045A170();
};

struct Owned_465B30
{
    char  _pad000[0x1518];
    void* Buffer;        // +0x1518
    unsigned char IsAllocated;   // +0x151C

    // FUNCTION: GAMEMD 0x465B30
    void FUN_00465B30();
};
GG_STATIC_ASSERT(offsetof(Owned_465B30, Buffer) == 0x1518);
GG_STATIC_ASSERT(offsetof(Owned_465B30, IsAllocated) == 0x151C);

struct Owned_465B70
{
    char  _pad000[0x14E4];
    void* Buffer;        // +0x14E4
    unsigned char IsAllocated;   // +0x14E8

    // FUNCTION: GAMEMD 0x465B70
    void FUN_00465B70();
};
GG_STATIC_ASSERT(offsetof(Owned_465B70, Buffer) == 0x14E4);
GG_STATIC_ASSERT(offsetof(Owned_465B70, IsAllocated) == 0x14E8);

struct Owned_465BB0
{
    char  _pad000[0x14EC];
    void* Buffer;        // +0x14EC
    unsigned char IsAllocated;   // +0x14F0

    // FUNCTION: GAMEMD 0x465BB0
    void FUN_00465BB0();
};
GG_STATIC_ASSERT(offsetof(Owned_465BB0, Buffer) == 0x14EC);
GG_STATIC_ASSERT(offsetof(Owned_465BB0, IsAllocated) == 0x14F0);

struct Owned_465BF0
{
    char  _pad000[0x14F4];
    void* Buffer;        // +0x14F4
    unsigned char IsAllocated;   // +0x14F8

    // FUNCTION: GAMEMD 0x465BF0
    void FUN_00465BF0();
};
GG_STATIC_ASSERT(offsetof(Owned_465BF0, Buffer) == 0x14F4);
GG_STATIC_ASSERT(offsetof(Owned_465BF0, IsAllocated) == 0x14F8);

struct Owned_465C30
{
    char  _pad000[0x14FC];
    void* Buffer;        // +0x14FC
    unsigned char IsAllocated;   // +0x1500

    // FUNCTION: GAMEMD 0x465C30
    void FUN_00465C30();
};
GG_STATIC_ASSERT(offsetof(Owned_465C30, Buffer) == 0x14FC);
GG_STATIC_ASSERT(offsetof(Owned_465C30, IsAllocated) == 0x1500);

struct Owned_465C70
{
    char  _pad000[0x1504];
    void* Buffer;        // +0x1504
    unsigned char IsAllocated;   // +0x1508

    // FUNCTION: GAMEMD 0x465C70
    void FUN_00465C70();
};
GG_STATIC_ASSERT(offsetof(Owned_465C70, Buffer) == 0x1504);
GG_STATIC_ASSERT(offsetof(Owned_465C70, IsAllocated) == 0x1508);

#endif  // GG_MATCH_CORE_GUARDED_FORWARD_METHODS_H

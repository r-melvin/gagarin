// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Every offset and vtable constant below is read numerically off the user's
//   retail gamemd.exe v1.001 with the local Ghidra CLI at 0x632F90, 0x632FF0
//   and 0x633370. The private-reference seed (consult-only, no LICENSE) names this
//   address run the observable-node family; it supplied intent only, and no
//   layout, no calling convention and no bytes.
//
//   CLASS IDENTITY CORRECTED (whole-image RTTI sweep, docs/rtti_sweep.md).
//   The earlier `NotifyNode` / `NotifySubNode` names were invented behaviour
//   names for unnamed classes. RTTI read off this binary names them:
//     0x007EFDC8 -> `.?AVBlowPipe@@`   (locator 0x00807D88, TD 0x00836858)
//     0x007EDF40 -> `.?AVBlowStraw@@`  (locator 0x00805E30, TD 0x0082C340)
//   Both re-read here with `ghidra memory read`, not taken on the sweep's
//   word. They are the pipe/straw stream family (SHAPipe, Base64Straw,
//   FilePipe, LZOPipe, PKStraw, RandomStraw, CacheStraw, ...), not a
//   notification family. The two ENCLOSING types are NOT named by RTTI --
//   nothing in the image carries a locator for them -- so they keep raw
//   address-anchored placeholders rather than another invented name.
//
// Three scalar-deleting destructors over one small stream shape.
//
//   BlowPipe        -- vptr at +0x00, two opaque base words at +0x04 and
//                      +0x08, an owned payload pointer at +0x0C
//                      (`MOV EDI,[ESI+0xC]`, released and then cleared).
//                      sizeof 0x10.
//   Obj_00632FF0    -- carries a BlowPipe at +0x14. Retail loads the payload
//                      as `MOV EBX,[EDI+0x20]` (0x14 + 0xC) and seats the
//                      subobject's vtable through `LEA ESI,[EDI+0x14]`.
//   Obj_00633370    -- the same enclosing shape, carrying a BlowStraw at
//                      +0x14 and the other shared base destructor.
//
// The payload is released under a null test with `MOV ECX,<p>;
// CALL 0x437FC0`, `PUSH <p>; CALL <free>; ADD ESP,4`, which is an ordinary
// `delete` of a type with a non-virtual, out-of-line destructor.
//
// The shared base destructor is reached as `MOV ECX,<obj>; CALL <addr>` with
// nothing pushed, so it is `__thiscall` taking no arguments. Two of them
// appear in this run: 0x631C80 under the BlowPipe pair and 0x6C9850 under
// Obj_00633370. The subobject is destroyed first, then the enclosing object's
// own base -- two calls to the same address in both enclosing destructors.
#ifndef GG_MATCH_COMBAT_OBSERVABLE_NODE_DTOR_METHODS_H
#define GG_MATCH_COMBAT_OBSERVABLE_NODE_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/pipe.h"

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) -- CRT free.
extern "C" void __cdecl gg_free(void* block);

// VTABLE: GAMEMD 0x007EFDC8 -- BlowPipe
extern char VT_007EFDC8;
// VTABLE: GAMEMD 0x007EDF40 -- BlowStraw (the Obj_00633370 subobject)
extern char VT_007EDF40;

// The owned payload. Only its destructor reaches the code, and that is
// non-virtual and out of line, so the type itself stays opaque.
// FUNCTION: GAMEMD 0x437FC0 (decl; reloc) -- ~NodePayload.
struct NodePayload
{
    int Opaque;
    ~NodePayload();
};

// Pipe cleanup uses the shared RTTI-backed base destructor. The other
// no-argument __thiscall remains an address-scoped Straw cleanup view;
// original ownership beyond the observed call is not established here.
// FUNCTION: GAMEMD 0x6C9850 (decl; reloc)
struct NodeBaseB { void Destruct(); };

// The in-place destructor is defined in the class body on purpose. Both
// enclosing types inline it, and retail's register colouring only falls out
// when the subobject's own address is what the block is written against: with
// the same statements spelled through `Node.` off the enclosing object, cl
// addresses the payload store at [this+0x20] and swaps ESI and EDI across the
// whole body (65.5%).
struct BlowPipe
{
    char*        Vptr;        // +0x00
    int          unknown_04;  // +0x04
    int          unknown_08;  // +0x08
    NodePayload* Payload;     // +0x0C

    void DestructInPlace()
    {
        Vptr = &VT_007EFDC8;
        delete Payload;
        Payload = 0;
        ((Pipe*)this)->Pipe::~Pipe();
    }

    // FUNCTION: GAMEMD 0x632F90
    BlowPipe* ScalarDeletingDtor(char flags);
};
GG_STATIC_ASSERT(offsetof(BlowPipe, Payload) == 0x0C);
GG_STATIC_ASSERT(sizeof(BlowPipe) == 0x10);

struct BlowStraw
{
    char*        Vptr;        // +0x00
    int          unknown_04;  // +0x04
    int          unknown_08;  // +0x08
    NodePayload* Payload;     // +0x0C

    void DestructInPlace()
    {
        Vptr = &VT_007EDF40;
        delete Payload;
        Payload = 0;
        ((NodeBaseB*)this)->Destruct();
    }
};
GG_STATIC_ASSERT(offsetof(BlowStraw, Payload) == 0x0C);

struct Obj_00632FF0
{
    char       unknown_00[0x14];  // +0x00 the enclosing object's own base
    BlowPipe Node;              // +0x14

    // FUNCTION: GAMEMD 0x632FF0
    Obj_00632FF0* ScalarDeletingDtor(char flags);
};
GG_STATIC_ASSERT(offsetof(Obj_00632FF0, Node) == 0x14);
// `MOV EBX,[EDI+0x20]` pins the subobject at +0x14 and its payload at +0x0C
// within it.
GG_STATIC_ASSERT(offsetof(Obj_00632FF0, Node) + offsetof(BlowPipe, Payload) == 0x20);

struct Obj_00633370
{
    char               unknown_00[0x14];  // +0x00
    BlowStraw Node;              // +0x14

    // FUNCTION: GAMEMD 0x633370
    Obj_00633370* ScalarDeletingDtor(char flags);
};
GG_STATIC_ASSERT(offsetof(Obj_00633370, Node) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00633370, Node) + offsetof(BlowStraw, Payload) == 0x20);

#endif  // GG_MATCH_COMBAT_OBSERVABLE_NODE_DTOR_METHODS_H

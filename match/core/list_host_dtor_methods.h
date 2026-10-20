// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x40E3E0 and 0x40E4C0. The node type is 0xC bytes
//   (vptr, Next at +4, Prev at +8), which places the two embedded nodes at +0x4
//   and +0x10 and matches the `LEA EAX,[EDI+0x10]` / `LEA EAX,[EDI+4]` pair.
#ifndef GG_MATCH_CORE_LIST_HOST_DTOR_METHODS_H
#define GG_MATCH_CORE_LIST_HOST_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E1B04 — GenericList (RTTI, docs/rtti_sweep.md).
extern void* const VTBL_007E1B04[];
// VTABLE: GAMEMD 0x7E1B0C — GenericNode (RTTI), installed as each node is destroyed.
extern void* const VTBL_007E1B0C[];

extern "C" void __cdecl FUN_007C8B3D(void* block);   // GAMEMD 0x7C8B3D

struct Node_0040E3E0
{
    const void* Vptr;         // +0x0000
    Node_0040E3E0* Next;      // +0x0004
    Node_0040E3E0* Prev;      // +0x0008

    // Splice this node out of its list. The `this != 0` test is retail's and is
    // kept: it survives even where the receiver is `&member` and provably
    // non-null (`LEA EAX,[EDI+0x10]; CMP EAX,ESI` at 0x40E422), so it is in the
    // source rather than something the compiler could have introduced.
    void Unlink()
    {
        int zero = 0;
        if (this != (Node_0040E3E0*)zero && this->Next != (Node_0040E3E0*)zero
            && this->Prev != (Node_0040E3E0*)zero) {
            this->Prev->Next = this->Next;
            this->Next->Prev = this->Prev;
            this->Prev = (Node_0040E3E0*)zero;
            this->Next = (Node_0040E3E0*)zero;
        }
    }

    void Dtor()
    {
        this->Vptr = VTBL_007E1B0C;
        this->Unlink();
    }
};
GG_STATIC_ASSERT(sizeof(Node_0040E3E0) == 0xC);

struct Host_0040E3E0
{
    const void* Vptr;         // +0x0000
    Node_0040E3E0 A;          // +0x0004
    Node_0040E3E0 B;          // +0x0010

    // FUNCTION: GAMEMD 0x40E3E0
    Host_0040E3E0* Destroy(int flags);
};
GG_STATIC_ASSERT(offsetof(Host_0040E3E0, A) == 0x4);
GG_STATIC_ASSERT(offsetof(Host_0040E3E0, B) == 0x10);

// The second instantiation. Identical layout and identical body; written out as
// its own type rather than shared, because the family rule in the methodology
// exists precisely because look-alike siblings have been caught diverging.
struct Host_0040E4C0
{
    const void* Vptr;         // +0x0000
    Node_0040E3E0 A;          // +0x0004
    Node_0040E3E0 B;          // +0x0010

    // FUNCTION: GAMEMD 0x40E4C0
    Host_0040E4C0* Destroy(int flags);
};

#endif  // GG_MATCH_CORE_LIST_HOST_DTOR_METHODS_H

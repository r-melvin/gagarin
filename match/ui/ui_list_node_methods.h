// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Entry-origin retail bodies at 0x5B3F50..0x5B4793 confirm the layouts,
// call conventions and operations below. RTTI names GenericNode at 0x7E1B0C,
// GenericList at 0x7E1B04 and MixFileClass at 0x7EDF50 (TD0x82C320).
// SortedTreeNode is a descriptive name. BlowStraw's deleting destructor
// 0x5B45C0, which sits in this address run, is emitted from its class in
// match/platform/pk_blow_pipes.h.
// Intrusive-node fields now use the shared layout; the original source-file
// grouping is not established by these functions.
#ifndef GG_MATCH_UI_UI_LIST_NODE_METHODS_H
#define GG_MATCH_UI_UI_LIST_NODE_METHODS_H

#include <stddef.h>
#include "../_layout/generic_list.h"
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) — the CRT free.
extern "C" void __cdecl gg_free(void* block);
// LIBRARY: GAMEMD 0x7C93E8 (decl; reloc) — the other free (the pool release
// already modelled in match/core/small_misc46_methods.h).
extern "C" void __cdecl FUN_007C93E8(void* block);

// VTABLE: GAMEMD 0x7EDF50 — MixFileClass.
extern char VT_007EDF50;
#include "../_layout/sorted_tree_node.h"

// ---------------------------------------------------------------------------
// GenericNode and its primitives use the shared binary-confirmed layout.

// ---------------------------------------------------------------------------
// The MixFileClass destroyed at 0x5B3F50 and 0x5B4630: a GenericNode with four
// owned resources bolted on.
//
// Offsets confirmed numerically in 0x5B3F50: +0x0C at 0x5B3F56
// (`MOV EAX,[ESI + 0xC]`, released through 0x7C93E8 and NOT cleared), +0x24 at
// 0x5B3F6C, the ownership byte +0x12 at 0x5B3F73 (`CMP byte ptr [ESI+0x12],BL`,
// a byte, cleared with the same zero), and +0x20 at 0x5B3F84. Everything in
// between is untouched here and stays a named gap.
class MixFileClass
{
public:
    char*     Vptr;            // +0x00
    GenericNode* Prev;            // +0x04
    GenericNode* Next;            // +0x08
    void*     Buffer;          // +0x0C
    char      unknown_10[2];   // +0x10
    bool      OwnsRecord;      // +0x12
    char      unknown_13[0x0D];// +0x13
    void*     Scratch;         // +0x20
    void*     Record;          // +0x24

    void DestructInPlace()
    {
        this->Vptr = &VT_007EDF50;
        if (this->Buffer != 0) {
            FUN_007C93E8(this->Buffer);
        }
        if (this->Record != 0 && this->OwnsRecord) {
            gg_free(this->Record);
            this->OwnsRecord = false;
        }
        this->Record = 0;
        if (this->Scratch != 0) {
            gg_free(this->Scratch);
            this->Scratch = 0;
        }
        ((GenericNode*)this)->Unlink();
        ((GenericNode*)this)->DestroyNode();
    }

    // FUNCTION: GAMEMD 0x5B3F50
    void Destruct();
    // FUNCTION: GAMEMD 0x5B4630
    MixFileClass* ScalarDeletingDtor(char flags);
};
GG_STATIC_ASSERT(offsetof(MixFileClass, Prev) == 0x04);
GG_STATIC_ASSERT(offsetof(MixFileClass, Next) == 0x08);
GG_STATIC_ASSERT(offsetof(MixFileClass, Buffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(MixFileClass, OwnsRecord) == 0x12);
GG_STATIC_ASSERT(offsetof(MixFileClass, Scratch) == 0x20);
GG_STATIC_ASSERT(offsetof(MixFileClass, Record) == 0x24);
GG_STATIC_ASSERT(sizeof(MixFileClass) == 0x28);

// ---------------------------------------------------------------------------
// GenericList at 0x5B46E0 uses the shared declaration.

#endif  // GG_MATCH_UI_UI_LIST_NODE_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//
//   Seven small intrusive-container helpers at 0x5B3F50-0x5B4793: a sorted
//   binary-tree insert, a recursive tree teardown, a doubly-linked-list unlink,
//   and four destructors over the node and host shapes those use.
//
//   Every offset, vtable constant and calling convention below was read
//   numerically off the user's retail gamemd.exe v1.001 through the local
//   Ghidra CLI. The private-reference seed (consult-only, no LICENSE) grouped this
//   address run as `ui/ui_linked_list_utils.cpp` and named the members'
//   roles; it supplied intent only and contributed no bytes, layout or
//   conventions. Its signatures spell the receivers as ordinary pointer
//   parameters; the receiver registers here come from the usual disassembly
//   tells (`MOV ESI,ECX` with no stack cleanup, and a second argument arriving
//   in EDX at 0x5B3FF0, which is __fastcall rather than __thiscall).
//
//   The list node is the same 0xC-byte shape already matched in
//   match/core/list_host_dtor_methods.h (vtable 0x7E1B0C, host vtable
//   0x7E1B04); it is modelled independently here so this TU stands alone, and
//   the two agree offset for offset.
//
//   CLASS IDENTITIES CORRECTED (whole-image RTTI sweep, docs/rtti_sweep.md).
//   Four types here carried invented behaviour names. RTTI read off this
//   binary names all four:
//     0x7E1B0C -> GenericNode   (was `ListNode`)
//     0x7E1B04 -> GenericList   (was `ListHost`; the same spelling
//                                match/platform/ini_class_node_methods.h
//                                already uses for these two vtables)
//     0x7EDF50 -> MixFileClass  (was `TrackedNode`; locator 0x00805DE0,
//                                TD 0x0082C320 = `.?AVMixFileClass@@`,
//                                re-read here with `ghidra memory read`)
//     0x7EDF40 -> BlowStraw     (was `EmbeddedSubObject`; locator
//                                0x00805E30, TD 0x0082C340)
//   The MixFileClass identity is independently corroborated inside this tree:
//   match/platform/mix_file_class.h already pins sizeof(MixFileClass) == 0x28
//   with its constructor at 0x5B3C20 and a Node<> destructor in slot 0, and
//   the 0x28-byte shape destroyed at 0x5B3F50/0x5B4630 below is that object's
//   full layout. `BlowStraw` is the pipe/straw stream family, not a node.
#ifndef GG_MATCH_UI_UI_LIST_NODE_METHODS_H
#define GG_MATCH_UI_UI_LIST_NODE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — the CRT free.
extern "C" void __cdecl gg_free(void* block);
// FUNCTION: GAMEMD 0x7C93E8 (decl; reloc) — the other free (the pool release
// already modelled in match/core/small_misc46_methods.h).
extern "C" void __cdecl FUN_007C93E8(void* block);

// VTABLE: GAMEMD 0x7E1B0C — GenericNode.
extern char VT_007E1B0C;
// VTABLE: GAMEMD 0x7E1B04 — GenericList.
extern char VT_007E1B04;
// VTABLE: GAMEMD 0x7EDF50 — MixFileClass.
extern char VT_007EDF50;
// VTABLE: GAMEMD 0x7EDF40 — BlowStraw (the same constant the pipe/straw
// family seats at 0x633370).
extern char VT_007EDF40;

// FUNCTION: GAMEMD 0x437FC0 (decl; reloc) — the payload's non-virtual,
// out-of-line destructor.
struct NodePayload
{
    int Opaque;
    ~NodePayload();
};

// FUNCTION: GAMEMD 0x6C9850 (decl; reloc) — a shared base destructor reached
// as `MOV ECX,<obj>; CALL <addr>` with nothing pushed: __thiscall, no
// arguments.
struct NodeBaseB { void Destruct(); };

// ---------------------------------------------------------------------------
// The sorted binary tree (0x5B3FF0, 0x5B4080).
//
// Offsets confirmed numerically at 0x5B3FFF/0x5B4004 (`LEA EDX,[EAX + 0x4]` for
// one child and `MOV EDX,EAX` for the other, so the children sit at +0x00 and
// +0x04) and at 0x5B3FFA (`MOV EDX,dword ptr [EAX + 0x8]`, the ordering key).
struct SortedTreeNode
{
    SortedTreeNode* Low;   // +0x00
    SortedTreeNode* High;  // +0x04
    int             Key;   // +0x08

    // Members, not free functions taking the node: retail keeps the node in
    // ECX and 0x5B3FF0's slot pointer arrives in EDX, which is `__fastcall` on
    // a member (this in ECX, the first explicit argument in EDX, nothing
    // cleaned); a __thiscall member would push the slot and return `RET 4`.
    // FUNCTION: GAMEMD 0x5B3FF0
    void __fastcall SortedTreeInsert(SortedTreeNode** slot);
    // FUNCTION: GAMEMD 0x5B4080
    void SortedTreeFree();
};
GG_STATIC_ASSERT(offsetof(SortedTreeNode, Low) == 0x00);
GG_STATIC_ASSERT(offsetof(SortedTreeNode, High) == 0x04);
GG_STATIC_ASSERT(offsetof(SortedTreeNode, Key) == 0x08);
GG_STATIC_ASSERT(sizeof(SortedTreeNode) == 0x0C);

// ---------------------------------------------------------------------------
// The intrusive doubly-linked list node.
//
// Offsets confirmed numerically at 0x5B4594/0x5B459B (`MOV EDX,[ECX + 0x4]`,
// `MOV EAX,[ECX + 0x8]`) and by the cross-writes at 0x5B45A2/0x5B45AB
// (`MOV [EAX + 0x4],EDX` then `MOV [EAX + 0x8],EDX`), which pin +0x04 and
// +0x08 as the two link directions. The vtable pointer at +0x00 is written
// with 0x7E1B0C at 0x5B3FC0.
struct GenericNode
{
    char*     Vptr;  // +0x00
    GenericNode* Prev;  // +0x04
    GenericNode* Next;  // +0x08

    // Splice this node out of its list. All three null tests are retail's and
    // are re-emitted even where the caller has just made them.
    void Unlink()
    {
        if (this != 0 && this->Prev != 0 && this->Next != 0) {
            this->Next->Prev = this->Prev;
            this->Prev->Next = this->Next;
            this->Next = 0;
            this->Prev = 0;
        }
    }

    void Dtor()
    {
        this->Vptr = &VT_007E1B0C;
        this->Unlink();
    }

    // FUNCTION: GAMEMD 0x5B4590 — the out-of-line copy of the same unlink,
    // a member rather than a free function taking the node.
    void ListNodeUnlink();
};
GG_STATIC_ASSERT(offsetof(GenericNode, Prev) == 0x04);
GG_STATIC_ASSERT(offsetof(GenericNode, Next) == 0x08);
GG_STATIC_ASSERT(sizeof(GenericNode) == 0x0C);

// ---------------------------------------------------------------------------
// The BlowStraw sub-object destroyed at 0x5B45C0: vtable 0x7EDF40, an owned
// payload at +0x0C (`MOV EDI,[ESI + 0xC]`, deleted and then cleared) and the
// shared base destructor at 0x6C9850.
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

    // FUNCTION: GAMEMD 0x5B45C0
    BlowStraw* ScalarDeletingDtor(char flags);
};
GG_STATIC_ASSERT(offsetof(BlowStraw, Payload) == 0x0C);
GG_STATIC_ASSERT(sizeof(BlowStraw) == 0x10);

// ---------------------------------------------------------------------------
// The MixFileClass destroyed at 0x5B3F50 and 0x5B4630: a GenericNode with four
// owned resources bolted on.
//
// Offsets confirmed numerically in 0x5B3F50: +0x0C at 0x5B3F56
// (`MOV EAX,[ESI + 0xC]`, released through 0x7C93E8 and NOT cleared), +0x24 at
// 0x5B3F6C, the ownership byte +0x12 at 0x5B3F73 (`CMP byte ptr [ESI+0x12],BL`,
// a byte, cleared with the same zero), and +0x20 at 0x5B3F84. Everything in
// between is untouched here and stays a named gap.
struct MixFileClass
{
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
        ((GenericNode*)this)->Dtor();
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
// The GenericList destroyed at 0x5B46E0. Its own vtable is 0x7E1B04 and it
// carries two list nodes, at +0x04 and +0x10 (`LEA EAX,[EDI + 0x10]` at
// 0x5B4722 and `LEA EAX,[EDI + 0x4]` at 0x5B474F). The drain loop walks
// `[EDI+8]`, which is the first node's +0x04 link.
struct GenericList
{
    char*    Vptr;  // +0x00
    GenericNode A;     // +0x04
    GenericNode B;     // +0x10

    // FUNCTION: GAMEMD 0x5B46E0
    GenericList* ScalarDeletingDtor(char flags);
};
GG_STATIC_ASSERT(offsetof(GenericList, A) == 0x04);
GG_STATIC_ASSERT(offsetof(GenericList, B) == 0x10);
GG_STATIC_ASSERT(offsetof(GenericList, A) + offsetof(GenericNode, Prev) == 0x08);
GG_STATIC_ASSERT(sizeof(GenericList) == 0x1C);

#endif  // GG_MATCH_UI_UI_LIST_NODE_METHODS_H

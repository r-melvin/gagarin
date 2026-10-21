// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// GenericNode and GenericList RTTI is at 0x8174E8/0x817508; primary
// tables are 0x7E1B0C/0x7E1B04. Entry-origin constructors/destructors at
// 0x52ACE0, 0x52AB80 and 0x5B46E0 confirm the fields and unlink order.
// The explicit vptr fields preserve the observed inline stores; complete
// original source ownership and native virtual declarations remain unknown.
#ifndef GG_MATCH_LAYOUT_GENERIC_LIST_H
#define GG_MATCH_LAYOUT_GENERIC_LIST_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
class GenericNode
{
public:
    void*        Vtable;     // +0x00
    GenericNode* NextNode;   // +0x04
    GenericNode* PrevNode;   // +0x08

    // The guard retail spells out three times per unlink: `CMP ESI,EBX`,
    // `CMP EBX,[ECX+4]`, `CMP EBX,[ECX+8]`, in that order.
    // FUNCTION: GAMEMD 0x5B4590
    void ListNodeUnlink();
    __forceinline bool IsValid() const;
    __forceinline void Unlink();
    __forceinline void Link(GenericNode* node);
    // What the GenericNode destructor collapses to once inlined: seat the base
    // vtable, then unlink.
    __forceinline void DestroyNode();
    // What the GenericNode constructor collapses to. Retail writes the two
    // links before the seat, so they are written in that order here.
    __forceinline void InitNode();
};
class GenericList
{
public:
    void*       Vtable;      // +0x00
    GenericNode FirstNode;   // +0x04
    GenericNode LastNode;    // +0x10

    // What the GenericList constructor collapses to: build both sentinels,
    // seat the list, and link the head to the tail. It is shared by the plain
    // list at 0x52ACE0 and the List<INIEntry*> instantiation at 0x52AF50,
    // which carries the identical body with one extra seat store, so it is
    // forced inline: cl emits a call rather than an expansion for an ordinary
    // base constructor, and retail has no such call.
    // FUNCTION: GAMEMD 0x5B46E0
    GenericList* ScalarDeletingDtor(char flags);
    __forceinline void InitList();

    // First() is the head sentinel's forward link, which is why INISection's
    // destructor reads [ESI+0x18] for a list seated at +0x10.
    GenericNode* First() const { return FirstNode.NextNode; }
    __forceinline void DestroyList();
};
GG_STATIC_ASSERT(offsetof(GenericNode, Vtable) == 0);
GG_STATIC_ASSERT(offsetof(GenericNode, NextNode) == 4);
GG_STATIC_ASSERT(offsetof(GenericNode, PrevNode) == 8);
GG_STATIC_ASSERT(sizeof(GenericNode) == 0xC);
GG_STATIC_ASSERT(offsetof(GenericList, Vtable) == 0);
GG_STATIC_ASSERT(offsetof(GenericList, FirstNode) == 4);
GG_STATIC_ASSERT(offsetof(GenericList, LastNode) == 0x10);
GG_STATIC_ASSERT(sizeof(GenericList) == 0x1C);
// VTABLE: GAMEMD 0x7E1B0C -- GenericNode, one deleting slot.
// VTABLE: GAMEMD 0x7E1B04 -- GenericList, one deleting slot.
__forceinline bool GenericNode::IsValid() const
{
    return this != 0 && NextNode != 0 && PrevNode != 0;
}

__forceinline void GenericNode::Unlink()
{
    if (IsValid()) {
        PrevNode->NextNode = NextNode;
        NextNode->PrevNode = PrevNode;
        PrevNode = 0;
        NextNode = 0;
    }
}

__forceinline void GenericNode::Link(GenericNode* node)
{
    node->Unlink();
    node->NextNode = NextNode;
    node->PrevNode = this;
    if (NextNode != 0) {
        NextNode->PrevNode = node;
    }
    NextNode = node;
}

__forceinline void GenericNode::DestroyNode()
{
    Vtable = reinterpret_cast<void*>(0x7E1B0C);
    Unlink();
}

__forceinline void GenericNode::InitNode()
{
    NextNode = 0;
    PrevNode = 0;
    Vtable = reinterpret_cast<void*>(0x7E1B0C);
}

__forceinline void GenericList::DestroyList()
{
    Vtable = reinterpret_cast<void*>(0x7E1B04);

    while (First()->IsValid()) {
        First()->Unlink();
    }

    LastNode.DestroyNode();
    FirstNode.DestroyNode();
}

__forceinline void GenericList::InitList()
{
    FirstNode.InitNode();
    LastNode.InitNode();
    Vtable = reinterpret_cast<void*>(0x7E1B04);
    FirstNode.Link(&LastNode);
}
#endif

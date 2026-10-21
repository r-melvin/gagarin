// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// GenericNode and GenericList RTTI is at 0x8174E8/0x817508; primary
// tables are 0x7E1B0C/0x7E1B04. The native GenericNode constructor at
// 0x40E320, GenericList constructor at 0x52ACE0, and destructors at 0x52AB80
// and 0x5B46E0 confirm the fields and unlink order.
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

    // Native no-argument constructor: its three stores and constructor-like
    // call sites are confirmed at 0x40E320.
    // FUNCTION: GAMEMD 0x40E320
    GenericNode();
    // The guard retail spells out three times per unlink: `CMP ESI,EBX`,
    // `CMP EBX,[ECX+4]`, `CMP EBX,[ECX+8]`, in that order.
    // FUNCTION: GAMEMD 0x5B4590
    void ListNodeUnlink();
    // FUNCTION: GAMEMD 0x40E340 -- inserts the argument after this node.
    void LinkNode(GenericNode* node);
    // FUNCTION: GAMEMD 0x40E390 -- primary table slot zero.
    void* DeletingDestructor(char flags);
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
// RTTI at 0x803658/0x8036F8 confirms the intermediate Node<T> bases of
// INIEntry/INISection, with zero-offset GenericNode bases. Constructors put
// derived data at +0x0C. This models that prefix; the original virtual API
// remains unrecovered and the inherited explicit vptr is retained.
template<class T> class Node : public GenericNode
{
public:
    void* DeletingDestructor(unsigned int flags);
};
typedef void* (GenericNode::*GenericNodeDeletingSlot)(char);
// VTABLE: GAMEMD 0x7E1B0C -- explicit one-slot GenericNode table.
extern GenericNodeDeletingSlot GG_VTABLE_GENERIC_NODE_SLOTS;

class GenericList
{
public:
    void*       Vtable;      // +0x00
    GenericNode FirstNode;   // +0x04
    GenericNode LastNode;    // +0x10

    // FUNCTION: GAMEMD 0x52ACE0
    GenericList();

    // Separate matched teardown body; the primary table target is 0x40E3E0.
    // FUNCTION: GAMEMD 0x5B46E0
    GenericList* ScalarDeletingDtor(char flags);
    // FUNCTION: GAMEMD 0x40E3E0 -- table 0x7E1B04 slot zero.
    void* DeletingDestructor(unsigned int flags);
    // Explicit reset helper. The native constructor at 0x52ACE0 instead uses
    // automatic member construction before seating and linking the sentinels.
    // The owning TU's /Ob2 also inlines that constructor into the derived
    // List<INIEntry*> constructor at 0x52AF50, reproducing its full span.
    __forceinline void InitList();

    // First() is the head sentinel's forward link, which is why INISection's
    // destructor reads [ESI+0x18] for a list seated at +0x10.
    GenericNode* First() const { return FirstNode.NextNode; }
    __forceinline void DestroyList();
};
typedef void* (GenericList::*GenericListDeletingSlot)(unsigned int);
// VTABLE: GAMEMD 0x7E1B04 -- explicit one-slot GenericList table.
extern GenericListDeletingSlot GG_VTABLE_GENERIC_LIST_SLOTS;

// RTTI at 0x8035F0/0x7FAC10 confirms List<INIEntry*> and
// List<INISection*> each derive from GenericList at offset zero. Embedded
// list/index boundaries at INISection+0x10/+0x2C and INIClass+0x0C/+0x28
// establish 0x1C storage for these specializations. Other List<T> APIs and
// original native virtual declarations remain unrecovered.
template<class T> class List : public GenericList
{
public:
    List();
    void* DeletingDestructor(unsigned int flags);
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
    Vtable = &GG_VTABLE_GENERIC_NODE_SLOTS;
    Unlink();
}

__forceinline void GenericNode::InitNode()
{
    NextNode = 0;
    PrevNode = 0;
    Vtable = &GG_VTABLE_GENERIC_NODE_SLOTS;
}

__forceinline void GenericList::DestroyList()
{
    Vtable = &GG_VTABLE_GENERIC_LIST_SLOTS;

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
    Vtable = &GG_VTABLE_GENERIC_LIST_SLOTS;
    FirstNode.Link(&LastNode);
}
#endif

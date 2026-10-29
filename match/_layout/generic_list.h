// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// GenericNode and GenericList RTTI is at 0x8174E8/0x817508; primary
// tables are 0x7E1B0C/0x7E1B04, each one slot wide (the virtual destructor).
// The native GenericNode constructor at 0x40E320, the link body at 0x40E340,
// the scalar deleting destructors at 0x40E390/0x40E3E0 and the GenericList
// constructor at 0x52ACE0 are the compiler's own expansion of the classes
// below; the unlink order and fields are confirmed by those bodies.
#ifndef GG_MATCH_LAYOUT_GENERIC_LIST_H
#define GG_MATCH_LAYOUT_GENERIC_LIST_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// VTABLE: GAMEMD 0x7E1B0C -- GenericNode, one deleting slot.
class GenericNode
{
public:
    GenericNode* NextNode;   // +0x04
    GenericNode* PrevNode;   // +0x08

    // FUNCTION: GAMEMD 0x40E320
    GenericNode();
    // Scalar deleting destructor: 0x40E390.
    virtual ~GenericNode() { Unlink(); }
    bool IsValid() const
    {
        return this != 0 && NextNode != 0 && PrevNode != 0;
    }
    void Unlink()
    {
        if (IsValid()) {
            PrevNode->NextNode = NextNode;
            NextNode->PrevNode = PrevNode;
            PrevNode = 0;
            NextNode = 0;
        }
    }
    // FUNCTION: GAMEMD 0x40E340 -- inserts the argument after this node.
    void Link(GenericNode* node);
};
// RTTI at 0x803658/0x8036F8 confirms the intermediate Node<T> bases of
// INIEntry/INISection, with zero-offset GenericNode bases.
template<class T> class Node : public GenericNode
{
public:
    Node() {}
    virtual ~Node() {}
};

// VTABLE: GAMEMD 0x7E1B04 -- GenericList, one deleting slot.
class GenericList
{
public:
    GenericNode FirstNode;   // +0x04
    GenericNode LastNode;    // +0x10

    // FUNCTION: GAMEMD 0x52ACE0
    GenericList();
    // Scalar deleting destructor: 0x40E3E0.
    virtual ~GenericList()
    {
        while (First()->IsValid()) {
            First()->Unlink();
        }
    }
    // First() is the head sentinel's forward link, which is why INISection's
    // destructor reads [ESI+0x18] for a list seated at +0x10.
    GenericNode* First() const { return FirstNode.NextNode; }
};

// RTTI at 0x8035F0/0x7FAC10 confirms List<INIEntry*> and
// List<INISection*> each derive from GenericList at offset zero. Embedded
// list/index boundaries at INISection+0x10/+0x2C and INIClass+0x0C/+0x28
// establish 0x1C storage for these specializations.
template<class T> class List : public GenericList
{
public:
    List() {}
    virtual ~List() {}
};
GG_STATIC_ASSERT(offsetof(GenericNode, NextNode) == 4);
GG_STATIC_ASSERT(offsetof(GenericNode, PrevNode) == 8);
GG_STATIC_ASSERT(sizeof(GenericNode) == 0xC);
GG_STATIC_ASSERT(offsetof(GenericList, FirstNode) == 4);
GG_STATIC_ASSERT(offsetof(GenericList, LastNode) == 0x10);
GG_STATIC_ASSERT(sizeof(GenericList) == 0x1C);
#endif

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x5B3F50-0x5B4793.
//   Ordered ascending by retail address.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy

#include "ui_list_node_methods.h"

// FUNCTION: GAMEMD 0x5B3F50
//
// Destroy a MixFileClass in place: reseat its vtable, release the buffer at
// +0x0C through the pool free, release the record at +0x24 only while the
// ownership byte says the node allocated it, clear both it and the scratch
// block, and finally take the node out of its list twice — once explicitly and
// once through the list-node base destructor that runs after it.
void MixFileClass::Destruct()
{
    DestructInPlace();
}

// FUNCTION: GAMEMD 0x5B3FF0
//
// Insert a node into a binary tree ordered by the key at +0x08. The walk
// carries the slot that will hold the new node rather than the parent, so the
// descent, the empty-tree case and the final store are all one assignment. The
// node's own children are cleared after the link, not before.
void SortedTreeNode::SortedTreeInsert(SortedTreeNode** slot)
{
    SortedTreeNode* cursor = *slot;
    if (cursor != 0) {
        int key = this->Key;
        do {
            slot = (cursor->Key < key) ? &cursor->High : &cursor->Low;
            cursor = *slot;
        } while (cursor != 0);
    }

    *slot = this;
    this->Low = 0;
    this->High = 0;
}

// FUNCTION: GAMEMD 0x5B4080
//
// Free a whole tree depth-first. Both child calls are guarded before the call
// even though the callee opens with the same test, and the node itself is freed
// last.
void SortedTreeNode::SortedTreeFree()
{
    if (this != 0) {
        if (this->Low != 0) {
            this->Low->SortedTreeFree();
        }
        if (this->High != 0) {
            this->High->SortedTreeFree();
        }
        gg_free(this);
    }
}

// FUNCTION: GAMEMD 0x5B4590
//
// Splice a node out of its list. The out-of-line twin of GenericNode::Unlink; the
// second pair of links is re-read from the node rather than kept in registers,
// because the first store can alias them.
void GenericNode::ListNodeUnlink()
{
    if (this != 0 && this->NextNode != 0 && this->PrevNode != 0) {
        this->PrevNode->NextNode = this->NextNode;
        this->NextNode->PrevNode = this->PrevNode;
        this->PrevNode = 0;
        this->NextNode = 0;
    }
}

// FUNCTION: GAMEMD 0x5B4630
//
// The MixFileClass scalar deleting destructor: the same body as Destruct
// above, written out longhand rather than shared, with the conditional free and
// the `this` return that VC6's deleting-destructor convention adds.
MixFileClass* MixFileClass::ScalarDeletingDtor(char flags)
{
    DestructInPlace();
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5B46E0
//
// The GenericList scalar deleting destructor: drain the list hanging off
// the first node, then destroy the two nodes in reverse order, then free the
// host if asked. The drain re-reads the head every iteration and the unlink
// re-tests all three pointers the guard has just tested; both repetitions are
// retail's.
GenericList* GenericList::ScalarDeletingDtor(char flags)
{
    this->Vtable = &GG_VTABLE_GENERIC_LIST_SLOTS;

    while (1) {
        if (!(this->FirstNode.NextNode != 0 && this->FirstNode.NextNode->NextNode != 0
              && this->FirstNode.NextNode->PrevNode != 0)) {
            break;
        }
        this->FirstNode.NextNode->Unlink();
    }

    this->LastNode.DestroyNode();
    this->FirstNode.DestroyNode();

    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

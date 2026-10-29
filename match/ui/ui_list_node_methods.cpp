// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x5B3F50-0x5B4793.
//   Ordered ascending by retail address.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT

#include "ui_list_node_methods.h"

// FUNCTION: GAMEMD 0x5B3F50
//
// Destroy a MixFileClass: release the buffer at +0x0C through the pool free,
// release the record at +0x24 only while the ownership byte says the node
// allocated it, clear both it and the scratch block, and finally take the node
// out of its list - once explicitly and once through the list-node base
// destructor that runs after it.
MixFileClass::~MixFileClass()
{
    if (Buffer != 0) {
        FUN_007C93E8(Buffer);
    }
    if (Record != 0 && OwnsRecord) {
        gg_free(Record);
        OwnsRecord = false;
    }
    Record = 0;
    if (Scratch != 0) {
        gg_free(Scratch);
        Scratch = 0;
    }
    Unlink();
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

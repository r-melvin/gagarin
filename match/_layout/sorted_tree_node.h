// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x5B3FF0 passes the node in ECX and a child slot in EDX.
// 0x5B40B0 allocates 0x10 bytes, stores the key at +8 and cached value at +C,
// and passes the same node to 0x5B3FF0. The name describes these operations;
// the original type name is not established.
#ifndef GG_MATCH_LAYOUT_SORTED_TREE_NODE_H
#define GG_MATCH_LAYOUT_SORTED_TREE_NODE_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct SortedTreeNode
{
    SortedTreeNode* Low;
    SortedTreeNode* High;
    int Key;
    void* Value;

    // Declaration: GAMEMD 0x5B3FF0
    void __fastcall SortedTreeInsert(SortedTreeNode** slot);
    // Declaration: GAMEMD 0x5B4080
    void SortedTreeFree();
};
GG_STATIC_ASSERT(offsetof(SortedTreeNode, Low) == 0x00);
GG_STATIC_ASSERT(offsetof(SortedTreeNode, High) == 0x04);
GG_STATIC_ASSERT(offsetof(SortedTreeNode, Key) == 0x08);
GG_STATIC_ASSERT(offsetof(SortedTreeNode, Value) == 0x0C);
GG_STATIC_ASSERT(sizeof(((SortedTreeNode*)0)->Low) == 4);
GG_STATIC_ASSERT(sizeof(((SortedTreeNode*)0)->High) == 4);
GG_STATIC_ASSERT(sizeof(((SortedTreeNode*)0)->Key) == 4);
GG_STATIC_ASSERT(sizeof(((SortedTreeNode*)0)->Value) == 4);
GG_STATIC_ASSERT(sizeof(SortedTreeNode) == 0x10);
#endif

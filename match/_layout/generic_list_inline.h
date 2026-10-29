// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Inline bodies of GenericNode::GenericNode (0x40E320), GenericNode::Link
// (0x40E340) and GenericList::GenericList (0x52ACE0) for translation units whose
// retail code expands them in place (the compiler's inline decision differs
// per call site in retail; the out-of-line bodies live in
// match/platform/ini_class_node_methods.cpp). Include after generic_list.h.
#ifndef GG_MATCH_LAYOUT_GENERIC_LIST_INLINE_H
#define GG_MATCH_LAYOUT_GENERIC_LIST_INLINE_H
#include "generic_list.h"
inline GenericNode::GenericNode() : NextNode(0), PrevNode(0) {}
inline void GenericNode::Link(GenericNode* node)
{
    node->Unlink();
    node->NextNode = NextNode;
    node->PrevNode = this;
    if (NextNode != 0) {
        NextNode->PrevNode = node;
    }
    NextNode = node;
}
inline GenericList::GenericList() { FirstNode.Link(&LastNode); }
#endif

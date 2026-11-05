// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Inline body of GenericList::GenericList (0x52ACE0) for translation units whose retail code expands the head sentinel
// and calls GenericNode::GenericNode (0x40E320) for the tail, then GenericNode::Link (0x40E340), as at 0x4F1BDB.
// An inline GenericNode() gives the same bytes but leaves that call against a local COMDAT copy, which
// clashes with the out-of-line definition in ini_class_node_methods.cpp (LNK2005); the int overload keeps the call external.
#ifndef GG_MATCH_LAYOUT_GENERIC_LIST_CTOR_FIRST_INLINE_H
#define GG_MATCH_LAYOUT_GENERIC_LIST_CTOR_FIRST_INLINE_H
#include "generic_list.h"
inline GenericList::GenericList() : FirstNode(0) { FirstNode.Link(&LastNode); }
#endif

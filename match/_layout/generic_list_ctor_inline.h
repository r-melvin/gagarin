// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Inline bodies of GenericNode::GenericNode (0x40E320) and GenericList::GenericList (0x52ACE0) for translation
// units whose retail code expands the constructors but still calls GenericNode::Link (0x40E340), as the
// wolinfoMD.ini accessors do (`call 0x40E340` at 0x7797A6). generic_list_inline.h adds the inline Link.
#ifndef GG_MATCH_LAYOUT_GENERIC_LIST_CTOR_INLINE_H
#define GG_MATCH_LAYOUT_GENERIC_LIST_CTOR_INLINE_H
#include "generic_list.h"
inline GenericNode::GenericNode() : NextNode(0), PrevNode(0) {}
inline GenericList::GenericList() { FirstNode.Link(&LastNode); }
#endif

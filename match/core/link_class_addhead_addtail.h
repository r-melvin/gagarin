// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   LinkClass::AddHead / LinkClass::AddTail list-splice ops, matched
//   byte-for-byte against the user's retail gamemd.exe v1.001 (Ghidra CLI
//   disassembly at 0x5566D0 / 0x556700), cross-checked against YRpp
//   (reconfirmed here).
//
// Reuses the binding LinkClass layout + vtable-slot order from
// link_class_methods.h. The vtable slots these methods call indirectly:
//   * Remove     == vtable +0x24 (slot 9)
//   * HeadOfList == vtable +0x18 (slot 6)
//   * TailOfList == vtable +0x1c (slot 7)
// are fixed by that header's declaration order.
#ifndef GG_MATCH_CORE_LINK_CLASS_ADDHEAD_ADDTAIL_H
#define GG_MATCH_CORE_LINK_CLASS_ADDHEAD_ADDTAIL_H

#include "link_class_methods.h"

#endif  // GG_MATCH_CORE_LINK_CLASS_ADDHEAD_ADDTAIL_H

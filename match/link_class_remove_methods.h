// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   LinkClass::Remove, matched byte-for-byte against the user's retail
//   gamemd.exe v1.001 (Ghidra CLI disassembly at 0x556730), cross-checked
//   against YRpp (reconfirmed here).
//
// Reuses the binding LinkClass layout + vtable-slot order from
// link_class_methods.h. The vtable slots this method calls indirectly:
//   * HeadOfList == vtable +0x18 (slot 6)
//   * TailOfList == vtable +0x1c (slot 7)
// are fixed by that header's declaration order. Next@0x4 / Previous@0x8 are
// confirmed numerically from the disasm below ([ESI+0x4] / [ESI+0x8]).
#ifndef GG_MATCH_CORE_LINK_CLASS_REMOVE_METHODS_H
#define GG_MATCH_CORE_LINK_CLASS_REMOVE_METHODS_H

#include "link_class_methods.h"

#endif  // GG_MATCH_CORE_LINK_CLASS_REMOVE_METHODS_H

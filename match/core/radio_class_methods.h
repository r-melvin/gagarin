// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes to match: user's retail gamemd.exe v1.001 (Ghidra disasm at
//   0x65AD50..0x65AEA1). Offsets reconfirmed from the member accesses:
//     [ECX+0xE4] = RadioLinks.Items, [ECX+0xE8] = RadioLinks.Capacity, where
//     RadioLinks (VectorClass) lives at 0xE0 (committed _layout/radio_class.h).
//   Names + signatures cross-checked vs YRpp (consult-only).
//
// RadioClass radio-link query/mutator methods. The class layout (and these
// method declarations) live in the committed P2 layout-spine header; this TU
// only supplies the bodies.
#ifndef GG_MATCH_CORE_RADIO_CLASS_METHODS_H
#define GG_MATCH_CORE_RADIO_CLASS_METHODS_H

#include "../_layout/radio_class.h"

#endif  // GG_MATCH_CORE_RADIO_CLASS_METHODS_H

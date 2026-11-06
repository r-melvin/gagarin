// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x486920: the cell's OverlayTypeIndex `[EBX+0x44]`
//   (0x7E = veins), OverlayData `[EBX+0x11E]` (at least 0x30), SlopeIndex
//   `[EBX+0x11C]`, the flag word `[EBX+0x140]` bit 0x20000, MapCoords
//   `[EBX+0x24]` and the occupier list `[EBX+0xE4]` threaded through
//   `[ESI+0x30]`; on each occupier the height slot `[EAX+0x1C8]`, the
//   AbstractClass flag byte `[ESI+0x14]` bit 0, the type slot `[EDX+0x84]`
//   and the type's byte at `+0xC91`, plus the ability probe 0x70D0D0 with
//   8 pushed; the 0x1C8-byte animation from `operator new` 0x7C8E17 built
//   by 0x421EA0 with the rules animation at `[0x8871E0]+0xE8`; and the
//   cell's own height query 0x47B3A0 taking a sub-cell offset. Offsets
//   agree with match/cell_class_fog_methods.h (Flags 0x140) and
//   match/cell_class_wall_owner_methods.h (OverlayTypeIndex 0x44).
//   Names cross-checked against YRpp.
#ifndef GG_MATCH_MAP_CELL_CLASS_ACTIVATE_VEINS_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_ACTIVATE_VEINS_METHODS_H

#include "_layout/rules_class.h"

#endif  // GG_MATCH_MAP_CELL_CLASS_ACTIVATE_VEINS_METHODS_H

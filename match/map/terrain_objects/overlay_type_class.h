// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only)
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI
//   .?AVOverlayTypeClass@@ (terrain_common_views.h), the constructor 0x5FE250 (every member store below), the
//   INI reader 0x5FE770 (every key string and member offset), the CRC slot 0x5FEA50, and the
//   allocation sites 0x5FECC6 and 0x6C313C (`PUSH 0x2BC; CALL 0x7C8E17`, two sites, both agreeing).
//
// OverlayTypeClass: the rules-INI template of an overlay ([OverlayTypes] sections). The class is the
// canonical one in _layout/overlay_type_class.h (ObjectTypeClass base); this header adds the module
// statics (overlay_shared.h).
//
//   +0x00..+0x293  ObjectTypeClass (AbstractClass / AbstractTypeClass / ObjectTypeClass members)
//   +0x294 ArrayIndex  +0x298 Land  +0x29C CellAnim  +0x2A0 DamageLevels  +0x2A4 Strength
//   +0x2A8 Wall  +0x2A9 Tiberium  +0x2AA Crate  +0x2AB CrateTrigger  +0x2AC NoUseTileLandType
//   +0x2AD IsVeinholeMonster  +0x2AE IsVeins  +0x2B0 Explodes  +0x2B1 ChainReaction
//   +0x2B2 Overrides  +0x2B3 DrawFlat  +0x2B4 IsRubble  +0x2B5 IsARock  +0x2B6 RadarColor
//   sizeof 0x2BC (from the allocation)
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_TYPE_CLASS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_TYPE_CLASS_H

#include "../../_layout/overlay_type_class.h"
#include "overlay_shared.h"

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_TYPE_CLASS_H

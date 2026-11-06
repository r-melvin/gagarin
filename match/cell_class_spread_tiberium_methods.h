// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI inside 0x483780:
//     CellClass: MapCoords [EDI+0x24] (0x483851), OverlayTypeIndex [EDI+0x44]
//       (0x48379B, 0x4837EB), FirstObject [EDI+0xE4] (0x4837E1), the byte
//       [EDI+0x11C] (0x4837BB) and OverlayData [EDI+0x11E] (0x4837AF).
//     ScenarioClass* at 0xA8B230: the byte at +0 tested with 0x80 (0x483796)
//       and the Randomizer sub-object at +0x218 (LEA at 0x483833).
//     TiberiumClass::Array.Items at 0xB0F4EC indexed by the tiberium index
//       (0x4837C5, 0x48381D); the double at [EAX+0xA0] compared against the
//       double constant at 0x7E3810 (0x4837CE).
//     The 4-byte per-direction step table at 0x89F688, X at +0 and Y at +2
//       (0x48385B, 0x48386F).
//     MapClass::Instance as the immediate 0x87F7E8 feeding GetCellAt 0x5657A0
//       (0x483886).
//   The CellClass offsets agree with the already-matched
//   match/cell_class_tiberium_methods.h and
//   match/cell_class_tiberium_germinate_methods.h (read, not edited;
//   re-derived here so this TU stands alone). Names cross-checked against YRpp.
#ifndef GG_MATCH_MAP_CELL_CLASS_SPREAD_TIBERIUM_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_SPREAD_TIBERIUM_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x5FDD20 (decl; reloc) -- overlay index -> tiberium index,
// or -1. __fastcall, the overlay index in ECX.
int OverlayTypeIndexToTiberium_00483780(int overlayIndex);

// GLOBAL: GAMEMD 0x7E3810 -- the double the tiberium's +0xA0 is compared with.
extern const double DAT_007E3810;

// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
#include "scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;

#endif  // GG_MATCH_MAP_CELL_CLASS_SPREAD_TIBERIUM_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
//
// File-scope reference-counted pointers. Each initialiser calls the out-of-line
// rc_ptr_base constructor (0x65D430) on the object, seats the derived table and
// registers an exit stub that reseats the table and tail-jumps into the
// rc_ptr_base destructor (0x65D460). The four at 0xB77F58..0xB77F78 sit in the
// WorldDom.cpp window (0x7AF0B0-0x7B0B9F) next to the two owned blocks at
// 0xB77F54/0xB77F60; 0xB75E48 follows the Wonline code.
#include "world_domination_tour.h"

namespace WorldDominationTour { class Campaign; }

// SYNTHETIC: GAMEMD 0x006C8840 -- rc_ptr<PlayerProfile>::`scalar deleting destructor' (compiler-emitted for the
// rc_ptr<PlayerProfile> below; retail's copy sits in an unrecovered TU near 0x6C8840)

// SYNTHETIC: GAMEMD 0x0077D120 -- initialiser of DAT_00B75E48, registers the exit stub
// SYNTHETIC: GAMEMD 0x0077D140 -- exit stub of DAT_00B75E48 (destructor)
// GLOBAL: GAMEMD 0xB75E48
rc_ptr<PlayerProfile> DAT_00B75E48;

// SYNTHETIC: GAMEMD 0x007B0110 -- initialiser of DAT_00B77F58, registers the exit stub
// SYNTHETIC: GAMEMD 0x007B0130 -- exit stub of DAT_00B77F58 (destructor)
// GLOBAL: GAMEMD 0xB77F58
rc_ptr<WDTState> DAT_00B77F58;

// SYNTHETIC: GAMEMD 0x007B0150 -- initialiser of DAT_00B77F70, registers the exit stub
// SYNTHETIC: GAMEMD 0x007B0170 -- exit stub of DAT_00B77F70 (destructor)
// GLOBAL: GAMEMD 0xB77F70
rc_ptr<WDTState> DAT_00B77F70;

// SYNTHETIC: GAMEMD 0x007B0190 -- initialiser of DAT_00B77F68, registers the exit stub
// SYNTHETIC: GAMEMD 0x007B01B0 -- exit stub of DAT_00B77F68 (destructor)
// GLOBAL: GAMEMD 0xB77F68
rc_ptr<WorldDominationTour::Campaign> DAT_00B77F68;

// SYNTHETIC: GAMEMD 0x007B01D0 -- initialiser of DAT_00B77F78, registers the exit stub
// SYNTHETIC: GAMEMD 0x007B01F0 -- exit stub of DAT_00B77F78 (destructor)
// GLOBAL: GAMEMD 0xB77F78
rc_ptr<WorldDominationTour::Campaign> DAT_00B77F78;

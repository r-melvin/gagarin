// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x65B4C0-0x65B527), cross-checked
//   against YRpp (reconfirmed
//   numerically here).
//   Add at 0x65B530 independently confirms the shared fields/global;
//   its 0x4A-byte entry-origin body was rechecked through REA/Ghidra.
//
// RadSiteClass - a radiation site: a center cell, a spread (in cells and in
// leptons), a rad level, and a countdown duration / time-left pair used to
// scale the currently applied radiation.
#ifndef GG_MATCH_COMBAT_RAD_SITE_CLASS_H
#define GG_MATCH_COMBAT_RAD_SITE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/rules_class.h"

// CellStruct - map cell coordinate (short X, short Y); 4 bytes. SetBaseCell
// copies it as a single dword (mov edx,[eax]; mov [ecx+0x40],edx).
#include "../_layout/cell.h"

#include "../_layout/rad_site_class.h"

GG_STATIC_ASSERT(offsetof(RadSiteClass, BaseCell)        == 0x40);
GG_STATIC_ASSERT(offsetof(RadSiteClass, Spread)          == 0x44);
GG_STATIC_ASSERT(offsetof(RadSiteClass, SpreadInLeptons) == 0x48);
GG_STATIC_ASSERT(offsetof(RadSiteClass, RadLevel)        == 0x4C);
GG_STATIC_ASSERT(offsetof(RadSiteClass, RadDuration)     == 0x6C);
GG_STATIC_ASSERT(offsetof(RadSiteClass, RadTimeLeft)     == 0x70);
#endif  // GG_MATCH_COMBAT_RAD_SITE_CLASS_H

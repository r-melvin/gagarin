// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// This address-ordered view groups neighboring global reset and periodic-state
// update routines. Every global width and address below is corroborated by a
// direct qword/dword operand in the retail functions defined in the source.
#ifndef GG_MATCH_CORE_PERIODIC_STATE_UPDATES_00439480_H
#define GG_MATCH_CORE_PERIODIC_STATE_UPDATES_00439480_H

#include "../_rt/gg_static_assert.h"

GG_STATIC_ASSERT(sizeof(unsigned int) == 4);
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(double) == 8);

// GLOBAL: GAMEMD 0x0089C700
extern double DAT_0089C700;
// GLOBAL: GAMEMD 0x0089C720
extern double DAT_0089C720;
// GLOBAL: GAMEMD 0x0089C728
extern double DAT_0089C728;
// GLOBAL: GAMEMD 0x0089C730
extern double DAT_0089C730;
// GLOBAL: GAMEMD 0x0089C748
extern double DAT_0089C748;
// GLOBAL: GAMEMD 0x0089C750
extern double DAT_0089C750;
// GLOBAL: GAMEMD 0x0089C758
extern double DAT_0089C758;
// GLOBAL: GAMEMD 0x0089C770
extern double DAT_0089C770;
// GLOBAL: GAMEMD 0x0089C778
extern int DAT_0089C778;
// GLOBAL: GAMEMD 0x007E1720
extern double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1728
extern double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730
extern double DAT_007E1730;
// GLOBAL: GAMEMD 0x007E1738
extern double DAT_007E1738;
// GLOBAL: GAMEMD 0x007E1740
extern double DAT_007E1740;
// GLOBAL: GAMEMD 0x007E3D70
extern double DAT_007E3D70;
// GLOBAL: GAMEMD 0x007E3D78
extern double DAT_007E3D78;


#endif

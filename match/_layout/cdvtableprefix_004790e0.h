// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_CDVTABLEPREFIX_004790E0_H
#define GG_MATCH__LAYOUT_CDVTABLEPREFIX_004790E0_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "cd_004790e0.h"

typedef bool (CD_004790E0::*CDSlot0Call_004790E0)(int);
struct CDVtablePrefix_004790E0 { CDSlot0Call_004790E0 slot0; };
GG_STATIC_ASSERT(sizeof(CDSlot0Call_004790E0) == 4);
GG_STATIC_ASSERT(offsetof(CDVtablePrefix_004790E0, slot0) == 0);
GG_STATIC_ASSERT(sizeof(CDVtablePrefix_004790E0) == 4);

#endif

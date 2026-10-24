// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Physical grouping only, not an original record type/name claim.
// Native6971C4..6971E5: eight IPX objects at398+n*68; later zero33C..67C.
#ifndef GG_MATCH_LAYOUT_SESSION_RECORD_H
#define GG_MATCH_LAYOUT_SESSION_RECORD_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "ipx_address_class.h"
struct SessionRecord_0000033C
{
    char unknown_00[0x5C];
    IPXAddressClass unknown_5C;
};
GG_STATIC_ASSERT(offsetof(SessionRecord_0000033C, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(sizeof(SessionRecord_0000033C) == 0x68);
#endif

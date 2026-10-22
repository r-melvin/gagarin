// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: pinned retail instruction operands at 0x4B5A50 and DropPod
//             uses at 0x4B5AB0 / 0x4B6070.
// Address-scoped view of the three adjacent dwords at 0x008A0820. This records
// their demonstrated coordinate use; it does not assert an original aggregate
// type or name.
#ifndef GG_MATCH_CORE_COORDINATE_STORAGE_008A0820_H
#define GG_MATCH_CORE_COORDINATE_STORAGE_008A0820_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../movement/loco_interfaces.h"

// The adjacent dwords are used through the existing LocoCoord shape. This is
// an address-scoped storage view, not a claim about the original declaration.
typedef LocoCoord CoordinateStorage_008A0820;

// GLOBAL: GAMEMD 0x008A0820 — one contiguous three-dword storage view.
extern "C" CoordinateStorage_008A0820 DAT_008A0820;

#endif

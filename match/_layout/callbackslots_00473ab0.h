// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_CALLBACKSLOTS_00473AB0_H
#define GG_MATCH__LAYOUT_CALLBACKSLOTS_00473AB0_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "callbackview_00473ab0.h"

typedef void (CallbackView_00473AB0::*CallbackCall_00473AB0)(int);
struct CallbackSlots_00473AB0 { CallbackCall_00473AB0 first; };
GG_STATIC_ASSERT(sizeof(CallbackCall_00473AB0) == 4);
GG_STATIC_ASSERT(offsetof(CallbackSlots_00473AB0, first) == 0);

#endif

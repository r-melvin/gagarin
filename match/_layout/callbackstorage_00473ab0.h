// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_CALLBACKSTORAGE_00473AB0_H_H
#define GG_MATCH__LAYOUT_CALLBACKSTORAGE_00473AB0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CallbackStorage_00473AB0 { void* vtable; unsigned char unknown_04[4]; };
GG_STATIC_ASSERT(offsetof(CallbackStorage_00473AB0, vtable) == 0);
GG_STATIC_ASSERT(offsetof(CallbackStorage_00473AB0, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(CallbackStorage_00473AB0) == 8);
#endif

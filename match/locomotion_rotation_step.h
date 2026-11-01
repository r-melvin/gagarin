// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary: retail gamemd.exe v1.001. Entry-origin disassembly
// at 0x55A730 and 0x55A7D0 reads the double at 0x7E4408; the pinned image
// stores -pi/16 there. The identifier is a working ABI name, not a retail name.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_ROTATION_STEP_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_ROTATION_STEP_H
#include "_rt/gg_static_assert.h"
#include "shared_constants_globals.h"
GG_STATIC_ASSERT(sizeof(double) == 8);
#endif

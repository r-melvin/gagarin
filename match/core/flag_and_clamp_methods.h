// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and globals read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x4010A0 / 0x401170 / 0x406620 /
//   0x407000. None is bound by YRpp.
//
// Flag tests, a flag clear and a clamped setter.
#ifndef GG_MATCH_CORE_FLAG_AND_CLAMP_METHODS_H
#define GG_MATCH_CORE_FLAG_AND_CLAMP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "triple_timer_init_methods.h"
#include "../_layout/audio_event_type.h"

// GLOBAL: GAMEMD 0x87E728
extern void* DAT_0087E728;



// FUNCTION: GAMEMD 0x407000
bool __cdecl FUN_00407000();

#endif  // GG_MATCH_CORE_FLAG_AND_CLAMP_METHODS_H

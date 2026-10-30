// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, the clamp bound and both shifts read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x4061D0.
//
// Clamp a level to 0..0x4000, scale it by the rate held at +0x24, and hand it
// to one of two setters depending on the mode at +0x1C.
//
// The clamp is written twice in retail, once per branch, and each copy compares
// *unsigned* (`CMP EDX,0x4000; JBE`) before testing the sign. With the value
// unsigned the second test can never fire - anything negative is already above
// the bound - so the `XOR EAX,EAX` arm is dead in both copies. It is reproduced
// as written rather than tidied away.
//
// The scale is `(rate >> 16) * level >> 14`, both shifts unsigned.
#ifndef GG_MATCH_CORE_CLAMPED_SCALE_METHODS_H
#define GG_MATCH_CORE_CLAMPED_SCALE_METHODS_H

#include <stddef.h>
#include "triple_timer_init_methods.h"
#include "../_layout/audio_event.h"
#include "../_rt/gg_static_assert.h"


#endif  // GG_MATCH_CORE_CLAMPED_SCALE_METHODS_H

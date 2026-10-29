// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x720A80: `MOV EAX,[ESI+0x18]` (Themes.Items),
//   `MOV EAX,[ESI+0x24]` (Themes.Count), `[ECX+0x289]` (ThemeControl::Repeat),
//   `[ESI+0x10]` (IsScoreRepeat), `[ESI+0x12]` (IsScoreShuffle), the global
//   Randomizer at 0x886B88 (`MOV ECX,0x886B88; CALL 0x65C7E0`) and the
//   __thiscall IsAvailable at 0x721140. Names cross-checked against YRpp
//   (names only, no text copied).
//
// ThemeClass -- the score jukebox. Layout mirrors match/audio/
// theme_class_methods.h (Themes vector @0x14 -> Items @0x18, Count @0x24) and
// is redefined here so the TU stays standalone.
#ifndef GG_MATCH_AUDIO_THEME_CLASS_RANDOM_METHODS_H
#define GG_MATCH_AUDIO_THEME_CLASS_RANDOM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/theme_class.h"
#include "../core/randomizer.h"   // Randomizer::RandomRanged @0x65C7E0

#endif  // GG_MATCH_AUDIO_THEME_CLASS_RANDOM_METHODS_H

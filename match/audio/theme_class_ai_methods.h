// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x7209D0: `[ESI+0x4]` (LastTheme, pushed to
//   0x720A80), `[ESI+0x8]` (QueuedTheme, compared to -1/-3/-2 and stored),
//   `[ESI+0xC]` (Volume, signed `JLE`), `[ESI+0x11]` (IsFading byte),
//   `[ESI+0x2C]` (Stream, receiver of 0x4080D0 / 0x407F40 / 0x408070), the
//   byte globals `[0xA8ED64]` / `[0xA8EC74]`, the dword global `[0xA8E7AC]`,
//   the log format string at 0x8447B8 and the callees 0x407000 / 0x4068E0 /
//   0x720A80 / 0x720BB0. Names cross-checked against YRpp
//   every offset reconfirmed here. The layout
//   repeats the one proven in match/audio/theme_class_queue_methods.h.
#ifndef GG_MATCH_AUDIO_THEME_CLASS_AI_METHODS_H
#define GG_MATCH_AUDIO_THEME_CLASS_AI_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/theme_class.h"

// GLOBAL: GAMEMD 0xA8EC74 — ThemeClass::ScoresPresent (byte).
extern bool ScoresPresent_00A8EC74;
// GLOBAL: GAMEMD 0xA8ED64 — byte gate; nonzero suppresses the whole tick.
extern bool DAT_00A8ED64;
// GLOBAL: GAMEMD 0xA8E7AC — dword; nonzero suppresses starting a score.
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x407000 (decl; reloc) — audio engine present.
int __cdecl FUN_00407000();
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

#endif  // GG_MATCH_AUDIO_THEME_CLASS_AI_METHODS_H

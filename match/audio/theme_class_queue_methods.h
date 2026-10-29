// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI. QueueSong @0x720B20: `[ESI+0x4]` (LastTheme), `[ESI+0x8]`
//   (QueuedTheme, stored), `[ESI+0x11]` (IsFading byte), `[ESI+0x2C]`
//   (Stream), the byte globals `[0xA8EC74]` / `[0xA8ED64]`, the log format
//   string at 0x8447D4 and the callees 0x407000 / 0x4068E0 / 0x4080D0 /
//   0x407F40 / 0x408070 / 0x4080C0. IsAvailable @0x721140: `[ECX+0x24]`
//   (Themes.Count, unsigned compare), `[ECX+0x18]` (Themes.Items), the
//   ThemeControl bytes `[EAX+0x28A]` / `[EAX+0x288]`, ints `[EAX+0x28C]` /
//   `[EAX+0x280]`, the pointer global `[0xA83D4C]` (HouseClass::CurrentPlayer)
//   with `[EDX+0x34]` (Type) and `[EDX+0xBC]` (the type's side index), the int
//   global `[0xA8B238]` (SessionClass::Instance.GameMode) and the pointer
//   global `[0xA8B230]` (ScenarioClass::Instance) with `[ECX+0x1254]`.
//   Names cross-checked against YRpp
//   every offset reconfirmed here.
//   The ThemeClass / ThemeControl layout repeats the one already proven in
//   match/audio/theme_class_methods.h (Themes@0x14 -> Items@0x18, Count@0x24).
#ifndef GG_MATCH_AUDIO_THEME_CLASS_QUEUE_METHODS_H
#define GG_MATCH_AUDIO_THEME_CLASS_QUEUE_METHODS_H

#include <stddef.h>
#include "../_layout/session_class.h"
#include "../_rt/gg_static_assert.h"
#include "../_layout/theme_class.h"




// GLOBAL: GAMEMD 0xA8EC74 — ThemeClass::ScoresPresent (byte).
extern bool ScoresPresent_00A8EC74;
// GLOBAL: GAMEMD 0xA8ED64 — byte gate; nonzero suppresses queueing.
extern bool DAT_00A8ED64;
// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
extern HouseClass* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;

// FUNCTION: GAMEMD 0x407000 (decl; reloc) — audio engine present.
int __cdecl FUN_00407000();
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

#endif  // GG_MATCH_AUDIO_THEME_CLASS_QUEUE_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x720EA0: `CMP dword ptr [ESI],-1` (CurrentTheme),
//   `[ESI+0x4]` (LastTheme, the log argument), `[ESI+0x8]` (QueuedTheme, the
//   three -1 stores at 0x720F4B), `MOV AL,[ESI+0x11]` (IsFading, set to 1 at
//   0x720F28), `[ESI+0x2C]` (Stream, receiver of 0x4080D0 / 0x407F40 /
//   0x408070 / 0x4080C0), the byte globals `[0xA8EC74]` / `[0xA8ED64]`, the
//   engine probe `CALL 0x407000`, the log sink `CALL 0x4068E0` with the
//   strings at 0x844830 / 0x84481C, and the byte parameter `MOV AL,[ESP+8]`.
//   Names cross-checked against YRpp
//   ; the layout repeats match/audio/theme_class_queue_methods.h.
#ifndef GG_MATCH_AUDIO_THEME_CLASS_STOP_METHODS_H
#define GG_MATCH_AUDIO_THEME_CLASS_STOP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The playback stream object hanging off ThemeClass +0x2C. Its four
// __thiscall methods are declared only (bodies live in match/core).
#include "themestream_00720ea0.h"

struct ThemeClass
{
    int  CurrentTheme;          // +0x00
    int  LastTheme;             // +0x04
    int  QueuedTheme;           // +0x08
    int  Volume;                // +0x0C
    bool IsScoreRepeat;         // +0x10
    bool IsFading;              // +0x11
    bool IsScoreShuffle;        // +0x12
    char _pad13[0x2C - 0x13];   // +0x13
    ThemeStream_00720EA0* Stream;  // +0x2C

    // FUNCTION: GAMEMD 0x720EA0
    void Stop(bool fade);
};
GG_STATIC_ASSERT(offsetof(ThemeClass, CurrentTheme) == 0x00);
GG_STATIC_ASSERT(offsetof(ThemeClass, LastTheme)    == 0x04);
GG_STATIC_ASSERT(offsetof(ThemeClass, QueuedTheme)  == 0x08);
GG_STATIC_ASSERT(offsetof(ThemeClass, IsFading)     == 0x11);
GG_STATIC_ASSERT(offsetof(ThemeClass, Stream)       == 0x2C);

// GLOBAL: GAMEMD 0xA8EC74 — ThemeClass::ScoresPresent (byte).
extern bool ScoresPresent_00A8EC74;
// GLOBAL: GAMEMD 0xA8ED64 — byte gate; nonzero suppresses the stop.
extern bool DAT_00A8ED64;

// FUNCTION: GAMEMD 0x407000 (decl; reloc) — audio engine present.
int __cdecl FUN_00407000();
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

#endif  // GG_MATCH_AUDIO_THEME_CLASS_STOP_METHODS_H

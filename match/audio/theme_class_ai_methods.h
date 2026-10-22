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

// The playback stream object hanging off ThemeClass +0x2C. Three __thiscall
// methods are declared only (bodies live in match/core).
struct ThemeStream_007209D0
{
    // FUNCTION: GAMEMD 0x407F40 (decl; reloc)
    void FUN_00407F40();
    // FUNCTION: GAMEMD 0x408070 (decl; reloc)
    int  FUN_00408070() const;
    // FUNCTION: GAMEMD 0x4080D0 (decl; reloc)
    int  FUN_004080D0() const;
};

// DynamicVectorClass<ThemeControl*> head — not touched here; modelled for the
// 0x18-byte span so Stream lands at +0x2C.
struct ThemeControlVector_007209D0
{
    void* Vtbl;                 // +0x00
    void* Items;                // +0x04
    int   Capacity;             // +0x08
    int   IsAllocated;          // +0x0C
    int   Count;                // +0x10
    int   CapacityIncrement;    // +0x14
};
GG_STATIC_ASSERT(sizeof(ThemeControlVector_007209D0) == 0x18);

struct ThemeClass
{
    int  CurrentTheme;                      // +0x00
    int  LastTheme;                         // +0x04
    int  QueuedTheme;                       // +0x08
    int  Volume;                            // +0x0C
    bool IsScoreRepeat;                     // +0x10
    bool IsFading;                          // +0x11
    bool IsScoreShuffle;                    // +0x12
    ThemeControlVector_007209D0 Themes;     // +0x14
    ThemeStream_007209D0* Stream;           // +0x2C

    // FUNCTION: GAMEMD 0x7209D0
    void AI();
    // FUNCTION: GAMEMD 0x720A80 (decl; reloc) — pick the next score.
    int GetRandomIndex(int index);
    // FUNCTION: GAMEMD 0x720BB0 (decl; reloc) — start playing a score; its
    // own trace string at 0x8447EC names it Theme::PlaySong.
    void PlaySong(int index);
};
GG_STATIC_ASSERT(offsetof(ThemeClass, LastTheme)   == 0x04);
GG_STATIC_ASSERT(offsetof(ThemeClass, QueuedTheme) == 0x08);
GG_STATIC_ASSERT(offsetof(ThemeClass, Volume)      == 0x0C);
GG_STATIC_ASSERT(offsetof(ThemeClass, IsFading)    == 0x11);
GG_STATIC_ASSERT(offsetof(ThemeClass, Stream)      == 0x2C);

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

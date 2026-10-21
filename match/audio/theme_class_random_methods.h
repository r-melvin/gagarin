// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x720A80: `MOV EAX,[ESI+0x18]` (Themes.Items),
//   `MOV EAX,[ESI+0x24]` (Themes.Count), `[ECX+0x289]` (ThemeControl::Repeat),
//   `[ESI+0x10]` (IsScoreRepeat), `[ESI+0x12]` (IsScoreShuffle), the global
//   Randomizer at 0x886B88 (`MOV ECX,0x886B88; CALL 0x65C7E0`) and the
//   __thiscall IsAvailable at 0x721140. Names cross-checked against YRpp
//   ThemeClass.h (consult-only; names only, no text copied).
//
// ThemeClass -- the score jukebox. Layout mirrors match/audio/
// theme_class_methods.h (Themes vector @0x14 -> Items @0x18, Count @0x24) and
// is redefined here so the TU stays standalone.
#ifndef GG_MATCH_AUDIO_THEME_CLASS_RANDOM_METHODS_H
#define GG_MATCH_AUDIO_THEME_CLASS_RANDOM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/randomizer.h"   // Randomizer::RandomRanged @0x65C7E0

// One registered score. Only Repeat (+0x289) is touched here; the rest is
// modelled for size faithfulness.
struct ThemeControl
{
    char    ID[0x100];        // +0x0000
    char    Sound[0x100];     // +0x0100
    wchar_t UIName[0x40];     // +0x0200
    int     Scenario;         // +0x0280
    float   Length;           // +0x0284
    bool    Normal;           // +0x0288
    bool    Repeat;           // +0x0289
    bool    Exists;           // +0x028A
    int     Side;             // +0x028C
};
GG_STATIC_ASSERT(offsetof(ThemeControl, Repeat) == 0x289);

// DynamicVectorClass<ThemeControl*> head: vtable@0, Items@4, Count@0x10.
struct ThemeControlVector
{
    void*          _vtable;            // +0x0000
    ThemeControl** Items;              // +0x0004
    int            Capacity;           // +0x0008
    int            IsAllocated;        // +0x000C
    int            Count;              // +0x0010
    int            CapacityIncrement;  // +0x0014
};
GG_STATIC_ASSERT(offsetof(ThemeControlVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(ThemeControlVector, Count) == 0x10);

struct ThemeClass
{
    int  CurrentTheme;        // +0x0000
    int  LastTheme;           // +0x0004
    int  QueuedTheme;         // +0x0008
    int  Volume;              // +0x000C
    bool IsScoreRepeat;       // +0x0010
    bool IsFading;            // +0x0011
    bool IsScoreShuffle;      // +0x0012
    ThemeControlVector Themes;  // +0x0014  (Items +0x18, Count +0x24)
    void* Stream;             // +0x002C

    // FUNCTION: GAMEMD 0x721140 (decl; reloc) -- may this score play now.
    bool IsAvailable(int index);

    // FUNCTION: GAMEMD 0x720A80
    int GetRandomIndex(int index);
};
GG_STATIC_ASSERT(offsetof(ThemeClass, IsScoreRepeat) == 0x10);
GG_STATIC_ASSERT(offsetof(ThemeClass, IsScoreShuffle) == 0x12);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) == 0x14);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) + offsetof(ThemeControlVector, Items) == 0x18);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) + offsetof(ThemeControlVector, Count) == 0x24);

#endif  // GG_MATCH_AUDIO_THEME_CLASS_RANDOM_METHODS_H

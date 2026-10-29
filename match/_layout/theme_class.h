// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Canonical ThemeClass (the score jukebox) and ThemeControl (one registered score). Read from the
//   retail gamemd.exe v1.001:
//   - no vtable of its own (RTTI names only the vector instantiations): ThemeClass has no virtual
//     functions, and the object at 0xA83D10 is 0x2C bytes plus the stream pointer, i.e. 0x30.
//   - Constructor 0x720960 stores -1 to +0x00/+0x04/+0x08, 0xFF to +0x0C (Volume), clears the three
//     bytes at +0x10..+0x12, runs the inlined DynamicVectorClass<ThemeControl*> constructor at +0x14
//     (Items 0, Capacity 0, IsInitialized 1, IsAllocated 0, vtable 0x7F568C, CapacityIncrement 10,
//     Count 0) and finally clears Stream (+0x2C). The exit-time stub 0x4E7E50 is the vector's destructor
//     inlined into ThemeClass' (empty) one.
//   - Clear 0x720770 deletes every ThemeControl (removing element 0 each pass) and then tears down and
//     releases the stream (0x4080C0, 0x4080F0, 0x407F40, 0x407A90) before clearing the pointer.
//   - Accessors 0x720940 / 0x7209B0 / 0x720E50 / 0x721270 index Themes.Items (+0x18) against Themes.Count
//     (+0x24); ThemeControl offsets are confirmed by those and by 0x721140, 0x720A80, 0x7207F0.
//   Names cross-checked against YRpp (names only).
#ifndef GG_MATCH_LAYOUT_THEME_CLASS_H
#define GG_MATCH_LAYOUT_THEME_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class.h"

// ThemeControl -- one registered score's metadata (YRpp order).
struct ThemeControl
{
    char    ID[0x100];      // +0x000
    char    Sound[0x100];   // +0x100
    wchar_t UIName[0x40];   // +0x200
    int     Scenario;       // +0x280
    float   Length;         // +0x284
    bool    Normal;         // +0x288
    bool    Repeat;         // +0x289
    bool    Exists;         // +0x28A
    int     Side;           // +0x28C
};
GG_STATIC_ASSERT(offsetof(ThemeControl, ID)       == 0x000);
GG_STATIC_ASSERT(offsetof(ThemeControl, Sound)    == 0x100);
GG_STATIC_ASSERT(offsetof(ThemeControl, UIName)   == 0x200);
GG_STATIC_ASSERT(offsetof(ThemeControl, Scenario) == 0x280);
GG_STATIC_ASSERT(offsetof(ThemeControl, Length)   == 0x284);
GG_STATIC_ASSERT(offsetof(ThemeControl, Normal)   == 0x288);
GG_STATIC_ASSERT(offsetof(ThemeControl, Repeat)   == 0x289);
GG_STATIC_ASSERT(offsetof(ThemeControl, Exists)   == 0x28A);
GG_STATIC_ASSERT(offsetof(ThemeControl, Side)     == 0x28C);

// The playback stream object hanging off ThemeClass +0x2C. Methods are declared only (bodies live in
// match/core).
struct ThemeStream
{
    // FUNCTION: GAMEMD 0x407A90 (decl; reloc) -- final release, called by ThemeClass::Clear.
    void FUN_00407A90();
    // FUNCTION: GAMEMD 0x407F40 (decl; reloc)
    void FUN_00407F40();
    // FUNCTION: GAMEMD 0x408070 (decl; reloc)
    int  FUN_00408070() const;
    // FUNCTION: GAMEMD 0x4080C0 (decl; reloc)
    void FUN_004080C0();
    // FUNCTION: GAMEMD 0x4080D0 (decl; reloc)
    int  FUN_004080D0() const;
    // FUNCTION: GAMEMD 0x4080F0 (decl; reloc)
    void FUN_004080F0();
};

struct ThemeSaveStream_00721010;

// The global score jukebox at 0xA83D10.
struct ThemeClass
{
    // FUNCTION: GAMEMD 0x720960
    ThemeClass();
    // FUNCTION: GAMEMD 0x720770
    void           Clear();
    const char*    GetName(unsigned int index) const;    // GAMEMD 0x720940
    const wchar_t* GetUIName(unsigned int index) const;  // GAMEMD 0x7209B0
    int            GetLength(unsigned int index) const;  // GAMEMD 0x720E50
    const char*    GetID(int index) const;               // GAMEMD 0x721270
    void           QueueSong(int index);                 // GAMEMD 0x720B20
    bool           IsAvailable(int theme) const;         // GAMEMD 0x721140
    void           Stop(bool fade);                      // GAMEMD 0x720EA0
    bool           FUN_00720FD0();                       // GAMEMD 0x720FD0
    int            FindIndex(const char* id) const;      // GAMEMD 0x721210
    void           FadeStream();                         // GAMEMD 0x720E80
    void           Suspend();                            // GAMEMD 0x720F70
    long           SaveIndexes(ThemeSaveStream_00721010* stm); // GAMEMD 0x721010
    // FUNCTION: GAMEMD 0x7207F0 -- read each score's sound file and fill Length / Exists.
    void Scan();
    // FUNCTION: GAMEMD 0x7209D0
    void AI();
    // FUNCTION: GAMEMD 0x720A80 (decl; reloc) -- pick the next score.
    int GetRandomIndex(int index);
    // FUNCTION: GAMEMD 0x720BB0 (decl; reloc) -- start playing a score; its own trace string at
    // 0x8447EC names it Theme::PlaySong.
    void PlaySong(int index);

    int  CurrentTheme;    // +0x00
    int  LastTheme;       // +0x04
    int  QueuedTheme;     // +0x08
    int  Volume;          // +0x0C
    bool IsScoreRepeat;   // +0x10
    bool IsFading;        // +0x11
    bool IsScoreShuffle;  // +0x12
    DynamicVectorClass<ThemeControl*> Themes;  // +0x14
    ThemeStream* Stream;  // +0x2C
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ThemeClass, CurrentTheme)   == 0x00);
GG_STATIC_ASSERT(offsetof(ThemeClass, LastTheme)      == 0x04);
GG_STATIC_ASSERT(offsetof(ThemeClass, QueuedTheme)    == 0x08);
GG_STATIC_ASSERT(offsetof(ThemeClass, Volume)         == 0x0C);
GG_STATIC_ASSERT(offsetof(ThemeClass, IsScoreRepeat)  == 0x10);
GG_STATIC_ASSERT(offsetof(ThemeClass, IsFading)       == 0x11);
GG_STATIC_ASSERT(offsetof(ThemeClass, IsScoreShuffle) == 0x12);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes)         == 0x14);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) + offsetof(DynamicVectorClass<ThemeControl*>, Items) == 0x18);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) + offsetof(DynamicVectorClass<ThemeControl*>, Count) == 0x24);
GG_STATIC_ASSERT(offsetof(ThemeClass, Stream)         == 0x2C);
GG_STATIC_ASSERT(sizeof(ThemeClass) == 0x30);
#endif

#endif  // GG_MATCH_LAYOUT_THEME_CLASS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names and
//   member order cross-checked against YRpp (`struct ThemeControl`
//   `class ThemeClass`; every offset reconfirmed
//   numerically from the disassembly below).
//
// ThemeClass — the global music/score jukebox. Holds a DynamicVectorClass of
// ThemeControl entries (one per registered score) plus the playback state.
// The four accessors modelled here index that vector and read string / float
// fields out of the selected ThemeControl.
//
// Offsets confirmed from the four accessor disassemblies:
//   GetName    @0x720940:  MOV EDX,[ECX+0x24] (Count); MOV ECX,[ECX+0x18] (Items)
//   GetUIName  @0x7209B0:  Items[i] + 0x200  -> ThemeControl::UIName
//   GetLength  @0x720E50:  FLD float[EDX+0x284] -> ThemeControl::Length
//   GetID      @0x721270:  same Items[i] base, signed bounds, default "none"
#ifndef GG_MATCH_AUDIO_THEME_CLASS_METHODS_H
#define GG_MATCH_AUDIO_THEME_CLASS_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// ThemeControl — one registered score's metadata. YRpp order:
//   FixedString<0x100>  ID      @0x000
//   FixedString<0x100>  Sound   @0x100
//   FixedWString<0x40>  UIName  @0x200   (0x40 wchar_t == 0x80 bytes)
//   int                 Scenario@0x280
//   float               Length  @0x284
//   bool Normal/Repeat/Exists   @0x288..
//   int                 Side    @0x28C
// Only ID(0x000) / UIName(0x200) / Length(0x284) are touched here; the rest are
// modelled for size faithfulness. ID at offset 0 is why GetName/GetID return the
// element pointer unmodified.
// ---------------------------------------------------------------------------
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

GG_STATIC_ASSERT(offsetof(ThemeControl, ID)     == 0x000);
GG_STATIC_ASSERT(offsetof(ThemeControl, UIName) == 0x200);
GG_STATIC_ASSERT(offsetof(ThemeControl, Length) == 0x284);

// DynamicVectorClass<ThemeControl*> head. vtable@0, Items@4, Count@0x10.
// (Mirrors match/_layout/vector_class.h, with Items typed to the element.)
struct ThemeControlVector
{
    void*          _vtable;            // +0x00
    ThemeControl** Items;             // +0x04
    int            Capacity;          // +0x08
    int            IsAllocated;       // +0x0C
    int            Count;             // +0x10
    int            CapacityIncrement; // +0x14
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ThemeControlVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(ThemeControlVector, Count) == 0x10);
#endif

// ---------------------------------------------------------------------------
// ThemeClass — playback state header then the Themes vector @0x14. The 3 bools
// at 0x10..0x12 leave a 1-byte tail pad before the 4-byte-aligned vector, so
// Themes lands at 0x14, putting Items at 0x18 and Count at 0x24 — exactly the
// [ECX+0x18]/[ECX+0x24] member accesses in every accessor.
// ---------------------------------------------------------------------------
struct ThemeClass
{
    const char*    GetName(unsigned int index) const;    // GAMEMD 0x720940
    const wchar_t* GetUIName(unsigned int index) const;  // GAMEMD 0x7209B0
    int            GetLength(unsigned int index) const;   // GAMEMD 0x720E50
    const char*    GetID(int index) const;                // GAMEMD 0x721270
    void FUN_00720BB0(int index); // GAMEMD 0x720BB0; caller0x683D19
    void           QueueSong(int index);                  // GAMEMD 0x720B20
    void           Stop(bool fade);                       // GAMEMD 0x720EA0
    bool           FUN_00720FD0();                        // GAMEMD 0x720FD0
    int            FindIndex(const char* id) const;       // GAMEMD 0x721210

    int  CurrentTheme;    // +0x00
    int  LastTheme;       // +0x04
    int  QueuedTheme;     // +0x08
    int  Volume;          // +0x0C
    bool IsScoreRepeat;   // +0x10
    bool IsFading;        // +0x11
    bool IsScoreShuffle;  // +0x12
    ThemeControlVector Themes;  // +0x14
    void* Stream;         // +0x2C
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes)       == 0x14);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) + offsetof(ThemeControlVector, Items) == 0x18);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) + offsetof(ThemeControlVector, Count) == 0x24);
#endif

#endif  // GG_MATCH_AUDIO_THEME_CLASS_METHODS_H

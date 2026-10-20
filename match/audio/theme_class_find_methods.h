// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Member order
//   cross-checked against YRpp ThemeClass.h (`struct ThemeControl` / `class
//   ThemeClass`, consult-only, NO LICENSE; every offset reconfirmed numerically
//   from the disassembly below).
//
// ThemeClass::FindIndex — locate a registered score by its ID string. Walks the
// Themes vector (DynamicVectorClass<ThemeControl*> @0x14) and _stricmp's each
// element's ID (ThemeControl+0) against the query. This TU mirrors the layout
// already proven in theme_class_methods.h (Themes@0x14 -> Items@0x18, Count@0x24)
// but keeps its own self-contained definition so the single touched method can
// be declared on the struct.
//
// Offsets confirmed from the 0x721210 disassembly:
//   MOV EAX,[EBX+0x24]  -> Themes.Count   (this+0x24)
//   MOV EAX,[EBX+0x18]  -> Themes.Items   (this+0x18)
//   PUSH [EAX+ESI*4]    -> Items[i]  (== &Items[i]->ID, ID at ThemeControl+0)
//   CALL 0x7C8D20       -> _stricmp(Items[i]->ID, id)
#ifndef GG_MATCH_AUDIO_THEME_CLASS_FIND_METHODS_H
#define GG_MATCH_AUDIO_THEME_CLASS_FIND_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ThemeControl — one registered score. Only ID (offset 0) is touched here; the
// rest is modelled for size faithfulness (YRpp ThemeClass.h order).
struct ThemeControl
{
    char    ID[0x100];      // +0x000  FixedString<0x100>
    char    Sound[0x100];   // +0x100
    wchar_t UIName[0x40];   // +0x200
    int     Scenario;       // +0x280
    float   Length;         // +0x284
    bool    Normal;         // +0x288
    bool    Repeat;         // +0x289
    bool    Exists;         // +0x28A
    int     Side;           // +0x28C
};

GG_STATIC_ASSERT(offsetof(ThemeControl, ID) == 0x000);

// DynamicVectorClass<ThemeControl*> head: vtable@0, Items@4, Count@0x10.
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

// ThemeClass — playback state header then the Themes vector @0x14, placing
// Items at 0x18 and Count at 0x24 (matching [EBX+0x18]/[EBX+0x24]).
struct ThemeClass
{
    int FindIndex(const char* id) const;  // GAMEMD 0x721210

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
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) == 0x14);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) + offsetof(ThemeControlVector, Items) == 0x18);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) + offsetof(ThemeControlVector, Count) == 0x24);
#endif

#endif  // GG_MATCH_AUDIO_THEME_CLASS_FIND_METHODS_H

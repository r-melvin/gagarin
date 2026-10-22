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
//   Names cross-checked against YRpp ThemeClass.h / HouseClass.h /
//   ScenarioClass.h (consult-only, NO LICENSE); every offset reconfirmed here.
//   The ThemeClass / ThemeControl layout repeats the one already proven in
//   match/audio/theme_class_methods.h (Themes@0x14 -> Items@0x18, Count@0x24).
#ifndef GG_MATCH_AUDIO_THEME_CLASS_QUEUE_METHODS_H
#define GG_MATCH_AUDIO_THEME_CLASS_QUEUE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One registered score's metadata (see theme_class_methods.h for the full
// derivation). Only Scenario/Normal/Exists/Side are touched here.
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
GG_STATIC_ASSERT(offsetof(ThemeControl, Scenario) == 0x280);
GG_STATIC_ASSERT(offsetof(ThemeControl, Normal)   == 0x288);
GG_STATIC_ASSERT(offsetof(ThemeControl, Exists)   == 0x28A);
GG_STATIC_ASSERT(offsetof(ThemeControl, Side)     == 0x28C);

// DynamicVectorClass<ThemeControl*> head: vtable@0, Items@4, Count@0x10.
struct ThemeControlVector
{
    void*          Vtbl;               // +0x00
    ThemeControl** Items;              // +0x04
    int            Capacity;           // +0x08
    int            IsAllocated;        // +0x0C
    int            Count;              // +0x10
    int            CapacityIncrement;  // +0x14
};
GG_STATIC_ASSERT(offsetof(ThemeControlVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(ThemeControlVector, Count) == 0x10);

// The playback stream object hanging off ThemeClass +0x2C. Its four
// __thiscall methods are declared only (bodies live in match/core).
struct ThemeStream_00720B20
{
    // FUNCTION: GAMEMD 0x407F40 (decl; reloc)
    void FUN_00407F40();
    // FUNCTION: GAMEMD 0x408070 (decl; reloc)
    int  FUN_00408070() const;
    // FUNCTION: GAMEMD 0x4080C0 (decl; reloc)
    void FUN_004080C0();
    // FUNCTION: GAMEMD 0x4080D0 (decl; reloc)
    int  FUN_004080D0() const;
};

struct ThemeClass
{
    int  CurrentTheme;          // +0x00
    int  LastTheme;             // +0x04
    int  QueuedTheme;           // +0x08
    int  Volume;                // +0x0C
    bool IsScoreRepeat;         // +0x10
    bool IsFading;              // +0x11
    bool IsScoreShuffle;        // +0x12
    ThemeControlVector Themes;  // +0x14
    ThemeStream_00720B20* Stream;  // +0x2C

    // FUNCTION: GAMEMD 0x720B20 — named by its own trace string at 0x8447D4.
    void QueueSong(int theme);
    // FUNCTION: GAMEMD 0x721140
    bool IsAvailable(int theme) const;
};
GG_STATIC_ASSERT(offsetof(ThemeClass, LastTheme)   == 0x04);
GG_STATIC_ASSERT(offsetof(ThemeClass, QueuedTheme) == 0x08);
GG_STATIC_ASSERT(offsetof(ThemeClass, IsFading)    == 0x11);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes)      == 0x14);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) + offsetof(ThemeControlVector, Items) == 0x18);
GG_STATIC_ASSERT(offsetof(ThemeClass, Themes) + offsetof(ThemeControlVector, Count) == 0x24);
GG_STATIC_ASSERT(offsetof(ThemeClass, Stream)      == 0x2C);

// HouseClass::CurrentPlayer -> Type -> side index, as read at 0x721195.
struct HouseType_00721140
{
    char _pad000[0xBC];   // +0x0000
    int  SideIndex;       // +0x00BC
};
GG_STATIC_ASSERT(offsetof(HouseType_00721140, SideIndex) == 0xBC);

struct House_00721140
{
    char _pad000[0x34];         // +0x0000
    HouseType_00721140* Type;   // +0x0034
};
GG_STATIC_ASSERT(offsetof(House_00721140, Type) == 0x34);

// ScenarioClass::Instance +0x1254, compared against ThemeControl::Scenario.
struct Scenario_00721140
{
    char _pad0000[0x1254];   // +0x0000
    int  At_1254;            // +0x1254
};
GG_STATIC_ASSERT(offsetof(Scenario_00721140, At_1254) == 0x1254);

// GLOBAL: GAMEMD 0xA8EC74 — ThemeClass::ScoresPresent (byte).
extern bool ScoresPresent_00A8EC74;
// GLOBAL: GAMEMD 0xA8ED64 — byte gate; nonzero suppresses queueing.
extern bool DAT_00A8ED64;
// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern House_00721140* CurrentPlayer_00A83D4C;
// GLOBAL: GAMEMD 0xA8B238 — SessionClass::Instance.GameMode (Campaign == 0).
extern int GameMode_00A8B238;
// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern Scenario_00721140* ScenarioInstance_00A8B230;

// FUNCTION: GAMEMD 0x407000 (decl; reloc) — audio engine present.
int __cdecl FUN_00407000();
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

#endif  // GG_MATCH_AUDIO_THEME_CLASS_QUEUE_METHODS_H

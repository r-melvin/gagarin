// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check
//   Six CCINIClass readers that turn an INI name into an enumeration by
//   linear-searching a static name table, read numerically off the user's
//   retail gamemd.exe v1.001 with the local Ghidra CLI. They sit inside the
//   same contiguous 0x474810..0x475A3D run as the already-matched helpers in
//   ccini_class_small_readers_methods.cpp, from which ReadString's
//   convention and the "" literal at 0x889F64 are taken.
//
//   Every table identity below was confirmed by reading the table:
//   `ghidra memory read` gives 0x81B958 -> {"green",1}
//   (pips), 0x81B9B0 -> {"Ammo",1} (pip scales), 0x81B9D8 -> {"1x1",0}
//   (building foundations), 0x81BA88 -> "Normal" (movement zones) and
//   0x7E4C50 -> "None" (super-weapon actions). The table extents come from
//   the loop's own terminating compare, which retail strength-reduced into
//   an absolute end address: 0x81B9B0, 0x81B9D8, 0x81BA88, 0x81BABC and
//   0x7E4D74 respectively.
//
//   The first three tables are {name, value} pairs with a 8-byte stride and
//   return the paired value; the last two are bare name arrays with a
//   4-byte stride and return the index.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_NAME_TABLE_READERS_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_NAME_TABLE_READERS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x889F64  ""
extern const char STR_00889F64[];

// FUNCTION: GAMEMD 0x7C8D20 (decl; reloc) — the CRT case-insensitive string
// compare. Declared under its placeholder rather than as `stricmp` so cl
// cannot substitute an intrinsic for the out-of-line call retail makes.
extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);

// A {name, value} row. The stride is 8 and the value sits one dword past the
// name: retail's match arm loads `[EDI*8 + base + 4]`.
struct NameValuePair
{
    const char* Name;       // +0x0000
    int         Value;      // +0x0004
};
GG_STATIC_ASSERT(offsetof(NameValuePair, Name) == 0x00 &&
                 offsetof(NameValuePair, Value) == 0x04 &&
                 sizeof(NameValuePair) == 0x08);

// GLOBAL: GAMEMD 0x81B958 — the pip name table, 11 rows (ends at 0x81B9B0).
extern NameValuePair DAT_0081B958[11];
// GLOBAL: GAMEMD 0x81B9B0 — the pip-scale table, 5 rows (ends at 0x81B9D8).
extern NameValuePair DAT_0081B9B0[5];
// GLOBAL: GAMEMD 0x81B9D8 — the foundation table, 22 rows (ends at 0x81BA88).
extern NameValuePair DAT_0081B9D8[22];
// GLOBAL: GAMEMD 0x81BA88 — the movement-zone names, 13 (ends at 0x81BABC).
extern const char* DAT_0081BA88[13];
// GLOBAL: GAMEMD 0x7E4C50 — the super-weapon action names, 73 (ends 0x7E4D74).
extern const char* DAT_007E4C50[73];

// The colour-scheme record the 0x474A90 reader walks. Its name is a pointer
// at +0x304 (`MOV EDX,[EAX+0x304]`) and the dword at +0x310 disqualifies a
// scheme when it equals 1 (`CMP dword ptr [ECX+0x310],0x1`).
struct ColorScheme_00474A90
{
    char        _pad000[0x304];     // +0x0000
    const char* Name;               // +0x0304
    char        _pad308[0x8];       // +0x0308
    int         Flags;              // +0x0310
};
GG_STATIC_ASSERT(offsetof(ColorScheme_00474A90, Name) == 0x304 &&
                 offsetof(ColorScheme_00474A90, Flags) == 0x310);

// GLOBAL: GAMEMD 0xB054D4 — pointer to the colour-scheme pointer array.
extern ColorScheme_00474A90** DAT_00B054D4;
// GLOBAL: GAMEMD 0xB054E0 — how many schemes that array holds.
extern int DAT_00B054E0;

class CCINI_004748A0
{
public:
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — INIClass::ReadString.
    int ReadString(const char* section, const char* key, const char* defaultValue,
                   char* buffer, unsigned int size);

    // FUNCTION: GAMEMD 0x4748A0
    int ReadPip(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474940
    int ReadPipScale(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474A90
    int ReadColorScheme(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474DA0
    int ReadFoundation(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474E40
    int ReadMovementZone(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474EE0
    int ReadSuperWeaponAction(const char* section, const char* key, int defaultValue);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_NAME_TABLE_READERS_METHODS_H

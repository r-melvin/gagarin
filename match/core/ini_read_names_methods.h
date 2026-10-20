// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, string addresses and call targets read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x410B90. The two
//   string literals are read out of the image: 0x817854 is "Name" and 0x81784C
//   is "UIName".
//
// Read the two name keys out of the object's own INI section. The section name
// lives in the buffer at +0x24, so its address is what every call receives; the
// UIName read only happens when the byte at +0x3D is already set, and that same
// byte is where the value goes.
#ifndef GG_MATCH_CORE_INI_READ_NAMES_METHODS_H
#define GG_MATCH_CORE_INI_READ_NAMES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x817854 "Name"
extern const char STR_00817854[];
// STRING: GAMEMD 0x81784C "UIName"
extern const char STR_0081784C[];

struct CCINI_00410B90
{
    // FUNCTION: GAMEMD 0x5257C0 — select the section, two stack arguments.
    void FUN_005257C0(const char* section, int flags);
    // FUNCTION: GAMEMD 0x528660 — read one key into the destination.
    void FUN_00528660(const char* section, const char* key, void* destination);
};

struct Obj_00410B90
{
    char _pad000[0x24];
    char Section[0x3D - 0x24];   // +0x0024
    char UIName;                 // +0x003D
    char _pad03E[0x64 - 0x3E];
    char Name;                   // +0x0064

    // FUNCTION: GAMEMD 0x410B90
    bool FUN_00410B90(CCINI_00410B90* ini);
};
GG_STATIC_ASSERT(offsetof(Obj_00410B90, Section) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_00410B90, UIName) == 0x3D);
GG_STATIC_ASSERT(offsetof(Obj_00410B90, Name) == 0x64);

#endif  // GG_MATCH_CORE_INI_READ_NAMES_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Calling convention and argument order read off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x52A940: `this` arrives in
//   ECX and is parked in EDI, the three stack arguments are `[ESP+0x2C]`,
//   `[ESP+0x30]` and `[ESP+0x34]`, and the frame is one 32-byte buffer. The
//   method name is the YRpp one; no member offset is touched.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_TIME_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_TIME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CRT sprintf, __cdecl variadic; the caller pops the five arguments
// (`ADD ESP,0x14`). LIBRARY: GAMEMD 0x7C8EF4 (excluded from the match target).
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

struct CCINI_0052A940
{
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — INIClass::WriteString.
    bool WriteString(const char* section, const char* key, const char* value);

    // FUNCTION: GAMEMD 0x52A940 — CCINIClass::WriteTime.
    bool WriteTime(const char* section, const char* key, int value);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_TIME_METHODS_H

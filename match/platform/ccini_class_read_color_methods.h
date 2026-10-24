// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, strings and argument slots read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x474C70: the default colour is the
//   fourth stack argument (`MOV ESI,[ESP+0xA0]`, bytes `[ESI]`, `[ESI+1]`,
//   `[ESI+2]` pushed to the CRT sprintf at 0x7C8EF4 with the "%d,%d,%d"
//   literal at 0x8189B0), the out pointer is the first (`[ESP+0x98]`), and
//   the string reader is INIClass::ReadString 0x528A10 (section, key,
//   default text, 64-byte buffer, 64). On success the three ints parsed by
//   the CRT sscanf at 0x7CA530 are packed as a word + byte store into the out
//   struct; on failure the default is copied the same way. The method name
//   and the by-value/by-reference pair come from YRpp
//   (every slot reconfirmed above).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_READ_COLOR_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_READ_COLOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8EF4 -- CRT sprintf (excluded from the match target).
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);
// LIBRARY: GAMEMD 0x7CA530 -- CRT sscanf (excluded from the match target).
extern "C" int __cdecl sscanf(const char* buffer, const char* format, ...);

// ColorStruct -- packed RGB triple (no padding; size = 3).
#include "../_layout/color_struct.h"
GG_STATIC_ASSERT(offsetof(ColorStruct, G) == 0x01);
GG_STATIC_ASSERT(offsetof(ColorStruct, B) == 0x02);
GG_STATIC_ASSERT(sizeof(ColorStruct) == 3);

// No member of the INI object is touched here; only the calling convention
// and the forwarded reader matter, so the body stays opaque.
class CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) -- INIClass::ReadString.
    int ReadString(const char* pSection, const char* pKey, const char* pDefault,
                   char* pBuffer, int size);

    // FUNCTION: GAMEMD 0x474C70
    ColorStruct* ReadColor(ColorStruct* pOut, const char* pSection,
                           const char* pKey, const ColorStruct& defValue);
};

// STRING: GAMEMD 0x8189B0 -- "%d,%d,%d".

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_READ_COLOR_METHODS_H

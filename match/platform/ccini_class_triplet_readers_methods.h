// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check
//   The pair of CCINIClass readers that parse a three-element
//   comma-separated value, read numerically off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI.
//
//   Both return their triple by value through a hidden buffer, not through
//   an output parameter: `RET 0x10` with only three source-level arguments,
//   the first stack dword reloaded at the end and handed back in EAX
//   (0x4764C0 `MOV EAX,ECX`). `this` reaches ReadString in ECX untouched,
//   so both are __thiscall members.
//
//   Frame evidence: the default triple is copied into a 12-byte local at
//   ESP+0x00..0x0B and the parse buffer is the 0x200 bytes above it, which
//   is exactly the 0x20C the prologue reserves.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_TRIPLET_READERS_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_TRIPLET_READERS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x889F64  ""
extern const char STR_00889F64[];
// STRING: GAMEMD 0x817F70  ","
extern const char STR_00817F70[];

// FUNCTION: GAMEMD 0x7C9CC2 (decl; reloc) — the CRT token splitter.
extern "C" char* __cdecl FUN_007C9CC2(char* text, const char* delimiters);
// FUNCTION: GAMEMD 0x7C9BFD (decl; reloc) — the CRT text-to-int.
extern "C" int __cdecl FUN_007C9BFD(const char* text);
// FUNCTION: GAMEMD 0x7C9D66 (decl; reloc) — the CRT text-to-double; the
// result arrives on the x87 stack and is stored straight out as a float.
extern "C" double __cdecl FUN_007C9D66(const char* text);

struct FloatTriple
{
    float X;    // +0x0000
    float Y;    // +0x0004
    float Z;    // +0x0008
};
GG_STATIC_ASSERT(offsetof(FloatTriple, Y) == 0x04 &&
                 offsetof(FloatTriple, Z) == 0x08 &&
                 sizeof(FloatTriple) == 0x0C);

struct IntTriple
{
    int X;      // +0x0000
    int Y;      // +0x0004
    int Z;      // +0x0008
};
GG_STATIC_ASSERT(offsetof(IntTriple, Y) == 0x04 &&
                 offsetof(IntTriple, Z) == 0x08 &&
                 sizeof(IntTriple) == 0x0C);

class CCINI_00476340
{
public:
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — INIClass::ReadString.
    int ReadString(const char* section, const char* key, const char* defaultValue,
                   char* buffer, unsigned int size);

    // FUNCTION: GAMEMD 0x476340
    FloatTriple ReadFloatTriple(const char* section, const char* key,
                                const FloatTriple& defaultValue);
    // FUNCTION: GAMEMD 0x476420
    IntTriple   ReadIntTriple(const char* section, const char* key,
                              const IntTriple& defaultValue);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_TRIPLET_READERS_METHODS_H

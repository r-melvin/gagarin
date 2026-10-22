// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x474B50: the default's three bytes `MOV AL,[ESI+2]`,
//   `MOV DL,[ESI]`, `MOV CL,[ESI+1]` zero-extended into the five-argument
//   CRT sprintf (0x7C8EF4, "%d,%d,%d" at 0x8189B0); the string reader
//   0x528A10 `__thiscall(section, key, default, buffer, 0x40)` tested with
//   `TEST EAX,EAX`; the five-argument CRT sscanf (0x7CA530) into three int
//   slots at [ESP+0x8/0x10/0xC]; the three-byte result written as a word
//   plus a byte through the hidden return pointer ([ESP+0x98], `RET 0x10`),
//   and the default copied the same way (`MOV DX,[ESI]; MOV DL,[ESI+2]`)
//   on the miss path. Method name from YRpp (consult-only;
//   name only).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_READ3BYTES_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_READ3BYTES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CRT sprintf / sscanf, __cdecl variadic; the caller pops the arguments.
// FUNCTION: GAMEMD 0x7C8EF4 (decl; reloc)
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);
// FUNCTION: GAMEMD 0x7CA530 (decl; reloc)
extern "C" int __cdecl sscanf(const char* buffer, const char* format, ...);

// ColorStruct — packed RGB triple (size 3). The user-declared constructors
// are what make VC6 hand it back through a hidden pointer.
struct ColorStruct
{
    unsigned char R;   // +0x00
    unsigned char G;   // +0x01
    unsigned char B;   // +0x02

    ColorStruct() {}
    ColorStruct(unsigned char r, unsigned char g, unsigned char b)
        : R(r), G(g), B(b) {}
};
GG_STATIC_ASSERT(offsetof(ColorStruct, G) == 0x01);
GG_STATIC_ASSERT(offsetof(ColorStruct, B) == 0x02);
GG_STATIC_ASSERT(sizeof(ColorStruct) == 3);

// Opaque INI parser; only the out-of-line string reader is called.
class CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) -- INIClass::ReadString.
    int ReadString(const char* section, const char* key, const char* def,
                   char* buffer, int size);

    // FUNCTION: GAMEMD 0x474B50
    ColorStruct Read3Bytes(const char* section, const char* key,
                           const ColorStruct& def);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_READ3BYTES_METHODS_H

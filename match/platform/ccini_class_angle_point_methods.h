// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Five more CCINIClass accessors the Ghidra function list does not know
//   about, found by sweeping the 0x47465A..0x474810 address gap as raw
//   bytes behind its 0x90 pads. The private-reference seed names none of them.
//   They sit immediately below the already-matched fixed-point reader at
//   0x474620 and share its INI plumbing.
//
//   Constants read out of the binary rather than assumed: the double at
//   0x7E1740 is 0.00390625 (one 256th), and 0x81C000 is "%d,%d" — the
//   eight bytes immediately below the "<random>" literal at 0x81C008.
//   The 0x474690 / 0x4746E0 pair are inverses of each other over a 360
//   degree scale: one multiplies by 360 and divides by 256 with a LEA
//   chain, the other multiplies by 256 and divides by 360 through the
//   0xB60B60B7 magic.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_ANGLE_POINT_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_ANGLE_POINT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x889F64  ""
extern const char STR_00889F64[];
// STRING: GAMEMD 0x817F6C  "%d"
extern const char STR_00817F6C[];
// STRING: GAMEMD 0x81C000  "%d,%d"
extern const char STR_0081C000[];

// FUNCTION: GAMEMD 0x7C8EF4 (decl; reloc) — the CRT formatter.
extern "C" int __cdecl FUN_007C8EF4(char* buffer, const char* format, ...);
// FUNCTION: GAMEMD 0x7CA530 (decl; reloc) — the CRT scanner.
extern "C" int __cdecl FUN_007CA530(const char* text, const char* format, ...);
// FUNCTION: GAMEMD 0x7C9BFD (decl; reloc) — the CRT text-to-int.
extern "C" int __cdecl FUN_007C9BFD(const char* text);

// A packed pair of 16-bit coordinates, four bytes wide: the 0x474740
// reader assembles its result out of two word stores and hands the whole
// dword back through a hidden buffer.
struct Point16
{
    short X;    // +0x0000
    short Y;    // +0x0002
};
GG_STATIC_ASSERT(offsetof(Point16, Y) == 0x02 && sizeof(Point16) == 0x04);

class CCINI_00474660
{
public:
    // FUNCTION: GAMEMD 0x5285B0 (decl; reloc) — INIClass::WriteDouble.
    bool    WriteDouble(const char* section, const char* key, double value);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — INIClass::ReadString.
    int     ReadString(const char* section, const char* key, const char* defaultValue,
                       char* buffer, unsigned int size);
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — INIClass::WriteString.
    bool    WriteString(const char* section, const char* key, const char* value);

    // FUNCTION: GAMEMD 0x474660
    bool    WriteFixedFraction(const char* section, const char* key, int value);
    // FUNCTION: GAMEMD 0x474690
    bool    WriteAngleDegrees(const char* section, const char* key, int facing);
    // FUNCTION: GAMEMD 0x4746E0
    int     ReadAngleDegrees(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474740
    Point16 ReadPoint(const char* section, const char* key, const Point16* defaultValue);
    // FUNCTION: GAMEMD 0x4747C0
    bool    WritePoint(const char* section, const char* key, const Point16* value);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_ANGLE_POINT_METHODS_H

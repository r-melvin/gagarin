// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x474660, 0x474690,
//   0x4746E0, 0x474740 and 0x4747C0.

#include "ccini_class_angle_point_methods.h"

// FUNCTION: GAMEMD 0x474660
//
// Write an eight-bit fixed-point fraction back out as the real number it
// stands for: the writer paired with the already-matched 0x474620 reader,
// which reads a double and scales it by 256.
bool CCINI_00474660::WriteFixedFraction(const char* section, const char* key,
                                        int value)
{
    return WriteDouble(section, key, value * 0.00390625);
}

// FUNCTION: GAMEMD 0x474690
//
// Write a byte facing out as degrees. The multiply by 360 is a LEA chain
// and the divide by 256 an arithmetic shift with the usual sign bias.
bool CCINI_00474660::WriteAngleDegrees(const char* section, const char* key,
                                       int facing)
{
    char buffer[32];

    FUN_007C8EF4(buffer, STR_00817F6C, facing * 360 / 256);

    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x4746E0
//
// The inverse: read degrees and scale them back into the byte facing.
int CCINI_00474660::ReadAngleDegrees(const char* section, const char* key,
                                     int defaultValue)
{
    char buffer[32];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        return FUN_007C9BFD(buffer) * 256 / 360;
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x474740
//
// Read a comma-separated coordinate pair. The two scanned integers land in
// the incoming argument slots, which are dead once the string has been
// read — the frame reserves nothing but the buffer.
Point16 CCINI_00474660::ReadPoint(const char* section, const char* key,
                                  const Point16* defaultValue)
{
    char buffer[64];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        int x;
        int y;

        FUN_007CA530(buffer, STR_0081C000, &x, &y);

        Point16 value;

        value.X = (short)x;
        value.Y = (short)y;

        return value;
    }

    return *defaultValue;
}

// FUNCTION: GAMEMD 0x4747C0
//
// The matching writer. Both coordinates are sign-extended from their words
// on the way into the formatter, which is the varargs promotion of a
// signed short.
bool CCINI_00474660::WritePoint(const char* section, const char* key,
                                const Point16* value)
{
    char buffer[64];

    FUN_007C8EF4(buffer, STR_0081C000, value->X, value->Y);

    return WriteString(section, key, buffer);
}

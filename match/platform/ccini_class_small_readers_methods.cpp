// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x474620, 0x4749E0,
//   0x474A20, 0x474B20, 0x474F50, 0x474FA0, 0x474FF0, 0x475030, 0x475060
//   and 0x4750A0.

#include "ccini_class_small_readers_methods.h"

// FUNCTION: GAMEMD 0x474620
//
// Read a fixed-point fraction. The value is read as a double with -1.0 as
// the sentinel default; the sentinel gives the caller's own default back
// untouched, anything else is scaled by 256 and truncated, so the result is
// an 8-bit fixed-point fraction.
int CCINI_00474620::FUN_00474620(const char* section, const char* key, int defaultValue)
{
    double value = ReadDouble(section, key, -1.0);

    if (value == -1.0) {
        return defaultValue;
    }

    return (int)(value * 256.0);
}

// FUNCTION: GAMEMD 0x4749E0
//
// Read an enumerated value through its name: the caller's default is turned
// back into its name by the 0x473960 table, that name is the default handed
// to ReadString, and whatever comes back is parsed by 0x473980.
int CCINI_00474620::FUN_004749E0(const char* section, const char* key,
                                 unsigned int defaultValue)
{
    char buffer[32];

    ReadString(section, key, FUN_00473960(defaultValue), buffer, sizeof(buffer));

    return FUN_00473980(buffer);
}

// FUNCTION: GAMEMD 0x474A20
//
// Write the same enumerated value back out by name. A zero value is not
// written at all.
bool CCINI_00474620::FUN_00474A20(const char* section, const char* key,
                                  unsigned int value)
{
    if (value != 0) {
        return WriteString(section, key, FUN_00473960(value));
    }

    return false;
}

// FUNCTION: GAMEMD 0x474B20
//
// Write an index into the 0xB054D4 table out as that entry's name.
bool CCINI_00474620::FUN_00474B20(const char* section, const char* key, int index)
{
    return WriteString(section, key, DAT_00B054D4[index]->Name);
}

// FUNCTION: GAMEMD 0x474F50
//
// Read an index into the 0xA8E334 table. The caller's default index is
// spelled as that entry's inline ID text; -1 means "no default", which is
// an empty string. The answer is parsed back to an index by 0x6CEE60.
int CCINI_00474620::FUN_00474F50(const char* section, const char* key, int index)
{
    char        empty[28];
    char        buffer[32];
    const char* defaultName;

    if (index != -1) {
        defaultName = DAT_00A8E334[index]->ID;
    } else {
        empty[0] = '\0';
        defaultName = empty;
    }

    ReadString(section, key, defaultName, buffer, sizeof(buffer));

    return FUN_006CEE60(buffer);
}

// FUNCTION: GAMEMD 0x474FA0
//
// Read a name with no default at all: an empty answer leaves the caller's
// value alone, and anything else is parsed by 0x753250.
int CCINI_00474620::FUN_00474FA0(const char* section, const char* key,
                                 int defaultValue)
{
    char buffer[100];

    ReadString(section, key, STR_00889F64, buffer, sizeof(buffer));

    if (strlen(buffer) != 0) {
        return FUN_00753250(buffer);
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x474FF0
//
// The 0x4749E0 reader over the second enum table (0x40DCB0 / 0x40DCE0).
int CCINI_00474620::FUN_00474FF0(const char* section, const char* key,
                                 int defaultValue)
{
    char buffer[32];

    ReadString(section, key, (const char*)FUN_0040DCB0(defaultValue), buffer,
               sizeof(buffer));

    return FUN_0040DCE0(buffer);
}

// FUNCTION: GAMEMD 0x475030
//
// The matching writer for the second enum table.
bool CCINI_00474620::FUN_00475030(const char* section, const char* key, int value)
{
    return WriteString(section, key, (const char*)FUN_0040DCB0(value));
}

// FUNCTION: GAMEMD 0x475060
//
// The 0x4749E0 reader over the third enum table (0x45DD20 / 0x45DD50).
int CCINI_00474620::FUN_00475060(const char* section, const char* key,
                                 int defaultValue)
{
    char buffer[32];

    ReadString(section, key, (const char*)FUN_0045DD20(defaultValue), buffer,
               sizeof(buffer));

    return FUN_0045DD50(buffer);
}

// FUNCTION: GAMEMD 0x4750A0
//
// The matching writer for the third enum table.
bool CCINI_00474620::FUN_004750A0(const char* section, const char* key, int value)
{
    return WriteString(section, key, (const char*)FUN_0045DD20(value));
}

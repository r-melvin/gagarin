// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4748A0, 0x474940,
//   0x474A90, 0x474DA0, 0x474E40 and 0x474EE0.

#include "ccini_class_name_table_readers_methods.h"

// FUNCTION: GAMEMD 0x4748A0
//
// Read a pip by name. The caller's default index is spelled as that row's
// own name and handed to ReadString as the default, so an absent key round
// trips through the table rather than being special-cased; an unrecognised
// name falls back on 1 rather than on the caller's value.
int CCINI_004748A0::ReadPip(const char* section, const char* key, int defaultValue)
{
    char buffer[32];

    ReadString(section, key, DAT_0081B958[defaultValue].Name, buffer,
               sizeof(buffer));

    for (int i = 0; i < 11; ++i) {
        if (FUN_007C8D20(buffer, DAT_0081B958[i].Name) == 0) {
            return DAT_0081B958[i].Value;
        }
    }

    return 1;
}

// FUNCTION: GAMEMD 0x474940
//
// Read a pip scale. Unlike the pip reader this one has no default name at
// all: an empty or missing key gives the caller's value back untouched, and
// an unrecognised name gives 0.
int CCINI_004748A0::ReadPipScale(const char* section, const char* key,
                                 int defaultValue)
{
    char buffer[32];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer)) > 0) {
        for (int i = 0; i < 5; ++i) {
            if (FUN_007C8D20(buffer, DAT_0081B9B0[i].Name) == 0) {
                return DAT_0081B9B0[i].Value;
            }
        }

        return 0;
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x474A90
//
// Read a colour scheme by name. The table is a live array rather than a
// static one, so both the count and the base are re-read on every turn of
// the loop, and a scheme whose flag word is 1 is skipped even when its name
// matches. An unrecognised name gives the caller's index back.
int CCINI_004748A0::ReadColorScheme(const char* section, const char* key,
                                    int defaultValue)
{
    char buffer[32];

    ReadString(section, key, DAT_00B054D4[defaultValue]->Name, buffer,
               sizeof(buffer));

    for (int i = 0; i < DAT_00B054E0; ++i) {
        if (FUN_007C8D20(DAT_00B054D4[i]->Name, buffer) == 0 &&
            DAT_00B054D4[i]->Flags != 1) {
            return i;
        }
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x474DA0
//
// The pip reader's shape over the building-foundation table, failing to 0.
int CCINI_004748A0::ReadFoundation(const char* section, const char* key,
                                   int defaultValue)
{
    char buffer[32];

    ReadString(section, key, DAT_0081B9D8[defaultValue].Name, buffer,
               sizeof(buffer));

    for (int i = 0; i < 22; ++i) {
        if (FUN_007C8D20(buffer, DAT_0081B9D8[i].Name) == 0) {
            return DAT_0081B9D8[i].Value;
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x474E40
//
// A bare name array rather than a pair table, so the answer is the index
// itself; an unrecognised name gives -1.
int CCINI_004748A0::ReadMovementZone(const char* section, const char* key,
                                     int defaultValue)
{
    char buffer[32];

    ReadString(section, key, DAT_0081BA88[defaultValue], buffer, sizeof(buffer));

    for (int i = 0; i < 13; ++i) {
        if (FUN_007C8D20(buffer, DAT_0081BA88[i]) == 0) {
            return i;
        }
    }

    return -1;
}

// FUNCTION: GAMEMD 0x474EE0
//
// The movement-zone reader's shape over the 73 super-weapon action names,
// failing to 0 rather than to -1.
int CCINI_004748A0::ReadSuperWeaponAction(const char* section, const char* key,
                                          int defaultValue)
{
    char buffer[32];

    ReadString(section, key, DAT_007E4C50[defaultValue], buffer, sizeof(buffer));

    for (int i = 0; i < 73; ++i) {
        if (FUN_007C8D20(buffer, DAT_007E4C50[i]) == 0) {
            return i;
        }
    }

    return 0;
}

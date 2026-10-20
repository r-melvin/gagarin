// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x474910, 0x4749B0,
//   0x474A50, 0x474A70, 0x474C20, 0x474D50, 0x474E10, 0x474EB0, 0x475150,
//   0x475440 and 0x4757A0.

#include "ccini_class_enum_writers_methods.h"

// FUNCTION: GAMEMD 0x474910
//
// Write a pip index out as its name. The zero index means "no pip" and is
// not written at all, which is the same convention the already-matched
// 0x474A20 writer uses.
bool CCINI_00474910::WritePip(const char* section, const char* key, int index)
{
    if (index != 0) {
        return WriteString(section, key, DAT_0081B958[index].Name);
    }

    return false;
}

// FUNCTION: GAMEMD 0x4749B0
//
// The same writer over the pip-scale table.
bool CCINI_00474910::WritePipScale(const char* section, const char* key, int index)
{
    if (index != 0) {
        return WriteString(section, key, DAT_0081B9B0[index].Name);
    }

    return false;
}

// FUNCTION: GAMEMD 0x474A50
//
// Read a scalar and hand it back wrapped in its one-dword value class,
// which is why a three-argument reader returns through a hidden buffer and
// cleans sixteen bytes rather than twelve.
IniValue CCINI_00474910::FUN_00474A50(const char* section, const char* key,
                                      int defaultValue)
{
    IniValue value;

    value.Value = ReadScalar(section, key, defaultValue);

    return value;
}

// FUNCTION: GAMEMD 0x474A70
//
// Its matching writer: a plain forwarder with the receiver passed straight
// through in ECX.
bool CCINI_00474910::FUN_00474A70(const char* section, const char* key, int value)
{
    return WriteScalar(section, key, value);
}

// FUNCTION: GAMEMD 0x474C20
//
// Write a three-byte colour out as a decimal triple. Each component is
// widened from a byte with an explicit zero before the push, which is the
// varargs promotion of the unsigned byte rather than an explicit mask.
bool CCINI_00474910::FUN_00474C20(const char* section, const char* key,
                                  const unsigned char* rgb)
{
    char buffer[64];

    FUN_007C8EF4(buffer, STR_008189B0, rgb[0], rgb[1], rgb[2]);

    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x474D50
//
// A second, byte-identical copy of the same writer. Retail really does
// contain both, 0x130 bytes apart, so the translation unit spells the body
// out twice rather than sharing one.
bool CCINI_00474910::FUN_00474D50(const char* section, const char* key,
                                  const unsigned char* rgb)
{
    char buffer[64];

    FUN_007C8EF4(buffer, STR_008189B0, rgb[0], rgb[1], rgb[2]);

    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x474E10
//
// Write a foundation index out as its name; -1 means "none" and writes
// nothing. Note the sentinel differs from the pip writers' zero.
bool CCINI_00474910::WriteFoundation(const char* section, const char* key, int index)
{
    if (index != -1) {
        return WriteString(section, key, DAT_0081B9D8[index].Name);
    }

    return false;
}

// FUNCTION: GAMEMD 0x474EB0
//
// The same over the movement-zone names, which are a bare pointer array
// rather than a pair table.
bool CCINI_00474910::WriteMovementZone(const char* section, const char* key,
                                       int index)
{
    if (index != -1) {
        return WriteString(section, key, DAT_0081BA88[index]);
    }

    return false;
}

// FUNCTION: GAMEMD 0x475150
//
// Write a house-type bit mask out as a comma-separated list of IDs: the
// house-type twin of the house writer at 0x4752E0, over a registry whose
// bit index lives at +0xB8 and whose ID text is inline at +0x24.
bool CCINI_00474910::WriteHouseTypesList(const char* section, const char* key,
                                         unsigned int bits)
{
    char buffer[128];

    buffer[0] = '\0';

    if (bits != 0) {
        int count = DAT_00A83C98.Count;

        if (count > 0) {
            for (int i = 0; i < count; ++i) {
                HouseTypeRecord* type = DAT_00A83C98.Items[i];

                if (bits & (1 << type->Index)) {
                    if (buffer[0] != '\0') {
                        strcat(buffer, STR_00817F70);
                    }

                    strcat(buffer, type->ID);
                }
            }

            if (buffer[0] != '\0') {
                return WriteString(section, key, buffer);
            }
        }
    }

    return true;
}

// FUNCTION: GAMEMD 0x475440
//
// Write an armour index out as its name, with no sentinel at all.
bool CCINI_00474910::WriteArmorName(const char* section, const char* key, int index)
{
    return WriteString(section, key, DAT_007E5210[index]);
}

// FUNCTION: GAMEMD 0x4757A0
//
// Write a movie index out as that movie's ID, spelling -1 as "<none>". The
// default is materialised before the test, so the constant is loaded into
// the same register the lookup overwrites.
bool CCINI_00474910::WriteMovie(const char* section, const char* key, int index)
{
    const char* name = STR_00817474;

    if (index != -1) {
        name = DAT_008B4124[index]->ID;
    }

    return WriteString(section, key, name);
}

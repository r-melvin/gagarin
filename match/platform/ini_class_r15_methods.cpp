// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x528170 and 0x5295A0 in the user's retail gamemd.exe v1.001;
//   the literals are at 0x825BD0 ("%X"), 0x825BF8 ("yes") and 0x825BF4 ("no").
//
// INIClass writers. Address index: 0x528170 0x5295A0 0x529820 0x529C40 0x52A0A0 0x527640 0x527C60 0x528600 0x5281C0.
#include <stdio.h>
#include "../core/string_class.h"
#include "../_layout/ini_class.h"

// FUNCTION: GAMEMD 0x528170
// Writes `value` as upper-case hexadecimal text.
bool INIClass::FUN_00528170(const char* section, const char* key, int value)
{
    char buffer[0x200];
    sprintf(buffer, "%X", value);
    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x5295A0
// WriteBool for names held in Wstring objects; the key's text is fetched first.
bool INIClass::WriteBool(const Wstring& section, const Wstring& key, bool value)
{
    const char* keyText = key.FUN_007B5440();
    const char* sectionText = section.FUN_007B5440();
    if (value) {
        return WriteString(sectionText, keyText, "yes");
    }
    return WriteString(sectionText, keyText, "no");
}

// FUNCTION: GAMEMD 0x529820
// Writes "%d,%d" of the first two values.
bool INIClass::Write2Integers(const Wstring& section, const Wstring& key, const int* values)
{
    char buffer[56];
    const char* keyText = key.FUN_007B5440();
    const char* sectionText = section.FUN_007B5440();
    sprintf(buffer, "%d,%d", values[0], values[1]);
    return WriteString(sectionText, keyText, buffer);
}

// FUNCTION: GAMEMD 0x529C40
// Writes "%d,%d,%d" of the three values.
bool INIClass::WriteIntTriple(const Wstring& section, const Wstring& key, const int* values)
{
    char buffer[56];
    const char* keyText = key.FUN_007B5440();
    const char* sectionText = section.FUN_007B5440();
    sprintf(buffer, "%d,%d,%d", values[0], values[1], values[2]);
    return WriteString(sectionText, keyText, buffer);
}

// FUNCTION: GAMEMD 0x52A0A0
// Writes "%f,%f,%f" of the three floats.
bool INIClass::WriteFloatTriple(const Wstring& section, const Wstring& key, const float* values)
{
    char buffer[56];
    const char* keyText = key.FUN_007B5440();
    const char* sectionText = section.FUN_007B5440();
    sprintf(buffer, "%f,%f,%f", values[0], values[1], values[2]);
    return WriteString(sectionText, keyText, buffer);
}

// FUNCTION: GAMEMD 0x527640
// WriteInteger with Wstring names: format 1 "%Xh", 2 "$%X", otherwise "%d".
bool INIClass::WriteInteger(const Wstring& section, const Wstring& key, int value, int format)
{
    char buffer[0x200];
    const char* keyText = key.FUN_007B5440();
    const char* sectionText = section.FUN_007B5440();
    switch (format) {
    case 1:
        sprintf(buffer, "%Xh", value);
        break;
    case 2:
        sprintf(buffer, "$%X", value);
        break;
    default:
        sprintf(buffer, "%d", value);
        break;
    }
    return WriteString(sectionText, keyText, buffer);
}

// FUNCTION: GAMEMD 0x527C60
// Writes "%d,%d,%d,%d" of the four values.
bool INIClass::WriteIntQuad(const Wstring& section, const Wstring& key, const int* values)
{
    char buffer[0x40];
    const char* keyText = key.FUN_007B5440();
    const char* sectionText = section.FUN_007B5440();
    sprintf(buffer, "%d,%d,%d,%d", values[0], values[1], values[2], values[3]);
    return WriteString(sectionText, keyText, buffer);
}

// FUNCTION: GAMEMD 0x528600
// Writes a double with "%f".
// PARTIAL: 93.3% -- retail computes the buffer address (LEA) before the FSTP of the double argument; the
// two instructions come out swapped here.
bool INIClass::WriteDouble(const Wstring& section, const Wstring& key, double value)
{
    char buffer[0x200];
    const char* keyText = key.FUN_007B5440();
    const char* sectionText = section.FUN_007B5440();
    double v = value;
    sprintf(buffer, "%f", v);
    return WriteString(sectionText, keyText, buffer);
}

// FUNCTION: GAMEMD 0x5281C0
// Writes `value` as upper-case hexadecimal text, names held in Wstring objects.
bool INIClass::FUN_005281C0(const Wstring& section, const Wstring& key, int value)
{
    char buffer[0x200];
    const char* keyText = key.FUN_007B5440();
    const char* sectionText = section.FUN_007B5440();
    sprintf(buffer, "%X", value);
    return WriteString(sectionText, keyText, buffer);
}

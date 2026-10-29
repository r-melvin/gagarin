// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below; the
//   class and the evidence for its single member are in string_class.h.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// Further Wstring bodies, ascending by retail address.
#include <string.h>
#include <ctype.h>
#include "string_class.h"
// GLOBAL: GAMEMD 0x889F64
extern char GLOBAL_00889F64[];

// Length of a possibly unset string (the inline form of Wstring::Length).
static inline unsigned int LengthOf(const char* text)
{
    if (text == 0) {
        return 0;
    }
    return strlen(text);
}

// FUNCTION: GAMEMD 0x7B4A10
// Appends the whole text, reallocating the buffer; null text changes nothing.
bool Wstring::FUN_007B4A10(const char* text)
{
    if (!text) {
        return true;
    }
    char* old = unknown_00;
    unsigned int total = strlen(text) + 1;
    if (old) {
        total += strlen(old);
    }
    unknown_00 = new char[total];
    if (old) {
        strcpy(unknown_00, old);
    } else {
        unknown_00[0] = 0;
    }
    strcat(unknown_00, text);
    if (old) {
        delete old;
    }
    return true;
}

// FUNCTION: GAMEMD 0x7B4AC0
// Appends up to `count` characters of the text, reallocating the buffer.
bool Wstring::FUN_007B4AC0(int count, const char* text)
{
    char* old = unknown_00;
    unsigned int total = count + 1;
    if (old) {
        total += strlen(old);
    }
    unknown_00 = new char[total];
    if (old) {
        strcpy(unknown_00, old);
    } else {
        unknown_00[0] = 0;
    }
    if (text) {
        strncat(unknown_00, text, count);
    }
    if (old) {
        delete old;
    }
    return true;
}

// FUNCTION: GAMEMD 0x7B4C20
// Same append, returning this.
Wstring& Wstring::operator+=(const char* text)
{
    if (text) {
        char* old = unknown_00;
        unsigned int total = strlen(text) + 1;
        if (old) {
            total += strlen(old);
        }
        unknown_00 = new char[total];
        if (old) {
            strcpy(unknown_00, old);
        } else {
            unknown_00[0] = 0;
        }
        strcat(unknown_00, text);
        if (old) {
            delete old;
        }
    }
    return *this;
}

// FUNCTION: GAMEMD 0x7B4CD0
// Appends another string (unset counts as empty); returns this.
Wstring& Wstring::operator+=(const Wstring& other)
{
    const char* text;
    if (other.unknown_00 == 0) {
        text = GLOBAL_00889F64;
    } else {
        text = other.unknown_00;
    }
    return *this += text;
}

// FUNCTION: GAMEMD 0x7B5AE0
// Replaces the buffer with a copy of up to `length` characters of the source.
bool Wstring::FUN_007B5AE0(int length, const char* source)
{
    if (unknown_00) {
        delete unknown_00;
    }
    unknown_00 = 0;
    unknown_00 = new char[length + 1];
    unknown_00[0] = 0;
    if (source) {
        strncpy(unknown_00, source, length);
    }
    unknown_00[length] = 0;
    return true;
}

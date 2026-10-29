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

// FUNCTION: GAMEMD 0x7B4B50
// Appends another string, taken by pointer; an unset source appends the fallback text.
bool Wstring::FUN_007B4B50(const Wstring* other)
{
    const char* text;
    if (other->unknown_00 == 0) {
        text = GLOBAL_00889F64;
    } else {
        text = other->unknown_00;
    }
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

// FUNCTION: GAMEMD 0x7B5020
// Removes `count` characters starting at `start` (clamped to the string);
// reports false when nothing is left to remove.
bool Wstring::FUN_007B5020(int start, int count)
{
    int len = strlen(unknown_00);
    if (count + start > len) {
        start = len - count;
    }
    if (start < 0) {
        count += start;
        start = 0;
    }
    if (count <= 0) {
        return false;
    }
    char* result = new char[len - count + 1];
    unknown_00[start] = 0;
    unknown_00[start + count - 1] = 0;
    strcpy(result, unknown_00);
    strcat(result, unknown_00 + start + count);
    delete unknown_00;
    unknown_00 = result;
    return true;
}

// FUNCTION: GAMEMD 0x7B5A40
// Replaces the buffer with a copy of the text; always reports success.
bool Wstring::FUN_007B5A40(const char* text)
{
    if (unknown_00) {
        delete unknown_00;
    }
    unknown_00 = 0;
    unknown_00 = new char[text ? strlen(text) + 1 : 1];
    unknown_00[0] = 0;
    if (text) {
        strcpy(unknown_00, text);
    }
    return true;
}

// FUNCTION: GAMEMD 0x7B5230
// Removes the trailing run of characters that all appear in `trim`.
void Wstring::FUN_007B5230(const Wstring* trim)
{
    unsigned int i = LengthOf(unknown_00);
    while (i-- != 0) {
        const char* set = trim->unknown_00;
        if (set == 0) {
            set = GLOBAL_00889F64;
        }
        if (strchr(set, unknown_00[i]) == 0) {
            break;
        }
    }
    int count = i + 1;
    const char* source = GLOBAL_00889F64;
    if (unknown_00 != 0) {
        source = unknown_00;
    }
    char* head = new char[count + 1];
    head[0] = 0;
    if (source) {
        strncpy(head, source, count);
    }
    head[count] = 0;
    const char* text = GLOBAL_00889F64;
    if (head != 0) {
        text = head;
    }
    if (unknown_00) {
        delete unknown_00;
    }
    unknown_00 = 0;
    unknown_00 = new char[text ? strlen(text) + 1 : 1];
    unknown_00[0] = 0;
    if (text) {
        strcpy(unknown_00, text);
    }
    if (head != 0) {
        delete head;
    }
}

// FUNCTION: GAMEMD 0x7B5E30
// Cuts the string at the first occurrence of `ch`; false when absent.
bool Wstring::FUN_007B5E30(char ch)
{
    if (unknown_00 == 0) {
        return false;
    }
    char* found = strchr(unknown_00, ch);
    if (found == 0) {
        return false;
    }
    unsigned int count = found - unknown_00;
    const char* source = GLOBAL_00889F64;
    if (unknown_00 != 0) {
        source = unknown_00;
    }
    char* head = new char[count + 1];
    head[0] = 0;
    if (source) {
        strncpy(head, source, count);
    }
    head[count] = 0;
    const char* text = GLOBAL_00889F64;
    if (head != 0) {
        text = head;
    }
    if (unknown_00) {
        delete unknown_00;
    }
    unknown_00 = 0;
    unknown_00 = new char[text ? strlen(text) + 1 : 1];
    unknown_00[0] = 0;
    if (text) {
        strcpy(unknown_00, text);
    }
    if (head != 0) {
        delete head;
    }
    return true;
}

// FUNCTION: GAMEMD 0x7B54D0
// Inserts `text` at `pos` (clamped to the current length); an unset string
// simply takes a copy of the text.
bool Wstring::FUN_007B54D0(const char* text, unsigned int pos)
{
    if (unknown_00 == 0) {
        unknown_00 = 0;
        unknown_00 = new char[text ? strlen(text) + 1 : 1];
        unknown_00[0] = 0;
        if (text) {
            strcpy(unknown_00, text);
        }
        return true;
    }
    if (pos > strlen(unknown_00)) {
        pos = strlen(unknown_00);
    }
    char* grown = new char[strlen(unknown_00) + 1 + strlen(text)];
    memset(grown, 0, strlen(unknown_00) + 1 + strlen(text));
    strcpy(grown, unknown_00);
    memmove(grown + pos + strlen(text), grown + pos, strlen(unknown_00) + 1 - pos);
    memmove(grown + pos, text, strlen(text));
    delete unknown_00;
    unknown_00 = grown;
    return true;
}

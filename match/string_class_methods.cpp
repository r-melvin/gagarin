// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native7B5B30 expands Length; /Ob2 preserves all existing complete sections.
// Canonical Wstring bodies, ascending by retail address. The class and the
// evidence for its single member are in string_class.h.
#include <string.h>
#include "string_class.h"
// GLOBAL: GAMEMD 0x889F64
extern char GLOBAL_00889F64[];

// LIBRARY: GAMEMD 0x007CAFF4
// _tolower
// Narrow CRT declaration; implementation remains in the toolchain library.
extern "C" int __cdecl tolower(int ch);

// LIBRARY: GAMEMD 0x007C97D3
// _toupper
extern "C" int __cdecl toupper(int ch);

// Length of a possibly unset string (the inline form of Wstring::Length).
static inline unsigned int LengthOf(const char* text)
{
    if (text == 0) {
        return 0;
    }
    return strlen(text);
}


// FUNCTION: GAMEMD 0x7B4620
Wstring::Wstring() : unknown_00(0)
{
}

// FUNCTION: GAMEMD 0x7B4630
Wstring::Wstring(const char* text)
{
    unknown_00 = 0;
    unknown_00 = new char[text ? strlen(text) + 1 : 1];
    unknown_00[0] = 0;
    if (text) {
        strcpy(unknown_00, text);
    }
}

// FUNCTION: GAMEMD 0x7B4690
Wstring::Wstring(const Wstring& other)
{
    unknown_00 = 0;
    if (other.unknown_00 != 0) {
        unknown_00 = new char[strlen(other.unknown_00) + 1];
        strcpy(unknown_00, other.unknown_00);
    }
}

// FUNCTION: GAMEMD 0x7B46F0
Wstring::~Wstring()
{
    if (unknown_00 != 0) {
        delete[] unknown_00;
    }
    unknown_00 = 0;
}

// FUNCTION: GAMEMD 0x7B4710
bool Wstring::FUN_007B4710(const char* text) const
{
    if (unknown_00 == 0 && text == 0) {
        return true;
    }
    if (unknown_00 == 0 || text == 0) {
        return false;
    }
    return strcmp(unknown_00, text) ? false : true;
}

// FUNCTION: GAMEMD 0x7B4780
bool Wstring::operator==(const Wstring& other) const
{
    if (unknown_00 == 0 && other.unknown_00 == 0) {
        return true;
    }
    if (unknown_00 == 0 || other.unknown_00 == 0) {
        return false;
    }
    return strcmp(unknown_00, other.unknown_00) ? false : true;
}

// FUNCTION: GAMEMD 0x7B47F0
bool Wstring::FUN_007B47F0(const char* text) const
{
    if (unknown_00 == 0 && text == 0) {
        return false;
    }
    if (unknown_00 == 0 || text == 0) {
        return true;
    }
    return strcmp(unknown_00, text) ? true : false;
}

// FUNCTION: GAMEMD 0x7B4860
bool Wstring::operator!=(const Wstring& other) const
{
    if (unknown_00 == 0 && other.unknown_00 == 0) {
        return false;
    }
    if (unknown_00 == 0 || other.unknown_00 == 0) {
        return true;
    }
    return strcmp(unknown_00, other.unknown_00) ? true : false;
}

// FUNCTION: GAMEMD 0x7B48D0
// Native releases the old buffer before reading text; no alias check.
Wstring& Wstring::operator=(const char* text)
{
    if (unknown_00 != 0) {
        delete[] unknown_00;
    }
    unknown_00 = 0;
    unknown_00 = new char[text ? strlen(text) + 1 : 1];
    unknown_00[0] = 0;
    if (text) {
        strcpy(unknown_00, text);
    }
    return *this;
}

// FUNCTION: GAMEMD 0x7B4940
// Assignment from another string: nothing to do when both are null or when
// both hold equal text; a null source assigns the fallback text 0x889F64.
Wstring& Wstring::operator=(const Wstring& other)
{
    if (unknown_00 == 0 && other.unknown_00 == 0) {
        return *this;
    }
    if (unknown_00 != 0 && other.unknown_00 != 0 && strcmp(unknown_00, other.unknown_00) == 0) {
        return *this;
    }
    const char* text = other.unknown_00;
    if (text == 0) {
        text = GLOBAL_00889F64;
    }
    if (unknown_00 != 0) {
        delete[] unknown_00;
    }
    unknown_00 = 0;
    unknown_00 = new char[text ? strlen(text) + 1 : 1];
    unknown_00[0] = 0;
    if (text) {
        strcpy(unknown_00, text);
    }
    return *this;
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

// FUNCTION: GAMEMD 0x7B50F0
bool Wstring::FUN_007B50F0(char ch)
{
    bool removed = false;
    if (unknown_00 == 0) {
        return false;
    }
    int len = strlen(unknown_00);
    char* found = strchr(unknown_00, ch);
    if (found != 0) {
        removed = true;
        do {
            memmove(found, found + 1, unknown_00 - found + len - 1);
            len--;
            unknown_00[len] = '\0';
            found = strchr(unknown_00, ch);
        } while (found != 0);
        char* copy = new char[strlen(unknown_00) + 1];
        strcpy(copy, unknown_00);
        delete unknown_00;
        unknown_00 = copy;
    }
    return removed;
}

// FUNCTION: GAMEMD 0x7B51B0
void Wstring::FUN_007B51B0()
{
    FUN_007B50F0(' ');
    FUN_007B50F0('\t');
}

// FUNCTION: GAMEMD 0x7B51D0
// Removes the leading run of characters that all appear in `trim`.
void Wstring::FUN_007B51D0(const Wstring* trim)
{
    int count = 0;
    while (count < Length()) {
        const char* set = trim->unknown_00;
        if (set == 0) {
            set = GLOBAL_00889F64;
        }
        if (strchr(set, unknown_00[count]) == 0) {
            break;
        }
        count++;
    }
    if (count > 0) {
        FUN_007B5020(0, count);
    }
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

// FUNCTION: GAMEMD 0x7B5340
void Wstring::FUN_007B5340()
{
    if (unknown_00 != 0) {
        delete[] unknown_00;
    }
    unknown_00 = 0;
}

// FUNCTION: GAMEMD 0x7B53B0
void Wstring::Copy_Padded(char* dest, unsigned int size) const
{
    strncpy(dest, unknown_00, size);
    unsigned int len = strlen(unknown_00);
    if (len < size) {
        memset(dest + len, ' ', size - len);
    }
    dest[size] = '\0';
}

// FUNCTION: GAMEMD 0x7B5400
const char* Wstring::FUN_007B5400() const
{
    if (unknown_00 != 0) {
        return unknown_00;
    }
    return GLOBAL_00889F64;
}

// FUNCTION: GAMEMD 0x7B54B0
int Wstring::Length() const
{
    if (unknown_00 == 0) {
        return 0;
    }
    return strlen(unknown_00);
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

// FUNCTION: GAMEMD 0x7B5AB0
bool Wstring::FUN_007B5AB0(char ch, unsigned int index)
{
    if (index >= strlen(unknown_00)) {
        return false;
    }
    unknown_00[index] = ch;
    return true;
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

// FUNCTION: GAMEMD 0x7B5B30
void Wstring::FUN_007B5B30()
{
    for (unsigned int i = 0; i < Length(); ++i) {
        char ch = unknown_00[i];
        if (ch >= 'A' && ch <= 'Z') {
            unknown_00[i] = tolower(ch);
        }
    }
}

// FUNCTION: GAMEMD 0x7B5C50
void Wstring::FUN_007B5C50()
{
    for (unsigned int i = 0; i < Length(); ++i) {
        char ch = unknown_00[i];
        if (ch >= 'a' && ch <= 'z') {
            unknown_00[i] = toupper(ch);
        }
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


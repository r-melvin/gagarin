// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native7B5B30 expands Length; /Ob2 preserves all existing complete sections.
// Canonical Wstring bodies, ascending by retail address. The class and the
// evidence for its single member are in string_class.h.
#include <string.h>
#include "string_class.h"
#include <ctype.h>
#include <stdio.h>
#include <new>
// GLOBAL: GAMEMD 0x889F64
extern char GLOBAL_00889F64[];
// GLOBAL: GAMEMD 0x822050 -- line terminator set "\r\n".
extern char DAT_00822050[];



// Length of a possibly unset string (the inline form of Wstring::Length).
static inline unsigned int LengthOf(const char* text)
{
    if (text == 0) {
        return 0;
    }
    return strlen(text);
}


// The inline expansion of the constructor from text: `self` takes a fresh copy.
static inline void InitText(Wstring* self, const char* text)
{
    self->unknown_00 = 0;
    self->unknown_00 = new char[text ? strlen(text) + 1 : 1];
    self->unknown_00[0] = 0;
    if (text) {
        strcpy(self->unknown_00, text);
    }
}

// The inline expansion of assignment from text: release the buffer, then copy.
static inline void AssignText(Wstring* self, const char* text)
{
    if (self->unknown_00) {
        delete self->unknown_00;
    }
    InitText(self, text);
}

// The inline expansion of 0x7B4B50: append another string.
static inline void AppendString(Wstring* self, const Wstring* other)
{
    const char* text;
    if (other->unknown_00 == 0) {
        text = GLOBAL_00889F64;
    } else {
        text = other->unknown_00;
    }
    if (text) {
        char* old = self->unknown_00;
        unsigned int total = strlen(text) + 1;
        if (old) {
            total += strlen(old);
        }
        self->unknown_00 = new char[total];
        if (old) {
            strcpy(self->unknown_00, old);
        } else {
            self->unknown_00[0] = 0;
        }
        strcat(self->unknown_00, text);
        if (old) {
            delete old;
        }
    }
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
// Retail 0x7B63C0 calls this; the null-text early return with the body in its else arm is the
// shape that keeps cl from expanding it there (the early-return-only form is expanded).
bool Wstring::FUN_007B4A10(const char* text)
{
    if (!text) {
        return true;
    } else {
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
    AppendString(this, other);
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

// FUNCTION: GAMEMD 0x7B5640
// Inserts the character at `pos` (clamped to the current length); an unset
// string simply takes a one-character copy.
bool Wstring::FUN_007B5640(char ch, unsigned int pos)
{
    char text[2];
    if (unknown_00 == 0) {
        text[0] = ch;
        text[1] = 0;
        InitText(this, text);
        return true;
    }
    unsigned int len = strlen(unknown_00);
    if (pos > len) {
        pos = len;
    }
    char* grown = new char[len + 2];
    text[1] = 0;
    char saved = unknown_00[pos];
    unknown_00[pos] = 0;
    strcpy(grown, unknown_00);
    unknown_00[pos] = saved;
    text[0] = ch;
    strcat(grown, text);
    strcat(grown, unknown_00 + pos);
    delete unknown_00;
    unknown_00 = grown;
    return true;
}

// FUNCTION: GAMEMD 0x7B57A0
// Replaces every occurrence of `find` with `repl` (null `repl` deletes them).
bool Wstring::FUN_007B57A0(const char* find, const char* repl)
{
    char* result = 0;
    const char* cur = FUN_007B5400();
    while (cur && *cur) {
        const char* hit = strstr(cur, find);
        if (hit == 0) {
            if (cur) {
                char* old = result;
                unsigned int total = strlen(cur) + 1;
                if (old) {
                    total += strlen(old);
                }
                result = new char[total];
                if (old) {
                    strcpy(result, old);
                } else {
                    result[0] = 0;
                }
                strcat(result, cur);
                if (old) {
                    delete old;
                }
            }
            break;
        }
        int count = hit - cur;
        if (count != 0) {
            char* old = result;
            unsigned int total = count + 1;
            if (old) {
                total += strlen(old);
            }
            result = new char[total];
            if (old) {
                strcpy(result, old);
            } else {
                result[0] = 0;
            }
            strncat(result, cur, count);
            if (old) {
                delete old;
            }
        }
        if (repl) {
            char* old = result;
            unsigned int total = strlen(repl) + 1;
            if (old) {
                total += strlen(old);
            }
            result = new char[total];
            if (old) {
                strcpy(result, old);
            } else {
                result[0] = 0;
            }
            strcat(result, repl);
            if (old) {
                delete old;
            }
        }
        cur = hit + strlen(find);
    }
    const char* text = result ? result : GLOBAL_00889F64;
    AssignText(this, text);
    if (result != 0) {
        delete result;
    }
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

// FUNCTION: GAMEMD 0x7B5B80
Wstring Wstring::FUN_007B5B80() const
{
    Wstring work(*this);
    for (unsigned int i = 0; i < work.Length(); ++i) {
        char ch = work.unknown_00[i];
        if (ch >= 'A' && ch <= 'Z') {
            work.unknown_00[i] = tolower(ch);
        }
    }
    return work;
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

// FUNCTION: GAMEMD 0x7B5CA0
Wstring Wstring::FUN_007B5CA0() const
{
    Wstring work(*this);
    for (unsigned int i = 0; i < work.Length(); ++i) {
        char ch = work.unknown_00[i];
        if (ch >= 'a' && ch <= 'z') {
            work.unknown_00[i] = toupper(ch);
        }
    }
    return work;
}

// FUNCTION: GAMEMD 0x7B5D70
// Replaces the buffer with a copy of up to `length` leading characters.
bool Wstring::FUN_007B5D70(int length)
{
    const char* source = unknown_00;
    if (source == 0) {
        source = GLOBAL_00889F64;
    }
    char* head = new char[length + 1];
    head[0] = 0;
    if (source) {
        strncpy(head, source, length);
    }
    head[length] = 0;
    const char* text = head ? head : GLOBAL_00889F64;
    AssignText(this, text);
    if (head != 0) {
        delete head;
    }
    return true;
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


// FUNCTION: GAMEMD 0x7B60E0
// Splits the line starting at `start` into `out` (terminator excluded from the
// scan, CR LF counted as one); returns the index after it, or -1 past the end.
int Wstring::FUN_007B60E0(int start, Wstring* out)
{
    int end = start;
    if (start >= (int)LengthOf(unknown_00)) {
        return -1;
    }
    while (end < (int)LengthOf(unknown_00)) {
        if (strchr(DAT_00822050, unknown_00[end]) != 0) {
            break;
        }
        ++end;
    }
    int stop = end;
    if (unknown_00[end] == '\r' && unknown_00[end + 1] == '\n') {
        ++end;
        stop = end;
    }
    AssignText(out, unknown_00 + start);
    int length = stop - start + 1;
    const char* source = GLOBAL_00889F64;
    if (out->unknown_00 != 0) {
        source = out->unknown_00;
    }
    char* head = new char[length + 1];
    head[0] = 0;
    if (source) {
        strncpy(head, source, length);
    }
    head[length] = 0;
    const char* text = GLOBAL_00889F64;
    if (head != 0) {
        text = head;
    }
    AssignText(out, text);
    if (head != 0) {
        delete head;
    }
    return stop + 1;
}

// FUNCTION: GAMEMD 0x7B6290
// Formats `value` with "%d" into a new string held by `out`.
Wstring* FUN_007B6290(Wstring* out, int value)
{
    char text[16];
    sprintf(text, "%d", value);
    InitText(out, text);
    return out;
}

// FUNCTION: GAMEMD 0x7B6320
// Formats `value` zero-padded to `width` digits into a new string held by `out`.
Wstring* FUN_007B6320(Wstring* out, int value, int width)
{
    char format[8];
    char text[8];
    sprintf(format, "%%0%dd", width);
    sprintf(text, format, value);
    InitText(out, text);
    return out;
}

// FUNCTION: GAMEMD 0x7B63C0
// Builds `prefix` followed by `suffix` into `out`.
Wstring* FUN_007B63C0(Wstring* out, const char* prefix, const Wstring* suffix)
{
    Wstring head(prefix);
    Wstring joined(head);
    const char* text;
    if (suffix->unknown_00 == 0) {
        text = GLOBAL_00889F64;
    } else {
        text = suffix->unknown_00;
    }
    joined.FUN_007B4A10(text);
    out->unknown_00 = 0;
    if (joined.unknown_00 != 0) {
        out->unknown_00 = new char[strlen(joined.unknown_00) + 1];
        strcpy(out->unknown_00, joined.unknown_00);
    }
    return out;
}

// FUNCTION: GAMEMD 0x7B64E0
// Builds the concatenation of two strings into `out`.
Wstring* FUN_007B64E0(Wstring* out, const Wstring* first, const Wstring* second)
{
    Wstring joined(*first);
    AppendString(&joined, second);
    out->unknown_00 = 0;
    if (joined.unknown_00 != 0) {
        out->unknown_00 = new char[strlen(joined.unknown_00) + 1];
        strcpy(out->unknown_00, joined.unknown_00);
    }
    return out;
}

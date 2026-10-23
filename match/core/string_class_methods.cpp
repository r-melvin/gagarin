// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Obj_007B4620 bodies, ascending by retail address. The class and the
// evidence for its single member are in string_class.h.
#include <string.h>
#include "string_class.h"

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
Obj_007B4620::Obj_007B4620(const Obj_007B4620& other)
{
    Str = 0;
    if (other.Str != 0) {
        Str = new char[strlen(other.Str) + 1];
        strcpy(Str, other.Str);
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

// FUNCTION: GAMEMD 0x7B4780
bool Obj_007B4620::operator==(const Obj_007B4620& other) const
{
    if (Str == 0 && other.Str == 0) {
        return true;
    }
    if (Str == 0 || other.Str == 0) {
        return false;
    }
    return strcmp(Str, other.Str) ? false : true;
}

// FUNCTION: GAMEMD 0x7B4860
bool Obj_007B4620::operator!=(const Obj_007B4620& other) const
{
    if (Str == 0 && other.Str == 0) {
        return false;
    }
    if (Str == 0 || other.Str == 0) {
        return true;
    }
    return strcmp(Str, other.Str) ? true : false;
}

// FUNCTION: GAMEMD 0x7B50F0
bool Obj_007B4620::FUN_007B50F0(char ch)
{
    bool removed = false;
    if (Str == 0) {
        return false;
    }
    int len = strlen(Str);
    char* found = strchr(Str, ch);
    if (found != 0) {
        removed = true;
        do {
            memmove(found, found + 1, Str - found + len - 1);
            len--;
            Str[len] = '\0';
            found = strchr(Str, ch);
        } while (found != 0);
        char* copy = new char[strlen(Str) + 1];
        strcpy(copy, Str);
        delete Str;
        Str = copy;
    }
    return removed;
}

// FUNCTION: GAMEMD 0x7B51B0
void Obj_007B4620::FUN_007B51B0()
{
    FUN_007B50F0(' ');
    FUN_007B50F0('\t');
}

// FUNCTION: GAMEMD 0x7B53B0
void Obj_007B4620::Copy_Padded(char* dest, unsigned int size) const
{
    strncpy(dest, Str, size);
    unsigned int len = strlen(Str);
    if (len < size) {
        memset(dest + len, ' ', size - len);
    }
    dest[size] = '\0';
}

// FUNCTION: GAMEMD 0x7B54B0
int Obj_007B4620::Length() const
{
    if (Str == 0) {
        return 0;
    }
    return strlen(Str);
}

// FUNCTION: GAMEMD 0x7B5AB0
bool Obj_007B4620::FUN_007B5AB0(char ch, unsigned int index)
{
    if (index >= strlen(Str)) {
        return false;
    }
    Str[index] = ch;
    return true;
}

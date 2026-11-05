// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at 0x7B4A10.
//   PLACEMENT LEAD (inference): 0x7B63C0 (match/string_class_methods.cpp) reaches it by a
//   real CALL. At /Ob2 cl inlines any body it can see, so the retail call implies the body
//   was compiled in a different original object than that caller. This file is that
//   separate object; the original file name is not known and is not claimed.
#include <string.h>
#include <new>
#include "string_class.h"

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


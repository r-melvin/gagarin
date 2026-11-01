// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#ifndef GG_CORE_BOUNDED_TEXT_H
#define GG_CORE_BOUNDED_TEXT_H
#include <string.h>
struct AbstractNoInit;

// Native 0x410800 clears only the first byte of each text member before
// installing the derived vtables; 0x410960 leaves the buffers untouched.
// Native 0x410800 and 0x410A60 use bounded temporaries and self-checked copies.
// gagarin helper for those operations.
// This name does not claim an original template or recovered source spelling.
template<int N> struct GgBoundedText
{
    char Data[N];
    GgBoundedText() { Data[0] = 0; }
    explicit GgBoundedText(const AbstractNoInit&) {}
    operator char*() { return Data; }
    operator const char*() const { return Data; }
    GgBoundedText(const char* text)
    {
        if (text == 0)
            Data[0] = 0;
        else
        {
            strncpy(Data, text, N - 1);
            Data[N - 1] = 0;
        }
    }
    void CopyTo(char* destination) const
    {
        if (Data != destination)
            memcpy(destination, Data, N);
    }
};
#endif

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small leaf bodies from
//   the 0x6C9000-0x735100 range; the receivers are placeholder views of the members touched.
//
// Address index: 0x6C9960 0x6CE240 0x735060 0x735090

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" wchar_t* __cdecl wcscpy(wchar_t*, const wchar_t*);
extern "C" size_t __cdecl wcslen(const wchar_t*);

// An object that owns one heap-allocated wide string at +0x14.
struct TextHolder_006C9960
{
    unsigned char unknown_00[0x14];
    wchar_t* Text;   // +0x14

    void FUN_006C9960(const wchar_t* text);
};
GG_STATIC_ASSERT(offsetof(TextHolder_006C9960, Text) == 0x14);

// FUNCTION: GAMEMD 0x6C9960
// Replaces the owned string with a copy of the given one (or none).
void TextHolder_006C9960::FUN_006C9960(const wchar_t* text)
{
    if (Text) {
        delete[] Text;
        Text = 0;
    }
    if (text) {
        Text = new wchar_t[wcslen(text) + 1];
        if (Text) {
            wcscpy(Text, text);
        }
    }
}

struct Triple_006CE240
{
    int X;
    int Y;
    int Z;

    Triple_006CE240 FUN_006CE240(const Triple_006CE240& other) const;
};

// FUNCTION: GAMEMD 0x6CE240
// Component-wise sum, returned by value.
Triple_006CE240 Triple_006CE240::FUN_006CE240(const Triple_006CE240& other) const
{
    Triple_006CE240 sum;
    sum.X = other.X + X;
    sum.Y = other.Y + Y;
    sum.Z = other.Z + Z;
    return sum;
}

// FUNCTION: GAMEMD 0x735060
// Widens a byte string into a wide buffer, stopping at the terminator or after the given count
// (a count of -1 never runs out), and terminates it.
void __fastcall FUN_00735060(unsigned short* dst, const char* src, int count)
{
    while (*src && count) {
        *dst = (unsigned char)*src;
        dst++;
        src++;
        if (count != -1) {
            count--;
        }
    }
    *dst = 0;
}

// FUNCTION: GAMEMD 0x735090
// Narrows a wide string into a byte buffer under the same count rule, and terminates it.
void __fastcall FUN_00735090(char* dst, const unsigned short* src, int count)
{
    while (*src && count) {
        *dst = (char)*src;
        src++;
        dst++;
        if (count != -1) {
            count--;
        }
    }
    *dst = 0;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the address below.
//   Address index: 0x7350C0, 0x735120.

#include <stddef.h>

// GLOBAL: GAMEMD 0xB1CF90 -- index of the buffer handed out next.
extern unsigned int DAT_00B1CF90;
// GLOBAL: GAMEMD 0xB0FE94 -- eight 1 KiB scratch buffers handed out in turn.
extern char DAT_00B0FE94[8][0x400];

// Copy at most `count` characters, keeping the low byte of each, and
// terminate the result.
static inline void NarrowCopy(char* dst, const wchar_t* src, unsigned int count)
{
    while (*src != 0 && count != 0) {
        *dst++ = (char)*src++;
        if (count != (unsigned int)-1)
            count--;
    }
    *dst = 0;
}

// FUNCTION: GAMEMD 0x7350C0
// Narrows a wide string (low byte of each character, at most 1024) into the
// next of eight rotating scratch buffers and returns that buffer; null in,
// null out.
char* __fastcall FUN_007350C0(const wchar_t* text)
{
    if (!text)
        return 0;
    char* buffer = DAT_00B0FE94[DAT_00B1CF90];
    NarrowCopy(buffer, text, 0x400);
    buffer[0x3FF] = 0;
    DAT_00B1CF90 = (DAT_00B1CF90 + 1) & 7;
    return buffer;
}

// GLOBAL: GAMEMD 0xB1CF94 -- index of the wide buffer handed out next.
extern unsigned int DAT_00B1CF94;
// GLOBAL: GAMEMD 0xB13F24 -- eight 2 KiB wide scratch buffers handed out in turn.
extern wchar_t DAT_00B13F24[8][0x400];

// Copy at most `count` characters, widening each byte, and terminate the result.
static inline void WidenCopy(wchar_t* dst, const char* src, unsigned int count)
{
    while (*src != 0 && count != 0) {
        *dst++ = (unsigned char)*src++;
        if (count != (unsigned int)-1)
            count--;
    }
    *dst = 0;
}

// FUNCTION: GAMEMD 0x735120
// Widens a narrow string (at most 1024 characters) into the next of eight
// rotating scratch buffers and returns that buffer; null in, null out.
wchar_t* __fastcall FUN_00735120(const char* text)
{
    if (!text)
        return 0;
    wchar_t* buffer = DAT_00B13F24[DAT_00B1CF94];
    WidenCopy(buffer, text, 0x400);
    buffer[0x3FF] = 0;
    DAT_00B1CF94 = (DAT_00B1CF94 + 1) & 7;
    return buffer;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0FE94
char DAT_00B0FE94[8][0x400];
// GLOBAL: GAMEMD 0xB1CF90
unsigned int DAT_00B1CF90;
// GLOBAL: GAMEMD 0xB13F24
wchar_t DAT_00B13F24[8][0x400];
// GLOBAL: GAMEMD 0xB1CF94
unsigned int DAT_00B1CF94;
// END defined globals

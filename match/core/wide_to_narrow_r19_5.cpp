// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the address below.
//   Address index: 0x7350C0.

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

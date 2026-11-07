// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read off retail gamemd.exe v1.001 at 0x410E70 via the local Ghidra CLI.

#include "drawing.h"

// FUNCTION: GAMEMD 0x410E70  (__stdcall, RET 0xC)
// Fill `count` 16-bit cells with one value: an odd leading cell if the
// destination is not dword aligned, then whole dwords, then a trailing cell.
// The trailing store is reached through the end pointer of the dword run, so it
// is skipped when there was no dword run.
void __stdcall FUN_00410E70(unsigned short* dest, int count, unsigned short value)
{
    if (((unsigned long)dest & 2) && count) {
        *dest = value;
        dest++;
        count--;
    }

    int pairs = count >> 1;
    unsigned short* end = 0;
    if (pairs) {
        unsigned long* wide = (unsigned long*)dest;
        unsigned long both = ((unsigned long)value << 16) + value;
        for (int i = pairs; i != 0; i--) {
            *wide++ = both;
        }
        end = dest + pairs * 2;
    }

    if ((count & 1) && end) {
        *end = value;
    }
}

// FUNCTION: GAMEMD 0x411330  (__thiscall, RET 0x10)
// Fill a rectangle of the ring buffer with the cell value 0x7F, row by row; a row that runs past the
// buffer's end continues from its start.
void ABuffer::FUN_00411330(RectangleStruct rectangle)
{
    unsigned int offset = (unsigned int)Surface->vf_23(rectangle.X, rectangle.Y);
    Surface->Lock();
    unsigned int position = BufferPosition + offset;
    if (position >= (unsigned int)BufferTail)
        position -= BufferSize;

    for (int row = rectangle.Height; row > 0; row--) {
        if (position + rectangle.Width * 2 >= (unsigned int)BufferTail) {
            int first = ((unsigned int)BufferTail - position) >> 1;
            FUN_00410E70((unsigned short*)position, first, 0x7F);
            FUN_00410E70((unsigned short*)BufferHead, rectangle.Width - first, 0x7F);
        } else {
            FUN_00410E70((unsigned short*)position, rectangle.Width, 0x7F);
        }
        position += Width * 2;
        if (position >= (unsigned int)BufferTail)
            position -= BufferSize;
    }
}

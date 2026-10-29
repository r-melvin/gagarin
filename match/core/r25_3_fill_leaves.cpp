// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below.
//
// Address index: 0x7BCAF0 0x7BE5D0

#include <stdlib.h>

// FUNCTION: GAMEMD 0x7BCAF0
// Fill count 16-bit words with the low word of value: a leading word to reach 4-byte alignment,
// then whole dwords, then a trailing word.
void __stdcall FUN_007BCAF0(short* dest, unsigned int count, unsigned int value)
{
    if (((unsigned int)dest & 2) && count != 0) {
        *dest = (short)value;
        dest++;
        count--;
    }
    int pairs = (int)count >> 1;
    int* tail = 0;
    if (pairs != 0) {
        tail = (int*)dest;
        int both = (int)((value & 0xFFFF) * 0x10001);
        for (int i = pairs; i != 0; i--) {
            *tail++ = both;
        }
        tail = (int*)dest + pairs;
    }
    if ((count & 1) && tail != 0) {
        *(short*)tail = (short)value;
    }
}

// FUNCTION: GAMEMD 0x7BE5D0
// Memory callback of a decoder: op 2 allocates size bytes, op 3 frees the block, ops 4 and 5 hand the
// block back and op 6 stores -1 through it.
void* __cdecl FUN_007BE5D0(int context, int op, void* block, size_t size)
{
    void* result = 0;
    switch (op) {
    case 2:
        result = malloc(size);
        break;
    case 3:
        free(block);
        break;
    case 4:
    case 5:
        result = block;
        break;
    case 6:
        *(int*)block = -1;
        break;
    }
    return result;
}

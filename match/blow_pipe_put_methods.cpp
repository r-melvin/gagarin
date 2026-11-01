// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#include "pk_blow_pipes.h"

// LIBRARY: GAMEMD 0x7CA090 (decl; reloc) -- CRT memmove.
extern "C" void* __cdecl memmove(void* destination, const void* source, unsigned int count);
// FUNCTION: GAMEMD 0x438210
int BlowStraw::FUN_006C98E0(void* destination, int length)
{
    if (destination == 0 || length <= 0) return 0;
    if (Cipher == 0) return Straw::FUN_006C98E0(destination, length);
    int total = 0;
    do {
        if (Counter > 0) {
            int count = length < Counter ? length : Counter;
            memmove(destination, &Buffer[8 - Counter], count);
            Counter -= count;
            destination = static_cast<char*>(destination) + count;
            length -= count;
            total += count;
        }
        if (length == 0) break;
        int count = Straw::FUN_006C98E0(Buffer, 8);
        if (count == 0) break;
        if (count == 8) {
            if (Control == PIPE_DIR_1) Cipher->Reverse(Buffer, count, Buffer);
            else Cipher->Forward(Buffer, count, Buffer);
        } else {
            memmove(&Buffer[8 - count], Buffer, count);
        }
        Counter = count;
    } while (length > 0);
    return total;
}

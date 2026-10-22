// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The parameters keep the canonical Pipe/Straw int ABI view (pointer, count);
// the casts below hand that view to memmove and the hash as pointers.
#include "buffer_straws.h"

// FUNCTION: GAMEMD 0x4A2030
int HashPipe_004A2030::FUN_00631D10(int first, int second)
{
    Hash.Feed((const void*)first, second);
    return Pipe::FUN_00631D10(first, second);
}

// FUNCTION: GAMEMD 0x4A20B0
int HashStraw_004A20B0::FUN_006C98E0(int first, int second)
{
    if (first == 0 || second < 1) {
        return 0;
    }
    int counter = Straw::FUN_006C98E0(first, second);
    Hash.Feed((const void*)first, counter);
    return counter;
}

// FUNCTION: GAMEMD 0x4A2780
int CacheStraw::FUN_006C98E0(int first, int second)
{
    int total = 0;

    if (Buffer.Buffer != 0 && first != 0 && second > 0) {
        while (second > 0) {
            if (Length > 0) {
                int tocopy = (Length < second) ? Length : second;
                memmove((void*)first, (char*)Buffer.Buffer + Index, tocopy);
                second -= tocopy;
                Index += tocopy;
                total += tocopy;
                Length -= tocopy;
                first += tocopy;
            }
            if (second == 0) {
                break;
            }
            Length = Straw::FUN_006C98E0((int)Buffer.Buffer, Buffer.Size);
            Index = 0;
            if (Length == 0) {
                break;
            }
        }
    }
    return total;
}

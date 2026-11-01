// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Straw slot 2 takes a destination pointer and a signed byte count.
#include "buffer_straws.h"

// FUNCTION: GAMEMD 0x4A2030
int HashPipe_004A2030::FUN_00631D10(int first, int second)
{
    Hash.Feed((const void*)first, second);
    return Pipe::FUN_00631D10(first, second);
}

// FUNCTION: GAMEMD 0x4A20B0
int HashStraw_004A20B0::FUN_006C98E0(void* first, int second)
{
    if (first == 0 || second < 1) {
        return 0;
    }
    int counter = Straw::FUN_006C98E0(first, second);
    Hash.Feed(first, counter);
    return counter;
}


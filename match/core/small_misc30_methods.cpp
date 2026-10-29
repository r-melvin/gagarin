// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x438060.
#include "../platform/pk_blow_pipes.h"

// FUNCTION: GAMEMD 0x438060
int BlowPipe::FUN_00631D30()
{
    int written = 0;
    int length = Counter;
    if (length > 0 && Cipher != 0) {
        written = Pipe::FUN_00631D10((int)Buffer, length);
    }
    Counter = 0;
    return Pipe::FUN_00631D30() + written;
}

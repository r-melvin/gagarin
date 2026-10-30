// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#include "../platform/pk_blow_pipes.h"

// LIBRARY: GAMEMD 0x7CA090 (decl; reloc) -- CRT memmove.
extern "C" void* __cdecl memmove(void* destination, const void* source, unsigned int count);

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

// BlowPipe slot +0x10: stage bytes into the eight-byte block at +0x10, run
// the cipher at +0x0C over complete blocks, then pass each block down the pipe.
// This keeps the canonical Pipe int ABI view (pointer, count).
// FUNCTION: GAMEMD 0x4380A0
int BlowPipe::FUN_00631D10(int first, int second)
{
    if (first == 0 || second < 1 || Cipher == 0) {
        return Pipe::FUN_00631D10(first, second);
    }

    int total = 0;
    if (Counter != 0) {
        int room = sizeof(Buffer) - Counter;
        if (room >= second) {
            room = second;
        }
        memmove(&Buffer[Counter], (const void*)first, room);
        Counter += room;
        first += room;
        second -= room;
        if (Counter == sizeof(Buffer)) {
            if (Control == PIPE_DIR_1) {
                Cipher->Reverse(Buffer, Counter, Buffer);
            } else {
                Cipher->Forward(Buffer, Counter, Buffer);
            }
            total = Pipe::FUN_00631D10((int)Buffer, sizeof(Buffer));
            Counter = 0;
        }
    }

    while (second >= sizeof(Buffer)) {
        if (Control == PIPE_DIR_1) {
            Cipher->Reverse((const void*)first, sizeof(Buffer), Buffer);
        } else {
            Cipher->Forward((const void*)first, sizeof(Buffer), Buffer);
        }
        total += Pipe::FUN_00631D10((int)Buffer, sizeof(Buffer));
        first += sizeof(Buffer);
        second -= sizeof(Buffer);
    }

    if (second > 0) {
        memmove(Buffer, (const void*)first, second);
        Counter = second;
    }
    return total;
}

// FUNCTION: GAMEMD 0x4381D0
void BlowPipe::Key(const void* key, int length)
{
    if (Cipher == 0) Cipher = new BlockCipherView;
    if (Cipher) Cipher->Key(key, length);
}

// FUNCTION: GAMEMD 0x438300
void BlowStraw::Key(const void* key, int length)
{
    if (Cipher == 0) Cipher = new BlockCipherView;
    if (Cipher) Cipher->Key(key, length);
}

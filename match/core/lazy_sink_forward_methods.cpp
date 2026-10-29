// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#include "../platform/pk_blow_pipes.h"

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

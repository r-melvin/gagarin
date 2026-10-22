// Provenance: own-binary-via-Ghidra
// PKPipe slot +0x10 (0x632DC0) and PKStraw slot +0x08 (0x633130): the
// first call through either object exchanges a 56-byte cipher key under
// the public key at +0x38 (random bytes from the straw at +0x10, staged
// in the buffer at +0x3C), then the remaining data passes through to the
// base Pipe/Straw slot. The int parameters are base-slot ABI view
// (pointer, byte count).
#include <string.h>
#include "pk_key_pipes.h"

// FUNCTION: GAMEMD 0x632DC0
int PKPipe::FUN_00631D10(int source, int length)
{

    if (source == 0 || length < 1 || Key == NULL) {
        return Pipe::FUN_00631D10(source, length);
    }

    int total = 0;
    if (unknown_C) {
        if (Control == PIPE_DIR_0) {
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            unknown_10->FUN_006C98E0((int)buffer, PK_SESSION_KEY_BYTES);
            total = Pipe::FUN_00631D10((int)Buffer, Key->Encrypt(buffer, SessionKeyPlainBytes(), Buffer));
            Cipher.Key(buffer, PK_SESSION_KEY_BYTES);
            unknown_C = false;
        } else {
            int take = (unknown_140 < length) ? unknown_140 : length;
            memmove(&Buffer[Counter - unknown_140], (const void*)source, take);
            length -= take;
            unknown_140 -= take;
            source += take;
            if (unknown_140 == 0) {
                char buffer[256];
                Key->Decrypt(Buffer, Counter, buffer);
                Cipher.Key(buffer, PK_SESSION_KEY_BYTES);
                unknown_C = false;
            }
        }
    }
    return total + Pipe::FUN_00631D10(source, length);
}

// FUNCTION: GAMEMD 0x633130
int PKStraw::FUN_006C98E0(int source, int length)
{

    if (source == 0 || length < 1 || Key == NULL) {
        return Straw::FUN_006C98E0(source, length);
    }

    int total = 0;
    if (unknown_C) {
        char buffer[256];
        if (Control == PIPE_DIR_1) {
            int readCount = Straw::FUN_006C98E0((int)buffer, SessionKeyCipherBytes());
            if (readCount != SessionKeyCipherBytes()) {
                return 0;
            }
            Key->Decrypt(buffer, readCount, Buffer);
            Cipher.Key(Buffer, PK_SESSION_KEY_BYTES);
        } else {
            memset(buffer, 0, sizeof(buffer));
            unknown_10->FUN_006C98E0((int)buffer, PK_SESSION_KEY_BYTES);
            Counter = unknown_140 = Key->Encrypt(buffer, SessionKeyPlainBytes(), Buffer);
            Cipher.Key(buffer, PK_SESSION_KEY_BYTES);
        }
        unknown_C = false;
    }

    if (unknown_140 > 0) {
        int take = (length < unknown_140) ? length : unknown_140;
        memmove((void*)source, &Buffer[Counter - unknown_140], take);
        source += take;
        unknown_140 -= take;
        length -= take;
        total = take;
    }
    return total + Straw::FUN_006C98E0(source, length);
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x412610 and
//   0x41D7E0.

#include "small_misc47_methods.h"

// FUNCTION: GAMEMD 0x412610
int FUN_00412610(const char* text)
{
    int value = 0;

    while (text != 0) {
        if (FUN_007C99B4(*text) == 0) {
            break;
        }

        char c = *text;

        value <<= 4;
        text++;

        if (c >= '0' && c <= '9') {
            value += c - 0x30;
        } else {
            value += FUN_007C97D3(c) - 0x37;
        }
    }

    return value;
}


// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The hex parser at 0x6F0680 was read
// instruction by instruction from gamemd.exe v1.001; global addresses and constants confirmed.

// LIBRARY: GAMEMD 0x7C99B4 isxdigit, 0x7C998C isdigit, 0x7C97D3 toupper.
extern "C" int __cdecl FUN_007C99B4(int c);
extern "C" int __cdecl FUN_007C998C(int c);
extern "C" int __cdecl FUN_007C97D3(int c);

// FUNCTION: GAMEMD 0x6F0680 -- parse a hexadecimal string.
int FUN_006F0680(const char* text)
{
    int value = 0;

    while (FUN_007C99B4(*text) != 0) {
        value <<= 4;
        if (FUN_007C998C(*text) != 0) {
            value += *text - 0x30;
        } else {
            value += FUN_007C97D3(*text) - 0x37;
        }
        text++;
    }

    return value;
}

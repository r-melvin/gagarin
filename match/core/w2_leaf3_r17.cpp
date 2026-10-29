// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. String hashes built on the
//   rotating checksum step at 0x64DE80.
//
// Address index: 0x5DAB80 0x5DAC00

#include <string.h>
#include <wchar.h>

// FUNCTION: GAMEMD 0x64DE80 (decl; reloc) -- rotate the running checksum left one bit and add a value.
void __fastcall FUN_0064DE80(unsigned int* sum, unsigned int value);

// FUNCTION: GAMEMD 0x5DAB80
// Checksum of an upper-cased copy of a narrow string.
int __fastcall FUN_005DAB80(const char* text)
{
    unsigned int sum = 0;
    char buffer[0x50];
    strcpy(buffer, text);
    _strupr(buffer);
    for (unsigned int i = 0; i < strlen(buffer); i++) {
        FUN_0064DE80(&sum, buffer[i]);
    }
    return sum;
}

// FUNCTION: GAMEMD 0x5DAC00
// Checksum of an upper-cased copy of a wide string.
int __fastcall FUN_005DAC00(const wchar_t* text)
{
    unsigned int sum = 0;
    wchar_t buffer[0x50];
    wcscpy(buffer, text);
    _wcsupr(buffer);
    for (unsigned int i = 0; i < wcslen(buffer); i++) {
        FUN_0064DE80(&sum, buffer[i]);
    }
    return sum;
}

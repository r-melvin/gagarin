// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: small functions beside the NullModem unit (0x5F1350..0x5F34D0) that forward to the
//   shared WinModemClass instance at 0xB72D20 or work on the text buffer at 0xA8EA7C, each
//   disassembled from the user's gamemd.exe v1.001.

#include <string.h>
#include <stdlib.h>
#include "null_modem_class_methods.h"
#include "win_modem_class.h"

// GLOBAL: GAMEMD 0xA8EA7C -- growable text buffer: pointer, capacity, length.
extern char* DAT_00A8EA7C;
// GLOBAL: GAMEMD 0xA8EA80
extern int DAT_00A8EA80;
// GLOBAL: GAMEMD 0xA8EA84
extern int DAT_00A8EA84;
// GLOBAL: GAMEMD 0xAC1344
extern bool DAT_00AC1344;

// CRT isdigit (0x7C998C).
int __cdecl gg_isdigit(int c);
// FUNCTION: GAMEMD 0x5F33B0 (decl; reloc) -- the modem poll callback.
int __cdecl FUN_005F33B0();

// FUNCTION: GAMEMD 0x5F1350
// Appends one character to the text buffer while room remains for the terminator.
void __fastcall FUN_005F1350(char c)
{
    if (DAT_00A8EA84 < DAT_00A8EA80 - 1) {
        DAT_00A8EA7C[DAT_00A8EA84] = c;
        DAT_00A8EA7C[DAT_00A8EA84 + 1] = 0;
        DAT_00A8EA84++;
    }
}

// FUNCTION: GAMEMD 0x5F3320
// Passes a value to the shared modem's slot 8 (stores +0x64).
void __stdcall FUN_005F3320(int value)
{
    WinModem_00B72D20->Set_Value_64(value);
}

// FUNCTION: GAMEMD 0x5F3350
// Maps carriage returns and line feeds in the text buffer to the codes 1 and 2.
void FUN_005F3350()
{
    for (unsigned int i = 0; i < strlen(DAT_00A8EA7C); i++) {
        char c = DAT_00A8EA7C[i];
        if (c == '\r') {
            DAT_00A8EA7C[i] = 1;
        } else if (c == '\n') {
            DAT_00A8EA7C[i] = 2;
        }
    }
}

// FUNCTION: GAMEMD 0x5F3400
// Installs the poll callback on the shared modem and clears the abort flag.
void FUN_005F3400()
{
    WinModem_00B72D20->Set_Value_68((int)FUN_005F33B0);
    DAT_00AC1344 = false;
}

// FUNCTION: GAMEMD 0x5F3420
// Removes the poll callback from the shared modem and clears the abort flag.
void FUN_005F3420()
{
    WinModem_00B72D20->Set_Value_68(0);
    DAT_00AC1344 = false;
}

// STRING: GAMEMD 0x832678 -- "AT"
extern const char STR_00832678[];

// FUNCTION: GAMEMD 0x5F3450
// Reads the shared modem's status word; clears bit 7 when an "AT" query gets answer code 2.
// PARTIAL: 91.7% -- retail saves the status in ESI after pushing the trailing -1 (two instructions swapped).
int FUN_005F3450()
{
    char reply[0x54];
    int status = WinModem_00B72D20->Get_Modem_Status();
    if (WinModem_00B72D20->FUN_slot1C(STR_00832678, 0xD, reply, 0x51, 0x5A, 1, -1) == 2) {
        status &= ~0x80;
    }
    return status;
}

// FUNCTION: GAMEMD 0x5F34A0
// Forwards six arguments plus a trailing -1 to the shared modem's slot 7.
int __stdcall FUN_005F34A0(const char* a1, int a2, char* a3, int a4, int a5, int a6)
{
    return WinModem_00B72D20->FUN_slot1C(a1, a2, a3, a4, a5, a6, -1);
}

// FUNCTION: GAMEMD 0x5F34D0
// Returns the integer value of an all-digit string, or -1 if any character is not a digit.
int __stdcall FUN_005F34D0(const char* text)
{
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        if (!gg_isdigit(text[i])) {
            return -1;
        }
    }
    return atoi(text);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8EA7C
char* DAT_00A8EA7C;
// GLOBAL: GAMEMD 0xA8EA80
int DAT_00A8EA80;
// GLOBAL: GAMEMD 0xA8EA84
int DAT_00A8EA84;
// GLOBAL: GAMEMD 0xAC1344
bool DAT_00AC1344;
// END defined globals

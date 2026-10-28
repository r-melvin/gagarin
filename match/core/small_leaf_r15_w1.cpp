// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every constant, string and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//
// Round 15 small free functions, ascending by retail address.
// Address index: 0x4A3B80 0x4A83D0.
#include <windows.h>
#include <stdio.h>

// FUNCTION: GAMEMD 0x4A3A10 (decl; reloc)
int __fastcall FUN_004A3A10(int a, int b, int c, int d);

// FUNCTION: GAMEMD 0x4A3B80
// 0x4A3A10 of the first two stack arguments (ECX/EDX pass straight through), divided by 8000.
int __fastcall FUN_004A3B80(int ecx, int edx, int a, int b, int unused)
{
    return FUN_004A3A10(ecx, edx, a, b) / 8000;
}

// FUNCTION: GAMEMD 0x4A83D0
// Shows the "Please insert disk %d" prompt; true when the user accepts.
bool __stdcall FUN_004A83D0(int disk)
{
    char text[0x100];
    sprintf(text, "Please insert disk %d", disk);
    bool r = MessageBoxA(0, text, "Hey!", MB_OKCANCEL) == IDOK;
    return r;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu289_methods.h"

// FUNCTION: GAMEMD 0x7AF390
// Tail-calls a method on a global object.
void FUN_007AF390(int a1, int a2)
{
    FUN_007B46F0(DAT_00B77EF0, a2);
}

// FUNCTION: GAMEMD 0x7AF3A0
// Tail-calls a method on a global object.
void FUN_007AF3A0(int a1, int a2)
{
    FUN_007B46F0(DAT_00B77F30, a2);
}

// FUNCTION: GAMEMD 0x7AF3B0
// Tail-calls a method on a global object.
void FUN_007AF3B0(int a1, int a2)
{
    FUN_007B46F0(DAT_00B77F08, a2);
}

// FUNCTION: GAMEMD 0x7AF3C0
// Tail-calls a method on a global object.
void FUN_007AF3C0(int a1, int a2)
{
    FUN_007B46F0(DAT_00B77F20, a2);
}

// FUNCTION: GAMEMD 0x7AF4C0
// Tail-calls a method on a global object.
void FUN_007AF4C0(int a1, int a2)
{
    FUN_007B46F0(DAT_00B77EB0, a2);
}

// FUNCTION: GAMEMD 0x7AF4D0
// Tail-calls a method on a global object.
void FUN_007AF4D0(int a1, int a2)
{
    FUN_007B46F0(DAT_00B77F1C, a2);
}

// FUNCTION: GAMEMD 0x7AF4E0
// Tail-calls a method on a global object.
void FUN_007AF4E0(int a1, int a2)
{
    FUN_007B46F0(DAT_00B77EC8, a2);
}

// FUNCTION: GAMEMD 0x7AF4F0
// Tail-calls a method on a global object.
void FUN_007AF4F0(int a1, int a2)
{
    FUN_007B46F0(DAT_00B77EC0, a2);
}

// FUNCTION: GAMEMD 0x7B0290
// Returns the address of a global.
void* __cdecl FUN_007B0290()
{
    return DAT_00B77F70;
}

// FUNCTION: GAMEMD 0x7B0310
// Returns a global (dword).
int __cdecl FUN_007B0310()
{
    return DAT_00B77F54;
}

// FUNCTION: GAMEMD 0x7B0340
// Returns a global (dword).
int __cdecl FUN_007B0340()
{
    return DAT_00B77F60;
}

// FUNCTION: GAMEMD 0x7B0380
// Returns the address of a global.
void* __cdecl FUN_007B0380()
{
    return DAT_00B77F78;
}

// FUNCTION: GAMEMD 0x7B0430
// Returns a constant boolean.
bool __cdecl FUN_007B0430()
{
    return true;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001.

#include "member_setter_family_methods.h"

// FUNCTION: GAMEMD 0x00487C70
//
// Store the argument into the member at +0xF8.
void Setter_00487C70::FUN_00487C70(int value)
{
    *(int*)(Bytes + 0xF8) = value;
}


// FUNCTION: GAMEMD 0x00681110
//
// Store the argument into the member at +0x188.
void Setter_00487C70::FUN_00681110(int value)
{
    *(int*)(Bytes + 0x188) = value;
}

// FUNCTION: GAMEMD 0x00681130
//
// Store the argument into the member at +0x18C.
void Setter_00487C70::FUN_00681130(int value)
{
    *(int*)(Bytes + 0x18C) = value;
}

// FUNCTION: GAMEMD 0x006812C0
//
// Store the argument into the member at +0x3F0.
void Setter_00487C70::FUN_006812C0(int value)
{
    *(int*)(Bytes + 0x3F0) = value;
}


// FUNCTION: GAMEMD 0x00759F20
//
// Store the argument into the member at +0x510.
void Setter_00487C70::FUN_00759F20(int value)
{
    *(int*)(Bytes + 0x510) = value;
}


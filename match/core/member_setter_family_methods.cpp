// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001.

#include "member_setter_family_methods.h"

// FUNCTION: GAMEMD 0x00487C70
//
// Store the argument into the member at +0xF8.
void __fastcall FUN_00487C70(Setter_00487C70* self, int, int value)
{
    *(int*)(self->Bytes + 0xF8) = value;
}

// FUNCTION: GAMEMD 0x0050DA00
//
// Store the argument into the member at +0x54F0.
void __fastcall FUN_0050DA00(Setter_00487C70* self, int, int value)
{
    *(int*)(self->Bytes + 0x54F0) = value;
}

// FUNCTION: GAMEMD 0x0050DFE0
//
// Store the argument into the member at +0x5494.
void __fastcall FUN_0050DFE0(Setter_00487C70* self, int, int value)
{
    *(int*)(self->Bytes + 0x5494) = value;
}

// FUNCTION: GAMEMD 0x0050E000
//
// Store the argument into the member at +0x5490.
void __fastcall FUN_0050E000(Setter_00487C70* self, int, int value)
{
    *(int*)(self->Bytes + 0x5490) = value;
}

// FUNCTION: GAMEMD 0x006301F0
//
// Store the argument into the member at +0xEC.
void __fastcall FUN_006301F0(Setter_00487C70* self, int, int value)
{
    *(int*)(self->Bytes + 0xEC) = value;
}

// FUNCTION: GAMEMD 0x00681110
//
// Store the argument into the member at +0x188.
void __fastcall FUN_00681110(Setter_00487C70* self, int, int value)
{
    *(int*)(self->Bytes + 0x188) = value;
}

// FUNCTION: GAMEMD 0x00681130
//
// Store the argument into the member at +0x18C.
void __fastcall FUN_00681130(Setter_00487C70* self, int, int value)
{
    *(int*)(self->Bytes + 0x18C) = value;
}

// FUNCTION: GAMEMD 0x006812C0
//
// Store the argument into the member at +0x3F0.
void __fastcall FUN_006812C0(Setter_00487C70* self, int, int value)
{
    *(int*)(self->Bytes + 0x3F0) = value;
}

// FUNCTION: GAMEMD 0x00705D10
//
// Store the argument into the member at +0x514.
void __fastcall FUN_00705D10(Setter_00487C70* self, int, int value)
{
    *(int*)(self->Bytes + 0x514) = value;
}

// FUNCTION: GAMEMD 0x00759F20
//
// Store the argument into the member at +0x510.
void __fastcall FUN_00759F20(Setter_00487C70* self, int, int value)
{
    *(int*)(self->Bytes + 0x510) = value;
}


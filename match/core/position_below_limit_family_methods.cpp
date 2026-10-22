// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001.

#include "position_below_limit_family_methods.h"


// FUNCTION: GAMEMD 0x004F3FC0
//
// Is this cursor still inside its owner's limit.
bool __fastcall FUN_004F3FC0(Cursor_004F28B0* self)
{
    return self->Position < self->Owner->Limit;
}

// FUNCTION: GAMEMD 0x00765700
//
// Is this cursor still inside its owner's limit.
bool __fastcall FUN_00765700(Cursor_004F28B0* self)
{
    return self->Position < self->Owner->Limit;
}

// FUNCTION: GAMEMD 0x00766920
//
// Is this cursor still inside its owner's limit.
bool __fastcall FUN_00766920(Cursor_004F28B0* self)
{
    return self->Position < self->Owner->Limit;
}


// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001.

#include "positive_field_predicates.h"

// FUNCTION: GAMEMD 0x0050D9C0
//
// True when the signed member at +0x164 is positive.
bool __fastcall FUN_0050D9C0(Predicate_0050D9C0* self)
{
    return *(int*)(self->Bytes + 0x164) > 0;
}

// FUNCTION: GAMEMD 0x0050D9D0
//
// True when the signed member at +0x168 is positive.
bool __fastcall FUN_0050D9D0(Predicate_0050D9C0* self)
{
    return *(int*)(self->Bytes + 0x168) > 0;
}

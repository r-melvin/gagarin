// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI and REA: `MOV EDX,[ECX+off]; XOR EAX,EAX; TEST EDX,EDX;
//   SETG AL; RET`. Each tests one signed member for > 0; the member offset is
//   the only thing that varies. Both are called from FUN_006F9E50 and
//   FUN_00709A90; the owning class is not yet confirmed, so the object is a
//   byte array reaching the highest confirmed offset.
#ifndef GG_MATCH_CORE_POSITIVE_FIELD_PREDICATES_H
#define GG_MATCH_CORE_POSITIVE_FIELD_PREDICATES_H

#include "../_rt/gg_static_assert.h"

struct Predicate_0050D9C0
{
    char Bytes[0x16C];
};
GG_STATIC_ASSERT(sizeof(Predicate_0050D9C0) == 0x16C);

// FUNCTION: GAMEMD 0x0050D9C0 — tests +0x164 > 0
bool __fastcall FUN_0050D9C0(Predicate_0050D9C0* self);
// FUNCTION: GAMEMD 0x0050D9D0 — tests +0x168 > 0
bool __fastcall FUN_0050D9D0(Predicate_0050D9C0* self);

#endif

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). The
//   IsBuildCat5 signature is cross-checked against YRpp
//   (consult-only, no LICENSE); the calling convention and the +0xE08 access
//   below are reconfirmed numerically from the disassembly.
//
// ObjectTypeClass — base type-class for every in-world object type. Only the
// pieces touched by the methods modelled in this TU are declared; the full
// AbstractTypeClass-derived layout is P2 work.
#ifndef GG_MATCH_CORE_OBJECT_TYPE_CLASS_H
#define GG_MATCH_CORE_OBJECT_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A retail callee we are NOT matching: resolves a type object from an
// AbstractType id + index. __fastcall (ECX=abstractID, EDX=idx) confirmed from
// 0x5004ED (MOV ECX,ESI; CALL 0x48DCD0 with idx still live in EDX). Declared
// body-less so cl emits a (reloc-normalised) call. Returns a pointer whose
// +0xE08 dword IS the value IsBuildCat5 returns.
char* __fastcall ObjTypeFindFromCat(int abstractID, int idx);   // GAMEMD 0x48DCD0

struct ObjectTypeClass
{
    // FUNCTION: GAMEMD 0x5004E0  ObjectTypeClass::IsBuildCat5 (static __fastcall)
    static int __fastcall IsBuildCat5(int abstractID, int idx);
};

#endif  // GG_MATCH_CORE_OBJECT_TYPE_CLASS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). The
//   IsBuildCat5 signature is cross-checked against YRpp
//  ; the calling convention and the +0xE08 access
//   below are reconfirmed numerically from the disassembly.
//
// ObjectTypeClass — base type-class for every in-world object type. Only the
// static category lookup is declared on the canonical AbstractTypeClass-derived
// ObjectTypeClass; no separate class declaration is needed here.
#ifndef GG_MATCH_CORE_OBJECT_TYPE_CLASS_H
#define GG_MATCH_CORE_OBJECT_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A retail callee we are NOT matching: resolves a type object from an
// AbstractType id + index. __fastcall (ECX=abstractID, EDX=idx) confirmed from
// 0x5004ED (MOV ECX,ESI; CALL 0x48DCD0 with idx still live in EDX). Declared
// body-less so cl emits a (reloc-normalised) call. Returns a pointer whose
// +0xE08 dword IS the value IsBuildCat5 returns.
char* ObjTypeFindFromCat(int abstractID, int idx);   // GAMEMD 0x48DCD0

#include "../_layout/object_type_class.h"

#endif  // GG_MATCH_CORE_OBJECT_TYPE_CLASS_H

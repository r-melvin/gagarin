// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and slots read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x43B5E0: `CALL 0x427CB0`
//   with the name in ECX (AnimTypeClass::FindIndex), `MOV ECX,[0x8B4154]` /
//   `MOV EDI,[ECX+EAX*4]` (AnimTypeClass::Array.Items, base 0x8B4150),
//   `CALL [EDX+0x48]` on the target with a 12-byte out buffer (GetCoords,
//   by-value CoordStruct), `PUSH 0x1C8` / `CALL 0x7C8E17` / `CALL 0x421EA0`
//   (sizeof(AnimClass) + its 7-arg ctor), `CALL 0x424C90` / `CALL 0x424CA0`
//   (two one-arg AnimClass setters) and `MOV BYTE [ESI+0x19D],1`.  Names from
//   YRpp (reconfirmed here).
#ifndef GG_MATCH_AI_HOUSE_CLASS_PSI_WARN_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_PSI_WARN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

#include "../_layout/coord_struct.h"
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

class AnimTypeClass;   // opaque — only ever passed through
class BulletClass;     // opaque
class HouseClass;
#include "../_layout/anim_class.h"

// The warn target: only its vtable+0x48 GetCoords (by-value CoordStruct
// return, hence the hidden out-pointer push) is used.  Never instantiated.
#include "../_layout/cell_class.h"

// FUNCTION: GAMEMD 0x427CB0 (decl; reloc) — AnimTypeClass::FindIndex(name).
int AnimType_FindIndex(const char* name);

// GLOBAL: GAMEMD 0x8B4150 — AnimTypeClass::Array.
extern DynamicVectorClassLayout AnimTypeArray;

class HouseClass
{
public:
    // FUNCTION: GAMEMD 0x43B5E0
    AnimClass* __fastcall PsiWarn(CellClass* target, BulletClass* bullet,
                                  const char* animName);
};

#endif  // GG_MATCH_AI_HOUSE_CLASS_PSI_WARN_METHODS_H

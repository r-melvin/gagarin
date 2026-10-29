// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4C2A60: seven stacked dwords (`RET 0x1C`) stored as two
//   three-dword coordinates at this+0x00 (`MOV EAX,ESI`) and this+0x0C
//   (`LEA EDX,[ESI+0xC]`) plus the int at [ESI+0x18]; the Randomizer at
//   0x886B88 (`MOV ECX,0x886B88; CALL 0x65C7E0` with 0 and 0x100) stored at
//   [ESI+0x1C]; the global vector at 0x8A0E88 read as `[0x8A0E90]` capacity,
//   `[0x8A0E95]` byte allocated flag, `[0x8A0E98]` count, `[0x8A0E9C]`
//   increment, `[0x8A0E8C]` items, with Resize through `MOV EDX,[0x8A0E88];
//   CALL [EDX+8]` (the inlined AddItem); `PUSH 0x100; CALL 0x7C8E17`
//   (operator new) null-tested, then the 6-argument __thiscall 0x62DC50 on
//   the block with `[[0x8871E0]+0x1020]`, the address of the second
//   coordinate, 0, 0, 0x8A0E50 and 0. Names cross-checked against YRpp
//   (every offset reconfirmed above).
#ifndef GG_MATCH_COMBAT_EBOLT_FIRE_METHODS_H
#define GG_MATCH_COMBAT_EBOLT_FIRE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/randomizer.h"
#include "../_layout/coord_struct.h"
#include "../_layout/ebolt_class.h"
#include "../core/header_init_shapes.h"

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

// The 0x100-byte object built by 0x62DC50 (a particle system).
struct ParticleSystem_004C2A60
{
    char opaque[0x100];

    // FUNCTION: GAMEMD 0x62DC50 (decl; reloc) — the constructor, six stack
    // arguments; called explicitly on the raw block so no EH frame is
    // registered.
    ParticleSystem_004C2A60* Construct(void* type, CoordStruct* coord,
                                       int a, int b, void* p, int c);
};
GG_STATIC_ASSERT(sizeof(ParticleSystem_004C2A60) == 0x100);

#endif  // GG_MATCH_COMBAT_EBOLT_FIRE_METHODS_H

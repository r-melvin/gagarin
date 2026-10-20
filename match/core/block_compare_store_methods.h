// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x402800: `LEA EBX,[EAX+0x17C]` with `MOV ECX,0x8`
//   before the REPE CMPSD gives a 32-byte block, and the flag it guards is the
//   dword immediately after it at +0x19C.
#ifndef GG_MATCH_CORE_BLOCK_COMPARE_STORE_METHODS_H
#define GG_MATCH_CORE_BLOCK_COMPARE_STORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00402800
{
    char _pad000[0x17C];   // +0x0000
    int  Block[8];         // +0x017C  32 bytes compared as a unit
    int  Changed;          // +0x019C  set when the block was replaced
};
GG_STATIC_ASSERT(offsetof(Obj_00402800, Block) == 0x17C);
GG_STATIC_ASSERT(offsetof(Obj_00402800, Changed) == 0x19C);

// FUNCTION: GAMEMD 0x402800
int __fastcall FUN_00402800(Obj_00402800* self, const int* incoming);

#endif  // GG_MATCH_CORE_BLOCK_COMPARE_STORE_METHODS_H

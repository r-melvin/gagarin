// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4087F0. The allocation size (0xA4) and the memset
//   count (`MOV ECX,0x29` before REP STOSD) agree, and the slot stride comes
//   from `ADD EAX,0x40` with the loop bound `CMP ECX,0x2`.
#ifndef GG_MATCH_CORE_SLOT_ARRAY_FACTORY_METHODS_H
#define GG_MATCH_CORE_SLOT_ARRAY_FACTORY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Owner_004087F0;

// The loop writes five fields per slot, reached off a cursor that starts at
// slot 0 + 0x24; the negative displacements in the disassembly (-0x24, -0x10,
// -0xC, -0x8) are that cursor's, so they resolve to slot offsets 0x00, 0x14,
// 0x18 and 0x1C, with the cursor itself at 0x24.
struct Slot_004087F0
{
    Owner_004087F0* Owner;   // +0x0000
    char _pad004[0x10];      // +0x0004
    int  Index;              // +0x0014
    int  field_18;           // +0x0018
    int  field_1C;           // +0x001C
    char _pad020[0x4];       // +0x0020
    int  field_24;           // +0x0024
    char _pad028[0x18];      // +0x0028
};
GG_STATIC_ASSERT(sizeof(Slot_004087F0) == 0x40);
GG_STATIC_ASSERT(offsetof(Slot_004087F0, Index) == 0x14);
GG_STATIC_ASSERT(offsetof(Slot_004087F0, field_24) == 0x24);

struct Owner_004087F0
{
    char _pad000[0x4];       // +0x0000
    char Embedded[0x14];     // +0x0004  initialised by 0x4072C0
    Slot_004087F0 Slots[2];  // +0x0018
    int  field_98;           // +0x0098  zeroed again after the memset
    char _pad09C[0x8];       // +0x009C
};
GG_STATIC_ASSERT(offsetof(Owner_004087F0, Slots) == 0x18);
GG_STATIC_ASSERT(offsetof(Owner_004087F0, field_98) == 0x98);
GG_STATIC_ASSERT(sizeof(Owner_004087F0) == 0xA4);

// LIBRARY: GAMEMD 0x7C8E17 — the allocator (malloc thunk, __cdecl).
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
// FUNCTION: GAMEMD 0x4072C0 — initialise the embedded sub-object.
void FUN_004072C0(void* embedded);

// FUNCTION: GAMEMD 0x4087F0
Owner_004087F0* FUN_004087F0();

#endif  // GG_MATCH_CORE_SLOT_ARRAY_FACTORY_METHODS_H

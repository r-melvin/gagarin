// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x40A260. The block size (0xE0) and the REP STOSD count
//   (`MOV ECX,0x38`) agree.
#ifndef GG_MATCH_CORE_AUX_BLOCK_ATTACH_METHODS_H
#define GG_MATCH_CORE_AUX_BLOCK_ATTACH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Host_0040A260;

// LIBRARY: GAMEMD 0x7C8E17 — the allocator (malloc thunk, __cdecl).
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
// FUNCTION: GAMEMD 0x402800 — store a 32-byte block if it differs.
int FUN_00402800(Host_0040A260* host, const int* incoming);

// The auxiliary block. Its first word is a back-pointer to the host, which is
// how 0x40A260 reaches the host again for the final call.
struct Aux_0040A260
{
    Host_0040A260* Host;   // +0x0000
    char _pad004[0x78];    // +0x0004
    int  field_7C;         // +0x007C
    char _pad080[0x10];    // +0x0080
    int  field_90;         // +0x0090
    char _pad094[0x14];    // +0x0094
    int  field_A8;         // +0x00A8
    char _pad0AC[0x4];     // +0x00AC
    int  field_B0;         // +0x00B0
    char _pad0B4[0x2C];    // +0x00B4
};
GG_STATIC_ASSERT(offsetof(Aux_0040A260, field_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(Aux_0040A260, field_B0) == 0xB0);
GG_STATIC_ASSERT(sizeof(Aux_0040A260) == 0xE0);

struct Host_0040A260
{
    char _pad000[0xAC];    // +0x0000
    char* field_AC;        // +0x00AC  the source block sits 0x44 into this
    char _pad0B0[0xA8];    // +0x00B0
    Aux_0040A260* Aux;     // +0x0158
    char _pad15C[0x4C];    // +0x015C
    int  field_1A8;        // +0x01A8
    int  field_1AC;        // +0x01AC
    int  field_1B0;        // +0x01B0
    int  field_1B4;        // +0x01B4
};
GG_STATIC_ASSERT(offsetof(Host_0040A260, field_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(Host_0040A260, Aux) == 0x158);
GG_STATIC_ASSERT(offsetof(Host_0040A260, field_1A8) == 0x1A8);
GG_STATIC_ASSERT(offsetof(Host_0040A260, field_1B4) == 0x1B4);

// FUNCTION: GAMEMD 0x40A260
int FUN_0040A260(Host_0040A260* self);

#endif  // GG_MATCH_CORE_AUX_BLOCK_ATTACH_METHODS_H

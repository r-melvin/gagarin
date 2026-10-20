// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, globals and call targets read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x404DD0.
#ifndef GG_MATCH_CORE_SMALL_MISC45_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC45_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

// ---------------------------------------------------------------------------
// 0x404DD0 — retire an object: either free it outright or hand it back to the
// pool at 0x87E2A8, then drop the live count at 0x87E28C either way.
//
// Bit 7 of the flag byte at +0x18 is the "heap-allocated" marker, and it is
// tested in place (`TEST AL,0x80` after a byte load). The two paths each carry
// their own copy of the decrement rather than sharing one - retail has two
// separate `DEC EAX` sequences, interleaved differently with the surrounding
// stack adjustment and pop.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x407450 — the pre-teardown step, __fastcall.
void __fastcall FUN_00407450(void* self);
// FUNCTION: GAMEMD 0x407530 — return to the pool, __fastcall (pool in ECX,
// object in EDX).
void __fastcall FUN_00407530(void* pool, void* self);

extern void* DAT_0087E2A8;   // GLOBAL: GAMEMD 0x87E2A8 — the pool
extern int   DAT_0087E28C;   // GLOBAL: GAMEMD 0x87E28C — live count

struct Obj_00404DD0
{
    char _pad000[0x18];
    char Flags;      // +0x0018
    char _pad019[0x138 - 0x19];
    int  Pending;    // +0x0138
};
GG_STATIC_ASSERT(offsetof(Obj_00404DD0, Flags) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_00404DD0, Pending) == 0x138);

// FUNCTION: GAMEMD 0x404DD0
void __fastcall FUN_00404DD0(Obj_00404DD0* self);

// ---------------------------------------------------------------------------
// 0x404D80 — release every slot of the array at +0x28 and reset the count.
//
// The count at +0xA8 is re-read on every pass, so it is the loop condition
// rather than a value captured up front. Both exits clear it, and retail emits
// two copies of that store because ESI is only pushed inside the loop and the
// two epilogues therefore differ.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x401F90 — the per-slot release, __fastcall.
void __fastcall FUN_00401F90(void* item);

struct Obj_00404D80
{
    char  _pad000[0x28];
    void* Slots[(0xA8 - 0x28) / 4];   // +0x0028
    int   Count;                      // +0x00A8
};
GG_STATIC_ASSERT(offsetof(Obj_00404D80, Slots) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_00404D80, Count) == 0xA8);

// FUNCTION: GAMEMD 0x404D80
void __fastcall FUN_00404D80(Obj_00404D80* self);

// ---------------------------------------------------------------------------
// 0x404E20 — first non-empty list in a rectangular table of list headers.
//
// The table at 0x87DE38 is `count` rows of ten headers; the inner stride is
// 0x0C and the outer 0x78, both read straight off the walk. The answer is the
// found node biased back by 0xA4 (`ADD EAX,0xFFFFFF5C`), i.e. the owning object
// whose link member sits at +0xA4. Nothing found gives zero.
//
// Both loops are bottom-tested with their guards peeled, and the outer count is
// spilled to the stack slot the `PUSH ECX` opened rather than kept in a
// register.
// ---------------------------------------------------------------------------
#include "intrusive_list_methods.h"

struct Row_00404E20
{
    ListNode Headers[10];   // 10 x 0x0C = 0x78
};
GG_STATIC_ASSERT(sizeof(Row_00404E20) == 0x78);

// GLOBAL: GAMEMD 0x87DE38 — the table.
extern Row_00404E20 DAT_0087DE38[];

// FUNCTION: GAMEMD 0x404E20
void* __fastcall FUN_00404E20(int rows);

#endif  // GG_MATCH_CORE_SMALL_MISC45_METHODS_H

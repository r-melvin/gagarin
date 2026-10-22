// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, the dispatch slot and the element stride read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x402EF0.
//
// Tear the whole thing down: run every list entry's own teardown, tell the
// registrar at +0x18 to drop this object, clear its slot, floor its count, then
// free the object.
#ifndef GG_MATCH_CORE_LIST_TEARDOWN_METHODS_H
#define GG_MATCH_CORE_LIST_TEARDOWN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

struct Owner_00402EF0;

// FUNCTION: GAMEMD 0x402550 — the per-entry teardown, __fastcall.
void FUN_00402550(ListNode* node);

typedef void (* RegistrarSlot_00402EF0)(Owner_00402EF0*);

struct Registrar_00402EF0
{
    char  _pad000[0xC];
    void* Dispatch;   // +0x000C
    int   Count;      // +0x0010
    char  _pad014[0x1C - 0x14];
    void* Slots[1];   // +0x001C
};
GG_STATIC_ASSERT(offsetof(Registrar_00402EF0, Dispatch) == 0xC);
GG_STATIC_ASSERT(offsetof(Registrar_00402EF0, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(Registrar_00402EF0, Slots) == 0x1C);

struct Owner_00402EF0
{
    char                _pad000[0x18];
    Registrar_00402EF0* Registrar;   // +0x0018
    int                 SlotIndex;   // +0x001C
    char                _pad020[0xF8 - 0x20];
    ListNode            Items;       // +0x00F8
};
GG_STATIC_ASSERT(offsetof(Owner_00402EF0, Registrar) == 0x18);
GG_STATIC_ASSERT(offsetof(Owner_00402EF0, SlotIndex) == 0x1C);
GG_STATIC_ASSERT(offsetof(Owner_00402EF0, Items) == 0xF8);

// FUNCTION: GAMEMD 0x402EF0
void FUN_00402EF0(Owner_00402EF0* self);

// ---------------------------------------------------------------------------
// 0x4033C0 — the same teardown, bracketed by a global busy counter.
//
// The counter at +0x18 of the singleton held at 0x815E98 is raised, an unlink
// step runs, and it is floored straight back down; only then does the list
// sweep and the registrar work happen. The singleton is re-read for every one
// of its four uses.
// ---------------------------------------------------------------------------
struct Busy_004033C0
{
    char _pad000[0x18];
    int  Count;   // +0x0018
};
GG_STATIC_ASSERT(offsetof(Busy_004033C0, Count) == 0x18);

extern Busy_004033C0* DAT_00815E98;   // GLOBAL: GAMEMD 0x815E98

// FUNCTION: GAMEMD 0x407450 — the unlink step, __fastcall.
void FUN_00407450(Owner_00402EF0* self);

// FUNCTION: GAMEMD 0x4033C0
void FUN_004033C0(Owner_00402EF0* self);

#endif  // GG_MATCH_CORE_LIST_TEARDOWN_METHODS_H

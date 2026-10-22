// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, slot displacements and flag masks read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x4025B0, 0x402600 and
//   0x402650. None is bound by YRpp.
//
// Three state transitions on the same object. Each opens by running slot +0x28
// of the dispatch table at +0xD4, then does its own flag work, then runs slot
// +0x2C. The two that end there reach it by `JMP dword ptr [EDX+0x2C]`, a tail
// call through the table.
//
// The table at +0xD4 holds __fastcall entries taking the object: retail loads
// the table pointer and calls through a fixed displacement in it, and the very
// first call needs no `MOV ECX,ESI` because the object is still in ECX from
// entry.
#ifndef GG_MATCH_CORE_DISPATCH_STATE_METHODS_H
#define GG_MATCH_CORE_DISPATCH_STATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004025B0;

typedef void (__fastcall* DispatchSlot_004025B0)(Obj_004025B0*);
typedef long (__fastcall* DispatchResult_004025B0)(Obj_004025B0*);
typedef void (__fastcall* Handler_004025B0)(Obj_004025B0*);

#define DISPATCH_004025B0(o, off) \
    ((*(DispatchSlot_004025B0*)((char*)(o)->Dispatch + (off)))(o))
#define DISPATCH_RESULT_004025B0(o, off) \
    ((*(DispatchResult_004025B0*)((char*)(o)->Dispatch + (off)))(o))

struct Obj_004025B0
{
    char             _pad000[0xC];
    int              Recorded;   // +0x000C
    char             Part[0xA4 - 0x10];   // +0x0010
    int              Flags;      // +0x00A4
    char             _pad0A8[0xBC - 0xA8];
    Handler_004025B0 Handler;    // +0x00BC
    char             _pad0C0[0xD4 - 0xC0];
    void*            Dispatch;   // +0x00D4
    char             _pad0D8[0x168 - 0xD8];
    int              Pending;    // +0x0168

    // These six are members, not free functions taking the object. Retail puts
    // the object in ECX throughout, and 0x402440's recorded value arrives in
    // EDX, which is `__fastcall` on a member (this in ECX, the first explicit
    // argument in EDX, nothing cleaned); a plain __thiscall member would push
    // that value and return `RET 4`, so only 0x402440 keeps __fastcall and the
    // rest are ordinary __thiscall members. Declared ascending by retail
    // address.
    // FUNCTION: GAMEMD 0x402440 — the 0x4025B0 transition with a value
    // recorded at +0x0C on the way in and bit 3 set on the way out.
    void __fastcall FUN_00402440(int value);
    // FUNCTION: GAMEMD 0x402550 — the 0x4025B0 transition followed by
    // teardown: one more step at 0x4028B0, dispatch slot +0x08, and the free.
    void FUN_00402550();
    // FUNCTION: GAMEMD 0x4025B0
    void FUN_004025B0();
    // FUNCTION: GAMEMD 0x402600
    void FUN_00402600();
    // FUNCTION: GAMEMD 0x402650
    void FUN_00402650();
    // FUNCTION: GAMEMD 0x402720 — start: refuse when already running or with
    // nothing pending, otherwise reset, pre-step, and run slots +0x28, +0x0C
    // and +0x2C. A zero result from +0x0C marks the object busy.
    long FUN_00402720();
};
GG_STATIC_ASSERT(offsetof(Obj_004025B0, Recorded) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_004025B0, Flags) == 0xA4);
GG_STATIC_ASSERT(offsetof(Obj_004025B0, Handler) == 0xBC);
GG_STATIC_ASSERT(offsetof(Obj_004025B0, Dispatch) == 0xD4);
GG_STATIC_ASSERT(offsetof(Obj_004025B0, Pending) == 0x168);

// FUNCTION: GAMEMD 0x401080 — resets the sub-object at +0x10, __fastcall.
void __fastcall FUN_00401080(void* part);
// FUNCTION: GAMEMD 0x402220 — the pre-step, __fastcall.
void __fastcall FUN_00402220(Obj_004025B0* self);

// FUNCTION: GAMEMD 0x4028B0 — the extra teardown step 0x402550 runs.
void __fastcall FUN_004028B0(Obj_004025B0* self);
extern "C" void __cdecl FUN_007C8B3D(void* block);

#endif  // GG_MATCH_CORE_DISPATCH_STATE_METHODS_H

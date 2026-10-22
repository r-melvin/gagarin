// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every offset, flag mask and call target below is read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI at the four
//   addresses named. None is bound by YRpp, so the retail
//   placeholder names are kept.
#ifndef GG_MATCH_CORE_SMALL_MISC37_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC37_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x4023F0 — clear three fields, reset a sub-object, then hand off through a
// function-pointer member if one is installed. The hand-off is a real tail
// `JMP EAX`, so the member is a __fastcall function pointer and its result is
// this function's result; with no handler the answer is zero.
// ---------------------------------------------------------------------------
struct Obj_004023F0;
typedef int (* Handler_004023F0)(Obj_004023F0* self);

// FUNCTION: GAMEMD 0x401000 — resets the sub-object at +0x10.
void FUN_00401000(void* sub);

struct Obj_004023F0
{
    char             _pad000[0x10];
    char             Sub[0xA4 - 0x10];   // +0x0010
    // volatile (+0xA4, +0xA8, +0x168): this body is the hook at +0x164 that the
    // mixer thread 0x4095B0 (CreateThread @0x409511) calls @0x40974F; 0x4095B0
    // also tests +0xA4 at 0x409626 and 0x402330 (hook +0x160, @0x409A8B)
    // reads +0x168. The caller's thread writes all three (0x402440, 0x4024A0).
    volatile int     Flags;              // +0x00A4
    volatile int     FlagsHigh;          // +0x00A8
    char             _pad0AC[0xB8 - 0xAC];
    Handler_004023F0 Handler;            // +0x00B8
    char             _pad0BC[0x168 - 0xBC];
    volatile int     Pending;            // +0x0168

    // FUNCTION: GAMEMD 0x4023F0
    int FUN_004023F0();
};
GG_STATIC_ASSERT(offsetof(Obj_004023F0, Flags) == 0xA4);
GG_STATIC_ASSERT(offsetof(Obj_004023F0, FlagsHigh) == 0xA8);
GG_STATIC_ASSERT(offsetof(Obj_004023F0, Handler) == 0xB8);
GG_STATIC_ASSERT(offsetof(Obj_004023F0, Pending) == 0x168);

// ---------------------------------------------------------------------------
// 0x405580 — detach from the owner at +0xB0, but only when that owner still
// names this object as its current one, then raise two flag bits either way.
// ---------------------------------------------------------------------------
struct Obj_00405580;

// FUNCTION: GAMEMD 0x4026A0 / 0x4026B0 — the detach pair, both __fastcall on
// the owner. The second is reached by `JMP`, so it is a free function.
void FUN_004026A0(void* owner);
void FUN_004026B0(void* owner);

struct Owner_00405580
{
    char         _pad000[0xC0];
    Obj_00405580* Current;   // +0x00C0
};
GG_STATIC_ASSERT(offsetof(Owner_00405580, Current) == 0xC0);

struct Obj_00405580
{
    char           _pad000[0x18];
    int            Flags;    // +0x0018
    char           _pad01C[0xB0 - 0x1C];
    Owner_00405580* Owner;   // +0x00B0
};
GG_STATIC_ASSERT(offsetof(Obj_00405580, Flags) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_00405580, Owner) == 0xB0);

// FUNCTION: GAMEMD 0x405580
void FUN_00405580(Obj_00405580* self);

// ---------------------------------------------------------------------------
// 0x406550 — run two resets over the sub-object at +0x18, the second by tail
// call.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x407150 / 0x4071C0
void FUN_00407150(void* sub);
void FUN_004071C0(void* sub);

struct Obj_00406550
{
    char _pad000[0x18];
    char Sub[0x4];   // +0x0018
};

// FUNCTION: GAMEMD 0x406550
void FUN_00406550(Obj_00406550* self);

#endif  // GG_MATCH_CORE_SMALL_MISC37_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, slots, table bases and constants read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x4067D0, 0x413CD0 and
//   0x452170.
#ifndef GG_MATCH_CORE_SMALL_MISC41_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC41_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);

// ---------------------------------------------------------------------------
// 0x4067D0 — look a name up in the null-terminated table at 0x816018 and
// optionally hand back its value.
//
// The table runs until an entry with a null name, and the walk stops either on
// a match or on that terminator - so the same pointer serves both outcomes, and
// the answer is simply whether the entry it stopped on has a name. The value is
// written through the second argument only when one was supplied.
// ---------------------------------------------------------------------------
struct NameValue_004067D0
{
    const char* Name;    // +0x0000
    int         Value;   // +0x0004
};

// GLOBAL: GAMEMD 0x816018 — the table, terminated by a null name.
extern NameValue_004067D0 DAT_00816018[];

// GLOBAL: GAMEMD 0x8160C0 — the second table, same layout and terminator.
extern NameValue_004067D0 DAT_008160C0[];

// FUNCTION: GAMEMD 0x4067D0
bool __fastcall FUN_004067D0(const char* name, int* value);

// FUNCTION: GAMEMD 0x406820 — the same walk over 0x8160C0, but the value is
// OR-ed into the destination rather than assigned, and the two register
// arguments arrive the other way round (`MOV EBX,ECX` takes the destination,
// `MOV EDI,EDX` the name).
bool __fastcall FUN_00406820(int* flags, const char* name);

// GLOBAL: GAMEMD 0x816048 — the third table, same layout and terminator.
extern NameValue_004067D0 DAT_00816048[];

// FUNCTION: GAMEMD 0x406870 — the same walk over 0x816048, with the found value
// treated as a set of mutually exclusive flag groups: bits 5-6 and bits 10-11
// each displace whatever was already there before the OR. The masks come
// straight off the byte-narrowed ANDs, `AND AL,0x9F` for 0x60 and
// `AND AH,0xF3` for 0xC00.
bool __fastcall FUN_00406870(int* flags, const char* name);

// ---------------------------------------------------------------------------
// 0x413CD0 — a type-checked predicate.
//
// `SUB EAX,0xF; NEG EAX; SBB EAX,EAX; NOT EAX; AND EAX,ESI` is the branchless
// form of `(WhatAmI() == 15) ? this : 0`, which is what a conditional
// expression compiles to here rather than a branch.
// ---------------------------------------------------------------------------
struct Sub_00413CD0
{
    char _pad000[0xEC1];
    char Enabled;   // +0x0EC1
};
GG_STATIC_ASSERT(offsetof(Sub_00413CD0, Enabled) == 0xEC1);

struct Obj_00413CD0
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020();
    virtual void vt_024();
    virtual void vt_028();
    virtual int WhatAmI();              // +0x002C

    char           _pad004[0x6C0 - 0x04];
    Sub_00413CD0*  Settings;   // +0x06C0
    char           _pad6C4[0x6D9 - 0x6C4];
    char           Suppressed; // +0x06D9
};
GG_STATIC_ASSERT(offsetof(Obj_00413CD0, Settings) == 0x6C0);
GG_STATIC_ASSERT(offsetof(Obj_00413CD0, Suppressed) == 0x6D9);

// FUNCTION: GAMEMD 0x413CD0
bool __fastcall FUN_00413CD0(Obj_00413CD0* self);

// ---------------------------------------------------------------------------
// 0x452170 — stamp a byte into all 21 slots of the array at +0x55C.
//
// The stamped value is the argument, except that the specific value 15 is
// remapped to 16 when slot +0x68 answers 5. `MOV [EAX+0x178],BL` stores the low
// byte, so the destination field is a byte even though the argument is a word.
// ---------------------------------------------------------------------------
struct Slot_00452170
{
    char _pad000[0x178];
    char Stamp;   // +0x0178
};
GG_STATIC_ASSERT(offsetof(Slot_00452170, Stamp) == 0x178);

struct Obj_00452170
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020();
    virtual void vt_024();
    virtual void vt_028();
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual int vt_068(int a, int b);   // +0x0068

    char           _pad004[0x55C - 0x04];
    Slot_00452170* Slots[0x15];   // +0x055C

    // FUNCTION: GAMEMD 0x452170
    void FUN_00452170(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00452170, Slots) == 0x55C);

#endif  // GG_MATCH_CORE_SMALL_MISC41_METHODS_H

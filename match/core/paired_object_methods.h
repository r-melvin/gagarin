// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x402190 and 0x404140. The two objects are the same
//   type: 0x402190 initialises +0xB0..+0xC0 on itself and 0x404140 clears the
//   same fields through the +0xB0 pointer, so that pointer names a peer.
#ifndef GG_MATCH_CORE_PAIRED_OBJECT_METHODS_H
#define GG_MATCH_CORE_PAIRED_OBJECT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "triple_timer_init_methods.h"

struct Obj_00402190;

// The three slots at +0x15C..+0x164 are filled with the addresses of three
// concrete functions rather than pointing at a shared vtable, so they are
// per-instance hooks, not virtuals.
typedef int (__fastcall* Hook_00402190)(Obj_00402190* self);

// FUNCTION: GAMEMD 0x4022C0
int __fastcall FUN_004022C0(Obj_00402190* self);
// FUNCTION: GAMEMD 0x4023F0
int __fastcall FUN_004023F0(Obj_00402190* self);
// FUNCTION: GAMEMD 0x4025B0
void __fastcall FUN_004025B0(Obj_00402190* peer);
// FUNCTION: GAMEMD 0x4026F0
void __fastcall FUN_004026F0(Obj_00402190* peer);

// FUNCTION: GAMEMD 0x402330 — one of the three hooks, so a free function by
// necessity (see the note on Obj_00402190's members below).
int __fastcall FUN_00402330(Obj_00402190* self);

// GLOBAL: GAMEMD 0x87DE30 — a timer group, not a scalar: 0x402220 passes the
// value stored from here straight to 0x4010C0 as the scaling source.
extern Obj_00401000* DAT_0087DE30;

// The context hanging off +0xAC. Only the two members 0x402220 reads are
// modelled; the rest is P2.
struct Ctx_00402220
{
    char _pad000[0x68];       // +0x0000
    Obj_00401000 Timers;      // +0x0068
    char _pad0E0[0x8];        // +0x00E0
    Obj_00401000* At_E8;      // +0x00E8
};
GG_STATIC_ASSERT(offsetof(Ctx_00402220, Timers) == 0x68);
GG_STATIC_ASSERT(offsetof(Ctx_00402220, At_E8) == 0xE8);

// The queue entry hanging off +0x168, and the record 0x408520 resolves it to.
struct Item_00402330
{
    int At_00;                // +0x0000  cleared once the record is taken
    int At_04;                // +0x0004
};
struct Rec_00402330
{
    char _pad000[0xC];        // +0x0000
    int  At_0C;               // +0x000C
    int  At_10;               // +0x0010
};
GG_STATIC_ASSERT(offsetof(Rec_00402330, At_0C) == 0xC);

// FUNCTION: GAMEMD 0x408520 — resolve a queue entry to its record, or null.
Rec_00402330* __fastcall FUN_00408520(Item_00402330* item);

struct Obj_00402190
{
    char _pad000[0xC];             // +0x0000
    int  field_0C;                 // +0x000C  set to 1
    Obj_00401000 TimersA;          // +0x0010
    char _pad088[0x8];             // +0x0088
    Obj_00401000* field_90;        // +0x0090
    Obj_00401000* field_94;        // +0x0094  seeded from DAT_0087DE30
    Obj_00401000* field_98;        // +0x0098
    Obj_00401000* field_9C;        // +0x009C
    int  field_A0;                 // +0x00A0
    int  field_A4;                 // +0x00A4
    int  field_A8;                 // +0x00A8  countdown, -1 = forever
    Ctx_00402220* Context;         // +0x00AC
    Obj_00402190* Peer;            // +0x00B0
    Hook_00402190 Hook_B4;         // +0x00B4  optional per-instance callback
    int  field_B8;                 // +0x00B8
    int  field_BC;                 // +0x00BC
    Obj_00402190* PeerBackRef;     // +0x00C0
    char _pad0C4[0x10];            // +0x00C4
    Hook_00402190* VTable_D4;      // +0x00D4  dispatch table, slot 9 at +0x24
    Obj_00401000 TimersB;          // +0x00D8
    char _pad150[0xC];             // +0x0150
    Hook_00402190 Hook15C;         // +0x015C
    Hook_00402190 Hook160;         // +0x0160
    Hook_00402190 Hook164;         // +0x0164
    Item_00402330* Current;        // +0x0168
    Rec_00402330* field_16C;       // +0x016C
    int  field_170;                // +0x0170
    int  field_174;                // +0x0174
    int  field_178;                // +0x0178

    // These five are members, not free functions taking the object: the
    // object is the only register argument, so they are ordinary __thiscall.
    // 0x402330 is deliberately NOT among them: its address is stored into the
    // +0x160 hook slot, whose type is a plain `int (__fastcall*)(Obj*)`. A
    // non-static member's address is a pointer-to-member and will not go
    // there, so retail's own source cannot have declared it as one — the free
    // spelling is the recovery, not a shortcut. The same argument covers the
    // sibling hooks 0x4022C0 and 0x4023F0, which live in other TUs.
    // Declared ascending by retail address.
    // FUNCTION: GAMEMD 0x402190
    void FUN_00402190();
    // FUNCTION: GAMEMD 0x402220
    void FUN_00402220();
    // FUNCTION: GAMEMD 0x4024A0
    void FUN_004024A0();
    // FUNCTION: GAMEMD 0x404140
    void FUN_00404140();
};
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_94) == 0x94);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_98) == 0x98);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_A4) == 0xA4);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_A8) == 0xA8);
GG_STATIC_ASSERT(offsetof(Obj_00402190, Context) == 0xAC);
GG_STATIC_ASSERT(offsetof(Obj_00402190, Hook_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_BC) == 0xBC);
GG_STATIC_ASSERT(offsetof(Obj_00402190, Hook160) == 0x160);
GG_STATIC_ASSERT(offsetof(Obj_00402190, Hook164) == 0x164);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_16C) == 0x16C);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_170) == 0x170);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_174) == 0x174);
GG_STATIC_ASSERT(offsetof(Obj_00402190, TimersA) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Obj_00402190, Peer) == 0xB0);
GG_STATIC_ASSERT(offsetof(Obj_00402190, PeerBackRef) == 0xC0);
GG_STATIC_ASSERT(offsetof(Obj_00402190, TimersB) == 0xD8);
GG_STATIC_ASSERT(offsetof(Obj_00402190, Hook15C) == 0x15C);
GG_STATIC_ASSERT(offsetof(Obj_00402190, VTable_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(Obj_00402190, Current) == 0x168);
GG_STATIC_ASSERT(offsetof(Obj_00402190, field_178) == 0x178);


#endif  // GG_MATCH_CORE_PAIRED_OBJECT_METHODS_H

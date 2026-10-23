// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x40A6D0. The two scalings are (x >> 16) * 100 >> 14 and
//   (x >> 16) * 200 >> 14 — retail builds both multiplies out of LEA chains — and
//   the second is biased by 0x64 so it straddles zero.
#ifndef GG_MATCH_AUDIO_PAN_AND_PITCH_METHODS_H
#define GG_MATCH_AUDIO_PAN_AND_PITCH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/triple_timer_init_methods.h"
#include "audio_sample_methods.h"

// GLOBAL: GAMEMD 0x816380 — the volume curve.
extern int DAT_00816380[];
// GLOBAL: GAMEMD 0x816510 — the pan curve, indexed either side of its base.
extern int DAT_00816510[];

struct Sink_0040A6D0;

// Only the prefixes accessed by this function are modeled; full object and
// vtable sizes have not been recovered. Slot displacements come from
// CALL [EDX+0x3C/0x40/0x44] at 0x40A6FD, 0x40A728 and 0x40A761.
struct SinkVtbl_0040A6D0
{
    char unknown_00[8];
    unsigned long (__stdcall* At_08)(Sink_0040A6D0*);
    void* unknown_0C;
    int (__stdcall* At_10)(Sink_0040A6D0*, unsigned*, unsigned*);
    char unknown_14[0x10];
    int (__stdcall* At_24)(Sink_0040A6D0*, unsigned*);
    void* unknown_28;
    int (__stdcall* At_2C)(Sink_0040A6D0*, unsigned, unsigned, void**, unsigned*, void**, unsigned*, unsigned);
    int (__stdcall* At_30)(Sink_0040A6D0*, int, int, unsigned);
    int (__stdcall* At_34)(Sink_0040A6D0*, unsigned);
    int (__stdcall* At_38)(Sink_0040A6D0*, const void*);                           // +0x0000
    int (__stdcall* At_3C)(Sink_0040A6D0*, int volume); // +0x003C
    int (__stdcall* At_40)(Sink_0040A6D0*, int pan);    // +0x0040
    int (__stdcall* At_44)(Sink_0040A6D0*, int rate);
    int (__stdcall* At_48)(Sink_0040A6D0*);
    int (__stdcall* At_4C)(Sink_0040A6D0*, void*, unsigned, void*, unsigned);
    int (__stdcall* At_50)(Sink_0040A6D0*);   // +0x0044
};
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_10) == 0x10);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_34) == 0x34);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_38) == 0x38);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_50) == 0x50);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_08) == 8);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_24) == 0x24);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_30) == 0x30);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_48) == 0x48);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_40) == 0x40);
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_44) == 0x44);

struct Sink_0040A6D0 { SinkVtbl_0040A6D0* Vptr; };
GG_STATIC_ASSERT(offsetof(Sink_0040A6D0, Vptr) == 0x0);

struct Voice_0040A6D0;
typedef Voice_0040A6D0 Settings_0040A6D0;
struct Pool_00402860;
struct Format_0040A340
{
    char unknown_00[0x14];
    AudioSampleData* unknown_14;
};
GG_STATIC_ASSERT(offsetof(Format_0040A340, unknown_14) == 0x14);
GG_STATIC_ASSERT(sizeof(Format_0040A340) == 0x18);

struct State_0040ACD0 { int unknown_00; int unknown_04; };
GG_STATIC_ASSERT(offsetof(State_0040ACD0, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(State_0040ACD0, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(State_0040ACD0) == 8);

struct Aux_0040A6D0
{
    Settings_0040A6D0* Settings;   // +0x0000
    unsigned unknown_04;
    int unknown_08;
    int unknown_0C;
    __int64 unknown_10;
    __int64 unknown_18;
    unsigned char* unknown_20;
    int unknown_24;
    unsigned char* unknown_28;
    int unknown_2C;
    unsigned unknown_30;
    unsigned unknown_34;
    int unknown_38;
    int unknown_3C;
    unsigned unknown_40;
    AudioSampleData unknown_44;
    Sink_0040A6D0* Sink;           // +0x0064
    int unknown_68;
    int unknown_6C;
    int (__fastcall* unknown_70)(void*, void*, int*, const void*, int*);
    unsigned unknown_74;
    unsigned unknown_78;
    unsigned char* unknown_7C;
    unsigned unknown_80;
    unsigned unknown_84;
    unsigned unknown_88;
    unsigned unknown_8C;
    unsigned char* unknown_90;
    unsigned unknown_94;
    unsigned unknown_98;
    unsigned unknown_9C;
    unsigned unknown_A0;
    int unknown_A4;
    int unknown_A8;
    unsigned unknown_AC;
    int (__fastcall* unknown_B0)(Aux_0040A6D0*);
    State_0040ACD0 unknown_B4[2];
    char unknown_C4[8];
    int unknown_CC;
    int unknown_D0;
    int unknown_D4;
    unsigned unknown_D8;
    unsigned unknown_DC;
};
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, Settings) == 0x0);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_CC) == 0xCC);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_D0) == 0xD0);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_D8) == 0xD8);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_DC) == 0xDC);
GG_STATIC_ASSERT(sizeof(Aux_0040A6D0) == 0xE0);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, Sink) == 0x64);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_74) == 0x74);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_78) == 0x78);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_84) == 0x84);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_88) == 0x88);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_8C) == 0x8C);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_94) == 0x94);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_A4) == 0xA4);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_A8) == 0xA8);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, unknown_B4) == 0xB4);


// The two values driving volume and pan are not separate members: 0xDC and 0x12C
// are the First and Third timers' 16.16 values inside the group at +0xD8
// (0xD8 + 4 and 0xD8 + 0x54). That is what makes them continuous parameters
// rather than settings.
struct Voice_0040A6D0
{
    char unknown_00[0xA4];
    unsigned unknown_A4;
    int unknown_A8;
    Pool_00402860* unknown_AC;
    char unknown_B0[0x28];
    Obj_00401000 Timers;           // +0x00D8 .. +0x0150
    char unknown_150[0x8];        // +0x0150
    Aux_0040A6D0* Aux;             // +0x0158
    void (__fastcall* unknown_15C)(Voice_0040A6D0*);
    void (__fastcall* unknown_160)(Voice_0040A6D0*);
    void (__fastcall* unknown_164)(Voice_0040A6D0*);
    Format_0040A340* unknown_168;
    int unknown_16C;
    unsigned char* unknown_170;
    int unknown_174;
    int unknown_178;
    int unknown_17C;
    int unknown_180;
    int At_184;
    int unknown_188;
    int unknown_18C;
    char unknown_190[0x10];
    int unknown_1A0;
    int unknown_1A4;
    unsigned __int64 unknown_1A8;
    unsigned __int64 unknown_1B0;
    // FUNCTION: GAMEMD 0x402800 (decl; reloc)
    void __fastcall FUN_00402800(const AudioSampleData*);
    // FUNCTION: GAMEMD 0x40A340
    int FUN_0040A340();

    // FUNCTION: GAMEMD 0x40A2D0
    int FUN_0040A2D0();
    // FUNCTION: GAMEMD 0x40A650
    int FUN_0040A650();
    // FUNCTION: GAMEMD 0x40A670
    int FUN_0040A670();
    // FUNCTION: GAMEMD 0x40A6A0
    int FUN_0040A6A0();
    // FUNCTION: GAMEMD 0x40A6D0
    int FUN_0040A6D0();
};
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_A4) == 0xA4);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_15C) == 0x15C);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_160) == 0x160);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_164) == 0x164);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_168) == 0x168);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_170) == 0x170);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_174) == 0x174);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, At_184) == 0x184);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_18C) == 0x18C);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_1A0) == 0x1A0);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_1A8) == 0x1A8);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, unknown_1B0) == 0x1B0);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, Timers) == 0xD8);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, Aux) == 0x158);
// Pin the complete displacement of each value load, not just the timer group.
// 0x40A6D4 reads +0xDC; 0x40A700 reads +0x12C.
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, Timers)
    + offsetof(Obj_00401000, First) + offsetof(Timer_00401000, Value) == 0xDC);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, Timers)
    + offsetof(Obj_00401000, Third) + offsetof(Timer_00401000, Value) == 0x12C);

#endif  // GG_MATCH_AUDIO_PAN_AND_PITCH_METHODS_H

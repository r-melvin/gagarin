// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x40A6D0. The two scalings are (x >> 16) * 100 >> 14 and
//   (x >> 16) * 200 >> 14 — retail builds both multiplies out of LEA chains — and
//   the second is biased by 0x64 so it straddles zero.
#ifndef GG_MATCH_AUDIO_PAN_AND_PITCH_METHODS_H
#define GG_MATCH_AUDIO_PAN_AND_PITCH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../core/triple_timer_init_methods.h"

// GLOBAL: GAMEMD 0x816380 — the volume curve.
extern int DAT_00816380[];
// GLOBAL: GAMEMD 0x816510 — the pan curve, indexed either side of its base.
extern int DAT_00816510[];

struct Sink_0040A6D0;

struct SinkVtbl_0040A6D0
{
    char _pad000[0x3C];                                 // +0x0000
    int (__stdcall* At_3C)(Sink_0040A6D0*, int volume); // +0x003C
    int (__stdcall* At_40)(Sink_0040A6D0*, int pan);    // +0x0040
    int (__stdcall* At_44)(Sink_0040A6D0*, int rate);   // +0x0044
};
GG_STATIC_ASSERT(offsetof(SinkVtbl_0040A6D0, At_44) == 0x44);

struct Sink_0040A6D0 { SinkVtbl_0040A6D0* Vptr; };

struct Settings_0040A6D0
{
    char _pad000[0x184];      // +0x0000
    int  At_184;              // +0x0184
};
GG_STATIC_ASSERT(offsetof(Settings_0040A6D0, At_184) == 0x184);

struct Aux_0040A6D0
{
    Settings_0040A6D0* Settings;   // +0x0000
    char _pad004[0x60];            // +0x0004
    Sink_0040A6D0* Sink;           // +0x0064
};
GG_STATIC_ASSERT(offsetof(Aux_0040A6D0, Sink) == 0x64);

// The two values driving volume and pan are not separate members: 0xDC and 0x12C
// are the First and Third timers' 16.16 values inside the group at +0xD8
// (0xD8 + 4 and 0xD8 + 0x54). That is what makes them continuous parameters
// rather than settings.
struct Voice_0040A6D0
{
    char _pad000[0xD8];            // +0x0000
    Obj_00401000 Timers;           // +0x00D8 .. +0x0150
    char _pad150[0x8];             // +0x0150
    Aux_0040A6D0* Aux;             // +0x0158

    // FUNCTION: GAMEMD 0x40A6D0
    int FUN_0040A6D0();
};
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, Timers) == 0xD8);
GG_STATIC_ASSERT(offsetof(Voice_0040A6D0, Aux) == 0x158);

#endif  // GG_MATCH_AUDIO_PAN_AND_PITCH_METHODS_H

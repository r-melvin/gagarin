// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entry points and globals confirmed from retail 0x409FF0..0x40A7B5.
//   The IAT at 0x7E11E8/0x7E11EC identifies the WinAPI critical-section calls.
//   This is audio code despite the legacy neighbouring "surface" model:
//   0x409488 passes &DAT_0087E89C to thunk 0x7C89DA, which jumps through
//   IAT 0x7E1050 (the retail PE imports ordinal 1 from DSOUND.dll).
#ifndef GG_MATCH_AUDIO_DSOUND_ACCESS_METHODS_H
#define GG_MATCH_AUDIO_DSOUND_ACCESS_METHODS_H

#include <stddef.h>
#include <windows.h>
#include "../_rt/gg_static_assert.h"

// Opaque here: the getter returns this sound-buffer interface without reading
// any of its members. Other reconstructed modules still use a legacy name.
struct SoundBuffer_0040A7B0;
// GLOBAL: GAMEMD 0x87E8A0
extern SoundBuffer_0040A7B0* DAT_0087E8A0;

// GLOBAL: GAMEMD 0x87E880
extern CRITICAL_SECTION DAT_0087E880;

// Prefixes accessed by 0x409FF0: MOV ECX,[EAX]; CALL [ECX+8].
// Only the known prefix is modeled; full interface/table extent is unknown.
struct DirectSoundResource_00409FF0;
struct DirectSoundResourceVtbl_00409FF0
{
    char unknown_00[8];
    unsigned long (__stdcall* Release)(DirectSoundResource_00409FF0*);
};
struct DirectSoundResource_00409FF0 { DirectSoundResourceVtbl_00409FF0* Vptr; };
GG_STATIC_ASSERT(offsetof(DirectSoundResource_00409FF0, Vptr) == 0);
GG_STATIC_ASSERT(offsetof(DirectSoundResourceVtbl_00409FF0, Release) == 8);

// GLOBAL: GAMEMD 0x87E89C
extern DirectSoundResource_00409FF0* DAT_0087E89C;
// GLOBAL: GAMEMD 0x87E898
extern int DAT_0087E898;
// GLOBAL: GAMEMD 0x87E878
extern volatile int DAT_0087E878;
// GLOBAL: GAMEMD 0x87E850
extern int DAT_0087E850;
// GLOBAL: GAMEMD 0x87E858
extern volatile int DAT_0087E858;
// GLOBAL: GAMEMD 0x87E86C
extern HANDLE DAT_0087E86C;

// FUNCTION: GAMEMD 0x409FF0
void __cdecl FUN_00409FF0();

// FUNCTION: GAMEMD 0x40A770
int __cdecl FUN_0040A770();
// FUNCTION: GAMEMD 0x40A780
int __cdecl FUN_0040A780();
// FUNCTION: GAMEMD 0x40A790
int __cdecl FUN_0040A790();
// FUNCTION: GAMEMD 0x40A7B0
SoundBuffer_0040A7B0* __cdecl FUN_0040A7B0();

#endif // GG_MATCH_AUDIO_DSOUND_ACCESS_METHODS_H

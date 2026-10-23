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
    int (__stdcall* CreateBuffer)(DirectSoundResource_00409FF0*, const void*, SoundBuffer_0040A7B0**, void*);
    int (__stdcall* GetCaps)(DirectSoundResource_00409FF0*, void*);
    void* unknown_14;
    int (__stdcall* SetCooperativeLevel)(DirectSoundResource_00409FF0*, HWND, unsigned);
};
struct DirectSoundResource_00409FF0 { DirectSoundResourceVtbl_00409FF0* Vptr; };
GG_STATIC_ASSERT(offsetof(DirectSoundResource_00409FF0, Vptr) == 0);
GG_STATIC_ASSERT(offsetof(DirectSoundResourceVtbl_00409FF0, Release) == 8);
GG_STATIC_ASSERT(offsetof(DirectSoundResourceVtbl_00409FF0, CreateBuffer) == 0xC);
GG_STATIC_ASSERT(offsetof(DirectSoundResourceVtbl_00409FF0, GetCaps) == 0x10);
GG_STATIC_ASSERT(offsetof(DirectSoundResourceVtbl_00409FF0, SetCooperativeLevel) == 0x18);

// GLOBAL: GAMEMD 0x87E89C
extern DirectSoundResource_00409FF0* DAT_0087E89C;
// GLOBAL: GAMEMD 0x87E898
extern int DAT_0087E898;
// GLOBAL: GAMEMD 0x87E878
extern int DAT_0087E878;  // reference count; main thread only (0x409470, 0x409FF0)
struct Pool_00402860;
struct BackendState_004095B0
{
    // Thread4095B0 created409511 reads stop at4095C8/409848;
    // owner409FF0 writes stop at40A034. Completion is written4095C1/409855/409868,
    // read by owner40A03E/40A047. The declarations alone are volatile.
    volatile int unknown_00;
    int unknown_04;
    volatile int unknown_08;
    int unknown_0C;
    unsigned unknown_10;
    unsigned unknown_14;
    int unknown_18;
    int unknown_1C;
    Pool_00402860* unknown_20;
};
GG_STATIC_ASSERT(offsetof(BackendState_004095B0, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(BackendState_004095B0, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(BackendState_004095B0, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(BackendState_004095B0, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(BackendState_004095B0, unknown_20) == 0x20);
GG_STATIC_ASSERT(sizeof(BackendState_004095B0) == 0x24);
// GLOBAL: GAMEMD 0x87E850
extern BackendState_004095B0 DAT_0087E850;
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

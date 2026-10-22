// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x750920: the enable flag `MOV AL,[0x8464AC]`; the
//   voc table's Items `[0xB1D37C]` and Count `[0xB1D388]` (index in ECX,
//   `MOV ECX,[EAX+ECX*4]; MOV EBX,[ECX]` = the entry's +0x00 event); the
//   controller argument at `[ESP+0x8]` and the float volume at `[ESP+0x4]`
//   (scaled by the 16384.0f literal at 0x7EF38C and clamped to 0x4000
//   unsigned); the pan argument arrives in EDX and is spilled to the one
//   local. Callee conventions from their own entry points: 0x406130
//   __thiscall(controller), 0x406310 / 0x4052F0 / 0x405190 / 0x4061D0 /
//   0x406270 / 0x4060F0 __fastcall. Names from YRpp
//   (names only, no text copied).
#ifndef GG_MATCH_AUDIO_VOC_CLASS_PLAY_GLOBAL_METHODS_H
#define GG_MATCH_AUDIO_VOC_CLASS_PLAY_GLOBAL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// The audio-event descriptor a voc entry owns at +0x00; only handled by
// pointer here.
struct AudioEvent_00750920;

// The live sample handle returned by the player; opaque here.
struct AudioHandle_00750920;

// Element of VocClass::Array: the event descriptor sits at +0x00.
struct VocItem_00750920
{
    AudioEvent_00750920* Event;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(VocItem_00750920, Event) == 0x00);

// The per-object handle onto a live audio event (AudioController).
struct AudioController_00750920
{
    // FUNCTION: GAMEMD 0x406130 (decl; reloc) -- the live handle, if any.
    AudioHandle_00750920* GetEvent();
};

// FUNCTION: GAMEMD 0x406310 (decl; reloc) -- the event a handle is playing.
AudioEvent_00750920* __fastcall FUN_00406310(AudioHandle_00750920* handle);
// FUNCTION: GAMEMD 0x4052F0 (decl; reloc) -- stop a handle.
void __fastcall FUN_004052F0(AudioHandle_00750920* handle);
// FUNCTION: GAMEMD 0x405190 (decl; reloc) -- start a new handle for an event.
AudioHandle_00750920* __fastcall FUN_00405190(AudioEvent_00750920* event);
// FUNCTION: GAMEMD 0x4061D0 (decl; reloc) -- AdjustAudioEventVolume.
void __fastcall FUN_004061D0(AudioHandle_00750920* handle, unsigned int volume);
// FUNCTION: GAMEMD 0x406270 (decl; reloc) -- AdjustAudioEventPanning.
void __fastcall FUN_00406270(AudioHandle_00750920* handle, unsigned int pan);
// FUNCTION: GAMEMD 0x4060F0 (decl; reloc) -- AudioController::SetEvent.
void __fastcall FUN_004060F0(AudioController_00750920* controller,
                             AudioHandle_00750920* handle,
                             AudioEvent_00750920* event);

// GLOBAL: GAMEMD 0x8464AC -- VocClass::VoicesEnabled.
extern char DAT_008464AC;

struct VocClass
{
    // GLOBAL: GAMEMD 0xB1D378 -- VocClass::Array (Items 0xB1D37C, Count 0xB1D388).
    static DynamicVectorClassLayout Array;

    // FUNCTION: GAMEMD 0x750920
    // The pan is declared after the volume: callers issue the EDX load
    // between the volume push and the controller push (0x50C8C0, 0x458200),
    // which is cl's right-to-left order for this declaration. The volume
    // still travels on the stack, so the body compiles the same either way.
    static AudioHandle_00750920* __fastcall PlayGlobal(
        int index, float volume, unsigned int pan,
        AudioController_00750920* controller);
};

#endif  // GG_MATCH_AUDIO_VOC_CLASS_PLAY_GLOBAL_METHODS_H

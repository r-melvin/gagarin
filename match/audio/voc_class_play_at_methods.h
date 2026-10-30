// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x7509E0: the enable flag `MOV AL,[0x8464AC]`; the
//   voc table's Items `[0xB1D37C]` and Count `[0xB1D388]` (index in ECX,
//   `MOV ECX,[EAX+ECX*4]; MOV EDI,[ECX]` = the entry's +0x00 event); the
//   coordinates in EDX (kept in EBX for the positional volume helper
//   0x750AC0, __fastcall coords, int* pan-out, event -> float in ST0), the
//   controller at `[ESP+0x14]`; the returned volume is compared against the
//   float 0.0 at 0x7E1748 (`FCOM; FNSTSW; TEST AH,0x41`), scaled by the
//   16384.0f literal at 0x7EF38C and clamped to 0x4000 unsigned; the pan the
//   helper wrote is reloaded from the controller argument's home slot
//   (`MOV EDX,[ESP+0x14]`), which is the parameter-slot reuse of a plain int
//   local. Callee conventions from their own entry points: 0x406130
//   __thiscall(controller), 0x406310 / 0x4052F0 / 0x405190 / 0x4061D0 /
//   0x406270 / 0x4060F0 __fastcall. Names from YRpp
//   (names only, no text copied). The non-positional twin,
//   PlayGlobal 0x750920, is matched in match/audio/voc_class_play_global_methods.
#ifndef GG_MATCH_AUDIO_VOC_CLASS_PLAY_AT_METHODS_H
#define GG_MATCH_AUDIO_VOC_CLASS_PLAY_AT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/voc_class.h"

#include "../_layout/coord_struct.h"
GG_STATIC_ASSERT(offsetof(CoordStruct, Z) == 0x8);
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

// The audio-event descriptor a voc entry owns at +0x00; only handled by
// pointer here.
// FUNCTION: GAMEMD 0x405190 (decl; reloc) -- start a new event for a descriptor.
AudioEvent* FUN_00405190(AudioEventType* type);
// FUNCTION: GAMEMD 0x4052F0 (decl; reloc) -- stop an event.
void FUN_004052F0(AudioEvent* event);
// FUNCTION: GAMEMD 0x750AC0 (decl; reloc) -- positional volume (float in ST0) and pan for a descriptor.
float FUN_00750AC0(CoordStruct* coords, int* pan, AudioEventType* type);

// GLOBAL: GAMEMD 0x8464AC -- VocClass::VoicesEnabled.
extern char DAT_008464AC;

#endif  // GG_MATCH_AUDIO_VOC_CLASS_PLAY_AT_METHODS_H

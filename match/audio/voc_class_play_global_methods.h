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
#include "../_layout/voc_class.h"

// FUNCTION: GAMEMD 0x405190 (decl; reloc) -- start a new event for a descriptor.
AudioEvent* FUN_00405190(AudioEventType* type);
// FUNCTION: GAMEMD 0x4052F0 (decl; reloc) -- stop an event.
void FUN_004052F0(AudioEvent* event);

// GLOBAL: GAMEMD 0x8464AC -- VocClass::VoicesEnabled.
extern char DAT_008464AC;

#endif  // GG_MATCH_AUDIO_VOC_CLASS_PLAY_GLOBAL_METHODS_H

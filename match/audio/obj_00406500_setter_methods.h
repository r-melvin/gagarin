// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x406520 / 0x406530 / 0x406540 / 0x4065C0 / 0x4065D0 /
//   0x4065E0 / 0x406640. No YRpp binding covers any of them.
//
// A family of one-instruction field setters clustered at 0x4065xx, all on the
// same object. Nothing names the type, so both it and the seven entry points
// keep Ghidra placeholder names and the fields are `unknown_XX` — a legitimate
// layout primitive here, not a gap to be filled by guesswork.
//
// Calling convention: `MOV [ECX+off],EDX; RET` with no stack adjustment. The
// value arrives in EDX, which __thiscall never does — that is __fastcall, with
// the object in ECX and the value in EDX.
#ifndef GG_MATCH_AUDIO_OBJ_00406500_SETTER_METHODS_H
#define GG_MATCH_AUDIO_OBJ_00406500_SETTER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/audio_event_type.h"



#endif  // GG_MATCH_AUDIO_OBJ_00406500_SETTER_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and vtable slots read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x69BAB0:
//     `MOV AL,[ECX+0x30D8]` / `MOV byte ptr [ECX+0x30D8],1`   (InGameFrameActive)
//     `CMP dword ptr [ECX],0`                                 (GameMode, +0x00)
//     `MOV ECX,[0xA8B230]; MOV AL,[ECX+0x35A2]`               (provider flag)
//     `MOV ECX,[0x887640]; MOV EAX,[ECX]; CALL [EAX+0x1C]`    (mouse slot 7)
//     `MOV ECX,[0x887640]; MOV EDX,[ECX]; CALL [EDX+0x18]`    (mouse slot 6)
//     `MOV ECX,[0x87E758]; MOV EDX,0x4000; JMP 0x407150`      (__fastcall tail)
//   YRpp names only: SessionClass::Resume @0x69BAB0,
//   InGameFrameActive @+0x30D8, Unsorted::IsActive @0xA8E9A0,
//   GameOptionsClass::Instance @0xA8EB60, WWMouseClass::Instance @0x887640,
//   Unsorted::CurrentFrame @0xA8ED84.
#ifndef GG_MATCH_NETWORK_SESSION_CLASS_RESUME_METHODS_H
#define GG_MATCH_NETWORK_SESSION_CLASS_RESUME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// GLOBAL: GAMEMD 0xA8E9A0 — Unsorted::IsActive (byte).
extern char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0x83ED20 — the game speed saved across a pause (-1 = none).
extern int DAT_0083ED20;
// GLOBAL: GAMEMD 0xA8EB60 — GameOptionsClass::Instance; first dword is the speed.
#include "../ui/game_options_class_methods.h"
extern GameOptionsClass DAT_00A8EB60;
// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"
// GLOBAL: GAMEMD 0xB07784 — a frame deadline re-armed at CurrentFrame + 3.
extern int DAT_00B07784;

// Canonical Scenario layout: 0x69BAB0 reads its byte at +0x35A2.
#include "../core/scenario_class_methods.h"
#include "../_layout/scenario_ptr_00a8b230.h"

// FUNCTION: GAMEMD 0x684240 (decl; reloc) — no arguments, no cleanup.
void __cdecl FUN_00684240(void);

#include "../ui/input_controls/mouse_ww_mouse_class.h"
#include "../core/flag_object_00407100.h"
// GLOBAL: GAMEMD 0x87E758
extern Obj_00407100* DAT_0087E758;

#include "../_layout/session_class.h"

#endif  // GG_MATCH_NETWORK_SESSION_CLASS_RESUME_METHODS_H

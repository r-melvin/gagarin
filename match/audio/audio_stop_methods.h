// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x405D40:
//     handle  [EAX+0x0] Voice, [EAX+0x4] Serial, [EAX+0x8] Token,
//             [EAX+0xC] Owner (CMP dword ptr [EAX+0xC],0x87E294)
//     voice   [ESI+0x18] Flags (TEST byte,1 / TEST byte,2 / OR ..,1),
//             [ESI+0x1C] State (set to 4), [ESI+0x24] Token,
//             [ESI+0x28] the sub-object array walked by LEA EDI,[ESI+0x28],
//             [ESI+0xA8] the array count, [ESI+0xB0] Peer,
//             [ESI+0x138] Serial, [ESI+0x278] unknown_278
//     peer    [..+0x90], [..+0x98], [..+0x9C], [..+0xB4], [..+0xB8],
//             [..+0xBC], [..+0xC0] Voice (back-pointer, CMP ESI,[ECX+0xC0])
//   The same handle/voice/peer shapes are pinned by 0x406060 in
//   match/audio/audio_end_looping_methods.h and by 0x405FD0 in
//   match/audio/sample_registry_methods.h; neither is edited — this TU
//   redeclares the parts it needs (plus the peer fields 0x90..0xBC and the
//   voice fields 0x1C/0x28/0xA8/0x278, which are new here) so it stands alone.
//   YRpp names 0x405D40 Audio::Stop.
#ifndef GG_MATCH_AUDIO_AUDIO_STOP_METHODS_H
#define GG_MATCH_AUDIO_AUDIO_STOP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/triple_timer_init_methods.h"
#include "../core/tail_call_methods.h"
#include "../_layout/audio_controller.h"
#include "../_layout/audio_event.h"

// GLOBAL: GAMEMD 0x87E2A0 — nonzero once the audio subsystem is up.
extern int DAT_0087E2A0;
// GLOBAL: GAMEMD 0x87E294 — the sample table; the handle's owner is compared
// against its address.
extern char DAT_0087E294[];

void FUN_00401F90(void* sub);

#endif  // GG_MATCH_AUDIO_AUDIO_STOP_METHODS_H

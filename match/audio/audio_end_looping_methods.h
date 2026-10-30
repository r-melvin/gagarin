// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x406060:
//     handle  [ESI+0x0] Voice, [ESI+0x4] Serial, [ESI+0x8] Token,
//             [ESI+0xC] Owner (compared against the address 0x87E294)
//     voice   [EDI+0x18] Flags (TEST ..,0x20; OR ..,0x60), [EDI+0x24] Token,
//             [EDI+0xB0] Peer, [EDI+0x138] Serial
//     token   [EAX+0x10] Flags (TEST byte,1), [EAX+0x4C] unknown_4C
//     peer    [EAX+0xC0] Voice (back-pointer)
//   The same handle/voice/peer shapes are already pinned by 0x405FD0 in
//   match/audio/sample_registry_methods.h; this TU redeclares them locally
//   (with the token typed as a pointer, which is how 0x406060 reads it) so it
//   stands alone. YRpp names 0x406060 Audio::EndLooping.
#ifndef GG_MATCH_AUDIO_AUDIO_END_LOOPING_METHODS_H
#define GG_MATCH_AUDIO_AUDIO_END_LOOPING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/audio_controller.h"
#include "../_layout/audio_event.h"

// GLOBAL: GAMEMD 0x87E2A0 — nonzero once the audio subsystem is up.
extern int DAT_0087E2A0;

#endif  // GG_MATCH_AUDIO_AUDIO_END_LOOPING_METHODS_H

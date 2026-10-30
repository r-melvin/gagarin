// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   `AdjustAudioEventPanning` (every offset
//   reconfirmed numerically from the disassembly).
//
// AdjustAudioEventPanning clamps a pan value to [0, 0x4000] and dispatches it to
// one of two per-channel pan setters depending on the event's playback type
// ([event+0x1c] == 3 selects the 0x407170 variant, else the 0x407150 variant).
// Neither pan setter is matched here — they are declared so cl emits the
// (relocation-normalised) tail-call jump the retail code uses.
#ifndef GG_MATCH_AUDIO_AUDIO_PAN_METHODS_H
#define GG_MATCH_AUDIO_AUDIO_PAN_METHODS_H

#include <stddef.h>  // offsetof, size_t
#include "../core/triple_timer_init_methods.h"
#include "../_rt/gg_static_assert.h"
#include "../_layout/audio_event.h"

// The two per-channel pan setters (ECX = &event->Channel, EDX = clamped pan).
// Declared only — bodies live elsewhere; cl emits a tail-call jump (reloc).



// AudioEvent::AdjustAudioEventPanning (0x406270) is declared in match/_layout/audio_event.h.

#endif  // GG_MATCH_AUDIO_AUDIO_PAN_METHODS_H

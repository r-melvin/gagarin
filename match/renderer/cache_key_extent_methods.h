// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 at 0x600670 and
//   0x600680. Both take the receiver in ECX with no stack cleanup at the call
//   sites (0x610FED, 0x6110A8, 0x612517, 0x612569), so both are __thiscall
//   members of the same two-int key:
//     * 0x600670 is `MOV EAX,[ECX+4]; IMUL EAX,[ECX]; RET` — the product of the
//       two fields, returned as a full dword.
//     * 0x600680 is `RET 4` and compares [arg+4] against [this+4] first, then
//       [arg] against [this], answering AL=1/0. The +4 field is compared first
//       in both, which is what fixes the field order below.
//   Field names are positional: no RTTI reaches these two (the key is a plain
//   POD with no vtable), so `Width`/`Height` is a reading of the multiply, not
//   a recovered Westwood name.
//
//   The private-reference seed files these under audio/voc_codec.cpp as
//   `computeFrameSize` / `compareAudioMixerStates`; the grouping is right (they
//   are neighbours of one cache) and the audio attribution is not.
#ifndef GG_MATCH_RENDERER_CACHE_KEY_EXTENT_METHODS_H
#define GG_MATCH_RENDERER_CACHE_KEY_EXTENT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The two-dword cache key. Callers hold arrays of pointers to entries whose
// first eight bytes are this pair (0x612500: `MOV EDI,[EAX+ESI*4]` then
// `MOV ECX,EDI` straight into the comparison below).
struct CacheKey_00600670
{
    int Width;    // +0x00
    int Height;   // +0x04

    // FUNCTION: GAMEMD 0x600670 (__thiscall)
    int Extent();

    // FUNCTION: GAMEMD 0x600680 (__thiscall)
    bool operator==(const CacheKey_00600670& other) const;
};

GG_STATIC_ASSERT(offsetof(CacheKey_00600670, Height) == 0x04);
GG_STATIC_ASSERT(sizeof(CacheKey_00600670) == 0x08);

#endif  // GG_MATCH_RENDERER_CACHE_KEY_EXTENT_METHODS_H

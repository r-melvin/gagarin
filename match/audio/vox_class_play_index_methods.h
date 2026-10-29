// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x752480: the engine handle 0xB1D4CC, the entry count
//   0xB1D4B0 and table 0xB1D4A4, the suppression flag 0xB1D3D8, the
//   currently speaking entry 0xB1D4C4, the pending-node list head 0xB1D3C8
//   and the two counters 0xB1D4D0 / 0xB1D4D4; on an entry the default
//   priority `[EBX+0x4C]` and default volume `[EBX+0x48]` and the state
//   dword at `+0x50` (2 = finished); on a queued node the owning entry at
//   `+0xC`; and the helpers 0x4073C0 (pop a node), 0x407450 (release it),
//   0x7C8B3D (free), 0x407F40 (stop the engine), 0x752370 (reset the
//   queue), 0x752680 (the entry's live node, priority at `+0x18`),
//   0x752590 (start it) and 0x752760 (pump). Names cross-checked against
//   YRpp.
#ifndef GG_MATCH_AUDIO_VOX_CLASS_PLAY_INDEX_METHODS_H
#define GG_MATCH_AUDIO_VOX_CLASS_PLAY_INDEX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vox_class_methods.h"

// The pending-node list.
struct VoxQueue_00752480
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x4073C0 (decl; reloc) — take the next pending node.
    VoxNode* FUN_004073C0();
};
// GLOBAL: GAMEMD 0xB1D3C8 — the pending-node list.
extern VoxQueue_00752480 DAT_00B1D3C8;

// The audio engine handle.
struct VoxEngine_00752480
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x407F40 (decl; reloc) — stop whatever is playing.
    void FUN_00407F40();
    // FUNCTION: GAMEMD 0x407A90 (decl; reloc) — release the engine.
    void FUN_00407A90();
    // FUNCTION: GAMEMD 0x408070 (decl; reloc) -- non-zero while the engine is busy.
    int FUN_00408070() const;
};
// GLOBAL: GAMEMD 0xB1D4CC — the engine handle.
extern VoxEngine_00752480* DAT_00B1D4CC;

// GLOBAL: GAMEMD 0xB1D4B0 — how many speech entries there are.
extern int DAT_00B1D4B0;
// GLOBAL: GAMEMD 0xB1D4A4 — the speech entry table.
extern VoxClass** DAT_00B1D4A4;
// GLOBAL: GAMEMD 0xB1D3D8 — non-zero while speech is suppressed.
extern int DAT_00B1D3D8;
// GLOBAL: GAMEMD 0xB1D4C4 — the entry currently speaking.
extern VoxClass* DAT_00B1D4C4;
// GLOBAL: GAMEMD 0xB1D4D0 — the queued entry counter.
extern int DAT_00B1D4D0;
// GLOBAL: GAMEMD 0xB1D4D4 — the queued frame counter.
extern int DAT_00B1D4D4;

// FUNCTION: GAMEMD 0x407450 (decl; reloc) — release a pending node.
void FUN_00407450(VoxNode* node);
// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);
// FUNCTION: GAMEMD 0x752370 (decl; reloc) — reset the speech queue.
void __cdecl FUN_00752370();
// FUNCTION: GAMEMD 0x752590 (decl; reloc) — start an entry.
void FUN_00752590(VoxClass* entry, int priority, int volume);
// FUNCTION: GAMEMD 0x752760 (decl; reloc) — pump the speech queue.
void __cdecl FUN_00752760();

#endif  // GG_MATCH_AUDIO_VOX_CLASS_PLAY_INDEX_METHODS_H

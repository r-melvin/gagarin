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
//   YRpp VoxClass.h (consult-only; NO LICENSE).
#ifndef GG_MATCH_AUDIO_VOX_CLASS_PLAY_INDEX_METHODS_H
#define GG_MATCH_AUDIO_VOX_CLASS_PLAY_INDEX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One speech entry.
struct VoxEntry_00752480
{
    char _pad000[0x48];   // +0x0000
    int  Volume;          // +0x0048
    int  Priority;        // +0x004C
    int  State;           // +0x0050  2 = finished
};
GG_STATIC_ASSERT(offsetof(VoxEntry_00752480, Volume)   == 0x48);
GG_STATIC_ASSERT(offsetof(VoxEntry_00752480, Priority) == 0x4C);
GG_STATIC_ASSERT(offsetof(VoxEntry_00752480, State)    == 0x50);

// One queued playback node.
struct VoxNode_00752480
{
    char               _pad000[0xC];   // +0x0000
    VoxEntry_00752480* Entry;          // +0x000C
    char               _pad010[8];     // +0x0010
    int                Priority;       // +0x0018
};
GG_STATIC_ASSERT(offsetof(VoxNode_00752480, Entry)    == 0xC);
GG_STATIC_ASSERT(offsetof(VoxNode_00752480, Priority) == 0x18);

// The pending-node list.
struct VoxQueue_00752480
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x4073C0 (decl; reloc) — take the next pending node.
    VoxNode_00752480* FUN_004073C0();
};
// GLOBAL: GAMEMD 0xB1D3C8 — the pending-node list.
extern VoxQueue_00752480 DAT_00B1D3C8;

// The audio engine handle.
struct VoxEngine_00752480
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x407F40 (decl; reloc) — stop whatever is playing.
    void FUN_00407F40();
};
// GLOBAL: GAMEMD 0xB1D4CC — the engine handle.
extern VoxEngine_00752480* DAT_00B1D4CC;

// GLOBAL: GAMEMD 0xB1D4B0 — how many speech entries there are.
extern int DAT_00B1D4B0;
// GLOBAL: GAMEMD 0xB1D4A4 — the speech entry table.
extern VoxEntry_00752480** DAT_00B1D4A4;
// GLOBAL: GAMEMD 0xB1D3D8 — non-zero while speech is suppressed.
extern int DAT_00B1D3D8;
// GLOBAL: GAMEMD 0xB1D4C4 — the entry currently speaking.
extern VoxEntry_00752480* DAT_00B1D4C4;
// GLOBAL: GAMEMD 0xB1D4D0 — the queued entry counter.
extern int DAT_00B1D4D0;
// GLOBAL: GAMEMD 0xB1D4D4 — the queued frame counter.
extern int DAT_00B1D4D4;

// FUNCTION: GAMEMD 0x407450 (decl; reloc) — release a pending node.
void __fastcall FUN_00407450(VoxNode_00752480* node);
// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);
// FUNCTION: GAMEMD 0x752370 (decl; reloc) — reset the speech queue.
void __cdecl FUN_00752370();
// FUNCTION: GAMEMD 0x752680 (decl; reloc) — the entry's live node, if any.
VoxNode_00752480* __fastcall FUN_00752680(VoxEntry_00752480* entry);
// FUNCTION: GAMEMD 0x752590 (decl; reloc) — start an entry.
void __fastcall FUN_00752590(VoxEntry_00752480* entry, int priority, int volume);
// FUNCTION: GAMEMD 0x752760 (decl; reloc) — pump the speech queue.
void __cdecl FUN_00752760();

// The owning class. Nothing at this address touches an instance, so no layout
// is recovered here; the struct exists so the routine is spelled as the static
// member it is rather than as a free function, and so the next address on this
// class has somewhere to attach.
struct VoxClass
{
    // FUNCTION: GAMEMD 0x752480 — VoxClass::PlayIndex (static __fastcall: the
    // index arrives in ECX, the priority in EDX and the volume on the stack).
    static void __fastcall PlayIndex(int index, int priority, int volume);
};

#endif  // GG_MATCH_AUDIO_VOX_CLASS_PLAY_INDEX_METHODS_H

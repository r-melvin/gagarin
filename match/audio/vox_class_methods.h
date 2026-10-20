// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   VoxClass.h (consult-only, NO LICENSE; every offset/address reconfirmed
//   numerically from the disassembly below).
//
// VoxClass — the EVA voice table. Each entry names an EVA event ("New construction
// options", "Unit lost", ...). Play() resolves a name to its index and forwards
// to PlayIndex; SilenceIndex() tears down any live voices spawned by an index.
//
// Only the members/globals the two matched methods touch are modelled here; the
// full VoxClass body (Volume/Priority/Type/...) and the audio-controller layout
// are P2 work. Every offset asserted below is confirmed from the disassembly.
#ifndef GG_MATCH_AUDIO_VOX_CLASS_METHODS_H
#define GG_MATCH_AUDIO_VOX_CLASS_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// VoxNode — one live EVA voice handle returned by VoxClass::GetActiveVoice
// (0x752680). SilenceIndex walks the chain of live voices for an index:
//   * +0x04  self-referential "is-detached" sentinel (CMP [ESI+4],ESI)
//   * +0x0C  pointer to the audio-event object whose state field (+0x50) is
//            forced to 2 ("stop/idle") on teardown (MOV [ECX+0x50],2)
// Modelled only to the offsets SilenceIndex dereferences.
// ---------------------------------------------------------------------------
struct VoxEvent
{
    char _pad0[0x50];   // +0x00
    int  State;         // +0x50  (forced to 2 on teardown)
};
GG_STATIC_ASSERT(offsetof(VoxEvent, State) == 0x50);

struct VoxNode
{
    char      _pad0[0x4];   // +0x00
    VoxNode*  Link;         // +0x04  (compared to `this`)
    char      _pad8[0x4];   // +0x08
    VoxEvent* Event;        // +0x0C

    // 0x407450 (__thiscall) — detach this voice node. Declared only (reloc call).
    void Detach();
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(VoxNode, Link)  == 0x04);
GG_STATIC_ASSERT(offsetof(VoxNode, Event) == 0x0C);
#endif

// ---------------------------------------------------------------------------
// VoxClass — Name sits at offset 0 (the entry address doubles as the name
// pointer; confirmed by Play pushing the raw VoxClass* as the _strcmpi operand).
// ---------------------------------------------------------------------------
struct VoxClass
{
    // Static EVA dispatch entry points (cl emits __fastcall; ECX=arg0,EDX=arg1).
    static void __fastcall Play(const char* pName, int nUnk, int nUnk2);   // GAMEMD 0x752700
    static void __fastcall SilenceIndex(int index);                        // GAMEMD 0x752A40

    // Retail callees NOT matched here — declared only so cl emits relocated calls.
    static void __fastcall PlayIndex(int index, int nUnk, int nUnk2);      // GAMEMD 0x752480
    VoxNode* GetActiveVoice();                                             // GAMEMD 0x752680 (__thiscall)

    char Name[0x28];   // +0x00
};
GG_STATIC_ASSERT(offsetof(VoxClass, Name) == 0x00);

#endif  // GG_MATCH_AUDIO_VOX_CLASS_METHODS_H

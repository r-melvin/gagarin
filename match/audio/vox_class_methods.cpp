// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names cross-
//   checked against YRpp (each offset and
//   global address reconfirmed against the user's binary below).
//
// Translation unit: VoxClass EVA-voice dispatch.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x752700   VoxClass::Play          (__fastcall)
//   FUNCTION: GAMEMD 0x752A40   VoxClass::SilenceIndex  (__fastcall)
//   GLOBAL:   GAMEMD 0xB1D4A0   VoxArray prefix view    (Items/Count only)
//   GLOBAL:   GAMEMD 0xB1D4A4   Array.Items
//   GLOBAL:   GAMEMD 0xB1D4B0   Array.Count
//   GLOBAL:   GAMEMD 0xB1D4B8   current EVA VoxNode*    (cleared on teardown)
//   LIBRARY:  GAMEMD 0x7C8D20   _strcmpi  (CRT; excluded from match target)
//   FUNCTION: GAMEMD 0x752480   VoxClass::PlayIndex     (reloc callee)
//   FUNCTION: GAMEMD 0x752680   VoxClass::GetActiveVoice(reloc callee)
//   FUNCTION: GAMEMD 0x407450   VoxNode::Detach         (reloc callee)
//   LIBRARY: GAMEMD 0x7C8B3D   release voice node      (reloc callee, cdecl)

#include "vox_class_methods.h"

// ---------------------------------------------------------------------------
// GLOBAL: GAMEMD 0xB1D4A0 — the global EVA voice table. Modelled to the two
// touched members: Items @+0x04 (==0xB1D4A4) and Count @+0x10
// (==0xB1D4B0), confirmed from the absolute operands. The untouched regions
// are gaps; the complete container layout and intervening field names are not
// claimed here.
// ---------------------------------------------------------------------------
struct VoxArrayType
{
    char  unknown_00[0x04];
    void* Items;      // +0x04  (VoxClass** base) == 0xB1D4A4
    char  unknown_08[0x08];
    int   Count;      // +0x10  == 0xB1D4B0
};
GG_STATIC_ASSERT(offsetof(VoxArrayType, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(VoxArrayType, Count) == 0x10);

extern VoxArrayType VoxArray;       // 0xB1D4A0
extern VoxNode*     VoxCurrentNode; // 0xB1D4B8

// CRT _strcmpi — declared (no body) so cl emits a relocated cdecl call rather
// than an intrinsic; arg order matches the retail push sequence below.
extern "C" int __cdecl Vox_strcmpi(const char* a, const char* b);

// 0x7C8B3D — release/recycle a finished voice node (cdecl, one arg). Reloc call.
void __cdecl VoxReleaseNode(VoxNode* node);

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x752700  VoxClass::Play  (__fastcall)
// Complete retail span: 0x5F bytes, including RET immediate at 0x75275C.
//
// Resolve an EVA event name to its table index and play it; if the name is not
// found, play index -1. A null name is a no-op. The name is compared against
// each entry via _strcmpi (entry address == name pointer, Name @+0x00).
// ---------------------------------------------------------------------------
static __inline int VoxFindIndex(const char* pName)
{
    for (int i = 0; i < VoxArray.Count; ++i)
    {
        if (Vox_strcmpi(pName, ((VoxClass**)VoxArray.Items)[i]->Name) == 0)
            return i;
    }
    return -1;
}

void VoxClass::Play(const char* pName, int nUnk, int nUnk2)
{
    if (pName != 0)
        PlayIndex(VoxFindIndex(pName), nUnk, nUnk2);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x752A40  VoxClass::SilenceIndex  (__fastcall)
//
// Tear down every live voice currently associated with an EVA index. For each
// live node returned by GetActiveVoice: detach it if not already self-linked,
// clear the global current-node pointer if it referenced this node, force the
// backing audio event into the stopped state (State=2), then release the node.
// ---------------------------------------------------------------------------
void VoxClass::SilenceIndex(int index)
{
    if (index >= 0 && index < VoxArray.Count)
    {
        VoxNode* node = ((VoxClass**)VoxArray.Items)[index]->GetActiveVoice();
        while (node != 0)
        {
            if (node->Link != node)
                node->Detach();
            if (node == VoxCurrentNode)
                VoxCurrentNode = 0;
            node->Event->State = 2;
            VoxReleaseNode(node);
            node = ((VoxClass**)VoxArray.Items)[index]->GetActiveVoice();
        }
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB1D4A0
VoxArrayType VoxArray;
// END defined globals

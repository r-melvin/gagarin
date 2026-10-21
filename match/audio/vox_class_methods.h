// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-disassembly | RTTI not required by these methods
//
// Minimal ABI views for the Vox fields accessed by Play and SilenceIndex.
// These are touched-prefix models, not recovered complete class/array layouts.
#ifndef GG_MATCH_AUDIO_VOX_CLASS_METHODS_H
#define GG_MATCH_AUDIO_VOX_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct VoxEvent
{
    char unknown_00[0x50];
    int State; // observed at +0x50 in SilenceIndex
};
GG_STATIC_ASSERT(offsetof(VoxEvent, State) == 0x50);

struct VoxNode
{
    char unknown_00[0x04];
    VoxNode* Link;    // observed at +0x04
    char unknown_08[0x04];
    VoxEvent* Event;  // observed at +0x0C

    void Detach();   // call target 0x407450
};
GG_STATIC_ASSERT(offsetof(VoxNode, Link) == 0x04);
GG_STATIC_ASSERT(offsetof(VoxNode, Event) == 0x0C);

struct VoxClass
{
    static void __fastcall Play(const char* pName, int nUnk, int nUnk2);
    static void __fastcall SilenceIndex(int index);
    static void __fastcall PlayIndex(int index, int nUnk, int nUnk2);
    VoxNode* GetActiveVoice();

    // The entry address is passed to _strcmpi as a string pointer, proving
    // only that the Name prefix starts at +0. Its storage extent is unknown.
    char Name[1];
};
GG_STATIC_ASSERT(offsetof(VoxClass, Name) == 0x00);

#endif

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-disassembly | RTTI not required by these methods | YRpp-cross-check
//
// Minimal ABI views for the Vox fields accessed by Play and SilenceIndex.
// These are touched-prefix models, not recovered complete class/array layouts.
#ifndef GG_MATCH_AUDIO_VOX_CLASS_METHODS_H
#define GG_MATCH_AUDIO_VOX_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct VoxClass;

// One queued playback node.
struct VoxNode
{
    char unknown_00[0x04];
    VoxNode* Link;    // observed at +0x04
    char unknown_08[0x04];
    VoxClass* Event;  // observed at +0x0C: the speech entry the node plays
    char unknown_10[8];
    int Priority;     // observed at +0x18

    void Detach();   // call target 0x407450
    VoxNode* FUN_004073E0();   // call target 0x4073E0: the next node in the list
};
GG_STATIC_ASSERT(offsetof(VoxNode, Link) == 0x04);
GG_STATIC_ASSERT(offsetof(VoxNode, Event) == 0x0C);
GG_STATIC_ASSERT(offsetof(VoxNode, Priority) == 0x18);

// One speech entry.
struct VoxClass
{
    static void Play(const char* pName, int nUnk, int nUnk2);
    static void SilenceIndex(int index);
    static void PlayIndex(int index, int nUnk, int nUnk2);
    VoxNode* GetActiveVoice();

    // The entry address is passed to _strcmpi as a string pointer, proving
    // only that the Name prefix starts at +0. Its storage extent is unknown.
    char Name[1];
    char unknown_01[0x47];
    int  Volume;    // +0x48
    int  Priority;  // +0x4C
    int  State;     // +0x50  2 = finished
};
GG_STATIC_ASSERT(offsetof(VoxClass, Name) == 0x00);
GG_STATIC_ASSERT(offsetof(VoxClass, Volume) == 0x48);
GG_STATIC_ASSERT(offsetof(VoxClass, Priority) == 0x4C);
GG_STATIC_ASSERT(offsetof(VoxClass, State) == 0x50);

#endif

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI (PAVVocClass, vector bases) | YRpp-cross-check
//   VocClass is the 4-byte heap wrapper that is the element of the DynamicVectorClass<VocClass*> at
//   0xB1D378 (operator_new(4) at 0x7510D0; its only member is the sound descriptor pointer, read as
//   `**(Array.Items + i*4)` by 0x750920 / 0x7509E0 / 0x7514D0 / 0x751520 / 0x7518A0). The descriptor
//   (AudioEventType, 0x148 bytes) is in audio_event_type.h; the live event in audio_event.h.
//   PlayAtPos 0x750E20 pops a voice node from the pool at 0xB1D3A4, constructs its AudioController
//   (0x405BE0), calls PlayAt and links the node into the live list at 0xB1D320 (the list VocClass's
//   Save/Load walk), so it is a VocClass method; it used to be filed under VoxClass.
#ifndef GG_MATCH__LAYOUT_VOC_CLASS_H
#define GG_MATCH__LAYOUT_VOC_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vector_class.h"
#include "coord_struct.h"
#include "audio_controller.h"
#include "audio_event.h"
#include "audio_event_type.h"
#include "../core/intrusive_list_methods.h"

class CCINIClass;

class VocClass
{
public:
    // FUNCTION: GAMEMD 0x7503F0 -- remove this entry from Array
    void FUN_007503F0();
    // FUNCTION: GAMEMD 0x750440 -- read this entry's sound.ini section into its descriptor
    bool ReadINI(CCINIClass* ini);
    // FUNCTION: GAMEMD 0x7514D0
    static int FindIndex(const char* pName);
    // FUNCTION: GAMEMD 0x750920
    static AudioEvent* PlayGlobal(int index, float volume, unsigned int pan, AudioController* controller);
    // FUNCTION: GAMEMD 0x7509E0
    static AudioEvent* PlayAt(int index, CoordStruct* coords, AudioController* controller);
    // FUNCTION: GAMEMD 0x750E20
    static AudioEvent* PlayAtPos(int index, CoordStruct* coords, int extra);

    // GLOBAL: GAMEMD 0xB1D378 -- VocClass::Array (Items 0xB1D37C, Count 0xB1D388).
    static DynamicVectorClassLayout Array;

    AudioEventType* EventType;   // +0x00 (null when audio is off)
};
GG_STATIC_ASSERT(offsetof(VocClass, EventType) == 0x00);
GG_STATIC_ASSERT(sizeof(VocClass) == 0x04);

// A live positional voice (0x3C-byte block from the pool at 0xB1D3A4): a list link, the controller PlayAtPos
// constructs, the world position and the caller's extra word.
struct VocVoiceNode
{
    // FUNCTION: GAMEMD 0x4073E0 (decl; reloc) -- the next node
    VocVoiceNode* FUN_004073E0();
    // FUNCTION: GAMEMD 0x407450 (decl; reloc) -- unlink
    void FUN_00407450();

    ListNode        Link;        // +0x00
    AudioController Handle;      // +0x0C (0x14)
    CoordStruct     Coords;      // +0x20
    unsigned int    Flags;       // +0x2C  PlayAtPos' third argument, masked by 0x750F40
    int             Remaining;   // +0x30  =0 at PlayAtPos
};
GG_STATIC_ASSERT(offsetof(VocVoiceNode, Handle) == 0x0C);
GG_STATIC_ASSERT(offsetof(VocVoiceNode, Coords) == 0x20);
GG_STATIC_ASSERT(offsetof(VocVoiceNode, Flags) == 0x2C);
GG_STATIC_ASSERT(offsetof(VocVoiceNode, Remaining) == 0x30);

#endif

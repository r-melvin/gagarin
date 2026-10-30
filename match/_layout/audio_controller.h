// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check; the one canonical AudioController.
//   Layout from the member accesses of 0x4060F0 / 0x406130 / 0x406170 / 0x405BE0 (constructor:
//   `[+0xC]=0x87E294; [+0..8]=0`). sizeof is 0x14, proven by the back-to-back constructor calls
//   at this+0x3C / this+0x50 in BombClass and the 0x4A4 / 0x4C0 spacing in TechnoClass.
//     +0x00 Event      the live AudioEvent (validated against EventType + Stamp before use)
//     +0x04 Stamp      copy of the event's Serial at SetEvent time
//     +0x08 EventType  the descriptor the controller was last set to
//     +0x0C AudioIndex AudioIDXData** that equals &AudioIDXData_Instance (0x87E294) while valid
//   AudioEvent is attested by the pool string "AudioEvents : %05d - Max: %05d" (0x81624C);
//   AudioEventType is a placeholder name. Both are opaque here (see audio_event.h).
#ifndef GG_MATCH__LAYOUT_AUDIO_CONTROLLER_H
#define GG_MATCH__LAYOUT_AUDIO_CONTROLLER_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct AudioIDXData;
struct AudioEvent;
struct AudioEventType;

struct AudioController
{
    // FUNCTION: GAMEMD 0x405BE0 -- construct/reset: AudioIndex = &AudioIDXData_Instance, the rest zero.
    void FUN_00405BE0();
    // FUNCTION: GAMEMD 0x405C00 -- release the controller's event (a Stop variant that also clears
    // EventType / AudioIndex).
    void FUN_00405C00();
    // FUNCTION: GAMEMD 0x405D40
    void Stop();
    // FUNCTION: GAMEMD 0x405FD0 (decl; reloc)
    void FUN_00405FD0();
    // FUNCTION: GAMEMD 0x406060 -- ends a looping voice (YRpp: Audio::EndLooping)
    void EndLooping();
    // FUNCTION: GAMEMD 0x4060F0
    static void SetEvent(AudioController* pThis, AudioEvent* event, AudioEventType* eventType);
    // FUNCTION: GAMEMD 0x406130
    AudioEvent* GetEvent();
    // FUNCTION: GAMEMD 0x406170
    AudioEventType* GetEventType();

    AudioEvent*     Event;       // +0x00
    unsigned int    Stamp;       // +0x04
    AudioEventType* EventType;   // +0x08
    AudioIDXData**  AudioIndex;  // +0x0C
    unsigned int    Unused;      // +0x10
};
GG_STATIC_ASSERT(offsetof(AudioController, Stamp)     == 0x04);
GG_STATIC_ASSERT(offsetof(AudioController, EventType) == 0x08);
GG_STATIC_ASSERT(offsetof(AudioController, AudioIndex) == 0x0C);
GG_STATIC_ASSERT(sizeof(AudioController)              == 0x14);

// GLOBAL: GAMEMD 0x87E294 -- the sample table; a live controller's AudioIndex points at it.
extern AudioIDXData* AudioIDXData_Instance;

#endif

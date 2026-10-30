// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7509E0. Names from
//   YRpp.
//   LIBRARY: GAMEMD 0x7C5F00  __ftol  (CRT float->long; the (int) cast; reloc)

#include "voc_class_play_at_methods.h"

// FUNCTION: GAMEMD 0x7509E0
//
// Play a positional sound through an optional controller. The voc entry's
// event is looked up by index; a controller that is already playing a
// different event is stopped so a fresh handle can be started. The volume
// and pan come from the listener's distance to `coords`; an inaudible
// result (volume not above zero) stops any handle instead of starting one.
// Audible volume is scaled to the 0..0x4000 fixed range. The controller, if
// any, is re-bound to whatever handle results, and that handle is returned.
//
// The handle local is declared before the event local: retail zeroes ESI
// (handle) and EDI (event) together ahead of the index test and keeps the
// coordinates in EBX; with the event declared first the coordinates take EDI
// and the event EBX (63.9%, pure register naming).
AudioEvent* VocClass::PlayAt(
    int index, CoordStruct* coords, AudioController* controller)
{
    if (DAT_008464AC == 0)
        return 0;

    AudioEvent* handle = 0;
    AudioEventType* event = 0;
    if (index >= 0 && index < Array.Count)
        event = ((VocClass**)Array.Items)[index]->EventType;

    if (controller != 0) {
        handle = controller->GetEvent();
        if (handle != 0) {
            if (handle->GetEventType() != event) {
                handle->FUN_004052F0();
                handle = 0;
            }
        }
    }

    if (event != 0) {
        int pan;
        float volume = GetPositionalVolume(coords, &pan, event);
        if (volume > 0.0f) {
            unsigned int vol = (unsigned int)(int)(volume * 16384.0f);
            if (vol >= 0x4000)
                vol = 0x4000;

            if (handle == 0)
                handle = event->FUN_00405190();

            if (handle != 0) {
                handle->FUN_004061D0(vol);
                handle->AdjustAudioEventPanning(pan);
            }
        } else {
            if (handle != 0) {
                handle->FUN_004052F0();
                handle = 0;
            }
        }
    }

    if (controller != 0)
        AudioController::SetEvent(controller, handle, event);

    return handle;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7509E0. Names from
//   YRpp VocClass.h (consult-only).
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
AudioHandle_007509E0* __fastcall VocClass::PlayAt(
    int index, CoordStruct* coords, AudioController_007509E0* controller)
{
    if (DAT_008464AC == 0)
        return 0;

    AudioHandle_007509E0* handle = 0;
    AudioEvent_007509E0* event = 0;
    if (index >= 0 && index < Array.Count)
        event = ((VocItem_007509E0**)Array.Items)[index]->Event;

    if (controller != 0) {
        handle = controller->GetEvent();
        if (handle != 0) {
            if (FUN_00406310(handle) != event) {
                FUN_004052F0(handle);
                handle = 0;
            }
        }
    }

    if (event != 0) {
        int pan;
        float volume = FUN_00750AC0(coords, &pan, event);
        if (volume > 0.0f) {
            unsigned int vol = (unsigned int)(int)(volume * 16384.0f);
            if (vol >= 0x4000)
                vol = 0x4000;

            if (handle == 0)
                handle = FUN_00405190(event);

            if (handle != 0) {
                FUN_004061D0(handle, vol);
                FUN_00406270(handle, pan);
            }
        } else {
            if (handle != 0) {
                FUN_004052F0(handle);
                handle = 0;
            }
        }
    }

    if (controller != 0)
        FUN_004060F0(controller, handle, event);

    return handle;
}

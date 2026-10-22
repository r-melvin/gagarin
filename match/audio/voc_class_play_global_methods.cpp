// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x750920. Names from
//   YRpp.
//   LIBRARY: GAMEMD 0x7C5F00  __ftol  (CRT float->long; the (int) cast; reloc)

#include "voc_class_play_global_methods.h"

// FUNCTION: GAMEMD 0x750920
//
// Play a non-positional sound through an optional controller. The voc entry's
// event is looked up by index; a controller that is already playing a
// different event is stopped so a fresh handle can be started. Volume is a
// 0..1 float scaled to the 0..0x4000 fixed range. The controller, if any, is
// re-bound to whatever handle results, and that handle is returned.
AudioHandle_00750920* VocClass::PlayGlobal(
    int index, float volume, unsigned int pan,
    AudioController_00750920* controller)
{
    if (DAT_008464AC == 0)
        return 0;

    AudioEvent_00750920* event = 0;
    if (index >= 0 && index < Array.Count)
        event = ((VocItem_00750920**)Array.Items)[index]->Event;

    AudioHandle_00750920* handle = 0;
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
        unsigned int vol = (unsigned int)(int)(volume * 16384.0f);
        if (vol >= 0x4000)
            vol = 0x4000;

        if (handle == 0)
            handle = FUN_00405190(event);

        if (handle != 0) {
            FUN_004061D0(handle, vol);
            FUN_00406270(handle, pan);
        }
    }

    if (controller != 0)
        FUN_004060F0(controller, handle, event);

    return handle;
}

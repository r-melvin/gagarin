// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4CC770.

#include "flash_data_methods.h"

// FUNCTION: GAMEMD 0x4CC770  FlashData::Update (__thiscall)
// Tick the flash countdown and toggle the visible state on odd frames, so the
// object blinks at half the frame rate. Returns whether the flash is still
// running. The unconditional clear before the odd-frame test is retail's own
// shape (`MOV byte [ECX+4],0` then a conditional `MOV byte [ECX+4],1`).
bool FlashData::Update()
{
    if (DurationRemaining != 0) {
        DurationRemaining--;
        FlashingNow = false;
        if (DurationRemaining & 1)
            FlashingNow = true;

        return true;
    }
    return false;
}

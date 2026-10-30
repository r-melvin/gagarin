// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry 0x402800 compares/copies eight dwords at +0x17C and writes +0x19C.
// Calls 0x40A2C6 and 0x40A36D identify the source as AudioSampleData.
#include <string.h>
#include "pan_and_pitch_methods.h"

// FUNCTION: GAMEMD 0x402800
// Store a new audio format only when its 32-byte record differs.
int __fastcall Voice_0040A6D0::FUN_00402800(const AudioSampleData* incoming)
{
    if (memcmp(incoming, &unknown_17C, sizeof(unknown_17C)) == 0) {
        unknown_19C = 0;
    } else {
        unknown_19C = 1;
        memcpy(&unknown_17C, incoming, sizeof(unknown_17C));
    }
    return unknown_19C;
}

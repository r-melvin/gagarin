// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x401580.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x401580   FUN_00401580 (__fastcall)

#include "audio_idx_data_destroy_methods.h"

// FUNCTION: GAMEMD 0x401580  (__fastcall)
//
// Release the two owned sub-objects, then the raw IDX buffer, then the record
// itself. The null tests in front of the two deletes are not in the source -
// `delete p` emits its own.
void AudioIDXData::FUN_00401580()
{
    delete this->Samples;
    delete this->Headers;

    if (this->RawData) {
        FUN_007C8B3D(this->RawData);
    }

    FUN_007C8B3D(this);
}

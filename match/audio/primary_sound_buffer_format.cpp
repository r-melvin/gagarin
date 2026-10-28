// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x40A7C0..0x40A8FA configures the primary DirectSound buffer.
#include "primary_sound_buffer_format.h"
#include <string.h>
#pragma intrinsic(memset)

// FUNCTION: GAMEMD 0x40A7C0
// Apply a PCM format and resume looping playback. Movie callers pass the
// sample rate, bits per sample and channel count (44100, 16, 2).
void FUN_0040A7C0(int samplesPerSecond, int bitsPerSample, int channels)
{
    if (DAT_0087E8A0 != 0) {
        WAVEFORMATEX format;

        format.wFormatTag  = 1;
        format.nChannels  = (unsigned short)channels;
        format.nSamplesPerSec  = samplesPerSecond;
        format.nBlockAlign  = (unsigned short)(bitsPerSample / 8 * channels);
        format.nAvgBytesPerSec = format.nBlockAlign * samplesPerSecond;
        format.wBitsPerSample = (unsigned short)bitsPerSample;
        format.cbSize  = 0;

        DAT_0087E8A0->Vptr->Stop(DAT_0087E8A0);
        DAT_0087E8A0->Vptr->SetFormat(DAT_0087E8A0, &format);
        DAT_0087E8A0->Vptr->Play(DAT_0087E8A0, 0, 0, 1);
    }
}

// FUNCTION: GAMEMD 0x40A850
// Restore the current mode's PCM format, then play the primary sound buffer.
void FUN_0040A850()
{
    Pool_00402860* mode = static_cast<Pool_00402860*>(FUN_00407010());

    if (DAT_0087E8A0 != 0 && mode != 0) {
        DAT_0087E8A0->Vptr->Stop(DAT_0087E8A0);

        WAVEFORMATEX format;
        memset(&format, 0, sizeof(format));

        format.nChannels  = (unsigned short)mode->unknown_44.NumChannels;
        format.nSamplesPerSec  = mode->unknown_44.SampleRate;
        format.wFormatTag  = 1;
        format.nBlockAlign  = (unsigned short)((unsigned short)mode->unknown_44.BytesPerSample * (unsigned short)mode->unknown_44.NumChannels);
        format.nAvgBytesPerSec = format.nBlockAlign * format.nSamplesPerSec;
        format.wBitsPerSample = (unsigned short)((unsigned short)mode->unknown_44.BytesPerSample * 8);
        format.cbSize  = 0;

        DAT_0087E8A0->Vptr->SetFormat(DAT_0087E8A0, &format);
        DAT_0087E8A0->Vptr->Play(DAT_0087E8A0, 0, 0, 1);
    }
}

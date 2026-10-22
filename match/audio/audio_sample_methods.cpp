// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm of 0x401640).
//   Names cross-checked against YRpp (every
//   offset reconfirmed against the disassembly).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x401640  AudioIDXData::GetSampleInformation  (__fastcall)

#include "audio_sample_methods.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x401640  (__fastcall: pThis=ECX, index=EDX, pBuffer=stack)
//
// Decode the static WAV-header fields for sample `index` into `pBuffer`. Each
// AudioIDXEntry is 0x24 bytes, so the entry is Samples[index]; the channel/depth
// counts come from packed bit-flags ((Flags&bit)!=0)+1 == 1 or 2). When the
// "compressed" flag (0x8) is set the format/depth are forced (1, 2). Returns the
// passed-in buffer.
// ---------------------------------------------------------------------------
AudioSampleData* __fastcall AudioIDXData::GetSampleInformation(
    int index, AudioSampleData* pBuffer) const
{
    const AudioIDXEntry* entry = &this->Samples[index];

    pBuffer->Data = 4;
    pBuffer->SampleRate = entry->SampleRate;
    pBuffer->NumChannels = (entry->Flags & 1) ? 2 : 1;
    pBuffer->BlockAlign = entry->ChunkSize;

    if ((entry->Flags & 8) != 0)
    {
        pBuffer->Format = 1;
        pBuffer->BytesPerSample = 2;
        return pBuffer;
    }

    pBuffer->Format = 0;
    pBuffer->BytesPerSample = (entry->Flags & 4) ? 2 : 1;
    return pBuffer;
}

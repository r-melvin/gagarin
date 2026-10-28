// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x6614F0 and 0x661510: RGBClass writes and
//   reads its three channel bytes through IStream slots +0x10 (Write) and +0x0C (Read).
//
// Address index: 0x6614F0 0x661510

#include "leaf_batch3_methods.h"
#include "../_layout/rgb_class.h"

// FUNCTION: GAMEMD 0x6614F0
// Write the three channel bytes to a COM stream.
long RGBClass::Save(IStream_004C6320* stream)
{
    return stream->Write(this, sizeof(*this), 0);
}

// FUNCTION: GAMEMD 0x661510
// Read the three channel bytes from a COM stream.
long RGBClass::Load(IStream_004C6320* stream)
{
    return stream->Read(this, sizeof(*this), 0);
}

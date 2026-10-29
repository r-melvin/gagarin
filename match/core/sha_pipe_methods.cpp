// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry-origin 0x69E9B0 (0x26) and 0x69E9E0 (0x10), verified against the
// pinned retail image. Original helper types/names/return types are unknown.
// No constructor, destructor or native SHAPipe table is instantiated here.
#include "../_layout/sha_pipe.h"

// Opaque thiscall views for the state forwarded at SHAPipe +0x0C. No field
// layout or original helper class identity is asserted.
class ShaState
{
public:
    // FUNCTION: GAMEMD 0x69D960 -- two stack dwords; discarded result view.
    void Update(int first, int second);
    // FUNCTION: GAMEMD 0x69D9E0 -- one output pointer; discarded result view.
    void Finish(void* output);
};

// FUNCTION: GAMEMD 0x69E9B0
int SHAPipe::FUN_00631D10(int first, int second)
{
    ((ShaState*)&IsCached)->Update(first, second);
    return Pipe::FUN_00631D10(first, second);
}

// FUNCTION: GAMEMD 0x69E9E0
void SHAPipe::Result(void* out)
{
    ((ShaState*)&IsCached)->Finish(out);
}

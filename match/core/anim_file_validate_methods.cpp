// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and constants read off retail gamemd.exe v1.001 at 0x426990 via
//   the local Ghidra CLI. The receiver is the AnimFile object of
//   small_misc38_methods.h (vtable 0x7E3584); this file uses a field view of
//   the header it reads, not a second AnimFile definition.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The animation header held at +0x8C of the file object, and the six-byte
// frame table at +0x80E.
struct AnimFrameEntry_00426990
{
    unsigned short Value;       // +0x00  at most 0x100
    unsigned short unknown_02;
    unsigned short unknown_04;
};
GG_STATIC_ASSERT(sizeof(AnimFrameEntry_00426990) == 6);

struct AnimFileView_00426990
{
    char           unknown_000[0x8C];
    unsigned long  Signature;        // +0x8C  0x2046504C
    unsigned short Version;          // +0x90  must be 0x100
    unsigned short FrameCount;       // +0x92
    unsigned long  Total;            // +0x94  at most 0xFFFF
    unsigned short Limit;            // +0x98  at most 0x100
    unsigned short Format;           // +0x9A  must be 0x500
    unsigned long  Ident;            // +0x9C  0x4D494E41
    unsigned short Width;            // +0xA0  must be 0x140
    unsigned short Height;           // +0xA2  must be 0xC8
    char           unknown_0A4[4];
    unsigned char  Flag_A8;          // +0xA8  must be 0
    unsigned char  Flag_A9;          // +0xA9  at most 1
    unsigned char  Flag_AA;          // +0xAA  must be 0
    unsigned char  Flag_AB;          // +0xAB  must be 1
    char           unknown_0AC[0x80E - 0xAC];
    AnimFrameEntry_00426990 Table[1]; // +0x80E

    // FUNCTION: GAMEMD 0x426990
    bool FUN_00426990();
};
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Signature) == 0x8C);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Version) == 0x90);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, FrameCount) == 0x92);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Total) == 0x94);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Limit) == 0x98);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Format) == 0x9A);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Ident) == 0x9C);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Width) == 0xA0);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Height) == 0xA2);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Flag_A8) == 0xA8);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Flag_AB) == 0xAB);
GG_STATIC_ASSERT(offsetof(AnimFileView_00426990, Table) == 0x80E);

// FUNCTION: GAMEMD 0x426990
// Accept the animation header only when every field has its expected value
// and each frame-table entry is within range.
bool AnimFileView_00426990::FUN_00426990()
{
    if (Signature != 0x2046504C) return false;
    if (Ident != 0x4D494E41) return false;
    if (Version != 0x100) return false;
    if (Total > 0xFFFF) return false;
    if (Limit > 0x100) return false;
    if (Format != 0x500) return false;
    if (Width != 0x140) return false;
    if (Height != 0xC8) return false;
    if (Flag_A9 > 1) return false;
    if (Flag_AB != 1) return false;
    if (Flag_AA != 0) return false;
    if (Flag_A8 != 0) return false;
    for (int i = 0; i < FrameCount; i++) {
        if (Table[i].Value > 0x100) return false;
    }
    return true;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read off the user's retail gamemd.exe v1.001 at the addresses below; every name is a placeholder.
#ifndef GG_MATCH_DISPLAY_LAYER_H
#define GG_MATCH_DISPLAY_LAYER_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "com_member_release_family_methods.h"

struct DDSurface;
struct DisplayTriangle;

// The three objects of the overlay pass (0x8A0E08, 0x8A0E0C, 0x8A0E10). Their methods are contiguous
// (0x4A33A0, 0x4A3660, 0x4A3840), so one class is assumed; the binary does not state it.
struct DisplayLayer
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x4A33A0 (decl; reloc)
    int FUN_004A33A0(int arg);
    // FUNCTION: GAMEMD 0x4A3660 (decl; reloc)
    void FUN_004A3660(DDSurface* surface);
    // FUNCTION: GAMEMD 0x4A3840 (decl; reloc)
    void FUN_004A3840(DisplayTriangle* batch);
};

// The 0x78-byte texture object of the overlay pass (0x8A0E04 / 0x8A0E08 / 0x8A0E0C): the layer methods act
// on it, 0x4A3370 releases its two interfaces. Size from operator new(0x78) at 0x4C17E5 / 0x4C194A.
struct ComPair_004A3370 : public DisplayLayer
{
    char  unknown_04[0x70 - 4];
    IUnk* Second;   // +0x70
    IUnk* First;    // +0x74
    // FUNCTION: GAMEMD 0x4A3270 (decl; reloc) -- the constructor: width, height and kind (0 plain, 1 filled, 2 target).
    ComPair_004A3370(int width, int height, int kind);
};
GG_STATIC_ASSERT(offsetof(ComPair_004A3370, Second) == 0x70);
GG_STATIC_ASSERT(offsetof(ComPair_004A3370, First) == 0x74);
GG_STATIC_ASSERT(sizeof(ComPair_004A3370) == 0x78);

// FUNCTION: GAMEMD 0x4A3370 (decl; reloc) -- release both interfaces of a texture (defined in leaf_sweep_w1b.cpp).
void __fastcall FUN_004A3370(ComPair_004A3370* self);

#endif  // GG_MATCH_DISPLAY_LAYER_H

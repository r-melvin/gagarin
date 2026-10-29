// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_UI_TRIVIAL_TU065_METHODS_H
#define GG_MATCH_UI_TRIVIAL_TU065_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004A5950;

// A direction word the way 0x4A5960 handles it: the 16-bit direction with its
// two bytes addressable, followed by two bytes that ride along unchanged.
struct DirWord_004A5960
{
    union {
        unsigned int Whole;
        struct {
            union {
                unsigned short Raw;
                struct {
                    unsigned char Low;
                    unsigned char High;
                };
            };
            unsigned short Padding;
        };
    };
};
GG_STATIC_ASSERT(sizeof(DirWord_004A5960) == 4);

struct Obj_004A5950
{
    char unknown_00[0xB4];
    int unknown_B4;   // +0x00B4
    // FUNCTION: GAMEMD 0x4A5950
    int FUN_004A5950() const;
    int unknown_B8;   // +0x00B8
    int unknown_BC;   // +0x00BC
    // FUNCTION: GAMEMD 0x4A5960
    void FUN_004A5960(DirWord_004A5960 dir);
};
GG_STATIC_ASSERT(offsetof(Obj_004A5950, unknown_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(Obj_004A5950, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(Obj_004A5950, unknown_BC) == 0xBC);


// FUNCTION: GAMEMD 0x4A5090
void __cdecl FUN_004A5090();

#endif  // GG_MATCH_UI_TRIVIAL_TU065_METHODS_H

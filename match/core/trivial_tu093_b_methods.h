// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU093_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU093_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004F3A90;

struct Obj_004F3A90
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4(unsigned char);
    char unknown_04[0x4];
    unsigned char unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x4F3A90
    void FUN_004F3A90(unsigned char a1);
};
GG_STATIC_ASSERT(offsetof(Obj_004F3A90, unknown_08) == 0x8);



#endif  // GG_MATCH_CORE_TRIVIAL_TU093_B_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_UI_TRIVIAL_TU228_B_METHODS_H
#define GG_MATCH_UI_TRIVIAL_TU228_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006D0F00;

struct Obj_006D0F00
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual void vf_8();
    virtual void vf_9();
    virtual void vf_10();
    virtual void vf_11();
    virtual void vf_12();
    virtual void vf_13();
    virtual void vf_14(int);
    char unknown_04[0x5541];
    unsigned char unknown_5545;   // +0x5545
    // FUNCTION: GAMEMD 0x6D0F00
    void FUN_006D0F00();
};
GG_STATIC_ASSERT(offsetof(Obj_006D0F00, unknown_5545) == 0x5545);



#endif  // GG_MATCH_UI_TRIVIAL_TU228_B_METHODS_H

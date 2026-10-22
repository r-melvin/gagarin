// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_UI_TRIVIAL_TU228_METHODS_H
#define GG_MATCH_UI_TRIVIAL_TU228_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Gptr_00887368;
struct Obj_006D0FB0;
struct Obj_006D15F0;

// GLOBAL: GAMEMD 0x87F6CC
extern int DAT_0087F6CC;
// GLOBAL: GAMEMD 0x887368
extern Gptr_00887368* DAT_00887368;
// GLOBAL: GAMEMD 0xB0CC20
extern int DAT_00B0CC20;
// GLOBAL: GAMEMD 0xB0CC40
extern char DAT_00B0CC40[];
// GLOBAL: GAMEMD 0xB0CD28
extern int DAT_00B0CD28;

struct Gptr_00887368
{
    // FUNCTION: GAMEMD 0x724730
    void FUN_00724730(int);
};

struct Obj_006D0FB0
{
    char unknown_00[0x20];
    int unknown_20;   // +0x0020
    int unknown_24;   // +0x0024
    char unknown_28[0x5];
    unsigned char unknown_2D;   // +0x002D
    char unknown_2E[0x2];
    int unknown_30;   // +0x0030
    char unknown_34[0x1C];
    int unknown_50;   // +0x0050
};
GG_STATIC_ASSERT(offsetof(Obj_006D0FB0, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Obj_006D0FB0, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_006D0FB0, unknown_2D) == 0x2D);
GG_STATIC_ASSERT(offsetof(Obj_006D0FB0, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_006D0FB0, unknown_50) == 0x50);

struct Obj_006D15F0
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
    virtual void vf_13(void*);
    // FUNCTION: GAMEMD 0x6D15F0
    void FUN_006D15F0();
};


// FUNCTION: GAMEMD 0x6CFDF0
int FUN_006CFDF0(int a1);
// FUNCTION: GAMEMD 0x6CFE10
int FUN_006CFE10(int a1);
// FUNCTION: GAMEMD 0x6D0E50
void __cdecl FUN_006D0E50();
// FUNCTION: GAMEMD 0x6D0FB0
void FUN_006D0FB0(Obj_006D0FB0* a1, int a2, int a3);

#endif  // GG_MATCH_UI_TRIVIAL_TU228_METHODS_H

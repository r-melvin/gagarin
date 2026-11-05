// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU019_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU019_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

struct Arg1_0041C150;
struct Obj_0041B900;
struct Obj_0041B910;
struct Obj_0041B9E0;
struct Obj_0041C160;




struct Arg1_0041C150
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg1_0041C150, unknown_00) == 0x0);



struct Obj_0041B900
{
    // FUNCTION: GAMEMD 0x41B900
    void FUN_0041B900();
};

struct Obj_0041B910
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
    virtual void vf_14();
    virtual void vf_15();
    virtual void vf_16();
    virtual void vf_17();
    virtual void vf_18();
    virtual void vf_19();
    virtual void vf_20();
    // FUNCTION: GAMEMD 0x41B910
    void FUN_0041B910();
};

struct Obj_0041B9E0
{
    char unknown_00[0x6D5];
    unsigned char unknown_6D5;   // +0x06D5
    // FUNCTION: GAMEMD 0x41B9E0
    unsigned char FUN_0041B9E0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0041B9E0, unknown_6D5) == 0x6D5);












struct Obj_0041C160
{
    char unknown_00[0x560];
    int unknown_560;   // +0x0560
    // FUNCTION: GAMEMD 0x41C160
    void FUN_0041C160(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0041C160, unknown_560) == 0x560);

// FUNCTION: GAMEMD 0x414A10
void __stdcall FUN_00414A10(int a1, int a2);
// FUNCTION: GAMEMD 0x41A140
void __cdecl FUN_0041A140();

#endif  // GG_MATCH_CORE_TRIVIAL_TU019_METHODS_H

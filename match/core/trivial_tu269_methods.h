// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU269_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU269_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0075F880;
struct Obj_0075F890;
struct Obj_0075F8A0;
struct Obj_007610D0;
struct Obj_007631F0;

struct Obj_0075F880
{
    // FUNCTION: GAMEMD 0x75F880
    int FUN_0075F880() const;
};

struct Obj_0075F890
{
    // FUNCTION: GAMEMD 0x75F890
    int FUN_0075F890() const;
};

struct Obj_0075F8A0
{
    // FUNCTION: GAMEMD 0x75F8A0
    int FUN_0075F8A0() const;
};

struct Obj_007610D0
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
    virtual void vf_21();
    virtual void vf_22();
    virtual void vf_23();
    virtual void vf_24();
    virtual void vf_25();
    virtual void vf_26();
    virtual void vf_27();
    virtual void vf_28();
    virtual void vf_29();
    virtual void vf_30();
    virtual void vf_31();
    virtual void vf_32();
    virtual void vf_33();
    virtual void vf_34();
    virtual void vf_35();
    virtual void vf_36();
    virtual void vf_37();
    virtual void vf_38();
    virtual void vf_39();
    virtual void vf_40();
    virtual void vf_41();
    virtual void vf_42();
    virtual void vf_43();
    virtual void vf_44();
    virtual void vf_45();
    virtual void vf_46();
    virtual void vf_47();
    virtual void vf_48();
    virtual void vf_49();
    virtual void vf_50();
    virtual void vf_51();
    virtual void vf_52();
    virtual void vf_53();
    virtual void vf_54();
    virtual void vf_55();
    virtual void vf_56();
    virtual void vf_57();
    virtual void vf_58();
    virtual void vf_59();
    virtual void vf_60();
    virtual void vf_61();
    virtual void vf_62();
    char unknown_04[0x1CC];
    int unknown_1D0;   // +0x01D0
    // FUNCTION: GAMEMD 0x7610D0
    void FUN_007610D0();
};
GG_STATIC_ASSERT(offsetof(Obj_007610D0, unknown_1D0) == 0x1D0);

struct Obj_007631F0
{
    // FUNCTION: GAMEMD 0x7631F0
    int FUN_007631F0() const;
};


// FUNCTION: GAMEMD 0x762060
void __cdecl FUN_00762060();
// FUNCTION: GAMEMD 0x762AE0
void __cdecl FUN_00762AE0();

#endif  // GG_MATCH_CORE_TRIVIAL_TU269_METHODS_H

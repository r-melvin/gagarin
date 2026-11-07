// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU086_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU086_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

struct Obj_004D94A0;
struct Obj_004DA2A0;
struct Obj_004DFA50;

// FUNCTION: GAMEMD 0x5F6C30 (declaration)
bool FUN_005F6C30(Obj_004DFA50*, int);

struct Obj_004D94A0
{
    char unknown_00[0x5A0];
    int unknown_5A0;   // +0x05A0
    // FUNCTION: GAMEMD 0x4D94A0
    void FUN_004D94A0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_004D94A0, unknown_5A0) == 0x5A0);


struct Obj_004DA2A0
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
    virtual void vf_63();
    virtual void vf_64();
    virtual void vf_65();
    virtual void vf_66();
    virtual void vf_67();
    virtual void vf_68();
    virtual void vf_69();
    virtual void vf_70();
    virtual void vf_71();
    virtual void vf_72();
    virtual void vf_73();
    virtual void vf_74();
    virtual void vf_75();
    virtual void vf_76();
    virtual void vf_77();
    virtual void vf_78();
    virtual void vf_79();
    virtual void vf_80();
    virtual void vf_81();
    virtual void vf_82();
    virtual void vf_83();
    virtual void vf_84();
    virtual void vf_85();
    virtual void vf_86();
    virtual void vf_87();
    virtual void vf_88();
    virtual void vf_89();
    virtual void vf_90();
    virtual void vf_91();
    virtual void vf_92();
    virtual void vf_93();
    virtual void vf_94();
    virtual void vf_95();
    virtual void vf_96();
    virtual int vf_97();
    // FUNCTION: GAMEMD 0x4DA2A0
    bool FUN_004DA2A0();
};











struct Obj_004DFA50
{
    char unknown_00[0x6AD];
    unsigned char unknown_6AD;   // +0x06AD
};
GG_STATIC_ASSERT(offsetof(Obj_004DFA50, unknown_6AD) == 0x6AD);


// FUNCTION: GAMEMD 0x4DFA50
unsigned char FUN_004DFA50(Obj_004DFA50* a1, int a2);
// FUNCTION: GAMEMD 0x4E0C30
void __cdecl FUN_004E0C30();

#endif  // GG_MATCH_CORE_TRIVIAL_TU086_METHODS_H

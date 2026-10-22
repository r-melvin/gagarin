// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU086_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU086_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_004DA020;
struct Arg2_004DA020;
struct Obj_004D94A0;
struct Obj_004D9C00;
struct Obj_004DA2A0;
struct Obj_004DBA30;
struct Obj_004DBA40;
struct Obj_004DDC40;
struct Obj_004DE750;
struct Obj_004DE760;
struct Obj_004DF1A0;
struct Obj_004DF1C0;
struct Obj_004DF1D0;
struct Obj_004DF1E0;
struct Obj_004DF310;
struct Obj_004DFA50;

// FUNCTION: GAMEMD 0x5F6C30 (declaration)
bool FUN_005F6C30(Obj_004DFA50*, int);

struct Arg1_004DA020
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg1_004DA020, unknown_00) == 0x0);

struct Arg2_004DA020
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg2_004DA020, unknown_00) == 0x0);

struct Obj_004D94A0
{
    char unknown_00[0x5A0];
    int unknown_5A0;   // +0x05A0
    // FUNCTION: GAMEMD 0x4D94A0
    void FUN_004D94A0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_004D94A0, unknown_5A0) == 0x5A0);

struct Obj_004D9C00
{
    // FUNCTION: GAMEMD 0x4D9C00
    int FUN_004D9C00() const;
};

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

struct Obj_004DBA30
{
    // FUNCTION: GAMEMD 0x4DBA30
    void FUN_004DBA30();
};

struct Obj_004DBA40
{
    // FUNCTION: GAMEMD 0x4DBA40
    void FUN_004DBA40();
};

struct Obj_004DDC40
{
    char unknown_00[0x684];
    char unknown_684;   // +0x0684
    // FUNCTION: GAMEMD 0x4DDC40
    char FUN_004DDC40(int a1);
    // FUNCTION: GAMEMD 0x5F6A70
    bool FUN_005F6A70(int);
};
GG_STATIC_ASSERT(offsetof(Obj_004DDC40, unknown_684) == 0x684);

struct Obj_004DE750
{
    // FUNCTION: GAMEMD 0x4DE750
    void FUN_004DE750(int a1);
};

struct Obj_004DE760
{
    // FUNCTION: GAMEMD 0x4DE760
    void FUN_004DE760(int a1);
};

struct Obj_004DF1A0
{
    char unknown_00[0x5C4];
    int unknown_5C4;   // +0x05C4
    int unknown_5C8;   // +0x05C8
    int unknown_5CC;   // +0x05CC
    char unknown_5D0[0x1];
    unsigned char unknown_5D1;   // +0x05D1
    // FUNCTION: GAMEMD 0x4DF1A0
    void FUN_004DF1A0();
};
GG_STATIC_ASSERT(offsetof(Obj_004DF1A0, unknown_5C4) == 0x5C4);
GG_STATIC_ASSERT(offsetof(Obj_004DF1A0, unknown_5C8) == 0x5C8);
GG_STATIC_ASSERT(offsetof(Obj_004DF1A0, unknown_5CC) == 0x5CC);
GG_STATIC_ASSERT(offsetof(Obj_004DF1A0, unknown_5D1) == 0x5D1);

struct Obj_004DF1C0
{
    char unknown_00[0x5C4];
    int unknown_5C4;   // +0x05C4
    // FUNCTION: GAMEMD 0x4DF1C0
    bool FUN_004DF1C0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004DF1C0, unknown_5C4) == 0x5C4);

struct Obj_004DF1D0
{
    char unknown_00[0x5D1];
    unsigned char unknown_5D1;   // +0x05D1
    // FUNCTION: GAMEMD 0x4DF1D0
    unsigned char FUN_004DF1D0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004DF1D0, unknown_5D1) == 0x5D1);

struct Obj_004DF1E0
{
    char unknown_00[0x5C4];
    int unknown_5C4;   // +0x05C4
    // FUNCTION: GAMEMD 0x4DF1E0
    int FUN_004DF1E0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004DF1E0, unknown_5C4) == 0x5C4);

struct Obj_004DF310
{
    char unknown_00[0x5C4];
    int unknown_5C4;   // +0x05C4
    // FUNCTION: GAMEMD 0x4DF310
    bool FUN_004DF310() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004DF310, unknown_5C4) == 0x5C4);

struct Obj_004DFA50
{
    char unknown_00[0x6AD];
    unsigned char unknown_6AD;   // +0x06AD
};
GG_STATIC_ASSERT(offsetof(Obj_004DFA50, unknown_6AD) == 0x6AD);


// FUNCTION: GAMEMD 0x4DA020
Arg1_004DA020* __stdcall FUN_004DA020(Arg1_004DA020* a1, Arg2_004DA020* a2);
// FUNCTION: GAMEMD 0x4DFA50
unsigned char FUN_004DFA50(Obj_004DFA50* a1, int a2);
// FUNCTION: GAMEMD 0x4E0C30
void __cdecl FUN_004E0C30();

#endif  // GG_MATCH_CORE_TRIVIAL_TU086_METHODS_H

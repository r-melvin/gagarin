// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU099_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU099_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

struct Obj_0051F620;
struct Obj_005216C0;
struct Obj_00521C40;
struct Obj_00521C40_6C0;
struct Obj_005224E0;
struct Obj_005224E0_6C0;
struct Obj_005224F0;
struct Obj_005224F0_6C0;
struct Obj_00522540;
struct Obj_00522540_6C0;
struct Obj_005228B0;
struct Obj_005228C0;
struct Obj_00522D00;
struct Obj_00522D20;

// FUNCTION: GAMEMD 0x4DED70 (declaration)
void FUN_004DED70(Obj_005216C0*, int);
// FUNCTION: GAMEMD 0x521320 (declaration)
int FUN_00521320(Obj_0051F620*, int);
// FUNCTION: GAMEMD 0x70F070 (declaration)
void FUN_0070F070(Obj_005228B0*, int);
// FUNCTION: GAMEMD 0x70F090 (declaration)
void FUN_0070F090(Obj_005228C0*, int);

struct Obj_0051F620
{
    // FUNCTION: GAMEMD 0x4D5070
    void FUN_004D5070();
};


struct Obj_005216C0
{
};



struct Obj_00521C40
{
    char unknown_00[0x6C0];
    Obj_00521C40_6C0* unknown_6C0;   // +0x06C0
    char unknown_6C4[0x10];
    int unknown_6D4;   // +0x06D4
    // FUNCTION: GAMEMD 0x521C40
    Obj_00521C40_6C0* FUN_00521C40();
};
GG_STATIC_ASSERT(offsetof(Obj_00521C40, unknown_6C0) == 0x6C0);
GG_STATIC_ASSERT(offsetof(Obj_00521C40, unknown_6D4) == 0x6D4);

struct Obj_00521C40_6C0
{
    char unknown_00[0xEBC];
    unsigned char unknown_EBC;   // +0x0EBC
};
GG_STATIC_ASSERT(offsetof(Obj_00521C40_6C0, unknown_EBC) == 0xEBC);




struct Obj_005224E0
{
    char unknown_00[0x6C0];
    Obj_005224E0_6C0* unknown_6C0;   // +0x06C0
    // FUNCTION: GAMEMD 0x5224E0
    unsigned char FUN_005224E0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_005224E0, unknown_6C0) == 0x6C0);

struct Obj_005224E0_6C0
{
    char unknown_00[0xEC8];
    unsigned char unknown_EC8;   // +0x0EC8
};
GG_STATIC_ASSERT(offsetof(Obj_005224E0_6C0, unknown_EC8) == 0xEC8);

struct Obj_005224F0
{
    char unknown_00[0x6C0];
    Obj_005224F0_6C0* unknown_6C0;   // +0x06C0
    // FUNCTION: GAMEMD 0x5224F0
    unsigned char FUN_005224F0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_005224F0, unknown_6C0) == 0x6C0);

struct Obj_005224F0_6C0
{
    char unknown_00[0x6C4];
    int unknown_6C4;   // +0x06C4
};
GG_STATIC_ASSERT(offsetof(Obj_005224F0_6C0, unknown_6C4) == 0x6C4);

struct Obj_00522540
{
    char unknown_00[0x6C0];
    Obj_00522540_6C0* unknown_6C0;   // +0x06C0
    // FUNCTION: GAMEMD 0x522540
    unsigned char FUN_00522540() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00522540, unknown_6C0) == 0x6C0);

struct Obj_00522540_6C0
{
    char unknown_00[0x6AC];
    unsigned char unknown_6AC;   // +0x06AC
};
GG_STATIC_ASSERT(offsetof(Obj_00522540_6C0, unknown_6AC) == 0x6AC);

struct Obj_005228B0
{
};

struct Obj_005228C0
{
};

struct Obj_00522D00
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
    virtual void vf_97();
    virtual void vf_98();
    virtual void vf_99();
    virtual void vf_100();
    virtual void vf_101();
    virtual void vf_102();
    virtual void vf_103();
    virtual void vf_104();
    virtual void vf_105();
    virtual void vf_106();
    virtual void vf_107();
    virtual void vf_108();
    virtual void vf_109();
    virtual void vf_110();
    virtual void vf_111();
    virtual void vf_112();
    virtual void vf_113();
    virtual void vf_114();
    virtual void vf_115();
    virtual void vf_116();
    virtual void vf_117();
    virtual void vf_118();
    virtual void vf_119();
    virtual void vf_120();
    virtual void vf_121();
    virtual void vf_122(int, int);
    char unknown_04[0xA8];
    int unknown_AC;   // +0x00AC
    // FUNCTION: GAMEMD 0x522D00
    void FUN_00522D00();
};
GG_STATIC_ASSERT(offsetof(Obj_00522D00, unknown_AC) == 0xAC);

struct Obj_00522D20
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
    virtual void vf_97();
    virtual void vf_98();
    virtual void vf_99();
    virtual void vf_100();
    virtual void vf_101();
    virtual void vf_102();
    virtual void vf_103();
    virtual void vf_104();
    virtual void vf_105();
    virtual void vf_106();
    virtual void vf_107();
    virtual void vf_108();
    virtual void vf_109();
    virtual void vf_110();
    virtual void vf_111();
    virtual void vf_112();
    virtual void vf_113();
    virtual void vf_114();
    virtual void vf_115();
    virtual void vf_116();
    virtual void vf_117();
    virtual void vf_118();
    virtual void vf_119();
    virtual void vf_120();
    virtual void vf_121();
    virtual void vf_122(int, int);
    // FUNCTION: GAMEMD 0x522D20
    void FUN_00522D20();
};




// FUNCTION: GAMEMD 0x51F620
void FUN_0051F620(Obj_0051F620* a1, int a2);
// FUNCTION: GAMEMD 0x5216C0
void FUN_005216C0(Obj_005216C0* a1, int a2);
// FUNCTION: GAMEMD 0x5228B0
void FUN_005228B0(Obj_005228B0* a1, int a2);
// FUNCTION: GAMEMD 0x5228C0
void FUN_005228C0(Obj_005228C0* a1, int a2);
// FUNCTION: GAMEMD 0x522A50
void __stdcall FUN_00522A50(int a1);

#endif  // GG_MATCH_CORE_TRIVIAL_TU099_METHODS_H

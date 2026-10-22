// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU180_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU180_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class PlanningNotify;
class PlanningNodeClass;

struct Obj_00634800;
struct Obj_00634950;
struct Obj_00634960;
struct Obj_00636110;
struct Obj_00636520;
struct Obj_00636530;
struct Obj_00636540;
struct Obj_00636550;
struct Obj_00636550_0;
struct Obj_00636570;
struct Obj_00636DA0;
struct Obj_00636DD0;
struct Obj_00636DE0;
struct Obj_00636FA0;
struct Obj_00636FC0;
struct Obj_00636FD0;
struct Obj_00636FE0;
struct Obj_00637000;
struct Obj_00637010;
struct Obj_00637020;
struct Obj_00637030;
struct Obj_0063A210;
struct Obj_0063D500;
struct Obj_0063D520;

// GLOBAL: GAMEMD 0x836BD4
extern char DAT_00836BD4[];
// GLOBAL: GAMEMD 0xAC4C90
extern int DAT_00AC4C90;
// GLOBAL: GAMEMD 0xAC4CF4
extern bool DAT_00AC4CF4;

// FUNCTION: GAMEMD 0x730A90 (declaration)
void FUN_00730A90(int, int);
// FUNCTION: GAMEMD 0x731CD0 (declaration)
int __cdecl FUN_00731CD0();
// FUNCTION: GAMEMD 0x731CE0 (declaration)
int __cdecl FUN_00731CE0();
// FUNCTION: GAMEMD 0x734E60 (declaration)
int FUN_00734E60(Obj_0063A210*, int, void*, int);

struct Obj_00634800
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x634800
    int* FUN_00634800();
};
GG_STATIC_ASSERT(offsetof(Obj_00634800, unknown_38) == 0x38);

struct Obj_00634950
{
    char unknown_00[0x1C];
    unsigned char unknown_1C;   // +0x001C
    // FUNCTION: GAMEMD 0x634950
    void FUN_00634950();
};
GG_STATIC_ASSERT(offsetof(Obj_00634950, unknown_1C) == 0x1C);

struct Obj_00634960
{
    char unknown_00[0x1C];
    unsigned char unknown_1C;   // +0x001C
    // FUNCTION: GAMEMD 0x634960
    unsigned char FUN_00634960() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00634960, unknown_1C) == 0x1C);

struct Obj_00636110
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x636110
    int FUN_00636110() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00636110, unknown_00) == 0x0);

struct Obj_00636520
{
    char unknown_00[0x1C];
    unsigned char unknown_1C;   // +0x001C
    // FUNCTION: GAMEMD 0x636520
    void FUN_00636520();
};
GG_STATIC_ASSERT(offsetof(Obj_00636520, unknown_1C) == 0x1C);

struct Obj_00636530
{
    char unknown_00[0x1C];
    unsigned char unknown_1C;   // +0x001C
    // FUNCTION: GAMEMD 0x636530
    void FUN_00636530();
};
GG_STATIC_ASSERT(offsetof(Obj_00636530, unknown_1C) == 0x1C);

struct Obj_00636540
{
    char unknown_00[0x1C];
    unsigned char unknown_1C;   // +0x001C
    // FUNCTION: GAMEMD 0x636540
    unsigned char FUN_00636540() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00636540, unknown_1C) == 0x1C);

struct Obj_00636550
{
    Obj_00636550_0* unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x636550
    int FUN_00636550();
};
GG_STATIC_ASSERT(offsetof(Obj_00636550, unknown_00) == 0x0);

struct Obj_00636550_0
{
    char unknown_00[0xAC];
    int unknown_AC;   // +0x00AC
    char unknown_B0[0x4];
    int unknown_B4;   // +0x00B4
};
GG_STATIC_ASSERT(offsetof(Obj_00636550_0, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(Obj_00636550_0, unknown_B4) == 0xB4);

struct Obj_00636570
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    char unknown_18[0x74];
    int unknown_8C;   // +0x008C
    // FUNCTION: GAMEMD 0x636570
    int FUN_00636570();
};
GG_STATIC_ASSERT(offsetof(Obj_00636570, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00636570, unknown_8C) == 0x8C);

struct Obj_00636DA0
{
    char unknown_00[0x8C];
    int unknown_8C;   // +0x008C
    // FUNCTION: GAMEMD 0x636DA0
    unsigned char FUN_00636DA0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00636DA0, unknown_8C) == 0x8C);

struct Obj_00636DD0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    char unknown_18[0x74];
    int unknown_8C;   // +0x008C
    // FUNCTION: GAMEMD 0x636DD0
    int FUN_00636DD0();
};
GG_STATIC_ASSERT(offsetof(Obj_00636DD0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00636DD0, unknown_8C) == 0x8C);

struct Obj_00636DE0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    char unknown_18[0x74];
    int unknown_8C;   // +0x008C
    // FUNCTION: GAMEMD 0x636DE0
    int FUN_00636DE0();
};
GG_STATIC_ASSERT(offsetof(Obj_00636DE0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00636DE0, unknown_8C) == 0x8C);

struct Obj_00636FA0
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    int unknown_94;   // +0x0094
    unsigned char unknown_98;   // +0x0098
    // FUNCTION: GAMEMD 0x636FA0
    void FUN_00636FA0(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_00636FA0, unknown_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Obj_00636FA0, unknown_94) == 0x94);
GG_STATIC_ASSERT(offsetof(Obj_00636FA0, unknown_98) == 0x98);

struct Obj_00636FC0
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x636FC0
    int FUN_00636FC0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00636FC0, unknown_90) == 0x90);

struct Obj_00636FD0
{
    char unknown_00[0x94];
    int unknown_94;   // +0x0094
    // FUNCTION: GAMEMD 0x636FD0
    int FUN_00636FD0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00636FD0, unknown_94) == 0x94);

struct Obj_00636FE0
{
    char unknown_00[0x94];
    int unknown_94;   // +0x0094
    // FUNCTION: GAMEMD 0x636FE0
    int FUN_00636FE0();
};
GG_STATIC_ASSERT(offsetof(Obj_00636FE0, unknown_94) == 0x94);

struct Obj_00637000
{
    char unknown_00[0x94];
    int unknown_94;   // +0x0094
    // FUNCTION: GAMEMD 0x637000
    bool FUN_00637000() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00637000, unknown_94) == 0x94);

struct Obj_00637010
{
    char unknown_00[0x94];
    int unknown_94;   // +0x0094
    // FUNCTION: GAMEMD 0x637010
    bool FUN_00637010() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00637010, unknown_94) == 0x94);

struct Obj_00637020
{
    char unknown_00[0x98];
    unsigned char unknown_98;   // +0x0098
    // FUNCTION: GAMEMD 0x637020
    unsigned char FUN_00637020() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00637020, unknown_98) == 0x98);

struct Obj_00637030
{
    char unknown_00[0x99];
    unsigned char unknown_99;   // +0x0099
    // FUNCTION: GAMEMD 0x637030
    unsigned char FUN_00637030() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00637030, unknown_99) == 0x99);

struct Obj_0063A210
{
    // FUNCTION: GAMEMD 0x63A210
    void FUN_0063A210();
};

struct Obj_0063D500
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
    // FUNCTION: GAMEMD 0x63D500
    int FUN_0063D500();
};

struct Obj_0063D520
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
    virtual void vf_122();
    virtual void vf_123();
    virtual void vf_124();
    virtual void vf_125();
    virtual void vf_126();
    virtual void vf_127();
    virtual void vf_128();
    virtual void vf_129();
    virtual void vf_130();
    virtual void vf_131();
    virtual void vf_132();
    virtual void vf_133();
    virtual void vf_134();
    virtual void vf_135();
    virtual void vf_136();
    virtual void vf_137();
    virtual void vf_138();
    virtual void vf_139();
    virtual void vf_140();
    virtual void vf_141();
    virtual void vf_142();
    virtual void vf_143();
    virtual void vf_144();
    virtual void vf_145();
    virtual void vf_146();
    virtual void vf_147();
    virtual void vf_148();
    virtual void vf_149();
    virtual void vf_150();
    virtual void vf_151();
    virtual void vf_152();
    virtual void vf_153();
    virtual void vf_154();
    virtual void vf_155();
    virtual void vf_156();
    virtual void vf_157();
    virtual void vf_158();
    virtual void vf_159();
    virtual void vf_160();
    virtual void vf_161();
    virtual void vf_162();
    virtual void vf_163();
    virtual void vf_164();
    virtual void vf_165();
    virtual void vf_166();
    virtual void vf_167();
    virtual void vf_168();
    virtual void vf_169();
    virtual void vf_170();
    virtual void vf_171();
    virtual void vf_172();
    virtual void vf_173();
    virtual void vf_174();
    virtual void vf_175();
    virtual void vf_176();
    virtual void vf_177();
    virtual void vf_178();
    virtual void vf_179();
    virtual void vf_180();
    virtual void vf_181();
    virtual void vf_182();
    virtual void vf_183();
    virtual void vf_184();
    virtual void vf_185();
    virtual void vf_186();
    virtual void vf_187();
    virtual void vf_188();
    virtual void vf_189();
    virtual void vf_190();
    virtual void vf_191();
    virtual void vf_192();
    virtual void vf_193();
    virtual void vf_194();
    virtual void vf_195();
    virtual void vf_196();
    virtual void vf_197();
    virtual void vf_198();
    virtual void vf_199();
    virtual void vf_200();
    virtual void vf_201();
    virtual void vf_202();
    virtual void vf_203();
    virtual void vf_204();
    virtual void vf_205();
    virtual void vf_206();
    virtual void vf_207();
    virtual void vf_208();
    virtual void vf_209();
    virtual void vf_210();
    virtual void vf_211();
    virtual void vf_212();
    virtual void vf_213();
    virtual void vf_214();
    virtual void vf_215();
    virtual void vf_216();
    virtual void vf_217();
    virtual void vf_218();
    virtual void vf_219();
    virtual void vf_220();
    virtual void vf_221();
    virtual void vf_222();
    virtual void vf_223();
    virtual void vf_224();
    virtual void vf_225();
    virtual void vf_226();
    virtual void vf_227();
    virtual void vf_228();
    virtual void vf_229();
    virtual void vf_230();
    virtual void vf_231();
    virtual void vf_232();
    virtual void vf_233();
    virtual void vf_234();
    virtual void vf_235();
    virtual void vf_236();
    virtual void vf_237();
    virtual void vf_238();
    virtual void vf_239();
    virtual void vf_240();
    virtual void vf_241();
    virtual void vf_242();
    virtual void vf_243();
    virtual void vf_244();
    virtual void vf_245();
    virtual void vf_246();
    virtual void vf_247();
    virtual void vf_248();
    virtual void vf_249();
    virtual void vf_250();
    virtual void vf_251();
    virtual void vf_252();
    virtual void vf_253();
    virtual void vf_254();
    virtual void vf_255();
    virtual void vf_256();
    virtual void vf_257();
    virtual void vf_258();
    virtual void vf_259();
    virtual void vf_260();
    virtual void vf_261();
    virtual void vf_262();
    virtual void vf_263();
    virtual void vf_264();
    virtual void vf_265();
    virtual void vf_266();
    virtual void vf_267();
    virtual void vf_268();
    virtual void vf_269();
    virtual void vf_270();
    virtual void vf_271();
    virtual void vf_272();
    virtual void vf_273();
    virtual void vf_274();
    virtual void vf_275();
    virtual void vf_276();
    virtual void vf_277();
    virtual void vf_278();
    virtual void vf_279();
    virtual void vf_280();
    virtual void vf_281();
    virtual void vf_282();
    virtual void vf_283();
    virtual void vf_284();
    virtual void vf_285();
    virtual void vf_286();
    virtual void vf_287();
    virtual void vf_288();
    virtual void vf_289();
    virtual void vf_290();
    virtual void vf_291();
    virtual void vf_292();
    virtual void vf_293();
    virtual void vf_294();
    virtual void vf_295();
    virtual void vf_296();
    virtual void vf_297();
    virtual void vf_298();
    virtual void vf_299();
    virtual void vf_300();
    virtual int vf_301();
    // FUNCTION: GAMEMD 0x63D520
    int FUN_0063D520();
};


// FUNCTION: GAMEMD 0x637060
void FUN_00637060(PlanningNotify* a1);
// FUNCTION: GAMEMD 0x637DB0
bool FUN_00637DB0(int a1);
// FUNCTION: GAMEMD 0x638B50
int FUN_00638B50(int a1);
// FUNCTION: GAMEMD 0x638C20
int FUN_00638C20(int a1);
// FUNCTION: GAMEMD 0x63A4A0
void FUN_0063A4A0(int a1);
// FUNCTION: GAMEMD 0x63AD30
void FUN_0063AD30(PlanningNodeClass* a1);
// FUNCTION: GAMEMD 0x63AD40
PlanningNodeClass* __cdecl FUN_0063AD40();

#endif  // GG_MATCH_CORE_TRIVIAL_TU180_METHODS_H

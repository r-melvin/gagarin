// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU099_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU099_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0051F620;
struct Obj_0051FAF0;
struct Obj_005216C0;
struct Obj_00521B20;
struct Obj_00521B40;
struct Obj_00521C40;
struct Obj_00521C40_6C0;
struct Obj_005220F0;
struct Obj_005224D0;
struct Obj_005224D0_6C0;
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
struct Obj_005232F0;
struct Obj_00523340;

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

struct Obj_0051FAF0
{
    char unknown_00[0x6C0];
    int unknown_6C0;   // +0x06C0
    // FUNCTION: GAMEMD 0x51FAF0
    int FUN_0051FAF0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0051FAF0, unknown_6C0) == 0x6C0);

struct Obj_005216C0
{
};

struct Obj_00521B20
{
    char unknown_00[0x6C4];
    int unknown_6C4;   // +0x06C4
    // FUNCTION: GAMEMD 0x521B20
    void FUN_00521B20();
};
GG_STATIC_ASSERT(offsetof(Obj_00521B20, unknown_6C4) == 0x6C4);

struct Obj_00521B40
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
    virtual void vf_301();
    virtual void vf_302();
    virtual void vf_303();
    virtual void vf_304();
    virtual void vf_305();
    virtual void vf_306();
    virtual void vf_307();
    virtual void vf_308();
    virtual void vf_309();
    virtual void vf_310();
    virtual void vf_311();
    virtual void vf_312();
    virtual void vf_313();
    virtual void vf_314();
    virtual void vf_315();
    virtual void vf_316();
    virtual void vf_317();
    virtual void vf_318();
    virtual void vf_319();
    virtual void vf_320();
    virtual void vf_321();
    virtual void vf_322();
    virtual void vf_323();
    virtual void vf_324();
    virtual void vf_325();
    virtual void vf_326();
    virtual void vf_327();
    virtual void vf_328();
    virtual void vf_329();
    virtual void vf_330();
    virtual void vf_331();
    virtual void vf_332();
    virtual void vf_333();
    virtual void vf_334();
    virtual void vf_335();
    virtual void vf_336();
    virtual void vf_337();
    virtual void vf_338();
    virtual void vf_339();
    virtual void vf_340();
    virtual void vf_341();
    virtual void vf_342(int, int, int);
    char unknown_04[0x6E0];
    unsigned char unknown_6E4;   // +0x06E4
    // FUNCTION: GAMEMD 0x521B40
    void FUN_00521B40();
};
GG_STATIC_ASSERT(offsetof(Obj_00521B40, unknown_6E4) == 0x6E4);

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

struct Obj_005220F0
{
    char unknown_00[0x6D8];
    unsigned char unknown_6D8;   // +0x06D8
    // FUNCTION: GAMEMD 0x5220F0
    void FUN_005220F0();
};
GG_STATIC_ASSERT(offsetof(Obj_005220F0, unknown_6D8) == 0x6D8);

struct Obj_005224D0
{
    char unknown_00[0x6C0];
    Obj_005224D0_6C0* unknown_6C0;   // +0x06C0
    // FUNCTION: GAMEMD 0x5224D0
    unsigned char FUN_005224D0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_005224D0, unknown_6C0) == 0x6C0);

struct Obj_005224D0_6C0
{
    char unknown_00[0xEC3];
    unsigned char unknown_EC3;   // +0x0EC3
};
GG_STATIC_ASSERT(offsetof(Obj_005224D0_6C0, unknown_EC3) == 0xEC3);

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

struct Obj_005232F0
{
    // FUNCTION: GAMEMD 0x5232F0
    int FUN_005232F0() const;
};

struct Obj_00523340
{
    // FUNCTION: GAMEMD 0x523340
    int FUN_00523340() const;
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

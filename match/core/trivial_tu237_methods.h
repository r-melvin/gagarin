// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU237_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU237_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_0070F000;
struct Obj_006F60C0;
struct Obj_006F9DB0;
struct Obj_006F9DB0_21C;
struct Obj_006F9DC0;
struct Obj_006FC090;
struct Obj_00701190;
struct Obj_00703850;
struct Obj_00705D30;
struct Obj_00705D30_514;
struct Obj_00705D50;
struct Obj_007094E0;
struct Obj_007099D0;
struct Obj_00709A20;
struct Obj_0070C5B0;
struct Obj_0070C5C0;
struct Obj_0070C5D0;
struct Obj_0070C5D0_274;
struct Obj_0070C5F0;
struct Obj_0070D670;
struct Obj_0070D980;
struct Obj_0070DCE0;
struct Obj_0070DD90;
struct Obj_0070DE20;
struct Obj_0070F000;
struct Obj_0070F010;
struct Obj_0070F020;
struct Obj_0070F030;
struct Obj_0070F0E0;
struct Obj_0070F0F0;
struct Obj_0070F100;
struct Obj_0070F110;
struct Obj_0070FE40;

// GLOBAL: GAMEMD 0x87F7E8
class MapClass;
extern MapClass DAT_0087F7E8;

// FUNCTION: GAMEMD 0x6562D0 (declaration)
void FUN_006562D0(void*, int, int);

struct Arg1_0070F000
{
    char unknown_00[0xC];
    char unknown_0C;   // +0x000C
};
GG_STATIC_ASSERT(offsetof(Arg1_0070F000, unknown_0C) == 0xC);

struct Obj_006F60C0
{
    // FUNCTION: GAMEMD 0x6F60C0
    void FUN_006F60C0(int a1, int a2);
};

struct Obj_006F9DB0
{
    char unknown_00[0x21C];
    Obj_006F9DB0_21C* unknown_21C;   // +0x021C
    // FUNCTION: GAMEMD 0x6F9DB0
    int FUN_006F9DB0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_006F9DB0, unknown_21C) == 0x21C);

struct Obj_006F9DB0_21C
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
};
GG_STATIC_ASSERT(offsetof(Obj_006F9DB0_21C, unknown_30) == 0x30);

struct Obj_006F9DC0
{
    char unknown_00[0x21C];
    int unknown_21C;   // +0x021C
    // FUNCTION: GAMEMD 0x6F9DC0
    int FUN_006F9DC0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_006F9DC0, unknown_21C) == 0x21C);

struct Obj_006FC090
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
    virtual void vf_240(int, int, int);
    // FUNCTION: GAMEMD 0x6FC090
    void FUN_006FC090(int a1, int a2);
};

struct Obj_00701190
{
    // FUNCTION: GAMEMD 0x701190
    bool FUN_00701190() const;
};

struct Obj_00703850
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
    virtual void vf_279(int);
    // FUNCTION: GAMEMD 0x703850
    void FUN_00703850();
};

struct Obj_00705D30
{
    char unknown_00[0x514];
    Obj_00705D30_514* unknown_514;   // +0x0514
    // FUNCTION: GAMEMD 0x705D30
    unsigned char FUN_00705D30();
};
GG_STATIC_ASSERT(offsetof(Obj_00705D30, unknown_514) == 0x514);

struct Obj_00705D30_514
{
    // FUNCTION: GAMEMD 0x636DC0
    int FUN_00636DC0();
};

struct Obj_00705D50
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
    virtual bool vf_118();
    // FUNCTION: GAMEMD 0x705D50
    bool FUN_00705D50();
};

struct Obj_007094E0
{
    char unknown_00[0xAC];
    int unknown_AC;   // +0x00AC
    // FUNCTION: GAMEMD 0x7094E0
    int FUN_007094E0();
};
GG_STATIC_ASSERT(offsetof(Obj_007094E0, unknown_AC) == 0xAC);

struct Obj_007099D0
{
    // FUNCTION: GAMEMD 0x7099D0
    int FUN_007099D0(int a1, int a2) const;
};

struct Obj_00709A20
{
    // FUNCTION: GAMEMD 0x709A20
    void FUN_00709A20(int a1);
};

struct Obj_0070C5B0
{
    char unknown_00[0x270];
    unsigned char unknown_270;   // +0x0270
    // FUNCTION: GAMEMD 0x70C5B0
    unsigned char FUN_0070C5B0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0070C5B0, unknown_270) == 0x270);

struct Obj_0070C5C0
{
    char unknown_00[0x271];
    unsigned char unknown_271;   // +0x0271
    // FUNCTION: GAMEMD 0x70C5C0
    unsigned char FUN_0070C5C0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0070C5C0, unknown_271) == 0x271);

struct Obj_0070C5D0
{
    char unknown_00[0x274];
    Obj_0070C5D0_274* unknown_274;   // +0x0274
    // FUNCTION: GAMEMD 0x70C5D0
    bool FUN_0070C5D0();
};
GG_STATIC_ASSERT(offsetof(Obj_0070C5D0, unknown_274) == 0x274);

struct Obj_0070C5D0_274
{
    char unknown_00[0x28];
    int unknown_28;   // +0x0028
};
GG_STATIC_ASSERT(offsetof(Obj_0070C5D0_274, unknown_28) == 0x28);

struct Obj_0070C5F0
{
    char unknown_00[0x270];
    bool unknown_270;   // +0x0270
    bool unknown_271;   // +0x0271
    // FUNCTION: GAMEMD 0x70C5F0
    bool FUN_0070C5F0();
};
GG_STATIC_ASSERT(offsetof(Obj_0070C5F0, unknown_270) == 0x270);
GG_STATIC_ASSERT(offsetof(Obj_0070C5F0, unknown_271) == 0x271);

struct Obj_0070D670
{
    char unknown_00[0x2FC];
    int unknown_2FC;   // +0x02FC
    // FUNCTION: GAMEMD 0x70D670
    int FUN_0070D670();
};
GG_STATIC_ASSERT(offsetof(Obj_0070D670, unknown_2FC) == 0x2FC);

struct Obj_0070D980
{
    // FUNCTION: GAMEMD 0x70D980
    void FUN_0070D980();
};

struct Obj_0070DCE0
{
    char unknown_00[0x124];
    int unknown_124;   // +0x0124
    // FUNCTION: GAMEMD 0x70DCE0
    bool FUN_0070DCE0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0070DCE0, unknown_124) == 0x124);

struct Obj_0070DD90
{
    // FUNCTION: GAMEMD 0x70DD90
    int FUN_0070DD90() const;
};

struct Obj_0070DE20
{
    char unknown_00[0x144];
    int unknown_144;   // +0x0144
    // FUNCTION: GAMEMD 0x70DE20
    void FUN_0070DE20(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0070DE20, unknown_144) == 0x144);

struct Obj_0070F000
{
    // FUNCTION: GAMEMD 0x70F000
    int FUN_0070F000(Arg1_0070F000* a1) const;
};

struct Obj_0070F010
{
    // FUNCTION: GAMEMD 0x70F010
    void FUN_0070F010();
};

struct Obj_0070F020
{
    // FUNCTION: GAMEMD 0x70F020
    bool FUN_0070F020() const;
};

struct Obj_0070F030
{
    // FUNCTION: GAMEMD 0x70F030
    bool FUN_0070F030() const;
};

struct Obj_0070F0E0
{
    // FUNCTION: GAMEMD 0x70F0E0
    bool FUN_0070F0E0() const;
};

struct Obj_0070F0F0
{
    // FUNCTION: GAMEMD 0x70F0F0
    bool FUN_0070F0F0() const;
};

struct Obj_0070F100
{
    // FUNCTION: GAMEMD 0x70F100
    void FUN_0070F100();
};

struct Obj_0070F110
{
    // FUNCTION: GAMEMD 0x70F110
    bool FUN_0070F110() const;
};

struct Obj_0070FE40
{
    char unknown_00[0x1D0];
    int unknown_1D0;   // +0x01D0
    // FUNCTION: GAMEMD 0x70FE40
    void FUN_0070FE40(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0070FE40, unknown_1D0) == 0x1D0);


// FUNCTION: GAMEMD 0x6FF950
void __cdecl FUN_006FF950();
// FUNCTION: GAMEMD 0x709460
int __stdcall FUN_00709460(int a1);
// FUNCTION: GAMEMD 0x709800
int __stdcall FUN_00709800(int a1);
// FUNCTION: GAMEMD 0x70CCF0
void FUN_0070CCF0(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU237_METHODS_H

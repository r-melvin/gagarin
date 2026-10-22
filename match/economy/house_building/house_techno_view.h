// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Partial, house-cluster-scoped view of the TechnoClass objects that HouseClass walks.
//   Only the members and virtual slots the house entries touch are named; every other slot is a
//   positional placeholder. Retail evidence (gamemd.exe v1.001, HouseClass entries 0x4F6A20 / 0x4F6A80 /
//   0x4F6AE0 / 0x4F6B50 / 0x5013A0 / 0x501400):
//     global array 0xA8EC78: Items at +0x04 (0xA8EC7C), Count at +0x10 (0xA8EC88); the technos are
//     owner-tested through the dword at techno+0x21C; the type comes from slot 33 (call [vptr+0x84])
//     and its dword at +0x3BC is compared with the caller's argument; +0x670 / +0x674 are summed.
//   The views never claim to be TechnoClass / TechnoTypeClass (read-only dependencies, bound by address).
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_TECHNO_VIEW_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_TECHNO_VIEW_H

#include <stddef.h>
struct HBCoord;
#include "../../_rt/gg_static_assert.h"

// TechnoTypeClass-shaped: only the members read by the house entries.
struct HouseTechnoTypeView
{
    unsigned char unknown_00[0xA0];
    int           unknown_A0;           // +0xA0 read at 0x501481 and passed on as the damage amount
    unsigned char unknown_A4[0x232 - 0xA4];
    unsigned char Insignificant;        // +0x232 tested at 0x50145F
    unsigned char unknown_233[0x3BC - 0x233];
    int           Category;             // +0x3BC compared with the argument of 0x4F6A20 / 0x4F6A80 / ...
    unsigned char unknown_3C0[0x670 - 0x3C0];
    int           ThreatPosed;          // +0x670
    int           Points;               // +0x674
};
GG_STATIC_ASSERT(offsetof(HouseTechnoTypeView, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(HouseTechnoTypeView, Insignificant) == 0x232);
GG_STATIC_ASSERT(offsetof(HouseTechnoTypeView, Category) == 0x3BC);
GG_STATIC_ASSERT(offsetof(HouseTechnoTypeView, ThreatPosed) == 0x670);
GG_STATIC_ASSERT(offsetof(HouseTechnoTypeView, Points) == 0x674);

// FUNCTION: GAMEMD 0x6EA870 (read-only here): the object at techno+0x5D4 is told about the techno.
struct HouseTechnoLinkView
{
    void M_6EA870(struct HouseTechnoView* techno, int a, int b);
};

// TechnoClass-shaped. The slot numbers are the retail primary-table indices (all __thiscall here;
// the leading COM block is never called through this view).
struct HouseTechnoView
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
    virtual int WhatAmI();                                  // 11  +0x2C: 6 == BuildingClass (cmp at 0x5014F0)
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
    virtual HouseTechnoTypeView* GetTechnoType();           // 33  +0x84
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
    virtual void vf_73(int arg);                            // 73  +0x124 (called on the flag carrier)
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
    virtual int ReceiveDamage(int* damage, int distance, void* warhead, HouseTechnoView* source,
                              bool ignoreDefenses, bool preventPassengerEscape, void* sourceHouse);   // 91  +0x16C
    virtual void vf_92();
    virtual bool vf_93(struct HBCoord* coord, bool a, bool b);   // 93  +0x174
    virtual void vf_94();
    virtual void vf_95();
    virtual void vf_96();
    virtual int vf_97();                                    // 97  +0x184 (compared with 0x13)
    virtual void vf_98();
    virtual void vf_99();
    virtual void vf_100();
    virtual void vf_101();
    virtual void vf_102();
    virtual void vf_103();
    virtual void vf_104(int arg);                           // 104 +0x1A0
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
    virtual void vf_122(int mission, int arg);              // 122 +0x1E8
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
    virtual int vf_258();                                   // 258 +0x408
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
    virtual void vf_312();                                  // 312 +0x4E0 (called on the buildings during a tech-tree recheck)

    // FUNCTION: GAMEMD 0x457DE0 (read-only here)
    void M_457DE0(int a, int b);

    unsigned char unknown_04[0x10];
    unsigned char IsTechno : 1;         // +0x14 bit 0
    unsigned char unknown_bit1 : 1;     // +0x14 bit 1
    unsigned char IsFoot : 1;           // +0x14 bit 2, tested at 0x5014B6 (the foot-class objects)
    unsigned char unknown_bits : 5;     // +0x14 bits 3-7
    unsigned char unknown_15[0x6C - 0x15];
    int           Strength;             // +0x6C tested > 0 at 0x5013D1
    unsigned char unknown_70[0x4];
    unsigned char IsOnMap;              // +0x74 tested at 0x501432
    unsigned char unknown_75[0x81 - 0x75];
    unsigned char InLimbo;              // +0x81 tested at 0x50143D and 0x5013C4
    unsigned char unknown_82[0x90 - 0x82];
    unsigned char unknown_90;           // +0x90 tested by the tech-tree recheck (0x4F9296)
    unsigned char unknown_91[0xB4 - 0x91];
    int           unknown_B4;           // +0xB4 compared with 0x13 (0x4F92B6)
    unsigned char unknown_B8[0x21C - 0xB8];
    void*         Owner;                // +0x21C owning house, compared at 0x4F6A45 / 0x501426
    unsigned char unknown_220[0x2C4 - 0x220];
    unsigned char MindControlled;       // +0x2C4 tested at 0x50144B
    unsigned char unknown_2C5[0x5A4 - 0x2C5];
    void*         unknown_5A4;          // +0x5A4 tested by the update slot's flag-carrier guard (0x4F8980)
    unsigned char unknown_5A8[0x5D4 - 0x5A8];
    struct HouseTechnoLinkView* unknown_5D4;   // +0x5D4 tested at 0x5014C5 (this of the call at 0x5014D4)
};
GG_STATIC_ASSERT(offsetof(HouseTechnoView, Strength) == 0x6C);
GG_STATIC_ASSERT(offsetof(HouseTechnoView, IsOnMap) == 0x74);
GG_STATIC_ASSERT(offsetof(HouseTechnoView, InLimbo) == 0x81);
GG_STATIC_ASSERT(offsetof(HouseTechnoView, unknown_90) == 0x90);
GG_STATIC_ASSERT(offsetof(HouseTechnoView, unknown_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(HouseTechnoView, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(HouseTechnoView, MindControlled) == 0x2C4);
GG_STATIC_ASSERT(offsetof(HouseTechnoView, unknown_5A4) == 0x5A4);
GG_STATIC_ASSERT(offsetof(HouseTechnoView, unknown_5D4) == 0x5D4);

// Inline helper: "is this object a FootClass?". The two-return form is what makes the bit-field read
// spill its result into a stack byte (0x5014BF), as the passenger-list code of the combat module shows.
static inline bool HouseIsFoot(HouseTechnoView* object)
{
    if (object == 0)
        return false;
    return object->IsFoot;
}

// GLOBAL: GAMEMD 0xA8EC78 - the all-technos DynamicVectorClass (Items at +0x04, Count at +0x10).
struct HouseTechnoArrayView
{
    void*             _vtable;           // +0x00
    HouseTechnoView** Items;             // +0x04
    int               Capacity;          // +0x08
    int               unknown_0C;        // +0x0C
    int               Count;             // +0x10
    int               CapacityIncrement; // +0x14
};
GG_STATIC_ASSERT(offsetof(HouseTechnoArrayView, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(HouseTechnoArrayView, Count) == 0x10);
extern HouseTechnoArrayView HouseTechnoArray;
#endif

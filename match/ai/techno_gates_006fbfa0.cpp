// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x6FBFA0 and 0x6FC030, read instruction by instruction from gamemd.exe v1.001: two
// object-state gates next to each other. The object and its owner are placeholder views whose
// offsets are asserted below.
//   0x6FBFA0 0x6FC030
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct TypeView_006FBFA0 {
    unsigned char unknown_00[0x1A6];
    bool unknown_1A6;   // +0x01A6
};
GG_STATIC_ASSERT(offsetof(TypeView_006FBFA0, unknown_1A6) == 0x1A6);

struct OwnerView_006FBFA0 {
    unsigned char unknown_00[0x34];
    TypeView_006FBFA0* unknown_34;   // +0x0034
    // FUNCTION: GAMEMD 0x50B6F0 (decl; reloc)
    bool FUN_0050B6F0();
};
GG_STATIC_ASSERT(offsetof(OwnerView_006FBFA0, unknown_34) == 0x34);

struct TagView_006FBFA0 {
    // FUNCTION: GAMEMD 0x6E53A0 (decl; reloc)
    void FUN_006E53A0(int a1, void* a2, int a3, int a4, int a5);
};

struct ObjectView_006FBFA0 {
    virtual void vf_000();
    virtual void vf_001();
    virtual void vf_002();
    virtual void vf_003();
    virtual void vf_004();
    virtual void vf_005();
    virtual void vf_006();
    virtual void vf_007();
    virtual void vf_008();
    virtual void vf_009();
    virtual void vf_010();
    virtual void vf_011();
    virtual void vf_012();
    virtual void vf_013();
    virtual void vf_014();
    virtual void vf_015();
    virtual void vf_016();
    virtual void vf_017();
    virtual void vf_018();
    virtual void vf_019();
    virtual void vf_020();
    virtual void vf_021();
    virtual void vf_022();
    virtual void vf_023();
    virtual void vf_024();
    virtual void vf_025();
    virtual void vf_026();
    virtual void vf_027();
    virtual void vf_028();
    virtual void vf_029();
    virtual void vf_030();
    virtual void vf_031();
    virtual void vf_032();
    virtual void vf_033();
    virtual void vf_034();
    virtual void vf_035();
    virtual void vf_036();
    virtual void vf_037();
    virtual void vf_038();
    virtual void vf_039();
    virtual void vf_040();
    virtual void vf_041();
    virtual void vf_042();
    virtual void vf_043();
    virtual void vf_044();
    virtual void vf_045();
    virtual void vf_046();
    virtual void vf_047();
    virtual void vf_048();
    virtual void vf_049();
    virtual void vf_050();
    virtual void vf_051();
    virtual void vf_052();
    virtual void vf_053();
    virtual void vf_054();
    virtual void vf_055();
    virtual void vf_056();
    virtual void vf_057();
    virtual void vf_058();
    virtual void vf_059();
    virtual void vf_060();
    virtual void vf_061();
    virtual void vf_062();
    virtual void vf_063();
    virtual void vf_064();
    virtual void vf_065();
    virtual void vf_066();
    virtual void vf_067();
    virtual void vf_068();
    virtual void vf_069();
    virtual void vf_070();
    virtual void vf_071();
    virtual void vf_072();
    virtual void vf_073();
    virtual void vf_074();
    virtual void vf_075();
    virtual void vf_076();
    virtual void vf_077();
    virtual void vf_078();
    virtual void vf_079();
    virtual void vf_080();
    virtual void vf_081();
    virtual void vf_082();
    virtual void vf_083();
    virtual void vf_084();
    virtual void vf_085();
    virtual void vf_086();
    virtual void vf_087();
    virtual void vf_088();
    virtual void vf_089();
    virtual void vf_090();
    virtual void vf_091();
    virtual void vf_092();
    virtual void vf_093();
    virtual void vf_094();
    virtual void vf_095();
    virtual void vf_096();
    virtual void vf_097();
    virtual void vf_098();
    virtual void vf_099();
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
    virtual void* vf_111();
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
    unsigned char unknown_04[0x30];
    TagView_006FBFA0* unknown_34;   // +0x0034
    unsigned char unknown_38[0x190];
    unsigned char unknown_1C8;   // +0x01C8
    unsigned char unknown_1C9[0x53];
    OwnerView_006FBFA0* unknown_21C;   // +0x021C
    unsigned char unknown_220[0xBC];
    int unknown_2DC;   // +0x02DC
    unsigned char unknown_2E0[4];
    int unknown_2E4;   // +0x02E4
    unsigned char unknown_2E8[0x130];
    bool unknown_418;   // +0x0418
    unsigned char unknown_419[2];
    bool unknown_41B;   // +0x041B

    // FUNCTION: GAMEMD 0x5F4520 (decl; reloc)
    bool FUN_005F4520();
    // FUNCTION: GAMEMD 0x5F6C70 (decl; reloc)
    bool FUN_005F6C70();
    // FUNCTION: GAMEMD 0x637840 (decl; reloc)
    void FUN_00637840();
    // FUNCTION: GAMEMD 0x6FBFA0
    bool FUN_006FBFA0();
    // FUNCTION: GAMEMD 0x6FC030
    bool FUN_006FC030();
};
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_1C8) == 0x1C8);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_2DC) == 0x2DC);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_2E4) == 0x2E4);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_418) == 0x418);
GG_STATIC_ASSERT(offsetof(ObjectView_006FBFA0, unknown_41B) == 0x41B);

// GLOBAL: GAMEMD 0xB73550
extern int DAT_00B73550;
// GLOBAL: GAMEMD 0xB0EA50
extern int DAT_00B0EA50;
// GLOBAL: GAMEMD 0x822CF2
extern bool DAT_00822CF2;

// FUNCTION: GAMEMD 0x47C520 (decl; reloc)
int __fastcall FUN_0047C520(void* arg);

// FUNCTION: GAMEMD 0x6FBFA0
// When allowed, tells the attached tag, wakes the object and reports success.
bool ObjectView_006FBFA0::FUN_006FBFA0()
{
    if (unknown_41B || unknown_21C->FUN_0050B6F0() || DAT_00B73550 == 0) {
        if (FUN_005F4520()) {
            if (unknown_34 != 0) {
                unknown_34->FUN_006E53A0(0x21, this, DAT_00B0EA50, 0, 0);
            }
            if (unknown_21C->FUN_0050B6F0() || unknown_21C->unknown_34->unknown_1A6) {
                if (DAT_00822CF2) {
                    vf_216();
                }
            }
            FUN_00637840();
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6FC030
// True only when none of the blocking fields is set and the base check passes.
bool ObjectView_006FBFA0::FUN_006FC030()
{
    if (unknown_2DC != 0) {
        return false;
    }
    if (unknown_1C8) {
        return false;
    }
    if (unknown_2E4 != 0) {
        return false;
    }
    if (unknown_418 && FUN_0047C520(vf_111()) != 0) {
        return false;
    }
    return FUN_005F6C70();
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Team mission action handlers in retail gamemd.exe v1.001 between 0x6EDDC0 and 0x6EE1F0, the
// siblings of the handlers in tu235_team_class.cpp. Each takes (this = team, action record*,
// unused), walks the team's member list (first member at +0x54, next at +0x5D8) and finally
// sets the "action done" flag at +0x80. Owners/members are placeholder views verified by the
// offsets asserted below.
#include <stddef.h>
#include "../_layout/house_class.h"
#include "../_rt/gg_static_assert.h"

struct ActionArg_006EDDC0 {
    unsigned char unknown_00[4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(ActionArg_006EDDC0, unknown_04) == 0x4);

struct MemberType_006EE1F0 {
    unsigned char unknown_00[0x5E0];
    int unknown_5E0;   // +0x05E0
    unsigned char unknown_5E4[0x18];
    int unknown_5FC;   // +0x05FC
    unsigned char unknown_600[0x84];
    int unknown_684;   // +0x0684
};
GG_STATIC_ASSERT(offsetof(MemberType_006EE1F0, unknown_5E0) == 0x5E0);
GG_STATIC_ASSERT(offsetof(MemberType_006EE1F0, unknown_5FC) == 0x5FC);
GG_STATIC_ASSERT(offsetof(MemberType_006EE1F0, unknown_684) == 0x684);

struct TaskEntryType_006EF470 {
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
    virtual int vf_011();
    unsigned char unknown_04[0x5DC];
    int unknown_5E0;   // +0x05E0
};
GG_STATIC_ASSERT(offsetof(TaskEntryType_006EF470, unknown_5E0) == 0x5E0);

struct TaskEntry_006EF470 {
    TaskEntryType_006EF470* unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
};

struct TaskForce_006EF470 {
    unsigned char unknown_00[0x9C];
    int unknown_9C;   // +0x009C
    unsigned char unknown_A0[8];
    TaskEntry_006EF470 unknown_A8[1];   // +0x00A8
};
GG_STATIC_ASSERT(offsetof(TaskForce_006EF470, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(TaskForce_006EF470, unknown_A8) == 0xA8);

struct TeamType_006EF470 {
    unsigned char unknown_00[0xE4];
    TaskForce_006EF470* unknown_E4;   // +0x00E4
    unsigned char unknown_E8[0xF];
    char unknown_F7;   // +0x00F7
};
GG_STATIC_ASSERT(offsetof(TeamType_006EF470, unknown_E4) == 0xE4);
GG_STATIC_ASSERT(offsetof(TeamType_006EF470, unknown_F7) == 0xF7);

struct CoordStruct_006EDF10 {
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(CoordStruct_006EDF10) == 0xC);

struct CellStruct_006EDF10 {
    short unknown_00;   // +0x0000
    short unknown_02;   // +0x0002
};
GG_STATIC_ASSERT(sizeof(CellStruct_006EDF10) == 0x4);

struct CellView_006EE100 {
    unsigned char unknown_00[0x140];
    unsigned int unknown_140;   // +0x0140
};
GG_STATIC_ASSERT(offsetof(CellView_006EE100, unknown_140) == 0x140);

struct MapView_006EDF10 {
    // FUNCTION: GAMEMD 0x57B790 (decl; reloc)
    void FUN_0057B790(CellStruct_006EDF10* cell);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc)
    int FUN_00578080(CoordStruct_006EDF10* coord);
    // FUNCTION: GAMEMD 0x565730 (decl; reloc)
    CellView_006EE100* FUN_00565730(CoordStruct_006EDF10* coord);
};

struct TacticalView_006EE100 {
    // FUNCTION: GAMEMD 0x6D2420 (decl; reloc)
    void FUN_006D2420(CoordStruct_006EDF10* coord, int arg);
};



struct Rules_006F03B0 {
    unsigned char unknown_00[0x171C];
    int unknown_171C;   // +0x171C
    int unknown_1720;   // +0x1720
};
GG_STATIC_ASSERT(offsetof(Rules_006F03B0, unknown_1720) == 0x1720);

struct RttiPair_006F03B0 {
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
};

struct Target_006F03B0 {
    // FUNCTION: GAMEMD 0x691500 (decl; reloc)
    RttiPair_006F03B0* FUN_00691500(RttiPair_006F03B0* out);
};

struct Member_006EDDC0;
struct TypeView_006EE310 {
    unsigned char unknown_00[4];
};

struct DirValue_006EDCA0 {
    short unknown_00;   // +0x0000
    DirValue_006EDCA0() {}
    DirValue_006EDCA0(int v) { unknown_00 = (short)(v << 13); }
};
GG_STATIC_ASSERT(sizeof(DirValue_006EDCA0) == 0x2);

struct FacingSlot_006EDCA0 {
    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc)
    DirValue_006EDCA0* FUN_004C93D0(DirValue_006EDCA0* out);
};

// The COM locomotor interface the member holds at +0x674 (slot 4 = IsMoving, slot 19 = set facing).
struct ILocomotion_006EDCA0 {
    virtual void __stdcall vf_000();
    virtual void __stdcall vf_001();
    virtual void __stdcall vf_002();
    virtual void __stdcall vf_003();
    virtual bool __stdcall vf_004();
    virtual void __stdcall vf_005();
    virtual void __stdcall vf_006();
    virtual void __stdcall vf_007();
    virtual void __stdcall vf_008();
    virtual void __stdcall vf_009();
    virtual void __stdcall vf_010();
    virtual void __stdcall vf_011();
    virtual void __stdcall vf_012();
    virtual void __stdcall vf_013();
    virtual void __stdcall vf_014();
    virtual void __stdcall vf_015();
    virtual void __stdcall vf_016();
    virtual void __stdcall vf_017();
    virtual void __stdcall vf_018();
    virtual void __stdcall vf_019(DirValue_006EDCA0 dir);
};

extern void __stdcall _com_issue_error(long hr);
struct ILocomotionPtr_006EDCA0 {
    ILocomotion_006EDCA0* m_pInterface;
    ILocomotion_006EDCA0* operator->() const
    {
        if (m_pInterface == 0) {
            _com_issue_error(0x80004003);
        }
        return m_pInterface;
    }
};

struct Member_006EDDC0 {
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
    virtual int vf_011();
    virtual void vf_012();
    virtual void vf_013();
    virtual void vf_014();
    virtual void vf_015();
    virtual void vf_016();
    virtual void vf_017();
    virtual CoordStruct_006EDF10* vf_018(CoordStruct_006EDF10* out);
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
    virtual MemberType_006EE1F0* vf_033();
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
    virtual int vf_091(int* damage, int distance, void* warhead, void* source, bool ignoreDefense, bool preventsPassengerEscape, void* house);
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
    virtual void vf_328(int arg);
    // FUNCTION: GAMEMD 0x6EF9E0
    bool FUN_006EF9E0();
    unsigned char unknown_04[0x68];
    int unknown_6C;   // +0x006C
    unsigned char unknown_70[4];
    bool unknown_74;   // +0x0074
    unsigned char unknown_75[0xC];
    bool unknown_81;   // +0x0081
    unsigned char unknown_82[0xE];
    bool unknown_90;   // +0x0090
    unsigned char unknown_91[0x5F];
    int unknown_F0;   // +0x00F0
    unsigned char unknown_F4[0x20];
    int unknown_114;   // +0x0114
    unsigned char unknown_118[0x104];
    HouseClass* unknown_21C;   // +0x021C
    unsigned char unknown_220[0xDC];
    int unknown_2FC;   // +0x02FC
    unsigned char unknown_300[0xD5];
    bool unknown_3D5;   // +0x03D5
    unsigned char unknown_3D6[0x202];
    Member_006EDDC0* unknown_5D8;   // +0x05D8
    unsigned char unknown_5DC[0x98];
    ILocomotionPtr_006EDCA0 unknown_674;   // +0x0674
    unsigned char unknown_678[0x11];
    bool unknown_689;   // +0x0689
};
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_81) == 0x81);
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_F0) == 0xF0);
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_2FC) == 0x2FC);
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_3D5) == 0x3D5);
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_5D8) == 0x5D8);
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_674) == 0x674);
GG_STATIC_ASSERT(offsetof(Member_006EDDC0, unknown_689) == 0x689);

struct Owner_006EDDC0 {
    unsigned char unknown_00[0x24];
    TeamType_006EF470* unknown_24;   // +0x0024
    Target_006F03B0* unknown_28;   // +0x0028
    unsigned char unknown_2C[8];
    Member_006EDDC0* unknown_34;   // +0x0034
    unsigned char unknown_38[4];
    int unknown_3C;   // +0x003C
    unsigned char unknown_40[0x14];
    Member_006EDDC0* unknown_54;   // +0x0054
    unsigned char unknown_58[0x28];
    bool unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDDC0
    void FUN_006EDDC0(ActionArg_006EDDC0* a1, int a2);
    // FUNCTION: GAMEMD 0x6EDE90
    void FUN_006EDE90(ActionArg_006EDDC0* a1, int a2);
    // FUNCTION: GAMEMD 0x6EE1F0
    void FUN_006EE1F0(int a1, int a2);
    // FUNCTION: GAMEMD 0x6EC370
    bool FUN_006EC370();
    // FUNCTION: GAMEMD 0x6EC3D0
    Member_006EDDC0* FUN_006EC3D0();
    // FUNCTION: GAMEMD 0x6EF470
    bool FUN_006EF470();
    // FUNCTION: GAMEMD 0x6EF5C0
    void FUN_006EF5C0(ActionArg_006EDDC0* a1, bool a2);
    // FUNCTION: GAMEMD 0x6EDD60
    void FUN_006EDD60(ActionArg_006EDDC0* a1, int a2);
    // FUNCTION: GAMEMD 0x6EDD90
    void FUN_006EDD90(ActionArg_006EDDC0* a1, int a2);
    // FUNCTION: GAMEMD 0x6EE050
    void FUN_006EE050(ActionArg_006EDDC0* a1, int a2);
    // FUNCTION: GAMEMD 0x6EE0A0
    void FUN_006EE0A0(ActionArg_006EDDC0* a1, int a2);
    // FUNCTION: GAMEMD 0x6EE0E0
    void FUN_006EE0E0(ActionArg_006EDDC0* a1, int a2);
    // FUNCTION: GAMEMD 0x6E9050 (decl; reloc) -- TeamClass::AssignMissionTarget.
    void FUN_006E9050(void* target);
    // FUNCTION: GAMEMD 0x6EB490 (decl; reloc)
    void FUN_006EB490();
    // FUNCTION: GAMEMD 0x6EE310
    void FUN_006EE310(ActionArg_006EDDC0* a1, bool a2);
    // FUNCTION: GAMEMD 0x6F03B0
    int FUN_006F03B0();
    // FUNCTION: GAMEMD 0x6F03F0
    bool FUN_006F03F0();
    // FUNCTION: GAMEMD 0x6EDCA0
    void FUN_006EDCA0(ActionArg_006EDDC0* a1, int a2);
    // FUNCTION: GAMEMD 0x6EDFD0
    void FUN_006EDFD0(ActionArg_006EDDC0* a1, int a2);
    // FUNCTION: GAMEMD 0x6EDF10
    void FUN_006EDF10(ActionArg_006EDDC0* a1, int a2);
    // FUNCTION: GAMEMD 0x6EE100
    void FUN_006EE100(ActionArg_006EDDC0* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Owner_006EDDC0, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Owner_006EDDC0, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Owner_006EDDC0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Owner_006EDDC0, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(Owner_006EDDC0, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(Owner_006EDDC0, unknown_80) == 0x80);

// GLOBAL: GAMEMD 0xA8E7AC
extern int DAT_00A8E7AC;

// GLOBAL: GAMEMD 0x87F7E8
extern MapView_006EDF10 DAT_0087F7E8;
// GLOBAL: GAMEMD 0x887324
extern TacticalView_006EE100* DAT_00887324;
// GLOBAL: GAMEMD 0x8871E0
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;
// GLOBAL: GAMEMD 0xB0E948
extern int DAT_00B0E948;
// GLOBAL: GAMEMD 0xB0E99C
extern int DAT_00B0E99C;

// GLOBAL: GAMEMD 0xA83C6C
extern TypeView_006EE310** DAT_00A83C6C;
// GLOBAL: GAMEMD 0xA8022C
extern HouseClass** DAT_00A8022C;

// FUNCTION: GAMEMD 0x6EEBD0 (decl; reloc) -- fastcall: ecx = type, edx = house; returns the target or null.
void* __fastcall FUN_006EEBD0(TypeView_006EE310* type, HouseClass* house, Member_006EDDC0* member, int y, char flag);

// FUNCTION: GAMEMD 0x539EB0 (decl; reloc)
void __fastcall FUN_00539EB0(int a1, int a2, int a3, void* a4);

// FUNCTION: GAMEMD 0x53A100 (decl; reloc)
bool __cdecl FUN_0053A100();
// FUNCTION: GAMEMD 0x53A090 (decl; reloc)
void __fastcall FUN_0053A090();

// FUNCTION: GAMEMD 0x750920 (decl; reloc) -- VocClass::PlayGlobal(index, volume, pan, controller).
void* FUN_00750920(int voc, float volume, unsigned int pan, void* controller);

// FUNCTION: GAMEMD 0x6EDDC0
// Calls member virtual slot 328 with the record's argument for every member.
void Owner_006EDDC0::FUN_006EDDC0(ActionArg_006EDDC0* a1, int a2)
{
    for (Member_006EDDC0* m = unknown_54; m != 0; m = m->unknown_5D8) {
        m->vf_328(a1->unknown_04);
    }
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EDE90
// Plays a global sound for the record's argument.
void Owner_006EDDC0::FUN_006EDE90(ActionArg_006EDDC0* a1, int a2)
{
    FUN_00750920(a1->unknown_04, 1.0f, 0x2000, 0);
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EE1F0
// Completes only if no member's type value exceeds the member's own value.
void Owner_006EDDC0::FUN_006EE1F0(int a1, int a2)
{
    for (Member_006EDDC0* m = unknown_54; m != 0; m = m->unknown_5D8) {
        MemberType_006EE1F0* t = m->vf_033();
        if (t->unknown_5E0 > m->unknown_114) {
            return;
        }
    }
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EC370
// True when every member has its flag at +0x3D5 set.
bool Owner_006EDDC0::FUN_006EC370()
{
    bool all = true;
    Member_006EDDC0* m = unknown_54;
    while (m != 0) {
        if (!m->unknown_3D5) {
            all = false;
            break;
        }
        m = m->unknown_5D8;
    }
    return all;
}

// FUNCTION: GAMEMD 0x6EC3D0
// The eligible member whose type value at +0x5FC is greatest (first member if none).
Member_006EDDC0* Owner_006EDDC0::FUN_006EC3D0()
{
    Member_006EDDC0* m = unknown_54;
    int bestValue = -1;
    Member_006EDDC0* best = m;
    for (; m != 0; m = m->unknown_5D8) {
        int value = m->vf_033()->unknown_5FC;
        if (m != 0 && m->unknown_90 && m->unknown_6C != 0 && (DAT_00A8E7AC != 0 || !m->unknown_81)
            && (m->unknown_689 || m->vf_011() == 2) && value > bestValue) {
            best = m;
            bestValue = value;
        }
    }
    return best;
}

// FUNCTION: GAMEMD 0x6EF5C0
// When enabled, copies the record's argument into every member's field at +0xF0.
void Owner_006EDDC0::FUN_006EF5C0(ActionArg_006EDDC0* a1, bool a2)
{
    if (a2) {
        int value = a1->unknown_04;
        for (Member_006EDDC0* m = unknown_54; m != 0; m = m->unknown_5D8) {
            m->unknown_F0 = value;
        }
        unknown_80 = true;
    }
}

// FUNCTION: GAMEMD 0x6EF470
// True if the team type's task force lists a type whose class id is 3 and whose count at +0x5E0 is positive.
bool Owner_006EDDC0::FUN_006EF470()
{
    for (int i = 0; i < unknown_24->unknown_E4->unknown_9C; i++) {
        TaskEntryType_006EF470* t = unknown_24->unknown_E4->unknown_A8[i].unknown_00;
        if (t->vf_011() == 3 && t->unknown_5E0 > 0) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6EDD60
// Calls member virtual slot 326 for every member.
void Owner_006EDDC0::FUN_006EDD60(ActionArg_006EDDC0* a1, int a2)
{
    for (Member_006EDDC0* m = unknown_54; m != 0; m = m->unknown_5D8) {
        m->vf_326();
    }
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EDD90
// Calls member virtual slot 325 for every member.
void Owner_006EDDC0::FUN_006EDD90(ActionArg_006EDDC0* a1, int a2)
{
    for (Member_006EDDC0* m = unknown_54; m != 0; m = m->unknown_5D8) {
        m->vf_325();
    }
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EE050
// Calls member virtual slots 53 and 62 for every member (next link read first).
void Owner_006EDDC0::FUN_006EE050(ActionArg_006EDDC0* a1, int a2)
{
    for (Member_006EDDC0* m = unknown_54; m != 0; ) {
        Member_006EDDC0* next = m->unknown_5D8;
        m->vf_053();
        m->vf_062();
        m = next;
    }
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EE0E0
// Runs the global fix-up when the global condition holds.
void Owner_006EDDC0::FUN_006EE0E0(ActionArg_006EDDC0* a1, int a2)
{
    if (FUN_0053A100()) {
        FUN_0053A090();
    }
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EE0A0
// When the global condition fails, forwards the record's argument to the global handler.
void Owner_006EDDC0::FUN_006EE0A0(ActionArg_006EDDC0* a1, int a2)
{
    if (!FUN_0053A100()) {
        FUN_00539EB0(a1->unknown_04, DAT_008871E0->LightningDeferment, DAT_00B0E948, 0);
    }
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EDF10
// Moves the view to the first member's cell.
void Owner_006EDDC0::FUN_006EDF10(ActionArg_006EDDC0* a1, int a2)
{
    for (Member_006EDDC0* m = unknown_54; m != 0; m = m->unknown_5D8) {
        CoordStruct_006EDF10 tmp;
        CoordStruct_006EDF10* c = m->vf_018(&tmp);
        CellStruct_006EDF10 cell;
        cell.unknown_00 = (short)(c->unknown_00 / 256);
        cell.unknown_02 = (short)(c->unknown_04 / 256);
        CellStruct_006EDF10 where = cell;
        DAT_0087F7E8.FUN_0057B790(&where);
    }
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EE100
// Looks at the target's coordinate (raised by the bridge height on bridge cells) in the tactical view.
void Owner_006EDDC0::FUN_006EE100(ActionArg_006EDDC0* a1, int a2)
{
    CoordStruct_006EDF10 tmp;
    CoordStruct_006EDF10 coord = *unknown_34->vf_018(&tmp);
    coord.unknown_08 = DAT_0087F7E8.FUN_00578080(&coord);
    if ((DAT_0087F7E8.FUN_00565730(&coord)->unknown_140 & 0x100) != 0
        || (DAT_0087F7E8.FUN_00565730(&coord)->unknown_140 & 0x400) != 0) {
        coord.unknown_08 += DAT_00B0E99C;
    }
    DAT_00887324->FUN_006D2420(&coord, a1->unknown_04);
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EDFD0
// Keeps dealing the warhead damage to every living member until none is hit any more.
void Owner_006EDDC0::FUN_006EDFD0(ActionArg_006EDDC0* a1, int a2)
{
    bool again;
    do {
        again = false;
        for (Member_006EDDC0* m = unknown_54; m != 0; m = m->unknown_5D8) {
            if (m->unknown_6C > 0 && m->unknown_90 && m->unknown_74 && !m->unknown_81) {
                int damage = m->unknown_6C;
                m->vf_091(&damage, 0, DAT_008871E0->C4Warhead, 0, true, false, 0);
                again = true;
            }
        }
    } while (again);
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EDCA0
// Turns every idle member to the record's facing; completes once no member is still moving.
void Owner_006EDDC0::FUN_006EDCA0(ActionArg_006EDDC0* a1, int a2)
{
    bool done = true;
    Member_006EDDC0* m = unknown_54;
    if (m != 0) {
        do {
            if (m->unknown_674->vf_004()) {
                done = false;
            } else {
                DirValue_006EDCA0 cur;
                FacingSlot_006EDCA0* facing = (FacingSlot_006EDCA0*)((char*)m + 0x388);
                if (facing->FUN_004C93D0(&cur)->unknown_00 != DirValue_006EDCA0(a1->unknown_04).unknown_00) {
                    DirValue_006EDCA0 dir(a1->unknown_04);
                    m->unknown_674->vf_019(dir);
                }
            }
            m = m->unknown_5D8;
        } while (m != 0);
    }
    if (done) {
        unknown_80 = true;
    }
}

// FUNCTION: GAMEMD 0x6EE310
// Picks a mission target for the team from the record's packed value, then finishes
// unless a member is not ready.
void Owner_006EDDC0::FUN_006EE310(ActionArg_006EDDC0* a1, bool a2)
{
    if (a2 && unknown_3C == 0) {
        Member_006EDDC0* first = unknown_54;
        if (first != 0) {
            int packed = a1->unknown_04;
            int x = packed & 0xFFFF;
            int y = (packed >> 16) & 0xFFFF;
            TypeView_006EE310* type = DAT_00A83C6C[x];
            HouseClass* house = 0;
            int index = first->unknown_21C->EnemyHouseIndex;
            if (index != -1) {
                house = DAT_00A8022C[index];
            }
            void* target = FUN_006EEBD0(type, house, first, y, unknown_24->unknown_F7);
            if (target != 0) {
                FUN_006E9050(target);
            }
        }
    }
    if (unknown_3C != 0) {
        for (Member_006EDDC0* m = unknown_54; m != 0; m = m->unknown_5D8) {
            if (m->vf_033()->unknown_684 <= 0 || m->unknown_2FC > 0) {
                FUN_006EB490();
                return;
            }
        }
    }
    FUN_006E9050(0);
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6F03F0
// True when any member's type value at +0x684 is not positive or the member's value at +0x2FC is positive.
bool Owner_006EDDC0::FUN_006F03F0()
{
    bool r = false;
    for (Member_006EDDC0* m = unknown_54; m != 0; m = m->unknown_5D8) {
        if (m->vf_033()->unknown_684 <= 0 || m->unknown_2FC > 0) {
            r = true;
            break;
        }
    }
    return r;
}

// FUNCTION: GAMEMD 0x6F03B0
// Returns the rules value for the owner's object class: one value for classes 0x35/0x36, another otherwise.
int Owner_006EDDC0::FUN_006F03B0()
{
    RttiPair_006F03B0 pair;
    int id = unknown_28->FUN_00691500(&pair)->unknown_00;
    if (id == 0x36 || id == 0x35) {
        return ((Rules_006F03B0*)DAT_008871E0)->unknown_1720;
    }
    return ((Rules_006F03B0*)DAT_008871E0)->unknown_171C;
}

// FUNCTION: GAMEMD 0x6EF9E0
// True for a live, healthy member that is not hidden (or the global override is on).
bool Member_006EDDC0::FUN_006EF9E0()
{
    if (this != 0 && unknown_90 && unknown_6C != 0 && (DAT_00A8E7AC != 0 || !unknown_81)) {
        return true;
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA83C6C
TypeView_006EE310** DAT_00A83C6C;
// GLOBAL: GAMEMD 0xB0E948
int DAT_00B0E948;
// END defined globals

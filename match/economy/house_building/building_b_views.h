// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Address-scoped partial views for the "building-b" cluster of BuildingClass entries (0x44F5C0..0x459F20).
//   Maintained by hand since the module consolidation; shared types come from house_building_common_types.h.
//   Every member offset below is pinned by an offsetof assert and was read from a retail instruction of one
//   of the cluster's bodies (see the per-function evidence in building_b_class.cpp).
//
//   BuildingClass RTTI (read from gamemd.exe v1.001): .?AVBuildingClass@@ (TD 0x818D60); COLs 0x7FC360 (offset 0,
//   table 0x7E3EBC), 0x7FC2E0 (offset 4, 0x7E3EA0), 0x7FC2C8 (offset 8, 0x7E3E98), 0x7FC2B0 (offset 12,
//   0x7E3E90); hierarchy 0x7FC350: BuildingClass, TechnoClass, RadioClass, MissionClass, ObjectClass,
//   AbstractClass, IPersistStream, IPersist, IUnknown, IRTTITypeInfo, IUnknown, INoticeSink, INoticeSource,
//   FlasherClass, StageClass. sizeof(BuildingClass) == 0x720 from `push 0x720; call 0x7C8E17` at the allocation
//   sites 0x44FAF8, 0x44FD6E, 0x45E806, 0x45E883 (and seven more).
//
//   TEMPORARY ABI VIEWS: the classes here are named BuildingB* and never claim to be BuildingClass /
//   TechnoClass / BuildingTypeClass / HouseClass; they are to be consolidated with the canonical
//   headers. Slot numbers are retail primary-table indices (table address point 0x7E3EBC for BuildingClass).
//   IPersistStream slots (0-7) are __stdcall with `this` on the stack where a body shows it; every other slot
//   is __thiscall (ECX = this). The views are sparse: they do not claim complete class or table closure.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_B_VIEWS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_B_VIEWS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "house_building_layout.h"
#include "building_b_shared.h"

class BuildingBView;
class BuildingBTypeView;
class BuildingBHouseView;
class BuildingBSurfaceView;
class BuildingBTargetObjView;
class BuildingBAnimObjView;
class BuildingBAnimDataView;
class BuildingBParticleSystemTypeView;
class BuildingBParticleSystemView;
class BuildingBAbstractView;
class BuildingBPointVector;
class BuildingBView;
class BuildingBObjectView;
class BuildingBCrcView;
class BuildingBTargetView;
class BuildingBRttiHolder;
class BuildingBCellView;
class BuildingBMapView;
class BuildingBTacticalView;
class BuildingBAudioView;
class BuildingBOccupantView;
class BuildingBOccupantTypeView;
class BuildingBRulesView;

// GLOBAL: GAMEMD 0xA8ED84 (the frame counter CDTimerClass compares against)
extern int BuildingBFrame;


// A 16-byte colour record returned by the surface (read-only here).
struct BuildingBColor16
{
public:
    int a;   // +0x0
    int b;   // +0x4
    int c;   // +0x8
    int d;   // +0xC
};
GG_STATIC_ASSERT(offsetof(BuildingBColor16, a) == 0x0);
GG_STATIC_ASSERT(offsetof(BuildingBColor16, b) == 0x4);
GG_STATIC_ASSERT(offsetof(BuildingBColor16, c) == 0x8);
GG_STATIC_ASSERT(offsetof(BuildingBColor16, d) == 0xC);
GG_STATIC_ASSERT(sizeof(BuildingBColor16) == 0x10);

// Partial view of the surface object behind global 0x89DDC0 (read-only here).
class BuildingBSurfaceView
{
public:
    // virtual table (primary), slot index in the comment
    virtual void unused_slot_0();
    virtual void unused_slot_1();
    virtual void unused_slot_2();
    virtual void unused_slot_3();
    virtual void unused_slot_4();
    virtual void unused_slot_5();
    virtual void vf_6(int a);   // slot 6 (+0x18)
    virtual void unused_slot_7();
    virtual void unused_slot_8();
    virtual void unused_slot_9();
    virtual void unused_slot_10();
    virtual void unused_slot_11();
    virtual void unused_slot_12();
    virtual void unused_slot_13();
    virtual void unused_slot_14();
    virtual void unused_slot_15();
    virtual void unused_slot_16();
    virtual void unused_slot_17();
    virtual void unused_slot_18();
    virtual void unused_slot_19();
    virtual void unused_slot_20();
    virtual void unused_slot_21();
    virtual void unused_slot_22();
    virtual char* vf_23(int a, int b);   // slot 23 (+0x5C)
    virtual void unused_slot_24();
    virtual void unused_slot_25();
    virtual void unused_slot_26();
    virtual void unused_slot_27();
    virtual void unused_slot_28();
    virtual void unused_slot_29();
    virtual BuildingBColor16* vf_30(BuildingBColor16* out, int flag);   // slot 30 (+0x78)
    virtual int vf_31();   // slot 31 (+0x7C)
    void Func_7BB920(int x, int y, int radius, BuildingBColor16 color);
};

// A 24-bit colour (3 bytes).
struct BuildingBColor
{
public:
    void Func_6612C0(int amount, const BuildingBColor* target);
    unsigned char R;   // +0x0
    unsigned char G;   // +0x1
    unsigned char B;   // +0x2
};
GG_STATIC_ASSERT(offsetof(BuildingBColor, R) == 0x0);
GG_STATIC_ASSERT(offsetof(BuildingBColor, G) == 0x1);
GG_STATIC_ASSERT(offsetof(BuildingBColor, B) == 0x2);
GG_STATIC_ASSERT(sizeof(BuildingBColor) == 0x3);

// Opaque data object of an anim (read-only here).
class BuildingBAnimDataView
{
public:
    char unknown_00[0x35C];   // +0x0
    bool unknown_35C;   // +0x35C
};
GG_STATIC_ASSERT(offsetof(BuildingBAnimDataView, unknown_35C) == 0x35C);

// Partial view of an AnimClass held in BuildingClass::Anims (read-only here).
class BuildingBAnimObjView
{
public:
    char unknown_00[0xC8];   // +0x0
    BuildingBAnimDataView* unknown_C8;   // +0xC8
    char unknown_CC[0x8];   // +0xCC
    int unknown_D4;   // +0xD4
    char unknown_D8[0x24];   // +0xD8
    int unknown_FC;   // +0xFC
    char unknown_100[0x78];   // +0x100
    char unknown_178;   // +0x178
};
GG_STATIC_ASSERT(offsetof(BuildingBAnimObjView, unknown_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(BuildingBAnimObjView, unknown_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(BuildingBAnimObjView, unknown_FC) == 0xFC);
GG_STATIC_ASSERT(offsetof(BuildingBAnimObjView, unknown_178) == 0x178);

// Partial view of the object at BuildingClass+0x294 (read-only here).
class BuildingBTargetObjView
{
public:
    char unknown_00[0x50];   // +0x0
    void* unknown_50;   // +0x50
};
GG_STATIC_ASSERT(offsetof(BuildingBTargetObjView, unknown_50) == 0x50);

// ParticleSystemTypeClass (opaque here).
class BuildingBParticleSystemTypeView
{
public:
    char unknown_00[0x1];   // +0x0
};
GG_STATIC_ASSERT(sizeof(BuildingBParticleSystemTypeView) == 0x1);

// ParticleSystemClass (constructor 0x62DC50, owned by the particle module; partial; sizeof 0x100 from the push 0x100 at 0x459973 / 0x4599A3 etc).
class BuildingBParticleSystemView
{
public:
    // virtual table (primary), slot index in the comment
    virtual void unused_slot_0();
    virtual void unused_slot_1();
    virtual void unused_slot_2();
    virtual void unused_slot_3();
    virtual void unused_slot_4();
    virtual void unused_slot_5();
    virtual void unused_slot_6();
    virtual void unused_slot_7();
    virtual void vf_8(int a);   // slot 8 (+0x20)
    BuildingBParticleSystemView(BuildingBParticleSystemTypeView* type, HBCoord* where, BuildingBCellView* cell, BuildingBView* owner, const HBCoord* b, int c);
    void Func_6301F0(int a);
    char unknown_04[0xFC];   // +0x4
};
GG_STATIC_ASSERT(sizeof(BuildingBParticleSystemView) == 0x100);

// Partial view of an object reached through BuildingClass+0x218 (read-only here).
class BuildingBAbstractView
{
public:
    // virtual table (primary), slot index in the comment
    virtual void unused_slot_0();
    virtual void unused_slot_1();
    virtual void unused_slot_2();
    virtual void unused_slot_3();
    virtual void unused_slot_4();
    virtual void unused_slot_5();
    virtual void unused_slot_6();
    virtual void unused_slot_7();
    virtual void unused_slot_8();
    virtual void unused_slot_9();
    virtual void unused_slot_10();
    virtual int vf_11();   // slot 11 (+0x2C)
    char unknown_04[0xE8];   // +0x4
    int unknown_EC;   // +0xEC
};
GG_STATIC_ASSERT(offsetof(BuildingBAbstractView, unknown_EC) == 0xEC);

// A vector of points (vptr, Items, Capacity, flags, Count; read-only here).
class BuildingBPointVector
{
public:
    // virtual table (primary), slot index in the comment
    virtual void unused_slot_0_pv();   // slot 0 (+0x0)
    HBPoint2D* Items;   // +0x4
    int Capacity;   // +0x8
    char unknown_0C[0x4];   // +0xC
    int Count;   // +0x10
    char unknown_14[0x4];   // +0x14
};
GG_STATIC_ASSERT(offsetof(BuildingBPointVector, Items) == 0x4);
GG_STATIC_ASSERT(offsetof(BuildingBPointVector, Capacity) == 0x8);
GG_STATIC_ASSERT(offsetof(BuildingBPointVector, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(BuildingBPointVector) == 0x18);

// Partial view of an object in a cell list (read-only here).
class BuildingBObjectView
{
public:
    // virtual table (primary), slot index in the comment
    virtual void unused_slot_0();
    virtual void unused_slot_1();
    virtual void unused_slot_2();
    virtual void unused_slot_3();
    virtual void unused_slot_4();
    virtual void unused_slot_5();
    virtual void unused_slot_6();
    virtual void unused_slot_7();
    virtual void unused_slot_8();
    virtual void unused_slot_9();
    virtual void unused_slot_10();
    virtual int vf_11();   // slot 11 (+0x2C)
    virtual void unused_slot_12();
    virtual void unused_slot_13();
    virtual void unused_slot_14();
    virtual void unused_slot_15();
    virtual void unused_slot_16();
    virtual void unused_slot_17();
    virtual void unused_slot_18();
    virtual void unused_slot_19();
    virtual void unused_slot_20();
    virtual void unused_slot_21();
    virtual void unused_slot_22();
    virtual void unused_slot_23();
    virtual void unused_slot_24();
    virtual void unused_slot_25();
    virtual void unused_slot_26();
    virtual void unused_slot_27();
    virtual void unused_slot_28();
    virtual void unused_slot_29();
    virtual void unused_slot_30();
    virtual void unused_slot_31();
    virtual void unused_slot_32();
    virtual BuildingBTypeView* vf_33();   // slot 33 (+0x84)
    virtual void unused_slot_34();
    virtual void unused_slot_35();
    virtual void unused_slot_36();
    virtual void unused_slot_37();
    virtual void unused_slot_38();
    virtual void unused_slot_39();
    virtual void unused_slot_40();
    virtual void unused_slot_41();
    virtual void unused_slot_42();
    virtual void unused_slot_43();
    virtual void unused_slot_44();
    virtual void unused_slot_45();
    virtual void unused_slot_46();
    virtual void unused_slot_47();
    virtual void unused_slot_48();
    virtual void unused_slot_49();
    virtual void unused_slot_50();
    virtual void unused_slot_51();
    virtual void unused_slot_52();
    virtual void vf_53();   // slot 53 (+0xD4)
    virtual bool vf_54(HBCoord* where, int dir);   // slot 54 (+0xD8)
    virtual void unused_slot_55();
    virtual void unused_slot_56();
    virtual void unused_slot_57();
    virtual void unused_slot_58();
    virtual void unused_slot_59();
    virtual void unused_slot_60();
    virtual void unused_slot_61();
    virtual void vf_62();   // slot 62 (+0xF8)
    virtual void unused_slot_63();
    virtual void unused_slot_64();
    virtual void unused_slot_65();
    virtual void unused_slot_66();
    virtual void unused_slot_67();
    virtual void unused_slot_68();
    virtual void unused_slot_69();
    virtual void unused_slot_70();
    virtual void unused_slot_71();
    virtual void unused_slot_72();
    virtual void unused_slot_73();
    virtual void unused_slot_74();
    virtual void unused_slot_75();
    virtual void unused_slot_76();
    virtual void unused_slot_77();
    virtual void unused_slot_78();
    virtual void unused_slot_79();
    virtual void unused_slot_80();
    virtual void unused_slot_81();
    virtual void unused_slot_82();
    virtual void unused_slot_83();
    virtual void unused_slot_84();
    virtual void unused_slot_85();
    virtual void unused_slot_86();
    virtual void unused_slot_87();
    virtual void unused_slot_88();
    virtual void unused_slot_89();
    virtual void unused_slot_90();
    virtual void unused_slot_91();
    virtual void unused_slot_92();
    virtual void unused_slot_93();
    virtual void unused_slot_94();
    virtual void unused_slot_95();
    virtual void unused_slot_96();
    virtual void unused_slot_97();
    virtual void unused_slot_98();
    virtual void unused_slot_99();
    virtual void unused_slot_100();
    virtual void unused_slot_101();
    virtual void unused_slot_102();
    virtual void unused_slot_103();
    virtual void unused_slot_104();
    virtual void unused_slot_105();
    virtual void unused_slot_106();
    virtual void unused_slot_107();
    virtual void unused_slot_108();
    virtual void unused_slot_109();
    virtual HBCell* vf_110(HBCell* out);   // slot 110 (+0x1B8)
    virtual void unused_slot_111();
    virtual void unused_slot_112();
    virtual void unused_slot_113();
    virtual void unused_slot_114();
    virtual void unused_slot_115();
    virtual void unused_slot_116();
    virtual void unused_slot_117();
    virtual void unused_slot_118();
    virtual void unused_slot_119();
    virtual void unused_slot_120();
    virtual void unused_slot_121();
    virtual void unused_slot_122();
    virtual void unused_slot_123();
    virtual void unused_slot_124();
    virtual void unused_slot_125();
    virtual void unused_slot_126();
    virtual void unused_slot_127();
    virtual void unused_slot_128();
    virtual void unused_slot_129();
    virtual void unused_slot_130();
    virtual void unused_slot_131();
    virtual void unused_slot_132();
    virtual void unused_slot_133();
    virtual void unused_slot_134();
    virtual void unused_slot_135();
    virtual void unused_slot_136();
    virtual void unused_slot_137();
    virtual void unused_slot_138();
    virtual void unused_slot_139();
    virtual void unused_slot_140();
    virtual void unused_slot_141();
    virtual void unused_slot_142();
    virtual void unused_slot_143();
    virtual void unused_slot_144();
    virtual void unused_slot_145();
    virtual void unused_slot_146();
    virtual void unused_slot_147();
    virtual void unused_slot_148();
    virtual void unused_slot_149();
    virtual void unused_slot_150();
    virtual void unused_slot_151();
    virtual void unused_slot_152();
    virtual void unused_slot_153();
    virtual void unused_slot_154();
    virtual void unused_slot_155();
    virtual void unused_slot_156();
    virtual void unused_slot_157();
    virtual void unused_slot_158();
    virtual void unused_slot_159();
    virtual void unused_slot_160();
    virtual void unused_slot_161();
    virtual void unused_slot_162();
    virtual void unused_slot_163();
    virtual void unused_slot_164();
    virtual void unused_slot_165();
    virtual void unused_slot_166();
    virtual void unused_slot_167();
    virtual void unused_slot_168();
    virtual void unused_slot_169();
    virtual void unused_slot_170();
    virtual void unused_slot_171();
    virtual void unused_slot_172();
    virtual void unused_slot_173();
    virtual void unused_slot_174();
    virtual void unused_slot_175();
    virtual void unused_slot_176();
    virtual void unused_slot_177();
    virtual void unused_slot_178();
    virtual void unused_slot_179();
    virtual void unused_slot_180();
    virtual void unused_slot_181();
    virtual void unused_slot_182();
    virtual void unused_slot_183();
    virtual void unused_slot_184();
    virtual void unused_slot_185();
    virtual void unused_slot_186();
    virtual void unused_slot_187();
    virtual void unused_slot_188();
    virtual void unused_slot_189();
    virtual void unused_slot_190();
    virtual void unused_slot_191();
    virtual void unused_slot_192();
    virtual void unused_slot_193();
    virtual void unused_slot_194();
    virtual void unused_slot_195();
    virtual void unused_slot_196();
    virtual void unused_slot_197();
    virtual void unused_slot_198();
    virtual void unused_slot_199();
    virtual void unused_slot_200();
    virtual void unused_slot_201();
    virtual void unused_slot_202();
    virtual void unused_slot_203();
    virtual void unused_slot_204();
    virtual void unused_slot_205();
    virtual void unused_slot_206();
    virtual void unused_slot_207();
    virtual void unused_slot_208();
    virtual void unused_slot_209();
    virtual void unused_slot_210();
    virtual void unused_slot_211();
    virtual void unused_slot_212();
    virtual void unused_slot_213();
    virtual void unused_slot_214();
    virtual void unused_slot_215();
    virtual void unused_slot_216();
    virtual void unused_slot_217();
    virtual void unused_slot_218();
    virtual void unused_slot_219();
    virtual void unused_slot_220();
    virtual void unused_slot_221();
    virtual void unused_slot_222();
    virtual void unused_slot_223();
    virtual void unused_slot_224();
    virtual void unused_slot_225();
    virtual void unused_slot_226();
    virtual void unused_slot_227();
    virtual void unused_slot_228();
    virtual void unused_slot_229();
    virtual void unused_slot_230();
    virtual void unused_slot_231();
    virtual void unused_slot_232();
    virtual void unused_slot_233();
    virtual void unused_slot_234();
    virtual void unused_slot_235();
    virtual void unused_slot_236();
    virtual void unused_slot_237();
    virtual void unused_slot_238();
    virtual void unused_slot_239();
    virtual void unused_slot_240();
    virtual void unused_slot_241();
    virtual void unused_slot_242();
    virtual void unused_slot_243();
    virtual void unused_slot_244();
    virtual void unused_slot_245();
    virtual void unused_slot_246();
    virtual void unused_slot_247();
    virtual void unused_slot_248();
    virtual void unused_slot_249();
    virtual void unused_slot_250();
    virtual void unused_slot_251();
    virtual void unused_slot_252();
    virtual void unused_slot_253();
    virtual void unused_slot_254();
    virtual void unused_slot_255();
    virtual void unused_slot_256();
    virtual void unused_slot_257();
    virtual void unused_slot_258();
    virtual void unused_slot_259();
    virtual void unused_slot_260();
    virtual void unused_slot_261();
    virtual void unused_slot_262();
    virtual void unused_slot_263();
    virtual void vf_264();   // slot 264 (+0x420)
    char unknown_04[0x10];   // +0x4
    unsigned char unknown_14;   // +0x14
    char unknown_15[0x1B];   // +0x15
    BuildingBObjectView* NextObject;   // +0x30
    char unknown_34[0x68];   // +0x34
    HBCoord Location;   // +0x9C
};
GG_STATIC_ASSERT(offsetof(BuildingBObjectView, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(BuildingBObjectView, NextObject) == 0x30);
GG_STATIC_ASSERT(offsetof(BuildingBObjectView, Location) == 0x9C);

// CDTimerClass (0xC bytes): start frame (-1 = stopped), unknown dword, frames left.
// Not merged: cluster timers differ in constructors and inline bodies (see house_building_views.h).
struct BuildingBTimer
{
public:
    int GetTimeLeft() const;
    int StartTime;   // +0x0
    int unknown_04;   // +0x4
    int TimeLeft;   // +0x8
};
GG_STATIC_ASSERT(offsetof(BuildingBTimer, StartTime) == 0x0);
GG_STATIC_ASSERT(offsetof(BuildingBTimer, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(BuildingBTimer, TimeLeft) == 0x8);
GG_STATIC_ASSERT(sizeof(BuildingBTimer) == 0xC);

// Any object whose IRTTITypeInfo subobject sits at +4 (read-only here).
class BuildingBRttiHolder
{
public:
    // virtual table (primary), slot index in the comment
    virtual void unused_slot_0_holder();   // slot 0 (+0x0)
    HBRttiBase Rtti;   // +0x4
};
GG_STATIC_ASSERT(offsetof(BuildingBRttiHolder, Rtti) == 0x4);

// Partial view of the target object handed to vf_26 (read-only here).
class BuildingBTargetView
{
public:
    char unknown_00[0x30];   // +0x0
    int unknown_30;   // +0x30
};
GG_STATIC_ASSERT(offsetof(BuildingBTargetView, unknown_30) == 0x30);

// The CRC accumulator (read-only here).
class BuildingBCrcView
{
public:
    void AddBool(bool value);
    void AddInt(int value);
    void AddByte(unsigned char value);
    char unknown_00[0x1];   // +0x0
};
GG_STATIC_ASSERT(sizeof(BuildingBCrcView) == 0x1);

// Partial view of CellClass (read-only here).
class BuildingBCellView
{
public:
    // virtual table (primary), slot index in the comment
    virtual void unused_slot_0();
    virtual void unused_slot_1();
    virtual void unused_slot_2();
    virtual void unused_slot_3();
    virtual void unused_slot_4();
    virtual void unused_slot_5();
    virtual void unused_slot_6();
    virtual void unused_slot_7();
    virtual void unused_slot_8();
    virtual void unused_slot_9();
    virtual void unused_slot_10();
    virtual void unused_slot_11();
    virtual void unused_slot_12();
    virtual void unused_slot_13();
    virtual void unused_slot_14();
    virtual void unused_slot_15();
    virtual void unused_slot_16();
    virtual void unused_slot_17();
    virtual HBCoord* vf_18(HBCoord* out);   // slot 18 (+0x48)
    bool Func_4870B0(int a);
    void Func_487110(int a);
    void Func_487130(int a);
    BuildingBView* Func_47C3D0(HBPoint2D* where, char a, void* b);
    BuildingBView* Func_47EC40(char a);
    BuildingBView* Func_47C520();
    bool Func_4870D0(int a);
    void Func_487150(int a);
    void Func_487170(int a);
    void Func_487180(int a);
    void Func_487160(int a);
    char unknown_04[0x3C];   // +0x4
    int unknown_40;   // +0x40
    int SmudgeIndex;   // +0x44
    char unknown_48[0x9C];   // +0x48
    BuildingBObjectView* FirstObject;   // +0xE4
    char unknown_E8[0x22];   // +0xE8
    short unknown_10A;   // +0x10A
    char unknown_10C[0x12];   // +0x10C
    unsigned char unknown_11E;   // +0x11E
    char unknown_11F[0x5];   // +0x11F
    unsigned int Flags;   // +0x124
};
GG_STATIC_ASSERT(offsetof(BuildingBCellView, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(BuildingBCellView, SmudgeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(BuildingBCellView, FirstObject) == 0xE4);
GG_STATIC_ASSERT(offsetof(BuildingBCellView, unknown_10A) == 0x10A);
GG_STATIC_ASSERT(offsetof(BuildingBCellView, unknown_11E) == 0x11E);
GG_STATIC_ASSERT(offsetof(BuildingBCellView, Flags) == 0x124);

// Partial view of the map object at global 0x87F7E8 (read-only here).
class BuildingBMapView
{
public:
    HBCell* Func_56DC20(HBCell* out, HBCell* start, int a, int b, int c, char d, int e, int f, char g, char h, char i, char j, HBCell* k, char l, char m);
    bool Func_578460(HBCell* cell, int a);
    bool Func_586360(HBCoord* where);
    BuildingBCellView* Func_565730(HBCoord* where);
    BuildingBPointVector* Func_656580(BuildingBTypeView* type);
    void Func_655740(BuildingBView* building, int x, int y);
    void Func_6562D0(HBPoint2D* point);
    BuildingBCellView* Func_5657A0(HBCell* cell);
    BuildingBCellView* GetCellAtCoord(HBCoord coord);
    char unknown_00[0x1];   // +0x0
};
GG_STATIC_ASSERT(sizeof(BuildingBMapView) == 0x1);

// Partial view of the tactical object behind global 0x887324 (read-only here).
class BuildingBTacticalView
{
public:
    HBPoint2D* Func_6D2070(HBPoint2D* out, const HBPoint2D* in);
    void Func_6D2140(const HBCoord* in, HBPoint2D* out);
    char unknown_00[0xB0];   // +0x0
    HBPoint2D Offset;   // +0xB0
};
GG_STATIC_ASSERT(offsetof(BuildingBTacticalView, Offset) == 0xB0);

// AudioController embedded in a techno (0x14 bytes).
class BuildingBAudioView
{
public:
    void Func_405BE0();
    int unknown_00;   // +0x0
    char unknown_04[0x10];   // +0x4
};
GG_STATIC_ASSERT(offsetof(BuildingBAudioView, unknown_00) == 0x0);
GG_STATIC_ASSERT(sizeof(BuildingBAudioView) == 0x14);

// Partial view of the BuildingTypeClass object at BuildingClass+0x520.
class BuildingBTypeView
{
public:
    // virtual table (primary), slot index in the comment
    virtual void unused_slot_0();
    virtual void unused_slot_1();
    virtual void unused_slot_2();
    virtual void unused_slot_3();
    virtual void unused_slot_4();
    virtual void unused_slot_5();
    virtual void unused_slot_6();
    virtual void unused_slot_7();
    virtual void unused_slot_8();
    virtual void unused_slot_9();
    virtual void unused_slot_10();
    virtual void unused_slot_11();
    virtual void unused_slot_12();
    virtual void unused_slot_13();
    virtual void unused_slot_14();
    virtual void unused_slot_15();
    virtual void unused_slot_16();
    virtual void unused_slot_17();
    virtual void unused_slot_18();
    virtual void unused_slot_19();
    virtual void unused_slot_20();
    virtual void unused_slot_21();
    virtual void unused_slot_22();
    virtual void unused_slot_23();
    virtual void unused_slot_24();
    virtual void unused_slot_25();
    virtual void unused_slot_26();
    virtual void unused_slot_27();
    virtual void unused_slot_28();
    virtual void unused_slot_29();
    virtual void unused_slot_30();
    virtual void unused_slot_31();
    virtual void unused_slot_32();
    virtual void unused_slot_33();
    virtual void unused_slot_34();
    virtual void unused_slot_35();
    virtual void unused_slot_36();
    virtual void unused_slot_37();
    virtual void unused_slot_38();
    virtual int vf_39();   // slot 39 (+0x9C)
    virtual void unused_slot_40();
    virtual void unused_slot_41();
    virtual void unused_slot_42();
    virtual void unused_slot_43();
    virtual void unused_slot_44();
    virtual void unused_slot_45();
    virtual int vf_46(BuildingBHouseView* house, int a);   // slot 46 (+0xB8)
    virtual void unused_slot_47();
    virtual int vf_48();   // slot 48 (+0xC0)
    int Func_45EC90();
    int Func_45ECA0(int a);
    HBRect* Func_465570(HBRect* out);
    int* Func_7177C0(int a);
    bool Func_465D40();
    char unknown_04[0x5C];   // +0x4
    int unknown_60;   // +0x60
    char unknown_64[0x3A4];   // +0x64
    int unknown_408;   // +0x408
    char unknown_40C[0x170];   // +0x40C
    int unknown_57C;   // +0x57C
    char unknown_580[0x6C];   // +0x580
    bool unknown_5EC;   // +0x5EC
    bool unknown_5ED;   // +0x5ED
    char unknown_5EE[0x2];   // +0x5EE
    int unknown_5F0;   // +0x5F0
    int unknown_5F4;   // +0x5F4
    char unknown_5F8[0x84];   // +0x5F8
    int unknown_67C;   // +0x67C
    char unknown_680[0xE4];   // +0x680
    BuildingBParticleSystemTypeView* unknown_764;   // +0x764
    HBCoord unknown_coord_768;   // +0x768
    BuildingBParticleSystemTypeView* unknown_774;   // +0x774
    char unknown_778[0x54];   // +0x778
    HBCoord unknown_coords_7CC[4];   // +0x7CC
    char unknown_7FC[0x49E];   // +0x7FC
    bool unknown_C9A;   // +0xC9A
    char unknown_C9B[0x2];   // +0xC9B
    bool unknown_C9D;   // +0xC9D
    char unknown_C9E[0x3];   // +0xC9E
    bool unknown_CA1;   // +0xCA1
    char unknown_CA2[0x2B];   // +0xCA2
    bool unknown_CCD;   // +0xCCD
    char unknown_CCE[0x176];   // +0xCCE
    HBPoint2D PointE44;   // +0xE44
    char unknown_E4C[0x6C];   // +0xE4C
    int unknown_EB8;   // +0xEB8
    HBCoord CoordEBC;   // +0xEBC
    HBCoord CoordEC8;   // +0xEC8
    char unknown_ED4[0x10];   // +0xED4
    int unknown_EE4;   // +0xEE4
    char unknown_EE8[0x2F8];   // +0xEE8
    HBPoint2D PointOffset;   // +0x11E0
    char unknown_11E8[0x33C];   // +0x11E8
    int unknown_1524;   // +0x1524
    int unknown_1528;   // +0x1528
    int unknown_152C;   // +0x152C
    char unknown_1530[0x22];   // +0x1530
    bool unknown_1552;   // +0x1552
    char unknown_1553[0x19];   // +0x1553
    int unknown_156C;   // +0x156C
    char unknown_1570[0x3];   // +0x1570
    bool unknown_1573;   // +0x1573
    bool unknown_1574;   // +0x1574
    char unknown_1575[0x5];   // +0x1575
    bool unknown_157A;   // +0x157A
    bool unknown_157B;   // +0x157B
    bool unknown_157C;   // +0x157C
    char unknown_157D[0xB];   // +0x157D
    HBPoint2D OccupyPoints[1];   // +0x1588
    char unknown_1590[0x119];   // +0x1590
    bool unknown_16A9;   // +0x16A9
    char unknown_16AA[0x2];   // +0x16AA
    bool unknown_16AC;   // +0x16AC
    char unknown_16AD[0xC];   // +0x16AD
    bool unknown_16B9;   // +0x16B9
    char unknown_16BA[0xB];   // +0x16BA
    bool unknown_16C5;   // +0x16C5
    bool unknown_16C6;   // +0x16C6
    bool unknown_16C7;   // +0x16C7
    char unknown_16C8[0x3F];   // +0x16C8
    char unknown_1707;   // +0x1707
    bool unknown_1708;   // +0x1708
};
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_60) == 0x60);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_408) == 0x408);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_57C) == 0x57C);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_5EC) == 0x5EC);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_5ED) == 0x5ED);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_5F0) == 0x5F0);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_5F4) == 0x5F4);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_67C) == 0x67C);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_764) == 0x764);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_coord_768) == 0x768);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_774) == 0x774);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_coords_7CC) == 0x7CC);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_C9A) == 0xC9A);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_C9D) == 0xC9D);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_CA1) == 0xCA1);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_CCD) == 0xCCD);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, PointE44) == 0xE44);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_EB8) == 0xEB8);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, CoordEBC) == 0xEBC);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, CoordEC8) == 0xEC8);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_EE4) == 0xEE4);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, PointOffset) == 0x11E0);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_1524) == 0x1524);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_1528) == 0x1528);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_152C) == 0x152C);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_1552) == 0x1552);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_156C) == 0x156C);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_1573) == 0x1573);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_1574) == 0x1574);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_157A) == 0x157A);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_157B) == 0x157B);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_157C) == 0x157C);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, OccupyPoints) == 0x1588);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_16A9) == 0x16A9);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_16AC) == 0x16AC);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_16B9) == 0x16B9);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_16C5) == 0x16C5);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_16C6) == 0x16C6);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_16C7) == 0x16C7);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_1707) == 0x1707);
GG_STATIC_ASSERT(offsetof(BuildingBTypeView, unknown_1708) == 0x1708);

// Partial view of the owning HouseClass (BuildingClass+0x21C).
class BuildingBHouseView
{
public:
    bool Func_50B6F0();
    double Func_4FCE30();
    bool Func_50B730();
    bool Func_4F9A50(BuildingBHouseView* other);
    char unknown_00[0x30];   // +0x0
    int unknown_30;   // +0x30
    char unknown_34[0x1B4];   // +0x34
    int SideIndex;   // +0x1E8
    char unknown_1EC[0xB8];   // +0x1EC
    BuildingBTimer unknown_timer_2A4;   // +0x2A4
    char unknown_2B0[0x5449];   // +0x2B0
    BuildingBColor unknown_color_56F9;   // +0x56F9
    char unknown_56FC[0x7F];   // +0x56FC
    bool unknown_577B;   // +0x577B
};
GG_STATIC_ASSERT(offsetof(BuildingBHouseView, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(BuildingBHouseView, SideIndex) == 0x1E8);
GG_STATIC_ASSERT(offsetof(BuildingBHouseView, unknown_timer_2A4) == 0x2A4);
GG_STATIC_ASSERT(offsetof(BuildingBHouseView, unknown_color_56F9) == 0x56F9);
GG_STATIC_ASSERT(offsetof(BuildingBHouseView, unknown_577B) == 0x577B);

// VeterancyStruct embedded at +0x150 of a techno (4 bytes).
struct BuildingBVeterancyView
{
public:
    bool Func_750010();
    int Value;   // +0x0
};
GG_STATIC_ASSERT(offsetof(BuildingBVeterancyView, Value) == 0x0);
GG_STATIC_ASSERT(sizeof(BuildingBVeterancyView) == 0x4);

// Partial view of the type object of an occupant (InfantryTypeClass).
class BuildingBOccupantTypeView
{
public:
    char unknown_00[0xE04];   // +0x0
    int unknown_E04;   // +0xE04
    char unknown_E08[0x18];   // +0xE08
    int unknown_E20;   // +0xE20
};
GG_STATIC_ASSERT(offsetof(BuildingBOccupantTypeView, unknown_E04) == 0xE04);
GG_STATIC_ASSERT(offsetof(BuildingBOccupantTypeView, unknown_E20) == 0xE20);

// Partial view of an occupant of the building (an InfantryClass).
class BuildingBOccupantView
{
public:
    // virtual table (primary), slot index in the comment
    virtual void unused_slot_0();
    virtual void unused_slot_1();
    virtual void unused_slot_2();
    virtual void unused_slot_3();
    virtual void unused_slot_4();
    virtual void unused_slot_5();
    virtual void unused_slot_6();
    virtual void unused_slot_7();
    virtual void unused_slot_8();
    virtual void unused_slot_9();
    virtual void unused_slot_10();
    virtual void unused_slot_11();
    virtual void unused_slot_12();
    virtual void unused_slot_13();
    virtual void unused_slot_14();
    virtual void unused_slot_15();
    virtual void unused_slot_16();
    virtual void unused_slot_17();
    virtual void unused_slot_18();
    virtual HBCoord* vf_19(HBCoord* out, int a);   // slot 19 (+0x4C)
    virtual void unused_slot_20();
    virtual void unused_slot_21();
    virtual void unused_slot_22();
    virtual void unused_slot_23();
    virtual void unused_slot_24();
    virtual void unused_slot_25();
    virtual void unused_slot_26();
    virtual void unused_slot_27();
    virtual void unused_slot_28();
    virtual void unused_slot_29();
    virtual void unused_slot_30();
    virtual void unused_slot_31();
    virtual void unused_slot_32();
    virtual void unused_slot_33();
    virtual void unused_slot_34();
    virtual void unused_slot_35();
    virtual void unused_slot_36();
    virtual void unused_slot_37();
    virtual void unused_slot_38();
    virtual void unused_slot_39();
    virtual void unused_slot_40();
    virtual void unused_slot_41();
    virtual void unused_slot_42();
    virtual void unused_slot_43();
    virtual void unused_slot_44();
    virtual void unused_slot_45();
    virtual void unused_slot_46();
    virtual void unused_slot_47();
    virtual void unused_slot_48();
    virtual void unused_slot_49();
    virtual void unused_slot_50();
    virtual void unused_slot_51();
    virtual void unused_slot_52();
    virtual void unused_slot_53();
    virtual void unused_slot_54();
    virtual void unused_slot_55();
    virtual void unused_slot_56();
    virtual void unused_slot_57();
    virtual void unused_slot_58();
    virtual void unused_slot_59();
    virtual void unused_slot_60();
    virtual void unused_slot_61();
    virtual void unused_slot_62();
    virtual void unused_slot_63();
    virtual void unused_slot_64();
    virtual void unused_slot_65();
    virtual void unused_slot_66();
    virtual void unused_slot_67();
    virtual void unused_slot_68();
    virtual void unused_slot_69();
    virtual void unused_slot_70();
    virtual void unused_slot_71();
    virtual void unused_slot_72();
    virtual void unused_slot_73();
    virtual void unused_slot_74();
    virtual void unused_slot_75();
    virtual void unused_slot_76();
    virtual void unused_slot_77();
    virtual void unused_slot_78();
    virtual void unused_slot_79();
    virtual void unused_slot_80();
    virtual void unused_slot_81();
    virtual void unused_slot_82();
    virtual void unused_slot_83();
    virtual void unused_slot_84();
    virtual void unused_slot_85();
    virtual void unused_slot_86();
    virtual void unused_slot_87();
    virtual void unused_slot_88();
    virtual void unused_slot_89();
    virtual void unused_slot_90();
    virtual void unused_slot_91();
    virtual void unused_slot_92();
    virtual void vf_93(const HBCoord* where, int a, int b);   // slot 93 (+0x174)
    virtual void unused_slot_94();
    virtual void unused_slot_95();
    virtual void unused_slot_96();
    virtual void unused_slot_97();
    virtual void unused_slot_98();
    virtual void unused_slot_99();
    virtual void unused_slot_100();
    virtual void unused_slot_101();
    virtual void unused_slot_102();
    virtual void unused_slot_103();
    virtual void unused_slot_104();
    virtual void unused_slot_105();
    virtual void unused_slot_106();
    virtual void unused_slot_107();
    virtual void unused_slot_108();
    virtual void unused_slot_109();
    virtual void unused_slot_110();
    virtual void unused_slot_111();
    virtual void unused_slot_112();
    virtual void unused_slot_113();
    virtual void unused_slot_114();
    virtual void unused_slot_115();
    virtual void unused_slot_116();
    virtual void unused_slot_117();
    virtual void unused_slot_118();
    virtual void unused_slot_119();
    virtual void unused_slot_120();
    virtual void unused_slot_121();
    virtual void unused_slot_122();
    virtual void unused_slot_123();
    virtual void unused_slot_124();
    virtual void unused_slot_125();
    virtual void unused_slot_126();
    virtual void unused_slot_127();
    virtual void unused_slot_128();
    virtual void unused_slot_129();
    virtual void unused_slot_130();
    virtual void unused_slot_131();
    virtual void unused_slot_132();
    virtual void unused_slot_133();
    virtual void unused_slot_134();
    virtual void unused_slot_135();
    virtual void unused_slot_136();
    virtual void unused_slot_137();
    virtual void unused_slot_138();
    virtual void unused_slot_139();
    virtual void unused_slot_140();
    virtual void unused_slot_141();
    virtual void unused_slot_142();
    virtual void unused_slot_143();
    virtual void unused_slot_144();
    virtual void unused_slot_145();
    virtual void unused_slot_146();
    virtual void unused_slot_147();
    virtual void unused_slot_148();
    virtual void unused_slot_149();
    virtual void unused_slot_150();
    virtual void unused_slot_151();
    virtual void unused_slot_152();
    virtual void unused_slot_153();
    virtual void unused_slot_154();
    virtual void unused_slot_155();
    virtual void unused_slot_156();
    virtual void unused_slot_157();
    virtual void unused_slot_158();
    virtual void unused_slot_159();
    virtual void unused_slot_160();
    virtual void unused_slot_161();
    virtual void unused_slot_162();
    virtual void unused_slot_163();
    virtual void unused_slot_164();
    virtual void unused_slot_165();
    virtual void unused_slot_166();
    virtual void unused_slot_167();
    virtual void unused_slot_168();
    virtual void unused_slot_169();
    virtual void unused_slot_170();
    virtual void unused_slot_171();
    virtual void unused_slot_172();
    virtual void unused_slot_173();
    virtual void unused_slot_174();
    virtual void unused_slot_175();
    virtual void unused_slot_176();
    virtual void unused_slot_177();
    virtual void unused_slot_178();
    virtual void unused_slot_179();
    virtual void unused_slot_180();
    virtual void unused_slot_181();
    virtual void unused_slot_182();
    virtual void unused_slot_183();
    virtual void unused_slot_184();
    virtual void unused_slot_185();
    virtual void unused_slot_186();
    virtual void unused_slot_187();
    virtual void unused_slot_188();
    virtual void unused_slot_189();
    virtual void unused_slot_190();
    virtual void unused_slot_191();
    virtual void unused_slot_192();
    virtual void unused_slot_193();
    virtual void unused_slot_194();
    virtual void unused_slot_195();
    virtual void unused_slot_196();
    virtual void unused_slot_197();
    virtual void unused_slot_198();
    virtual void unused_slot_199();
    virtual void unused_slot_200();
    virtual void unused_slot_201();
    virtual void unused_slot_202();
    virtual void unused_slot_203();
    virtual void unused_slot_204();
    virtual void unused_slot_205();
    virtual void unused_slot_206();
    virtual void unused_slot_207();
    virtual void unused_slot_208();
    virtual void unused_slot_209();
    virtual void unused_slot_210();
    virtual void unused_slot_211();
    virtual void unused_slot_212();
    virtual void unused_slot_213();
    virtual void unused_slot_214();
    virtual void unused_slot_215();
    virtual void unused_slot_216();
    virtual void unused_slot_217();
    virtual void unused_slot_218();
    virtual void unused_slot_219();
    virtual void unused_slot_220();
    virtual void unused_slot_221();
    virtual void unused_slot_222();
    virtual void unused_slot_223();
    virtual void unused_slot_224();
    virtual void unused_slot_225();
    virtual void unused_slot_226();
    virtual void unused_slot_227();
    virtual void unused_slot_228();
    virtual void unused_slot_229();
    virtual void unused_slot_230();
    virtual void unused_slot_231();
    virtual void unused_slot_232();
    virtual void unused_slot_233();
    virtual void unused_slot_234();
    virtual void unused_slot_235();
    virtual void unused_slot_236();
    virtual void unused_slot_237();
    virtual void unused_slot_238();
    virtual void unused_slot_239();
    virtual void unused_slot_240();
    virtual void unused_slot_241();
    virtual void unused_slot_242();
    virtual void unused_slot_243();
    virtual void unused_slot_244();
    virtual void unused_slot_245();
    virtual void unused_slot_246();
    virtual void unused_slot_247();
    virtual void unused_slot_248();
    virtual void unused_slot_249();
    virtual void unused_slot_250();
    virtual void unused_slot_251();
    virtual void unused_slot_252();
    virtual void unused_slot_253();
    virtual void vf_254(int a);   // slot 254 (+0x3F8)
    char unknown_04[0x10];   // +0x4
    unsigned char unknown_14;   // +0x14
    char unknown_15[0x7B];   // +0x15
    bool IsAlive;   // +0x90
    char unknown_91[0xBF];   // +0x91
    BuildingBVeterancyView Veterancy;   // +0x150
    char unknown_154[0x450];   // +0x154
    BuildingBView* unknown_5A4;   // +0x5A4
    char unknown_5A8[0x118];   // +0x5A8
    BuildingBOccupantTypeView* Type;   // +0x6C0
};
GG_STATIC_ASSERT(offsetof(BuildingBOccupantView, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(BuildingBOccupantView, IsAlive) == 0x90);
GG_STATIC_ASSERT(offsetof(BuildingBOccupantView, Veterancy) == 0x150);
GG_STATIC_ASSERT(offsetof(BuildingBOccupantView, unknown_5A4) == 0x5A4);
GG_STATIC_ASSERT(offsetof(BuildingBOccupantView, Type) == 0x6C0);

// Partial view of the rules object at global 0x8871E0.
class BuildingBRulesView
{
public:
    char unknown_00[0x14F8];   // +0x0
    int unknown_14F8;   // +0x14F8
    int unknown_14FC;   // +0x14FC
    int unknown_1500;   // +0x1500
};
GG_STATIC_ASSERT(offsetof(BuildingBRulesView, unknown_14F8) == 0x14F8);
GG_STATIC_ASSERT(offsetof(BuildingBRulesView, unknown_14FC) == 0x14FC);
GG_STATIC_ASSERT(offsetof(BuildingBRulesView, unknown_1500) == 0x1500);

// Partial view of BuildingClass (derives TechnoClass at 0; sizeof 0x720).
class BuildingBView
{
public:
    // virtual table (primary), slot index in the comment
    virtual void unused_slot_0();
    virtual void unused_slot_1();
    virtual void unused_slot_2();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);   // slot 3 (+0xC)
    virtual void unused_slot_4();
    virtual HRESULT __stdcall Load(IStream* pStm);   // slot 5 (+0x14)
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // slot 6 (+0x18)
    virtual void unused_slot_7();
    virtual void* vf_8(unsigned int flags);   // slot 8 (+0x20)
    virtual void unused_slot_9();
    virtual void unused_slot_10();
    virtual int vf_11();   // slot 11 (+0x2C)
    virtual int vf_12();   // slot 12 (+0x30)
    virtual void vf_13(BuildingBCrcView* crc);   // slot 13 (+0x34)
    virtual void unused_slot_14();
    virtual void unused_slot_15();
    virtual void unused_slot_16();
    virtual void unused_slot_17();
    virtual HBCoord* vf_18(HBCoord* out);   // slot 18 (+0x48)
    virtual void unused_slot_19();
    virtual void unused_slot_20();
    virtual void unused_slot_21();
    virtual void unused_slot_22();
    virtual void unused_slot_23();
    virtual void unused_slot_24();
    virtual void unused_slot_25();
    virtual int vf_26(bool a, BuildingBTargetView* target);   // slot 26 (+0x68)
    virtual int vf_27();   // slot 27 (+0x6C)
    virtual void unused_slot_28();
    virtual void unused_slot_29();
    virtual void unused_slot_30();
    virtual void unused_slot_31();
    virtual bool vf_32();   // slot 32 (+0x80)
    virtual BuildingBTypeView* vf_33();   // slot 33 (+0x84)
    virtual BuildingBTypeView* vf_34();   // slot 34 (+0x88)
    virtual void unused_slot_35();
    virtual int vf_36();   // slot 36 (+0x90)
    virtual bool vf_37();   // slot 37 (+0x94)
    virtual void unused_slot_38();
    virtual void unused_slot_39();
    virtual bool vf_40();   // slot 40 (+0xA0)
    virtual HBCoord* vf_41(HBCoord* out);   // slot 41 (+0xA4)
    virtual void unused_slot_42();
    virtual HBCoord* vf_43(HBCoord* out);   // slot 43 (+0xAC)
    virtual void unused_slot_44();
    virtual HBCoord* vf_45(HBCoord* out, int unused);   // slot 45 (+0xB4)
    virtual void unused_slot_46();
    virtual void unused_slot_47();
    virtual void unused_slot_48();
    virtual void unused_slot_49();
    virtual void unused_slot_50();
    virtual void unused_slot_51();
    virtual void unused_slot_52();
    virtual void vf_53();   // slot 53 (+0xD4)
    virtual bool vf_54(HBCoord* where, int dir);   // slot 54 (+0xD8)
    virtual void unused_slot_55();
    virtual void unused_slot_56();
    virtual void unused_slot_57();
    virtual void unused_slot_58();
    virtual void unused_slot_59();
    virtual void vf_60(HBCoord* coord);   // slot 60 (+0xF0)
    virtual void vf_61(HBCoord* coord);   // slot 61 (+0xF4)
    virtual void vf_62();   // slot 62 (+0xF8)
    virtual void unused_slot_63();
    virtual void unused_slot_64();
    virtual void unused_slot_65();
    virtual HBCell* vf_66(int a);   // slot 66 (+0x108)
    virtual void unused_slot_67();
    virtual void unused_slot_68();
    virtual void unused_slot_69();
    virtual void unused_slot_70();
    virtual void unused_slot_71();
    virtual void unused_slot_72();
    virtual void unused_slot_73();
    virtual void unused_slot_74();
    virtual HBRect* vf_75(HBRect* out);   // slot 75 (+0x12C)
    virtual void vf_76(BuildingBColor tint);   // slot 76 (+0x130)
    virtual void unused_slot_77();
    virtual void unused_slot_78();
    virtual void unused_slot_79();
    virtual void unused_slot_80();
    virtual void unused_slot_81();
    virtual void vf_82(int a);   // slot 82 (+0x148)
    virtual void unused_slot_83();
    virtual void unused_slot_84();
    virtual void vf_85(int a, int b, int c);   // slot 85 (+0x154)
    virtual void unused_slot_86();
    virtual void unused_slot_87();
    virtual bool vf_88();   // slot 88 (+0x160)
    virtual void unused_slot_89();
    virtual void unused_slot_90();
    virtual void unused_slot_91();
    virtual void unused_slot_92();
    virtual void unused_slot_93();
    virtual void unused_slot_94();
    virtual void unused_slot_95();
    virtual void unused_slot_96();
    virtual int vf_97();   // slot 97 (+0x184)
    virtual void unused_slot_98();
    virtual void unused_slot_99();
    virtual void unused_slot_100();
    virtual void unused_slot_101();
    virtual void unused_slot_102();
    virtual void unused_slot_103();
    virtual void unused_slot_104();
    virtual void unused_slot_105();
    virtual void unused_slot_106();
    virtual void unused_slot_107();
    virtual void unused_slot_108();
    virtual void unused_slot_109();
    virtual HBCell* vf_110(HBCell* out);   // slot 110 (+0x1B8)
    virtual BuildingBCellView* vf_111();   // slot 111 (+0x1BC)
    virtual void unused_slot_112();
    virtual void unused_slot_113();
    virtual void unused_slot_114();
    virtual void unused_slot_115();
    virtual void unused_slot_116();
    virtual void unused_slot_117();
    virtual void unused_slot_118();
    virtual void unused_slot_119();
    virtual void unused_slot_120();
    virtual int vf_121();   // slot 121 (+0x1E4)
    virtual void unused_slot_122();
    virtual void unused_slot_123();
    virtual void unused_slot_124();
    virtual void unused_slot_125();
    virtual void unused_slot_126();
    virtual void unused_slot_127();
    virtual bool vf_128();   // slot 128 (+0x200)
    virtual void unused_slot_129();
    virtual void unused_slot_130();
    virtual void unused_slot_131();
    virtual void unused_slot_132();
    virtual void unused_slot_133();
    virtual void unused_slot_134();
    virtual void unused_slot_135();
    virtual void unused_slot_136();
    virtual void unused_slot_137();
    virtual void unused_slot_138();
    virtual void unused_slot_139();
    virtual void unused_slot_140();
    virtual void unused_slot_141();
    virtual void unused_slot_142();
    virtual void unused_slot_143();
    virtual void unused_slot_144();
    virtual void unused_slot_145();
    virtual void unused_slot_146();
    virtual void unused_slot_147();
    virtual void unused_slot_148();
    virtual void unused_slot_149();
    virtual void unused_slot_150();
    virtual void unused_slot_151();
    virtual void unused_slot_152();
    virtual void unused_slot_153();
    virtual void unused_slot_154();
    virtual void unused_slot_155();
    virtual void unused_slot_156();
    virtual void unused_slot_157();
    virtual void unused_slot_158();
    virtual void unused_slot_159();
    virtual void unused_slot_160();
    virtual bool vf_161();   // slot 161 (+0x284)
    virtual void unused_slot_162();
    virtual void unused_slot_163();
    virtual void unused_slot_164();
    virtual void unused_slot_165();
    virtual void unused_slot_166();
    virtual void unused_slot_167();
    virtual bool vf_168();   // slot 168 (+0x2A0)
    virtual bool vf_169();   // slot 169 (+0x2A4)
    virtual void unused_slot_170();
    virtual bool vf_171();   // slot 171 (+0x2AC)
    virtual void unused_slot_172();
    virtual void unused_slot_173();
    virtual void unused_slot_174();
    virtual void unused_slot_175();
    virtual void unused_slot_176();
    virtual void unused_slot_177();
    virtual void unused_slot_178();
    virtual void unused_slot_179();
    virtual int vf_180();   // slot 180 (+0x2D0)
    virtual int vf_181();   // slot 181 (+0x2D4)
    virtual int vf_182();   // slot 182 (+0x2D8)
    virtual int vf_183();   // slot 183 (+0x2DC)
    virtual void vf_184();   // slot 184 (+0x2E0)
    virtual void unused_slot_185();
    virtual void unused_slot_186();
    virtual void unused_slot_187();
    virtual void unused_slot_188();
    virtual void unused_slot_189();
    virtual void unused_slot_190();
    virtual void unused_slot_191();
    virtual HBCoord* vf_192(HBCoord* out, int a);   // slot 192 (+0x300)
    virtual void unused_slot_193();
    virtual void unused_slot_194();
    virtual void unused_slot_195();
    virtual void unused_slot_196();
    virtual void unused_slot_197();
    virtual void unused_slot_198();
    virtual void unused_slot_199();
    virtual void unused_slot_200();
    virtual bool vf_201(int* flag);   // slot 201 (+0x324)
    virtual bool vf_202();   // slot 202 (+0x328)
    virtual void unused_slot_203();
    virtual void unused_slot_204();
    virtual void unused_slot_205();
    virtual void unused_slot_206();
    virtual void unused_slot_207();
    virtual void unused_slot_208();
    virtual void unused_slot_209();
    virtual void unused_slot_210();
    virtual void unused_slot_211();
    virtual bool vf_212();   // slot 212 (+0x350)
    virtual void vf_213(int a);   // slot 213 (+0x354)
    virtual void unused_slot_214();
    virtual void unused_slot_215();
    virtual void unused_slot_216();
    virtual void unused_slot_217();
    virtual void unused_slot_218();
    virtual void vf_219();   // slot 219 (+0x36C)
    virtual void unused_slot_220();
    virtual void unused_slot_221();
    virtual void unused_slot_222();
    virtual void unused_slot_223();
    virtual void unused_slot_224();
    virtual void unused_slot_225();
    virtual void unused_slot_226();
    virtual void unused_slot_227();
    virtual void unused_slot_228();
    virtual void unused_slot_229();
    virtual void unused_slot_230();
    virtual void unused_slot_231();
    virtual void unused_slot_232();
    virtual void unused_slot_233();
    virtual void unused_slot_234();
    virtual void unused_slot_235();
    virtual void unused_slot_236();
    virtual void unused_slot_237();
    virtual void unused_slot_238();
    virtual void unused_slot_239();
    virtual void unused_slot_240();
    virtual void unused_slot_241();
    virtual void unused_slot_242();
    virtual void unused_slot_243();
    virtual void unused_slot_244();
    virtual void unused_slot_245();
    virtual void unused_slot_246();
    virtual void unused_slot_247();
    virtual void unused_slot_248();
    virtual void unused_slot_249();
    virtual void unused_slot_250();
    virtual void unused_slot_251();
    virtual void unused_slot_252();
    virtual void unused_slot_253();
    virtual void vf_254(int a);   // slot 254 (+0x3F8)
    virtual bool vf_255();   // slot 255 (+0x3FC)
    virtual bool vf_256();   // slot 256 (+0x400)
    virtual int vf_257();   // slot 257 (+0x404)
    virtual int vf_258();   // slot 258 (+0x408)
    virtual void unused_slot_259();
    virtual void vf_260(bool refresh);   // slot 260 (+0x410)
    virtual void unused_slot_261();
    virtual void unused_slot_262();
    virtual void unused_slot_263();
    virtual void unused_slot_264();
    virtual void unused_slot_265();
    virtual void unused_slot_266();
    virtual void unused_slot_267();
    virtual void unused_slot_268();
    virtual void unused_slot_269();
    virtual void unused_slot_270();
    virtual void unused_slot_271();
    virtual void unused_slot_272();
    virtual void unused_slot_273();
    virtual void unused_slot_274();
    virtual void unused_slot_275();
    virtual void unused_slot_276();
    virtual void unused_slot_277();
    virtual void unused_slot_278();
    virtual void vf_279(int a);   // slot 279 (+0x45C)
    virtual void vf_280(int a);   // slot 280 (+0x460)
    virtual int vf_281(int a);   // slot 281 (+0x464)
    virtual void vf_282();   // slot 282 (+0x468)
    virtual void unused_slot_283();
    virtual void unused_slot_284();
    virtual void unused_slot_285();
    virtual void unused_slot_286();
    virtual void unused_slot_287();
    virtual void vf_288(void* first, void* second);   // slot 288 (+0x480)
    virtual void unused_slot_289();
    virtual void unused_slot_290();
    virtual void unused_slot_291();
    virtual bool vf_292(HBCoord* where, int dir);   // slot 292 (+0x490)
    virtual void unused_slot_293();
    virtual void vf_294();   // slot 294 (+0x498)
    virtual void vf_295();   // slot 295 (+0x49C)
    virtual void unused_slot_296();
    virtual void unused_slot_297();
    virtual void unused_slot_298();
    virtual void unused_slot_299();
    virtual void unused_slot_300();
    virtual void unused_slot_301();
    virtual void unused_slot_302();
    virtual void unused_slot_303();
    virtual void unused_slot_304();
    virtual void unused_slot_305();
    virtual void unused_slot_306();
    virtual void unused_slot_307();
    virtual void unused_slot_308();
    virtual void unused_slot_309();
    virtual void unused_slot_310();
    virtual void unused_slot_311();
    virtual void unused_slot_312();
    virtual void unused_slot_313();
    virtual void unused_slot_314();
    virtual void unused_slot_315();
    virtual void unused_slot_316();
    virtual void vf_317(HBCell cell);   // slot 317 (+0x4F4)
    virtual void vf_318(HBCell cell);   // slot 318 (+0x4F8)
    virtual void vf_319(HBCell cell);   // slot 319 (+0x4FC)
    virtual void vf_320(HBCell cell);   // slot 320 (+0x500)
    virtual int vf_321();   // slot 321 (+0x504)
    int Func_4566B0();
    void Func_6F9DD0(int a);
    int Func_70E360(int a);
    void ApplyAnimLevel();
    void Func_70C610(void* first);
    void Func_709A30(void* first, void* second);
    bool Func_6FBDC0();
    bool Func_6FBC90();
    void Func_43BCF0();
    bool Func_701120();
    void Func_708E00();
    void Func_70E2B0(int a, int b, int c);
    BuildingBView(const HBNoInit& noInit);
    void Func_70C270(BuildingBCrcView* crc);
    int Func_703860(bool a, BuildingBTargetView* target);
    bool Func_701140();
    void Func_70E140(int a);
    HRESULT __stdcall Func_70BF50(IStream* pStm);
    HRESULT __stdcall Func_70C250(IStream* pStm, BOOL fClearDirty);
    HBCoord* Func_453BF0(HBCoord* out, int a, int b);
    HBCoord* Func_6F3D60(HBCoord* out, int a);
    HBRttiBase Rtti;   // +0x4
    char unknown_08[0xC];   // +0x8
    unsigned char unknown_14;   // +0x14
    char unknown_15[0x57];   // +0x15
    int Health;   // +0x6C
    char unknown_70[0x10];   // +0x70
    bool NeedsRedraw;   // +0x80
    bool InLimbo;   // +0x81
    char unknown_82[0xE];   // +0x82
    bool IsAlive;   // +0x90
    char unknown_91[0xB];   // +0x91
    HBCoord Location;   // +0x9C
    char unknown_A8[0x4];   // +0xA8
    int CurrentMission;   // +0xAC
    char unknown_B0[0x40];   // +0xB0
    unsigned int unknown_F0;   // +0xF0
    char unknown_F4[0x114];   // +0xF4
    HBPoint2D RadarPosition;   // +0x208
    char unknown_210[0x8];   // +0x210
    BuildingBAbstractView* unknown_218;   // +0x218
    BuildingBHouseView* Owner;   // +0x21C
    int unknown_220;   // +0x220
    char unknown_224[0x70];   // +0x224
    BuildingBTargetObjView* unknown_294;   // +0x294
    char unknown_298[0x28];   // +0x298
    void* MindControlledBy;   // +0x2C0
    char unknown_2C4[0x48];   // +0x2C4
    BuildingBParticleSystemView* unknown_30C;   // +0x30C
    char unknown_310[0x10A];   // +0x310
    bool unknown_41A;   // +0x41A
    bool unknown_41B;   // +0x41B
    char unknown_41C[0x7];   // +0x41C
    bool IsRadarTracked;   // +0x423
    char unknown_424[0xE0];   // +0x424
    int EMPLockRemaining;   // +0x504
    char unknown_508[0x18];   // +0x508
    BuildingBTypeView* Type;   // +0x520
    void* Factory;   // +0x524
    BuildingBTimer C4Timer;   // +0x528
    int BState;   // +0x534
    int QueueBState;   // +0x538
    int OwnerCountryIndex;   // +0x53C
    BuildingBRttiHolder* C4AppliedBy;   // +0x540
    int unknown_544;   // +0x544
    BuildingBRttiHolder* FirestormAnim;   // +0x548
    void* PsiWarnAnim;   // +0x54C
    BuildingBTimer FactoryRetryTimer;   // +0x550
    BuildingBAnimObjView* Anims[21];   // +0x55C
    char unknown_5B0[0x18];   // +0x5B0
    void* DamageFireAnims[8];   // +0x5C8
    char unknown_5E8[0x4];   // +0x5E8
    BuildingBTypeView* Upgrades[3];   // +0x5EC
    char unknown_5F8[0x4];   // +0x5F8
    int unknown_5FC;   // +0x5FC
    void* Spotlight;   // +0x600
    char unknown_604[0x10];   // +0x604
    void* LightSource;   // +0x614
    int LaserFenceFrame;   // +0x618
    int FirestormWallFrame;   // +0x61C
    char unknown_620[0x1C];   // +0x620
    HBRect unknown_rect_63C;   // +0x63C
    HBCoord unknown_coord_64C;   // +0x64C
    HBPoint2D unknown_point_658;   // +0x658
    bool HasPower;   // +0x660
    char unknown_661[0xB];   // +0x661
    BuildingBVector<void> Overpowerers;   // +0x66C
    BuildingBVector<BuildingBOccupantView> Occupants;   // +0x684
    int FiringOccupantIndex;   // +0x69C
    BuildingBAudioView Audio7;   // +0x6A0
    BuildingBAudioView Audio8;   // +0x6B4
    char unknown_6C8[0x2];   // +0x6C8
    bool BeingProduced;   // +0x6CA
    bool ShouldRebuild;   // +0x6CB
    bool HasEngineer;   // +0x6CC
    char unknown_6CD[0x3];   // +0x6CD
    BuildingBTimer CashProductionTimer;   // +0x6D0
    bool unknown_6DC;   // +0x6DC
    bool IsReadyToCommence;   // +0x6DD
    bool NeedsRepairs;   // +0x6DE
    bool C4Applied;   // +0x6DF
    bool NoCrew;   // +0x6E0
    bool unknown_bool_6E1;   // +0x6E1
    bool unknown_bool_6E2;   // +0x6E2
    bool HasBeenCaptured;   // +0x6E3
    bool ActuallyPlacedOnMap;   // +0x6E4
    bool unknown_bool_6E5;   // +0x6E5
    bool IsDamaged;   // +0x6E6
    bool IsFogged;   // +0x6E7
    bool IsBeingRepaired;   // +0x6E8
    char unknown_6E9[0x1];   // +0x6E9
    bool StuffEnabled;   // +0x6EA
    char HasCloakingData;   // +0x6EB
    char CloakRadius;   // +0x6EC
    char Translucency;   // +0x6ED
    char unknown_6EE[0x6];   // +0x6EE
    void* SecretProduction;   // +0x6F4
    char unknown_6F8[0x8];   // +0x6F8
    short unknown_short_700;   // +0x700
    char UpgradeLevel;   // +0x702
    char unknown_703[0x1D];   // +0x703
};
GG_STATIC_ASSERT(offsetof(BuildingBView, Rtti) == 0x4);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(BuildingBView, Health) == 0x6C);
GG_STATIC_ASSERT(offsetof(BuildingBView, NeedsRedraw) == 0x80);
GG_STATIC_ASSERT(offsetof(BuildingBView, InLimbo) == 0x81);
GG_STATIC_ASSERT(offsetof(BuildingBView, IsAlive) == 0x90);
GG_STATIC_ASSERT(offsetof(BuildingBView, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(BuildingBView, CurrentMission) == 0xAC);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_F0) == 0xF0);
GG_STATIC_ASSERT(offsetof(BuildingBView, RadarPosition) == 0x208);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_218) == 0x218);
GG_STATIC_ASSERT(offsetof(BuildingBView, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_220) == 0x220);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_294) == 0x294);
GG_STATIC_ASSERT(offsetof(BuildingBView, MindControlledBy) == 0x2C0);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_30C) == 0x30C);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_41A) == 0x41A);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_41B) == 0x41B);
GG_STATIC_ASSERT(offsetof(BuildingBView, IsRadarTracked) == 0x423);
GG_STATIC_ASSERT(offsetof(BuildingBView, EMPLockRemaining) == 0x504);
GG_STATIC_ASSERT(offsetof(BuildingBView, Type) == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingBView, Factory) == 0x524);
GG_STATIC_ASSERT(offsetof(BuildingBView, C4Timer) == 0x528);
GG_STATIC_ASSERT(offsetof(BuildingBView, BState) == 0x534);
GG_STATIC_ASSERT(offsetof(BuildingBView, QueueBState) == 0x538);
GG_STATIC_ASSERT(offsetof(BuildingBView, OwnerCountryIndex) == 0x53C);
GG_STATIC_ASSERT(offsetof(BuildingBView, C4AppliedBy) == 0x540);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_544) == 0x544);
GG_STATIC_ASSERT(offsetof(BuildingBView, FirestormAnim) == 0x548);
GG_STATIC_ASSERT(offsetof(BuildingBView, PsiWarnAnim) == 0x54C);
GG_STATIC_ASSERT(offsetof(BuildingBView, FactoryRetryTimer) == 0x550);
GG_STATIC_ASSERT(offsetof(BuildingBView, Anims) == 0x55C);
GG_STATIC_ASSERT(offsetof(BuildingBView, DamageFireAnims) == 0x5C8);
GG_STATIC_ASSERT(offsetof(BuildingBView, Upgrades) == 0x5EC);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_5FC) == 0x5FC);
GG_STATIC_ASSERT(offsetof(BuildingBView, Spotlight) == 0x600);
GG_STATIC_ASSERT(offsetof(BuildingBView, LightSource) == 0x614);
GG_STATIC_ASSERT(offsetof(BuildingBView, LaserFenceFrame) == 0x618);
GG_STATIC_ASSERT(offsetof(BuildingBView, FirestormWallFrame) == 0x61C);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_rect_63C) == 0x63C);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_coord_64C) == 0x64C);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_point_658) == 0x658);
GG_STATIC_ASSERT(offsetof(BuildingBView, HasPower) == 0x660);
GG_STATIC_ASSERT(offsetof(BuildingBView, Overpowerers) == 0x66C);
GG_STATIC_ASSERT(offsetof(BuildingBView, Occupants) == 0x684);
GG_STATIC_ASSERT(offsetof(BuildingBView, FiringOccupantIndex) == 0x69C);
GG_STATIC_ASSERT(offsetof(BuildingBView, Audio7) == 0x6A0);
GG_STATIC_ASSERT(offsetof(BuildingBView, Audio8) == 0x6B4);
GG_STATIC_ASSERT(offsetof(BuildingBView, BeingProduced) == 0x6CA);
GG_STATIC_ASSERT(offsetof(BuildingBView, ShouldRebuild) == 0x6CB);
GG_STATIC_ASSERT(offsetof(BuildingBView, HasEngineer) == 0x6CC);
GG_STATIC_ASSERT(offsetof(BuildingBView, CashProductionTimer) == 0x6D0);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_6DC) == 0x6DC);
GG_STATIC_ASSERT(offsetof(BuildingBView, IsReadyToCommence) == 0x6DD);
GG_STATIC_ASSERT(offsetof(BuildingBView, NeedsRepairs) == 0x6DE);
GG_STATIC_ASSERT(offsetof(BuildingBView, C4Applied) == 0x6DF);
GG_STATIC_ASSERT(offsetof(BuildingBView, NoCrew) == 0x6E0);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_bool_6E1) == 0x6E1);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_bool_6E2) == 0x6E2);
GG_STATIC_ASSERT(offsetof(BuildingBView, HasBeenCaptured) == 0x6E3);
GG_STATIC_ASSERT(offsetof(BuildingBView, ActuallyPlacedOnMap) == 0x6E4);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_bool_6E5) == 0x6E5);
GG_STATIC_ASSERT(offsetof(BuildingBView, IsDamaged) == 0x6E6);
GG_STATIC_ASSERT(offsetof(BuildingBView, IsFogged) == 0x6E7);
GG_STATIC_ASSERT(offsetof(BuildingBView, IsBeingRepaired) == 0x6E8);
GG_STATIC_ASSERT(offsetof(BuildingBView, StuffEnabled) == 0x6EA);
GG_STATIC_ASSERT(offsetof(BuildingBView, HasCloakingData) == 0x6EB);
GG_STATIC_ASSERT(offsetof(BuildingBView, CloakRadius) == 0x6EC);
GG_STATIC_ASSERT(offsetof(BuildingBView, Translucency) == 0x6ED);
GG_STATIC_ASSERT(offsetof(BuildingBView, SecretProduction) == 0x6F4);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_short_700) == 0x700);
GG_STATIC_ASSERT(offsetof(BuildingBView, UpgradeLevel) == 0x702);
GG_STATIC_ASSERT(sizeof(BuildingBView) == 0x720);


// FUNCTION: GAMEMD 0x456980 (read-only here; __fastcall, flags in cl/dl)
void BuildingBFunc_456980(char a, char b, HBCoord at, BuildingBColor color, float intensity, char c, char d);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
// FUNCTION: GAMEMD 0x4CAC40 (read-only here; cdecl, double argument)
double __cdecl BuildingBFunc_4CAC40(double value);
// LIBRARY: GAMEMD 0x7C5F00 is the compiler's float-to-long helper.
// The checked cast of `this` the retail code expands inline: only a Building (RTTI 6) survives.
inline BuildingBView* BuildingBCastBuilding(BuildingBView* object)
{
    if (object == 0)
        return 0;
    return object->vf_11() == 6 ? object : 0;
}

// Sets the translucency level on every anim (retail expands this twice inline).
inline void BuildingBView::ApplyAnimLevel()
{
    int level = Translucency;
    if (level == 0xF && vf_26(false, 0) == 5)
        level = 0x10;
    for (int i = 0; i < 21; i++) {
        if (Anims[i])
            Anims[i]->unknown_178 = level;
    }
}
// The checked cast the retail code expands inline: null stays null, any other object must report RTTI 0xB.
inline BuildingBAbstractView* BuildingBCastAbstract(BuildingBAbstractView* object)
{
    if (object == 0)
        return 0;
    return object->vf_11() == 0xB ? object : 0;
}
inline HBRect operator+(const HBRect& r, const HBPoint2D& p)
{
    HBRect result;
    result.X = r.X + p.X;
    result.Y = r.Y + p.Y;
    result.Width = r.Width;
    result.Height = r.Height;
    return result;
}
inline BuildingBCellView* BuildingBMapView::GetCellAtCoord(HBCoord coord)
{
    HBCell cell = BuildingBCellOf(coord);
    return Func_5657A0(&cell);
}
inline int BuildingBTimer::GetTimeLeft() const
{
    int left = TimeLeft;
    if (StartTime != -1) {
        int elapsed = BuildingBFrame - StartTime;
        if (elapsed < left)
            left = left - elapsed;
        else
            left = 0;
    }
    return left;
}
// Layout of the vector family, pinned here because the first member use instantiates the template.
typedef BuildingBVector<void> BuildingBVoidVector;
GG_STATIC_ASSERT(offsetof(BuildingBVoidVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(BuildingBVoidVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(BuildingBVoidVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(BuildingBVoidVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(BuildingBVoidVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(BuildingBVoidVector) == 0x18);


inline bool operator==(const HBCoord& a, const HBCoord& b)
{
    return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
}
inline bool operator==(const HBPoint2D& a, const HBPoint2D& b)
{
    return a.X == b.X && a.Y == b.Y;
}

// GLOBAL: GAMEMD 0xA83DEC (pointer to the item table) / 0xA83DF8 (count) of a global techno array
extern BuildingBOccupantView** BuildingBUnitItems;
extern int BuildingBUnitCount;
// GLOBAL: GAMEMD 0x89C870
extern HBCoord BuildingBGlobal_0089C870;
// GLOBAL: GAMEMD 0x89DDC0 (pointer to the surface)
extern BuildingBSurfaceView* BuildingBSurface;
// GLOBAL: GAMEMD 0xA8EB44 (pointer to the item table) / 0xA8EB50 (count) of the global building array
extern BuildingBView** BuildingBBuildingItems;
extern int BuildingBBuildingCount;
// GLOBAL: GAMEMD 0x89C818 (the empty cell value)
extern HBCell BuildingBEmptyCell;
// GLOBAL: GAMEMD 0x89C848 (retail data, bound by address)
extern HBCoord BuildingBEmptyCoord;
// GLOBAL: GAMEMD 0x8871E0
extern BuildingBRulesView* BuildingBRules;
// GLOBAL: GAMEMD 0xB73550
extern int BuildingBGlobal_00B73550;
// GLOBAL: GAMEMD 0xA83D4C (the local player's house)
extern BuildingBHouseView* BuildingBPlayer;
// GLOBAL: GAMEMD 0xA8B238
extern int BuildingBGlobal_00A8B238;
// GLOBAL: GAMEMD 0xA8B320
extern bool BuildingBGlobal_00A8B320;
// GLOBAL: GAMEMD 0x87F7E8 (the map object; its address is passed in ECX)
extern BuildingBMapView BuildingBMap;
// GLOBAL: GAMEMD 0x887324 (pointer to the tactical object)
extern BuildingBTacticalView* BuildingBTactical;




// BEGIN canonical-layout asserts
GG_STATIC_ASSERT(offsetof(BuildingBView, Health) == HB_BLD_HEALTH);
GG_STATIC_ASSERT(offsetof(BuildingBView, NeedsRedraw) == HB_BLD_NEEDS_REDRAW);
GG_STATIC_ASSERT(offsetof(BuildingBView, InLimbo) == HB_BLD_IN_LIMBO);
GG_STATIC_ASSERT(offsetof(BuildingBView, IsAlive) == HB_BLD_IS_ALIVE);
GG_STATIC_ASSERT(offsetof(BuildingBView, Location) == HB_BLD_LOCATION);
GG_STATIC_ASSERT(offsetof(BuildingBView, CurrentMission) == HB_BLD_CURRENT_MISSION);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_218) == HB_BLD_UNKNOWN_218);
GG_STATIC_ASSERT(offsetof(BuildingBView, Owner) == HB_BLD_OWNER);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_294) == HB_BLD_UNKNOWN_294);
GG_STATIC_ASSERT(offsetof(BuildingBView, MindControlledBy) == HB_BLD_MIND_CONTROLLED_BY);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_30C) == HB_BLD_UNKNOWN_30C);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_41A) == HB_BLD_UNKNOWN_41A);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_41B) == HB_BLD_UNKNOWN_41B);
GG_STATIC_ASSERT(offsetof(BuildingBView, Type) == HB_BLD_TYPE);
GG_STATIC_ASSERT(offsetof(BuildingBView, Factory) == HB_BLD_FACTORY);
GG_STATIC_ASSERT(offsetof(BuildingBView, C4Timer) == HB_BLD_C4_TIMER);
GG_STATIC_ASSERT(offsetof(BuildingBView, BState) == HB_BLD_BSTATE);
GG_STATIC_ASSERT(offsetof(BuildingBView, OwnerCountryIndex) == HB_BLD_OWNER_COUNTRY_INDEX);
GG_STATIC_ASSERT(offsetof(BuildingBView, C4AppliedBy) == HB_BLD_C4_APPLIED_BY);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_544) == HB_BLD_UNKNOWN_544);
GG_STATIC_ASSERT(offsetof(BuildingBView, FirestormAnim) == HB_BLD_FIRESTORM_ANIM);
GG_STATIC_ASSERT(offsetof(BuildingBView, PsiWarnAnim) == HB_BLD_PSI_WARN_ANIM);
GG_STATIC_ASSERT(offsetof(BuildingBView, Anims) == HB_BLD_ANIMS);
GG_STATIC_ASSERT(offsetof(BuildingBView, DamageFireAnims) == HB_BLD_DAMAGE_FIRE_ANIMS);
GG_STATIC_ASSERT(offsetof(BuildingBView, Upgrades) == HB_BLD_UPGRADES);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_5FC) == HB_BLD_UNKNOWN_5FC);
GG_STATIC_ASSERT(offsetof(BuildingBView, Spotlight) == HB_BLD_SPOTLIGHT);
GG_STATIC_ASSERT(offsetof(BuildingBView, LightSource) == HB_BLD_LIGHT_SOURCE);
GG_STATIC_ASSERT(offsetof(BuildingBView, LaserFenceFrame) == HB_BLD_LASER_FENCE_FRAME);
GG_STATIC_ASSERT(offsetof(BuildingBView, HasPower) == HB_BLD_HAS_POWER);
GG_STATIC_ASSERT(offsetof(BuildingBView, Overpowerers) == HB_BLD_OVERPOWERERS);
GG_STATIC_ASSERT(offsetof(BuildingBView, Occupants) == HB_BLD_OCCUPANTS);
GG_STATIC_ASSERT(offsetof(BuildingBView, Audio7) == HB_BLD_AUDIO7);
GG_STATIC_ASSERT(offsetof(BuildingBView, ShouldRebuild) == HB_BLD_SHOULD_REBUILD);
GG_STATIC_ASSERT(offsetof(BuildingBView, HasEngineer) == HB_BLD_HAS_ENGINEER);
GG_STATIC_ASSERT(offsetof(BuildingBView, CashProductionTimer) == HB_BLD_CASH_PRODUCTION_TIMER);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_6DC) == HB_BLD_UNKNOWN_6DC);
GG_STATIC_ASSERT(offsetof(BuildingBView, IsReadyToCommence) == HB_BLD_IS_READY_TO_COMMENCE);
GG_STATIC_ASSERT(offsetof(BuildingBView, NeedsRepairs) == HB_BLD_NEEDS_REPAIRS);
GG_STATIC_ASSERT(offsetof(BuildingBView, C4Applied) == HB_BLD_C4_APPLIED);
GG_STATIC_ASSERT(offsetof(BuildingBView, NoCrew) == HB_BLD_NO_CREW);
GG_STATIC_ASSERT(offsetof(BuildingBView, HasBeenCaptured) == HB_BLD_HAS_BEEN_CAPTURED);
GG_STATIC_ASSERT(offsetof(BuildingBView, ActuallyPlacedOnMap) == HB_BLD_ACTUALLY_PLACED_ON_MAP);
GG_STATIC_ASSERT(offsetof(BuildingBView, IsDamaged) == HB_BLD_IS_DAMAGED);
GG_STATIC_ASSERT(offsetof(BuildingBView, IsBeingRepaired) == HB_BLD_IS_BEING_REPAIRED);
GG_STATIC_ASSERT(offsetof(BuildingBView, StuffEnabled) == HB_BLD_STUFF_ENABLED);
GG_STATIC_ASSERT(offsetof(BuildingBView, HasCloakingData) == HB_BLD_HAS_CLOAKING_DATA);
GG_STATIC_ASSERT(offsetof(BuildingBView, CloakRadius) == HB_BLD_CLOAK_RADIUS);
GG_STATIC_ASSERT(offsetof(BuildingBView, Translucency) == HB_BLD_TRANSLUCENCY);
GG_STATIC_ASSERT(offsetof(BuildingBView, unknown_short_700) == HB_BLD_UNKNOWN_700);
GG_STATIC_ASSERT(offsetof(BuildingBView, UpgradeLevel) == HB_BLD_UPGRADE_LEVEL);
// END canonical-layout asserts

#endif

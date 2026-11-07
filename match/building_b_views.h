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

#include "_layout/cell_class.h"
#include "_layout/session_class.h"
#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "house_building_layout.h"
#include "building_b_shared.h"
#include "_layout/house_class.h"
#include "_layout/color_struct.h"
#include "_layout/techno_type_class.h"
#include "_layout/player_ptr_00a83d4c.h"
#include "_layout/building_class.h"
#include "_layout/infantry_class.h"
#include "_layout/anim_class.h"

class BuildingBView;
class BuildingTypeClass;
class HouseClass;
class BuildingBSurfaceView;
class BuildingBTargetObjView;
class ParticleSystemTypeClass;
class BuildingBParticleSystemView;
class BuildingBView;
class BuildingBTargetView;
class BuildingBTacticalView;


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


// Partial view of the object at BuildingClass+0x294 (read-only here).
class BuildingBTargetObjView
{
public:
    char unknown_00[0x50];   // +0x0
    void* unknown_50;   // +0x50
};
GG_STATIC_ASSERT(offsetof(BuildingBTargetObjView, unknown_50) == 0x50);

// ParticleSystemTypeClass (opaque here).
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
    BuildingBParticleSystemView(ParticleSystemTypeClass* type, CoordStruct* where, CellClass* cell, BuildingClass* owner, const CoordStruct* b, int c);
    void Func_6301F0(int a);
    char unknown_04[0xFC];   // +0x4
};
GG_STATIC_ASSERT(sizeof(BuildingBParticleSystemView) == 0x100);

// Partial view of the target object handed to vf_26 (read-only here).
class BuildingBTargetView
{
public:
    char unknown_00[0x30];   // +0x0
    int unknown_30;   // +0x30
};
GG_STATIC_ASSERT(offsetof(BuildingBTargetView, unknown_30) == 0x30);

// Partial view of the tactical object behind global 0x887324 (read-only here).
class BuildingBTacticalView
{
public:
    Point2D* Func_6D2070(Point2D* out, const Point2D* in);
    void Func_6D2140(const CoordStruct* in, Point2D* out);
    char unknown_00[0xB0];   // +0x0
    Point2D Offset;   // +0xB0
};
GG_STATIC_ASSERT(offsetof(BuildingBTacticalView, Offset) == 0xB0);

// Remaining partial view of BuildingClass for 0x456750 (slot 76) only. Retail's override writes the tint it builds
// into its own argument slot (the incoming argument is a ColorStruct there, tint.R is forwarded in the plain
// branch) while the retail callers (0x6DBE20) push the integer 1 for the same slot, so the override cannot sit
// on the canonical class whose ObjectClass slot 76 takes an int: that scored 87.0 against 100.0 here.
class BuildingBView
{
public:
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
    virtual CoordStruct* vf_18(CoordStruct* out);   // slot 18 (+0x48)
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
    virtual void vf_76(ColorStruct tint);   // slot 76 (+0x130)
    int Func_4566B0();
    char unknown_04[0x217];   // +0x4
    HouseClass* Owner;   // +0x21C
    char unknown_220[0x300];   // +0x220
    BuildingTypeClass* Type;   // +0x520
    char unknown_524[0x13C];   // +0x524
    bool HasPower;   // +0x660
    char unknown_661[0xBF];   // +0x661
};
GG_STATIC_ASSERT(offsetof(BuildingBView, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(BuildingBView, Type) == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingBView, HasPower) == 0x660);
GG_STATIC_ASSERT(sizeof(BuildingBView) == 0x720);


// FUNCTION: GAMEMD 0x456980 (read-only here; __fastcall, flags in cl/dl)
void BuildingBFunc_456980(char a, char b, CoordStruct at, ColorStruct color, float intensity, char c, char d);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
// FUNCTION: GAMEMD 0x4CAC40 (read-only here; cdecl, double argument)
double __cdecl BuildingBFunc_4CAC40(double value);
// LIBRARY: GAMEMD 0x7C5F00 is the compiler's float-to-long helper.
inline RectangleStruct operator+(const RectangleStruct& r, const Point2D& p)
{
    RectangleStruct result;
    result.X = r.X + p.X;
    result.Y = r.Y + p.Y;
    result.Width = r.Width;
    result.Height = r.Height;
    return result;
}


// GLOBAL: GAMEMD 0xA83DEC (pointer to the item table) / 0xA83DF8 (count) of a global techno array
// GLOBAL: GAMEMD 0x89C870
extern CoordStruct BuildingBGlobal_0089C870;
// GLOBAL: GAMEMD 0x89DDC0 (pointer to the surface)
extern BuildingBSurfaceView* BuildingBSurface;
// GLOBAL: GAMEMD 0xA8EB40 (the global building array; item table +4, count +0x10)
extern DynamicVectorClass<BuildingClass*> DAT_00A8EB40;
// GLOBAL: GAMEMD 0x89C818 (the empty cell value)
extern CellStruct BuildingBEmptyCell;
// GLOBAL: GAMEMD 0x89C848 (retail data, bound by address)
extern CoordStruct BuildingBEmptyCoord;
// GLOBAL: GAMEMD 0xB73550
extern int BuildingBGlobal_00B73550;
// GLOBAL: GAMEMD 0x887324 (pointer to the tactical object)
extern BuildingBTacticalView* BuildingBTactical;





#endif

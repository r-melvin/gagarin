// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI
//   .?AVBuildingTypeClass@@ (TD 0x8193A8): COLs 0x7FC618 / 0x7FC5A0 / 0x7FC588 / 0x7FC570 for the
//   tables 0x7E4570 (49 slots) / 0x7E4554 (6) / 0x7E454C (1) / 0x7E4544 (1); chain BuildingTypeClass ->
//   TechnoTypeClass -> ObjectTypeClass -> AbstractTypeClass -> AbstractClass -> IPersistStream ->
//   IPersist -> IUnknown, IRTTITypeInfo -> IUnknown, INoticeSink, INoticeSource. The constructor
//   0x45DD90 (every member store below), the INI reader 0x45FE50 (every key string and member offset),
//   the CRC slot 0x464B30, Load 0x465010, Save 0x465300, the scalar deleting destructor 0x465DC0 and
//   the allocation sites 0x465416, 0x466053 and 0x6C29BC (`PUSH 0x1798; CALL 0x7C8E17`, all agreeing).
//
// BuildingTypeClass: the rules-INI template of a building ([BuildingTypes] sections). Declared here
// as BuildingTypeView_0045DD90, because its base is the ABI view TypesBuildingTypeTechnoView rather than
// TechnoTypeClass; the canonical class is in _layout/building_type_class_layout.h.
//   +0x00..+0xDF7   TypesBuildingTypeTechnoView (AbstractClass .. TechnoTypeClass; READ-ONLY, only the
//                   members this module touches are named)
//   +0xDF8..+0x1797 the members below (names are the INI keys the reader proves).  sizeof 0x1798
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_TYPE_CLASS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_TYPE_CLASS_H

#include "types_shared.h"

class BuildingTypeView_0045DD90;
class HouseClass;

// Not HBPoint2D: the constructors change how the 8-byte value is returned (see house_building_views.h).
struct TypesPoint2D
{
    int X;   // +0x00
    int Y;   // +0x04

    TypesPoint2D() {}
    TypesPoint2D(int x, int y) : X(x), Y(y) {}
};
GG_STATIC_ASSERT(sizeof(TypesPoint2D) == 8);

// Builds a point through a named local returned by value.
inline TypesPoint2D TypesMakePoint(int x, int y)
{
    TypesPoint2D point(x, y);
    return point;
}

// A coordinate with a zeroing constructor, the element of the docking offset vector.
struct TypesDockCoord
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08

    bool operator==(const TypesDockCoord& other) const { return X == other.X && Y == other.Y && Z == other.Z; }
    bool operator!=(const TypesDockCoord& other) const { return !(*this == other); }
};
GG_STATIC_ASSERT(sizeof(TypesDockCoord) == 0xC);

// The 16-byte object the constructor copies out of the global at 0x89C8A0 into +0x1538.
struct TypesQuad
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;
};
GG_STATIC_ASSERT(sizeof(TypesQuad) == 0x10);

// One frame descriptor of the six building animation frames (+0xF04). Defaults {0, 1, 0}.
struct BuildingTypeAnimFrame
{
    int Start;   // +0x00
    int Count;   // +0x04
    int Rate;    // +0x08
};
GG_STATIC_ASSERT(sizeof(BuildingTypeAnimFrame) == 0xC);

// One of the 21 animation slots (+0xF4C): three art names, a pixel offset and the power flags.
struct BuildingTypeAnim
{
    char Anim[0x10];         // +0x00
    char Damaged[0x10];      // +0x10
    char Garrisoned[0x10];   // +0x20
    int  X;                  // +0x30
    int  Y;                  // +0x34
    int  ZAdjust;            // +0x38
    int  YSort;              // +0x3C
    bool Powered;            // +0x40
    bool PoweredLight;       // +0x41
    bool PoweredEffect;      // +0x42
    bool PoweredSpecial;     // +0x43

};
GG_STATIC_ASSERT(sizeof(BuildingTypeAnim) == 0x44);

// ABI view of TechnoTypeClass (sizeof 0xDF8), the base of BuildingTypeClass. Slot numbers are the
// retail primary-table indices (table 0x7E4570, 49 slots; slots 0..26 are the AbstractTypeClass part,
// 27..39 the ObjectTypeClass part, 40..47 the TechnoTypeClass part, 48 the extra one
// BuildingTypeClass adds). The IPersistStream slots 0-7 are __stdcall with `this` on the stack; every
// other slot is __thiscall. Inherited slots are READ-ONLY here.
// VTABLE: GAMEMD 0x7E4570 (IPersistStream side), GAMEMD 0x7E4554 (IRTTITypeInfo side), GAMEMD 0x7E454C
//         (INoticeSink side), GAMEMD 0x7E4544 (INoticeSource side)
class TypesBuildingTypeTechnoView : public IPersistStream, public HBRttiBase,
                                    public HBNoticeSinkBase, public HBNoticeSourceBase
{
public:
    // FUNCTION: GAMEMD 0x710AF0 (TechnoTypeClass named constructor; read-only here)
    TypesBuildingTypeTechnoView(const char* id, int arg);
    // FUNCTION: GAMEMD 0x711840 (TechnoTypeClass no-init constructor; read-only here)
    TypesBuildingTypeTechnoView(const HBNoInit& noInit);

    // FUNCTION: GAMEMD 0x5F9070 (ObjectTypeClass work after a load; read-only here)
    void PostLoad();

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);       // 0   0x410260
    virtual ULONG __stdcall AddRef();                                        // 1   0x410300
    virtual ULONG __stdcall Release();                                       // 2   0x410310
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                   // 3   overridden (0x465380)
    virtual HRESULT __stdcall IsDirty();                                     // 4   0x410450
    virtual HRESULT __stdcall Load(IStream* pStm);                           // 5   base 0x7162F0; overridden (0x465010)
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);         // 6   base 0x716DC0; overridden (0x465300)
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);           // 7   0x7170A0
    virtual ~TypesBuildingTypeTechnoView();                                  // 8   base 0x45E580's callee chain; overridden (0x465DC0)
    virtual void vf_9();                                                     // 9   0x410470
    virtual void vf_10();                                                    // 10  0x410480
    virtual int WhatAmI();                                                   // 11  overridden (0x465D90)
    virtual int Size();                                                      // 12  overridden (0x465DA0)
    virtual void ComputeCRC(TypesCrcView& crc);                              // 13  base 0x7171A0; overridden (0x464B30)
    virtual void vf_14();                                                    // 14  0x410490
    virtual void vf_15();                                                    // 15  0x4104A0
    virtual int vf_16();                                                     // 16  overridden (0x465DB0)
    virtual void vf_17();                                                    // 17  0x410440
    virtual void vf_18();                                                    // 18  0x4104C0
    virtual void vf_19();                                                    // 19  0x4104F0
    virtual void vf_20();                                                    // 20  0x410520
    virtual void vf_21();                                                    // 21  0x410530
    virtual void vf_22();                                                    // 22  0x410540
    virtual void vf_23();                                                    // 23  0x410570
    virtual void vf_24();                                                    // 24  0x410C20
    virtual bool ReadINI(TypesIniView* ini);                                 // 25  base 0x712170; overridden (0x45FE50)
    virtual void vf_26();                                                    // 26  0x410B90
    virtual HBCoord vf_27(const HBCoord* in);                          // 27  overridden (0x464A70)
    virtual void vf_28();                                                    // 28  0x711EC0
    virtual int vf_29();                                                     // 29  base 0x716290; overridden (0x45ECE0)
    virtual HBCoord vf_30();                                              // 30  overridden (0x45EBD0)
    virtual HBCoord vf_31();                                              // 31  overridden (0x464AF0)
    virtual bool vf_32(void* where, void* owner);                            // 32  overridden (0x45E800)
    virtual int vf_33(HouseClass* owner);                                    // 33  overridden (0x45EDD0)
    virtual void vf_34();                                                    // 34  0x711EE0
    virtual void* vf_35(void* owner);                                        // 35  overridden (0x45E880)
    virtual void* vf_36(bool arg);                                           // 36  overridden (0x45EC20)
    virtual void vf_37();                                                    // 37  0x5F7900
    virtual void vf_38();                                                    // 38  0x712040
    virtual void* vf_39();                                                   // 39  overridden (0x45F040)
    virtual bool vf_40();                                                    // 40  overridden (0x465910)
    virtual bool vf_41();                                                    // 41  overridden (0x465920)
    virtual bool vf_42(void* arg1, void* arg2);                              // 42  base 0x716150; overridden (0x464AC0)
    virtual void vf_43();                                                    // 43  0x45ED50
    virtual void vf_44();                                                    // 44  0x7120D0
    virtual void vf_45();                                                    // 45  0x712120
    virtual void vf_46();                                                    // 46  0x711F60
    virtual void vf_47();                                                    // 47  0x717800
    virtual void* vf_48();                                                   // 48  overridden (0x465960)

    char unknown_10[0x14];                      // +0x10
    char ID[0x18];                              // +0x24  AbstractTypeClass::ID, the INI section name
    unsigned char unknown_3C[0x68];               // +0x3C
    void* Image;                                // +0xA4  the loaded shape
    bool ImageAllocated;                        // +0xA8
    unsigned char unknown_A9[0x14F];              // +0xA9
    char ImageFile[0x34];                       // +0x1F8  the art file name (without extension)
    unsigned char unknown_22C[0x1A8];             // +0x22C
    int unknown_3D4;                            // +0x3D4
    unsigned char unknown_3D8[0x2A4];             // +0x3D8
    int unknown_67C;                            // +0x67C  LandTypes-style enum written by ReadINI (WaterBound)
    unsigned char unknown_680[0x98];              // +0x680
    int unknown_718;                            // +0x718
    unsigned char unknown_71C[0xE4];              // +0x71C
    int unknown_800;                            // +0x800
    unsigned char unknown_804[0x48A];             // +0x804
    bool unknown_C8E;                           // +0xC8E
    unsigned char unknown_C8F[0xB];               // +0xC8F
    bool unknown_C9A;                           // +0xC9A
    bool unknown_C9B;                           // +0xC9B
    unsigned char unknown_C9C[0x5];               // +0xC9C
    bool unknown_CA1;                           // +0xCA1
    unsigned char unknown_CA2[0x8C];              // +0xCA2
    bool unknown_D2E;                           // +0xD2E
    unsigned char unknown_D2F[0x6];               // +0xD2F
    bool unknown_D35;                           // +0xD35
    bool unknown_D36;                           // +0xD36
    unsigned char unknown_D37[0x1];               // +0xD37
    bool unknown_D38;                           // +0xD38
    unsigned char unknown_D39[0x2];               // +0xD39
    bool unknown_D3B;                           // +0xD3B
    unsigned char unknown_D3C[0x5A];              // +0xD3C
    bool unknown_D96;                           // +0xD96
    bool unknown_D97;                           // +0xD97
    unsigned char unknown_D98[0x60];              // +0xD98
};
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, Image) == 0xA4);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, ImageAllocated) == 0xA8);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, ImageFile) == 0x1F8);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_3D4) == 0x3D4);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_67C) == 0x67C);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_718) == 0x718);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_800) == 0x800);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_C8E) == 0xC8E);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_C9A) == 0xC9A);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_C9B) == 0xC9B);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_CA1) == 0xCA1);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_D2E) == 0xD2E);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_D35) == 0xD35);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_D36) == 0xD36);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_D38) == 0xD38);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_D3B) == 0xD3B);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_D96) == 0xD96);
GG_STATIC_ASSERT(offsetof(TypesBuildingTypeTechnoView, unknown_D97) == 0xD97);
GG_STATIC_ASSERT(sizeof(TypesBuildingTypeTechnoView) == 0xDF8);
// GLOBAL: GAMEMD 0xA83C68 - BuildingTypeClass::Array, every building type (DynamicVectorClass; read-only here).
extern DynamicVectorClass<BuildingTypeView_0045DD90*> TypesBuildingTypeArray;

// The building object (read-only view): only the constructor and the Unlimbo slot are used here.
class TypesBuildingView
{
public:
    // FUNCTION: GAMEMD 0x43B740 (BuildingClass named constructor; not part of this cluster - bound)
    TypesBuildingView(BuildingTypeView_0045DD90* type, void* owner);
    virtual ~TypesBuildingView();
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
    // Slot 54 (+0xD8): Unlimbo(coordinate, facing).
    virtual bool Unlimbo(HBCoord* coord, int facing);

    unsigned char unknown_04[0x720 - 4];   // +0x04..+0x71F (sizeof from the allocation: 0x720)
};
GG_STATIC_ASSERT(sizeof(TypesBuildingView) == 0x720);

// VTABLE: GAMEMD 0x7E4570 (IPersistStream side) and GAMEMD 0x7E4554 / 0x7E454C / 0x7E4544
class BuildingTypeView_0045DD90 : public TypesBuildingTypeTechnoView
{
public:
    // FUNCTION: GAMEMD 0x45DD90 - the named constructor.
    BuildingTypeView_0045DD90(const char* id);
    // FUNCTION: GAMEMD 0x45E520 (no-init constructor; not part of this cluster - bound)
    BuildingTypeView_0045DD90(const HBNoInit& noInit);
    // FUNCTION: GAMEMD 0x45FA90 (post-load work; not part of this cluster - bound)
    void LoadFixup();
    // FUNCTION: GAMEMD 0x45F230 (stamps the theater into the art names; not part of this cluster - bound)
    void StampTheater(int theaterIndex);

    // ---- overrides (IPersistStream side) -----------------------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                   // 3   0x465380
    virtual HRESULT __stdcall Load(IStream* pStm);                           // 5   0x465010
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);         // 6   0x465300
    // Slot 8: the scalar deleting destructor 0x465DC0 is compiler output; the destructor body 0x45E580
    // is out of line (not part of this cluster).
    // FUNCTION: GAMEMD 0x465DC0 (scalar deleting destructor; ??_G)
    virtual ~BuildingTypeView_0045DD90();
    virtual int WhatAmI();                                                   // 11  0x465D90
    virtual int Size();                                                      // 12  0x465DA0
    virtual void ComputeCRC(TypesCrcView& crc);                              // 13  0x464B30
    virtual int vf_16();                                                     // 16  0x465DB0
    virtual bool ReadINI(TypesIniView* ini);                                 // 25  0x45FE50
    virtual HBCoord vf_27(const HBCoord* in);                          // 27  0x464A70
    virtual int vf_29();                                                     // 29  0x45ECE0
    virtual HBCoord vf_30();                                              // 30  0x45EBD0
    virtual HBCoord vf_31();                                              // 31  0x464AF0
    virtual bool vf_32(void* where, void* owner);                            // 32  0x45E800
    virtual int vf_33(HouseClass* owner);                                    // 33  0x45EDD0
    virtual void* vf_35(void* owner);                                        // 35  0x45E880
    virtual void* vf_36(bool arg);                                           // 36  0x45EC20
    virtual void* vf_39();                                                   // 39  0x45F040
    virtual bool vf_40();                                                    // 40  0x465910
    virtual bool vf_41();                                                    // 41  0x465920
    virtual bool vf_42(void* arg1, void* arg2);                              // 42  0x464AC0
    virtual void* vf_48();                                                   // 48  0x465960

    // ---- members (complete-object offsets) ---------------------------------------------------
    int ArrayIndex;                             // +0xDF8
    void* FoundationData;                       // +0xDFC  cell list of the foundation
    void* Buildup;                              // +0xE00  the loaded buildup shape
    bool BuildupLoaded;                         // +0xE04
    unsigned char unknown_E05[0x3];               // +0xE05
    int BuildCat;                               // +0xE08
    HBCoord HalfDamageSmokeLocation1;        // +0xE0C
    HBCoord HalfDamageSmokeLocation2;        // +0xE18
    unsigned char unknown_E24[0x4];               // +0xE24
    double GateCloseDelay;                      // +0xE28
    int LightVisibility;                        // +0xE30
    int LightIntensity;                         // +0xE34
    int LightRedTint;                           // +0xE38
    int LightGreenTint;                         // +0xE3C
    int LightBlueTint;                          // +0xE40
    TypesPoint2D PrimaryFirePixelOffset;        // +0xE44
    TypesPoint2D SecondaryFirePixelOffset;      // +0xE4C
    void* ToOverlay;                            // +0xE54
    void* ToTile;                               // +0xE58
    char BuildupFile[0x10];                     // +0xE5C
    int BuildupSound;                           // +0xE6C
    int PackupSound;                            // +0xE70
    int CreateUnitSound;                        // +0xE74
    int UnitEnterSound;                         // +0xE78
    int UnitExitSound;                          // +0xE7C
    int WorkingSound;                           // +0xE80
    int NotWorkingSound;                        // +0xE84
    char PowersUpBuilding[0x18];                // +0xE88
    void* FreeUnit;                             // +0xEA0
    void* SecretInfantry;                       // +0xEA4
    void* SecretUnit;                           // +0xEA8
    void* SecretBuilding;                       // +0xEAC
    int unknown_EB0;                            // +0xEB0
    int Adjacent;                               // +0xEB4
    int Factory;                                // +0xEB8
    HBCoord TargetCoordOffset;               // +0xEBC
    HBCoord ExitCoord;                       // +0xEC8
    void* FoundationOutside;                    // +0xED4
    int unknown_ED8;                            // +0xED8
    int DeployFacing;                           // +0xEDC
    int PowerBonus;                             // +0xEE0
    int PowerDrain;                             // +0xEE4
    int ExtraPowerBonus;                        // +0xEE8
    int ExtraPowerDrain;                        // +0xEEC
    int Foundation;                             // +0xEF0
    int Height;                                 // +0xEF4
    int OccupyHeight;                           // +0xEF8
    int MidPoint;                               // +0xEFC
    int DoorStages;                             // +0xF00
    BuildingTypeAnimFrame BuildingAnimFrame[0x6];// +0xF04
    BuildingTypeAnim BuildingAnim[0x15];        // +0xF4C
    int Upgrades;                               // +0x14E0
    void* DeployingAnim;                        // +0x14E4
    bool DeployingAnimLoaded;                   // +0x14E8
    unsigned char unknown_14E9[0x3];              // +0x14E9
    void* UnderDoorAnim;                        // +0x14EC
    bool UnderDoorAnimLoaded;                   // +0x14F0
    unsigned char unknown_14F1[0x3];              // +0x14F1
    void* Rubble;                               // +0x14F4
    bool RubbleLoaded;                          // +0x14F8
    unsigned char unknown_14F9[0x3];              // +0x14F9
    void* RoofDeployingAnim;                    // +0x14FC
    bool RoofDeployingAnimLoaded;               // +0x1500
    unsigned char unknown_1501[0x3];              // +0x1501
    void* UnderRoofDoorAnim;                    // +0x1504
    bool UnderRoofDoorAnimLoaded;               // +0x1508
    unsigned char unknown_1509[0x3];              // +0x1509
    void* DoorAnim;                             // +0x150C
    void* SpecialZOverlay;                      // +0x1510
    int SpecialZOverlayZAdjust;                 // +0x1514
    void* BibShape;                             // +0x1518
    bool BibShapeLoaded;                        // +0x151C
    unsigned char unknown_151D[0x3];              // +0x151D
    int NormalZAdjust;                          // +0x1520
    int AntiAirValue;                           // +0x1524
    int AntiArmorValue;                         // +0x1528
    int AntiInfantryValue;                      // +0x152C
    TypesPoint2D ZShapePointMove;               // +0x1530
    TypesQuad unknown_1538;                     // +0x1538
    unsigned short ExtraLight;                  // +0x1548
    bool TogglePower;                           // +0x154A
    bool HasSpotlight;                          // +0x154B
    bool IsTemple;                              // +0x154C
    bool IsPlug;                                // +0x154D
    bool HoverPad;                              // +0x154E
    bool BaseNormal;                            // +0x154F
    bool EligibileForAllyBuilding;              // +0x1550
    bool EligibleForDelayKill;                  // +0x1551
    bool NeedsEngineer;                         // +0x1552
    unsigned char unknown_1553[0x1];              // +0x1553
    int CaptureEvaEvent;                        // +0x1554
    int ProduceCashStartup;                     // +0x1558
    int ProduceCashAmount;                      // +0x155C
    int ProduceCashDelay;                       // +0x1560
    int InfantryGainSelfHeal;                   // +0x1564
    int UnitsGainSelfHeal;                      // +0x1568
    int RefinerySmokeFrames;                    // +0x156C
    bool Bib;                                   // +0x1570
    bool Wall;                                  // +0x1571
    bool Capturable;                            // +0x1572
    bool Powered;                               // +0x1573
    bool PoweredSpecial;                        // +0x1574
    bool Overpowerable;                         // +0x1575
    bool Spyable;                               // +0x1576
    bool CanC4;                                 // +0x1577
    bool WantsExtraSpace;                       // +0x1578
    bool Unsellable;                            // +0x1579
    bool ClickRepairable;                       // +0x157A
    bool CanBeOccupied;                         // +0x157B
    bool CanOccupyFire;                         // +0x157C
    unsigned char unknown_157D[0x3];              // +0x157D
    int MaxNumberOccupants;                     // +0x1580
    bool ShowOccupantPips;                      // +0x1584
    unsigned char unknown_1585[0x3];              // +0x1585
    TypesPoint2D MuzzleFlash[0xA];              // +0x1588
    TypesPoint2D DamageFireOffset[0x8];         // +0x15D8
    TypesPoint2D QueueingCell;                  // +0x1618
    int NumberImpassableRows;                   // +0x1620
    TypesPoint2D RemoveOccupy[0x8];             // +0x1624
    TypesPoint2D AddOccupy[0x8];                // +0x1664
    bool Radar;                                 // +0x16A4
    bool SpySat;                                // +0x16A5
    bool ChargeAnim;                            // +0x16A6
    bool IsAnimDelayedFire;                     // +0x16A7
    bool SiloDamage;                            // +0x16A8
    bool UnitRepair;                            // +0x16A9
    bool UnitReload;                            // +0x16AA
    bool Bunker;                                // +0x16AB
    bool Cloning;                               // +0x16AC
    bool Grinding;                              // +0x16AD
    bool UnitAbsorb;                            // +0x16AE
    bool InfantryAbsorb;                        // +0x16AF
    bool SecretLab;                             // +0x16B0
    bool DoubleThick;                           // +0x16B1
    bool Flat;                                  // +0x16B2
    bool DockUnload;                            // +0x16B3
    bool Recoilless;                            // +0x16B4
    bool HasStupidGuardMode;                    // +0x16B5
    bool BridgeRepairHut;                       // +0x16B6
    bool Gate;                                  // +0x16B7
    bool SAM;                                   // +0x16B8
    bool ConstructionYard;                      // +0x16B9
    bool NukeSilo;                              // +0x16BA
    bool Refinery;                              // +0x16BB
    bool Weeder;                                // +0x16BC
    bool WeaponsFactory;                        // +0x16BD
    bool LaserFencePost;                        // +0x16BE
    bool LaserFence;                            // +0x16BF
    bool FirestormWall;                         // +0x16C0
    bool Hospital;                              // +0x16C1
    bool Armory;                                // +0x16C2
    bool EMPulseCannon;                         // +0x16C3
    bool TickTank;                              // +0x16C4
    bool TurretAnimIsVoxel;                     // +0x16C5
    bool BarrelAnimIsVoxel;                     // +0x16C6
    bool CloakGenerator;                        // +0x16C7
    bool SensorArray;                           // +0x16C8
    bool ICBMLauncher;                          // +0x16C9
    bool Artillary;                             // +0x16CA
    bool Helipad;                               // +0x16CB
    bool OrePurifier;                           // +0x16CC
    bool FactoryPlant;                          // +0x16CD
    unsigned char unknown_16CE[0x2];              // +0x16CE
    float InfantryCostBonus;                    // +0x16D0
    float UnitsCostBonus;                       // +0x16D4
    float AircraftCostBonus;                    // +0x16D8
    float BuildingsCostBonus;                   // +0x16DC
    float DefensesCostBonus;                    // +0x16E0
    bool GDIBarracks;                           // +0x16E4
    bool NODBarracks;                           // +0x16E5
    bool YuriBarracks;                          // +0x16E6
    unsigned char unknown_16E7[0x1];              // +0x16E7
    float ChargedAnimTime;                      // +0x16E8
    int DelayedFireDelay;                       // +0x16EC
    int SuperWeapon;                            // +0x16F0
    int SuperWeapon2;                           // +0x16F4
    int GateStages;                             // +0x16F8
    int PowersUpToLevel;                        // +0x16FC
    bool DamagedDoor;                           // +0x1700
    bool InvisibleInGame;                       // +0x1701
    bool TerrainPalette;                        // +0x1702
    bool PlaceAnywhere;                         // +0x1703
    bool ExtraDamageStage;                      // +0x1704
    bool AIBuildThis;                           // +0x1705
    bool IsBaseDefense;                         // +0x1706
    unsigned char CloakRadiusInCells;           // +0x1707
    bool ConcentricRadialIndicator;             // +0x1708
    unsigned char unknown_1709[0x3];              // +0x1709
    int PsychicDetectionRadius;                 // +0x170C
    int BarrelStartPitch;                       // +0x1710
    char VoxelBarrelFile[0x10];                 // +0x1714
    unsigned char unknown_1724[0x4];              // +0x1724
    double unknown_1728;                        // +0x1728
    HBCoord VoxelBarrelOffsetToPitchPivotPoint;// +0x1730
    HBCoord VoxelBarrelOffsetToRotatePivotPoint;// +0x173C
    HBCoord VoxelBarrelOffsetToBuildingPivotPoint;// +0x1748
    HBCoord VoxelBarrelOffsetToBarrelEnd;    // +0x1754
    bool DemandLoad;                            // +0x1760
    bool DemandLoadBuildup;                     // +0x1761
    bool FreeBuildup;                           // +0x1762
    bool IsThreatRatingNode;                    // +0x1763
    bool PrimaryFireDualOffset;                 // +0x1764
    bool ProtectWithWall;                       // +0x1765
    bool CanHideThings;                         // +0x1766
    bool CrateBeneath;                          // +0x1767
    bool LeaveRubble;                           // +0x1768
    bool CrateBeneathIsMoney;                   // +0x1769
    char TheaterSpecificID[0x13];               // +0x176A
    unsigned char unknown_177D[0x3];              // +0x177D
    int NumberOfDocks;                          // +0x1780
    VectorClass<TypesDockCoord> DockingOffsets; // +0x1784
    unsigned char unknown_1794[0x4];              // +0x1794
};

GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ArrayIndex) == 0xDF8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, FoundationData) == 0xDFC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Buildup) == 0xE00);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BuildupLoaded) == 0xE04);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BuildCat) == 0xE08);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, HalfDamageSmokeLocation1) == 0xE0C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, HalfDamageSmokeLocation2) == 0xE18);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, GateCloseDelay) == 0xE28);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, LightVisibility) == 0xE30);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, LightIntensity) == 0xE34);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, LightRedTint) == 0xE38);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, LightGreenTint) == 0xE3C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, LightBlueTint) == 0xE40);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, PrimaryFirePixelOffset) == 0xE44);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SecondaryFirePixelOffset) == 0xE4C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ToOverlay) == 0xE54);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ToTile) == 0xE58);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BuildupFile) == 0xE5C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BuildupSound) == 0xE6C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, PackupSound) == 0xE70);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, CreateUnitSound) == 0xE74);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnitEnterSound) == 0xE78);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnitExitSound) == 0xE7C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, WorkingSound) == 0xE80);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, NotWorkingSound) == 0xE84);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, PowersUpBuilding) == 0xE88);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, FreeUnit) == 0xEA0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SecretInfantry) == 0xEA4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SecretUnit) == 0xEA8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SecretBuilding) == 0xEAC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, unknown_EB0) == 0xEB0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Adjacent) == 0xEB4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Factory) == 0xEB8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, TargetCoordOffset) == 0xEBC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ExitCoord) == 0xEC8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, FoundationOutside) == 0xED4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, unknown_ED8) == 0xED8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DeployFacing) == 0xEDC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, PowerBonus) == 0xEE0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, PowerDrain) == 0xEE4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ExtraPowerBonus) == 0xEE8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ExtraPowerDrain) == 0xEEC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Foundation) == 0xEF0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Height) == 0xEF4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, OccupyHeight) == 0xEF8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, MidPoint) == 0xEFC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DoorStages) == 0xF00);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BuildingAnimFrame) == 0xF04);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BuildingAnim) == 0xF4C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Upgrades) == 0x14E0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DeployingAnim) == 0x14E4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DeployingAnimLoaded) == 0x14E8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnderDoorAnim) == 0x14EC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnderDoorAnimLoaded) == 0x14F0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Rubble) == 0x14F4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, RubbleLoaded) == 0x14F8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, RoofDeployingAnim) == 0x14FC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, RoofDeployingAnimLoaded) == 0x1500);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnderRoofDoorAnim) == 0x1504);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnderRoofDoorAnimLoaded) == 0x1508);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DoorAnim) == 0x150C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SpecialZOverlay) == 0x1510);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SpecialZOverlayZAdjust) == 0x1514);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BibShape) == 0x1518);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BibShapeLoaded) == 0x151C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, NormalZAdjust) == 0x1520);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, AntiAirValue) == 0x1524);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, AntiArmorValue) == 0x1528);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, AntiInfantryValue) == 0x152C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ZShapePointMove) == 0x1530);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, unknown_1538) == 0x1538);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ExtraLight) == 0x1548);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, TogglePower) == 0x154A);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, HasSpotlight) == 0x154B);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, IsTemple) == 0x154C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, IsPlug) == 0x154D);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, HoverPad) == 0x154E);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BaseNormal) == 0x154F);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, EligibileForAllyBuilding) == 0x1550);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, EligibleForDelayKill) == 0x1551);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, NeedsEngineer) == 0x1552);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, CaptureEvaEvent) == 0x1554);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ProduceCashStartup) == 0x1558);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ProduceCashAmount) == 0x155C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ProduceCashDelay) == 0x1560);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, InfantryGainSelfHeal) == 0x1564);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnitsGainSelfHeal) == 0x1568);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, RefinerySmokeFrames) == 0x156C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Bib) == 0x1570);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Wall) == 0x1571);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Capturable) == 0x1572);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Powered) == 0x1573);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, PoweredSpecial) == 0x1574);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Overpowerable) == 0x1575);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Spyable) == 0x1576);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, CanC4) == 0x1577);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, WantsExtraSpace) == 0x1578);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Unsellable) == 0x1579);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ClickRepairable) == 0x157A);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, CanBeOccupied) == 0x157B);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, CanOccupyFire) == 0x157C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, MaxNumberOccupants) == 0x1580);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ShowOccupantPips) == 0x1584);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, MuzzleFlash) == 0x1588);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DamageFireOffset) == 0x15D8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, QueueingCell) == 0x1618);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, NumberImpassableRows) == 0x1620);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, RemoveOccupy) == 0x1624);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, AddOccupy) == 0x1664);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Radar) == 0x16A4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SpySat) == 0x16A5);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ChargeAnim) == 0x16A6);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, IsAnimDelayedFire) == 0x16A7);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SiloDamage) == 0x16A8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnitRepair) == 0x16A9);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnitReload) == 0x16AA);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Bunker) == 0x16AB);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Cloning) == 0x16AC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Grinding) == 0x16AD);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnitAbsorb) == 0x16AE);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, InfantryAbsorb) == 0x16AF);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SecretLab) == 0x16B0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DoubleThick) == 0x16B1);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Flat) == 0x16B2);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DockUnload) == 0x16B3);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Recoilless) == 0x16B4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, HasStupidGuardMode) == 0x16B5);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BridgeRepairHut) == 0x16B6);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Gate) == 0x16B7);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SAM) == 0x16B8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ConstructionYard) == 0x16B9);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, NukeSilo) == 0x16BA);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Refinery) == 0x16BB);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Weeder) == 0x16BC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, WeaponsFactory) == 0x16BD);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, LaserFencePost) == 0x16BE);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, LaserFence) == 0x16BF);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, FirestormWall) == 0x16C0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Hospital) == 0x16C1);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Armory) == 0x16C2);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, EMPulseCannon) == 0x16C3);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, TickTank) == 0x16C4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, TurretAnimIsVoxel) == 0x16C5);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BarrelAnimIsVoxel) == 0x16C6);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, CloakGenerator) == 0x16C7);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SensorArray) == 0x16C8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ICBMLauncher) == 0x16C9);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Artillary) == 0x16CA);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, Helipad) == 0x16CB);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, OrePurifier) == 0x16CC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, FactoryPlant) == 0x16CD);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, InfantryCostBonus) == 0x16D0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, UnitsCostBonus) == 0x16D4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, AircraftCostBonus) == 0x16D8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BuildingsCostBonus) == 0x16DC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DefensesCostBonus) == 0x16E0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, GDIBarracks) == 0x16E4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, NODBarracks) == 0x16E5);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, YuriBarracks) == 0x16E6);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ChargedAnimTime) == 0x16E8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DelayedFireDelay) == 0x16EC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SuperWeapon) == 0x16F0);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, SuperWeapon2) == 0x16F4);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, GateStages) == 0x16F8);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, PowersUpToLevel) == 0x16FC);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DamagedDoor) == 0x1700);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, InvisibleInGame) == 0x1701);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, TerrainPalette) == 0x1702);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, PlaceAnywhere) == 0x1703);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ExtraDamageStage) == 0x1704);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, AIBuildThis) == 0x1705);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, IsBaseDefense) == 0x1706);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, CloakRadiusInCells) == 0x1707);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ConcentricRadialIndicator) == 0x1708);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, PsychicDetectionRadius) == 0x170C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, BarrelStartPitch) == 0x1710);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, VoxelBarrelFile) == 0x1714);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, unknown_1728) == 0x1728);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, VoxelBarrelOffsetToPitchPivotPoint) == 0x1730);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, VoxelBarrelOffsetToRotatePivotPoint) == 0x173C);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, VoxelBarrelOffsetToBuildingPivotPoint) == 0x1748);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, VoxelBarrelOffsetToBarrelEnd) == 0x1754);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DemandLoad) == 0x1760);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DemandLoadBuildup) == 0x1761);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, FreeBuildup) == 0x1762);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, IsThreatRatingNode) == 0x1763);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, PrimaryFireDualOffset) == 0x1764);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, ProtectWithWall) == 0x1765);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, CanHideThings) == 0x1766);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, CrateBeneath) == 0x1767);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, LeaveRubble) == 0x1768);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, CrateBeneathIsMoney) == 0x1769);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, TheaterSpecificID) == 0x176A);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, NumberOfDocks) == 0x1780);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_0045DD90, DockingOffsets) == 0x1784);
// sizeof is from the allocation: `PUSH 0x1798; CALL 0x7C8E17` at 0x465416, 0x466053, 0x6C29BC.
GG_STATIC_ASSERT(sizeof(BuildingTypeView_0045DD90) == 0x1798);

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_TYPE_CLASS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: BuildingTypeClass ctor FUN_0x0045DD90 member-access sites
//   (start 0xDF8, size 0x1798), cross-checked vs YRpp.
//   Parent ctor 0x710AF0 (TechnoTypeClass). Anchors
//   align_E24, unknown_1538/153C/1540/1544, align_1794 land exactly; ctor
//   ground-truth spot-checks ArrayIndex@0xDF8, Buildup@0xE00,
//   unknown_1538@0x1538, DockingOffsets@0x1784.
//
// BuildingTypeClass — leaf type blueprint for every building type. Derives
// TechnoTypeClass (the full type spine: AbstractClass COM base + ObjectType art
// + Techno combat/movement/voice/cameo blueprint) at offset 0, and adds the
// building-specific fields from 0xDF8 (foundation, animations, power, occupancy,
// barrel/turret geometry, docking).
//
// Pointer / *Class* members read as int/undefined4 in decomp are 64-bit
// truncation sites; modelled here as real 4-byte pointers (opaque
// forward-declared structs) / exact-size component structs so every downstream
// offset stays byte-exact.
#ifndef GG_MATCH_LAYOUT_BUILDING_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_BUILDING_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "techno_type_class.h"   // TechnoTypeClass (sizeof 0xDF8) + CoordStruct
#include "vector_class.h"        // VectorClassLayoutOf
#include "../vector_class.h"       // VectorClass<T> (sizeof 0x10) — DockingOffsets
#include "tpoint3d.h"            // TPoint3D<int>, the DockingOffsets element

// ---------------------------------------------------------------------------
// Local component structs (sizes proven by the oracle doc).
// ---------------------------------------------------------------------------

#include "geometry2d.h"

// BuildingAnimFrameStruct — 3-int building-anim frame descriptor (size = 0xC).
struct BuildingAnimFrameStruct
{
    int Frame;    // +0x00
    int Count;    // +0x04
    int Rate;     // +0x08
};
GG_STATIC_ASSERT(sizeof(BuildingAnimFrameStruct) == 0xC);

// BuildingAnimStruct — per-slot building animation record (size = 0x44). Member
// names are the art INI key suffixes the type reader stores into each field
// (<Prefix>, <Prefix>Damaged, <Prefix>Garrisoned, <Prefix>X ... <Prefix>PoweredSpecial).
struct BuildingAnimStruct
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
GG_STATIC_ASSERT(offsetof(BuildingAnimStruct, Damaged)    == 0x10);
GG_STATIC_ASSERT(offsetof(BuildingAnimStruct, Garrisoned) == 0x20);
GG_STATIC_ASSERT(offsetof(BuildingAnimStruct, X)          == 0x30);
GG_STATIC_ASSERT(offsetof(BuildingAnimStruct, Powered)    == 0x40);
GG_STATIC_ASSERT(sizeof(BuildingAnimStruct) == 0x44);

// The 16-byte object the constructor copies out of the global at 0x89C8A0 into +0x1538 (a struct copy
// through one base register in retail, not four independent member stores).
struct BuildingTypeQuad
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;
};
GG_STATIC_ASSERT(sizeof(BuildingTypeQuad) == 0x10);

// Opaque forward decls for the truncation-site pointer members (4 bytes each).
// (SHPStruct, BuildingTypeClass, UnitTypeClass, InfantryTypeClass are already
//  forward-declared by techno_type_class.h; re-declared here is harmless.)
struct CellStruct;
class OverlayTypeClass;
class IsometricTileTypeClass;

// ---------------------------------------------------------------------------
// BuildingTypeClass  (0xDF8..0x1797, sizeof = 0x1798)
// ---------------------------------------------------------------------------
class BuildingTypeClass : public TechnoTypeClass
{
public:
    // FUNCTION: GAMEMD 0x45DD90 -- the named constructor.
    BuildingTypeClass(const char* id);
    // FUNCTION: GAMEMD 0x45E520 -- the no-initialisation constructor.
    BuildingTypeClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x45E580 -- the destructor body; 0x465DC0 is the compiler-made scalar deleting destructor.
    virtual ~BuildingTypeClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);              // 3   0x465380
    virtual HRESULT __stdcall Load(IStream* pStm);                      // 5   0x465010
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);    // 6   0x465300
    virtual void vf_13(Obj_004A1D30* crc);                              // 13  0x464B30
    virtual bool vf_25(CCINIClass* ini);                                // 25  0x45FE50
    virtual CoordStruct vf_27(const CoordStruct& coord);                // 27  0x464A70
    virtual int vf_29();                                                // 29  0x45ECE0
    virtual CoordStruct vf_30();                                        // 30  0x45EBD0
    virtual CoordStruct vf_31();                                        // 31  0x464AF0
    virtual bool vf_32(const CellStruct* cell, HouseClass* house);      // 32  0x45E800
    virtual int vf_33(HouseClass* owner);                               // 33  0x45EDD0
    virtual ObjectClass* vf_35(HouseClass* house);                      // 35  0x45E880
    virtual CellStruct* vf_36(int a1);                                  // 36  0x45EC20
    virtual void* vf_39();                                              // 39  0x45F040
    virtual int vf_43();                                                // 43  0x45ED50
    virtual bool vf_42(CellStruct* cell, HouseClass* owner);            // 42  0x464AC0
    // FUNCTION: GAMEMD 0x45FA90 (decl; reloc) -- post-load work.
    void LoadFixup();
    // FUNCTION: GAMEMD 0x45F230 (decl; reloc) -- stamps the theater into the art names.
    void StampTheater(int theaterIndex);
    virtual int vf_16();                    // 16  0x465DB0
    virtual int vf_12();                    // 12  0x465DA0
    virtual int vf_11();                    // 11  0x465D90
    virtual bool vf_41();                    // 41  0x465920
    virtual bool vf_40();                    // 40  0x465910
    // Native introduced slot 48, after TechnoTypeClass slots 0..47; 0x465960.
    virtual void* vf_48();

    // FUNCTION: GAMEMD 0x45EC90 (decl; reloc)
    int GetFoundationWidth() const;
    // FUNCTION: GAMEMD 0x45ECA0 (decl; reloc) -- one stack argument (RET 4)
    int GetFoundationHeight(bool includeBib) const;
    // FUNCTION: GAMEMD 0x465570 (decl; reloc) -- writes a rectangle into `out` and returns it; RET 4.
    RectangleStruct* FUN_00465570(RectangleStruct* out) const;
    // FUNCTION: GAMEMD 0x465AF0 -- releases the owned buildup image.
    void ClearBuildUp();
    // FUNCTION: GAMEMD 0x465D40 -- const predicate; existing external spelling
    // below remains for callers whose source ownership is not recovered here.
    bool IsVehicle() const;

    int               ArrayIndex;                  // +0xDF8
    CellStruct*       FoundationData;              // +0xDFC
    SHPStruct*        Buildup;                     // +0xE00
    bool              BuildupLoaded;               // +0xE04
    unsigned char     _pad_E05[3];                 // +0xE05
    int               BuildCat;                    // +0xE08 (enum)
    CoordStructInit       HalfDamageSmokeLocation1;    // +0xE0C (0xC)
    CoordStructInit       HalfDamageSmokeLocation2;    // +0xE18 (0xC)
    unsigned long     align_E24;                   // +0xE24 (DWORD)
    double            GateCloseDelay;              // +0xE28
    int               LightVisibility;             // +0xE30
    int               LightIntensity;              // +0xE34
    int               LightRedTint;                // +0xE38
    int               LightGreenTint;              // +0xE3C
    int               LightBlueTint;               // +0xE40
    Point2D           PrimaryFirePixelOffset;      // +0xE44 (8)
    Point2D           SecondaryFirePixelOffset;    // +0xE4C (8)
    OverlayTypeClass* ToOverlay;                   // +0xE54
    IsometricTileTypeClass* ToTile;                // +0xE58
    char              BuildupFile[0x10];           // +0xE5C
    int               BuildupSound;                // +0xE6C
    int               PackupSound;                 // +0xE70
    int               CreateUnitSound;             // +0xE74
    int               UnitEnterSound;              // +0xE78
    int               UnitExitSound;               // +0xE7C
    int               WorkingSound;                // +0xE80
    int               NotWorkingSound;             // +0xE84
    char              PowersUpBuilding[0x18];      // +0xE88
    UnitTypeClass*    FreeUnit;                     // +0xEA0
    InfantryTypeClass* SecretInfantry;             // +0xEA4
    UnitTypeClass*    SecretUnit;                   // +0xEA8
    BuildingTypeClass* SecretBuilding;             // +0xEAC
    int               field_EB0;                   // +0xEB0
    int               Adjacent;                    // +0xEB4
    int               Factory;                     // +0xEB8 (AbstractType enum)
    CoordStructInit       TargetCoordOffset;           // +0xEBC (0xC)
    CoordStructInit       ExitCoord;                   // +0xEC8 (0xC)
    CellStruct*       FoundationOutside;           // +0xED4
    int               field_ED8;                   // +0xED8
    int               DeployFacing;                // +0xEDC
    int               PowerBonus;                  // +0xEE0
    int               PowerDrain;                  // +0xEE4
    int               ExtraPowerBonus;             // +0xEE8
    int               ExtraPowerDrain;             // +0xEEC
    int               Foundation;                  // +0xEF0 (enum)
    int               Height;                      // +0xEF4
    int               OccupyHeight;                // +0xEF8
    int               MidPoint;                    // +0xEFC
    int               DoorStages;                  // +0xF00
    BuildingAnimFrameStruct BuildingAnimFrame[6];  // +0xF04 (0x48)
    BuildingAnimStruct      BuildingAnim[0x15];    // +0xF4C (0x594)
    int               Upgrades;                    // +0x14E0
    SHPStruct*        DeployingAnim;               // +0x14E4
    bool              DeployingAnimLoaded;         // +0x14E8
    unsigned char     _pad_14E9[3];                // +0x14E9
    SHPStruct*        UnderDoorAnim;               // +0x14EC
    bool              UnderDoorAnimLoaded;         // +0x14F0
    unsigned char     _pad_14F1[3];                // +0x14F1
    SHPStruct*        Rubble;                      // +0x14F4
    bool              RubbleLoaded;                // +0x14F8
    unsigned char     _pad_14F9[3];                // +0x14F9
    SHPStruct*        RoofDeployingAnim;           // +0x14FC
    bool              RoofDeployingAnimLoaded;     // +0x1500
    unsigned char     _pad_1501[3];                // +0x1501
    SHPStruct*        UnderRoofDoorAnim;           // +0x1504
    bool              UnderRoofDoorAnimLoaded;     // +0x1508
    unsigned char     _pad_1509[3];                // +0x1509
    SHPStruct*        DoorAnim;                    // +0x150C
    SHPStruct*        SpecialZOverlay;             // +0x1510
    int               SpecialZOverlayZAdjust;      // +0x1514
    SHPStruct*        BibShape;                    // +0x1518
    bool              BibShapeLoaded;              // +0x151C
    unsigned char     _pad_151D[3];                // +0x151D
    int               NormalZAdjust;               // +0x1520
    int               AntiAirValue;                // +0x1524
    int               AntiArmorValue;              // +0x1528
    int               AntiInfantryValue;           // +0x152C
    Point2D           ZShapePointMove;             // +0x1530 (8)
    BuildingTypeQuad  unknown_1538;                // +0x1538 (0x10)
    short             ExtraLight;                  // +0x1548 (WORD, read with a sign-extending load at 0x43D824)
    bool              TogglePower;                 // +0x154A
    bool              HasSpotlight;                        // +0x154B
    bool              IsTemple;                            // +0x154C
    bool              IsPlug;                              // +0x154D
    bool              HoverPad;                            // +0x154E
    bool              BaseNormal;                          // +0x154F
    bool              EligibileForAllyBuilding;            // +0x1550
    bool              EligibleForDelayKill;                // +0x1551
    bool              NeedsEngineer;                       // +0x1552
    unsigned char     _pad_1553[1];                // +0x1553
    int               CaptureEvaEvent;             // +0x1554
    int               ProduceCashStartup;          // +0x1558
    int               ProduceCashAmount;           // +0x155C
    int               ProduceCashDelay;            // +0x1560
    int               InfantryGainSelfHeal;        // +0x1564
    int               UnitsGainSelfHeal;           // +0x1568
    int               RefinerySmokeFrames;         // +0x156C
    bool              Bib;                                 // +0x1570
    bool              Wall;                                // +0x1571
    bool              Capturable;                          // +0x1572
    bool              Powered;                             // +0x1573
    bool              PoweredSpecial;                      // +0x1574
    bool              Overpowerable;                       // +0x1575
    bool              Spyable;                             // +0x1576
    bool              CanC4;                               // +0x1577
    bool              WantsExtraSpace;                     // +0x1578
    bool              Unsellable;                          // +0x1579
    bool              ClickRepairable;                     // +0x157A
    bool              CanBeOccupied;                       // +0x157B
    bool              CanOccupyFire;                       // +0x157C
    unsigned char     _pad_157D[3];                // +0x157D
    int               MaxNumberOccupants;          // +0x1580
    bool              ShowOccupantPips;            // +0x1584
    unsigned char     _pad_1585[3];                // +0x1585
    Point2D           MuzzleFlash[0xA];            // +0x1588 (0x50)
    Point2D           DamageFireOffset[8];         // +0x15D8 (0x40)
    Point2D           QueueingCell;                // +0x1618 (8)
    int               NumberImpassableRows;        // +0x1620
    Point2D           RemoveOccupy[8];             // +0x1624 (0x40)
    Point2D           AddOccupy[8];                // +0x1664 (0x40)
    bool              Radar;                               // +0x16A4
    bool              SpySat;                              // +0x16A5
    bool              ChargeAnim;                          // +0x16A6
    bool              IsAnimDelayedFire;                   // +0x16A7
    bool              SiloDamage;                          // +0x16A8
    bool              UnitRepair;                          // +0x16A9
    bool              UnitReload;                          // +0x16AA
    bool              Bunker;                              // +0x16AB
    bool              Cloning;                             // +0x16AC
    bool              Grinding;                            // +0x16AD
    bool              UnitAbsorb;                          // +0x16AE
    bool              InfantryAbsorb;                      // +0x16AF
    bool              SecretLab;                           // +0x16B0
    bool              DoubleThick;                         // +0x16B1
    bool              Flat;                                // +0x16B2
    bool              DockUnload;                          // +0x16B3
    bool              Recoilless;                          // +0x16B4
    bool              HasStupidGuardMode;                  // +0x16B5
    bool              BridgeRepairHut;                     // +0x16B6
    bool              Gate;                                // +0x16B7
    bool              SAM;                                 // +0x16B8
    bool              ConstructionYard;                    // +0x16B9
    bool              NukeSilo;                            // +0x16BA
    bool              Refinery;                            // +0x16BB
    bool              Weeder;                              // +0x16BC
    bool              WeaponsFactory;                      // +0x16BD
    bool              LaserFencePost;                      // +0x16BE
    bool              LaserFence;                          // +0x16BF
    bool              FirestormWall;                       // +0x16C0
    bool              Hospital;                            // +0x16C1
    bool              Armory;                              // +0x16C2
    bool              EMPulseCannon;                       // +0x16C3
    bool              TickTank;                            // +0x16C4
    bool              TurretAnimIsVoxel;                   // +0x16C5
    bool              BarrelAnimIsVoxel;                   // +0x16C6
    bool              CloakGenerator;                      // +0x16C7
    bool              SensorArray;                         // +0x16C8
    bool              ICBMLauncher;                        // +0x16C9
    bool              Artillary;                           // +0x16CA
    bool              Helipad;                             // +0x16CB
    bool              OrePurifier;                         // +0x16CC
    bool              FactoryPlant;                        // +0x16CD
    unsigned char     _pad_16CE[2];                // +0x16CE
    float             InfantryCostBonus;           // +0x16D0
    float             UnitsCostBonus;              // +0x16D4
    float             AircraftCostBonus;           // +0x16D8
    float             BuildingsCostBonus;          // +0x16DC
    float             DefensesCostBonus;           // +0x16E0
    bool              GDIBarracks;                         // +0x16E4
    bool              NODBarracks;                         // +0x16E5
    bool              YuriBarracks;                        // +0x16E6
    unsigned char     _pad_16E7[1];                // +0x16E7
    float             ChargedAnimTime;             // +0x16E8
    int               DelayedFireDelay;            // +0x16EC
    int               SuperWeapon;                 // +0x16F0
    int               SuperWeapon2;                // +0x16F4
    int               GateStages;                  // +0x16F8
    int               PowersUpToLevel;             // +0x16FC
    bool              DamagedDoor;                         // +0x1700
    bool              InvisibleInGame;                     // +0x1701
    bool              TerrainPalette;                      // +0x1702
    bool              PlaceAnywhere;                       // +0x1703
    bool              ExtraDamageStage;                    // +0x1704
    bool              AIBuildThis;                         // +0x1705
    bool              IsBaseDefense;                       // +0x1706
    unsigned char     CloakRadiusInCells;          // +0x1707 (BYTE)
    bool              ConcentricRadialIndicator;   // +0x1708
    unsigned char     _pad_1709[3];                // +0x1709
    int               PsychicDetectionRadius;      // +0x170C
    int               BarrelStartPitch;            // +0x1710
    char              VoxelBarrelFile[0x10];       // +0x1714
    unsigned char     unknown_1724[4];             // +0x1724
    double            unknown_1728;                // +0x1728 (CRC input as a double)
    CoordStruct       VoxelBarrelOffsetToPitchPivotPoint;    // +0x1730 (0xC)
    CoordStruct       VoxelBarrelOffsetToRotatePivotPoint;   // +0x173C (0xC)
    CoordStruct       VoxelBarrelOffsetToBuildingPivotPoint; // +0x1748 (0xC)
    CoordStruct       VoxelBarrelOffsetToBarrelEnd;          // +0x1754 (0xC)
    bool              DemandLoad;                          // +0x1760
    bool              DemandLoadBuildup;                   // +0x1761
    bool              FreeBuildup;                         // +0x1762
    bool              IsThreatRatingNode;                  // +0x1763
    bool              PrimaryFireDualOffset;               // +0x1764
    bool              ProtectWithWall;                     // +0x1765
    bool              CanHideThings;                       // +0x1766
    bool              CrateBeneath;                        // +0x1767
    bool              LeaveRubble;                         // +0x1768
    bool              CrateBeneathIsMoney;                 // +0x1769
    char              TheaterSpecificID[0x13];     // +0x176A (0x176A..0x177C)
    unsigned char     _pad_177D[3];                // +0x177D
    int               NumberOfDocks;               // +0x1780
    VectorClass<TPoint3D<int> > DockingOffsets;          // +0x1784 (0x10); retail RTTI: vtable 0x7E4638
    unsigned long     align_1794;                  // +0x1794 (DWORD)
};

// --- Representative offset asserts (spanning the struct) + final sizeof ------
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, ArrayIndex)        == 0xDF8);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, align_E24)         == 0xE24);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, GateCloseDelay)    == 0xE28);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, BuildupFile)       == 0xE5C);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, SecretBuilding)    == 0xEAC);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, TargetCoordOffset) == 0xEBC);
GG_STATIC_ASSERT(sizeof(((BuildingTypeClass*)0)->TargetCoordOffset) == 0x0C);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, BuildingAnimFrame) == 0xF04);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, BuildingAnim)      == 0xF4C);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, Upgrades)          == 0x14E0);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, BibShape)          == 0x1518);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, unknown_1538)      == 0x1538);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, HasSpotlight)     == 0x154B);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, Bib)              == 0x1570);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, MuzzleFlash)       == 0x1588);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, AddOccupy)         == 0x1664);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, Radar)            == 0x16A4);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, TickTank)         == 0x16C4);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, WeaponsFactory)   == 0x16BD);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, ChargedAnimTime)   == 0x16E8);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, CloakRadiusInCells)== 0x1707);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, VoxelBarrelFile)   == 0x1714);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, DemandLoad)        == 0x1760);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, TheaterSpecificID) == 0x176A);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, NumberOfDocks)     == 0x1780);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, DockingOffsets)    == 0x1784);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, align_1794)        == 0x1794);
GG_STATIC_ASSERT(sizeof(BuildingTypeClass)                      == 0x1798);

GG_STATIC_ASSERT(offsetof(BuildingTypeClass, BuildCat) == 0xE08);

#endif  // GG_MATCH_LAYOUT_BUILDING_TYPE_CLASS_H

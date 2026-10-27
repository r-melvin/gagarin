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
#include "vector_class.h"        // VectorClass (sizeof 0x10) — DockingOffsets

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
    // Native introduced slot 48, after TechnoTypeClass slots 0..47; 0x465960.
    virtual void* vf_48();

    // FUNCTION: GAMEMD 0x45EC90 (decl; reloc)
    int GetFoundationWidth() const;
    // FUNCTION: GAMEMD 0x45ECA0 (decl; reloc) -- one stack argument (RET 4)
    int GetFoundationHeight(bool includeBib) const;
    // FUNCTION: GAMEMD 0x465AF0 -- releases the owned buildup image.
    void ClearBuildUp();
    // FUNCTION: GAMEMD 0x465D40 -- const predicate; existing external spelling
    // below remains for callers whose source ownership is not recovered here.
    bool IsVehicle() const;
    // FUNCTION: GAMEMD 0x465D40 (decl; reloc) -- no stack arguments, result in AL; BuildingClass slot 32 (0x457620) returns it.
    bool FUN_00465D40();

    int               ArrayIndex;                  // +0xDF8
    CellStruct*       FoundationData;              // +0xDFC
    SHPStruct*        Buildup;                     // +0xE00
    bool              BuildupLoaded;               // +0xE04
    unsigned char     _pad_E05[3];                 // +0xE05
    int               BuildCat;                    // +0xE08 (enum)
    CoordStruct       HalfDamageSmokeLocation1;    // +0xE0C (0xC)
    CoordStruct       HalfDamageSmokeLocation2;    // +0xE18 (0xC)
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
    CoordStruct       TargetCoordOffset;           // +0xEBC (0xC)
    CoordStruct       ExitCoord;                   // +0xEC8 (0xC)
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
    int               unknown_1538;                // +0x1538
    int               unknown_153C;                // +0x153C
    int               unknown_1540;                // +0x1540
    int               unknown_1544;                // +0x1544
    short             ExtraLight;                  // +0x1548 (WORD, read with a sign-extending load at 0x43D824)
    bool              TogglePower;                 // +0x154A
    // 8 x bool: HasSpotlight, IsTemple, IsPlug, HoverPad, BaseNormal,
    // EligibileForAllyBuilding, EligibleForDelayKill, NeedsEngineer.
    bool              bools_154B[8];               // +0x154B (0x154B..0x1552)
    unsigned char     _pad_1553[1];                // +0x1553
    int               CaptureEvaEvent;             // +0x1554
    int               ProduceCashStartup;          // +0x1558
    int               ProduceCashAmount;           // +0x155C
    int               ProduceCashDelay;            // +0x1560
    int               InfantryGainSelfHeal;        // +0x1564
    int               UnitsGainSelfHeal;           // +0x1568
    int               RefinerySmokeFrames;         // +0x156C
    // 13 x bool: Bib, Wall, Capturable, Powered, PoweredSpecial, Overpowerable,
    // Spyable, CanC4, WantsExtraSpace, Unsellable, ClickRepairable,
    // CanBeOccupied, CanOccupyFire.
    bool              bools_1570[13];              // +0x1570 (0x1570..0x157C)
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
    // 42 x bool: Radar … FactoryPlant.
    bool              bools_16A4[42];              // +0x16A4 (0x16A4..0x16CD)
    unsigned char     _pad_16CE[2];                // +0x16CE
    float             InfantryCostBonus;           // +0x16D0
    float             UnitsCostBonus;              // +0x16D4
    float             AircraftCostBonus;           // +0x16D8
    float             BuildingsCostBonus;          // +0x16DC
    float             DefensesCostBonus;           // +0x16E0
    // 3 x bool: GDIBarracks, NODBarracks, YuriBarracks.
    bool              bools_16E4[3];               // +0x16E4 (0x16E4..0x16E6)
    unsigned char     _pad_16E7[1];                // +0x16E7
    float             ChargedAnimTime;             // +0x16E8
    int               DelayedFireDelay;            // +0x16EC
    int               SuperWeapon;                 // +0x16F0
    int               SuperWeapon2;                // +0x16F4
    int               GateStages;                  // +0x16F8
    int               PowersUpToLevel;             // +0x16FC
    // 7 x bool: DamagedDoor, InvisibleInGame, TerrainPalette, PlaceAnywhere,
    // ExtraDamageStage, AIBuildThis, IsBaseDefense.
    bool              bools_1700[7];               // +0x1700 (0x1700..0x1706)
    unsigned char     CloakRadiusInCells;          // +0x1707 (BYTE)
    bool              ConcentricRadialIndicator;   // +0x1708
    unsigned char     _pad_1709[3];                // +0x1709
    int               PsychicDetectionRadius;      // +0x170C
    int               BarrelStartPitch;            // +0x1710
    char              VoxelBarrelFile[0x1C];       // +0x1714
    CoordStruct       VoxelBarrelOffsetToPitchPivotPoint;    // +0x1730 (0xC)
    CoordStruct       VoxelBarrelOffsetToRotatePivotPoint;   // +0x173C (0xC)
    CoordStruct       VoxelBarrelOffsetToBuildingPivotPoint; // +0x1748 (0xC)
    CoordStruct       VoxelBarrelOffsetToBarrelEnd;          // +0x1754 (0xC)
    // 10 x bool: DemandLoad, DemandLoadBuildup, FreeBuildup, IsThreatRatingNode,
    // PrimaryFireDualOffset, ProtectWithWall, CanHideThings, CrateBeneath,
    // LeaveRubble, CrateBeneathIsMoney.
    bool              bools_1760[10];              // +0x1760 (0x1760..0x1769)
    char              TheaterSpecificID[0x13];     // +0x176A (0x176A..0x177C)
    unsigned char     _pad_177D[3];                // +0x177D
    int               NumberOfDocks;               // +0x1780
    VectorClassLayout       DockingOffsets;              // +0x1784 (0x10)
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
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_154B)        == 0x154B);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_1570)        == 0x1570);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, MuzzleFlash)       == 0x1588);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, AddOccupy)         == 0x1664);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_16A4)        == 0x16A4);
GG_STATIC_ASSERT(sizeof(((BuildingTypeClass*)0)->bools_16A4[0]) == 0x01);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_16A4) + 25   == 0x16BD);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, ChargedAnimTime)   == 0x16E8);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, CloakRadiusInCells)== 0x1707);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, VoxelBarrelFile)   == 0x1714);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_1760)        == 0x1760);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, TheaterSpecificID) == 0x176A);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, NumberOfDocks)     == 0x1780);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, DockingOffsets)    == 0x1784);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, align_1794)        == 0x1794);
GG_STATIC_ASSERT(sizeof(BuildingTypeClass)                      == 0x1798);

GG_STATIC_ASSERT(offsetof(BuildingTypeClass, BuildCat) == 0xE08);

#endif  // GG_MATCH_LAYOUT_BUILDING_TYPE_CLASS_H

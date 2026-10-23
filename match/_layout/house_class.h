// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: HouseClass ctor FUN_0x004F54A0 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0; sizeof(AbstractClass) == 0x24). The ctor is
//   ~1020 instructions and, uniquely in this codebase, initialises essentially
//   the entire 0x24..0x160B7 object in one body; 287 distinct member offsets
//   were extracted from its [EBP+disp] operand set (EBP is `this` throughout).
//   The citations beside each member are stores from that body.
//
//   sizeof: `PUSH 0x160B8` (90296) precedes the ctor call at 8 of the 8
//   allocation sites found by `ghidra x-ref to 0x4F54A0`, and the last member
//   PowerSurplus @0x160B4 closes the object exactly on that.
//
//   RTTI (read from the binary, outranks any document): SEVEN complete object
//   locators name ".?AVHouseClass@@", with COL base-offsets
//   0x0 / 0x4 / 0x8 / 0xC / 0x24 / 0x28 / 0x2C. So HouseClass carries three
//   further interface subobjects at 0x24, 0x28 and 0x2C — above the
//   AbstractClass base, below ArrayIndex — in addition to the usual three COM
//   subobjects at 0x4/0x8/0xC. The ctor stores all seven vptrs at
//   0x004F5DCC..0x004F5DFB. YRpp's member list does not enumerate them (they
//   are implied by its base list), so anyone laying HouseClass out from the
//   member list alone will be 0xC bytes short before ArrayIndex.
//
//   Four independent anchor checks — YRpp embeds the offset in four member
//   names, and all four land exactly where the ctor puts them:
//     AIState_1E4 @0x1E4, unknown_324 @0x324, AircraftType_53D0 @0x53D0,
//     Unknown_Timer_5640 @0x5640.
//   Three array widths close on their successors to the byte:
//     ThreatPosedEstimates[130][130] = 0x10810 bytes, 0x57E4 -> 0x15FF4 (the
//     ctor's next store is `MOV byte [EBP+0x15FF4],BL` @0x004F5D41);
//     the ten UnitTrackerClass blocks at stride 0x808, 0x328 -> 0x5378;
//     the twelve CounterClass blocks at stride 0x14, 0x5500 -> 0x55F0.
//
//   Cross-read against YRpp: 185 named members claimed;
//   180 confirmed by a ctor store or by exact closure between two confirmed
//   neighbours; 5 unconfirmed and recorded as unknown_XX (0x549C ZoneInfos —
//   bounded but never written, 0x16058/0x1605C StartingPoint/StartingAllies,
//   0x16084, 0x16098). No offset disagreement found: every YRpp offset this
//   ctor touches is correct. The only structural omission is the three
//   interface vptrs noted above.
//
// HouseClass — a player/country. Derives AbstractClass at offset 0.
#ifndef GG_MATCH_LAYOUT_HOUSE_CLASS_H
#define GG_MATCH_LAYOUT_HOUSE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "mission_class.h"    // CDTimerClass
#include "techno_class.h"     // StorageClass
#include "foot_class.h"       // CellStruct
#include "vector_class.h"     // DynamicVectorClass
#include "components.h"       // ColorStruct

// --- opaque blocks whose SIZE is proven but whose fields are not named -------
// Each size is proven by closure between two confirmed neighbours in the ctor.

// UnitTrackerClass — 0x808. Ten of them run 0x328..0x5378 at stride 0x808
// (ctor LEA ECX sites 0x004F58E9..0x004F594C).
#ifndef GG_MATCH_LAYOUT_UNITTRACKERCLASS_DEFINED
#define GG_MATCH_LAYOUT_UNITTRACKERCLASS_DEFINED
struct UnitTrackerClass { unsigned char unknown_00[0x808]; };
GG_STATIC_ASSERT(sizeof(UnitTrackerClass) == 0x808);
#endif

// CounterClass — 0x14. Twelve of them run 0x5500..0x55F0 at stride 0x14
// (ctor LEA ECX sites 0x004F5AAB..0x004F5B2E).
#ifndef GG_MATCH_LAYOUT_COUNTERCLASS_DEFINED
#define GG_MATCH_LAYOUT_COUNTERCLASS_DEFINED
class CounterClass
{
public:
    unsigned char unknown_00[0x14];
    // FUNCTION: GAMEMD 0x49FB60 (decl; reloc) -- the sum over every type (ECX = the counter, no arguments).
    int FUN_0049FB60() const;
};
GG_STATIC_ASSERT(sizeof(CounterClass) == 0x14);
#endif

// DropshipStruct — 0x2C. Three of them run 0x5670..0x56F4 (ctor LEA ESI
// @0x004F5BFF; next confirmed member CurrentDropshipIndex @0x56F4).
#ifndef GG_MATCH_LAYOUT_DROPSHIPSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_DROPSHIPSTRUCT_DEFINED
struct DropshipStruct { unsigned char unknown_00[0x2C]; };
GG_STATIC_ASSERT(sizeof(DropshipStruct) == 0x2C);
#endif

// BaseClass — 0x78, at 0x5700..0x5778 (ctor LEA ECX @0x004F5C42; next
// confirmed member RecheckPower @0x5778).
#ifndef GG_MATCH_LAYOUT_BASECLASS_DEFINED
#define GG_MATCH_LAYOUT_BASECLASS_DEFINED
class BaseClass { public: unsigned char unknown_00[0x78]; };
GG_STATIC_ASSERT(sizeof(BaseClass) == 0x78);
#endif

// ZoneInfoStruct — 0xC. Five of them fill 0x549C..0x54D8, bounded by Radius
// @0x5498 and LATime @0x54D8; the ctor never writes the block, so the 0xC
// stride is an inference from the 0x3C span, not a direct measurement.
#ifndef GG_MATCH_LAYOUT_ZONEINFOSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_ZONEINFOSTRUCT_DEFINED
struct ZoneInfoStruct { unsigned char unknown_00[0xC]; };
GG_STATIC_ASSERT(sizeof(ZoneInfoStruct) == 0xC);
#endif

class BuildingTypeClass;
class HouseTypeClass;
class UnitTypeClass;
template<class T> class DynamicVectorClass;

#include <ocidl.h>   // IConnectionPointContainer (VC98 SDK, LIBRARY)

#include "house_interfaces.h"   // IHouse, IPublicHouse

// Bases per retail CHD (COL 0x802A28): IHouse mdisp 0x24, IPublicHouse 0x28,
// IConnectionPointContainer 0x2C.
class HouseClass : public AbstractClass, public IHouse, public IPublicHouse, public IConnectionPointContainer
{
public:
    // FUNCTION: GAMEMD 0x502D30 (decl; reloc) -- first house whose type has this country index; ECX carries it.
    static HouseClass* FindByCountryIndex(int country);
    // FUNCTION: GAMEMD 0x4F9790 (decl; reloc) -- one stack argument.
    void FUN_004F9790(int unknownStackArg0);
    // FUNCTION: GAMEMD 0x4F9950 (decl; reloc) -- one stack argument.
    void FUN_004F9950(int unknownStackArg0);
    // FUNCTION: GAMEMD 0x4FCE30 (decl; reloc)
    double FUN_004FCE30();
    // FUNCTION: GAMEMD 0x4F9750 (decl; reloc) -- matched in economy/house_class_misc_methods.cpp.
    double GetWeedStoragePercentage();
    // FUNCTION: GAMEMD 0x509140 (decl; reloc) -- (factory kind, naval, category), RET 0xC;
    // BuildingClass 0x452360 passes Type->Factory, Type->Naval, 0.
    void Update_FactoriesQueues(int factoryOf, bool isNaval, int buildCat);
    // FUNCTION: GAMEMD 0x50B6F0 (decl; reloc)
    bool IsControlledByCurrentPlayer() const;
    // FUNCTION: GAMEMD 0x50B730 (decl; reloc)
    bool IsControlledByHuman() const;
    // Nested pointer spelling confirmed by RTTI at tables 0x7EA964/0x7EA944.
    // Its element fields and complete size remain unknown.
    struct StartingTechnoStruct;
    struct BuildChoiceClass;    // RTTI: .?AUBuildChoiceClass@HouseClass@@ (vector element)
    // +0x24/+0x28/+0x2C: IHouse, IPublicHouse, IConnectionPointContainer vptrs
    //   (ctor stores 0x7EA834 @0x004F5DE8, 0x7EA80C @0x004F5DEF, 0x7EA7F4 @0x004F5DFB).
    int    ArrayIndex;                     // +0x30 ctor MOV [EBP+0x30],-1 @0x004F54B8
    HouseTypeClass* Type;                  // +0x34 ctor MOV [EBP+0x34],EAX(=arg) @0x004F54C2
    DynamicVectorClassLayout RelatedTags;                 // +0x38  ctor LEA ESI @0x004F54B4 (vptr 0x7EA5A4)
    DynamicVectorClassLayout ConYards;                    // +0x50  ctor LEA ESI @0x004F54DB
    DynamicVectorClassLayout Buildings;                   // +0x68  ctor LEA ESI @0x004F54F3
    DynamicVectorClassLayout UnitRepairStations;          // +0x80  ctor LEA ESI @0x004F550B
    DynamicVectorClassLayout Grinders;                    // +0x98  ctor LEA ESI @0x004F5526
    DynamicVectorClassLayout Absorbers;                   // +0xB0  ctor LEA ESI @0x004F5541
    DynamicVectorClassLayout Bunkers;                     // +0xC8  ctor LEA ESI @0x004F555C
    DynamicVectorClassLayout Occupiables;                 // +0xE0  ctor LEA ESI @0x004F5577
    DynamicVectorClassLayout CloningVats;                 // +0xF8  ctor LEA ESI @0x004F5592
    DynamicVectorClassLayout SecretLabs;                  // +0x110 ctor LEA ESI @0x004F55AD
    DynamicVectorClassLayout PsychicDetectionBuildings;   // +0x128 ctor LEA ESI @0x004F55C8
    DynamicVectorClassLayout FactoryPlants;               // +0x140 ctor LEA ESI @0x004F55E3
    int    CountResourceGatherers;         // +0x158 ctor @0x004F55FE
    int    CountResourceDestinations;      // +0x15C ctor @0x004F5604
    int    CountWarfactories;              // +0x160 ctor @0x004F5610
    int    InfantrySelfHeal;               // +0x164 ctor @0x004F5617
    int    UnitsSelfHeal;                  // +0x168 ctor @0x004F5620
    DynamicVectorClassLayout StartingUnits;      // +0x16C ctor LEA ESI @0x004F560A
    int    AIDifficulty;                   // +0x184 ctor @0x004F5648 (0 == Hard)
    double FirepowerMultiplier;            // +0x188 ctor halves @0x004F564E/0x004F5654
    double GroundspeedMultiplier;          // +0x190 ctor @0x004F565A/0x004F5660
    double AirspeedMultiplier;             // +0x198 ctor @0x004F5666/0x004F566C
    double ArmorMultiplier;                // +0x1A0 ctor @0x004F5672/0x004F5678
    double ROFMultiplier;                  // +0x1A8 ctor @0x004F567E/0x004F5684
    double CostMultiplier;                 // +0x1B0 ctor @0x004F568A/0x004F5690
    double BuildTimeMultiplier;            // +0x1B8 ctor @0x004F5696/0x004F569C
    double RepairDelay;                    // +0x1C0 ctor @0x004F56A2/0x004F56A8
    double BuildDelay;                     // +0x1C8 ctor @0x004F56AE/0x004F56B7
    int    IQLevel;                        // +0x1D0 ctor @0x004F56BD
    int    TechLevel;                      // +0x1D4 ctor MOV [EBP+0x1D4],1 @0x004F56C3
    unsigned int AltAllies;                // +0x1D8 IndexBitfield; ctor @0x004F56CD
    int    StartingCredits;                // +0x1DC ctor @0x004F56D3
    int    StartingEdge;                   // +0x1E0 ctor @0x004F56D9
    unsigned int AIState_1E4;              // +0x1E4 ctor @0x004F56DF (name anchor confirmed)
    int    SideIndex;                      // +0x1E8 ctor MOV [EBP+0x1E8],-1 @0x004F6455
    unsigned char IsHumanPlayer;           // +0x1EC ctor @0x004F56E5
    unsigned char IsInPlayerControl;       // +0x1ED ctor @0x004F56EB
    unsigned char Production;              // +0x1EE ctor @0x004F56F1
    unsigned char AutocreateAllowed;       // +0x1EF ctor @0x004F56F7
    unsigned char NodeLogic_1F0;           // +0x1F0 ctor MOV byte,1 @0x004F56FD (name anchor confirmed)
    unsigned char ShipYardConst_1F1;       // +0x1F1 ctor @0x004F5704 (name anchor confirmed)
    unsigned char AITriggersActive;        // +0x1F2 ctor @0x004F570A
    unsigned char AutoBaseBuilding;        // +0x1F3 ctor @0x004F5710
    unsigned char DiscoveredByPlayer;      // +0x1F4 ctor @0x004F5716
    unsigned char Defeated;                // +0x1F5 ctor @0x004F571C
    unsigned char IsGameOver;              // +0x1F6 ctor @0x004F5722
    unsigned char IsWinner;                // +0x1F7 ctor @0x004F5728
    unsigned char IsLoser;                 // +0x1F8 ctor @0x004F572E
    unsigned char CiviliansEvacuated;      // +0x1F9 ctor @0x004F5734
    unsigned char FirestormActive;         // +0x1FA ctor @0x004F573A
    unsigned char HasThreatNode;           // +0x1FB ctor @0x004F5740
    unsigned char RecheckTechTree;         // +0x1FC ctor MOV byte,1 @0x004F5746
    unsigned char align_1FD[3];            // +0x1FD
    int    IPAddress;                      // +0x200 ctor @0x004F574D
    int    TournamentTeamID;               // +0x204 ctor @0x004F5753
    unsigned char LostConnection;          // +0x208 ctor @0x004F5759
    unsigned char align_209[3];            // +0x209
    int    SelectedPathIndex;              // +0x20C ctor @0x004F575F
    void*  PlanningPaths[12];              // +0x210 .. 0x23F ctor LEA EDI @0x004F643B (12 dwords = 0x30)
    signed char   Visionary;               // +0x240 ctor @0x004F5765
    unsigned char MapIsClear;              // +0x241 ctor @0x004F576B
    unsigned char IsTiberiumShort;         // +0x242 ctor @0x004F5771
    unsigned char HasBeenSpied;            // +0x243 ctor @0x004F5777
    unsigned char HasBeenThieved;          // +0x244 ctor @0x004F577D
    unsigned char Repairing;               // +0x245 ctor @0x004F5783
    unsigned char IsBuiltSomething;        // +0x246 ctor @0x004F5789
    unsigned char IsResigner;              // +0x247 ctor @0x004F578F
    unsigned char IsGiverUpper;            // +0x248 ctor @0x004F5795
    unsigned char AllToHunt;               // +0x249 ctor @0x004F579B
    unsigned char IsParanoid;              // +0x24A ctor @0x004F57A1
    unsigned char IsToLook;                // +0x24B ctor MOV byte,1 @0x004F57A7
    int    IQLevel2;                       // +0x24C ctor @0x004F57BB
    int    AIMode;                         // +0x250 ctor @0x004F57C4
    DynamicVectorClassLayout Supers;             // +0x254 ctor LEA ESI @0x004F57B4
    int    LastBuiltBuildingType;          // +0x26C ctor @0x004F57DE
    int    LastBuiltInfantryType;          // +0x270 ctor @0x004F57E4
    int    LastBuiltAircraftType;          // +0x274 ctor @0x004F57EA
    int    LastBuiltVehicleType;           // +0x278 ctor @0x004F57F0
    int    AllowWinBlocks;                 // +0x27C ctor @0x004F57F6
    CDTimerClass RepairTimer;              // +0x280 ctor @0x004F5802/0x004F5808
    CDTimerClass AlertTimer;               // +0x28C ctor @0x004F581A/0x004F5814
    CDTimerClass BorrowedTime;             // +0x298 ctor @0x004F5825/0x004F582B
    CDTimerClass PowerBlackoutTimer;       // +0x2A4 ctor @0x004F583D/0x004F5837
    CDTimerClass RadarBlackoutTimer;       // +0x2B0 ctor @0x004F5849/0x004F584F
    unsigned char Side2TechInfiltrated;    // +0x2BC ctor @0x004F5855
    unsigned char Side1TechInfiltrated;    // +0x2BD ctor @0x004F585B
    unsigned char Side0TechInfiltrated;    // +0x2BE ctor @0x004F5861
    unsigned char BarracksInfiltrated;     // +0x2BF ctor @0x004F5867
    unsigned char WarFactoryInfiltrated;   // +0x2C0 ctor @0x004F586D
    unsigned char align_2C1[3];            // +0x2C1
    unsigned int InfantryAltOwner;         // +0x2C4 ctor @0x004F5879
    unsigned int UnitAltOwner;             // +0x2C8 ctor @0x004F587F
    unsigned int AircraftAltOwner;         // +0x2CC ctor @0x004F5885
    unsigned int BuildingAltOwner;         // +0x2D0 ctor @0x004F588B
    int    AirportDocks;                   // +0x2D4 ctor @0x004F5891
    int    PoweredUnitCenters;             // +0x2D8 ctor @0x004F5897
    int    CreditsSpent;                   // +0x2DC ctor @0x004F589D
    int    HarvestedCredits;               // +0x2E0 ctor @0x004F58A3
    int    StolenBuildingsCredits;         // +0x2E4 ctor @0x004F58A9
    int    OwnedUnits;                     // +0x2E8 ctor @0x004F58AF
    int    OwnedNavy;                      // +0x2EC ctor @0x004F58B5
    int    OwnedBuildings;                 // +0x2F0 ctor @0x004F58BB
    int    OwnedInfantry;                  // +0x2F4 ctor @0x004F58C1
    int    OwnedAircraft;                  // +0x2F8 ctor @0x004F58C7
    StorageClass OwnedTiberium;            // +0x2FC ctor LEA ECX @0x004F5873
    int    Balance;                        // +0x30C ctor @0x004F58D8
    int    TotalStorage;                   // +0x310 ctor @0x004F58DE
    StorageClass OwnedWeed;                // +0x314 ctor LEA ECX @0x004F58D2
    unsigned int unknown_324;              // +0x324 (name anchor confirmed; ctor leaves it, bounded
                                           //        by OwnedWeed end and BuiltAircraftTypes start)
    UnitTrackerClass BuiltAircraftTypes;   // +0x328   ctor LEA ECX @0x004F58E9
    UnitTrackerClass BuiltInfantryTypes;   // +0xB30   ctor LEA ECX @0x004F58F4
    UnitTrackerClass BuiltUnitTypes;       // +0x1338  ctor LEA ECX @0x004F58FF
    UnitTrackerClass BuiltBuildingTypes;   // +0x1B40  ctor LEA ECX @0x004F590A
    UnitTrackerClass KilledAircraftTypes;  // +0x2348  ctor LEA ECX @0x004F5915
    UnitTrackerClass KilledInfantryTypes;  // +0x2B50  ctor LEA ECX @0x004F5920
    UnitTrackerClass KilledUnitTypes;      // +0x3358  ctor LEA ECX @0x004F592B
    UnitTrackerClass KilledBuildingTypes;  // +0x3B60  ctor LEA ECX @0x004F5936
    UnitTrackerClass CapturedBuildings;    // +0x4368  ctor LEA ECX @0x004F5941
    UnitTrackerClass CollectedCrates;      // +0x4B70  ctor LEA ECX @0x004F594C
    int    NumAirpads;                     // +0x5378 ctor @0x004F595C
    int    NumBarracks;                    // +0x537C ctor @0x004F5962
    int    NumWarFactories;                // +0x5380 ctor @0x004F5968
    int    NumConYards;                    // +0x5384 ctor @0x004F596E
    int    NumShipyards;                   // +0x5388 ctor @0x004F5974
    int    NumOrePurifiers;                // +0x538C ctor @0x004F597A
    float  CostInfantryMult;               // +0x5390 ctor @0x004F5980
    float  CostUnitsMult;                  // +0x5394 ctor @0x004F5986
    float  CostAircraftMult;               // +0x5398 ctor @0x004F598C
    float  CostBuildingsMult;              // +0x539C ctor @0x004F5992
    float  CostDefensesMult;               // +0x53A0 ctor @0x004F5998
    int    PowerOutput;                    // +0x53A4 ctor @0x004F599E
    int    PowerDrain;                     // +0x53A8 ctor @0x004F59A4
    void*  Primary_ForAircraft;            // +0x53AC ctor @0x004F59AA
    void*  Primary_ForInfantry;            // +0x53B0 ctor @0x004F59B0
    void*  Primary_ForVehicles;            // +0x53B4 ctor @0x004F59B6
    void*  Primary_ForShips;               // +0x53B8 ctor @0x004F59BC
    void*  Primary_ForBuildings;           // +0x53BC ctor @0x004F59C2
    void*  Primary_Unused1;                // +0x53C0 ctor @0x004F59C8
    void*  Primary_Unused2;                // +0x53C4 ctor @0x004F59CE
    void*  Primary_Unused3;                // +0x53C8 ctor @0x004F59D4
    void*  Primary_ForDefenses;            // +0x53CC ctor @0x004F59DA
    unsigned char AircraftType_53D0;       // +0x53D0 ctor @0x004F59E0 (name anchor confirmed)
    unsigned char InfantryType_53D1;       // +0x53D1 ctor @0x004F59E6
    unsigned char VehicleType_53D2;        // +0x53D2 ctor @0x004F59EC
    unsigned char ShipType_53D3;           // +0x53D3 ctor @0x004F59F2
    unsigned char BuildingType_53D4;       // +0x53D4 ctor @0x004F59F8
    unsigned char unknown_53D5;            // +0x53D5 ctor @0x004F59FE
    unsigned char unknown_53D6;            // +0x53D6 ctor @0x004F5A04
    unsigned char unknown_53D7;            // +0x53D7 ctor @0x004F5A0A
    unsigned char DefenseType_53D8;        // +0x53D8 ctor @0x004F5A10
    unsigned char unknown_53D9[3];         // +0x53D9 never written by the ctor
    void*  OurFlagCarrier;                 // +0x53DC UnitClass*; ctor @0x004F5A16
    CellStruct OurFlagCoords;              // +0x53E0 ctor word stores @0x004F5A1C/0x004F5A23
    int    KilledUnitsOfHouses[20];        // +0x53E4 .. 0x5433 ctor LEA EDI @0x004F62A1
    int    TotalKilledUnits;               // +0x5434 ctor @0x004F5A2A
    int    KilledBuildingsOfHouses[20];    // +0x5438 .. 0x5487 ctor LEA EDI @0x004F62AE
    int    TotalKilledBuildings;           // +0x5488 ctor @0x004F5A30
    int    WhoLastHurtMe;                  // +0x548C ctor @0x004F5A36
    CellStruct BaseSpawnCell;              // +0x5490 ctor @0x004F5A41
    CellStruct BaseCenter;                 // +0x5494 ctor @0x004F5A4D
    int    Radius;                         // +0x5498 ctor @0x004F5A53
    ZoneInfoStruct ZoneInfos[5];           // +0x549C .. 0x54D7 bounded, not written — see note
    int    LATime;                         // +0x54D8 ctor @0x004F5A59
    int    LAEnemy;                        // +0x54DC ctor @0x004F5A5F
    int    ToCapture;                      // +0x54E0 ctor @0x004F5A65
    unsigned int RadarVisibleTo;           // +0x54E4 IndexBitfield; ctor @0x004F5A6B
    int    PointTotal;                     // +0x54E8 ctor @0x004F5A71
    int    PreferredTargetType;            // +0x54EC ctor MOV [EBP+0x54EC],1 @0x004F5A77
    CellStruct PreferredTargetCell;        // +0x54F0 ctor @0x004F5A81/0x004F5A88
    CellStruct PreferredDefensiveCell;     // +0x54F4 ctor @0x004F5A8F/0x004F5A96
    CellStruct PreferredDefensiveCell2;    // +0x54F8 ctor @0x004F5A9D/0x004F5AA4
    int    PreferredDefensiveCellStartTime;// +0x54FC ctor MOV [EBP+0x54FC],-100 @0x004F5AB1
    CounterClass OwnedBuildingTypes;            // +0x5500 ctor LEA ECX @0x004F5AAB
    CounterClass OwnedUnitTypes;                // +0x5514 ctor LEA ECX @0x004F5AC0
    CounterClass OwnedInfantryTypes;            // +0x5528 ctor LEA ECX @0x004F5ACB
    CounterClass OwnedAircraftTypes;            // +0x553C ctor LEA ECX @0x004F5AD6
    CounterClass ActiveBuildingTypes;           // +0x5550 ctor LEA ECX @0x004F5AE1
    CounterClass ActiveUnitTypes;               // +0x5564 ctor LEA ECX @0x004F5AEC
    CounterClass ActiveInfantryTypes;           // +0x5578 ctor LEA ECX @0x004F5AF7
    CounterClass ActiveAircraftTypes;           // +0x558C ctor LEA ECX @0x004F5B02
    CounterClass FactoryProducedBuildingTypes;  // +0x55A0 ctor LEA ECX @0x004F5B0D
    CounterClass FactoryProducedUnitTypes;      // +0x55B4 ctor LEA ECX @0x004F5B18
    CounterClass FactoryProducedInfantryTypes;  // +0x55C8 ctor LEA ECX @0x004F5B23
    CounterClass FactoryProducedAircraftTypes;  // +0x55DC ctor LEA ECX @0x004F5B2E
    CDTimerClass AttackTimer;              // +0x55F0 ctor @0x004F5B40/0x004F637D
    int    InitialAttackDelay;             // +0x55FC ctor @0x004F5B4C
    int    EnemyHouseIndex;                // +0x5600 ctor @0x004F5B59
    DynamicVectorClassLayout AngerNodes;         // +0x5604 ctor LEA ECX @0x004F5B52
    DynamicVectorClassLayout ScoutNodes;         // +0x561C ctor LEA ECX @0x004F5B65
    CDTimerClass AITimer;                  // +0x5634 ctor @0x004F5BA2/0x004F5BA8
    CDTimerClass Unknown_Timer_5640;       // +0x5640 ctor @0x004F5BBA/0x004F5BB4 (name anchor confirmed)
    int    ProducingBuildingTypeIndex;     // +0x564C ctor @0x004F5BC0
    int    ProducingUnitTypeIndex;         // +0x5650 ctor @0x004F5BC6
    int    ProducingInfantryTypeIndex;     // +0x5654 ctor @0x004F5BCC
    int    ProducingAircraftTypeIndex;     // +0x5658 ctor @0x004F5BD2
    int    RatioAITriggerTeam;             // +0x565C ctor MOV [EBP+0x565C],0x64 @0x004F5BDD
    int    RatioTeamAircraft;              // +0x5660 ctor @0x004F5BE7
    int    RatioTeamInfantry;              // +0x5664 ctor @0x004F5BED
    int    RatioTeamBuildings;             // +0x5668 ctor @0x004F5BF3
    int    BaseDefenseTeamCount;           // +0x566C ctor @0x004F5BF9
    DropshipStruct DropshipData[3];        // +0x5670 .. 0x56F3 ctor LEA ESI @0x004F5BFF
    int    CurrentDropshipIndex;           // +0x56F4 ctor @0x004F5C22
    unsigned char HasCloakingRanges;       // +0x56F8 ctor @0x004F5C28
    ColorStruct Color;                     // +0x56F9 ctor @0x004F5C30/0x004F5C36/0x004F5C3C
    ColorStruct LaserColor;                // +0x56FC ctor @0x004F5C48/0x004F5C4E/0x004F5C54
    unsigned char align_56FF;              // +0x56FF
    BaseClass Base;                        // +0x5700 .. 0x5777 ctor LEA ECX @0x004F5C42
    unsigned char RecheckPower;            // +0x5778 ctor MOV byte,1 @0x004F5C5F
    unsigned char RecheckRadar;            // +0x5779 ctor MOV byte,1 @0x004F5C66
    unsigned char SpySatActive;            // +0x577A ctor @0x004F5C6D
    unsigned char IsBeingDrained;          // +0x577B ctor @0x004F5C73
    int    Edge;                           // +0x577C ctor @0x004F5C79
    CellStruct EMPTarget;                  // +0x5780 ctor @0x004F5C7F/0x004F5C86
    CellStruct NukeTarget;                 // +0x5784 ctor @0x004F5C8D/0x004F5C94
    unsigned int Allies;                   // +0x5788 IndexBitfield; ctor @0x004F5C9B
    CDTimerClass DamageDelayTimer;         // +0x578C ctor @0x004F5CC4/0x004F5CBE
    CDTimerClass TeamDelayTimer;           // +0x5798 ctor @0x004F5CD5/0x004F5CDB
    CDTimerClass TriggerDelayTimer;        // +0x57A4 ctor @0x004F5CE7/0x004F5CED
    CDTimerClass SpeakAttackDelayTimer;    // +0x57B0 ctor @0x004F5CFF/0x004F5CF9
    CDTimerClass SpeakPowerDelayTimer;     // +0x57BC ctor @0x004F5D0B/0x004F5D11
    CDTimerClass SpeakMoneyDelayTimer;     // +0x57C8 ctor @0x004F5D23/0x004F5D1D
    CDTimerClass SpeakMaxedDelayTimer;     // +0x57D4 ctor @0x004F5D2F/0x004F5D35
    void*  AIGeneral;                      // +0x57E0 IAIHouse*; ctor @0x004F5D3B
    unsigned int ThreatPosedEstimates[130][130]; // +0x57E4 .. 0x15FF3 ctor LEA EDI @0x004F61F6;
                                           //   0x10810 bytes, closing exactly on PlainName
    char   PlainName[21];                  // +0x15FF4 ctor MOV byte [EBP+0x15FF4],BL @0x004F5D41
    char   UINameString[33];               // +0x16009 ctor MOV byte [EBP+0x16009],BL @0x004F5D4D
    unsigned short UIName[21];             // +0x1602A wchar_t[21]; ctor MOV word [EBP+0x1602A],BX @0x004F5E46
    int    ColorSchemeIndex;               // +0x16054 ctor @0x004F5D54
    int    StartingPoint;                  // +0x16058 NOT written by the ctor (union with a CellStruct)
    unsigned int StartingAllies;           // +0x1605C NOT written by the ctor
    unsigned int unknown_16060;            // +0x16060 ctor @0x004F5D5D
    DynamicVectorClassLayout WaypointPath;       // +0x16064 ctor LEA ESI @0x004F5D47
    unsigned int unknown_1607C;            // +0x1607C ctor @0x004F5D74
    unsigned int unknown_16080;            // +0x16080 ctor @0x004F5D7A
    unsigned int unknown_16084;            // +0x16084 NOT written by the ctor
    double unused_16088;                   // +0x16088 ctor @0x004F5D85/0x004F5D8B
    double unused_16090;                   // +0x16090 ctor @0x004F5D91/0x004F5D97
    unsigned int padding_16098;            // +0x16098 NOT written by the ctor
    float  PredictionEnemyArmor;           // +0x1609C ctor @0x004F5DA2
    float  PredictionEnemyAir;             // +0x160A0 ctor @0x004F5DA8
    float  PredictionEnemyInfantry;        // +0x160A4 ctor @0x004F5DAE
    int    TotalOwnedInfantryCost;         // +0x160A8 ctor @0x004F5DB4
    int    TotalOwnedVehicleCost;          // +0x160AC ctor @0x004F5DBA
    int    TotalOwnedAircraftCost;         // +0x160B0 ctor @0x004F5DC0
    int    PowerSurplus;                   // +0x160B4 ctor @0x004F5DC6; closes the object at 0x160B8

    // Methods reached from other units (__thiscall; bodies not recovered here).
    // FUNCTION: GAMEMD 0x50DEF0 (decl; reloc) -- a cell by value through a hidden pointer, RET 4.
    Cell FUN_0050DEF0() const;
    // FUNCTION: GAMEMD 0x50DF30 (decl; reloc) -- a coordinate by value through a hidden pointer, RET 4.
    CoordStruct FUN_0050DF30() const;
    // FUNCTION: GAMEMD 0x5051E0 (decl; reloc) -- the first buildable type of a rules type list, RET 4.
    BuildingTypeClass* FUN_005051E0(const void* typeList);
    // FUNCTION: GAMEMD 0x50E000 (decl; reloc) -- takes one cell by value, RET 4.
    void FUN_0050E000(Cell cell);
    // FUNCTION: GAMEMD 0x4F9A50 (decl; reloc) -- is the other house an ally (one stack argument).
    UnitTypeClass* FUN_00505310(const DynamicVectorClass<UnitTypeClass*>& types); // GAMEMD 0x505310
    void FUN_004FC060(ObjectClass* object, bool value); // GAMEMD 0x4FC060
    float GiveTiberium(float amount, int type); // GAMEMD 0x4F9610
    bool IsAlliedWith(const HouseClass* house) const;
    // FUNCTION: GAMEMD 0x50B730 (decl; reloc) -- no arguments, bool.
    bool FUN_0050B730();
    // FUNCTION: GAMEMD 0x4F9B70 (decl; reloc) -- RET 8.
    void FUN_004F9B70(HouseClass* other, bool flag);
    // FUNCTION: GAMEMD 0x4F9F90 (decl; reloc) -- RET 8.
    void FUN_004F9F90(HouseClass* other, bool flag);
    // FUNCTION: GAMEMD 0x50C8C0 (decl; reloc)
    void FUN_0050C8C0();
    // FUNCTION: GAMEMD 0x50D290 (decl; reloc)
    void FUN_0050D290(HouseClass* other);
    // FUNCTION: GAMEMD 0x50D2D0 (decl; reloc)
    void FUN_0050D2D0(HouseClass* other);
    // FUNCTION: GAMEMD 0x50D6D0 (decl; reloc) -- takes a cell by value.
    void FUN_0050D610(); // FUNCTION: GAMEMD 0x50D610 (decl; primary RET at0x50D6C1)
    void FUN_0050D6D0(CellStruct cell);
    // FUNCTION: GAMEMD 0x50DA00 (decl; reloc) -- takes a cell by value.
    void FUN_0050DA00(CellStruct cell);
    // FUNCTION: GAMEMD 0x50DA20 (decl; reloc) -- takes a cell by value.
    void FUN_0050DA20(CellStruct cell);
    // FUNCTION: GAMEMD 0x50DFE0 (decl; reloc) -- takes a cell by value.
    void FUN_0050DFE0(CellStruct cell);
};

GG_STATIC_ASSERT(offsetof(HouseClass, TechLevel) == 0x1D4); // 0x6886B0 accesses
GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex)                 == 0x30);
GG_STATIC_ASSERT(offsetof(HouseClass, Type)                       == 0x34);
GG_STATIC_ASSERT(offsetof(HouseClass, RelatedTags)                == 0x38);
GG_STATIC_ASSERT(offsetof(HouseClass, ConYards)                   == 0x50);
GG_STATIC_ASSERT(offsetof(HouseClass, FactoryPlants)              == 0x140);
GG_STATIC_ASSERT(offsetof(HouseClass, CountResourceGatherers)     == 0x158);
GG_STATIC_ASSERT(offsetof(HouseClass, StartingUnits)              == 0x16C);
GG_STATIC_ASSERT(offsetof(HouseClass, AIDifficulty)               == 0x184);
GG_STATIC_ASSERT(offsetof(HouseClass, FirepowerMultiplier)        == 0x188);
GG_STATIC_ASSERT(offsetof(HouseClass, BuildDelay)                 == 0x1C8);
GG_STATIC_ASSERT(offsetof(HouseClass, IQLevel)                    == 0x1D0);
GG_STATIC_ASSERT(offsetof(HouseClass, AltAllies)                  == 0x1D8);
GG_STATIC_ASSERT(offsetof(HouseClass, StartingEdge)               == 0x1E0);
GG_STATIC_ASSERT(offsetof(HouseClass, AIState_1E4)                == 0x1E4);
GG_STATIC_ASSERT(offsetof(HouseClass, SideIndex)                  == 0x1E8);
GG_STATIC_ASSERT(offsetof(HouseClass, IsHumanPlayer)              == 0x1EC);
GG_STATIC_ASSERT(offsetof(HouseClass, NodeLogic_1F0)              == 0x1F0);
GG_STATIC_ASSERT(offsetof(HouseClass, ShipYardConst_1F1)          == 0x1F1);
GG_STATIC_ASSERT(offsetof(HouseClass, RecheckTechTree)            == 0x1FC);
GG_STATIC_ASSERT(offsetof(HouseClass, IPAddress)                  == 0x200);
GG_STATIC_ASSERT(offsetof(HouseClass, SelectedPathIndex)          == 0x20C);
GG_STATIC_ASSERT(offsetof(HouseClass, PlanningPaths)              == 0x210);
GG_STATIC_ASSERT(offsetof(HouseClass, Visionary)                  == 0x240);
GG_STATIC_ASSERT(offsetof(HouseClass, IsToLook)                   == 0x24B);
GG_STATIC_ASSERT(offsetof(HouseClass, IQLevel2)                   == 0x24C);
GG_STATIC_ASSERT(offsetof(HouseClass, AIMode)                     == 0x250);
GG_STATIC_ASSERT(offsetof(HouseClass, Supers)                     == 0x254);
GG_STATIC_ASSERT(offsetof(HouseClass, LastBuiltBuildingType)      == 0x26C);
GG_STATIC_ASSERT(offsetof(HouseClass, AllowWinBlocks)             == 0x27C);
GG_STATIC_ASSERT(offsetof(HouseClass, RepairTimer)                == 0x280);
GG_STATIC_ASSERT(offsetof(HouseClass, RadarBlackoutTimer)         == 0x2B0);
GG_STATIC_ASSERT(offsetof(HouseClass, Side2TechInfiltrated)       == 0x2BC);
GG_STATIC_ASSERT(offsetof(HouseClass, InfantryAltOwner)           == 0x2C4);
GG_STATIC_ASSERT(offsetof(HouseClass, AirportDocks)               == 0x2D4);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedAircraft)              == 0x2F8);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedTiberium)              == 0x2FC);
GG_STATIC_ASSERT(offsetof(HouseClass, Balance)                    == 0x30C);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedWeed)                  == 0x314);
GG_STATIC_ASSERT(offsetof(HouseClass, unknown_324)                == 0x324);
GG_STATIC_ASSERT(offsetof(HouseClass, BuiltAircraftTypes)         == 0x328);
GG_STATIC_ASSERT(offsetof(HouseClass, CollectedCrates)            == 0x4B70);
GG_STATIC_ASSERT(offsetof(HouseClass, NumAirpads)                 == 0x5378);
GG_STATIC_ASSERT(offsetof(HouseClass, CostInfantryMult)           == 0x5390);
GG_STATIC_ASSERT(offsetof(HouseClass, PowerOutput)                == 0x53A4);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForAircraft)        == 0x53AC);
GG_STATIC_ASSERT(offsetof(HouseClass, AircraftType_53D0)          == 0x53D0);
GG_STATIC_ASSERT(offsetof(HouseClass, DefenseType_53D8)           == 0x53D8);
GG_STATIC_ASSERT(offsetof(HouseClass, OurFlagCarrier)             == 0x53DC);
GG_STATIC_ASSERT(offsetof(HouseClass, OurFlagCoords)              == 0x53E0);
GG_STATIC_ASSERT(offsetof(HouseClass, KilledUnitsOfHouses)        == 0x53E4);
GG_STATIC_ASSERT(offsetof(HouseClass, TotalKilledUnits)           == 0x5434);
GG_STATIC_ASSERT(offsetof(HouseClass, KilledBuildingsOfHouses)    == 0x5438);
GG_STATIC_ASSERT(offsetof(HouseClass, TotalKilledBuildings)       == 0x5488);
GG_STATIC_ASSERT(offsetof(HouseClass, WhoLastHurtMe)              == 0x548C);
GG_STATIC_ASSERT(offsetof(HouseClass, Radius)                     == 0x5498);
GG_STATIC_ASSERT(offsetof(HouseClass, ZoneInfos)                  == 0x549C);
GG_STATIC_ASSERT(offsetof(HouseClass, LATime)                     == 0x54D8);
GG_STATIC_ASSERT(offsetof(HouseClass, PreferredTargetType)        == 0x54EC);
GG_STATIC_ASSERT(offsetof(HouseClass, PreferredDefensiveCellStartTime) == 0x54FC);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedBuildingTypes)         == 0x5500);
GG_STATIC_ASSERT(offsetof(HouseClass, FactoryProducedAircraftTypes) == 0x55DC);
GG_STATIC_ASSERT(offsetof(HouseClass, AttackTimer)                == 0x55F0);
GG_STATIC_ASSERT(offsetof(HouseClass, EnemyHouseIndex)            == 0x5600);
GG_STATIC_ASSERT(offsetof(HouseClass, AngerNodes)                 == 0x5604);
GG_STATIC_ASSERT(offsetof(HouseClass, ScoutNodes)                 == 0x561C);
GG_STATIC_ASSERT(offsetof(HouseClass, AITimer)                    == 0x5634);
GG_STATIC_ASSERT(offsetof(HouseClass, Unknown_Timer_5640)         == 0x5640);
GG_STATIC_ASSERT(offsetof(HouseClass, RatioAITriggerTeam)         == 0x565C);
GG_STATIC_ASSERT(offsetof(HouseClass, DropshipData)               == 0x5670);
GG_STATIC_ASSERT(offsetof(HouseClass, CurrentDropshipIndex)       == 0x56F4);
GG_STATIC_ASSERT(offsetof(HouseClass, Color)                      == 0x56F9);
GG_STATIC_ASSERT(offsetof(HouseClass, LaserColor)                 == 0x56FC);
GG_STATIC_ASSERT(offsetof(HouseClass, Base)                       == 0x5700);
GG_STATIC_ASSERT(offsetof(HouseClass, RecheckPower)               == 0x5778);
GG_STATIC_ASSERT(offsetof(HouseClass, Edge)                       == 0x577C);
GG_STATIC_ASSERT(offsetof(HouseClass, EMPTarget)                  == 0x5780);
GG_STATIC_ASSERT(offsetof(HouseClass, Allies)                     == 0x5788);
GG_STATIC_ASSERT(offsetof(HouseClass, DamageDelayTimer)           == 0x578C);
GG_STATIC_ASSERT(offsetof(HouseClass, SpeakMaxedDelayTimer)       == 0x57D4);
GG_STATIC_ASSERT(offsetof(HouseClass, AIGeneral)                  == 0x57E0);
GG_STATIC_ASSERT(offsetof(HouseClass, ThreatPosedEstimates)       == 0x57E4);
GG_STATIC_ASSERT(offsetof(HouseClass, PlainName)                  == 0x15FF4);
GG_STATIC_ASSERT(offsetof(HouseClass, UINameString)               == 0x16009);
GG_STATIC_ASSERT(offsetof(HouseClass, UIName)                     == 0x1602A);
GG_STATIC_ASSERT(offsetof(HouseClass, ColorSchemeIndex)           == 0x16054);
GG_STATIC_ASSERT(offsetof(HouseClass, unknown_16060)              == 0x16060);
GG_STATIC_ASSERT(offsetof(HouseClass, WaypointPath)               == 0x16064);
GG_STATIC_ASSERT(offsetof(HouseClass, unknown_1607C)              == 0x1607C);
GG_STATIC_ASSERT(offsetof(HouseClass, unused_16088)               == 0x16088);
GG_STATIC_ASSERT(offsetof(HouseClass, unused_16090)               == 0x16090);
GG_STATIC_ASSERT(offsetof(HouseClass, PredictionEnemyArmor)       == 0x1609C);
GG_STATIC_ASSERT(offsetof(HouseClass, TotalOwnedInfantryCost)     == 0x160A8);
GG_STATIC_ASSERT(offsetof(HouseClass, PowerSurplus)               == 0x160B4);
GG_STATIC_ASSERT(sizeof(HouseClass)                               == 0x160B8);

// VTABLE: GAMEMD 0x007EA8A0  HouseClass            (COL base 0x00)
// VTABLE: GAMEMD 0x007EA884  HouseClass::(+0x04)   (COL base 0x04)
// VTABLE: GAMEMD 0x007EA87C  HouseClass::(+0x08)   (COL base 0x08)
// VTABLE: GAMEMD 0x007EA874  HouseClass::(+0x0C)   (COL base 0x0C)
// VTABLE: GAMEMD 0x007EA834  HouseClass::(+0x24)   (COL base 0x24)
// VTABLE: GAMEMD 0x007EA80C  HouseClass::(+0x28)   (COL base 0x28)
// VTABLE: GAMEMD 0x007EA7F4  HouseClass::(+0x2C)   (COL base 0x2C)

#endif  // GG_MATCH_LAYOUT_HOUSE_CLASS_H

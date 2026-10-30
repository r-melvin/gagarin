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

class WaypointPathClass;
class WaypointClass;
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "mission_class.h"    // CDTimerClass
#include "techno_class.h"     // StorageClass
#include "foot_class.h"       // CellStruct
#include "vector_class.h"     // DynamicVectorClass
#include "components.h"       // ColorStruct
#include "../core/vector_class.h"
class BuildingClass;
class TagClass;
class SuperClass;
class CCINIClass;
#include "anger_scout_struct.h"

// --- opaque blocks whose SIZE is proven but whose fields are not named -------
// Each size is proven by closure between two confirmed neighbours in the ctor.

#include "unit_tracker_class.h"

// CounterClass — 0x14. Twelve of them run 0x5500..0x55F0 at stride 0x14
// (ctor LEA ECX sites 0x004F5AAB..0x004F5B2E).
#ifndef GG_MATCH_LAYOUT_COUNTERCLASS_DEFINED
#define GG_MATCH_LAYOUT_COUNTERCLASS_DEFINED
class CounterClass : public VectorClass<int>
{
public:
    // External native49F9B0; RTTI7FF690 proves the zero-offset VectorClass<int> base.
    CounterClass();
    // Native slot3 at7E5C60 points49FB40; remaining six slots are inherited.
    virtual void Clear();
    // Native ctor stores zero at+10;49FB60 reads the cached total here.
    int Total;
    // Declarations from existing House Load/Save/count call sites.
    int GetCount(int typeIndex);
    // Native49FB70 returns the stream HRESULT or zero; ECX receiver, RET4.
    HRESULT Save(IStream* stream);
    // Native49FBE0: ECX receiver, stream argument, HRESULT result, RET4.
    HRESULT Load(IStream* stream);
    // FUNCTION: GAMEMD 0x49FB60 (decl; reloc) -- the sum over every type (ECX = the counter, no arguments).
    int FUN_0049FB60() const;
    // FUNCTION: GAMEMD 0x49FA00 (decl) -- grow to hold the index, bump it and the total; ECX receiver, RET4.
    int FUN_0049FA00(int index);
    // FUNCTION: GAMEMD 0x49FA70 (decl) -- as 0x49FA00 but decrements; ECX receiver, RET4.
    int FUN_0049FA70(int index);
    // FUNCTION: GAMEMD 0x49FAE0 (decl) -- grow to hold the index and read it; ECX receiver, RET4.
    int FUN_0049FAE0(int index);
    // FUNCTION: GAMEMD 0x49FC80 (decl) -- grow to hold the index; ECX receiver, RET4.
    bool FUN_0049FC80(int index);
};
GG_STATIC_ASSERT(offsetof(CounterClass, Total) == 0x10);
GG_STATIC_ASSERT(sizeof(CounterClass) == 0x14);
#endif

// DropshipStruct — 0x2C. Three of them run 0x5670..0x56F4 (ctor LEA ESI
// @0x004F5BFF; next confirmed member CurrentDropshipIndex @0x56F4).
#ifndef GG_MATCH_LAYOUT_DROPSHIPSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_DROPSHIPSTRUCT_DEFINED
struct DropshipStruct {
    // Declaration: GAMEMD 0x4B69B0 -- native frame/delay/flag initialization.
    DropshipStruct();
    // Declaration: GAMEMD 0x4B6BB0 -- called by503040 with this member receiver.
    void Swizzle();
    unsigned char unknown_00[0x2C];
};
GG_STATIC_ASSERT(sizeof(DropshipStruct) == 0x2C);
#endif

// BaseClass — 0x78, at 0x5700..0x5778 (ctor LEA ECX @0x004F5C42; next
// confirmed member RecheckPower @0x5778).
#ifndef GG_MATCH_LAYOUT_BASECLASS_DEFINED
#define GG_MATCH_LAYOUT_BASECLASS_DEFINED
class BaseClass {
public:
    // External native constructor42E6F0 installs7E3880. RTTI has no base.
    BaseClass();
    // Slots0/1: receiver and stream are stack arguments, RET8.
    virtual void __stdcall LoadFromStream(IStream* stream);
    virtual void __stdcall SaveToStream(IStream* stream);
    // Slot2: ECX receiver and one checksum pointer, RET4.
    virtual void ComputeCrc(Obj_004A1D30* crc);
    unsigned char unknown_04[0x70];
    HouseClass* unknown_74; // 0x6869DB writes containing House at +0x5774
    int FailedToPlaceNode(class BaseNodeClass* Node);   // GAMEMD 0x42F380
    // FUNCTION: GAMEMD 0x42F260 -- one stack argument (RET 4); BuildingClass 0x440580 passes itself (decl; reloc).
    void FUN_0042F260(BuildingClass* building);
    // FUNCTION: GAMEMD 0x42EBE0 (decl; reloc) -- reads the base layout of a house's section, RET 8.
    void FUN_0042EBE0(CCINIClass* ini, const char* section);
};
GG_STATIC_ASSERT(offsetof(BaseClass, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(BaseClass, unknown_74) == 0x74);
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
class TechnoTypeClass;
class UnitTypeClass; class UnitClass; class FactoryClass; class TeamTypeClass;
template<class T> class DynamicVectorClass;

#include <ocidl.h>   // IConnectionPointContainer (VC98 SDK, LIBRARY)

#include "house_interfaces.h"   // IHouse, IPublicHouse

// Bases per retail CHD (COL 0x802A28): IHouse mdisp 0x24, IPublicHouse 0x28,
// IConnectionPointContainer 0x2C.
class HouseClass : public AbstractClass, public IHouse, public IPublicHouse, public IConnectionPointContainer
{
public:
    // FUNCTION: GAMEMD 0x4F9A90 (decl; reloc), ECX receiver, one AbstractClass*.
    bool FUN_004F9A90(AbstractClass* object);
    // FUNCTION: GAMEMD 0x4FDCE0 - runs IHouse slots 13 and 14 when the argument is 4.
    bool FUN_004FDCE0(int arg);
    // FUNCTION: GAMEMD 0x502100 / 0x502130 - apply FUN_004F9B70 / FUN_004F9F90 to an object's house.
    void FUN_00502100(AbstractClass* object, bool flag);
    void FUN_00502130(AbstractClass* object, bool flag);
    // FUNCTION: GAMEMD 0x4F9F70 - applies FUN_004F9F90 to the house at the given array index.
    void FUN_004F9F70(int index, bool flag);
    // FUNCTION: GAMEMD 0x4FCE00 - stores the starting credits and balance (third argument) and the colour index (first).
    void FUN_004FCE00(int colorIndex, int unused, int credits);
    // Declaration: GAMEMD 0x4F54A0 -- recovered body currently on legacy owner.
    HouseClass(HouseTypeClass* type);
    // Declaration: GAMEMD 0x4F5190 -- forwards this opaque argument to4101C0.
    HouseClass(const AbstractNoInit& noInit);
    // External ordinary destructor: the native deleting provider50E380 calls4F7140.
    virtual ~HouseClass();
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);
    virtual ULONG __stdcall AddRef();
    virtual ULONG __stdcall Release();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall EnumConnectionPoints(IEnumConnectionPoints** ppEnum);
    virtual HRESULT __stdcall FindConnectionPoint(REFIID riid, IConnectionPoint** ppCP);
    virtual int vf_11();
    virtual int vf_12();
    virtual int vf_16();
    virtual void vf_13(Obj_004A1D30* crc);

    // Existing interface slots in native order; placeholder identities are retained.
    virtual HRESULT __stdcall vf_03();
    virtual BSTR __stdcall vf_04();
    virtual IUnknown* __stdcall vf_05();
    virtual HRESULT __stdcall vf_06();
    virtual HRESULT __stdcall vf_07();
    virtual HRESULT __stdcall IHouse_vf_08();
    virtual HRESULT __stdcall vf_09();
    virtual HRESULT __stdcall vf_10(int a1);
    virtual HRESULT __stdcall vf_11(int a1);
    virtual void* __stdcall vf_12(void* a1);
    virtual HRESULT __stdcall vf_13();
    virtual HRESULT __stdcall IHouse_vf_14();
    virtual HRESULT __stdcall IPublicHouse_vf_05(int a1);
    virtual HRESULT __stdcall IPublicHouse_vf_06(int a1);
    virtual void* __stdcall IPublicHouse_vf_07(void* a1);
    virtual bool __stdcall IPublicHouse_vf_08();

    // Coordinate helper expanded by native4F6BC0/4F6D10.
    CellStruct HouseBaseCell() const;

    // Declaration: GAMEMD 0x501640 -- ECX house at 0x64CA0D.
    void AllyAIHouses();

    // Declaration: GAMEMD 0x4FB920
    void FUN_004FB920();
    // FUNCTION: GAMEMD 0x502D30 (decl; reloc) -- first house whose type has this country index; ECX carries it.
    static HouseClass* FindByCountryIndex(int country);
    // FUNCTION: GAMEMD 0x4F9790 (decl; reloc) -- one stack argument.
    void FUN_004F9790(int unknownStackArg0);
    // FUNCTION: GAMEMD 0x4F9950 (decl; reloc) -- one stack argument.
    void FUN_004F9950(int unknownStackArg0);
    // FUNCTION: GAMEMD 0x4FCE30 (decl; reloc)
    double FUN_004FCE30();
    // FUNCTION: GAMEMD 0x4F9750 (decl; reloc) -- matched in economy/house_class_misc_methods.cpp.
    WaypointPathClass* EnsurePlanningPathExists(int index); // 0x504740, RET4
    WaypointClass* GetPlanningWaypointAt(const CellStruct* cell); // 0x5023B0
    bool GetPlanningWaypointProperties(WaypointClass*, int*, unsigned char*); // 0x502460
    double GetWeedStoragePercentage();
    // FUNCTION: GAMEMD 0x509140 (decl; reloc) -- (factory kind, naval, category), RET 0xC;
    // BuildingClass 0x452360 passes Type->Factory, Type->Naval, 0.
    void Update_FactoriesQueues(int factoryOf, bool isNaval, int buildCat);
    // CALLEE: GAMEMD 0x4F7870 -- native 0x5F79A3 passes this ObjectTypeClass
    // pointer and two Boolean arguments, testing the signed EAX result.
    int FUN_004F7870(ObjectTypeClass* type, bool a2, bool a3);
    // FUNCTION: GAMEMD 0x50B6F0 (decl; reloc)
    bool IsControlledByCurrentPlayer() const;
    // FUNCTION: GAMEMD 0x50B730 (decl; reloc)
    bool IsControlledByHuman() const;
    // Nested pointer spelling confirmed by RTTI at tables 0x7EA964/0x7EA944.
    // Native Load stores DWORD0/WORD4/WORD6 into an eight-byte allocation.
    struct StartingTechnoStruct
    {
        ObjectTypeClass* Type;   // +0x00 the type to re-create (0x50D440 asks it to create an object)
        CellStruct Cell;         // +0x04 the cell it starts on
    };
    struct BuildChoiceClass;    // RTTI: .?AUBuildChoiceClass@HouseClass@@ (vector element)
    // +0x24/+0x28/+0x2C: IHouse, IPublicHouse, IConnectionPointContainer vptrs
    //   (ctor stores 0x7EA834 @0x004F5DE8, 0x7EA80C @0x004F5DEF, 0x7EA7F4 @0x004F5DFB).
    int    ArrayIndex;                     // +0x30 ctor MOV [EBP+0x30],-1 @0x004F54B8
    HouseTypeClass* Type;                  // +0x34 ctor MOV [EBP+0x34],EAX(=arg) @0x004F54C2
    DynamicVectorClass<TagClass*> RelatedTags;                 // +0x38  ctor LEA ESI @0x004F54B4 (vptr 0x7EA5A4)
    DynamicVectorClass<BuildingClass*> ConYards;                    // +0x50  ctor LEA ESI @0x004F54DB
    DynamicVectorClass<BuildingClass*> Buildings;                   // +0x68  ctor LEA ESI @0x004F54F3
    DynamicVectorClass<BuildingClass*> UnitRepairStations;          // +0x80  ctor LEA ESI @0x004F550B
    DynamicVectorClass<BuildingClass*> Grinders;                    // +0x98  ctor LEA ESI @0x004F5526
    DynamicVectorClass<BuildingClass*> Absorbers;                   // +0xB0  ctor LEA ESI @0x004F5541
    DynamicVectorClass<BuildingClass*> Bunkers;                     // +0xC8  ctor LEA ESI @0x004F555C
    DynamicVectorClass<BuildingClass*> Occupiables;                 // +0xE0  ctor LEA ESI @0x004F5577
    DynamicVectorClass<BuildingClass*> CloningVats;                 // +0xF8  ctor LEA ESI @0x004F5592
    DynamicVectorClass<BuildingClass*> SecretLabs;                  // +0x110 ctor LEA ESI @0x004F55AD
    DynamicVectorClass<BuildingClass*> PsychicDetectionBuildings;   // +0x128 ctor LEA ESI @0x004F55C8
    DynamicVectorClass<BuildingClass*> FactoryPlants;               // +0x140 ctor LEA ESI @0x004F55E3
    int    CountResourceGatherers;         // +0x158 ctor @0x004F55FE
    int    CountResourceDestinations;      // +0x15C ctor @0x004F5604
    int    CountWarfactories;              // +0x160 ctor @0x004F5610
    int    InfantrySelfHeal;               // +0x164 ctor @0x004F5617
    int    UnitsSelfHeal;                  // +0x168 ctor @0x004F5620
    DynamicVectorClass<StartingTechnoStruct*> StartingUnits;      // +0x16C ctor LEA ESI @0x004F560A
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
    bool IsHumanPlayer;           // +0x1EC ctor @0x004F56E5
    unsigned char IsInPlayerControl;       // +0x1ED ctor @0x004F56EB
    bool Production;              // +0x1EE ctor @0x004F56F1
    bool AutocreateAllowed;       // +0x1EF ctor @0x004F56F7
    unsigned char NodeLogic_1F0;           // +0x1F0 ctor MOV byte,1 @0x004F56FD (name anchor confirmed)
    unsigned char ShipYardConst_1F1;       // +0x1F1 ctor @0x004F5704 (name anchor confirmed)
    bool AITriggersActive;        // +0x1F2 ctor @0x004F570A
    unsigned char AutoBaseBuilding;        // +0x1F3 ctor @0x004F5710
    unsigned char DiscoveredByPlayer;      // +0x1F4 ctor @0x004F5716
    bool Defeated;                // +0x1F5 ctor @0x004F571C
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
    WaypointPathClass* PlanningPaths[12];              // +0x210 .. 0x23F ctor LEA EDI @0x004F643B (12 dwords = 0x30)
    signed char   Visionary;               // +0x240 ctor @0x004F5765
    bool MapIsClear;              // +0x241 ctor @0x004F576B
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
    DynamicVectorClass<SuperClass*> Supers;             // +0x254 ctor LEA ESI @0x004F57B4
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
    FactoryClass* Primary_ForAircraft;            // +0x53AC ctor @0x004F59AA
    FactoryClass* Primary_ForInfantry;            // +0x53B0 ctor @0x004F59B0
    FactoryClass* Primary_ForVehicles;            // +0x53B4 ctor @0x004F59B6
    FactoryClass* Primary_ForShips;               // +0x53B8 ctor @0x004F59BC
    FactoryClass* Primary_ForBuildings;           // +0x53BC ctor @0x004F59C2
    FactoryClass* Primary_Unused1;                // +0x53C0 ctor @0x004F59C8
    FactoryClass* Primary_Unused2;                // +0x53C4 ctor @0x004F59CE
    FactoryClass* Primary_Unused3;                // +0x53C8 ctor @0x004F59D4
    FactoryClass* Primary_ForDefenses;            // +0x53CC ctor @0x004F59DA
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
    AbstractClass* OurFlagCarrier;         // +0x53DC the carrying UnitClass, or the CellClass the dropped flag lies in; ctor @0x004F5A16
    CellStruct OurFlagCoords;              // +0x53E0 ctor word stores @0x004F5A1C/0x004F5A23
    int    KilledUnitsOfHouses[20];        // +0x53E4 .. 0x5433 ctor LEA EDI @0x004F62A1
    int    TotalKilledUnits;               // +0x5434 ctor @0x004F5A2A
    int    KilledBuildingsOfHouses[20];    // +0x5438 .. 0x5487 ctor LEA EDI @0x004F62AE
    int    TotalKilledBuildings;           // +0x5488 ctor @0x004F5A30
    int    WhoLastHurtMe;                  // +0x548C ctor @0x004F5A36
    Cell   BaseSpawnCell;                  // +0x5490 ctor @0x004F5A41
    Cell   BaseCenter;                     // +0x5494 ctor @0x004F5A4D
    int    Radius;                         // +0x5498 ctor @0x004F5A53
    ZoneInfoStruct ZoneInfos[5];           // +0x549C .. 0x54D7 bounded, not written — see note
    int    LATime;                         // +0x54D8 ctor @0x004F5A59
    int    LAEnemy;                        // +0x54DC ctor @0x004F5A5F
    BuildingClass* ToCapture;              // +0x54E0 ctor @0x004F5A65
    unsigned int RadarVisibleTo;           // +0x54E4 IndexBitfield; ctor @0x004F5A6B
    int    PointTotal;                     // +0x54E8 ctor @0x004F5A71
    int    PreferredTargetType;            // +0x54EC ctor MOV [EBP+0x54EC],1 @0x004F5A77
    Cell   PreferredTargetCell;            // +0x54F0 ctor @0x004F5A81/0x004F5A88
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
    DynamicVectorClass<AngerStruct> AngerNodes;         // +0x5604 ctor LEA ECX @0x004F5B52
    DynamicVectorClass<ScoutStruct> ScoutNodes;         // +0x561C ctor LEA ECX @0x004F5B65
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
    IUnknown* AIGeneral;                      // +0x57E0 nativeSave queries IUnknown slot0; ctor @0x004F5D3B
    unsigned int ThreatPosedEstimates[130][130]; // +0x57E4 .. 0x15FF3 ctor LEA EDI @0x004F61F6;
                                           //   0x10810 bytes, closing exactly on PlainName
    char   PlainName[21];                  // +0x15FF4 ctor MOV byte [EBP+0x15FF4],BL @0x004F5D41
    char   UINameString[33];               // +0x16009 ctor MOV byte [EBP+0x16009],BL @0x004F5D4D
    unsigned short UIName[21];             // +0x1602A wchar_t[21]; ctor MOV word [EBP+0x1602A],BX @0x004F5E46
    int    ColorSchemeIndex;               // +0x16054 ctor @0x004F5D54
    int    StartingPoint;                  // +0x16058 NOT written by the ctor (union with a CellStruct)
    unsigned int StartingAllies;           // +0x1605C NOT written by the ctor
    unsigned int unknown_16060;            // +0x16060 ctor @0x004F5D5D
    DynamicVectorClass<IConnectionPoint*> ConnectionPoints;       // +0x16064 ctor LEA ESI @0x004F5D47
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
    // FUNCTION: GAMEMD 0x50DAA0 -- StartingEdge when it is 0..3, else 0.
    int FUN_0050DAA0() const;
    // FUNCTION: GAMEMD 0x50DAC0 -- the map edge opposite Edge (0->2, 1->3, 2->0, 3->1), else 0.
    int FUN_0050DAC0() const;
    // FUNCTION: GAMEMD 0x4F9A50 (decl; reloc) -- is the other house an ally (one stack argument).
    UnitTypeClass* FUN_00505310(const DynamicVectorClass<const UnitTypeClass*>& types); // GAMEMD 0x505310
    void FUN_004FC060(ObjectClass* object, bool value); // GAMEMD 0x4FC060
    float GiveTiberium(float amount, int type); // GAMEMD 0x4F9610
    bool IsAlliedWith(const HouseClass* house) const;
    float FUN_0050C160() const; // GAMEMD 0x50C160
    // FUNCTION: GAMEMD 0x50B730 (decl; reloc) -- no arguments, bool.
    bool FUN_0050B730();
    // FUNCTION: GAMEMD 0x50BDF0 -- ECX=House, one TechnoType* stack argument,
    // float result in ST0, RET 4. Native body switches on slot 11.
    float FUN_0050BDF0(TechnoTypeClass* type);
    // FUNCTION: GAMEMD 0x50BEB0 -- same native ABI as 0x50BDF0.
    float FUN_0050BEB0(TechnoTypeClass* type);
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
    // FUNCTION: GAMEMD 0x50D250 (decl) -- hand a packed short pair to every base node, last to first; RET 4.
    void FUN_0050D250(unsigned delta);
    // FUNCTION: GAMEMD 0x4FA2E0 (decl) -- spread a signed amount over nine threat cells; RET 8.
    void FUN_004FA2E0(int index, int amount);
    // FUNCTION: GAMEMD 0x4FBD00 (decl) -- any other non-allied house with that building type active; RET 4.
    bool FUN_004FBD00(int typeIndex);
    // FUNCTION: GAMEMD 0x4FBD80 (decl) -- the type object this house is producing for an RTTI class; RET 8.
    void* FUN_004FBD80(int rtti, int unused);
    // FUNCTION: GAMEMD 0x5005B0 (decl) -- set the per-class flag for an RTTI class; RET 0xC.
    void FUN_005005B0(int rtti, bool naval, int kind);
    // FUNCTION: GAMEMD 0x500660 (decl) -- clear the per-class flag; RET 0xC.
    void FUN_00500660(int rtti, bool naval, int kind);
    // FUNCTION: GAMEMD 0x500700 (decl) -- read the per-class flag; RET 0xC.
    unsigned char FUN_00500700(int rtti, bool naval, int kind);
    // FUNCTION: GAMEMD 0x5007A0 (decl) -- store a value into the per-class flag; RET 0x10.
    void FUN_005007A0(int rtti, bool naval, int kind, bool value);
    // FUNCTION: GAMEMD 0x500910 (decl) -- the factory count for an RTTI class; RET 8.
    int FUN_00500910(int rtti, bool naval);
    // FUNCTION: GAMEMD 0x4FD940 (decl) -- 4 when no live, on-map building makes a factory type; else 0.
    int FUN_004FD940();
    // FUNCTION: GAMEMD 0x4F9700 (decl) -- add one unit of a tiberium type, up to `count` times, while below capacity; RET 8.
    void FUN_004F9700(int count, int index);
    // FUNCTION: GAMEMD 0x4F9670 (decl) -- the placed building with the most free storage room, or null.
    BuildingClass* FUN_004F9670();
    // FUNCTION: GAMEMD 0x50D6D0 (decl; reloc) -- takes a cell by value.
    void FUN_0050D610(); // FUNCTION: GAMEMD 0x50D610 (decl; primary RET at0x50D6C1)
    void MarkScoutNode(HouseClass* house);                    // FUNCTION: GAMEMD 0x504860
    void AddStartingUnit(void* type, int cell);               // FUNCTION: GAMEMD 0x50D560
    void FreeStartingUnits();                                 // FUNCTION: GAMEMD 0x50D5D0
    void RespawnStartingForces();                             // FUNCTION: GAMEMD 0x50D440
    float FUN_0050C050(TechnoTypeClass* type);                // FUNCTION: GAMEMD 0x50C050
    float FUN_0050C0A0(TechnoTypeClass* type);                // FUNCTION: GAMEMD 0x50C0A0
    void FUN_0050D6D0(CellStruct cell);
    // FUNCTION: GAMEMD 0x50DA00 (decl; reloc) -- takes a cell by value.
    void FUN_0050DA00(CellStruct cell);
    // FUNCTION: GAMEMD 0x50DA20 (decl; reloc) -- takes a cell by value.
    void FUN_0050DA20(CellStruct cell);
    // FUNCTION: GAMEMD 0x50DFE0 (decl; reloc) -- takes a cell by value.
    void FUN_0050DFE0(CellStruct cell);

    // Consolidated from the per-TU views (ODR); named members, addresses beside each.
    static HouseClass* FindByPlayerAt(int at);                  // 0x510ED0
    bool Fire_SW(int index, const CellStruct& cell);            // 0x4FAE50
    void FUN_004FAF00(SuperClass* sw, const CellStruct& cell);  // 0x4FAF00 (decl; reloc)
    bool CanExtendSelectedPlanningPath();                       // 0x5090F0
    bool SelectPlanningWaypoint(const WaypointClass* wp);       // 0x502290
    int FindEmptyPlanningPath();                                // 0x5090A0
    bool IsPlanningCellFreeOfOtherPaths(const CellStruct* cell); // 0x5022F0
    void AddPlanningWaypoint(const WaypointClass* wp);          // 0x502160
    void SDDTORAllAndTriggers();                                // 0x4FB920
    int BeginProduction(int rtti, int id, unsigned char naval, int flag); // 0x4FA350 (RET 0x10)
    void GiveMoney(int amount);                                 // 0x4F9950
    void MakeAlly(int houseIndex, bool announce);               // 0x4F9B50
    void MakeAlly(HouseClass* who, bool announce);              // 0x4F9B70
    void ReshroudMap();                                         // 0x50BD10
    int GetInfSelfHealStep() const;                             // 0x50D9E0
    int GetUnitSelfHealStep() const;                            // 0x50D9F0
    bool GainedPoweredCenter(TechnoTypeClass* type);            // 0x50E1B0
    bool IsAlliedWith(int idxHouse) const;                      // 0x4F9A10
    bool IsAlliedWith(ObjectClass const* pObject) const;        // 0x4F9A90
    float GetArmorMultiplier(TechnoClass* subject);             // 0x50BD30
    void DestroyAll();                                          // 0x4FC6D0
    void DestroyAllBuildings();                                 // 0x4FC790
    void DestroyAllNonBuildingsNonNaval();                      // 0x4FC820
    void DestroyAllNonBuildingsNaval();                         // 0x4FC8D0
    void FUN_004FF700(TechnoClass* techno);                     // 0x4FF700
    char PickedUpFlag(UnitClass* Who, bool dwUnk);     // 0x4FC060
    bool UpdateFlagCoords(AbstractClass* obj, bool clearCell);    // 0x4FBE40 (RET 8)
    void AcquiredThreatNode();                                  // 0x509130
    bool IonSensitivesShouldBeOffline() const;                  // 0x53A130
    // FUNCTION: GAMEMD 0x504790 (decl; reloc) -- adds to the anger of `house`'s node and re-picks the enemy.
    void UpdateAngerNodes(int scoreAdd, HouseClass* house);
    // FUNCTION: GAMEMD 0x5093C0 -- clears the anger of `house`'s node.
    void FUN_005093C0(HouseClass* house);
    void ForceEnd();                                            // 0x4FCDC0
    unsigned char Win(bool savour);                             // 0x4FC9E0 (decl; reloc)
    bool CanOverpower(TechnoClass* pTarget) const;              // 0x4F9AF0
    void Cheer();                                               // 0x50C8C0
    double GetPowerPercentage() const;                          // 0x4FCE30
    void CreatePowerOutage(int duration);                       // 0x50BC90
    void CreateRadarOutage(int duration);                       // 0x50BCD0
    double GetStoragePercentage();                              // 0x4F6E70
    // FUNCTION: GAMEMD 0x5095D0 (decl; reloc) -- how many live teams of this type the house fields.
    int FUN_005095D0(TeamTypeClass* type);
    // FUNCTION: GAMEMD 0x509EC0 -- fires the given super weapon at the preferred defensive cell.
    void FUN_00509EC0(SuperClass* super);
    // FUNCTION: GAMEMD 0x5092F0 -- marks the radar visible to `house` and refreshes the map for the local player.
    void FUN_005092F0(HouseClass* house);
    // FUNCTION: GAMEMD 0x50E010 -- a powering centre is back; the first one reactivates the technos of `type`.
    void FUN_0050E010(TechnoTypeClass* type);
    // FUNCTION: GAMEMD 0x50E280 -- reactivates every on-map techno of this house whose type is `type`.
    void FUN_0050E280(TechnoTypeClass* type);
    // FUNCTION: GAMEMD 0x4F9370 -- updates every super weapon; the local player is told when one became ready.
    void FUN_004F9370();
    // FUNCTION: GAMEMD 0x4FCBD0 -- the counterpart of Win: clears IsWinner and settles IsGameOver/IsLoser; RET 4.
    unsigned char Lose(bool savour);
    // FUNCTION: GAMEMD 0x4F93E0 (decl; reloc) -- takes the building by pointer; RET 4.
    void FUN_004F93E0(void* building);
    // FUNCTION: GAMEMD 0x50E0E0 -- one powering centre is gone; at zero the technos of `type` are deactivated; RET 4.
    void LostPoweredCenter(TechnoTypeClass* type);
    // FUNCTION: GAMEMD 0x500510 -- the primary factory for an RTTI class (naval picks ships over vehicles, combat picks defences over buildings); RET 0xC.
    FactoryClass* GetPrimaryFactory(int absID, bool naval, int buildCat) const;
    // FUNCTION: GAMEMD 0x50D170 -- picks a super-weapon target cell of the given target type from a team's threat search; the "no cell" sentinel when none.
    Cell PickTargetByType(int targetType);
    // FUNCTION: GAMEMD 0x4F9970 -- redraws every silo building when the tiberium fill level moves a quarter step.
    void UpdateAllSilos(int prevStorage, int prevTotalStorage);
    // FUNCTION: GAMEMD 0x50DA10 -- resets the preferred target cell to the "no cell" sentinel.
    void FUN_0050DA10();
    // FUNCTION: GAMEMD 0x50DA50 -- resets both preferred defensive cells to the sentinel and the start time to -100.
    void FUN_0050DA50();
    // FUNCTION: GAMEMD 0x50DA80 -- Edge when it is 0..3, else 0.
    int FUN_0050DA80() const;
    // FUNCTION: GAMEMD 0x50DFF0 -- resets the base centre to the "no cell" sentinel.
    void FUN_0050DFF0();
    // FUNCTION: GAMEMD 0x50CBF0 (decl; reloc) -- picks an ion-cannon target cell; hidden result pointer, no stack arguments.
    Cell PickIonCannonTarget();
    // FUNCTION: GAMEMD 0x509E00 -- fires the lightning storm at the stored, ion-cannon or by-type target; nothing while the global flag is set.
    void Fire_LightningStorm(SuperClass* pSuper);
    // FUNCTION: GAMEMD 0x509B20 -- the same target choice as Fire_LightningStorm without the global-flag test.
    void FUN_00509B20(SuperClass* pSuper);
    // FUNCTION: GAMEMD 0x509BD0 -- fires the super weapon at the sentinel cell when an enemy is picked.
    void FUN_00509BD0(SuperClass* pSuper);
    // FUNCTION: GAMEMD 0x509C10 -- the same target choice as Fire_LightningStorm without the global-flag test.
    void FUN_00509C10(SuperClass* pSuper);
    // FUNCTION: GAMEMD 0x509CD0 -- fires the paradrop at the preferred cell, a free spot near the enemy's base centre, or the by-type pick.
    void Fire_ParaDrop(SuperClass* pSuper);
    // Inlined by retail (no out-of-line body): BaseCenter when set, otherwise BaseSpawnCell.
    Cell GetBaseCenter() const;
    // FUNCTION: GAMEMD 0x501540 -- may this house propose an alliance with `other` (not itself, an ally, civilian outside campaigns, or once defeated).
    bool CanAlly(HouseClass* other);
    // FUNCTION: GAMEMD 0x509140 -- re-checks the factory serving a category after the buildable set changed: drops unbuildable queue entries and abandons, suspends or resumes the current item.
    void UpdateFactoriesQueues(int rtti, bool isNaval, int buildCat);
    // FUNCTION: GAMEMD 0x4FB6B0 -- a factory finished an object: remembers its type per category, tallies it and plays the ready voice; RET 4.
    void RegisterJustBuilt(TechnoClass* pTechno);
    // FUNCTION: GAMEMD 0x4FF550 -- an object left the books: clears its tracked flag and walks the owned counts and tallies down; RET 4.
    void RemoveTracking(TechnoClass* pTechno);
    // FUNCTION: GAMEMD 0x5051E0 -- first type in the list this house may build (owner, required/forbidden masks, planning side, super weapon rules).
    TechnoTypeClass* FirstBuildableFromArray(DynamicVectorClass<TechnoTypeClass*>* items);
    // FUNCTION: GAMEMD 0x50BF60 -- every cost multiplier restarts at one and folds in each owned building's type factors.
    void CalculateCostMultipliers();
    // FUNCTION: GAMEMD 0x50C170 -- index of the house whose name matches, or -1.
    static int FindIndexByName(const char* name);
    // FUNCTION: GAMEMD 0x4FD060 -- the first live building of that type index, optionally restricted to one sector.
    BuildingClass* FindBuildingOfType(int index, int sector);
    // FUNCTION: GAMEMD 0x4FD040 -- the building type being produced, null when none.
    BuildingTypeClass* GetProducingBuildingType();
    // FUNCTION: GAMEMD 0x4FFB20 (decl; reloc) -- which sector a coordinate is in.
    int SectorOf(const CoordStruct& coords);
    // FUNCTION: GAMEMD 0x4FFD50 -- sector of an object's coordinates, -1 for a null object.
    int SectorOfObject(BuildingClass* object);
    // FUNCTION: GAMEMD 0x4FFD90 -- sector of the centre of a cell.
    int SectorOfCell(CellStruct* cell);
    // FUNCTION: GAMEMD 0x4FBF60 -- a carrier drops the flag on a cell (or the nearest free one); RET 8.
    bool DroppedFlag(const CellStruct& cell, bool dwUnk);
    // FUNCTION: GAMEMD 0x505360 -- are all of a type's prerequisites among the first `count` owned building types.
    bool AllPrerequisitesAvailable(TechnoTypeClass* type, DynamicVectorClass<BuildingTypeClass*>* owned, int count);
    // FUNCTION: GAMEMD 0x65EAB0 -- flies a flight of aircraft of one type in from the house's map edge; returns how many made it in. __fastcall on a member: the type index travels in EDX, RET 0x10.
    int __fastcall SendSpyPlanes(int typeIndex, int count, int a2, AbstractClass* a3, AbstractClass* a4);
    // FUNCTION: GAMEMD 0x4FC980 -- ends the game for this house once and starts the borrowed-time countdown; answers the game-over flag.
    char FUN_004FC980();
    // FUNCTION: GAMEMD 0x4FF980 -- takes one off the factory counter of a removed building's category.
    void FUN_004FF980(TechnoClass* building);
    // FUNCTION: GAMEMD 0x4FFA50 -- adds one to the factory counter of an added building's category.
    void FUN_004FFA50(TechnoClass* building);
    // FUNCTION: GAMEMD 0x4FD150
    void FUN_004FD150();
    // FUNCTION: GAMEMD 0x50A490 -- one stack argument (RET 4).
    void FUN_0050A490(BuildingClass* building);
    // FUNCTION: GAMEMD 0x4FCE80 -- two stack arguments (RET 8).
    void FUN_004FCE80(CellStruct* cell, char flag);
    // FUNCTION: GAMEMD 0x50B1D0
    void FUN_0050B1D0();
    // FUNCTION: GAMEMD 0x500B40 -- reads the house's INI section, RET 4.
    void FUN_00500B40(CCINIClass* ini);
    // FUNCTION: GAMEMD 0x50BF60 -- no stack arguments (Ghidra: __fastcall, one unused ECX).
    void FUN_0050BF60();
    // FUNCTION: GAMEMD 0x50B6F0 -- 52 bytes, result in AL.
    bool FUN_0050B6F0();
    // FUNCTION: GAMEMD 0x509140 -- three stack arguments (RET 0xC).
    void FUN_00509140(int a, char b, int c);
    // FUNCTION: GAMEMD 0x50DB00 (decl; reloc) -- one stack argument (RET 4).
    void FUN_0050DB00(BuildingClass* building);
    // FUNCTION: GAMEMD 0x4FAA10 (decl; reloc) -- two stack arguments (RET 8).
    void FUN_004FAA10(int kind, int value);
};

GG_STATIC_ASSERT(offsetof(HouseClass, TechLevel) == 0x1D4); // 0x6886B0 accesses
GG_STATIC_ASSERT(offsetof(HouseClass, Buildings) == 0x68);
GG_STATIC_ASSERT(offsetof(HouseClass, Buildings.Items) == 0x6C);
GG_STATIC_ASSERT(offsetof(HouseClass, Buildings.Count) == 0x78);
GG_STATIC_ASSERT(sizeof(((HouseClass*)0)->Buildings) == 0x18);
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
GG_STATIC_ASSERT(sizeof(((HouseClass*)0)->PlanningPaths) == 0x30);
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
GG_STATIC_ASSERT(offsetof(HouseClass, CostUnitsMult)              == 0x5394);
GG_STATIC_ASSERT(offsetof(HouseClass, CostAircraftMult)           == 0x5398);
GG_STATIC_ASSERT(offsetof(HouseClass, CostBuildingsMult)          == 0x539C);
GG_STATIC_ASSERT(offsetof(HouseClass, CostDefensesMult)           == 0x53A0);
GG_STATIC_ASSERT(sizeof(((HouseClass*)0)->Type)                   == 4);
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
GG_STATIC_ASSERT(offsetof(HouseClass, Base) + offsetof(BaseClass, unknown_74) == 0x5774);
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
GG_STATIC_ASSERT(sizeof(((HouseClass*)0)->ColorSchemeIndex)         == 4);
GG_STATIC_ASSERT(offsetof(HouseClass, unknown_16060)              == 0x16060);
GG_STATIC_ASSERT(offsetof(HouseClass, ConnectionPoints)               == 0x16064);
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

// Queue 0x64E250/0x64E25D/0x64E264 field accesses.
GG_STATIC_ASSERT(offsetof(HouseClass, MapIsClear) == 0x241);
GG_STATIC_ASSERT(offsetof(HouseClass, BarracksInfiltrated) == 0x2BF);
GG_STATIC_ASSERT(sizeof(((HouseClass*)0)->BarracksInfiltrated) == 1);
GG_STATIC_ASSERT(offsetof(HouseClass, WarFactoryInfiltrated) == 0x2C0);
GG_STATIC_ASSERT(sizeof(((HouseClass*)0)->WarFactoryInfiltrated) == 1);
GG_STATIC_ASSERT(offsetof(HouseClass, StartingPoint) == 0x16058);
GG_STATIC_ASSERT(offsetof(HouseClass, StartingAllies) == 0x1605C);

// Existing body field reads/writes: interface receivers are at House+0x24.
// 501400 stores [interface+225];4F69D0 reads [interface+2EC].
GG_STATIC_ASSERT(offsetof(HouseClass, AllToHunt) == 0x249);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedBuildings) == 0x2F0);
GG_STATIC_ASSERT(offsetof(HouseClass, TotalStorage) == 0x310);
GG_STATIC_ASSERT(offsetof(HouseClass, PowerDrain) == 0x53A8);

GG_STATIC_ASSERT(offsetof(HouseClass, BaseSpawnCell) == 0x5490);
GG_STATIC_ASSERT(offsetof(HouseClass, BaseCenter) == 0x5494);

// Existing502D60 field reads; complete-object offsets.
GG_STATIC_ASSERT(offsetof(HouseClass, GroundspeedMultiplier) == 0x190);
GG_STATIC_ASSERT(offsetof(HouseClass, AirspeedMultiplier) == 0x198);
GG_STATIC_ASSERT(offsetof(HouseClass, ArmorMultiplier) == 0x1A0);
GG_STATIC_ASSERT(offsetof(HouseClass, ROFMultiplier) == 0x1A8);
GG_STATIC_ASSERT(offsetof(HouseClass, CostMultiplier) == 0x1B0);
GG_STATIC_ASSERT(offsetof(HouseClass, BuildTimeMultiplier) == 0x1B8);
GG_STATIC_ASSERT(offsetof(HouseClass, RepairDelay) == 0x1C0);
GG_STATIC_ASSERT(offsetof(HouseClass, Production) == 0x1EE);
GG_STATIC_ASSERT(offsetof(HouseClass, AutocreateAllowed) == 0x1EF);
GG_STATIC_ASSERT(offsetof(HouseClass, AITriggersActive) == 0x1F2);
GG_STATIC_ASSERT(offsetof(HouseClass, Defeated) == 0x1F5);
GG_STATIC_ASSERT(offsetof(HouseClass, AlertTimer) == 0x28C);
GG_STATIC_ASSERT(offsetof(HouseClass, BorrowedTime) == 0x298);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedUnits) == 0x2E8);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedInfantry) == 0x2F4);
GG_STATIC_ASSERT(offsetof(HouseClass, NumBarracks) == 0x537C);
GG_STATIC_ASSERT(offsetof(HouseClass, NumWarFactories) == 0x5380);
GG_STATIC_ASSERT(offsetof(HouseClass, NumShipyards) == 0x5388);
GG_STATIC_ASSERT(offsetof(HouseClass, NumConYards) == 0x5384);
GG_STATIC_ASSERT(offsetof(HouseClass, NumOrePurifiers) == 0x538C);

GG_STATIC_ASSERT(sizeof(bool) == 1);


// Native503D98/503DA0/503DA9 field stores; stream record extent eight bytes.
GG_STATIC_ASSERT(offsetof(HouseClass::StartingTechnoStruct, Type) == 0);
GG_STATIC_ASSERT(offsetof(HouseClass::StartingTechnoStruct, Cell) == 4);
GG_STATIC_ASSERT(sizeof(HouseClass::StartingTechnoStruct) == 8);

#endif  // GG_MATCH_LAYOUT_HOUSE_CLASS_H

// House Load (0x00503040): native member receivers and swizzle address operands.
GG_STATIC_ASSERT(offsetof(HouseClass, UnitRepairStations) == 0x80);
GG_STATIC_ASSERT(offsetof(HouseClass, Grinders) == 0x98);
GG_STATIC_ASSERT(offsetof(HouseClass, Absorbers) == 0xB0);
GG_STATIC_ASSERT(offsetof(HouseClass, Bunkers) == 0xC8);
GG_STATIC_ASSERT(offsetof(HouseClass, Occupiables) == 0xE0);
GG_STATIC_ASSERT(offsetof(HouseClass, CloningVats) == 0xF8);
GG_STATIC_ASSERT(offsetof(HouseClass, SecretLabs) == 0x110);
GG_STATIC_ASSERT(offsetof(HouseClass, PsychicDetectionBuildings) == 0x128);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForInfantry) == 0x53B0);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForVehicles) == 0x53B4);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForShips) == 0x53B8);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForBuildings) == 0x53BC);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_Unused1) == 0x53C0);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_Unused2) == 0x53C4);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_Unused3) == 0x53C8);
GG_STATIC_ASSERT(offsetof(HouseClass, Primary_ForDefenses) == 0x53CC);
GG_STATIC_ASSERT(offsetof(HouseClass, ToCapture) == 0x54E0);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedUnitTypes) == 0x5514);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedInfantryTypes) == 0x5528);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedAircraftTypes) == 0x553C);
GG_STATIC_ASSERT(offsetof(HouseClass, ActiveBuildingTypes) == 0x5550);
GG_STATIC_ASSERT(offsetof(HouseClass, ActiveUnitTypes) == 0x5564);
GG_STATIC_ASSERT(offsetof(HouseClass, ActiveInfantryTypes) == 0x5578);
GG_STATIC_ASSERT(offsetof(HouseClass, ActiveAircraftTypes) == 0x558C);
GG_STATIC_ASSERT(offsetof(HouseClass, FactoryProducedBuildingTypes) == 0x55A0);
GG_STATIC_ASSERT(offsetof(HouseClass, FactoryProducedUnitTypes) == 0x55B4);
GG_STATIC_ASSERT(offsetof(HouseClass, FactoryProducedInfantryTypes) == 0x55C8);

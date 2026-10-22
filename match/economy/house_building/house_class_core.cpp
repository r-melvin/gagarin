// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//
// HouseClass entries of the house/building cluster (layout and evidence: house_class_core.h, house_views.h).

#include <string.h>
#include <new.h>
#include "house_class_core.h"

#pragma intrinsic(memcmp)

// ---- globals / read-only externals ----------------------------------------------------------------
// GLOBAL: GAMEMD 0x7EA768 / 0x7E9B00 - IID_IHouse / IID_IPublicHouse. The library ids (IID_IUnknown
//         0x7F7C90, IID_IPersist 0x7F7C70, IID_IPersistStream 0x7F7C80, IID_IConnectionPointContainer
//         0x7F7CD0) come from the SDK import library.
extern const IID IID_IHouse;
extern const IID IID_IPublicHouse;
// GLOBAL: GAMEMD 0x820270 - the program's own copy of IID_IPersistStream (data of the original unit), used by Save.
extern const IID DAT_00820270;
// GLOBAL: GAMEMD 0x7E9AF0 - the id of the AI general interface the house loads from its stream.
extern const IID DAT_007E9AF0;
// GLOBAL: GAMEMD 0x7E9560 - CLSID_House.
extern const CLSID CLSID_House;
// GLOBAL: GAMEMD 0x7E36C0 - the interface id requested from the global object below.
extern const IID DAT_007E36C0;
// GLOBAL: GAMEMD 0x89A29C - the object the main interface is queried from.
extern unsigned char HouseMainObject;
// FUNCTION: GAMEMD 0x429360 (decl; reloc) - queries an interface of a global object.
void __stdcall HouseQueryObjectInterface(void* object, const IID* riid, void** result);

// FUNCTION: GAMEMD 0x7DC720 (decl; reloc; LIBRARY, comsupp) - throws the COM error
void __stdcall HouseComIssueError(long hr);

// GLOBAL: GAMEMD 0xA80228 - HouseClass::Array (Items at +0x04 = 0xA8022C, Count at +0x10 = 0xA80238).
extern HouseDynVector<HouseClusterView*> HouseArray;
// GLOBAL: GAMEMD 0xB0F670 / 0xB0F640 / 0xB0F5F0 / 0xB0F618 / 0xB0F720 - global object lists the
// constructor registers the house in, one after the other (element types unproven, all house pointers).
extern HouseDynVector<HouseClusterView*> HouseListB0F670;
extern HouseDynVector<HouseClusterView*> HouseListB0F640;
extern HouseDynVector<HouseClusterView*> HouseListB0F5F0;
extern HouseDynVector<HouseClusterView*> HouseListB0F618;
extern HouseDynVector<HouseClusterView*> HouseListB0F720;
// GLOBAL: GAMEMD 0xA8B228 / 0xA8E358 / 0xA83CF0 / 0xA83C78 - the type-array counts the unit trackers are sized from.
extern int HouseAircraftTypeCount;
extern int HouseInfantryTypeCount;
extern int HouseUnitTypeCount;
extern int HouseBuildingTypeCount;
// GLOBAL: GAMEMD 0x889F64 - the default interface name text copied into UINameString.
extern char HouseDefaultName[];
// GLOBAL: GAMEMD 0x7E9550 - the id handed to the connection-point source object.
extern const IID DAT_007E9550;

// CAPPED at 98.3% (multiset identical; 17 instructions differ in order or register only: the -1 constant
// load near +0x214, the five byte stores near +0x3BB, a push near +0x69F, one add operand order near
// +0xBC6, two fill-setup orders). Variants tried: memset vs element loops for the fills, vector ctor with
// init list vs body assignments (body kept), AddItem shapes.
// FUNCTION: GAMEMD 0x4F54A0
HouseClusterView::HouseClusterView(HouseTypeView* type)
    : ArrayIndex(-1),
      Type(type),
      RelatedTags(0, 0),
      ConYards(0, 0),
      Buildings(0, 0),
      UnitRepairStations(0, 0),
      Grinders(0, 0),
      Absorbers(0, 0),
      Bunkers(0, 0),
      Occupiables(0, 0),
      CloningVats(0, 0),
      SecretLabs(0, 0),
      PsychicDetectionBuildings(0, 0),
      FactoryPlants(0, 0),
      CountResourceGatherers(0),
      CountResourceDestinations(0),
      CountWarfactories(0),
      InfantrySelfHeal(0),
      UnitsSelfHeal(0),
      StartingUnits(0, 0),
      AIDifficulty(HouseScenario->Difficulty),
      FirepowerMultiplier(1.0),
      GroundspeedMultiplier(1.0),
      AirspeedMultiplier(1.0),
      ArmorMultiplier(1.0),
      ROFMultiplier(1.0),
      CostMultiplier(1.0),
      BuildTimeMultiplier(1.0),
      RepairDelay(0.0),
      BuildDelay(0.0),
      IQLevel(0),
      TechLevel(1),
      AltAllies(0),
      StartingCredits(0),
      StartingEdge(-1),
      AIState_1E4(0),
      IsHumanPlayer(false),
      IsInPlayerControl(false),
      Production(false),
      AutocreateAllowed(false),
      NodeLogic_1F0(true),
      ShipYardConst_1F1(false),
      AITriggersActive(false),
      AutoBaseBuilding(false),
      DiscoveredByPlayer(false),
      Defeated(false),
      IsGameOver(false),
      IsWinner(false),
      IsLoser(false),
      CiviliansEvacuated(false),
      FirestormActive(false),
      HasThreatNode(false),
      RecheckTechTree(true),
      IPAddress(0),
      TournamentTeamID(0),
      LostConnection(false),
      SelectedPathIndex(-1),
      Visionary(0),
      MapIsClear(false),
      IsTiberiumShort(false),
      HasBeenSpied(false),
      HasBeenThieved(false),
      Repairing(false),
      IsBuiltSomething(false),
      IsResigner(false),
      IsGiverUpper(false),
      AllToHunt(false),
      IsParanoid(false),
      IsToLook(true),
      IQLevel2(IQLevel),
      AIMode(0),
      Supers(0, 0),
      LastBuiltBuildingType(-1),
      LastBuiltInfantryType(-1),
      LastBuiltAircraftType(-1),
      LastBuiltVehicleType(-1),
      AllowWinBlocks(0),
      Side2TechInfiltrated(false),
      Side1TechInfiltrated(false),
      Side0TechInfiltrated(false),
      BarracksInfiltrated(false),
      WarFactoryInfiltrated(false),
      InfantryAltOwner(0),
      UnitAltOwner(0),
      AircraftAltOwner(0),
      BuildingAltOwner(0),
      AirportDocks(0),
      PoweredUnitCenters(0),
      CreditsSpent(0),
      HarvestedCredits(0),
      StolenBuildingsCredits(0),
      OwnedUnits(0),
      OwnedNavy(0),
      OwnedBuildings(0),
      OwnedInfantry(0),
      OwnedAircraft(0),
      Balance(0),
      TotalStorage(0),
      NumAirpads(0),
      NumBarracks(0),
      NumWarFactories(0),
      NumConYards(0),
      NumShipyards(0),
      NumOrePurifiers(0),
      CostInfantryMult(1.0f),
      CostUnitsMult(1.0f),
      CostAircraftMult(1.0f),
      CostBuildingsMult(1.0f),
      CostDefensesMult(1.0f),
      PowerOutput(0),
      PowerDrain(0),
      Primary_ForAircraft(0),
      Primary_ForInfantry(0),
      Primary_ForVehicles(0),
      Primary_ForShips(0),
      Primary_ForBuildings(0),
      Primary_Unused1(0),
      Primary_Unused2(0),
      Primary_Unused3(0),
      Primary_ForDefenses(0),
      AircraftType_53D0(0),
      InfantryType_53D1(0),
      VehicleType_53D2(0),
      ShipType_53D3(0),
      BuildingType_53D4(0),
      unknown_53D5(0),
      unknown_53D6(0),
      unknown_53D7(0),
      DefenseType_53D8(0),
      OurFlagCarrier(0),
      OurFlagCoords(0, 0),
      TotalKilledUnits(0),
      TotalKilledBuildings(0),
      WhoLastHurtMe(-1),
      BaseSpawnCell(HouseEmptyCell),
      BaseCenter(HouseEmptyCell),
      Radius(0),
      LATime(0),
      LAEnemy(-1),
      ToCapture(0),
      RadarVisibleTo(0),
      PointTotal(0),
      PreferredTargetType(1),
      PreferredTargetCell(0, 0),
      PreferredDefensiveCell(0, 0),
      PreferredDefensiveCell2(0, 0),
      PreferredDefensiveCellStartTime(-100),
      AttackTimer(),
      InitialAttackDelay(0),
      EnemyHouseIndex(-1),
      AngerNodes(0, 0),
      ScoutNodes(0, 0),
      ProducingBuildingTypeIndex(-1),
      ProducingUnitTypeIndex(-1),
      ProducingInfantryTypeIndex(-1),
      ProducingAircraftTypeIndex(-1),
      RatioAITriggerTeam(100),
      RatioTeamAircraft(75),
      RatioTeamInfantry(75),
      RatioTeamBuildings(75),
      BaseDefenseTeamCount(0),
      CurrentDropshipIndex(0),
      HasCloakingRanges(false),
      Color(0, 0, 0),
      LaserColor(255, 255, 255),
      RecheckPower(true),
      RecheckRadar(true),
      SpySatActive(false),
      IsBeingDrained(false),
      Edge(0),
      EMPTarget(0, 0),
      NukeTarget(0, 0),
      Allies(0),
      DamageDelayTimer((int)(HouseRules->DamageDelay * 900.0)),
      TeamDelayTimer(1),
      TriggerDelayTimer(),
      SpeakAttackDelayTimer(1),
      SpeakPowerDelayTimer(1),
      SpeakMoneyDelayTimer(1),
      SpeakMaxedDelayTimer(1),
      AIGeneral(0),
      ColorSchemeIndex(0),
      unknown_16060(0),
      ConnectionPoints(0, 0),
      unknown_1607C(0),
      unknown_16080(0),
      unused_16088(1.0),
      unused_16090(1.0),
      PredictionEnemyArmor(0.33f),
      PredictionEnemyAir(0.33f),
      PredictionEnemyInfantry(0.33f),
      TotalOwnedInfantryCost(0),
      TotalOwnedVehicleCost(0),
      TotalOwnedAircraftCost(0),
      PowerSurplus(0)
{
    UINameString.Assign(HouseDefaultName);
    UIName[0] = 0;
    HBRttiBase::Create_ID();
    if (Type)
        ColorSchemeIndex = Type->ColorScheme;
    HouseListB0F670.AddItem(this);
    HouseListB0F640.AddItem(this);
    HouseListB0F5F0.AddItem(this);
    HouseListB0F618.AddItem(this);
    HouseListB0F720.AddItem(this);
    ArrayIndex = HouseArray.Count;
    if (type) {
        for (int i = 0; i < HouseArray.Count; i++) {
            HouseArray.Items[i]->AngerNodes.AddItem(HouseAngerNode(this, 0));
            AngerNodes.AddItem(HouseAngerNode(HouseArray.Items[i], 0));
            HouseArray.Items[i]->ScoutNodes.AddItem(HouseScoutNode(this, false));
            ScoutNodes.AddItem(HouseScoutNode(HouseArray.Items[i], false));
        }
    }
    HouseArray.AddItem(this);

    memset(ThreatPosedEstimates, 0, sizeof(ThreatPosedEstimates));
    for (int i = 0; i < HouseSuperTypeCount; i++) {
        HouseSuperObject* super = new HouseSuperObject(HouseSuperTypeItems[i], this);
        Supers.AddItem(super);
    }
    memset(KilledUnitsOfHouses, 0, sizeof(KilledUnitsOfHouses));
    memset(KilledBuildingsOfHouses, 0, sizeof(KilledBuildingsOfHouses));
    if (type) {
        PlainName.Assign(type->Name);
        wcscpy((wchar_t*)UIName, type->UIName);
    }
    memset(ThreatPosedEstimates, 0, sizeof(ThreatPosedEstimates));
    AltAllies |= 1 << ArrayIndex;
    int attackDelay = (int)(HouseScenario->Random.RandomRanged(450, 1800) * HouseRules->AttackDelay);
    AttackTimer = HouseTimer(attackDelay);
    InitialAttackDelay = attackDelay;
    BuiltAircraftTypes.Init(HouseAircraftTypeCount);
    BuiltInfantryTypes.Init(HouseInfantryTypeCount);
    BuiltUnitTypes.Init(HouseUnitTypeCount);
    BuiltBuildingTypes.Init(HouseBuildingTypeCount);
    KilledAircraftTypes.Init(HouseAircraftTypeCount);
    KilledInfantryTypes.Init(HouseInfantryTypeCount);
    KilledUnitTypes.Init(HouseUnitTypeCount);
    KilledBuildingTypes.Init(HouseBuildingTypeCount);
    CapturedBuildings.Init(HouseBuildingTypeCount);
    CollectedCrates.Init(19);
    for (int k = 0; k < 12; k++)
        PlanningPaths[k] = 0;
    if (type)
        HasThreatNode = true;
    SideIndex = -1;
    if (Type) {
        int side = Type->Side;
        if (side == 0)
            SideIndex = 0;
        else if (side == 1)
            SideIndex = side;
        else if (side == 2)
            SideIndex = side;
    }

    IUnknown* unknown = 0;
    HouseClusterView::QueryInterface(IID_IUnknown, (void**)&unknown);
    HouseConnPtSource* source = new HouseConnPtSource(&DAT_007E9550, unknown);
    unknown_1607C = (unsigned int)source;
    IConnectionPoint* point;
    source->QueryInterface(IID_IConnectionPoint, (void**)&point);
    ConnectionPoints.AddItem(point);
    unknown->Release();
}

// FUNCTION: GAMEMD 0x4F6830
HRESULT __stdcall HouseClusterView::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == 0)
        return E_POINTER;

    *ppv = 0;
    if (memcmp(&riid, &IID_IUnknown, sizeof(IID)) == 0)
        *ppv = this;
    if (memcmp(&riid, &IID_IHouse, sizeof(IID)) == 0)
        *ppv = static_cast<HouseIHouseBase*>(this);
    if (memcmp(&riid, &IID_IPublicHouse, sizeof(IID)) == 0)
        *ppv = static_cast<HousePublicHouseBase*>(this);
    if (memcmp(&riid, &IID_IConnectionPointContainer, sizeof(IID)) == 0)
        *ppv = static_cast<IConnectionPointContainer*>(this);
    if (memcmp(&riid, &IID_IPersist, sizeof(IID)) == 0)
        *ppv = this;
    if (memcmp(&riid, &IID_IPersistStream, sizeof(IID)) == 0)
        *ppv = this;

    if (*ppv == 0)
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

// FUNCTION: GAMEMD 0x4F6910
bool __stdcall HouseClusterView::HasEnoughPower()
{
    return PowerOutput >= PowerDrain;
}

// FUNCTION: GAMEMD 0x4F6930
IUnknown* __stdcall HouseClusterView::GetMainInterface()
{
    IUnknown* result;
    HouseQueryObjectInterface(&HouseMainObject, &DAT_007E36C0, (void**)&result);
    return result;
}

// FUNCTION: GAMEMD 0x4F6950
BSTR __stdcall HouseClusterView::GetName()
{
    WCHAR buffer[32];
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, Type->NameBuffer, -1, buffer, 32);
    return SysAllocString(buffer);
}

// FUNCTION: GAMEMD 0x4F6990
int __stdcall HouseClusterView::GetCredits()
{
    float multiplier = Type->ValueMultiplier;
    return (int)(OwnedTiberium.GetTotalValue() * multiplier + Balance);
}

// FUNCTION: GAMEMD 0x4F69D0
int __stdcall HouseClusterView::GetTiberiumStored()
{
    return TotalStorage - (int)OwnedTiberium.GetTotalAmount();
}

// FUNCTION: GAMEMD 0x4F6A00
int __stdcall HouseClusterView::GetPowerOutput()
{
    return PowerOutput;
}

// FUNCTION: GAMEMD 0x4F6A10
int __stdcall HouseClusterView::GetPowerDrain()
{
    return PowerDrain;
}

// FUNCTION: GAMEMD 0x4F6A20
int __stdcall HouseClusterView::CountOwnedOfCategory(int category)
{
    int count = 0;
    for (int i = 0; i < HouseTechnoArray.Count; i++) {
        HouseTechnoView* techno = HouseTechnoArray.Items[i];
        if (techno->Owner == this && techno->GetTechnoType()->Category == category)
            count++;
    }
    return count;
}

// FUNCTION: GAMEMD 0x4F6A80
int __stdcall HouseClusterView::PublicCountOwnedOfCategory(int category)
{
    int count = 0;
    for (int i = 0; i < HouseTechnoArray.Count; i++) {
        HouseTechnoView* techno = HouseTechnoArray.Items[i];
        if (techno->Owner == this && techno->GetTechnoType()->Category == category)
            count++;
    }
    return count;
}

// FUNCTION: GAMEMD 0x4F6AE0
int __stdcall HouseClusterView::SumScoreOfCategory(int category)
{
    int total = 0;
    for (int i = 0; i < HouseTechnoArray.Count; i++) {
        HouseTechnoView* techno = HouseTechnoArray.Items[i];
        HouseTechnoTypeView* type = techno->GetTechnoType();
        if (techno->Owner == this && type->Category == category)
            total += type->ThreatPosed + type->Points;
    }
    return total;
}

// FUNCTION: GAMEMD 0x4F6B50
int __stdcall HouseClusterView::PublicSumScoreOfCategory(int category)
{
    int total = 0;
    for (int i = 0; i < HouseTechnoArray.Count; i++) {
        HouseTechnoView* techno = HouseTechnoArray.Items[i];
        HouseTechnoTypeView* type = techno->GetTechnoType();
        if (techno->Owner == this && type->Category == category)
            total += type->ThreatPosed + type->Points;
    }
    return total;
}

// FUNCTION: GAMEMD 0x4F6BC0
void* __stdcall HouseClusterView::GetBaseCenter(void* cell)
{
    HBCell center;
    center.X = HouseCellCoord(HouseBaseCell()).X / 256;
    center.Y = HouseCellCoord(HouseBaseCell()).Y / 256;
    *(HBCell*)cell = center;
    return cell;
}

// FUNCTION: GAMEMD 0x4F6D10
void* __stdcall HouseClusterView::PublicGetBaseCenter(void* cell)
{
    HBCell center;
    center.X = HouseCellCoord(HouseBaseCell()).X / 256;
    center.Y = HouseCellCoord(HouseBaseCell()).Y / 256;
    *(HBCell*)cell = center;
    return cell;
}

// FUNCTION: GAMEMD 0x4F6E60
int __stdcall HouseClusterView::GetIndex()
{
    return ArrayIndex;
}

// FUNCTION: GAMEMD 0x4FB9B0
void HouseClusterView::PointerExpired(HouseAbstractPtrView* pointer, bool removed)
{
    if (ToCapture == pointer)
        ToCapture = 0;

    HouseTagRef* tag = (HouseTagRef*)HouseRtDynamicCast(pointer, 0, HouseTypeDesc_AbstractClass, HouseTypeDesc_TagClass, 0);
    if (tag)
        RelatedTags.RemoveItem(tag);

    if (pointer->WhatAmI() == 6 && removed) {
        int index = ConYards.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            ConYards.RemoveAt(index);
        UnitRepairStations.RemoveItem((HouseBuildingRef*)pointer);
        index = Grinders.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            Grinders.RemoveAt(index);
        Absorbers.RemoveItem((HouseBuildingRef*)pointer);
        index = Bunkers.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            Bunkers.RemoveAt(index);
        Occupiables.RemoveItem((HouseBuildingRef*)pointer);
        index = CloningVats.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            CloningVats.RemoveAt(index);
        index = SecretLabs.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            SecretLabs.RemoveAt(index);
        PsychicDetectionBuildings.RemoveItem((HouseBuildingRef*)pointer);
        index = FactoryPlants.FindItemIndex((HouseBuildingRef*)pointer);
        if (index != -1)
            FactoryPlants.RemoveAt(index);
        Buildings.RemoveItem((HouseBuildingRef*)pointer);
        CalculateCostMultipliers();
    }

    for (int i = 0; i < 12; i++) {
        if (PlanningPaths[i] == pointer)
            PlanningPaths[i] = 0;
    }
    if (Primary_ForAircraft == pointer)
        Primary_ForAircraft = 0;
    if (Primary_ForInfantry == pointer)
        Primary_ForInfantry = 0;
    if (Primary_ForVehicles == pointer)
        Primary_ForVehicles = 0;
    if (Primary_ForShips == pointer)
        Primary_ForShips = 0;
    if (Primary_ForBuildings == pointer)
        Primary_ForBuildings = 0;
    if (Primary_Unused1 == pointer)
        Primary_Unused1 = 0;
    if (Primary_Unused2 == pointer)
        Primary_Unused2 = 0;
    if (Primary_Unused3 == pointer)
        Primary_Unused3 = 0;
    if (Primary_ForDefenses == pointer)
        Primary_ForDefenses = 0;
}

// FUNCTION: GAMEMD 0x5013A0
int __stdcall HouseClusterView::SellAllBuildings()
{
    if (OwnedBuildings > 0) {
        int count = Buildings.Count;
        for (int i = 0; i < count; i++) {
            HouseTechnoView* building = (HouseTechnoView*)Buildings.Items[i];
            if (building && !building->InLimbo && building->Strength > 0)
                building->vf_104(1);
        }
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x501400
int __stdcall HouseClusterView::DestroyAllTechnos()
{
    for (int i = HouseTechnoArray.Count - 1; i >= 0; i--) {
        HouseTechnoView* techno = HouseTechnoArray.Items[i];
        if (this == techno->Owner && techno->IsOnMap && !techno->InLimbo) {
            if (techno->MindControlled && techno->GetTechnoType()->Insignificant && !IsHumanPlayer) {
                int damage = techno->GetTechnoType()->unknown_A0;
                techno->ReceiveDamage(&damage, 0, HouseRules->unknown_FA8, 0, true, true, 0);
            } else if (techno) {
                if (HouseIsFoot(techno)) {
                    if (techno->unknown_5D4)
                        techno->unknown_5D4->M_6EA870(techno, -1, 0);
                    techno->vf_122(15, 0);
                } else if (techno->WhatAmI() == 6) {
                    if (techno->vf_258() > 0)
                        techno->M_457DE0(1, 0);
                }
            }
        }
    }
    AllToHunt = true;
    return 0;
}

// FUNCTION: GAMEMD 0x5024F0
HRESULT __stdcall HouseClusterView::EnumConnectionPoints(IEnumConnectionPoints** ppEnum)
{
    if (ppEnum == 0)
        return E_POINTER;

    HouseConnPtEnum* enumerator = new HouseConnPtEnum(&ConnectionPoints);
    if (enumerator == 0)
        return E_OUTOFMEMORY;

    enumerator->AddRef();
    *ppEnum = enumerator;
    return S_OK;
}

// FUNCTION: GAMEMD 0x502550
HRESULT __stdcall HouseClusterView::FindConnectionPoint(REFIID riid, IConnectionPoint** ppCP)
{
    if (ppCP == 0)
        return E_POINTER;

    *ppCP = 0;
    for (int i = 0; i < ConnectionPoints.Count; i++) {
        IConnectionPoint* point = ConnectionPoints.Items[i];
        IID id;
        point->GetConnectionInterface(&id);
        if (memcmp(&id, &riid, sizeof(IID)) == 0) {
            *ppCP = point;
            point->AddRef();
            return S_OK;
        }
    }
    return CONNECT_E_CANNOTCONNECT;
}

// CAPPED at 91.7%: the three inlined timer reads load the start into EDX and the frame into ECX in
// retail, the reverse here (18 register-only differences, multiset identical). Variants: conditional
// form, early-return form, local-copy form, ternary form.
// FUNCTION: GAMEMD 0x502D60
void HouseClusterView::ComputeCrc(HouseCrcView* crc)
{
    HouseAbstractView::ComputeCrc(crc);
    crc->AddInt(AIDifficulty);
    crc->AddInt(Type->ArrayIndex2);
    crc->AddDouble(FirepowerMultiplier);
    crc->AddDouble(GroundspeedMultiplier);
    crc->AddDouble(AirspeedMultiplier);
    crc->AddDouble(ArmorMultiplier);
    crc->AddDouble(ROFMultiplier);
    crc->AddDouble(CostMultiplier);
    crc->AddDouble(BuildTimeMultiplier);
    crc->AddDouble(RepairDelay);
    crc->AddDouble(BuildDelay);
    crc->AddBool(IsHumanPlayer);
    crc->AddBool(Production);
    crc->AddBool(AutocreateAllowed);
    crc->AddBool(AITriggersActive);
    crc->AddBool(Defeated);
    crc->AddInt(IQLevel2);
    crc->AddInt(AIMode);
    crc->AddInt(AllowWinBlocks);
    crc->AddInt(RepairTimer.GetTimeLeft());
    crc->AddInt(AlertTimer.GetTimeLeft());
    crc->AddInt(BorrowedTime.GetTimeLeft());
    crc->AddInt(OwnedUnits);
    crc->AddInt(OwnedBuildings);
    crc->AddInt(OwnedInfantry);
    crc->AddInt(OwnedAircraft);
    crc->AddInt(Balance);
    crc->AddInt(TotalStorage);
    crc->AddInt(NumAirpads);
    crc->AddInt(NumBarracks);
    crc->AddInt(NumWarFactories);
    crc->AddInt(NumShipyards);
    crc->AddInt(NumConYards);
    crc->AddInt(NumOrePurifiers);
    crc->AddInt(PowerOutput);
    crc->AddInt(PowerDrain);
    crc->AddBool(MapIsClear);
    crc->AddInt(WhoLastHurtMe);
    crc->AddInt(EnemyHouseIndex);
    Base.ComputeCrc(crc);
}

// CAPPED at 99.6%: six instructions differ, the grown-capacity add at the ConYards / Buildings /
// UnitRepairStations loads is `add ecx,eax` in retail and `add eax,ecx` here (multiset identical).
// Variants: cap+inc, inc+cap, Capacity member without a local, grown-capacity temporary.
// FUNCTION: GAMEMD 0x503040
HRESULT __stdcall HouseClusterView::Load(IStream* pStm)
{
    int i;
    int count;
    HRESULT hr;

    ConYards.Clear();
    Buildings.Clear();
    UnitRepairStations.Clear();
    Grinders.Clear();
    Absorbers.Clear();
    Bunkers.Clear();
    Occupiables.Clear();
    CloningVats.Clear();
    SecretLabs.Clear();
    PsychicDetectionBuildings.Clear();
    FactoryPlants.Clear();
    for (i = StartingUnits.Count - 1; i >= 0; i--)
        delete StartingUnits.Items[i];
    StartingUnits.Clear();
    for (i = 0; i < ConnectionPoints.Count; i++) {
        while (ConnectionPoints.Items[i]->Release() > 0)
            ;
        ConnectionPoints.Items[i] = 0;
    }
    ConnectionPoints.Clear();
    while (Supers.Count) {
        delete Supers.Items[0];
        if (0 < Supers.Count) {
            Supers.Count = Supers.Count - 1;
            for (i = 0; i < Supers.Count; ++i)
                Supers.Items[i] = Supers.Items[i + 1];
        }
    }

    hr = HouseAbstractView::Load(pStm);
    if (hr < 0)
        return hr;
    new (this) HouseClusterView(HBNoInit());
    Base.LoadFromStream(pStm);
    OwnedBuildingTypes.Load(pStm);
    OwnedUnitTypes.Load(pStm);
    OwnedInfantryTypes.Load(pStm);
    OwnedAircraftTypes.Load(pStm);
    ActiveBuildingTypes.Load(pStm);
    ActiveUnitTypes.Load(pStm);
    ActiveInfantryTypes.Load(pStm);
    ActiveAircraftTypes.Load(pStm);
    FactoryProducedBuildingTypes.Load(pStm);
    FactoryProducedUnitTypes.Load(pStm);
    FactoryProducedInfantryTypes.Load(pStm);
    FactoryProducedAircraftTypes.Load(pStm);
    HouseSwizzle.Swizzle(&Type);
    HouseSwizzle.Swizzle(&Primary_ForInfantry);
    HouseSwizzle.Swizzle(&Primary_ForVehicles);
    HouseSwizzle.Swizzle(&Primary_ForAircraft);
    HouseSwizzle.Swizzle(&Primary_ForShips);
    HouseSwizzle.Swizzle(&Primary_ForBuildings);
    HouseSwizzle.Swizzle(&Primary_Unused1);
    HouseSwizzle.Swizzle(&Primary_Unused2);
    HouseSwizzle.Swizzle(&Primary_Unused3);
    HouseSwizzle.Swizzle(&Primary_ForDefenses);
    HouseSwizzle.Swizzle(&ToCapture);
    for (i = 0; i < 12; i++)
        HouseSwizzle.Swizzle(&PlanningPaths[i]);
    for (i = 0; i < 3; i++)
        DropshipData[i].Swizzle();

    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseSuperRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Supers.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseTagRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        RelatedTags.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseAngerNode node;
        node.House = 0;
        node.Value = 0;
        hr = pStm->Read(&node, 8, 0);
        if (hr < 0)
            return hr;
        AngerNodes.AddItem(node);
    }
    for (i = 0; i < AngerNodes.Count; i++)
        HouseSwizzle.Swizzle(&AngerNodes.Items[i]);
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseScoutNode node;
        node.Cell = 0;
        node.Flag = false;
        hr = pStm->Read(&node, 8, 0);
        if (hr < 0)
            return hr;
        ScoutNodes.AddItem(node);
    }
    for (i = 0; i < ScoutNodes.Count; i++)
        HouseSwizzle.Swizzle(&ScoutNodes.Items[ScoutNodes.Count - 1]);
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        ConYards.AddItemCapFirst(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Buildings.AddItemCapFirst(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        UnitRepairStations.AddItemCapFirst(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Grinders.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Absorbers.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Bunkers.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Occupiables.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        CloningVats.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        SecretLabs.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        PsychicDetectionBuildings.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseBuildingRef* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        FactoryPlants.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        HouseStartingUnit* unit = new HouseStartingUnit;
        int type = 0;
        short x;
        short y;
        hr = pStm->Read(&type, 4, 0);
        if (hr < 0)
            return hr;
        hr = pStm->Read(&x, 2, 0);
        if (hr < 0)
            return hr;
        hr = pStm->Read(&y, 2, 0);
        if (hr < 0)
            return hr;
        unit->Type = type;
        unit->X = x;
        unit->Y = y;
        StartingUnits.AddItem(unit);
    }

    for (i = 0; i < Supers.Count; i++)
        HouseSwizzle.Swizzle(&Supers.Items[i]);
    for (i = 0; i < RelatedTags.Count; i++)
        HouseSwizzle.Swizzle(&RelatedTags.Items[i]);
    for (i = 0; i < ConYards.Count; i++)
        HouseSwizzle.Swizzle(&ConYards.Items[i]);
    for (i = 0; i < Buildings.Count; i++)
        HouseSwizzle.Swizzle(&Buildings.Items[i]);
    for (i = 0; i < UnitRepairStations.Count; i++)
        HouseSwizzle.Swizzle(&UnitRepairStations.Items[i]);
    for (i = 0; i < Grinders.Count; i++)
        HouseSwizzle.Swizzle(&Grinders.Items[i]);
    for (i = 0; i < Absorbers.Count; i++)
        HouseSwizzle.Swizzle(&Absorbers.Items[i]);
    for (i = 0; i < Bunkers.Count; i++)
        HouseSwizzle.Swizzle(&Bunkers.Items[i]);
    for (i = 0; i < Occupiables.Count; i++)
        HouseSwizzle.Swizzle(&Occupiables.Items[i]);
    for (i = 0; i < CloningVats.Count; i++)
        HouseSwizzle.Swizzle(&CloningVats.Items[i]);
    for (i = 0; i < SecretLabs.Count; i++)
        HouseSwizzle.Swizzle(&SecretLabs.Items[i]);
    for (i = 0; i < PsychicDetectionBuildings.Count; i++)
        HouseSwizzle.Swizzle(&PsychicDetectionBuildings.Items[i]);
    for (i = 0; i < FactoryPlants.Count; i++)
        HouseSwizzle.Swizzle(&FactoryPlants.Items[i]);
    for (i = 0; i < StartingUnits.Count; i++)
        HouseSwizzle.Swizzle(StartingUnits.Items[i]);

    int hasAIGeneral = 0;
    hr = pStm->Read(&hasAIGeneral, 4, 0);
    if (hr < 0 || !hasAIGeneral)
        return hr;
    return OleLoadFromStream(pStm, DAT_007E9AF0, (void**)&AIGeneral);
}

// FUNCTION: GAMEMD 0x504080
HRESULT __stdcall HouseClusterView::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT result = HouseAbstractView::Save(pStm, fClearDirty);

    if (result >= 0) {
    Base.SaveToStream(pStm);
    OwnedBuildingTypes.Save(pStm);
    OwnedUnitTypes.Save(pStm);
    OwnedInfantryTypes.Save(pStm);
    OwnedAircraftTypes.Save(pStm);
    ActiveBuildingTypes.Save(pStm);
    ActiveUnitTypes.Save(pStm);
    ActiveInfantryTypes.Save(pStm);
    ActiveAircraftTypes.Save(pStm);
    FactoryProducedBuildingTypes.Save(pStm);
    FactoryProducedUnitTypes.Save(pStm);
    FactoryProducedInfantryTypes.Save(pStm);
    FactoryProducedAircraftTypes.Save(pStm);

    int i;
    int count = Supers.Count;
    HRESULT hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Supers.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = RelatedTags.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&RelatedTags.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = AngerNodes.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&AngerNodes.Items[i], 8, 0);
        if (hr < 0)
            return hr;
    }
    count = ScoutNodes.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&ScoutNodes.Items[i], 8, 0);
        if (hr < 0)
            return hr;
    }
    count = ConYards.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&ConYards.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = Buildings.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Buildings.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = UnitRepairStations.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&UnitRepairStations.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = Grinders.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Grinders.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = Absorbers.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Absorbers.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = Bunkers.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Bunkers.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = Occupiables.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&Occupiables.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = CloningVats.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&CloningVats.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = SecretLabs.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&SecretLabs.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = PsychicDetectionBuildings.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&PsychicDetectionBuildings.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = FactoryPlants.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = pStm->Write(&FactoryPlants.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    count = StartingUnits.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        HouseStartingUnit* unit = StartingUnits.Items[i];
        hr = pStm->Write(unit, 4, 0);
        if (hr < 0)
            return hr;
        hr = pStm->Write(&unit->X, 2, 0);
        if (hr < 0)
            return hr;
        hr = pStm->Write(&unit->Y, 2, 0);
        if (hr < 0)
            return hr;
    }

    int hasAIGeneral = AIGeneral != 0;
    result = pStm->Write(&hasAIGeneral, 4, 0);
    if (result >= 0 && hasAIGeneral) {

    IUnknown* general = AIGeneral;
    IPersistStream* persist = 0;
    if (general) {
        IPersistStream* queried;
        HRESULT queryResult = general->QueryInterface(DAT_00820270, (void**)&queried);
        persist = FAILED(queryResult) ? 0 : queried;
        if (!SUCCEEDED(queryResult) && queryResult != E_NOINTERFACE)
            HouseComIssueError(queryResult);
    }
    result = OleSaveToStream(persist, pStm);
    if (persist)
        persist->Release();
    }
    }
    return result;
}

// FUNCTION: GAMEMD 0x5046F0
HRESULT __stdcall HouseClusterView::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;

    *pClassID = CLSID_House;
    return S_OK;
}

// FUNCTION: GAMEMD 0x504730
int HouseClusterView::Size()
{
    return sizeof(HouseClusterView);
}

// FUNCTION: GAMEMD 0x50E340
ULONG __stdcall HouseClusterView::AddRef()
{
    return 1;
}

// FUNCTION: GAMEMD 0x50E350
ULONG __stdcall HouseClusterView::Release()
{
    return 1;
}

// FUNCTION: GAMEMD 0x50E360
int HouseClusterView::WhatAmI()
{
    return 13;
}

// FUNCTION: GAMEMD 0x50E370
int HouseClusterView::vf_16()
{
    return ArrayIndex;
}

// SYNTHETIC: GAMEMD 0x50E380 -- compiler-generated scalar deleting destructor.
// SYNTHETIC: GAMEMD 0x510A20 -- compiler-generated QueryInterface adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A30 -- compiler-generated AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A40 -- compiler-generated Release adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A50 -- compiler-generated QueryInterface adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A60 -- compiler-generated AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A70 -- compiler-generated Release adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A80 -- compiler-generated QueryInterface adjustor thunk.
// SYNTHETIC: GAMEMD 0x510A90 -- compiler-generated AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AA0 -- compiler-generated Release adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AB0 -- compiler-generated GetIndex adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AC0 -- compiler-generated GetName adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AD0 -- compiler-generated QueryInterface adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AE0 -- compiler-generated AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x510AF0 -- compiler-generated Release adjustor thunk.

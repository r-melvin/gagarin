// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// BuildingTypeClass entries (layout and evidence: types_building_type_class.h).

#include "types_building_shared.h"

// GLOBAL: GAMEMD 0x7E95C0 - CLSID of BuildingTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_BuildingType =
    { 0xAE8B33DB, 0x061C, 0x11D2, { 0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

// CAPPED at 83.4% aligned-instruction match (322 of 386 retail instructions; 389 compiled). Observed delta:
// retail reserves an 8-byte stack local (`sub esp,8`) and uses EBP for the anim-slot pointer, loading the
// zero for X, Y and the strings from three different registers; this build has no local and uses EDI for the
// pointer with one zero register. The array-registration tail differs by register choice only (retail
// `mov eax,Count; mov ecx,Capacity`, this build the reverse). Forms tried: all scalar members in the
// initialiser list with plain Point2D constructors (74.6%); coordinate members built with a 3-argument
// constructor (76.2%); Point2D members built through a by-value helper (78.8%); the docking vector element left
// unconstructed with its three zero stores moved to the end (83.4%, kept); the anim-slot loop as a struct
// constructor (66.8%, dropped) and as a memset/assignment variants (82.6% to 83.4%).
// FUNCTION: GAMEMD 0x45DD90
BuildingTypeClass::BuildingTypeClass(const char* id)
    : TypesBuildingTypeTechnoView(id, 0), ArrayIndex(-1), FoundationData(0), Buildup(0),
      BuildupLoaded(false), BuildCat(0), HalfDamageSmokeLocation1(TypesZeroCoord),
      HalfDamageSmokeLocation2(TypesZeroCoord), GateCloseDelay(0.0), LightVisibility(5000),
      LightIntensity(0), LightRedTint(1000000), LightGreenTint(1000000), LightBlueTint(1000000),
      PrimaryFirePixelOffset(TypesMakePoint(0xFFFF, 0xFFFF)), SecondaryFirePixelOffset(TypesMakePoint(0xFFFF, 0xFFFF)), ToOverlay(0), ToTile(0), BuildupSound(-1), PackupSound(-1), CreateUnitSound(-1),
      UnitEnterSound(-1), UnitExitSound(-1), WorkingSound(-1), NotWorkingSound(-1), FreeUnit(0),
      SecretInfantry(0), SecretUnit(0), SecretBuilding(0), unknown_EB0(-1), Adjacent(3), Factory(0),
      TargetCoordOffset(0, 0, 0), ExitCoord(0, 0, 0), FoundationOutside(0), unknown_ED8(0), DeployFacing(0x80), PowerBonus(0), PowerDrain(0),
      ExtraPowerBonus(0), ExtraPowerDrain(0), Foundation(0), Height(2), OccupyHeight(2), MidPoint(0),
      DoorStages(0), Upgrades(0), DeployingAnim(0), UnderDoorAnim(0), Rubble(0), RoofDeployingAnim(0),
      UnderRoofDoorAnim(0), DoorAnim(0), SpecialZOverlay(0), SpecialZOverlayZAdjust(0), BibShape(0),
      BibShapeLoaded(false), NormalZAdjust(0), AntiAirValue(0), AntiArmorValue(0),
      AntiInfantryValue(0), ZShapePointMove(TypesMakePoint(0, 0)), unknown_1538(TypesZeroQuad), ExtraLight(0), TogglePower(true),
      HasSpotlight(false), IsTemple(false), IsPlug(false), HoverPad(false), BaseNormal(true),
      EligibileForAllyBuilding(false), EligibleForDelayKill(false), NeedsEngineer(false),
      CaptureEvaEvent(-1), ProduceCashStartup(0), ProduceCashAmount(0), ProduceCashDelay(0),
      InfantryGainSelfHeal(0), UnitsGainSelfHeal(0), RefinerySmokeFrames(25), Bib(false), Wall(false),
      Capturable(false), Powered(false), PoweredSpecial(false), Overpowerable(false), Spyable(false),
      CanC4(true), WantsExtraSpace(false), Unsellable(false), ClickRepairable(true),
      CanBeOccupied(false), CanOccupyFire(false), MaxNumberOccupants(0), ShowOccupantPips(true),
      QueueingCell(TypesMakePoint(0, 0)), NumberImpassableRows(-1), Radar(false), SpySat(false), ChargeAnim(false), IsAnimDelayedFire(false),
      SiloDamage(false), UnitRepair(false), UnitReload(false), Bunker(false), Cloning(false),
      Grinding(false), UnitAbsorb(false), InfantryAbsorb(false), SecretLab(false), DoubleThick(false),
      Flat(false), DockUnload(false), Recoilless(false), HasStupidGuardMode(true),
      BridgeRepairHut(false), Gate(false), SAM(false), ConstructionYard(false), NukeSilo(false),
      Refinery(false), Weeder(false), WeaponsFactory(false), LaserFencePost(false), LaserFence(false),
      FirestormWall(false), Hospital(false), Armory(false), EMPulseCannon(false), TickTank(false),
      TurretAnimIsVoxel(false), BarrelAnimIsVoxel(false), CloakGenerator(false), SensorArray(false),
      ICBMLauncher(false), Artillary(false), Helipad(false), OrePurifier(false), FactoryPlant(false),
      InfantryCostBonus(1.0f), UnitsCostBonus(1.0f), AircraftCostBonus(1.0f), BuildingsCostBonus(1.0f),
      DefensesCostBonus(1.0f), GDIBarracks(false), NODBarracks(false), YuriBarracks(false),
      ChargedAnimTime(1000.0f), DelayedFireDelay(0), SuperWeapon(-1), SuperWeapon2(-1), GateStages(9),
      PowersUpToLevel(-1), DamagedDoor(false), InvisibleInGame(false), TerrainPalette(false),
      PlaceAnywhere(false), ExtraDamageStage(true), AIBuildThis(false), IsBaseDefense(false),
      CloakRadiusInCells(20), ConcentricRadialIndicator(false), PsychicDetectionRadius(0),
      BarrelStartPitch(0x40), DemandLoad(false), DemandLoadBuildup(false), FreeBuildup(false),
      IsThreatRatingNode(false), PrimaryFireDualOffset(false), ProtectWithWall(false),
      CanHideThings(true), CrateBeneath(false), LeaveRubble(false), CrateBeneathIsMoney(false),
      NumberOfDocks(1), DockingOffsets(1, 0)
{
    HBRttiBase::Create_ID();
    TypesAddItemEarlyOut(TypesBuildingTypeArray, this);
    ArrayIndex = TypesFindIndex(TypesBuildingTypeArray, this);
    BuildingAnimFrame[0].Start = 0;
    BuildingAnimFrame[0].Count = 1;
    BuildingAnimFrame[0].Rate = 0;
    BuildingAnimFrame[1].Start = 0;
    BuildingAnimFrame[1].Count = 1;
    BuildingAnimFrame[1].Rate = 0;
    BuildingAnimFrame[2].Start = 0;
    BuildingAnimFrame[2].Count = 1;
    BuildingAnimFrame[2].Rate = 0;
    BuildingAnimFrame[4].Start = 0;
    BuildingAnimFrame[4].Count = 1;
    BuildingAnimFrame[4].Rate = 0;
    BuildingAnimFrame[5].Start = 0;
    BuildingAnimFrame[5].Count = 1;
    BuildingAnimFrame[5].Rate = 0;
    int i;
    for (i = 0; i < 21; ++i) {
        BuildingTypeAnim& anim = BuildingAnim[i];
        memset(anim.Anim, 0, sizeof(anim.Anim));
        memset(anim.Damaged, 0, sizeof(anim.Damaged));
        memset(anim.Garrisoned, 0, sizeof(anim.Garrisoned));
        anim.X = 0;
        anim.Y = 0;
        anim.ZAdjust = 0;
        anim.YSort = 0;
        anim.Powered = true;
        anim.PoweredLight = false;
        anim.PoweredEffect = false;
        anim.PoweredSpecial = false;
    }
    BuildupFile[0] = 0;
    PowersUpBuilding[0] = 0;
    TheaterSpecificID[0] = 0;
    VoxelBarrelFile[0] = 0;
    unknown_C8E = false;
    DeployingAnimLoaded = false;
    UnderDoorAnimLoaded = false;
    RubbleLoaded = false;
    RoofDeployingAnimLoaded = false;
    UnderRoofDoorAnimLoaded = false;
    for (i = 0; i < 10; ++i) {
        MuzzleFlash[i].X = TypesZeroCoord.X;
        MuzzleFlash[i].Y = TypesZeroCoord.Y;
    }
    for (i = 0; i < 8; ++i) {
        DamageFireOffset[i].X = TypesZeroCoord.X;
        DamageFireOffset[i].Y = TypesZeroCoord.Y;
    }
    for (i = 0; i < 8; ++i) {
        RemoveOccupy[i].X = 0xFFFF;
        RemoveOccupy[i].Y = 0xFFFF;
        AddOccupy[i].X = 0xFFFF;
        AddOccupy[i].Y = 0xFFFF;
    }
    unknown_D35 = true;
    unknown_D36 = true;
    unknown_D3B = false;
    unknown_D38 = false;
    unknown_D97 = false;
    unknown_D96 = false;
    unknown_D2E = false;
    TypesDockCoord* dock = DockingOffsets.Items;
    dock->X = 0;
    dock->Y = 0;
    dock->Z = 0;
}

// FUNCTION: GAMEMD 0x45E800
bool BuildingTypeClass::vf_32(void* where, void* owner)
{
    TypesBuildingView* building = new TypesBuildingView(this, owner);
    if (building) {
        const HBCell* cell = (const HBCell*)where;
        HBCoord coord;
        coord.X = cell->X * 256 + 128;
        coord.Y = cell->Y * 256 + 128;
        coord.Z = 0;
        return building->Unlimbo(&coord, 0);
    }
    return false;
}

// FUNCTION: GAMEMD 0x45E880
void* BuildingTypeClass::vf_35(void* owner)
{
    return new TypesBuildingView(this, owner);
}

// FUNCTION: GAMEMD 0x45EBD0
HBCoord BuildingTypeClass::vf_30()
{
    int width;
    int height;
    TypesShapeView* shape = (TypesShapeView*)vf_39();
    if (shape) {
        TypesFrameRect tmp;
        TypesFrameRect rect = *shape->GetFrameRect(&tmp, 0);
        width = rect.W;
        height = rect.H;
    } else {
        width = 0;
        height = 0;
    }
    HBCoord coord;
    coord.X = width;
    coord.Y = width;
    coord.Z = height;
    return coord;
}

// FUNCTION: GAMEMD 0x45EC20
// The function-local static (guard bit 0 of 0x89C890, cell at 0x89C8E8) is built through a temporary;
// its destructor stub is the bare RET at 0x45EC80 (compiler-generated atexit entry).
void* BuildingTypeClass::vf_36(bool arg)
{
    static TypesStaticCell list = TypesMakeStaticCell(0x7FFF, 0x7FFF);
    void* data = FoundationData;
    if (data == 0)
        data = &list;
    return data;
}

// FUNCTION: GAMEMD 0x45ECE0
int BuildingTypeClass::vf_29()
{
    int pips = TypesFoundationWidth[Foundation] * 60 / 8;
    switch (unknown_3D4) {
    case 2:
        if (Weeder) {
            int limit = TypesRules->unknown_17D0;
            if (limit < 0)
                return 0;
            if (limit > pips)
                return pips;
            return limit;
        } else {
            int limit = unknown_800;
            if (limit < 0)
                return 0;
            if (limit > pips)
                return pips;
            return limit;
        }
    case 4:
        return pips;
    }
    return TypesBuildingTypeTechnoView::vf_29();
}

// CAPPED at 20.3% (12 of 59 instructions by position; the instruction sequence has the same shape). Observed
// delta: register assignment only. Retail holds `this` in EBX, the argument in EBP, the running cost in ESI and
// the first PadAircraft type in EDI and evaluates the second type's cost first, spilling it to [esp+0x14]; this
// build holds the argument in EBX, `this` in EDI/EBP and calls the first type first. Forms tried: seven
// (cached rules pointer or not, second-first and first-first call order, an explicit temporary for each cost,
// early-return and fall-through tails, `freeUnit` loaded early or late).
// FUNCTION: GAMEMD 0x45EDD0
int BuildingTypeClass::vf_33(int house)
{
    int cost = TypesBuildingTypeTechnoView::vf_33(house);
    TypesCostTypeView** padAircraft = TypesRules->PadAircraft;
    TypesCostTypeView* first = padAircraft[0];
    if ((void*)this == (void*)first->DockItems[0] && !TypesRules->unknown_17E8) {
        int a = padAircraft[1]->GetCost(house);
        int b = first->GetCost(house);
        cost += (a + b) / 2;
    }
    TypesCostTypeView* freeUnit = (TypesCostTypeView*)FreeUnit;
    if (freeUnit) {
        cost += freeUnit->GetCost(house);
        return cost <= 0 ? 0 : cost;
    }
    return cost;
}

// FUNCTION: GAMEMD 0x45F040
void* BuildingTypeClass::vf_39()
{
    if (Image == 0 && DemandLoad) {
        const char* theater = TheaterSpecificID;
        if (theater[0]) {
            TypesFileView file(theater);
            file.Open(0);
            Image = file.ReadShape();
            if (Image) {
                ImageAllocated = true;
            } else {
                char name[260];
                strncpy(name, theater, 0x13);
                TypesStampGenericTheater(name);
                TypesFileView file2(name);
                Image = file2.ReadShape();
                if (Image)
                    ImageAllocated = true;
            }
        }
        return Image;
    }
    return Image;
}

// FUNCTION: GAMEMD 0x464A70
HBCoord BuildingTypeClass::vf_27(const HBCoord* in)
{
    HBCoord coord = *in;
    coord.Z = TypesMap.GetFloorHeight(&coord);
    return coord;
}

// FUNCTION: GAMEMD 0x464AC0
bool BuildingTypeClass::vf_42(void* arg1, void* arg2)
{
    if (PlaceAnywhere)
        return true;
    return TypesBuildingTypeTechnoView::vf_42(arg1, arg2);
}

// FUNCTION: GAMEMD 0x464AF0
HBCoord BuildingTypeClass::vf_31()
{
    HBCoord coord;
    coord.X = TypesFoundationWidth[Foundation] << 8;
    coord.Y = TypesFoundationHeight[Foundation] << 8;
    coord.Z = Height * TypesLevelHeight;
    return coord;
}

// FUNCTION: GAMEMD 0x464B30
void BuildingTypeClass::ComputeCRC(TypesCrcView& crc)
{
    TypesBuildingTypeTechnoView::ComputeCRC(crc);
    crc.AddDouble(GateCloseDelay);
    crc.AddInt(LightVisibility);
    crc.AddInt(LightIntensity);
    crc.AddInt(LightRedTint);
    crc.AddInt(LightGreenTint);
    crc.AddInt(LightBlueTint);
    crc.AddString(BuildupFile);
    crc.AddString(PowersUpBuilding);
    crc.AddInt(Adjacent);
    crc.AddInt(Factory);
    crc.AddInt(PowerBonus);
    crc.AddInt(PowerDrain);
    crc.AddInt(ExtraPowerBonus);
    crc.AddInt(ExtraPowerDrain);
    crc.AddInt(Foundation);
    crc.AddInt(Height);
    crc.AddInt(OccupyHeight);
    crc.AddInt(MidPoint);
    crc.AddInt(DoorStages);
    crc.AddBytes(BuildingAnimFrame, sizeof(BuildingAnimFrame));
    crc.AddBytes(BuildingAnim, sizeof(BuildingAnim));
    crc.AddInt(Upgrades);
    crc.AddInt(SpecialZOverlayZAdjust);
    crc.AddBool(HoverPad);
    crc.AddBool(IsPlug);
    crc.AddBool(IsTemple);
    crc.AddBool(HasSpotlight);
    crc.AddBool(BaseNormal);
    crc.AddBool(EligibileForAllyBuilding);
    crc.AddBool(NeedsEngineer);
    crc.AddBool(Bib);
    crc.AddBool(Wall);
    crc.AddBool(Capturable);
    crc.AddBool(Powered);
    crc.AddBool(Unsellable);
    crc.AddBool(Radar);
    crc.AddBool(SpySat);
    crc.AddBool(ChargeAnim);
    crc.AddBool(IsAnimDelayedFire);
    crc.AddInt(DelayedFireDelay);
    crc.AddBool(SiloDamage);
    crc.AddBool(UnitRepair);
    crc.AddBool(UnitReload);
    crc.AddBool(Cloning);
    crc.AddBool(Grinding);
    crc.AddBool(UnitAbsorb);
    crc.AddBool(InfantryAbsorb);
    crc.AddBool(SecretLab);
    crc.AddBool(Flat);
    crc.AddBool(DockUnload);
    crc.AddBool(Recoilless);
    crc.AddBool(BridgeRepairHut);
    crc.AddBool(Gate);
    crc.AddBool(SAM);
    crc.AddBool(ConstructionYard);
    crc.AddBool(NukeSilo);
    crc.AddBool(Refinery);
    crc.AddBool(WeaponsFactory);
    crc.AddBool(LaserFencePost);
    crc.AddBool(LaserFence);
    crc.AddBool(FirestormWall);
    crc.AddBool(Helipad);
    crc.AddBool(OrePurifier);
    crc.AddBool(ExtraDamageStage);
    crc.AddBool(Hospital);
    crc.AddBool(Armory);
    crc.AddInt(GateStages);
    crc.AddInt(PowersUpToLevel);
    crc.AddBool(DamagedDoor);
    crc.AddBool(InvisibleInGame);
    crc.AddBool(TerrainPalette);
    crc.AddBool(TurretAnimIsVoxel);
    crc.AddBool(BarrelAnimIsVoxel);
    crc.AddString(VoxelBarrelFile);
    crc.AddDouble(unknown_1728);
    crc.AddBytes(&VoxelBarrelOffsetToPitchPivotPoint, sizeof(HBCoord));
    crc.AddBytes(&VoxelBarrelOffsetToRotatePivotPoint, sizeof(HBCoord));
    crc.AddBytes(&VoxelBarrelOffsetToBuildingPivotPoint, sizeof(HBCoord));
    crc.AddBytes(&VoxelBarrelOffsetToBarrelEnd, sizeof(HBCoord));
    crc.AddBool(CrateBeneath);
    crc.AddBool(LeaveRubble);
    crc.AddBool(CrateBeneathIsMoney);
    crc.AddInt(NumberOfDocks);
    crc.AddInt(BarrelStartPitch);
    crc.AddBool(ConcentricRadialIndicator);
}

// CAPPED at 94.6% aligned-instruction match (192 of 203 retail instructions). Observed delta: only stack
// slots. Retail keeps the element count in the dead pStm argument slot and the loop index and the no-init
// temporary in the dead `this` slot; this build puts the count in the `this` slot and the index in the pStm slot,
// so six [esp+N] operands differ and the two-instruction foundation table address (`lea edx,[eax+0x89C900]`)
// is written with a relocation. Forms tried: count and index declared in different orders and at function
// scope; an initialised count; a named no-init tag; an extra stream alias; the count and loop in a nested block
// (kept, 94.6% against 89.7% without).
// FUNCTION: GAMEMD 0x465010
HRESULT __stdcall BuildingTypeClass::Load(IStream* pStm)
{
    if (FreeBuildup && Buildup) {
        gg_free(Buildup);
        Buildup = 0;
        BuildupLoaded = false;
    }
    if (BibShapeLoaded && BibShape) {
        gg_free(BibShape);
        BibShape = 0;
        BibShapeLoaded = false;
    }
    if (DeployingAnimLoaded && DeployingAnim) {
        gg_free(DeployingAnim);
        DeployingAnim = 0;
        DeployingAnimLoaded = false;
    }
    if (UnderDoorAnimLoaded && UnderDoorAnim) {
        gg_free(UnderDoorAnim);
        UnderDoorAnim = 0;
        UnderDoorAnimLoaded = false;
    }
    if (RubbleLoaded && Rubble) {
        gg_free(Rubble);
        Rubble = 0;
        RubbleLoaded = false;
    }
    if (RoofDeployingAnimLoaded && RoofDeployingAnim) {
        gg_free(RoofDeployingAnim);
        RoofDeployingAnim = 0;
        RoofDeployingAnimLoaded = false;
    }
    if (UnderRoofDoorAnimLoaded && UnderRoofDoorAnim) {
        gg_free(UnderRoofDoorAnim);
        UnderRoofDoorAnim = 0;
        UnderRoofDoorAnimLoaded = false;
    }

    HRESULT hr = TypesBuildingTypeTechnoView::Load(pStm);
    if (hr < 0)
        return hr;

    new (this) BuildingTypeClass(HBNoInit());

    {
    int count;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;

    new (&DockingOffsets) VectorClass<TypesDockCoord>;
    DockingOffsets.SetCapacity(count, 0);
    for (int i = 0; i < count; ++i) {
        TypesDockCoord coord;
        coord.X = 0;
        coord.Y = 0;
        coord.Z = 0;
        hr = pStm->Read(&coord, sizeof(coord), 0);
        if (hr < 0)
            return hr;
        DockingOffsets.Items[i] = coord;
    }
    }

    LoadFixup();
    PostLoad();
    FoundationData = &TypesFoundationCells[Foundation];
    FoundationOutside = &TypesFoundationOutsideCells[Foundation];
    ToTile = 0;
    TypesSwizzle.Swizzle(&ToOverlay);
    TypesSwizzle.Swizzle(&FreeUnit);
    TypesSwizzle.Swizzle(&SecretInfantry);
    TypesSwizzle.Swizzle(&SecretUnit);
    TypesSwizzle.Swizzle(&SecretBuilding);
    LoadFixup();
    Buildup = 0;
    BuildupLoaded = false;
    BibShape = 0;
    BibShapeLoaded = false;
    DeployingAnim = 0;
    DeployingAnimLoaded = false;
    UnderDoorAnim = 0;
    UnderDoorAnimLoaded = false;
    Rubble = 0;
    RubbleLoaded = false;
    RoofDeployingAnim = 0;
    RoofDeployingAnimLoaded = false;
    UnderRoofDoorAnim = 0;
    UnderRoofDoorAnimLoaded = false;
    StampTheater(TypesScenario->TheaterIndex);
    return S_OK;
}

// FUNCTION: GAMEMD 0x465300
HRESULT __stdcall BuildingTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = TypesBuildingTypeTechnoView::Save(pStm, fClearDirty);
    if (hr < 0)
        return hr;

    int count = DockingOffsets.Capacity;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (int i = 0; i < count; ++i) {
        hr = pStm->Write(&DockingOffsets.Items[i], sizeof(TypesDockCoord), 0);
        if (hr < 0)
            return hr;
    }
    return S_OK;
}

// FUNCTION: GAMEMD 0x465380
HRESULT __stdcall BuildingTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_BuildingType;
    return S_OK;
}

// FUNCTION: GAMEMD 0x465910
bool BuildingTypeClass::vf_40()
{
    return false;
}

// FUNCTION: GAMEMD 0x465920
bool BuildingTypeClass::vf_41()
{
    return false;
}

// FUNCTION: GAMEMD 0x465960
void* BuildingTypeClass::vf_48()
{
    if (Buildup == 0 && DemandLoadBuildup) {
        if (strlen(BuildupFile)) {
            char path[260];
            _makepath(path, 0, 0, BuildupFile, TypesShpExtension);
            TypesStampTheater(path, TypesScenario->TheaterIndex);
            TypesFileView file(path);
            void* shape = file.ReadShape();
            if (shape == 0) {
                TypesStampGenericTheater(path);
                TypesFileView file2(path);
                shape = file2.ReadShape();
            }
            Buildup = shape;
            if (shape) {
                BuildupLoaded = true;
                int rate = 1;
                int frames = ((short*)shape)[3] / 2;
                if (Gate)
                    frames = GateStages + 1;
                if (frames > 0)
                    rate = (int)(TypesRules->unknown_1518 * 900.0 / frames);
                BuildingAnimFrame[0].Start = 0;
                BuildingAnimFrame[0].Count = frames;
                BuildingAnimFrame[0].Rate = rate;
            }
        }
        return Buildup;
    }
    return Buildup;
}

// FUNCTION: GAMEMD 0x465D90
int BuildingTypeClass::WhatAmI()
{
    return 7;
}

// FUNCTION: GAMEMD 0x465DA0
int BuildingTypeClass::Size()
{
    return 0x1798;
}

// FUNCTION: GAMEMD 0x465DB0
int BuildingTypeClass::vf_16()
{
    return ArrayIndex;
}

// SYNTHETIC: GAMEMD 0x465DC0 -- compiler-generated scalar deleting destructor.

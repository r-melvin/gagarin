// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU039 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x45afa0-0x4660cf,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// BuildingTypeClass entries (layout and evidence: types_building_type_class.h).
//
// Retail RTTI names VectorClass/DynamicVectorClass over Cell, BaseNodeClass, TPoint3D<int>, Point2D,
// TRect<int> and DirtyAreaStruct. Element layouts and compare shapes are read from the FindItemIndex,
// Slot5, Slot6 and SetCapacity bodies; field names are placeholders.
//
// Find-by-name walks, ordered ascending by retail address, written out longhand
// per the family rule.
//
// Buffer-holder deleting destructors, ordered ascending by retail address.
//
// The buffer-release template, ordered ascending by retail address.
//
// Constant-return and identity leaves, ordered ascending by retail address.
//
// FindOrAllocate, ordered ascending by retail address, written out longhand per
// the family rule.
//
// The whole body sits inside one positive guard so that the single `return 0`
// lands in the trailing block, where retail has it at the very end. Written as
// three early `return 0` statements it scores 15.8% - every rejection gets its
// own inline epilogue and everything after shifts.
//
//   Bytes compared against retail gamemd.exe v1.001 at each address below.
//
// Leaf accessors, ordered ascending by retail address.
//
// BuildingTypeClass::ReadINI (0x45FE50, 0x4C06 bytes): the rules-INI reader. Every key string, default and
// member offset was read from the retail instructions; the statement order is the retail order. The art-INI
// (global 0x887180) reads use the object's image name as their section; the rules reads use the object ID.
//
// The 18 animation slots are expanded by the local macros below, one invocation per slot. A function-style
// helper changes the generated code (the compiler stops expanding it after a few uses), so the repeated shape is
// kept as macros: read the three names (the damaged and garrisoned names fall back to the base name), then, if
// any name is set, the placement values and (where the slot has them) the four power flags. The four SuperAnim
// slots read their X and Y defaults from other slots' values (retail loads them from ActiveAnimFour, ActiveAnimTwo
// and ActiveAnimThree); TYPES_READ_ANIM_QUIRK reproduces that.

#include "house_building/types_building_shared.h"

// LIBRARY: GAMEMD 0x7C8B3D - CRT free.
extern "C" void __cdecl gg_free(void*);

// GLOBAL: GAMEMD 0x7E95C0 - CLSID of BuildingTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_BuildingType =
    { 0xAE8B33DB, 0x061C, 0x11D2, { 0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

#include "../core/guarded_forward_methods.h"

#include "../core/vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

struct Cell { short X; short Y; Cell() {} bool operator==(const Cell& o) const { return X==o.X && Y==o.Y; } bool operator!=(const Cell& o) const { return !(*this==o); } };

// VTABLE: GAMEMD 0x007E38D0 -- VectorClass<Cell>.
// VTABLE: GAMEMD 0x007E3890 -- DynamicVectorClass<Cell>.
template class VectorClass<Cell>;
template class DynamicVectorClass<Cell>;

 struct BaseNodeClass { int unknown_00; Cell unknown_04; unsigned char unknown_08; int unknown_0C; BaseNodeClass() {} BaseNodeClass(const BaseNodeClass& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {} bool operator==(const BaseNodeClass& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; } bool operator!=(const BaseNodeClass& o) const { return !(*this==o); } };

// VTABLE: GAMEMD 0x007E38F0 -- VectorClass<BaseNodeClass>.
// VTABLE: GAMEMD 0x007E38B0 -- DynamicVectorClass<BaseNodeClass>.
template class VectorClass<BaseNodeClass>;
template class DynamicVectorClass<BaseNodeClass>;

template<class T> struct TPoint3D { T X; T Y; T Z; TPoint3D() {} bool operator==(const TPoint3D<T>& o) const { return X==o.X && Y==o.Y && Z==o.Z; } bool operator!=(const TPoint3D<T>& o) const { return !(*this==o); } };

// VTABLE: GAMEMD 0x007E4638 -- VectorClass<TPoint3D<int>>.
template class VectorClass<TPoint3D<int> >;

#include "../_layout/geometry2d.h"
template class DynamicVectorClass<Point2D>;

template class DynamicVectorClass<TRect<int> >;

#include "../_layout/dirty_area.h"
template class DynamicVectorClass<DirtyAreaStruct>;

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0045B1B0;
struct Obj_0045C2F0;
struct Obj_00465D80;

struct Obj_0045B1B0
{
    // FUNCTION: GAMEMD 0x45B1B0
    void FUN_0045B1B0();
    // FUNCTION: GAMEMD 0x45B1C0
    void FUN_0045B1C0();
};

struct Obj_0045C2F0
{
    // FUNCTION: GAMEMD 0x45C2F0
    void FUN_0045C2F0();
    // FUNCTION: GAMEMD 0x45C300
    void FUN_0045C300();
};

struct Obj_00465D80
{
    // FUNCTION: GAMEMD 0x465D80
    Obj_00465D80* FUN_00465D80();
};


void __cdecl FUN_0045EC80();


#include "../core/find_by_name_methods.h"

#include "../core/small_misc51_methods.h"

#include "../ai/threat_budget_methods.h"

#include "../core/buffer_holder_dtor_methods.h"

#include "../core/buffer_release_methods.h"

#include "../core/const_return_stub_methods.h"

#include "../core/find_or_allocate_methods.h"

#include "../core/leaf_accessor_methods.h"

#include "../core/name_value_lookup_methods.h"

#include "../core/small_misc50_methods.h"

#include <stdio.h>
#include <stdlib.h>
#include "house_building/types_building_shared.h"

#define TYPES_ANIM_NAME(INI, SECTION, FIELD, KEY)                           \
    (INI).ReadString(SECTION, KEY, TypesEmptyText, animName, 0x10);          \
    if (strlen(animName))                                                    \
        strcpy(FIELD, animName);

#define TYPES_ANIM_NAMES(INI, SECTION, ANIM, PREFIX)                         \
    TYPES_ANIM_NAME(INI, SECTION, (ANIM).Anim, PREFIX)                       \
    TYPES_ANIM_NAME(INI, SECTION, (ANIM).Damaged, PREFIX "Damaged")          \
    if (!strlen((ANIM).Damaged))                                             \
        strcpy((ANIM).Damaged, (ANIM).Anim);                                 \
    TYPES_ANIM_NAME(INI, SECTION, (ANIM).Garrisoned, PREFIX "Garrisoned")    \
    if (!strlen((ANIM).Garrisoned))                                          \
        strcpy((ANIM).Garrisoned, (ANIM).Anim);

#define TYPES_ANIM_PRESENT(ANIM) \
    (strlen((ANIM).Anim) || strlen((ANIM).Damaged) || strlen((ANIM).Garrisoned))

#define TYPES_ANIM_VALUES(INI, SECTION, ANIM, PREFIX, DEFX, DEFY)            \
    (ANIM).X = (INI).ReadInt(SECTION, PREFIX "X", DEFX);                     \
    (ANIM).Y = (INI).ReadInt(SECTION, PREFIX "Y", DEFY);                     \
    (ANIM).ZAdjust = (INI).ReadInt(SECTION, PREFIX "ZAdjust", (ANIM).ZAdjust); \
    (ANIM).YSort = (INI).ReadInt(SECTION, PREFIX "YSort", (ANIM).YSort);

#define TYPES_ANIM_FLAGS(INI, SECTION, ANIM, PREFIX)                         \
    (ANIM).Powered = (INI).ReadBool(SECTION, PREFIX "Powered", (ANIM).Powered); \
    (ANIM).PoweredLight = (INI).ReadBool(SECTION, PREFIX "PoweredLight", (ANIM).PoweredLight); \
    (ANIM).PoweredEffect = (INI).ReadBool(SECTION, PREFIX "PoweredEffect", (ANIM).PoweredEffect); \
    (ANIM).PoweredSpecial = (INI).ReadBool(SECTION, PREFIX "PoweredSpecial", (ANIM).PoweredSpecial);

#define TYPES_READ_ANIM(ANIM, PREFIX)                                        \
    TYPES_ANIM_NAMES(TypesArtIni, ImageFile, ANIM, PREFIX)                   \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(TypesArtIni, ImageFile, ANIM, PREFIX, (ANIM).X, (ANIM).Y) \
        TYPES_ANIM_FLAGS(TypesArtIni, ImageFile, ANIM, PREFIX)               \
    }

#define TYPES_READ_ANIM_QUIRK(ANIM, PREFIX, DEFX, DEFY)                      \
    TYPES_ANIM_NAMES(TypesArtIni, ImageFile, ANIM, PREFIX)                   \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(TypesArtIni, ImageFile, ANIM, PREFIX, DEFX, DEFY)  \
        TYPES_ANIM_FLAGS(TypesArtIni, ImageFile, ANIM, PREFIX)               \
    }

#define TYPES_READ_ANIM_NOBOOLS(ANIM, PREFIX)                                \
    TYPES_ANIM_NAMES(TypesArtIni, ImageFile, ANIM, PREFIX)                   \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(TypesArtIni, ImageFile, ANIM, PREFIX, (ANIM).X, (ANIM).Y) \
    }

// The turret slot is read from the rules INI under the object ID.
#define TYPES_READ_ANIM_NOBOOLS_RULES(ANIM, PREFIX)                          \
    TYPES_ANIM_NAMES(*ini, ID, ANIM, PREFIX)                                 \
    if (TYPES_ANIM_PRESENT(ANIM)) {                                          \
        TYPES_ANIM_VALUES(*ini, ID, ANIM, PREFIX, (ANIM).X, (ANIM).Y)        \
    }

// CAPPED at 72.2% aligned-instruction match (4204 of 5819 retail instructions; 5861 compiled); 91.0% when
// register names are ignored. Observed delta, all of it layout and scheduling rather than missing statements:
//  - the stack frame is 12 bytes larger than retail's (sub esp,0x364 against 0x358), which shifts every
//    esp-relative local and the incoming argument by 12; with that shift removed the frame-text and
//    default-text buffers (0x140/0x180 in retail) are swapped;
//  - retail keeps `this` in EBP, the section pointer in EBX (ESI early on) and the reader in ESI (EDI early on);
//    this build puts `this` in EBX, the section pointer in EBP and the reader in ESI;
//  - the MuzzleFlash / DamageFireOffset loops: retail walks the member array through a pointer kept in a stack
//    slot and compares against a register holding 0xFFFF that is also the default's source; this build indexes
//    the array and compares against immediates (the pointer-walking form was tried and scored 71.6%);
//  - the RemoveOccupy / AddOccupy defaults and the coordinate defaults are built in different stack temporaries.
// Forms tried: (1) every buffer declared inside its own block (66.6%); (2) every buffer declared once at function
// scope, giving the key and name buffers retail's shared addresses (72.2%, kept); (3) the occupancy loops with a
// running pointer (71.6%, dropped). The anim-slot macros, the unmodified statement order and all key strings
// are as retail.

#include "../renderer/font_bias_methods.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E4530
extern const double DAT_007E4530;
// GLOBAL: GAMEMD 0x89C8B8
extern double DAT_0089C8B8;

// SYNTHETIC: GAMEMD 0x45AFD0
// GLOBAL: GAMEMD 0x89D360
double DAT_0089D360 = DAT_0089C8B8 / DAT_007E4530;

// SYNTHETIC: GAMEMD 0x45AFF0
// GLOBAL: GAMEMD 0x89C8F8
double DAT_0089C8F8 = DAT_007E1718 / DAT_0089D360;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45B1B0
// Tail-forwards to another function.
void Obj_0045B1B0::FUN_0045B1B0()
{
    FUN_0045B1C0();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45C2F0
// Tail-forwards to another function.
void Obj_0045C2F0::FUN_0045C2F0()
{
    FUN_0045C300();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45DD50
//
// The same scan over the smaller table. Written out rather than shared.
int FUN_0045DD50(const char* name)
{
    for (int i = 0; i < 6; i++) {
        if (FUN_007C8D20(DAT_00819288[i].Name, name) == 0) {
            return DAT_00819288[i].Value;
        }
    }

    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E520
// PARTIAL, 78.9% (15/19). Plain stores: cl lifts the `field_1790 = 1` byte
// store ahead of the three zero stores; retail emits it after them.
Obj_0045E520* Obj_0045E520::FUN_0045E520(int value)
{
    FUN_00711840(value);

    field_E00  = 0;
    field_1788 = 0;
    field_178C = 0;
    field_1790 = 1;
    field_1791 = 0;

    Secondary = &VT_007E4638;

    vt0 = &VT_007E4570;
    vt1 = &VT_007E4554;
    vt2 = &VT_007E454C;
    vt3 = &VT_007E4544;

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E760
int FUN_0045E760(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A83C78; i++) {
            if (FUN_007C8D20(DAT_00A83C6C[i] + 0x64, name) == 0) {
                return i;
            }
        }
    }

    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E7B0
int FUN_0045E7B0(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A83C78; i++) {
            if (FUN_007C8D20(DAT_00A83C6C[i] + 0x24, name) == 0) {
                return i;
            }
        }
    }

    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E880
void* BuildingTypeClass::vf_35(void* owner)
{
    return new TypesBuildingView(this, owner);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45E8F0
//
// Load the image once and rebias every non-zero pixel by 0x41, in place. The
// global is both the "already loaded" flag and the result, so a second call does
// nothing.
//
// Zero pixels are left alone rather than being biased to a negative value — that
// is what makes 0 the transparent index and everything else an offset into a
// palette that starts at 'A'.
//
// PARTIAL (95.3%, 41/43) — identical multiset. One register delta remains: the
// inner load and store swap the SIB base and index roles (`[EDX+ECX]` against
// `[ECX+EDX]`) — the cheap addressing class in section 4.8. The global-store
// ordering delta recorded earlier no longer shows in the current build.
//
// Eleven further spellings were measured this pass and every one holds at
// 86.0% or drops. For the global store: the surface bound to a local with the
// global assigned from it and the load call made through the local; the same
// with the call made through the global; the store folded into an inline
// `Store(p)` helper whose result is the call's receiver; the scratch buffer
// bound to a `void*` local first; the load call lifted into an inline helper
// taking the surface as `Image_0045E8F0* const&` (the lever that resolved
// 0x40A260); and a volatile-qualified store of the global (81.4%). For the SIB
// roles: the reversed subscript `x[row]`, the pointer form `*(row + x)`, an
// unsigned loop index (81.4%), and the row rebound to a `char* const line`
// inside the loop. The rebias walk lifted into its own inline function scores
// 81.4%, so the two loops are one function in retail.
//
// The cursor and the row counter are separate locals copied from the pixel
// pointer and the height, and that is load-bearing rather than style. Retail
// copies both (`MOV EDX,EAX; MOV EDI,ECX` at 0x45E94C) because the originals stay
// live; walking the returned pointer directly and counting down the height
// in place removes both copies and scores 16.3%. Two extra locals, seventy
// points.
void FUN_0045E8F0()
{
    char scratch[0x10];

    if (DAT_0089DDBC != 0) {
        return;
    }

    DAT_0089DDBC = FUN_005B40B0(&DAT_008193F4, 0);
    DAT_0089DDBC->FUN_0069E7E0(scratch, 0);
    char* pixels = DAT_0089DDBC->FUN_0069E740(0);

    int width = DAT_0089DDBC->Width;
    int height = DAT_0089DDBC->Height;
    if (height <= 0) {
        return;
    }

    char* row = pixels;
    int rows = height;
    do {
        for (int x = 0; x < width; x++) {
            if (row[x] != 0) {
                row[x] = row[x] - 0x41;
            }
        }
        row += width;
        rows--;
    } while (rows != 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45EC80
// Empty function.
void __cdecl FUN_0045EC80()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45ED50
//
// Start from the base budget, and when this object is the one the host's pair
// points at — and the host is not in the suppressed state — take off half the
// two measurements. Whatever the trailing object measures comes off as well,
// and that result is clamped at zero; the early exit is not clamped.
//
// PARTIAL (56.6%, 30/53). Everything up to and including the pair adjustment is
// byte-exact, including the callee-saved naming (budget in ESI, the pair entry
// in EDI). The whole residual is the trailing object: retail parks it in EBX —
// reusing the register that held `this`, which dies at that load — and pays a
// `MOV ECX,EBX` before the slot call, where VC6 loads it straight into ECX and
// skips the copy. Everything after is the same instruction stream renamed.
//
// The ESI/EDI half was fixed by phrasing: subtracting into a fresh local
// (`int r = budget - ...`) rather than back into `budget` lowers the budget
// variable's use count, and VC6 hands ESI to the lighter of the two. Written as
// `budget -= ...; return budget > 0 ? budget : 0` the names come out swapped
// (47.2%).
//
// The EBX half is not source-selectable so far. Rejected, all 56.6% or worse:
// a `this`-walking local reassigned to the trailing object; a `for`/`while`
// whose induction variable starts at `this` and whose body always returns; a
// reference instead of a pointer; re-reading `this->At_EA0` twice and letting
// CSE pick the register; a static inline wrapper around the slot call; a
// genuine `virtual` at slot 43 instead of the member-pointer idiom; declaring
// the locals `register`; and the flag sweep /G3 /G5 /G6 /GB /Gr /Gd /Zp1 /Oa
// /Ow /Gf /Ob0 /Ob2 /Ox (all identical). /O1 /Os and dropping /Oy change the
// whole function and score 0%.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EBP,
// ESI, EDI on both sides, none sunk), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
int BuildingTypeClass_0045ED50::FUN_0045ED50()
{
    int budget = FUN_00711EB0();
    Host_0045ED50* host = DAT_008871E0;
    BuildingTypeClass_0045ED50** pair = host->At_B5C;
    BuildingTypeClass_0045ED50* first = pair[0];

    if (this == *first->At_3EC && host->At_17E8 == 0) {
        BuildingTypeClass_0045ED50* second = pair[1];

        budget += -(((second->*second->Vptr->At_AC)()
                     + (first->*first->Vptr->At_AC)()) / 2);
    }

    BuildingTypeClass_0045ED50* trailing = this->At_EA0;
    if (trailing != 0) {
        int result = budget - (trailing->*trailing->Vptr->At_AC)();
        return result > 0 ? result : 0;
    }

    return budget;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45F160
//
// Same skeleton as 0x45F1D0 and the same trailing-block layout - retail's `JNZ`
// jumps forward to the cached case - but both successful paths answer true and
// the value written is a constant rather than the measurement. Written out
// longhand rather than shared with the sibling, per the family rule.
bool Obj_0045F1D0::FUN_0045F160(Shape_0045F1D0** shape, int* bias)
{
    if (Enabled && shape != 0) {
        Shape_0045F1D0* cached = Cached;

        if (cached == 0) {
            Shape_0045F1D0* fresh = vt_09C();

            *shape = fresh;

            if (fresh != 0) {
                if (fresh->Height / 2 > 3) {
                    *bias = 3;

                    return true;
                }
            }
        } else {
            *shape = cached;
            *bias  = 0;

            return true;
        }
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45F1D0
bool Obj_0045F1D0::FUN_0045F1D0(Shape_0045F1D0** shape, int* half)
{
    if (Enabled && shape != 0) {
        Shape_0045F1D0* cached = Cached;

        // The cached path is the *trailing* block: retail's `JNZ` at 0x45F1EB
        // jumps forward to it, so the fresh lookup is the fall-through and the
        // guard is written as `cached == 0`. The other way round scores 21.6%.
        if (cached == 0) {
            Shape_0045F1D0* fresh = vt_09C();

            *shape = fresh;

            if (fresh != 0) {
                int height = fresh->Height / 2;

                if (height > 3) {
                    *half = height + 3;

                    return true;
                }
            }
        } else {
            *shape = cached;
            *half  = cached->Height / 2;
        }
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x45FE50
bool BuildingTypeClass::ReadINI(TypesIniView* ini)
{
    int i;
    HBCoord coordDefault;
    char animName[0x80];
    TypesPoint2D pointDefault;
    TypesPoint2D pointDefault2;
    char name[0x80];
    char frameText[0x40];
    char frameDefault[0x40];
    char dockKey[0x20];
    char yKey[0x40];
    char sortKey[0x40];
    char animKey[0x40];
    char damagedKey[0x40];
    char zKey[0x40];
    char xKey[0x40];

    ini->ClearCache();
    if (TypesBuildingTypeTechnoView::ReadINI(ini)) {
        BuildCat = ini->ReadBuildCat(ID, "BuildCat", BuildCat);
        AntiInfantryValue = ini->ReadInt(ID, "AntiInfantryValue", AntiInfantryValue);
        AntiArmorValue = ini->ReadInt(ID, "AntiArmorValue", AntiArmorValue);
        AntiAirValue = ini->ReadInt(ID, "AntiAirValue", AntiAirValue);
        HasSpotlight = ini->ReadBool(ID, "HasSpotlight", HasSpotlight);
        HalfDamageSmokeLocation1 = ini->ReadCoord(ID, "HalfDamageSmokeLocation1", HalfDamageSmokeLocation1);
        HalfDamageSmokeLocation2 = ini->ReadCoord(ID, "HalfDamageSmokeLocation2", HalfDamageSmokeLocation2);
        Radar = ini->ReadBool(ID, "Radar", Radar);
        SpySat = ini->ReadBool(ID, "SpySat", SpySat);
        unknown_67C = ini->ReadBool(ID, "WaterBound", unknown_67C == 5) ? 5 : -1;
        Adjacent = ini->ReadInt(ID, "Adjacent", Adjacent);
        Capturable = ini->ReadBool(ID, "Capturable", Capturable);
        Powered = ini->ReadBool(ID, "Powered", Powered);
        PoweredSpecial = ini->ReadBool(ID, "PoweredSpecial", PoweredSpecial);
        Overpowerable = ini->ReadBool(ID, "Overpowerable", Overpowerable);
        Spyable = ini->ReadBool(ID, "Spyable", Spyable);
        CanC4 = ini->ReadBool(ID, "CanC4", CanC4);
        WantsExtraSpace = ini->ReadBool(ID, "WantsExtraSpace", WantsExtraSpace);
        Bib = ini->ReadBool(ID, "Bib", Bib);
        Unsellable = ini->ReadBool(ID, "Unsellable", Unsellable);
        ClickRepairable = ini->ReadBool(ID, "ClickRepairable", ClickRepairable);
        CanBeOccupied = ini->ReadBool(ID, "CanBeOccupied", CanBeOccupied);
        CanOccupyFire = ini->ReadBool(ID, "CanOccupyFire", CanOccupyFire);
        ShowOccupantPips = ini->ReadBool(ID, "ShowOccupantPips", ShowOccupantPips);
        MaxNumberOccupants = ini->ReadInt(ID, "MaxNumberOccupants", MaxNumberOccupants);
        NumberImpassableRows = ini->ReadInt(ID, "NumberImpassableRows", NumberImpassableRows);
        ProduceCashStartup = ini->ReadInt(ID, "ProduceCashStartup", ProduceCashStartup);
        ProduceCashAmount = ini->ReadInt(ID, "ProduceCashAmount", ProduceCashAmount);
        ProduceCashDelay = ini->ReadInt(ID, "ProduceCashDelay", ProduceCashDelay);
        InfantryGainSelfHeal = ini->ReadInt(ID, "InfantryGainSelfHeal", InfantryGainSelfHeal);
        UnitsGainSelfHeal = ini->ReadInt(ID, "UnitsGainSelfHeal", UnitsGainSelfHeal);
        RefinerySmokeFrames = ini->ReadInt(ID, "RefinerySmokeFrames", RefinerySmokeFrames);
        BaseNormal = ini->ReadBool(ID, "BaseNormal", BaseNormal);
        EligibileForAllyBuilding = ini->ReadBool(ID, "EligibileForAllyBuilding", EligibileForAllyBuilding);
        EligibleForDelayKill = ini->ReadBool(ID, "EligibleForDelayKill", EligibleForDelayKill);
        NeedsEngineer = ini->ReadBool(ID, "NeedsEngineer", NeedsEngineer);
        CaptureEvaEvent = ini->ReadEvaEvent(ID, "CaptureEvaEvent", CaptureEvaEvent);
        ProtectWithWall = ini->ReadBool(ID, "ProtectWithWall", ProtectWithWall);
        for (i = 0; i < MaxNumberOccupants; ++i) {
            char number[0x10];
            strcpy(animName, "MuzzleFlash");
            itoa(i, number, 10);
            strcat(animName, number);
            pointDefault = TypesMakePoint(0xFFFF, 0xFFFF);
            MuzzleFlash[i] = TypesArtIni.ReadPoint(ImageFile, animName, pointDefault);
            if (MuzzleFlash[i].X == 0xFFFF && MuzzleFlash[i].Y == 0xFFFF) {
                MuzzleFlash[i].X = 0;
                MuzzleFlash[i].Y = 0;
            }
        }
        for (i = 0; i < 8; ++i) {
            char number[0x10];
            strcpy(animName, "DamageFireOffset");
            itoa(i, number, 10);
            strcat(animName, number);
            pointDefault = TypesMakePoint(0xFFFF, 0xFFFF);
            DamageFireOffset[i] = TypesArtIni.ReadPoint(ImageFile, animName, pointDefault);
            if (DamageFireOffset[i].X == 0xFFFF && DamageFireOffset[i].Y == 0xFFFF) {
                DamageFireOffset[i].X = TypesZeroCoord.X;
                DamageFireOffset[i].Y = TypesZeroCoord.Y;
                break;
            }
        }
        Wall = ini->ReadBool(ID, "Wall", Wall);
        Weeder = ini->ReadBool(ID, "Weeder", Weeder);
        Helipad = ini->ReadBool(ID, "Helipad", Helipad);
        OrePurifier = ini->ReadBool(ID, "OrePurifier", OrePurifier);
        FactoryPlant = ini->ReadBool(ID, "FactoryPlant", FactoryPlant);
        Factory = ini->ReadFactory(ID, "Factory", Factory);
        {
            void* old = FreeUnit;
            FreeUnit = ini->ReadString(ID, "FreeUnit", TypesEmptyText, name, 0x80) ? (void*)TypesFindUnitType(name) : old;
        }
        HoverPad = ini->ReadBool(ID, "HoverPad", HoverPad);
        IsTemple = ini->ReadBool(ID, "IsTemple", IsTemple);
        IsPlug = ini->ReadBool(ID, "IsPlug", IsPlug);
        {
            void* old = SecretInfantry;
            SecretInfantry = ini->ReadString(ID, "SecretInfantry", TypesEmptyText, name, 0x80) ? (void*)TypesFindInfantryType(name) : old;
        }
        {
            void* old = SecretUnit;
            SecretUnit = ini->ReadString(ID, "SecretUnit", TypesEmptyText, name, 0x80) ? (void*)TypesFindUnitType(name) : old;
        }
        {
            void* old = SecretBuilding;
            SecretBuilding = ini->ReadString(ID, "SecretBuilding", TypesEmptyText, name, 0x80) ? TypesFindBuildingType(name, &TypesBuildingTypeArray) : old;
        }
        InfantryCostBonus = (float)ini->ReadDouble(ID, "InfantryCostBonus", InfantryCostBonus);
        UnitsCostBonus = (float)ini->ReadDouble(ID, "UnitsCostBonus", UnitsCostBonus);
        AircraftCostBonus = (float)ini->ReadDouble(ID, "AircraftCostBonus", AircraftCostBonus);
        BuildingsCostBonus = (float)ini->ReadDouble(ID, "BuildingsCostBonus", BuildingsCostBonus);
        DefensesCostBonus = (float)ini->ReadDouble(ID, "DefensesCostBonus", DefensesCostBonus);
        TogglePower = ini->ReadBool(ID, "TogglePower", TogglePower);
        {
            int sound = BuildupSound;
            if (ini->ReadString(ID, "BuildupSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = BuildupSound;
            }
            BuildupSound = sound;
        }
        {
            int sound = PackupSound;
            if (ini->ReadString(ID, "PackupSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = PackupSound;
            }
            PackupSound = sound;
        }
        {
            int sound = CreateUnitSound;
            if (ini->ReadString(ID, "CreateUnitSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = CreateUnitSound;
            }
            CreateUnitSound = sound;
        }
        {
            int sound = UnitExitSound;
            if (ini->ReadString(ID, "UnitExitSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = UnitExitSound;
            }
            UnitExitSound = sound;
        }
        {
            int sound = UnitEnterSound;
            if (ini->ReadString(ID, "UnitEnterSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = UnitEnterSound;
            }
            UnitEnterSound = sound;
        }
        {
            int sound = WorkingSound;
            if (ini->ReadString(ID, "WorkingSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = WorkingSound;
            }
            WorkingSound = sound;
        }
        {
            int sound = NotWorkingSound;
            if (ini->ReadString(ID, "NotWorkingSound", TypesEmptyText, name, 0x80)) {
                sound = TypesFindVoc(name);
                if (sound == -1)
                    sound = NotWorkingSound;
            }
            NotWorkingSound = sound;
        }
        UnitRepair = ini->ReadBool(ID, "UnitRepair", UnitRepair);
        UnitReload = ini->ReadBool(ID, "UnitReload", UnitReload);
        Bunker = ini->ReadBool(ID, "Bunker", Bunker);
        Cloning = ini->ReadBool(ID, "Cloning", Cloning);
        Grinding = ini->ReadBool(ID, "Grinding", Grinding);
        UnitAbsorb = ini->ReadBool(ID, "UnitAbsorb", UnitAbsorb);
        InfantryAbsorb = ini->ReadBool(ID, "InfantryAbsorb", InfantryAbsorb);
        SecretLab = ini->ReadBool(ID, "SecretLab", SecretLab);
        DockUnload = ini->ReadBool(ID, "DockUnload", DockUnload);
        Gate = ini->ReadBool(ID, "Gate", Gate);
        SAM = ini->ReadBool(ID, "SAM", SAM);
        ConstructionYard = ini->ReadBool(ID, "ConstructionYard", ConstructionYard);
        NukeSilo = ini->ReadBool(ID, "NukeSilo", NukeSilo);
        Refinery = ini->ReadBool(ID, "Refinery", Refinery);
        WeaponsFactory = ini->ReadBool(ID, "WeaponsFactory", WeaponsFactory);
        LaserFencePost = ini->ReadBool(ID, "LaserFencePost", LaserFencePost);
        LaserFence = ini->ReadBool(ID, "LaserFence", LaserFence);
        FirestormWall = ini->ReadBool(ID, "FirestormWall", FirestormWall);
        Hospital = ini->ReadBool(ID, "Hospital", Hospital);
        Armory = ini->ReadBool(ID, "Armory", Armory);
        GDIBarracks = ini->ReadBool(ID, "GDIBarracks", GDIBarracks);
        NODBarracks = ini->ReadBool(ID, "NODBarracks", NODBarracks);
        YuriBarracks = ini->ReadBool(ID, "YuriBarracks", YuriBarracks);
        EMPulseCannon = ini->ReadBool(ID, "EMPulseCannon", EMPulseCannon);
        TickTank = ini->ReadBool(ID, "TickTank", TickTank);
        ChargedAnimTime = (float)ini->ReadDouble(ID, "ChargedAnimTime", ChargedAnimTime);
        SuperWeapon = ini->ReadSuperWeapon(ID, "SuperWeapon", SuperWeapon);
        SuperWeapon2 = ini->ReadSuperWeapon(ID, "SuperWeapon2", SuperWeapon2);
        CloakGenerator = ini->ReadBool(ID, "CloakGenerator", CloakGenerator);
        SensorArray = ini->ReadBool(ID, "SensorArray", SensorArray);
        CloakRadiusInCells = (unsigned char)ini->ReadInt(ID, "CloakRadiusInCells", (signed char)CloakRadiusInCells);
        PsychicDetectionRadius = ini->ReadInt(ID, "PsychicDetectionRadius", PsychicDetectionRadius);
        BarrelStartPitch = ini->ReadInt(ID, "BarrelStartPitch", BarrelStartPitch >> 5) << 5;
        DeployFacing = ini->ReadInt(ID, "DeployFacing", DeployFacing >> 5) << 5;
        LightVisibility = ini->ReadInt(ID, "LightVisibility", LightVisibility);
        LightIntensity = (int)(ini->ReadDouble(ID, "LightIntensity", (double)(LightIntensity / 1000)) * 1000.0 + 0.1);
        LightRedTint = (int)(ini->ReadDouble(ID, "LightRedTint", (double)(LightRedTint / 1000)) * 1000.0 + 0.1);
        LightGreenTint = (int)(ini->ReadDouble(ID, "LightGreenTint", (double)(LightGreenTint / 1000)) * 1000.0 + 0.1);
        LightBlueTint = (int)(ini->ReadDouble(ID, "LightBlueTint", (double)(LightBlueTint / 1000)) * 1000.0 + 0.1);
        GateCloseDelay = ini->ReadDouble(ID, "GateCloseDelay", GateCloseDelay);
        InvisibleInGame = ini->ReadBool(ID, "InvisibleInGame", InvisibleInGame);
        {
            ini->ReadString(ID, "PowersUpBuilding", TypesEmptyText, animName, 0x18);
            if (strlen(animName))
                strcpy(PowersUpBuilding, animName);
        }
        PowersUpToLevel = ini->ReadInt(ID, "PowersUpToLevel", PowersUpToLevel);
        BridgeRepairHut = ini->ReadBool(ID, "BridgeRepairHut", BridgeRepairHut);
        HasStupidGuardMode = ini->ReadBool(ID, "HasStupidGuardMode", HasStupidGuardMode);
        CrateBeneath = ini->ReadBool(ID, "CrateBeneath", CrateBeneath);
        CrateBeneathIsMoney = ini->ReadBool(ID, "CrateBeneathIsMoney", CrateBeneathIsMoney);
        LeaveRubble = ini->ReadBool(ID, "LeaveRubble", LeaveRubble);
        PlaceAnywhere = ini->ReadBool(ID, "PlaceAnywhere", PlaceAnywhere);
        ICBMLauncher = ini->ReadBool(ID, "ICBMLauncher", ICBMLauncher);
        Artillary = ini->ReadBool(ID, "Artillary", Artillary);
        {
            coordDefault = TargetCoordOffset;
            TargetCoordOffset = ini->ReadCoord(ID, "TargetCoordOffset", coordDefault);
        }
        {
            coordDefault = ExitCoord;
            ExitCoord = ini->ReadCoord(ID, "ExitCoord", coordDefault);
        }
        AIBuildThis = ini->ReadBool(ID, "AIBuildThis", AIBuildThis);
        IsBaseDefense = ini->ReadBool(ID, "IsBaseDefense", IsBaseDefense);
        IsThreatRatingNode = ini->ReadBool(ID, "IsThreatRatingNode", IsThreatRatingNode);
        ConcentricRadialIndicator = ini->ReadBool(ID, "ConcentricRadialIndicator", ConcentricRadialIndicator);
        unknown_718 = unknown_CA1 ? 0x20 : 1;
        {
            int power = PowerBonus > 0 ? PowerBonus : -PowerDrain;
            power = ini->ReadInt(ID, "Power", power);
            PowerBonus = power;
            if (power < 0) {
                PowerDrain = -power;
                PowerBonus = 0;
            } else {
                PowerDrain = 0;
            }
        }
        {
            int power = ExtraPowerBonus > 0 ? ExtraPowerBonus : -ExtraPowerDrain;
            power = ini->ReadInt(ID, "ExtraPower", power);
            ExtraPowerBonus = power;
            if (power < 0) {
                ExtraPowerDrain = -power;
                ExtraPowerBonus = 0;
            }
        }
        Height = TypesArtIni.ReadInt(ImageFile, "Height", Height);
        OccupyHeight = TypesArtIni.ReadInt(ImageFile, "OccupyHeight", Height);
        Recoilless = TypesArtIni.ReadBool(ImageFile, "Recoilless", Recoilless);
        DoubleThick = TypesArtIni.ReadBool(ImageFile, "DoubleThick", DoubleThick);
        Flat = TypesArtIni.ReadBool(ImageFile, "Flat", Flat);
        SiloDamage = TypesArtIni.ReadBool(ImageFile, "SiloDamage", SiloDamage);
        ChargeAnim = TypesArtIni.ReadBool(ImageFile, "ChargeAnim", ChargeAnim);
        IsAnimDelayedFire = TypesArtIni.ReadBool(ImageFile, "IsAnimDelayedFire", IsAnimDelayedFire);
        DelayedFireDelay = TypesArtIni.ReadInt(ImageFile, "DelayedFireDelay", DelayedFireDelay);
        {
            void* old = ToOverlay;
            ToOverlay = TypesArtIni.ReadString(ImageFile, "ToOverlay", TypesEmptyText, name, 0x80) ? TypesFindOverlay(name) : old;
        }
        Foundation = TypesArtIni.ReadFoundation(ImageFile, "Foundation", Foundation);
        {
            int foundation = TypesArtIni.ReadFoundation(ID, "Foundation", Foundation);
            if (foundation)
                Foundation = foundation;
        }
        MidPoint = TypesArtIni.ReadInt(ImageFile, "MidPoint", MidPoint);
        DoorStages = TypesArtIni.ReadInt(ImageFile, "DoorStages", DoorStages);
        DamagedDoor = TypesArtIni.ReadBool(ImageFile, "DamagedDoor", DamagedDoor);
        TerrainPalette = TypesArtIni.ReadBool(ImageFile, "TerrainPalette", TerrainPalette);
        GateStages = TypesArtIni.ReadInt(ImageFile, "GateStages", GateStages);
        PrimaryFirePixelOffset = TypesArtIni.ReadPoint(ImageFile, "PrimaryFirePixelOffset", PrimaryFirePixelOffset);
        SecondaryFirePixelOffset = TypesArtIni.ReadPoint(ImageFile, "SecondaryFirePixelOffset", SecondaryFirePixelOffset);
        PrimaryFireDualOffset = TypesArtIni.ReadBool(ImageFile, "PrimaryFireDualOffset", PrimaryFireDualOffset);
        ExtraDamageStage = TypesArtIni.ReadBool(ImageFile, "ExtraDamageStage", ExtraDamageStage);
        SpecialZOverlayZAdjust = TypesArtIni.ReadInt(ImageFile, "SpecialZOverlayZAdjust", SpecialZOverlayZAdjust);
        NormalZAdjust = TypesArtIni.ReadInt(ImageFile, "NormalZAdjust", NormalZAdjust);
        ZShapePointMove = TypesArtIni.ReadPoint(ImageFile, "ZShapePointMove", ZShapePointMove);
        ExtraLight = (short)TypesArtIni.ReadInt(ImageFile, "ExtraLight", (short)ExtraLight);
        CanHideThings = TypesArtIni.ReadBool(ID, "CanHideThings", CanHideThings);
        for (i = 1; i <= 8; ++i) {
            wsprintfA(animName, "RemoveOccupy%d", i);
            pointDefault = TypesMakePoint(0xFFFF, 0xFFFF);
            RemoveOccupy[i - 1] = TypesArtIni.ReadPoint(ImageFile, animName, pointDefault);
            wsprintfA(animName, "AddOccupy%d", i);
            pointDefault2 = TypesMakePoint(0xFFFF, 0xFFFF);
            AddOccupy[i - 1] = TypesArtIni.ReadPoint(ImageFile, animName, pointDefault2);
        }
        {
            pointDefault = TypesMakePoint(0, 0);
            QueueingCell = TypesArtIni.ReadPoint(ImageFile, "QueueingCell", pointDefault);
        }
        FoundationData = &TypesFoundationCells[Foundation];
        FoundationOutside = &TypesFoundationOutsideCells[Foundation];
        {
            TypesArtIni.ReadString(ImageFile, "Buildup", TypesEmptyText, animName, 0x10);
            if (strlen(animName))
                strcpy(BuildupFile, animName);
        }
        StampTheater(TypesScenario->TheaterIndex);
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[1].Start, BuildingAnimFrame[1].Count, BuildingAnimFrame[1].Rate);
            if (TypesArtIni.ReadString(ImageFile, "AnimIdle", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[1].Start, &BuildingAnimFrame[1].Count, &BuildingAnimFrame[1].Rate);
        }
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[2].Start, BuildingAnimFrame[2].Count, BuildingAnimFrame[2].Rate);
            if (TypesArtIni.ReadString(ImageFile, "AnimActive", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[2].Start, &BuildingAnimFrame[2].Count, &BuildingAnimFrame[2].Rate);
        }
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[4].Start, BuildingAnimFrame[4].Count, BuildingAnimFrame[4].Rate);
            if (TypesArtIni.ReadString(ImageFile, "AnimAux1", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[4].Start, &BuildingAnimFrame[4].Count, &BuildingAnimFrame[4].Rate);
        }
        {
            sprintf(frameDefault, "%d,%d,%d", BuildingAnimFrame[5].Start, BuildingAnimFrame[5].Count, BuildingAnimFrame[5].Rate);
            if (TypesArtIni.ReadString(ImageFile, "AnimAux2", frameDefault, frameText, 0x40) > 0)
                sscanf(frameText, "%d,%d,%d", &BuildingAnimFrame[5].Start, &BuildingAnimFrame[5].Count, &BuildingAnimFrame[5].Rate);
        }
        TYPES_READ_ANIM(BuildingAnim[3], "ActiveAnim")
        TYPES_READ_ANIM(BuildingAnim[4], "ActiveAnimTwo")
        TYPES_READ_ANIM(BuildingAnim[5], "ActiveAnimThree")
        TYPES_READ_ANIM(BuildingAnim[6], "ActiveAnimFour")
        TYPES_READ_ANIM_QUIRK(BuildingAnim[14], "SuperAnim", BuildingAnim[6].X, BuildingAnim[6].Y)
        TYPES_READ_ANIM_QUIRK(BuildingAnim[15], "SuperAnimTwo", BuildingAnim[4].X, BuildingAnim[4].Y)
        TYPES_READ_ANIM_QUIRK(BuildingAnim[16], "SuperAnimThree", BuildingAnim[5].X, BuildingAnim[5].Y)
        TYPES_READ_ANIM_QUIRK(BuildingAnim[17], "SuperAnimFour", BuildingAnim[5].X, BuildingAnim[5].Y)
        TYPES_READ_ANIM(BuildingAnim[10], "SpecialAnim")
        TYPES_READ_ANIM(BuildingAnim[11], "SpecialAnimTwo")
        TYPES_READ_ANIM(BuildingAnim[12], "SpecialAnimThree")
        TYPES_READ_ANIM(BuildingAnim[13], "SpecialAnimFour")
        TYPES_READ_ANIM(BuildingAnim[19], "LowPower")
        TYPES_READ_ANIM(BuildingAnim[20], "SuperLowPower")
        TYPES_READ_ANIM_NOBOOLS(BuildingAnim[8], "ProductionAnim")
        TYPES_READ_ANIM(BuildingAnim[18], "IdleAnim")
        TYPES_READ_ANIM_NOBOOLS(BuildingAnim[7], "PreProductionAnim")
        TYPES_READ_ANIM_NOBOOLS_RULES(BuildingAnim[9], "TurretAnim")
        TurretAnimIsVoxel = ini->ReadBool(ID, "TurretAnimIsVoxel", TurretAnimIsVoxel);
        BarrelAnimIsVoxel = ini->ReadBool(ID, "BarrelAnimIsVoxel", BarrelAnimIsVoxel);
        ini->ReadString(ID, "VoxelBarrelFile", VoxelBarrelFile, VoxelBarrelFile, 0x10);
        {
            coordDefault = VoxelBarrelOffsetToPitchPivotPoint;
            VoxelBarrelOffsetToPitchPivotPoint = ini->ReadCoord(ID, "VoxelBarrelOffsetToPitchPivotPoint", coordDefault);
        }
        {
            coordDefault = VoxelBarrelOffsetToRotatePivotPoint;
            VoxelBarrelOffsetToRotatePivotPoint = ini->ReadCoord(ID, "VoxelBarrelOffsetToRotatePivotPoint", coordDefault);
        }
        {
            coordDefault = VoxelBarrelOffsetToBuildingPivotPoint;
            VoxelBarrelOffsetToBuildingPivotPoint = ini->ReadCoord(ID, "VoxelBarrelOffsetToBuildingPivotPoint", coordDefault);
        }
        {
            coordDefault = VoxelBarrelOffsetToBarrelEnd;
            VoxelBarrelOffsetToBarrelEnd = ini->ReadCoord(ID, "VoxelBarrelOffsetToBarrelEnd", coordDefault);
        }
        Upgrades = ini->ReadInt(ID, "Upgrades", Upgrades);
        if (Upgrades > 0) {
            for (i = 1; i - 1 < Upgrades; ++i) {
                BuildingTypeAnim& slot = BuildingAnim[i - 1];
                sprintf(animKey, "PowerUp%01dAnim", i);
                sprintf(damagedKey, "PowerUp%01dDamagedAnim", i);
                sprintf(xKey, "PowerUp%01dLocXX", i);
                sprintf(yKey, "PowerUp%01dLocYY", i);
                sprintf(zKey, "PowerUp%01dLocZZ", i);
                sprintf(sortKey, "PowerUp%01dYSort", i);
                TypesArtIni.ReadString(ImageFile, animKey, TypesEmptyText, animName, 0x10);
                if (strlen(animName))
                    strcpy(slot.Anim, animName);
                TypesArtIni.ReadString(ImageFile, damagedKey, TypesEmptyText, animName, 0x10);
                if (strlen(animName))
                    strcpy(slot.Damaged, animName);
                slot.X = TypesArtIni.ReadInt(ImageFile, xKey, slot.X);
                slot.Y = TypesArtIni.ReadInt(ImageFile, yKey, slot.Y);
                slot.ZAdjust = TypesArtIni.ReadInt(ImageFile, zKey, slot.ZAdjust);
                slot.YSort = TypesArtIni.ReadInt(ImageFile, sortKey, slot.YSort);
            }
        }
        {
            int oldDocks = NumberOfDocks;
            NumberOfDocks = ini->ReadInt(ID, "NumberOfDocks", oldDocks);
            if (NumberOfDocks > DockingOffsets.Capacity) {
                DockingOffsets.SetCapacity(NumberOfDocks, 0);
                for (i = oldDocks; i < NumberOfDocks; ++i) {
                    TypesDockCoord zero;
                    zero.X = 0;
                    zero.Y = 0;
                    zero.Z = 0;
                    DockingOffsets.Items[i] = zero;
                }
            }
            for (i = 0; i < NumberOfDocks; ++i) {
                sprintf(dockKey, "DockingOffset%d", i);
                coordDefault = *(HBCoord*)&DockingOffsets.Items[i];
                HBCoord result = TypesArtIni.ReadCoord(ImageFile, dockKey, coordDefault);
                *(HBCoord*)&DockingOffsets.Items[i] = result;
            }
        }
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x464A70
HBCoord BuildingTypeClass::vf_27(const HBCoord* in)
{
    HBCoord coord = *in;
    coord.Z = TypesMap.GetFloorHeight(&coord);
    return coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x464AC0
bool BuildingTypeClass::vf_42(void* arg1, void* arg2)
{
    if (PlaceAnywhere)
        return true;
    return TypesBuildingTypeTechnoView::vf_42(arg1, arg2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x464AF0
HBCoord BuildingTypeClass::vf_31()
{
    HBCoord coord;
    coord.X = TypesFoundationWidth[Foundation] << 8;
    coord.Y = TypesFoundationHeight[Foundation] << 8;
    coord.Z = Height * TypesLevelHeight;
    return coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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
    crc.FUN_004A1DB0(BuildupFile);
    crc.FUN_004A1DB0(PowersUpBuilding);
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
    crc.FUN_004A1DB0(VoxelBarrelFile);
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465380
HRESULT __stdcall BuildingTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_BuildingType;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4653C0
char* FUN_004653C0(const char* name)
{
    if (FUN_007C8D20(STR_00817474, name) != 0
        && FUN_007C8D20(STR_00817694, name) != 0) {

        for (int i = 0; i < DAT_00A83C78; i++) {
            if (FUN_007C8D20(DAT_00A83C6C[i] + 0x24, name) == 0) {
                return DAT_00A83C6C[i];
            }
        }

        void* item = FUN_007C8E17(0x1798);

        if (item != 0) {
            return ((Item*)item)->FUN_0045DD90(name);
        }
    }

    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465910
bool BuildingTypeClass::vf_40()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465920
bool BuildingTypeClass::vf_41()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465B30
void Owned_465B30::FUN_00465B30()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465B70
void Owned_465B70::FUN_00465B70()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465BB0
void Owned_465BB0::FUN_00465BB0()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465BF0
void Owned_465BF0::FUN_00465BF0()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465C30
void Owned_465C30::FUN_00465C30()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465C70
void Owned_465C70::FUN_00465C70()
{
    if (IsAllocated) {
        void* buffer = Buffer;
        if (buffer) {
            FUN_007C8B3D(buffer);
            Buffer = 0;
            IsAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465D30
// `XOR AL,AL` rather than `XOR EAX,EAX` — only the low byte is set, so the
// return type is bool, not int.
bool __cdecl FUN_00465D30()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465D70
int Obj_00465D00::FUN_00465D70() const
{
    return unknown_EDC;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465D80
// Returns its receiver.
Obj_00465D80* Obj_00465D80::FUN_00465D80()
{
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465D90
int BuildingTypeClass::WhatAmI()
{
    return 7;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465DA0
int BuildingTypeClass::Size()
{
    return 0x1798;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465DB0
int BuildingTypeClass::vf_16()
{
    return ArrayIndex;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x465DC0 -- compiler-generated scalar deleting destructor.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00465E10
// VectorClass<TPoint3D<int>>::operator==
// FUNCTION: GAMEMD 0x00465E70
// VectorClass<TPoint3D<int>>::SetCapacity
// FUNCTION: GAMEMD 0x00465F80
// VectorClass<TPoint3D<int>>::FindItemIndex
// FUNCTION: GAMEMD 0x00465FD0
// VectorClass<TPoint3D<int>>::Slot5
// FUNCTION: GAMEMD 0x00465DE0
// VectorClass<TPoint3D<int>>::Slot6

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x465F50
void FUN_00465F50(BufferHolder* obj)
{
    void* buffer = obj->Buffer;

    if (buffer != 0 && obj->IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        obj->Buffer = 0;
    }

    obj->IsAllocated = 0;
    obj->Length = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x466080
void* BufferHolderDtor::FUN_00466080(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4638;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

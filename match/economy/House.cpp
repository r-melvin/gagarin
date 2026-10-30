// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Original translation unit House.CPP. The name is the source-file string at 0x824724
//   in retail gamemd.exe v1.001, passed by the assert at 0x4f8d43 inside this object's
//   code range (0x4f4f00-0x510aff). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   YRpp.
//
//   cross-checked against YRpp (each offset/address reconfirmed against the user's binary below).
//
// Translation unit: BasePlanningCellContainer growth + qsort comparator.
//
//   LIBRARY:  GAMEMD 0x7C8E17  operator new / malloc  (CRT; array new/delete)
//   LIBRARY:  GAMEMD 0x7C8B3D  operator delete / free (CRT; array new/delete)
//
// The trivial leaves the big shape sweeps left behind: four loads of a
// container's +0x10 field, five loads of its +0x04 storage pointer, five
// constant-true returns with no arguments, three with one argument, three
// one-argument no-ops, and three stores of the ECX argument into a fixed
// global. Ordered ascending by retail address.
//
//   Name cross-checked against YRpp (convention + 0xE08 offset reconfirmed against the user's binary below).
//
// Translation unit: ObjectTypeClass::IsBuildCat5.
//
// NOTE on the sibling method ObjectTypeClass::LoadVoxel @0x5F8110: that retail
// routine is 0xBCB (3019) bytes ending at the RET @0x5F8CDA, dominated by many
// fully-inlined std::string temporaries (CCFileClass/IndexClass ctor+dtor pairs
// at 0x4739F0/0x473C50/0x43AE50/0x431B80) and voxel/HVA loader calls. It is not
// matchable in a single pass and is deferred; not included in this TU.
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The two imports are
//   named by the PE import table (GetAsyncKeyState 0x7E13E0, SendMessageA
//   0x7E14A4).
//
// Small leaves (64 bytes or less) between 0x500000 and 0x6B0000 that other
// translation units already declared as callees but nothing defined.
//
// Retail RTTI names VectorClass/DynamicVectorClass over ZoneConnectionClass, WaypointClass and
// DiscreteDistributionClass<T>::DistributionObject<T*>. WaypointClass and the distribution objects have
// element destructors, so their ctor/Clear/SetCapacity bodies (array-delete paths) are not claimed here.
//
// Retail RTTI type descriptors name VectorClass<HouseClass::BuildChoiceClass*> and
// DynamicVectorClass<HouseClass::BuildChoiceClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// Slot 5 of the retail DynamicVectorClass<AngerStruct>, <ScoutStruct> and
// <SwizzlePointerClass> vtables (owners read from retail RTTI). The bodies
// divide the byte offset by 8 (shr 3), agreeing with the eight-byte element
// asserts in the canonical pair-vector header. VC6 emits nothing for an
// explicit member instantiation, so the dynamic class is instantiated whole;
// only slot 5 is claimed here.
//
// Retail RTTI names VectorClass/DynamicVectorClass over the 8-byte pair structs, HashObject<K,V> and
// AcceleratorTracker/UndoInfoStruct. Only slots that reproduce retail bytes are claimed.
//
// Retail RTTI names VectorClass/DynamicVectorClass over unsigned short, bool, double and unsigned char.
// Scalar elements need no element type; the canonical templates are instantiated as-is.
//
// HouseClass entries of the house/building cluster (layout and evidence: house_class_core.h, house_views.h).
//
//   LIBRARY: GAMEMD 0x7C5F00  __ftol  (CRT double->long; the (int) casts; reloc)

#include "../_layout/swizzle_manager_class.h"
#include "../_layout/super_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_class_allied_inline.h"
#include "../_layout/house_type_class.h"
#include "../_layout/building_class.h"
#include "../_layout/placement_object.h"
#include "../_layout/tag_class.h"
#include "../_layout/team_type_class.h"
#include "../_layout/task_force_class.h"
#include "../_layout/base_node_class.h"
#include "../_layout/factory_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../core/scenario_class_methods.h"
#include "../_layout/rules_class.h"
#include "../_layout/player_ptr_00a83d4c.h"
#include "../_layout/obj_004a1d30.h"
// Native502D60 reads the country second index through this actual field.
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArrayIndex2) == 0xB8);


// A cell as two shorts (read through a pointer at 0x4FFD90).
struct Cell_004FFD90
{
    short X;   // +0x0000
    short Y;   // +0x0002
};

// GLOBAL: GAMEMD 0xA83C6C — BuildingTypeClass::Array items.
extern BuildingTypeClass** DAT_00A83C6C;
// GLOBAL: GAMEMD 0xA83C78 — BuildingTypeClass::Array count.
extern int DAT_00A83C78;
// GLOBAL: GAMEMD 0xA8B263 — SWAllowed.
extern char DAT_00A8B263;
// GLOBAL: GAMEMD 0xA8022C — HouseClass::Array.Items.
extern HouseClass** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA80238 — HouseClass::Array.Count.
extern int DAT_00A80238;

// Index of a type in BuildingTypeClass::Array, or -1. Inlined into the search
// below (`XOR EAX,EAX; TEST EDI,EDI; JLE; ... OR EAX,-1`).
static inline int TypeIndex_004FD060(BuildingTypeClass* type)
{
    for (int i = 0; i < DAT_00A83C78; ++i) {
        if (DAT_00A83C6C[i] == type) {
            return i;
        }
    }
    return -1;
}

#include <string.h>
#include <stdlib.h>

#pragma intrinsic(strcpy, strcmp)

#include "../ai/house_class_lost_powered_center_methods.h"


#include "../core/empty_function_family_methods.h"

#include "../core/general_structures.h"

#include "../core/leftover_trivial_leaf_sweep.h"

#include "../core/member_setter_family_methods.h"

#include "../core/object_type_class.h"

#include "../core/positive_field_predicates.h"

#include "../core/trivial_tu095_methods.h"

#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// A two-short cell value copied as one dword.
#include "../_layout/cell_0050def0.h"

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
// GLOBAL: GAMEMD 0x00A9FAB0
extern "C" int DAT_00A9FAB0;
// GLOBAL: GAMEMD 0x00AA0444
extern "C" int DAT_00AA0444;
// GLOBAL: GAMEMD 0x00AA0168 (256 key-state words)
extern "C" short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0x00B45B68
extern "C" int DAT_00B45B68;
// GLOBAL: GAMEMD 0x008B4130
extern "C" int DAT_008B4130;

// ---------------------------------------------------------------------------

#include "../_layout/team_005095d0.h"

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

#include "../_layout/obj_005095d0.h"

#include "../_layout/obj_0053ecb0.h"

#include "../_layout/triple_0053eda0.h"

#include "../_layout/obj_0053eda0.h"

#include "../_layout/obj_005402b0.h"

#include "../_layout/obj_00542fc0.h"

#include "../_layout/entry_005657a0.h"

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

#include "../_layout/obj_005657a0.h"


#include "../_layout/iface_005bf500.h"

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

#include "../_layout/vector_005c6120.h"

#include "../_layout/obj_005f9710.h"

#include "../_layout/quad_00645c30.h"

#include "../_layout/record_00656580.h"

#include "../_layout/key_00656580.h"

#include "../_layout/obj_00656580.h"


#include "../_layout/pair_0065c890.h"

#include "../_layout/obj_0068bcb0.h"

#include "../_layout/obj_0068c030.h"

#include "../_layout/owner_006915d0.h"

#include "../_layout/cursor_006915d0.h"

#include "../_layout/obj_00696f10.h"

#include "../_layout/obj_0069b540.h"


#include "../_layout/type_006a46d0.h"

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

#include "../core/vector_class_operations.h"
#include "../core/zone_connection_class.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.



template class DynamicVectorClass<ZoneConnectionClass>;

#include "../_layout/waypoint_class.h"

template class DynamicVectorClass<WaypointClass>;

class CellClass; template<class C> struct DiscreteDistributionClass { template<class P> struct DistributionObject { P Object; int Weight; DistributionObject() : Weight(0) {} ~DistributionObject() {} DistributionObject(const DistributionObject<P>& o) : Object(o.Object), Weight(o.Weight) {} bool operator==(const DistributionObject<P>& o) const { return Object==o.Object && Weight==o.Weight; } bool operator!=(const DistributionObject<P>& o) const { return !(*this==o); } }; };

template class DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass*> >;

class BuildingTypeClass; 

template class DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*> >;

class AITriggerTypeClass; 

template class DynamicVectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass*> >;

#include "../core/vector_class_operations.h"


template class DynamicVectorClass<HouseClass::BuildChoiceClass*>;

GG_STATIC_ASSERT(sizeof(HouseClass::BuildChoiceClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<HouseClass::BuildChoiceClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<HouseClass::BuildChoiceClass* >) == 0x18);

#include "../core/pair_vector_ctor_family_methods.h"

#include "../core/vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<ScoutStruct>;

#include "../core/pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<AngerStruct>;

#include "../core/pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<SwizzlePointerClass>;

template<class K,class V> struct HashObject { K Key; V Value; HashObject() {} HashObject(const HashObject<K,V>& o) : Key(o.Key), Value(o.Value) {} bool operator==(const HashObject<K,V>& o) const { return Key==o.Key; } bool operator!=(const HashObject<K,V>& o) const { return !(*this==o); } };

template class DynamicVectorClass<HashObject<unsigned int,unsigned int> >;

#include "../core/pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<HashObject<unsigned int,SubzoneConnectionStruct> >;

struct RadarTrackingStruct { int unknown_00; int unknown_04; int unknown_08; RadarTrackingStruct() {} RadarTrackingStruct(const RadarTrackingStruct& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08) {} bool operator==(const RadarTrackingStruct& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08; } bool operator!=(const RadarTrackingStruct& o) const { return !(*this==o); } }; class TechnoClass; 

template class DynamicVectorClass<HashObject<RadarTrackingStruct,TechnoClass*> >;

struct AcceleratorTracker { int A; int B; AcceleratorTracker() : A(0), B(0) {} bool operator==(const AcceleratorTracker& o) const { return A==o.A && B==o.B; } bool operator!=(const AcceleratorTracker& o) const { return !(*this==o); } };

template class DynamicVectorClass<AcceleratorTracker>;

#include "../core/undo_info_struct.h"

template class DynamicVectorClass<UndoInfoStruct>;

#include "../core/vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<unsigned short>;

template class DynamicVectorClass<bool>;

template class DynamicVectorClass<double>;

#include <string.h>
#include <new.h>
#include "../_layout/building_type_class_layout.h"
#include "house_building/house_class_core.h"

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


// Raw PBVTeamTypeClass RTTI identifies const pointer elements and the
// TypeList -> DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Original TU boundaries, final link and complete TypeList size are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"
#include "../core/type_list.h"
class TeamTypeClass;

// VTABLE: GAMEMD 0x7EA9E4 -- VectorClass<const TeamTypeClass*>.
template class VectorClass<const TeamTypeClass*>;
typedef VectorClass<const TeamTypeClass*> GgTeamTypeVectorClass;
GG_STATIC_ASSERT(offsetof(GgTeamTypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTeamTypeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTeamTypeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTeamTypeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EAAE8 -- DynamicVectorClass<const TeamTypeClass*>.
template class DynamicVectorClass<const TeamTypeClass*>;
typedef DynamicVectorClass<const TeamTypeClass*> GgTeamTypeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTeamTypeDynamicVectorClass, CapacityIncrement) == 0x14);

// VTABLE: GAMEMD 0x7EA9C4 -- TypeList<const TeamTypeClass*>.
template class TypeList<const TeamTypeClass*>;
typedef TypeList<const TeamTypeClass*> GgTeamTypeTypeList;
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTeamTypeTypeList, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const TeamTypeClass*) == 4);

// FUNCTION: GAMEMD 0x429360 (decl; reloc) - queries an interface of a global object.
void __stdcall HouseQueryObjectInterface(void* object, const IID* riid, void** result);

// LIBRARY: GAMEMD 0x7DC720 (decl; reloc; LIBRARY, comsupp) - throws the COM error
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



#include "../_layout/building_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/factory_class.h"
#include "../_layout/map_0087f7e8.h"

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- VocClass::PlayAt.
int VocClass_PlayAt(int index, CoordStruct* coords, int volume);

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EA758
extern const double DAT_007EA758;
// GLOBAL: GAMEMD 0xA8EFA0
extern double DAT_00A8EFA0;
// GLOBAL: GAMEMD 0xA8F018
extern double DAT_00A8F018;
// GLOBAL: GAMEMD 0xA8F020
extern int DAT_00A8F020;
// GLOBAL: GAMEMD 0xA8F024
extern int DAT_00A8F024;
// GLOBAL: GAMEMD 0xA8F028
extern int DAT_00A8F028;
// GLOBAL: GAMEMD 0xA8F030
extern double DAT_00A8F030;

// CAPPED at 98.3% (multiset identical; 17 instructions differ in order or register only: the -1 constant
// load near +0x214, the five byte stores near +0x3BB, a push near +0x69F, one add operand order near
// +0xBC6, two fill-setup orders). Variants tried: memset vs element loops for the fills, vector ctor with
// init list vs body assignments (body kept), AddItem shapes.
// Existing coordinate choice, now expressed on the actual House owner.
inline CellStruct HouseClass::HouseBaseCell() const
{
    if (BaseCenter.X == HouseEmptyCell.X && BaseCenter.Y == HouseEmptyCell.Y)
        return BaseSpawnCell;
    return BaseCenter;
}

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
HRESULT __stdcall HouseClass::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == 0)
        return E_POINTER;

    *ppv = 0;
    if (memcmp(&riid, &IID_IUnknown, sizeof(IID)) == 0)
        *ppv = this;
    if (memcmp(&riid, &IID_IHouse, sizeof(IID)) == 0)
        *ppv = static_cast<IHouse*>(this);
    if (memcmp(&riid, &IID_IPublicHouse, sizeof(IID)) == 0)
        *ppv = static_cast<IPublicHouse*>(this);
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
bool __stdcall HouseClass::IPublicHouse_vf_08()
{
    return PowerOutput >= PowerDrain;
}

// FUNCTION: GAMEMD 0x4F6930
IUnknown* __stdcall HouseClass::vf_05()
{
    IUnknown* result;
    HouseQueryObjectInterface(&HouseMainObject, &DAT_007E36C0, (void**)&result);
    return result;
}

// FUNCTION: GAMEMD 0x4F6950
BSTR __stdcall HouseClass::vf_04()
{
    WCHAR buffer[32];
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, Type->Name, -1, buffer, 32);
    return SysAllocString(buffer);
}

// FUNCTION: GAMEMD 0x4F6990
HRESULT __stdcall HouseClass::vf_06()
{
    float multiplier = Type->IncomeMult;
    return (int)(OwnedTiberium.GetTotalValue() * multiplier + Balance);
}

// FUNCTION: GAMEMD 0x4F69D0
HRESULT __stdcall HouseClass::vf_07()
{
    return TotalStorage - (int)OwnedTiberium.GetTotalAmount();
}

// FUNCTION: GAMEMD 0x4F6A00
HRESULT __stdcall HouseClass::IHouse_vf_08()
{
    return PowerOutput;
}

// FUNCTION: GAMEMD 0x4F6A10
HRESULT __stdcall HouseClass::vf_09()
{
    return PowerDrain;
}

// FUNCTION: GAMEMD 0x4F6A20
HRESULT __stdcall HouseClass::vf_10(int category)
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
HRESULT __stdcall HouseClass::IPublicHouse_vf_05(int category)
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
HRESULT __stdcall HouseClass::vf_11(int category)
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
HRESULT __stdcall HouseClass::IPublicHouse_vf_06(int category)
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
void* __stdcall HouseClass::vf_12(void* cell)
{
    CellStruct center;
    center.X = HouseCellCoord(HouseBaseCell()).X / 256;
    center.Y = HouseCellCoord(HouseBaseCell()).Y / 256;
    *(CellStruct*)cell = center;
    return cell;
}

// FUNCTION: GAMEMD 0x4F6D10
void* __stdcall HouseClass::IPublicHouse_vf_07(void* cell)
{
    CellStruct center;
    center.X = HouseCellCoord(HouseBaseCell()).X / 256;
    center.Y = HouseCellCoord(HouseBaseCell()).Y / 256;
    *(CellStruct*)cell = center;
    return cell;
}

// FUNCTION: GAMEMD 0x4F6E60
HRESULT __stdcall HouseClass::vf_03()
{
    return ArrayIndex;
}

// FUNCTION: GAMEMD 0x004F6EB0
void FUN_004F6EB0()
{
}

// Unclaimed (below partial bar), GAMEMD 0x4F6EC0
// Switches to the given difficulty row of the rules: loads the nine multipliers (scaled by the house
// type's biases in a multiplayer game), restarts the team delay timer and returns the previous difficulty.
int HouseClass::FUN_004F6EC0(int difficulty)
{
    int previous = AIDifficulty;
    AIDifficulty = difficulty;
    if (Session_00A8B238.GameMode != 0) {
        FirepowerMultiplier = RulesInstance->Difficulty[difficulty].FirepowerMult * Type->FirepowerMult;
        GroundspeedMultiplier = Type->GroundspeedMult * (RulesInstance->Difficulty[difficulty].GroundspeedMult * RulesInstance->GameSpeedBias);
        AirspeedMultiplier = Type->AirspeedMult * (RulesInstance->Difficulty[difficulty].AirspeedMult * RulesInstance->GameSpeedBias);
        ArmorMultiplier = RulesInstance->Difficulty[difficulty].ArmorMult * Type->ArmorMult;
        ROFMultiplier = RulesInstance->Difficulty[difficulty].ROFMult * Type->ROFMult;
        CostMultiplier = RulesInstance->Difficulty[difficulty].CostMult * Type->CostMult;
        RepairDelay = RulesInstance->Difficulty[difficulty].RepairDelay;
        BuildDelay = RulesInstance->Difficulty[difficulty].BuildDelay;
        BuildTimeMultiplier = Type->BuildtimeMult * (RulesInstance->Difficulty[difficulty].BuildtimeMult * RulesInstance->GameSpeedBias);
    } else {
        FirepowerMultiplier = RulesInstance->Difficulty[difficulty].FirepowerMult;
        GroundspeedMultiplier = RulesInstance->Difficulty[difficulty].GroundspeedMult
            * RulesInstance->GameSpeedBias;
        AirspeedMultiplier = RulesInstance->Difficulty[difficulty].AirspeedMult
            * RulesInstance->GameSpeedBias;
        ArmorMultiplier = RulesInstance->Difficulty[difficulty].ArmorMult;
        ROFMultiplier = RulesInstance->Difficulty[difficulty].ROFMult;
        CostMultiplier = RulesInstance->Difficulty[difficulty].CostMult;
        RepairDelay = RulesInstance->Difficulty[difficulty].RepairDelay;
        BuildDelay = RulesInstance->Difficulty[difficulty].BuildDelay;
        BuildTimeMultiplier = RulesInstance->Difficulty[difficulty].BuildtimeMult
            * RulesInstance->GameSpeedBias;
    }
    TeamDelayTimer = CDTimerClass(RulesInstance->TeamDelays.Items[difficulty] + ArrayIndex * 175);
    return previous;
}

// FUNCTION: GAMEMD 0x4F7850
// Stores several members.
Obj_004F7850* Obj_004F7850::FUN_004F7850()
{
    unknown_00 = 0;
    unknown_04 = 1;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = -1;
    return this;
}

// STRING: GAMEMD 0x824784 "EVA_OreMinerUnderAttack"
extern const char STR_00824784[];
// STRING: GAMEMD 0x824768 "EVA_OurBaseIsUnderAttack"
extern const char STR_00824768[];
// STRING: GAMEMD 0x82474C "EVA_OurAllyIsUnderAttack"
extern const char STR_0082474C[];
// FUNCTION: GAMEMD 0x65FA70 (decl; reloc) -- RadarEventClass::Create; the cell goes on the stack.
bool __fastcall FUN_0065FA70(int type, CellStruct cell);
// FUNCTION: GAMEMD 0x750920 (decl; reloc) -- VocClass::PlayGlobal.
void* __fastcall FUN_00750920(int index, float volume, unsigned int pan, int* controller);

// The cell holding a coordinate, taken through the reference so the caller's temporary is read in place.
static inline CellStruct CellOfCoord(const CoordStruct& coord)
{
    CellStruct cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

// FUNCTION: GAMEMD 0x4F93E0
// A building of this house is under attack: raises the radar event and the matching EVA line for the
// local player (own base, own miner or an ally), then notifies the related tags.
void HouseClass::FUN_004F93E0(BuildingClass* building)
{
    if (building != 0 && building->vf_32()) {
        return;
    }
    bool controlled = IsControlledByCurrentPlayer_0050E0E0(this);
    bool ally;
    if (DAT_00A83D4C == 0 || DAT_00A83D4C == this || !IsAlliedWith(DAT_00A83D4C)
        || (Session_00A8B238.GameMode != 0 && building->Owner->Type->MultiplayPassive)) {
        ally = false;
    } else {
        ally = true;
    }
    if (controlled) {
        if (building != 0 && building->Type != 0 && building->Type->UndeploysInto != 0
            && building->Type->ResourceGatherer) {
            CellStruct cell = CellOfCoord(building->vf_18());
            if (FUN_0065FA70(4, cell)) {
                Vox_0050E0E0::Play(STR_00824784, -1, -1);
            }
        } else {
            CellStruct cell = CellOfCoord(building->vf_18());
            if (FUN_0065FA70(3, cell)) {
                Vox_0050E0E0::Play(STR_00824768, -1, -1);
                FUN_00750920(RulesInstance->BaseUnderAttackSound, 1.0f, 0x2000, 0);
            }
        }
    } else if (ally) {
        CellStruct cell = CellOfCoord(building->vf_18());
        if (FUN_0065FA70(0x10, cell)) {
            Vox_0050E0E0::Play(STR_0082474C, -1, -1);
            FUN_00750920(RulesInstance->BaseUnderAttackSound, 1.0f, 0x2000, 0);
        }
    }
    // TAGLOOP-BEGIN
    for (int i = 0; i < RelatedTags.Count; i++) {
        RelatedTags.Items[i]->FUN_006E53A0(6, 0, DAT_00A8EF98, false, 0);
    }
    // TAGLOOP-END
}

// FUNCTION: GAMEMD 0x4F9970
//
// Redraw every silo when the house's fill level changes. Both the previous
// and the current storage are reduced to a quarter-step (0..4, rounded) and
// nothing happens unless the step moved; then every live, on-map building of a
// silo-capable type is re-marked so its fill art updates.
void HouseClass::UpdateAllSilos(int prevStorage, int prevTotalStorage)
{
    int before = 0;
    if (prevTotalStorage != 0) {
        before = (int)((double)prevStorage / prevTotalStorage * 4.0 + 0.5);
    }

    int after = 0;
    if (this->TotalStorage != 0) {
        after = (int)(this->OwnedTiberium.GetTotalAmount() / this->TotalStorage * 4.0 + 0.5);
    }

    if (before != after) {
        int count = this->Buildings.Count;
        for (int i = 0; i < count; i++) {
            BuildingClass* b = this->Buildings.Items[i];
            if (b != 0 && !b->InLimbo && b->Type->bools_16A4[4]) {
                b->vf_73(2);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x4F9F70
// Applies FUN_004F9F90 to the house stored at `index` of the global house array.
void HouseClass::FUN_004F9F70(int index, bool flag)
{
    this->FUN_004F9F90((HouseClass*)HouseArray.Items[index], flag);
}

// FUNCTION: GAMEMD 0x6ABC60 (decl; reloc)
int __fastcall FUN_006ABC60(int a, int b, int c);

// FUNCTION: GAMEMD 0x4FA910
// Puts the factory that serves the given type category on hold; returns 3 when there is none.
int HouseClass::FUN_004FA910(int rtti, int index, bool naval)
{
    int buildCat;
    if (index < 0) {
        buildCat = 0;
    } else {
        buildCat = ObjectTypeClass::IsBuildCat5(rtti, index);
    }

    FactoryClass* factory;
    switch (rtti) {
    case 0xF:
    case 0x10:
        factory = Primary_ForInfantry;
        break;
    case 1:
    case 0x28:
        if (naval) {
            factory = Primary_ForShips;
        } else {
            factory = Primary_ForVehicles;
        }
        break;
    case 6:
    case 7:
        if (buildCat == 5) {
            factory = Primary_ForDefenses;
        } else {
            factory = Primary_ForBuildings;
        }
        break;
    case 2:
    case 3:
        factory = Primary_ForAircraft;
        break;
    default:
        factory = 0;
        break;
    }

    if (factory == 0) {
        return 3;
    }
    factory->Suspend(true);
    if (DAT_00A83D4C == this) {
        DAT_0087F7E8.FUN_006A60A0(FUN_006ABC60(rtti, index, 0));
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4FB6B0  HouseClass::RegisterJustBuilt (__thiscall, ret 4)
//
// A factory has just finished something. The house records which type it was
// per category, bumps that category's per-type tally unless the type opts out,
// and picks the "unit ready" announcement: the rules-wide one for the category,
// overridden by the type's own creation sound when it has one. Nothing is said
// for buildings unless their type supplies a sound.
void HouseClass::RegisterJustBuilt(TechnoClass* pTechno)
{
    int voice = -1;

    this->IsBuiltSomething = 1;

    TechnoTypeClass* pType = pTechno->vf_33();

    // Canonical names LastBuiltAircraftType/VehicleType sit at +0x274/+0x278;
    // retail stores the unit type at +0x274 and the aircraft type at +0x278.
    switch (pTechno->vf_11()) {
    case 1:
        this->LastBuiltAircraftType = pType->vf_16();
        if (pType->bools_C8C[19] == 0) {
            this->FactoryProducedUnitTypes.FUN_0049FA00(pType->vf_16());
        }
        voice = RulesInstance->CreateUnitSound;
        break;

    case 15:
        this->LastBuiltInfantryType = pType->vf_16();
        if (pType->bools_C8C[19] == 0) {
            this->FactoryProducedInfantryTypes.FUN_0049FA00(pType->vf_16());
        }
        voice = RulesInstance->CreateInfantrySound;
        break;

    case 6:
        this->LastBuiltBuildingType = pType->vf_16();
        if (pType->bools_C8C[19] == 0) {
            this->FactoryProducedBuildingTypes.FUN_0049FA00(pType->vf_16());
        }
        break;

    case 2:
        this->LastBuiltVehicleType = pType->vf_16();
        if (pType->bools_C8C[19] == 0) {
            this->FactoryProducedAircraftTypes.FUN_0049FA00(pType->vf_16());
        }
        voice = RulesInstance->CreateAircraftSound;
        break;
    }

    if (pType->CreateSound != -1) {
        voice = pType->CreateSound;
    }

    if (voice != -1) {
        CoordStruct coords = pTechno->Location;
        VocClass_PlayAt(voice, &coords, 0);
    }

    this->RecheckTechTree = 1;
}

// GLOBAL: GAMEMD 0x880994 / 0x88099A / 0x88099B / 0x88099C / 0x8809A0 -- placement state reset when placement starts.
extern int DAT_00880994;
extern bool DAT_0088099A;
extern bool DAT_0088099B;
extern bool DAT_0088099C;
extern int DAT_008809A0;
// FUNCTION: GAMEMD 0x48DC90 (decl; reloc) -- deselects everything.
void __cdecl FUN_0048DC90();

// FUNCTION: GAMEMD 0x4FB840
// Starts placing `object` for the local player: clears the selection and the repair and sell modes,
// records the placement state and marks the foundation under `target`.
bool HouseClass::FUN_004FB840(ObjectClass* target, BuildingClass* object)
{
    if (this == DAT_00A83D4C && PlacementType_00880990 == 0 && target != 0 && object != 0) {
        FUN_0048DC90();
        DAT_0087F7E8.FUN_004AC8C0(0);
        DAT_0087F7E8.FUN_004AC660(0);
        DAT_0088099A = false;
        DAT_0088099B = false;
        DAT_0088099C = false;
        DAT_008809A0 = -1;
        PlacementType_00880990 = object->Type;
        PlacementObject_0088098C = object;
        DAT_00880994 = ArrayIndex;
        DAT_0087F7E8.FUN_004A8BF0(object->vf_66(1));
        CellStruct cell;
        DAT_0087F7E8.FUN_004A91B0(&cell, target->vf_110());
        target->vf_73(2);
        return true;
    }
    return false;
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
        if (static_cast<void*>(PlanningPaths[i]) == pointer)
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

// FUNCTION: GAMEMD 0x4FCE00
// Sets the starting credits and balance to `credits`, and the colour scheme index (also on the
// house type) to `colorIndex`; the middle argument is ignored.
void HouseClass::FUN_004FCE00(int colorIndex, int unused, int credits)
{
    this->StartingCredits = credits;
    this->Balance = credits;
    this->Type->ColorSchemeIndex = colorIndex;
    this->ColorSchemeIndex = colorIndex;
}

// FUNCTION: GAMEMD 0x4FD040
BuildingTypeClass* HouseClass::GetProducingBuildingType()
{
    if (this->ProducingBuildingTypeIndex != -1) {
        return DAT_00A83C6C[this->ProducingBuildingTypeIndex];
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4FD060
//
// The first live building this house owns whose type has the given array
// index, optionally restricted to one map sector. The per-type counter is
// consulted first so houses without such a building skip the walk.
BuildingClass* HouseClass::FindBuildingOfType(int index, int sector)
{
    if (this->OwnedBuildingTypes.GetCount(index) > 0) {
        int count = this->Buildings.Count;
        for (int i = 0; i < count; ++i) {
            BuildingClass* building = this->Buildings.Items[i];
            if (building != 0 && building->InLimbo == 0) {
                if (TypeIndex_004FD060(building->Type) == index) {
                    if (sector == -1) {
                        return building;
                    }
                    if (this->SectorOf(building->vf_18()) == sector) {
                        return building;
                    }
                }
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4FF540
void __stdcall FUN_004FF540(int)
{
}

// FUNCTION: GAMEMD 0x4FF550  HouseClass::RemoveTracking (__thiscall, ret 4)
//
// The mirror of RegisterJustBuilt: an object has left the house's books. It
// clears the object's "tracked" flag, then — unless the type opts out of
// tracking entirely — walks down the per-category owned counts and the
// per-type tally for the category the object belongs to. Buildings are split
// between two counts depending on whether they are power/production relevant;
// infantry only decrement while their "still counted" flag is set; units also
// give back a second count when their type asks for it.
void HouseClass::RemoveTracking(TechnoClass* pTechno)
{
    pTechno->CountedAsOwned = false;

    if (pTechno->vf_33()->Insignificant != 0) {
        return;
    }

    if (pTechno->vf_33()->bools_C8C[19] != 0) {
        return;
    }

    switch (pTechno->vf_11()) {
    case 6:
        if (!pTechno->vf_32()
            && (static_cast<BuildingClass*>(pTechno)->Type->UndeploysInto == 0
                || static_cast<BuildingClass*>(pTechno)->Type->UndeploysInto->ResourceGatherer == 0)) {
            this->OwnedBuildings--;
        } else {
            this->OwnedUnits--;
        }
        {
            TechnoTypeClass* pType = pTechno->vf_33();
            this->OwnedBuildingTypes.FUN_0049FA70(pType->vf_16());
        }
        break;

    case 2:
        this->OwnedAircraft--;
        {
            TechnoTypeClass* pType = pTechno->vf_33();
            this->OwnedAircraftTypes.FUN_0049FA70(pType->vf_16());
        }
        break;

    case 15:
        if (pTechno->CountedAsOwnedSpecial != 0) {
            this->OwnedInfantry--;
            pTechno->CountedAsOwnedSpecial = false;
        }
        {
            TechnoTypeClass* pType = pTechno->vf_33();
            this->OwnedInfantryTypes.FUN_0049FA70(pType->vf_16());
        }
        break;

    case 1:
        this->OwnedUnits--;
        {
            TechnoTypeClass* pType = pTechno->vf_33();
            this->OwnedUnitTypes.FUN_0049FA70(pType->vf_16());
        }
        if (pTechno->vf_33()->Naval != 0) {
            if (pTechno->vf_33()->Passengers == 0) {
                this->OwnedNavy--;
            }
        }
        break;
    }
}

// FUNCTION: GAMEMD 0x5004E0  (static __fastcall)
//
//   PUSH ESI / MOV ESI,ECX            ESI = abstractID
//   TEST EDX,EDX / JGE                idx < 0  -> return 0
//   MOV ECX,ESI / CALL 0x48DCD0       p = ObjTypeFindFromCat(abstractID, idx)
//   CMP ESI,6 JZ / CMP ESI,7 JZ       abstractID must be 6 or 7
//   (else)  XOR EAX,EAX / RET         return 0
//   MOV EAX,[EAX+0xE08] / RET         return *(int*)(p + 0xE08)
//
// abstractID is held in ESI (callee-saved) across the call so the two CMPs run
// after it; idx stays live in EDX up to the call.
int ObjectTypeClass::IsBuildCat5(int abstractID, int idx)
{
    char* p;
    if (idx < 0)
        return 0;
    p = ObjTypeFindFromCat(abstractID, idx);
    if (abstractID != 6 && abstractID != 7)
        return 0;
    return *(int*)(p + 0xE08);
}

// HouseClass INI reader (0x500B40): reads one house's section, named after its plain name. Every key
// string, destination offset, reader call and default was read off the user's retail gamemd.exe v1.001
// disassembly; field names are the INI key strings themselves.
#include "../_layout/color_struct.h"
#include "../_layout/scenario_ptr_00a8b230.h"
#include "../core/scenario_class_methods.h"
#include "../_layout/session_class.h"
#include "../ui/game_options_class_methods.h"
#include "../platform/ccini_class_methods.h"

// GLOBAL: GAMEMD 0xA8EB60 -- the game options.
extern GameOptionsClass DAT_00A8EB60;
// GLOBAL: GAMEMD 0x8871E0 -- the active rules.
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;
// GLOBAL: GAMEMD 0xA8ED84 is the frame counter (core/frame_counter.h).

// The readers this function uses that CCINIClass itself does not declare (same reader object in retail).
class HouseIniView : public CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x475980 (decl; reloc) -- edge by name.
    int ReadEdge(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x475260 (decl; reloc) -- a list of house names as a bit mask.
    unsigned int ReadHousesList(const char* section, const char* key, unsigned int fallback);
};

// A colour scheme record, as far as this body reads it: the converter and the palette index.
struct ConvertView_00500B40
{
    int unknown_00;
    int Format;                // +0x04 1 = bytes, otherwise words
    char unknown_08[0x16C];
    unsigned char* Pixels;     // +0x174 bytes when Format is 1, words otherwise
    int Pixel(int index) const
    {
        int format = Format;
        unsigned char* pixels = Pixels;
        if (format == 1)
            return pixels[index];
        return ((unsigned short*)pixels)[index];
    }
};
GG_STATIC_ASSERT(offsetof(ConvertView_00500B40, Format) == 0x04);
GG_STATIC_ASSERT(offsetof(ConvertView_00500B40, Pixels) == 0x174);
struct SchemeView_00500B40
{
    char unknown_000[0x30C];
    ConvertView_00500B40* Convert;   // +0x30C
    char unknown_310[0x20];
    int PixelIndex;                  // +0x330
};
GG_STATIC_ASSERT(offsetof(SchemeView_00500B40, Convert) == 0x30C);
GG_STATIC_ASSERT(offsetof(SchemeView_00500B40, PixelIndex) == 0x330);
// GLOBAL: GAMEMD 0xB054D4 -- colour scheme records.
extern SchemeView_00500B40** DAT_00B054D4;
// GLOBAL: GAMEMD 0x8A0DD0..0x8A0DE4 -- the display's colour shift operands.
extern short DAT_008A0DD0;
extern int DAT_008A0DD4;
extern short DAT_008A0DD8;
extern int DAT_008A0DDC;
extern short DAT_008A0DE0;
extern int DAT_008A0DE4;
// GLOBAL: GAMEMD 0x7E2800 -- 0.0 (double).
extern const double DAT_007E2800;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- square root; __cdecl, one double.
double __cdecl Sqrt_004CAC40(double value);
// FUNCTION: GAMEMD 0x50B920 (decl; reloc) -- adjusts the three colour channels in place.
void __fastcall FUN_0050B920(double* first, double* second, double* third);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log (format, args...).
void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- __fastcall string-table lookup.
unsigned short* __fastcall FUN_00734E60(const char* label, int* out, const char* file, int line);
// LIBRARY: GAMEMD 0x7CA422 (decl; reloc) -- CRT wcsncpy.
unsigned short* __cdecl FUN_007CA422(unsigned short* destination, const unsigned short* source, int count);
// LIBRARY: GAMEMD 0x7CA489 (decl; reloc) -- CRT wcscpy.
unsigned short* __cdecl FUN_007CA489(unsigned short* destination, const unsigned short* source);

// The inlined bounded-name assignment: the source is copied through a local, then onto the destination.
static inline void AssignName32(char* destination, const char* source)
{
    char copy[0x20];
    if (source == 0) {
        copy[0] = 0;
    } else {
        strncpy(copy, source, 0x1f);
        copy[0x1f] = 0;
    }
    if (copy != destination)
        memcpy(destination, copy, 0x20);
}
// FUNCTION: GAMEMD 0x500B40
// PARTIAL: 85.9% (instruction multiset identical, 427 of 427). The remaining delta is stack layout: retail
// orders the three colour channel doubles B, R, G from the lowest slot (shared with the shift temporaries)
// where this body gives R, G, B, which moves every access to them and the locals above; the registers of
// the inlined pixel read also differ. Declaration order, assignment order and the zero-length branch order
// do not change the slot order. The UI name buffer is 0x60 bytes: the retail frame is 0x40 bytes larger
// than a 0x20 buffer gives.
// Reads the house's section: tech level, credits, player control, the UI name, team ratios, IQ, edge,
// colour (with its laser colour), allies and the team delay timer.
void HouseClass::FUN_00500B40(CCINIClass* ini)
{
    char section[21];
    strcpy(section, PlainName);
    ini->Reset();
    // STRING: GAMEMD 0x824E40
    TechLevel = ini->ReadInteger(section, "TechLevel", DAT_00A8B230->unknown_1254);
    // STRING: GAMEMD 0x824E38
    StartingCredits = ini->ReadInteger(section, "Credits", 0) * 100;
    // STRING: GAMEMD 0x824E28
    IsInPlayerControl = ini->ReadBool(section, "PlayerControl", false);
    if (IsInPlayerControl && Session_00A8B238.GameMode == 0) {
        if (DAT_00A8EB60.Difficulty == 0)
            Balance = DAT_008871E0->CampaignMoneyDeltaEasy + StartingCredits;
        else if (DAT_00A8EB60.Difficulty == 2)
            Balance = DAT_008871E0->CampaignMoneyDeltaHard + StartingCredits;
        else
            Balance = StartingCredits;
        Balance = Balance > 0 ? Balance : 0;
    } else {
        Balance = StartingCredits;
    }
    char uiName[0x60];
    // STRING: GAMEMD 0x81784C
    // STRING: GAMEMD 0x81784C
    ini->ReadString(section, "UIName", UINameString, uiName, 0x20);
    AssignName32(UINameString, uiName);
    if (UINameString[0]) {
        // STRING: GAMEMD 0x824724
        FUN_007CA422(UIName, FUN_00734E60(UINameString, 0, "D:\\ra2mdpost\\House.CPP", 0x213B), 0x20);
        UIName[20] = 0;
    } else {
        FUN_007CA489(UIName, Type->UIName);
    }
    // STRING: GAMEMD 0x824E14
    RatioAITriggerTeam = ini->ReadInteger(section, "RatioAITriggerTeam", RatioAITriggerTeam);
    // STRING: GAMEMD 0x824E00
    RatioTeamAircraft = ini->ReadInteger(section, "RatioTeamAircraft", 0x4B);
    // STRING: GAMEMD 0x824DEC
    RatioTeamInfantry = ini->ReadInteger(section, "RatioTeamInfantry", 0x4B);
    // STRING: GAMEMD 0x824DDC
    RatioTeamBuildings = ini->ReadInteger(section, "RatioTeamUnits", 0x4B);
    SideIndex = Type->SideIndex;
    if (SideIndex == -1)
        SideIndex = 0;
    int iq = ini->ReadInteger(section, "IQ", 0);
    if (iq > DAT_008871E0->unknown_1434)
        iq = 1;
    IQLevel = iq;
    IQLevel2 = iq;
    // STRING: GAMEMD 0x824DD0
    StartingEdge = static_cast<HouseIniView*>(ini)->ReadEdge(section, "Edge", -1);
    // STRING: GAMEMD 0x81B138
    ColorSchemeIndex = ini->ReadColorScheme(section, "Color", ColorSchemeIndex);
    if (ColorSchemeIndex < 0)
        ColorSchemeIndex = 5;
    SchemeView_00500B40* scheme = DAT_00B054D4[ColorSchemeIndex];
    if (scheme == 0) {
        FUN_004068E0("********* Forcing House %s [%s] to color WHITE (from %d) because he biffed the initialization process!!!!", PlainName, Type->Name.Data, ColorSchemeIndex);
        ColorSchemeIndex = 5;
        scheme = DAT_00B054D4[5];
    }
    unsigned short pixel = scheme->Convert->Pixel(scheme->PixelIndex);
    ColorStruct shifted;
    shifted.R = (pixel >> DAT_008A0DD0) << DAT_008A0DD4;
    shifted.G = (pixel >> DAT_008A0DE0) << DAT_008A0DE4;
    shifted.B = (pixel >> DAT_008A0DD8) << DAT_008A0DDC;
    Color = shifted;
    double blue;
    double red;
    double green;
    red = Color.R;
    green = Color.G;
    blue = Color.B;
    double length = Sqrt_004CAC40(red * red + green * green + blue * blue);
    if (length == DAT_007E2800) {
        blue = 255.0;
        green = 255.0;
        red = 255.0;
    } else {
        red = red * 240.0 / length;
        if (red > 255.0)
            red = 255.0;
        green = green * 240.0 / length;
        if (green > 255.0)
            green = 255.0;
        blue = blue * 240.0 / length;
        if (blue > 255.0)
            blue = 255.0;
        if (red < 96.0)
            red = 0.0;
        if (green < 96.0)
            green = 0.0;
        if (blue < 96.0)
            blue = 0.0;
    }
    FUN_0050B920(&red, &green, &blue);
    LaserColor.FUN_0050E430((unsigned char)(int)red, (unsigned char)(int)green, (unsigned char)(int)blue);
    AIGeneral = 0;
    FUN_004F9B70(DAT_00A8022C[ArrayIndex], false);
    // STRING: GAMEMD 0x824D5C
    unsigned int allies = static_cast<HouseIniView*>(ini)->ReadHousesList(section, "Allies", 0);
    for (int i = 0; i < DAT_00A80238; i++) {
        HouseClass* other = DAT_00A8022C[i];
        if (allies & (1 << other->ArrayIndex))
            FUN_004F9B70(other, false);
    }
    TeamDelayTimer = CDTimerClass(DAT_008871E0->TeamDelays.Items[AIDifficulty] + ArrayIndex * 175);
    Base.FUN_0042EBE0(ini, section);
    Base.unknown_74 = this;
}

// FUNCTION: GAMEMD 0x5013A0
HRESULT __stdcall HouseClass::vf_13()
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
HRESULT __stdcall HouseClass::IHouse_vf_14()
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

// Receiver of the empty-cell writer at 0x501AA0 (no layout claimed).
struct Obj_00501AA0
{
    // FUNCTION: GAMEMD 0x501AA0
    Cell_004FFD90* FUN_00501AA0(Cell_004FFD90* out, int a2, int a3);
};

// FUNCTION: GAMEMD 0x501AA0
// Writes the zero cell to `out` and returns it; the other two arguments are ignored.
Cell_004FFD90* Obj_00501AA0::FUN_00501AA0(Cell_004FFD90* out, int a2, int a3)
{
    Cell_004FFD90 cell;
    cell.X = 0;
    cell.Y = 0;
    *out = cell;
    return out;
}

// FUNCTION: GAMEMD 0x502100
// Applies FUN_004F9B70 to the object's house; does nothing for a null object.
void HouseClass::FUN_00502100(AbstractClass* object, bool flag)
{
    if (object) {
        this->FUN_004F9B70(object->vf_15(), flag);
    }
}

// FUNCTION: GAMEMD 0x502130
// Applies FUN_004F9F90 to the object's house; does nothing for a null object.
void HouseClass::FUN_00502130(AbstractClass* object, bool flag)
{
    if (object) {
        this->FUN_004F9F90(object->vf_15(), flag);
    }
}

// FUNCTION: GAMEMD 0x5024F0
HRESULT __stdcall HouseClass::EnumConnectionPoints(IEnumConnectionPoints** ppEnum)
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
HRESULT __stdcall HouseClass::FindConnectionPoint(REFIID riid, IConnectionPoint** ppCP)
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

// Native boolean-member and checksum-sink contracts preserve this exact CRC body.
// FUNCTION: GAMEMD 0x502D60
void HouseClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D50(AIDifficulty);
    crc->FUN_004A1D50(Type->ArrayIndex2);
    crc->FUN_004A1D90(FirepowerMultiplier);
    crc->FUN_004A1D90(GroundspeedMultiplier);
    crc->FUN_004A1D90(AirspeedMultiplier);
    crc->FUN_004A1D90(ArmorMultiplier);
    crc->FUN_004A1D90(ROFMultiplier);
    crc->FUN_004A1D90(CostMultiplier);
    crc->FUN_004A1D90(BuildTimeMultiplier);
    crc->FUN_004A1D90(RepairDelay);
    crc->FUN_004A1D90(BuildDelay);
    crc->FUN_004A1CA0(IsHumanPlayer);
    crc->FUN_004A1CA0(Production);
    crc->FUN_004A1CA0(AutocreateAllowed);
    crc->FUN_004A1CA0(AITriggersActive);
    crc->FUN_004A1CA0(Defeated);
    crc->FUN_004A1D50(IQLevel2);
    crc->FUN_004A1D50(AIMode);
    crc->FUN_004A1D50(AllowWinBlocks);
    crc->FUN_004A1D50(RepairTimer.GetTimeLeft());
    crc->FUN_004A1D50(AlertTimer.GetTimeLeft());
    crc->FUN_004A1D50(BorrowedTime.GetTimeLeft());
    crc->FUN_004A1D50(OwnedUnits);
    crc->FUN_004A1D50(OwnedBuildings);
    crc->FUN_004A1D50(OwnedInfantry);
    crc->FUN_004A1D50(OwnedAircraft);
    crc->FUN_004A1D50(Balance);
    crc->FUN_004A1D50(TotalStorage);
    crc->FUN_004A1D50(NumAirpads);
    crc->FUN_004A1D50(NumBarracks);
    crc->FUN_004A1D50(NumWarFactories);
    crc->FUN_004A1D50(NumShipyards);
    crc->FUN_004A1D50(NumConYards);
    crc->FUN_004A1D50(NumOrePurifiers);
    crc->FUN_004A1D50(PowerOutput);
    crc->FUN_004A1D50(PowerDrain);
    crc->FUN_004A1CA0(MapIsClear);
    crc->FUN_004A1D50(WhoLastHurtMe);
    crc->FUN_004A1D50(EnemyHouseIndex);
    Base.ComputeCrc(crc);
}

// Partial 98.3%: twelve canonical AddItem growth arguments use EAX where retail
// uses ECX (24 ADD/PUSH instruction differences, identical mnemonic multiset).
// Keep the shared operation; no per-container arithmetic-order variants.
// FUNCTION: GAMEMD 0x503040
HRESULT __stdcall HouseClass::Load(IStream* pStm)
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

    hr = AbstractClass::Load(pStm);
    if (hr < 0)
        return hr;
    new (this) HouseClass(AbstractNoInit());
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
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Primary_ForInfantry);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Primary_ForVehicles);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Primary_ForAircraft);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Primary_ForShips);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Primary_ForBuildings);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Primary_Unused1);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Primary_Unused2);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Primary_Unused3);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Primary_ForDefenses);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&ToCapture);
    for (i = 0; i < 12; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&PlanningPaths[i]);
    for (i = 0; i < 3; i++)
        DropshipData[i].Swizzle();

    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        SuperClass* item = 0;
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
        TagClass* item = 0;
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
        AngerStruct node;
        node.House = 0;
        node.AngerLevel = 0;
        hr = pStm->Read(&node, 8, 0);
        if (hr < 0)
            return hr;
        AngerNodes.AddItem(node);
    }
    for (i = 0; i < AngerNodes.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&AngerNodes.Items[i]);
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        ScoutStruct node;
        node.A = 0;
        node.B = 0;
        hr = pStm->Read(&node, 8, 0);
        if (hr < 0)
            return hr;
        ScoutNodes.AddItem(node);
    }
    for (i = 0; i < ScoutNodes.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&ScoutNodes.Items[ScoutNodes.Count - 1]);
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        BuildingClass* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        ConYards.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        BuildingClass* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        Buildings.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        BuildingClass* item = 0;
        hr = pStm->Read(&item, 4, 0);
        if (hr < 0)
            return hr;
        UnitRepairStations.AddItem(item);
    }
    count = 0;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    while (count--) {
        BuildingClass* item = 0;
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
        BuildingClass* item = 0;
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
        BuildingClass* item = 0;
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
        BuildingClass* item = 0;
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
        BuildingClass* item = 0;
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
        BuildingClass* item = 0;
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
        BuildingClass* item = 0;
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
        BuildingClass* item = 0;
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
        StartingTechnoStruct* unit = new StartingTechnoStruct;
        ObjectTypeClass* type = 0;
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
        unit->Cell.X = x;
        unit->Cell.Y = y;
        StartingUnits.AddItem(unit);
    }

    for (i = 0; i < Supers.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Supers.Items[i]);
    for (i = 0; i < RelatedTags.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&RelatedTags.Items[i]);
    for (i = 0; i < ConYards.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&ConYards.Items[i]);
    for (i = 0; i < Buildings.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Buildings.Items[i]);
    for (i = 0; i < UnitRepairStations.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&UnitRepairStations.Items[i]);
    for (i = 0; i < Grinders.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Grinders.Items[i]);
    for (i = 0; i < Absorbers.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Absorbers.Items[i]);
    for (i = 0; i < Bunkers.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Bunkers.Items[i]);
    for (i = 0; i < Occupiables.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Occupiables.Items[i]);
    for (i = 0; i < CloningVats.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&CloningVats.Items[i]);
    for (i = 0; i < SecretLabs.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&SecretLabs.Items[i]);
    for (i = 0; i < PsychicDetectionBuildings.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&PsychicDetectionBuildings.Items[i]);
    for (i = 0; i < FactoryPlants.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(&FactoryPlants.Items[i]);
    for (i = 0; i < StartingUnits.Count; i++)
        DAT_00B0C110.SwizzleManagerClass::vf_4(StartingUnits.Items[i]);

    int hasAIGeneral = 0;
    hr = pStm->Read(&hasAIGeneral, 4, 0);
    if (hr < 0 || !hasAIGeneral)
        return hr;
    return OleLoadFromStream(pStm, DAT_007E9AF0, (void**)&AIGeneral);
}

// FUNCTION: GAMEMD 0x504080
HRESULT __stdcall HouseClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT result = AbstractClass::Save(pStm, fClearDirty);

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
        StartingTechnoStruct* unit = StartingUnits.Items[i];
        hr = pStm->Write(unit, 4, 0);
        if (hr < 0)
            return hr;
        hr = pStm->Write(&unit->Cell.X, 2, 0);
        if (hr < 0)
            return hr;
        hr = pStm->Write(&unit->Cell.Y, 2, 0);
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
HRESULT __stdcall HouseClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;

    *pClassID = CLSID_House;
    return S_OK;
}

// FUNCTION: GAMEMD 0x504730
int HouseClass::vf_12()
{
    return sizeof(HouseClass);
}

// FUNCTION: GAMEMD 0x504790
//
// Add `scoreAdd` to the anger level of every node tracking `house`, then
// re-pick the enemy: the angriest node whose house is not defeated and not an
// ally (the ally test is the 0x4F9A50 overload inlined). The winner's array
// index lands in EnemyHouseIndex, or -1 when no node qualifies.
void HouseClass::UpdateAngerNodes(int scoreAdd, HouseClass* house)
{
    int i;

    for (i = 0; i < this->AngerNodes.Count; i++) {
        if (this->AngerNodes.Items[i].House == house)
            this->AngerNodes.Items[i].AngerLevel += scoreAdd;
    }

    HouseClass* best = 0;
    int bestLevel = 0;

    for (i = 0; i < this->AngerNodes.Count; i++) {
        int level = this->AngerNodes.Items[i].AngerLevel;
        HouseClass* h = this->AngerNodes.Items[i].House;
        if (level > bestLevel && !h->Defeated && !this->IsAlliedWith(h)) {
            bestLevel = level;
            best = h;
        }
    }

    if (best != 0)
        this->EnemyHouseIndex = best->ArrayIndex;
    else
        this->EnemyHouseIndex = -1;
}

// FUNCTION: GAMEMD 0x5051E0
//
// First type in the list this house may build: owner bit for its parent
// country, required and forbidden house masks, AI base-planning side. A type
// carrying a super weapon is skipped when supers are allowed, unless it is a
// construction-yard type or its super cannot be disabled from the shell.
TechnoTypeClass* HouseClass::FirstBuildableFromArray(DynamicVectorClass<TechnoTypeClass*>* items)
{
    unsigned int owner = 1 << HouseTypeClass::FindIndexOfName(Type->ParentCountry);

    for (int i = 0; i < items->Count; i++) {
        TechnoTypeClass* type = items->Items[i];
        if ((type->OwnerFlags & owner)
            && (type->RequiredHouses == 0xFFFFFFFF
                || (type->RequiredHouses & (1 << Type->ArrayIndex2)))
            && (type->ForbiddenHouses == 0xFFFFFFFF
                || !(type->ForbiddenHouses & (1 << Type->ArrayIndex2)))
            && (type->AIBasePlanningSide == -1
                || type->AIBasePlanningSide == Type->SideIndex)) {
            if (DAT_00A8B263) {
                return type;
            }
            BuildingTypeClass* buildingType = static_cast<BuildingTypeClass*>(type);
            if (buildingType->SuperWeapon == -1) {
                return type;
            }
            for (int j = 0; j < RulesInstance->list_091C.Count; j++) {
                if (RulesInstance->list_091C.Items[j] == buildingType) {
                    return type;
                }
            }
            if (!Supers.Items[buildingType->SuperWeapon]->Type->DisableableFromShell) {
                return type;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x506B70
// Empty function.
void __cdecl FUN_00506B70()
{
}

// FUNCTION: GAMEMD 0x506B80
// Empty function.
void __cdecl FUN_00506B80()
{
}

// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern ScenarioClass* DAT_00A8B230;

// FUNCTION: GAMEMD 0x508150
// Estimates the enemy's mix of vehicles, aircraft and infantry from the costs of what its enemy house
// owns (plus a flat 3000 and a difficulty-scaled random jitter) and stores the three shares.
void HouseClass::FUN_00508150()
{
    if (EnemyHouseIndex == -1) {
        PredictionEnemyInfantry = 0.33f;
        PredictionEnemyAir = 0.33f;
        PredictionEnemyArmor = 0.33f;
        return;
    }
    HouseClass* enemy = DAT_00A8022C[EnemyHouseIndex];
    int aircraft = enemy->TotalOwnedAircraftCost + 3000;
    int vehicles = enemy->TotalOwnedVehicleCost + 3000;
    int infantry = enemy->TotalOwnedInfantryCost + 3000;

    int range;
    range = (int)(aircraft * (RulesInstance->list_09A8.Items[AIDifficulty] * 0.01f));
    aircraft += DAT_00A8B230->unknown_0218.RandomRanged(-range, range);
    range = (int)(vehicles * (RulesInstance->list_09A8.Items[AIDifficulty] * 0.01f));
    vehicles += DAT_00A8B230->unknown_0218.RandomRanged(-range, range);
    range = (int)(infantry * (RulesInstance->list_09A8.Items[AIDifficulty] * 0.01f));
    infantry += DAT_00A8B230->unknown_0218.RandomRanged(-range, range);

    int total = aircraft + vehicles + infantry;
    if (total <= 0) {
        PredictionEnemyInfantry = 0.33f;
        PredictionEnemyAir = 0.33f;
        PredictionEnemyArmor = 0.33f;
        return;
    }
    PredictionEnemyArmor = (float)vehicles / (float)total;
    PredictionEnemyAir = (float)aircraft / (float)total;
    PredictionEnemyInfantry = (float)infantry / (float)total;
}

// FUNCTION: GAMEMD 0x005095D0
// Count the entries of the global vector at 0x8B40E8 whose +0x2C is this
// object and whose +0x24 is `kind`, walking from the end.
int Obj_005095D0::FUN_005095D0(int kind)
{
    int count = 0;
    for (int i = DAT_008B40F8 - 1; i >= 0; i--) {
        Team_005095D0* team = DAT_008B40EC[i];
        if (team != NULL && team->unknown_2C == this && kind == team->unknown_24) {
            count++;
        }
    }
    return count;
}

// GLOBAL: GAMEMD 0x8B3DC4 / 0x8B3DD0 -- a techno array, items and count.
extern TechnoClass** DAT_008B3DC4;
extern int DAT_008B3DD0;

// FUNCTION: GAMEMD 0x508F60
// Switches the house's spy-satellite reveal on or off: it is on while a live, active radar-type building
// that is not being sold stays unpowered or inactive, and the local player hears the matching sound.
void HouseClass::FUN_00508F60()
{
    int i;
    RecheckRadar = 0;
    for (i = 0; i < Buildings.Count; i++) {
        BuildingClass* building = Buildings.Items[i];
        if (building != 0 && building->Type->bools_16A4[1] && !building->InLimbo && building->IsOnMap) {
            if (IsControlledByCurrentPlayer_0050E0E0(this) && !building->DiscoveredByCurrentPlayer
                && Session_00A8B238.GameMode == 0) {
                continue;
            }
            if (building->CurrentMission != 0x13 && building->QueuedMission != 0x13) {
                if (!building->vf_117()) {
                    if (SpySatActive) {
                        return;
                    }
                    DAT_0087F7E8.FUN_00577D90(this);
                    SpySatActive = 1;
                    if (this == DAT_00A83D4C) {
                        FUN_00750920(RulesInstance->SpySatActivationSound, 1.0f, 0x2000, 0);
                    }
                    return;
                }
                break;
            }
        }
    }
    if (SpySatActive) {
        DAT_0087F7E8.FUN_00577AB0(this);
        SpySatActive = 0;
        if (this == DAT_00A83D4C) {
            FUN_00750920(RulesInstance->SpySatDeactivationSound, 1.0f, 0x2000, 0);
        }
    }
}

// FUNCTION: GAMEMD 0x509610
// Whether every slot of the team type's task force can be filled: the type is buildable by this house
// or (outside multiplayer) some unit of this house of that type can join the team.
bool HouseClass::FUN_00509610(TeamTypeClass* team)
{
    if (team != 0 && team->TaskForce != 0) {
        for (int i = 0; i < team->TaskForce->EntryCount; i++) {
            TechnoTypeClass* type = team->TaskForce->Entries[i].Type;
            if (type == 0 || type->vf_37(true, true, false, this) == 0) {
                if (Session_00A8B238.GameMode != 0) {
                    return false;
                }
                int k = DAT_008B3DD0 - 1;
                if (k < 0) {
                    return false;
                }
                for (;;) {
                    TechnoClass* techno = DAT_008B3DC4[k];
                    if (techno->Owner == this
                        && type == techno->vf_33()
                        && team->FUN_006F1E20(techno, this)) {
                        break;
                    }
                    k--;
                    if (k < 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x509CC0
// Empty function that pops its stack arguments.
void __stdcall FUN_00509CC0(int a1)
{
}

// GLOBAL: GAMEMD 0x7E2AC8 -- default multiplier used by both native helpers.
extern const float DAT_007E2AC8;

// GLOBAL: GAMEMD 0xA8ED6B -- when set, base-node bookkeeping is skipped.
extern unsigned char DAT_00A8ED6B;

// FUNCTION: GAMEMD 0x50A490
// A building of this house was destroyed: finds its base node, clears the other nodes that point at the
// same cell and, for a defense in a multiplayer game, empties the node itself.
void HouseClass::FUN_0050A490(BuildingClass* building)
{
    if (!DAT_00A8ED6B) {
        CoordStruct coord = building->Location;
        Cell cell((short)(coord.X / 256), (short)(coord.Y / 256));
        for (int i = 0; i < Base.unknown_14; i++) {
            BaseNodeClass* node = &Base.unknown_08[i];
            if (node->unknown_00 == building->Type->ArrayIndex && node->unknown_04 == cell) {
                Cell nodeCell = Base.unknown_08[i].unknown_04;
                for (int j = 0; j < Base.unknown_14; j++) {
                    if (i != j && Base.unknown_08[j].unknown_04 == nodeCell) {
                        Base.unknown_08[j].unknown_04 = DAT_00A8EF98;
                    }
                }
                if (building->Type->bools_1700[6] && Session_00A8B238.GameMode != 0) {
                    Base.unknown_08[i].unknown_00 = -1;
                    Base.unknown_08[i].unknown_04 = DAT_00A8EF98;
                }
                return;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x50B760
// In a multiplayer game, whether any cell within the base-spacing ring around a building footprint at
// `cell` is marked as base space of this house. Outside multiplayer the answer is always yes.
bool HouseClass::FUN_0050B760(BuildingTypeClass* type, CellStruct* cell)
{
    if (Session_00A8B238.GameMode == 0) {
        return true;
    }
    int spacing = RulesInstance->AIBaseSpacing;
    int width = type->GetFoundationWidth() + spacing * 2;
    int height = type->GetFoundationHeight(false) + spacing * 2;
    unsigned int bit = 1 << ArrayIndex;
    for (int x = cell->X - spacing - 1; x < cell->X + width + 1; x++) {
        for (int y = cell->Y - spacing - 1; y < cell->Y + height + 1; y++) {
            CellStruct position;
            position.X = x;
            position.Y = y;
            if (DAT_0087F7E8.FUN_005657A0(&position)->BaseSpacerOfHouses & bit) {
                return true;
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x50BDF0
float HouseClass::FUN_0050BDF0(TechnoTypeClass* type)
{
    switch (type->vf_11()) {
    case 16:
        return Type->CostInfantryMult;
    case 40:
        return Type->CostUnitsMult;
    case 3:
        return Type->CostAircraftMult;
    case 7:
        if (static_cast<BuildingTypeClass*>(type)->BuildCat == 5)
            return Type->CostDefensesMult;
        return Type->CostBuildingsMult;
    }
    return DAT_007E2AC8;
}

// FUNCTION: GAMEMD 0x50BEB0
float HouseClass::FUN_0050BEB0(TechnoTypeClass* type)
{
    switch (type->vf_11()) {
    case 16:
        return CostInfantryMult;
    case 40:
        return CostUnitsMult;
    case 3:
        return CostAircraftMult;
    case 7:
        if (static_cast<BuildingTypeClass*>(type)->BuildCat == 5)
            return CostDefensesMult;
        return CostBuildingsMult;
    }
    return DAT_007E2AC8;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50BF60  HouseClass::CalculateCostMultipliers
//
// Start every cost multiplier at one and fold in each owned building's five
// type factors, re-reading the list pointer and the building for every
// factor as retail does.
//
// MATCHED 100% (44/44). The one lever: write the five multipliers through a
// `float*` local aimed at the first of them rather than through the named
// members. With the named float members cl 8804's type-based alias analysis
// proves the stores cannot touch the int `Count` and hoists
// `MOV EDX,[ECX+0x150]` above the whole function (4.3%); routing them through
// a float pointer makes the Count read live again, so the entry test loads it
// and the back edge re-reads it in place (`CMP EAX,dword ptr [ECX+0x150]`),
// which is exactly retail's loop. A `*(volatile int*)&Count` read in the loop
// condition gets the re-read too but costs a `MOV EDX,mem; CMP EAX,EDX` pair
// at the back edge instead of retail's folded memory compare (84.4%).
void HouseClass::CalculateCostMultipliers()
{
    float* mult = &CostInfantryMult;

    mult[0] = 1.0f;
    mult[1] = 1.0f;
    mult[2] = 1.0f;
    mult[3] = 1.0f;
    mult[4] = 1.0f;

    for (int i = 0; i < FactoryPlants.Count; ++i) {
        mult[0] = FactoryPlants.Items[i]->Type->InfantryCostBonus * mult[0];
        mult[1] = FactoryPlants.Items[i]->Type->UnitsCostBonus * mult[1];
        mult[2] = FactoryPlants.Items[i]->Type->AircraftCostBonus * mult[2];
        mult[3] = FactoryPlants.Items[i]->Type->BuildingsCostBonus * mult[3];
        mult[4] = FactoryPlants.Items[i]->Type->DefensesCostBonus * mult[4];
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50C160
// Fp getter.
float Obj_0050C160::FUN_0050C160() const
{
    return unknown_34->unknown_148;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50C170
//
// Walk the global house list comparing each house's name against the caller's
// string; return the index of the first hit or -1. The name is first copied
// into a 20-byte frame buffer (retail's inlined strcpy: REPNE SCASB then REP
// MOVSD/MOVSB), and the comparison is the inlined strcmp byte loop. The count
// is re-read from the global at the end of every iteration.
int HouseClass::FindIndexByName(const char* name)
{
    char buf[20];

    for (int i = 0; i < DAT_00A80238; i++) {
        strcpy(buf, DAT_00A8022C[i]->PlainName);
        if (strcmp(buf, name) == 0) {
            return i;
        }
    }

    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Unclaimed (retail inlines 0x505180 here, which is not reconstructed), GAMEMD 0x50C210
// Re-centres the base on the last live building of one of the base-centre types (the construction yards).
void HouseClass::FUN_0050C210()
{
    for (int i = Buildings.Count - 1; i >= 0; i--) {
        BuildingClass* building = Buildings.Items[i];
        for (int j = 0; j < RulesInstance->list_08AC.Count; j++) {
            if (RulesInstance->list_08AC.Items[j] == building->Type) {
                if (!building->InLimbo) {
                    if (building == 0) {
                        return;
                    }
                    CoordStruct location = building->Location;
                    Cell cell((short)(location.X / 256), (short)(location.Y / 256));
                    BaseSpawnCell = cell;
                    FUN_00505180();
                    Base.unknown_08[0].unknown_04 = cell;
                    Base.unknown_50 = cell;
                    return;
                }
                break;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x50CAD0
// Whether the base node's building type may be (re)built now: miners are capped by difficulty, other
// types wait out the replace delay or need a neighbouring building of this house.
bool HouseClass::FUN_0050CAD0(BaseNodeClass* node)
{
    int index = node->unknown_00;
    if (index < 0) {
        return true;
    }
    if (index >= DAT_00A83C78) {
        return false;
    }
    BuildingTypeClass* type = DAT_00A83C6C[index];
    if (type->ResourceDestination && type->ResourceGatherer) {
        if (CountResourceGatherers < RulesInstance->AISlaveMinerNumber.Items[AIDifficulty]) {
            return true;
        }
        return false;
    }
    if (Session_00A8B238.GameMode == 0) {
        return true;
    }
    if (type == 0) {
        return false;
    }
    if (type->GetWeapon(0)->WeaponType != 0) {
        return true;
    }
    if (type->bools_1570[1]) {
        for (int facing = 0; facing < 8; facing++) {
            CellClass* cell = DAT_0087F7E8.FUN_005657A0(&node->unknown_04);
            BuildingClass* building = cell->GetNeighbourCell(facing)->GetBuilding();
            if (building != 0 && building->Owner == this) {
                return true;
            }
        }
        return false;
    }
    if (type->PowerBonus > 0) {
        return true;
    }
    if (LATime + RulesInstance->AIRestrictReplaceTime <= CurrentFrame) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x50D440
//
// Re-create the house's recorded starting forces, last entry first. Each
// entry's type is asked what it is; aircraft, building, unit and infantry
// types create an object for this house, which is kept only when its flag
// byte says it is a techno. The object is then unlimboed at the centre of the
// entry's cell, and torn down again through +0xF8 when that fails.
//
// The two case groups carry the same body twice: retail keeps two copies of
// the create-and-test and cross-jumps only the flag fold. The techno pointer
// is left null for any other kind of type and the unlimbo still dereferences
// it, as retail does. Score with scripts/vc6/raw_match.py: diff_retail.py
// also counts the embedded jump/index tables (19 junk `add`s) as instructions.
//
// PARTIAL (81.9%, 68/83 instructions; mnemonic multiset identical). The whole
// residual is one register swap: retail keeps `this` in EBX and the entry
// pointer in EBP, cl 8804 the other way round, so the prologue/epilogue pushes
// and every use of the two differ by name only. Written on the real types
// (StartingTechnoStruct::Type/Cell, ObjectTypeClass::vf_35, TechnoClass::vf_292)
// the score is unchanged from the earlier view-struct version, which tried: a
// `house = this` alias; all locals at function scope; the entry as a reference
// or `const`; re-indexing (reloads after the calls); a named cell pointer; an
// inlined `operator[]`; per-case block-scoped `obj`; a `default:` arm; helper
// functions for the create-and-test, the loop body or the whole loop; swapped
// case order; a `while` loop; local declaration order; a separate `placed` bool.
void HouseClass::RespawnStartingForces()
{
    int i;

    for (i = this->StartingUnits.Count - 1; i >= 0; i--) {
        StartingTechnoStruct* entry = this->StartingUnits.Items[i];
        ObjectTypeClass* type = entry->Type;
        TechnoClass* techno = 0;
        ObjectClass* obj;

        switch (type->vf_11()) {
        case 3:
        case 7:
        case 0x28:
            obj = type->vf_35(this);
            if (obj == 0) {
                techno = 0;
            } else {
                techno = obj->Flags.IsTechno ? static_cast<TechnoClass*>(obj) : 0;
            }
            break;
        case 0x10:
            obj = type->vf_35(this);
            if (obj == 0) {
                techno = 0;
            } else {
                techno = obj->Flags.IsTechno ? static_cast<TechnoClass*>(obj) : 0;
            }
            break;
        }

        CellClass* cell = DAT_0087F7E8.FUN_005657A0(&entry->Cell);
        CoordStruct coord = cell->vf_18();
        if (!techno->vf_292(&coord, 0)) {
            techno->vf_62();
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050D9C0
//
// True when the signed member at +0x164 is positive.
bool FUN_0050D9C0(Predicate_0050D9C0* self)
{
    return *(int*)(self->Bytes + 0x164) > 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050D9D0
//
// True when the signed member at +0x168 is positive.
bool FUN_0050D9D0(Predicate_0050D9C0* self)
{
    return *(int*)(self->Bytes + 0x168) > 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DA00
//
// Store the argument into the member at +0x54F0.
void Setter_00487C70::FUN_0050DA00(int value)
{
    *(int*)(Bytes + 0x54F0) = value;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DA10
void HouseClass::FUN_0050DA10()
{
    PreferredTargetCell = DAT_00A8EF98;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50DA40
// Stores its argument in a member; pops its stack arguments.
void Obj_0050DA40::FUN_0050DA40(int a1)
{
    unknown_54F8 = a1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DA50
void HouseClass::FUN_0050DA50()
{
    PreferredDefensiveCell = DAT_00A8EF98;
    PreferredDefensiveCellStartTime = -100;
    PreferredDefensiveCell2 = DAT_00A8EF98;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DA80
// +0x577C when it is 0..3, else 0.
int HouseClass::FUN_0050DA80() const
{
    int value = Edge;
    if (value >= 0 && value <= 3) {
        return value;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DEF0
// +0x5490 while +0x5494 still holds the global cell at 0xA8EF98, else +0x5494.
Cell HouseClass::FUN_0050DEF0() const
{
    if (BaseCenter == DAT_00A8EF98) {
        return BaseSpawnCell;
    }
    return BaseCenter;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DFE0
//
// Store the argument into the member at +0x5494.
void Setter_00487C70::FUN_0050DFE0(int value)
{
    *(int*)(Bytes + 0x5494) = value;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050DFF0
void HouseClass::FUN_0050DFF0()
{
    BaseCenter = DAT_00A8EF98;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050E000
//
// Store the argument into the member at +0x5490.
void Setter_00487C70::FUN_0050E000(int value)
{
    *(int*)(Bytes + 0x5490) = value;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E0E0
//
// One powering centre of this house has gone. Once the count reaches zero
// every live techno of this house whose type is the powered one is
// deactivated, walking the techno array from the top; if any was, and the
// house is the local player's, the "robot tanks offline" EVA line plays.
void HouseClass::LostPoweredCenter(TechnoTypeClass* type)
{
    if (--this->PoweredUnitCenters == 0 && type != 0) {
        bool found = false;
        for (int i = DAT_00A8EC78.Count - 1; i >= 0; i--) {
            Techno_0050E0E0* techno = DAT_00A8EC78.Items[i];
            if (techno->Owner == this
                && (techno->*techno->Vtbl->GetTechnoType)() == type
                && !techno->InLimbo) {
                techno->Deactivate();
                found = true;
            }
        }
        if (found && DAT_00A8E9A0 && IsControlledByCurrentPlayer_0050E0E0(this)
            && DAT_00A8E7AC == 0) {
            Vox_0050E0E0::Play(STR_00824E4C, -1, -1);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E340
ULONG __stdcall HouseClass::AddRef()
{
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E350
ULONG __stdcall HouseClass::Release()
{
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E360
int HouseClass::vf_11()
{
    return 13;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E370
int HouseClass::vf_16()
{
    return ArrayIndex;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x50E380 -- compiler-generated scalar deleting destructor.
// SYNTHETIC: GAMEMD 0x510460 -- compiler-generated vector deleting destructor of DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E430
// Stores several members; pops its stack arguments.
void Obj_0050E430::FUN_0050E430(unsigned char a1, unsigned char a2, unsigned char a3)
{
    unknown_00 = a1;
    unknown_01 = a2;
    unknown_02 = a3;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E450
// Stores several members; pops its stack arguments.
Obj_0050E450* Obj_0050E450::FUN_0050E450(int a1, Arg2_0050E450* a2)
{
    unknown_00 = a1;
    unknown_04 = a2->unknown_00;
    unknown_08 = 0;
    unknown_0C = 0;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x50E590
// DynamicVectorClass<AngerStruct>::Slot5 (slot 5)
template class DynamicVectorClass<AngerStruct>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x50E600
// DynamicVectorClass<ScoutStruct>::Slot5 (slot 5)
template class DynamicVectorClass<ScoutStruct>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x50E670
// DynamicVectorClass<HouseClass::BuildChoiceClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x50E690
// VectorClass<HouseClass::BuildChoiceClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x50F4E0
// VectorClass<HouseClass::BuildChoiceClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x50F520
// VectorClass<HouseClass::BuildChoiceClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x50F600
// VectorClass<HouseClass::BuildChoiceClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x50F640
// VectorClass<HouseClass::BuildChoiceClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x50F660
// DynamicVectorClass<HouseClass::BuildChoiceClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x50F710
// DynamicVectorClass<HouseClass::BuildChoiceClass*>::FindItemIndex (slot 4)
template class VectorClass<HouseClass::BuildChoiceClass*>;

// The receiver of the cell comparison at 0x50E470 is a cell itself.
struct Cell_0050E470 : Cell_004FFD90
{
    // FUNCTION: GAMEMD 0x50E470
    bool FUN_0050E470(const Cell_004FFD90* other);
};

// FUNCTION: GAMEMD 0x50E470
// True when both coordinates of the two cells are equal.
bool Cell_0050E470::FUN_0050E470(const Cell_004FFD90* other)
{
    return X == other->X && Y == other->Y;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50E6A0
// DynamicVectorClass<const TeamTypeClass*>::Clear

// FUNCTION: GAMEMD 0x50E6D0
// DynamicVectorClass<const TeamTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x50E6F0
// VectorClass<const TeamTypeClass*>::Slot6

// SYNTHETIC: GAMEMD 0x50E7E0
// TypeList<const TeamTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x50E830
// DynamicVectorClass<const TeamTypeClass*>::copy constructor

// SYNTHETIC: GAMEMD 0x50E8C0
// DynamicVectorClass<const TeamTypeClass*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x50F740
// VectorClass<const TeamTypeClass*>::operator==

// FUNCTION: GAMEMD 0x50F780
// VectorClass<const TeamTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x50F830
// VectorClass<const TeamTypeClass*>::Clear

// FUNCTION: GAMEMD 0x50F860
// VectorClass<const TeamTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x50F8A0
// VectorClass<const TeamTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x50F8C0
// DynamicVectorClass<const TeamTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x50F970
// DynamicVectorClass<const TeamTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x510310
// VectorClass<const TeamTypeClass*>::scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050F9A0
// VectorClass<bool>::operator==
// FUNCTION: GAMEMD 0x0050F9E0
// VectorClass<bool>::SetCapacity
// FUNCTION: GAMEMD 0x0050FAC0
// VectorClass<bool>::FindItemIndex
// FUNCTION: GAMEMD 0x0050FB00
// VectorClass<bool>::Slot5
// FUNCTION: GAMEMD 0x0050FB20
// DynamicVectorClass<bool>::SetCapacity
// FUNCTION: GAMEMD 0x0050FBD0
// DynamicVectorClass<bool>::FindItemIndex
// FUNCTION: GAMEMD 0x0050E730
// DynamicVectorClass<bool>::Slot5
// VTABLE: GAMEMD 0x007EAA5C -- VectorClass<bool>.
// VTABLE: GAMEMD 0x007EAA7C -- DynamicVectorClass<bool>.
template class VectorClass<bool>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050FC00
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::operator==
// FUNCTION: GAMEMD 0x0050FC60
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::SetCapacity
// FUNCTION: GAMEMD 0x0050FDB0
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x0050FE00
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::Slot5
// FUNCTION: GAMEMD 0x0050FF50
// DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::AddItem
// FUNCTION: GAMEMD 0x0050FFB0
// DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::FindItemIndex
// FUNCTION: GAMEMD 0x0050E7A0
// DynamicVectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::Slot5
template class VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*> >;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050F070
// DynamicVectorClass<AngerStruct>::SetCapacity
// FUNCTION: GAMEMD 0x0050F170
// DynamicVectorClass<AngerStruct>::FindItemIndex
// VTABLE: GAMEMD 0x007EA984 -- VectorClass<AngerStruct>.
// VTABLE: GAMEMD 0x007EA924 -- DynamicVectorClass<AngerStruct>.
template class VectorClass<AngerStruct>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0050F3A0
// DynamicVectorClass<ScoutStruct>::SetCapacity
// FUNCTION: GAMEMD 0x0050F4A0
// DynamicVectorClass<ScoutStruct>::FindItemIndex
// VTABLE: GAMEMD 0x007EA9A4 -- VectorClass<ScoutStruct>.
// VTABLE: GAMEMD 0x007EA904 -- DynamicVectorClass<ScoutStruct>.
template class VectorClass<ScoutStruct>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x50FF40
// Empty function.
void __cdecl FUN_0050FF40()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x510860  (__thiscall)
//
// Grow the cell array by `additionalCapacity` slots, preserving the existing
// Count elements. Reject a negative request; reject allocation failure. On
// success: copy the live elements, free the old buffer, publish the new buffer
// and capacity, and clear the Unknown_10 cursor.
//
// MATCHED (100%, 56/56) as plain C++. The allocation is an array new of
// BasePlanningCell, which has an (empty) default constructor: retail's
// otherwise unexplained `DEC EBX; MOV [ESP+0x14],EBX` is the counter of the
// element-construction loop, whose empty body cl removes while keeping the
// counter's store. A raw operator new call instead gives 1.8%. The success
// arms are nested so both failures fall through to the one trailing
// `return false`, as in retail.
// ---------------------------------------------------------------------------
bool BasePlanningCellContainer::AddCapacity(int additionalCapacity)
{
    if (additionalCapacity >= 0) {
        int newCapacity = Capacity + additionalCapacity;
        BasePlanningCell* newItems = new BasePlanningCell[newCapacity];
        if (newItems != 0) {
            int i = 0;
            if (Count > 0) {
                do {
                    newItems[i] = Items[i];
                    ++i;
                } while (i < Count);
            }
            delete[] Items;
            Items = newItems;
            Capacity += additionalCapacity;
            Unknown_10 = 0;
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x5108F0  (__cdecl)
//
// qsort comparator over BasePlanningCell::Weight (the leading int of each
// element). Ascending: 0 when equal, +1 when a > b, -1 when a < b.
//
// MATCHED (100%, 16/16). This was recorded as a phrasing-invariant setcc-tail
// delta and is not one. Retail emits `setge dl; dec; and -2; inc` and the
// ternary written `(wa >= wb) ? 1 : -1` emits the mirror `setl dl; dec; and 2;
// dec` (81.2%). The lever is which arm carries the negative literal: writing
// the *less-than* test with -1 in the true arm, `(wa < wb) ? -1 : 1`, makes cl
// keep the comparison as written and invert the arithmetic instead, which is
// retail's tail exactly. Spelling the tail out by hand as
// `((wa >= wb) - 1 & -2) + 1` also reaches 100%, so the two forms are the same
// codegen path. Eight other spellings stay at 81.2% (`>` ternary, nested ifs,
// a named bool, a named int result, the loads written inline) and two are
// worse: `1 - 2 * (wa < wb)` is 62.5% and inverting the equality guard to
// `if (wa != wb) return ...` is 43.8%.
// ---------------------------------------------------------------------------
int __cdecl BasePlanningCellContainer::Comparator(const void* a, const void* b)
{
    int wa = *(const int*)a;
    int wb = *(const int*)b;
    if (wa == wb)
        return 0;
    return (wa < wb) ? -1 : 1;
}

// FUNCTION: GAMEMD 0x00510970
// Constructor (capacity, optional storage) of the vector of BuildingTypeClass distribution objects.

// FUNCTION: GAMEMD 0x504860
// Sets the flag byte of every scout node that tracks `house`.
void HouseClass::MarkScoutNode(HouseClass* house)
{
    for (int i = 0; i < ScoutNodes.Count; i++) {
        if ((HouseClass*)ScoutNodes.Items[i].A == house)
            ScoutNodes.Items[i].B = 1;
    }
}

// Retail's starting-unit record: a type pointer and a cell copied as one dword
// (0x50D560 stores both as dwords into the 8-byte allocation).
struct StartingUnitRecord_0050D560
{
    void* Type;     // +0x00
    int   Cell;     // +0x04
};
GG_STATIC_ASSERT(sizeof(StartingUnitRecord_0050D560) == 8);

// FUNCTION: GAMEMD 0x50D560
// Appends a new (type, cell) record to StartingUnits.
void HouseClass::AddStartingUnit(void* type, int cell)
{
    StartingUnitRecord_0050D560* record = new StartingUnitRecord_0050D560;
    record->Cell = cell;
    record->Type = type;
    StartingUnits.AddItem((StartingTechnoStruct*)record);
}

// FUNCTION: GAMEMD 0x50D5D0
// Deletes every starting-unit record, newest first, then clears the vector.
void HouseClass::FreeStartingUnits()
{
    for (int i = StartingUnits.Count - 1; i >= 0; i--)
        delete StartingUnits.Items[i];
    StartingUnits.Clear();
}

// FUNCTION: GAMEMD 0x50D610
// Records every techno owned by this house (type and current cell) as a starting-unit
// record, walking the techno array from the top.
void HouseClass::FUN_0050D610()
{
    for (int i = DAT_00A8EC78.Count - 1; i >= 0; i--) {
        Techno_0050E0E0* techno = DAT_00A8EC78.Items[i];
        if ((void*)techno->Owner == (void*)this) {
            TechnoCell_0050E0E0 buffer;
            int cell = *(int*)(techno->*techno->Vtbl->GetCell)(&buffer);
            void* type = (void*)(techno->*techno->Vtbl->GetTechnoType)();
            StartingUnitRecord_0050D560* record = new StartingUnitRecord_0050D560;
            record->Type = type;
            record->Cell = cell;
            StartingUnits.AddItem((StartingTechnoStruct*)record);
        }
    }
}

GG_STATIC_ASSERT(offsetof(HouseTypeClass, SpeedInfantryMult) == 0x128);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, SpeedUnitsMult) == 0x12C);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, SpeedAircraftMult) == 0x130);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, BuildtimeInfantryMult) == 0x134);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, BuildtimeUnitsMult) == 0x138);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, BuildtimeAircraftMult) == 0x13C);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, BuildtimeBuildingsMult) == 0x140);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, BuildtimeDefensesMult) == 0x144);

// FUNCTION: GAMEMD 0x50C050
// The country's speed multiplier for the kind of techno type given (1.0 for other kinds).
float HouseClass::FUN_0050C050(TechnoTypeClass* type)
{
    switch (type->vf_11()) {
    case 3:
        return Type->SpeedAircraftMult;
    case 16:
        return Type->SpeedInfantryMult;
    case 40:
        return Type->SpeedUnitsMult;
    }
    return DAT_007E2AC8;
}

// FUNCTION: GAMEMD 0x50C0A0
// The country's build-time multiplier for the kind of techno type given (defences are
// buildings of build category 5; 1.0 for other kinds).
float HouseClass::FUN_0050C0A0(TechnoTypeClass* type)
{
    switch (type->vf_11()) {
    case 16:
        return Type->BuildtimeInfantryMult;
    case 40:
        return Type->BuildtimeUnitsMult;
    case 3:
        return Type->BuildtimeAircraftMult;
    case 7:
        if (static_cast<BuildingTypeClass*>(type)->BuildCat == 5)
            return Type->BuildtimeDefensesMult;
        return Type->BuildtimeBuildingsMult;
    }
    return DAT_007E2AC8;
}

// Receiver of the empty-coordinate getter at 0x4FD120 (no layout claimed).
struct Obj_004FD120
{
    // FUNCTION: GAMEMD 0x4FD120
    HBCoord* FUN_004FD120(HBCoord* out, int unused);
};

// FUNCTION: GAMEMD 0x4FD120
// Writes the default (unset-base) coordinate to `out` and returns it; the second argument is ignored.
HBCoord* Obj_004FD120::FUN_004FD120(HBCoord* out, int unused)
{
    *out = HouseEmptyCoord;
    return out;
}

// FUNCTION: GAMEMD 0x4FDCE0
// For argument 4, runs the two IHouse sweeps (slots 13 and 14) on this house's interface.
bool HouseClass::FUN_004FDCE0(int arg)
{
    if (arg == 4) {
        IHouse* house = (IHouse*)((char*)this + 0x24);
        house->vf_13();
        house->IHouse_vf_14();
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4FFD50
int HouseClass::SectorOfObject(BuildingClass* object)
{
    if (object == 0)
        return -1;
    return SectorOf(object->vf_18());
}

// FUNCTION: GAMEMD 0x4FFD90
int HouseClass::SectorOfCell(CellStruct* cell)
{
    CoordStruct coords;
    coords.X = cell->X * 256 + 128;
    coords.Y = cell->Y * 256 + 128;
    coords.Z = 0;
    return SectorOf(coords);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x89A29C
unsigned char HouseMainObject;
// GLOBAL: GAMEMD 0xA83C78
int DAT_00A83C78;
// GLOBAL: GAMEMD 0xA8B263
char DAT_00A8B263;
// GLOBAL: GAMEMD 0x824E4C
extern const char STR_00824E4C[] = "EVA_RobotTanksOffline";
// GLOBAL: GAMEMD 0xA80238
int DAT_00A80238;
// GLOBAL: GAMEMD 0xA8EF98
HBCell HouseEmptyCell;
// GLOBAL: GAMEMD 0xA8EFF8
HBCoord HouseEmptyCoord;
// GLOBAL: GAMEMD 0xA83C6C
BuildingTypeClass** DAT_00A83C6C;
// GLOBAL: GAMEMD 0xA8EC78
TechnoVector_0050E0E0 DAT_00A8EC78;
// GLOBAL: GAMEMD 0x7E36C0
extern const IID DAT_007E36C0 = {0x96F02EC3, 0x6FE8, 0x11D1, {0xB6, 0xFD, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9560
extern const CLSID CLSID_House = {0xD9D4A910, 0x87C6, 0x11D1, {0xB7, 0x07, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9B00
extern const IID IID_IPublicHouse = {0xCAACF210, 0x86E3, 0x11D1, {0xB7, 0x06, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7EA768
extern const IID IID_IHouse = {0x941582E0, 0x86DA, 0x11D1, {0xB7, 0x06, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x820270
extern const IID DAT_00820270 = {0x00000109, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
// END defined globals

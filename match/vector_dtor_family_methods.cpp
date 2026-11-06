// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 44 base-template instantiations reproduce 77 remaining retail destructor
// bodies. Each group's written vptr and RTTI identify its base-destruction
// element type, not necessarily the wrapper's original declaring class.
// Multiple FUNCTION markers bind relocation-identical bodies to this model;
// their original ownership/link placement remains to be recovered. Groups are
// ordered by their first retail address. See the header for the evidence limits.
#include "vector_dtor_family_methods.h"

// ---------------------------------------------------------------------------
// The element types, declared exactly as their RTTI manglings require: `V`
// tags become `class`, `U` tags `struct`, `W4` tags an enum, and a nested or
// scoped name gets its enclosing scope. None of them is defined -- the
// destructor only ever handles `T*`, so an incomplete type is all the
// template needs, and all these declarations do is reproduce the mangled
// template argument spelling recorded by RTTI. A scope written `namespace` below could equally have
// been a class: MSVC mangles the two identically, so the binary cannot
// decide that distinction.
// ---------------------------------------------------------------------------
class AITriggerTypeClass;
class AbstractClass;
class AbstractTypeClass;
struct AcceleratorTracker;
class AircraftClass;
class AircraftTypeClass;
struct AngerStruct;
class AnimClass;
class AnimTypeClass;
class BuildingClass;
class BuildingLightClass;
class BuildingTypeClass;
class BulletTypeClass;
struct ButtonFadeEffect;
class CCINIClass;
class CampaignClass;
class CellClass;
class ColorScheme;
class ConvertClass;
class CoopCampaignClass;
struct CrossDissolveEffect;
struct DamageGroup;
struct DirtyAreaStruct;
#include "disk_id.h"
#include "type_list.h"
class DiskLaserClass;
template<class T0> class DynamicVectorClass;
class EBolt;
class EMPulseClass;
class EgoClass;
class EventClass;
class FactoryClass;
class FileEntryClass;
class FootClass;
struct GlobalPacketType;
class GraphicMenuItem;
class HSVClass;
struct HWND__;
template<class T0, class T1> struct HashObject;
class HashString;
class HouseTypeClass;
struct IConnectionPoint;
class InfantryTypeClass;
class IonBlastClass;
struct KamikazeControl;
class LaserDrawClass;
class LineTrail;
struct MPlayerScoreType;
class MSAnim;
class MSAnimEntry;
class MSSfx;
class MSSfxEntry;
class MSTextEntry;
class MapRegionClass;
class MapSelection;
class MapStage;
class MovieHandle;
class MultiMission;
class MultiplayerGameMode;
class MultiplayerTeam;
struct NodeNameType;
class ObjectClass;
class ObjectTypeClass;
class OverlayClass;
class OverlayTypeClass;
#include "_layout/owner_talk_class.h"
class ParasiteClass;
class ParticleClass;
class ParticleSystemClass;
class ParticleSystemTypeClass;
class ParticleTypeClass;
enum PassabilityType { PassabilityType_placeholder };
class PhoneEntryClass;
class PlanningBranchClass;
class PlanningMemberClass;
class PlanningNodeClass;
class PlanningTokenClass;
class Point2D;
#include "_layout/fogged_object_class.h"
#include "_layout/house_class.h"
#include "_layout/iso_tile_type_class.h"
#include "_layout/light_source_class.h"
class RadBeam;
class RadSiteClass;
struct RadarTrackingStruct;
class SchemeNode;
struct ScoutStruct;
class ScriptTypeClass;
class ShadowControlClass;
class SideClass;
#include "_layout/slave_manager_class.h"
class SmudgeClass;
class SmudgeTypeClass;
#include "_layout/spawn_manager_class.h"
class SpotLightClass;
class SubTitle;
struct SubzoneConnectionStruct;
class SuperClass;
class SuperWeaponTypeClass;
class TActionClass;
class TEventClass;
template<class T0> class TRect;
class TagClass;
class TagTypeClass;
class TaskForceClass;
class TeamTypeClass;
class TechnoClass;
class TechnoTypeClass;
class TemporalClass;
class TerrainClass;
class TerrainTypeClass;
struct ThemeControl;
class TiberiumClass;
class ToolTip;
class TriggerClass;
class TriggerTypeClass;
class TubeClass;
struct UndoInfoStruct;
class UnitClass;
class UnitTypeClass;
class VeinholeMonsterClass;
class VocClass;
class VoxClass;
class VoxelAnimTypeClass;
class WaveClass;
class WaypointPathClass;
#include "winsock_interface_class.h"
namespace WorldDominationTour
{
    class Centroid;
    class Map
    {
        struct AnimationPalette;
    };
}  // namespace WorldDominationTour
struct ZoneConnectionClass;
struct _DDSURFACEDESC;
struct _WIN32_FIND_DATAA;
struct tConnInfoStruct;
struct tagCONNECTDATA;

// ---------------------------------------------------------------------------
// The instantiations, in ascending retail-address order of each group's first
// address.
// ---------------------------------------------------------------------------

// FUNCTION: GAMEMD 0x0040B300
// VectorClass<SubzoneConnectionStruct> -- reseats retail vtable 0x007E177C; locator 0x007FA5D8 -> type descriptor 0x00816848
//   `.?AV?$VectorClass@USubzoneConnectionStruct@@@@`. 0x40B300 is slot 0 of
//   that vtable. The identical body at 0x5890B0 is slot 0 of
//   DynamicVectorClass<SubzoneConnectionStruct> (0x7ED5A0) and is bound in
//   pair_vector_ctor_family_methods.cpp.
template class VectorClass<SubzoneConnectionStruct>;

// RGB providers are owned by vector_color_slot_methods.cpp.

// FUNCTION: GAMEMD 0x0040CF30
// VectorClass<ObjectClass*> -- reseats retail vtable 0x007E192C; locator 0x007FA9A0 -> type descriptor 0x00816AA8
//   `.?AV?$VectorClass@PAVObjectClass@@@@`. 0x40CF30 is slot 0 of that vtable. The identical
//   bodies at 0x488030 (slot 0 of DynamicVectorClass<ObjectClass*>, 0x7E4F64) and 0x4AEB50
//   (slot 0 of LayerClass, 0x7E6060; owned by Display.cpp) store the VectorClass vptr 0x7E192C because the Dynamic
//   destructor inlines the base destructor; 0x488030 is bound in vector_objectclass_slot_methods.cpp.
template class VectorClass<ObjectClass*>;

// Nested char-vector instantiation moved to vector_nested_char_methods.cpp.

// VectorClass<int> -- reseats retail vtable 0x007E4DB8; locator 0x007FCDB0 -> type descriptor 0x0081C038
//   `.?AV?$VectorClass@H@@`. Its deleting destructor is owned by vector_int_methods.cpp (0x478630); the second
//   body formerly claimed here, 0x49FCE0, is CounterClass's (counter_class_r13_methods.cpp).
template class VectorClass<int>;

// Layout asserted on the int instantiation; every instantiation in this
// family has the same layout, because the only member whose type varies is
// a pointer. The assert has to follow an explicit instantiation: VC6 fails
// to re-parse the template body when offsetof is what first instantiates
// it, and it will not take a template-id as offsetof's first argument
// either, hence the typedef.
typedef VectorClass<int> GgVectorRep;
GG_STATIC_ASSERT(offsetof(GgVectorRep, Items)       == 0x4);
GG_STATIC_ASSERT(offsetof(GgVectorRep, Capacity)    == 0x8);
GG_STATIC_ASSERT(offsetof(GgVectorRep, IsAllocated) == 0xD);
GG_STATIC_ASSERT(sizeof(GgVectorRep)                == 0x10);

// FUNCTION: GAMEMD 0x004A14A0
// VectorClass<tagCONNECTDATA> -- reseats retail vtable 0x007E5C84; locator 0x007FF6D8 -> type descriptor 0x0081F5F8
//   `.?AV?$VectorClass@UtagCONNECTDATA@@@@`.
template class VectorClass<tagCONNECTDATA>;

// FUNCTION: GAMEMD 0x004D2D10
// VectorClass<FoggedObjectClass::DrawRecord> -- reseats retail vtable 0x007E8BC0; locator 0x00800800 -> type descriptor 0x00822458
//   `.?AV?$VectorClass@UDrawRecord@FoggedObjectClass@@@@`.
template class VectorClass<FoggedObjectClass::DrawRecord>;

// FUNCTION: GAMEMD 0x004D2D60
// DynamicVectorClass<FoggedObjectClass::DrawRecord> -- slot 0 of retail vtable 0x007E8BA0.
template class DynamicVectorClass<FoggedObjectClass::DrawRecord>;

// FUNCTION: GAMEMD 0x004EF620
// VectorClass<SuperClass*> -- reseats retail vtable 0x007EA504; locator 0x008022B8 -> type descriptor 0x00823DF8
//   `.?AV?$VectorClass@PAVSuperClass@@@@`.
template class VectorClass<SuperClass*>;

// FUNCTION: GAMEMD 0x004EF670
// DynamicVectorClass<SuperClass*> -- slot 0 of retail vtable 0x007EA4E4.
template class DynamicVectorClass<SuperClass*>;


// FUNCTION: GAMEMD 0x004EF940
// VectorClass<ThemeControl*> -- reseats retail vtable 0x007EA584; locator 0x00802448 -> type descriptor 0x00823F40
//   `.?AV?$VectorClass@PAUThemeControl@@@@`.
template class VectorClass<ThemeControl*>;

// FUNCTION: GAMEMD 0x007213E0
// DynamicVectorClass<ThemeControl*> -- slot 0 of retail vtable 0x007F568C.
template class DynamicVectorClass<ThemeControl*>;

// FUNCTION: GAMEMD 0x00510130
// VectorClass<AngerStruct> -- reseats retail vtable 0x007EA984; locator 0x00802BC0 -> type descriptor 0x00824588
//   `.?AV?$VectorClass@UAngerStruct@@@@`.
template class VectorClass<AngerStruct>;

// FUNCTION: GAMEMD 0x00510180
// DynamicVectorClass<AngerStruct> -- slot 0 of retail vtable 0x007EA924.
template class DynamicVectorClass<AngerStruct>;

// FUNCTION: GAMEMD 0x005101D0
// VectorClass<ScoutStruct> -- reseats retail vtable 0x007EA9A4; locator 0x00802B90 -> type descriptor 0x00824520
//   `.?AV?$VectorClass@UScoutStruct@@@@`.
template class VectorClass<ScoutStruct>;

// FUNCTION: GAMEMD 0x00510220
// DynamicVectorClass<ScoutStruct> -- slot 0 of retail vtable 0x007EA904.
template class DynamicVectorClass<ScoutStruct>;

// FUNCTION: GAMEMD 0x00510270
// VectorClass<HouseClass::BuildChoiceClass*> -- reseats retail vtable 0x007EA7D4; locator 0x00802888 -> type descriptor 0x00824418
//   `.?AV?$VectorClass@PAUBuildChoiceClass@HouseClass@@@@`.
template class VectorClass<HouseClass::BuildChoiceClass*>;

// FUNCTION: GAMEMD 0x005102C0
// DynamicVectorClass<HouseClass::BuildChoiceClass*> -- slot 0 of retail vtable 0x007EA7B4.
template class DynamicVectorClass<HouseClass::BuildChoiceClass*>;

// FUNCTION: GAMEMD 0x00510360
// VectorClass<bool> -- reseats retail vtable 0x007EAA5C; locator 0x00802D68 -> type descriptor 0x00824E70
//   `.?AV?$VectorClass@_N@@`.
template class VectorClass<bool>;

// FUNCTION: GAMEMD 0x005103B0
// DynamicVectorClass<bool> -- slot 0 of retail vtable 0x007EAA7C.
template class DynamicVectorClass<bool>;

// FUNCTION: GAMEMD 0x0054A710
// VectorClass<unsigned short*> -- reseats retail vtable 0x007ECD0C; locator 0x00804C58 -> type descriptor 0x008290F0
//   `.?AV?$VectorClass@PAG@@`.
template class VectorClass<unsigned short*>;

// FUNCTION: GAMEMD 0x0054A760
// DynamicVectorClass<unsigned short*> -- slot 0 of retail vtable 0x007ECCEC.
template class DynamicVectorClass<unsigned short*>;

// FUNCTION: GAMEMD 0x0054A7B0
// VectorClass<IsometricTileTypeClass::TileInsertType*> -- reseats retail vtable 0x007ECBFC; locator 0x00804B08 -> type descriptor 0x00829030
//   `.?AV?$VectorClass@PAUTileInsertType@IsometricTileTypeClass@@@@`.
template class VectorClass<IsometricTileTypeClass::TileInsertType*>;

// FUNCTION: GAMEMD 0x0054A800
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*> -- slot 0 of retail vtable 0x007ECBDC.
template class DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>;


// FUNCTION: GAMEMD 0x00555820
// VectorClass<LightSourceClass::PendingCellClass*> -- reseats retail vtable 0x007ECFDC; locator 0x00805040 -> type descriptor 0x00829B68
//   `.?AV?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@`.
template class VectorClass<LightSourceClass::PendingCellClass*>;

// FUNCTION: GAMEMD 0x00555870
// DynamicVectorClass<LightSourceClass::PendingCellClass*> -- slot 0 of retail vtable 0x007ECFBC.
template class DynamicVectorClass<LightSourceClass::PendingCellClass*>;

// FUNCTION: GAMEMD 0x00589060
// VectorClass<CellClass*> -- reseats retail vtable 0x007ED480; locator 0x008055E0 -> type descriptor 0x0082AB78
//   `.?AV?$VectorClass@PAVCellClass@@@@`.
template class VectorClass<CellClass*>;

// FUNCTION: GAMEMD 0x005AD570
// DynamicVectorClass<CellClass*> -- slot 0 of retail vtable 0x007ED9BC.
template class DynamicVectorClass<CellClass*>;

// FUNCTION: GAMEMD 0x0058A3D0
// VectorClass<ZoneConnectionClass> -- reseats retail vtable 0x007ED4E0; locator 0x00805610 -> type descriptor 0x0082AA88
//   `.?AV?$VectorClass@UZoneConnectionClass@@@@`.
template class VectorClass<ZoneConnectionClass>;

// FUNCTION: GAMEMD 0x0058A420
// DynamicVectorClass<ZoneConnectionClass> -- slot 0 of retail vtable 0x007ED4C0.
template class DynamicVectorClass<ZoneConnectionClass>;

// FUNCTION: GAMEMD 0x0058AA90
// VectorClass<PassabilityType> -- reseats retail vtable 0x007ED560; locator 0x00805740 -> type descriptor 0x0082ACE0
//   `.?AV?$VectorClass@W4PassabilityType@@@@`.
template class VectorClass<PassabilityType>;

// FUNCTION: GAMEMD 0x0058AAE0
// DynamicVectorClass<PassabilityType> -- slot 0 of retail vtable 0x007ED580.
template class DynamicVectorClass<PassabilityType>;

// FUNCTION: GAMEMD 0x0058AB30
// VectorClass<HashObject<unsigned int, unsigned int>> -- reseats retail vtable 0x007ED5C0; locator 0x00805828 -> type descriptor 0x0082ABA8
//   `.?AV?$VectorClass@U?$HashObject@II@@@@`.
template class VectorClass<HashObject<unsigned int, unsigned int> >;

// FUNCTION: GAMEMD 0x0058AB80
// VectorClass<HashObject<unsigned int, SubzoneConnectionStruct>> -- reseats retail vtable 0x007ED5E0; locator 0x00805858 -> type descriptor 0x0082AC10
//   `.?AV?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@`.
template class VectorClass<HashObject<unsigned int, SubzoneConnectionStruct> >;

// FUNCTION: GAMEMD 0x005AD4D0
// VectorClass<TRect<int>> -- reseats retail vtable 0x007ED970; locator 0x00805AC0 -> type descriptor 0x0082BFE0
//   `.?AV?$VectorClass@V?$TRect@H@@@@`.
template class VectorClass<TRect<int> >;

// FUNCTION: GAMEMD 0x005AD520
// DynamicVectorClass<TRect<int>> -- slot 0 of retail vtable 0x007ED99C.
template class DynamicVectorClass<TRect<int> >;

// FUNCTION: GAMEMD 0x005AD5C0
// VectorClass<double> -- reseats retail vtable 0x007EDA4C; locator 0x00805B40 -> type descriptor 0x0082C048
//   `.?AV?$VectorClass@N@@`.
template class VectorClass<double>;

// FUNCTION: GAMEMD 0x005AD610
// DynamicVectorClass<double> -- slot 0 of retail vtable 0x007EDA6C.
template class DynamicVectorClass<double>;

// FUNCTION: GAMEMD 0x005D16C0
// VectorClass<Point2D> -- reseats retail vtable 0x007EEB74; locator 0x00806B88 -> type descriptor 0x00830380
//   `.?AV?$VectorClass@VPoint2D@@@@`.
template class VectorClass<Point2D>;

// FUNCTION: GAMEMD 0x005D1710
// DynamicVectorClass<Point2D> -- slot 0 of retail vtable 0x007EEB54.
template class DynamicVectorClass<Point2D>;

// MSAnimEntry vector specialization moved to vector_msanimentry_methods.cpp.

// FUNCTION: GAMEMD 0x005D5780
// VectorClass<AcceleratorTracker> -- reseats retail vtable 0x007EECEC; locator 0x00806EC0 -> type descriptor 0x00830728
//   `.?AV?$VectorClass@UAcceleratorTracker@@@@`.
template class VectorClass<AcceleratorTracker>;

// FUNCTION: GAMEMD 0x005D57D0
// DynamicVectorClass<AcceleratorTracker> -- slot 0 of retail vtable 0x007EECCC.
template class DynamicVectorClass<AcceleratorTracker>;

// FUNCTION: GAMEMD 0x005D88B0
// VectorClass<MultiplayerGameMode*> -- reseats retail vtable 0x007EED40; locator 0x00806F58 -> type descriptor 0x008307B8
//   `.?AV?$VectorClass@PAVMultiplayerGameMode@@@@`.
template class VectorClass<MultiplayerGameMode*>;

// FUNCTION: GAMEMD 0x005D8900
// DynamicVectorClass<MultiplayerGameMode*> -- slot 0 of retail vtable 0x007EED20.
template class DynamicVectorClass<MultiplayerGameMode*>;

// FUNCTION: GAMEMD 0x00628760
// VectorClass<HSVClass> -- reseats retail vtable 0x007EF7F0; locator 0x008079E8 -> type descriptor 0x00836478
//   `.?AV?$VectorClass@VHSVClass@@@@`.
template class VectorClass<HSVClass>;

// FUNCTION: GAMEMD 0x006287B0
// DynamicVectorClass<HSVClass> -- slot 0 of retail vtable 0x007EF750.
template class DynamicVectorClass<HSVClass>;

// FUNCTION: GAMEMD 0x00628E80
// VectorClass<HashObject<HashString, SchemeNode*>> -- reseats retail vtable 0x007EF7D0; locator 0x008079B8 -> type descriptor 0x008364D0
//   `.?AV?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@`.
template class VectorClass<HashObject<HashString, SchemeNode*> >;

// FUNCTION: GAMEMD 0x0063EC50
// VectorClass<PlanningMemberClass*> -- reseats retail vtable 0x007EFF04; locator 0x008080A0 -> type descriptor 0x00836A60
//   `.?AV?$VectorClass@PAVPlanningMemberClass@@@@`.
template class VectorClass<PlanningMemberClass*>;

// FUNCTION: GAMEMD 0x0063ECF0
// VectorClass<PlanningBranchClass*> -- reseats retail vtable 0x007EFF24; locator 0x008080D0 -> type descriptor 0x008369E8
//   `.?AV?$VectorClass@PAVPlanningBranchClass@@@@`.
template class VectorClass<PlanningBranchClass*>;

// FUNCTION: GAMEMD 0x0063EED0
// VectorClass<PlanningTokenClass*> -- reseats retail vtable 0x007EFEA4; locator 0x00807FA0 -> type descriptor 0x00836970
//   `.?AV?$VectorClass@PAVPlanningTokenClass@@@@`.
template class VectorClass<PlanningTokenClass*>;

// FUNCTION: GAMEMD 0x00658D10
// VectorClass<HashObject<RadarTrackingStruct, TechnoClass*>> -- reseats retail vtable 0x007F044C; locator 0x008083F0 -> type descriptor 0x008393E0
//   `.?AV?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@`.
template class VectorClass<HashObject<RadarTrackingStruct, TechnoClass*> >;

// FUNCTION: GAMEMD 0x0065C1B0
// VectorClass<RadSiteClass*> -- reseats retail vtable 0x007F07C4; locator 0x00808628 -> type descriptor 0x00839598
//   `.?AV?$VectorClass@PAVRadSiteClass@@@@`.
template class VectorClass<RadSiteClass*>;

// FUNCTION: GAMEMD 0x0065C200
// DynamicVectorClass<RadSiteClass*> -- slot 0 of retail vtable 0x007F07A4.
template class DynamicVectorClass<RadSiteClass*>;

// FUNCTION: GAMEMD 0x00664A70
// VectorClass<OwnerTalkClass::ConnectionListStruct*> -- reseats retail vtable 0x007F0C4C; locator 0x00808A00 -> type descriptor 0x008399F8
//   `.?AV?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@`.
template class VectorClass<OwnerTalkClass::ConnectionListStruct*>;

// FUNCTION: GAMEMD 0x00664AC0
// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*> -- slot 0 of retail vtable 0x007F0C2C.
template class DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*>;

// FUNCTION: GAMEMD 0x0069C6C0
// TypeList<DiskID> -- slot 0 of retail vtable 0x007F12D4 (RTTI `.?AV?$TypeList@W4DiskID@@@@`); it inlines the
//   VectorClass<DiskID> base destructor, so its body is the same 0x49 bytes as 0x69D460.
template class TypeList<DiskID>;

// FUNCTION: GAMEMD 0x0069D460
// VectorClass<DiskID> -- reseats retail vtable 0x007F1274; locator 0x00809270 -> type descriptor 0x0083F530
//   `.?AV?$VectorClass@W4DiskID@@@@`.
template class VectorClass<DiskID>;

// FUNCTION: GAMEMD 0x0069D590
// VectorClass<MultiMission*> -- reseats retail vtable 0x007F1214; locator 0x008091F8 -> type descriptor 0x0083EDD0
//   `.?AV?$VectorClass@PAVMultiMission@@@@`.
template class VectorClass<MultiMission*>;

// FUNCTION: GAMEMD 0x0069D5E0
// DynamicVectorClass<MultiMission*> -- slot 0 of retail vtable 0x007F11F4.
template class DynamicVectorClass<MultiMission*>;

// FUNCTION: GAMEMD 0x0069D6D0
// VectorClass<PhoneEntryClass*> -- reseats retail vtable 0x007F1254; locator 0x008091C8 -> type descriptor 0x0083ED60
//   `.?AV?$VectorClass@PAVPhoneEntryClass@@@@`.
template class VectorClass<PhoneEntryClass*>;

// FUNCTION: GAMEMD 0x0069D720
// DynamicVectorClass<PhoneEntryClass*> -- slot 0 of retail vtable 0x007F11B4.
template class DynamicVectorClass<PhoneEntryClass*>;

// FUNCTION: GAMEMD 0x006B1930
// VectorClass<SlaveManagerClass::SlaveControl*> -- reseats retail vtable 0x007F324C; locator 0x00809798 -> type descriptor 0x0083FD30
//   `.?AV?$VectorClass@PAUSlaveControl@SlaveManagerClass@@@@`.
template class VectorClass<SlaveManagerClass::SlaveControl*>;

// FUNCTION: GAMEMD 0x006B1980
// DynamicVectorClass<SlaveManagerClass::SlaveControl*> -- slot 0 of retail vtable 0x007F322C.
template class DynamicVectorClass<SlaveManagerClass::SlaveControl*>;

// FUNCTION: GAMEMD 0x006B19D0
// VectorClass<SlaveManagerClass*> -- reseats retail vtable 0x007F317C; locator 0x00809650 -> type descriptor 0x0083FC98
//   `.?AV?$VectorClass@PAVSlaveManagerClass@@@@`.
template class VectorClass<SlaveManagerClass*>;

// FUNCTION: GAMEMD 0x006B1A20
// DynamicVectorClass<SlaveManagerClass*> -- slot 0 of retail vtable 0x007F315C.
template class DynamicVectorClass<SlaveManagerClass*>;

// FUNCTION: GAMEMD 0x006B47A0
// VectorClass<UndoInfoStruct> -- reseats retail vtable 0x007F329C; locator 0x00809830 -> type descriptor 0x0083FF70
//   `.?AV?$VectorClass@UUndoInfoStruct@@@@`.
template class VectorClass<UndoInfoStruct>;

// FUNCTION: GAMEMD 0x006B47F0
// DynamicVectorClass<UndoInfoStruct> -- slot 0 of retail vtable 0x007F327C.
template class DynamicVectorClass<UndoInfoStruct>;

// FUNCTION: GAMEMD 0x006B8740
// VectorClass<SpawnManagerClass::SpawnControl*> -- reseats retail vtable 0x007F36D4; locator 0x00809B80 -> type descriptor 0x00840140
//   `.?AV?$VectorClass@PAUSpawnControl@SpawnManagerClass@@@@`.
template class VectorClass<SpawnManagerClass::SpawnControl*>;

// FUNCTION: GAMEMD 0x006B8790
// DynamicVectorClass<SpawnManagerClass::SpawnControl*> -- slot 0 of retail vtable 0x007F36B4.
template class DynamicVectorClass<SpawnManagerClass::SpawnControl*>;

// FUNCTION: GAMEMD 0x006B87E0
// VectorClass<SpawnManagerClass*> -- reseats retail vtable 0x007F3604; locator 0x00809A38 -> type descriptor 0x008400A8
//   `.?AV?$VectorClass@PAVSpawnManagerClass@@@@`.
template class VectorClass<SpawnManagerClass*>;

// FUNCTION: GAMEMD 0x006B8830
// DynamicVectorClass<SpawnManagerClass*> -- slot 0 of retail vtable 0x007F35E4.
template class DynamicVectorClass<SpawnManagerClass*>;

// FUNCTION: GAMEMD 0x006C6480
// VectorClass<unsigned long> -- reseats retail vtable 0x007F3748; locator 0x00809C18 -> type descriptor 0x00840A88
//   `.?AV?$VectorClass@K@@`.
template class VectorClass<unsigned long>;

// FUNCTION: GAMEMD 0x006C64D0
// DynamicVectorClass<unsigned long> -- slot 0 of retail vtable 0x007F3728.
template class DynamicVectorClass<unsigned long>;

// FUNCTION: GAMEMD 0x006DCC30
// VectorClass<DirtyAreaStruct> -- reseats retail vtable 0x007F42BC; locator 0x0080B860 -> type descriptor 0x00842958
//   `.?AV?$VectorClass@UDirtyAreaStruct@@@@`.
template class VectorClass<DirtyAreaStruct>;

// FUNCTION: GAMEMD 0x006DCC80
// DynamicVectorClass<DirtyAreaStruct> -- slot 0 of retail vtable 0x007F429C.
template class DynamicVectorClass<DirtyAreaStruct>;

// FUNCTION: GAMEMD 0x0074BFA0
// VectorClass<unsigned char> -- reseats retail vtable 0x007F65F4; locator 0x0080CEF8 -> type descriptor 0x00845F28
//   `.?AV?$VectorClass@E@@`.
template class VectorClass<unsigned char>;

// FUNCTION: GAMEMD 0x0076A770
// VectorClass<WorldDominationTour::Centroid> -- reseats retail vtable 0x007F71E0; locator 0x0080E008 -> type descriptor 0x00848B88
//   `.?AV?$VectorClass@VCentroid@WorldDominationTour@@@@`.
template class VectorClass<WorldDominationTour::Centroid>;

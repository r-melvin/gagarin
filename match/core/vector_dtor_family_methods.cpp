// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 71 base-template instantiations reproduce 135 remaining retail destructor
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
enum DiskID { DiskID_placeholder };
class DiskLaserClass;
template<class T0> class DynamicVectorClass;
class EBolt;
class EMPulseClass;
class EgoClass;
class EventClass;
class FactoryClass;
class FileEntryClass;
class FoggedObjectClass
{
public:
    struct DrawRecord;
};
class FootClass;
struct GlobalPacketType;
class GraphicMenuItem;
class HSVClass;
struct HWND__;
template<class T0, class T1> struct HashObject;
class HashString;
class HouseClass
{
public:
    struct BuildChoiceClass;
    struct StartingTechnoStruct;
};
class HouseTypeClass;
struct IConnectionPoint;
class InfantryTypeClass;
class IonBlastClass;
class IsometricTileTypeClass
{
public:
    struct TileInsertType;
};
struct KamikazeControl;
class LaserDrawClass;
class LightSourceClass
{
public:
    class PendingCellClass;
};
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
class OwnerTalkClass
{
public:
    struct ConnectionListStruct;
};
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
class RGBClass;
class RadBeam;
class RadSiteClass;
struct RadarTrackingStruct;
class SchemeNode;
struct ScoutStruct;
class ScriptTypeClass;
class ShadowControlClass;
class SideClass;
class SlaveManagerClass
{
public:
    struct SlaveControl;
};
class SmudgeClass;
class SmudgeTypeClass;
class SpawnManagerClass
{
public:
    struct SpawnControl;
};
class SpotLightClass;
class SubTitle;
struct SubzoneConnectionStruct;
class SuperClass;
class SuperWeaponTypeClass;
class SwizzlePointerClass;
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
class WinsockInterfaceClass
{
public:
    struct WinsockBufferType;
};
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

// FUNCTION: GAMEMD 0x00477AC0
// FUNCTION: GAMEMD 0x004786D0
// FUNCTION: GAMEMD 0x00645B10
// VectorClass<RGBClass> -- reseats retail vtable 0x007E4E38; locator 0x007FCF90 -> type descriptor 0x0081C198
//   `.?AV?$VectorClass@VRGBClass@@@@`.
template class VectorClass<RGBClass>;

// FUNCTION: GAMEMD 0x00488030
// FUNCTION: GAMEMD 0x004AEB50
// VectorClass<ObjectClass*> -- reseats retail vtable 0x007E192C; locator 0x007FA9A0 -> type descriptor 0x00816AA8
//   `.?AV?$VectorClass@PAVObjectClass@@@@`.
template class VectorClass<ObjectClass*>;

// Nested char-vector instantiation moved to vector_nested_char_methods.cpp.

// FUNCTION: GAMEMD 0x0049FCE0
// VectorClass<int> -- reseats retail vtable 0x007E4DB8; locator 0x007FCDB0 -> type descriptor 0x0081C038
//   `.?AV?$VectorClass@H@@`.
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

// FUNCTION: GAMEMD 0x004A0E10
// FUNCTION: GAMEMD 0x004A14A0
// VectorClass<tagCONNECTDATA> -- reseats retail vtable 0x007E5C84; locator 0x007FF6D8 -> type descriptor 0x0081F5F8
//   `.?AV?$VectorClass@UtagCONNECTDATA@@@@`.
template class VectorClass<tagCONNECTDATA>;

// FUNCTION: GAMEMD 0x004D2D10
// FUNCTION: GAMEMD 0x004D2D60
// VectorClass<FoggedObjectClass::DrawRecord> -- reseats retail vtable 0x007E8BC0; locator 0x00800800 -> type descriptor 0x00822458
//   `.?AV?$VectorClass@UDrawRecord@FoggedObjectClass@@@@`.
template class VectorClass<FoggedObjectClass::DrawRecord>;

// FUNCTION: GAMEMD 0x004EF620
// FUNCTION: GAMEMD 0x004EF670
// VectorClass<SuperClass*> -- reseats retail vtable 0x007EA504; locator 0x008022B8 -> type descriptor 0x00823DF8
//   `.?AV?$VectorClass@PAVSuperClass@@@@`.
template class VectorClass<SuperClass*>;


// FUNCTION: GAMEMD 0x004EF940
// FUNCTION: GAMEMD 0x007213E0
// VectorClass<ThemeControl*> -- reseats retail vtable 0x007EA584; locator 0x00802448 -> type descriptor 0x00823F40
//   `.?AV?$VectorClass@PAUThemeControl@@@@`.
template class VectorClass<ThemeControl*>;

// FUNCTION: GAMEMD 0x004EFAD0
// FUNCTION: GAMEMD 0x004EFB20
// VectorClass<TubeClass*> -- reseats retail vtable 0x007E9CC4; locator 0x00800F20 -> type descriptor 0x00822FD0
//   `.?AV?$VectorClass@PAVTubeClass@@@@`.
template class VectorClass<TubeClass*>;

// FUNCTION: GAMEMD 0x004EFD50
// FUNCTION: GAMEMD 0x004EFDA0
// VectorClass<SmudgeClass*> -- reseats retail vtable 0x007E9DC4; locator 0x00801180 -> type descriptor 0x00823170
//   `.?AV?$VectorClass@PAVSmudgeClass@@@@`.
template class VectorClass<SmudgeClass*>;

// FUNCTION: GAMEMD 0x004F0250
// FUNCTION: GAMEMD 0x004F02A0
// VectorClass<SideClass*> -- reseats retail vtable 0x007EA044; locator 0x00801770 -> type descriptor 0x00823580
//   `.?AV?$VectorClass@PAVSideClass@@@@`.
template class VectorClass<SideClass*>;

// FUNCTION: GAMEMD 0x004F0390
// FUNCTION: GAMEMD 0x004F03E0
// VectorClass<TaskForceClass*> -- reseats retail vtable 0x007EA0C4; locator 0x008018A0 -> type descriptor 0x00823650
//   `.?AV?$VectorClass@PAVTaskForceClass@@@@`.
template class VectorClass<TaskForceClass*>;

// FUNCTION: GAMEMD 0x004F0BB0
// FUNCTION: GAMEMD 0x004F0C00
// VectorClass<IsometricTileTypeClass*> -- reseats retail vtable 0x007EA404; locator 0x00802058 -> type descriptor 0x00823C10
//   `.?AV?$VectorClass@PAVIsometricTileTypeClass@@@@`.
template class VectorClass<IsometricTileTypeClass*>;

// FUNCTION: GAMEMD 0x004F0C50
// FUNCTION: GAMEMD 0x004F0CA0
// VectorClass<ParticleTypeClass*> -- reseats retail vtable 0x007EA444; locator 0x008020F0 -> type descriptor 0x00823C88
//   `.?AV?$VectorClass@PAVParticleTypeClass@@@@`.
template class VectorClass<ParticleTypeClass*>;

// FUNCTION: GAMEMD 0x00510130
// FUNCTION: GAMEMD 0x00510180
// VectorClass<AngerStruct> -- reseats retail vtable 0x007EA984; locator 0x00802BC0 -> type descriptor 0x00824588
//   `.?AV?$VectorClass@UAngerStruct@@@@`.
template class VectorClass<AngerStruct>;

// FUNCTION: GAMEMD 0x005101D0
// FUNCTION: GAMEMD 0x00510220
// VectorClass<ScoutStruct> -- reseats retail vtable 0x007EA9A4; locator 0x00802B90 -> type descriptor 0x00824520
//   `.?AV?$VectorClass@UScoutStruct@@@@`.
template class VectorClass<ScoutStruct>;

// FUNCTION: GAMEMD 0x00510270
// FUNCTION: GAMEMD 0x005102C0
// VectorClass<HouseClass::BuildChoiceClass*> -- reseats retail vtable 0x007EA7D4; locator 0x00802888 -> type descriptor 0x00824418
//   `.?AV?$VectorClass@PAUBuildChoiceClass@HouseClass@@@@`.
template class VectorClass<HouseClass::BuildChoiceClass*>;

// FUNCTION: GAMEMD 0x00510360
// FUNCTION: GAMEMD 0x005103B0
// VectorClass<bool> -- reseats retail vtable 0x007EAA5C; locator 0x00802D68 -> type descriptor 0x00824E70
//   `.?AV?$VectorClass@_N@@`.
template class VectorClass<bool>;

// FUNCTION: GAMEMD 0x0054A710
// FUNCTION: GAMEMD 0x0054A760
// VectorClass<unsigned short*> -- reseats retail vtable 0x007ECD0C; locator 0x00804C58 -> type descriptor 0x008290F0
//   `.?AV?$VectorClass@PAG@@`.
template class VectorClass<unsigned short*>;

// FUNCTION: GAMEMD 0x0054A7B0
// FUNCTION: GAMEMD 0x0054A800
// VectorClass<IsometricTileTypeClass::TileInsertType*> -- reseats retail vtable 0x007ECBFC; locator 0x00804B08 -> type descriptor 0x00829030
//   `.?AV?$VectorClass@PAUTileInsertType@IsometricTileTypeClass@@@@`.
template class VectorClass<IsometricTileTypeClass::TileInsertType*>;


// FUNCTION: GAMEMD 0x00555820
// FUNCTION: GAMEMD 0x00555870
// VectorClass<LightSourceClass::PendingCellClass*> -- reseats retail vtable 0x007ECFDC; locator 0x00805040 -> type descriptor 0x00829B68
//   `.?AV?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@`.
template class VectorClass<LightSourceClass::PendingCellClass*>;

// FUNCTION: GAMEMD 0x00557170
// FUNCTION: GAMEMD 0x005571C0
// VectorClass<LineTrail*> -- reseats retail vtable 0x007ED0EC; locator 0x008051D8 -> type descriptor 0x00829D48
//   `.?AV?$VectorClass@PAVLineTrail@@@@`.
template class VectorClass<LineTrail*>;

// FUNCTION: GAMEMD 0x00589060
// FUNCTION: GAMEMD 0x005AD570
// VectorClass<CellClass*> -- reseats retail vtable 0x007ED480; locator 0x008055E0 -> type descriptor 0x0082AB78
//   `.?AV?$VectorClass@PAVCellClass@@@@`.
template class VectorClass<CellClass*>;

// FUNCTION: GAMEMD 0x005890B0
// VectorClass<SubzoneConnectionStruct> -- reseats retail vtable 0x007E177C; locator 0x007FA5D8 -> type descriptor 0x00816848
//   `.?AV?$VectorClass@USubzoneConnectionStruct@@@@`.
template class VectorClass<SubzoneConnectionStruct>;

// FUNCTION: GAMEMD 0x0058A3D0
// FUNCTION: GAMEMD 0x0058A420
// VectorClass<ZoneConnectionClass> -- reseats retail vtable 0x007ED4E0; locator 0x00805610 -> type descriptor 0x0082AA88
//   `.?AV?$VectorClass@UZoneConnectionClass@@@@`.
template class VectorClass<ZoneConnectionClass>;

// FUNCTION: GAMEMD 0x0058AA90
// FUNCTION: GAMEMD 0x0058AAE0
// VectorClass<PassabilityType> -- reseats retail vtable 0x007ED560; locator 0x00805740 -> type descriptor 0x0082ACE0
//   `.?AV?$VectorClass@W4PassabilityType@@@@`.
template class VectorClass<PassabilityType>;

// FUNCTION: GAMEMD 0x0058AB30
// VectorClass<HashObject<unsigned int, unsigned int>> -- reseats retail vtable 0x007ED5C0; locator 0x00805828 -> type descriptor 0x0082ABA8
//   `.?AV?$VectorClass@U?$HashObject@II@@@@`.
template class VectorClass<HashObject<unsigned int, unsigned int> >;

// FUNCTION: GAMEMD 0x0058AB80
// VectorClass<HashObject<unsigned int, SubzoneConnectionStruct>> -- reseats retail vtable 0x007ED5E0; locator 0x00805858 -> type descriptor 0x0082AC10
//   `.?AV?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@`.
template class VectorClass<HashObject<unsigned int, SubzoneConnectionStruct> >;

// FUNCTION: GAMEMD 0x005AD4D0
// FUNCTION: GAMEMD 0x005AD520
// VectorClass<TRect<int>> -- reseats retail vtable 0x007ED970; locator 0x00805AC0 -> type descriptor 0x0082BFE0
//   `.?AV?$VectorClass@V?$TRect@H@@@@`.
template class VectorClass<TRect<int> >;

// FUNCTION: GAMEMD 0x005AD5C0
// FUNCTION: GAMEMD 0x005AD610
// VectorClass<double> -- reseats retail vtable 0x007EDA4C; locator 0x00805B40 -> type descriptor 0x0082C048
//   `.?AV?$VectorClass@N@@`.
template class VectorClass<double>;

// FUNCTION: GAMEMD 0x005D16C0
// FUNCTION: GAMEMD 0x005D1710
// VectorClass<Point2D> -- reseats retail vtable 0x007EEB74; locator 0x00806B88 -> type descriptor 0x00830380
//   `.?AV?$VectorClass@VPoint2D@@@@`.
template class VectorClass<Point2D>;


// FUNCTION: GAMEMD 0x005D18A0
// FUNCTION: GAMEMD 0x005D18F0
// VectorClass<MapStage*> -- reseats retail vtable 0x007EEAB4; locator 0x008069F0 -> type descriptor 0x00830200
//   `.?AV?$VectorClass@PAVMapStage@@@@`.
template class VectorClass<MapStage*>;

// MSAnimEntry vector specialization moved to vector_msanimentry_methods.cpp.

// FUNCTION: GAMEMD 0x005D19E0
// FUNCTION: GAMEMD 0x005D1A30
// VectorClass<MSSfxEntry*> -- reseats retail vtable 0x007EEAF4; locator 0x00806A20 -> type descriptor 0x00830268
//   `.?AV?$VectorClass@PAVMSSfxEntry@@@@`.
template class VectorClass<MSSfxEntry*>;

// FUNCTION: GAMEMD 0x005D2CA0
// FUNCTION: GAMEMD 0x005D2CF0
// VectorClass<MSAnim*> -- reseats retail vtable 0x007EEC24; locator 0x00806D48 -> type descriptor 0x00830558
//   `.?AV?$VectorClass@PAVMSAnim@@@@`.
template class VectorClass<MSAnim*>;

// FUNCTION: GAMEMD 0x005D2D40
// FUNCTION: GAMEMD 0x005D2D90
// VectorClass<MSSfx*> -- reseats retail vtable 0x007EEC44; locator 0x00806D18 -> type descriptor 0x00830500
//   `.?AV?$VectorClass@PAVMSSfx@@@@`.
template class VectorClass<MSSfx*>;

// FUNCTION: GAMEMD 0x005D5780
// FUNCTION: GAMEMD 0x005D57D0
// VectorClass<AcceleratorTracker> -- reseats retail vtable 0x007EECEC; locator 0x00806EC0 -> type descriptor 0x00830728
//   `.?AV?$VectorClass@UAcceleratorTracker@@@@`.
template class VectorClass<AcceleratorTracker>;

// FUNCTION: GAMEMD 0x005D8810
// FUNCTION: GAMEMD 0x005D8860
// VectorClass<MultiplayerTeam*> -- reseats retail vtable 0x007EEE54; locator 0x00807020 -> type descriptor 0x00830830
//   `.?AV?$VectorClass@PAVMultiplayerTeam@@@@`.
template class VectorClass<MultiplayerTeam*>;

// FUNCTION: GAMEMD 0x005D88B0
// FUNCTION: GAMEMD 0x005D8900
// VectorClass<MultiplayerGameMode*> -- reseats retail vtable 0x007EED40; locator 0x00806F58 -> type descriptor 0x008307B8
//   `.?AV?$VectorClass@PAVMultiplayerGameMode@@@@`.
template class VectorClass<MultiplayerGameMode*>;

// FUNCTION: GAMEMD 0x005F9DE0
// FUNCTION: GAMEMD 0x005F9E30
// VectorClass<ObjectTypeClass*> -- reseats retail vtable 0x007EF28C; locator 0x008074E0 -> type descriptor 0x00832A10
//   `.?AV?$VectorClass@PAVObjectTypeClass@@@@`.
template class VectorClass<ObjectTypeClass*>;

// FUNCTION: GAMEMD 0x00628760
// FUNCTION: GAMEMD 0x006287B0
// VectorClass<HSVClass> -- reseats retail vtable 0x007EF7F0; locator 0x008079E8 -> type descriptor 0x00836478
//   `.?AV?$VectorClass@VHSVClass@@@@`.
template class VectorClass<HSVClass>;

// FUNCTION: GAMEMD 0x00628E80
// VectorClass<HashObject<HashString, SchemeNode*>> -- reseats retail vtable 0x007EF7D0; locator 0x008079B8 -> type descriptor 0x008364D0
//   `.?AV?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@`.
template class VectorClass<HashObject<HashString, SchemeNode*> >;

// FUNCTION: GAMEMD 0x0062B330
// FUNCTION: GAMEMD 0x0062B380
// VectorClass<ParasiteClass*> -- reseats retail vtable 0x007EF844; locator 0x00807A80 -> type descriptor 0x008365D8
//   `.?AV?$VectorClass@PAVParasiteClass@@@@`.
template class VectorClass<ParasiteClass*>;

// FUNCTION: GAMEMD 0x0063EC50
// FUNCTION: GAMEMD 0x0063ECA0
// VectorClass<PlanningMemberClass*> -- reseats retail vtable 0x007EFF04; locator 0x008080A0 -> type descriptor 0x00836A60
//   `.?AV?$VectorClass@PAVPlanningMemberClass@@@@`.
template class VectorClass<PlanningMemberClass*>;

// FUNCTION: GAMEMD 0x0063ECF0
// FUNCTION: GAMEMD 0x0063ED40
// VectorClass<PlanningBranchClass*> -- reseats retail vtable 0x007EFF24; locator 0x008080D0 -> type descriptor 0x008369E8
//   `.?AV?$VectorClass@PAVPlanningBranchClass@@@@`.
template class VectorClass<PlanningBranchClass*>;

// FUNCTION: GAMEMD 0x0063ED90
// FUNCTION: GAMEMD 0x0063EDE0
// VectorClass<PlanningNodeClass*> -- reseats retail vtable 0x007EFE64; locator 0x00807F08 -> type descriptor 0x008368F8
//   `.?AV?$VectorClass@PAVPlanningNodeClass@@@@`.
template class VectorClass<PlanningNodeClass*>;

// FUNCTION: GAMEMD 0x0063EED0
// FUNCTION: GAMEMD 0x0063EF20
// VectorClass<PlanningTokenClass*> -- reseats retail vtable 0x007EFEA4; locator 0x00807FA0 -> type descriptor 0x00836970
//   `.?AV?$VectorClass@PAVPlanningTokenClass@@@@`.
template class VectorClass<PlanningTokenClass*>;

// FUNCTION: GAMEMD 0x00658D10
// VectorClass<HashObject<RadarTrackingStruct, TechnoClass*>> -- reseats retail vtable 0x007F044C; locator 0x008083F0 -> type descriptor 0x008393E0
//   `.?AV?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@`.
template class VectorClass<HashObject<RadarTrackingStruct, TechnoClass*> >;

// FUNCTION: GAMEMD 0x0065C1B0
// FUNCTION: GAMEMD 0x0065C200
// VectorClass<RadSiteClass*> -- reseats retail vtable 0x007F07C4; locator 0x00808628 -> type descriptor 0x00839598
//   `.?AV?$VectorClass@PAVRadSiteClass@@@@`.
template class VectorClass<RadSiteClass*>;

// FUNCTION: GAMEMD 0x00664A70
// FUNCTION: GAMEMD 0x00664AC0
// VectorClass<OwnerTalkClass::ConnectionListStruct*> -- reseats retail vtable 0x007F0C4C; locator 0x00808A00 -> type descriptor 0x008399F8
//   `.?AV?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@`.
template class VectorClass<OwnerTalkClass::ConnectionListStruct*>;

// FUNCTION: GAMEMD 0x0069C6C0
// FUNCTION: GAMEMD 0x0069D460
// VectorClass<DiskID> -- reseats retail vtable 0x007F1274; locator 0x00809270 -> type descriptor 0x0083F530
//   `.?AV?$VectorClass@W4DiskID@@@@`.
template class VectorClass<DiskID>;

// FUNCTION: GAMEMD 0x0069D590
// FUNCTION: GAMEMD 0x0069D5E0
// VectorClass<MultiMission*> -- reseats retail vtable 0x007F1214; locator 0x008091F8 -> type descriptor 0x0083EDD0
//   `.?AV?$VectorClass@PAVMultiMission@@@@`.
template class VectorClass<MultiMission*>;

// FUNCTION: GAMEMD 0x0069D6D0
// FUNCTION: GAMEMD 0x0069D720
// VectorClass<PhoneEntryClass*> -- reseats retail vtable 0x007F1254; locator 0x008091C8 -> type descriptor 0x0083ED60
//   `.?AV?$VectorClass@PAVPhoneEntryClass@@@@`.
template class VectorClass<PhoneEntryClass*>;

// FUNCTION: GAMEMD 0x006B1930
// FUNCTION: GAMEMD 0x006B1980
// VectorClass<SlaveManagerClass::SlaveControl*> -- reseats retail vtable 0x007F324C; locator 0x00809798 -> type descriptor 0x0083FD30
//   `.?AV?$VectorClass@PAUSlaveControl@SlaveManagerClass@@@@`.
template class VectorClass<SlaveManagerClass::SlaveControl*>;

// FUNCTION: GAMEMD 0x006B19D0
// FUNCTION: GAMEMD 0x006B1A20
// VectorClass<SlaveManagerClass*> -- reseats retail vtable 0x007F317C; locator 0x00809650 -> type descriptor 0x0083FC98
//   `.?AV?$VectorClass@PAVSlaveManagerClass@@@@`.
template class VectorClass<SlaveManagerClass*>;

// FUNCTION: GAMEMD 0x006B47A0
// FUNCTION: GAMEMD 0x006B47F0
// VectorClass<UndoInfoStruct> -- reseats retail vtable 0x007F329C; locator 0x00809830 -> type descriptor 0x0083FF70
//   `.?AV?$VectorClass@UUndoInfoStruct@@@@`.
template class VectorClass<UndoInfoStruct>;

// FUNCTION: GAMEMD 0x006B8740
// FUNCTION: GAMEMD 0x006B8790
// VectorClass<SpawnManagerClass::SpawnControl*> -- reseats retail vtable 0x007F36D4; locator 0x00809B80 -> type descriptor 0x00840140
//   `.?AV?$VectorClass@PAUSpawnControl@SpawnManagerClass@@@@`.
template class VectorClass<SpawnManagerClass::SpawnControl*>;

// FUNCTION: GAMEMD 0x006B87E0
// FUNCTION: GAMEMD 0x006B8830
// VectorClass<SpawnManagerClass*> -- reseats retail vtable 0x007F3604; locator 0x00809A38 -> type descriptor 0x008400A8
//   `.?AV?$VectorClass@PAVSpawnManagerClass@@@@`.
template class VectorClass<SpawnManagerClass*>;

// FUNCTION: GAMEMD 0x006C6480
// FUNCTION: GAMEMD 0x006C64D0
// VectorClass<unsigned long> -- reseats retail vtable 0x007F3748; locator 0x00809C18 -> type descriptor 0x00840A88
//   `.?AV?$VectorClass@K@@`.
template class VectorClass<unsigned long>;

// FUNCTION: GAMEMD 0x006CF850
// FUNCTION: GAMEMD 0x006CF8A0
// VectorClass<SwizzlePointerClass> -- reseats retail vtable 0x007F4154; locator 0x0080B7C8 -> type descriptor 0x00842758
//   `.?AV?$VectorClass@VSwizzlePointerClass@@@@`.
template class VectorClass<SwizzlePointerClass>;

// FUNCTION: GAMEMD 0x006DCC30
// FUNCTION: GAMEMD 0x006DCC80
// VectorClass<DirtyAreaStruct> -- reseats retail vtable 0x007F42BC; locator 0x0080B860 -> type descriptor 0x00842958
//   `.?AV?$VectorClass@UDirtyAreaStruct@@@@`.
template class VectorClass<DirtyAreaStruct>;

// FUNCTION: GAMEMD 0x0074BFA0
// VectorClass<unsigned char> -- reseats retail vtable 0x007F65F4; locator 0x0080CEF8 -> type descriptor 0x00845F28
//   `.?AV?$VectorClass@E@@`.
template class VectorClass<unsigned char>;

// FUNCTION: GAMEMD 0x0076A770
// VectorClass<WorldDominationTour::Centroid> -- reseats retail vtable 0x007F71E0; locator 0x0080E008 -> type descriptor 0x00848B88
//   `.?AV?$VectorClass@VCentroid@WorldDominationTour@@@@`.
template class VectorClass<WorldDominationTour::Centroid>;

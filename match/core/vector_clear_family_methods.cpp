// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x477D20 and its 160
//   siblings.
//
//   The retail class identity and slot binding are confirmed from the binary:
//   each annotated body occupies slot 3 of the listed VectorClass<T> vtable.
//   Slot 3 is Clear, called on a live vector by retail (including the
//   ToolTipManager constructor at 0x724000); these bodies clear owned storage
//   and reset vector bookkeeping without reseating a vptr. The source template
//   is VectorClass<T>::Clear, and the element argument is recovered from RTTI.
//
//   The 161 remaining addresses are one-to-one with 161 distinct VectorClass<T> tables;
//   each table's complete object locator and body address were read from the
//   retail binary. No destructor identity is inferred from the byte pattern.
//
//   KNOWN LIMITATION -- these compiled template instantiations are grouped
//   here for per-function verification. The retail binary does not establish
//   their original translation-unit grouping or final linker placement.
//   This sweep file does not establish an integrated engine link order.
// The ToolTip pointer Clear is bound in tooltip_vector_methods.cpp.
#include "vector_class.h"

// ---------------------------------------------------------------------------
// The element types, declared exactly as their RTTI manglings require: a `V`
// tag becomes `class`, a `U` tag `struct`, a `W4` tag an enum, and a nested or
// scoped name gets its enclosing scope. None is defined -- the body only ever
// handles `T*`, so an incomplete type is all the template needs. A scope
// written `namespace` below could equally have been a class: MSVC mangles the
// two identically, so the binary cannot decide it.
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
class RadarEventClass;
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
class TeamClass;
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
// The instantiations, in ascending retail-address order.
// ---------------------------------------------------------------------------

// FUNCTION: GAMEMD 0x00477D20
// VectorClass<int> -- vtable 0x007E4DB8 slot 3; locator 0x007FCDB0 -> type descriptor 0x0081C038
//   `.?AV?$VectorClass@H@@`.
template class VectorClass<int>;

// Layout asserted on the first instantiation; every instantiation in this
// family has the same layout, because the only member whose type varies is a
// pointer. The assert has to follow an explicit instantiation: VC6 fails to
// re-parse the template body when offsetof is what first instantiates it, and
// it will not take a template-id as offsetof's first argument either, hence
// the typedef.
typedef VectorClass<int> GgPlainVectorRep;
GG_STATIC_ASSERT(offsetof(GgPlainVectorRep, Items)       == 0x4);
GG_STATIC_ASSERT(offsetof(GgPlainVectorRep, Capacity)    == 0x8);
GG_STATIC_ASSERT(offsetof(GgPlainVectorRep, IsAllocated) == 0xD);
GG_STATIC_ASSERT(sizeof(GgPlainVectorRep)                == 0x10);

// FUNCTION: GAMEMD 0x004780B0
// VectorClass<TechnoTypeClass*> -- vtable 0x007E4DF8 slot 3; locator 0x007FCE60 -> type descriptor 0x0081C0A0
//   `.?AV?$VectorClass@PAVTechnoTypeClass@@@@`.
template class VectorClass<TechnoTypeClass*>;

// FUNCTION: GAMEMD 0x00478440
// VectorClass<RGBClass> -- vtable 0x007E4E38 slot 3; locator 0x007FCF90 -> type descriptor 0x0081C198
//   `.?AV?$VectorClass@VRGBClass@@@@`.
template class VectorClass<RGBClass>;

// FUNCTION: GAMEMD 0x0048AE60
// VectorClass<DamageGroup*> -- vtable 0x007E5144 slot 3; locator 0x007FD1D8 -> type descriptor 0x0081D168
//   `.?AV?$VectorClass@PAUDamageGroup@@@@`.
template class VectorClass<DamageGroup*>;

// FUNCTION: GAMEMD 0x0049AF70
// VectorClass<ConvertClass*> -- vtable 0x007E5338 slot 3; locator 0x007FD3A0 -> type descriptor 0x0081DC30
//   `.?AV?$VectorClass@PAVConvertClass@@@@`.
template class VectorClass<ConvertClass*>;

// FUNCTION: GAMEMD 0x0049EC40
// VectorClass<DynamicVectorClass<char*>*> -- vtable 0x007E5C04 slot 3; locator 0x007FF5F8 -> type descriptor 0x0081F288
//   `.?AV?$VectorClass@PAV?$DynamicVectorClass@PAD@@@@`.
template class VectorClass<DynamicVectorClass<char*>*>;

// FUNCTION: GAMEMD 0x0049EF10
// VectorClass<char*> -- vtable 0x007E5C24 slot 3; locator 0x007FF628 -> type descriptor 0x0081F240
//   `.?AV?$VectorClass@PAD@@`.
template class VectorClass<char*>;

// FUNCTION: GAMEMD 0x004A10A0
// VectorClass<tagCONNECTDATA> -- vtable 0x007E5C84 slot 3; locator 0x007FF6D8 -> type descriptor 0x0081F5F8
//   `.?AV?$VectorClass@UtagCONNECTDATA@@@@`.
template class VectorClass<tagCONNECTDATA>;

// FUNCTION: GAMEMD 0x004A1330
// VectorClass<IConnectionPoint*> -- vtable 0x007E5D08 slot 3; locator 0x007FF840 -> type descriptor 0x0081F6F0
//   `.?AV?$VectorClass@PAUIConnectionPoint@@@@`.
template class VectorClass<IConnectionPoint*>;

// FUNCTION: GAMEMD 0x004A4C20
// VectorClass<_DDSURFACEDESC*> -- vtable 0x007E5DEC slot 3; locator 0x007FF9E8 -> type descriptor 0x0081FEA0
//   `.?AV?$VectorClass@PAU_DDSURFACEDESC@@@@`.
template class VectorClass<_DDSURFACEDESC*>;

// FUNCTION: GAMEMD 0x004A7E70
// VectorClass<DiskLaserClass*> -- vtable 0x007E5EFC slot 3; locator 0x007FFB40 -> type descriptor 0x0081FF28
//   `.?AV?$VectorClass@PAVDiskLaserClass@@@@`.
template class VectorClass<DiskLaserClass*>;

// FUNCTION: GAMEMD 0x004B9D90
// VectorClass<ButtonFadeEffect*> -- vtable 0x007E8500 slot 3; locator 0x008001A8 -> type descriptor 0x00820420
//   `.?AV?$VectorClass@PAUButtonFadeEffect@@@@`.
template class VectorClass<ButtonFadeEffect*>;

// FUNCTION: GAMEMD 0x004B9FF0
// VectorClass<CrossDissolveEffect*> -- vtable 0x007E8520 slot 3; locator 0x00800110 -> type descriptor 0x008203A8
//   `.?AV?$VectorClass@PAUCrossDissolveEffect@@@@`.
template class VectorClass<CrossDissolveEffect*>;

// FUNCTION: GAMEMD 0x004C2D90
// VectorClass<EBolt*> -- vtable 0x007E86AC slot 3; locator 0x008002F8 -> type descriptor 0x00820710
//   `.?AV?$VectorClass@PAVEBolt@@@@`.
template class VectorClass<EBolt*>;

// FUNCTION: GAMEMD 0x004C4AF0
// VectorClass<EgoClass*> -- vtable 0x007E86FC slot 3; locator 0x00800390 -> type descriptor 0x00820778
//   `.?AV?$VectorClass@PAVEgoClass@@@@`.
template class VectorClass<EgoClass*>;

// FUNCTION: GAMEMD 0x004C5CB0
// VectorClass<EMPulseClass*> -- vtable 0x007E875C slot 3; locator 0x00800428 -> type descriptor 0x00820868
//   `.?AV?$VectorClass@PAVEMPulseClass@@@@`.
template class VectorClass<EMPulseClass*>;

// FUNCTION: GAMEMD 0x004CA9E0
// VectorClass<const TechnoTypeClass*> -- vtable 0x007E8954 slot 3; locator 0x00800640 -> type descriptor 0x00822220
//   `.?AV?$VectorClass@PBVTechnoTypeClass@@@@`.
template class VectorClass<const TechnoTypeClass*>;

// FUNCTION: GAMEMD 0x004D2B20
// VectorClass<FoggedObjectClass::DrawRecord> -- vtable 0x007E8BC0 slot 3; locator 0x00800800 -> type descriptor 0x00822458
//   `.?AV?$VectorClass@UDrawRecord@FoggedObjectClass@@@@`.
template class VectorClass<FoggedObjectClass::DrawRecord>;

// FUNCTION: GAMEMD 0x004E0410
// VectorClass<AbstractClass*> -- vtable 0x007E920C slot 3; locator 0x008009E0 -> type descriptor 0x008225B8
//   `.?AV?$VectorClass@PAVAbstractClass@@@@`.
template class VectorClass<AbstractClass*>;

// FUNCTION: GAMEMD 0x004E0670
// VectorClass<FootClass*> -- vtable 0x007E8C48 slot 3; locator 0x00800898 -> type descriptor 0x00822550
//   `.?AV?$VectorClass@PAVFootClass@@@@`.
template class VectorClass<FootClass*>;

// FUNCTION: GAMEMD 0x004E92F0
// VectorClass<TagClass*> -- vtable 0x007EA5C4 slot 3; locator 0x008024E0 -> type descriptor 0x00823F70
//   `.?AV?$VectorClass@PAVTagClass@@@@`.
template class VectorClass<TagClass*>;

// FUNCTION: GAMEMD 0x004E9550
// VectorClass<BuildingClass*> -- vtable 0x007E9E44 slot 3; locator 0x008012B0 -> type descriptor 0x00823240
//   `.?AV?$VectorClass@PAVBuildingClass@@@@`.
template class VectorClass<BuildingClass*>;

// FUNCTION: GAMEMD 0x004E97B0
// VectorClass<SuperClass*> -- vtable 0x007EA504 slot 3; locator 0x008022B8 -> type descriptor 0x00823DF8
//   `.?AV?$VectorClass@PAVSuperClass@@@@`.
template class VectorClass<SuperClass*>;

// FUNCTION: GAMEMD 0x004E9A10
// VectorClass<AITriggerTypeClass*> -- vtable 0x007E9B84 slot 3; locator 0x00800C28 -> type descriptor 0x00822D88
//   `.?AV?$VectorClass@PAVAITriggerTypeClass@@@@`.
template class VectorClass<AITriggerTypeClass*>;

// FUNCTION: GAMEMD 0x004E9C70
// VectorClass<BuildingLightClass*> -- vtable 0x007E9C44 slot 3; locator 0x00800DF0 -> type descriptor 0x00822EE0
//   `.?AV?$VectorClass@PAVBuildingLightClass@@@@`.
template class VectorClass<BuildingLightClass*>;

// FUNCTION: GAMEMD 0x004E9ED0
// VectorClass<ParticleClass*> -- vtable 0x007E9D84 slot 3; locator 0x008010E8 -> type descriptor 0x00823108
//   `.?AV?$VectorClass@PAVParticleClass@@@@`.
template class VectorClass<ParticleClass*>;

// FUNCTION: GAMEMD 0x004EA130
// VectorClass<TeamClass*> -- vtable 0x007E9F84 slot 3; locator 0x008015A8 -> type descriptor 0x00823448
//   `.?AV?$VectorClass@PAVTeamClass@@@@`.
template class VectorClass<TeamClass*>;

// FUNCTION: GAMEMD 0x004EA390
// VectorClass<ThemeControl*> -- vtable 0x007EA584 slot 3; locator 0x00802448 -> type descriptor 0x00823F40
//   `.?AV?$VectorClass@PAUThemeControl@@@@`.
template class VectorClass<ThemeControl*>;

// FUNCTION: GAMEMD 0x004EA510
// VectorClass<TriggerClass*> -- vtable 0x007E9C04 slot 3; locator 0x00800D58 -> type descriptor 0x00822E78
//   `.?AV?$VectorClass@PAVTriggerClass@@@@`.
template class VectorClass<TriggerClass*>;

// FUNCTION: GAMEMD 0x004EA770
// VectorClass<TriggerTypeClass*> -- vtable 0x007E9BC4 slot 3; locator 0x00800CC0 -> type descriptor 0x00822E00
//   `.?AV?$VectorClass@PAVTriggerTypeClass@@@@`.
template class VectorClass<TriggerTypeClass*>;

// FUNCTION: GAMEMD 0x004EA9D0
// VectorClass<TubeClass*> -- vtable 0x007E9CC4 slot 3; locator 0x00800F20 -> type descriptor 0x00822FD0
//   `.?AV?$VectorClass@PAVTubeClass@@@@`.
template class VectorClass<TubeClass*>;

// FUNCTION: GAMEMD 0x004EAC30
// VectorClass<ParticleSystemClass*> -- vtable 0x007E9C84 slot 3; locator 0x00800E88 -> type descriptor 0x00822F58
//   `.?AV?$VectorClass@PAVParticleSystemClass@@@@`.
template class VectorClass<ParticleSystemClass*>;

// FUNCTION: GAMEMD 0x004EAE90
// VectorClass<WaveClass*> -- vtable 0x007E9D04 slot 3; locator 0x00800FB8 -> type descriptor 0x00823038
//   `.?AV?$VectorClass@PAVWaveClass@@@@`.
template class VectorClass<WaveClass*>;

// FUNCTION: GAMEMD 0x004EB0F0
// VectorClass<OverlayClass*> -- vtable 0x007E9D44 slot 3; locator 0x00801050 -> type descriptor 0x008230A0
//   `.?AV?$VectorClass@PAVOverlayClass@@@@`.
template class VectorClass<OverlayClass*>;

// FUNCTION: GAMEMD 0x004EB350
// VectorClass<SmudgeClass*> -- vtable 0x007E9DC4 slot 3; locator 0x00801180 -> type descriptor 0x00823170
//   `.?AV?$VectorClass@PAVSmudgeClass@@@@`.
template class VectorClass<SmudgeClass*>;

// FUNCTION: GAMEMD 0x004EB5B0
// VectorClass<TerrainClass*> -- vtable 0x007E9E04 slot 3; locator 0x00801218 -> type descriptor 0x008231D8
//   `.?AV?$VectorClass@PAVTerrainClass@@@@`.
template class VectorClass<TerrainClass*>;

// FUNCTION: GAMEMD 0x004EB810
// VectorClass<AircraftClass*> -- vtable 0x007E9E84 slot 3; locator 0x00801348 -> type descriptor 0x008232A8
//   `.?AV?$VectorClass@PAVAircraftClass@@@@`.
template class VectorClass<AircraftClass*>;

// FUNCTION: GAMEMD 0x004EBA70
// VectorClass<UnitClass*> -- vtable 0x007E9EC4 slot 3; locator 0x008013E0 -> type descriptor 0x00823310
//   `.?AV?$VectorClass@PAVUnitClass@@@@`.
template class VectorClass<UnitClass*>;

// FUNCTION: GAMEMD 0x004EBCD0
// VectorClass<HouseClass*> -- vtable 0x007E9F04 slot 3; locator 0x00801478 -> type descriptor 0x00823378
//   `.?AV?$VectorClass@PAVHouseClass@@@@`.
template class VectorClass<HouseClass*>;

// FUNCTION: GAMEMD 0x004EBF30
// VectorClass<AnimClass*> -- vtable 0x007E9F44 slot 3; locator 0x00801510 -> type descriptor 0x008233E0
//   `.?AV?$VectorClass@PAVAnimClass@@@@`.
template class VectorClass<AnimClass*>;

// FUNCTION: GAMEMD 0x004EC190
// VectorClass<FactoryClass*> -- vtable 0x007E9FC4 slot 3; locator 0x00801640 -> type descriptor 0x008234B0
//   `.?AV?$VectorClass@PAVFactoryClass@@@@`.
template class VectorClass<FactoryClass*>;

// FUNCTION: GAMEMD 0x004EC3F0
// VectorClass<CampaignClass*> -- vtable 0x007EA004 slot 3; locator 0x008016D8 -> type descriptor 0x00823518
//   `.?AV?$VectorClass@PAVCampaignClass@@@@`.
template class VectorClass<CampaignClass*>;

// FUNCTION: GAMEMD 0x004EC650
// VectorClass<SideClass*> -- vtable 0x007EA044 slot 3; locator 0x00801770 -> type descriptor 0x00823580
//   `.?AV?$VectorClass@PAVSideClass@@@@`.
template class VectorClass<SideClass*>;

// FUNCTION: GAMEMD 0x004EC8B0
// VectorClass<HouseTypeClass*> -- vtable 0x007EA084 slot 3; locator 0x00801808 -> type descriptor 0x008235E8
//   `.?AV?$VectorClass@PAVHouseTypeClass@@@@`.
template class VectorClass<HouseTypeClass*>;

// FUNCTION: GAMEMD 0x004ECB10
// VectorClass<TaskForceClass*> -- vtable 0x007EA0C4 slot 3; locator 0x008018A0 -> type descriptor 0x00823650
//   `.?AV?$VectorClass@PAVTaskForceClass@@@@`.
template class VectorClass<TaskForceClass*>;

// FUNCTION: GAMEMD 0x004ECD70
// VectorClass<TeamTypeClass*> -- vtable 0x007EA104 slot 3; locator 0x00801938 -> type descriptor 0x008236B8
//   `.?AV?$VectorClass@PAVTeamTypeClass@@@@`.
template class VectorClass<TeamTypeClass*>;

// FUNCTION: GAMEMD 0x004ECFD0
// VectorClass<ScriptTypeClass*> -- vtable 0x007EA144 slot 3; locator 0x008019D0 -> type descriptor 0x00823720
//   `.?AV?$VectorClass@PAVScriptTypeClass@@@@`.
template class VectorClass<ScriptTypeClass*>;

// FUNCTION: GAMEMD 0x004ED230
// VectorClass<OverlayTypeClass*> -- vtable 0x007EA184 slot 3; locator 0x00801A68 -> type descriptor 0x00823790
//   `.?AV?$VectorClass@PAVOverlayTypeClass@@@@`.
template class VectorClass<OverlayTypeClass*>;

// FUNCTION: GAMEMD 0x004ED490
// VectorClass<SmudgeTypeClass*> -- vtable 0x007EA1C4 slot 3; locator 0x00801B00 -> type descriptor 0x00823808
//   `.?AV?$VectorClass@PAVSmudgeTypeClass@@@@`.
template class VectorClass<SmudgeTypeClass*>;

// FUNCTION: GAMEMD 0x004ED6F0
// VectorClass<TerrainTypeClass*> -- vtable 0x007EA204 slot 3; locator 0x00801B98 -> type descriptor 0x00823878
//   `.?AV?$VectorClass@PAVTerrainTypeClass@@@@`.
template class VectorClass<TerrainTypeClass*>;

// FUNCTION: GAMEMD 0x004ED950
// VectorClass<BuildingTypeClass*> -- vtable 0x007EA244 slot 3; locator 0x00801C30 -> type descriptor 0x008238F0
//   `.?AV?$VectorClass@PAVBuildingTypeClass@@@@`.
template class VectorClass<BuildingTypeClass*>;

// FUNCTION: GAMEMD 0x004EDBB0
// VectorClass<AircraftTypeClass*> -- vtable 0x007EA284 slot 3; locator 0x00801CC8 -> type descriptor 0x00823968
//   `.?AV?$VectorClass@PAVAircraftTypeClass@@@@`.
template class VectorClass<AircraftTypeClass*>;

// FUNCTION: GAMEMD 0x004EDE10
// VectorClass<UnitTypeClass*> -- vtable 0x007EA2C4 slot 3; locator 0x00801D60 -> type descriptor 0x008239E0
//   `.?AV?$VectorClass@PAVUnitTypeClass@@@@`.
template class VectorClass<UnitTypeClass*>;

// FUNCTION: GAMEMD 0x004EE070
// VectorClass<AnimTypeClass*> -- vtable 0x007EA304 slot 3; locator 0x00801DF8 -> type descriptor 0x00823A48
//   `.?AV?$VectorClass@PAVAnimTypeClass@@@@`.
template class VectorClass<AnimTypeClass*>;

// FUNCTION: GAMEMD 0x004EE2D0
// VectorClass<InfantryTypeClass*> -- vtable 0x007EA344 slot 3; locator 0x00801E90 -> type descriptor 0x00823AB0
//   `.?AV?$VectorClass@PAVInfantryTypeClass@@@@`.
template class VectorClass<InfantryTypeClass*>;

// FUNCTION: GAMEMD 0x004EE530
// VectorClass<BulletTypeClass*> -- vtable 0x007EA384 slot 3; locator 0x00801F28 -> type descriptor 0x00823B28
//   `.?AV?$VectorClass@PAVBulletTypeClass@@@@`.
template class VectorClass<BulletTypeClass*>;

// FUNCTION: GAMEMD 0x004EE790
// VectorClass<VoxelAnimTypeClass*> -- vtable 0x007EA3C4 slot 3; locator 0x00801FC0 -> type descriptor 0x00823B98
//   `.?AV?$VectorClass@PAVVoxelAnimTypeClass@@@@`.
template class VectorClass<VoxelAnimTypeClass*>;

// FUNCTION: GAMEMD 0x004EE9F0
// VectorClass<IsometricTileTypeClass*> -- vtable 0x007EA404 slot 3; locator 0x00802058 -> type descriptor 0x00823C10
//   `.?AV?$VectorClass@PAVIsometricTileTypeClass@@@@`.
template class VectorClass<IsometricTileTypeClass*>;

// FUNCTION: GAMEMD 0x004EEC50
// VectorClass<ParticleTypeClass*> -- vtable 0x007EA444 slot 3; locator 0x008020F0 -> type descriptor 0x00823C88
//   `.?AV?$VectorClass@PAVParticleTypeClass@@@@`.
template class VectorClass<ParticleTypeClass*>;

// FUNCTION: GAMEMD 0x004EEEB0
// VectorClass<ParticleSystemTypeClass*> -- vtable 0x007EA484 slot 3; locator 0x00802188 -> type descriptor 0x00823D00
//   `.?AV?$VectorClass@PAVParticleSystemTypeClass@@@@`.
template class VectorClass<ParticleSystemTypeClass*>;

// FUNCTION: GAMEMD 0x004EF110
// VectorClass<SuperWeaponTypeClass*> -- vtable 0x007EA4C4 slot 3; locator 0x00802220 -> type descriptor 0x00823D80
//   `.?AV?$VectorClass@PAVSuperWeaponTypeClass@@@@`.
template class VectorClass<SuperWeaponTypeClass*>;

// FUNCTION: GAMEMD 0x004EF370
// VectorClass<AbstractTypeClass*> -- vtable 0x007EA544 slot 3; locator 0x00802350 -> type descriptor 0x00823E60
//   `.?AV?$VectorClass@PAVAbstractTypeClass@@@@`.
template class VectorClass<AbstractTypeClass*>;

// FUNCTION: GAMEMD 0x004F29D0
// VectorClass<GraphicMenuItem*> -- vtable 0x007EA624 slot 3; locator 0x00802638 -> type descriptor 0x00824100
//   `.?AV?$VectorClass@PAVGraphicMenuItem@@@@`.
template class VectorClass<GraphicMenuItem*>;

// FUNCTION: GAMEMD 0x0050EA00
// VectorClass<const BuildingTypeClass*> -- vtable 0x007EAA08 slot 3; locator 0x00802CD0 -> type descriptor 0x00824CD8
//   `.?AV?$VectorClass@PBVBuildingTypeClass@@@@`.
template class VectorClass<const BuildingTypeClass*>;

// FUNCTION: GAMEMD 0x0050ED10
// VectorClass<HouseClass::StartingTechnoStruct*> -- vtable 0x007EA964 slot 3; locator 0x00802BF0 -> type descriptor 0x008245F0
//   `.?AV?$VectorClass@PAUStartingTechnoStruct@HouseClass@@@@`.
template class VectorClass<HouseClass::StartingTechnoStruct*>;

// FUNCTION: GAMEMD 0x0050EFD0
// VectorClass<AngerStruct> -- vtable 0x007EA984 slot 3; locator 0x00802BC0 -> type descriptor 0x00824588
//   `.?AV?$VectorClass@UAngerStruct@@@@`.
template class VectorClass<AngerStruct>;

// FUNCTION: GAMEMD 0x0050F300
// VectorClass<ScoutStruct> -- vtable 0x007EA9A4 slot 3; locator 0x00802B90 -> type descriptor 0x00824520
//   `.?AV?$VectorClass@UScoutStruct@@@@`.
template class VectorClass<ScoutStruct>;

// FUNCTION: GAMEMD 0x0050F5D0
// VectorClass<HouseClass::BuildChoiceClass*> -- vtable 0x007EA7D4 slot 3; locator 0x00802888 -> type descriptor 0x00824418
//   `.?AV?$VectorClass@PAUBuildChoiceClass@HouseClass@@@@`.
template class VectorClass<HouseClass::BuildChoiceClass*>;

// FUNCTION: GAMEMD 0x0050F830
// VectorClass<const TeamTypeClass*> -- vtable 0x007EA9E4 slot 3; locator 0x00802C20 -> type descriptor 0x00824680
//   `.?AV?$VectorClass@PBVTeamTypeClass@@@@`.
template class VectorClass<const TeamTypeClass*>;

// FUNCTION: GAMEMD 0x0050FA90
// VectorClass<bool> -- vtable 0x007EAA5C slot 3; locator 0x00802D68 -> type descriptor 0x00824E70
//   `.?AV?$VectorClass@_N@@`.
template class VectorClass<bool>;

// FUNCTION: GAMEMD 0x00512D30
// VectorClass<const InfantryTypeClass*> -- vtable 0x007EAC28 slot 3; locator 0x00803168 -> type descriptor 0x008251C0
//   `.?AV?$VectorClass@PBVInfantryTypeClass@@@@`.
template class VectorClass<const InfantryTypeClass*>;

// FUNCTION: GAMEMD 0x00513100
// VectorClass<const UnitTypeClass*> -- vtable 0x007EAC48 slot 3; locator 0x00803108 -> type descriptor 0x00825128
//   `.?AV?$VectorClass@PBVUnitTypeClass@@@@`.
template class VectorClass<const UnitTypeClass*>;

// FUNCTION: GAMEMD 0x005134D0
// VectorClass<const AircraftTypeClass*> -- vtable 0x007EAC68 slot 3; locator 0x00803138 -> type descriptor 0x00825080
//   `.?AV?$VectorClass@PBVAircraftTypeClass@@@@`.
template class VectorClass<const AircraftTypeClass*>;

// FUNCTION: GAMEMD 0x005251C0
// VectorClass<const AnimTypeClass*> -- vtable 0x007EB6F4 slot 3; locator 0x00803528 -> type descriptor 0x00825818
//   `.?AV?$VectorClass@PBVAnimTypeClass@@@@`.
template class VectorClass<const AnimTypeClass*>;

// FUNCTION: GAMEMD 0x00538610
// VectorClass<CCINIClass*> -- vtable 0x007EB80C slot 3; locator 0x008037D8 -> type descriptor 0x008261B8
//   `.?AV?$VectorClass@PAVCCINIClass@@@@`.
template class VectorClass<CCINIClass*>;

// FUNCTION: GAMEMD 0x0053C610
// VectorClass<const AnimClass*> -- vtable 0x007EBFEC slot 3; locator 0x008047E8 -> type descriptor 0x00827FD0
//   `.?AV?$VectorClass@PBVAnimClass@@@@`.
template class VectorClass<const AnimClass*>;

// FUNCTION: GAMEMD 0x0053DB90
// VectorClass<IonBlastClass*> -- vtable 0x007EC07C slot 3; locator 0x00804880 -> type descriptor 0x008280D0
//   `.?AV?$VectorClass@PAVIonBlastClass@@@@`.
template class VectorClass<IonBlastClass*>;

// FUNCTION: GAMEMD 0x0054A340
// VectorClass<unsigned short*> -- vtable 0x007ECD0C slot 3; locator 0x00804C58 -> type descriptor 0x008290F0
//   `.?AV?$VectorClass@PAG@@`.
template class VectorClass<unsigned short*>;

// FUNCTION: GAMEMD 0x0054A5A0
// VectorClass<IsometricTileTypeClass::TileInsertType*> -- vtable 0x007ECBFC slot 3; locator 0x00804B08 -> type descriptor 0x00829030
//   `.?AV?$VectorClass@PAUTileInsertType@IsometricTileTypeClass@@@@`.
template class VectorClass<IsometricTileTypeClass::TileInsertType*>;

// FUNCTION: GAMEMD 0x0054E9E0
// VectorClass<KamikazeControl*> -- vtable 0x007ECE9C slot 3; locator 0x00804D88 -> type descriptor 0x00829670
//   `.?AV?$VectorClass@PAUKamikazeControl@@@@`.
template class VectorClass<KamikazeControl*>;

// FUNCTION: GAMEMD 0x00551420
// VectorClass<LaserDrawClass*> -- vtable 0x007ECEFC slot 3; locator 0x00804E20 -> type descriptor 0x008296E0
//   `.?AV?$VectorClass@PAVLaserDrawClass@@@@`.
template class VectorClass<LaserDrawClass*>;

// FUNCTION: GAMEMD 0x005553B0
// VectorClass<LightSourceClass*> -- vtable 0x007ECF9C slot 3; locator 0x00804FA8 -> type descriptor 0x00829AF0
//   `.?AV?$VectorClass@PAVLightSourceClass@@@@`.
template class VectorClass<LightSourceClass*>;

// FUNCTION: GAMEMD 0x00555610
// VectorClass<LightSourceClass::PendingCellClass*> -- vtable 0x007ECFDC slot 3; locator 0x00805040 -> type descriptor 0x00829B68
//   `.?AV?$VectorClass@PAVPendingCellClass@LightSourceClass@@@@`.
template class VectorClass<LightSourceClass::PendingCellClass*>;

// FUNCTION: GAMEMD 0x00557000
// VectorClass<LineTrail*> -- vtable 0x007ED0EC slot 3; locator 0x008051D8 -> type descriptor 0x00829D48
//   `.?AV?$VectorClass@PAVLineTrail@@@@`.
template class VectorClass<LineTrail*>;

// FUNCTION: GAMEMD 0x00558330
// VectorClass<const unsigned short*> -- vtable 0x007ED1FC slot 3; locator 0x008052B0 -> type descriptor 0x00829DB0
//   `.?AV?$VectorClass@PBG@@`.
template class VectorClass<const unsigned short*>;

// FUNCTION: GAMEMD 0x0055A2A0
// VectorClass<FileEntryClass*> -- vtable 0x007ED32C slot 3; locator 0x008053E8 -> type descriptor 0x00829E18
//   `.?AV?$VectorClass@PAVFileEntryClass@@@@`.
template class VectorClass<FileEntryClass*>;

// FUNCTION: GAMEMD 0x005894A0
// VectorClass<ZoneConnectionClass> -- vtable 0x007ED4E0 slot 3; locator 0x00805610 -> type descriptor 0x0082AA88
//   `.?AV?$VectorClass@UZoneConnectionClass@@@@`.
template class VectorClass<ZoneConnectionClass>;

// FUNCTION: GAMEMD 0x00589D90
// VectorClass<CellClass*> -- vtable 0x007ED480 slot 3; locator 0x008055E0 -> type descriptor 0x0082AB78
//   `.?AV?$VectorClass@PAVCellClass@@@@`.
template class VectorClass<CellClass*>;

// FUNCTION: GAMEMD 0x00589FA0
// VectorClass<PassabilityType> -- vtable 0x007ED560 slot 3; locator 0x00805740 -> type descriptor 0x0082ACE0
//   `.?AV?$VectorClass@W4PassabilityType@@@@`.
template class VectorClass<PassabilityType>;

// FUNCTION: GAMEMD 0x0058A7B0
// VectorClass<HashObject<unsigned int, unsigned int>> -- vtable 0x007ED5C0 slot 3; locator 0x00805828 -> type descriptor 0x0082ABA8
//   `.?AV?$VectorClass@U?$HashObject@II@@@@`.
template class VectorClass<HashObject<unsigned int, unsigned int> >;

// FUNCTION: GAMEMD 0x0058A9F0
// VectorClass<HashObject<unsigned int, SubzoneConnectionStruct>> -- vtable 0x007ED5E0 slot 3; locator 0x00805858 -> type descriptor 0x0082AC10
//   `.?AV?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@`.
template class VectorClass<HashObject<unsigned int, SubzoneConnectionStruct> >;

// FUNCTION: GAMEMD 0x005AC790
// VectorClass<MapRegionClass*> -- vtable 0x007ED878 slot 3; locator 0x008058F0 -> type descriptor 0x0082B998
//   `.?AV?$VectorClass@PAVMapRegionClass@@@@`.
template class VectorClass<MapRegionClass*>;

// FUNCTION: GAMEMD 0x005ACB50
// VectorClass<_WIN32_FIND_DATAA*> -- vtable 0x007ED92C slot 3; locator 0x008059C0 -> type descriptor 0x0082BA98
//   `.?AV?$VectorClass@PAU_WIN32_FIND_DATAA@@@@`.
template class VectorClass<_WIN32_FIND_DATAA*>;

// FUNCTION: GAMEMD 0x005ACE20
// VectorClass<TRect<int>> -- vtable 0x007ED970 slot 3; locator 0x00805AC0 -> type descriptor 0x0082BFE0
//   `.?AV?$VectorClass@V?$TRect@H@@@@`.
template class VectorClass<TRect<int> >;

// FUNCTION: GAMEMD 0x005AD1F0
// VectorClass<double> -- vtable 0x007EDA4C slot 3; locator 0x00805B40 -> type descriptor 0x0082C048
//   `.?AV?$VectorClass@N@@`.
template class VectorClass<double>;

// FUNCTION: GAMEMD 0x005C0BC0
// VectorClass<const char*> -- vtable 0x007EE0D4 slot 3; locator 0x00805F38 -> type descriptor 0x0082D9D8
//   `.?AV?$VectorClass@PBD@@`.
template class VectorClass<const char*>;

// FUNCTION: GAMEMD 0x005C5220
// VectorClass<MPlayerScoreType*> -- vtable 0x007EE3D0 slot 3; locator 0x008062A0 -> type descriptor 0x0082DF68
//   `.?AV?$VectorClass@PAUMPlayerScoreType@@@@`.
template class VectorClass<MPlayerScoreType*>;

// FUNCTION: GAMEMD 0x005C5480
// VectorClass<NodeNameType*> -- vtable 0x007EE390 slot 3; locator 0x00806270 -> type descriptor 0x0082DBB0
//   `.?AV?$VectorClass@PAUNodeNameType@@@@`.
template class VectorClass<NodeNameType*>;

// FUNCTION: GAMEMD 0x005C56E0
// VectorClass<CoopCampaignClass*> -- vtable 0x007EE3B0 slot 3; locator 0x00806240 -> type descriptor 0x0082DB38
//   `.?AV?$VectorClass@PAVCoopCampaignClass@@@@`.
template class VectorClass<CoopCampaignClass*>;

// FUNCTION: GAMEMD 0x005D0920
// VectorClass<Point2D> -- vtable 0x007EEB74 slot 3; locator 0x00806B88 -> type descriptor 0x00830380
//   `.?AV?$VectorClass@VPoint2D@@@@`.
template class VectorClass<Point2D>;

// FUNCTION: GAMEMD 0x005D0BD0
// VectorClass<MSTextEntry*> -- vtable 0x007EEB94 slot 3; locator 0x00806BE8 -> type descriptor 0x00830440
//   `.?AV?$VectorClass@PAVMSTextEntry@@@@`.
template class VectorClass<MSTextEntry*>;

// FUNCTION: GAMEMD 0x005D0E30
// VectorClass<MapSelection*> -- vtable 0x007EEBB4 slot 3; locator 0x00806BB8 -> type descriptor 0x008303D8
//   `.?AV?$VectorClass@PAVMapSelection@@@@`.
template class VectorClass<MapSelection*>;

// FUNCTION: GAMEMD 0x005D1090
// VectorClass<MapStage*> -- vtable 0x007EEAB4 slot 3; locator 0x008069F0 -> type descriptor 0x00830200
//   `.?AV?$VectorClass@PAVMapStage@@@@`.
template class VectorClass<MapStage*>;

// FUNCTION: GAMEMD 0x005D12F0
// VectorClass<MSAnimEntry*> -- vtable 0x007EEAD4 slot 3; locator 0x008069C0 -> type descriptor 0x00830198
//   `.?AV?$VectorClass@PAVMSAnimEntry@@@@`.
template class VectorClass<MSAnimEntry*>;

// FUNCTION: GAMEMD 0x005D1550
// VectorClass<MSSfxEntry*> -- vtable 0x007EEAF4 slot 3; locator 0x00806A20 -> type descriptor 0x00830268
//   `.?AV?$VectorClass@PAVMSSfxEntry@@@@`.
template class VectorClass<MSSfxEntry*>;

// FUNCTION: GAMEMD 0x005D28D0
// VectorClass<MSAnim*> -- vtable 0x007EEC24 slot 3; locator 0x00806D48 -> type descriptor 0x00830558
//   `.?AV?$VectorClass@PAVMSAnim@@@@`.
template class VectorClass<MSAnim*>;

// FUNCTION: GAMEMD 0x005D2B30
// VectorClass<MSSfx*> -- vtable 0x007EEC44 slot 3; locator 0x00806D18 -> type descriptor 0x00830500
//   `.?AV?$VectorClass@PAVMSSfx@@@@`.
template class VectorClass<MSSfx*>;

// FUNCTION: GAMEMD 0x005D5240
// VectorClass<HWND__*> -- vtable 0x007EECAC slot 3; locator 0x00806E28 -> type descriptor 0x008306D0
//   `.?AV?$VectorClass@PAUHWND__@@@@`.
template class VectorClass<HWND__*>;

// FUNCTION: GAMEMD 0x005D5500
// VectorClass<AcceleratorTracker> -- vtable 0x007EECEC slot 3; locator 0x00806EC0 -> type descriptor 0x00830728
//   `.?AV?$VectorClass@UAcceleratorTracker@@@@`.
template class VectorClass<AcceleratorTracker>;

// FUNCTION: GAMEMD 0x005D83E0
// VectorClass<MultiplayerTeam*> -- vtable 0x007EEE54 slot 3; locator 0x00807020 -> type descriptor 0x00830830
//   `.?AV?$VectorClass@PAVMultiplayerTeam@@@@`.
template class VectorClass<MultiplayerTeam*>;

// FUNCTION: GAMEMD 0x005D8640
// VectorClass<MultiplayerGameMode*> -- vtable 0x007EED40 slot 3; locator 0x00806F58 -> type descriptor 0x008307B8
//   `.?AV?$VectorClass@PAVMultiplayerGameMode@@@@`.
template class VectorClass<MultiplayerGameMode*>;

// FUNCTION: GAMEMD 0x005EED00
// VectorClass<const MultiMission*> -- vtable 0x007EEF50 slot 3; locator 0x00807310 -> type descriptor 0x00831A00
//   `.?AV?$VectorClass@PBVMultiMission@@@@`.
template class VectorClass<const MultiMission*>;

// FUNCTION: GAMEMD 0x005F9C70
// VectorClass<ObjectTypeClass*> -- vtable 0x007EF28C slot 3; locator 0x008074E0 -> type descriptor 0x00832A10
//   `.?AV?$VectorClass@PAVObjectTypeClass@@@@`.
template class VectorClass<ObjectTypeClass*>;

// FUNCTION: GAMEMD 0x00600110
// VectorClass<SpotLightClass*> -- vtable 0x007EF6DC slot 3; locator 0x00807788 -> type descriptor 0x008335E8
//   `.?AV?$VectorClass@PAVSpotLightClass@@@@`.
template class VectorClass<SpotLightClass*>;

// FUNCTION: GAMEMD 0x00627F00
// VectorClass<ColorScheme*> -- vtable 0x007EF7B0 slot 3; locator 0x00807920 -> type descriptor 0x00836570
//   `.?AV?$VectorClass@PAVColorScheme@@@@`.
template class VectorClass<ColorScheme*>;

// FUNCTION: GAMEMD 0x006283E0
// VectorClass<HSVClass> -- vtable 0x007EF7F0 slot 3; locator 0x008079E8 -> type descriptor 0x00836478
//   `.?AV?$VectorClass@VHSVClass@@@@`.
template class VectorClass<HSVClass>;

// FUNCTION: GAMEMD 0x00628A40
// VectorClass<HashObject<HashString, SchemeNode*>> -- vtable 0x007EF7D0 slot 3; locator 0x008079B8 -> type descriptor 0x008364D0
//   `.?AV?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@`.
template class VectorClass<HashObject<HashString, SchemeNode*> >;

// FUNCTION: GAMEMD 0x0062B1C0
// VectorClass<ParasiteClass*> -- vtable 0x007EF844 slot 3; locator 0x00807A80 -> type descriptor 0x008365D8
//   `.?AV?$VectorClass@PAVParasiteClass@@@@`.
template class VectorClass<ParasiteClass*>;

// FUNCTION: GAMEMD 0x0063DE30
// VectorClass<PlanningMemberClass*> -- vtable 0x007EFF04 slot 3; locator 0x008080A0 -> type descriptor 0x00836A60
//   `.?AV?$VectorClass@PAVPlanningMemberClass@@@@`.
template class VectorClass<PlanningMemberClass*>;

// FUNCTION: GAMEMD 0x0063E140
// VectorClass<PlanningBranchClass*> -- vtable 0x007EFF24 slot 3; locator 0x008080D0 -> type descriptor 0x008369E8
//   `.?AV?$VectorClass@PAVPlanningBranchClass@@@@`.
template class VectorClass<PlanningBranchClass*>;

// FUNCTION: GAMEMD 0x0063E400
// VectorClass<PlanningNodeClass*> -- vtable 0x007EFE64 slot 3; locator 0x00807F08 -> type descriptor 0x008368F8
//   `.?AV?$VectorClass@PAVPlanningNodeClass@@@@`.
template class VectorClass<PlanningNodeClass*>;

// FUNCTION: GAMEMD 0x0063E740
// VectorClass<EventClass*> -- vtable 0x007EFE24 slot 3; locator 0x00807E70 -> type descriptor 0x00836890
//   `.?AV?$VectorClass@PAVEventClass@@@@`.
template class VectorClass<EventClass*>;

// FUNCTION: GAMEMD 0x0063EA40
// VectorClass<PlanningTokenClass*> -- vtable 0x007EFEA4 slot 3; locator 0x00807FA0 -> type descriptor 0x00836970
//   `.?AV?$VectorClass@PAVPlanningTokenClass@@@@`.
template class VectorClass<PlanningTokenClass*>;

// FUNCTION: GAMEMD 0x00658A70
// VectorClass<HashObject<RadarTrackingStruct, TechnoClass*>> -- vtable 0x007F044C slot 3; locator 0x008083F0 -> type descriptor 0x008393E0
//   `.?AV?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@`.
template class VectorClass<HashObject<RadarTrackingStruct, TechnoClass*> >;

// FUNCTION: GAMEMD 0x0065A330
// VectorClass<RadBeam*> -- vtable 0x007F04A4 slot 3; locator 0x008084F0 -> type descriptor 0x00839538
//   `.?AV?$VectorClass@PAVRadBeam@@@@`.
template class VectorClass<RadBeam*>;

// FUNCTION: GAMEMD 0x0065C040
// VectorClass<RadSiteClass*> -- vtable 0x007F07C4 slot 3; locator 0x00808628 -> type descriptor 0x00839598
//   `.?AV?$VectorClass@PAVRadSiteClass@@@@`.
template class VectorClass<RadSiteClass*>;

// FUNCTION: GAMEMD 0x00660DD0
// VectorClass<RadarEventClass*> -- vtable 0x007F0ACC slot 3; locator 0x008088A0 -> type descriptor 0x00839920
//   `.?AV?$VectorClass@PAVRadarEventClass@@@@`.
template class VectorClass<RadarEventClass*>;

// FUNCTION: GAMEMD 0x00664900
// VectorClass<OwnerTalkClass::ConnectionListStruct*> -- vtable 0x007F0C4C slot 3; locator 0x00808A00 -> type descriptor 0x008399F8
//   `.?AV?$VectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@`.
template class VectorClass<OwnerTalkClass::ConnectionListStruct*>;

// FUNCTION: GAMEMD 0x0067ABE0
// VectorClass<const VoxelAnimTypeClass*> -- vtable 0x007F0D5C slot 3; locator 0x00808BE0 -> type descriptor 0x0083A010
//   `.?AV?$VectorClass@PBVVoxelAnimTypeClass@@@@`.
template class VectorClass<const VoxelAnimTypeClass*>;

// FUNCTION: GAMEMD 0x0067AF60
// VectorClass<const SmudgeTypeClass*> -- vtable 0x007F0D7C slot 3; locator 0x00808BB0 -> type descriptor 0x00839F70
//   `.?AV?$VectorClass@PBVSmudgeTypeClass@@@@`.
template class VectorClass<const SmudgeTypeClass*>;

// FUNCTION: GAMEMD 0x0067B2E0
// VectorClass<const TerrainTypeClass*> -- vtable 0x007F0D9C slot 3; locator 0x00808C10 -> type descriptor 0x00839EC8
//   `.?AV?$VectorClass@PBVTerrainTypeClass@@@@`.
template class VectorClass<const TerrainTypeClass*>;

// FUNCTION: GAMEMD 0x0069C800
// VectorClass<DiskID> -- vtable 0x007F1274 slot 3; locator 0x00809270 -> type descriptor 0x0083F530
//   `.?AV?$VectorClass@W4DiskID@@@@`.
template class VectorClass<DiskID>;

// FUNCTION: GAMEMD 0x0069CE30
// VectorClass<MultiMission*> -- vtable 0x007F1214 slot 3; locator 0x008091F8 -> type descriptor 0x0083EDD0
//   `.?AV?$VectorClass@PAVMultiMission@@@@`.
template class VectorClass<MultiMission*>;

// FUNCTION: GAMEMD 0x0069D090
// VectorClass<GlobalPacketType*> -- vtable 0x007F1234 slot 3; locator 0x00809228 -> type descriptor 0x0083EE38
//   `.?AV?$VectorClass@PAUGlobalPacketType@@@@`.
template class VectorClass<GlobalPacketType*>;

// FUNCTION: GAMEMD 0x0069D2F0
// VectorClass<PhoneEntryClass*> -- vtable 0x007F1254 slot 3; locator 0x008091C8 -> type descriptor 0x0083ED60
//   `.?AV?$VectorClass@PAVPhoneEntryClass@@@@`.
template class VectorClass<PhoneEntryClass*>;

// FUNCTION: GAMEMD 0x006B1560
// VectorClass<SlaveManagerClass::SlaveControl*> -- vtable 0x007F324C slot 3; locator 0x00809798 -> type descriptor 0x0083FD30
//   `.?AV?$VectorClass@PAUSlaveControl@SlaveManagerClass@@@@`.
template class VectorClass<SlaveManagerClass::SlaveControl*>;

// FUNCTION: GAMEMD 0x006B17C0
// VectorClass<SlaveManagerClass*> -- vtable 0x007F317C slot 3; locator 0x00809650 -> type descriptor 0x0083FC98
//   `.?AV?$VectorClass@PAVSlaveManagerClass@@@@`.
template class VectorClass<SlaveManagerClass*>;

// FUNCTION: GAMEMD 0x006B45A0
// VectorClass<UndoInfoStruct> -- vtable 0x007F329C slot 3; locator 0x00809830 -> type descriptor 0x0083FF70
//   `.?AV?$VectorClass@UUndoInfoStruct@@@@`.
template class VectorClass<UndoInfoStruct>;

// FUNCTION: GAMEMD 0x006B8310
// VectorClass<SpawnManagerClass::SpawnControl*> -- vtable 0x007F36D4 slot 3; locator 0x00809B80 -> type descriptor 0x00840140
//   `.?AV?$VectorClass@PAUSpawnControl@SpawnManagerClass@@@@`.
template class VectorClass<SpawnManagerClass::SpawnControl*>;

// FUNCTION: GAMEMD 0x006B85D0
// VectorClass<SpawnManagerClass*> -- vtable 0x007F3604 slot 3; locator 0x00809A38 -> type descriptor 0x008400A8
//   `.?AV?$VectorClass@PAVSpawnManagerClass@@@@`.
template class VectorClass<SpawnManagerClass*>;

// FUNCTION: GAMEMD 0x006C62C0
// VectorClass<unsigned long> -- vtable 0x007F3748 slot 3; locator 0x00809C18 -> type descriptor 0x00840A88
//   `.?AV?$VectorClass@K@@`.
template class VectorClass<unsigned long>;

// FUNCTION: GAMEMD 0x006CAAC0
// VectorClass<SubTitle*> -- vtable 0x007F3F8C slot 3; locator 0x0080B560 -> type descriptor 0x008422A0
//   `.?AV?$VectorClass@PAVSubTitle@@@@`.
template class VectorClass<SubTitle*>;

// FUNCTION: GAMEMD 0x006CF690
// VectorClass<SwizzlePointerClass> -- vtable 0x007F4154 slot 3; locator 0x0080B7C8 -> type descriptor 0x00842758
//   `.?AV?$VectorClass@VSwizzlePointerClass@@@@`.
template class VectorClass<SwizzlePointerClass>;

// FUNCTION: GAMEMD 0x006DC780
// VectorClass<DirtyAreaStruct> -- vtable 0x007F42BC slot 3; locator 0x0080B860 -> type descriptor 0x00842958
//   `.?AV?$VectorClass@UDirtyAreaStruct@@@@`.
template class VectorClass<DirtyAreaStruct>;

// FUNCTION: GAMEMD 0x006DCAC0
// VectorClass<ShadowControlClass*> -- vtable 0x007F42FC slot 3; locator 0x0080B8F8 -> type descriptor 0x008429C0
//   `.?AV?$VectorClass@PAVShadowControlClass@@@@`.
template class VectorClass<ShadowControlClass*>;

// FUNCTION: GAMEMD 0x006E4940
// VectorClass<TActionClass*> -- vtable 0x007F43F0 slot 3; locator 0x0080BA40 -> type descriptor 0x00842B10
//   `.?AV?$VectorClass@PAVTActionClass@@@@`.
template class VectorClass<TActionClass*>;

// FUNCTION: GAMEMD 0x006E6630
// VectorClass<TagTypeClass*> -- vtable 0x007F4578 slot 3; locator 0x0080BC38 -> type descriptor 0x00842C48
//   `.?AV?$VectorClass@PAVTagTypeClass@@@@`.
template class VectorClass<TagTypeClass*>;

// FUNCTION: GAMEMD 0x0071B390
// VectorClass<TemporalClass*> -- vtable 0x007F5134 slot 3; locator 0x0080C278 -> type descriptor 0x00844560
//   `.?AV?$VectorClass@PAVTemporalClass@@@@`.
template class VectorClass<TemporalClass*>;

// FUNCTION: GAMEMD 0x0071FCF0
// VectorClass<TEventClass*> -- vtable 0x007F552C slot 3; locator 0x0080C530 -> type descriptor 0x00844690
//   `.?AV?$VectorClass@PAVTEventClass@@@@`.
template class VectorClass<TEventClass*>;

// FUNCTION: GAMEMD 0x00723880
// VectorClass<TiberiumClass*> -- vtable 0x007F56DC slot 3; locator 0x0080C720 -> type descriptor 0x00844860
//   `.?AV?$VectorClass@PAVTiberiumClass@@@@`.
template class VectorClass<TiberiumClass*>;

// FUNCTION: GAMEMD 0x0074C0E0
// VectorClass<unsigned char> -- vtable 0x007F65F4 slot 3; locator 0x0080CEF8 -> type descriptor 0x00845F28
//   `.?AV?$VectorClass@E@@`.
template class VectorClass<unsigned char>;

// FUNCTION: GAMEMD 0x0074F4B0
// VectorClass<VeinholeMonsterClass*> -- vtable 0x007F665C slot 3; locator 0x0080CF90 -> type descriptor 0x00846070
//   `.?AV?$VectorClass@PAVVeinholeMonsterClass@@@@`.
template class VectorClass<VeinholeMonsterClass*>;

// FUNCTION: GAMEMD 0x00751A20
// VectorClass<VocClass*> -- vtable 0x007F68CC slot 3; locator 0x0080D0E0 -> type descriptor 0x008464C8
//   `.?AV?$VectorClass@PAVVocClass@@@@`.
template class VectorClass<VocClass*>;

// FUNCTION: GAMEMD 0x007537A0
// VectorClass<VoxClass*> -- vtable 0x007F6924 slot 3; locator 0x0080D178 -> type descriptor 0x00846618
//   `.?AV?$VectorClass@PAVVoxClass@@@@`.
template class VectorClass<VoxClass*>;

// FUNCTION: GAMEMD 0x0075A580
// VectorClass<MovieHandle*> -- vtable 0x007F69A4 slot 3; locator 0x0080D210 -> type descriptor 0x00847AF8
//   `.?AV?$VectorClass@PAVMovieHandle@@@@`.
template class VectorClass<MovieHandle*>;

// FUNCTION: GAMEMD 0x00764550
// VectorClass<WaypointPathClass*> -- vtable 0x007F6E24 slot 3; locator 0x0080D4B0 -> type descriptor 0x00847EC8
//   `.?AV?$VectorClass@PAVWaypointPathClass@@@@`.
template class VectorClass<WaypointPathClass*>;

// FUNCTION: GAMEMD 0x0076A220
// VectorClass<WorldDominationTour::Map::AnimationPalette*> -- vtable 0x007F71A4 slot 3; locator 0x0080DF28 -> type descriptor 0x008488E0
//   `.?AV?$VectorClass@PAUAnimationPalette@Map@WorldDominationTour@@@@`.
template class VectorClass<WorldDominationTour::Map::AnimationPalette*>;

// FUNCTION: GAMEMD 0x0076A4F0
// VectorClass<WorldDominationTour::Centroid> -- vtable 0x007F71E0 slot 3; locator 0x0080E008 -> type descriptor 0x00848B88
//   `.?AV?$VectorClass@VCentroid@WorldDominationTour@@@@`.
template class VectorClass<WorldDominationTour::Centroid>;

// FUNCTION: GAMEMD 0x007AD180
// VectorClass<tConnInfoStruct*> -- vtable 0x007F78A4 slot 3; locator 0x0080E8B0 -> type descriptor 0x0084C6C0
//   `.?AV?$VectorClass@PAUtConnInfoStruct@@@@`.
template class VectorClass<tConnInfoStruct*>;

// FUNCTION: GAMEMD 0x007B2990
// VectorClass<WinsockInterfaceClass::WinsockBufferType*> -- vtable 0x007F7A3C slot 3; locator 0x0080EB28 -> type descriptor 0x0084DDA8
//   `.?AV?$VectorClass@PAUWinsockBufferType@WinsockInterfaceClass@@@@`.
template class VectorClass<WinsockInterfaceClass::WinsockBufferType*>;

// FUNCTION: GAMEMD 0x007B4410
// VectorClass<unsigned char*> -- vtable 0x007F7B0C slot 3; locator 0x0080EC10 -> type descriptor 0x0084E178
//   `.?AV?$VectorClass@PAE@@`.
template class VectorClass<unsigned char*>;

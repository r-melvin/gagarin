// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x478440 and its 68
//   siblings.
//
//   The retail class identity and slot binding are confirmed from the binary:
//   each annotated body occupies slot 3 of the listed VectorClass<T> vtable.
//   Slot 3 is Clear, called on a live vector by retail (including the
//   ToolTipManager constructor at 0x724000); these bodies clear owned storage
//   and reset vector bookkeeping without reseating a vptr. The source template
//   is VectorClass<T>::Clear, and the element argument is recovered from RTTI.
//
//   The 69 remaining addresses are bound to VectorClass<T> tables;
//   each table's complete object locator and body address were read from the
//   retail binary. No destructor identity is inferred from the byte pattern.
//
//   KNOWN LIMITATION -- these compiled template instantiations are grouped
//   here for per-function verification. The retail binary does not establish
//   their original translation-unit grouping or final linker placement.
//   This sweep file does not establish an integrated engine link order.
// Int, ToolTip and TechnoType pointer entries use native specialization TUs.
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

// Actual-template layout assertions are in vector_class_layout_asserts.cpp.

// FUNCTION: GAMEMD 0x00478440
// VectorClass<RGBClass> -- vtable 0x007E4E38 slot 3; locator 0x007FCF90 -> type descriptor 0x0081C198
//   `.?AV?$VectorClass@VRGBClass@@@@`.
template class VectorClass<RGBClass>;

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

// FUNCTION: GAMEMD 0x004D2B20
// VectorClass<FoggedObjectClass::DrawRecord> -- vtable 0x007E8BC0 slot 3; locator 0x00800800 -> type descriptor 0x00822458
//   `.?AV?$VectorClass@UDrawRecord@FoggedObjectClass@@@@`.
template class VectorClass<FoggedObjectClass::DrawRecord>;

// FUNCTION: GAMEMD 0x004E97B0
// VectorClass<SuperClass*> -- vtable 0x007EA504 slot 3; locator 0x008022B8 -> type descriptor 0x00823DF8
//   `.?AV?$VectorClass@PAVSuperClass@@@@`.
template class VectorClass<SuperClass*>;

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

// FUNCTION: GAMEMD 0x004EA9D0
// VectorClass<TubeClass*> -- vtable 0x007E9CC4 slot 3; locator 0x00800F20 -> type descriptor 0x00822FD0
//   `.?AV?$VectorClass@PAVTubeClass@@@@`.
template class VectorClass<TubeClass*>;

// FUNCTION: GAMEMD 0x004EB350
// VectorClass<SmudgeClass*> -- vtable 0x007E9DC4 slot 3; locator 0x00801180 -> type descriptor 0x00823170
//   `.?AV?$VectorClass@PAVSmudgeClass@@@@`.
template class VectorClass<SmudgeClass*>;

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

// FUNCTION: GAMEMD 0x004EE530
// VectorClass<BulletTypeClass*> -- vtable 0x007EA384 slot 3; locator 0x00801F28 -> type descriptor 0x00823B28
//   `.?AV?$VectorClass@PAVBulletTypeClass@@@@`.
template class VectorClass<BulletTypeClass*>;

// FUNCTION: GAMEMD 0x004EE9F0
// VectorClass<IsometricTileTypeClass*> -- vtable 0x007EA404 slot 3; locator 0x00802058 -> type descriptor 0x00823C10
//   `.?AV?$VectorClass@PAVIsometricTileTypeClass@@@@`.
template class VectorClass<IsometricTileTypeClass*>;

// FUNCTION: GAMEMD 0x004EEC50
// VectorClass<ParticleTypeClass*> -- vtable 0x007EA444 slot 3; locator 0x008020F0 -> type descriptor 0x00823C88
//   `.?AV?$VectorClass@PAVParticleTypeClass@@@@`.
template class VectorClass<ParticleTypeClass*>;

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

// FUNCTION: GAMEMD 0x0050FA90
// VectorClass<bool> -- vtable 0x007EAA5C slot 3; locator 0x00802D68 -> type descriptor 0x00824E70
//   `.?AV?$VectorClass@_N@@`.
template class VectorClass<bool>;

// FUNCTION: GAMEMD 0x0054A340
// VectorClass<unsigned short*> -- vtable 0x007ECD0C slot 3; locator 0x00804C58 -> type descriptor 0x008290F0
//   `.?AV?$VectorClass@PAG@@`.
template class VectorClass<unsigned short*>;

// FUNCTION: GAMEMD 0x0054A5A0
// VectorClass<IsometricTileTypeClass::TileInsertType*> -- vtable 0x007ECBFC slot 3; locator 0x00804B08 -> type descriptor 0x00829030
//   `.?AV?$VectorClass@PAUTileInsertType@IsometricTileTypeClass@@@@`.
template class VectorClass<IsometricTileTypeClass::TileInsertType*>;

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

// FUNCTION: GAMEMD 0x005ACE20
// VectorClass<TRect<int>> -- vtable 0x007ED970 slot 3; locator 0x00805AC0 -> type descriptor 0x0082BFE0
//   `.?AV?$VectorClass@V?$TRect@H@@@@`.
template class VectorClass<TRect<int> >;

// FUNCTION: GAMEMD 0x005AD1F0
// VectorClass<double> -- vtable 0x007EDA4C slot 3; locator 0x00805B40 -> type descriptor 0x0082C048
//   `.?AV?$VectorClass@N@@`.
template class VectorClass<double>;

// FUNCTION: GAMEMD 0x005D0920
// VectorClass<Point2D> -- vtable 0x007EEB74 slot 3; locator 0x00806B88 -> type descriptor 0x00830380
//   `.?AV?$VectorClass@VPoint2D@@@@`.
template class VectorClass<Point2D>;

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

// FUNCTION: GAMEMD 0x005F9C70
// VectorClass<ObjectTypeClass*> -- vtable 0x007EF28C slot 3; locator 0x008074E0 -> type descriptor 0x00832A10
//   `.?AV?$VectorClass@PAVObjectTypeClass@@@@`.
template class VectorClass<ObjectTypeClass*>;

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

// FUNCTION: GAMEMD 0x0069C800
// VectorClass<DiskID> -- vtable 0x007F1274 slot 3; locator 0x00809270 -> type descriptor 0x0083F530
//   `.?AV?$VectorClass@W4DiskID@@@@`.
template class VectorClass<DiskID>;

// FUNCTION: GAMEMD 0x0069CE30
// VectorClass<MultiMission*> -- vtable 0x007F1214 slot 3; locator 0x008091F8 -> type descriptor 0x0083EDD0
//   `.?AV?$VectorClass@PAVMultiMission@@@@`.
template class VectorClass<MultiMission*>;

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

// FUNCTION: GAMEMD 0x006CF690
// VectorClass<SwizzlePointerClass> -- vtable 0x007F4154 slot 3; locator 0x0080B7C8 -> type descriptor 0x00842758
//   `.?AV?$VectorClass@VSwizzlePointerClass@@@@`.
template class VectorClass<SwizzlePointerClass>;

// FUNCTION: GAMEMD 0x006DC780
// VectorClass<DirtyAreaStruct> -- vtable 0x007F42BC slot 3; locator 0x0080B860 -> type descriptor 0x00842958
//   `.?AV?$VectorClass@UDirtyAreaStruct@@@@`.
template class VectorClass<DirtyAreaStruct>;

// FUNCTION: GAMEMD 0x0074C0E0
// VectorClass<unsigned char> -- vtable 0x007F65F4 slot 3; locator 0x0080CEF8 -> type descriptor 0x00845F28
//   `.?AV?$VectorClass@E@@`.
template class VectorClass<unsigned char>;

// FUNCTION: GAMEMD 0x0076A4F0
// VectorClass<WorldDominationTour::Centroid> -- vtable 0x007F71E0 slot 3; locator 0x0080E008 -> type descriptor 0x00848B88
//   `.?AV?$VectorClass@VCentroid@WorldDominationTour@@@@`.
template class VectorClass<WorldDominationTour::Centroid>;

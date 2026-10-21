// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x477900 and its 81
//   siblings.
//
//   Retail calls these bodies through slot 3 of the listed
//   DynamicVectorClass<T> vtables. Slot 3 is Clear on a live vector: it resets
//   the count and storage bookkeeping without reseating the object's vptr.
//   The element types and class identity are checked against each retail RTTI
//   descriptor. Twelve addresses also occur as an inherited slot in a
//   TypeList<T> table; the implementation belongs to DynamicVectorClass<T>.
//   The DiskID entry remains separate because its owner is not proven to be
//   DynamicVectorClass<T>.
//
//   KNOWN LIMITATION -- these compiled template instantiations are grouped
//   here for per-function verification. The retail binary does not establish
//   their original translation-unit grouping or final linker placement.
//   This sweep file does not establish an integrated engine link order.
// Int, ToolTip and TechnoType pointer entries use native specialization TUs.
#include "vector_class.h"
#include "vector_counted_dtor_family_methods.h"

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

// Legacy CountedVector<DiskID> remains an isolated stand-in; canonical layout assertions are in vector_class_layout_asserts.cpp.

// FUNCTION: GAMEMD 0x00477900
// DynamicVectorClass<RGBClass> -- vtable 0x007F022C slot 3; locator 0x00808328 -> type descriptor 0x0081C140
//   `.?AV?$DynamicVectorClass@VRGBClass@@@@`.
//   The same body also sits at that slot in TypeList<RGBClass> (0x007E4E58); DynamicVectorClass<RGBClass> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template class DynamicVectorClass<RGBClass>;

// FUNCTION: GAMEMD 0x0049E950
// DynamicVectorClass<char*> -- vtable 0x007E5BC4 slot 3; locator 0x007FF560 -> type descriptor 0x0081F260
//   `.?AV?$DynamicVectorClass@PAD@@`.
template class DynamicVectorClass<char*>;

// FUNCTION: GAMEMD 0x0049E9B0
// DynamicVectorClass<DynamicVectorClass<char*>*> -- vtable 0x007E5BE4 slot 3; locator 0x007FF5C8 -> type descriptor 0x0081F2C8
//   `.?AV?$DynamicVectorClass@PAV?$DynamicVectorClass@PAD@@@@`.
template class DynamicVectorClass<DynamicVectorClass<char*>*>;

// FUNCTION: GAMEMD 0x004A0EB0
// DynamicVectorClass<tagCONNECTDATA> -- vtable 0x007E5CC4 slot 3; locator 0x007FF790 -> type descriptor 0x0081F670
//   `.?AV?$DynamicVectorClass@UtagCONNECTDATA@@@@`.
template class DynamicVectorClass<tagCONNECTDATA>;

// FUNCTION: GAMEMD 0x004A0F20
// DynamicVectorClass<IConnectionPoint*> -- vtable 0x007E5D48 slot 3; locator 0x007FF8F8 -> type descriptor 0x0081F778
//   `.?AV?$DynamicVectorClass@PAUIConnectionPoint@@@@`.
template class DynamicVectorClass<IConnectionPoint*>;

// FUNCTION: GAMEMD 0x004A4AD0
// DynamicVectorClass<_DDSURFACEDESC*> -- vtable 0x007E5E0C slot 3; locator 0x007FFA50 -> type descriptor 0x0081FED0
//   `.?AV?$DynamicVectorClass@PAU_DDSURFACEDESC@@@@`.
template class DynamicVectorClass<_DDSURFACEDESC*>;

// FUNCTION: GAMEMD 0x004C2C40
// DynamicVectorClass<EBolt*> -- vtable 0x007E868C slot 3; locator 0x008002C8 -> type descriptor 0x00820738
//   `.?AV?$DynamicVectorClass@PAVEBolt@@@@`.
template class DynamicVectorClass<EBolt*>;

// FUNCTION: GAMEMD 0x004D2930
// DynamicVectorClass<FoggedObjectClass::DrawRecord> -- vtable 0x007E8BA0 slot 3; locator 0x008007D0 -> type descriptor 0x00822498
//   `.?AV?$DynamicVectorClass@UDrawRecord@FoggedObjectClass@@@@`.
template class DynamicVectorClass<FoggedObjectClass::DrawRecord>;

// FUNCTION: GAMEMD 0x004E8350
// DynamicVectorClass<SuperClass*> -- vtable 0x007EA4E4 slot 3; locator 0x00802288 -> type descriptor 0x00823E28
//   `.?AV?$DynamicVectorClass@PAVSuperClass@@@@`.
template class DynamicVectorClass<SuperClass*>;

// FUNCTION: GAMEMD 0x004E8470
// DynamicVectorClass<ParticleClass*> -- vtable 0x007E9D64 slot 3; locator 0x008010B8 -> type descriptor 0x00823138
//   `.?AV?$DynamicVectorClass@PAVParticleClass@@@@`.
template class DynamicVectorClass<ParticleClass*>;

// FUNCTION: GAMEMD 0x004E84D0
// DynamicVectorClass<TeamClass*> -- vtable 0x007E9F64 slot 3; locator 0x00801578 -> type descriptor 0x00823478
//   `.?AV?$DynamicVectorClass@PAVTeamClass@@@@`.
template class DynamicVectorClass<TeamClass*>;

// FUNCTION: GAMEMD 0x004E8600
// DynamicVectorClass<TubeClass*> -- vtable 0x007E9CA4 slot 3; locator 0x00800EF0 -> type descriptor 0x00823000
//   `.?AV?$DynamicVectorClass@PAVTubeClass@@@@`.
template class DynamicVectorClass<TubeClass*>;

// FUNCTION: GAMEMD 0x004E8780
// DynamicVectorClass<SmudgeClass*> -- vtable 0x007E9DA4 slot 3; locator 0x00801150 -> type descriptor 0x008231A0
//   `.?AV?$DynamicVectorClass@PAVSmudgeClass@@@@`.
template class DynamicVectorClass<SmudgeClass*>;

// FUNCTION: GAMEMD 0x004E8A80
// DynamicVectorClass<SideClass*> -- vtable 0x007EA024 slot 3; locator 0x00801740 -> type descriptor 0x008235B0
//   `.?AV?$DynamicVectorClass@PAVSideClass@@@@`.
template class DynamicVectorClass<SideClass*>;

// FUNCTION: GAMEMD 0x004E8AE0
// DynamicVectorClass<HouseTypeClass*> -- vtable 0x007EA064 slot 3; locator 0x008017D8 -> type descriptor 0x00823618
//   `.?AV?$DynamicVectorClass@PAVHouseTypeClass@@@@`.
template class DynamicVectorClass<HouseTypeClass*>;

// FUNCTION: GAMEMD 0x004E8B40
// DynamicVectorClass<TaskForceClass*> -- vtable 0x007EA0A4 slot 3; locator 0x00801870 -> type descriptor 0x00823680
//   `.?AV?$DynamicVectorClass@PAVTaskForceClass@@@@`.
template class DynamicVectorClass<TaskForceClass*>;

// FUNCTION: GAMEMD 0x004E8F60
// DynamicVectorClass<BulletTypeClass*> -- vtable 0x007EA364 slot 3; locator 0x00801EF8 -> type descriptor 0x00823B60
//   `.?AV?$DynamicVectorClass@PAVBulletTypeClass@@@@`.
template class DynamicVectorClass<BulletTypeClass*>;

// FUNCTION: GAMEMD 0x004E9020
// DynamicVectorClass<IsometricTileTypeClass*> -- vtable 0x007EA3E4 slot 3; locator 0x00802028 -> type descriptor 0x00823C48
//   `.?AV?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@`.
template class DynamicVectorClass<IsometricTileTypeClass*>;

// FUNCTION: GAMEMD 0x004E9080
// DynamicVectorClass<ParticleTypeClass*> -- vtable 0x007EA424 slot 3; locator 0x008020C0 -> type descriptor 0x00823CC0
//   `.?AV?$DynamicVectorClass@PAVParticleTypeClass@@@@`.
template class DynamicVectorClass<ParticleTypeClass*>;

// FUNCTION: GAMEMD 0x0050E500
// DynamicVectorClass<HouseClass::StartingTechnoStruct*> -- vtable 0x007EA944 slot 3; locator 0x00802B60 -> type descriptor 0x00824638
//   `.?AV?$DynamicVectorClass@PAUStartingTechnoStruct@HouseClass@@@@`.
template class DynamicVectorClass<HouseClass::StartingTechnoStruct*>;

// FUNCTION: GAMEMD 0x0050E560
// DynamicVectorClass<AngerStruct> -- vtable 0x007EA924 slot 3; locator 0x00802AF8 -> type descriptor 0x008245B8
//   `.?AV?$DynamicVectorClass@UAngerStruct@@@@`.
template class DynamicVectorClass<AngerStruct>;

// FUNCTION: GAMEMD 0x0050E5D0
// DynamicVectorClass<ScoutStruct> -- vtable 0x007EA904 slot 3; locator 0x00802A90 -> type descriptor 0x00824550
//   `.?AV?$DynamicVectorClass@UScoutStruct@@@@`.
template class DynamicVectorClass<ScoutStruct>;

// FUNCTION: GAMEMD 0x0050E640
// DynamicVectorClass<HouseClass::BuildChoiceClass*> -- vtable 0x007EA7B4 slot 3; locator 0x00802858 -> type descriptor 0x00824458
//   `.?AV?$DynamicVectorClass@PAUBuildChoiceClass@HouseClass@@@@`.
template class DynamicVectorClass<HouseClass::BuildChoiceClass*>;

// FUNCTION: GAMEMD 0x0050E700
// DynamicVectorClass<bool> -- vtable 0x007EAA7C slot 3; locator 0x00802DD0 -> type descriptor 0x00824E90
//   `.?AV?$DynamicVectorClass@_N@@`.
template class DynamicVectorClass<bool>;

// FUNCTION: GAMEMD 0x0053DA40
// DynamicVectorClass<IonBlastClass*> -- vtable 0x007EC05C slot 3; locator 0x00804850 -> type descriptor 0x00828100
//   `.?AV?$DynamicVectorClass@PAVIonBlastClass@@@@`.
template class DynamicVectorClass<IonBlastClass*>;

// FUNCTION: GAMEMD 0x0054A190
// DynamicVectorClass<unsigned short*> -- vtable 0x007ECCEC slot 3; locator 0x00804C28 -> type descriptor 0x00829110
//   `.?AV?$DynamicVectorClass@PAG@@`.
template class DynamicVectorClass<unsigned short*>;

// FUNCTION: GAMEMD 0x0054A1F0
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*> -- vtable 0x007ECBDC slot 3; locator 0x00804AD8 -> type descriptor 0x00829078
//   `.?AV?$DynamicVectorClass@PAUTileInsertType@IsometricTileTypeClass@@@@`.
template class DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>;

// FUNCTION: GAMEMD 0x0054E890
// DynamicVectorClass<KamikazeControl*> -- vtable 0x007ECE7C slot 3; locator 0x00804D58 -> type descriptor 0x008296A8
//   `.?AV?$DynamicVectorClass@PAUKamikazeControl@@@@`.
template class DynamicVectorClass<KamikazeControl*>;

// FUNCTION: GAMEMD 0x005512D0
// DynamicVectorClass<LaserDrawClass*> -- vtable 0x007ECEDC slot 3; locator 0x00804DF0 -> type descriptor 0x00829710
//   `.?AV?$DynamicVectorClass@PAVLaserDrawClass@@@@`.
template class DynamicVectorClass<LaserDrawClass*>;

// FUNCTION: GAMEMD 0x00555200
// DynamicVectorClass<LightSourceClass*> -- vtable 0x007ECF7C slot 3; locator 0x00804F78 -> type descriptor 0x00829B28
//   `.?AV?$DynamicVectorClass@PAVLightSourceClass@@@@`.
template class DynamicVectorClass<LightSourceClass*>;

// FUNCTION: GAMEMD 0x00555260
// DynamicVectorClass<LightSourceClass::PendingCellClass*> -- vtable 0x007ECFBC slot 3; locator 0x00805010 -> type descriptor 0x00829BB0
//   `.?AV?$DynamicVectorClass@PAVPendingCellClass@LightSourceClass@@@@`.
template class DynamicVectorClass<LightSourceClass::PendingCellClass*>;

// FUNCTION: GAMEMD 0x00556EB0
// DynamicVectorClass<LineTrail*> -- vtable 0x007ED0CC slot 3; locator 0x008051A8 -> type descriptor 0x00829D78
//   `.?AV?$DynamicVectorClass@PAVLineTrail@@@@`.
template class DynamicVectorClass<LineTrail*>;

// FUNCTION: GAMEMD 0x00588C90
// DynamicVectorClass<SubzoneConnectionStruct> -- vtable 0x007ED5A0 slot 3; locator 0x008057F8 -> type descriptor 0x0082ADD0
//   `.?AV?$DynamicVectorClass@USubzoneConnectionStruct@@@@`.
template class DynamicVectorClass<SubzoneConnectionStruct>;

// FUNCTION: GAMEMD 0x00588CE0
// DynamicVectorClass<ZoneConnectionClass> -- vtable 0x007ED4C0 slot 3; locator 0x00805530 -> type descriptor 0x0082AAC0
//   `.?AV?$DynamicVectorClass@UZoneConnectionClass@@@@`.
template class DynamicVectorClass<ZoneConnectionClass>;

// FUNCTION: GAMEMD 0x00588F00
// DynamicVectorClass<PassabilityType> -- vtable 0x007ED580 slot 3; locator 0x008057A8 -> type descriptor 0x0082AD10
//   `.?AV?$DynamicVectorClass@W4PassabilityType@@@@`.
template class DynamicVectorClass<PassabilityType>;

// FUNCTION: GAMEMD 0x00588F60
// DynamicVectorClass<HashObject<unsigned int, unsigned int>> -- vtable 0x007ED540 slot 3; locator 0x008056A8 -> type descriptor 0x0082ABD8
//   `.?AV?$DynamicVectorClass@U?$HashObject@II@@@@`.
template class DynamicVectorClass<HashObject<unsigned int, unsigned int> >;

// FUNCTION: GAMEMD 0x00588FD0
// DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct>> -- vtable 0x007ED520 slot 3; locator 0x00805710 -> type descriptor 0x0082AC58
//   `.?AV?$DynamicVectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@`.
template class DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct> >;

// FUNCTION: GAMEMD 0x005AC4C0
// DynamicVectorClass<_WIN32_FIND_DATAA*> -- vtable 0x007ED94C slot 3; locator 0x00805A28 -> type descriptor 0x0082BAD0
//   `.?AV?$DynamicVectorClass@PAU_WIN32_FIND_DATAA@@@@`.
template class DynamicVectorClass<_WIN32_FIND_DATAA*>;

// FUNCTION: GAMEMD 0x005AC520
// DynamicVectorClass<TRect<int>> -- vtable 0x007ED99C slot 3; locator 0x00805A78 -> type descriptor 0x0082BFB0
//   `.?AV?$DynamicVectorClass@V?$TRect@H@@@@`.
template class DynamicVectorClass<TRect<int> >;

// FUNCTION: GAMEMD 0x005AC5A0
// DynamicVectorClass<CellClass*> -- vtable 0x007ED9BC slot 3; locator 0x00805B10 -> type descriptor 0x0082C010
//   `.?AV?$DynamicVectorClass@PAVCellClass@@@@`.
template class DynamicVectorClass<CellClass*>;

// FUNCTION: GAMEMD 0x005AC5F0
// DynamicVectorClass<double> -- vtable 0x007EDA6C slot 3; locator 0x00805BA8 -> type descriptor 0x0082C068
//   `.?AV?$DynamicVectorClass@N@@`.
template class DynamicVectorClass<double>;

// FUNCTION: GAMEMD 0x005C5070
// DynamicVectorClass<NodeNameType*> -- vtable 0x007EE370 slot 3; locator 0x00806210 -> type descriptor 0x0082DBE0
//   `.?AV?$DynamicVectorClass@PAUNodeNameType@@@@`.
template class DynamicVectorClass<NodeNameType*>;

// FUNCTION: GAMEMD 0x005D05A0
// DynamicVectorClass<Point2D> -- vtable 0x007EEB54 slot 3; locator 0x00806A88 -> type descriptor 0x008303A8
//   `.?AV?$DynamicVectorClass@VPoint2D@@@@`.
template class DynamicVectorClass<Point2D>;

// FUNCTION: GAMEMD 0x005D0670
// DynamicVectorClass<MapSelection*> -- vtable 0x007EEB14 slot 3; locator 0x00806AF0 -> type descriptor 0x00830408
//   `.?AV?$DynamicVectorClass@PAVMapSelection@@@@`.
template class DynamicVectorClass<MapSelection*>;

// FUNCTION: GAMEMD 0x005D06D0
// DynamicVectorClass<MapStage*> -- vtable 0x007EEA94 slot 3; locator 0x00806928 -> type descriptor 0x00830230
//   `.?AV?$DynamicVectorClass@PAVMapStage@@@@`.
template class DynamicVectorClass<MapStage*>;

// FUNCTION: GAMEMD 0x005D0730
// DynamicVectorClass<MSAnimEntry*> -- vtable 0x007EEA74 slot 3; locator 0x008068C0 -> type descriptor 0x008301C8
//   `.?AV?$DynamicVectorClass@PAVMSAnimEntry@@@@`.
template class DynamicVectorClass<MSAnimEntry*>;

// FUNCTION: GAMEMD 0x005D0790
// DynamicVectorClass<MSSfxEntry*> -- vtable 0x007EEA54 slot 3; locator 0x00806990 -> type descriptor 0x00830298
//   `.?AV?$DynamicVectorClass@PAVMSSfxEntry@@@@`.
template class DynamicVectorClass<MSSfxEntry*>;

// FUNCTION: GAMEMD 0x005D2720
// DynamicVectorClass<MSAnim*> -- vtable 0x007EEC04 slot 3; locator 0x00806CB8 -> type descriptor 0x00830580
//   `.?AV?$DynamicVectorClass@PAVMSAnim@@@@`.
template class DynamicVectorClass<MSAnim*>;

// FUNCTION: GAMEMD 0x005D2780
// DynamicVectorClass<MSSfx*> -- vtable 0x007EEBE4 slot 3; locator 0x00806C50 -> type descriptor 0x00830528
//   `.?AV?$DynamicVectorClass@PAVMSSfx@@@@`.
template class DynamicVectorClass<MSSfx*>;

// FUNCTION: GAMEMD 0x005D5080
// DynamicVectorClass<HWND__*> -- vtable 0x007EEC8C slot 3; locator 0x00806DF8 -> type descriptor 0x008306F8
//   `.?AV?$DynamicVectorClass@PAUHWND__@@@@`.
template class DynamicVectorClass<HWND__*>;

// FUNCTION: GAMEMD 0x005D50E0
// DynamicVectorClass<AcceleratorTracker> -- vtable 0x007EECCC slot 3; locator 0x00806E90 -> type descriptor 0x00830760
//   `.?AV?$DynamicVectorClass@UAcceleratorTracker@@@@`.
template class DynamicVectorClass<AcceleratorTracker>;

// FUNCTION: GAMEMD 0x005D80B0
// DynamicVectorClass<MultiplayerTeam*> -- vtable 0x007EEE34 slot 3; locator 0x00806FF0 -> type descriptor 0x00830868
//   `.?AV?$DynamicVectorClass@PAVMultiplayerTeam@@@@`.
template class DynamicVectorClass<MultiplayerTeam*>;

// FUNCTION: GAMEMD 0x005D8110
// DynamicVectorClass<MultiplayerGameMode*> -- vtable 0x007EED20 slot 3; locator 0x00806F28 -> type descriptor 0x008307F0
//   `.?AV?$DynamicVectorClass@PAVMultiplayerGameMode@@@@`.
template class DynamicVectorClass<MultiplayerGameMode*>;

// FUNCTION: GAMEMD 0x005F9B00
// DynamicVectorClass<ObjectTypeClass*> -- vtable 0x007EF26C slot 3; locator 0x008074B0 -> type descriptor 0x00832A48
//   `.?AV?$DynamicVectorClass@PAVObjectTypeClass@@@@`.
template class DynamicVectorClass<ObjectTypeClass*>;

// FUNCTION: GAMEMD 0x005FFFC0
// DynamicVectorClass<SpotLightClass*> -- vtable 0x007EF6BC slot 3; locator 0x00807758 -> type descriptor 0x00833618
//   `.?AV?$DynamicVectorClass@PAVSpotLightClass@@@@`.
template class DynamicVectorClass<SpotLightClass*>;

// FUNCTION: GAMEMD 0x00627D80
// DynamicVectorClass<HSVClass> -- vtable 0x007EF750 slot 3; locator 0x00807888 -> type descriptor 0x008364A0
//   `.?AV?$DynamicVectorClass@VHSVClass@@@@`.
template class DynamicVectorClass<HSVClass>;

// FUNCTION: GAMEMD 0x00628800
// DynamicVectorClass<HashObject<HashString, SchemeNode*>> -- vtable 0x007EF770 slot 3; locator 0x008078F0 -> type descriptor 0x00836520
//   `.?AV?$DynamicVectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@`.
template class DynamicVectorClass<HashObject<HashString, SchemeNode*> >;

// FUNCTION: GAMEMD 0x0062B070
// DynamicVectorClass<ParasiteClass*> -- vtable 0x007EF824 slot 3; locator 0x00807A50 -> type descriptor 0x00836608
//   `.?AV?$DynamicVectorClass@PAVParasiteClass@@@@`.
template class DynamicVectorClass<ParasiteClass*>;

// FUNCTION: GAMEMD 0x0063DB60
// DynamicVectorClass<PlanningMemberClass*> -- vtable 0x007EFEE4 slot 3; locator 0x00808070 -> type descriptor 0x00836A98
//   `.?AV?$DynamicVectorClass@PAVPlanningMemberClass@@@@`.
template class DynamicVectorClass<PlanningMemberClass*>;

// FUNCTION: GAMEMD 0x0063DBC0
// DynamicVectorClass<PlanningBranchClass*> -- vtable 0x007EFEC4 slot 3; locator 0x00808008 -> type descriptor 0x00836A20
//   `.?AV?$DynamicVectorClass@PAVPlanningBranchClass@@@@`.
template class DynamicVectorClass<PlanningBranchClass*>;

// FUNCTION: GAMEMD 0x0063DC20
// DynamicVectorClass<PlanningNodeClass*> -- vtable 0x007EFE44 slot 3; locator 0x00807ED8 -> type descriptor 0x00836930
//   `.?AV?$DynamicVectorClass@PAVPlanningNodeClass@@@@`.
template class DynamicVectorClass<PlanningNodeClass*>;

// FUNCTION: GAMEMD 0x0063DC80
// DynamicVectorClass<EventClass*> -- vtable 0x007EFE04 slot 3; locator 0x00807E40 -> type descriptor 0x008368C0
//   `.?AV?$DynamicVectorClass@PAVEventClass@@@@`.
template class DynamicVectorClass<EventClass*>;

// FUNCTION: GAMEMD 0x0063DCE0
// DynamicVectorClass<PlanningTokenClass*> -- vtable 0x007EFE84 slot 3; locator 0x00807F70 -> type descriptor 0x008369A8
//   `.?AV?$DynamicVectorClass@PAVPlanningTokenClass@@@@`.
template class DynamicVectorClass<PlanningTokenClass*>;

// FUNCTION: GAMEMD 0x00658890
// DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass*>> -- vtable 0x007F042C slot 3; locator 0x00808458 -> type descriptor 0x00839438
//   `.?AV?$DynamicVectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@`.
template class DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass*> >;

// FUNCTION: GAMEMD 0x0065A1E0
// DynamicVectorClass<RadBeam*> -- vtable 0x007F0484 slot 3; locator 0x008084C0 -> type descriptor 0x00839568
//   `.?AV?$DynamicVectorClass@PAVRadBeam@@@@`.
template class DynamicVectorClass<RadBeam*>;

// FUNCTION: GAMEMD 0x0065BEF0
// DynamicVectorClass<RadSiteClass*> -- vtable 0x007F07A4 slot 3; locator 0x008085F8 -> type descriptor 0x008395C8
//   `.?AV?$DynamicVectorClass@PAVRadSiteClass@@@@`.
template class DynamicVectorClass<RadSiteClass*>;

// FUNCTION: GAMEMD 0x00660C80
// DynamicVectorClass<RadarEventClass*> -- vtable 0x007F0AAC slot 3; locator 0x00808870 -> type descriptor 0x00839958
//   `.?AV?$DynamicVectorClass@PAVRadarEventClass@@@@`.
template class DynamicVectorClass<RadarEventClass*>;

// FUNCTION: GAMEMD 0x006647B0
// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*> -- vtable 0x007F0C2C slot 3; locator 0x008089D0 -> type descriptor 0x00839A40
//   `.?AV?$DynamicVectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@`.
template class DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*>;

// FUNCTION: GAMEMD 0x0069C4A0
// TypeList<DiskID> -- vtable 0x007F12D4 slot 3; locator 0x00809320 -> type descriptor 0x0083F5B0
//   `.?AV?$TypeList@W4DiskID@@@@`.
//   CAUTION: this is the only address in the family whose slot-3 owner is
//   not a DynamicVectorClass table. `DynamicVectorClass<DiskID>` is one of
//   the sweep's 34 type descriptors with no locator, so the base has no
//   vtable of its own and this copy is reachable only through the derived
//   table. The element type `DiskID` is certain either way; whether the
//   declaring class is the base or the derived one is not, so no claim is
//   made beyond the element.
template struct CountedVector<DiskID>;
typedef CountedVector<DiskID> GgCountedDiskIDRep;
GG_STATIC_ASSERT(offsetof(GgCountedDiskIDRep, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgCountedDiskIDRep, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgCountedDiskIDRep, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgCountedDiskIDRep, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(GgCountedDiskIDRep) == 0x14);

// FUNCTION: GAMEMD 0x0069C5A0
// DynamicVectorClass<MultiMission*> -- vtable 0x007F11F4 slot 3; locator 0x00809130 -> type descriptor 0x0083EE00
//   `.?AV?$DynamicVectorClass@PAVMultiMission@@@@`.
template class DynamicVectorClass<MultiMission*>;

// FUNCTION: GAMEMD 0x0069C600
// DynamicVectorClass<GlobalPacketType*> -- vtable 0x007F11D4 slot 3; locator 0x00809198 -> type descriptor 0x0083EE70
//   `.?AV?$DynamicVectorClass@PAUGlobalPacketType@@@@`.
template class DynamicVectorClass<GlobalPacketType*>;

// FUNCTION: GAMEMD 0x0069C660
// DynamicVectorClass<PhoneEntryClass*> -- vtable 0x007F11B4 slot 3; locator 0x008090C8 -> type descriptor 0x0083ED98
//   `.?AV?$DynamicVectorClass@PAVPhoneEntryClass@@@@`.
template class DynamicVectorClass<PhoneEntryClass*>;

// FUNCTION: GAMEMD 0x006B13B0
// DynamicVectorClass<SlaveManagerClass::SlaveControl*> -- vtable 0x007F322C slot 3; locator 0x00809768 -> type descriptor 0x0083FD70
//   `.?AV?$DynamicVectorClass@PAUSlaveControl@SlaveManagerClass@@@@`.
template class DynamicVectorClass<SlaveManagerClass::SlaveControl*>;

// FUNCTION: GAMEMD 0x006B1410
// DynamicVectorClass<SlaveManagerClass*> -- vtable 0x007F315C slot 3; locator 0x00809620 -> type descriptor 0x0083FCD0
//   `.?AV?$DynamicVectorClass@PAVSlaveManagerClass@@@@`.
template class DynamicVectorClass<SlaveManagerClass*>;

// FUNCTION: GAMEMD 0x006B43B0
// DynamicVectorClass<UndoInfoStruct> -- vtable 0x007F327C slot 3; locator 0x00809800 -> type descriptor 0x0083FFA0
//   `.?AV?$DynamicVectorClass@UUndoInfoStruct@@@@`.
template class DynamicVectorClass<UndoInfoStruct>;

// FUNCTION: GAMEMD 0x006B8160
// DynamicVectorClass<SpawnManagerClass::SpawnControl*> -- vtable 0x007F36B4 slot 3; locator 0x00809B50 -> type descriptor 0x00840180
//   `.?AV?$DynamicVectorClass@PAUSpawnControl@SpawnManagerClass@@@@`.
template class DynamicVectorClass<SpawnManagerClass::SpawnControl*>;

// FUNCTION: GAMEMD 0x006B81C0
// DynamicVectorClass<SpawnManagerClass*> -- vtable 0x007F35E4 slot 3; locator 0x00809A08 -> type descriptor 0x008400E0
//   `.?AV?$DynamicVectorClass@PAVSpawnManagerClass@@@@`.
template class DynamicVectorClass<SpawnManagerClass*>;

// FUNCTION: GAMEMD 0x006BED50
// DynamicVectorClass<unsigned long> -- vtable 0x007F3728 slot 3; locator 0x00809BE8 -> type descriptor 0x00840AA8
//   `.?AV?$DynamicVectorClass@K@@`.
template class DynamicVectorClass<unsigned long>;

// FUNCTION: GAMEMD 0x006CF4F0
// DynamicVectorClass<SwizzlePointerClass> -- vtable 0x007F4134 slot 3; locator 0x0080B798 -> type descriptor 0x00842790
//   `.?AV?$DynamicVectorClass@VSwizzlePointerClass@@@@`.
template class DynamicVectorClass<SwizzlePointerClass>;

// FUNCTION: GAMEMD 0x006DC4E0
// DynamicVectorClass<DirtyAreaStruct> -- vtable 0x007F429C slot 3; locator 0x0080B830 -> type descriptor 0x00842988
//   `.?AV?$DynamicVectorClass@UDirtyAreaStruct@@@@`.
template class DynamicVectorClass<DirtyAreaStruct>;

// FUNCTION: GAMEMD 0x007212B0
// DynamicVectorClass<ThemeControl*> -- vtable 0x007F568C slot 3; locator 0x0080C688 -> type descriptor 0x00844780
//   `.?AV?$DynamicVectorClass@PAUThemeControl@@@@`.
template class DynamicVectorClass<ThemeControl*>;

// FUNCTION: GAMEMD 0x00769CD0
// DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*> -- vtable 0x007F7144 slot 3; locator 0x0080DEC8 -> type descriptor 0x00848930
//   `.?AV?$DynamicVectorClass@PAUAnimationPalette@Map@WorldDominationTour@@@@`.
template class DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*>;

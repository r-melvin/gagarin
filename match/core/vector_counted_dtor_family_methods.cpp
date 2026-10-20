// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x477840 and its 160
//   siblings.
//
//   One class template, 161 explicit instantiations. Each
//   `template struct CountedVector<T>;` below makes the compiler generate the
//   plain destructor `?Destroy@?$CountedVector@<T>@@QAEXXZ`, whose 0x2A bytes
//   are the retail function at the annotated address: clear the count,
//   release the element block if this vector owns one, then clear the rest of
//   the bookkeeping.
//
//   THE ELEMENT TYPES ARE NOW RTTI-CONFIRMED; THE TEMPLATE NAME IS STILL A
//   PLACEHOLDER. This body stores no vtable, so it is bound by vtable
//   membership: each address occupies slot 3 of a retail vtable whose
//   complete object locator names the class. 160 of the 161 come out
//   `DynamicVectorClass<T>` -- which is what the extra store at +0x10 is, the
//   element count this family was named for. Twelve of those sit at slot 3 of
//   *two* tables, `DynamicVectorClass<T>` and its derived `TypeList<T>`; the
//   base is where the slot is declared (batch fifty-seven), and the base
//   chains in the sweep confirm `TypeList<T> : DynamicVectorClass<T> :
//   VectorClass<T>`. The one remaining address is noted where it appears.
//   161 addresses, 161 distinct element types, one-to-one -- the `const`
//   variants are distinct instantiations, which is why the count is 161 and
//   not the 147 a const-dropping demangler reports.
//
//   The enclosing name stays `CountedVector`: retail's symbol is
//   `??1?$DynamicVectorClass@<T>@@UAE@XZ`, but spelling it as the class's own
//   virtual destructor does not compile to these bytes (VC6 puts a vptr store
//   at the head of a virtual destructor; retail's body has none). It is a
//   modelling stand-in for `DynamicVectorClass<T>::~DynamicVectorClass`,
//   recorded as such rather than asserted as a retail name.
//
//   KNOWN LIMITATION -- staging ground, not a destination: MSVC6 emits each
//   template instantiation as a COMDAT into the translation unit that
//   instantiated it, so these 161 instantiations belong to many different
//   original Westwood translation units. One sweep file is right for matching
//   bytes now and wrong for retail's eventual link order.
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

// FUNCTION: GAMEMD 0x00477840
// DynamicVectorClass<int> -- vtable 0x007E4E78 slot 3; locator 0x007FCFC8 -> type descriptor 0x0081C058
//   `.?AV?$DynamicVectorClass@H@@`.
//   The same body also sits at that slot in TypeList<int> (0x007E4DD8); DynamicVectorClass<int> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<int>;

// Layout asserted on the first instantiation; every instantiation in this
// family has the same layout, because the only member whose type varies is a
// pointer. The assert has to follow an explicit instantiation: VC6 fails to
// re-parse the template body when offsetof is what first instantiates it, and
// it will not take a template-id as offsetof's first argument either, hence
// the typedef.
typedef CountedVector<int> GgCountedVectorRep;
GG_STATIC_ASSERT(offsetof(GgCountedVectorRep, Items)       == 0x4);
GG_STATIC_ASSERT(offsetof(GgCountedVectorRep, Capacity)    == 0x8);
GG_STATIC_ASSERT(offsetof(GgCountedVectorRep, IsAllocated) == 0xD);
GG_STATIC_ASSERT(offsetof(GgCountedVectorRep, Count)       == 0x10);
GG_STATIC_ASSERT(sizeof(GgCountedVectorRep)                == 0x14);

// FUNCTION: GAMEMD 0x004778A0
// DynamicVectorClass<TechnoTypeClass*> -- vtable 0x007E858C slot 3; locator 0x008000E0 -> type descriptor 0x0081C0D8
//   `.?AV?$DynamicVectorClass@PAVTechnoTypeClass@@@@`.
//   The same body also sits at that slot in TypeList<TechnoTypeClass*> (0x007E4E18); DynamicVectorClass<TechnoTypeClass*> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<TechnoTypeClass*>;

// FUNCTION: GAMEMD 0x00477900
// DynamicVectorClass<RGBClass> -- vtable 0x007F022C slot 3; locator 0x00808328 -> type descriptor 0x0081C140
//   `.?AV?$DynamicVectorClass@VRGBClass@@@@`.
//   The same body also sits at that slot in TypeList<RGBClass> (0x007E4E58); DynamicVectorClass<RGBClass> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<RGBClass>;

// FUNCTION: GAMEMD 0x0048AD10
// DynamicVectorClass<DamageGroup*> -- vtable 0x007E5170 slot 3; locator 0x007FD240 -> type descriptor 0x0081D198
//   `.?AV?$DynamicVectorClass@PAUDamageGroup@@@@`.
template struct CountedVector<DamageGroup*>;

// FUNCTION: GAMEMD 0x00491390
// DynamicVectorClass<ConvertClass*> -- vtable 0x007E5318 slot 3; locator 0x007FD370 -> type descriptor 0x0081DC60
//   `.?AV?$DynamicVectorClass@PAVConvertClass@@@@`.
template struct CountedVector<ConvertClass*>;

// FUNCTION: GAMEMD 0x0049E950
// DynamicVectorClass<char*> -- vtable 0x007E5BC4 slot 3; locator 0x007FF560 -> type descriptor 0x0081F260
//   `.?AV?$DynamicVectorClass@PAD@@`.
template struct CountedVector<char*>;

// FUNCTION: GAMEMD 0x0049E9B0
// DynamicVectorClass<DynamicVectorClass<char*>*> -- vtable 0x007E5BE4 slot 3; locator 0x007FF5C8 -> type descriptor 0x0081F2C8
//   `.?AV?$DynamicVectorClass@PAV?$DynamicVectorClass@PAD@@@@`.
template struct CountedVector<DynamicVectorClass<char*>*>;

// FUNCTION: GAMEMD 0x004A0EB0
// DynamicVectorClass<tagCONNECTDATA> -- vtable 0x007E5CC4 slot 3; locator 0x007FF790 -> type descriptor 0x0081F670
//   `.?AV?$DynamicVectorClass@UtagCONNECTDATA@@@@`.
template struct CountedVector<tagCONNECTDATA>;

// FUNCTION: GAMEMD 0x004A0F20
// DynamicVectorClass<IConnectionPoint*> -- vtable 0x007E5D48 slot 3; locator 0x007FF8F8 -> type descriptor 0x0081F778
//   `.?AV?$DynamicVectorClass@PAUIConnectionPoint@@@@`.
template struct CountedVector<IConnectionPoint*>;

// FUNCTION: GAMEMD 0x004A4AD0
// DynamicVectorClass<_DDSURFACEDESC*> -- vtable 0x007E5E0C slot 3; locator 0x007FFA50 -> type descriptor 0x0081FED0
//   `.?AV?$DynamicVectorClass@PAU_DDSURFACEDESC@@@@`.
template struct CountedVector<_DDSURFACEDESC*>;

// FUNCTION: GAMEMD 0x004A7D20
// DynamicVectorClass<DiskLaserClass*> -- vtable 0x007E5EDC slot 3; locator 0x007FFB10 -> type descriptor 0x0081FF58
//   `.?AV?$DynamicVectorClass@PAVDiskLaserClass@@@@`.
template struct CountedVector<DiskLaserClass*>;

// FUNCTION: GAMEMD 0x004B9BE0
// DynamicVectorClass<ButtonFadeEffect*> -- vtable 0x007E856C slot 3; locator 0x00800210 -> type descriptor 0x00820458
//   `.?AV?$DynamicVectorClass@PAUButtonFadeEffect@@@@`.
template struct CountedVector<ButtonFadeEffect*>;

// FUNCTION: GAMEMD 0x004B9C40
// DynamicVectorClass<CrossDissolveEffect*> -- vtable 0x007E854C slot 3; locator 0x00800178 -> type descriptor 0x008203E0
//   `.?AV?$DynamicVectorClass@PAUCrossDissolveEffect@@@@`.
template struct CountedVector<CrossDissolveEffect*>;

// FUNCTION: GAMEMD 0x004C2C40
// DynamicVectorClass<EBolt*> -- vtable 0x007E868C slot 3; locator 0x008002C8 -> type descriptor 0x00820738
//   `.?AV?$DynamicVectorClass@PAVEBolt@@@@`.
template struct CountedVector<EBolt*>;

// FUNCTION: GAMEMD 0x004C49A0
// DynamicVectorClass<EgoClass*> -- vtable 0x007E86DC slot 3; locator 0x00800360 -> type descriptor 0x008207A8
//   `.?AV?$DynamicVectorClass@PAVEgoClass@@@@`.
template struct CountedVector<EgoClass*>;

// FUNCTION: GAMEMD 0x004C5B60
// DynamicVectorClass<EMPulseClass*> -- vtable 0x007E873C slot 3; locator 0x008003F8 -> type descriptor 0x00820898
//   `.?AV?$DynamicVectorClass@PAVEMPulseClass@@@@`.
template struct CountedVector<EMPulseClass*>;

// FUNCTION: GAMEMD 0x004CA890
// DynamicVectorClass<const TechnoTypeClass*> -- vtable 0x007E8934 slot 3; locator 0x00800540 -> type descriptor 0x00822258
//   `.?AV?$DynamicVectorClass@PBVTechnoTypeClass@@@@`.
template struct CountedVector<const TechnoTypeClass*>;

// FUNCTION: GAMEMD 0x004D2930
// DynamicVectorClass<FoggedObjectClass::DrawRecord> -- vtable 0x007E8BA0 slot 3; locator 0x008007D0 -> type descriptor 0x00822498
//   `.?AV?$DynamicVectorClass@UDrawRecord@FoggedObjectClass@@@@`.
template struct CountedVector<FoggedObjectClass::DrawRecord>;

// FUNCTION: GAMEMD 0x004E0190
// DynamicVectorClass<AbstractClass*> -- vtable 0x007E91EC slot 3; locator 0x008009B0 -> type descriptor 0x008225E8
//   `.?AV?$DynamicVectorClass@PAVAbstractClass@@@@`.
template struct CountedVector<AbstractClass*>;

// FUNCTION: GAMEMD 0x004E01F0
// DynamicVectorClass<FootClass*> -- vtable 0x007E8C28 slot 3; locator 0x00800868 -> type descriptor 0x00822580
//   `.?AV?$DynamicVectorClass@PAVFootClass@@@@`.
template struct CountedVector<FootClass*>;

// FUNCTION: GAMEMD 0x004E8290
// DynamicVectorClass<TagClass*> -- vtable 0x007EA5A4 slot 3; locator 0x008024B0 -> type descriptor 0x00823FA0
//   `.?AV?$DynamicVectorClass@PAVTagClass@@@@`.
template struct CountedVector<TagClass*>;

// FUNCTION: GAMEMD 0x004E82F0
// DynamicVectorClass<BuildingClass*> -- vtable 0x007E9E24 slot 3; locator 0x00801280 -> type descriptor 0x00823270
//   `.?AV?$DynamicVectorClass@PAVBuildingClass@@@@`.
template struct CountedVector<BuildingClass*>;

// FUNCTION: GAMEMD 0x004E8350
// DynamicVectorClass<SuperClass*> -- vtable 0x007EA4E4 slot 3; locator 0x00802288 -> type descriptor 0x00823E28
//   `.?AV?$DynamicVectorClass@PAVSuperClass@@@@`.
template struct CountedVector<SuperClass*>;

// FUNCTION: GAMEMD 0x004E83B0
// DynamicVectorClass<AITriggerTypeClass*> -- vtable 0x007E9B64 slot 3; locator 0x00800BF8 -> type descriptor 0x00822DC0
//   `.?AV?$DynamicVectorClass@PAVAITriggerTypeClass@@@@`.
template struct CountedVector<AITriggerTypeClass*>;

// FUNCTION: GAMEMD 0x004E8410
// DynamicVectorClass<BuildingLightClass*> -- vtable 0x007E9C24 slot 3; locator 0x00800DC0 -> type descriptor 0x00822F18
//   `.?AV?$DynamicVectorClass@PAVBuildingLightClass@@@@`.
template struct CountedVector<BuildingLightClass*>;

// FUNCTION: GAMEMD 0x004E8470
// DynamicVectorClass<ParticleClass*> -- vtable 0x007E9D64 slot 3; locator 0x008010B8 -> type descriptor 0x00823138
//   `.?AV?$DynamicVectorClass@PAVParticleClass@@@@`.
template struct CountedVector<ParticleClass*>;

// FUNCTION: GAMEMD 0x004E84D0
// DynamicVectorClass<TeamClass*> -- vtable 0x007E9F64 slot 3; locator 0x00801578 -> type descriptor 0x00823478
//   `.?AV?$DynamicVectorClass@PAVTeamClass@@@@`.
template struct CountedVector<TeamClass*>;

// FUNCTION: GAMEMD 0x004E8540
// DynamicVectorClass<TriggerClass*> -- vtable 0x007E9BE4 slot 3; locator 0x00800D28 -> type descriptor 0x00822EA8
//   `.?AV?$DynamicVectorClass@PAVTriggerClass@@@@`.
template struct CountedVector<TriggerClass*>;

// FUNCTION: GAMEMD 0x004E85A0
// DynamicVectorClass<TriggerTypeClass*> -- vtable 0x007E9BA4 slot 3; locator 0x00800C90 -> type descriptor 0x00822E38
//   `.?AV?$DynamicVectorClass@PAVTriggerTypeClass@@@@`.
template struct CountedVector<TriggerTypeClass*>;

// FUNCTION: GAMEMD 0x004E8600
// DynamicVectorClass<TubeClass*> -- vtable 0x007E9CA4 slot 3; locator 0x00800EF0 -> type descriptor 0x00823000
//   `.?AV?$DynamicVectorClass@PAVTubeClass@@@@`.
template struct CountedVector<TubeClass*>;

// FUNCTION: GAMEMD 0x004E8660
// DynamicVectorClass<ParticleSystemClass*> -- vtable 0x007E9C64 slot 3; locator 0x00800E58 -> type descriptor 0x00822F90
//   `.?AV?$DynamicVectorClass@PAVParticleSystemClass@@@@`.
template struct CountedVector<ParticleSystemClass*>;

// FUNCTION: GAMEMD 0x004E86C0
// DynamicVectorClass<WaveClass*> -- vtable 0x007E9CE4 slot 3; locator 0x00800F88 -> type descriptor 0x00823068
//   `.?AV?$DynamicVectorClass@PAVWaveClass@@@@`.
template struct CountedVector<WaveClass*>;

// FUNCTION: GAMEMD 0x004E8720
// DynamicVectorClass<OverlayClass*> -- vtable 0x007E9D24 slot 3; locator 0x00801020 -> type descriptor 0x008230D0
//   `.?AV?$DynamicVectorClass@PAVOverlayClass@@@@`.
template struct CountedVector<OverlayClass*>;

// FUNCTION: GAMEMD 0x004E8780
// DynamicVectorClass<SmudgeClass*> -- vtable 0x007E9DA4 slot 3; locator 0x00801150 -> type descriptor 0x008231A0
//   `.?AV?$DynamicVectorClass@PAVSmudgeClass@@@@`.
template struct CountedVector<SmudgeClass*>;

// FUNCTION: GAMEMD 0x004E87E0
// DynamicVectorClass<TerrainClass*> -- vtable 0x007E9DE4 slot 3; locator 0x008011E8 -> type descriptor 0x00823208
//   `.?AV?$DynamicVectorClass@PAVTerrainClass@@@@`.
template struct CountedVector<TerrainClass*>;

// FUNCTION: GAMEMD 0x004E8840
// DynamicVectorClass<AircraftClass*> -- vtable 0x007E9E64 slot 3; locator 0x00801318 -> type descriptor 0x008232D8
//   `.?AV?$DynamicVectorClass@PAVAircraftClass@@@@`.
template struct CountedVector<AircraftClass*>;

// FUNCTION: GAMEMD 0x004E88A0
// DynamicVectorClass<UnitClass*> -- vtable 0x007E9EA4 slot 3; locator 0x008013B0 -> type descriptor 0x00823340
//   `.?AV?$DynamicVectorClass@PAVUnitClass@@@@`.
template struct CountedVector<UnitClass*>;

// FUNCTION: GAMEMD 0x004E8900
// DynamicVectorClass<HouseClass*> -- vtable 0x007E9EE4 slot 3; locator 0x00801448 -> type descriptor 0x008233A8
//   `.?AV?$DynamicVectorClass@PAVHouseClass@@@@`.
template struct CountedVector<HouseClass*>;

// FUNCTION: GAMEMD 0x004E8960
// DynamicVectorClass<AnimClass*> -- vtable 0x007E9F24 slot 3; locator 0x008014E0 -> type descriptor 0x00823410
//   `.?AV?$DynamicVectorClass@PAVAnimClass@@@@`.
template struct CountedVector<AnimClass*>;

// FUNCTION: GAMEMD 0x004E89C0
// DynamicVectorClass<FactoryClass*> -- vtable 0x007E9FA4 slot 3; locator 0x00801610 -> type descriptor 0x008234E0
//   `.?AV?$DynamicVectorClass@PAVFactoryClass@@@@`.
template struct CountedVector<FactoryClass*>;

// FUNCTION: GAMEMD 0x004E8A20
// DynamicVectorClass<CampaignClass*> -- vtable 0x007E9FE4 slot 3; locator 0x008016A8 -> type descriptor 0x00823548
//   `.?AV?$DynamicVectorClass@PAVCampaignClass@@@@`.
template struct CountedVector<CampaignClass*>;

// FUNCTION: GAMEMD 0x004E8A80
// DynamicVectorClass<SideClass*> -- vtable 0x007EA024 slot 3; locator 0x00801740 -> type descriptor 0x008235B0
//   `.?AV?$DynamicVectorClass@PAVSideClass@@@@`.
template struct CountedVector<SideClass*>;

// FUNCTION: GAMEMD 0x004E8AE0
// DynamicVectorClass<HouseTypeClass*> -- vtable 0x007EA064 slot 3; locator 0x008017D8 -> type descriptor 0x00823618
//   `.?AV?$DynamicVectorClass@PAVHouseTypeClass@@@@`.
template struct CountedVector<HouseTypeClass*>;

// FUNCTION: GAMEMD 0x004E8B40
// DynamicVectorClass<TaskForceClass*> -- vtable 0x007EA0A4 slot 3; locator 0x00801870 -> type descriptor 0x00823680
//   `.?AV?$DynamicVectorClass@PAVTaskForceClass@@@@`.
template struct CountedVector<TaskForceClass*>;

// FUNCTION: GAMEMD 0x004E8BA0
// DynamicVectorClass<TeamTypeClass*> -- vtable 0x007EA0E4 slot 3; locator 0x00801908 -> type descriptor 0x008236E8
//   `.?AV?$DynamicVectorClass@PAVTeamTypeClass@@@@`.
template struct CountedVector<TeamTypeClass*>;

// FUNCTION: GAMEMD 0x004E8C00
// DynamicVectorClass<ScriptTypeClass*> -- vtable 0x007EA124 slot 3; locator 0x008019A0 -> type descriptor 0x00823758
//   `.?AV?$DynamicVectorClass@PAVScriptTypeClass@@@@`.
template struct CountedVector<ScriptTypeClass*>;

// FUNCTION: GAMEMD 0x004E8C60
// DynamicVectorClass<OverlayTypeClass*> -- vtable 0x007EA164 slot 3; locator 0x00801A38 -> type descriptor 0x008237C8
//   `.?AV?$DynamicVectorClass@PAVOverlayTypeClass@@@@`.
template struct CountedVector<OverlayTypeClass*>;

// FUNCTION: GAMEMD 0x004E8CC0
// DynamicVectorClass<SmudgeTypeClass*> -- vtable 0x007EA1A4 slot 3; locator 0x00801AD0 -> type descriptor 0x00823840
//   `.?AV?$DynamicVectorClass@PAVSmudgeTypeClass@@@@`.
template struct CountedVector<SmudgeTypeClass*>;

// FUNCTION: GAMEMD 0x004E8D20
// DynamicVectorClass<TerrainTypeClass*> -- vtable 0x007EA1E4 slot 3; locator 0x00801B68 -> type descriptor 0x008238B0
//   `.?AV?$DynamicVectorClass@PAVTerrainTypeClass@@@@`.
template struct CountedVector<TerrainTypeClass*>;

// FUNCTION: GAMEMD 0x004E8D80
// DynamicVectorClass<BuildingTypeClass*> -- vtable 0x007EA224 slot 3; locator 0x00801C00 -> type descriptor 0x00823928
//   `.?AV?$DynamicVectorClass@PAVBuildingTypeClass@@@@`.
template struct CountedVector<BuildingTypeClass*>;

// FUNCTION: GAMEMD 0x004E8DE0
// DynamicVectorClass<AircraftTypeClass*> -- vtable 0x007EA264 slot 3; locator 0x00801C98 -> type descriptor 0x008239A0
//   `.?AV?$DynamicVectorClass@PAVAircraftTypeClass@@@@`.
template struct CountedVector<AircraftTypeClass*>;

// FUNCTION: GAMEMD 0x004E8E40
// DynamicVectorClass<UnitTypeClass*> -- vtable 0x007EA2A4 slot 3; locator 0x00801D30 -> type descriptor 0x00823A10
//   `.?AV?$DynamicVectorClass@PAVUnitTypeClass@@@@`.
template struct CountedVector<UnitTypeClass*>;

// FUNCTION: GAMEMD 0x004E8EA0
// DynamicVectorClass<AnimTypeClass*> -- vtable 0x007EA2E4 slot 3; locator 0x00801DC8 -> type descriptor 0x00823A78
//   `.?AV?$DynamicVectorClass@PAVAnimTypeClass@@@@`.
template struct CountedVector<AnimTypeClass*>;

// FUNCTION: GAMEMD 0x004E8F00
// DynamicVectorClass<InfantryTypeClass*> -- vtable 0x007EA324 slot 3; locator 0x00801E60 -> type descriptor 0x00823AE8
//   `.?AV?$DynamicVectorClass@PAVInfantryTypeClass@@@@`.
template struct CountedVector<InfantryTypeClass*>;

// FUNCTION: GAMEMD 0x004E8F60
// DynamicVectorClass<BulletTypeClass*> -- vtable 0x007EA364 slot 3; locator 0x00801EF8 -> type descriptor 0x00823B60
//   `.?AV?$DynamicVectorClass@PAVBulletTypeClass@@@@`.
template struct CountedVector<BulletTypeClass*>;

// FUNCTION: GAMEMD 0x004E8FC0
// DynamicVectorClass<VoxelAnimTypeClass*> -- vtable 0x007EA3A4 slot 3; locator 0x00801F90 -> type descriptor 0x00823BD0
//   `.?AV?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@`.
template struct CountedVector<VoxelAnimTypeClass*>;

// FUNCTION: GAMEMD 0x004E9020
// DynamicVectorClass<IsometricTileTypeClass*> -- vtable 0x007EA3E4 slot 3; locator 0x00802028 -> type descriptor 0x00823C48
//   `.?AV?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@`.
template struct CountedVector<IsometricTileTypeClass*>;

// FUNCTION: GAMEMD 0x004E9080
// DynamicVectorClass<ParticleTypeClass*> -- vtable 0x007EA424 slot 3; locator 0x008020C0 -> type descriptor 0x00823CC0
//   `.?AV?$DynamicVectorClass@PAVParticleTypeClass@@@@`.
template struct CountedVector<ParticleTypeClass*>;

// FUNCTION: GAMEMD 0x004E90E0
// DynamicVectorClass<ParticleSystemTypeClass*> -- vtable 0x007EA464 slot 3; locator 0x00802158 -> type descriptor 0x00823D40
//   `.?AV?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@`.
template struct CountedVector<ParticleSystemTypeClass*>;

// FUNCTION: GAMEMD 0x004E9140
// DynamicVectorClass<SuperWeaponTypeClass*> -- vtable 0x007EA4A4 slot 3; locator 0x008021F0 -> type descriptor 0x00823DB8
//   `.?AV?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@`.
template struct CountedVector<SuperWeaponTypeClass*>;

// FUNCTION: GAMEMD 0x004E91A0
// DynamicVectorClass<AbstractTypeClass*> -- vtable 0x007EA524 slot 3; locator 0x00802320 -> type descriptor 0x00823E98
//   `.?AV?$DynamicVectorClass@PAVAbstractTypeClass@@@@`.
template struct CountedVector<AbstractTypeClass*>;

// FUNCTION: GAMEMD 0x004F2850
// DynamicVectorClass<GraphicMenuItem*> -- vtable 0x007EA604 slot 3; locator 0x00802578 -> type descriptor 0x00824138
//   `.?AV?$DynamicVectorClass@PAVGraphicMenuItem@@@@`.
template struct CountedVector<GraphicMenuItem*>;

// FUNCTION: GAMEMD 0x0050E4A0
// DynamicVectorClass<const BuildingTypeClass*> -- vtable 0x007EAA28 slot 3; locator 0x00802D38 -> type descriptor 0x00824D10
//   `.?AV?$DynamicVectorClass@PBVBuildingTypeClass@@@@`.
//   The same body also sits at that slot in TypeList<BuildingTypeClass*> (0x007ED90C); DynamicVectorClass<const BuildingTypeClass*> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<const BuildingTypeClass*>;

// FUNCTION: GAMEMD 0x0050E500
// DynamicVectorClass<HouseClass::StartingTechnoStruct*> -- vtable 0x007EA944 slot 3; locator 0x00802B60 -> type descriptor 0x00824638
//   `.?AV?$DynamicVectorClass@PAUStartingTechnoStruct@HouseClass@@@@`.
template struct CountedVector<HouseClass::StartingTechnoStruct*>;

// FUNCTION: GAMEMD 0x0050E560
// DynamicVectorClass<AngerStruct> -- vtable 0x007EA924 slot 3; locator 0x00802AF8 -> type descriptor 0x008245B8
//   `.?AV?$DynamicVectorClass@UAngerStruct@@@@`.
template struct CountedVector<AngerStruct>;

// FUNCTION: GAMEMD 0x0050E5D0
// DynamicVectorClass<ScoutStruct> -- vtable 0x007EA904 slot 3; locator 0x00802A90 -> type descriptor 0x00824550
//   `.?AV?$DynamicVectorClass@UScoutStruct@@@@`.
template struct CountedVector<ScoutStruct>;

// FUNCTION: GAMEMD 0x0050E640
// DynamicVectorClass<HouseClass::BuildChoiceClass*> -- vtable 0x007EA7B4 slot 3; locator 0x00802858 -> type descriptor 0x00824458
//   `.?AV?$DynamicVectorClass@PAUBuildChoiceClass@HouseClass@@@@`.
template struct CountedVector<HouseClass::BuildChoiceClass*>;

// FUNCTION: GAMEMD 0x0050E6A0
// DynamicVectorClass<const TeamTypeClass*> -- vtable 0x007EAAE8 slot 3; locator 0x00802EA0 -> type descriptor 0x008246B0
//   `.?AV?$DynamicVectorClass@PBVTeamTypeClass@@@@`.
//   The same body also sits at that slot in TypeList<TeamTypeClass*> (0x007EA9C4); DynamicVectorClass<const TeamTypeClass*> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<const TeamTypeClass*>;

// FUNCTION: GAMEMD 0x0050E700
// DynamicVectorClass<bool> -- vtable 0x007EAA7C slot 3; locator 0x00802DD0 -> type descriptor 0x00824E90
//   `.?AV?$DynamicVectorClass@_N@@`.
template struct CountedVector<bool>;

// FUNCTION: GAMEMD 0x005128A0
// DynamicVectorClass<const InfantryTypeClass*> -- vtable 0x007EAC88 slot 3; locator 0x008031A0 -> type descriptor 0x008251F8
//   `.?AV?$DynamicVectorClass@PBVInfantryTypeClass@@@@`.
//   The same body also sits at that slot in TypeList<InfantryTypeClass*> (0x007EAC08); DynamicVectorClass<const InfantryTypeClass*> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<const InfantryTypeClass*>;

// FUNCTION: GAMEMD 0x00512900
// DynamicVectorClass<const UnitTypeClass*> -- vtable 0x007EACA8 slot 3; locator 0x008031D8 -> type descriptor 0x00825158
//   `.?AV?$DynamicVectorClass@PBVUnitTypeClass@@@@`.
//   The same body also sits at that slot in TypeList<UnitTypeClass*> (0x007EABE8); DynamicVectorClass<const UnitTypeClass*> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<const UnitTypeClass*>;

// FUNCTION: GAMEMD 0x00512990
// DynamicVectorClass<const AircraftTypeClass*> -- vtable 0x007EACC8 slot 3; locator 0x00803210 -> type descriptor 0x008250B8
//   `.?AV?$DynamicVectorClass@PBVAircraftTypeClass@@@@`.
//   The same body also sits at that slot in TypeList<AircraftTypeClass*> (0x007EABC8); DynamicVectorClass<const AircraftTypeClass*> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<const AircraftTypeClass*>;

// FUNCTION: GAMEMD 0x00524ED0
// DynamicVectorClass<const AnimTypeClass*> -- vtable 0x007EB714 slot 3; locator 0x00803560 -> type descriptor 0x00825848
//   `.?AV?$DynamicVectorClass@PBVAnimTypeClass@@@@`.
//   The same body also sits at that slot in TypeList<AnimTypeClass*> (0x007EB6D4); DynamicVectorClass<const AnimTypeClass*> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<const AnimTypeClass*>;

// FUNCTION: GAMEMD 0x005384C0
// DynamicVectorClass<CCINIClass*> -- vtable 0x007EB82C slot 3; locator 0x00803840 -> type descriptor 0x008261E8
//   `.?AV?$DynamicVectorClass@PAVCCINIClass@@@@`.
template struct CountedVector<CCINIClass*>;

// FUNCTION: GAMEMD 0x0053C4C0
// DynamicVectorClass<const AnimClass*> -- vtable 0x007EBFCC slot 3; locator 0x008047B8 -> type descriptor 0x00828000
//   `.?AV?$DynamicVectorClass@PBVAnimClass@@@@`.
template struct CountedVector<const AnimClass*>;

// FUNCTION: GAMEMD 0x0053DA40
// DynamicVectorClass<IonBlastClass*> -- vtable 0x007EC05C slot 3; locator 0x00804850 -> type descriptor 0x00828100
//   `.?AV?$DynamicVectorClass@PAVIonBlastClass@@@@`.
template struct CountedVector<IonBlastClass*>;

// FUNCTION: GAMEMD 0x0054A190
// DynamicVectorClass<unsigned short*> -- vtable 0x007ECCEC slot 3; locator 0x00804C28 -> type descriptor 0x00829110
//   `.?AV?$DynamicVectorClass@PAG@@`.
template struct CountedVector<unsigned short*>;

// FUNCTION: GAMEMD 0x0054A1F0
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*> -- vtable 0x007ECBDC slot 3; locator 0x00804AD8 -> type descriptor 0x00829078
//   `.?AV?$DynamicVectorClass@PAUTileInsertType@IsometricTileTypeClass@@@@`.
template struct CountedVector<IsometricTileTypeClass::TileInsertType*>;

// FUNCTION: GAMEMD 0x0054E890
// DynamicVectorClass<KamikazeControl*> -- vtable 0x007ECE7C slot 3; locator 0x00804D58 -> type descriptor 0x008296A8
//   `.?AV?$DynamicVectorClass@PAUKamikazeControl@@@@`.
template struct CountedVector<KamikazeControl*>;

// FUNCTION: GAMEMD 0x005512D0
// DynamicVectorClass<LaserDrawClass*> -- vtable 0x007ECEDC slot 3; locator 0x00804DF0 -> type descriptor 0x00829710
//   `.?AV?$DynamicVectorClass@PAVLaserDrawClass@@@@`.
template struct CountedVector<LaserDrawClass*>;

// FUNCTION: GAMEMD 0x00555200
// DynamicVectorClass<LightSourceClass*> -- vtable 0x007ECF7C slot 3; locator 0x00804F78 -> type descriptor 0x00829B28
//   `.?AV?$DynamicVectorClass@PAVLightSourceClass@@@@`.
template struct CountedVector<LightSourceClass*>;

// FUNCTION: GAMEMD 0x00555260
// DynamicVectorClass<LightSourceClass::PendingCellClass*> -- vtable 0x007ECFBC slot 3; locator 0x00805010 -> type descriptor 0x00829BB0
//   `.?AV?$DynamicVectorClass@PAVPendingCellClass@LightSourceClass@@@@`.
template struct CountedVector<LightSourceClass::PendingCellClass*>;

// FUNCTION: GAMEMD 0x00556EB0
// DynamicVectorClass<LineTrail*> -- vtable 0x007ED0CC slot 3; locator 0x008051A8 -> type descriptor 0x00829D78
//   `.?AV?$DynamicVectorClass@PAVLineTrail@@@@`.
template struct CountedVector<LineTrail*>;

// FUNCTION: GAMEMD 0x005581E0
// DynamicVectorClass<const unsigned short*> -- vtable 0x007ED1DC slot 3; locator 0x00805280 -> type descriptor 0x00829DD0
//   `.?AV?$DynamicVectorClass@PBG@@`.
template struct CountedVector<const unsigned short*>;

// FUNCTION: GAMEMD 0x0055A150
// DynamicVectorClass<FileEntryClass*> -- vtable 0x007ED30C slot 3; locator 0x00805370 -> type descriptor 0x00829E48
//   `.?AV?$DynamicVectorClass@PAVFileEntryClass@@@@`.
template struct CountedVector<FileEntryClass*>;

// FUNCTION: GAMEMD 0x00588C90
// DynamicVectorClass<SubzoneConnectionStruct> -- vtable 0x007ED5A0 slot 3; locator 0x008057F8 -> type descriptor 0x0082ADD0
//   `.?AV?$DynamicVectorClass@USubzoneConnectionStruct@@@@`.
template struct CountedVector<SubzoneConnectionStruct>;

// FUNCTION: GAMEMD 0x00588CE0
// DynamicVectorClass<ZoneConnectionClass> -- vtable 0x007ED4C0 slot 3; locator 0x00805530 -> type descriptor 0x0082AAC0
//   `.?AV?$DynamicVectorClass@UZoneConnectionClass@@@@`.
template struct CountedVector<ZoneConnectionClass>;

// FUNCTION: GAMEMD 0x00588F00
// DynamicVectorClass<PassabilityType> -- vtable 0x007ED580 slot 3; locator 0x008057A8 -> type descriptor 0x0082AD10
//   `.?AV?$DynamicVectorClass@W4PassabilityType@@@@`.
template struct CountedVector<PassabilityType>;

// FUNCTION: GAMEMD 0x00588F60
// DynamicVectorClass<HashObject<unsigned int, unsigned int>> -- vtable 0x007ED540 slot 3; locator 0x008056A8 -> type descriptor 0x0082ABD8
//   `.?AV?$DynamicVectorClass@U?$HashObject@II@@@@`.
template struct CountedVector<HashObject<unsigned int, unsigned int> >;

// FUNCTION: GAMEMD 0x00588FD0
// DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct>> -- vtable 0x007ED520 slot 3; locator 0x00805710 -> type descriptor 0x0082AC58
//   `.?AV?$DynamicVectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@`.
template struct CountedVector<HashObject<unsigned int, SubzoneConnectionStruct> >;

// FUNCTION: GAMEMD 0x005AC3A0
// DynamicVectorClass<MapRegionClass*> -- vtable 0x007ED858 slot 3; locator 0x008058C0 -> type descriptor 0x0082B9C8
//   `.?AV?$DynamicVectorClass@PAVMapRegionClass@@@@`.
template struct CountedVector<MapRegionClass*>;

// FUNCTION: GAMEMD 0x005AC4C0
// DynamicVectorClass<_WIN32_FIND_DATAA*> -- vtable 0x007ED94C slot 3; locator 0x00805A28 -> type descriptor 0x0082BAD0
//   `.?AV?$DynamicVectorClass@PAU_WIN32_FIND_DATAA@@@@`.
template struct CountedVector<_WIN32_FIND_DATAA*>;

// FUNCTION: GAMEMD 0x005AC520
// DynamicVectorClass<TRect<int>> -- vtable 0x007ED99C slot 3; locator 0x00805A78 -> type descriptor 0x0082BFB0
//   `.?AV?$DynamicVectorClass@V?$TRect@H@@@@`.
template struct CountedVector<TRect<int> >;

// FUNCTION: GAMEMD 0x005AC5A0
// DynamicVectorClass<CellClass*> -- vtable 0x007ED9BC slot 3; locator 0x00805B10 -> type descriptor 0x0082C010
//   `.?AV?$DynamicVectorClass@PAVCellClass@@@@`.
template struct CountedVector<CellClass*>;

// FUNCTION: GAMEMD 0x005AC5F0
// DynamicVectorClass<double> -- vtable 0x007EDA6C slot 3; locator 0x00805BA8 -> type descriptor 0x0082C068
//   `.?AV?$DynamicVectorClass@N@@`.
template struct CountedVector<double>;

// FUNCTION: GAMEMD 0x005C0A70
// DynamicVectorClass<const char*> -- vtable 0x007EE0B4 slot 3; locator 0x00805F08 -> type descriptor 0x0082D9F8
//   `.?AV?$DynamicVectorClass@PBD@@`.
template struct CountedVector<const char*>;

// FUNCTION: GAMEMD 0x005C5010
// DynamicVectorClass<MPlayerScoreType*> -- vtable 0x007EE3F0 slot 3; locator 0x00806308 -> type descriptor 0x0082DFA0
//   `.?AV?$DynamicVectorClass@PAUMPlayerScoreType@@@@`.
template struct CountedVector<MPlayerScoreType*>;

// FUNCTION: GAMEMD 0x005C5070
// DynamicVectorClass<NodeNameType*> -- vtable 0x007EE370 slot 3; locator 0x00806210 -> type descriptor 0x0082DBE0
//   `.?AV?$DynamicVectorClass@PAUNodeNameType@@@@`.
template struct CountedVector<NodeNameType*>;

// FUNCTION: GAMEMD 0x005C50D0
// DynamicVectorClass<CoopCampaignClass*> -- vtable 0x007EE350 slot 3; locator 0x008061A8 -> type descriptor 0x0082DB70
//   `.?AV?$DynamicVectorClass@PAVCoopCampaignClass@@@@`.
template struct CountedVector<CoopCampaignClass*>;

// FUNCTION: GAMEMD 0x005D05A0
// DynamicVectorClass<Point2D> -- vtable 0x007EEB54 slot 3; locator 0x00806A88 -> type descriptor 0x008303A8
//   `.?AV?$DynamicVectorClass@VPoint2D@@@@`.
template struct CountedVector<Point2D>;

// FUNCTION: GAMEMD 0x005D0610
// DynamicVectorClass<MSTextEntry*> -- vtable 0x007EEB34 slot 3; locator 0x00806B58 -> type descriptor 0x00830470
//   `.?AV?$DynamicVectorClass@PAVMSTextEntry@@@@`.
template struct CountedVector<MSTextEntry*>;

// FUNCTION: GAMEMD 0x005D0670
// DynamicVectorClass<MapSelection*> -- vtable 0x007EEB14 slot 3; locator 0x00806AF0 -> type descriptor 0x00830408
//   `.?AV?$DynamicVectorClass@PAVMapSelection@@@@`.
template struct CountedVector<MapSelection*>;

// FUNCTION: GAMEMD 0x005D06D0
// DynamicVectorClass<MapStage*> -- vtable 0x007EEA94 slot 3; locator 0x00806928 -> type descriptor 0x00830230
//   `.?AV?$DynamicVectorClass@PAVMapStage@@@@`.
template struct CountedVector<MapStage*>;

// FUNCTION: GAMEMD 0x005D0730
// DynamicVectorClass<MSAnimEntry*> -- vtable 0x007EEA74 slot 3; locator 0x008068C0 -> type descriptor 0x008301C8
//   `.?AV?$DynamicVectorClass@PAVMSAnimEntry@@@@`.
template struct CountedVector<MSAnimEntry*>;

// FUNCTION: GAMEMD 0x005D0790
// DynamicVectorClass<MSSfxEntry*> -- vtable 0x007EEA54 slot 3; locator 0x00806990 -> type descriptor 0x00830298
//   `.?AV?$DynamicVectorClass@PAVMSSfxEntry@@@@`.
template struct CountedVector<MSSfxEntry*>;

// FUNCTION: GAMEMD 0x005D2720
// DynamicVectorClass<MSAnim*> -- vtable 0x007EEC04 slot 3; locator 0x00806CB8 -> type descriptor 0x00830580
//   `.?AV?$DynamicVectorClass@PAVMSAnim@@@@`.
template struct CountedVector<MSAnim*>;

// FUNCTION: GAMEMD 0x005D2780
// DynamicVectorClass<MSSfx*> -- vtable 0x007EEBE4 slot 3; locator 0x00806C50 -> type descriptor 0x00830528
//   `.?AV?$DynamicVectorClass@PAVMSSfx@@@@`.
template struct CountedVector<MSSfx*>;

// FUNCTION: GAMEMD 0x005D5080
// DynamicVectorClass<HWND__*> -- vtable 0x007EEC8C slot 3; locator 0x00806DF8 -> type descriptor 0x008306F8
//   `.?AV?$DynamicVectorClass@PAUHWND__@@@@`.
template struct CountedVector<HWND__*>;

// FUNCTION: GAMEMD 0x005D50E0
// DynamicVectorClass<AcceleratorTracker> -- vtable 0x007EECCC slot 3; locator 0x00806E90 -> type descriptor 0x00830760
//   `.?AV?$DynamicVectorClass@UAcceleratorTracker@@@@`.
template struct CountedVector<AcceleratorTracker>;

// FUNCTION: GAMEMD 0x005D80B0
// DynamicVectorClass<MultiplayerTeam*> -- vtable 0x007EEE34 slot 3; locator 0x00806FF0 -> type descriptor 0x00830868
//   `.?AV?$DynamicVectorClass@PAVMultiplayerTeam@@@@`.
template struct CountedVector<MultiplayerTeam*>;

// FUNCTION: GAMEMD 0x005D8110
// DynamicVectorClass<MultiplayerGameMode*> -- vtable 0x007EED20 slot 3; locator 0x00806F28 -> type descriptor 0x008307F0
//   `.?AV?$DynamicVectorClass@PAVMultiplayerGameMode@@@@`.
template struct CountedVector<MultiplayerGameMode*>;

// FUNCTION: GAMEMD 0x005EEBB0
// DynamicVectorClass<const MultiMission*> -- vtable 0x007EEF70 slot 3; locator 0x008072C8 -> type descriptor 0x008319C8
//   `.?AV?$DynamicVectorClass@PBVMultiMission@@@@`.
template struct CountedVector<const MultiMission*>;

// FUNCTION: GAMEMD 0x005F9B00
// DynamicVectorClass<ObjectTypeClass*> -- vtable 0x007EF26C slot 3; locator 0x008074B0 -> type descriptor 0x00832A48
//   `.?AV?$DynamicVectorClass@PAVObjectTypeClass@@@@`.
template struct CountedVector<ObjectTypeClass*>;

// FUNCTION: GAMEMD 0x005FFFC0
// DynamicVectorClass<SpotLightClass*> -- vtable 0x007EF6BC slot 3; locator 0x00807758 -> type descriptor 0x00833618
//   `.?AV?$DynamicVectorClass@PAVSpotLightClass@@@@`.
template struct CountedVector<SpotLightClass*>;

// FUNCTION: GAMEMD 0x00627D20
// DynamicVectorClass<ColorScheme*> -- vtable 0x007EF790 slot 3; locator 0x00807988 -> type descriptor 0x008365A0
//   `.?AV?$DynamicVectorClass@PAVColorScheme@@@@`.
template struct CountedVector<ColorScheme*>;

// FUNCTION: GAMEMD 0x00627D80
// DynamicVectorClass<HSVClass> -- vtable 0x007EF750 slot 3; locator 0x00807888 -> type descriptor 0x008364A0
//   `.?AV?$DynamicVectorClass@VHSVClass@@@@`.
template struct CountedVector<HSVClass>;

// FUNCTION: GAMEMD 0x00628800
// DynamicVectorClass<HashObject<HashString, SchemeNode*>> -- vtable 0x007EF770 slot 3; locator 0x008078F0 -> type descriptor 0x00836520
//   `.?AV?$DynamicVectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@`.
template struct CountedVector<HashObject<HashString, SchemeNode*> >;

// FUNCTION: GAMEMD 0x0062B070
// DynamicVectorClass<ParasiteClass*> -- vtable 0x007EF824 slot 3; locator 0x00807A50 -> type descriptor 0x00836608
//   `.?AV?$DynamicVectorClass@PAVParasiteClass@@@@`.
template struct CountedVector<ParasiteClass*>;

// FUNCTION: GAMEMD 0x0063DB60
// DynamicVectorClass<PlanningMemberClass*> -- vtable 0x007EFEE4 slot 3; locator 0x00808070 -> type descriptor 0x00836A98
//   `.?AV?$DynamicVectorClass@PAVPlanningMemberClass@@@@`.
template struct CountedVector<PlanningMemberClass*>;

// FUNCTION: GAMEMD 0x0063DBC0
// DynamicVectorClass<PlanningBranchClass*> -- vtable 0x007EFEC4 slot 3; locator 0x00808008 -> type descriptor 0x00836A20
//   `.?AV?$DynamicVectorClass@PAVPlanningBranchClass@@@@`.
template struct CountedVector<PlanningBranchClass*>;

// FUNCTION: GAMEMD 0x0063DC20
// DynamicVectorClass<PlanningNodeClass*> -- vtable 0x007EFE44 slot 3; locator 0x00807ED8 -> type descriptor 0x00836930
//   `.?AV?$DynamicVectorClass@PAVPlanningNodeClass@@@@`.
template struct CountedVector<PlanningNodeClass*>;

// FUNCTION: GAMEMD 0x0063DC80
// DynamicVectorClass<EventClass*> -- vtable 0x007EFE04 slot 3; locator 0x00807E40 -> type descriptor 0x008368C0
//   `.?AV?$DynamicVectorClass@PAVEventClass@@@@`.
template struct CountedVector<EventClass*>;

// FUNCTION: GAMEMD 0x0063DCE0
// DynamicVectorClass<PlanningTokenClass*> -- vtable 0x007EFE84 slot 3; locator 0x00807F70 -> type descriptor 0x008369A8
//   `.?AV?$DynamicVectorClass@PAVPlanningTokenClass@@@@`.
template struct CountedVector<PlanningTokenClass*>;

// FUNCTION: GAMEMD 0x00658890
// DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass*>> -- vtable 0x007F042C slot 3; locator 0x00808458 -> type descriptor 0x00839438
//   `.?AV?$DynamicVectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@`.
template struct CountedVector<HashObject<RadarTrackingStruct, TechnoClass*> >;

// FUNCTION: GAMEMD 0x0065A1E0
// DynamicVectorClass<RadBeam*> -- vtable 0x007F0484 slot 3; locator 0x008084C0 -> type descriptor 0x00839568
//   `.?AV?$DynamicVectorClass@PAVRadBeam@@@@`.
template struct CountedVector<RadBeam*>;

// FUNCTION: GAMEMD 0x0065BEF0
// DynamicVectorClass<RadSiteClass*> -- vtable 0x007F07A4 slot 3; locator 0x008085F8 -> type descriptor 0x008395C8
//   `.?AV?$DynamicVectorClass@PAVRadSiteClass@@@@`.
template struct CountedVector<RadSiteClass*>;

// FUNCTION: GAMEMD 0x00660C80
// DynamicVectorClass<RadarEventClass*> -- vtable 0x007F0AAC slot 3; locator 0x00808870 -> type descriptor 0x00839958
//   `.?AV?$DynamicVectorClass@PAVRadarEventClass@@@@`.
template struct CountedVector<RadarEventClass*>;

// FUNCTION: GAMEMD 0x006647B0
// DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*> -- vtable 0x007F0C2C slot 3; locator 0x008089D0 -> type descriptor 0x00839A40
//   `.?AV?$DynamicVectorClass@PAUConnectionListStruct@OwnerTalkClass@@@@`.
template struct CountedVector<OwnerTalkClass::ConnectionListStruct*>;

// FUNCTION: GAMEMD 0x0067A410
// DynamicVectorClass<const VoxelAnimTypeClass*> -- vtable 0x007F0DCC slot 3; locator 0x00808C48 -> type descriptor 0x0083A048
//   `.?AV?$DynamicVectorClass@PBVVoxelAnimTypeClass@@@@`.
//   The same body also sits at that slot in TypeList<VoxelAnimTypeClass*> (0x007F0D3C); DynamicVectorClass<const VoxelAnimTypeClass*> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<const VoxelAnimTypeClass*>;

// FUNCTION: GAMEMD 0x0067A680
// DynamicVectorClass<const SmudgeTypeClass*> -- vtable 0x007F0DEC slot 3; locator 0x00808C80 -> type descriptor 0x00839FA8
//   `.?AV?$DynamicVectorClass@PBVSmudgeTypeClass@@@@`.
//   The same body also sits at that slot in TypeList<SmudgeTypeClass*> (0x007F0D1C); DynamicVectorClass<const SmudgeTypeClass*> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<const SmudgeTypeClass*>;

// FUNCTION: GAMEMD 0x0067A930
// DynamicVectorClass<const TerrainTypeClass*> -- vtable 0x007F0E0C slot 3; locator 0x00808CB8 -> type descriptor 0x00839F00
//   `.?AV?$DynamicVectorClass@PBVTerrainTypeClass@@@@`.
//   The same body also sits at that slot in TypeList<TerrainTypeClass*> (0x007F0CFC); DynamicVectorClass<const TerrainTypeClass*> is the
//   base of those, so the slot is declared here (batch fifty-seven).
template struct CountedVector<const TerrainTypeClass*>;

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

// FUNCTION: GAMEMD 0x0069C5A0
// DynamicVectorClass<MultiMission*> -- vtable 0x007F11F4 slot 3; locator 0x00809130 -> type descriptor 0x0083EE00
//   `.?AV?$DynamicVectorClass@PAVMultiMission@@@@`.
template struct CountedVector<MultiMission*>;

// FUNCTION: GAMEMD 0x0069C600
// DynamicVectorClass<GlobalPacketType*> -- vtable 0x007F11D4 slot 3; locator 0x00809198 -> type descriptor 0x0083EE70
//   `.?AV?$DynamicVectorClass@PAUGlobalPacketType@@@@`.
template struct CountedVector<GlobalPacketType*>;

// FUNCTION: GAMEMD 0x0069C660
// DynamicVectorClass<PhoneEntryClass*> -- vtable 0x007F11B4 slot 3; locator 0x008090C8 -> type descriptor 0x0083ED98
//   `.?AV?$DynamicVectorClass@PAVPhoneEntryClass@@@@`.
template struct CountedVector<PhoneEntryClass*>;

// FUNCTION: GAMEMD 0x006B13B0
// DynamicVectorClass<SlaveManagerClass::SlaveControl*> -- vtable 0x007F322C slot 3; locator 0x00809768 -> type descriptor 0x0083FD70
//   `.?AV?$DynamicVectorClass@PAUSlaveControl@SlaveManagerClass@@@@`.
template struct CountedVector<SlaveManagerClass::SlaveControl*>;

// FUNCTION: GAMEMD 0x006B1410
// DynamicVectorClass<SlaveManagerClass*> -- vtable 0x007F315C slot 3; locator 0x00809620 -> type descriptor 0x0083FCD0
//   `.?AV?$DynamicVectorClass@PAVSlaveManagerClass@@@@`.
template struct CountedVector<SlaveManagerClass*>;

// FUNCTION: GAMEMD 0x006B43B0
// DynamicVectorClass<UndoInfoStruct> -- vtable 0x007F327C slot 3; locator 0x00809800 -> type descriptor 0x0083FFA0
//   `.?AV?$DynamicVectorClass@UUndoInfoStruct@@@@`.
template struct CountedVector<UndoInfoStruct>;

// FUNCTION: GAMEMD 0x006B8160
// DynamicVectorClass<SpawnManagerClass::SpawnControl*> -- vtable 0x007F36B4 slot 3; locator 0x00809B50 -> type descriptor 0x00840180
//   `.?AV?$DynamicVectorClass@PAUSpawnControl@SpawnManagerClass@@@@`.
template struct CountedVector<SpawnManagerClass::SpawnControl*>;

// FUNCTION: GAMEMD 0x006B81C0
// DynamicVectorClass<SpawnManagerClass*> -- vtable 0x007F35E4 slot 3; locator 0x00809A08 -> type descriptor 0x008400E0
//   `.?AV?$DynamicVectorClass@PAVSpawnManagerClass@@@@`.
template struct CountedVector<SpawnManagerClass*>;

// FUNCTION: GAMEMD 0x006BED50
// DynamicVectorClass<unsigned long> -- vtable 0x007F3728 slot 3; locator 0x00809BE8 -> type descriptor 0x00840AA8
//   `.?AV?$DynamicVectorClass@K@@`.
template struct CountedVector<unsigned long>;

// FUNCTION: GAMEMD 0x006CA7C0
// DynamicVectorClass<SubTitle*> -- vtable 0x007F3F6C slot 3; locator 0x0080B530 -> type descriptor 0x008422D0
//   `.?AV?$DynamicVectorClass@PAVSubTitle@@@@`.
template struct CountedVector<SubTitle*>;

// FUNCTION: GAMEMD 0x006CF4F0
// DynamicVectorClass<SwizzlePointerClass> -- vtable 0x007F4134 slot 3; locator 0x0080B798 -> type descriptor 0x00842790
//   `.?AV?$DynamicVectorClass@VSwizzlePointerClass@@@@`.
template struct CountedVector<SwizzlePointerClass>;

// FUNCTION: GAMEMD 0x006DC4E0
// DynamicVectorClass<DirtyAreaStruct> -- vtable 0x007F429C slot 3; locator 0x0080B830 -> type descriptor 0x00842988
//   `.?AV?$DynamicVectorClass@UDirtyAreaStruct@@@@`.
template struct CountedVector<DirtyAreaStruct>;

// FUNCTION: GAMEMD 0x006DC580
// DynamicVectorClass<ShadowControlClass*> -- vtable 0x007F42DC slot 3; locator 0x0080B8C8 -> type descriptor 0x008429F8
//   `.?AV?$DynamicVectorClass@PAVShadowControlClass@@@@`.
template struct CountedVector<ShadowControlClass*>;

// FUNCTION: GAMEMD 0x006E47F0
// DynamicVectorClass<TActionClass*> -- vtable 0x007F43D0 slot 3; locator 0x0080BA10 -> type descriptor 0x00842B40
//   `.?AV?$DynamicVectorClass@PAVTActionClass@@@@`.
template struct CountedVector<TActionClass*>;

// FUNCTION: GAMEMD 0x006E64E0
// DynamicVectorClass<TagTypeClass*> -- vtable 0x007F4558 slot 3; locator 0x0080BC08 -> type descriptor 0x00842C78
//   `.?AV?$DynamicVectorClass@PAVTagTypeClass@@@@`.
template struct CountedVector<TagTypeClass*>;

// FUNCTION: GAMEMD 0x0071B240
// DynamicVectorClass<TemporalClass*> -- vtable 0x007F5114 slot 3; locator 0x0080C248 -> type descriptor 0x00844590
//   `.?AV?$DynamicVectorClass@PAVTemporalClass@@@@`.
template struct CountedVector<TemporalClass*>;

// FUNCTION: GAMEMD 0x0071FBA0
// DynamicVectorClass<TEventClass*> -- vtable 0x007F550C slot 3; locator 0x0080C500 -> type descriptor 0x008446C0
//   `.?AV?$DynamicVectorClass@PAVTEventClass@@@@`.
template struct CountedVector<TEventClass*>;

// FUNCTION: GAMEMD 0x007212B0
// DynamicVectorClass<ThemeControl*> -- vtable 0x007F568C slot 3; locator 0x0080C688 -> type descriptor 0x00844780
//   `.?AV?$DynamicVectorClass@PAUThemeControl@@@@`.
template struct CountedVector<ThemeControl*>;

// FUNCTION: GAMEMD 0x00723730
// DynamicVectorClass<TiberiumClass*> -- vtable 0x007F56BC slot 3; locator 0x0080C6F0 -> type descriptor 0x00844890
//   `.?AV?$DynamicVectorClass@PAVTiberiumClass@@@@`.
template struct CountedVector<TiberiumClass*>;

// FUNCTION: GAMEMD 0x00724C30
// DynamicVectorClass<const ToolTip*> -- vtable 0x007F57C8 slot 3; locator 0x0080C840 -> type descriptor 0x00844968
//   `.?AV?$DynamicVectorClass@PBVToolTip@@@@`.
template struct CountedVector<const ToolTip*>;

// FUNCTION: GAMEMD 0x0074F360
// DynamicVectorClass<VeinholeMonsterClass*> -- vtable 0x007F663C slot 3; locator 0x0080CF60 -> type descriptor 0x008460A8
//   `.?AV?$DynamicVectorClass@PAVVeinholeMonsterClass@@@@`.
template struct CountedVector<VeinholeMonsterClass*>;

// FUNCTION: GAMEMD 0x007518D0
// DynamicVectorClass<VocClass*> -- vtable 0x007F68AC slot 3; locator 0x0080D0B0 -> type descriptor 0x008464F8
//   `.?AV?$DynamicVectorClass@PAVVocClass@@@@`.
template struct CountedVector<VocClass*>;

// FUNCTION: GAMEMD 0x00753650
// DynamicVectorClass<VoxClass*> -- vtable 0x007F6904 slot 3; locator 0x0080D148 -> type descriptor 0x00846648
//   `.?AV?$DynamicVectorClass@PAVVoxClass@@@@`.
template struct CountedVector<VoxClass*>;

// FUNCTION: GAMEMD 0x0075A430
// DynamicVectorClass<MovieHandle*> -- vtable 0x007F6984 slot 3; locator 0x0080D1E0 -> type descriptor 0x00847B28
//   `.?AV?$DynamicVectorClass@PAVMovieHandle@@@@`.
template struct CountedVector<MovieHandle*>;

// FUNCTION: GAMEMD 0x00763F90
// DynamicVectorClass<WaypointPathClass*> -- vtable 0x007F6E04 slot 3; locator 0x0080D480 -> type descriptor 0x00847F00
//   `.?AV?$DynamicVectorClass@PAVWaypointPathClass@@@@`.
template struct CountedVector<WaypointPathClass*>;

// FUNCTION: GAMEMD 0x00769CD0
// DynamicVectorClass<WorldDominationTour::Map::AnimationPalette*> -- vtable 0x007F7144 slot 3; locator 0x0080DEC8 -> type descriptor 0x00848930
//   `.?AV?$DynamicVectorClass@PAUAnimationPalette@Map@WorldDominationTour@@@@`.
template struct CountedVector<WorldDominationTour::Map::AnimationPalette*>;

// FUNCTION: GAMEMD 0x007AC970
// DynamicVectorClass<tConnInfoStruct*> -- vtable 0x007F78C4 slot 3; locator 0x0080E918 -> type descriptor 0x0084C6F8
//   `.?AV?$DynamicVectorClass@PAUtConnInfoStruct@@@@`.
template struct CountedVector<tConnInfoStruct*>;

// FUNCTION: GAMEMD 0x007B2840
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*> -- vtable 0x007F7A1C slot 3; locator 0x0080EAC8 -> type descriptor 0x0084DDF8
//   `.?AV?$DynamicVectorClass@PAUWinsockBufferType@WinsockInterfaceClass@@@@`.
template struct CountedVector<WinsockInterfaceClass::WinsockBufferType*>;

// FUNCTION: GAMEMD 0x007B42C0
// DynamicVectorClass<unsigned char*> -- vtable 0x007F7AEC slot 3; locator 0x0080EB90 -> type descriptor 0x0084E198
//   `.?AV?$DynamicVectorClass@PAE@@`.
template struct CountedVector<unsigned char*>;

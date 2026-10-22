// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The constructor and the four T-independent members of TClassFactory<T>
//   for all 77 retail instantiations. Each instantiation's vtable (from its
//   RTTI locator) lists the member addresses; the bodies were compared byte
//   for byte across all 77. The constructor is the member-initialiser form in
//   class_factory.h: it clears RefCount before the vptr store, which is the
//   retail order (0x6BEE40 for CStreamClass).
//
//   Each explicit class instantiation emits these five members and the
//   vtable. CreateInstance (slot 3) needs T complete and is only declared, so
//   it is not emitted here; the vtable references it as an external.
//   In retail each instantiation is a COMDAT of the translation unit that
//   registered T's factory, so this grouping is not retail's TU layout.
//
//   Annotation convention: one by-name TEMPLATE marker per member, all
//   above the explicit instantiation that emits them (reccmp does not accept
//   several FUNCTION markers for one module stacked on one definition).

#include "class_factory.h"

// VTABLE: GAMEMD 0x7F3768 -- TClassFactory<CStreamClass>
class CStreamClass;
// TEMPLATE: GAMEMD 0x6BEE40
// TClassFactory<CStreamClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BEE50
// TClassFactory<CStreamClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BEEC0
// TClassFactory<CStreamClass>::AddRef
// TEMPLATE: GAMEMD 0x6BEEE0
// TClassFactory<CStreamClass>::Release
// TEMPLATE: GAMEMD 0x6BEF90
// TClassFactory<CStreamClass>::LockServer
template class TClassFactory<CStreamClass>;

// Layout, asserted on the first instantiation (T carries no members here).
typedef TClassFactory<CStreamClass> GgClassFactoryRep;
GG_STATIC_ASSERT(offsetof(GgClassFactoryRep, RefCount) == 0x4);
GG_STATIC_ASSERT(sizeof(GgClassFactoryRep) == 0x8);

// VTABLE: GAMEMD 0x7F3780 -- TClassFactory<WaveClass>
class WaveClass;
// TEMPLATE: GAMEMD 0x6BEFC0
// TClassFactory<WaveClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BEFD0
// TClassFactory<WaveClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF040
// TClassFactory<WaveClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF060
// TClassFactory<WaveClass>::Release
// TEMPLATE: GAMEMD 0x6BF110
// TClassFactory<WaveClass>::LockServer
template class TClassFactory<WaveClass>;

// VTABLE: GAMEMD 0x7F3798 -- TClassFactory<TerrainTypeClass>
class TerrainTypeClass;
// TEMPLATE: GAMEMD 0x6BF140
// TClassFactory<TerrainTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF150
// TClassFactory<TerrainTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF1C0
// TClassFactory<TerrainTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF1E0
// TClassFactory<TerrainTypeClass>::Release
// TEMPLATE: GAMEMD 0x6BF290
// TClassFactory<TerrainTypeClass>::LockServer
template class TClassFactory<TerrainTypeClass>;

// VTABLE: GAMEMD 0x7F37B0 -- TClassFactory<TerrainClass>
class TerrainClass;
// TEMPLATE: GAMEMD 0x6BF2C0
// TClassFactory<TerrainClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF2D0
// TClassFactory<TerrainClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF340
// TClassFactory<TerrainClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF360
// TClassFactory<TerrainClass>::Release
// TEMPLATE: GAMEMD 0x6BF410
// TClassFactory<TerrainClass>::LockServer
template class TClassFactory<TerrainClass>;

// VTABLE: GAMEMD 0x7F37C8 -- TClassFactory<SuperWeaponTypeClass>
class SuperWeaponTypeClass;
// TEMPLATE: GAMEMD 0x6BF440
// TClassFactory<SuperWeaponTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF450
// TClassFactory<SuperWeaponTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF4C0
// TClassFactory<SuperWeaponTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF4E0
// TClassFactory<SuperWeaponTypeClass>::Release
// TEMPLATE: GAMEMD 0x6BF590
// TClassFactory<SuperWeaponTypeClass>::LockServer
template class TClassFactory<SuperWeaponTypeClass>;

// VTABLE: GAMEMD 0x7F37E0 -- TClassFactory<SuperClass>
class SuperClass;
// TEMPLATE: GAMEMD 0x6BF5C0
// TClassFactory<SuperClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF5D0
// TClassFactory<SuperClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF640
// TClassFactory<SuperClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF660
// TClassFactory<SuperClass>::Release
// TEMPLATE: GAMEMD 0x6BF710
// TClassFactory<SuperClass>::LockServer
template class TClassFactory<SuperClass>;

// VTABLE: GAMEMD 0x7F37F8 -- TClassFactory<Tactical>
class Tactical;
// TEMPLATE: GAMEMD 0x6BF740
// TClassFactory<Tactical>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF750
// TClassFactory<Tactical>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF7C0
// TClassFactory<Tactical>::AddRef
// TEMPLATE: GAMEMD 0x6BF7E0
// TClassFactory<Tactical>::Release
// TEMPLATE: GAMEMD 0x6BF890
// TClassFactory<Tactical>::LockServer
template class TClassFactory<Tactical>;

// VTABLE: GAMEMD 0x7F3810 -- TClassFactory<CellClass>
class CellClass;
// TEMPLATE: GAMEMD 0x6BF8C0
// TClassFactory<CellClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF8D0
// TClassFactory<CellClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF940
// TClassFactory<CellClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF960
// TClassFactory<CellClass>::Release
// TEMPLATE: GAMEMD 0x6BFA10
// TClassFactory<CellClass>::LockServer
template class TClassFactory<CellClass>;

// VTABLE: GAMEMD 0x7F3828 -- TClassFactory<EMPulseClass>
class EMPulseClass;
// TEMPLATE: GAMEMD 0x6BFA40
// TClassFactory<EMPulseClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BFA50
// TClassFactory<EMPulseClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BFAC0
// TClassFactory<EMPulseClass>::AddRef
// TEMPLATE: GAMEMD 0x6BFAE0
// TClassFactory<EMPulseClass>::Release
// TEMPLATE: GAMEMD 0x6BFB90
// TClassFactory<EMPulseClass>::LockServer
template class TClassFactory<EMPulseClass>;

// VTABLE: GAMEMD 0x7F3840 -- TClassFactory<LightSourceClass>
class LightSourceClass;
// TEMPLATE: GAMEMD 0x6BFBC0
// TClassFactory<LightSourceClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BFBD0
// TClassFactory<LightSourceClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BFC40
// TClassFactory<LightSourceClass>::AddRef
// TEMPLATE: GAMEMD 0x6BFC60
// TClassFactory<LightSourceClass>::Release
// TEMPLATE: GAMEMD 0x6BFD10
// TClassFactory<LightSourceClass>::LockServer
template class TClassFactory<LightSourceClass>;

// VTABLE: GAMEMD 0x7F3858 -- TClassFactory<SideClass>
class SideClass;
// TEMPLATE: GAMEMD 0x6BFD40
// TClassFactory<SideClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BFD50
// TClassFactory<SideClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BFDC0
// TClassFactory<SideClass>::AddRef
// TEMPLATE: GAMEMD 0x6BFDE0
// TClassFactory<SideClass>::Release
// TEMPLATE: GAMEMD 0x6BFE90
// TClassFactory<SideClass>::LockServer
template class TClassFactory<SideClass>;

// VTABLE: GAMEMD 0x7F3870 -- TClassFactory<TiberiumClass>
class TiberiumClass;
// TEMPLATE: GAMEMD 0x6BFEC0
// TClassFactory<TiberiumClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BFED0
// TClassFactory<TiberiumClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BFF40
// TClassFactory<TiberiumClass>::AddRef
// TEMPLATE: GAMEMD 0x6BFF60
// TClassFactory<TiberiumClass>::Release
// TEMPLATE: GAMEMD 0x6C0010
// TClassFactory<TiberiumClass>::LockServer
template class TClassFactory<TiberiumClass>;

// VTABLE: GAMEMD 0x7F3888 -- TClassFactory<TubeClass>
class TubeClass;
// TEMPLATE: GAMEMD 0x6C0040
// TClassFactory<TubeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0050
// TClassFactory<TubeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C00C0
// TClassFactory<TubeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C00E0
// TClassFactory<TubeClass>::Release
// TEMPLATE: GAMEMD 0x6C0190
// TClassFactory<TubeClass>::LockServer
template class TClassFactory<TubeClass>;

// VTABLE: GAMEMD 0x7F38A0 -- TClassFactory<CampaignClass>
class CampaignClass;
// TEMPLATE: GAMEMD 0x6C01C0
// TClassFactory<CampaignClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C01D0
// TClassFactory<CampaignClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0240
// TClassFactory<CampaignClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0260
// TClassFactory<CampaignClass>::Release
// TEMPLATE: GAMEMD 0x6C0310
// TClassFactory<CampaignClass>::LockServer
template class TClassFactory<CampaignClass>;

// VTABLE: GAMEMD 0x7F38B8 -- TClassFactory<BuildingLightClass>
class BuildingLightClass;
// TEMPLATE: GAMEMD 0x6C0340
// TClassFactory<BuildingLightClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0350
// TClassFactory<BuildingLightClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C03C0
// TClassFactory<BuildingLightClass>::AddRef
// TEMPLATE: GAMEMD 0x6C03E0
// TClassFactory<BuildingLightClass>::Release
// TEMPLATE: GAMEMD 0x6C0490
// TClassFactory<BuildingLightClass>::LockServer
template class TClassFactory<BuildingLightClass>;

// VTABLE: GAMEMD 0x7F38D0 -- TClassFactory<WaypointPathClass>
class WaypointPathClass;
// TEMPLATE: GAMEMD 0x6C04C0
// TClassFactory<WaypointPathClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C04D0
// TClassFactory<WaypointPathClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0540
// TClassFactory<WaypointPathClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0560
// TClassFactory<WaypointPathClass>::Release
// TEMPLATE: GAMEMD 0x6C0610
// TClassFactory<WaypointPathClass>::LockServer
template class TClassFactory<WaypointPathClass>;

// VTABLE: GAMEMD 0x7F38E8 -- TClassFactory<TemporalClass>
class TemporalClass;
// TEMPLATE: GAMEMD 0x6C0640
// TClassFactory<TemporalClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0650
// TClassFactory<TemporalClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C06C0
// TClassFactory<TemporalClass>::AddRef
// TEMPLATE: GAMEMD 0x6C06E0
// TClassFactory<TemporalClass>::Release
// TEMPLATE: GAMEMD 0x6C0790
// TClassFactory<TemporalClass>::LockServer
template class TClassFactory<TemporalClass>;

// VTABLE: GAMEMD 0x7F3900 -- TClassFactory<AirstrikeClass>
class AirstrikeClass;
// TEMPLATE: GAMEMD 0x6C07C0
// TClassFactory<AirstrikeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C07D0
// TClassFactory<AirstrikeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0840
// TClassFactory<AirstrikeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0860
// TClassFactory<AirstrikeClass>::Release
// TEMPLATE: GAMEMD 0x6C0910
// TClassFactory<AirstrikeClass>::LockServer
template class TClassFactory<AirstrikeClass>;

// VTABLE: GAMEMD 0x7F3918 -- TClassFactory<SpawnManagerClass>
class SpawnManagerClass;
// TEMPLATE: GAMEMD 0x6C0940
// TClassFactory<SpawnManagerClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0950
// TClassFactory<SpawnManagerClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C09C0
// TClassFactory<SpawnManagerClass>::AddRef
// TEMPLATE: GAMEMD 0x6C09E0
// TClassFactory<SpawnManagerClass>::Release
// TEMPLATE: GAMEMD 0x6C0A90
// TClassFactory<SpawnManagerClass>::LockServer
template class TClassFactory<SpawnManagerClass>;

// VTABLE: GAMEMD 0x7F3930 -- TClassFactory<SlaveManagerClass>
class SlaveManagerClass;
// TEMPLATE: GAMEMD 0x6C0AC0
// TClassFactory<SlaveManagerClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0AD0
// TClassFactory<SlaveManagerClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0B40
// TClassFactory<SlaveManagerClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0B60
// TClassFactory<SlaveManagerClass>::Release
// TEMPLATE: GAMEMD 0x6C0C10
// TClassFactory<SlaveManagerClass>::LockServer
template class TClassFactory<SlaveManagerClass>;

// VTABLE: GAMEMD 0x7F3948 -- TClassFactory<CaptureManagerClass>
class CaptureManagerClass;
// TEMPLATE: GAMEMD 0x6C0C40
// TClassFactory<CaptureManagerClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0C50
// TClassFactory<CaptureManagerClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0CC0
// TClassFactory<CaptureManagerClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0CE0
// TClassFactory<CaptureManagerClass>::Release
// TEMPLATE: GAMEMD 0x6C0D90
// TClassFactory<CaptureManagerClass>::LockServer
template class TClassFactory<CaptureManagerClass>;

// VTABLE: GAMEMD 0x7F3960 -- TClassFactory<DiskLaserClass>
class DiskLaserClass;
// TEMPLATE: GAMEMD 0x6C0DC0
// TClassFactory<DiskLaserClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0DD0
// TClassFactory<DiskLaserClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0E40
// TClassFactory<DiskLaserClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0E60
// TClassFactory<DiskLaserClass>::Release
// TEMPLATE: GAMEMD 0x6C0F10
// TClassFactory<DiskLaserClass>::LockServer
template class TClassFactory<DiskLaserClass>;

// VTABLE: GAMEMD 0x7F3978 -- TClassFactory<ParasiteClass>
class ParasiteClass;
// TEMPLATE: GAMEMD 0x6C0F40
// TClassFactory<ParasiteClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0F50
// TClassFactory<ParasiteClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0FC0
// TClassFactory<ParasiteClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0FE0
// TClassFactory<ParasiteClass>::Release
// TEMPLATE: GAMEMD 0x6C1090
// TClassFactory<ParasiteClass>::LockServer
template class TClassFactory<ParasiteClass>;

// VTABLE: GAMEMD 0x7F3990 -- TClassFactory<BombClass>
class BombClass;
// TEMPLATE: GAMEMD 0x6C10C0
// TClassFactory<BombClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C10D0
// TClassFactory<BombClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1140
// TClassFactory<BombClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1160
// TClassFactory<BombClass>::Release
// TEMPLATE: GAMEMD 0x6C1210
// TClassFactory<BombClass>::LockServer
template class TClassFactory<BombClass>;

// VTABLE: GAMEMD 0x7F39A8 -- TClassFactory<RadSiteClass>
class RadSiteClass;
// TEMPLATE: GAMEMD 0x6C1240
// TClassFactory<RadSiteClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1250
// TClassFactory<RadSiteClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C12C0
// TClassFactory<RadSiteClass>::AddRef
// TEMPLATE: GAMEMD 0x6C12E0
// TClassFactory<RadSiteClass>::Release
// TEMPLATE: GAMEMD 0x6C1390
// TClassFactory<RadSiteClass>::LockServer
template class TClassFactory<RadSiteClass>;

// VTABLE: GAMEMD 0x7F39C0 -- TClassFactory<TEventClass>
class TEventClass;
// TEMPLATE: GAMEMD 0x6C13C0
// TClassFactory<TEventClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C13D0
// TClassFactory<TEventClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1440
// TClassFactory<TEventClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1460
// TClassFactory<TEventClass>::Release
// TEMPLATE: GAMEMD 0x6C1510
// TClassFactory<TEventClass>::LockServer
template class TClassFactory<TEventClass>;

// VTABLE: GAMEMD 0x7F39D8 -- TClassFactory<VoxelAnimTypeClass>
class VoxelAnimTypeClass;
// TEMPLATE: GAMEMD 0x6C1540
// TClassFactory<VoxelAnimTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1550
// TClassFactory<VoxelAnimTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C15C0
// TClassFactory<VoxelAnimTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C15E0
// TClassFactory<VoxelAnimTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C1690
// TClassFactory<VoxelAnimTypeClass>::LockServer
template class TClassFactory<VoxelAnimTypeClass>;

// VTABLE: GAMEMD 0x7F39F0 -- TClassFactory<VoxelAnimClass>
class VoxelAnimClass;
// TEMPLATE: GAMEMD 0x6C16C0
// TClassFactory<VoxelAnimClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C16D0
// TClassFactory<VoxelAnimClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1740
// TClassFactory<VoxelAnimClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1760
// TClassFactory<VoxelAnimClass>::Release
// TEMPLATE: GAMEMD 0x6C1810
// TClassFactory<VoxelAnimClass>::LockServer
template class TClassFactory<VoxelAnimClass>;

// VTABLE: GAMEMD 0x7F3A08 -- TClassFactory<TActionClass>
class TActionClass;
// TEMPLATE: GAMEMD 0x6C1840
// TClassFactory<TActionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1850
// TClassFactory<TActionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C18C0
// TClassFactory<TActionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C18E0
// TClassFactory<TActionClass>::Release
// TEMPLATE: GAMEMD 0x6C1990
// TClassFactory<TActionClass>::LockServer
template class TClassFactory<TActionClass>;

// VTABLE: GAMEMD 0x7F3A20 -- TClassFactory<TriggerClass>
class TriggerClass;
// TEMPLATE: GAMEMD 0x6C19C0
// TClassFactory<TriggerClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C19D0
// TClassFactory<TriggerClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1A40
// TClassFactory<TriggerClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1A60
// TClassFactory<TriggerClass>::Release
// TEMPLATE: GAMEMD 0x6C1B10
// TClassFactory<TriggerClass>::LockServer
template class TClassFactory<TriggerClass>;

// VTABLE: GAMEMD 0x7F3A38 -- TClassFactory<TriggerTypeClass>
class TriggerTypeClass;
// TEMPLATE: GAMEMD 0x6C1B40
// TClassFactory<TriggerTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1B50
// TClassFactory<TriggerTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1BC0
// TClassFactory<TriggerTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1BE0
// TClassFactory<TriggerTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C1C90
// TClassFactory<TriggerTypeClass>::LockServer
template class TClassFactory<TriggerTypeClass>;

// VTABLE: GAMEMD 0x7F3A50 -- TClassFactory<ScriptClass>
class ScriptClass;
// TEMPLATE: GAMEMD 0x6C1CC0
// TClassFactory<ScriptClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1CD0
// TClassFactory<ScriptClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1D40
// TClassFactory<ScriptClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1D60
// TClassFactory<ScriptClass>::Release
// TEMPLATE: GAMEMD 0x6C1E10
// TClassFactory<ScriptClass>::LockServer
template class TClassFactory<ScriptClass>;

// VTABLE: GAMEMD 0x7F3A68 -- TClassFactory<ScriptTypeClass>
class ScriptTypeClass;
// TEMPLATE: GAMEMD 0x6C1E40
// TClassFactory<ScriptTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1E50
// TClassFactory<ScriptTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1EC0
// TClassFactory<ScriptTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1EE0
// TClassFactory<ScriptTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C1F90
// TClassFactory<ScriptTypeClass>::LockServer
template class TClassFactory<ScriptTypeClass>;

// VTABLE: GAMEMD 0x7F3A80 -- TClassFactory<TagClass>
class TagClass;
// TEMPLATE: GAMEMD 0x6C1FC0
// TClassFactory<TagClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1FD0
// TClassFactory<TagClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2040
// TClassFactory<TagClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2060
// TClassFactory<TagClass>::Release
// TEMPLATE: GAMEMD 0x6C2110
// TClassFactory<TagClass>::LockServer
template class TClassFactory<TagClass>;

// VTABLE: GAMEMD 0x7F3A98 -- TClassFactory<TagTypeClass>
class TagTypeClass;
// TEMPLATE: GAMEMD 0x6C2140
// TClassFactory<TagTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2150
// TClassFactory<TagTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C21C0
// TClassFactory<TagTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C21E0
// TClassFactory<TagTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C2290
// TClassFactory<TagTypeClass>::LockServer
template class TClassFactory<TagTypeClass>;

// VTABLE: GAMEMD 0x7F3AB0 -- TClassFactory<TeamClass>
class TeamClass;
// TEMPLATE: GAMEMD 0x6C22C0
// TClassFactory<TeamClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C22D0
// TClassFactory<TeamClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2340
// TClassFactory<TeamClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2360
// TClassFactory<TeamClass>::Release
// TEMPLATE: GAMEMD 0x6C2410
// TClassFactory<TeamClass>::LockServer
template class TClassFactory<TeamClass>;

// VTABLE: GAMEMD 0x7F3AC8 -- TClassFactory<TeamTypeClass>
class TeamTypeClass;
// TEMPLATE: GAMEMD 0x6C2440
// TClassFactory<TeamTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2450
// TClassFactory<TeamTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C24C0
// TClassFactory<TeamTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C24E0
// TClassFactory<TeamTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C2590
// TClassFactory<TeamTypeClass>::LockServer
template class TClassFactory<TeamTypeClass>;

// VTABLE: GAMEMD 0x7F3AE0 -- TClassFactory<TaskForceClass>
class TaskForceClass;
// TEMPLATE: GAMEMD 0x6C25C0
// TClassFactory<TaskForceClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C25D0
// TClassFactory<TaskForceClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2640
// TClassFactory<TaskForceClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2660
// TClassFactory<TaskForceClass>::Release
// TEMPLATE: GAMEMD 0x6C2710
// TClassFactory<TaskForceClass>::LockServer
template class TClassFactory<TaskForceClass>;

// VTABLE: GAMEMD 0x7F3AF8 -- TClassFactory<UnitTypeClass>
class UnitTypeClass;
// TEMPLATE: GAMEMD 0x6C2740
// TClassFactory<UnitTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2750
// TClassFactory<UnitTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C27C0
// TClassFactory<UnitTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C27E0
// TClassFactory<UnitTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C2890
// TClassFactory<UnitTypeClass>::LockServer
template class TClassFactory<UnitTypeClass>;

// VTABLE: GAMEMD 0x7F3B10 -- TClassFactory<BuildingTypeClass>
class BuildingTypeClass;
// TEMPLATE: GAMEMD 0x6C28C0
// TClassFactory<BuildingTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C28D0
// TClassFactory<BuildingTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2940
// TClassFactory<BuildingTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2960
// TClassFactory<BuildingTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C2A10
// TClassFactory<BuildingTypeClass>::LockServer
template class TClassFactory<BuildingTypeClass>;

// VTABLE: GAMEMD 0x7F3B28 -- TClassFactory<AircraftTypeClass>
class AircraftTypeClass;
// TEMPLATE: GAMEMD 0x6C2A40
// TClassFactory<AircraftTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2A50
// TClassFactory<AircraftTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2AC0
// TClassFactory<AircraftTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2AE0
// TClassFactory<AircraftTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C2B90
// TClassFactory<AircraftTypeClass>::LockServer
template class TClassFactory<AircraftTypeClass>;

// VTABLE: GAMEMD 0x7F3B40 -- TClassFactory<InfantryTypeClass>
class InfantryTypeClass;
// TEMPLATE: GAMEMD 0x6C2BC0
// TClassFactory<InfantryTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2BD0
// TClassFactory<InfantryTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2C40
// TClassFactory<InfantryTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2C60
// TClassFactory<InfantryTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C2D10
// TClassFactory<InfantryTypeClass>::LockServer
template class TClassFactory<InfantryTypeClass>;

// VTABLE: GAMEMD 0x7F3B58 -- TClassFactory<BulletTypeClass>
class BulletTypeClass;
// TEMPLATE: GAMEMD 0x6C2D40
// TClassFactory<BulletTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2D50
// TClassFactory<BulletTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2DC0
// TClassFactory<BulletTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2DE0
// TClassFactory<BulletTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C2E90
// TClassFactory<BulletTypeClass>::LockServer
template class TClassFactory<BulletTypeClass>;

// VTABLE: GAMEMD 0x7F3B70 -- TClassFactory<IsometricTileTypeClass>
class IsometricTileTypeClass;
// TEMPLATE: GAMEMD 0x6C2EC0
// TClassFactory<IsometricTileTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2ED0
// TClassFactory<IsometricTileTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2F40
// TClassFactory<IsometricTileTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2F60
// TClassFactory<IsometricTileTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C3010
// TClassFactory<IsometricTileTypeClass>::LockServer
template class TClassFactory<IsometricTileTypeClass>;

// VTABLE: GAMEMD 0x7F3B88 -- TClassFactory<OverlayTypeClass>
class OverlayTypeClass;
// TEMPLATE: GAMEMD 0x6C3040
// TClassFactory<OverlayTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3050
// TClassFactory<OverlayTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C30C0
// TClassFactory<OverlayTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C30E0
// TClassFactory<OverlayTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C3190
// TClassFactory<OverlayTypeClass>::LockServer
template class TClassFactory<OverlayTypeClass>;

// VTABLE: GAMEMD 0x7F3BA0 -- TClassFactory<SmudgeTypeClass>
class SmudgeTypeClass;
// TEMPLATE: GAMEMD 0x6C31C0
// TClassFactory<SmudgeTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C31D0
// TClassFactory<SmudgeTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3240
// TClassFactory<SmudgeTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3260
// TClassFactory<SmudgeTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C3310
// TClassFactory<SmudgeTypeClass>::LockServer
template class TClassFactory<SmudgeTypeClass>;

// VTABLE: GAMEMD 0x7F3BB8 -- TClassFactory<UnitClass>
class UnitClass;
// TEMPLATE: GAMEMD 0x6C3340
// TClassFactory<UnitClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3350
// TClassFactory<UnitClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C33C0
// TClassFactory<UnitClass>::AddRef
// TEMPLATE: GAMEMD 0x6C33E0
// TClassFactory<UnitClass>::Release
// TEMPLATE: GAMEMD 0x6C3490
// TClassFactory<UnitClass>::LockServer
template class TClassFactory<UnitClass>;

// VTABLE: GAMEMD 0x7F3BD0 -- TClassFactory<BuildingClass>
class BuildingClass;
// TEMPLATE: GAMEMD 0x6C34C0
// TClassFactory<BuildingClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C34D0
// TClassFactory<BuildingClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3540
// TClassFactory<BuildingClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3560
// TClassFactory<BuildingClass>::Release
// TEMPLATE: GAMEMD 0x6C3610
// TClassFactory<BuildingClass>::LockServer
template class TClassFactory<BuildingClass>;

// VTABLE: GAMEMD 0x7F3BE8 -- TClassFactory<AircraftClass>
class AircraftClass;
// TEMPLATE: GAMEMD 0x6C3640
// TClassFactory<AircraftClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3650
// TClassFactory<AircraftClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C36C0
// TClassFactory<AircraftClass>::AddRef
// TEMPLATE: GAMEMD 0x6C36E0
// TClassFactory<AircraftClass>::Release
// TEMPLATE: GAMEMD 0x6C3790
// TClassFactory<AircraftClass>::LockServer
template class TClassFactory<AircraftClass>;

// VTABLE: GAMEMD 0x7F3C00 -- TClassFactory<InfantryClass>
class InfantryClass;
// TEMPLATE: GAMEMD 0x6C37C0
// TClassFactory<InfantryClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C37D0
// TClassFactory<InfantryClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3840
// TClassFactory<InfantryClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3860
// TClassFactory<InfantryClass>::Release
// TEMPLATE: GAMEMD 0x6C3910
// TClassFactory<InfantryClass>::LockServer
template class TClassFactory<InfantryClass>;

// VTABLE: GAMEMD 0x7F3C18 -- TClassFactory<AnimClass>
class AnimClass;
// TEMPLATE: GAMEMD 0x6C3940
// TClassFactory<AnimClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3950
// TClassFactory<AnimClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C39C0
// TClassFactory<AnimClass>::AddRef
// TEMPLATE: GAMEMD 0x6C39E0
// TClassFactory<AnimClass>::Release
// TEMPLATE: GAMEMD 0x6C3A90
// TClassFactory<AnimClass>::LockServer
template class TClassFactory<AnimClass>;

// VTABLE: GAMEMD 0x7F3C30 -- TClassFactory<AnimTypeClass>
class AnimTypeClass;
// TEMPLATE: GAMEMD 0x6C3AC0
// TClassFactory<AnimTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3AD0
// TClassFactory<AnimTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3B40
// TClassFactory<AnimTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3B60
// TClassFactory<AnimTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C3C10
// TClassFactory<AnimTypeClass>::LockServer
template class TClassFactory<AnimTypeClass>;

// VTABLE: GAMEMD 0x7F3C48 -- TClassFactory<HouseTypeClass>
class HouseTypeClass;
// TEMPLATE: GAMEMD 0x6C3C40
// TClassFactory<HouseTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3C50
// TClassFactory<HouseTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3CC0
// TClassFactory<HouseTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3CE0
// TClassFactory<HouseTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C3D90
// TClassFactory<HouseTypeClass>::LockServer
template class TClassFactory<HouseTypeClass>;

// VTABLE: GAMEMD 0x7F3C60 -- TClassFactory<HouseClass>
class HouseClass;
// TEMPLATE: GAMEMD 0x6C3DC0
// TClassFactory<HouseClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3DD0
// TClassFactory<HouseClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3E40
// TClassFactory<HouseClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3E60
// TClassFactory<HouseClass>::Release
// TEMPLATE: GAMEMD 0x6C3F10
// TClassFactory<HouseClass>::LockServer
template class TClassFactory<HouseClass>;

// VTABLE: GAMEMD 0x7F3C78 -- TClassFactory<DriveLocomotionClass>
class DriveLocomotionClass;
// TEMPLATE: GAMEMD 0x6C3F40
// TClassFactory<DriveLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3F50
// TClassFactory<DriveLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3FC0
// TClassFactory<DriveLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3FE0
// TClassFactory<DriveLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4090
// TClassFactory<DriveLocomotionClass>::LockServer
template class TClassFactory<DriveLocomotionClass>;

// VTABLE: GAMEMD 0x7F3C90 -- TClassFactory<JumpjetLocomotionClass>
class JumpjetLocomotionClass;
// TEMPLATE: GAMEMD 0x6C40C0
// TClassFactory<JumpjetLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C40D0
// TClassFactory<JumpjetLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4140
// TClassFactory<JumpjetLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4160
// TClassFactory<JumpjetLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4210
// TClassFactory<JumpjetLocomotionClass>::LockServer
template class TClassFactory<JumpjetLocomotionClass>;

// VTABLE: GAMEMD 0x7F3CA8 -- TClassFactory<HoverLocomotionClass>
class HoverLocomotionClass;
// TEMPLATE: GAMEMD 0x6C4240
// TClassFactory<HoverLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4250
// TClassFactory<HoverLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C42C0
// TClassFactory<HoverLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C42E0
// TClassFactory<HoverLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4390
// TClassFactory<HoverLocomotionClass>::LockServer
template class TClassFactory<HoverLocomotionClass>;

// VTABLE: GAMEMD 0x7F3CC0 -- TClassFactory<RocketLocomotionClass>
class RocketLocomotionClass;
// TEMPLATE: GAMEMD 0x6C43C0
// TClassFactory<RocketLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C43D0
// TClassFactory<RocketLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4440
// TClassFactory<RocketLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4460
// TClassFactory<RocketLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4510
// TClassFactory<RocketLocomotionClass>::LockServer
template class TClassFactory<RocketLocomotionClass>;

// VTABLE: GAMEMD 0x7F3CD8 -- TClassFactory<TunnelLocomotionClass>
class TunnelLocomotionClass;
// TEMPLATE: GAMEMD 0x6C4540
// TClassFactory<TunnelLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4550
// TClassFactory<TunnelLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C45C0
// TClassFactory<TunnelLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C45E0
// TClassFactory<TunnelLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4690
// TClassFactory<TunnelLocomotionClass>::LockServer
template class TClassFactory<TunnelLocomotionClass>;

// VTABLE: GAMEMD 0x7F3CF0 -- TClassFactory<WalkLocomotionClass>
class WalkLocomotionClass;
// TEMPLATE: GAMEMD 0x6C46C0
// TClassFactory<WalkLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C46D0
// TClassFactory<WalkLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4740
// TClassFactory<WalkLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4760
// TClassFactory<WalkLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4810
// TClassFactory<WalkLocomotionClass>::LockServer
template class TClassFactory<WalkLocomotionClass>;

// VTABLE: GAMEMD 0x7F3D08 -- TClassFactory<DropPodLocomotionClass>
class DropPodLocomotionClass;
// TEMPLATE: GAMEMD 0x6C4840
// TClassFactory<DropPodLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4850
// TClassFactory<DropPodLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C48C0
// TClassFactory<DropPodLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C48E0
// TClassFactory<DropPodLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4990
// TClassFactory<DropPodLocomotionClass>::LockServer
template class TClassFactory<DropPodLocomotionClass>;

// VTABLE: GAMEMD 0x7F3D20 -- TClassFactory<FlyLocomotionClass>
class FlyLocomotionClass;
// TEMPLATE: GAMEMD 0x6C49C0
// TClassFactory<FlyLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C49D0
// TClassFactory<FlyLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4A40
// TClassFactory<FlyLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4A60
// TClassFactory<FlyLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4B10
// TClassFactory<FlyLocomotionClass>::LockServer
template class TClassFactory<FlyLocomotionClass>;

// VTABLE: GAMEMD 0x7F3D38 -- TClassFactory<TeleportLocomotionClass>
class TeleportLocomotionClass;
// TEMPLATE: GAMEMD 0x6C4B40
// TClassFactory<TeleportLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4B50
// TClassFactory<TeleportLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4BC0
// TClassFactory<TeleportLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4BE0
// TClassFactory<TeleportLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4C90
// TClassFactory<TeleportLocomotionClass>::LockServer
template class TClassFactory<TeleportLocomotionClass>;

// VTABLE: GAMEMD 0x7F3D50 -- TClassFactory<MechLocomotionClass>
class MechLocomotionClass;
// TEMPLATE: GAMEMD 0x6C4CC0
// TClassFactory<MechLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4CD0
// TClassFactory<MechLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4D40
// TClassFactory<MechLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4D60
// TClassFactory<MechLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4E10
// TClassFactory<MechLocomotionClass>::LockServer
template class TClassFactory<MechLocomotionClass>;

// VTABLE: GAMEMD 0x7F3D68 -- TClassFactory<ShipLocomotionClass>
class ShipLocomotionClass;
// TEMPLATE: GAMEMD 0x6C4E40
// TClassFactory<ShipLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4E50
// TClassFactory<ShipLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4EC0
// TClassFactory<ShipLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4EE0
// TClassFactory<ShipLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x6C4F90
// TClassFactory<ShipLocomotionClass>::LockServer
template class TClassFactory<ShipLocomotionClass>;

// VTABLE: GAMEMD 0x7F3D80 -- TClassFactory<BulletClass>
class BulletClass;
// TEMPLATE: GAMEMD 0x6C4FC0
// TClassFactory<BulletClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4FD0
// TClassFactory<BulletClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5040
// TClassFactory<BulletClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5060
// TClassFactory<BulletClass>::Release
// TEMPLATE: GAMEMD 0x6C5110
// TClassFactory<BulletClass>::LockServer
template class TClassFactory<BulletClass>;

// VTABLE: GAMEMD 0x7F3D98 -- TClassFactory<FactoryClass>
class FactoryClass;
// TEMPLATE: GAMEMD 0x6C5140
// TClassFactory<FactoryClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5150
// TClassFactory<FactoryClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C51C0
// TClassFactory<FactoryClass>::AddRef
// TEMPLATE: GAMEMD 0x6C51E0
// TClassFactory<FactoryClass>::Release
// TEMPLATE: GAMEMD 0x6C5290
// TClassFactory<FactoryClass>::LockServer
template class TClassFactory<FactoryClass>;

// VTABLE: GAMEMD 0x7F3DB0 -- TClassFactory<WarheadTypeClass>
class WarheadTypeClass;
// TEMPLATE: GAMEMD 0x6C52C0
// TClassFactory<WarheadTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C52D0
// TClassFactory<WarheadTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5340
// TClassFactory<WarheadTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5360
// TClassFactory<WarheadTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C5410
// TClassFactory<WarheadTypeClass>::LockServer
template class TClassFactory<WarheadTypeClass>;

// VTABLE: GAMEMD 0x7F3DC8 -- TClassFactory<WeaponTypeClass>
class WeaponTypeClass;
// TEMPLATE: GAMEMD 0x6C5440
// TClassFactory<WeaponTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5450
// TClassFactory<WeaponTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C54C0
// TClassFactory<WeaponTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C54E0
// TClassFactory<WeaponTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C5590
// TClassFactory<WeaponTypeClass>::LockServer
template class TClassFactory<WeaponTypeClass>;

// VTABLE: GAMEMD 0x7F3DE0 -- TClassFactory<ParticleClass>
class ParticleClass;
// TEMPLATE: GAMEMD 0x6C55C0
// TClassFactory<ParticleClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C55D0
// TClassFactory<ParticleClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5640
// TClassFactory<ParticleClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5660
// TClassFactory<ParticleClass>::Release
// TEMPLATE: GAMEMD 0x6C5710
// TClassFactory<ParticleClass>::LockServer
template class TClassFactory<ParticleClass>;

// VTABLE: GAMEMD 0x7F3DF8 -- TClassFactory<ParticleTypeClass>
class ParticleTypeClass;
// TEMPLATE: GAMEMD 0x6C5740
// TClassFactory<ParticleTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5750
// TClassFactory<ParticleTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C57C0
// TClassFactory<ParticleTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C57E0
// TClassFactory<ParticleTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C5890
// TClassFactory<ParticleTypeClass>::LockServer
template class TClassFactory<ParticleTypeClass>;

// VTABLE: GAMEMD 0x7F3E10 -- TClassFactory<ParticleSystemClass>
class ParticleSystemClass;
// TEMPLATE: GAMEMD 0x6C58C0
// TClassFactory<ParticleSystemClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C58D0
// TClassFactory<ParticleSystemClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5940
// TClassFactory<ParticleSystemClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5960
// TClassFactory<ParticleSystemClass>::Release
// TEMPLATE: GAMEMD 0x6C5A10
// TClassFactory<ParticleSystemClass>::LockServer
template class TClassFactory<ParticleSystemClass>;

// VTABLE: GAMEMD 0x7F3E28 -- TClassFactory<ParticleSystemTypeClass>
class ParticleSystemTypeClass;
// TEMPLATE: GAMEMD 0x6C5A40
// TClassFactory<ParticleSystemTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5A50
// TClassFactory<ParticleSystemTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5AC0
// TClassFactory<ParticleSystemTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5AE0
// TClassFactory<ParticleSystemTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C5B90
// TClassFactory<ParticleSystemTypeClass>::LockServer
template class TClassFactory<ParticleSystemTypeClass>;

// VTABLE: GAMEMD 0x7F3E40 -- TClassFactory<AITriggerTypeClass>
class AITriggerTypeClass;
// TEMPLATE: GAMEMD 0x6C5BC0
// TClassFactory<AITriggerTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5BD0
// TClassFactory<AITriggerTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5C40
// TClassFactory<AITriggerTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5C60
// TClassFactory<AITriggerTypeClass>::Release
// TEMPLATE: GAMEMD 0x6C5D10
// TClassFactory<AITriggerTypeClass>::LockServer
template class TClassFactory<AITriggerTypeClass>;

// VTABLE: GAMEMD 0x7F3E58 -- TClassFactory<NeuronClass>
class NeuronClass;
// TEMPLATE: GAMEMD 0x6C5D40
// TClassFactory<NeuronClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5D50
// TClassFactory<NeuronClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5DC0
// TClassFactory<NeuronClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5DE0
// TClassFactory<NeuronClass>::Release
// TEMPLATE: GAMEMD 0x6C5E90
// TClassFactory<NeuronClass>::LockServer
template class TClassFactory<NeuronClass>;

// VTABLE: GAMEMD 0x7F3E70 -- TClassFactory<FoggedObjectClass>
class FoggedObjectClass;
// TEMPLATE: GAMEMD 0x6C5EC0
// TClassFactory<FoggedObjectClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5ED0
// TClassFactory<FoggedObjectClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5F40
// TClassFactory<FoggedObjectClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5F60
// TClassFactory<FoggedObjectClass>::Release
// TEMPLATE: GAMEMD 0x6C6010
// TClassFactory<FoggedObjectClass>::LockServer
template class TClassFactory<FoggedObjectClass>;

// VTABLE: GAMEMD 0x7F3E88 -- TClassFactory<AlphaShapeClass>
class AlphaShapeClass;
// TEMPLATE: GAMEMD 0x6C6040
// TClassFactory<AlphaShapeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C6050
// TClassFactory<AlphaShapeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C60C0
// TClassFactory<AlphaShapeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C60E0
// TClassFactory<AlphaShapeClass>::Release
// TEMPLATE: GAMEMD 0x6C6190
// TClassFactory<AlphaShapeClass>::LockServer
template class TClassFactory<AlphaShapeClass>;

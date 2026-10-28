// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// File-scope DynamicVectorClass<T> objects whose exit-time destructors were
// emitted as stand-alone stubs: each stub restores the VectorClass<T> vtable,
// frees the array when it is owned, and clears the flag and capacity. T is the
// element type of the vector's RTTI TypeDescriptor, read through the vptr stored by the
// matching initialiser. The initialisers (the __xc table entries, which also
// register these stubs with atexit) are left to the translation-unit migration;
// they compile here as a by-product and are not claimed. The globals' retail
// addresses are bound for verification through the per-TU symbol map.
#include "vector_class_operations.h"

class AITriggerTypeClass;
class AbstractClass;
class AbstractTypeClass;
class AircraftClass;
class AircraftTypeClass;
class AirstrikeClass;
class AlphaShapeClass;
class AnimClass;
class AnimTypeClass;
class BuildingClass;
class BuildingLightClass;
class BuildingTypeClass;
class BulletClass;
class BulletTypeClass;
class CampaignClass;
class CaptureManagerClass;
class ColorScheme;
class CommandClass;
class DiskLaserClass;
class EBolt;
class EgoClass;
class FactoryClass;
class FootClass;
class HouseClass;
class HouseTypeClass;
class InfantryClass;
class InfantryTypeClass;
class IsometricTileClass;
class IsometricTileTypeClass;
class LightConvertClass;
class LightSourceClass;
class LineTrail;
class MixFileClass;
class MovieHandle;
class ObjectClass;
class OverlayClass;
class OverlayTypeClass;
class ParasiteClass;
class ParticleClass;
class ParticleSystemClass;
class ParticleSystemTypeClass;
class ParticleTypeClass;
class RadBeam;
class RadSiteClass;
class ScriptClass;
class ScriptTypeClass;
class SideClass;
class SlaveManagerClass;
class SmudgeClass;
class SmudgeTypeClass;
class SpawnManagerClass;
class SpotLightClass;
class SuperClass;
class SuperWeaponTypeClass;
class TActionClass;
class TEventClass;
class TagClass;
class TaskForceClass;
class TeamClass;
class TeamTypeClass;
class TechnoClass;
class TechnoTypeClass;
class TemporalClass;
class TerrainClass;
class TerrainTypeClass;
class TiberiumClass;
class TriggerClass;
class TriggerTypeClass;
class TubeClass;
class UnitClass;
class UnitTypeClass;
class VocClass;
class VoxClass;
class VoxelAnimClass;
class VoxelAnimTypeClass;
class WarheadTypeClass;
class WaveClass;
class WaypointPathClass;
class WeaponTypeClass;
struct HWND__;

// GLOBAL: GAMEMD 0x0087F658
// SYNTHETIC: GAMEMD 0x0040BE10 -- exit-time destructor stub of DAT_0087F658
// SYNTHETIC: GAMEMD 0x0040BDD0 -- initialiser of DAT_0087F658
DynamicVectorClass<const CommandClass*> DAT_0087F658;

// GLOBAL: GAMEMD 0x0087F698
// SYNTHETIC: GAMEMD 0x0040C1F0 -- exit-time destructor stub of DAT_0087F698
// SYNTHETIC: GAMEMD 0x0040C1B0 -- initialiser of DAT_0087F698
DynamicVectorClass<LightConvertClass*> DAT_0087F698;

// GLOBAL: GAMEMD 0x0087F750
// SYNTHETIC: GAMEMD 0x0040C7E0 -- exit-time destructor stub of DAT_0087F750
// SYNTHETIC: GAMEMD 0x0040C7A0 -- initialiser of DAT_0087F750
DynamicVectorClass<IsometricTileClass*> DAT_0087F750;

// GLOBAL: GAMEMD 0x00884D90
// SYNTHETIC: GAMEMD 0x0040D380 -- exit-time destructor stub of DAT_00884D90
// SYNTHETIC: GAMEMD 0x0040D340 -- initialiser of DAT_00884D90
DynamicVectorClass<MixFileClass*> DAT_00884D90;

// GLOBAL: GAMEMD 0x00884DC0
// SYNTHETIC: GAMEMD 0x0040D400 -- exit-time destructor stub of DAT_00884DC0
// SYNTHETIC: GAMEMD 0x0040D3C0 -- initialiser of DAT_00884DC0
DynamicVectorClass<MixFileClass*> DAT_00884DC0;

// GLOBAL: GAMEMD 0x00884DA8
// SYNTHETIC: GAMEMD 0x0040D480 -- exit-time destructor stub of DAT_00884DA8
// SYNTHETIC: GAMEMD 0x0040D440 -- initialiser of DAT_00884DA8
DynamicVectorClass<MixFileClass*> DAT_00884DA8;

// GLOBAL: GAMEMD 0x00884DE0
// SYNTHETIC: GAMEMD 0x0040D500 -- exit-time destructor stub of DAT_00884DE0
// SYNTHETIC: GAMEMD 0x0040D4C0 -- initialiser of DAT_00884DE0
DynamicVectorClass<MixFileClass*> DAT_00884DE0;

// GLOBAL: GAMEMD 0x008872B0
// SYNTHETIC: GAMEMD 0x0040E7B0 -- exit-time destructor stub of DAT_008872B0
// SYNTHETIC: GAMEMD 0x0040E770 -- initialiser of DAT_008872B0
DynamicVectorClass<ScriptClass*> DAT_008872B0;

// GLOBAL: GAMEMD 0x00887388
// SYNTHETIC: GAMEMD 0x0040EE80 -- exit-time destructor stub of DAT_00887388
// SYNTHETIC: GAMEMD 0x0040EE40 -- initialiser of DAT_00887388
DynamicVectorClass<VoxelAnimClass*> DAT_00887388;

// GLOBAL: GAMEMD 0x008874C0
// SYNTHETIC: GAMEMD 0x0040F4D0 -- exit-time destructor stub of DAT_008874C0
// SYNTHETIC: GAMEMD 0x0040F490 -- initialiser of DAT_008874C0
DynamicVectorClass<WarheadTypeClass*> DAT_008874C0;

// GLOBAL: GAMEMD 0x00887568
// SYNTHETIC: GAMEMD 0x0040FB70 -- exit-time destructor stub of DAT_00887568
// SYNTHETIC: GAMEMD 0x0040FB30 -- initialiser of DAT_00887568
DynamicVectorClass<WeaponTypeClass*> DAT_00887568;

// GLOBAL: GAMEMD 0x00889FB8
// SYNTHETIC: GAMEMD 0x0041D2C0 -- exit-time destructor stub of DAT_00889FB8
// SYNTHETIC: GAMEMD 0x0041D280 -- initialiser of DAT_00889FB8
DynamicVectorClass<AirstrikeClass*> DAT_00889FB8;

// GLOBAL: GAMEMD 0x0088A0F0

// GLOBAL: GAMEMD 0x0089E0F0

// GLOBAL: GAMEMD 0x008A0208

// GLOBAL: GAMEMD 0x008A0E88

// GLOBAL: GAMEMD 0x008A3770
// SYNTHETIC: GAMEMD 0x004C3C50 -- exit-time destructor stub of DAT_008A3770
// SYNTHETIC: GAMEMD 0x004C3C10 -- initialiser of DAT_008A3770
DynamicVectorClass<EgoClass*> DAT_008A3770;

// GLOBAL: GAMEMD 0x008B3DC0
// SYNTHETIC: GAMEMD 0x004D31A0 -- exit-time destructor stub of DAT_008B3DC0
// SYNTHETIC: GAMEMD 0x004D3160 -- initialiser of DAT_008B3DC0
DynamicVectorClass<FootClass*> DAT_008B3DC0;

// GLOBAL: GAMEMD 0x00A8B200
// SYNTHETIC: GAMEMD 0x004E6520 -- exit-time destructor stub of DAT_00A8B200
// SYNTHETIC: GAMEMD 0x004E64E0 -- initialiser of DAT_00A8B200
DynamicVectorClass<AITriggerTypeClass*> DAT_00A8B200;

// GLOBAL: GAMEMD 0x008B4178
// SYNTHETIC: GAMEMD 0x004E65A0 -- exit-time destructor stub of DAT_008B4178
// SYNTHETIC: GAMEMD 0x004E6560 -- initialiser of DAT_008B4178
DynamicVectorClass<TriggerTypeClass*> DAT_008B4178;

// GLOBAL: GAMEMD 0x00A8EAE8
// SYNTHETIC: GAMEMD 0x004E6620 -- exit-time destructor stub of DAT_00A8EAE8
// SYNTHETIC: GAMEMD 0x004E65E0 -- initialiser of DAT_00A8EAE8
DynamicVectorClass<TriggerClass*> DAT_00A8EAE8;

// GLOBAL: GAMEMD 0x008B4190
// SYNTHETIC: GAMEMD 0x004E66A0 -- exit-time destructor stub of DAT_008B4190
// SYNTHETIC: GAMEMD 0x004E6660 -- initialiser of DAT_008B4190
DynamicVectorClass<BuildingLightClass*> DAT_008B4190;

// GLOBAL: GAMEMD 0x00A80208
// SYNTHETIC: GAMEMD 0x004E6720 -- exit-time destructor stub of DAT_00A80208
// SYNTHETIC: GAMEMD 0x004E66E0 -- initialiser of DAT_00A80208
DynamicVectorClass<ParticleSystemClass*> DAT_00A80208;

// GLOBAL: GAMEMD 0x008B4138
// SYNTHETIC: GAMEMD 0x004E67A0 -- exit-time destructor stub of DAT_008B4138
// SYNTHETIC: GAMEMD 0x004E6760 -- initialiser of DAT_008B4138
DynamicVectorClass<TubeClass*> DAT_008B4138;

// GLOBAL: GAMEMD 0x00A8EC38
// SYNTHETIC: GAMEMD 0x004E6820 -- exit-time destructor stub of DAT_00A8EC38
// SYNTHETIC: GAMEMD 0x004E67E0 -- initialiser of DAT_00A8EC38
DynamicVectorClass<WaveClass*> DAT_00A8EC38;

// GLOBAL: GAMEMD 0x00A8ED40
// SYNTHETIC: GAMEMD 0x004E68A0 -- exit-time destructor stub of DAT_00A8ED40
// SYNTHETIC: GAMEMD 0x004E6860 -- initialiser of DAT_00A8ED40
DynamicVectorClass<BulletClass*> DAT_00A8ED40;

// GLOBAL: GAMEMD 0x00A8EC50
// SYNTHETIC: GAMEMD 0x004E6920 -- exit-time destructor stub of DAT_00A8EC50
// SYNTHETIC: GAMEMD 0x004E68E0 -- initialiser of DAT_00A8EC50
DynamicVectorClass<OverlayClass*> DAT_00A8EC50;

// GLOBAL: GAMEMD 0x00A83DC8
// SYNTHETIC: GAMEMD 0x004E69A0 -- exit-time destructor stub of DAT_00A83DC8
// SYNTHETIC: GAMEMD 0x004E6960 -- initialiser of DAT_00A83DC8
DynamicVectorClass<ParticleClass*> DAT_00A83DC8;

// GLOBAL: GAMEMD 0x00A8B1E0
// SYNTHETIC: GAMEMD 0x004E6A20 -- exit-time destructor stub of DAT_00A8B1E0
// SYNTHETIC: GAMEMD 0x004E69E0 -- initialiser of DAT_00A8B1E0
DynamicVectorClass<SmudgeClass*> DAT_00A8B1E0;

// GLOBAL: GAMEMD 0x00A8E988
// SYNTHETIC: GAMEMD 0x004E6AA0 -- exit-time destructor stub of DAT_00A8E988
// SYNTHETIC: GAMEMD 0x004E6A60 -- initialiser of DAT_00A8E988
DynamicVectorClass<TerrainClass*> DAT_00A8E988;

// GLOBAL: GAMEMD 0x00A83DE8
// SYNTHETIC: GAMEMD 0x004E6B20 -- exit-time destructor stub of DAT_00A83DE8
// SYNTHETIC: GAMEMD 0x004E6AE0 -- initialiser of DAT_00A83DE8
DynamicVectorClass<InfantryClass*> DAT_00A83DE8;

// GLOBAL: GAMEMD 0x00A8EB40
// SYNTHETIC: GAMEMD 0x004E6BA0 -- exit-time destructor stub of DAT_00A8EB40
// SYNTHETIC: GAMEMD 0x004E6B60 -- initialiser of DAT_00A8EB40
DynamicVectorClass<BuildingClass*> DAT_00A8EB40;

// GLOBAL: GAMEMD 0x00A8E390
// SYNTHETIC: GAMEMD 0x004E6C20 -- exit-time destructor stub of DAT_00A8E390
// SYNTHETIC: GAMEMD 0x004E6BE0 -- initialiser of DAT_00A8E390
DynamicVectorClass<AircraftClass*> DAT_00A8E390;

// GLOBAL: GAMEMD 0x008B4108
// SYNTHETIC: GAMEMD 0x004E6CA0 -- exit-time destructor stub of DAT_008B4108
// SYNTHETIC: GAMEMD 0x004E6C60 -- initialiser of DAT_008B4108
DynamicVectorClass<UnitClass*> DAT_008B4108;

// GLOBAL: GAMEMD 0x00A80228
// SYNTHETIC: GAMEMD 0x004E6D20 -- exit-time destructor stub of DAT_00A80228
// SYNTHETIC: GAMEMD 0x004E6CE0 -- initialiser of DAT_00A80228
DynamicVectorClass<HouseClass*> DAT_00A80228;

// GLOBAL: GAMEMD 0x00A8E9A8
// SYNTHETIC: GAMEMD 0x004E6DA0 -- exit-time destructor stub of DAT_00A8E9A8
// SYNTHETIC: GAMEMD 0x004E6D60 -- initialiser of DAT_00A8E9A8
DynamicVectorClass<AnimClass*> DAT_00A8E9A8;

// GLOBAL: GAMEMD 0x00ABCA10

// GLOBAL: GAMEMD 0x00ABCB78
// SYNTHETIC: GAMEMD 0x005569E0 -- exit-time destructor stub of DAT_00ABCB78
// SYNTHETIC: GAMEMD 0x005569A0 -- initialiser of DAT_00ABCB78
DynamicVectorClass<LineTrail*> DAT_00ABCB78;

// GLOBAL: GAMEMD 0x00ABF390
// SYNTHETIC: GAMEMD 0x005BF810 -- exit-time destructor stub of DAT_00ABF390
// SYNTHETIC: GAMEMD 0x005BF7D0 -- initialiser of DAT_00ABF390
DynamicVectorClass<const char*> DAT_00ABF390;

// GLOBAL: GAMEMD 0x00ABFC90
// SYNTHETIC: GAMEMD 0x005D4C90 -- exit-time destructor stub of DAT_00ABFC90
// SYNTHETIC: GAMEMD 0x005D4C50 -- initialiser of DAT_00ABFC90
DynamicVectorClass<HWND__*> DAT_00ABFC90;

// GLOBAL: GAMEMD 0x00AC1678
// SYNTHETIC: GAMEMD 0x005FF210 -- exit-time destructor stub of DAT_00AC1678
// SYNTHETIC: GAMEMD 0x005FF1D0 -- initialiser of DAT_00AC1678
DynamicVectorClass<SpotLightClass*> DAT_00AC1678;

// GLOBAL: GAMEMD 0x00AC4910

// GLOBAL: GAMEMD 0x00B04A60
// SYNTHETIC: GAMEMD 0x006590D0 -- exit-time destructor stub of DAT_00B04A60
// SYNTHETIC: GAMEMD 0x00659090 -- initialiser of DAT_00B04A60
DynamicVectorClass<RadBeam*> DAT_00B04A60;

// GLOBAL: GAMEMD 0x00B04BD0
// SYNTHETIC: GAMEMD 0x0065B1A0 -- exit-time destructor stub of DAT_00B04BD0
// SYNTHETIC: GAMEMD 0x0065B160 -- initialiser of DAT_00B04BD0
DynamicVectorClass<RadSiteClass*> DAT_00B04BD0;

// GLOBAL: GAMEMD 0x00B054D0
// SYNTHETIC: GAMEMD 0x0068C370 -- exit-time destructor stub of DAT_00B054D0
// SYNTHETIC: GAMEMD 0x0068C330 -- initialiser of DAT_00B054D0
DynamicVectorClass<ColorScheme*> DAT_00B054D0;

// GLOBAL: GAMEMD 0x00B0B5F0
// SYNTHETIC: GAMEMD 0x006AF160 -- exit-time destructor stub of DAT_00B0B5F0
// SYNTHETIC: GAMEMD 0x006AF120 -- initialiser of DAT_00B0B5F0
DynamicVectorClass<SlaveManagerClass*> DAT_00B0B5F0;

// GLOBAL: GAMEMD 0x00B0B880

// GLOBAL: GAMEMD 0x00B0BC88
// SYNTHETIC: GAMEMD 0x006BB2A0 -- exit-time destructor stub of DAT_00B0BC88
// SYNTHETIC: GAMEMD 0x006BB260 -- initialiser of DAT_00B0BC88
DynamicVectorClass<unsigned long> DAT_00B0BC88;

// GLOBAL: GAMEMD 0x00B0E658
// SYNTHETIC: GAMEMD 0x006DCFC0 -- exit-time destructor stub of DAT_00B0E658
// SYNTHETIC: GAMEMD 0x006DCF80 -- initialiser of DAT_00B0E658
DynamicVectorClass<TActionClass*> DAT_00B0E658;

// GLOBAL: GAMEMD 0x00B0E720
// SYNTHETIC: GAMEMD 0x006E4DA0 -- exit-time destructor stub of DAT_00B0E720
// SYNTHETIC: GAMEMD 0x006E4D60 -- initialiser of DAT_00B0E720
DynamicVectorClass<TagClass*> DAT_00B0E720;

// GLOBAL: GAMEMD 0x00B0EC60

// GLOBAL: GAMEMD 0x00B0F1A0
// SYNTHETIC: GAMEMD 0x0071E660 -- exit-time destructor stub of DAT_00B0F1A0
// SYNTHETIC: GAMEMD 0x0071E620 -- initialiser of DAT_00B0F1A0
DynamicVectorClass<TEventClass*> DAT_00B0F1A0;

// GLOBAL: GAMEMD 0x00B0F4E8
// SYNTHETIC: GAMEMD 0x00721680 -- exit-time destructor stub of DAT_00B0F4E8
// SYNTHETIC: GAMEMD 0x00721640 -- initialiser of DAT_00B0F4E8
DynamicVectorClass<TiberiumClass*> DAT_00B0F4E8;

// GLOBAL: GAMEMD 0x00B0F720
// SYNTHETIC: GAMEMD 0x00725310 -- exit-time destructor stub of DAT_00B0F720
// SYNTHETIC: GAMEMD 0x007252D0 -- initialiser of DAT_00B0F720
DynamicVectorClass<AbstractClass*> DAT_00B0F720;

// GLOBAL: GAMEMD 0x00B0F670
// SYNTHETIC: GAMEMD 0x00725390 -- exit-time destructor stub of DAT_00B0F670
// SYNTHETIC: GAMEMD 0x00725350 -- initialiser of DAT_00B0F670
DynamicVectorClass<AbstractClass*> DAT_00B0F670;

// GLOBAL: GAMEMD 0x00B0F618
// SYNTHETIC: GAMEMD 0x00725410 -- exit-time destructor stub of DAT_00B0F618
// SYNTHETIC: GAMEMD 0x007253D0 -- initialiser of DAT_00B0F618
DynamicVectorClass<AbstractClass*> DAT_00B0F618;

// GLOBAL: GAMEMD 0x00B0F708
// SYNTHETIC: GAMEMD 0x00725490 -- exit-time destructor stub of DAT_00B0F708
// SYNTHETIC: GAMEMD 0x00725450 -- initialiser of DAT_00B0F708
DynamicVectorClass<AbstractClass*> DAT_00B0F708;

// GLOBAL: GAMEMD 0x00B0F5B8
// SYNTHETIC: GAMEMD 0x00725510 -- exit-time destructor stub of DAT_00B0F5B8
// SYNTHETIC: GAMEMD 0x007254D0 -- initialiser of DAT_00B0F5B8
DynamicVectorClass<AbstractClass*> DAT_00B0F5B8;

// GLOBAL: GAMEMD 0x00B0F640
// SYNTHETIC: GAMEMD 0x00725590 -- exit-time destructor stub of DAT_00B0F640
// SYNTHETIC: GAMEMD 0x00725550 -- initialiser of DAT_00B0F640
DynamicVectorClass<AbstractClass*> DAT_00B0F640;

// GLOBAL: GAMEMD 0x00B0F658
// SYNTHETIC: GAMEMD 0x00725610 -- exit-time destructor stub of DAT_00B0F658
// SYNTHETIC: GAMEMD 0x007255D0 -- initialiser of DAT_00B0F658
DynamicVectorClass<AbstractClass*> DAT_00B0F658;

// GLOBAL: GAMEMD 0x00B0F5F0
// SYNTHETIC: GAMEMD 0x00725690 -- exit-time destructor stub of DAT_00B0F5F0
// SYNTHETIC: GAMEMD 0x00725650 -- initialiser of DAT_00B0F5F0
DynamicVectorClass<AbstractClass*> DAT_00B0F5F0;

// GLOBAL: GAMEMD 0x00B0F5D8
// SYNTHETIC: GAMEMD 0x00725710 -- exit-time destructor stub of DAT_00B0F5D8
// SYNTHETIC: GAMEMD 0x007256D0 -- initialiser of DAT_00B0F5D8
DynamicVectorClass<AbstractClass*> DAT_00B0F5D8;

// GLOBAL: GAMEMD 0x00B0F6C8
// SYNTHETIC: GAMEMD 0x00725790 -- exit-time destructor stub of DAT_00B0F6C8
// SYNTHETIC: GAMEMD 0x00725750 -- initialiser of DAT_00B0F6C8
DynamicVectorClass<AbstractClass*> DAT_00B0F6C8;

// GLOBAL: GAMEMD 0x00B0F6F0
// SYNTHETIC: GAMEMD 0x00725810 -- exit-time destructor stub of DAT_00B0F6F0
// SYNTHETIC: GAMEMD 0x007257D0 -- initialiser of DAT_00B0F6F0
DynamicVectorClass<AbstractClass*> DAT_00B0F6F0;

// GLOBAL: GAMEMD 0x00B0F698
// SYNTHETIC: GAMEMD 0x00725890 -- exit-time destructor stub of DAT_00B0F698
// SYNTHETIC: GAMEMD 0x00725850 -- initialiser of DAT_00B0F698
DynamicVectorClass<AbstractClass*> DAT_00B0F698;

// GLOBAL: GAMEMD 0x00B1D378
// SYNTHETIC: GAMEMD 0x00750340 -- exit-time destructor stub of DAT_00B1D378
// SYNTHETIC: GAMEMD 0x00750300 -- initialiser of DAT_00B1D378
DynamicVectorClass<VocClass*> DAT_00B1D378;

// GLOBAL: GAMEMD 0x00B1D4A0
// SYNTHETIC: GAMEMD 0x00752250 -- exit-time destructor stub of DAT_00B1D4A0
// SYNTHETIC: GAMEMD 0x00752210 -- initialiser of DAT_00B1D4A0
DynamicVectorClass<VoxClass*> DAT_00B1D4A0;

// GLOBAL: GAMEMD 0x00B45B58
// SYNTHETIC: GAMEMD 0x007591C0 -- exit-time destructor stub of DAT_00B45B58
// SYNTHETIC: GAMEMD 0x00759180 -- initialiser of DAT_00B45B58
DynamicVectorClass<MovieHandle*> DAT_00B45B58;

// GLOBAL: GAMEMD 0x00B72608
// SYNTHETIC: GAMEMD 0x007635D0 -- exit-time destructor stub of DAT_00B72608
// SYNTHETIC: GAMEMD 0x00763590 -- initialiser of DAT_00B72608
DynamicVectorClass<WaypointPathClass*> DAT_00B72608;


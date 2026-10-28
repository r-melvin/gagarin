// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// File-scope DynamicVectorClass<T> objects in the unit at 0x4E62D0..0x4E8268, in
// retail order. Each definition yields the fused run-time initialiser
// (constructor plus atexit registration) and, 0x40 bytes after it, the exit
// destructor stub it registers.
#include "vector_class_operations.h"

class AbstractTypeClass;
class AircraftTypeClass;
class AnimClass;
class AnimTypeClass;
class BuildingClass;
class BuildingTypeClass;
class BulletTypeClass;
class CampaignClass;
class FactoryClass;
class HouseTypeClass;
class InfantryTypeClass;
class IsometricTileTypeClass;
class ObjectClass;
class OverlayTypeClass;
class ParticleSystemTypeClass;
class ParticleTypeClass;
class ScriptTypeClass;
class SideClass;
class SmudgeTypeClass;
class SuperClass;
class SuperWeaponTypeClass;
class TaskForceClass;
class TeamClass;
class TeamTypeClass;
class TechnoClass;
class TechnoTypeClass;
class TerrainTypeClass;
class UnitTypeClass;
class VoxelAnimTypeClass;
class TagClass;

// SYNTHETIC: GAMEMD 0x004E6DE0 -- initialiser of DAT_008B40E8
// GLOBAL: GAMEMD 0x008B40E8
// SYNTHETIC: GAMEMD 0x004E6E20 -- exit-time destructor stub of DAT_008B40E8
DynamicVectorClass<TeamClass*> DAT_008B40E8;

// SYNTHETIC: GAMEMD 0x004E6E60 -- initialiser of DAT_00A83E30
// GLOBAL: GAMEMD 0x00A83E30
// SYNTHETIC: GAMEMD 0x004E6EA0 -- exit-time destructor stub of DAT_00A83E30
DynamicVectorClass<FactoryClass*> DAT_00A83E30;

// SYNTHETIC: GAMEMD 0x004E6EE0 -- initialiser of DAT_00A83CF8
// GLOBAL: GAMEMD 0x00A83CF8
// SYNTHETIC: GAMEMD 0x004E6F20 -- exit-time destructor stub of DAT_00A83CF8
DynamicVectorClass<CampaignClass*> DAT_00A83CF8;

// SYNTHETIC: GAMEMD 0x004E6F60 -- initialiser of DAT_008B4120
// GLOBAL: GAMEMD 0x008B4120
// SYNTHETIC: GAMEMD 0x004E6FA0 -- exit-time destructor stub of DAT_008B4120
DynamicVectorClass<SideClass*> DAT_008B4120;

// SYNTHETIC: GAMEMD 0x004E6FE0 -- initialiser of DAT_00A83C98
// GLOBAL: GAMEMD 0x00A83C98
// SYNTHETIC: GAMEMD 0x004E7020 -- exit-time destructor stub of DAT_00A83C98
DynamicVectorClass<HouseTypeClass*> DAT_00A83C98;

// SYNTHETIC: GAMEMD 0x004E7060 -- initialiser of DAT_00A8E8D0
// GLOBAL: GAMEMD 0x00A8E8D0
// SYNTHETIC: GAMEMD 0x004E70A0 -- exit-time destructor stub of DAT_00A8E8D0
DynamicVectorClass<TaskForceClass*> DAT_00A8E8D0;

// SYNTHETIC: GAMEMD 0x004E70E0 -- initialiser of DAT_00A8ECA0
// GLOBAL: GAMEMD 0x00A8ECA0
// SYNTHETIC: GAMEMD 0x004E7120 -- exit-time destructor stub of DAT_00A8ECA0
DynamicVectorClass<TeamTypeClass*> DAT_00A8ECA0;

// SYNTHETIC: GAMEMD 0x004E7160 -- initialiser of DAT_008B41C8
// GLOBAL: GAMEMD 0x008B41C8
// SYNTHETIC: GAMEMD 0x004E71A0 -- exit-time destructor stub of DAT_008B41C8
DynamicVectorClass<ScriptTypeClass*> DAT_008B41C8;

// SYNTHETIC: GAMEMD 0x004E71E0 -- initialiser of DAT_00A83D80
// GLOBAL: GAMEMD 0x00A83D80
// SYNTHETIC: GAMEMD 0x004E7220 -- exit-time destructor stub of DAT_00A83D80
DynamicVectorClass<OverlayTypeClass*> DAT_00A83D80;

// SYNTHETIC: GAMEMD 0x004E7260 -- initialiser of DAT_00A8EC18
// GLOBAL: GAMEMD 0x00A8EC18
// SYNTHETIC: GAMEMD 0x004E72A0 -- exit-time destructor stub of DAT_00A8EC18
DynamicVectorClass<SmudgeTypeClass*> DAT_00A8EC18;

// SYNTHETIC: GAMEMD 0x004E72E0 -- initialiser of DAT_00A8E318
// GLOBAL: GAMEMD 0x00A8E318
// SYNTHETIC: GAMEMD 0x004E7320 -- exit-time destructor stub of DAT_00A8E318
DynamicVectorClass<TerrainTypeClass*> DAT_00A8E318;

// SYNTHETIC: GAMEMD 0x004E7360 -- initialiser of DAT_00A83C68
// GLOBAL: GAMEMD 0x00A83C68
// SYNTHETIC: GAMEMD 0x004E73A0 -- exit-time destructor stub of DAT_00A83C68
DynamicVectorClass<BuildingTypeClass*> DAT_00A83C68;

// SYNTHETIC: GAMEMD 0x004E73E0 -- initialiser of DAT_00A8B218
// GLOBAL: GAMEMD 0x00A8B218
// SYNTHETIC: GAMEMD 0x004E7420 -- exit-time destructor stub of DAT_00A8B218
DynamicVectorClass<AircraftTypeClass*> DAT_00A8B218;

// SYNTHETIC: GAMEMD 0x004E7460 -- initialiser of DAT_00A83CE0
// GLOBAL: GAMEMD 0x00A83CE0
// SYNTHETIC: GAMEMD 0x004E74A0 -- exit-time destructor stub of DAT_00A83CE0
DynamicVectorClass<UnitTypeClass*> DAT_00A83CE0;

// SYNTHETIC: GAMEMD 0x004E74E0 -- initialiser of DAT_008B4150
// GLOBAL: GAMEMD 0x008B4150
// SYNTHETIC: GAMEMD 0x004E7520 -- exit-time destructor stub of DAT_008B4150
DynamicVectorClass<AnimTypeClass*> DAT_008B4150;

// SYNTHETIC: GAMEMD 0x004E7560 -- initialiser of DAT_00A8E348
// GLOBAL: GAMEMD 0x00A8E348
// SYNTHETIC: GAMEMD 0x004E75A0 -- exit-time destructor stub of DAT_00A8E348
DynamicVectorClass<InfantryTypeClass*> DAT_00A8E348;

// SYNTHETIC: GAMEMD 0x004E75E0 -- initialiser of DAT_00A83C80
// GLOBAL: GAMEMD 0x00A83C80
// SYNTHETIC: GAMEMD 0x004E7620 -- exit-time destructor stub of DAT_00A83C80
DynamicVectorClass<BulletTypeClass*> DAT_00A83C80;

// SYNTHETIC: GAMEMD 0x004E7660 -- initialiser of DAT_00A8EB28
// GLOBAL: GAMEMD 0x00A8EB28
// SYNTHETIC: GAMEMD 0x004E76A0 -- exit-time destructor stub of DAT_00A8EB28
DynamicVectorClass<VoxelAnimTypeClass*> DAT_00A8EB28;

// SYNTHETIC: GAMEMD 0x004E76E0 -- initialiser of DAT_00A8ED28
// GLOBAL: GAMEMD 0x00A8ED28
// SYNTHETIC: GAMEMD 0x004E7720 -- exit-time destructor stub of DAT_00A8ED28
DynamicVectorClass<IsometricTileTypeClass*> DAT_00A8ED28;

// SYNTHETIC: GAMEMD 0x004E7760 -- initialiser of DAT_00A83D98
// GLOBAL: GAMEMD 0x00A83D98
// SYNTHETIC: GAMEMD 0x004E77A0 -- exit-time destructor stub of DAT_00A83D98
DynamicVectorClass<ParticleTypeClass*> DAT_00A83D98;

// SYNTHETIC: GAMEMD 0x004E77E0 -- initialiser of DAT_00A83D68
// GLOBAL: GAMEMD 0x00A83D68
// SYNTHETIC: GAMEMD 0x004E7820 -- exit-time destructor stub of DAT_00A83D68
DynamicVectorClass<ParticleSystemTypeClass*> DAT_00A83D68;

// SYNTHETIC: GAMEMD 0x004E7860 -- initialiser of DAT_00A8E330
// GLOBAL: GAMEMD 0x00A8E330
// SYNTHETIC: GAMEMD 0x004E78A0 -- exit-time destructor stub of DAT_00A8E330
DynamicVectorClass<SuperWeaponTypeClass*> DAT_00A8E330;

// SYNTHETIC: GAMEMD 0x004E78E0 -- initialiser of DAT_00A83CB8
// GLOBAL: GAMEMD 0x00A83CB8
// SYNTHETIC: GAMEMD 0x004E7920 -- exit-time destructor stub of DAT_00A83CB8
DynamicVectorClass<SuperClass*> DAT_00A83CB8;

// SYNTHETIC: GAMEMD 0x004E7960 -- initialiser of DAT_00A83D50
// GLOBAL: GAMEMD 0x00A83D50
// SYNTHETIC: GAMEMD 0x004E79A0 -- exit-time destructor stub of DAT_00A83D50
DynamicVectorClass<SuperClass*> DAT_00A83D50;

// SYNTHETIC: GAMEMD 0x004E79E0 -- initialiser of DAT_00A8EC78
// GLOBAL: GAMEMD 0x00A8EC78
// SYNTHETIC: GAMEMD 0x004E7A20 -- exit-time destructor stub of DAT_00A8EC78
DynamicVectorClass<TechnoClass*> DAT_00A8EC78;

// SYNTHETIC: GAMEMD 0x004E7A60 -- initialiser of DAT_00A8EB00
// GLOBAL: GAMEMD 0x00A8EB00
// SYNTHETIC: GAMEMD 0x004E7AA0 -- exit-time destructor stub of DAT_00A8EB00
DynamicVectorClass<TechnoTypeClass*> DAT_00A8EB00;

// SYNTHETIC: GAMEMD 0x004E7AE0 -- initialiser of DAT_00A8E360
// GLOBAL: GAMEMD 0x00A8E360
// SYNTHETIC: GAMEMD 0x004E7B20 -- exit-time destructor stub of DAT_00A8E360
DynamicVectorClass<ObjectClass*> DAT_00A8E360;

// SYNTHETIC: GAMEMD 0x004E7B60 -- initialiser of DAT_00A8E968
// GLOBAL: GAMEMD 0x00A8E968
// SYNTHETIC: GAMEMD 0x004E7BA0 -- exit-time destructor stub of DAT_00A8E968
DynamicVectorClass<AbstractTypeClass*> DAT_00A8E968;

// SYNTHETIC: GAMEMD 0x004E7BE0 -- initialiser of DAT_008B41E0
// GLOBAL: GAMEMD 0x008B41E0
// SYNTHETIC: GAMEMD 0x004E7C20 -- exit-time destructor stub of DAT_008B41E0
DynamicVectorClass<BuildingClass*> DAT_008B41E0;

// SYNTHETIC: GAMEMD 0x004E7C60 -- initialiser of DAT_00A83E00
// GLOBAL: GAMEMD 0x00A83E00
// SYNTHETIC: GAMEMD 0x004E7CA0 -- exit-time destructor stub of DAT_00A83E00
DynamicVectorClass<AnimClass*> DAT_00A83E00;

// SYNTHETIC: GAMEMD 0x004E7D40 -- initialiser of DAT_00A8ECB8
// GLOBAL: GAMEMD 0x00A8ECB8
// SYNTHETIC: GAMEMD 0x004E7D80 -- exit-time destructor stub of DAT_00A8ECB8
DynamicVectorClass<ObjectClass*> DAT_00A8ECB8;

// SYNTHETIC: GAMEMD 0x004E7F30 -- initialiser of DAT_008B41A8
// GLOBAL: GAMEMD 0x008B41A8
// SYNTHETIC: GAMEMD 0x004E7F70 -- exit-time destructor stub of DAT_008B41A8
DynamicVectorClass<TagClass*> DAT_008B41A8;

// SYNTHETIC: GAMEMD 0x004E7FB0 -- initialiser of DAT_008B40C8
// GLOBAL: GAMEMD 0x008B40C8
// SYNTHETIC: GAMEMD 0x004E7FF0 -- exit-time destructor stub of DAT_008B40C8
DynamicVectorClass<TagClass*> DAT_008B40C8;

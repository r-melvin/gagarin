// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 175 remaining 73-byte deleting-destructor bodies are bound here through
// 91 VectorClass<T> base-destruction views. The vptr written at body+6,
// its retail COL and its type descriptor establish that base and element T.
// Instructions confirm Items+4, Capacity+8 and ownership byte+D; the low
// deleting flag controls the final free of the object.
//
// The written base vptr does NOT prove which class declared the deleting
// wrapper. An inherited/derived wrapper can inline that same base destructor.
// These are exact code-body bindings, not proof of original wrapper ownership,
// original TU boundaries, or duplicate-COMDAT linker behavior. Audit each
// owning slot-zero vtable when integrating its class. The int and ToolTip
// base/dynamic pairs and TypeList<int> now use their actual slot targets.
#ifndef GG_MATCH_CORE_VECTOR_DTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_DTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) -- CRT free.
extern "C" void __cdecl gg_free(void* block);

// The shared template declares all seven confirmed virtual slots.
#include "vector_class.h"

// The retail vtables this family reseats, each with the class named by its
// own complete object locator four bytes below it.
// VTABLE: GAMEMD 0x007E4DB8 -- VectorClass<int>
extern char VT_007E4DB8;
// VTABLE: GAMEMD 0x007E4E38 -- VectorClass<RGBClass>
extern char VT_007E4E38;
// VTABLE: GAMEMD 0x007E192C -- VectorClass<ObjectClass*>
extern char VT_007E192C;
// VTABLE: GAMEMD 0x007E5C24 -- VectorClass<char*>
extern char VT_007E5C24;
// VTABLE: GAMEMD 0x007E5C04 -- VectorClass<DynamicVectorClass<char*>*>
extern char VT_007E5C04;
// VTABLE: GAMEMD 0x007E5C84 -- VectorClass<tagCONNECTDATA>
extern char VT_007E5C84;
// VTABLE: GAMEMD 0x007E5D08 -- VectorClass<IConnectionPoint*>
extern char VT_007E5D08;
// VTABLE: GAMEMD 0x007E5DEC -- VectorClass<_DDSURFACEDESC*>
extern char VT_007E5DEC;
// VTABLE: GAMEMD 0x007E8500 -- VectorClass<ButtonFadeEffect*>
extern char VT_007E8500;
// VTABLE: GAMEMD 0x007E8520 -- VectorClass<CrossDissolveEffect*>
extern char VT_007E8520;
// VTABLE: GAMEMD 0x007E86AC -- VectorClass<EBolt*>
extern char VT_007E86AC;
// VTABLE: GAMEMD 0x007E8BC0 -- VectorClass<FoggedObjectClass::DrawRecord>
extern char VT_007E8BC0;
// VTABLE: GAMEMD 0x007EA504 -- VectorClass<SuperClass*>
extern char VT_007EA504;
// VTABLE: GAMEMD 0x007E9D84 -- VectorClass<ParticleClass*>
extern char VT_007E9D84;
// VTABLE: GAMEMD 0x007E9F84 -- VectorClass<TeamClass*>
extern char VT_007E9F84;
// VTABLE: GAMEMD 0x007EA584 -- VectorClass<ThemeControl*>
extern char VT_007EA584;
// VTABLE: GAMEMD 0x007E9CC4 -- VectorClass<TubeClass*>
extern char VT_007E9CC4;
// VTABLE: GAMEMD 0x007E9DC4 -- VectorClass<SmudgeClass*>
extern char VT_007E9DC4;
// VTABLE: GAMEMD 0x007E9F44 -- VectorClass<AnimClass*>
extern char VT_007E9F44;
// VTABLE: GAMEMD 0x007EA044 -- VectorClass<SideClass*>
extern char VT_007EA044;
// VTABLE: GAMEMD 0x007EA084 -- VectorClass<HouseTypeClass*>
extern char VT_007EA084;
// VTABLE: GAMEMD 0x007EA0C4 -- VectorClass<TaskForceClass*>
extern char VT_007EA0C4;
// VTABLE: GAMEMD 0x007EA384 -- VectorClass<BulletTypeClass*>
extern char VT_007EA384;
// VTABLE: GAMEMD 0x007EA404 -- VectorClass<IsometricTileTypeClass*>
extern char VT_007EA404;
// VTABLE: GAMEMD 0x007EA444 -- VectorClass<ParticleTypeClass*>
extern char VT_007EA444;
// VTABLE: GAMEMD 0x007EA964 -- VectorClass<HouseClass::StartingTechnoStruct*>
extern char VT_007EA964;
// VTABLE: GAMEMD 0x007EA984 -- VectorClass<AngerStruct>
extern char VT_007EA984;
// VTABLE: GAMEMD 0x007EA9A4 -- VectorClass<ScoutStruct>
extern char VT_007EA9A4;
// VTABLE: GAMEMD 0x007EA7D4 -- VectorClass<HouseClass::BuildChoiceClass*>
extern char VT_007EA7D4;
// VTABLE: GAMEMD 0x007EAA5C -- VectorClass<bool>
extern char VT_007EAA5C;
// VTABLE: GAMEMD 0x007EC07C -- VectorClass<IonBlastClass*>
extern char VT_007EC07C;
// VTABLE: GAMEMD 0x007ECD0C -- VectorClass<unsigned short*>
extern char VT_007ECD0C;
// VTABLE: GAMEMD 0x007ECBFC -- VectorClass<IsometricTileTypeClass::TileInsertType*>
extern char VT_007ECBFC;
// VTABLE: GAMEMD 0x007ECE9C -- VectorClass<KamikazeControl*>
extern char VT_007ECE9C;
// VTABLE: GAMEMD 0x007ECEFC -- VectorClass<LaserDrawClass*>
extern char VT_007ECEFC;
// VTABLE: GAMEMD 0x007ECF9C -- VectorClass<LightSourceClass*>
extern char VT_007ECF9C;
// VTABLE: GAMEMD 0x007ECFDC -- VectorClass<LightSourceClass::PendingCellClass*>
extern char VT_007ECFDC;
// VTABLE: GAMEMD 0x007ED0EC -- VectorClass<LineTrail*>
extern char VT_007ED0EC;
// VTABLE: GAMEMD 0x007ED480 -- VectorClass<CellClass*>
extern char VT_007ED480;
// VTABLE: GAMEMD 0x007E177C -- VectorClass<SubzoneConnectionStruct>
extern char VT_007E177C;
// VTABLE: GAMEMD 0x007ED4E0 -- VectorClass<ZoneConnectionClass>
extern char VT_007ED4E0;
// VTABLE: GAMEMD 0x007ED560 -- VectorClass<PassabilityType>
extern char VT_007ED560;
// VTABLE: GAMEMD 0x007ED5C0 -- VectorClass<HashObject<unsigned int, unsigned int>>
extern char VT_007ED5C0;
// VTABLE: GAMEMD 0x007ED5E0 -- VectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>
extern char VT_007ED5E0;
// VTABLE: GAMEMD 0x007ED878 -- VectorClass<MapRegionClass*>
extern char VT_007ED878;
// VTABLE: GAMEMD 0x007ED92C -- VectorClass<_WIN32_FIND_DATAA*>
extern char VT_007ED92C;
// VTABLE: GAMEMD 0x007ED970 -- VectorClass<TRect<int>>
extern char VT_007ED970;
// VTABLE: GAMEMD 0x007EDA4C -- VectorClass<double>
extern char VT_007EDA4C;
// VTABLE: GAMEMD 0x007EE390 -- VectorClass<NodeNameType*>
extern char VT_007EE390;
// VTABLE: GAMEMD 0x007EEB74 -- VectorClass<Point2D>
extern char VT_007EEB74;
// VTABLE: GAMEMD 0x007EEBB4 -- VectorClass<MapSelection*>
extern char VT_007EEBB4;
// VTABLE: GAMEMD 0x007EEAB4 -- VectorClass<MapStage*>
extern char VT_007EEAB4;
// VTABLE: GAMEMD 0x007EEAD4 -- VectorClass<MSAnimEntry*>
extern char VT_007EEAD4;
// VTABLE: GAMEMD 0x007EEAF4 -- VectorClass<MSSfxEntry*>
extern char VT_007EEAF4;
// VTABLE: GAMEMD 0x007EEC24 -- VectorClass<MSAnim*>
extern char VT_007EEC24;
// VTABLE: GAMEMD 0x007EEC44 -- VectorClass<MSSfx*>
extern char VT_007EEC44;
// VTABLE: GAMEMD 0x007EECAC -- VectorClass<HWND__*>
extern char VT_007EECAC;
// VTABLE: GAMEMD 0x007EECEC -- VectorClass<AcceleratorTracker>
extern char VT_007EECEC;
// VTABLE: GAMEMD 0x007EEE54 -- VectorClass<MultiplayerTeam*>
extern char VT_007EEE54;
// VTABLE: GAMEMD 0x007EED40 -- VectorClass<MultiplayerGameMode*>
extern char VT_007EED40;
// VTABLE: GAMEMD 0x007EF28C -- VectorClass<ObjectTypeClass*>
extern char VT_007EF28C;
// VTABLE: GAMEMD 0x007EF6DC -- VectorClass<SpotLightClass*>
extern char VT_007EF6DC;
// VTABLE: GAMEMD 0x007EF7F0 -- VectorClass<HSVClass>
extern char VT_007EF7F0;
// VTABLE: GAMEMD 0x007EF7D0 -- VectorClass<HashObject<HashString, SchemeNode*>>
extern char VT_007EF7D0;
// VTABLE: GAMEMD 0x007EF844 -- VectorClass<ParasiteClass*>
extern char VT_007EF844;
// VTABLE: GAMEMD 0x007EFF04 -- VectorClass<PlanningMemberClass*>
extern char VT_007EFF04;
// VTABLE: GAMEMD 0x007EFF24 -- VectorClass<PlanningBranchClass*>
extern char VT_007EFF24;
// VTABLE: GAMEMD 0x007EFE64 -- VectorClass<PlanningNodeClass*>
extern char VT_007EFE64;
// VTABLE: GAMEMD 0x007EFE24 -- VectorClass<EventClass*>
extern char VT_007EFE24;
// VTABLE: GAMEMD 0x007EFEA4 -- VectorClass<PlanningTokenClass*>
extern char VT_007EFEA4;
// VTABLE: GAMEMD 0x007F044C -- VectorClass<HashObject<RadarTrackingStruct, TechnoClass*>>
extern char VT_007F044C;
// VTABLE: GAMEMD 0x007F04A4 -- VectorClass<RadBeam*>
extern char VT_007F04A4;
// VTABLE: GAMEMD 0x007F07C4 -- VectorClass<RadSiteClass*>
extern char VT_007F07C4;
// VTABLE: GAMEMD 0x007F0ACC -- VectorClass<RadarEventClass*>
extern char VT_007F0ACC;
// VTABLE: GAMEMD 0x007F0C4C -- VectorClass<OwnerTalkClass::ConnectionListStruct*>
extern char VT_007F0C4C;
// VTABLE: GAMEMD 0x007F1274 -- VectorClass<DiskID>
extern char VT_007F1274;
// VTABLE: GAMEMD 0x007F1214 -- VectorClass<MultiMission*>
extern char VT_007F1214;
// VTABLE: GAMEMD 0x007F1234 -- VectorClass<GlobalPacketType*>
extern char VT_007F1234;
// VTABLE: GAMEMD 0x007F1254 -- VectorClass<PhoneEntryClass*>
extern char VT_007F1254;
// VTABLE: GAMEMD 0x007F324C -- VectorClass<SlaveManagerClass::SlaveControl*>
extern char VT_007F324C;
// VTABLE: GAMEMD 0x007F317C -- VectorClass<SlaveManagerClass*>
extern char VT_007F317C;
// VTABLE: GAMEMD 0x007F329C -- VectorClass<UndoInfoStruct>
extern char VT_007F329C;
// VTABLE: GAMEMD 0x007F36D4 -- VectorClass<SpawnManagerClass::SpawnControl*>
extern char VT_007F36D4;
// VTABLE: GAMEMD 0x007F3604 -- VectorClass<SpawnManagerClass*>
extern char VT_007F3604;
// VTABLE: GAMEMD 0x007F3748 -- VectorClass<unsigned long>
extern char VT_007F3748;
// VTABLE: GAMEMD 0x007F3F8C -- VectorClass<SubTitle*>
extern char VT_007F3F8C;
// VTABLE: GAMEMD 0x007F4154 -- VectorClass<SwizzlePointerClass>
extern char VT_007F4154;
// VTABLE: GAMEMD 0x007F42BC -- VectorClass<DirtyAreaStruct>
extern char VT_007F42BC;
// VTABLE: GAMEMD 0x007F65F4 -- VectorClass<unsigned char>
extern char VT_007F65F4;
// VTABLE: GAMEMD 0x007F71A4 -- VectorClass<WorldDominationTour::Map::AnimationPalette*>
extern char VT_007F71A4;
// VTABLE: GAMEMD 0x007F71E0 -- VectorClass<WorldDominationTour::Centroid>
extern char VT_007F71E0;

#endif  // GG_MATCH_CORE_VECTOR_DTOR_FAMILY_METHODS_H

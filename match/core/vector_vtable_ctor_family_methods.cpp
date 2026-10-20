// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x65D430 and its 77
//   siblings.
//
//   One class template, 78 explicit instantiations. Each traits type below
//   names one retail vtable, and `template struct VtableObj<Vtbl_XXXXXXXX>;`
//   makes the compiler generate `?Init@?$VtableObj@UVtbl_XXXXXXXX@@@@QAEPAU1@XZ`,
//   whose 0x10 bytes are the retail function at the annotated address: clear
//   the member at +4, seat that class's vtable at +0, return the object in
//   EAX.
//
//   The traits type is the only thing that varies -- nothing else in the
//   family differs, so one template covers all 78 with no splitting. Unlike
//   the deleting-destructor family, the vtable cannot come from the
//   instantiation's own emitted vtable: retail's store order rules out a
//   constructor. See the header for the measurement.
//
//   KNOWN LIMITATION -- staging ground, not a destination: MSVC6 emits each
//   template instantiation as a COMDAT into the translation unit that
//   instantiated it, so these 78 instantiations belong to many different
//   original Westwood translation units. One sweep file is right for matching
//   bytes now and wrong for retail's eventual link order.
//
//   Instantiations are in ascending retail-address order.

#include "vector_vtable_ctor_family_methods.h"

// FUNCTION: GAMEMD 0x0065D430
// rc_ptr_base -- seats retail vtable 0x007F094C; locator 0x008087C0 -> type
//   descriptor 0x00827F78 `.?AVrc_ptr_base@@`.
struct Vtbl_rc_ptr_base { static char* Vtable() { return &VT_007F094C; } };
template struct VtableObj<Vtbl_rc_ptr_base>;

// Layout asserted on the first instantiation; every instantiation in this
// family has the same layout, because the type parameter carries no members.
// The assert has to follow an explicit instantiation: VC6 fails to re-parse
// the template body when offsetof is what first instantiates it, and it will
// not take a template-id as offsetof's first argument either, hence the
// typedef.
typedef VtableObj<Vtbl_rc_ptr_base> GgVtableObjRep;
GG_STATIC_ASSERT(offsetof(GgVtableObjRep, Vptr)   == 0x0);
GG_STATIC_ASSERT(offsetof(GgVtableObjRep, Field4) == 0x4);
GG_STATIC_ASSERT(sizeof(GgVtableObjRep)           == 0x8);

// FUNCTION: GAMEMD 0x006BEE40
// TClassFactory<CStreamClass> -- seats retail vtable 0x007F3768; locator 0x00809C68 -> type
//   descriptor 0x00840F68 `.?AV?$TClassFactory@VCStreamClass@@@@`.
struct Vtbl_TClassFactory_CStreamClass { static char* Vtable() { return &VT_007F3768; } };
template struct VtableObj<Vtbl_TClassFactory_CStreamClass>;

// FUNCTION: GAMEMD 0x006BEFC0
// TClassFactory<WaveClass> -- seats retail vtable 0x007F3780; locator 0x00809CB8 -> type
//   descriptor 0x00840F98 `.?AV?$TClassFactory@VWaveClass@@@@`.
struct Vtbl_TClassFactory_WaveClass { static char* Vtable() { return &VT_007F3780; } };
template struct VtableObj<Vtbl_TClassFactory_WaveClass>;

// FUNCTION: GAMEMD 0x006BF140
// TClassFactory<TerrainTypeClass> -- seats retail vtable 0x007F3798; locator 0x00809D08 -> type
//   descriptor 0x00840FC8 `.?AV?$TClassFactory@VTerrainTypeClass@@@@`.
struct Vtbl_TClassFactory_TerrainTypeClass { static char* Vtable() { return &VT_007F3798; } };
template struct VtableObj<Vtbl_TClassFactory_TerrainTypeClass>;

// FUNCTION: GAMEMD 0x006BF2C0
// TClassFactory<TerrainClass> -- seats retail vtable 0x007F37B0; locator 0x00809D58 -> type
//   descriptor 0x00841000 `.?AV?$TClassFactory@VTerrainClass@@@@`.
struct Vtbl_TClassFactory_TerrainClass { static char* Vtable() { return &VT_007F37B0; } };
template struct VtableObj<Vtbl_TClassFactory_TerrainClass>;

// FUNCTION: GAMEMD 0x006BF440
// TClassFactory<SuperWeaponTypeClass> -- seats retail vtable 0x007F37C8; locator 0x00809DA8 -> type
//   descriptor 0x00841030 `.?AV?$TClassFactory@VSuperWeaponTypeClass@@@@`.
struct Vtbl_TClassFactory_SuperWeaponTypeClass { static char* Vtable() { return &VT_007F37C8; } };
template struct VtableObj<Vtbl_TClassFactory_SuperWeaponTypeClass>;

// FUNCTION: GAMEMD 0x006BF5C0
// TClassFactory<SuperClass> -- seats retail vtable 0x007F37E0; locator 0x00809DF8 -> type
//   descriptor 0x00841068 `.?AV?$TClassFactory@VSuperClass@@@@`.
struct Vtbl_TClassFactory_SuperClass { static char* Vtable() { return &VT_007F37E0; } };
template struct VtableObj<Vtbl_TClassFactory_SuperClass>;

// FUNCTION: GAMEMD 0x006BF740
// TClassFactory<Tactical> -- seats retail vtable 0x007F37F8; locator 0x00809E48 -> type
//   descriptor 0x00841098 `.?AV?$TClassFactory@VTactical@@@@`.
struct Vtbl_TClassFactory_Tactical { static char* Vtable() { return &VT_007F37F8; } };
template struct VtableObj<Vtbl_TClassFactory_Tactical>;

// FUNCTION: GAMEMD 0x006BF8C0
// TClassFactory<CellClass> -- seats retail vtable 0x007F3810; locator 0x00809E98 -> type
//   descriptor 0x008410C8 `.?AV?$TClassFactory@VCellClass@@@@`.
struct Vtbl_TClassFactory_CellClass { static char* Vtable() { return &VT_007F3810; } };
template struct VtableObj<Vtbl_TClassFactory_CellClass>;

// FUNCTION: GAMEMD 0x006BFA40
// TClassFactory<EMPulseClass> -- seats retail vtable 0x007F3828; locator 0x00809EE8 -> type
//   descriptor 0x008410F8 `.?AV?$TClassFactory@VEMPulseClass@@@@`.
struct Vtbl_TClassFactory_EMPulseClass { static char* Vtable() { return &VT_007F3828; } };
template struct VtableObj<Vtbl_TClassFactory_EMPulseClass>;

// FUNCTION: GAMEMD 0x006BFBC0
// TClassFactory<LightSourceClass> -- seats retail vtable 0x007F3840; locator 0x00809F38 -> type
//   descriptor 0x00841128 `.?AV?$TClassFactory@VLightSourceClass@@@@`.
struct Vtbl_TClassFactory_LightSourceClass { static char* Vtable() { return &VT_007F3840; } };
template struct VtableObj<Vtbl_TClassFactory_LightSourceClass>;

// FUNCTION: GAMEMD 0x006BFD40
// TClassFactory<SideClass> -- seats retail vtable 0x007F3858; locator 0x00809F88 -> type
//   descriptor 0x00841160 `.?AV?$TClassFactory@VSideClass@@@@`.
struct Vtbl_TClassFactory_SideClass { static char* Vtable() { return &VT_007F3858; } };
template struct VtableObj<Vtbl_TClassFactory_SideClass>;

// FUNCTION: GAMEMD 0x006BFEC0
// TClassFactory<TiberiumClass> -- seats retail vtable 0x007F3870; locator 0x00809FD8 -> type
//   descriptor 0x00841190 `.?AV?$TClassFactory@VTiberiumClass@@@@`.
struct Vtbl_TClassFactory_TiberiumClass { static char* Vtable() { return &VT_007F3870; } };
template struct VtableObj<Vtbl_TClassFactory_TiberiumClass>;

// FUNCTION: GAMEMD 0x006C0040
// TClassFactory<TubeClass> -- seats retail vtable 0x007F3888; locator 0x0080A028 -> type
//   descriptor 0x008411C0 `.?AV?$TClassFactory@VTubeClass@@@@`.
struct Vtbl_TClassFactory_TubeClass { static char* Vtable() { return &VT_007F3888; } };
template struct VtableObj<Vtbl_TClassFactory_TubeClass>;

// FUNCTION: GAMEMD 0x006C01C0
// TClassFactory<CampaignClass> -- seats retail vtable 0x007F38A0; locator 0x0080A078 -> type
//   descriptor 0x008411F0 `.?AV?$TClassFactory@VCampaignClass@@@@`.
struct Vtbl_TClassFactory_CampaignClass { static char* Vtable() { return &VT_007F38A0; } };
template struct VtableObj<Vtbl_TClassFactory_CampaignClass>;

// FUNCTION: GAMEMD 0x006C0340
// TClassFactory<BuildingLightClass> -- seats retail vtable 0x007F38B8; locator 0x0080A0C8 -> type
//   descriptor 0x00841220 `.?AV?$TClassFactory@VBuildingLightClass@@@@`.
struct Vtbl_TClassFactory_BuildingLightClass { static char* Vtable() { return &VT_007F38B8; } };
template struct VtableObj<Vtbl_TClassFactory_BuildingLightClass>;

// FUNCTION: GAMEMD 0x006C04C0
// TClassFactory<WaypointPathClass> -- seats retail vtable 0x007F38D0; locator 0x0080A118 -> type
//   descriptor 0x00841258 `.?AV?$TClassFactory@VWaypointPathClass@@@@`.
struct Vtbl_TClassFactory_WaypointPathClass { static char* Vtable() { return &VT_007F38D0; } };
template struct VtableObj<Vtbl_TClassFactory_WaypointPathClass>;

// FUNCTION: GAMEMD 0x006C0640
// TClassFactory<TemporalClass> -- seats retail vtable 0x007F38E8; locator 0x0080A168 -> type
//   descriptor 0x00841290 `.?AV?$TClassFactory@VTemporalClass@@@@`.
struct Vtbl_TClassFactory_TemporalClass { static char* Vtable() { return &VT_007F38E8; } };
template struct VtableObj<Vtbl_TClassFactory_TemporalClass>;

// FUNCTION: GAMEMD 0x006C07C0
// TClassFactory<AirstrikeClass> -- seats retail vtable 0x007F3900; locator 0x0080A1B8 -> type
//   descriptor 0x008412C0 `.?AV?$TClassFactory@VAirstrikeClass@@@@`.
struct Vtbl_TClassFactory_AirstrikeClass { static char* Vtable() { return &VT_007F3900; } };
template struct VtableObj<Vtbl_TClassFactory_AirstrikeClass>;

// FUNCTION: GAMEMD 0x006C0940
// TClassFactory<SpawnManagerClass> -- seats retail vtable 0x007F3918; locator 0x0080A208 -> type
//   descriptor 0x008412F0 `.?AV?$TClassFactory@VSpawnManagerClass@@@@`.
struct Vtbl_TClassFactory_SpawnManagerClass { static char* Vtable() { return &VT_007F3918; } };
template struct VtableObj<Vtbl_TClassFactory_SpawnManagerClass>;

// FUNCTION: GAMEMD 0x006C0AC0
// TClassFactory<SlaveManagerClass> -- seats retail vtable 0x007F3930; locator 0x0080A258 -> type
//   descriptor 0x00841328 `.?AV?$TClassFactory@VSlaveManagerClass@@@@`.
struct Vtbl_TClassFactory_SlaveManagerClass { static char* Vtable() { return &VT_007F3930; } };
template struct VtableObj<Vtbl_TClassFactory_SlaveManagerClass>;

// FUNCTION: GAMEMD 0x006C0C40
// TClassFactory<CaptureManagerClass> -- seats retail vtable 0x007F3948; locator 0x0080A2A8 -> type
//   descriptor 0x00841360 `.?AV?$TClassFactory@VCaptureManagerClass@@@@`.
struct Vtbl_TClassFactory_CaptureManagerClass { static char* Vtable() { return &VT_007F3948; } };
template struct VtableObj<Vtbl_TClassFactory_CaptureManagerClass>;

// FUNCTION: GAMEMD 0x006C0DC0
// TClassFactory<DiskLaserClass> -- seats retail vtable 0x007F3960; locator 0x0080A2F8 -> type
//   descriptor 0x00841398 `.?AV?$TClassFactory@VDiskLaserClass@@@@`.
struct Vtbl_TClassFactory_DiskLaserClass { static char* Vtable() { return &VT_007F3960; } };
template struct VtableObj<Vtbl_TClassFactory_DiskLaserClass>;

// FUNCTION: GAMEMD 0x006C0F40
// TClassFactory<ParasiteClass> -- seats retail vtable 0x007F3978; locator 0x0080A348 -> type
//   descriptor 0x008413C8 `.?AV?$TClassFactory@VParasiteClass@@@@`.
struct Vtbl_TClassFactory_ParasiteClass { static char* Vtable() { return &VT_007F3978; } };
template struct VtableObj<Vtbl_TClassFactory_ParasiteClass>;

// FUNCTION: GAMEMD 0x006C10C0
// TClassFactory<BombClass> -- seats retail vtable 0x007F3990; locator 0x0080A398 -> type
//   descriptor 0x008413F8 `.?AV?$TClassFactory@VBombClass@@@@`.
struct Vtbl_TClassFactory_BombClass { static char* Vtable() { return &VT_007F3990; } };
template struct VtableObj<Vtbl_TClassFactory_BombClass>;

// FUNCTION: GAMEMD 0x006C1240
// TClassFactory<RadSiteClass> -- seats retail vtable 0x007F39A8; locator 0x0080A3E8 -> type
//   descriptor 0x00841428 `.?AV?$TClassFactory@VRadSiteClass@@@@`.
struct Vtbl_TClassFactory_RadSiteClass { static char* Vtable() { return &VT_007F39A8; } };
template struct VtableObj<Vtbl_TClassFactory_RadSiteClass>;

// FUNCTION: GAMEMD 0x006C13C0
// TClassFactory<TEventClass> -- seats retail vtable 0x007F39C0; locator 0x0080A438 -> type
//   descriptor 0x00841458 `.?AV?$TClassFactory@VTEventClass@@@@`.
struct Vtbl_TClassFactory_TEventClass { static char* Vtable() { return &VT_007F39C0; } };
template struct VtableObj<Vtbl_TClassFactory_TEventClass>;

// FUNCTION: GAMEMD 0x006C1540
// TClassFactory<VoxelAnimTypeClass> -- seats retail vtable 0x007F39D8; locator 0x0080A488 -> type
//   descriptor 0x00841488 `.?AV?$TClassFactory@VVoxelAnimTypeClass@@@@`.
struct Vtbl_TClassFactory_VoxelAnimTypeClass { static char* Vtable() { return &VT_007F39D8; } };
template struct VtableObj<Vtbl_TClassFactory_VoxelAnimTypeClass>;

// FUNCTION: GAMEMD 0x006C16C0
// TClassFactory<VoxelAnimClass> -- seats retail vtable 0x007F39F0; locator 0x0080A4D8 -> type
//   descriptor 0x008414C0 `.?AV?$TClassFactory@VVoxelAnimClass@@@@`.
struct Vtbl_TClassFactory_VoxelAnimClass { static char* Vtable() { return &VT_007F39F0; } };
template struct VtableObj<Vtbl_TClassFactory_VoxelAnimClass>;

// FUNCTION: GAMEMD 0x006C1840
// TClassFactory<TActionClass> -- seats retail vtable 0x007F3A08; locator 0x0080A528 -> type
//   descriptor 0x008414F0 `.?AV?$TClassFactory@VTActionClass@@@@`.
struct Vtbl_TClassFactory_TActionClass { static char* Vtable() { return &VT_007F3A08; } };
template struct VtableObj<Vtbl_TClassFactory_TActionClass>;

// FUNCTION: GAMEMD 0x006C19C0
// TClassFactory<TriggerClass> -- seats retail vtable 0x007F3A20; locator 0x0080A578 -> type
//   descriptor 0x00841520 `.?AV?$TClassFactory@VTriggerClass@@@@`.
struct Vtbl_TClassFactory_TriggerClass { static char* Vtable() { return &VT_007F3A20; } };
template struct VtableObj<Vtbl_TClassFactory_TriggerClass>;

// FUNCTION: GAMEMD 0x006C1B40
// TClassFactory<TriggerTypeClass> -- seats retail vtable 0x007F3A38; locator 0x0080A5C8 -> type
//   descriptor 0x00841550 `.?AV?$TClassFactory@VTriggerTypeClass@@@@`.
struct Vtbl_TClassFactory_TriggerTypeClass { static char* Vtable() { return &VT_007F3A38; } };
template struct VtableObj<Vtbl_TClassFactory_TriggerTypeClass>;

// FUNCTION: GAMEMD 0x006C1CC0
// TClassFactory<ScriptClass> -- seats retail vtable 0x007F3A50; locator 0x0080A618 -> type
//   descriptor 0x00841588 `.?AV?$TClassFactory@VScriptClass@@@@`.
struct Vtbl_TClassFactory_ScriptClass { static char* Vtable() { return &VT_007F3A50; } };
template struct VtableObj<Vtbl_TClassFactory_ScriptClass>;

// FUNCTION: GAMEMD 0x006C1E40
// TClassFactory<ScriptTypeClass> -- seats retail vtable 0x007F3A68; locator 0x0080A668 -> type
//   descriptor 0x008415B8 `.?AV?$TClassFactory@VScriptTypeClass@@@@`.
struct Vtbl_TClassFactory_ScriptTypeClass { static char* Vtable() { return &VT_007F3A68; } };
template struct VtableObj<Vtbl_TClassFactory_ScriptTypeClass>;

// FUNCTION: GAMEMD 0x006C1FC0
// TClassFactory<TagClass> -- seats retail vtable 0x007F3A80; locator 0x0080A6B8 -> type
//   descriptor 0x008415F0 `.?AV?$TClassFactory@VTagClass@@@@`.
struct Vtbl_TClassFactory_TagClass { static char* Vtable() { return &VT_007F3A80; } };
template struct VtableObj<Vtbl_TClassFactory_TagClass>;

// FUNCTION: GAMEMD 0x006C2140
// TClassFactory<TagTypeClass> -- seats retail vtable 0x007F3A98; locator 0x0080A708 -> type
//   descriptor 0x00841620 `.?AV?$TClassFactory@VTagTypeClass@@@@`.
struct Vtbl_TClassFactory_TagTypeClass { static char* Vtable() { return &VT_007F3A98; } };
template struct VtableObj<Vtbl_TClassFactory_TagTypeClass>;

// FUNCTION: GAMEMD 0x006C22C0
// TClassFactory<TeamClass> -- seats retail vtable 0x007F3AB0; locator 0x0080A758 -> type
//   descriptor 0x00841650 `.?AV?$TClassFactory@VTeamClass@@@@`.
struct Vtbl_TClassFactory_TeamClass { static char* Vtable() { return &VT_007F3AB0; } };
template struct VtableObj<Vtbl_TClassFactory_TeamClass>;

// FUNCTION: GAMEMD 0x006C2440
// TClassFactory<TeamTypeClass> -- seats retail vtable 0x007F3AC8; locator 0x0080A7A8 -> type
//   descriptor 0x00841680 `.?AV?$TClassFactory@VTeamTypeClass@@@@`.
struct Vtbl_TClassFactory_TeamTypeClass { static char* Vtable() { return &VT_007F3AC8; } };
template struct VtableObj<Vtbl_TClassFactory_TeamTypeClass>;

// FUNCTION: GAMEMD 0x006C25C0
// TClassFactory<TaskForceClass> -- seats retail vtable 0x007F3AE0; locator 0x0080A7F8 -> type
//   descriptor 0x008416B0 `.?AV?$TClassFactory@VTaskForceClass@@@@`.
struct Vtbl_TClassFactory_TaskForceClass { static char* Vtable() { return &VT_007F3AE0; } };
template struct VtableObj<Vtbl_TClassFactory_TaskForceClass>;

// FUNCTION: GAMEMD 0x006C2740
// TClassFactory<UnitTypeClass> -- seats retail vtable 0x007F3AF8; locator 0x0080A848 -> type
//   descriptor 0x008416E0 `.?AV?$TClassFactory@VUnitTypeClass@@@@`.
struct Vtbl_TClassFactory_UnitTypeClass { static char* Vtable() { return &VT_007F3AF8; } };
template struct VtableObj<Vtbl_TClassFactory_UnitTypeClass>;

// FUNCTION: GAMEMD 0x006C28C0
// TClassFactory<BuildingTypeClass> -- seats retail vtable 0x007F3B10; locator 0x0080A898 -> type
//   descriptor 0x00841710 `.?AV?$TClassFactory@VBuildingTypeClass@@@@`.
struct Vtbl_TClassFactory_BuildingTypeClass { static char* Vtable() { return &VT_007F3B10; } };
template struct VtableObj<Vtbl_TClassFactory_BuildingTypeClass>;

// FUNCTION: GAMEMD 0x006C2A40
// TClassFactory<AircraftTypeClass> -- seats retail vtable 0x007F3B28; locator 0x0080A8E8 -> type
//   descriptor 0x00841748 `.?AV?$TClassFactory@VAircraftTypeClass@@@@`.
struct Vtbl_TClassFactory_AircraftTypeClass { static char* Vtable() { return &VT_007F3B28; } };
template struct VtableObj<Vtbl_TClassFactory_AircraftTypeClass>;

// FUNCTION: GAMEMD 0x006C2BC0
// TClassFactory<InfantryTypeClass> -- seats retail vtable 0x007F3B40; locator 0x0080A938 -> type
//   descriptor 0x00841780 `.?AV?$TClassFactory@VInfantryTypeClass@@@@`.
struct Vtbl_TClassFactory_InfantryTypeClass { static char* Vtable() { return &VT_007F3B40; } };
template struct VtableObj<Vtbl_TClassFactory_InfantryTypeClass>;

// FUNCTION: GAMEMD 0x006C2D40
// TClassFactory<BulletTypeClass> -- seats retail vtable 0x007F3B58; locator 0x0080A988 -> type
//   descriptor 0x008417B8 `.?AV?$TClassFactory@VBulletTypeClass@@@@`.
struct Vtbl_TClassFactory_BulletTypeClass { static char* Vtable() { return &VT_007F3B58; } };
template struct VtableObj<Vtbl_TClassFactory_BulletTypeClass>;

// FUNCTION: GAMEMD 0x006C2EC0
// TClassFactory<IsometricTileTypeClass> -- seats retail vtable 0x007F3B70; locator 0x0080A9D8 -> type
//   descriptor 0x008417F0 `.?AV?$TClassFactory@VIsometricTileTypeClass@@@@`.
struct Vtbl_TClassFactory_IsometricTileTypeClass { static char* Vtable() { return &VT_007F3B70; } };
template struct VtableObj<Vtbl_TClassFactory_IsometricTileTypeClass>;

// FUNCTION: GAMEMD 0x006C3040
// TClassFactory<OverlayTypeClass> -- seats retail vtable 0x007F3B88; locator 0x0080AA28 -> type
//   descriptor 0x00841828 `.?AV?$TClassFactory@VOverlayTypeClass@@@@`.
struct Vtbl_TClassFactory_OverlayTypeClass { static char* Vtable() { return &VT_007F3B88; } };
template struct VtableObj<Vtbl_TClassFactory_OverlayTypeClass>;

// FUNCTION: GAMEMD 0x006C31C0
// TClassFactory<SmudgeTypeClass> -- seats retail vtable 0x007F3BA0; locator 0x0080AA78 -> type
//   descriptor 0x00841860 `.?AV?$TClassFactory@VSmudgeTypeClass@@@@`.
struct Vtbl_TClassFactory_SmudgeTypeClass { static char* Vtable() { return &VT_007F3BA0; } };
template struct VtableObj<Vtbl_TClassFactory_SmudgeTypeClass>;

// FUNCTION: GAMEMD 0x006C3340
// TClassFactory<UnitClass> -- seats retail vtable 0x007F3BB8; locator 0x0080AAC8 -> type
//   descriptor 0x00841898 `.?AV?$TClassFactory@VUnitClass@@@@`.
struct Vtbl_TClassFactory_UnitClass { static char* Vtable() { return &VT_007F3BB8; } };
template struct VtableObj<Vtbl_TClassFactory_UnitClass>;

// FUNCTION: GAMEMD 0x006C34C0
// TClassFactory<BuildingClass> -- seats retail vtable 0x007F3BD0; locator 0x0080AB18 -> type
//   descriptor 0x008418C8 `.?AV?$TClassFactory@VBuildingClass@@@@`.
struct Vtbl_TClassFactory_BuildingClass { static char* Vtable() { return &VT_007F3BD0; } };
template struct VtableObj<Vtbl_TClassFactory_BuildingClass>;

// FUNCTION: GAMEMD 0x006C3640
// TClassFactory<AircraftClass> -- seats retail vtable 0x007F3BE8; locator 0x0080AB68 -> type
//   descriptor 0x008418F8 `.?AV?$TClassFactory@VAircraftClass@@@@`.
struct Vtbl_TClassFactory_AircraftClass { static char* Vtable() { return &VT_007F3BE8; } };
template struct VtableObj<Vtbl_TClassFactory_AircraftClass>;

// FUNCTION: GAMEMD 0x006C37C0
// TClassFactory<InfantryClass> -- seats retail vtable 0x007F3C00; locator 0x0080ABB8 -> type
//   descriptor 0x00841928 `.?AV?$TClassFactory@VInfantryClass@@@@`.
struct Vtbl_TClassFactory_InfantryClass { static char* Vtable() { return &VT_007F3C00; } };
template struct VtableObj<Vtbl_TClassFactory_InfantryClass>;

// FUNCTION: GAMEMD 0x006C3940
// TClassFactory<AnimClass> -- seats retail vtable 0x007F3C18; locator 0x0080AC08 -> type
//   descriptor 0x00841958 `.?AV?$TClassFactory@VAnimClass@@@@`.
struct Vtbl_TClassFactory_AnimClass { static char* Vtable() { return &VT_007F3C18; } };
template struct VtableObj<Vtbl_TClassFactory_AnimClass>;

// FUNCTION: GAMEMD 0x006C3AC0
// TClassFactory<AnimTypeClass> -- seats retail vtable 0x007F3C30; locator 0x0080AC58 -> type
//   descriptor 0x00841988 `.?AV?$TClassFactory@VAnimTypeClass@@@@`.
struct Vtbl_TClassFactory_AnimTypeClass { static char* Vtable() { return &VT_007F3C30; } };
template struct VtableObj<Vtbl_TClassFactory_AnimTypeClass>;

// FUNCTION: GAMEMD 0x006C3C40
// TClassFactory<HouseTypeClass> -- seats retail vtable 0x007F3C48; locator 0x0080ACA8 -> type
//   descriptor 0x008419B8 `.?AV?$TClassFactory@VHouseTypeClass@@@@`.
struct Vtbl_TClassFactory_HouseTypeClass { static char* Vtable() { return &VT_007F3C48; } };
template struct VtableObj<Vtbl_TClassFactory_HouseTypeClass>;

// FUNCTION: GAMEMD 0x006C3DC0
// TClassFactory<HouseClass> -- seats retail vtable 0x007F3C60; locator 0x0080ACF8 -> type
//   descriptor 0x008419E8 `.?AV?$TClassFactory@VHouseClass@@@@`.
struct Vtbl_TClassFactory_HouseClass { static char* Vtable() { return &VT_007F3C60; } };
template struct VtableObj<Vtbl_TClassFactory_HouseClass>;

// FUNCTION: GAMEMD 0x006C3F40
// TClassFactory<DriveLocomotionClass> -- seats retail vtable 0x007F3C78; locator 0x0080AD48 -> type
//   descriptor 0x00841A18 `.?AV?$TClassFactory@VDriveLocomotionClass@@@@`.
struct Vtbl_TClassFactory_DriveLocomotionClass { static char* Vtable() { return &VT_007F3C78; } };
template struct VtableObj<Vtbl_TClassFactory_DriveLocomotionClass>;

// FUNCTION: GAMEMD 0x006C40C0
// TClassFactory<JumpjetLocomotionClass> -- seats retail vtable 0x007F3C90; locator 0x0080AD98 -> type
//   descriptor 0x00841A50 `.?AV?$TClassFactory@VJumpjetLocomotionClass@@@@`.
struct Vtbl_TClassFactory_JumpjetLocomotionClass { static char* Vtable() { return &VT_007F3C90; } };
template struct VtableObj<Vtbl_TClassFactory_JumpjetLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4240
// TClassFactory<HoverLocomotionClass> -- seats retail vtable 0x007F3CA8; locator 0x0080ADE8 -> type
//   descriptor 0x00841A88 `.?AV?$TClassFactory@VHoverLocomotionClass@@@@`.
struct Vtbl_TClassFactory_HoverLocomotionClass { static char* Vtable() { return &VT_007F3CA8; } };
template struct VtableObj<Vtbl_TClassFactory_HoverLocomotionClass>;

// FUNCTION: GAMEMD 0x006C43C0
// TClassFactory<RocketLocomotionClass> -- seats retail vtable 0x007F3CC0; locator 0x0080AE38 -> type
//   descriptor 0x00841AC0 `.?AV?$TClassFactory@VRocketLocomotionClass@@@@`.
struct Vtbl_TClassFactory_RocketLocomotionClass { static char* Vtable() { return &VT_007F3CC0; } };
template struct VtableObj<Vtbl_TClassFactory_RocketLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4540
// TClassFactory<TunnelLocomotionClass> -- seats retail vtable 0x007F3CD8; locator 0x0080AE88 -> type
//   descriptor 0x00841AF8 `.?AV?$TClassFactory@VTunnelLocomotionClass@@@@`.
struct Vtbl_TClassFactory_TunnelLocomotionClass { static char* Vtable() { return &VT_007F3CD8; } };
template struct VtableObj<Vtbl_TClassFactory_TunnelLocomotionClass>;

// FUNCTION: GAMEMD 0x006C46C0
// TClassFactory<WalkLocomotionClass> -- seats retail vtable 0x007F3CF0; locator 0x0080AED8 -> type
//   descriptor 0x00841B30 `.?AV?$TClassFactory@VWalkLocomotionClass@@@@`.
struct Vtbl_TClassFactory_WalkLocomotionClass { static char* Vtable() { return &VT_007F3CF0; } };
template struct VtableObj<Vtbl_TClassFactory_WalkLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4840
// TClassFactory<DropPodLocomotionClass> -- seats retail vtable 0x007F3D08; locator 0x0080AF28 -> type
//   descriptor 0x00841B68 `.?AV?$TClassFactory@VDropPodLocomotionClass@@@@`.
struct Vtbl_TClassFactory_DropPodLocomotionClass { static char* Vtable() { return &VT_007F3D08; } };
template struct VtableObj<Vtbl_TClassFactory_DropPodLocomotionClass>;

// FUNCTION: GAMEMD 0x006C49C0
// TClassFactory<FlyLocomotionClass> -- seats retail vtable 0x007F3D20; locator 0x0080AF78 -> type
//   descriptor 0x00841BA0 `.?AV?$TClassFactory@VFlyLocomotionClass@@@@`.
struct Vtbl_TClassFactory_FlyLocomotionClass { static char* Vtable() { return &VT_007F3D20; } };
template struct VtableObj<Vtbl_TClassFactory_FlyLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4B40
// TClassFactory<TeleportLocomotionClass> -- seats retail vtable 0x007F3D38; locator 0x0080AFC8 -> type
//   descriptor 0x00841BD8 `.?AV?$TClassFactory@VTeleportLocomotionClass@@@@`.
struct Vtbl_TClassFactory_TeleportLocomotionClass { static char* Vtable() { return &VT_007F3D38; } };
template struct VtableObj<Vtbl_TClassFactory_TeleportLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4CC0
// TClassFactory<MechLocomotionClass> -- seats retail vtable 0x007F3D50; locator 0x0080B018 -> type
//   descriptor 0x00841C18 `.?AV?$TClassFactory@VMechLocomotionClass@@@@`.
struct Vtbl_TClassFactory_MechLocomotionClass { static char* Vtable() { return &VT_007F3D50; } };
template struct VtableObj<Vtbl_TClassFactory_MechLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4E40
// TClassFactory<ShipLocomotionClass> -- seats retail vtable 0x007F3D68; locator 0x0080B068 -> type
//   descriptor 0x00841C50 `.?AV?$TClassFactory@VShipLocomotionClass@@@@`.
struct Vtbl_TClassFactory_ShipLocomotionClass { static char* Vtable() { return &VT_007F3D68; } };
template struct VtableObj<Vtbl_TClassFactory_ShipLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4FC0
// TClassFactory<BulletClass> -- seats retail vtable 0x007F3D80; locator 0x0080B0B8 -> type
//   descriptor 0x00841C88 `.?AV?$TClassFactory@VBulletClass@@@@`.
struct Vtbl_TClassFactory_BulletClass { static char* Vtable() { return &VT_007F3D80; } };
template struct VtableObj<Vtbl_TClassFactory_BulletClass>;

// FUNCTION: GAMEMD 0x006C5140
// TClassFactory<FactoryClass> -- seats retail vtable 0x007F3D98; locator 0x0080B108 -> type
//   descriptor 0x00841CB8 `.?AV?$TClassFactory@VFactoryClass@@@@`.
struct Vtbl_TClassFactory_FactoryClass { static char* Vtable() { return &VT_007F3D98; } };
template struct VtableObj<Vtbl_TClassFactory_FactoryClass>;

// FUNCTION: GAMEMD 0x006C52C0
// TClassFactory<WarheadTypeClass> -- seats retail vtable 0x007F3DB0; locator 0x0080B158 -> type
//   descriptor 0x00841CE8 `.?AV?$TClassFactory@VWarheadTypeClass@@@@`.
struct Vtbl_TClassFactory_WarheadTypeClass { static char* Vtable() { return &VT_007F3DB0; } };
template struct VtableObj<Vtbl_TClassFactory_WarheadTypeClass>;

// FUNCTION: GAMEMD 0x006C5440
// TClassFactory<WeaponTypeClass> -- seats retail vtable 0x007F3DC8; locator 0x0080B1A8 -> type
//   descriptor 0x00841D20 `.?AV?$TClassFactory@VWeaponTypeClass@@@@`.
struct Vtbl_TClassFactory_WeaponTypeClass { static char* Vtable() { return &VT_007F3DC8; } };
template struct VtableObj<Vtbl_TClassFactory_WeaponTypeClass>;

// FUNCTION: GAMEMD 0x006C55C0
// TClassFactory<ParticleClass> -- seats retail vtable 0x007F3DE0; locator 0x0080B1F8 -> type
//   descriptor 0x00841D58 `.?AV?$TClassFactory@VParticleClass@@@@`.
struct Vtbl_TClassFactory_ParticleClass { static char* Vtable() { return &VT_007F3DE0; } };
template struct VtableObj<Vtbl_TClassFactory_ParticleClass>;

// FUNCTION: GAMEMD 0x006C5740
// TClassFactory<ParticleTypeClass> -- seats retail vtable 0x007F3DF8; locator 0x0080B248 -> type
//   descriptor 0x00841D88 `.?AV?$TClassFactory@VParticleTypeClass@@@@`.
struct Vtbl_TClassFactory_ParticleTypeClass { static char* Vtable() { return &VT_007F3DF8; } };
template struct VtableObj<Vtbl_TClassFactory_ParticleTypeClass>;

// FUNCTION: GAMEMD 0x006C58C0
// TClassFactory<ParticleSystemClass> -- seats retail vtable 0x007F3E10; locator 0x0080B298 -> type
//   descriptor 0x00841DC0 `.?AV?$TClassFactory@VParticleSystemClass@@@@`.
struct Vtbl_TClassFactory_ParticleSystemClass { static char* Vtable() { return &VT_007F3E10; } };
template struct VtableObj<Vtbl_TClassFactory_ParticleSystemClass>;

// FUNCTION: GAMEMD 0x006C5A40
// TClassFactory<ParticleSystemTypeClass> -- seats retail vtable 0x007F3E28; locator 0x0080B2E8 -> type
//   descriptor 0x00841DF8 `.?AV?$TClassFactory@VParticleSystemTypeClass@@@@`.
struct Vtbl_TClassFactory_ParticleSystemTypeClass { static char* Vtable() { return &VT_007F3E28; } };
template struct VtableObj<Vtbl_TClassFactory_ParticleSystemTypeClass>;

// FUNCTION: GAMEMD 0x006C5BC0
// TClassFactory<AITriggerTypeClass> -- seats retail vtable 0x007F3E40; locator 0x0080B338 -> type
//   descriptor 0x00841E38 `.?AV?$TClassFactory@VAITriggerTypeClass@@@@`.
struct Vtbl_TClassFactory_AITriggerTypeClass { static char* Vtable() { return &VT_007F3E40; } };
template struct VtableObj<Vtbl_TClassFactory_AITriggerTypeClass>;

// FUNCTION: GAMEMD 0x006C5D40
// TClassFactory<NeuronClass> -- seats retail vtable 0x007F3E58; locator 0x0080B388 -> type
//   descriptor 0x00841E70 `.?AV?$TClassFactory@VNeuronClass@@@@`.
struct Vtbl_TClassFactory_NeuronClass { static char* Vtable() { return &VT_007F3E58; } };
template struct VtableObj<Vtbl_TClassFactory_NeuronClass>;

// FUNCTION: GAMEMD 0x006C5EC0
// TClassFactory<FoggedObjectClass> -- seats retail vtable 0x007F3E70; locator 0x0080B3D8 -> type
//   descriptor 0x00841EA0 `.?AV?$TClassFactory@VFoggedObjectClass@@@@`.
struct Vtbl_TClassFactory_FoggedObjectClass { static char* Vtable() { return &VT_007F3E70; } };
template struct VtableObj<Vtbl_TClassFactory_FoggedObjectClass>;

// FUNCTION: GAMEMD 0x006C6040
// TClassFactory<AlphaShapeClass> -- seats retail vtable 0x007F3E88; locator 0x0080B428 -> type
//   descriptor 0x00841ED8 `.?AV?$TClassFactory@VAlphaShapeClass@@@@`.
struct Vtbl_TClassFactory_AlphaShapeClass { static char* Vtable() { return &VT_007F3E88; } };
template struct VtableObj<Vtbl_TClassFactory_AlphaShapeClass>;

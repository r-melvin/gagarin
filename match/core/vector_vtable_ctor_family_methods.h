// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x6C07C0 and its 77 siblings: a four-instruction body,
//   `MOV EAX,ECX; MOV [EAX+4],0; MOV [EAX],<vtable>; RET`. One member is
//   cleared at +4 *before* the vtable is seated at +0, and the object is
//   returned in EAX. Only the vtable address varies between instances, and
//   there are 78 bodies over 78 distinct vtables -- one each.
//
//   These 78 bodies are one class template's member, emitted once per
//   instantiation as its own COMDAT. This header carries the template; the
//   translation unit beside it carries one explicit instantiation per retail
//   address.
//
//   THE CLASSES ARE RTTI-CONFIRMED. The vtable each body seats was re-read
//   out of the binary as the `imm32` of the store, and every one of the 78
//   carries a complete object locator: 77 `TClassFactory<T>` instantiations
//   over concrete engine classes (`CStreamClass`, `WaveClass`, the eleven
//   locomotors, the type classes, ...) and one `rc_ptr_base`. So this family
//   is the engine's persistence class-factory table, and the traits types are
//   now named after those classes. The `VtableObj`/`Init` spelling stays a
//   modelling stand-in for the reason given below -- the store order proves
//   retail's member is not a constructor -- but nothing address-suffixed is
//   left in it.
//
//   WHY THIS FAMILY NEEDS A TRAITS PARAMETER AND THE DELETING-DESTRUCTOR
//   FAMILY DOES NOT. In vector_dtor_family_methods.h the vtable address is
//   written nowhere in the source: it is the instantiation's own vtable, which
//   the compiler seats and the linker relocates. That cannot work here,
//   because **the store order proves this body is not a constructor**. A real
//   C++ constructor always seats the vptr before initialising members; VC6
//   emits, for `template<class T> struct A { virtual void S0(); int Field4;
//   A() { Field4 = 0; } };`
//
//       MOV EAX,ECX ; MOV [EAX],<own vtable> ; MOV [EAX+4],0 ; RET
//
//   -- the two stores the other way round from retail. Retail clears +4 first,
//   so retail's own source declared this as an ordinary member that *seats* a
//   vtable pointer, not as a constructor that owns one. The vtable address is
//   therefore an input to the body, carried by a traits type parameter, and
//   the emitted relocation is to that named vtable rather than to the
//   instantiation's own. Tested, not assumed: the constructor spelling was
//   compiled and its store order read off the object.
//
//   KNOWN LIMITATION -- this file is a staging ground, not a destination. The
//   TU-partition work established that MSVC6 emits each template instantiation
//   as a COMDAT into the translation unit that instantiated it. These 78
//   instantiations therefore belong to many different original Westwood
//   translation units, not to one. Grouping them in a single sweep file is
//   correct for matching bytes now and wrong for reproducing retail's link
//   order eventually; they will have to be redistributed to their owning TUs
//   when the partition is reconstructed.
#ifndef GG_MATCH_CORE_VECTOR_VTABLE_CTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_VTABLE_CTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The object this family seats a vtable into. The vtable pointer is an
// explicit member, not a compiler-managed one, for the reason given above.
template<class T>
struct VtableObj
{
    char* Vptr;    // +0x0000
    int   Field4;  // +0x0004

    VtableObj* Init()
    {
        this->Field4 = 0;
        this->Vptr   = T::Vtable();
        return this;
    }
};

// The retail vtables seated by this family. Each is the one vtable of one of
// the instantiations in vector_vtable_ctor_family_methods.cpp, with the class
// named by its own complete object locator four bytes below it. 77 of the 78
// are `TClassFactory<T>` over a concrete engine class; the odd one out is
// `rc_ptr_base`. The traits types in the translation unit are named after
// those classes rather than after the address of the body they produce.
// VTABLE: GAMEMD 0x7F094C -- rc_ptr_base
extern char VT_007F094C;
// VTABLE: GAMEMD 0x7F3768 -- TClassFactory<CStreamClass>
extern char VT_007F3768;
// VTABLE: GAMEMD 0x7F3780 -- TClassFactory<WaveClass>
extern char VT_007F3780;
// VTABLE: GAMEMD 0x7F3798 -- TClassFactory<TerrainTypeClass>
extern char VT_007F3798;
// VTABLE: GAMEMD 0x7F37B0 -- TClassFactory<TerrainClass>
extern char VT_007F37B0;
// VTABLE: GAMEMD 0x7F37C8 -- TClassFactory<SuperWeaponTypeClass>
extern char VT_007F37C8;
// VTABLE: GAMEMD 0x7F37E0 -- TClassFactory<SuperClass>
extern char VT_007F37E0;
// VTABLE: GAMEMD 0x7F37F8 -- TClassFactory<Tactical>
extern char VT_007F37F8;
// VTABLE: GAMEMD 0x7F3810 -- TClassFactory<CellClass>
extern char VT_007F3810;
// VTABLE: GAMEMD 0x7F3828 -- TClassFactory<EMPulseClass>
extern char VT_007F3828;
// VTABLE: GAMEMD 0x7F3840 -- TClassFactory<LightSourceClass>
extern char VT_007F3840;
// VTABLE: GAMEMD 0x7F3858 -- TClassFactory<SideClass>
extern char VT_007F3858;
// VTABLE: GAMEMD 0x7F3870 -- TClassFactory<TiberiumClass>
extern char VT_007F3870;
// VTABLE: GAMEMD 0x7F3888 -- TClassFactory<TubeClass>
extern char VT_007F3888;
// VTABLE: GAMEMD 0x7F38A0 -- TClassFactory<CampaignClass>
extern char VT_007F38A0;
// VTABLE: GAMEMD 0x7F38B8 -- TClassFactory<BuildingLightClass>
extern char VT_007F38B8;
// VTABLE: GAMEMD 0x7F38D0 -- TClassFactory<WaypointPathClass>
extern char VT_007F38D0;
// VTABLE: GAMEMD 0x7F38E8 -- TClassFactory<TemporalClass>
extern char VT_007F38E8;
// VTABLE: GAMEMD 0x7F3900 -- TClassFactory<AirstrikeClass>
extern char VT_007F3900;
// VTABLE: GAMEMD 0x7F3918 -- TClassFactory<SpawnManagerClass>
extern char VT_007F3918;
// VTABLE: GAMEMD 0x7F3930 -- TClassFactory<SlaveManagerClass>
extern char VT_007F3930;
// VTABLE: GAMEMD 0x7F3948 -- TClassFactory<CaptureManagerClass>
extern char VT_007F3948;
// VTABLE: GAMEMD 0x7F3960 -- TClassFactory<DiskLaserClass>
extern char VT_007F3960;
// VTABLE: GAMEMD 0x7F3978 -- TClassFactory<ParasiteClass>
extern char VT_007F3978;
// VTABLE: GAMEMD 0x7F3990 -- TClassFactory<BombClass>
extern char VT_007F3990;
// VTABLE: GAMEMD 0x7F39A8 -- TClassFactory<RadSiteClass>
extern char VT_007F39A8;
// VTABLE: GAMEMD 0x7F39C0 -- TClassFactory<TEventClass>
extern char VT_007F39C0;
// VTABLE: GAMEMD 0x7F39D8 -- TClassFactory<VoxelAnimTypeClass>
extern char VT_007F39D8;
// VTABLE: GAMEMD 0x7F39F0 -- TClassFactory<VoxelAnimClass>
extern char VT_007F39F0;
// VTABLE: GAMEMD 0x7F3A08 -- TClassFactory<TActionClass>
extern char VT_007F3A08;
// VTABLE: GAMEMD 0x7F3A20 -- TClassFactory<TriggerClass>
extern char VT_007F3A20;
// VTABLE: GAMEMD 0x7F3A38 -- TClassFactory<TriggerTypeClass>
extern char VT_007F3A38;
// VTABLE: GAMEMD 0x7F3A50 -- TClassFactory<ScriptClass>
extern char VT_007F3A50;
// VTABLE: GAMEMD 0x7F3A68 -- TClassFactory<ScriptTypeClass>
extern char VT_007F3A68;
// VTABLE: GAMEMD 0x7F3A80 -- TClassFactory<TagClass>
extern char VT_007F3A80;
// VTABLE: GAMEMD 0x7F3A98 -- TClassFactory<TagTypeClass>
extern char VT_007F3A98;
// VTABLE: GAMEMD 0x7F3AB0 -- TClassFactory<TeamClass>
extern char VT_007F3AB0;
// VTABLE: GAMEMD 0x7F3AC8 -- TClassFactory<TeamTypeClass>
extern char VT_007F3AC8;
// VTABLE: GAMEMD 0x7F3AE0 -- TClassFactory<TaskForceClass>
extern char VT_007F3AE0;
// VTABLE: GAMEMD 0x7F3AF8 -- TClassFactory<UnitTypeClass>
extern char VT_007F3AF8;
// VTABLE: GAMEMD 0x7F3B10 -- TClassFactory<BuildingTypeClass>
extern char VT_007F3B10;
// VTABLE: GAMEMD 0x7F3B28 -- TClassFactory<AircraftTypeClass>
extern char VT_007F3B28;
// VTABLE: GAMEMD 0x7F3B40 -- TClassFactory<InfantryTypeClass>
extern char VT_007F3B40;
// VTABLE: GAMEMD 0x7F3B58 -- TClassFactory<BulletTypeClass>
extern char VT_007F3B58;
// VTABLE: GAMEMD 0x7F3B70 -- TClassFactory<IsometricTileTypeClass>
extern char VT_007F3B70;
// VTABLE: GAMEMD 0x7F3B88 -- TClassFactory<OverlayTypeClass>
extern char VT_007F3B88;
// VTABLE: GAMEMD 0x7F3BA0 -- TClassFactory<SmudgeTypeClass>
extern char VT_007F3BA0;
// VTABLE: GAMEMD 0x7F3BB8 -- TClassFactory<UnitClass>
extern char VT_007F3BB8;
// VTABLE: GAMEMD 0x7F3BD0 -- TClassFactory<BuildingClass>
extern char VT_007F3BD0;
// VTABLE: GAMEMD 0x7F3BE8 -- TClassFactory<AircraftClass>
extern char VT_007F3BE8;
// VTABLE: GAMEMD 0x7F3C00 -- TClassFactory<InfantryClass>
extern char VT_007F3C00;
// VTABLE: GAMEMD 0x7F3C18 -- TClassFactory<AnimClass>
extern char VT_007F3C18;
// VTABLE: GAMEMD 0x7F3C30 -- TClassFactory<AnimTypeClass>
extern char VT_007F3C30;
// VTABLE: GAMEMD 0x7F3C48 -- TClassFactory<HouseTypeClass>
extern char VT_007F3C48;
// VTABLE: GAMEMD 0x7F3C60 -- TClassFactory<HouseClass>
extern char VT_007F3C60;
// VTABLE: GAMEMD 0x7F3C78 -- TClassFactory<DriveLocomotionClass>
extern char VT_007F3C78;
// VTABLE: GAMEMD 0x7F3C90 -- TClassFactory<JumpjetLocomotionClass>
extern char VT_007F3C90;
// VTABLE: GAMEMD 0x7F3CA8 -- TClassFactory<HoverLocomotionClass>
extern char VT_007F3CA8;
// VTABLE: GAMEMD 0x7F3CC0 -- TClassFactory<RocketLocomotionClass>
extern char VT_007F3CC0;
// VTABLE: GAMEMD 0x7F3CD8 -- TClassFactory<TunnelLocomotionClass>
extern char VT_007F3CD8;
// VTABLE: GAMEMD 0x7F3CF0 -- TClassFactory<WalkLocomotionClass>
extern char VT_007F3CF0;
// VTABLE: GAMEMD 0x7F3D08 -- TClassFactory<DropPodLocomotionClass>
extern char VT_007F3D08;
// VTABLE: GAMEMD 0x7F3D20 -- TClassFactory<FlyLocomotionClass>
extern char VT_007F3D20;
// VTABLE: GAMEMD 0x7F3D38 -- TClassFactory<TeleportLocomotionClass>
extern char VT_007F3D38;
// VTABLE: GAMEMD 0x7F3D50 -- TClassFactory<MechLocomotionClass>
extern char VT_007F3D50;
// VTABLE: GAMEMD 0x7F3D68 -- TClassFactory<ShipLocomotionClass>
extern char VT_007F3D68;
// VTABLE: GAMEMD 0x7F3D80 -- TClassFactory<BulletClass>
extern char VT_007F3D80;
// VTABLE: GAMEMD 0x7F3D98 -- TClassFactory<FactoryClass>
extern char VT_007F3D98;
// VTABLE: GAMEMD 0x7F3DB0 -- TClassFactory<WarheadTypeClass>
extern char VT_007F3DB0;
// VTABLE: GAMEMD 0x7F3DC8 -- TClassFactory<WeaponTypeClass>
extern char VT_007F3DC8;
// VTABLE: GAMEMD 0x7F3DE0 -- TClassFactory<ParticleClass>
extern char VT_007F3DE0;
// VTABLE: GAMEMD 0x7F3DF8 -- TClassFactory<ParticleTypeClass>
extern char VT_007F3DF8;
// VTABLE: GAMEMD 0x7F3E10 -- TClassFactory<ParticleSystemClass>
extern char VT_007F3E10;
// VTABLE: GAMEMD 0x7F3E28 -- TClassFactory<ParticleSystemTypeClass>
extern char VT_007F3E28;
// VTABLE: GAMEMD 0x7F3E40 -- TClassFactory<AITriggerTypeClass>
extern char VT_007F3E40;
// VTABLE: GAMEMD 0x7F3E58 -- TClassFactory<NeuronClass>
extern char VT_007F3E58;
// VTABLE: GAMEMD 0x7F3E70 -- TClassFactory<FoggedObjectClass>
extern char VT_007F3E70;
// VTABLE: GAMEMD 0x7F3E88 -- TClassFactory<AlphaShapeClass>
extern char VT_007F3E88;

#endif  // GG_MATCH_CORE_VECTOR_VTABLE_CTOR_FAMILY_METHODS_H

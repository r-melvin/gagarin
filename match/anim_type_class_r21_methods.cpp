// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   AnimTypeClass members read off retail gamemd.exe v1.001 (vtable 0x7E3608).
//   Address index: 0x4289D0, 0x428EA0
#include "FUNCTION.H"
#include "vector_class_operations.h"

// GLOBAL: GAMEMD 0xB0F670 -- the registry every abstract object leaves when destroyed.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F670;
// GLOBAL: GAMEMD 0x8B4150 -- AnimTypeClass::Array.
extern DynamicVectorClass<AnimTypeClass*> DAT_008B4150;

// FUNCTION: GAMEMD 0x427530
AnimTypeClass::AnimTypeClass(const char* id) throw()
    : ObjectTypeClass(id), ArrayIndex(-1), MiddleFrameIndex(0), MiddleFrameWidth(0), MiddleFrameHeight(0),
      unknown_2A4(0), Damage(0), Rate(1), Start(0), LoopStart(0), LoopEnd(0), End(0), LoopCount(0), Next(0),
      SpawnsParticle(-1), NumParticles(0), DetailLevel(0), TranslucencyDetailLevel(0),
      RandomLoopDelay(0, 0), RandomRate(0, 0), Translucency(0), Spawns(0), SpawnCount(0), Report(-1),
      StopSound(-1), BounceAnim(0), ExpireAnim(0), TrailerAnim(0), TrailerSeperation(0),
      Elasticity(0.800000011920929), MinZVel(3.5), unknown_double_320(3.5), MaxXYVel(15.0), Warhead(0),
      DamageRadius(0), TiberiumSpawnType(0), TiberiumSpreadRadius(0), YSortAdjust(0), YDrawOffset(0),
      ZAdjust(0), MakeInfantry(-1), RunningFrames(0), IsFlamingGuy(false), IsVeins(false), IsMeteor(false),
      TiberiumChainReaction(false), IsTiberium(false), HideIfNoOre(false), Bouncer(false), Tiled(false),
      ShouldUseCellDrawer(true), UseNormalLight(false), DemandLoad(false), FreeLoad(false),
      IsAnimatedTiberium(false), AltPalette(false), Normalized(false), Layer(3), DoubleThick(false),
      Flat(false), Translucent(false), Scorch(false), Flamer(false), Crater(false), ForceBigCraters(false),
      Sticky(false), PingPong(false), Reverse(false), Shadow(false), PsiWarning(false),
      ShouldFogRemove(true)
{
    vf_rtti_5();
    IsLogic = true;
    RadarInvisible = true;
    Selectable = false;
    LegalTarget = false;
    Insignificant = true;
    Immune = true;
    AllowCellContent = false;
    DAT_008B4150.AddItem(this);
    DAT_00B0F670.AddItem(this);
    ArrayIndex = DAT_008B4150.FindItemIndex(this);
}

// FUNCTION: GAMEMD 0x4289D0
// Slot 13: feed the synchronisation checksum with the type's layer, flags and timing.
void AnimTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(Layer);
    crc->FUN_004A1CA0(Normalized);
    crc->FUN_004A1CA0(Flat);
    crc->FUN_004A1CA0(Translucent);
    crc->FUN_004A1CA0(Scorch);
    crc->FUN_004A1CA0(Flamer);
    crc->FUN_004A1CA0(Crater);
    crc->FUN_004A1CA0(Sticky);
    crc->FUN_004A1CA0(PingPong);
    crc->FUN_004A1CA0(Reverse);
    crc->FUN_004A1CA0(Shadow);
    crc->FUN_004A1D50(MiddleFrameIndex);
    crc->FUN_004A1D90(Damage);
    crc->FUN_004A1CA0(TiberiumChainReaction);
    crc->FUN_004A1D50(Rate);
    crc->FUN_004A1D50(Start);
    crc->FUN_004A1D50(LoopStart);
    crc->FUN_004A1D50(LoopEnd);
    crc->FUN_004A1D50(End);
    crc->FUN_004A1D50(Report);
    crc->FUN_004A1D50(StopSound);
    crc->FUN_004A1D50(NumParticles);
    crc->FUN_004A1D50(DetailLevel);
    crc->FUN_004A1D50(TranslucencyDetailLevel);
    crc->FUN_004A1D50(RandomLoopDelay.Min);
    crc->FUN_004A1D50(RandomLoopDelay.Max);
    crc->FUN_004A1D50(Translucency);
    crc->FUN_004A1CA0(Tiled);
}

// The scalar deleting form of the destructor (??_G); the destructor body is inlined into it.
// FUNCTION: GAMEMD 0x427880
// FUNCTION: GAMEMD 0x428EA0
AnimTypeClass::~AnimTypeClass()
{
    DAT_00B0F670.RemoveItem(this);
    DAT_008B4150.RemoveItem(this);
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   AnimTypeClass members read off retail gamemd.exe v1.001 (vtable 0x7E3608).
//   Address index: 0x4289D0, 0x428EA0
#include "../_layout/anim_type_class.h"
#include "../core/vector_class_operations.h"
#include "../_layout/obj_004a1d30.h"

// GLOBAL: GAMEMD 0xB0F670 -- the registry every abstract object leaves when destroyed.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F670;
// GLOBAL: GAMEMD 0x8B4150 -- AnimTypeClass::Array.
extern DynamicVectorClass<AnimTypeClass*> DAT_008B4150;

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

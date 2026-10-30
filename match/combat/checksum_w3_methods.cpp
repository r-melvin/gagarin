// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Synchronisation-checksum virtuals (slot 13) of SuperClass and VoxelAnimClass,
//   read off retail gamemd.exe v1.001. Functions are in ascending retail address order.

#include "../_layout/super_class.h"
#include "../_layout/tube_class.h"
#include "../movement/waypoint_path_class_methods.h"
#include "../_layout/super_weapon_type_class.h"
#include "../_layout/slave_manager_class.h"
#include "../_layout/spawn_manager_class.h"
#include "../_layout/voxel_anim_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/frame_timer.h"
#include "../_layout/obj_004a1d30.h"
#include "../ai/tevent_class_methods.h"

// A pointed-to object's RTTI-info interface subobject sits at +4; its slot 4 (+0x10),
// __stdcall with the subobject as `this`, yields the id mixed into the checksum.
struct RttiInfoView
{
    virtual long __stdcall Slot0();
    virtual long __stdcall Slot1();
    virtual long __stdcall Slot2();
    virtual long __stdcall Slot3();
    virtual int __stdcall Slot4();
};

// Pass a stored flag byte through untouched (retail does not normalise it).
static inline bool& AsBool(unsigned char& flag)
{
    return reinterpret_cast<bool&>(flag);
}

static inline int RttiInfoId(void* object)
{
    return reinterpret_cast<RttiInfoView*>(static_cast<char*>(object) + 4)->Slot4();
}


class TiberiumClass : public AbstractTypeClass
{
public:
    virtual void vf_13(Obj_004A1D30* crc);
    char unknown_98[4];          // +0x98
    int unknown_9C;              // +0x9C
    char unknown_A0[8];          // +0xA0
    int unknown_A8;              // +0xA8
    char unknown_AC[0xC];        // +0xAC
    int unknown_B8;              // +0xB8
    int unknown_BC;              // +0xBC
    int unknown_C0;              // +0xC0
    char unknown_C4[0x20];       // +0xC4
    int unknown_E4;              // +0xE4
    int unknown_E8;              // +0xE8
};
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_A8) == 0xA8);
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_E8) == 0xE8);

// FUNCTION: GAMEMD 0x6CE020
// Super weapon flags and charge state, plus the attached animation's identity.
void SuperClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1CA0(IsPresent);
    crc->FUN_004A1CA0(IsOneTime);
    crc->FUN_004A1CA0(IsReady);
    crc->FUN_004A1D50(CameoChargeState);
    crc->FUN_004A1D50(ChargeDrainState);
    crc->FUN_004A1CA0(CanHold);
    crc->FUN_004A1CA0(AnimationGotInvalid);
    if (Animation) {
        crc->FUN_004A1D50(*(unsigned char*)((char*)Animation + 0x195));
        crc->FUN_004A1D50(RttiInfoId(Animation));
    }
}

// FUNCTION: GAMEMD 0x74AA30
// Voxel animation: frame counter, its type and cell references, flags.
void VoxelAnimClass::vf_13(Obj_004A1D30* crc)
{
    ObjectClass::vf_13(crc);
    crc->FUN_004A1D50(unknown_100);
    crc->FUN_004A1D50(RttiInfoId(unknown_104));
    if (unknown_108) {
        crc->FUN_004A1D50(RttiInfoId(reinterpret_cast<void*>(unknown_108)));
    }
    crc->FUN_004A1D50(RttiInfoId(reinterpret_cast<void*>(unknown_10C)));
    crc->FUN_004A1CA0(AsBool(unknown_110));
    crc->FUN_004A1CA0(AsBool(unknown_13C));
    crc->FUN_004A1D50(unknown_140);
}

// FUNCTION: GAMEMD 0x71F820
// Trigger event: its two referenced objects and parameters.
void TEventClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    if (NextEvent) {
        crc->FUN_004A1D50(RttiInfoId(NextEvent));
    }
    crc->FUN_004A1D50(EventKind);
    if (TeamType) {
        crc->FUN_004A1D50(RttiInfoId(TeamType));
    }
    crc->FUN_004A1D50(Value);
}

// FUNCTION: GAMEMD 0x727B30
// Trigger type: its house type and the chain links.
void TriggerTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(RttiInfoId(House));
    if (NextTrigger) {
        crc->FUN_004A1D50(RttiInfoId(NextTrigger));
    }
    if (FirstEvent) {
        crc->FUN_004A1D50(RttiInfoId(FirstEvent));
    }
    if (FirstAction) {
        crc->FUN_004A1D50(RttiInfoId(FirstAction));
    }
}

// FUNCTION: GAMEMD 0x728630
// Tube: its endpoints, facing steps and the 100-entry direction list.
void TubeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D30(StartCell.X);
    crc->FUN_004A1D30(StartCell.Y);
    crc->FUN_004A1D30(EndCell.X);
    crc->FUN_004A1D30(EndCell.Y);
    crc->FUN_004A1D50(Direction);
    for (int i = 0; i < 100; i++) {
        crc->FUN_004A1D50(Steps[i]);
    }
    crc->FUN_004A1D50(StepCount);
}

// FUNCTION: GAMEMD 0x763C00
// Waypoint path: its two numeric fields.
void WaypointPathClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D50(CurrentWaypointIndex);
    crc->FUN_004A1D50(Waypoints.Count);
}

// FUNCTION: GAMEMD 0x6CE910
// Super weapon type: its numeric settings and flags.
void SuperWeaponTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(ArrayIndex);
    crc->FUN_004A1D50(Action);
    crc->FUN_004A1D50(RechargeVoice);
    crc->FUN_004A1D50(ChargingVoice);
    crc->FUN_004A1D50(ImpatientVoice);
    crc->FUN_004A1D50(SuspendVoice);
    crc->FUN_004A1CA0(IsPowered);
    crc->FUN_004A1CA0(DisableableFromShell);
    crc->FUN_004A1CA0(PreClick);
    crc->FUN_004A1CA0(PostClick);
    crc->FUN_004A1D50(PreDependent);
    crc->FUN_004A1CA0(ShowTimer);
    crc->FUN_004A1D50(RechargeTime);
    crc->FUN_004A1D50(Type);
    crc->FUN_004A1CA0(UseChargeDrain);
    crc->FUN_004A1CA0(ManualControl);
}

// FUNCTION: GAMEMD 0x721DC0
// Tiberium type: growth and value settings.
void TiberiumClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(unknown_9C);
    crc->FUN_004A1D50(unknown_A8);
    crc->FUN_004A1D50(unknown_B8);
    crc->FUN_004A1D50(unknown_BC);
    crc->FUN_004A1D50(unknown_C0);
    crc->FUN_004A1D50(unknown_E4);
    crc->FUN_004A1D50(unknown_E8);
}

// FUNCTION: GAMEMD 0x6B10F0
// Slave manager: its counter and every slave's id, last to first.
void SlaveManagerClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D50(State);
    for (int i = SlaveNodes.Count - 1; i >= 0; i--) {
        crc->FUN_004A1D50(SlaveNodes.Items[i]->State);
    }
}

// FUNCTION: GAMEMD 0x6B7DE0
// Spawn manager: owner links and the remaining time of both timers.
void SpawnManagerClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D50(unknown_70);
    if (NewTarget) {
        crc->FUN_004A1D50(RttiInfoId(NewTarget));
    }
    if (Target) {
        crc->FUN_004A1D50(RttiInfoId(Target));
    }
    crc->FUN_004A1D50(UpdateTimer.GetTimeLeft());
    crc->FUN_004A1D50(SpawnTimer.GetTimeLeft());
    crc->FUN_004A1D50(SpawnedNodes.Count);
    crc->FUN_004A1D50(SpawnCount);
    if (SpawnType) {
        crc->FUN_004A1D50(RttiInfoId(SpawnType));
    }
    if (Owner) {
        crc->FUN_004A1D50(RttiInfoId(Owner));
    }
}

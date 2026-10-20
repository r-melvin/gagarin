// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6CB820, 0x6CC260-0x6CC297),
//   cross-checked against YRpp SuperClass.h / SuperWeaponTypeClass.h
//   (consult-only; reconfirmed numerically here).
//
// SuperClass — a per-house superweapon instance: recharge bookkeeping
// (CustomChargeTime override vs Type's [Type]RechargeTime) and the IsReady flag.
#ifndef GG_MATCH_COMBAT_SUPER_CLASS_METHODS_H
#define GG_MATCH_COMBAT_SUPER_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// SuperWeaponTypeClass — only RechargeTime @0xB0 is touched here
// (GetRechargeTime: mov eax,[Type]; mov eax,[eax+0xB0]).
struct SuperWeaponTypeClass
{
    char _pad0[0xB0];        // +0x00
    int  RechargeTime;       // +0xB0
    char _padB4[0xE5 - 0xB4];// +0xB4
    bool UseChargeDrain;     // +0xE5  (MOV DL,[EAX+0xE5] @0x6CC36A / 0x6CDE93)
};
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, RechargeTime)   == 0xB0);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, UseChargeDrain) == 0xE5);

// SuperClass : AbstractClass.  AbstractClass occupies [0x00..0x23] (the first
// SuperClass member, CustomChargeTime, sits at 0x24 in the retail disasm).
struct SuperClass
{
    char                  _base[0x24];        // +0x00  AbstractClass
    int                   CustomChargeTime;   // +0x24  -1 == "use Type default"
    SuperWeaponTypeClass* Type;               // +0x28
    char                  _pad2[0x6F - 0x2C]; // +0x2C
    bool                  IsReady;            // +0x6F  IsCharged / ready flag
    bool                  IsSuspended;        // +0x70  (MOV AL,[ECX+0x70] @0x6CC360)
    char                  _pad71[3];          // +0x71
    int                   ReadyFrame;         // +0x74
    int                   CameoChargeState;   // +0x78
    int                   ChargeDrainState;   // +0x7C  (MOV EAX,[ECX+0x7C] @0x6CC374)

    void SetReadiness(bool ready);            // GAMEMD 0x6CB820 __thiscall
    int  GetRechargeTime() const;             // GAMEMD 0x6CC260 __thiscall
    void SetRechargeTime(int time);           // GAMEMD 0x6CC280 __thiscall
    void ResetRechargeTime();                 // GAMEMD 0x6CC290 __thiscall
    bool CanFire() const;                     // GAMEMD 0x6CC360 __thiscall
    bool ShouldDrawProgress() const;          // GAMEMD 0x6CDE90 __thiscall
};
GG_STATIC_ASSERT(offsetof(SuperClass, CustomChargeTime) == 0x24);
GG_STATIC_ASSERT(offsetof(SuperClass, Type) == 0x28);
GG_STATIC_ASSERT(offsetof(SuperClass, IsSuspended)      == 0x70);
GG_STATIC_ASSERT(offsetof(SuperClass, ChargeDrainState) == 0x7C);
GG_STATIC_ASSERT(offsetof(SuperClass, IsReady) == 0x6F);

#endif  // GG_MATCH_COMBAT_SUPER_CLASS_METHODS_H

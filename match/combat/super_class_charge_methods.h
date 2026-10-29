// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6CB4D0 (SetOnHold) and 0x6CC1E0 (SetCharge):
//     CustomChargeTime        [EDI+0x24]  (MOV ESI,[EDI+0x24] @0x6CC1FB)
//     Type                    [ECX+0x28]  (MOV EAX,[ECX+0x28] @0x6CB4F6 / 0x6CC203)
//     RechargeTimer.StartTime [ECX+0x30]  (CMP dword [ECX+0x30],-1 @0x6CB503; MOV ESI,[ECX+0x30] @0x6CB51C)
//     RechargeTimer.CurrentTime [EAX+0x34] (MOV [EAX+0x4],EDX @0x6CC24A with EAX=this+0x30)
//     RechargeTimer.TimeLeft  [ECX+0x38]  (MOV EAX,[ECX+0x38] @0x6CB524; MOV [ECX+0x38],EAX @0x6CB53E)
//     CanHold                 [ECX+0x60]  (MOV AL,[ECX+0x60] @0x6CB4EA)
//     IsPresent               [ECX+0x6D]  (MOV AL,[ECX+0x6D] @0x6CB4D0 / [EDI+0x6D] @0x6CC1E6)
//     IsOneTime               [ECX+0x6E]  (MOV AL,[ECX+0x6E] @0x6CB4D8)
//     IsReady                 [EDI+0x6F]  (MOV byte [EDI+0x6F],1 @0x6CC227)
//     IsSuspended             [ECX+0x70]  (MOV AL,[ECX+0x70] @0x6CB4E3; MOV [ECX+0x70],BL @0x6CB513)
//     SuperWeaponTypeClass::RechargeTime  [EAX+0xB0] (MOV ESI,[EAX+0xB0] @0x6CC206)
//     SuperWeaponTypeClass::ManualControl [EAX+0xF5] (MOV DL,[EAX+0xF5] @0x6CB4F9)
//   Globals: Unsorted::CurrentFrame 0x00A8ED84 (MOV EDX,[0xA8ED84] @0x6CB509);
//   float constant 0x007EAAE0 = 0x3C23D70A = 0.01f (FMUL @0x6CC214).
//   Names cross-checked against YRpp
//   (every offset reconfirmed above). The
//   member run agrees with match/combat/super_class_methods.h and
//   super_class_more_methods.h (not edited; re-derived here so the TU stands
//   alone, extended with RechargeTimer, CanHold and IsOneTime).
#ifndef GG_MATCH_COMBAT_SUPER_CLASS_CHARGE_METHODS_H
#define GG_MATCH_COMBAT_SUPER_CLASS_CHARGE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x00A8ED84 — Unsorted::CurrentFrame, the global frame counter.
#include "../core/frame_counter.h"
#include "../_layout/frame_timer.h"
#include "../_layout/super_class.h"

// SuperClass : AbstractClass — a per-house superweapon instance.
class SuperClass;

// DynamicVectorClass<SuperClass*> at 0xB0F5B8 (an object: its address is the
// immediate `MOV ECX,0xB0F5B8`). Slot +0x10 is FindItemIndex(item const&).
struct SuperVector_006CB830
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual int  FindItemIndex(SuperClass* const& item);   // +0x0010

    // FUNCTION: GAMEMD 0x45ADD0 (decl; reloc) — remove the item at an index.
    void FUN_0045ADD0(int index);

    // DynamicVectorClass::Remove(item), expanded inline twice at 0x6CB830.
    // Issued through a member so the FindItemIndex dispatch stays virtual
    // (`MOV EDX,[vtbl]; CALL [EDX+0x10]`); called on the global object
    // directly VC6 devirtualises it.
    bool Remove(SuperClass* const& item)
    {
        int index = FindItemIndex(item);
        if (index != -1) {
            FUN_0045ADD0(index);
            return true;
        }
        return false;
    }
};
// GLOBAL: GAMEMD 0xB0F5B8 — the supers with a preclick animation pending.
extern SuperVector_006CB830 DAT_00B0F5B8;

// CDTimerClass Pause / Resume as retail inlined them into SetOnHold and Reset.
// The inlined GetTimeLeft keeps its own `CMP reg,-1; JZ` right after Pause's
// identical test (0x6CB51F / 0x6CB527).
inline void CDTimerClass::Pause()
{
    if (this->StartTime != -1) {
        this->TimeLeft = this->GetTimeLeft();
        this->StartTime = -1;
    }
}

// Restart the clock if it was stopped.
inline void CDTimerClass::Resume()
{
    if (this->StartTime == -1) {
        this->StartTime = CurrentFrame;
    }
}

// Inline mirror of GAMEMD 0x6CC260 SuperClass::GetRechargeTime (matched in
// match/combat/Super.cpp); retail inlines it into SetCharge.
inline int SuperClass::GetRechargeTime() const
{
    if (this->CustomChargeTime != -1)
        return this->CustomChargeTime;
    return this->Type->RechargeTime;
}

#endif  // GG_MATCH_COMBAT_SUPER_CLASS_CHARGE_METHODS_H

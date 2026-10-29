// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6CB4D0 and 0x6CC1E0.
//   LIBRARY: GAMEMD 0x7C5F00  __ftol  (CRT float->long; the (int) cast; reloc)
//   GLOBAL:  GAMEMD 0x00A8ED84 Unsorted::CurrentFrame

#include "super_class_charge_methods.h"
#include "../_layout/anim_class.h"

// SuperClass::SetOnHold (0x6CB4D0) is unmatched: plain CDTimerClass::Pause scored
// 50.9% because retail keeps the inlined GetTimeLeft's second `CMP ESI,-1` that
// VC6 folds in ordinary code (the previous body forced it with a reinterpret
// alias, removed as steering).

// FUNCTION: GAMEMD 0x6CB830  SuperClass::StopPreclickAnim
//
// Drop the preclick animation (and the pending-animation list entry) and, if
// the weapon is present, not ready and either not suspended or of a type
// that keeps charging, restart the recharge: an inlined Resume followed by a
// fresh CDTimerClass temporary from GetRechargeTime. The bool parameter is
// never read.
bool SuperClass::StopPreclickAnim(bool unused)
{
    if (this->Animation != 0) {
        this->Animation->RemainingIterations = 0;
        this->Animation = 0;
        DAT_00B0F5B8.Remove(this);
    }

    if (this->AnimationGotInvalid) {
        DAT_00B0F5B8.Remove(this);
        this->AnimationGotInvalid = false;
    }

    if (this->IsPresent && !this->IsReady && (!this->IsSuspended || this->Type->unknown_ED)) {
        this->CameoChargeState = -1;
        this->RechargeTimer.Resume();
        this->RechargeTimer = CDTimerClass(this->GetRechargeTime());
        if (this->Type->UseChargeDrain)
            this->ChargeDrainState = 0;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6CC1E0  SuperClass::SetCharge (__thiscall, ret 0x4)
//
// Sets the recharge progress to a percentage (0..100) of the full recharge
// time. The remaining frames are the recharge time less the charged fraction
// ((int)(percentage * 0.01f * rechargeTime), the __ftol call); a remainder of
// zero also marks the weapon ready. The clock is resumed if it was stopped and
// then replaced wholesale by a fresh CDTimerClass(remaining) — a 12-byte copy
// whose middle dword is the temporary's uninitialised CurrentTime slot.
//
// The explicit parentheses are load-bearing: `percentage * 0.01f * rechargeTime`
// unparenthesised makes VC6 emit FILD; FIMUL rechargeTime; FMUL 0.01f (90.0%),
// while `(percentage * 0.01f) * rechargeTime` gives retail's FILD; FMUL 0.01f;
// FIMUL rechargeTime.
void SuperClass::SetCharge(int percentage)
{
    if (this->IsPresent && percentage >= 0 && percentage <= 100) {
        int rechargeTime = this->GetRechargeTime();
        int remaining = rechargeTime - (int)((percentage * 0.01f) * rechargeTime);
        if (remaining == 0) {
            this->IsReady = true;
        }
        this->RechargeTimer.Resume();
        this->RechargeTimer = CDTimerClass(remaining);
    }
}

// SuperClass::Reset (0x6CE0B0) is unmatched for the same reason (72.7% with the
// plain Pause; the previous body forced the second `CMP ESI,-1` with the alias).

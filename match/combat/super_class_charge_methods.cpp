// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6CB4D0 and 0x6CC1E0.
//   LIBRARY: GAMEMD 0x7C5F00  __ftol  (CRT float->long; the (int) cast; reloc)
//   GLOBAL:  GAMEMD 0x00A8ED84 Unsorted::CurrentFrame

#include "super_class_charge_methods.h"
#include "../_layout/anim_class.h"

// FUNCTION: GAMEMD 0x6CB4D0  SuperClass::SetOnHold (__thiscall, ret 0x4)
//
// Suspends or resumes a superweapon's recharge. Refuses (false) when the weapon
// is not present, is a one-shot, is already in the requested state, or cannot
// be held at all. Otherwise a resume of a non-manual weapon restarts the
// recharge clock (Resume: only if it was stopped), while a hold — or any change
// on a ManualControl weapon — freezes the remaining time (Pause). The new
// suspend state is recorded and true reports that something changed.
//
// The four guards are one combined condition (that gives retail's single
// shared `xor al,al` tail). The inlined Pause tail keeps GetTimeLeft's own
// `CMP ESI,-1; JZ` (0x6CB527) two instructions after Pause's identical test
// (0x6CB51F) on the same cached register: that second test survives only
// when GetTimeLeft's guard reads StartTime through a different type
// (the unsigned view in the header), which stops VC6 folding it; every
// same-member spelling (preloaded local, early return, ternary, out-of-class
// inline, IsTicking helper, a static inline helper with a pointer parameter)
// dropped the two instructions and sat at 50.9%. The compare form
// `passed < TimeLeft ? TimeLeft - passed : 0` is retail's
// (SUB EDX,ESI; CMP EDX,EAX; JGE).
bool SuperClass::SetOnHold(bool onHold)
{
    if (this->IsPresent && !this->IsOneTime && onHold != this->IsSuspended && this->CanHold) {
        if (!onHold && !this->Type->ManualControl) {
            this->RechargeTimer.Resume();
        } else {
            this->RechargeTimer.Pause();
        }
        this->IsSuspended = onHold;
        return true;
    }
    return false;
}

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

// FUNCTION: GAMEMD 0x6CE0B0  SuperClass::Reset
//
// Back to a cold start: drop the preclick animation and its pending-list
// entry, clear the ready flag, and restart the recharge timer from
// GetRechargeTime — pausing it again straight away if it was not running
// before, so a held weapon stays held with its full time banked.
//
// The trailing Pause() inlines GetTimeLeft, whose own `CMP ESI,-1` on the
// just-tested StartTime retail keeps (0x6CE16F); the unsigned-view guard in
// the header (see SetOnHold) is what keeps VC6 from folding it here too.
void SuperClass::Reset()
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

    this->IsReady = false;
    bool running = this->RechargeTimer.StartTime != -1;
    this->CameoChargeState = -1;
    this->RechargeTimer = CDTimerClass(this->GetRechargeTime());
    if (!running)
        this->RechargeTimer.Pause();
}

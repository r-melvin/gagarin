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
//   Names cross-checked against YRpp SuperClass.h / SuperWeaponTypeClass.h /
//   Timer.h (consult-only, no LICENSE; every offset reconfirmed above). The
//   member run agrees with match/combat/super_class_methods.h and
//   super_class_more_methods.h (not edited; re-derived here so the TU stands
//   alone, extended with RechargeTimer, CanHold and IsOneTime).
#ifndef GG_MATCH_COMBAT_SUPER_CLASS_CHARGE_METHODS_H
#define GG_MATCH_COMBAT_SUPER_CLASS_CHARGE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x00A8ED84 — Unsorted::CurrentFrame, the global frame counter.
#include "../core/frame_counter.h"

// ---------------------------------------------------------------------------
// CDTimerClass = TimerStruct<FrameTimer> (sizeof 0x0C): a frame count-down.
//   +0x00 StartTime   (-1 == paused / not running)
//   +0x04 CurrentTime (the empty FrameTimer clock's storage; never written by
//                      the ctor, so a copy of a fresh temporary carries the
//                      stack garbage through — retail's MOV EDX,[ESP+0x10])
//   +0x08 TimeLeft
// The inline members below are what retail inlined into the two bodies:
// Resume / Pause (SetOnHold) and the (int) ctor + copy (SetCharge).
// ---------------------------------------------------------------------------
struct CDTimerClass
{
    union {
        int      StartTime;     // +0x00  (-1 == paused)
        unsigned StartTimeU;    // +0x00  same dword; GetTimeLeft's own guard
    };
    int CurrentTime;    // +0x04
    int TimeLeft;       // +0x08

    CDTimerClass(int duration)
    {
        this->StartTime = CurrentFrame;
        this->TimeLeft = duration;
    }

    // Frames still to run: while running, TimeLeft less the frames elapsed
    // since StartTime, floored at zero. The guard reads StartTime through
    // the unsigned union alias: when Pause inlines this right after its own
    // `StartTime != -1` test, retail keeps both compares on the one cached
    // register (`CMP ESI,-1; JZ` twice, 0x6CB51F / 0x6CB527) and VC6 folds
    // the second unless the two tests name different union members; the
    // alias is the same width, so the bytes are identical.
    int GetTimeLeft() const
    {
        int left = this->TimeLeft;
        if (this->StartTimeU != 0xFFFFFFFF) {
            int passed = CurrentFrame - this->StartTime;
            if (passed < left) {
                left = left - passed;
            } else {
                left = 0;
            }
        }
        return left;
    }

    // Freeze the remaining time and stop the clock.
    void Pause()
    {
        if (this->StartTime != -1) {
            this->TimeLeft = this->GetTimeLeft();
            this->StartTime = -1;
        }
    }

    // Restart the clock if it was stopped.
    void Resume()
    {
        if (this->StartTime == -1) {
            this->StartTime = CurrentFrame;
        }
    }
};
GG_STATIC_ASSERT(offsetof(CDTimerClass, StartTime)   == 0x00);
GG_STATIC_ASSERT(offsetof(CDTimerClass, StartTimeU)  == 0x00);
GG_STATIC_ASSERT(offsetof(CDTimerClass, CurrentTime) == 0x04);
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft)    == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimerClass) == 0x0C);

// SuperWeaponTypeClass — only RechargeTime @0xB0 and ManualControl @0xF5 are
// touched here.
struct SuperWeaponTypeClass
{
    char _pad0[0xB0];          // +0x00
    int  RechargeTime;         // +0xB0
    char _padB4[0xE5 - 0xB4];  // +0xB4
    bool At_E5;                // +0xE5
    char _padE6[0xED - 0xE6];  // +0xE6
    bool At_ED;                // +0xED
    char _padEE[0xF5 - 0xEE];  // +0xEE
    bool ManualControl;        // +0xF5
};
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, RechargeTime)  == 0xB0);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, ManualControl) == 0xF5);

// SuperClass : AbstractClass — a per-house superweapon instance.
struct SuperClass;

// The preclick animation; only the byte at +0x195 is cleared.
struct PreclickAnim_006CB830
{
    char _pad0000[0x195];   // +0x0000
    char At_195;            // +0x0195
};
GG_STATIC_ASSERT(offsetof(PreclickAnim_006CB830, At_195) == 0x195);

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

struct SuperClass
{
    char                  _base[0x24];        // +0x00  AbstractClass
    int                   CustomChargeTime;   // +0x24  -1 == "use Type default"
    SuperWeaponTypeClass* Type;               // +0x28
    char                  _pad2C[4];          // +0x2C  Owner (HouseClass*)
    CDTimerClass          RechargeTimer;      // +0x30
    char                  _pad3C[0x60 - 0x3C];// +0x3C
    bool                  CanHold;            // +0x60
    char                  _pad61[0x68 - 0x61];// +0x61
    PreclickAnim_006CB830* Animation;         // +0x68
    bool                  At_6C;              // +0x6C
    bool                  IsPresent;          // +0x6D
    bool                  IsOneTime;          // +0x6E
    bool                  IsReady;            // +0x6F
    bool                  IsSuspended;        // +0x70
    char                  _pad71[0x78 - 0x71];// +0x71
    int                   At_78;              // +0x78
    int                   At_7C;              // +0x7C

    // Inline mirror of GAMEMD 0x6CC260 SuperClass::GetRechargeTime (matched in
    // match/combat/super_class_methods.cpp); retail inlines it into SetCharge.
    int GetRechargeTime() const
    {
        if (this->CustomChargeTime != -1)
            return this->CustomChargeTime;
        return this->Type->RechargeTime;
    }

    // FUNCTION: GAMEMD 0x6CB4D0
    bool SetOnHold(bool onHold);
    // FUNCTION: GAMEMD 0x6CB830
    bool StopPreclickAnim(bool unused);

    // FUNCTION: GAMEMD 0x6CC1E0
    void SetCharge(int percentage);
    // FUNCTION: GAMEMD 0x6CE0B0
    void Reset();
};
GG_STATIC_ASSERT(offsetof(SuperClass, CustomChargeTime) == 0x24);
GG_STATIC_ASSERT(offsetof(SuperClass, Type)             == 0x28);
GG_STATIC_ASSERT(offsetof(SuperClass, RechargeTimer)    == 0x30);
GG_STATIC_ASSERT(offsetof(SuperClass, CanHold)          == 0x60);
GG_STATIC_ASSERT(offsetof(SuperClass, Animation)        == 0x68);
GG_STATIC_ASSERT(offsetof(SuperClass, At_6C)            == 0x6C);
GG_STATIC_ASSERT(offsetof(SuperClass, IsPresent)        == 0x6D);
GG_STATIC_ASSERT(offsetof(SuperClass, At_78)            == 0x78);
GG_STATIC_ASSERT(offsetof(SuperClass, At_7C)            == 0x7C);
GG_STATIC_ASSERT(offsetof(SuperClass, IsOneTime)        == 0x6E);
GG_STATIC_ASSERT(offsetof(SuperClass, IsReady)          == 0x6F);
GG_STATIC_ASSERT(offsetof(SuperClass, IsSuspended)      == 0x70);

#endif  // GG_MATCH_COMBAT_SUPER_CLASS_CHARGE_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x41F0D0 / 0x41F180 (the two bodies are identical
//   apart from the compared type constant, 1 vs 3):
//     HouseClass::Supers.Items        [ECX+0x258]  (MOV ESI,[ECX+0x258])
//     HouseClass::Supers.Count        [ECX+0x264]  (MOV EDX,[ECX+0x264])
//     SuperClass::Type                [EDI+0x28]   (MOV EDI,[EDI+0x28])
//     SuperWeaponTypeClass::Type      [EDI+0xB4]   (CMP dword [EDI+0xB4],1 / 3)
//     SuperClass::RechargeTimer.StartTime [EAX+0x30], .TimeLeft [EAX+0x38]
//     SuperClass::IsPresent           [EAX+0x6D]   (MOV CL,[EAX+0x6D])
//     RulesClass +0xD70 (float)       [EAX+0xD70]  (FSUB dword [EAX+0xD70])
//   Globals: Unsorted::CurrentFrame 0xA8ED84, RulesClass::Instance 0x8871E0,
//   the 1.0f literal at 0x7E2AC8.  Only the first stack argument is read; the
//   `RET 0x8` fixes a second (unused) one.  Names cross-checked against YRpp
//   AITriggerTypeClass.h / SuperClass.h / SuperWeaponTypeClass.h /
//   RulesClass.h (consult-only; every offset reconfirmed above).  The
//   SuperClass / CDTimerClass member run agrees with
//   match/combat/super_class_charge_methods.h (not edited; re-derived here so
//   the TU stands alone).
#ifndef GG_MATCH_AI_AI_TRIGGER_CHARGED_METHODS_H
#define GG_MATCH_AI_AI_TRIGGER_CHARGED_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"

// CDTimerClass (0x0C): a frame count-down.  GetTimeLeft is what retail
// inlined into both bodies.  The arm order matters: the subtract arm falls
// through into the one `MOV [ESP+0x10],ECX` spill that the paused path also
// jumps to (`CMP ESI,-1; JZ`), and the expired arm returns its zero through
// an out-of-line `MOV dword [ESP+0x10],0; JMP` at 0x41F171 / 0x41F221.  The
// `left = 0` assignment form emits three separate stores instead.
struct CDTimerClass
{
    int StartTime;      // +0x00  (-1 == paused)
    int CurrentTime;    // +0x04
    int TimeLeft;       // +0x08

    int GetTimeLeft() const
    {
        int left = this->TimeLeft;
        if (this->StartTime != -1) {
            int passed = CurrentFrame - this->StartTime;
            if (passed < left) {
                left = left - passed;
            } else {
                return 0;
            }
        }
        return left;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimerClass, StartTime) == 0x00);
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft)  == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimerClass) == 0x0C);

// SuperWeaponTypeClass — only the Type enum @0xB4 is compared here
// (1 == IronCurtain, 3 == ChronoSphere).
struct SuperWeaponTypeClass
{
    char _pad000[0xB4];      // +0x0000
    int  Type;               // +0x00B4
};
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, Type) == 0xB4);

// SuperClass : AbstractClass — a per-house superweapon instance.
struct SuperClass
{
    char                  _base[0x28];         // +0x0000  AbstractClass + CustomChargeTime
    SuperWeaponTypeClass* Type;                // +0x0028
    char                  _pad02C[4];          // +0x002C
    CDTimerClass          RechargeTimer;       // +0x0030
    char                  _pad03C[0x6D - 0x3C];// +0x003C
    bool                  IsPresent;           // +0x006D

    // FUNCTION: GAMEMD 0x6CC260 (decl; reloc)
    int GetRechargeTime() const;
};
GG_STATIC_ASSERT(offsetof(SuperClass, Type)          == 0x28);
GG_STATIC_ASSERT(offsetof(SuperClass, RechargeTimer) == 0x30);
GG_STATIC_ASSERT(offsetof(SuperClass, IsPresent)     == 0x6D);

// HouseClass — only the Supers vector is touched (Items @0x258, Count @0x264).
struct HouseClass
{
    char         _pad000[0x258];   // +0x0000
    SuperClass** SupersItems;      // +0x0258
    char         _pad25C[0x8];     // +0x025C
    int          SupersCount;      // +0x0264
};
GG_STATIC_ASSERT(offsetof(HouseClass, SupersItems) == 0x258);
GG_STATIC_ASSERT(offsetof(HouseClass, SupersCount) == 0x264);

// RulesClass — only the float threshold @0xD70 (AIMinorSuperReadyPercent).
struct RulesClass
{
    char  _pad000[0xD70];          // +0x0000
    float AIMinorSuperReadyPercent;// +0x0D70
};
GG_STATIC_ASSERT(offsetof(RulesClass, AIMinorSuperReadyPercent) == 0xD70);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern RulesClass* Rules;

struct AITriggerTypeClass
{
    // FUNCTION: GAMEMD 0x41F0D0
    bool IronCurtainCharged(HouseClass* callingHouse, HouseClass* targetHouse) const;

    // FUNCTION: GAMEMD 0x41F180
    bool ChronoSphereCharged(HouseClass* callingHouse, HouseClass* targetHouse) const;
};

#endif  // GG_MATCH_AI_AI_TRIGGER_CHARGED_METHODS_H

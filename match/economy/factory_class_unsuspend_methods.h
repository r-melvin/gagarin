// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4C9EA0: `[ESI+0x58]` (Object), `[ESI+0x68]`
//   (SpecialItem, compared with -1), `[ESI+0x70]` / `[ESI+0x71]` (IsSuspended /
//   IsManual bytes), `[ESI+0x24]` (Production.Value, compared with 0x36),
//   `[ESI+0x38]` (Production.Rate) and the three-dword timer copy at
//   `LEA ECX,[ESI+0x2C]` stamped from `[0xA8ED84]` (CurrentFrame),
//   `[ESI+0x60]` (Balance), `[ESI+0x6C]` (Owner) whose IHouse sub-object at
//   +0x24 is dispatched `PUSH EAX; MOV ECX,[EAX]; CALL [ECX+0x18]`
//   (__stdcall slot 6 = Available_Money). CALL 0x6F47A0 is TechnoClass::
//   TimeToBuild on the Object.  Names cross-checked against YRpp
//   FactoryClass.h / Interfaces.h (consult-only) and used as names only.
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_UNSUSPEND_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_UNSUSPEND_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
extern int CurrentFrame_004C9EA0;

// TechnoClass — only TimeToBuild() is reached.
struct Techno_004C9EA0
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x6F47A0 (decl; reloc) — TechnoClass::TimeToBuild.
    int TimeToBuild() const;
};

// IHouse COM interface: __stdcall virtuals, receiver on the stack.
struct IHouse_004C9EA0;
typedef long (__stdcall* IHouseSlot0_004C9EA0)(IHouse_004C9EA0*);
struct IHouseVtbl_004C9EA0
{
    char _pad000[0x18];                   // +0x0000  IUnknown x3, ID_Number, Name, Get_Application
    IHouseSlot0_004C9EA0 Available_Money; // +0x0018
};
GG_STATIC_ASSERT(offsetof(IHouseVtbl_004C9EA0, Available_Money) == 0x18);
struct IHouse_004C9EA0
{
    IHouseVtbl_004C9EA0* Vtbl;            // +0x0000
};

// HouseClass — only the IHouse sub-object at +0x24 is touched.
struct House_004C9EA0
{
    char _pad000[0x24];                   // +0x0000  AbstractClass
    IHouse_004C9EA0 IHouse;               // +0x0024
};
GG_STATIC_ASSERT(offsetof(House_004C9EA0, IHouse) == 0x24);

// FrameTimer — empty clock policy whose value is CurrentFrame; occupies the
// never-written middle dword of the timer.
struct FrameTimer_004C9EA0
{
    operator int() const { return CurrentFrame_004C9EA0; }
};

// CDTimerClass<FrameTimer> (0xC bytes): StartTime, CurrentTime (uninitialised
// by the ctor and copied through as the `[ESP+0xC]` garbage load), TimeLeft.
struct CDTimer_004C9EA0
{
    int                 StartTime;        // +0x0000
    FrameTimer_004C9EA0 CurrentTime;      // +0x0004
    int                 TimeLeft;         // +0x0008

    CDTimer_004C9EA0(int duration)
    {
        this->StartTime = this->CurrentTime;
        this->TimeLeft = duration;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_004C9EA0, TimeLeft) == 0x8);
GG_STATIC_ASSERT(sizeof(CDTimer_004C9EA0) == 0xC);

// StageClass (0x1C bytes): Value, HasChanged, Timer, Rate, Step.
struct Stage_004C9EA0
{
    int              Value;               // +0x0000
    bool             HasChanged;          // +0x0004
    CDTimer_004C9EA0 Timer;               // +0x0008
    int              Rate;                // +0x0014
    int              Step;                // +0x0018

    void Start(int rate)
    {
        this->Timer = CDTimer_004C9EA0(rate);
        this->Rate = rate;
    }
};
GG_STATIC_ASSERT(offsetof(Stage_004C9EA0, Timer) == 0x08);
GG_STATIC_ASSERT(offsetof(Stage_004C9EA0, Rate) == 0x14);
GG_STATIC_ASSERT(sizeof(Stage_004C9EA0) == 0x1C);

// FactoryClass : AbstractClass (0x24), 0x74 bytes.
struct Factory_004C9EA0
{
    char             _pad000[0x24];       // +0x0000  AbstractClass
    Stage_004C9EA0   Production;          // +0x0024
    char             _pad040[0x18];       // +0x0040  DynamicVectorClass QueuedObjects
    Techno_004C9EA0* Object;              // +0x0058
    char             _pad05C[4];          // +0x005C  OnHold / IsDifferent
    int              Balance;             // +0x0060
    int              OriginalBalance;     // +0x0064
    int              SpecialItem;         // +0x0068
    House_004C9EA0*  Owner;               // +0x006C
    bool             IsSuspended;         // +0x0070
    bool             IsManual;            // +0x0071
    char             _pad072[2];          // +0x0072

    // Inlined helpers (bodies in the .cpp ahead of their caller).
    int  GetBuildTimeFrames() const;      // 0x4C9FB0 out-of-line twin
    int  CostPerTick() const;
    bool Suspend(bool manual);            // 0x4C9E60 out-of-line twin

    // FUNCTION: GAMEMD 0x4C9EA0 — FactoryClass::Unsuspend.
    bool Unsuspend(bool manual);
};
GG_STATIC_ASSERT(offsetof(Factory_004C9EA0, Production) == 0x24);
GG_STATIC_ASSERT(offsetof(Factory_004C9EA0, Production.Timer) == 0x2C);
GG_STATIC_ASSERT(offsetof(Factory_004C9EA0, Production.Rate) == 0x38);
GG_STATIC_ASSERT(offsetof(Factory_004C9EA0, Object) == 0x58);
GG_STATIC_ASSERT(offsetof(Factory_004C9EA0, Balance) == 0x60);
GG_STATIC_ASSERT(offsetof(Factory_004C9EA0, SpecialItem) == 0x68);
GG_STATIC_ASSERT(offsetof(Factory_004C9EA0, Owner) == 0x6C);
GG_STATIC_ASSERT(offsetof(Factory_004C9EA0, IsSuspended) == 0x70);
GG_STATIC_ASSERT(offsetof(Factory_004C9EA0, IsManual) == 0x71);
GG_STATIC_ASSERT(sizeof(Factory_004C9EA0) == 0x74);

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_UNSUSPEND_METHODS_H

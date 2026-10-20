// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4C9FF0: `[ESI+0x58]` (Object, null-tested and
//   dispatched through `[EAX+0x88]` = GetTechnoType, `[EDX+0x2C]` = WhatAmI
//   and `PUSH 1; CALL [EDX+0x20]` = the deleting destructor), the type's
//   name `ADD EAX,0x64` pushed with the log string 0x8222AC into the
//   __cdecl 0x4068E0 (`ADD ESP,8`), the type's `[EDX+0x84]` taking the
//   Object's owner `[ECX+0x21C]`, `[ESI+0x60]` (Balance) subtracted from it
//   and refunded through 0x4F9950 on `[ESI+0x6C]` (Owner), `[ESI+0x68]`
//   (SpecialItem, set to -1 only when non-zero), `[ESI+0x38]` (Rate), the
//   three-dword timer at `LEA EDX,[ESI+0x2C]` stamped from `[0xA8ED84]`,
//   `[ESI+0x24]` (Production.Value), the bytes `[ESI+0x70]` / `[ESI+0x5D]`,
//   0x50B730 (IsControlledByHuman) on Owner, the owner's `[EAX+0x5654]`,
//   `[EAX+0x5650]`, `[EAX+0x5658]`, `[EAX+0x564C]` (-1 per WhatAmI 0xF / 1 /
//   2 / 6) and the global counter `[0xA8E7AC]` bumped around the delete.
//   Names cross-checked against YRpp FactoryClass.h / HouseClass.h
//   (consult-only) and used as names only.
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_ABANDON_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_ABANDON_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
extern int CurrentFrame_004C9FF0;
// GLOBAL: GAMEMD 0xA8E7AC — Unsorted::ScenarioInit.
extern int DAT_00A8E7AC;

// STRING: GAMEMD 0x8222AC — "Abandoning production of %s\n".
extern const char DAT_008222AC[];
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// HouseClass — the members touched here.
struct House_004C9FF0
{
    char _pad0000[0x564C];               // +0x0000
    int  At_564C;                        // +0x564C  cleared to -1 for WhatAmI 6
    int  At_5650;                        // +0x5650  cleared to -1 for WhatAmI 1
    int  At_5654;                        // +0x5654  cleared to -1 for WhatAmI 0xF
    int  At_5658;                        // +0x5658  cleared to -1 for WhatAmI 2

    // FUNCTION: GAMEMD 0x4F9950 (decl; reloc) — HouseClass::GiveMoney.
    void GiveMoney(int amount);
    // FUNCTION: GAMEMD 0x50B730 (decl; reloc) — HouseClass::IsControlledByHuman.
    bool IsControlledByHuman() const;
};
GG_STATIC_ASSERT(offsetof(House_004C9FF0, At_564C) == 0x564C);
GG_STATIC_ASSERT(offsetof(House_004C9FF0, At_5650) == 0x5650);
GG_STATIC_ASSERT(offsetof(House_004C9FF0, At_5654) == 0x5654);
GG_STATIC_ASSERT(offsetof(House_004C9FF0, At_5658) == 0x5658);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct TypeVtbl_004C9FF0;

// TechnoTypeClass — Name at +0x64 and the cost slot at +0x84.
struct TechnoType_004C9FF0
{
    TypeVtbl_004C9FF0* Vtbl;             // +0x0000
    char _pad0004[0x64 - 0x04];          // +0x0004
    char Name[0x31];                     // +0x0064
};
GG_STATIC_ASSERT(offsetof(TechnoType_004C9FF0, Name) == 0x64);

typedef int (TechnoType_004C9FF0::*Fn84_004C9FF0)(House_004C9FF0* house);

struct TypeVtbl_004C9FF0
{
    char           _pad000[0x84];        // +0x0000
    Fn84_004C9FF0  GetCost;              // +0x0084  cost for a house
};
GG_STATIC_ASSERT(offsetof(TypeVtbl_004C9FF0, GetCost) == 0x84);

// TechnoClass — three vtable slots and the Owner. The eight leading virtuals
// place the deleting destructor at +0x20 so `delete p` issues
// `PUSH 1; CALL [EDX+0x20]`; the class is never instantiated here.
struct Techno_004C9FF0
{
    virtual long vf_00();                // +0x00
    virtual long vf_04();                // +0x04
    virtual long vf_08();                // +0x08
    virtual long vf_0c();                // +0x0C
    virtual long vf_10();                // +0x10
    virtual long vf_14();                // +0x14
    virtual long vf_18();                // +0x18
    virtual long vf_1c();                // +0x1C
    virtual ~Techno_004C9FF0();          // +0x20  deleting destructor
    virtual long vf_24();                // +0x24
    virtual long vf_28();                // +0x28
    virtual int  WhatAmI();              // +0x2C
    virtual long vf_30();                // +0x30
    virtual long vf_34();                // +0x34
    virtual long vf_38();                // +0x38
    virtual long vf_3c();                // +0x3C
    virtual long vf_40();                // +0x40
    virtual long vf_44();                // +0x44
    virtual long vf_48();                // +0x48
    virtual long vf_4c();                // +0x4C
    virtual long vf_50();                // +0x50
    virtual long vf_54();                // +0x54
    virtual long vf_58();                // +0x58
    virtual long vf_5c();                // +0x5C
    virtual long vf_60();                // +0x60
    virtual long vf_64();                // +0x64
    virtual long vf_68();                // +0x68
    virtual long vf_6c();                // +0x6C
    virtual long vf_70();                // +0x70
    virtual long vf_74();                // +0x74
    virtual long vf_78();                // +0x78
    virtual long vf_7c();                // +0x7C
    virtual long vf_80();                // +0x80
    virtual long vf_84();                // +0x84
    virtual TechnoType_004C9FF0* GetTechnoType();   // +0x88

    char              _pad0004[0x21C - 0x04];        // +0x0004
    House_004C9FF0*   Owner;                         // +0x021C
};
GG_STATIC_ASSERT(offsetof(Techno_004C9FF0, Owner) == 0x21C);

// FrameTimer — empty clock policy whose value is CurrentFrame; occupies the
// never-written middle dword of the timer.
struct FrameTimer_004C9FF0
{
    operator int() const { return CurrentFrame_004C9FF0; }
};

// CDTimerClass<FrameTimer> (0xC bytes).
struct CDTimer_004C9FF0
{
    int                 StartTime;       // +0x0000
    FrameTimer_004C9FF0 CurrentTime;     // +0x0004
    int                 TimeLeft;        // +0x0008

    CDTimer_004C9FF0(int duration)
    {
        this->StartTime = this->CurrentTime;
        this->TimeLeft = duration;
    }
};
GG_STATIC_ASSERT(sizeof(CDTimer_004C9FF0) == 0xC);

// StageClass (0x1C bytes): Value, HasChanged, Timer, Rate, Step.
struct Stage_004C9FF0
{
    int              Value;              // +0x0000
    bool             HasChanged;         // +0x0004
    CDTimer_004C9FF0 Timer;              // +0x0008
    int              Rate;               // +0x0014
    int              Step;               // +0x0018

    void Start(int rate)
    {
        this->Timer = CDTimer_004C9FF0(rate);
        this->Rate = rate;
    }
};
GG_STATIC_ASSERT(offsetof(Stage_004C9FF0, Timer) == 0x08);
GG_STATIC_ASSERT(offsetof(Stage_004C9FF0, Rate) == 0x14);
GG_STATIC_ASSERT(sizeof(Stage_004C9FF0) == 0x1C);

// FactoryClass : AbstractClass (0x24), 0x74 bytes.
struct Factory_004C9FF0
{
    char              _pad000[0x24];     // +0x0000  AbstractClass
    Stage_004C9FF0    Production;        // +0x0024
    char              _pad040[0x18];     // +0x0040  DynamicVectorClass QueuedObjects
    Techno_004C9FF0*  Object;            // +0x0058
    bool              IsOnHold;          // +0x005C
    bool              IsDifferent;       // +0x005D
    char              _pad05E[2];        // +0x005E
    int               Balance;           // +0x0060
    int               OriginalBalance;   // +0x0064
    int               SpecialItem;       // +0x0068
    House_004C9FF0*   Owner;             // +0x006C
    bool              IsSuspended;       // +0x0070
    bool              IsManual;          // +0x0071
    char              _pad072[2];        // +0x0072

    // FUNCTION: GAMEMD 0x4C9FF0 — FactoryClass::AbandonProduction.
    bool AbandonProduction();
};
GG_STATIC_ASSERT(offsetof(Factory_004C9FF0, Production) == 0x24);
GG_STATIC_ASSERT(offsetof(Factory_004C9FF0, Production.Timer) == 0x2C);
GG_STATIC_ASSERT(offsetof(Factory_004C9FF0, Production.Rate) == 0x38);
GG_STATIC_ASSERT(offsetof(Factory_004C9FF0, Object) == 0x58);
GG_STATIC_ASSERT(offsetof(Factory_004C9FF0, IsDifferent) == 0x5D);
GG_STATIC_ASSERT(offsetof(Factory_004C9FF0, Balance) == 0x60);
GG_STATIC_ASSERT(offsetof(Factory_004C9FF0, SpecialItem) == 0x68);
GG_STATIC_ASSERT(offsetof(Factory_004C9FF0, Owner) == 0x6C);
GG_STATIC_ASSERT(offsetof(Factory_004C9FF0, IsSuspended) == 0x70);
GG_STATIC_ASSERT(sizeof(Factory_004C9FF0) == 0x74);

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_ABANDON_METHODS_H

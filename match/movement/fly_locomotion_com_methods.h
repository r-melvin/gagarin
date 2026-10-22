// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   The class was identified from its own runtime type information: the
//   primary vtable of this cluster starts at 0x7E89F4, its complete object
//   locator sits one dword below at 0x7E89F0 -> 0x800658, whose type
//   descriptor at +0xC is 0x8223E8, and the name eight bytes into that reads
//   ".?AVFlyLocomotionClass@@". The locator's base offset of 4 is what pins
//   the locomotor interface's vptr to +0x04 and the persist vptr to +0x00,
//   which the loader at 0x4CFCC0 re-seats with exactly those two constants
//   (0x7E8AC0 at +0, 0x7E89F4 at +4). YRpp names FlyLocomotionClass and the
//   ILocomotion slot order - name-only cross-check.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001:
//   +0x00 the persist vptr, +0x04 the locomotor vptr, +0x0C LinkedTo (read
//   through the interface as `MOV 0x8(%EAX),%ECX` in 0x4CFCF0 and 0x4CFDA0,
//   and through the object as `MOV 0xC(%ESI),%ECX` in 0x4CFC40), +0x38 the
//   halved distance in 0x4CFC40, +0x50 and +0x51 its two flag bytes, +0x53
//   the spin flag and +0x54 the spin value the touchdown path at 0x4CFD20
//   writes (as `0x4F(%ESI)` and `0x50(%ESI)` off the interface pointer, four
//   lower), and +0x58 the counter it clears.
//   LinkedTo's vtable slots: +0x84 returns the owner object whose byte at
//   +0xD27 gates 0x4CFDA0, and +0x1C8 returns the signed count both 0x4CFC40
//   and 0x4CFCF0 test.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_COM_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_COM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

typedef long HRESULT;

// The object LinkedTo's slot 0x84 hands back; only the gate byte is read.
struct Owner_004CFDA0
{
    char _pad000[0xD27];   // +0x0000
    char At_D27;           // +0x0D27
};
GG_STATIC_ASSERT(offsetof(Owner_004CFDA0, At_D27) == 0xD27);

// The locomotor's client object. Declaration order matters - see gg_vslot.h.
struct FootVtbl_004CFC40;

struct Foot_004CFC40
{
    FootVtbl_004CFC40* Vtbl;   // +0x0000
};

typedef Owner_004CFDA0* (Foot_004CFC40::*FnOwner_004CFC40)();
typedef int (Foot_004CFC40::*FnCount_004CFC40)();

struct FootVtbl_004CFC40
{
    char _pad000[0x84];             // +0x0000
    FnOwner_004CFC40 At_84;         // +0x0084
    char _pad088[0x1C8 - 0x88];     // +0x0088
    FnCount_004CFC40 At_1C8;        // +0x01C8
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CFC40, At_84) == 0x84 &&
                 offsetof(FootVtbl_004CFC40, At_1C8) == 0x1C8);

// The scenario's random generator; the touchdown spin is drawn from it.
struct RandomClass_004CFD20
{
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) — Randomizer::RandomRanged.
    int RandomRanged(int minval, int maxval);
};

struct ScenarioClass_004CFD20
{
    char _pad000[0x218];                 // +0x0000
    RandomClass_004CFD20 RandomNumber;   // +0x0218
};
GG_STATIC_ASSERT(offsetof(ScenarioClass_004CFD20, RandomNumber) == 0x218);

// GLOBAL: GAMEMD 0xA8B230 — the scenario object.
extern ScenarioClass_004CFD20* Scenario_00A8B230;

// A 16-byte class id, copied out whole by GetClassID.
struct Guid_004CFC80 { char Bytes[16]; };
GG_STATIC_ASSERT(sizeof(Guid_004CFC80) == 16);

// GLOBAL: GAMEMD 0x7E9A80 — CLSID_FlyLocomotionClass.
extern const Guid_004CFC80 CLSID_FlyLocomotion_007E9A80;

// FlyLocomotionClass seen through its own `this` (the __thiscall members).
struct FlyLocomotionClass
{
    void* PersistVptr;          // +0x0000
    void* LocomotorVptr;        // +0x0004
    char  _pad008[0x4];         // +0x0008
    Foot_004CFC40* LinkedTo;    // +0x000C
    char  _pad010[0x28];        // +0x0010
    int   FlightLevel;         // +0x0038
    char  _pad03C[0x14];        // +0x003C
    char  IsTakingOff;          // +0x0050
    char  IsLanding;            // +0x0051
    char  _pad052[0x1];         // +0x0052
    char  IsSpinning;           // +0x0053
    int   unknown_54;             // +0x0054
    int   SpinCount;            // +0x0058

    // FUNCTION: GAMEMD 0x4CFC40
    char IsMovingNow() const;
};
GG_STATIC_ASSERT(offsetof(FlyLocomotionClass, LocomotorVptr) == 0x04 &&
                 offsetof(FlyLocomotionClass, LinkedTo) == 0x0C &&
                 offsetof(FlyLocomotionClass, FlightLevel) == 0x38 &&
                 offsetof(FlyLocomotionClass, IsTakingOff) == 0x50 &&
                 offsetof(FlyLocomotionClass, IsLanding) == 0x51 &&
                 offsetof(FlyLocomotionClass, IsSpinning) == 0x53 &&
                 offsetof(FlyLocomotionClass, unknown_54) == 0x54 &&
                 offsetof(FlyLocomotionClass, SpinCount) == 0x58);

// The same object seen through its locomotor interface at +0x04. COM methods
// are __stdcall, so the interface pointer arrives as the first stacked
// argument and every displacement here is four lower than the object's.
// Only the two dispatched slots carry real names; the rest hold slot order.
struct ILocomotion_004CFD20
{
    virtual HRESULT       __stdcall QueryInterface(const void* riid,
                                                   void** ppv) = 0;   // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                      // +0x04
    virtual unsigned long __stdcall Release() = 0;                     // +0x08
    virtual void          __stdcall Slot0C() = 0;                      // +0x0C
    // +0x10 — true while the object is still airborne over its destination.
    virtual char          __stdcall IsToHaveShadow() = 0;              // +0x10
    virtual void          __stdcall Slot14() = 0;                      // +0x14
    virtual void          __stdcall Slot18() = 0;                      // +0x18
    virtual void          __stdcall Slot1C() = 0;                      // +0x1C
    virtual void          __stdcall Slot20() = 0;                      // +0x20
    virtual void          __stdcall Slot24() = 0;                      // +0x24
    virtual void          __stdcall Slot28() = 0;                      // +0x28
    virtual void          __stdcall Slot2C() = 0;                      // +0x2C
    virtual void          __stdcall Slot30() = 0;                      // +0x30
    virtual void          __stdcall Slot34() = 0;                      // +0x34
    virtual void          __stdcall Slot38() = 0;                      // +0x38
    virtual void          __stdcall Slot3C() = 0;                      // +0x3C
    virtual void          __stdcall Slot40() = 0;                      // +0x40
    virtual void          __stdcall Slot44() = 0;                      // +0x44
    // +0x48 — re-mark the object's occupation bits after the spin starts.
    virtual void          __stdcall MarkAllOccupationBits() = 0;       // +0x48

    char  _pad004[0x4];         // +0x0004  (object +0x08)
    Foot_004CFC40* LinkedTo;    // +0x0008  (object +0x0C)
    char  _pad00C[0x43];        // +0x000C
    char  IsSpinning;           // +0x004F  (object +0x53)
    int   unknown_50;             // +0x0050  (object +0x54)
    int   SpinCount;            // +0x0054  (object +0x58)
};
GG_STATIC_ASSERT(offsetof(ILocomotion_004CFD20, LinkedTo) == 0x08 &&
                 offsetof(ILocomotion_004CFD20, IsSpinning) == 0x4F &&
                 offsetof(ILocomotion_004CFD20, unknown_50) == 0x50 &&
                 offsetof(ILocomotion_004CFD20, SpinCount) == 0x54);

// FUNCTION: GAMEMD 0x55A910 (decl; reloc) — the shared locomotor process tail.
void __stdcall LocomotionClassProcess_0055A910(ILocomotion_004CFD20* self);
// FUNCTION: GAMEMD 0x55A930 (decl; reloc) — LocomotionClass::IsPowered.
bool __stdcall LocomotionClassIsPowered_0055A930(ILocomotion_004CFD20* self);

// FUNCTION: GAMEMD 0x4CFC80
HRESULT __stdcall FlyLocomotionGetClassID_004CFC80(ILocomotion_004CFD20* self,
                                                   Guid_004CFC80* classID);
// FUNCTION: GAMEMD 0x4CFCC0
HRESULT __stdcall FlyLocomotionLoad_004CFCC0(FlyLocomotionClass* self,
                                             void* stream);
// FUNCTION: GAMEMD 0x4CFCF0
int __stdcall FlyLocomotionZAdjustment_004CFCF0(ILocomotion_004CFD20* self);
// FUNCTION: GAMEMD 0x4CFD20
void __stdcall FlyLocomotionProcess_004CFD20(ILocomotion_004CFD20* self);
// FUNCTION: GAMEMD 0x4CFD90
bool __stdcall FlyLocomotionIsPowered_004CFD90(ILocomotion_004CFD20* self);
// FUNCTION: GAMEMD 0x4CFDA0
char __stdcall FlyLocomotionIsSurfacing_004CFDA0(ILocomotion_004CFD20* self);

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_COM_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every offset and slot below is read from the user's retail gamemd.exe
//   v1.001 with the local Ghidra CLI.
//
//   Slot identification method (binary, not document): `ghidra x-ref to 0xADDR`
//   returns the DATA references, which are the vtable words that hold the
//   function. Subtracting the AircraftClass vtable base 0x7E22A4 — proven by
//   RTTI: 0x7E22A0 -> COL 0x007FB4C0, +0xC -> type descriptor 0x00817B90,
//   name string ".?AVAircraftClass@@" — gives the slot directly:
//     0x006F7780 @ 0x7E2650 -> +0x3AC
//     0x007010D0 @ 0x7E2340 -> +0x09C
//     0x00701120 @ 0x7E2550 -> +0x2AC
//     0x0070EFD0 @ 0x7E2620 -> +0x37C
//     0x0070F090 @ 0x7E2764 -> +0x4C0
//     0x0070F850 @ 0x7E2674 -> +0x3D0
//   0x0070C5A0 is not in the AircraftClass table; its DATA ref 0x7E4144 belongs
//   to the next table down (base 0x7E3EBC, fixed by the 0x1C18 delta that
//   0x0070F850's two refs give), so its slot is +0x288.
//
//   Member offsets confirmed numerically from the bodies here, and all agree
//   with the committed spine match/_layout/techno_class.h:
//     +0x1C8  Deactivated        `MOV AL,[ESI+0x1c8]`
//     +0x218  ArchiveTarget      `MOV dword ptr [ESI+0x218],0`
//     +0x21C  Owner              `MOV ECX,[ESI+0x21c]` then CALL 0x50B6F0
//     +0x3D2  Cloakable          `MOV AL,[ECX+0x3d2]`
//     +0x504  EMPLockRemaining   `MOV EDX,[ECX+0x504]`
//
//   CORRECTION to our own spine: match/_layout/techno_class.h declares
//   EMPLockRemaining `unsigned int`. 0x0070EFD0 tests it with `SETG`, which is
//   the SIGNED greater-than; an unsigned compare would be `SETA`. The member is
//   a signed int. Modelled as int here.
//
//   CORRECTION to docs/decomp_spec/vtable_map_techno.md line 114: slot +0x2AC
//   is listed as `isArmed() -> bool`. The body at 0x00701120 returns with
//   `MOV EAX,0x1` / `XOR EAX,EAX`, which is int width; a bool return would be
//   `MOV AL,0x1` / `XOR AL,AL`, as the neighbouring 0x007010D0 in fact is.
//   Declared bool, the body does not match; declared int, it does.
#ifndef GG_MATCH_CORE_TECHNO_CLASS_PREDICATE_SLOTS_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_PREDICATE_SLOTS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class AbstractClass;
class TechnoClass;
struct TechnoPredVtbl;
struct TechnoTypePredVtbl;

// WeaponStruct — the (WeaponType*, turret index, FLH) record a weapon slot
// hands back. Only the type pointer at +0x00 is tested here.
struct WeaponStruct
{
    void* WeaponType;    // +0x00
};

// HouseClass — only the "is this the local player's house" predicate is
// reached, as a direct call with the house pointer in ECX.
class HouseClass
{
public:
    // FUNCTION: GAMEMD 0x50B6F0 (decl; reloc) — IsControlledByCurrentPlayer
    bool IsControlledByCurrentPlayer();
};

// TechnoTypeClass — reached only to tail-jump into its own slot +0xA4.
class TechnoTypeClass
{
public:
    TechnoTypePredVtbl* Vfptr;    // +0x000
};

class TechnoClass
{
public:
    // Declared ascending by retail address (reccmp/isle TU discipline).
    bool IsCloseEnoughToAttack(AbstractClass* target);   // GAMEMD 0x6F7780 +0x3AC
    bool IsGuardingWithLiveWeapon();                     // GAMEMD 0x7010D0 +0x09C
    int  IsArmed();                                      // GAMEMD 0x701120 +0x2AC
    bool IsCloakable();                                  // GAMEMD 0x70C5A0 +0x288
    bool IsUnderEMP();                                   // GAMEMD 0x70EFD0 +0x37C
    bool CanAttackOnTheMove();                           // GAMEMD 0x70F090 +0x4C0
    void CancelAndGoIdle();                              // GAMEMD 0x70F850 +0x3D0

    TechnoPredVtbl* Vfptr;                     // +0x000
    char            _pad_004[0x1C8 - 0x004];
    unsigned char   Deactivated;               // +0x1C8
    char            _pad_1C9[0x218 - 0x1C9];
    AbstractClass*  ArchiveTarget;             // +0x218
    HouseClass*     Owner;                     // +0x21C
    char            _pad_220[0x3D2 - 0x220];
    unsigned char   Cloakable;                 // +0x3D2
    char            _pad_3D3[0x504 - 0x3D3];
    int             EMPLockRemaining;          // +0x504
};
GG_STATIC_ASSERT(offsetof(TechnoClass, Vfptr)            == 0x000);
GG_STATIC_ASSERT(offsetof(TechnoClass, Deactivated)      == 0x1C8);
GG_STATIC_ASSERT(offsetof(TechnoClass, ArchiveTarget)    == 0x218);
GG_STATIC_ASSERT(offsetof(TechnoClass, Owner)            == 0x21C);
GG_STATIC_ASSERT(offsetof(TechnoClass, Cloakable)        == 0x3D2);
GG_STATIC_ASSERT(offsetof(TechnoClass, EMPLockRemaining) == 0x504);

// The classes have to be complete before these typedefs, or VC6 falls back to
// the multiple-inheritance member-pointer form and emits a `this` adjustment.
typedef TechnoTypeClass* (TechnoClass::*GetTechnoTypeFn)();
typedef void             (TechnoClass::*SetMissionDirectFn)(int);
typedef int              (TechnoClass::*SelectWeaponFn)(AbstractClass*);
typedef bool             (TechnoClass::*PredicateFn)();
typedef bool             (TechnoClass::*IsCloseEnoughFn)(AbstractClass*, int);
typedef void             (TechnoClass::*SetTargetFn)(AbstractClass*);
typedef WeaponStruct*    (TechnoClass::*GetTurretWeaponFn)();
typedef void             (TechnoClass::*SetDestinationFn)(AbstractClass*, bool);
typedef bool             (TechnoTypeClass::*TypePredicateFn)();

struct TechnoPredVtbl
{
    char               _pad_000[0x084];
    GetTechnoTypeFn    At_84;                      // +0x084
    char               _pad_088[0x1F0 - 0x088];
    SetMissionDirectFn At_1F0;                     // +0x1F0
    char               _pad_1F4[0x2E4 - 0x1F4];
    SelectWeaponFn     At_2E4;                     // +0x2E4
    char               _pad_2E8[0x37C - 0x2E8];
    PredicateFn        At_37C;                     // +0x37C
    char               _pad_380[0x3A8 - 0x380];
    IsCloseEnoughFn    At_3A8;                     // +0x3A8
    char               _pad_3AC[0x3C8 - 0x3AC];
    SetTargetFn        At_3C8;                     // +0x3C8
    char               _pad_3CC[0x3F4 - 0x3CC];
    GetTurretWeaponFn  At_3F4;                     // +0x3F4
    char               _pad_3F8[0x480 - 0x3F8];
    SetDestinationFn   At_480;                     // +0x480
};
GG_STATIC_ASSERT(offsetof(TechnoPredVtbl, At_84)  == 0x084);
GG_STATIC_ASSERT(offsetof(TechnoPredVtbl, At_1F0) == 0x1F0);
GG_STATIC_ASSERT(offsetof(TechnoPredVtbl, At_2E4) == 0x2E4);
GG_STATIC_ASSERT(offsetof(TechnoPredVtbl, At_37C) == 0x37C);
GG_STATIC_ASSERT(offsetof(TechnoPredVtbl, At_3A8) == 0x3A8);
GG_STATIC_ASSERT(offsetof(TechnoPredVtbl, At_3C8) == 0x3C8);
GG_STATIC_ASSERT(offsetof(TechnoPredVtbl, At_3F4) == 0x3F4);
GG_STATIC_ASSERT(offsetof(TechnoPredVtbl, At_480) == 0x480);

struct TechnoTypePredVtbl
{
    char            _pad_000[0x0A4];
    TypePredicateFn At_A4;                         // +0x0A4
};
GG_STATIC_ASSERT(offsetof(TechnoTypePredVtbl, At_A4) == 0x0A4);

#endif // GG_MATCH_CORE_TECHNO_CLASS_PREDICATE_SLOTS_METHODS_H

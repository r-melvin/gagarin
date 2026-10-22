// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x70E1A0-0x70E1D7 and
//   0x710550-0x710583), cross-checked against YRpp
//   (consult-only, no LICENSE; reconfirmed numerically here).
//   Touched members agree with the committed spine match/_layout/techno_class.h
//   (Passengers @0x114, CurrentWeaponNumber @0x138).
//
//   Helper callees (declared, not matched here, so cl emits a normalised call):
//     0x717880  TechnoTypeClass::HasTurret  -> (TurretCount @0x808) > 0
//     0x473450  PassengersClass::GetFirstPassenger -> *(this+0x04)
//   Both are reached by a direct relative CALL with the receiver in ECX, so
//   both are declared as ordinary __thiscall members of their own class; the
//   compiler rejects the receiver convention on a free function.
//
// TechnoClass weapon/passenger dispatch helpers:
//   GetPrimaryWeapon       — choose the current-numbered weapon when the type
//                            has a turret, else weapon 0, via virtual GetWeapon.
//   SetTargetForPassengers — walk the passenger list and forward a new target
//                            to each occupant (virtual SetTarget, slot +0x3C8).
#ifndef GG_MATCH_CORE_TECHNO_CLASS_WEAPON_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_WEAPON_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct WeaponStruct;
class  AbstractClass;
class  TechnoClass;
class  FootClass;
struct TechnoVtbl;
struct FootVtbl;

// TechnoTypeClass — only the turret predicate is reached from this TU, and it
// is reached as a direct call with the type pointer in ECX.
class TechnoTypeClass
{
public:
    // FUNCTION: GAMEMD 0x717880 (decl; reloc) — TurretCount @0x808 > 0
    bool HasTurret();
};

// PassengersClass — transport occupant list head (matches the committed spine).
struct PassengersClass
{
    // FUNCTION: GAMEMD 0x473450 (decl; reloc) — returns *(this+0x04)
    FootClass* GetFirstPassenger();

    int        NumPassengers;     // +0x00
    FootClass* FirstPassenger;    // +0x04
};
GG_STATIC_ASSERT(offsetof(PassengersClass, FirstPassenger) == 0x04);

// FootClass, as far as the passenger walk reads it: the primary vptr, the
// AbstractFlags byte at +0x14 whose bit 4 gates the walk, and the NextObject
// link at +0x30.
class FootClass
{
public:
    FootVtbl*     Vfptr;                    // +0x00
    char          _pad_004[0x14 - 0x04];    // +0x04
    unsigned char AbstractFlags;            // +0x14
    char          _pad_015[0x30 - 0x15];    // +0x15
    FootClass*    NextObject;               // +0x30
};
GG_STATIC_ASSERT(offsetof(FootClass, AbstractFlags) == 0x14);
GG_STATIC_ASSERT(offsetof(FootClass, NextObject)    == 0x30);

// Minimal TechnoClass view: only the members these two methods touch are
// modelled (full 0x520 layout is the committed spine match/_layout/techno_class.h
// and is P2 here). The primary vptr at +0x000 is modelled explicitly so the two
// slot dispatches can be written as ordinary C++.
class TechnoClass
{
public:
    // FUNCTION: GAMEMD 0x70E1A0  (__thiscall)
    WeaponStruct* GetPrimaryWeapon();
    // FUNCTION: GAMEMD 0x710550  (__thiscall)
    void          SetTargetForPassengers(AbstractClass* target);

    TechnoVtbl*     Vfptr;                // +0x000
    char            _pad_004[0x114-0x004];// +0x004 .. +0x113
    PassengersClass Passengers;           // +0x114 (8)
    char            _pad_11C[0x138-0x11C];// +0x11C .. +0x137
    int             CurrentWeaponNumber;  // +0x138
};

GG_STATIC_ASSERT(offsetof(TechnoClass, Vfptr)               == 0x000);
GG_STATIC_ASSERT(offsetof(TechnoClass, Passengers)          == 0x114);
GG_STATIC_ASSERT(offsetof(TechnoClass, CurrentWeaponNumber) == 0x138);

// The classes have to be complete before these typedefs, or VC6 falls back to
// the multiple-inheritance member-pointer form and emits a `this` adjustment.
typedef TechnoTypeClass* (TechnoClass::*GetTechnoTypeFn)();
typedef WeaponStruct*    (TechnoClass::*GetWeaponFn)(int);
typedef void             (FootClass::*SetTargetFn)(AbstractClass*);

// Primary vtable slots reached from this TU.
//   +0x084  GetTechnoType()      no arguments, the type pointer
//   +0x3F8  GetWeapon(int)       the weapon record for a weapon index
struct TechnoVtbl
{
    char            _pad_000[0x084];            // 0x000
    GetTechnoTypeFn At_84;                      // 0x084
    char            _pad_088[0x3F8 - 0x088];    // 0x088
    GetWeaponFn     At_3F8;                     // 0x3F8
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl, At_84)  == 0x084);
GG_STATIC_ASSERT(offsetof(TechnoVtbl, At_3F8) == 0x3F8);

//   +0x3C8  SetTarget(AbstractClass*)
struct FootVtbl
{
    char        _pad_000[0x3C8];    // 0x000
    SetTargetFn At_3C8;             // 0x3C8
};
GG_STATIC_ASSERT(offsetof(FootVtbl, At_3C8) == 0x3C8);

#endif // GG_MATCH_CORE_TECHNO_CLASS_WEAPON_METHODS_H

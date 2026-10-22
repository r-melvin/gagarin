// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4733A0: the list head `MOV [EDI],0` / `INC` (count
//   at +0x00) and `MOV ECX,[EDI+4]` (first passenger at +0x04); on each
//   passenger the chain link `MOV EAX,[ESI+0x30]` (ObjectClass::NextObject),
//   the foot test `MOV CL,[EAX+0x14]; SHR CL,2; AND CL,1` (AbstractFlags bit
//   2, read as a byte bit-field), and the virtual `CALL [EAX+0xD4]`. The
//   method name is YRpp's TechnoClass::AddPassenger (consult-only); the
//   receiver is the embedded PassengersClass at TechnoClass+0x114, as in the
//   siblings 0x473430 / 0x473450.
//
// PassengersClass::AddPassenger — link a passenger (and whatever chain of
// passengers it already trails) at the head of the transport's cargo list and
// recount.
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_PASSENGER_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_PASSENGER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/object_class.h"   // ObjectClass: AbstractFlags @0x14, NextObject @0x30

GG_STATIC_ASSERT(offsetof(AbstractClass, Flags) == 0x14);
GG_STATIC_ASSERT(offsetof(ObjectClass,   NextObject)    == 0x30);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct PassengerVtbl;

// The passenger as this list sees it: the ObjectClass spine with AbstractFlags
// overlaid as byte bit-fields, because retail reads the "is a FootClass" bit as
// `MOV CL,[EAX+0x14]; SHR CL,2; AND CL,1` — a one-bit field of a byte, not an
// int mask. Only the low byte of the flag word is modelled; NextObject threads
// the cargo chain; slot +0xD4 is the limbo virtual. Modelled standalone rather
// than over ../_layout/object_class.h; the spine's AbstractClass::Flags uses the
// same bit-field layout.
struct PassengerObj
{
    void*         _vtable;         // +0x0000 (PassengerVtbl*)
    char          _pad004[0x10];   // +0x0004
    unsigned char IsTechno : 1;    // +0x0014 bit 0
    unsigned char Flag1    : 1;    // +0x0014 bit 1
    unsigned char IsFoot   : 1;    // +0x0014 bit 2
    unsigned char _rest    : 5;    // +0x0014 bits 3..7
    char          _pad015[0x1B];   // +0x0015
    PassengerObj* NextObject;      // +0x0030
};
GG_STATIC_ASSERT(offsetof(PassengerObj, NextObject) == 0x30);
GG_STATIC_ASSERT(sizeof(PassengerObj)               == 0x34);

// The FootClass view of a passenger (the chain-walk cursor's type): no extra
// members, same layout. A distinct type only for readability — it does not
// change codegen.
struct PassengerFoot : PassengerObj
{
};
GG_STATIC_ASSERT(sizeof(PassengerFoot) == 0x34);

typedef int (PassengerObj::*FnD4_Passenger)();

struct PassengerVtbl
{
    char           _pad000[0xD4];   // +0x0000
    FnD4_Passenger Limbo;           // +0x00D4
};
GG_STATIC_ASSERT(offsetof(PassengerVtbl, Limbo) == 0xD4);

// PassengersClass — the cargo list head embedded in TechnoClass at +0x114.
struct PassengerList
{
    int           NumPassengers;    // +0x00
    PassengerObj* FirstPassenger;   // +0x04

    // FUNCTION: GAMEMD 0x4733A0  TechnoClass::AddPassenger  (__thiscall)
    void AddPassenger(PassengerObj* passenger);
};
GG_STATIC_ASSERT(offsetof(PassengerList, NumPassengers)  == 0x00);
GG_STATIC_ASSERT(offsetof(PassengerList, FirstPassenger) == 0x04);
GG_STATIC_ASSERT(sizeof(PassengerList)                   == 0x08);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_PASSENGER_METHODS_H

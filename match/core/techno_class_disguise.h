// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x70E280-0x70E2A4), cross-checked
//   against YRpp (DisguiseAs @0x70E280; Disguised @0x1D8,
//   DisguiseCreationFrame @0x1DC; consult-only, reconfirmed numerically here).
//   These two offsets agree with the committed spine match/_layout/techno_class.h
//   (Disguised @0x1D8, DisguiseCreationFrame @0x1DC).
//
// TechnoClass::DisguiseAs — record the start of a disguise (set the Disguised
// flag + stamp the creation frame) when given a non-null target, then dispatch
// the virtual at vtable slot +0x49C to actually apply/recompute the disguise.
#ifndef GG_MATCH_CORE_TECHNO_CLASS_DISGUISE_H
#define GG_MATCH_CORE_TECHNO_CLASS_DISGUISE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class AbstractClass;
class TechnoClass;

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84, stamped into
// DisguiseCreationFrame (MOV EAX,[0x00A8ED84]).
#include "../core/frame_counter.h"

// The primary vtable, modelled only as far as the one slot this TU dispatches
// through. Slot +0x49C takes no arguments and returns the value DisguiseAs
// itself returns (retail's `MOV EDX,[ECX]; CALL [EDX+0x49C]; RET 4` leaves EAX
// untouched afterwards), so the member-pointer's signature is fixed by the
// disassembly and not guessed.
struct TechnoVtbl;

// Minimal TechnoClass view: only the two disguise members touched by
// DisguiseAs are modelled (the full 0x520 layout is in the committed spine
// match/_layout/techno_class.h and is P2 here). The vptr at +0x000 is modelled
// explicitly so the slot dispatch can be written as ordinary C++.
class TechnoClass
{
public:
    // FUNCTION: GAMEMD 0x70E280  (__thiscall)
    unsigned long DisguiseAs(AbstractClass* pTarget);

    TechnoVtbl*   Vfptr;                // +0x000
    char          _pad_004[0x1D8 - 4];  // +0x004 .. +0x1D7
    unsigned char Disguised;            // +0x1D8 (bool)
    char          _pad_1D9[3];          // +0x1D9 .. +0x1DB
    int           DisguiseCreationFrame;// +0x1DC
};

GG_STATIC_ASSERT(offsetof(TechnoClass, Vfptr)                 == 0x000);
GG_STATIC_ASSERT(offsetof(TechnoClass, Disguised)             == 0x1D8);
GG_STATIC_ASSERT(offsetof(TechnoClass, DisguiseCreationFrame) == 0x1DC);

// The class has to be complete before the member-pointer typedef, or VC6 falls
// back to the multiple-inheritance form and emits a `this` adjustment.
typedef unsigned long (TechnoClass::*ApplyDisguiseFn)();

struct TechnoVtbl
{
    char            _pad_000[0x49C];    // 0x000
    ApplyDisguiseFn At_49C;             // 0x49C
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl, At_49C) == 0x49C);

#endif // GG_MATCH_CORE_TECHNO_CLASS_DISGUISE_H

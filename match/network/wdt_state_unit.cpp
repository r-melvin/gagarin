// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The WorldDominationTour::State constructors and their no-argument factory
// (retail .text 0x76F500..0x76F5FC). State (RTTI vtable 0x7F7314) is a
// ReferenceCounted holding an rc_ptr<WDTState> at +0x08 and one pointer at
// +0x10: operator new(0x14) at 0x76F504. The sibling factory 0x76F470 builds
// the second constructor in place; the table row it picks is
// ((WDTState*)Next.Pointer)->unknown_44[index] when index is below the count
// at +0x24. Class names are the retail RTTI names.

#include "world_domination_tour.h"

// FUNCTION: GAMEMD 0x76F470
// The factory for a State over `state` positioned on row `index`, returned in
// a handle (hidden result pointer in ECX, the source in EDX); the constructor
// below is expanded into it.
rc_ptr<WorldDominationTour::State> FUN_0076F470(const rc_ptr<WDTState>& state, int index)
{
    return rc_ptr<WorldDominationTour::State>(new WorldDominationTour::State(state, index));
}

// FUNCTION: GAMEMD 0x76F500
// The factory for a default State, returned in a handle (hidden result
// pointer in ECX).
rc_ptr<WorldDominationTour::State> FUN_0076F500()
{
    return rc_ptr<WorldDominationTour::State>(new WorldDominationTour::State());
}

// FUNCTION: GAMEMD 0x76F560
// An empty State: no state handle, no row.
WorldDominationTour::State::State()
    : unknown_10(0)
{
}

// FUNCTION: GAMEMD 0x76F5A0
// A State over `state`, positioned on row `index` when it exists.
WorldDominationTour::State::State(const rc_ptr<WDTState>& state, unsigned int index)
    : Next(state), unknown_10(0)
{
    WDTState* s = Next.Get();
    if (s != 0 && index < (unsigned int)s->unknown_24)
        unknown_10 = s->unknown_44[index];
}

// FUNCTION: GAMEMD 0x76F650
// Seats the State table, then the state handle and the ReferenceCounted
// destructor.
WorldDominationTour::State::~State()
{
}

// SYNTHETIC: GAMEMD 0x76F6C0
// State scalar deleting destructor, the destructor body inlined.

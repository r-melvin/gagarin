// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The WorldDominationTour::History block of retail .text (0x767940..0x767BEF):
// three of the unit's run-time initialisers, the History factory and
// constructor, and two History members, in retail address order. Class names
// are the retail RTTI names (".?AVHistory@WorldDominationTour@@" vtable
// 0x7F70DC, ".?AVReferenceCounted@@" 0x7F0954, ".?AV?$rc_ptr@VHistory@..."
// 0x7F6F74, ".?AV?$rc_ptr@VWDTState@@@@" 0x7F70EC).
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/header_tuning_globals.h"
#include "world_domination_tour.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xB72830
extern double DAT_00B72830;
// GLOBAL: GAMEMD 0x7F70C8
const double DAT_007F70C8 = 60.0;

// GLOBAL: GAMEMD 0xB72880
extern double DAT_00B72880;
// GLOBAL: GAMEMD 0xB72868
extern double DAT_00B72868;
// GLOBAL: GAMEMD 0xB72870
extern TuningCoordInit DAT_00B72870;

// ---- History ---------------------------------------------------------------------------------------------------------

// FUNCTION: GAMEMD 0x76F470 (decl; reloc) -- the State factory, same shape as 0x767B00.
rc_ptr<WorldDominationTour::State> FUN_0076F470(const rc_ptr<WDTState>& state, int arg);

// FUNCTION: GAMEMD 0x767B00
// The History factory: a new History over `state`, returned in a handle
// (hidden result pointer in ECX, the source in EDX).
rc_ptr<WorldDominationTour::History> FUN_00767B00(const rc_ptr<WDTState>& state)
{
    return rc_ptr<WorldDominationTour::History>(new WorldDominationTour::History(state));
}

// FUNCTION: GAMEMD 0x767B70
// The constructor: expanded into the factory above (/Ob2) and also kept out of line.
WorldDominationTour::History::History(const rc_ptr<WDTState>& state)
    : State(state)
{
}

// FUNCTION: GAMEMD 0x767BB0
rc_ptr<WorldDominationTour::State> WorldDominationTour::History::FUN_00767BB0(int arg) const
{
    return FUN_0076F470(State, arg);
}

// FUNCTION: GAMEMD 0x767BD0
int WorldDominationTour::History::FUN_00767BD0(unsigned int index) const
{
    WDTState* state = (WDTState*)State.Pointer;
    if (state != 0 && index < state->unknown_24)
        return 1;
    return 0;
}

// FUNCTION: GAMEMD 0x767BF0
// Seats the History table, then the state handle and the ReferenceCounted
// destructor.
WorldDominationTour::History::~History()
{
}

// SYNTHETIC: GAMEMD 0x767C50 -- rc_ptr<WDTState>::`scalar deleting destructor' (compiler-emitted for the
// rc_ptr<WDTState> this TU instantiates)
// SYNTHETIC: GAMEMD 0x767C10
// History scalar deleting destructor.

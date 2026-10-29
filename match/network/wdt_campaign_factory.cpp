// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x764B30 (the rc_ptr<Campaign> factory: operator new(0x4C) at 0x764B55,
//   constructor 0x764B90 with the first value in EDX and the source handle on the stack, handle vtable
//   0x7F6F24 = .?AV?$rc_ptr@VCampaign@WorldDominationTour@@@@). Class names are the retail RTTI names;
//   the Campaign class is in world_domination_tour.h.
//   Address index: 0x764B30.
#include "world_domination_tour.h"

// FUNCTION: GAMEMD 0x764B30
// The Campaign factory: an empty handle when the source holds nothing, otherwise a new Campaign
// over it (hidden result pointer in ECX, the first value in EDX).
rc_ptr<WorldDominationTour::Campaign> FUN_00764B30(unsigned int first, const rc_ptr_base& source)
{
    if (source.Pointer == 0)
        return rc_ptr<WorldDominationTour::Campaign>();
    return rc_ptr<WorldDominationTour::Campaign>(new WorldDominationTour::Campaign(first, source));
}

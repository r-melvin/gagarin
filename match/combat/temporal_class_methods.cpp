// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x71AB10  TemporalClass::GetWarpPerStep (__thiscall)
//   FUNCTION: GAMEMD 0x71AD40  TemporalClass::JustLetGo      (__thiscall)
//   FUNCTION: GAMEMD 0x71ADE0  TemporalClass::Detach         (__thiscall)

#include "../_layout/temporal_class.h"

// FUNCTION: GAMEMD 0x71AB10  (__thiscall)
// Accumulate this temporal's warp-per-step plus that of every helper temporal
// chained through unknown_44 (capped at 50 helpers deep), and cache the local
// value in WarpPerStep.
int TemporalClass::GetWarpPerStep(int nHelperCount) const
{
    int helper = 0;
    if (unknown_44) {
        if (nHelperCount <= 50)
            helper = unknown_44->GetWarpPerStep(nHelperCount + 1);
    }

    int amount = Owner->vf_3F8(Owner->vf_2E4(0))->Type->unknown_A4;
    unknown_4C = amount;
    return amount + helper;
}

// FUNCTION: GAMEMD 0x71AD40  (__thiscall)
// Release the target and unlink from both helper neighbours without notifying
// the owner (the lighter sibling of Detach).
void TemporalClass::JustLetGo()
{
    if (Target) {
        Target->unknown_270 = 0;
        Target->unknown_278 = 0;
        Target = 0;
    }

    if (unknown_44) {
        if (unknown_44->unknown_40 == this)
            unknown_44->unknown_40 = 0;
        unknown_44->Detach();
        unknown_44 = 0;
    }

    if (unknown_40) {
        if (unknown_40->unknown_44 == this)
            unknown_40->unknown_44 = 0;
        unknown_40->Detach();
        unknown_40 = 0;
    }

    unknown_44 = 0;
    unknown_40 = 0;
    unknown_3C = 0;
    unknown_38 = 0;
}

// FUNCTION: GAMEMD 0x71ADE0  (__thiscall)
// Detach this temporal: clear the (assumed non-null) target's impact flags,
// recursively detach both helper neighbours, then notify the owner.
void TemporalClass::Detach()
{
    Target->unknown_270 = 0;
    Target->unknown_278 = 0;
    Target = 0;

    if (unknown_44) {
        if (unknown_44->unknown_40 == this)
            unknown_44->unknown_40 = 0;
        unknown_44->Detach();
    }

    if (unknown_40) {
        if (unknown_40->unknown_44 == this)
            unknown_40->unknown_44 = 0;
        unknown_40->Detach();
    }

    unknown_44 = 0;
    unknown_40 = 0;
    unknown_3C = 0;
    unknown_38 = 0;

    if (Owner)
        Owner->vf_484(0, 1);
}

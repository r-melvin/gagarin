// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp TemporalClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x71AB10  TemporalClass::GetWarpPerStep (__thiscall)
//   FUNCTION: GAMEMD 0x71AD40  TemporalClass::JustLetGo      (__thiscall)
//   FUNCTION: GAMEMD 0x71ADE0  TemporalClass::Detach         (__thiscall)

#include "temporal_class_methods.h"

// FUNCTION: GAMEMD 0x71AB10  (__thiscall)
// Accumulate this temporal's warp-per-step plus that of every helper temporal
// chained through PrevTemporal (capped at 50 helpers deep), and cache the local
// value in WarpPerStep.
int TemporalClass::GetWarpPerStep(int nHelperCount) const
{
    int helper = 0;
    if (PrevTemporal) {
        if (nHelperCount <= 50)
            helper = PrevTemporal->GetWarpPerStep(nHelperCount + 1);
    }

    int amount = Owner->GetWeapon(Owner->SelectWeapon(0))->WeaponType->WarpAmount;
    WarpPerStep = amount;
    return amount + helper;
}

// FUNCTION: GAMEMD 0x71AD40  (__thiscall)
// Release the target and unlink from both helper neighbours without notifying
// the owner (the lighter sibling of Detach).
void TemporalClass::JustLetGo()
{
    if (Target) {
        Target->TemporalImpact = 0;
        Target->TemporalTargetingMe = 0;
        Target = 0;
    }

    if (PrevTemporal) {
        if (PrevTemporal->NextTemporal == this)
            PrevTemporal->NextTemporal = 0;
        PrevTemporal->Detach();
        PrevTemporal = 0;
    }

    if (NextTemporal) {
        if (NextTemporal->PrevTemporal == this)
            NextTemporal->PrevTemporal = 0;
        NextTemporal->Detach();
        NextTemporal = 0;
    }

    PrevTemporal = 0;
    NextTemporal = 0;
    SourceSW = 0;
    unknown_pointer_38 = 0;
}

// FUNCTION: GAMEMD 0x71ADE0  (__thiscall)
// Detach this temporal: clear the (assumed non-null) target's impact flags,
// recursively detach both helper neighbours, then notify the owner.
void TemporalClass::Detach()
{
    Target->TemporalImpact = 0;
    Target->TemporalTargetingMe = 0;
    Target = 0;

    if (PrevTemporal) {
        if (PrevTemporal->NextTemporal == this)
            PrevTemporal->NextTemporal = 0;
        PrevTemporal->Detach();
    }

    if (NextTemporal) {
        if (NextTemporal->PrevTemporal == this)
            NextTemporal->PrevTemporal = 0;
        NextTemporal->Detach();
    }

    PrevTemporal = 0;
    NextTemporal = 0;
    SourceSW = 0;
    unknown_pointer_38 = 0;

    if (Owner)
        Owner->NotifyOwnerOfDetach(0, 1);
}

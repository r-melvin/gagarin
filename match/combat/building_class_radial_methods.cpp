// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4566B0.

#include "building_class_radial_methods.h"

// FUNCTION: GAMEMD 0x4566B0
//
// Radius (in cells) of the radial range indicator drawn round a selected
// building. Psychic detectors use their detection radius; gap generators one
// of two gap radii depending on super-charge; cloak generators and sensor
// arrays the cloak radius; anything else its primary weapon's range in cells,
// and zero when it has no usable weapon.
//
// The gap branch is a ternary: each arm loads its byte into CL and VC6
// duplicates the `MOVSX EAX,CL` epilogue into both, which is retail's shape;
// two `return`s emit the sign-extension straight from memory.
//
// PARTIAL (42.9%, 27/63; mnemonic multiset identical). Retail zeroes EBX at
// entry (`XOR EBX,EBX` between `MOV ESI,ECX` and `PUSH EDI`), tests the
// psychic radius straight out of EAX (`JG` to the shared epilogue), keeps the
// weapon in EDI and returns the zero from the two weapon-rejecting exits via
// `MOV EAX,EBX`. This form -- the radius read into the result variable, the
// weapon block nested under `result <= 0`, `result = 0` after the two
// guards, one trailing `return result` -- is the only phrasing that
// reproduces retail's control flow and instruction multiset exactly; the
// residual is register naming only: cl 8804 keeps the result in EDI (loads
// and tests the radius there, `XOR EDI,EDI` late, before the call) and the
// weapon in EBX, where retail has the constant zero in EBX from entry and the
// radius in EAX. Variants tried: nested `if` with one trailing `return 0`;
// two `return 0`s (each folds to its own `XOR EAX,EAX`); `int result = 0`
// returned at the end (constant-folded, no register, 1.6%); the same with the
// range path routed through `result` (12.7%, takes EBX but merges the range
// epilogue); `int range = 0` conditionally overwritten then `return 0` /
// `return range` (folded, 1.6%); a `zero` local used in the compares and the
// returns (folded); `result = radius` in the positive branch with an
// else-chain (15.6%: takes EBX but pays `MOV EBX,ECX`); `result = Range`
// re-zeroed on the fall path (folded); /Ox and /O1 (no register). Same class
// as "Zero not held in a register" in the methodology; the 8447-vs-8804
// constant-register choice is the suspected cause.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply. Both sides
// emit five separate epilogues at the same five sites and push EBX/ESI/EDI in
// the same order; nothing is merged that retail leaves split. The residual is
// the shared-zero class, not a colouring shift: retail hoists `XOR EBX,EBX`
// above `PUSH EDI` at entry and spends it once on `MOV EAX,EBX` at the shared
// zero exit, i.e. it splits the live range of `result` between EAX (the radius
// arm) and EBX (the zero arm), where cl 8804 keeps one register (EDI) for both
// and materialises the zero at the `result = 0` statement.
int BuildingClass_004566B0::GetRadialIndicatorRange()
{
    Type_004566B0* type = this->Type;
    int result = type->PsychicDetectionRadius;

    if (result <= 0) {
        if (type->GapGenerator)
            return this->GapSuperCharged ? type->SuperGapRadiusInCells
                                         : type->GapRadiusInCells;

        if (type->SensorArray || type->CloakGenerator)
            return type->CloakRadiusInCells;

        result = 0;
        WeaponStruct_004566B0* weapon = this->GetPrimaryWeapon();
        if (this->FUN_0070E240(weapon)) {
            int range = weapon->WeaponType->Range;
            if (range > 0)
                return range / 256;
        }
    }
    return result;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41B890.

#include "deploy_ready_methods.h"

// FUNCTION: GAMEMD 0x41B890
//
// Whether this object may deploy: it must either have nothing at +0x2B4 or be in
// state 0x1F, its own enable byte must be set, and neither of the two mission
// values 0x1A and 0x1B may be current. The final permission comes from the linked
// type if there is one, and from the local byte at +0x3D4 if there is not.
//
// PARTIAL (59.5%, 22/37). Our stream is a strict subset of retail's: the
// mnemonic multiset reports nothing on our side that retail lacks, and two
// instructions on retail's that we do not emit — a `TEST ECX,ECX; JZ` at
// 0x41B8E2 re-testing a register the compiler has just branched on and which is
// provably zero at that point. Retail's build failed to thread that away; ours
// threads it, and no phrasing puts it back (a two-statement `&&` form, a ternary,
// an if/else into a temporary, and both arm orders were tried).
//
// The form below was chosen over a higher-scoring one deliberately. Writing the
// two permission paths as separate `return true` statements scores 65.8% but adds
// a duplicated `MOV AL,1; POP ESI; RET` on our side, so it differs from retail in
// five instructions rather than two; the shared `goto` reaches retail's single
// true block. The percentage is measuring alignment, not closeness.
//
// The slot at +0x184 is called twice rather than once and compared twice, which
// is retail's shape (0x41B8B4 and 0x41B8C3), so the two comparisons are separate
// short-circuit terms rather than one call held in a local.
bool AircraftClass_0041B890::FUN_0041B890()
{
    if ((this->At_2B4 == 0 || this->At_AC == 0x1F)
        && this->At_3D5 != 0
        && (this->*this->Vtbl->At_184)() != 0x1A
        && (this->*this->Vtbl->At_184)() != 0x1B) {

        if (this->At_5D4 == 0) {
            if (this->At_3D4) goto permitted;
        } else {
            if (FUN_006EC300(this->At_5D4)) goto permitted;
        }
    }

    return false;

permitted:
    return true;
}

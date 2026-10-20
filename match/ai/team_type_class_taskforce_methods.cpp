// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6F1FA0.

#include "team_type_class_taskforce_methods.h"

// FUNCTION: GAMEMD 0x6F1FA0
//
// Derive the team type's summary flags from its taskforce. +0xF0 starts set and
// +0xF1 clear; every participating entry type (+0xCCE) either clears +0xF0 (no
// +0x5E0 capability) or sets +0xF1. The +0xEC value starts at 9 and is folded
// through 0x5889F0 for every entry, participating or not. +0xF6 overrides +0xF0
// at the end.
void TeamTypeClass::ProcessTaskForce()
{
    this->At_F0 = 1;
    this->At_F1 = 0;
    this->At_EC = 9;

    for (int i = 0; i < this->TaskForce->CountEntries; i++) {
        TechnoType_006F1FA0* type = this->TaskForce->Entries[i].Type;

        if (type->At_CCE != 0) {
            if (type->At_5E0 == 0) {
                this->At_F0 = 0;
            } else {
                this->At_F1 = 1;
            }
        }

        this->At_EC = FUN_005889F0(type->At_5B4, this->At_EC);
    }

    if (this->At_F6 != 0) {
        this->At_F0 = 0;
    }
}

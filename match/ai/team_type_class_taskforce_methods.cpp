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
    this->Flag_F0 = true;
    this->Flag_F1 = false;
    this->unknown_EC = 9;

    for (int i = 0; i < this->TaskForce->EntryCount; i++) {
        TechnoTypeClass* type = this->TaskForce->Entries[i].Type;

        if (type->Naval) {
            if (type->Passengers == 0) {
                this->Flag_F0 = false;
            } else {
                this->Flag_F1 = true;
            }
        }

        this->unknown_EC = FUN_005889F0(type->MovementZone, this->unknown_EC);
    }

    if (this->Flag_F6) {
        this->Flag_F0 = false;
    }
}

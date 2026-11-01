// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4C9FF0.

#include "factory_class_abandon_methods.h"

// FUNCTION: GAMEMD 0x4C9FF0
//
// Drop whatever is being built. With nothing in production this reports
// false. Otherwise the object's name is logged, the money already sunk into it
// (the type's cost for the object's owner minus what is still owed) is
// refunded to the factory owner, the balance, special item, production stage
// and timer are reset and the factory is left suspended and marked changed.
// An AI owner also forgets its pending build of that kind (building 0xF,
// infantry 1, unit 2, aircraft 6). The object itself is deleted with the
// scenario-init counter raised around the delete.
//
// The stage reset goes through the inlined StageClass::SetRate (timer temporary,
// then Rate); written as plain member stores VC6 interleaves the following
// Value / flag stores into the timer copy.
bool Factory_004C9FF0::AbandonProduction()
{
    if (this->Object != 0) {
        FUN_004068E0(DAT_008222AC, this->Object->GetTechnoType()->Name);

        TechnoType_004C9FF0* type = this->Object->GetTechnoType();
        int cost = (type->*type->Vtbl->GetCost)(this->Object->Owner);
        this->Owner->GiveMoney(cost - this->Balance);
        this->Balance = 0;
        if (this->SpecialItem != 0) {
            this->SpecialItem = -1;
        }

        this->Production.SetRate(0);
        this->Production.Value = 0;
        this->IsSuspended = true;
        this->IsDifferent = true;

        if (!this->Owner->IsControlledByHuman()) {
            if (this->Object->WhatAmI() == 0xF) {
                this->Owner->At_5654 = -1;
            }
            if (this->Object->WhatAmI() == 1) {
                this->Owner->At_5650 = -1;
            }
            if (this->Object->WhatAmI() == 2) {
                this->Owner->At_5658 = -1;
            }
            if (this->Object->WhatAmI() == 6) {
                this->Owner->At_564C = -1;
            }
        }

        DAT_00A8E7AC++;
        if (this->Object) {
            delete this->Object;
        }
        this->Object = 0;
        DAT_00A8E7AC--;
        return true;
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8222AC
extern const char DAT_008222AC[] = "Abandoning production of %s\n";
// END defined globals

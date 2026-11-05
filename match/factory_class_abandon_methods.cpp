// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4C9FF0.

#include "_layout/factory_class.h"
#include "_layout/techno_class.h"
#include "_layout/techno_type_class.h"
#include "_layout/house_class.h"

// GLOBAL: GAMEMD 0xA8E7AC -- Unsorted::ScenarioInit.
extern int DAT_00A8E7AC;
// STRING: GAMEMD 0x8222AC -- "Abandoning production of %s\n".
extern const char DAT_008222AC[];
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x4C9FF0
//
// Drop whatever is being built. With nothing in production this reports
// false. Otherwise the object's name is logged, the money already sunk into it
// (the type's cost for the object's owner minus what is still owed) is
// refunded to the factory owner, the balance, special item, production stage
// and timer are reset and the factory is left suspended and marked changed.
// An AI owner also forgets its pending build of that kind (WhatAmI 0xF,
// 1, 2 and 6). The object itself is deleted with the
// scenario-init counter raised around the delete.
//
// The stage reset goes through the inlined StageClass::SetRate (timer temporary,
// then Rate); written as plain member stores VC6 interleaves the following
// Value / flag stores into the timer copy.
bool FactoryClass::AbandonProduction()
{
    if (this->Object != 0) {
        FUN_004068E0(DAT_008222AC, this->Object->vf_34()->Name.Data);

        int cost = this->Object->vf_34()->vf_33(this->Object->Owner);
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
            if (this->Object->vf_11() == 0xF) {
                this->Owner->ProducingInfantryTypeIndex = -1;
            }
            if (this->Object->vf_11() == 1) {
                this->Owner->ProducingUnitTypeIndex = -1;
            }
            if (this->Object->vf_11() == 2) {
                this->Owner->ProducingAircraftTypeIndex = -1;
            }
            if (this->Object->vf_11() == 6) {
                this->Owner->ProducingBuildingTypeIndex = -1;
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

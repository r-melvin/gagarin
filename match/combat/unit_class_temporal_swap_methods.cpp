// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   UnitClass virtual slots 309/310 read off retail gamemd.exe v1.001 (vtable 0x7F5C70):
//   hand the temporal weapon in use over from another unit to this one.
//   Address index: 0x746420 vf_309, 0x7464E0 vf_310.

#include "../_layout/unit_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/temporal_class.h"
#include "../core/frame_counter.h"

// FUNCTION: GAMEMD 0x746420
// Takes over the temporal link of the given unit (it must be a unit), carrying its
// rearm state across, then adopts that unit's mode.
void UnitClass::vf_309(int a1)
{
    UnitClass* other = reinterpret_cast<UnitClass*>(a1);
    TemporalClass* temporal = other->TemporalImUsing;
    if (temporal) {
        int rearming = 0;
        if (other->RearmTimer.GetTimeLeft()) {
            rearming = 1;
        }
        TemporalImUsing = temporal;
        temporal->Owner = reinterpret_cast<TemporalTechnoView*>(this);
        other->TemporalImUsing = 0;
        FUN_0070DC70(7);
        if (rearming) {
            CurrentBurstIndex++;
            RearmTimer = CDTimerClass(vf_198(7));
        }
    }
    FUN_0070DC70(other->vf_33()->IFVMode);
}

// FUNCTION: GAMEMD 0x7464E0
// Same hand-over for a possibly null foot object.
void UnitClass::vf_310(FootClass* passenger)
{
    if (passenger && TemporalImUsing) {
        TemporalClass* temporal = TemporalImUsing;
        int rearming = 0;
        if (RearmTimer.GetTimeLeft()) {
            rearming = 1;
        }
        passenger->TemporalImUsing = temporal;
        TemporalImUsing->Owner = reinterpret_cast<TemporalTechnoView*>(passenger);
        TemporalImUsing = 0;
        if (passenger->TemporalImUsing && passenger->TemporalImUsing->Target) {
            passenger->TemporalImUsing->FUN_0071ABC0();
        }
        if (rearming) {
            passenger->CurrentBurstIndex++;
            passenger->RearmTimer = CDTimerClass(passenger->vf_198(0));
        }
    }
    FUN_0070DC70(0);
}

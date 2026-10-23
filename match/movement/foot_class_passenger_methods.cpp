// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x4DE710),
//   cross-checked vs YRpp. Every offset reconfirmed
//   numerically in the header.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4DE710  FootClass::RemoveFirstPassenger (__thiscall)

#include "../_layout/foot_class.h"
#include "../_layout/techno_type_class.h"

// FUNCTION: GAMEMD 0x4DE710  (__thiscall)
// Pop the head of the transport cargo list. If the type byte @0x805 is set
// and the list just emptied, run FootClass slot 310 (+0x4D8) on the removed
// passenger. Returns the removed passenger.
FootClass* FootClass::RemoveFirstPassenger()
{
    FootClass* removed = this->Passengers.RemoveFirstPassenger();
    if (this->vf_33()->Gunner && this->Passengers.NumPassengers == 0)
        this->vf_310(removed);
    return removed;
}

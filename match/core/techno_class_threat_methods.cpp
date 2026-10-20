// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm
//   0x70F6E0-0x70F72E, len 0x4F). Names cross-checked against YRpp
//   TechnoClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x70F6E0  TechnoClass::UpdateThreatInCell (__thiscall)

#include "techno_class_threat_methods.h"

// FUNCTION: GAMEMD 0x70F6E0  (__thiscall)
// Re-stamp this object's threat contribution into a cell's per-house threat
// map: take the old contribution out, recompute it, and put the new one in.
void TechnoClass::UpdateThreatInCell(CellClass* Cell)
{
    if (Cell != 0) {
        Cell->AddThreat((this->*this->Vfptr->At_38)(), -this->ThreatPosed);
        this->ThreatPosed = 0;

        int threat = (this->*this->Vfptr->At_2C0)();

        this->ThreatPosed = threat;
        Cell->AddThreat((this->*this->Vfptr->At_38)(), threat);
    }
}

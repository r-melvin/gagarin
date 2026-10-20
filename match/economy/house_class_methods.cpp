// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Names cross-checked against YRpp HouseClass.h (consult-only, no LICENSE;
//   each offset reconfirmed against the user's binary below).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x509130   HouseClass::AcquiredThreatNode            (__thiscall)
//   FUNCTION: GAMEMD 0x53A130   HouseClass::IonSensitivesShouldBeOffline  (__thiscall)
//   FUNCTION: GAMEMD 0x7490C0   UnitTrackerClass::GetArray                (__thiscall)

#include "house_class_methods.h"

// FUNCTION: GAMEMD 0x509130  HouseClass::AcquiredThreatNode (__thiscall)
//   MOV byte ptr [ECX+0x1fb], 1 ; RET
void HouseClass::AcquiredThreatNode()
{
    this->HasThreatNode = true;
}

// FUNCTION: GAMEMD 0x53A130  HouseClass::IonSensitivesShouldBeOffline (__thiscall)
//   XOR AL,AL ; RET   (unconditional false)
bool HouseClass::IonSensitivesShouldBeOffline() const
{
    return false;
}


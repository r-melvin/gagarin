// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Bodies and
//   member offsets derived directly from the disassembly; signatures
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4D9920  FootClass::GreatestThreat        (__thiscall)
//   FUNCTION: GAMEMD 0x7104F0  FootClass::UpdatePassengerCoords (__thiscall)

#include "../_layout/foot_class.h"

#ifndef NULL
#define NULL 0
#endif

// FUNCTION: GAMEMD 0x4D9920  (__thiscall)
// Scan-limited override of TechnoClass::GreatestThreat: when IsScanLimited, force
// the threat flags to (set Range, clear Area) before delegating; if the delegate
// finds no target while scan-limited, clear the scan-limit flag and return the
// (null) result.
//   MOV AL,[ESI+0x688] ; (IsScanLimited ? AND AL,0xFD ; OR AL,1) ; CALL 0x6F8DF0
AbstractClass* FootClass::vf_241(unsigned int threat, CoordStruct* pCoord,
                                bool onlyTargetHouseEnemy)
{
    if (this->IsScanLimited)
        threat = threat & 0xFFFFFFFD | 1;

    AbstractClass* result = TechnoClass::vf_241(threat, pCoord, onlyTargetHouseEnemy);

    if (this->IsScanLimited && result == NULL)
        this->IsScanLimited = false;

    return result;
}


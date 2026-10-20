// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Bodies and
//   member offsets derived directly from the disassembly; signatures
//   cross-checked against YRpp FootClass.h (consult-only, no LICENSE).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4D9920  FootClass::GreatestThreat        (__thiscall)
//   FUNCTION: GAMEMD 0x7104F0  FootClass::UpdatePassengerCoords (__thiscall)

#include "foot_class_more_methods.h"

// FUNCTION: GAMEMD 0x4D9920  (__thiscall)
// Scan-limited override of TechnoClass::GreatestThreat: when IsScanLimited, force
// the threat flags to (set Range, clear Area) before delegating; if the delegate
// finds no target while scan-limited, clear the scan-limit flag and return the
// (null) result.
//   MOV AL,[ESI+0x688] ; (IsScanLimited ? AND AL,0xFD ; OR AL,1) ; CALL 0x6F8DF0
AbstractClass* FootMore::GreatestThreat(unsigned int threat, CoordStruct* pCoord,
                                        bool onlyTargetHouseEnemy)
{
    if (this->IsScanLimited)
        threat = threat & 0xFFFFFFFD | 1;

    AbstractClass* result = this->GreatestThreatBase(threat, pCoord, onlyTargetHouseEnemy);

    if (this->IsScanLimited && result == NULL)
        this->IsScanLimited = false;

    return result;
}

// FUNCTION: GAMEMD 0x7104F0  (__thiscall)
// Snap every passenger's Location to the transport's own Location. Walks the
// passenger linked list (first via Passengers.GetFirstPassenger, thereafter via
// NextObject) while each node carries AbstractFlags bit 0x4.
//   CALL 0x473450 ; copy this->Location -> stack coord ; CALL [vtbl+0x1B4] per node
void FootMore::UpdatePassengerCoords()
{
    void* p = ((PassengersHost*)&this->Passengers)->GetFirstPassenger();

    // Reach the privately-inherited ObjectClass base at offset 0 (single
    // inheritance throughout) without tripping member-access control. The
    // struct copy forms the Location base pointer once, mirroring `add EDI,0x9C`.
    CoordStruct crd = ((ObjectClass*)(void*)this)->Location;

    if (p != NULL)
    {
        do
        {
            ((PassengerObj*)p)->SetLocation(&crd);
            p = ((ObjectClass*)p)->NextObject;
        }
        while (p != NULL && (((AbstractClass*)p)->AbstractFlags & 4) != 0);
    }
}

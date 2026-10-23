// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x6EC3A0 (Ghidra disasm).
//   Names cross-checked against YRpp (
//   every offset reconfirmed against the user's binary in the header).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6EC3A0   TeamClass::ScanLimit           (__thiscall)
//   FUNCTION: GAMEMD 0x6E9050   TeamClass::AssignMissionTarget (referenced; matched elsewhere)

#include "team_class_methods.h"

// FUNCTION: GAMEMD 0x6EC3A0  (__thiscall)
// Drop the team's mission target, then walk the member list flagging each as
// scan-limited.  For every member it fires the slot-242 (byte 0x3C8) virtual
// with argument 0, then sets IsScanLimited = 1.
void TeamClass::ScanLimit()
{
    this->AssignMissionTarget(0);

    for (FootClass* member = this->FirstUnit; member; member = member->NextTeamMember)
    {
        member->vf_242(0);
        member->IsScanLimited = 1;
    }
}

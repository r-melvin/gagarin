// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//
// Translation unit: MissionControlClass static/lookup helpers.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5B36E0   MissionControlClass::IsRecruitableMission (__fastcall)
//   FUNCTION: GAMEMD 0x5B3740   MissionControlClass::GetName              (__thiscall)
//   FUNCTION: GAMEMD 0x5B3910   MissionControlClass::FindIndex            (__fastcall)
//   GLOBAL:   GAMEMD 0xA8E3A8   MissionControlClass MissionControls[]
//   GLOBAL:   GAMEMD 0x816CAC   const char* MissionControlNames[]
//   GLOBAL:   GAMEMD 0x817474   "" (empty-name sentinel)
//   LIBRARY:  GAMEMD 0x7C8D20   _stricmp  (CRT; excluded from match target)
//
// Verified: IsRecruitableMission/FindIndex 100% via diff_retail.py; GetName
// 100% via raw_match.py (Ghidra carries no function record at 0x5B3740, so the
// instruction differ has no retail listing — the raw COFF byte-slice compare is
// the oracle there). FindIndex matches only when phrased as a head-controlled
// `for` over the *pointer bound* (signed (int) compare => JL): a do-while /
// for(;;)+break lets our SP6 cl rotate the loop and peel a second stricmp call
// site, which retail's SP5 cl does not.

#include "mission_class_methods.h"

// Reloc-normalised externals (addresses confirmed from the disasm above).
extern MissionControlClass MissionControls[];      // 0xA8E3A8
extern const char*         MissionControlNames[];  // 0x816CAC
int __cdecl MC_stricmp(const char* a, const char* b);  // 0x7C8D20

// FUNCTION: GAMEMD 0x5B36E0  MissionControlClass::IsRecruitableMission (__fastcall)
bool MissionControlClass::IsRecruitableMission(int mission)
{
    if (mission == -1)
        return true;
    return MissionControls[mission].Recruitable;
}

// FUNCTION: GAMEMD 0x5B3740  MissionControlClass::GetName (__thiscall)
const char* MissionControlClass::GetName()
{
    if (this->ArrayIndex == -1)
        return "";
    return MissionControlNames[this->ArrayIndex];
}

// FUNCTION: GAMEMD 0x5B3910  MissionControlClass::FindIndex (__fastcall)
int MissionControlClass::FindIndex(const char* name)
{
    if (name != 0) {
        int index = 0;
        for (const char** p = MissionControlNames;
             (int)p < (int)&MissionControlNames[32];
             ++p, ++index) {
            if (MC_stricmp(*p, name) == 0)
                return index;
        }
    }
    return -1;
}

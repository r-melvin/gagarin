// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x66D1F0.

#include "rules_class_wallmodel_methods.h"


// FUNCTION: GAMEMD 0x66D1F0  RulesClass::Read_WallModel (__thiscall, ret 0x4)
// Two scalars out of [WallModel]. Absent section means nothing is read and the
// existing values stand.
//
// The section test is CCINIClass::Exists (0x679F40) with its key defaulted to
// null, written out in flag form: a `bool ok = false` declared in the caller,
// assigned in both arms of the (constant-folded) `key == 0` chain, and tested
// after that chain closes. That is the only spelling that reproduces retail
// byte-for-byte. The header-style inline (`return GetSection(s) != 0;`),
// whether returned straight, through a callee local, or into a caller flag,
// gives the same `TEST EAX,EAX; SETNZ AL; TEST AL,AL; JZ` head but keeps EAX
// free for the first argument group (`MOV AL,[ESI+0x1850]; MOV ECX,[global]`,
// 73.7%); a bare pointer test folds the bool away entirely (28.9%). The
// caller-scope flag assigned inside a nested block is what makes cl keep EAX
// occupied across the first load group, so the defaults land in CL/EDX and the
// second group in ECX/EAX/EDX exactly as retail has them.
bool RulesClass::Read_WallModel(CCINIClass* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(WallModelSection) != 0;
    } else {
        ok = pINI->GetEntry(WallModelSection, key) != 0;
    }

    if (ok) {
        AlliedWallTransparency  = pINI->ReadBool(WallModelSection,
                                                 "AlliedWallTransparency",
                                                 AlliedWallTransparency);
        WallPenetratorThreshold = pINI->ReadDouble(WallModelSection,
                                                   "WallPenetratorThreshold",
                                                   WallPenetratorThreshold);
        return true;
    }

    return false;
}

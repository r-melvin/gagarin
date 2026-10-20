// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes diffed against retail gamemd.exe v1.001 at 0x673E80.

#include "rules_class_read_powerups_methods.h"

// FUNCTION: GAMEMD 0x673E80  RulesClass::Read_Powerups (__thiscall, ret 4)
//
// Read the [Powerups] section. Each of the nineteen crate-powerup keys has a
// comma separated value "money,anim,oneTimeOnly,weight"; the fields are
// tokenised in place and written into the four parallel global arrays. A
// weight written with a trailing '%' is scaled by 1/100. Reports whether the
// section exists at all.
//
// STRING: GAMEMD 0x83D4AC "0,NONE"
// STRING: GAMEMD 0x817F70 ","
// STRING: GAMEMD 0x825BF8 "yes"
// STRING: GAMEMD 0x825BF4 "no"
bool Rules_00673E80::Read_Powerups(CCINI_00673E80* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(PowerupsSection_007F0CD8) != 0;
    } else {
        ok = pINI->GetEntry(PowerupsSection_007F0CD8, key) != 0;
    }

    if (ok) {
        char buffer[0x80];
        for (int i = 0; i < 19; i++) {
            if (pINI->ReadString(PowerupsSection_007F0CD8,
                                 PowerupKeyNames_007E523C[i],
                                 "0,NONE", buffer, 0x80) != 0) {
                char* tok = P_strtok(buffer, ",");
                if (tok != 0) {
                    Strtrim_00727CF0(tok);
                    PowerupMoney_0081DA8C[i] = P_atoi(tok);
                }
                tok = P_strtok(0, ",");
                if (tok != 0) {
                    Strtrim_00727CF0(tok);
                    PowerupAnim_0081DAD8[i] = FUN_00422B20(tok);
                }
                tok = P_strtok(0, ",");
                if (tok != 0) {
                    Strtrim_00727CF0(tok);
                    if (P_stricmp(tok, "yes") == 0) {
                        PowerupFlag_0089ECC0[i] = 1;
                    } else if (P_stricmp(tok, "no") == 0) {
                        PowerupFlag_0089ECC0[i] = 0;
                    }
                }
                tok = P_strtok(0, ",");
                if (tok != 0) {
                    double value;
                    if (P_strchr(tok, '%') != 0) {
                        value = P_atof(tok) * 0.01;
                    } else {
                        Strtrim_00727CF0(tok);
                        value = P_atof(tok);
                    }
                    PowerupWeight_0089EC28[i] = value;
                }
            }
        }
        return true;
    }

    return false;
}

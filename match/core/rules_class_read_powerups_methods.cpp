// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
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

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x89EC28
double PowerupWeight_0089EC28[19];
// GLOBAL: GAMEMD 0x89ECC0
char PowerupFlag_0089ECC0[19];
// GLOBAL: GAMEMD 0x81DA8C
int PowerupMoney_0081DA8C[19] = {50, 20, 1, 3, 5, 5, 20, 1, 1, 10, 10, 10, 1, 3, 1, 1, 1, 1, 1};
// GLOBAL: GAMEMD 0x81DAD8
int PowerupAnim_0081DAD8[19] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
// GLOBAL: GAMEMD 0x817278
extern const char STR_00817278[] = "Tiberium";
// GLOBAL: GAMEMD 0x81746C
extern const char STR_0081746C[] = "Unit";
// GLOBAL: GAMEMD 0x81D98C
extern const char STR_0081D98C[] = "Pod";
// GLOBAL: GAMEMD 0x81D990
extern const char STR_0081D990[] = "Gas";
// GLOBAL: GAMEMD 0x81D994
extern const char STR_0081D994[] = "IonStorm";
// GLOBAL: GAMEMD 0x81D9A0
extern const char STR_0081D9A0[] = "Veteran";
// GLOBAL: GAMEMD 0x81D9A8
extern const char STR_0081D9A8[] = "Invulnerability";
// GLOBAL: GAMEMD 0x81D9B8
extern const char STR_0081D9B8[] = "ICBM";
// GLOBAL: GAMEMD 0x81D9C0
extern const char STR_0081D9C0[] = "Firepower";
// GLOBAL: GAMEMD 0x81D9CC
extern const char STR_0081D9CC[] = "Speed";
// GLOBAL: GAMEMD 0x81D9D4
extern const char STR_0081D9D4[] = "Armor";
// GLOBAL: GAMEMD 0x81D9DC
extern const char STR_0081D9DC[] = "Reveal";
// GLOBAL: GAMEMD 0x81D9E4
extern const char STR_0081D9E4[] = "Darkness";
// GLOBAL: GAMEMD 0x81D9F0
extern const char STR_0081D9F0[] = "Squad";
// GLOBAL: GAMEMD 0x81D9F8
extern const char STR_0081D9F8[] = "Napalm";
// GLOBAL: GAMEMD 0x81DA00
extern const char STR_0081DA00[] = "Explosion";
// GLOBAL: GAMEMD 0x81DA0C
extern const char STR_0081DA0C[] = "Cloak";
// GLOBAL: GAMEMD 0x81DA14
extern const char STR_0081DA14[] = "HealBase";
// GLOBAL: GAMEMD 0x81DA20
extern const char STR_0081DA20[] = "Money";
// GLOBAL: GAMEMD 0x839D98
extern const char STR_00839D98[] = "Powerups";
// GLOBAL: GAMEMD 0x817278
extern const char STR_00817278[];
// GLOBAL: GAMEMD 0x81746C
extern const char STR_0081746C[];
// GLOBAL: GAMEMD 0x81D98C
extern const char STR_0081D98C[];
// GLOBAL: GAMEMD 0x81D990
extern const char STR_0081D990[];
// GLOBAL: GAMEMD 0x81D994
extern const char STR_0081D994[];
// GLOBAL: GAMEMD 0x81D9A0
extern const char STR_0081D9A0[];
// GLOBAL: GAMEMD 0x81D9A8
extern const char STR_0081D9A8[];
// GLOBAL: GAMEMD 0x81D9B8
extern const char STR_0081D9B8[];
// GLOBAL: GAMEMD 0x81D9C0
extern const char STR_0081D9C0[];
// GLOBAL: GAMEMD 0x81D9CC
extern const char STR_0081D9CC[];
// GLOBAL: GAMEMD 0x81D9D4
extern const char STR_0081D9D4[];
// GLOBAL: GAMEMD 0x81D9DC
extern const char STR_0081D9DC[];
// GLOBAL: GAMEMD 0x81D9E4
extern const char STR_0081D9E4[];
// GLOBAL: GAMEMD 0x81D9F0
extern const char STR_0081D9F0[];
// GLOBAL: GAMEMD 0x81D9F8
extern const char STR_0081D9F8[];
// GLOBAL: GAMEMD 0x81DA00
extern const char STR_0081DA00[];
// GLOBAL: GAMEMD 0x81DA0C
extern const char STR_0081DA0C[];
// GLOBAL: GAMEMD 0x81DA14
extern const char STR_0081DA14[];
// GLOBAL: GAMEMD 0x81DA20
extern const char STR_0081DA20[];
// GLOBAL: GAMEMD 0x839D98
extern const char STR_00839D98[];
// END defined globals

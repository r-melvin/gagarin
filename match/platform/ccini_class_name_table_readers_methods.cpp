// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4748A0, 0x474940,
//   0x474A90, 0x474DA0, 0x474E40 and 0x474EE0.

#include "ccini_class_name_table_readers_methods.h"

// FUNCTION: GAMEMD 0x4748A0
//
// Read a pip by name. The caller's default index is spelled as that row's
// own name and handed to ReadString as the default, so an absent key round
// trips through the table rather than being special-cased; an unrecognised
// name falls back on 1 rather than on the caller's value.
int CCINI_004748A0::ReadPip(const char* section, const char* key, int defaultValue)
{
    char buffer[32];

    ReadString(section, key, DAT_0081B958[defaultValue].Name, buffer,
               sizeof(buffer));

    for (int i = 0; i < 11; ++i) {
        if (FUN_007C8D20(buffer, DAT_0081B958[i].Name) == 0) {
            return DAT_0081B958[i].Value;
        }
    }

    return 1;
}

// FUNCTION: GAMEMD 0x474940
//
// Read a pip scale. Unlike the pip reader this one has no default name at
// all: an empty or missing key gives the caller's value back untouched, and
// an unrecognised name gives 0.
int CCINI_004748A0::ReadPipScale(const char* section, const char* key,
                                 int defaultValue)
{
    char buffer[32];

    if (ReadString(section, key, STR_00889F64, buffer, sizeof(buffer)) > 0) {
        for (int i = 0; i < 5; ++i) {
            if (FUN_007C8D20(buffer, DAT_0081B9B0[i].Name) == 0) {
                return DAT_0081B9B0[i].Value;
            }
        }

        return 0;
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x474A90
//
// Read a colour scheme by name. The table is a live array rather than a
// static one, so both the count and the base are re-read on every turn of
// the loop, and a scheme whose flag word is 1 is skipped even when its name
// matches. An unrecognised name gives the caller's index back.
int CCINI_004748A0::ReadColorScheme(const char* section, const char* key,
                                    int defaultValue)
{
    char buffer[32];

    ReadString(section, key, DAT_00B054D4[defaultValue]->Name, buffer,
               sizeof(buffer));

    for (int i = 0; i < DAT_00B054E0; ++i) {
        if (FUN_007C8D20(DAT_00B054D4[i]->Name, buffer) == 0 &&
            DAT_00B054D4[i]->Flags != 1) {
            return i;
        }
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x474DA0
//
// The pip reader's shape over the building-foundation table, failing to 0.
int CCINI_004748A0::ReadFoundation(const char* section, const char* key,
                                   int defaultValue)
{
    char buffer[32];

    ReadString(section, key, DAT_0081B9D8[defaultValue].Name, buffer,
               sizeof(buffer));

    for (int i = 0; i < 22; ++i) {
        if (FUN_007C8D20(buffer, DAT_0081B9D8[i].Name) == 0) {
            return DAT_0081B9D8[i].Value;
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x474E40
//
// A bare name array rather than a pair table, so the answer is the index
// itself; an unrecognised name gives -1.
int CCINI_004748A0::ReadMovementZone(const char* section, const char* key,
                                     int defaultValue)
{
    char buffer[32];

    ReadString(section, key, DAT_0081BA88[defaultValue], buffer, sizeof(buffer));

    for (int i = 0; i < 13; ++i) {
        if (FUN_007C8D20(buffer, DAT_0081BA88[i]) == 0) {
            return i;
        }
    }

    return -1;
}

// FUNCTION: GAMEMD 0x474EE0
//
// The movement-zone reader's shape over the 73 super-weapon action names,
// failing to 0 rather than to -1.
int CCINI_004748A0::ReadSuperWeaponAction(const char* section, const char* key,
                                          int defaultValue)
{
    char buffer[32];

    ReadString(section, key, DAT_007E4C50[defaultValue], buffer, sizeof(buffer));

    for (int i = 0; i < 73; ++i) {
        if (FUN_007C8D20(buffer, DAT_007E4C50[i]) == 0) {
            return i;
        }
    }

    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x816DBC
extern const char STR_00816DBC[] = "Repair";
// GLOBAL: GAMEMD 0x816DDC
extern const char STR_00816DDC[] = "Sabotage";
// GLOBAL: GAMEMD 0x816E1C
extern const char STR_00816E1C[] = "Harvest";
// GLOBAL: GAMEMD 0x816E24
extern const char STR_00816E24[] = "Eaten";
// GLOBAL: GAMEMD 0x816E2C
extern const char STR_00816E2C[] = "Capture";
// GLOBAL: GAMEMD 0x816E34
extern const char STR_00816E34[] = "Enter";
// GLOBAL: GAMEMD 0x816E5C
extern const char STR_00816E5C[] = "Move";
// GLOBAL: GAMEMD 0x816E64
extern const char STR_00816E64[] = "Attack";
// GLOBAL: GAMEMD 0x817154
extern const char STR_00817154[] = "Airstrike";
// GLOBAL: GAMEMD 0x81859C
extern const char STR_0081859C[] = "Damage";
// GLOBAL: GAMEMD 0x81AB68
extern const char STR_0081AB68[] = "TogglePower";
// GLOBAL: GAMEMD 0x81BC5C
extern const char STR_0081BC5C[] = "PsychicReveal";
// GLOBAL: GAMEMD 0x81BC6C
extern const char STR_0081BC6C[] = "NoForceShield";
// GLOBAL: GAMEMD 0x81BC7C
extern const char STR_0081BC7C[] = "ForceShield";
// GLOBAL: GAMEMD 0x81BC88
extern const char STR_0081BC88[] = "GeneticConverter";
// GLOBAL: GAMEMD 0x81BC9C
extern const char STR_0081BC9C[] = "SpyPlane";
// GLOBAL: GAMEMD 0x81BCA8
extern const char STR_0081BCA8[] = "PsychicDominator";
// GLOBAL: GAMEMD 0x81BCBC
extern const char STR_0081BCBC[] = "AmerParaDrop";
// GLOBAL: GAMEMD 0x81BCCC
extern const char STR_0081BCCC[] = "Demolish";
// GLOBAL: GAMEMD 0x81BCD8
extern const char STR_0081BCD8[] = "AttackMoveTar";
// GLOBAL: GAMEMD 0x81BCE8
extern const char STR_0081BCE8[] = "AttackMoveNav";
// GLOBAL: GAMEMD 0x81BCF8
extern const char STR_0081BCF8[] = "SelectBeacon";
// GLOBAL: GAMEMD 0x81BD08
extern const char STR_0081BD08[] = "PlaceBeacon";
// GLOBAL: GAMEMD 0x81BD14
extern const char STR_0081BD14[] = "AttackSupport";
// GLOBAL: GAMEMD 0x81BD24
extern const char STR_0081BD24[] = "SelectNode";
// GLOBAL: GAMEMD 0x81BD30
extern const char STR_0081BD30[] = "DisarmBomb";
// GLOBAL: GAMEMD 0x81BD3C
extern const char STR_0081BD3C[] = "DetonateAll";
// GLOBAL: GAMEMD 0x81BD48
extern const char STR_0081BD48[] = "Detonate";
// GLOBAL: GAMEMD 0x81BD54
extern const char STR_0081BD54[] = "NoIvanBomb";
// GLOBAL: GAMEMD 0x81BD60
extern const char STR_0081BD60[] = "IvanBomb";
// GLOBAL: GAMEMD 0x81BD6C
extern const char STR_0081BD6C[] = "AreaAttack";
// GLOBAL: GAMEMD 0x81BD78
extern const char STR_0081BD78[] = "PatrolWaypoint";
// GLOBAL: GAMEMD 0x81BD88
extern const char STR_0081BD88[] = "EnterWaypoint";
// GLOBAL: GAMEMD 0x81BD98
extern const char STR_0081BD98[] = "AttackWaypoint";
// GLOBAL: GAMEMD 0x81BDA8
extern const char STR_0081BDA8[] = "DragWaypoint";
// GLOBAL: GAMEMD 0x81BDB8
extern const char STR_0081BDB8[] = "LoopWaypointPath";
// GLOBAL: GAMEMD 0x81BDCC
extern const char STR_0081BDCC[] = "SelectWaypoint";
// GLOBAL: GAMEMD 0x81BDDC
extern const char STR_0081BDDC[] = "FollowWaypoint";
// GLOBAL: GAMEMD 0x81BDEC
extern const char STR_0081BDEC[] = "EnterWaypointMode";
// GLOBAL: GAMEMD 0x81BE0C
extern const char STR_0081BE0C[] = "PlaceWaypoint";
// GLOBAL: GAMEMD 0x81BE1C
extern const char STR_0081BE1C[] = "ParaDrop";
// GLOBAL: GAMEMD 0x81BE28
extern const char STR_0081BE28[] = "ChronoWarp";
// GLOBAL: GAMEMD 0x81BE34
extern const char STR_0081BE34[] = "ChronoSphere";
// GLOBAL: GAMEMD 0x81BE44
extern const char STR_0081BE44[] = "LightningStorm";
// GLOBAL: GAMEMD 0x81BE54
extern const char STR_0081BE54[] = "IronCurtain";
// GLOBAL: GAMEMD 0x81BE60
extern const char STR_0081BE60[] = "NoEnterTunnel";
// GLOBAL: GAMEMD 0x81BE70
extern const char STR_0081BE70[] = "EnterTunnel";
// GLOBAL: GAMEMD 0x81BE7C
extern const char STR_0081BE7C[] = "NoTogglePower";
// GLOBAL: GAMEMD 0x81BE8C
extern const char STR_0081BE8C[] = "NoGRepair";
// GLOBAL: GAMEMD 0x81BE98
extern const char STR_0081BE98[] = "NoEnter";
// GLOBAL: GAMEMD 0x81BEA0
extern const char STR_0081BEA0[] = "NoDeploy";
// GLOBAL: GAMEMD 0x81BEAC
extern const char STR_0081BEAC[] = "GRepair";
// GLOBAL: GAMEMD 0x81BEB4
extern const char STR_0081BEB4[] = "Heal";
// GLOBAL: GAMEMD 0x81BEBC
extern const char STR_0081BEBC[] = "GuardArea";
// GLOBAL: GAMEMD 0x81BEC8
extern const char STR_0081BEC8[] = "DontUse8";
// GLOBAL: GAMEMD 0x81BED4
extern const char STR_0081BED4[] = "DontUse7";
// GLOBAL: GAMEMD 0x81BEE0
extern const char STR_0081BEE0[] = "DontUse6";
// GLOBAL: GAMEMD 0x81BEEC
extern const char STR_0081BEEC[] = "DontUse5";
// GLOBAL: GAMEMD 0x81BEF8
extern const char STR_0081BEF8[] = "DontUse4";
// GLOBAL: GAMEMD 0x81BF04
extern const char STR_0081BF04[] = "Nuke";
// GLOBAL: GAMEMD 0x81BF0C
extern const char STR_0081BF0C[] = "DontUse3";
// GLOBAL: GAMEMD 0x81BF18
extern const char STR_0081BF18[] = "DontUse2";
// GLOBAL: GAMEMD 0x81BF24
extern const char STR_0081BF24[] = "Tote";
// GLOBAL: GAMEMD 0x81BF2C
extern const char STR_0081BF2C[] = "NoRepair";
// GLOBAL: GAMEMD 0x81BF38
extern const char STR_0081BF38[] = "NoSell";
// GLOBAL: GAMEMD 0x81BF40
extern const char STR_0081BF40[] = "SellUnit";
// GLOBAL: GAMEMD 0x81BF4C
extern const char STR_0081BF4C[] = "Sell";
// GLOBAL: GAMEMD 0x81BF54
extern const char STR_0081BF54[] = "ToggleSelect";
// GLOBAL: GAMEMD 0x81BF64
extern const char STR_0081BF64[] = "Select";
// GLOBAL: GAMEMD 0x81BF6C
extern const char STR_0081BF6C[] = "Self";
// GLOBAL: GAMEMD 0x81BF74
extern const char STR_0081BF74[] = "NoMove";
// GLOBAL: GAMEMD 0x816DBC
extern const char STR_00816DBC[];
// GLOBAL: GAMEMD 0x816DDC
extern const char STR_00816DDC[];
// GLOBAL: GAMEMD 0x816E1C
extern const char STR_00816E1C[];
// GLOBAL: GAMEMD 0x816E24
extern const char STR_00816E24[];
// GLOBAL: GAMEMD 0x816E2C
extern const char STR_00816E2C[];
// GLOBAL: GAMEMD 0x816E34
extern const char STR_00816E34[];
// GLOBAL: GAMEMD 0x816E5C
extern const char STR_00816E5C[];
// GLOBAL: GAMEMD 0x816E64
extern const char STR_00816E64[];
// GLOBAL: GAMEMD 0x817154
extern const char STR_00817154[];
// GLOBAL: GAMEMD 0x81859C
extern const char STR_0081859C[];
// GLOBAL: GAMEMD 0x81AB68
extern const char STR_0081AB68[];
// GLOBAL: GAMEMD 0x81BC5C
extern const char STR_0081BC5C[];
// GLOBAL: GAMEMD 0x81BC6C
extern const char STR_0081BC6C[];
// GLOBAL: GAMEMD 0x81BC7C
extern const char STR_0081BC7C[];
// GLOBAL: GAMEMD 0x81BC88
extern const char STR_0081BC88[];
// GLOBAL: GAMEMD 0x81BC9C
extern const char STR_0081BC9C[];
// GLOBAL: GAMEMD 0x81BCA8
extern const char STR_0081BCA8[];
// GLOBAL: GAMEMD 0x81BCBC
extern const char STR_0081BCBC[];
// GLOBAL: GAMEMD 0x81BCCC
extern const char STR_0081BCCC[];
// GLOBAL: GAMEMD 0x81BCD8
extern const char STR_0081BCD8[];
// GLOBAL: GAMEMD 0x81BCE8
extern const char STR_0081BCE8[];
// GLOBAL: GAMEMD 0x81BCF8
extern const char STR_0081BCF8[];
// GLOBAL: GAMEMD 0x81BD08
extern const char STR_0081BD08[];
// GLOBAL: GAMEMD 0x81BD14
extern const char STR_0081BD14[];
// GLOBAL: GAMEMD 0x81BD24
extern const char STR_0081BD24[];
// GLOBAL: GAMEMD 0x81BD30
extern const char STR_0081BD30[];
// GLOBAL: GAMEMD 0x81BD3C
extern const char STR_0081BD3C[];
// GLOBAL: GAMEMD 0x81BD48
extern const char STR_0081BD48[];
// GLOBAL: GAMEMD 0x81BD54
extern const char STR_0081BD54[];
// GLOBAL: GAMEMD 0x81BD60
extern const char STR_0081BD60[];
// GLOBAL: GAMEMD 0x81BD6C
extern const char STR_0081BD6C[];
// GLOBAL: GAMEMD 0x81BD78
extern const char STR_0081BD78[];
// GLOBAL: GAMEMD 0x81BD88
extern const char STR_0081BD88[];
// GLOBAL: GAMEMD 0x81BD98
extern const char STR_0081BD98[];
// GLOBAL: GAMEMD 0x81BDA8
extern const char STR_0081BDA8[];
// GLOBAL: GAMEMD 0x81BDB8
extern const char STR_0081BDB8[];
// GLOBAL: GAMEMD 0x81BDCC
extern const char STR_0081BDCC[];
// GLOBAL: GAMEMD 0x81BDDC
extern const char STR_0081BDDC[];
// GLOBAL: GAMEMD 0x81BDEC
extern const char STR_0081BDEC[];
// GLOBAL: GAMEMD 0x81BE00
extern const char STR_0081BE00[];
// GLOBAL: GAMEMD 0x81BE0C
extern const char STR_0081BE0C[];
// GLOBAL: GAMEMD 0x81BE1C
extern const char STR_0081BE1C[];
// GLOBAL: GAMEMD 0x81BE28
extern const char STR_0081BE28[];
// GLOBAL: GAMEMD 0x81BE34
extern const char STR_0081BE34[];
// GLOBAL: GAMEMD 0x81BE44
extern const char STR_0081BE44[];
// GLOBAL: GAMEMD 0x81BE54
extern const char STR_0081BE54[];
// GLOBAL: GAMEMD 0x81BE60
extern const char STR_0081BE60[];
// GLOBAL: GAMEMD 0x81BE70
extern const char STR_0081BE70[];
// GLOBAL: GAMEMD 0x81BE7C
extern const char STR_0081BE7C[];
// GLOBAL: GAMEMD 0x81BE8C
extern const char STR_0081BE8C[];
// GLOBAL: GAMEMD 0x81BE98
extern const char STR_0081BE98[];
// GLOBAL: GAMEMD 0x81BEA0
extern const char STR_0081BEA0[];
// GLOBAL: GAMEMD 0x81BEAC
extern const char STR_0081BEAC[];
// GLOBAL: GAMEMD 0x81BEB4
extern const char STR_0081BEB4[];
// GLOBAL: GAMEMD 0x81BEBC
extern const char STR_0081BEBC[];
// GLOBAL: GAMEMD 0x81BEC8
extern const char STR_0081BEC8[];
// GLOBAL: GAMEMD 0x81BED4
extern const char STR_0081BED4[];
// GLOBAL: GAMEMD 0x81BEE0
extern const char STR_0081BEE0[];
// GLOBAL: GAMEMD 0x81BEEC
extern const char STR_0081BEEC[];
// GLOBAL: GAMEMD 0x81BEF8
extern const char STR_0081BEF8[];
// GLOBAL: GAMEMD 0x81BF04
extern const char STR_0081BF04[];
// GLOBAL: GAMEMD 0x81BF0C
extern const char STR_0081BF0C[];
// GLOBAL: GAMEMD 0x81BF18
extern const char STR_0081BF18[];
// GLOBAL: GAMEMD 0x81BF24
extern const char STR_0081BF24[];
// GLOBAL: GAMEMD 0x81BF2C
extern const char STR_0081BF2C[];
// GLOBAL: GAMEMD 0x81BF38
extern const char STR_0081BF38[];
// GLOBAL: GAMEMD 0x81BF40
extern const char STR_0081BF40[];
// GLOBAL: GAMEMD 0x81BF4C
extern const char STR_0081BF4C[];
// GLOBAL: GAMEMD 0x81BF54
extern const char STR_0081BF54[];
// GLOBAL: GAMEMD 0x81BF64
extern const char STR_0081BF64[];
// GLOBAL: GAMEMD 0x81BF6C
extern const char STR_0081BF6C[];
// GLOBAL: GAMEMD 0x81BF74
extern const char STR_0081BF74[];
// GLOBAL: GAMEMD 0x816DBC
extern const char STR_00816DBC[];
// GLOBAL: GAMEMD 0x816DDC
extern const char STR_00816DDC[];
// GLOBAL: GAMEMD 0x816E1C
extern const char STR_00816E1C[];
// GLOBAL: GAMEMD 0x816E24
extern const char STR_00816E24[];
// GLOBAL: GAMEMD 0x816E2C
extern const char STR_00816E2C[];
// GLOBAL: GAMEMD 0x816E34
extern const char STR_00816E34[];
// GLOBAL: GAMEMD 0x816E5C
extern const char STR_00816E5C[];
// GLOBAL: GAMEMD 0x816E64
extern const char STR_00816E64[];
// GLOBAL: GAMEMD 0x817154
extern const char STR_00817154[];
// GLOBAL: GAMEMD 0x817F64
extern const char STR_00817F64[];
// GLOBAL: GAMEMD 0x81859C
extern const char STR_0081859C[];
// GLOBAL: GAMEMD 0x81AB68
extern const char STR_0081AB68[];
// GLOBAL: GAMEMD 0x81BC5C
extern const char STR_0081BC5C[];
// GLOBAL: GAMEMD 0x81BC6C
extern const char STR_0081BC6C[];
// GLOBAL: GAMEMD 0x81BC7C
extern const char STR_0081BC7C[];
// GLOBAL: GAMEMD 0x81BC88
extern const char STR_0081BC88[];
// GLOBAL: GAMEMD 0x81BC9C
extern const char STR_0081BC9C[];
// GLOBAL: GAMEMD 0x81BCA8
extern const char STR_0081BCA8[];
// GLOBAL: GAMEMD 0x81BCBC
extern const char STR_0081BCBC[];
// GLOBAL: GAMEMD 0x81BCCC
extern const char STR_0081BCCC[];
// GLOBAL: GAMEMD 0x81BCD8
extern const char STR_0081BCD8[];
// GLOBAL: GAMEMD 0x81BCE8
extern const char STR_0081BCE8[];
// GLOBAL: GAMEMD 0x81BCF8
extern const char STR_0081BCF8[];
// GLOBAL: GAMEMD 0x81BD08
extern const char STR_0081BD08[];
// GLOBAL: GAMEMD 0x81BD14
extern const char STR_0081BD14[];
// GLOBAL: GAMEMD 0x81BD24
extern const char STR_0081BD24[];
// GLOBAL: GAMEMD 0x81BD30
extern const char STR_0081BD30[];
// GLOBAL: GAMEMD 0x81BD3C
extern const char STR_0081BD3C[];
// GLOBAL: GAMEMD 0x81BD48
extern const char STR_0081BD48[];
// GLOBAL: GAMEMD 0x81BD54
extern const char STR_0081BD54[];
// GLOBAL: GAMEMD 0x81BD60
extern const char STR_0081BD60[];
// GLOBAL: GAMEMD 0x81BD6C
extern const char STR_0081BD6C[];
// GLOBAL: GAMEMD 0x81BD78
extern const char STR_0081BD78[];
// GLOBAL: GAMEMD 0x81BD88
extern const char STR_0081BD88[];
// GLOBAL: GAMEMD 0x81BD98
extern const char STR_0081BD98[];
// GLOBAL: GAMEMD 0x81BDA8
extern const char STR_0081BDA8[];
// GLOBAL: GAMEMD 0x81BDB8
extern const char STR_0081BDB8[];
// GLOBAL: GAMEMD 0x81BDCC
extern const char STR_0081BDCC[];
// GLOBAL: GAMEMD 0x81BDDC
extern const char STR_0081BDDC[];
// GLOBAL: GAMEMD 0x81BDEC
extern const char STR_0081BDEC[];
// GLOBAL: GAMEMD 0x81BE00
extern const char STR_0081BE00[];
// GLOBAL: GAMEMD 0x81BE0C
extern const char STR_0081BE0C[];
// GLOBAL: GAMEMD 0x81BE1C
extern const char STR_0081BE1C[];
// GLOBAL: GAMEMD 0x81BE28
extern const char STR_0081BE28[];
// GLOBAL: GAMEMD 0x81BE34
extern const char STR_0081BE34[];
// GLOBAL: GAMEMD 0x81BE44
extern const char STR_0081BE44[];
// GLOBAL: GAMEMD 0x81BE54
extern const char STR_0081BE54[];
// GLOBAL: GAMEMD 0x81BE60
extern const char STR_0081BE60[];
// GLOBAL: GAMEMD 0x81BE70
extern const char STR_0081BE70[];
// GLOBAL: GAMEMD 0x81BE7C
extern const char STR_0081BE7C[];
// GLOBAL: GAMEMD 0x81BE8C
extern const char STR_0081BE8C[];
// GLOBAL: GAMEMD 0x81BE98
extern const char STR_0081BE98[];
// GLOBAL: GAMEMD 0x81BEA0
extern const char STR_0081BEA0[];
// GLOBAL: GAMEMD 0x81BEAC
extern const char STR_0081BEAC[];
// GLOBAL: GAMEMD 0x81BEB4
extern const char STR_0081BEB4[];
// GLOBAL: GAMEMD 0x81BEBC
extern const char STR_0081BEBC[];
// GLOBAL: GAMEMD 0x81BEC8
extern const char STR_0081BEC8[];
// GLOBAL: GAMEMD 0x81BED4
extern const char STR_0081BED4[];
// GLOBAL: GAMEMD 0x81BEE0
extern const char STR_0081BEE0[];
// GLOBAL: GAMEMD 0x81BEEC
extern const char STR_0081BEEC[];
// GLOBAL: GAMEMD 0x81BEF8
extern const char STR_0081BEF8[];
// GLOBAL: GAMEMD 0x81BF04
extern const char STR_0081BF04[];
// GLOBAL: GAMEMD 0x81BF0C
extern const char STR_0081BF0C[];
// GLOBAL: GAMEMD 0x81BF18
extern const char STR_0081BF18[];
// GLOBAL: GAMEMD 0x81BF24
extern const char STR_0081BF24[];
// GLOBAL: GAMEMD 0x81BF2C
extern const char STR_0081BF2C[];
// GLOBAL: GAMEMD 0x81BF38
extern const char STR_0081BF38[];
// GLOBAL: GAMEMD 0x81BF40
extern const char STR_0081BF40[];
// GLOBAL: GAMEMD 0x81BF4C
extern const char STR_0081BF4C[];
// GLOBAL: GAMEMD 0x81BF54
extern const char STR_0081BF54[];
// GLOBAL: GAMEMD 0x81BF64
extern const char STR_0081BF64[];
// GLOBAL: GAMEMD 0x81BF6C
extern const char STR_0081BF6C[];
// GLOBAL: GAMEMD 0x81BF74
extern const char STR_0081BF74[];
// GLOBAL: GAMEMD 0x7E4C50
extern const char* DAT_007E4C50[73] = {STR_00817F64, STR_00816E5C, STR_0081BF74, STR_00816E34, STR_0081BF6C, STR_00816E64, STR_00816E1C, STR_0081BF64, STR_0081BF54, STR_00816E2C, STR_00816E24, STR_00816DBC, STR_0081BF4C, STR_0081BF40, STR_0081BF38, STR_0081BF2C, STR_00816DDC, STR_0081BF24, STR_0081BF18, STR_0081BF0C, STR_0081BF04, STR_0081BEF8, STR_0081BEEC, STR_0081BEE0, STR_0081BED4, STR_0081BEC8, STR_0081BEBC, STR_0081BEB4, STR_0081859C, STR_0081BEAC, STR_0081BEA0, STR_0081BE98, STR_0081BE8C, STR_0081AB68, STR_0081BE7C, STR_0081BE70, STR_0081BE60, STR_0081BE54, STR_0081BE44, STR_0081BE34, STR_0081BE28, STR_0081BE1C, STR_0081BE0C, STR_0081BE00, STR_0081BDEC, STR_0081BDDC, STR_0081BDCC, STR_0081BDB8, STR_0081BDA8, STR_0081BD98, STR_0081BD88, STR_0081BD78, STR_0081BD6C, STR_0081BD60, STR_0081BD54, STR_0081BD48, STR_0081BD3C, STR_0081BD30, STR_0081BD24, STR_0081BD14, STR_0081BD08, STR_0081BCF8, STR_0081BCE8, STR_0081BCD8, STR_0081BCCC, STR_0081BCBC, STR_0081BCA8, STR_0081BC9C, STR_0081BC88, STR_0081BC7C, STR_0081BC6C, STR_00817154, STR_0081BC5C};
// END defined globals

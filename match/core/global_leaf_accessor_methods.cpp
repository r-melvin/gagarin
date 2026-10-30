// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Leaf bodies that repeat byte for byte at several addresses and touch only
// globals: store of the ECX argument, indexed table reads, constant stores,
// and a two-value test. Each address binds to its own global (named by
// retail address, typed only as far as the instructions show) and was
// verified separately. Record structs name only the fields the bodies read.

extern int DAT_00816108;
#include "../_layout/rec12_008b4040.h"
extern Rec12_008B4040 DAT_008B4040[];
#include "../_layout/rec12_008b3f38.h"
extern Rec12_008B3F38 DAT_008B3F38[];
#include "../_layout/rec12_008b3fc8.h"
extern Rec12_008B3FC8 DAT_008B3FC8[];
extern unsigned char DAT_00A9FAB4;
extern unsigned char DAT_00ABCD58;
extern int DAT_00ABED0C;
extern int DAT_00ABF168[];
#include "../_layout/rec28_0082d028.h"
extern Rec28_0082D028 DAT_0082D028[];
extern int DAT_00AC4B80;
extern int DAT_00AC4C90;
extern int DAT_00AC4C38;
extern int DAT_00AC4BF0;
extern int DAT_007F0248[];
#include "../_layout/rec16_007f0998.h"
extern Rec16_007F0998 DAT_007F0998[];
extern int DAT_00B0CB78[];
extern int DAT_008449F8[];
extern unsigned char DAT_00B0FE58;
extern unsigned char DAT_008464AC;
extern int DAT_00B780A0;

// FUNCTION: GAMEMD 0x00406730
void FUN_00406730()
{
    DAT_00816108 = 0;
}


// FUNCTION: GAMEMD 0x0058BC20
void FUN_0058BC20()
{
    DAT_00ABED0C = 0;
}

// FUNCTION: GAMEMD 0x005BC450
int FUN_005BC450(int index)
{
    return DAT_00ABF168[index];
}

// FUNCTION: GAMEMD 0x005BE970
int __stdcall FUN_005BE970(int index)
{
    return DAT_0082D028[index].f00;
}

// FUNCTION: GAMEMD 0x005BE990
int __stdcall FUN_005BE990(int index)
{
    return DAT_0082D028[index].f04;
}


// FUNCTION: GAMEMD 0x00645BA0
int FUN_00645BA0(int index)
{
    return DAT_007F0248[index];
}


// FUNCTION: GAMEMD 0x006CFD30
int FUN_006CFD30(int index)
{
    return DAT_00B0CB78[index];
}

// FUNCTION: GAMEMD 0x007271D0
int FUN_007271D0(int index)
{
    return DAT_008449F8[index];
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABED0C
int DAT_00ABED0C;
// GLOBAL: GAMEMD 0x816108
int DAT_00816108 = 1;
// GLOBAL: GAMEMD 0x844A04
extern const char STR_00844A04[] = "Persistent";
// GLOBAL: GAMEMD 0x844A10
extern const char STR_00844A10[] = "Semi-persistant";
// GLOBAL: GAMEMD 0x844A20
extern const char STR_00844A20[] = "Volatile";
// GLOBAL: GAMEMD 0x8173D0
extern const char STR_008173D0[];
// GLOBAL: GAMEMD 0x83724C
extern const char STR_0083724C[];
// GLOBAL: GAMEMD 0x837260
extern const char STR_00837260[];
// GLOBAL: GAMEMD 0x83727C
extern const char STR_0083727C[];
// GLOBAL: GAMEMD 0x837290
extern const char STR_00837290[];
// GLOBAL: GAMEMD 0x8372A0
extern const char STR_008372A0[];
// GLOBAL: GAMEMD 0x8372B0
extern const char STR_008372B0[];
// GLOBAL: GAMEMD 0x8372BC
extern const char STR_008372BC[];
// GLOBAL: GAMEMD 0x8372CC
extern const char STR_008372CC[];
// GLOBAL: GAMEMD 0x8372D8
extern const char STR_008372D8[];
// GLOBAL: GAMEMD 0x8372E8
extern const char STR_008372E8[];
// GLOBAL: GAMEMD 0x8372F4
extern const char STR_008372F4[];
// GLOBAL: GAMEMD 0x844A04
extern const char STR_00844A04[];
// GLOBAL: GAMEMD 0x844A10
extern const char STR_00844A10[];
// GLOBAL: GAMEMD 0x844A20
extern const char STR_00844A20[];
// GLOBAL: GAMEMD 0x8173D0
extern const char STR_008173D0[];
// GLOBAL: GAMEMD 0x83724C
extern const char STR_0083724C[];
// GLOBAL: GAMEMD 0x837260
extern const char STR_00837260[];
// GLOBAL: GAMEMD 0x83727C
extern const char STR_0083727C[];
// GLOBAL: GAMEMD 0x837290
extern const char STR_00837290[];
// GLOBAL: GAMEMD 0x8372A0
extern const char STR_008372A0[];
// GLOBAL: GAMEMD 0x8372B0
extern const char STR_008372B0[];
// GLOBAL: GAMEMD 0x8372BC
extern const char STR_008372BC[];
// GLOBAL: GAMEMD 0x8372CC
extern const char STR_008372CC[];
// GLOBAL: GAMEMD 0x8372D8
extern const char STR_008372D8[];
// GLOBAL: GAMEMD 0x8372E8
extern const char STR_008372E8[];
// GLOBAL: GAMEMD 0x8372F4
extern const char STR_008372F4[];
// GLOBAL: GAMEMD 0x844A04
extern const char STR_00844A04[];
// GLOBAL: GAMEMD 0x844A10
extern const char STR_00844A10[];
// GLOBAL: GAMEMD 0x844A20
extern const char STR_00844A20[];
// END defined globals

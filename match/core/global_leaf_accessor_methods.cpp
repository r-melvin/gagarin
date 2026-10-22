// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Leaf bodies that repeat byte for byte at several addresses and touch only
// globals: store of the ECX argument, indexed table reads, constant stores,
// and a two-value test. Each address binds to its own global (named by
// retail address, typed only as far as the instructions show) and was
// verified separately. Record structs name only the fields the bodies read.

extern int DAT_00816108;
struct Rec12_008B4040 { int key; int unknown_04; int unknown_08; };
extern Rec12_008B4040 DAT_008B4040[];
struct Rec12_008B3F38 { int key; int unknown_04; int unknown_08; };
extern Rec12_008B3F38 DAT_008B3F38[];
struct Rec12_008B3FC8 { int key; int unknown_04; int unknown_08; };
extern Rec12_008B3FC8 DAT_008B3FC8[];
extern unsigned char DAT_00A9FAB4;
extern unsigned char DAT_00ABCD58;
extern int DAT_00ABED0C;
extern int DAT_00ABF168[];
struct Rec28_0082D028 { int f00; int f04; int unknown_08[5]; };
extern Rec28_0082D028 DAT_0082D028[];
extern int DAT_00AC4B80;
extern int DAT_00AC4C90;
extern int DAT_00AC4C38;
extern int DAT_00AC4BF0;
extern int DAT_007F0248[];
struct Rec16_007F0998 { int f00; int f04; int f08; int f0C; };
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

// FUNCTION: GAMEMD 0x004E4580
bool FUN_004E4580(int index)
{
    return DAT_008B4040[index].key != -1;
}

// FUNCTION: GAMEMD 0x004E50A0
bool FUN_004E50A0(int index)
{
    return DAT_008B3F38[index].key != -1;
}

// FUNCTION: GAMEMD 0x004E5B40
bool FUN_004E5B40(int index)
{
    return DAT_008B3FC8[index].key != -1;
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

// FUNCTION: GAMEMD 0x0063B090
void FUN_0063B090()
{
    DAT_00AC4BF0 = 0;
}

// FUNCTION: GAMEMD 0x00645BA0
int FUN_00645BA0(int index)
{
    return DAT_007F0248[index];
}

// FUNCTION: GAMEMD 0x00660AD0
int FUN_00660AD0(const int* index)
{
    return DAT_007F0998[*index].f04;
}

// FUNCTION: GAMEMD 0x00660AE0
int FUN_00660AE0(const int* index)
{
    return DAT_007F0998[*index].f08;
}

// FUNCTION: GAMEMD 0x00660AF0
int FUN_00660AF0(const int* index)
{
    return DAT_007F0998[*index].f00;
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

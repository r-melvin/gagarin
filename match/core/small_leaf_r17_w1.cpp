// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every offset, global and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//
// Round 17 small free functions, ascending by retail address.
// Address index: 0x414A20 0x48BB40 0x48DC20 0x53EC00 0x53F4F0.
#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// View of the object whose +0x294 field gates the mission test below.
struct Obj_00414A20
{
    char _pad_000[0x294];
    int unknown_294;       // +0x294

    bool FUN_00414A20(int mission);
};
GG_STATIC_ASSERT(offsetof(Obj_00414A20, unknown_294) == 0x294);

// FUNCTION: GAMEMD 0x414A20
// Missions 4, 0x1A, 0x1B, 0x1E and 0x1F need the +0x294 field set; every other mission is allowed.
bool Obj_00414A20::FUN_00414A20(int mission)
{
    switch (mission) {
    case 4:
    case 0x1A:
    case 0x1B:
    case 0x1E:
    case 0x1F:
        {
            bool needed = unknown_294 != 0;
            return needed;
        }
    default:
        return true;
    }
}

// An object whose slot 5 (+0x14) takes a flag word and answers a bool.
struct Obj_0048BB40
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual bool vf_5(unsigned int flags);

    bool __fastcall FUN_0048BB40(unsigned int flags);
};

// FUNCTION: GAMEMD 0x48BB40
// With bit 11 cleared, true when the flags hold nothing in bits 8-10 and 12; otherwise
// the negation of slot 5's answer for those flags.
bool __fastcall Obj_0048BB40::FUN_0048BB40(unsigned int flags)
{
    flags &= 0xFFFFF7FF;
    unsigned int reduced = flags & 0xFFFFE8FF;
    if (flags != reduced)
        return !vf_5(flags);
    return true;
}

// FUNCTION: GAMEMD 0x48DC20
// Maps the low byte values 0x21..0x28 (ignoring bits 8-10) to 1, 3, 5, 7, 6, 0, 2, 4; anything else is -1.
int __fastcall FUN_0048DC20(unsigned int value)
{
    switch (value & 0xFFFFF8FF) {
    case 0x25:
        return 6;
    case 0x27:
        return 2;
    case 0x26:
        return 0;
    case 0x28:
        return 4;
    case 0x24:
        return 7;
    case 0x21:
        return 1;
    case 0x23:
        return 5;
    case 0x22:
        return 3;
    default:
        return -1;
    }
}

// GLOBAL: GAMEMD 0x00AA0400 -- guards the two values below.
extern CRITICAL_SECTION DAT_00AA0400;
// GLOBAL: GAMEMD 0x00AA0434, 0x00AA0438 -- the shared pair copied out under the lock.
extern unsigned int DAT_00AA0434;
extern unsigned int DAT_00AA0438;
// GLOBAL: GAMEMD 0x00AA0444, 0x00AA0448 -- the two enable flags.
extern int DAT_00AA0444;
extern int DAT_00AA0448;

// FUNCTION: GAMEMD 0x53EC00
// Copies the shared pair out under the lock when both enable flags are set.
void __fastcall FUN_0053EC00(unsigned int* first, unsigned int* second)
{
    if (DAT_00AA0448 != 0 && DAT_00AA0444 != 0) {
        EnterCriticalSection(&DAT_00AA0400);
        *first = DAT_00AA0434;
        *second = DAT_00AA0438;
        LeaveCriticalSection(&DAT_00AA0400);
    }
}

// GLOBAL: GAMEMD 0x00AA0568 -- low word set by the call below.
extern unsigned short DAT_00AA0568;
// GLOBAL: GAMEMD 0x00AA0548, 0x00AA055C, 0x00AA0578, 0x00AA0530, 0x00AA0508, 0x00AA056C -- stored settings.
extern int DAT_00AA0548;
extern int DAT_00AA055C;
extern int DAT_00AA0578;
extern int DAT_00AA0530;
extern int DAT_00AA0508;
extern int DAT_00AA056C;
// GLOBAL: GAMEMD 0x00AA05A4 -- set once the settings are stored.
extern int DAT_00AA05A4;

// FUNCTION: GAMEMD 0x53F4F0
// Stores the seven settings into their globals and marks them set.
void __fastcall FUN_0053F4F0(unsigned short a, int b, int c, int d, int e, int f, int g)
{
    DAT_00AA0568 = a;
    DAT_00AA0548 = b;
    DAT_00AA055C = c;
    DAT_00AA0578 = d;
    DAT_00AA0530 = e;
    DAT_00AA0508 = f;
    DAT_00AA056C = g;
    DAT_00AA05A4 = 1;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   Small leaf helpers; the receivers are per-function placeholder views
//   that name only the fields each body reads.
#include <stdlib.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Declaration: GAMEMD 0x5F5850 -- one-argument query.
bool __stdcall FUN_005F5850(int a);
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;

// FUNCTION: GAMEMD 0x4238B0
bool __stdcall FUN_004238B0(int a)
{
    bool result = FUN_005F5850(a) != 0;
    return result;
}

struct Obj_00487C90
{
    char   unknown_00[0xF0];
    double unknown_F0;     // +0x00F0
    // FUNCTION: GAMEMD 0x487C90
    int FUN_00487C90() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00487C90, unknown_F0) == 0xF0);


// GLOBAL: GAMEMD 0xAA0E18
extern int DAT_00AA0E18;
// GLOBAL: GAMEMD 0xAA0748
extern int DAT_00AA0748;

struct Obj_004867B0
{
    char unknown_00[0x38];
    int  unknown_38;     // +0x0038
    // FUNCTION: GAMEMD 0x4867B0
    bool FUN_004867B0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004867B0, unknown_38) == 0x38);


// Four-byte-stride index into a table of 36-byte records.
struct Rec36_0048B720
{
    int flags;           // +0x00 bit 0: record in use
    int unknown_04;
    int unknown_08;
    int unknown_0C;
    int unknown_10;
    char unknown_14[4];
    int unknown_18;
    char unknown_1C[4];
    unsigned short unknown_20;
    char unknown_22[2];
};
GG_STATIC_ASSERT(sizeof(Rec36_0048B720) == 0x24);
GG_STATIC_ASSERT(offsetof(Rec36_0048B720, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Rec36_0048B720, unknown_20) == 0x20);

struct Obj_0048B720
{
    char             unknown_00[4];
    int              Count;       // +0x0004
    char             unknown_08[0x24 - 0x08];
    Rec36_0048B720*  Records;     // +0x0024
    int              Used;        // +0x0028
    char             unknown_2C[0x30 - 0x2C];
    int*             Order;       // +0x0030
    // FUNCTION: GAMEMD 0x48B720
    Rec36_0048B720* FUN_0048B720(int position) const;
    // FUNCTION: GAMEMD 0x48B390
    void FUN_0048B390();
};
GG_STATIC_ASSERT(offsetof(Obj_0048B720, Count) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_0048B720, Records) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_0048B720, Used) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_0048B720, Order) == 0x30);

// FUNCTION: GAMEMD 0x48B720
// The record at the given position of the order list, or null when it is not
// in use.
Rec36_0048B720* Obj_0048B720::FUN_0048B720(int position) const
{
    Rec36_0048B720* rec = &Records[Order[position]];
    return (rec->flags & 1) ? rec : 0;
}

// FUNCTION: GAMEMD 0x48B390
// Reset the table: nothing in use, every record's three state bits and its
// working fields cleared, and the order list zeroed.
void Obj_0048B720::FUN_0048B390()
{
    Used = 0;
    for (int i = 0; i < Count; i++) {
        Records[i].flags &= ~1;
        Records[i].flags &= ~2;
        Records[i].flags &= ~4;
        Records[i].unknown_04 = 0;
        Records[i].unknown_08 = 0;
        Records[i].unknown_0C = 0;
        Records[i].unknown_10 = 0;
        Records[i].unknown_18 = 0;
        Records[i].unknown_20 = 0;
        Order[i] = 0;
    }
}

// Same lookup over 24-byte records.
struct Rec24_0048B9E0
{
    int flags;           // +0x00 bit 0: record in use
    char unknown_04[0x14];
};
GG_STATIC_ASSERT(sizeof(Rec24_0048B9E0) == 0x18);

struct Obj_0048B9E0
{
    char             unknown_00[0x34];
    Rec24_0048B9E0*  Records;     // +0x0034
    char             unknown_38[0x40 - 0x38];
    int*             Order;       // +0x0040
    // FUNCTION: GAMEMD 0x48B9E0
    Rec24_0048B9E0* FUN_0048B9E0(int position) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0048B9E0, Records) == 0x34);
GG_STATIC_ASSERT(offsetof(Obj_0048B9E0, Order) == 0x40);

// FUNCTION: GAMEMD 0x48B9E0
Rec24_0048B9E0* Obj_0048B9E0::FUN_0048B9E0(int position) const
{
    Rec24_0048B9E0* rec = &Records[Order[position]];
    return (rec->flags & 1) ? rec : 0;
}

// A pair of 16-bit components; 0x4D03D0 compares their magnitudes.
struct Obj_004D03D0
{
    short X;    // +0x0000
    // FUNCTION: GAMEMD 0x4D03D0
    bool FUN_004D03D0(const Obj_004D03D0* other) const;
};

// FUNCTION: GAMEMD 0x4D03D0
// Whether this value's magnitude is at least the other's.
bool Obj_004D03D0::FUN_004D03D0(const Obj_004D03D0* other) const
{
    return abs(X) >= abs(other->X);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAA0748
int DAT_00AA0748;
// GLOBAL: GAMEMD 0xAA0E18
int DAT_00AA0E18;
// END defined globals

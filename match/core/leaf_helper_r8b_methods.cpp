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

// FUNCTION: GAMEMD 0x487C90
// Whether the stored double is above the shared constant.
int Obj_00487C90::FUN_00487C90() const
{
    return unknown_F0 > DAT_007E1718;
}

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

// FUNCTION: GAMEMD 0x4867B0
// Whether the stored value is one global, or falls in the sixteen values
// starting at another.
bool Obj_004867B0::FUN_004867B0() const
{
    int value = unknown_38;
    if (value == DAT_00AA0E18 || (value >= DAT_00AA0748 && value < DAT_00AA0748 + 0x10)) {
        return true;
    }
    return false;
}

// Four-byte-stride index into a table of 36-byte records.
struct Rec36_0048B720
{
    int flags;           // +0x00 bit 0: record in use
    char unknown_04[0x20];
};
GG_STATIC_ASSERT(sizeof(Rec36_0048B720) == 0x24);

struct Obj_0048B720
{
    char             unknown_00[0x24];
    Rec36_0048B720*  Records;     // +0x0024
    char             unknown_28[0x30 - 0x28];
    int*             Order;       // +0x0030
    // FUNCTION: GAMEMD 0x48B720
    Rec36_0048B720* FUN_0048B720(int position) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0048B720, Records) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_0048B720, Order) == 0x30);

// FUNCTION: GAMEMD 0x48B720
// The record at the given position of the order list, or null when it is not
// in use.
Rec36_0048B720* Obj_0048B720::FUN_0048B720(int position) const
{
    Rec36_0048B720* rec = &Records[Order[position]];
    return (rec->flags & 1) ? rec : 0;
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

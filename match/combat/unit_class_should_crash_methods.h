// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI inside 0x7438F0:
//     [ESI+0x6C4] the owning house's type record, whose bytes [EAX+0xD28]
//       (0x7438FD) and [EAX+0xD2D] (0x7439DE) gate the two branches;
//     [ESI+0x21C] the owning house (0x7439B9, 0x7439E8, 0x743A00, 0x743A1B),
//       with the int [ECX+0x184] compared with 2 (0x7439EE) and the int
//       [ECX+0x24C] compared against the rules value (0x743A0B);
//     RulesClass at 0x8871E0: the int [ECX+0x1728] (0x7439AD), the byte
//       [EDX+0x17EB] (0x7439CE) and the int [EAX+0x1448] (0x743A11);
//     vtable slots [EDX+0x48] — a CoordStruct-returning getter called with an
//       explicit out pointer (0x74393E, 0x74394C) — and [EDX+0xC8] (0x743A26);
//     the coordinate triple is read at [EAX+0], [EAX+4], [EAX+8] off the
//       returned pointer (0x74394F..0x743968).
//   Names cross-checked against YRpp (consult-only, NO LICENSE); every offset
//   reconfirmed above.
#ifndef GG_MATCH_COMBAT_UNIT_CLASS_SHOULD_CRASH_METHODS_H
#define GG_MATCH_COMBAT_UNIT_CLASS_SHOULD_CRASH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- square root; __cdecl, one double
// pushed on the stack, result left in ST(0).
double __cdecl Sqrt_004CAC40(double value);

struct Coord_007438F0
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(offsetof(Coord_007438F0, Z) == 0x08);

struct Rules_007438F0
{
    char _pad0000[0x1448];      // +0x0000
    int  At_1448;               // +0x1448
    char _pad144C[0x1728 - 0x144C]; // +0x144C
    int  At_1728;               // +0x1728
    char _pad172C[0x17EB - 0x172C]; // +0x172C
    char At_17EB;               // +0x17EB
};
GG_STATIC_ASSERT(offsetof(Rules_007438F0, At_1448) == 0x1448);
GG_STATIC_ASSERT(offsetof(Rules_007438F0, At_1728) == 0x1728);
GG_STATIC_ASSERT(offsetof(Rules_007438F0, At_17EB) == 0x17EB);

// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern Rules_007438F0* RulesInstance_007438F0;

// The owning house.
struct House_007438F0
{
    char _pad0000[0x184];       // +0x0000
    int  At_184;                // +0x0184
    char _pad0188[0x24C - 0x188]; // +0x0188
    int  At_24C;                // +0x024C

    // FUNCTION: GAMEMD 0x50B730 (decl; reloc)
    bool FUN_0050B730();
};
GG_STATIC_ASSERT(offsetof(House_007438F0, At_184) == 0x184);
GG_STATIC_ASSERT(offsetof(House_007438F0, At_24C) == 0x24C);

// The house type record hanging off the unit at +0x6C4.
struct HouseType_007438F0
{
    char _pad0000[0xD28];       // +0x0000
    char At_D28;                // +0x0D28
    char _pad0D29[0x04];        // +0x0D29
    char At_D2D;                // +0x0D2D
};
GG_STATIC_ASSERT(offsetof(HouseType_007438F0, At_D28) == 0xD28);
GG_STATIC_ASSERT(offsetof(HouseType_007438F0, At_D2D) == 0xD2D);

// Declaration order matters -- see match/_rt/gg_vslot.h.
struct Vtbl_007438F0;

// One class models both the unit and the candidate object: both are called
// through the same coordinate slot, and only the unit's members are read.
struct Obj_007438F0
{
    Vtbl_007438F0*     Vtbl;               // +0x0000
    char               _pad0004[0x21C - 0x04]; // +0x0004
    House_007438F0*    At_21C;             // +0x021C
    char               _pad0220[0x6C4 - 0x220]; // +0x0220
    HouseType_007438F0* At_6C4;            // +0x06C4

    // FUNCTION: GAMEMD 0x70D0D0 (decl; reloc) -- capability/flag query.
    bool FUN_0070D0D0(int what);
    // FUNCTION: GAMEMD 0x5F6CD0 (decl; reloc) -- "is a valid crash victim of".
    bool FUN_005F6CD0(Obj_007438F0* other);

    // FUNCTION: GAMEMD 0x7438F0 -- UnitClass::ShouldCrashIt.
    bool ShouldCrashIt(Obj_007438F0* victim);
};
GG_STATIC_ASSERT(offsetof(Obj_007438F0, At_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(Obj_007438F0, At_6C4) == 0x6C4);

typedef Coord_007438F0* (Obj_007438F0::*Fn048_007438F0)(Coord_007438F0* out);
typedef char (Obj_007438F0::*Fn0C8_007438F0)(House_007438F0* house);

struct Vtbl_007438F0
{
    char           _pad0000[0x48];            // +0x0000
    Fn048_007438F0 At_048;                    // +0x0048
    char           _pad004C[0xC8 - 0x4C];     // +0x004C
    Fn0C8_007438F0 At_0C8;                    // +0x00C8
};
GG_STATIC_ASSERT(offsetof(Vtbl_007438F0, At_048) == 0x48);
GG_STATIC_ASSERT(offsetof(Vtbl_007438F0, At_0C8) == 0xC8);

#endif  // GG_MATCH_COMBAT_UNIT_CLASS_SHOULD_CRASH_METHODS_H

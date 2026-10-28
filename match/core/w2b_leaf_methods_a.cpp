// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small leaf bodies from
//   the 0x65F000-0x68D000 range; the receivers are placeholder views of the members touched.
//
// Address index: 0x65FB70 0x660530 0x6643E0 0x683000 0x68C960 0x68C990

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7F09A4 -- byte at offset 4 of the sixteen-byte records starting at 0x7F09A0.
extern unsigned char DAT_007F09A4[];
// GLOBAL: GAMEMD 0xB04DB8
extern int DAT_00B04DB8;

// FUNCTION: GAMEMD 0x65FB70
// One byte out of the sixteen-byte record selected by an index.
unsigned char __fastcall FUN_0065FB70(int index)
{
    return DAT_007F09A4[index * 16];
}

// FUNCTION: GAMEMD 0x660530
// True when the global count is zero.
bool __cdecl FUN_00660530()
{
    bool r = DAT_00B04DB8 == 0;
    return r;
}

// Vector of four-byte entries: storage at +0x04, count at +0x10.
struct IntVector_006643E0
{
    int  unknown_00;
    int* Items;           // +0x04
    int  unknown_08;
    int  unknown_0C;
    int  Count;           // +0x10

    int FUN_006643E0(int index) const;
};
GG_STATIC_ASSERT(offsetof(IntVector_006643E0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(IntVector_006643E0, Count) == 0x10);

// FUNCTION: GAMEMD 0x6643E0
// The entry at an index plus one, or zero when the index is past the end.
int IntVector_006643E0::FUN_006643E0(int index) const
{
    if (index < Count) {
        return Items[index] + 1;
    }
    return 0;
}

struct Pair_00683000
{
    int key;
    int value;
};
// GLOBAL: GAMEMD 0x83D658 -- thirteen key/value pairs.
extern Pair_00683000 DAT_0083D658[13];

// FUNCTION: GAMEMD 0x683000
// The value paired with a key in the table, or zero.
int __fastcall FUN_00683000(int key)
{
    for (int i = 0; i < 13; i++) {
        if (DAT_0083D658[i].key == key) {
            return DAT_0083D658[i].value;
        }
    }
    return 0;
}

// ColorScheme view: the name pointer at +0x304.
struct ColorSchemeView_0068C960
{
    char        unknown_000[0x304];
    const char* Name;    // +0x304

    bool FUN_0068C960(const ColorSchemeView_0068C960& other) const;
    bool FUN_0068C990(const ColorSchemeView_0068C960& other) const;
};
GG_STATIC_ASSERT(offsetof(ColorSchemeView_0068C960, Name) == 0x304);

// FUNCTION: GAMEMD 0x68C960
// Equal when the names compare equal without regard to case.
bool ColorSchemeView_0068C960::FUN_0068C960(const ColorSchemeView_0068C960& other) const
{
    return _stricmp(Name, other.Name) == 0;
}

// FUNCTION: GAMEMD 0x68C990
// Different when the names compare unequal without regard to case.
bool ColorSchemeView_0068C960::FUN_0068C990(const ColorSchemeView_0068C960& other) const
{
    return _stricmp(Name, other.Name) != 0;
}

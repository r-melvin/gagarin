// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each body read from the entry-bounded retail function in gamemd.exe v1.001.
//   Owners are placeholders (Obj_<ADDR>) declaring only the fields touched,
//   with offset asserts.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Two parallel 24-entry word tables at +0x7C and +0xAC; each accessor tests
// whether an entry is positive.
struct Obj_004870D0
{
    char unknown_00[0x7C];
    short unknown_7C[0x18];   // +0x007C
    short unknown_AC[0x18];   // +0x00AC
    // FUNCTION: GAMEMD 0x4870D0
    bool FUN_004870D0(int index) const;
    // FUNCTION: GAMEMD 0x4870F0
    bool FUN_004870F0(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_004870D0, unknown_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(Obj_004870D0, unknown_AC) == 0xAC);


struct Obj_004A52D0
{
    char unknown_00[0x18];
    bool unknown_18;   // +0x0018
    bool unknown_19;   // +0x0019
    // FUNCTION: GAMEMD 0x4A52D0
    void FUN_004A52D0();
};
GG_STATIC_ASSERT(offsetof(Obj_004A52D0, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_004A52D0, unknown_19) == 0x19);

// FUNCTION: GAMEMD 0x4A52D0
// Clears one flag and sets the next.
void Obj_004A52D0::FUN_004A52D0()
{
    unknown_18 = false;
    unknown_19 = true;
}

struct Obj_004B6BE0
{
    char unknown_00[0x14];
    int unknown_14[1];   // +0x0014 (open-ended table)
    // FUNCTION: GAMEMD 0x4B6BE0
    int FUN_004B6BE0(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_004B6BE0, unknown_14) == 0x14);

// FUNCTION: GAMEMD 0x4B6BE0
// Returns one entry of the table at +0x14.
int Obj_004B6BE0::FUN_004B6BE0(int index) const
{
    return unknown_14[index];
}

// Two key members at +0x4C and +0x50, each set through the key's assignment
// operator (0x7B4940, defined out of line).
struct Key_007B4940
{
    int Data;   // +0x00
    // FUNCTION: GAMEMD 0x7B4940 (decl; reloc)
    Key_007B4940& operator=(const Key_007B4940& other);
};

struct Obj_004F2680
{
    char unknown_00[0x4C];
    Key_007B4940 unknown_4C;   // +0x004C
    Key_007B4940 unknown_50;   // +0x0050
    // FUNCTION: GAMEMD 0x4F2680
    void FUN_004F2680(const Key_007B4940& key);
    // FUNCTION: GAMEMD 0x4F2800
    void FUN_004F2800(const Key_007B4940& key);
};
GG_STATIC_ASSERT(offsetof(Obj_004F2680, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_004F2680, unknown_50) == 0x50);

// FUNCTION: GAMEMD 0x4F2680
// Assigns the key at +0x50.
void Obj_004F2680::FUN_004F2680(const Key_007B4940& key)
{
    unknown_50 = key;
}

// FUNCTION: GAMEMD 0x4F2800
// Assigns the key at +0x4C.
void Obj_004F2680::FUN_004F2800(const Key_007B4940& key)
{
    unknown_4C = key;
}

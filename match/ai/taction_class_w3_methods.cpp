// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. TActionClass handlers
//   from TAction.CPP (code range 0x6dcd70-0x6e4b4f); the receivers are placeholder views of the
//   house and super-weapon members touched, as in TAction.cpp.
//
// Address index: 0x6E42D0 0x6E4320 0x6E47C0

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Elem_006E42D0 {
    unsigned char unknown_00[0x6D];
    unsigned char unknown_6D;       // +0x6D: the super weapon is present
    // FUNCTION: GAMEMD 0x6CC1E0 (decl; reloc) -- SuperClass::SetCharge.
    void FUN_006CC1E0(int percentage);
};
GG_STATIC_ASSERT(offsetof(Elem_006E42D0, unknown_6D) == 0x6D);
struct Rec_006E42D0 {
    unsigned char unknown_00[0x258];
    Elem_006E42D0** unknown_258;    // +0x258: the house's super weapons
    int unknown_25C;
    int unknown_260;
    int unknown_264;                // +0x264: their count
};
GG_STATIC_ASSERT(offsetof(Rec_006E42D0, unknown_258) == 0x258);
GG_STATIC_ASSERT(offsetof(Rec_006E42D0, unknown_264) == 0x264);
struct Obj_006E42D0 {
    unsigned char unknown_00[0x48];
    int unknown_48;                 // +0x48: the percentage
    unsigned char unknown_4C[0x44];
    int unknown_90;                 // +0x90: the super weapon index
    bool FUN_006E42D0(Rec_006E42D0* a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E42D0, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(Obj_006E42D0, unknown_90) == 0x90);

// FUNCTION: GAMEMD 0x6E42D0
// Sets the charge of one of the house's present super weapons to a percentage from 0 to 100.
bool Obj_006E42D0::FUN_006E42D0(Rec_006E42D0* a1, int a2, int a3, int a4)
{
    if (a1 && unknown_90 >= 0 && unknown_90 <= a1->unknown_264) {
        Elem_006E42D0* super = a1->unknown_258[unknown_90];
        if (super->unknown_6D && unknown_48 >= 0 && unknown_48 <= 100) {
            super->FUN_006CC1E0(unknown_48);
            return true;
        }
    }
    return false;
}

struct Elem_006E4320 {
    // FUNCTION: GAMEMD 0x6CC280 (decl; reloc) -- SuperClass::SetRechargeTime.
    void FUN_006CC280(int time);
};
struct Rec_006E4320 {
    unsigned char unknown_00[0x258];
    Elem_006E4320** unknown_258;
    int unknown_25C;
    int unknown_260;
    int unknown_264;
};
GG_STATIC_ASSERT(offsetof(Rec_006E4320, unknown_258) == 0x258);
GG_STATIC_ASSERT(offsetof(Rec_006E4320, unknown_264) == 0x264);
struct Obj_006E4320 {
    unsigned char unknown_00[0x48];
    int unknown_48;                 // +0x48: the recharge time
    unsigned char unknown_4C[0x44];
    int unknown_90;                 // +0x90: the super weapon index
    bool FUN_006E4320(Rec_006E4320* a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E4320, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(Obj_006E4320, unknown_90) == 0x90);

// FUNCTION: GAMEMD 0x6E4320
// Sets the recharge time of one of the house's super weapons.
bool Obj_006E4320::FUN_006E4320(Rec_006E4320* a1, int a2, int a3, int a4)
{
    if (a1 && unknown_90 >= 0 && unknown_90 <= a1->unknown_264) {
        a1->unknown_258[unknown_90]->FUN_006CC280(unknown_48);
        return true;
    }
    return false;
}

// A 32-byte block that assigns by block copy and hands back a copy of itself.
struct Block_006E47C0 {
    int Words[8];

    Block_006E47C0 FUN_006E47C0(const Block_006E47C0& other);
};
GG_STATIC_ASSERT(sizeof(Block_006E47C0) == 0x20);

// FUNCTION: GAMEMD 0x6E47C0
// Copies the other block over this one (unless it is this one) and returns a copy of the result.
Block_006E47C0 Block_006E47C0::FUN_006E47C0(const Block_006E47C0& other)
{
    if (&other != this) {
        *this = other;
    }
    return *this;
}

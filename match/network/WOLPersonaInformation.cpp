// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit WOLPersonaInformation.cpp. The name is the source-file string at 0x84a0d0
//   in retail gamemd.exe v1.001, passed by the assert at 0x778f62 inside this object's
//   code range (0x7784f0-0x77b08f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The deleting destructors (??_G) of the World Domination Tour data classes are
// compiler output: the out-of-line destructors below make cl emit the tables and
// the wrappers, and /Ob2 expands the destructor bodies into them as retail has it.

#include "../FUNCTION.H"
#include "../core/trivial_tu286_methods.h"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"


// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F74E0
extern const double DAT_007F74E0;
// GLOBAL: GAMEMD 0xB73598
extern double DAT_00B73598;
// GLOBAL: GAMEMD 0xB735D0
extern double DAT_00B735D0;
// GLOBAL: GAMEMD 0xB735D8
extern int DAT_00B735D8;
// GLOBAL: GAMEMD 0xB735DC
extern int DAT_00B735DC;
// GLOBAL: GAMEMD 0xB735E0
extern int DAT_00B735E0;
// GLOBAL: GAMEMD 0xB735E8
extern double DAT_00B735E8;

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00778520()
{
    DAT_00B735E8 = DAT_00B73598 / DAT_007F74E0;
}

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00778540()
{
    DAT_00B735D0 = DAT_007E1718 / DAT_00B735E8;
}

// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_007786C0()
{
    DAT_00B735E0 = 0;
    DAT_00B735D8 = 0x80;
    DAT_00B735DC = 0x80;
}

int FUN_007B5440(int);
int FUN_007B7140(int);
int FUN_007350C0(int);
int FUN_00735120(int);

struct Obj_00779650 {
    void FUN_007B7600(int);
    void FUN_007B5A40(int);
};
// FUNCTION: GAMEMD 0x00779650
void __fastcall FUN_00779650(int a, Obj_00779650* target)
{
    target->FUN_007B7600(FUN_00735120(FUN_007B5440(a)));
}
// FUNCTION: GAMEMD 0x00779670
void __fastcall FUN_00779670(int a, Obj_00779650* target)
{
    target->FUN_007B5A40(FUN_007350C0(FUN_007B7140(a)));
}

// FUNCTION: GAMEMD 0x77A050
// Seats the PlayerProfile table, then the members in reverse order and the
// ReferenceCounted destructor.
PlayerProfile::~PlayerProfile()
{
}

struct Persona_0077A700
{
    char unknown_00[0x08];
    unsigned char Dirty;      // +0x08
    char unknown_09[0x07];
    int unknown_10;           // +0x10
    unsigned char unknown_14; // +0x14
    char unknown_15[0x03];
    int unknown_18;           // +0x18
    char unknown_1C[0x08];
    int unknown_24;           // +0x24
    int unknown_28;           // +0x28
    int unknown_2C;           // +0x2C
    int unknown_30;           // +0x30
    int unknown_34;           // +0x34

    // FUNCTION: GAMEMD 0x77A700 (__thiscall)
    void FUN_0077A700(int a, int b);
    // FUNCTION: GAMEMD 0x77A7C0 (__thiscall)
    void FUN_0077A7C0(const struct PersonaSrc_0077A7C0* src);
    void FUN_0077A4D0();
};
GG_STATIC_ASSERT(offsetof(Persona_0077A700, Dirty) == 0x08);
GG_STATIC_ASSERT(offsetof(Persona_0077A700, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Persona_0077A700, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Persona_0077A700, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Persona_0077A700, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Persona_0077A700, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Persona_0077A700, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(Persona_0077A700, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Persona_0077A700, unknown_34) == 0x34);

struct PersonaSrc_0077A7C0
{
    char unknown_00[0x08];
    int unknown_08;           // +0x08
    int unknown_0C;           // +0x0C
    int unknown_10;           // +0x10
    char unknown_14[0x08];
    int unknown_1C;           // +0x1C
    int unknown_20;           // +0x20
};
GG_STATIC_ASSERT(offsetof(PersonaSrc_0077A7C0, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(PersonaSrc_0077A7C0, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(PersonaSrc_0077A7C0, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(PersonaSrc_0077A7C0, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(PersonaSrc_0077A7C0, unknown_20) == 0x20);

// FUNCTION: GAMEMD 0x77A700
// Sets the id/stage pair. The same id only latches the flag at stage 2; a different id is taken
// when it is non-zero and the stage has not gone backwards (or nothing is held yet), and stage 3
// clears the latched flag.
void Persona_0077A700::FUN_0077A700(int a, int b)
{
    if (a == unknown_10) {
        if (b == 2 && !unknown_14) {
            unknown_14 = 1;
            Dirty = 1;
        }
        return;
    }
    bool newer = b >= unknown_18;
    if (unknown_10 == 0) {
        newer = true;
    } else if (!newer) {
        return;
    }
    if (a != 0 && newer) {
        if (b == 3) {
            unknown_14 = 0;
        }
        unknown_10 = a;
        unknown_18 = b;
        Dirty = 1;
    }
}

// FUNCTION: GAMEMD 0x77A760
// Branching.
unsigned char Obj_0077A760::FUN_0077A760(unsigned char a1)
{
    if (a1 != unknown_38)
    {
        unsigned char t1 = unknown_38;
        unknown_38 = a1;
        unknown_08 = 1;
    }
    return a1;
}

// FUNCTION: GAMEMD 0x77A780
// Branching.
int Obj_0077A780::FUN_0077A780(int a1)
{
    if (a1 != unknown_1C)
    {
        int t1 = unknown_1C;
        unknown_1C = a1;
        unknown_08 = 1;
    }
    return a1;
}

// FUNCTION: GAMEMD 0x77A7A0
// Branching.
int Obj_0077A7A0::FUN_0077A7A0(int a1)
{
    if (a1 != unknown_20)
    {
        int t1 = unknown_20;
        unknown_20 = a1;
        unknown_08 = 1;
    }
    return a1;
}


struct Arg1_0077A840;
struct Obj_0077A840;

struct Arg1_0077A840
{
    char unknown_00[0x10];
    int unknown_10;   // +0x0010
    char unknown_14[0x8];
    int unknown_1C;   // +0x001C
};
GG_STATIC_ASSERT(offsetof(Arg1_0077A840, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Arg1_0077A840, unknown_1C) == 0x1C);

struct Obj_0077A840
{
    char unknown_00[0x24];
    int unknown_24;   // +0x0024
    int unknown_28;   // +0x0028
    // FUNCTION: GAMEMD 0x77A840
    unsigned char FUN_0077A840(Arg1_0077A840* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0077A840, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_0077A840, unknown_28) == 0x28);

// FUNCTION: GAMEMD 0x77A7C0
// Copies the five tracked values from the source record, marking this record dirty and refreshing
// it when any of them changed.
void Persona_0077A700::FUN_0077A7C0(const PersonaSrc_0077A7C0* src)
{
    bool changed = false;
    if (src->unknown_1C != unknown_24) {
        unknown_24 = src->unknown_1C;
        Dirty = 1;
        changed = true;
    }
    if (src->unknown_10 != unknown_28) {
        unknown_28 = src->unknown_10;
        Dirty = 1;
        changed = true;
    }
    if (src->unknown_08 != unknown_2C) {
        unknown_2C = src->unknown_08;
        Dirty = 1;
        changed = true;
    }
    if (src->unknown_0C != unknown_30) {
        unknown_30 = src->unknown_0C;
        Dirty = 1;
        changed = true;
    }
    if (src->unknown_20 != unknown_34) {
        unknown_34 = src->unknown_20;
        Dirty = 1;
        FUN_0077A4D0();
    } else if (changed) {
        FUN_0077A4D0();
    }
}

// FUNCTION: GAMEMD 0x77A840
// Branching.
unsigned char Obj_0077A840::FUN_0077A840(Arg1_0077A840* a1)
{
    if (a1->unknown_1C != unknown_24)
    {
        return 1;
    }
    return (a1->unknown_10 != unknown_28) ? true : false;
}

// FUNCTION: GAMEMD 0x77A870
// Branching.
void Obj_0077A870::FUN_0077A870(int a1)
{
    if (unknown_2C != -1)
    {
        unknown_08 = 1;
        unknown_2C += a1;
    }
}

// FUNCTION: GAMEMD 0x77A890
// Branching.
void Obj_0077A890::FUN_0077A890(int a1)
{
    if (unknown_30 != -1)
    {
        unknown_08 = 1;
        unknown_30 += a1;
    }
}

// FUNCTION: GAMEMD 0x77A8B0
// Branching.
void Obj_0077A8B0::FUN_0077A8B0(int a1)
{
    if (unknown_34 != -1)
    {
        unknown_08 = 1;
        unknown_34 += a1;
    }
}

// SYNTHETIC: GAMEMD 0x77B030
// PlayerProfile scalar deleting destructor.

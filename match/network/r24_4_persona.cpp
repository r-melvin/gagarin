// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Persona record setters read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at
//   the address in each annotation. Receivers are placeholder views named after their address, as
//   in WOLPersonaInformation.cpp.
//   Address index: 0x77A700, 0x77A7C0.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

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

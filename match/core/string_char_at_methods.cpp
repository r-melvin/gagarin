// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Bounds-checked character read of a string holder (character pointer at
// +0x00), repeated unchanged for three owners: the byte at `index` when it is
// below the string length, otherwise zero. strlen is expanded inline. The
// owners are placeholders `Obj_<ADDR>`.

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

struct Obj_007B5410 {
    const char* text; // +0x00
    char FUN_007B5410(unsigned int index);
};
GG_STATIC_ASSERT(offsetof(Obj_007B5410, text) == 0x00);

// FUNCTION: GAMEMD 0x007B5410
char Obj_007B5410::FUN_007B5410(unsigned int index)
{
    if (index < strlen(text))
        return text[index];
    return 0;
}

struct Obj_007B5450 {
    const char* text; // +0x00
    char FUN_007B5450(unsigned int index);
};
GG_STATIC_ASSERT(offsetof(Obj_007B5450, text) == 0x00);

// FUNCTION: GAMEMD 0x007B5450
char Obj_007B5450::FUN_007B5450(unsigned int index)
{
    if (index < strlen(text))
        return text[index];
    return 0;
}

struct Obj_007B5480 {
    const char* text; // +0x00
    char FUN_007B5480(unsigned int index);
};
GG_STATIC_ASSERT(offsetof(Obj_007B5480, text) == 0x00);

// FUNCTION: GAMEMD 0x007B5480
char Obj_007B5480::FUN_007B5480(unsigned int index)
{
    if (index < strlen(text))
        return text[index];
    return 0;
}


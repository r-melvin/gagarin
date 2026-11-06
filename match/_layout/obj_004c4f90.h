// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   A number paired with a type: 0x4C4F90 prints "<number>,<type ID>" and 0x4C4EF0 parses that text back
//   (a "%d,%s" scan, then the type looked up by ID in the infantry, unit and aircraft type arrays). The
//   task force reader 0x6E8420 and writer 0x6E8510 are their only callers, on the six {amount, type}
//   entries at TaskForceClass+0xA4, so this is the task force entry.
#ifndef GG_MATCH_LAYOUT_OBJ_004C4F90_H
#define GG_MATCH_LAYOUT_OBJ_004C4F90_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "obj_004a1d30.h"

class TechnoTypeClass;

struct Obj_004C4F90
{
    int              Amount;   // +0x00
    TechnoTypeClass* Type;     // +0x04

    Obj_004C4F90() {}
    Obj_004C4F90(int amount, TechnoTypeClass* type) : Amount(amount), Type(type) {}

    // FUNCTION: GAMEMD 0x4C4EF0 (decl; reloc) -- parse "<number>,<type ID>" into this entry, RET 4.
    Obj_004C4F90* FUN_004C4EF0(const char* text);
    // FUNCTION: GAMEMD 0x4C4F90
    char* FUN_004C4F90() const;
    // FUNCTION: GAMEMD 0x4C4FC0
    void FUN_004C4FC0(Obj_004A1D30* crc) const;
};
GG_STATIC_ASSERT(offsetof(Obj_004C4F90, Type) == 4);
GG_STATIC_ASSERT(sizeof(Obj_004C4F90) == 8);

#endif

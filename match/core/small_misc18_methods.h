// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC18_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC18_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Six vtable pointers over four slots: the two at +0x08 and +0x0C are written
// twice, first with the base class's tables and then with the derived ones.
// That is what a multiple-inheritance constructor does, and reproducing it
// means writing both assignments out rather than collapsing them.
extern char VT_007E1FBC[];   // VTABLE: GAMEMD 0x7E1FBC
extern char VT_007E1FB4[];   // VTABLE: GAMEMD 0x7E1FB4
extern char VT_007E1F50b[];  // VTABLE: GAMEMD 0x7E1F50
extern char VT_007E1F34b[];  // VTABLE: GAMEMD 0x7E1F34
extern char VT_007E1F2Cb[];  // VTABLE: GAMEMD 0x7E1F2C
extern char VT_007E1F24b[];  // VTABLE: GAMEMD 0x7E1F24

struct Obj_004101C0
{
    char* vt0;   // +0x0000
    char* vt1;   // +0x0004
    char* vt2;   // +0x0008
    char* vt3;   // +0x000C

    // 0x4101C0 is AbstractClass::AbstractClass(AbstractNoInit), defined in
    // abstract_class_ctor.cpp; this caller-side view still names it.
    Obj_004101C0* FUN_004101C0(int flags);
};


#endif  // GG_MATCH_CORE_SMALL_MISC18_METHODS_H

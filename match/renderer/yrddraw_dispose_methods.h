// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Globals read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6BB8E0: the two byte flags `MOV AL,[0x8A0DEF]` and
//   `CMP byte ptr [0xB0BCF5],BL` / `MOV byte ptr [0xB0BCF5],1`; the six
//   surface pointers loaded through `MOV ECX,[0x88730C]` .. `[0x887308]`,
//   each released via the slot-0 deleting destructor (`MOV EAX,[ECX]; PUSH 1;
//   CALL [EAX]`) and then zeroed. Method / class names from YRpp YRDDraw.h
//   (consult-only; names only, no text copied).
#ifndef GG_MATCH_RENDERER_YRDDRAW_DISPOSE_METHODS_H
#define GG_MATCH_RENDERER_YRDDRAW_DISPOSE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A DirectDraw surface wrapper. Only its virtual destructor (vtable slot 0) is
// reached here: `delete p` lowers to the scalar-deleting-destructor call.
struct Surface_006BB8E0
{
    virtual ~Surface_006BB8E0();   // slot 0 -- declared only
};

// GLOBAL: GAMEMD 0x8A0DEF -- set once the sidebar/tab surfaces were built.
extern char DAT_008A0DEF;
// GLOBAL: GAMEMD 0xB0BCF5 -- set once DisposeOfStuff has run.
extern char DAT_00B0BCF5;

// GLOBAL: GAMEMD 0x88730C / 0x887310 / 0x8872FC / 0x887300 / 0x88731C /
// 0x887308 -- the six DirectDraw surfaces released in this order.
extern Surface_006BB8E0* DAT_0088730C;
extern Surface_006BB8E0* DAT_00887310;
extern Surface_006BB8E0* DAT_008872FC;
extern Surface_006BB8E0* DAT_00887300;
extern Surface_006BB8E0* DAT_0088731C;
extern Surface_006BB8E0* DAT_00887308;

// FUNCTION: GAMEMD 0x4C19B0 (decl; reloc) -- free the sidebar/tab surfaces.
void FUN_004C19B0();

struct YRDDraw
{
    // FUNCTION: GAMEMD 0x4A44F0 (decl; reloc)
    static void Restore();

    // FUNCTION: GAMEMD 0x6BB8E0
    static void DisposeOfStuff();
};

#endif  // GG_MATCH_RENDERER_YRDDRAW_DISPOSE_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x54F5C0 and 0x54F720),
//   cross-checked against YRpp InputManagerClass.h (consult-only; reconfirmed
//   numerically here).
//
// InputManagerClass — keyboard/mouse input dispatcher. This translation unit
// matches two methods: IsKeyPressed (a button-state probe that honours the
// system mouse-button-swap setting) and DoSomething (a ring-buffer head/tail
// flush). The class holds a 256-entry word ring buffer; only the head index
// @0x314 and tail index @0x318 are touched here.
#ifndef GG_MATCH_PLATFORM_INPUT_MANAGER_CLASS_METHODS_H
#define GG_MATCH_PLATFORM_INPUT_MANAGER_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct InputManagerClass
{
    char _pad0[0x314];          // +0x000  (5 ints + byte[256] + word[256], unmodelled)
    int  field_314;             // +0x314  ring-buffer head/read index
    int  field_318;             // +0x318  ring-buffer tail/write index

    // GAMEMD 0x54F5C0 — bool IsKeyPressed(int) const (__thiscall)
    bool IsKeyPressed(int key) const;

    // GAMEMD 0x54F720 — byte DoSomething() (__thiscall); flushes head==tail
    void DoSomething();
};

GG_STATIC_ASSERT(offsetof(InputManagerClass, field_314) == 0x314);
GG_STATIC_ASSERT(offsetof(InputManagerClass, field_318) == 0x318);

#endif  // GG_MATCH_PLATFORM_INPUT_MANAGER_CLASS_METHODS_H

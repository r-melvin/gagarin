// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x54F5C0 and 0x54F720),
//   cross-checked against YRpp (reconfirmed
//   numerically here).
//
// InputManagerClass — keyboard/mouse input dispatcher. This translation unit
// matches two methods: IsKeyPressed (a button-state probe that honours the
// system mouse-button-swap setting) and DoSomething (a ring-buffer head/tail
// flush). Retail index arithmetic wraps at 256; storage before the observed
// head at +0x314 and tail at +0x318 remains unmodelled here.
#ifndef GG_MATCH_PLATFORM_INPUT_MANAGER_CLASS_METHODS_H
#define GG_MATCH_PLATFORM_INPUT_MANAGER_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct InputManagerClass
{
    int            unknown_00;          // +0x000
    int            unknown_04;          // +0x004
    unsigned short unknown_08;          // +0x008
    unsigned short unknown_0A;          // +0x00A
    int            unknown_0C;          // +0x00C
    int            unknown_10;          // +0x010
    unsigned char  KeyState[0x100];     // +0x014  cleared by the constructor (0x40 dwords)
    unsigned short Ring[256];           // +0x114  queued key codes
    int  field_314;             // +0x314  ring-buffer head/read index
    int  field_318;             // +0x318  ring-buffer tail/write index

    // FUNCTION: GAMEMD 0x54F6F0 -- pumps input when the ring is not full.
    void FUN_0054F6F0();

    // FUNCTION: GAMEMD 0x54F000 (decl; reloc) — ABI view; original name unknown.
    unsigned short FUN_0054F000();
    // FUNCTION: GAMEMD 0x54F050 (decl; reloc)
    // InputManagerClass::FUN_0054F050
    unsigned short FUN_0054F050();

    // FUNCTION: GAMEMD 0x54F5C0 (decl; reloc) — key-state query.
    bool IsKeyPressed(int key) const;

    // FUNCTION: GAMEMD 0x54F720 (decl; reloc) — head/tail synchronization.
    void DoSomething();
};

GG_STATIC_ASSERT(offsetof(InputManagerClass, KeyState) == 0x14);
GG_STATIC_ASSERT(offsetof(InputManagerClass, Ring) == 0x114);
GG_STATIC_ASSERT(offsetof(InputManagerClass, field_314) == 0x314);
GG_STATIC_ASSERT(offsetof(InputManagerClass, field_318) == 0x318);
// The modeled prefix through the last confirmed field is 0x31C bytes; this
// does not assert the full retail object size.
GG_STATIC_ASSERT(offsetof(InputManagerClass, field_318) + sizeof(((InputManagerClass*)0)->field_318) == 0x31C);

// GLOBAL: GAMEMD 0x87F770 — shared input manager pointer.
extern InputManagerClass* DAT_0087F770;

// FUNCTION: GAMEMD 0x5D4D50 (decl; reloc) -- shared free call view.
// These callers supply no arguments and discard the result; the original
// source name and return type are not established by those calls.
void __cdecl FUN_005D4D50();

#endif  // GG_MATCH_PLATFORM_INPUT_MANAGER_CLASS_METHODS_H

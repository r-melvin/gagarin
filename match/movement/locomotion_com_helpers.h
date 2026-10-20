// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI. 0x70F0B0 maps a locomotor kind onto the two replacement kinds
//   the expansion added, gated by a global predicate at 0x731BF0; the kind
//   arrives in the register, so it is a free __fastcall whose second argument
//   is unused. 0x719EE0 is the COM hand-off of a pending object: the
//   interface pointer is reached at a negative displacement of 0xC from the
//   passed object, which is the usual adjustor for a secondary COM base, and
//   the two fields cleared there are at +0x428 and +0x42C. Names
//   cross-checked against the private-reference seed (consult-only); every offset and
//   convention re-derived here.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_COM_HELPERS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_COM_HELPERS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x731BF0 (decl; reloc) — is the expansion's rule set active.
bool __fastcall FUN_00731BF0();

// The secondary COM base, reached at -0xC from the object below.
struct ComBase_00719EE0
{
    char _pad000[0x428];   // +0x0000
    int  Pending428;       // +0x0428
    int  Pending42C;       // +0x042C
};
GG_STATIC_ASSERT(offsetof(ComBase_00719EE0, Pending428) == 0x428);
GG_STATIC_ASSERT(offsetof(ComBase_00719EE0, Pending42C) == 0x42C);

struct Owner_00719EE0
{
    char  _pad000[0x30];   // +0x0000
    void* Pending;         // +0x0030
};
GG_STATIC_ASSERT(offsetof(Owner_00719EE0, Pending) == 0x30);

// FUNCTION: GAMEMD 0x70F0B0
int __fastcall FUN_0070F0B0(int kind, int unusedInRegister, int unusedOnStack);

// FUNCTION: GAMEMD 0x719EE0
long __stdcall FUN_00719EE0(Owner_00719EE0* self, void** out);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_COM_HELPERS_H

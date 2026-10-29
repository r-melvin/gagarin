// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Globals and calling shapes read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x5DA6C0: the two
//   `MOV ECX,0xA8E9C0` receiver loads, `CMP dword ptr [0xA8B238],4`,
//   `MOV EAX,[0xA8D5FC]`, the `MOV ECX,0xA8D600` receiver for 0x53EDA0 and
//   the two locals handed to it at [ESP] and [ESP+4] (0x53EDA0 writes a dword
//   through the first and a dword + word through the second). YRpp names the
//   0xA8E9C0 and 0xA8B238 instances (name-only cross-check).
#ifndef GG_MATCH_CORE_INIT_MISC_METHODS_H
#define GG_MATCH_CORE_INIT_MISC_METHODS_H

#include <stddef.h>
#include "../_layout/session_class.h"
#include "../_rt/gg_static_assert.h"

// Shared manager declaration preserves the direct startup call bindings.
#include "../network/transport/connman_class.h"

// The 6-byte record 0x53EDA0 copies out through its second pointer
// (`MOV [EDX],ESI; MOV word ptr [EDX+4],AX`).
struct Rec6_005DA6C0
{
    int   Low;     // +0x0000
    short High;    // +0x0004
};
GG_STATIC_ASSERT(sizeof(Rec6_005DA6C0) == 8);

// The object at 0xA8D600 whose first dword and following 6 bytes 0x53EDA0
// copies out.
struct Addr_005DA6C0
{
    // FUNCTION: GAMEMD 0x53EDA0 (decl; reloc)
    void FUN_0053EDA0(int* first, Rec6_005DA6C0* rest);
};

// GLOBAL: GAMEMD 0xA8D600
extern Addr_005DA6C0 DAT_00A8D600;

// GLOBAL: GAMEMD 0xA8B238 — first dword of the session block (YRpp:
// SessionClass::Instance, the game-mode field).

// GLOBAL: GAMEMD 0xA8D5FC
extern int DAT_00A8D5FC;

// FUNCTION: GAMEMD 0x5DA6C0 — YRpp: Unsorted::Init.
bool __cdecl FUN_005DA6C0();

#endif  // GG_MATCH_CORE_INIT_MISC_METHODS_H

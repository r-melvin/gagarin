// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every entry point and offset below was read off the user's own retail
//   gamemd.exe v1.001 with the local Ghidra CLI: the held pointer at
//   `[ECX+0x10]` (`MOV EAX,[ECX+0x10]`) and one dereference of each side
//   (`MOV EAX,[EAX]`, `CMP EAX,[ECX]`).
//
// Four remaining identical 27-byte identity tests.
//
// The object holds a pointer at +0x10. The test says: that pointer is not
// null, and the dword it points at equals the dword the argument points at --
// the two handles refer to the same underlying thing. All four remaining instances are
// byte-for-byte identical, relocations included.
//
// Only one dereference per side. Spelled with two (`**Held == **other`)
// cl emits an extra load on each side and the body diverges after the fourth
// instruction.
//
// These four receiver identities remain unresolved. Their common byte layout
// does not establish one shared source class. The fifth former entry,
// 0x724FA0, is now identified from its caller as ToolTipTable::HasCachedKey
// and lives with ToolTipManager instead of using this free-function view.
#ifndef GG_MATCH_CORE_SAME_OBJECT_TEST_SWEEP_H
#define GG_MATCH_CORE_SAME_OBJECT_TEST_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HandleHolder
{
    char   _pad000[0x10];   // +0x0000
    void** Held;            // +0x0010

    bool FUN_0052B4D0(void** other);   // FUNCTION: GAMEMD 0x52B4D0
    bool FUN_0052B600(void** other);   // FUNCTION: GAMEMD 0x52B600
    bool FUN_0055F6C0(void** other);   // FUNCTION: GAMEMD 0x55F6C0
    bool FUN_00746EA0(void** other);   // FUNCTION: GAMEMD 0x746EA0
};
GG_STATIC_ASSERT(offsetof(HandleHolder, Held) == 0x10);

#endif  // GG_MATCH_CORE_SAME_OBJECT_TEST_SWEEP_H

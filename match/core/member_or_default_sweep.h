// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every entry point and default-object address below was read off the user's
//   own retail gamemd.exe v1.001 with the local Ghidra CLI.
//
// Four twelve-byte accessors; 0x7B5440 now has its canonical Wstring owner.
//
// `MOV EAX,[ECX]; TEST EAX,EAX; JNZ +5; MOV EAX,<global>; RET`. The object's
// first dword holds a pointer that may be null; when it is, the accessor hands
// back a fixed global object instead, so callers never see a null. Two of the
// four fall back to 0x889F64 and two to 0x887734.
//
// The positive arm has to be written first: spelled as `if (p == 0) return
// <global>; return p;` cl lays the constant load ahead of the test and the
// bytes diverge from the first instruction.
//
// 0x7B5440 is the narrow Wstring getter: native CCFile construction at
// 0x473A5C calls it on its string argument, supplied from mode member +0x2C
// at 0x5D5C2D..0x5D5C35; that member is copied by 0x7B4690 and released
// by 0x7B46F0. The other three receivers retain their placeholder model.
// No common class identity is claimed for those remaining accessors.
#ifndef GG_MATCH_CORE_MEMBER_OR_DEFAULT_SWEEP_H
#define GG_MATCH_CORE_MEMBER_OR_DEFAULT_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x887734
extern char GLOBAL_00887734[];
// GLOBAL: GAMEMD 0x889F64
extern char GLOBAL_00889F64[];

struct DefaultingHolder
{
    void* Object;   // +0x0000  may be null; the global stands in when it is
};
GG_STATIC_ASSERT(offsetof(DefaultingHolder, Object) == 0x0);

void* FUN_007B5400(DefaultingHolder* self);   // FUNCTION: GAMEMD 0x7B5400
void* FUN_007B7100(DefaultingHolder* self);   // FUNCTION: GAMEMD 0x7B7100
void* FUN_007B7140(DefaultingHolder* self);   // FUNCTION: GAMEMD 0x7B7140

#endif  // GG_MATCH_CORE_MEMBER_OR_DEFAULT_SWEEP_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every entry point, callee address and the +0x90 offset below was read off
//   the user's own retail gamemd.exe v1.001 with the local Ghidra CLI
//   (`MOV ESI,dword ptr [ECX+0x90]` at each entry, the five call targets at
//   0x17/0x25/0x30/0x37/0x48 of each body).
//
// Six 83-byte "resolve the stored ID, then act on the object" commands.
//
// Each takes four stack arguments, uses only the third (a handle), and reads
// the owner's stored ID at +0x90. The ID 0x2325 is the sentinel for "use the
// handle itself", which is resolved through 0x726910; the sentinel -1 means
// "nothing stored" and reports failure; anything else is an index, resolved
// either through 0x510ED0 or through 0x502D30 depending on what the predicate
// at 0x510F60 says about it. Whatever comes back, if it is non-null it is
// handed to the command's own action and the function reports success.
//
// Only the action call differs across the six; the resolve chain is identical
// in all of them, relocations included.
#ifndef GG_MATCH_CORE_ID_RESOLVE_COMMAND_SWEEP_H
#define GG_MATCH_CORE_ID_RESOLVE_COMMAND_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* FUN_00726910(void* handle);   // GAMEMD 0x726910
extern "C" bool  FUN_00510F60(int id);         // GAMEMD 0x510F60
class HouseClass;
extern "C" HouseClass* FUN_00510ED0(int id);   // GAMEMD 0x510ED0: the house of a multiplayer index
extern "C" HouseClass* FUN_00502D30(int id);   // GAMEMD 0x502D30: the house of a country index
extern "C" void  FUN_0050D440(void* obj);       // GAMEMD 0x50D440  action
extern "C" void  FUN_0050D320(void* obj);       // GAMEMD 0x50D320  action
extern "C" void  FUN_004FC6D0(void* obj);       // GAMEMD 0x4FC6D0  action
extern "C" void  FUN_004FC790(void* obj);       // GAMEMD 0x4FC790  action
extern "C" void  FUN_004FC820(void* obj);       // GAMEMD 0x4FC820  action
extern "C" void  FUN_004FC8D0(void* obj);       // GAMEMD 0x4FC8D0  action

// Only the stored ID is touched; everything ahead of it stays opaque padding.
struct IdCommandOwner
{
    char _pad000[0x90];   // +0x0000
    int  StoredId;        // +0x0090

    // The six commands are members, not free functions taking the owner:
    // retail puts the owner in ECX and the first of the five arguments in EDX,
    // with the remaining four on the stack and `RET 0x10` — that is
    // `__fastcall` on a member. A plain __thiscall member would push all five
    // and return `RET 0x14`, so the convention is kept. Declared ascending by
    // retail address.
    // FUNCTION: GAMEMD 0x6E30C0
    bool __fastcall FUN_006E30C0(int, int, int, void* handle, int);
    // FUNCTION: GAMEMD 0x6E3120
    bool __fastcall FUN_006E3120(int, int, int, void* handle, int);
    // FUNCTION: GAMEMD 0x6E3180
    bool __fastcall FUN_006E3180(int, int, int, void* handle, int);
    // FUNCTION: GAMEMD 0x6E31E0
    bool __fastcall FUN_006E31E0(int, int, int, void* handle, int);
    // FUNCTION: GAMEMD 0x6E3240
    bool __fastcall FUN_006E3240(int, int, int, void* handle, int);
    // FUNCTION: GAMEMD 0x6E32A0
    bool __fastcall FUN_006E32A0(int, int, int, void* handle, int);
};
GG_STATIC_ASSERT(offsetof(IdCommandOwner, StoredId) == 0x90);


#endif  // GG_MATCH_CORE_ID_RESOLVE_COMMAND_SWEEP_H

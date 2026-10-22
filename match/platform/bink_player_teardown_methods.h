// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, guards and import identities read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x432700 and
//   0x432A60. Neither address is bound by YRpp.
//
// Two byte-identical teardowns for a Bink video player object: release the
// helper allocation at +0x20, close the Bink handle at +0x04, close the Win32
// file handle at +0x28. Each is written out longhand rather than shared, per
// the family rule.
//
// The two import slots are identified from the call sites: 0x7E15A4 is
// BinkClose (it sits in the BINKW32 block alongside the already-confirmed
// BinkPause at 0x7E15B0) and 0x7E11E0 is CloseHandle, which is why the third
// field's empty value is -1 rather than 0.
#ifndef GG_MATCH_PLATFORM_BINK_PLAYER_TEARDOWN_METHODS_H
#define GG_MATCH_PLATFORM_BINK_PLAYER_TEARDOWN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Declared __declspec(dllimport) so the calls go indirect through the IAT slot
// (`CALL dword ptr [0x7E15A4]`, six bytes) as retail does; without it cl emits
// a five-byte direct call to an import thunk and the lengths diverge.
extern "C" __declspec(dllimport) void __stdcall BinkClose(void* bink);      // IAT 0x7E15A4
extern "C" __declspec(dllimport) int  __stdcall CloseHandle(void* handle);  // IAT 0x7E11E0

// The helper at +0x20 is destroyed by hand and then freed: retail calls
// 0x6C9AE0 with the pointer in ECX, then pushes it to the __cdecl free at
// 0x7C8B3D. That is an explicit destructor call followed by operator delete,
// not the compiler-generated deleting destructor - a `??_G` would have folded
// the two into one call.
void __fastcall FUN_006C9AE0(void* helper);
extern "C" void __cdecl FUN_007C8B3D(void* block);

struct BinkPlayer_00432700
{
    char  _pad000[0x4];
    void* Bink;      // +0x0004
    char  _pad008[0x20 - 0x08];
    void* Helper;    // +0x0020
    char  _pad024[0x4];
    void* File;      // +0x0028  Win32 HANDLE, empty value INVALID_HANDLE_VALUE

    // FUNCTION: GAMEMD 0x432700
    void FUN_00432700();
    // FUNCTION: GAMEMD 0x432A60
    void FUN_00432A60();
};
GG_STATIC_ASSERT(offsetof(BinkPlayer_00432700, Bink) == 0x04);
GG_STATIC_ASSERT(offsetof(BinkPlayer_00432700, Helper) == 0x20);
GG_STATIC_ASSERT(offsetof(BinkPlayer_00432700, File) == 0x28);

#endif  // GG_MATCH_PLATFORM_BINK_PLAYER_TEARDOWN_METHODS_H

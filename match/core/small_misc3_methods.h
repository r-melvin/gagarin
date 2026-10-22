// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. Import names read from the IAT
//   thunks. None of these addresses is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC3_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC3_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

// Bink video. Declared __declspec(dllimport) so the call goes indirect through
// the IAT slot (`CALL dword ptr [0x7E15B0]`, six bytes) as retail does; without
// it cl emits a five-byte direct call to an import thunk and the instruction
// lengths diverge.
extern "C" __declspec(dllimport) void __stdcall BinkPause(void* bink, int pause);   // IAT 0x7E15B0
extern "C" __declspec(dllimport) int  __stdcall BinkWait(void* bink);               // IAT 0x7E15C0

// __stdcall, one argument, no return used. Called with an HRESULT-shaped
// constant (0x80004003, E_POINTER) when a required pointer is missing.
void __stdcall FUN_007DC720(unsigned int hr);

// __thiscall, one argument.
struct Obj_006C9D00 { void FUN_006C9D30(int value); };

// FUNCTION: GAMEMD 0x407480 — the held node, unless it points at its own owner.
// Retail computes this branchlessly (`SUB; NEG; SBB; AND`), which is what a
// conditional expression compiles to here rather than a branch.
ListNode* __fastcall FUN_00407480(ListNode* self);

struct Obj_00402100
{
    char  _pad000[0xD4];
    void* Dispatch;   // +0x00D4  table of __thiscall slots

    // FUNCTION: GAMEMD 0x402170
    void FUN_00402170();
};
GG_STATIC_ASSERT(offsetof(Obj_00402100, Dispatch) == 0xD4);

typedef void (__fastcall* DispatchSlot)(Obj_00402100*);
#define DISPATCH_CALL(o, off) \
    ((*(DispatchSlot*)((char*)(o)->Dispatch + (off)))(o))

struct Obj_00432C00
{
    char              _pad00[0x4];
    void*             Bink;         // +0x0004
    char              _pad08[0x18];
    Obj_006C9D00*     unknown_20;   // +0x0020
    char              _pad24[0x2D - 0x24];
    unsigned char     unknown_2D;   // +0x002D

    // FUNCTION: GAMEMD 0x432C10
    void FUN_00432C10(int value);
    // FUNCTION: GAMEMD 0x432C30
    void FUN_00432C30(int pause);
    // FUNCTION: GAMEMD 0x433020
    void FUN_00433020();
};
GG_STATIC_ASSERT(offsetof(Obj_00432C00, Bink) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_00432C00, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Obj_00432C00, unknown_2D) == 0x2D);

struct Obj_0045A000
{
    void* Ptr;   // +0x0000

    // FUNCTION: GAMEMD 0x45A050
    void* FUN_0045A050();
};

#endif  // GG_MATCH_CORE_SMALL_MISC3_METHODS_H

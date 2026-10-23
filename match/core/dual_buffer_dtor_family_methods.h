// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI at the six remaining LCWStraw/LZOPipe/LZOStraw entries. The members
//   come straight off the instructions: the vtable pointer at +0 (`MOV dword
//   ptr [ESI],imm32`, the imm being this instance's vtable), the first buffer
//   at +0x14 (`MOV EAX,[ESI+0x14]`, `MOV dword ptr [ESI+0x14],0`) and the
//   second at +0x18. The deleting form reads its flags byte from `[ESP+8]`.
//   The trailing `MOV ECX,ESI; CALL` is the base class destructor, called
//   __thiscall after both buffers are released.
//
//   Two shapes over the same object: the 53-byte destructor, and the 73-byte
//   scalar-deleting destructor which is that destructor inlined plus the
//   `flags & 1` free and the `this` return. Within each shape the three members
//   differ only in the vtable constant and the call relocations. The class
//   is retained as an address-scoped layout view. Retail RTTI identifies
//   the remaining groups as LCWStraw and LZOPipe/LZOStraw. Their Pipe and
//   Straw cleanup calls retain their distinct observed target addresses.
#ifndef GG_MATCH_CORE_DUAL_BUFFER_DTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_DUAL_BUFFER_DTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);

// The vtables of LCWStraw (0x7ECF44), LZOPipe (0x7ED37C) and LZOStraw
// (0x7ED394). Their VTABLE annotations live with the classes in
// match/platform/compression_straws.h; these address-named references are the
// view this family's destructors store.
extern char VT_007ECF44;
extern char VT_007ED37C;
extern char VT_007ED394;

struct DualBuf
{
    char* Vptr;          // +0x0000
    char  _pad004[0x10]; // +0x0004  base subobject, never touched here
    void* BufA;          // +0x0014
    void* BufB;          // +0x0018

    void Dtor_00552450();
    void Dtor_0055C310();
    void Dtor_0055C780();

    void* FUN_005525F0(char flags);
    void* FUN_0055C6D0(char flags);
    void* FUN_0055C990(char flags);
};
GG_STATIC_ASSERT(offsetof(DualBuf, Vptr) == 0x0 &&
                 offsetof(DualBuf, BufA) == 0x14 &&
                 offsetof(DualBuf, BufB) == 0x18 &&
                 sizeof(DualBuf) == 0x1C);

// The 53-byte destructor: seat this class's vtable, release both buffers and
// null them, then chain to the base destructor.
#define GG_DUALBUF_DTOR_BODY(TAG, VT, BASE_CLEANUP)                                     \
void DualBuf::Dtor_##TAG()                                                \
{                                                                         \
    this->Vptr = &VT_##VT;                                                \
    gg_free(this->BufA);                                                  \
    this->BufA = 0;                                                       \
    gg_free(this->BufB);                                                  \
    this->BufB = 0;                                                       \
    BASE_CLEANUP;                                                     \
}

// The 73-byte scalar-deleting destructor: the same body inlined, then the
// caller-requested free and the `this` return.
#define GG_DUALBUF_SDD_BODY(TAG, VT, BASE_CLEANUP)                                      \
void* DualBuf::FUN_##TAG(char flags)                                      \
{                                                                         \
    this->Vptr = &VT_##VT;                                                \
    gg_free(this->BufA);                                                  \
    this->BufA = 0;                                                       \
    gg_free(this->BufB);                                                  \
    this->BufB = 0;                                                       \
    BASE_CLEANUP;                                                     \
    if (flags & 1) {                                                      \
        gg_free(this);                                                    \
    }                                                                     \
    return this;                                                          \
}

#endif  // GG_MATCH_CORE_DUAL_BUFFER_DTOR_FAMILY_METHODS_H

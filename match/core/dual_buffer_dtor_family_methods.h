// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI at 0x552060 and 0x552390 and their six siblings. The members
//   come straight off the instructions: the vtable pointer at +0 (`MOV dword
//   ptr [ESI],imm32`, the imm being this instance's vtable), the first buffer
//   at +0x14 (`MOV EAX,[ESI+0x14]`, `MOV dword ptr [ESI+0x14],0`) and the
//   second at +0x18. The deleting form reads its flags byte from `[ESP+8]`.
//   The trailing `MOV ECX,ESI; CALL` is the base class destructor, called
//   __thiscall after both buffers are released.
//
//   Two shapes over the same object: the 53-byte destructor, and the 73-byte
//   scalar-deleting destructor which is that destructor inlined plus the
//   `flags & 1` free and the `this` return. Within each shape the four members
//   differ only in the vtable constant and the call relocations. The class
//   carries no name in the binary or in the YRpp map, so the instances keep
//   address-tagged placeholder names.
#ifndef GG_MATCH_CORE_DUAL_BUFFER_DTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_DUAL_BUFFER_DTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);

// VTABLE: GAMEMD 0x007ECF2C
extern char VT_007ECF2C;
// VTABLE: GAMEMD 0x007ECF44
extern char VT_007ECF44;
// VTABLE: GAMEMD 0x007ED37C
extern char VT_007ED37C;
// VTABLE: GAMEMD 0x007ED394
extern char VT_007ED394;

struct DualBuf
{
    char* Vptr;          // +0x0000
    char  _pad004[0x10]; // +0x0004  base subobject, never touched here
    void* BufA;          // +0x0014
    void* BufB;          // +0x0018

    // FUNCTION: GAMEMD 0x631C80 (decl; reloc) — the base class destructor as
    // called from 0x552060 and 0x55C310; 0x552450 and 0x55C780 call 0x6C9850
    // instead, which the differ normalises away with the other call
    // relocations.
    void BaseDtor();

    void Dtor_00552060();
    void Dtor_00552450();
    void Dtor_0055C310();
    void Dtor_0055C780();
};
GG_STATIC_ASSERT(offsetof(DualBuf, Vptr) == 0x0 &&
                 offsetof(DualBuf, BufA) == 0x14 &&
                 offsetof(DualBuf, BufB) == 0x18 &&
                 sizeof(DualBuf) == 0x1C);

// The 53-byte destructor: seat this class's vtable, release both buffers and
// null them, then chain to the base destructor.
#define GG_DUALBUF_DTOR_BODY(TAG, VT)                                     \
void DualBuf::Dtor_##TAG()                                                \
{                                                                         \
    this->Vptr = &VT_##VT;                                                \
    gg_free(this->BufA);                                                  \
    this->BufA = 0;                                                       \
    gg_free(this->BufB);                                                  \
    this->BufB = 0;                                                       \
    this->BaseDtor();                                                     \
}

// The 73-byte scalar-deleting destructor: the same body inlined, then the
// caller-requested free and the `this` return.
#define GG_DUALBUF_SDD_BODY(TAG, VT)                                      \
void* __fastcall FUN_##TAG(DualBuf* self, int, char flags)                \
{                                                                         \
    self->Vptr = &VT_##VT;                                                \
    gg_free(self->BufA);                                                  \
    self->BufA = 0;                                                       \
    gg_free(self->BufB);                                                  \
    self->BufB = 0;                                                       \
    self->BaseDtor();                                                     \
    if (flags & 1) {                                                      \
        gg_free(self);                                                    \
    }                                                                     \
    return self;                                                          \
}

void* __fastcall FUN_00552390(DualBuf* self, int, char flags);
void* __fastcall FUN_005525F0(DualBuf* self, int, char flags);
void* __fastcall FUN_0055C6D0(DualBuf* self, int, char flags);
void* __fastcall FUN_0055C990(DualBuf* self, int, char flags);

#endif  // GG_MATCH_CORE_DUAL_BUFFER_DTOR_FAMILY_METHODS_H

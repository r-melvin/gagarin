// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x49F9D0 and its siblings: the plain (non-deleting)
//   destructor of the vector template for instantiations that reseat a base
//   vtable on the way out. Members touched are exactly the ones the
//   instructions name: the vtable pointer at +0 (`MOV dword ptr [ESI],imm32`),
//   the items pointer at +4 (`MOV EAX,[ESI+4]`, `MOV [ESI+4],EBX`), the
//   capacity at +8 (`MOV [ESI+8],EBX`) and the allocated flag at +0xD
//   (`CMP [ESI+0xD],BL`, `MOV [ESI+0xD],BL`). Zero is held in EBX and serves
//   both compares and all three stores.
//
//   This is the family of match/core/vector_clear_family_methods.cpp plus
//   a single vtable store: 45 bytes against that family's 39, the extra six
//   being the one `C7 06 imm32`. These carry no name in the binary or in the
//   YRpp map and keep their placeholder names.
#ifndef GG_MATCH_CORE_VECTOR_VTABLE_PLAIN_DTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_VTABLE_PLAIN_DTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);

// VTABLE: GAMEMD 0x007E37EC
extern char VT_007E37EC;
// VTABLE: GAMEMD 0x007E4DB8
extern char VT_007E4DB8;
// VTABLE: GAMEMD 0x007EAA08
extern char VT_007EAA08;
// VTABLE: GAMEMD 0x007EAC28
extern char VT_007EAC28;
// VTABLE: GAMEMD 0x007EAC48
extern char VT_007EAC48;
// VTABLE: GAMEMD 0x007EAC68
extern char VT_007EAC68;
// VTABLE: GAMEMD 0x007F0D9C
extern char VT_007F0D9C;

struct VtblVector_0049F9D0
{
    char* Vptr;          // +0x0000
    void* Items;         // +0x0004
    int   Capacity;      // +0x0008
    char  _pad00C;       // +0x000C
    char  IsAllocated;   // +0x000D
};
GG_STATIC_ASSERT(offsetof(VtblVector_0049F9D0, Vptr)        == 0x0);
GG_STATIC_ASSERT(offsetof(VtblVector_0049F9D0, Items)       == 0x4);
GG_STATIC_ASSERT(offsetof(VtblVector_0049F9D0, Capacity)    == 0x8);
GG_STATIC_ASSERT(offsetof(VtblVector_0049F9D0, IsAllocated) == 0xD);

#define GG_VTBL_PLAIN_DTOR_BODY(ADDR, VT)                                 \
void __fastcall FUN_##ADDR(VtblVector_0049F9D0* self)                     \
{                                                                         \
    self->Vptr = &VT_##VT;                                                \
    if (self->Items != 0 && self->IsAllocated != 0) {                     \
        gg_free(self->Items);                                             \
        self->Items = 0;                                                  \
    }                                                                     \
    self->IsAllocated = 0;                                                \
    self->Capacity = 0;                                                   \
}

// FUNCTION: GAMEMD 0x0049F9D0
void __fastcall FUN_0049F9D0(VtblVector_0049F9D0* self);
// FUNCTION: GAMEMD 0x00679F70
void __fastcall FUN_00679F70(VtblVector_0049F9D0* self);
// FUNCTION: GAMEMD 0x00679FA0
void __fastcall FUN_00679FA0(VtblVector_0049F9D0* self);
// FUNCTION: GAMEMD 0x00679FD0
void __fastcall FUN_00679FD0(VtblVector_0049F9D0* self);
// FUNCTION: GAMEMD 0x0067A000
void __fastcall FUN_0067A000(VtblVector_0049F9D0* self);
// FUNCTION: GAMEMD 0x0067A030
void __fastcall FUN_0067A030(VtblVector_0049F9D0* self);
// FUNCTION: GAMEMD 0x0067A060
void __fastcall FUN_0067A060(VtblVector_0049F9D0* self);
// FUNCTION: GAMEMD 0x00771A00
void __fastcall FUN_00771A00(VtblVector_0049F9D0* self);

#endif  // GG_MATCH_CORE_VECTOR_VTABLE_PLAIN_DTOR_FAMILY_METHODS_H

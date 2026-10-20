// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI at the retail vtable 0x7E3A78 identifies BitFont; slot zero points
//   to 0x434A40. That entry stores the vptr at +0, reads cache +8 and payload
//   +4, then releases payload pointers at +0x18/+0x1C. The resolver at
//   0x433990 allocates the payload as 0x24 bytes and writes its count at +0x20.
//   Complete entry evidence: /tmp/gagarin_bitfont_dtor_00434a40.json.
#ifndef GG_MATCH_UI_BIT_FONT_SCALAR_DTOR_00434A40_H
#define GG_MATCH_UI_BIT_FONT_SCALAR_DTOR_00434A40_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct BitFontPayload_00434A40
{
    char unknown_00[0x18];
    void* unknown_18;
    void* unknown_1C;
    int unknown_20;
};
GG_STATIC_ASSERT(offsetof(BitFontPayload_00434A40, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BitFontPayload_00434A40, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(BitFontPayload_00434A40, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(BitFontPayload_00434A40, unknown_20) == 0x20);
GG_STATIC_ASSERT(sizeof(BitFontPayload_00434A40) == 0x24);

struct BitFontScalarDtorView_00434A40
{
    void* unknown_00;
    BitFontPayload_00434A40* unknown_04;
    void* unknown_08;

    // FUNCTION: GAMEMD 0x434A40 — ECX=this, one stack flags argument, RET 4.
    // This is slot zero of BitFont's vtable at 0x7E3A78 (scalar deleting dtor).
    void* ScalarDeletingDestructor(unsigned int flags);
};
GG_STATIC_ASSERT(offsetof(BitFontScalarDtorView_00434A40, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BitFontScalarDtorView_00434A40, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(BitFontScalarDtorView_00434A40, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(BitFontScalarDtorView_00434A40) == 0x0C);

// VTABLE: GAMEMD 0x7E3A78 — slot zero is the scalar deleting destructor.
struct BitFontScalarDtorVtable_00434A40
{
    void* slot_00;
};
GG_STATIC_ASSERT(offsetof(BitFontScalarDtorVtable_00434A40, slot_00) == 0x00);
GG_STATIC_ASSERT(sizeof(BitFontScalarDtorVtable_00434A40) == 0x04);

// LIBRARY: GAMEMD 0x7C8B3D — retail delete/free wrapper, __cdecl.
void __cdecl operator delete(void* block);
// LIBRARY: GAMEMD 0x7C93E8 — CRT heap release, including small-block handling.
extern "C" void __cdecl free(void* block);

#endif  // GG_MATCH_UI_BIT_FONT_SCALAR_DTOR_00434A40_H

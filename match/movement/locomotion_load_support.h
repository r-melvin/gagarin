// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; scoped call/layout views for LocomotionClass::Load.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_LOAD_SUPPORT_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_LOAD_SUPPORT_H

#include <stddef.h>
#include <objidl.h>
#include "../_rt/gg_static_assert.h"

// IStream slot order read at 0x55AAC0; only Read is used by this support view.
struct IStream_0055AAC0
{
    virtual long __stdcall QueryInterface(const void*, void**) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual long __stdcall Read(void*, unsigned long, unsigned long*) = 0;
};
GG_STATIC_ASSERT(sizeof(IStream_0055AAC0) == 4);
GG_STATIC_ASSERT(sizeof(IStream) == 4);

// GLOBAL: GAMEMD 0xB0C110
struct Swizzle_0055AAC0
{
    // FUNCTION: GAMEMD 0x6CF240 (decl; reloc)
    long __stdcall FUN_006CF240(void** pointer);
    // FUNCTION: GAMEMD 0x6CF2C0 (decl; reloc)
    long __stdcall FUN_006CF2C0(int id, void* object);
};
extern Swizzle_0055AAC0 DAT_00B0C110;

#endif

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x55AAC0: the stream vtable slot `[EAX+0xC]`
//   / `[EBP+0xC]` (IStream::Read), the locomotor slot `[EAX+0x24]` called
//   with ECX=this and no arguments, the member `[ESI+0x14]` saved around the
//   raw read, and the two swizzle targets `[ESI+0xC]` and `[ESI+0x8]`. The
//   0xB0C110 receiver is pushed as the first stack argument of the two
//   `RET 8`/`RET 0xC` helpers 0x6CF2C0 / 0x6CF240. YRpp names the function
//   (LocomotionClass::Load), slot 9 (Size) and 0xB0C110 (SwizzleManagerClass)
//   - name-only cross-check.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_LOAD_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_LOAD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

typedef long HRESULT;

// Minimal IStream: only the vtable order matters. COM methods are __stdcall,
// so `this` is the first stacked argument (PUSH pStm; CALL [vtbl+0xC]).
struct IStream_0055AAC0
{
    virtual long          __stdcall QueryInterface(const void* riid, void** ppv) = 0; // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                                     // +0x04
    virtual unsigned long __stdcall Release() = 0;                                    // +0x08
    virtual long          __stdcall Read(void* pv, unsigned long cb,
                                         unsigned long* pcbRead) = 0;                 // +0x0C
};

// The swizzle manager at 0xB0C110; both entry points are __stdcall with the
// manager as the first stacked argument.
struct Swizzle_0055AAC0
{
    // FUNCTION: GAMEMD 0x6CF2C0 (decl; reloc) — register (old id, new object).
    HRESULT __stdcall FUN_006CF2C0(int id, void* object);
    // FUNCTION: GAMEMD 0x6CF240 (decl; reloc) — queue a pointer for fix-up.
    HRESULT __stdcall FUN_006CF240(void** pointer);
};

// GLOBAL: GAMEMD 0xB0C110
extern Swizzle_0055AAC0 DAT_00B0C110;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct LocoVtbl_0055AAC0;

struct Loco_0055AAC0
{
    LocoVtbl_0055AAC0* Vtbl;   // +0x0000
    char  _pad004[0x4];        // +0x0004
    void* At_8;                // +0x0008  swizzled
    void* At_C;                // +0x000C  swizzled
    char  _pad010[0x4];        // +0x0010
    void* At_14;               // +0x0014  preserved across the raw read
};
GG_STATIC_ASSERT(offsetof(Loco_0055AAC0, At_8)  == 0x8);
GG_STATIC_ASSERT(offsetof(Loco_0055AAC0, At_C)  == 0xC);
GG_STATIC_ASSERT(offsetof(Loco_0055AAC0, At_14) == 0x14);

typedef unsigned (Loco_0055AAC0::*FnSize_0055AAC0)();

struct LocoVtbl_0055AAC0
{
    char _pad000[0x24];          // +0x0000
    FnSize_0055AAC0 At_24;       // +0x0024  YRpp: Size
};
GG_STATIC_ASSERT(offsetof(LocoVtbl_0055AAC0, At_24) == 0x24);

// FUNCTION: GAMEMD 0x55AAC0 — YRpp: LocomotionClass::Load. COM __stdcall:
// the locomotor arrives as the first stacked argument, the stream second.
HRESULT __stdcall FUN_0055AAC0(Loco_0055AAC0* self, IStream_0055AAC0* pStm);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_LOAD_METHODS_H

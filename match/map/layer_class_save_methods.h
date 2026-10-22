// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x551B20. The receiver is a LayerClass (its callers,
//   DisplayClass::Save 0x4AE720 and 0x67D300, pass each layer of the array at
//   0x8A0360 in ECX), vector-shaped — Items @0x04
//   and Count @0x10 — and `Write` is dispatched through COM vtable slot +0x10,
//   which is ISequentialStream::Write.
//
// Note on the frame: retail has no `SUB ESP`, yet spills the element count to
// `[ESP+0x20]`, which resolves to the incoming argument slot. VC6 reuses the
// parameter's stack home for the local because the parameter itself lives in
// ESI for the whole body. That is an allocation choice, not something the
// source expresses — a plain `int` local is what produces it.
#ifndef GG_MATCH_MAP_LAYER_CLASS_SAVE_METHODS_H
#define GG_MATCH_MAP_LAYER_CLASS_SAVE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef long Gg_HRESULT;

#define GG_S_OK       0
#define GG_E_POINTER  ((Gg_HRESULT)0x80004003)

// Minimal IStream: the IUnknown trio, ISequentialStream::Read, then Write at
// +0x10. All __stdcall with `this` pushed, as COM requires.
struct Gg_IStream
{
    virtual Gg_HRESULT __stdcall QueryInterface(void* iid, void** ppv) = 0;   // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                             // +0x04
    virtual unsigned long __stdcall Release() = 0;                            // +0x08
    virtual Gg_HRESULT __stdcall Read(void* pv, unsigned long cb,
                                      unsigned long* pcbRead) = 0;            // +0x0C
    virtual Gg_HRESULT __stdcall Write(const void* pv, unsigned long cb,
                                       unsigned long* pcbWritten) = 0;        // +0x10
};

struct LayerClass
{
    void* _vtable;   // +0x00
    void* Items;     // +0x04
    int   Capacity;  // +0x08
    int   IsAlloc;   // +0x0C
    int   Count;     // +0x10

    Gg_HRESULT Save(Gg_IStream* pStm);   // GAMEMD 0x551B20 __thiscall
};
GG_STATIC_ASSERT(offsetof(LayerClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(LayerClass, Count) == 0x10);

#endif  // GG_MATCH_MAP_LAYER_CLASS_SAVE_METHODS_H

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: RTTI .?AVNeuronClass@@ (primary vtable 0x7E3DF0, +0x04 0x7E3DD4, +0x08 0x7E3DCC, +0x0C 0x7E3DC4);
//   constructor 0x43A350 (zeroes +0x24..+0x2C, stores the frame counter at +0x30, registers in
//   0xB0F5D8 and 0xB0F670); sizeof 0x38 from the allocation at 0x6C5E3C.
#ifndef GG_MATCH_LAYOUT_NEURON_CLASS_H
#define GG_MATCH_LAYOUT_NEURON_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "../core/vector_class.h"

// VTABLE: GAMEMD 0x7E3DF0 (IPersistStream side)
// VTABLE: GAMEMD 0x7E3DD4 (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7E3DCC (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7E3DC4 (INoticeSource side, +0x0C)
class NeuronClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x43A350 (declaration; constructor)
    NeuronClass();
    // The stream loader's in-place construction (expanded inside Load 0x43A540).
    NeuronClass(const AbstractNoInit& noInit) : AbstractClass(noInit) {}
    // FUNCTION: GAMEMD 0x43A440 (declaration; destructor; slot 8 = 0x43A9C0)
    virtual ~NeuronClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x43A500
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x43A540
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x43A5B0
    virtual int vf_11();                                                  // 11  0x43A9A0
    virtual int vf_12();                                                  // 12  0x43A9B0
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x43A5D0

    int unknown_24;   // +0x24 ctor 0 (swizzled by Load 0x43A540)
    int unknown_28;   // +0x28 ctor 0 (swizzled by Load)
    int unknown_2C;   // +0x2C ctor 0 (swizzled by Load)
    int unknown_30;   // +0x30 ctor: the frame counter
    int unknown_34;   // +0x34 (inside the allocation, not touched by the constructor)

    // GLOBAL: GAMEMD 0xB0F5D8
    static DynamicVectorClass<NeuronClass*> Array;
};
GG_STATIC_ASSERT(offsetof(NeuronClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(NeuronClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(sizeof(NeuronClass) == 0x38);

#endif  // GG_MATCH_LAYOUT_NEURON_CLASS_H

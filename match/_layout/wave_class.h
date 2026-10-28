// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x00847EB0 `.?AVWaveClass@@`; class hierarchy descriptor 0x0080D408.
//   Bases in RTTI (declaration) order: ObjectClass +0x0.
// VTABLE: GAMEMD 0x7F6BF4 (122 slots)
// VTABLE: GAMEMD 0x7F6BD8 (6 slots, subobject +0x4)
// VTABLE: GAMEMD 0x7F6BD0 (1 slots, subobject +0x8)
// VTABLE: GAMEMD 0x7F6BC8 (1 slots, subobject +0xC)
//   Allocation: operator new (0x7C8E17) of 0x240 bytes at 0x6BF0BC, 0x6FF449, 0x6FF623.
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_WAVE_CLASS_H
#define GG_MATCH_LAYOUT_WAVE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_class.h"
#include "facing_class.h"
#include "../core/vector_class.h"

class CellClass;

// The 0x18-byte facing-like member at +0x1D8; its constructor is the out-of-line routine at 0x4C91C0.
struct WaveFacing_1D8 : public FacingClass
{
    // FUNCTION: GAMEMD 0x4C91C0 (decl; reloc)
    WaveFacing_1D8();
};

class WaveClass : public ObjectClass
{
public:
    // FUNCTION: GAMEMD 0x75EBE0 (decl; reloc) -- default constructor, called by the class factory at 0x6BF0CF.
    WaveClass();
    virtual HRESULT __stdcall GetClassID(CLSID *pClassID);      // 3  0x75F840: override (SDK declaration)
    virtual long __stdcall Load(struct IStream *);              // 5  0x75F650: override of ObjectClass
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);// 6  0x75F7D0: override (declaration from the base header)
    virtual ~WaveClass();                                       // 8  0x763200: deleting destructor override
    virtual void vf_10(void* target, bool removed);                         // 10  0x75F610: override of ObjectClass
    virtual int vf_11();                                        // 11  0x7631F0: override (declaration from the base header)
    virtual int vf_12();                                        // 12  0x75F880: override (declaration from the base header)
    virtual void vf_23();                                       // 23  0x760F50: override of ObjectClass
    virtual int vf_30();                                        // 30  0x75F890: override of ObjectClass
    virtual class ObjectTypeClass * vf_34();                   // 34  0x75F8A0: override of ObjectClass
    virtual bool vf_53();                                       // 53  0x75F980: override of ObjectClass
    virtual bool vf_54(struct CoordStruct const &, int);        // 54  0x75F8B0: override of ObjectClass
    virtual void vf_69(Point2D* point, RectangleStruct* clip);  // 69  0x75F9F0: override of ObjectClass (RET 8)
    void* unknown_AC;  // +0xAC store at 0x75E975; cleared by vf_10 when it expires (0x75F610)
    int unknown_B0;  // +0xB0 store at 0x75E97B
    unsigned char unknown_B4[120];  // +0xB4
    unsigned char unknown_12C;  // +0x12C store at 0x75E981
    unsigned char unknown_12D;  // +0x12D store at 0x75E988
    unsigned char unknown_12E[2];  // +0x12E
    int unknown_130;  // +0x130 store at 0x75E98E
    int unknown_134;  // +0x134 store at 0x75E998
    int unknown_138;  // +0x138 store at 0x75E969
    int unknown_13C;  // +0x13C store at 0x75E99E
    int unknown_140;  // +0x140 store at 0x75E96F
    int unknown_144;  // +0x144 store at 0x75E9A4
    int unknown_148;  // +0x148 store at 0x75E9AA
    int unknown_14C;  // +0x14C store at 0x75E9B0
    unsigned char unknown_150[80];  // +0x150
    int unknown_1A0;  // +0x1A0 store at 0x75E9B6
    int unknown_1A4;  // +0x1A4 store at 0x75E9BC
    int unknown_1A8;  // +0x1A8 store at 0x75E9C2
    unsigned char unknown_1AC[32];  // +0x1AC
    int unknown_1CC;  // +0x1CC store at 0x75EB51
    int unknown_1D0;  // +0x1D0 store at 0x75E9CE
    void* unknown_1D4;  // +0x1D4 store at 0x75E9D4; cleared by vf_10 when it expires (0x75F610)
    WaveFacing_1D8 unknown_1D8;  // +0x1D8 (0x18)
    DynamicVectorClass<CellClass*> unknown_1F0;  // +0x1F0 (0x18) vptr store at 0x75E9FE; Save writes Count entries of Items (0x75F7D0)
    unsigned char unknown_208[56];  // +0x208
};
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_12C) == 0x12C);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_12D) == 0x12D);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_130) == 0x130);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_134) == 0x134);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_138) == 0x138);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_13C) == 0x13C);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_140) == 0x140);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_144) == 0x144);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_148) == 0x148);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_14C) == 0x14C);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_1A0) == 0x1A0);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_1A4) == 0x1A4);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_1A8) == 0x1A8);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_1CC) == 0x1CC);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_1D0) == 0x1D0);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_1D4) == 0x1D4);
GG_STATIC_ASSERT(offsetof(WaveClass, unknown_1F0) == 0x1F0);
GG_STATIC_ASSERT(sizeof(WaveClass) == 0x240);

#endif  // GG_MATCH_LAYOUT_WAVE_CLASS_H

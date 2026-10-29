// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout merged from the per-TU views of this class (constructors 0x554830 / 0x554760 / 0x5548E0, destructor
//   0x554910, Activate 0x554A60, Deactivate 0x554A80, ChangeLevels 0x554AA0, Calculate 0x554AF0). Every offset
//   below is read by one of those bodies.
#ifndef GG_MATCH_LAYOUT_LIGHT_SOURCE_CLASS_H
#define GG_MATCH_LAYOUT_LIGHT_SOURCE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "rad_site_class.h"   // TintStruct

// The world position handed to the constructor (three ints).
struct LightTint
{
    int Red;
    int Green;
    int Blue;
};

struct Obj_004A1D30;

class LightSourceClass : public AbstractClass
{
public:
    // Nested element type named by the retail vector RTTI; declared only.
    class PendingCellClass;

    LightSourceClass();
    LightSourceClass(LightTint tint, int a4, int a5, int a6, int a7, int a8);
    LightSourceClass(const AbstractNoInit& noInit);
    virtual ~LightSourceClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    virtual void vf_13(struct Obj_004A1D30*);

    void Activate(unsigned long dwZero);                              // GAMEMD 0x554A60
    void Deactivate(unsigned long dwZero);                            // GAMEMD 0x554A80
    void FUN_00554A80(char on);                                       // GAMEMD 0x554A80 (decl; reloc)
    void ChangeLevels(int nIntensity, TintStruct Tint, unsigned long mode); // GAMEMD 0x554AA0
    void Calculate(unsigned long dwZero);                             // GAMEMD 0x554AF0

    int unknown_24;           // +0x24 LightIntensity
    int TintRed;              // +0x28 LightTint.Red   (constructor argument a6)
    int TintGreen;            // +0x2C LightTint.Green (a7)
    int TintBlue;             // +0x30 LightTint.Blue  (a8)
    int unknown_34;           // +0x34 DetailLevel (2 in the full constructor)
    LightTint Tint;           // +0x38 Location (the constructor's first argument)
    int unknown_44;           // +0x44 LightVisibility (a4)
    unsigned char Activated;  // +0x48
};
GG_STATIC_ASSERT(offsetof(LightSourceClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(LightSourceClass, TintRed) == 0x28);
GG_STATIC_ASSERT(offsetof(LightSourceClass, TintGreen) == 0x2C);
GG_STATIC_ASSERT(offsetof(LightSourceClass, TintBlue) == 0x30);
GG_STATIC_ASSERT(offsetof(LightSourceClass, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(LightSourceClass, Tint) == 0x38);
GG_STATIC_ASSERT(offsetof(LightSourceClass, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(LightSourceClass, Activated) == 0x48);

#endif  // GG_MATCH_LAYOUT_LIGHT_SOURCE_CLASS_H

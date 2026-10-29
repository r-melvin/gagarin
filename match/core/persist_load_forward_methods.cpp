// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Persistence Load slots (primary table slot 5) whose body is the base load
// (AbstractClass body 0x410380) followed by re-seating every vtable pointer:
// a failed base load returns its code, otherwise the object is rebuilt in
// place with the no-initialisation base constructor (0x4101C0) and zero is
// returned. Each class is declared only as far as its virtuals; no layout is
// claimed.

#include <new.h>
#include "../_layout/abstract_class.h"

class LightSourceView_005550C0 : public AbstractClass
{
public:
    LightSourceView_005550C0(const AbstractNoInit& noInit) : AbstractClass(noInit) {}
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
};

// FUNCTION: GAMEMD 0x5550C0
HRESULT __stdcall LightSourceView_005550C0::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) LightSourceView_005550C0(AbstractNoInit());
    return 0;
}

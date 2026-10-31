// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   TClassFactory<T>: the engine's persistence class factory, one template
//   instantiated per persistable class. RTTI in the retail binary names 77
//   instantiations (`.?AV?$TClassFactory@V<T>@@@@`, bases IClassFactory,
//   IUnknown), each with a five-slot vtable at 0x7F3768 + 0x18*n:
//   QueryInterface, AddRef, Release, CreateInstance, LockServer.
//   QueryInterface, AddRef, Release and LockServer are byte-identical across
//   all 77 (Release differs only in the rel32 of its operator delete call).
//   CreateInstance differs per T (allocation size and T's constructor).
//
//   Layout: vptr +0x0, RefCount +0x4. RefCount is the counter AddRef/Release
//   update with InterlockedIncrement/Decrement on [this+4] and LockServer
//   updates without interlocking (0x6BEF90). Size 8 from the allocation site:
//   the registration routine (0x6BB9A0 onward) does `push 8; call operator
//   new`, the constructor, then CoRegisterClassObject(CLSID, factory,
//   CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &cookie) once per class.
//   The constructor (0x6BEE40 for CStreamClass) is the member-initialiser
//   form below: it clears RefCount before the vptr store, byte-exact.
#ifndef GG_MATCH_CORE_CLASS_FACTORY_H
#define GG_MATCH_CORE_CLASS_FACTORY_H

#include <stddef.h>
#include <objbase.h>
#include "../_rt/gg_static_assert.h"

template<class T>
class TClassFactory : public IClassFactory
{
public:
    // Declared only: retail calls the constructor out of line at every site, so its body is
    // defined next to the explicit instantiations (ClassFactoryInst.cpp).
    TClassFactory();

    // IUnknown
    STDMETHOD(QueryInterface)(REFIID riid, void** ppv)
    {
        if (ppv == NULL) {
            return E_POINTER;
        }
        *ppv = NULL;
        if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory)) {
            *ppv = this;
        }
        if (*ppv == NULL) {
            return E_NOINTERFACE;
        }
        AddRef();
        return S_OK;
    }

    STDMETHOD_(ULONG, AddRef)()
    {
        return InterlockedIncrement(&RefCount);
    }

    STDMETHOD_(ULONG, Release)()
    {
        LONG count = InterlockedDecrement(&RefCount);
        if (count == 0) {
            delete this;
        }
        return count;
    }

    // IClassFactory
    STDMETHOD(CreateInstance)(IUnknown* outer, REFIID riid, void** ppv);

    STDMETHOD(LockServer)(BOOL lock)
    {
        if (lock) {
            RefCount++;
        } else {
            RefCount--;
        }
        return S_OK;
    }

    LONG RefCount;  // +0x0004
};

#endif  // GG_MATCH_CORE_CLASS_FACTORY_H

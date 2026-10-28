// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   TEventClass stream loading and destruction, read off retail gamemd.exe v1.001
//   (vtable 0x7F5578). The class is a view that carries only the members these bodies
//   touch (offsets from the retail disassembly). Functions are in ascending retail address
//   order. /Ob2: the scalar deleting destructor carries the destructor body inline.

#include <new.h>
#include "../_layout/abstract_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

class TEventClass : public AbstractClass
{
public:
    // The stream loader's in-place construction.
    TEventClass(const AbstractNoInit& noInit) : AbstractClass(noInit) {}
    virtual ~TEventClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);                     // 5   0x71F8C0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual void vf_10(void* target, bool removed);                    // 10  0x71F800
    virtual int vf_11();
    virtual int vf_12();

    char unknown_24[4];        // +0x24
    TEventClass* unknown_28;   // +0x28 the next event in the chain
    int unknown_2C;            // +0x2C
    void* unknown_30;          // +0x30
    char unknown_34[0x54 - 0x34];
    void* unknown_54;          // +0x54
};
GG_STATIC_ASSERT(offsetof(TEventClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(TEventClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(TEventClass, unknown_54) == 0x54);

// GLOBAL: GAMEMD 0xB0F658 / 0xB0F670 / 0xB0F1A0 -- the registries a TEventClass leaves when destroyed.
extern DynamicVectorClass<TEventClass*> DAT_00B0F658;
extern DynamicVectorClass<TEventClass*> DAT_00B0F670;
extern DynamicVectorClass<TEventClass*> DAT_00B0F1A0;

// FUNCTION: GAMEMD 0x71F800
// Drop a pointer that is going away: unlink it from the chain, or forget the team.
void TEventClass::vf_10(void* target, bool removed)
{
    if (unknown_28 == target) {
        unknown_28 = unknown_28->unknown_28;
    }
    if (unknown_30 == target) {
        unknown_30 = 0;
    }
}

// FUNCTION: GAMEMD 0x71F8C0
// Re-establish the object after a stream load and queue its pointers for swizzling.
HRESULT __stdcall TEventClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) TEventClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_28);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_30);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_54);
    return 0;
}

// The destructor is only ever reached through the scalar deleting destructor, so it is
// inline: retail has no standalone copy.
inline TEventClass::~TEventClass()
{
    AnnounceExpiredPointer(1);
    DAT_00B0F658.RemoveItem(this);
    DAT_00B0F670.RemoveItem(this);
    DAT_00B0F1A0.RemoveItem(this);
}

// SYNTHETIC: GAMEMD 0x71FA80
// TEventClass scalar deleting destructor (primary slot 8), the destructor expanded in place.

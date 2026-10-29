// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TEventClass stream loading and destruction, read off retail gamemd.exe v1.001
//   (vtable 0x7F5578). The class is a view that carries only the members these bodies
//   touch (offsets from the retail disassembly). Functions are in ascending retail address
//   order. /Ob2: the scalar deleting destructor carries the destructor body inline.

#include <new.h>
#include "tevent_class_methods.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;


// GLOBAL: GAMEMD 0xB0F658 / 0xB0F670 / 0xB0F1A0 -- the registries a TEventClass leaves when destroyed.
extern DynamicVectorClass<TEventClass*> DAT_00B0F658;
extern DynamicVectorClass<TEventClass*> DAT_00B0F670;
extern DynamicVectorClass<TEventClass*> DAT_00B0F1A0;

// FUNCTION: GAMEMD 0x71F800
// Drop a pointer that is going away: unlink it from the chain, or forget the team.
void TEventClass::vf_10(void* target, bool removed)
{
    if (NextEvent == target) {
        NextEvent = NextEvent->NextEvent;
    }
    if (TeamType == target) {
        TeamType = 0;
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
    DAT_00B0C110.SwizzleManagerClass::vf_4(&NextEvent);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&TeamType);
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

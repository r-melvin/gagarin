// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   TaskForceClass stream loading and destruction, read off retail gamemd.exe v1.001
//   (vtable 0x7F4680). The layout is match/_layout/task_force_class.h.
//   /Ob2: the scalar deleting destructor carries the destructor body inline.

#include <new.h>
#include "../_layout/task_force_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0xA8E8D0 -- the task force registry.
extern DynamicVectorClass<TaskForceClass*> DAT_00A8E8D0;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// FUNCTION: GAMEMD 0x6E86A0
HRESULT __stdcall TaskForceClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) TaskForceClass(AbstractNoInit());
    for (int i = 0; i < 6; i++) {
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Entries[i].Type);
    }
    return 0;
}

// The destructor is only ever reached through the scalar deleting destructor, so it is
// inline: retail has no standalone copy.
inline TaskForceClass::~TaskForceClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A8E8D0.RemoveItem(this);
}

// SYNTHETIC: GAMEMD 0x6E87F0
// TaskForceClass scalar deleting destructor (primary slot 8), the destructor expanded in place.

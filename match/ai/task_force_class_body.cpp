// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TaskForceClass stream loading and destruction, read off retail gamemd.exe v1.001
//   (vtable 0x7F4680). The layout is match/_layout/task_force_class.h.
//   /Ob2: the scalar deleting destructor carries the destructor body inline.

#include <new.h>
#include "../_layout/session_class.h"
#include "../_layout/task_force_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0xA8E8D0 -- the task force registry.
extern DynamicVectorClass<TaskForceClass*> DAT_00A8E8D0;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;


// A techno type, as far as the dword the task force scan reads.
struct TaskForceTypeView
{
    char unknown_00[0x634];
    int unknown_634;   // +0x634
};
GG_STATIC_ASSERT(offsetof(TaskForceTypeView, unknown_634) == 0x634);

// FUNCTION: GAMEMD 0x6E8160
// The total number of units the task force asks for.
int TaskForceClass::FUN_006E8160() const
{
    int total = 0;
    for (int i = 0; i < EntryCount; i++) {
        total += Entries[i].Amount;
    }
    return total;
}

// FUNCTION: GAMEMD 0x6E8780
// The largest value of the entry types' +0x634 dword, or 11 for an unset one while the session is live.
int TaskForceClass::FUN_006E8780() const
{
    int result = 0;
    for (int i = 0; i < EntryCount; i++) {
        int value = reinterpret_cast<TaskForceTypeView*>(Entries[i].Type)->unknown_634;
        if (value > result) {
            result = value;
        } else if (value == -1 && Session_00A8B238.GameMode) {
            result = 11;
        }
    }
    return result;
}

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

// FUNCTION: GAMEMD 0x6E7F80
TaskForceClass::~TaskForceClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A8E8D0.RemoveItem(this);
}

// SYNTHETIC: GAMEMD 0x6E87F0
// TaskForceClass scalar deleting destructor (primary slot 8), the destructor expanded in place.

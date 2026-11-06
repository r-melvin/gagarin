// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TaskForceClass constructor, read off retail gamemd.exe v1.001 (0x6E7E80; vtable 0x7F4680). The layout is
//   match/_layout/task_force_class.h.
// TUSPLIT: GAMEMD 0x6E8220 same-file 6.3% separate 100.0%
//   Placement is a measured byte workaround, not evidence of an original file boundary: with the constructor visible
//   VC6 expands it inside the caller 0x6E8220 (match/task_force_class_body.cpp) where retail calls it; no ordinary
//   source shape (direct new, inline lookup wrapper, nested wrapper) keeps the call.

#include "_layout/task_force_class.h"
#include "vector_class_operations.h"
#include "vector_add_item_free.h"

// GLOBAL: GAMEMD 0xA8E8D0 -- the task force registry.
extern DynamicVectorClass<TaskForceClass*> DAT_00A8E8D0;

// FUNCTION: GAMEMD 0x6E7E80
TaskForceClass::TaskForceClass(const char* id)
    : AbstractTypeClass(id), ArrayIndex(-1), EntryCount(0), unknown_A0(0)
{
    DynamicVectorAddItemFree(&DAT_00A8E8D0, this);
    for (int i = 0; i < 6; i++) {
        Entries[i] = TaskForceEntry(0, 0);
    }
}

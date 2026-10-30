// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Target is the pinned retail gamemd.exe v1.001. Entry-origin disassembly
//   covers 0x6E4DE0..0x6E4F5B inclusive (0x17C bytes, ending RET 4). Stores
//   confirm TagClass fields/vptrs; direct operands confirm registries
//   0xB0E720, 0xB0F670, 0xB0F708 and coordinate source 0xB0E700. The constructor
//   reads TagTypeClass::FirstTrigger at +0xA0 and TriggerTypeClass::NextTrigger
//   at +0xA8, allocates 0x48 bytes, and invokes the native TriggerClass ctor at
//   0x725FA0 before prepending each trigger to FirstTrigger.
//   The retail span has no C++ exception cleanup. /GX adds a cleanup funclet
//   around trigger construction; the no-GX source build matches the full span.

#include "../FUNCTION.H"
#include "tag_class_destroy_methods.h"
#include "../core/abstract_registry.h"

// GLOBAL: GAMEMD 0xB0E700 — the CellStruct copied to TagClass::DefaultCoords.
// The raw instruction loads one DWORD from this address.
extern CellStruct DAT_00B0E700;

// FUNCTION: GAMEMD 0x6E4DE0
TagClass::TagClass(TagTypeClass* type)
    : Type(type), FirstTrigger(0), InstanceCount(0), DefaultCoords(DAT_00B0E700),
      Destroyed(0), IsExecuting(0)
{

    TagPtrVector_AddItem(reinterpret_cast<TagPtrVector*>(&TagClass::Array), this);
    TagPtrVector_AddItem(reinterpret_cast<TagPtrVector*>(&DAT_00B0F670), this);
    TagPtrVector_AddItem(reinterpret_cast<TagPtrVector*>(&DAT_00B0F708), this);

    if (type)
    {
        TriggerTypeClass* triggerType = type->FirstTrigger;
        while (triggerType)
        {
            TriggerClass* trigger = new TriggerClass(triggerType);
            trigger->AttachedTrigger = static_cast<TriggerClass*>(this->FirstTrigger);
            this->FirstTrigger = trigger;
            triggerType = triggerType->NextTrigger;
        }
    }
}

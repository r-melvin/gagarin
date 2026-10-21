// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Target is the pinned retail gamemd.exe v1.001. Entry-origin disassembly
//   covers 0x6E4DE0..0x6E4F5B inclusive (0x17C bytes, ending RET 4). Stores
//   confirm TagClass fields/vptrs; direct operands confirm registries
//   0xB0E720, 0xB0F670, 0xB0F708 and coordinate source 0xB0E700. The constructor
//   reads TagTypeClass::FirstTrigger at +0xA0 and TriggerTypeClass::NextTrigger
//   at +0xA8, allocates 0x48 bytes, and invokes the native TriggerClass ctor at
//   0x725FA0 before prepending each trigger to FirstTrigger.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
//   The retail span has no C++ exception cleanup. /GX adds a cleanup funclet
//   around trigger construction; the no-GX source build matches the full span.

#include "../_layout/tag_class.h"
#include "tag_class_destroy_methods.h"
#include "trigger_class_more_methods.h"

// GLOBAL: GAMEMD 0xB0E700 — the CellStruct copied to TagClass::DefaultCoords.
// The raw instruction loads one DWORD from this address.
extern CellStruct DAT_00B0E700;

// The two registries are vector-shaped in retail; their owning class identities
// are not established here. Member offsets are asserted by DynamicVectorClassLayout.
// GLOBAL: GAMEMD 0xB0F670
extern DynamicVectorClassLayout DAT_00B0F670;
// GLOBAL: GAMEMD 0xB0F708
extern DynamicVectorClassLayout DAT_00B0F708;

// Prefix views for linked trigger-type data. The only recovered members are the
// pointer reads at +0xA0 and +0xA8; no complete TriggerTypeClass layout is claimed.
struct TagTypeTriggerHeadView
{
    unsigned char unknown_00[0xA0];
    void* FirstTrigger;
};

struct TriggerTypeNextView
{
    unsigned char unknown_00[0xA8];
    void* NextTrigger;
};

GG_STATIC_ASSERT(offsetof(TagTypeTriggerHeadView, FirstTrigger) == 0xA0);
GG_STATIC_ASSERT(offsetof(TriggerTypeNextView, NextTrigger) == 0xA8);

// FUNCTION: GAMEMD 0x6E4DE0
TagClass::TagClass(TagTypeClass* type)
{
    this->Type = type;
    this->FirstTrigger = 0;
    this->InstanceCount = 0;
    this->DefaultCoords = DAT_00B0E700;
    this->Destroyed = 0;
    this->IsExecuting = 0;

    this->_vtable_IPersistStream = reinterpret_cast<void*>(0x007F44E0);
    this->_vtable_IRTTITypeInfo = reinterpret_cast<void*>(0x007F44C4);
    this->_vtable_INoticeSink = reinterpret_cast<void*>(0x007F44BC);
    this->_vtable_INoticeSource = reinterpret_cast<void*>(0x007F44B4);

    TagPtrVector_AddItem(reinterpret_cast<TagPtrVector*>(&TagClass::Array), this);
    TagPtrVector_AddItem(reinterpret_cast<TagPtrVector*>(&DAT_00B0F670), this);
    TagPtrVector_AddItem(reinterpret_cast<TagPtrVector*>(&DAT_00B0F708), this);

    if (type)
    {
        void* triggerType = reinterpret_cast<TagTypeTriggerHeadView*>(type)->FirstTrigger;
        while (triggerType)
        {
            TriggerClass* trigger = new TriggerClass(
                reinterpret_cast<TriggerTypeClass*>(triggerType));
            trigger->AttachedTrigger = static_cast<TriggerClass*>(this->FirstTrigger);
            this->FirstTrigger = trigger;
            triggerType = reinterpret_cast<TriggerTypeNextView*>(triggerType)->NextTrigger;
        }
    }
}

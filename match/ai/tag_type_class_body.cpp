// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The TagTypeClass block of retail .text (0x6E58D0..0x6E64BF) that the other
// tag_type_class_* units leave open: three of the unit's run-time
// initialisers, the destructor, the trigger-list helpers and the primary-table
// slots 5, 10, 11, 12, 13 and 16, in retail address order. TagTypeClass is
// declared in _layout/tag_type_class.h.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy
//   /Ob2: the destructor expands the registry RemoveItem bodies in place.

#include <new.h>
#include "../_layout/tag_type_class.h"
#include "../_layout/tag_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../core/vector_class_operations.h"
#include "../movement/locomotion_load_support.h"
#include "../core/abstract_registry.h"
#include "../core/header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xB0E7B8
extern double DAT_00B0E7B8;
// GLOBAL: GAMEMD 0x7F4540
const double DAT_007F4540 = 60.0;

// SYNTHETIC: GAMEMD 0x6E5900
// GLOBAL: GAMEMD 0xB0E808
double DAT_00B0E808 = DAT_00B0E7B8 / DAT_007F4540;
// SYNTHETIC: GAMEMD 0x6E5920
// GLOBAL: GAMEMD 0xB0E7F0
double DAT_00B0E7F0 = 1.0 / DAT_00B0E808;
// SYNTHETIC: GAMEMD 0x6E5AA0
// GLOBAL: GAMEMD 0xB0E7F8
TuningCoordInit DAT_00B0E7F8(128, 128, 0);

// FUNCTION: GAMEMD 0x6E5CA0
TagTypeClass::~TagTypeClass()
{
    AnnounceExpiredPointer(1);
    TriggerTypeClass* trigger = FirstTrigger;
    FirstTrigger = 0;
    while (trigger) {
        TriggerTypeClass* next = trigger->NextTrigger;
        trigger->NextTrigger = 0;
        delete trigger;
        trigger = next;
    }
    DynamicVectorClass<TagClass*>& tags = *reinterpret_cast<DynamicVectorClass<TagClass*>*>(&TagClass::Array);
    for (int i = 0; i < tags.Count; i++) {
        if (tags[i]->Type == this) {
            delete tags[i];
            i--;
        }
    }
    reinterpret_cast<DynamicVectorClass<TagTypeClass*>*>(&DAT_00B0F670)->RemoveItem(this);
    TagTypes.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x6E5DD0
bool TagTypeClass::FUN_006E5DD0(TriggerTypeClass* trigger)
{
    if (trigger) {
        trigger->NextTrigger = FirstTrigger;
        FirstTrigger = trigger;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6E5E00
bool TagTypeClass::FUN_006E5E00(TriggerTypeClass* trigger)
{
    TriggerTypeClass* node = FirstTrigger;
    if (node == trigger) {
        FirstTrigger = trigger->NextTrigger;
        return true;
    }
    for (; node; node = node->NextTrigger) {
        if (node->NextTrigger == trigger) {
            node->NextTrigger = trigger->NextTrigger;
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6E5E50
void TagTypeClass::vf_10(void* target, bool removed)
{
    if (FirstTrigger == target) {
        FirstTrigger = FirstTrigger->NextTrigger;
    }
}

// FUNCTION: GAMEMD 0x6E62E0
bool TagTypeClass::FUN_006E62E0(TriggerTypeClass* trigger) const
{
    for (TriggerTypeClass* node = FirstTrigger; node; node = node->NextTrigger) {
        if (node == trigger) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6E63E0
void TagTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(Persistence);
}

// FUNCTION: GAMEMD 0x6E6410
HRESULT __stdcall TagTypeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) TagTypeClass(AbstractNoInit());
    DAT_00B0C110.FUN_006CF240((void**)&FirstTrigger);
    return 0;
}

// FUNCTION: GAMEMD 0x6E6490
int TagTypeClass::vf_11()
{
    return 0x2D;
}

// FUNCTION: GAMEMD 0x6E64A0
int TagTypeClass::vf_12()
{
    return sizeof(TagTypeClass);
}

// FUNCTION: GAMEMD 0x6E64B0
int TagTypeClass::vf_16()
{
    return unknown_98;
}

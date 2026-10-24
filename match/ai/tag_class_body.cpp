// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The TagClass block of retail .text (0x6E4B50..0x6E58CF) that the other
// tag_class_* units leave open: three of the unit's run-time initialisers, the
// destructor, the small accessors, the event dispatcher and the primary-table
// slots 5, 10, 11, 12 and 13. Functions are in retail address order; TagClass
// itself is declared in _layout/tag_class.h.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//   /Ob2: the destructor expands the vector FindItemIndex bodies in place.

#include <new.h>
#include "../_layout/tag_class.h"
#include "../_layout/tag_type_class.h"
#include "../_layout/trigger_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/object_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../core/vector_class_operations.h"
#include "../movement/locomotion_load_support.h"
#include "tag_class_destroy_methods.h"
#include "../core/abstract_registry.h"
#include "../core/header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xB0E708
extern double DAT_00B0E708;
// GLOBAL: GAMEMD 0x7F44A0
const double DAT_007F44A0 = 60.0;

// SYNTHETIC: GAMEMD 0x6E4B80
// GLOBAL: GAMEMD 0xB0E770
double DAT_00B0E770 = DAT_00B0E708 / DAT_007F44A0;
// SYNTHETIC: GAMEMD 0x6E4BA0
// GLOBAL: GAMEMD 0xB0E758
double DAT_00B0E758 = 1.0 / DAT_00B0E770;
// SYNTHETIC: GAMEMD 0x6E4D20
// GLOBAL: GAMEMD 0xB0E760
TuningCoordInit DAT_00B0E760(128, 128, 0);

// ---- globals and helpers the bodies use ---------------------------------------------------------------------------

// GLOBAL: GAMEMD 0xA8E9A0
extern bool DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xA8ED5C
#include "../core/game_state_flags.h"
// GLOBAL: GAMEMD 0xA8ED6B
extern bool DAT_00A8ED6B;
// GLOBAL: GAMEMD 0xB0E700 -- the "no cell" value (defined in tag_class_array.cpp).
extern CellStruct DAT_00B0E700;
// GLOBAL: GAMEMD 0x8B40C8 -- a list of tags the destructor drops itself from.
extern DynamicVectorClass<TagClass*> DAT_008B40C8;
// GLOBAL: GAMEMD 0xA83CDC -- the cursor into 0x8B40C8.
extern int DAT_00A83CDC;
// GLOBAL: GAMEMD 0x8B41A8 -- a second tag list.
extern DynamicVectorClass<TagClass*> DAT_008B41A8;
// GLOBAL: GAMEMD 0xA83DBC -- the cursor into 0x8B41A8.
extern int DAT_00A83DBC;

// FUNCTION: GAMEMD 0x502D30 (decl; reloc) -- __fastcall, house for a country index.
HouseClass* FUN_00502D30(int index);

// GLOBAL: GAMEMD 0x87F7E8 -- the map; 0x5657A0 returns the cell at a coordinate.
struct Map_0087F7E8
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    CellClass* FUN_005657A0(const CellStruct* cell);
};
extern Map_0087F7E8 DAT_0087F7E8;

// The registries the destructor removes `this` from (abstract_registry.h holds their storage).
static inline void Tag_RemoveFrom(DynamicVectorClassLayout* list, TagClass* tag)
{
    reinterpret_cast<DynamicVectorClass<TagClass*>*>(list)->RemoveItem(tag);
}

// A count-down timer started now (the middle dword is left as it is).
static inline CDTimerClass Inline_006E4F60(int duration)
{
    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = duration;
    return timer;
}

// The append to the shared pending-delete list 0xB0F698 (the TagPtrVector_AddItem shape, for any element type).
static inline bool PendingDelete_Add(TagPtrVector* v, void* item)
{
    if (v->Count >= v->Capacity)
    {
        if (!v->IsAllocated && v->Capacity != 0)
            return false;
        if (v->CapacityIncrement <= 0)
            return false;
        if (!v->SetCapacity(v->Capacity + v->CapacityIncrement, 0))
            return false;
    }
    int i = v->Count++;
    ((void**)v->Items)[i] = item;
    return true;
}

// FUNCTION: GAMEMD 0x6E4F60
TagClass::~TagClass()
{
    AnnounceExpiredPointer(1);
    if (DAT_00A8E9A0) {
        if (DAT_00A8ED5C && Type && (Type->GetFlags() & 0x10)) {
            int index = DAT_008B40C8.FindItemIndex(this);
            if (DAT_00A83CDC >= index && --DAT_00A83CDC < 0 && DAT_008B40C8.Count == 0) {
                DAT_00A83CDC = 0;
            }
        }
        if (DAT_00A8E9A0) {
            if (DAT_00A8ED5C && Type && (Type->GetFlags() & 0x04)) {
                int index = DAT_008B41A8.FindItemIndex(this);
                if (DAT_00A83DBC >= index && --DAT_00A83DBC < 0 && DAT_008B41A8.Count == 0) {
                    DAT_00A83DBC = 0;
                }
            }
            if (DAT_00A8E9A0 && DAT_00A8ED5C && FirstTrigger && FirstTrigger->Type
                && FirstTrigger->Type->House && Type->HasAllowWinAction()) {
                HouseClass* house = FUN_00502D30(FirstTrigger->Type->House->ArrayIndex2);
                if (house->AllowWinBlocks) {
                    house->AllowWinBlocks--;
                }
                house->BorrowedTime = Inline_006E4F60(60);
            }
        }
    }
    for (TriggerClass* trigger = FirstTrigger; trigger; trigger = trigger->NextTrigger) {
        PendingDelete_Add(reinterpret_cast<TagPtrVector*>(&DAT_00B0F698), trigger);
    }
    Tag_RemoveFrom(&DAT_00B0F670, this);
    Tag_RemoveFrom(&DAT_00B0F708, this);
    Tag_RemoveFrom(&TagClass::Array, this);
    AnnounceExpiredPointer(1);
}

// FUNCTION: GAMEMD 0x6E5290
bool TagClass::FUN_006E5290() const
{
    return Destroyed;
}

// FUNCTION: GAMEMD 0x6E52F0
CellStruct* TagClass::FUN_006E52F0(CellStruct* out) const
{
    *out = DefaultCoords;
    return out;
}

// FUNCTION: GAMEMD 0x6E5360
int TagClass::FUN_006E5360() const
{
    if (Type && Type->HasAllowWinAction()) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6E53A0
bool TagClass::FUN_006E53A0(int event, ObjectClass* object, CellStruct cell, bool flag, int arg)
{
    bool result = false;
    bool destroyed = false;
    bool sprung = false;
    if (DAT_00A8ED6B || IsExecuting || Destroyed || !Type) {
        return false;
    }
    IsExecuting = true;
    for (TriggerClass* trigger = FirstTrigger; trigger; trigger = trigger->NextTrigger) {
        if (trigger->FUN_007264C0(event, object, flag, Type->Persistence == 2, arg)) {
            switch (Type->Persistence) {
            case 0:
                trigger->FireActions(object, cell);
                trigger->Destroy();
                result = true;
                destroyed = true;
                sprung = true;
                break;
            case 1:
                if (InstanceCount == 1) {
                    trigger->FireActions(object, cell);
                    trigger->Destroy();
                    destroyed = true;
                    result = true;
                } else {
                    sprung = true;
                }
                break;
            case 2:
                trigger->FireActions(object, cell);
                result = true;
                break;
            }
        }
    }
    IsExecuting = false;
    if (sprung) {
        if (object && object->AttachedTag == this) {
            object->AttachTrigger(0);
        }
        if (cell.X != DAT_00B0E700.X || cell.Y != DAT_00B0E700.Y) {
            DAT_0087F7E8.FUN_005657A0(&cell)->ReplaceTag(0);
        }
    }
    if (destroyed) {
        AnnounceExpiredPointer(1);
        TagPtrVector_AddItem(reinterpret_cast<TagPtrVector*>(&DAT_00B0F698), this);
    }
    return result;
}

// FUNCTION: GAMEMD 0x6E55A0
void TagClass::FUN_006E55A0(int index)
{
    FirstTrigger->NotifyGlobalChanged(index);
}

// FUNCTION: GAMEMD 0x6E5610
void TagClass::vf_10(void* target, bool removed)
{
    if (Type == target) {
        Type = 0;
    }
    if (FirstTrigger == target) {
        FirstTrigger = FirstTrigger->NextTrigger;
    }
    if (!Type) {
        Destroyed = true;
        TagPtrVector_AddItem(reinterpret_cast<TagPtrVector*>(&DAT_00B0F698), this);
    }
}

// FUNCTION: GAMEMD 0x6E56E0
void TagClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D50(Type->vf_rtti_4());
    if (FirstTrigger) {
        crc->FUN_004A1D50(FirstTrigger->vf_rtti_4());
    }
    crc->FUN_004A1CA0(Destroyed);
}

// FUNCTION: GAMEMD 0x6E5730
HRESULT __stdcall TagClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) TagClass(AbstractNoInit());
    DAT_00B0C110.FUN_006CF240((void**)&Type);
    DAT_00B0C110.FUN_006CF240((void**)&FirstTrigger);
    return 0;
}

// FUNCTION: GAMEMD 0x6E5890
int TagClass::vf_12()
{
    return sizeof(TagClass);
}

// FUNCTION: GAMEMD 0x6E58A0
int TagClass::vf_11()
{
    return 0x2C;
}

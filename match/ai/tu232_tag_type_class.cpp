// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU232 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x6e58d0-0x6e683f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// Retail PAVTagTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
//
//   0x6E6250 / 0x6E6280 / 0x6E62B0 via the local Ghidra disassembly. Offsets
//   confirmed numerically (see the header).
//
// TagTypeClass trigger-list folds. All five share one shape: walk the tag's
// TriggerTypeClass list and delegate to the same-named predicate on each
// trigger. GetFlags accumulates; the four Has* short-circuit on the first hit.
// Functions ordered ascending by retail address.
//
//   ReadFromINI reconstructed from raw retail entry-point bytes at 0x6E6080;
//   WriteToINI from entry-point Ghidra disassembly at 0x6E6160.
//   Method names describe recovered behavior; retail has no function symbols.
//
// Entry-origin retail span 0x6E5B60..0x6E5C99: 314 bytes, RET 4.
// Instructions confirm base construction, field/vptr writes, identity copy,
// array index and two vector appends. Original private names remain unknown.
// LIBRARY: GAMEMD 0x7C91D0 -- strncpy.
// GX emits exception cleanup absent from the retail body.
//
//   cross-checked against an outside reference (reconfirmed).
//
//   GLOBAL:   GAMEMD 0xB0E780  TagTypes  (DynamicVectorClass<TagTypeClass*>)
//   LIBRARY:  GAMEMD 0x7C8D20  _strcmpi  (CRT; excluded from match target)
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.

#include "../core/vector_class_operations.h"

class TagTypeClass;

// VTABLE: GAMEMD 0x7F4578 -- VectorClass<TagTypeClass*>.
template class VectorClass<TagTypeClass*>;
typedef VectorClass<TagTypeClass*> GgTagTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgTagTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F4558 -- DynamicVectorClass<TagTypeClass*>.
template class DynamicVectorClass<TagTypeClass*>;
typedef DynamicVectorClass<TagTypeClass*> GgTagTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTagTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(TagTypeClass*) == 4);

#include "tag_type_class_flag_methods.h"

#include "tag_type_class_ini_methods.h"

#include <stddef.h>
#include "../_layout/tag_type_class.h"
#include "../core/abstract_registry.h"

extern "C" char* __cdecl strncpy(char*, const char*, unsigned int);

struct TagTypeCtorVector
{
    virtual ~TagTypeCtorVector();
    virtual bool Equals(const TagTypeCtorVector& other) const;
    virtual bool SetCapacity(int capacity, void* memory);
    void* Items;
    int Capacity;
    unsigned char IsInitialized;
    unsigned char IsAllocated;
    unsigned char unknown_0E[2];
    int Count;
    int CapacityIncrement;
};
GG_STATIC_ASSERT(offsetof(TagTypeCtorVector, Items) == 4);
GG_STATIC_ASSERT(offsetof(TagTypeCtorVector, Capacity) == 8);
GG_STATIC_ASSERT(offsetof(TagTypeCtorVector, IsAllocated) == 0xD);
GG_STATIC_ASSERT(offsetof(TagTypeCtorVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(TagTypeCtorVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(TagTypeCtorVector) == 0x18);

static inline bool TagTypeCtorAdd(TagTypeCtorVector* vector, TagTypeClass* item)
{
    if (vector->Count >= vector->Capacity) {
        if (!vector->IsAllocated && vector->Capacity != 0)
            return false;
        if (vector->CapacityIncrement <= 0)
            return false;
        if (!vector->SetCapacity(vector->Capacity + vector->CapacityIncrement, 0))
            return false;
    }
    int index = vector->Count++;
    ((TagTypeClass**)vector->Items)[index] = item;
    return true;
}

// Native construction under GX adds exception cleanup absent from retail.
#include "tag_type_class_load_list_methods.h"
#include "../_layout/swizzle_manager_class.h"

#include "tag_type_class_methods.h"

// --- referenced retail callee (declared, no body => reloc-normalised CALL) ---
extern "C" int __cdecl _strcmpi(const char*, const char*);

#include "tag_type_class_save_methods.h"

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E5B60
TagTypeClass::TagTypeClass(const char* id)
    : AbstractTypeClass(id), unknown_98(-1), Persistence(0), FirstTrigger(0)
{

    char name[0x31];
    if (ID == 0) {
        name[0] = 0;
    } else {
        strncpy(name, ID, 0x30);
        name[0x30] = 0;
    }
    char* destination = Name;
    if (name != destination) {
        for (int i = 0; i < 0x31; ++i)
            destination[i] = name[i];
    }

    unknown_98 = TagTypes.Count;
    TagTypeCtorAdd(reinterpret_cast<TagTypeCtorVector*>(&TagTypes), this);
    TagTypeCtorAdd(reinterpret_cast<TagTypeCtorVector*>(&DAT_00B0F670), this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6E5E70  (__fastcall — name in ECX)
//
// Linear case-insensitive lookup of `name` in TagTypes, matching
// either the entry's ID (+0x24) or its Name (+0x64). Returns the entry pointer,
// or null. Count/Items are reloaded from the global each iteration.
// ---------------------------------------------------------------------------
TagTypeClass* TagTypeClass::FindByNameOrID(const char* name)
{
    if (name)
    {
        for (int i = 0; i < TagTypes.Count; ++i)
        {
            TagTypeClass* item = TagTypes.Items[i];
            if (_strcmpi(item->ID, name) == 0 ||
                _strcmpi(item->Name, name) == 0)
                return item;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E5ED0
//
// Read every tag out of the Tags section. A key that names nothing keeps a
// null tag; otherwise the existing tag type of that name is reused, or a
// new one built. Either way the name is registered and the tag loads its
// own record.
void TagTypeClass::LoadFromINIList(CCINI_006E5ED0* ini)
{
    int count = ini->GetKeyCount(DAT_007F4550);
    for (int i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007F4550, i);
        char buffer[0x18];
        if (ini->ReadString(DAT_007F4550, key, STR_00889F64, buffer, 0x18) > 0) {
            TagTypeClass* tag;
            if (gg_strcmp(STR_00817474, key) == 0
                || gg_strcmp(STR_00817694, key) == 0) {
                tag = 0;
            } else {
                for (int j = 0; j < TagTypes.Count; j++) {
                    if (gg_strcmp(TagTypes.Items[j]->ID, key) == 0) {
                        tag = TagTypes.Items[j];
                        goto have;
                    }
                }
                tag = new TagTypeClass(key);
            }
        have:
            DAT_00B0C110.SwizzleManagerClass::vf_6(FUN_00412610(key), tag);
            TagTypeLoadCallView* view = reinterpret_cast<TagTypeLoadCallView*>(tag);
            (view->*view->Vtable->Method)(ini);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E5FE0
//
// Rewrite the tag list into an INI. First every key already in the section is
// walked, its value read into a small buffer, and the section named by that
// value cleared; then the list section itself is cleared; then every live tag
// type is asked to write itself back through its +0x68 virtual.
//
// The key count is hoisted into a register for the first loop, but the
// section-name pointer is a global and is re-read after every call; the second
// loop re-reads both the item table and the count each time round.
void TagTypeClass::SaveToINIList(CCINI_006E5FE0* ini)
{
    char buffer[32];
    int  i;

    int count = ini->GetKeyCount(DAT_007F4550);
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007F4550, i);
        ini->ReadString(DAT_007F4550, key, STR_00889F64, buffer, 32);
        ini->Clear(buffer, 0);
    }
    ini->Clear(DAT_007F4550, 0);

    for (i = 0; i < TagTypes.Count; i++) {
        TagTypeClass* item = TagTypes.Items[i];
        TagTypeSaveCallView* view = reinterpret_cast<TagTypeSaveCallView*>(item);
        (view->*view->Vtable->Method)(ini);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E6080
bool TagTypeClass::ReadFromINI(TagINI_006E6080* ini)
{
    char buffer[0x80];
    ini->Reset();
    if (ini->ReadString(DAT_007F4550, ID, STR_00889F64, buffer, sizeof(buffer))) {
        strtok(buffer, STR_00817F70);
        Persistence = FUN_007C9BFD(buffer);
        char* token = strtok(0, STR_00817F70);
        TagName_006E6080 name;
        if (!token) {
            name.Text[0] = 0;
        } else {
            strncpy(name.Text, token, 0x30);
            name.Text[0x30] = 0;
        }
        // Preserve the fixed-size value assignment, including its self check.
        // The compare operand order controls retail's CMP EAX,EDI spelling.
        if (&name != (TagName_006E6080*)Name.Data) {
            *(TagName_006E6080*)Name.Data = name;
        }
        FirstTrigger = TriggerTypeClass::FindOrAllocate(strtok(0, STR_00817F70));
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E6160
bool TagTypeClass::WriteToINI(TagINI_006E6080* ini)
{
    char buffer[0x80];
    // Each arm submits its formatted record; VC6 shares the call itself while
    // retaining the per-arm argument setup seen in the retail body.
    if (!FirstTrigger) {
        wsprintfA(buffer, STR_00842CD8, Name.Data);
        ini->WriteString(DAT_007F4550, ID, buffer);
    } else {
        wsprintfA(buffer, STR_00842CCC, Persistence, Name.Data,
                  FirstTrigger->ID.Data);
        ini->WriteString(DAT_007F4550, ID, buffer);
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E61F0  TagTypeClass::GetFlags (__thiscall)
// Retail keeps the accumulator in EDI and returns it through EAX, so this is a
// full int fold rather than the BYTE an outside reference's `using Flags = BYTE` suggests.
int TagTypeClass::GetFlags() const
{
    int flags = 0;
    for (TriggerTypeClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        flags |= trigger->GetFlags();
    }
    return flags;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E6220  TagTypeClass::HasAllowWinAction (__thiscall)
bool TagTypeClass::HasAllowWinAction() const
{
    for (TriggerTypeClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        if (trigger->HasAllowWinAction()) {
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E6250  TagTypeClass::HasCrossesHorizontalLineEvent (__thiscall)
bool TagTypeClass::HasCrossesHorizontalLineEvent() const
{
    for (TriggerTypeClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        if (trigger->HasCrossesHorizontalLineEvent()) {
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E6280  TagTypeClass::HasCrossesVerticalLineEvent (__thiscall)
bool TagTypeClass::HasCrossesVerticalLineEvent() const
{
    for (TriggerTypeClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        if (trigger->HasCrossesVerticalLineEvent()) {
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E62B0  TagTypeClass::HasZoneEntryByEvent (__thiscall)
bool TagTypeClass::HasZoneEntryByEvent() const
{
    for (TriggerTypeClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        if (trigger->HasZoneEntryByEvent()) {
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E64C0
void* Obj_6E64C0::FUN_6E64C0(unsigned int flags)
{
    FUN_006E5CA0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E64E0
// DynamicVectorClass<TagTypeClass*>::Clear

// FUNCTION: GAMEMD 0x6E6510
// DynamicVectorClass<TagTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x6E6530
// VectorClass<TagTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x6E6540
// VectorClass<TagTypeClass*>::operator==

// FUNCTION: GAMEMD 0x6E6580
// VectorClass<TagTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x6E6630
// VectorClass<TagTypeClass*>::Clear

// FUNCTION: GAMEMD 0x6E6660
// VectorClass<TagTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x6E66A0
// VectorClass<TagTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x6E66C0
// DynamicVectorClass<TagTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x6E6770
// DynamicVectorClass<TagTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x6E67A0
// VectorClass<TagTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x6E67F0
// DynamicVectorClass<TagTypeClass*>::scalar deleting destructor

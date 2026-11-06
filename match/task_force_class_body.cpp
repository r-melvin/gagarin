// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TaskForceClass stream loading and destruction, read off retail gamemd.exe v1.001
//   (vtable 0x7F4680). The layout is match/_layout/task_force_class.h.
//   /Ob2: the scalar deleting destructor carries the destructor body inline.

#include <new.h>
#include <stdio.h>
#include <string.h>
#include "_layout/session_class.h"
#include "_layout/task_force_class.h"
#include "_layout/swizzle_manager_class.h"
#include "vector_class_operations.h"
#include "vector_add_item_free.h"
#include "ccini_class_methods.h"
#include "small_misc47_methods.h"

// GLOBAL: GAMEMD 0xA8E8D0 -- the task force registry.
extern DynamicVectorClass<TaskForceClass*> DAT_00A8E8D0;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;


// FUNCTION: GAMEMD 0x727CF0 (decl; reloc) -- trims a buffer in place.
void FUN_00727CF0(char* buffer);

// STRING: GAMEMD 0x889F64 -- the shared empty default string.
extern const char DAT_00889F64[];

// A techno type, as far as the dword the task force scan reads.
struct TaskForceTypeView
{
    char unknown_00[0x634];
    int unknown_634;   // +0x634
};
GG_STATIC_ASSERT(offsetof(TaskForceTypeView, unknown_634) == 0x634);

// The constructor at 0x6E7E80 is defined in match/task_force_class_ctor_006E7E80.cpp (see its TUSPLIT note).

// FUNCTION: GAMEMD 0x6E8000
TaskForceClass::TaskForceClass(const TaskForceClass& other)
    : AbstractTypeClass(other)
{
    ArrayIndex = other.ArrayIndex;
    EntryCount = other.EntryCount;
    unknown_A0 = other.unknown_A0;
    for (int i = 0; i < EntryCount; i++) {
        Entries[i] = other.Entries[i];
    }
}

// FUNCTION: GAMEMD 0x6E80F0
TaskForceClass TaskForceClass::FUN_006E80F0(TaskForceClass* source)
{
    if (this != source) {
        ArrayIndex = source->ArrayIndex;
        EntryCount = source->EntryCount;
        unknown_A0 = source->unknown_A0;
        for (int i = 0; i < EntryCount; i++) {
            Entries[i] = source->Entries[i];
        }
    }
    return *this;
}

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

static inline TaskForceClass* TaskForce_FindOrAllocate(const char* name)
{
    if (_strcmpi("<none>", name) == 0 || _strcmpi("none", name) == 0) {
        return 0;
    }
    for (int j = 0; j < DAT_00A8E8D0.Count; j++) {
        if (_strcmpi(DAT_00A8E8D0.Items[j]->ID, name) == 0) {
            return DAT_00A8E8D0.Items[j];
        }
    }
    return new TaskForceClass(name);
}

// FUNCTION: GAMEMD 0x6E8220
// Read every task force named in the TaskForces section: an existing one of that name is reused, or a new one is
// built, then it is registered under its name's key and reads its own record. The group value is stored on each.
void __fastcall FUN_006E8220(CCINIClass* ini, int group)
{
    int count = ini->GetKeyCount("TaskForces");
    for (int i = 0; i < count; i++) {
        const char* key = ini->GetKeyName("TaskForces", i);
        char buffer[0x18];
        if (ini->FUN_00528A10("TaskForces", key, DAT_00889F64, buffer, 0x18) > 0) {
            TaskForceClass* force = TaskForce_FindOrAllocate(buffer);
            DAT_00B0C110.SwizzleManagerClass::vf_6(FUN_00412610(buffer), force);
            force->vf_25(ini);
            force->unknown_A0 = group;
        }
    }
}

// FUNCTION: GAMEMD 0x6E8340
// Rewrite the TaskForces section: clear the sections the old list names, clear the list, then number the task forces
// of this group and have each write itself back.
void __fastcall FUN_006E8340(CCINIClass* ini, int group)
{
    char buffer[0x20];
    int count = ini->GetKeyCount("TaskForces");
    for (int i = 0; i < count; i++) {
        const char* key = ini->GetKeyName("TaskForces", i);
        ini->FUN_00528A10("TaskForces", key, DAT_00889F64, buffer, 0x20);
        ini->Clear(buffer, 0);
    }
    ini->Clear("TaskForces", 0);
    int number = 0;
    for (int j = 0; j < DAT_00A8E8D0.Count; j++) {
        TaskForceClass* force = DAT_00A8E8D0.Items[j];
        if (force->unknown_A0 == group) {
            sprintf(buffer, "%d", number++);
            FUN_00727CF0(buffer);
            ini->WriteString("TaskForces", buffer, force->ID);
            force->vf_26(ini);
        }
    }
}

// FUNCTION: GAMEMD 0x6E8420
bool TaskForceClass::vf_25(CCINIClass* ini)
{
    ini->Reset();
    if (AbstractTypeClass::vf_25(ini)) {
        EntryCount = 0;
        for (int i = 0; i < 6; i++) {
            char key[0x20];
            char value[0x80];
            sprintf(key, "%d", i);
            if (ini->FUN_00528A10(ID, key, DAT_00889F64, value, 0x80) > 0) {
                TaskForceEntry parsed;
                Entries[EntryCount] = *parsed.FUN_004C4EF0(value);
                if (Entries[EntryCount].Type) {
                    EntryCount++;
                }
            }
        }
        ArrayIndex = ini->FUN_005276D0(ID, "Group", ArrayIndex);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6E8510
bool TaskForceClass::vf_26(CCINIClass* ini)
{
    if (AbstractTypeClass::vf_26(ini)) {
        for (int i = 0; i < 6; i++) {
            char key[0x20];
            sprintf(key, "%d", i);
            if (i < EntryCount) {
                ini->WriteString(ID, key, Entries[i].FUN_004C4F90());
            } else {
                ini->Clear(ID, key);
            }
        }
        ini->WriteInteger(ID, "Group", ArrayIndex, 0);
        return true;
    }
    return false;
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

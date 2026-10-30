// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "../FUNCTION.H"
#include "trivial_tu251_methods.h"
#include "../core/abstract_registry.h"
#include "trigger_type_class_methods.h"
#include "trigger_type_class_more_methods.h"
#include "trigger_type_class_flags_methods.h"
#include "trigger_type_class_load_methods.h"
#include "trigger_type_class_save_list_methods.h"
extern "C" int __cdecl _strcmpi(const char*, const char*);

struct TriggerTypeCtorVector
{
    virtual ~TriggerTypeCtorVector();
    virtual bool Equals(const TriggerTypeCtorVector& other) const;
    virtual bool SetCapacity(int capacity, void* memory);
    void* Items;
    int Capacity;
    unsigned char IsInitialized;
    unsigned char IsAllocated;
    unsigned char unknown_0E[2];
    int Count;
    int CapacityIncrement;
};
GG_STATIC_ASSERT(offsetof(TriggerTypeCtorVector, Items) == 4);
GG_STATIC_ASSERT(offsetof(TriggerTypeCtorVector, Capacity) == 8);
GG_STATIC_ASSERT(offsetof(TriggerTypeCtorVector, IsAllocated) == 0xD);
GG_STATIC_ASSERT(offsetof(TriggerTypeCtorVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(TriggerTypeCtorVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(TriggerTypeCtorVector) == 0x18);

static inline bool TriggerTypeCtorAdd(TriggerTypeCtorVector* vector,
                                      TriggerTypeClass* item)
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
    ((TriggerTypeClass**)vector->Items)[index] = item;
    return true;
}


// FUNCTION: GAMEMD 0x726C80
TriggerTypeClass::TriggerTypeClass(const char* id)
    : AbstractTypeClass(id), ArrayIndex(-1), Difficulty_9C(1), Difficulty_9D(1),
      Difficulty_9E(1), Enabled(1), unknown_A0(0), House(0), NextTrigger(0),
      FirstEvent(0), FirstAction(0)
{
    TriggerTypeCtorAdd(reinterpret_cast<TriggerTypeCtorVector*>(&DAT_00B0F658), this);
    TriggerTypeCtorAdd(reinterpret_cast<TriggerTypeCtorVector*>(&DAT_00B0F670), this);
    ArrayIndex = Array.Count;
    TriggerTypeCtorAdd(reinterpret_cast<TriggerTypeCtorVector*>(&Array), this);
}

// FUNCTION: GAMEMD 0x726F50  (__thiscall)
// True if any event in the list is a Crosses-Vertical-Line event (kind 0x1a).
bool TriggerTypeClass::HasCrossesVerticalLineEvent() const
{
    bool result = false;
    TTriggerListNode* node = FirstEvent;
    while (node) {
        if (node->Kind == 0x1a) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}

// FUNCTION: GAMEMD 0x726F80  (__thiscall)
// True if any event in the list is a Crosses-Horizontal-Line event (kind 0x19).
bool TriggerTypeClass::HasCrossesHorizontalLineEvent() const
{
    TTriggerListNode* node = FirstEvent;
    bool result = false;
    while (node) {
        if (node->Kind == 0x19) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}

// FUNCTION: GAMEMD 0x726FB0  (__thiscall)
// True if any event in the list is a Zone-Entry-By event (kind 0x18).
bool TriggerTypeClass::HasZoneEntryByEvent() const
{
    TTriggerListNode* node = FirstEvent;
    bool result = false;
    while (node) {
        if (node->Kind == 0x18) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}

// FUNCTION: GAMEMD 0x726FE0  (__thiscall)
// True if any action in the list is an Allow-Win action (kind 0xf).
bool TriggerTypeClass::HasAllowWinAction() const
{
    TTriggerListNode* node = FirstAction;
    bool result = false;
    while (node) {
        if (node->Kind == 0xf) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}

// FUNCTION: GAMEMD 0x727010  (__thiscall)
// True if any event sets/clears global variable `value`
// (kind 0x1b = set, 0x1c = clear) with matching Value.
bool TriggerTypeClass::HasGlobalSetOrClearedEvent(int value) const
{
    bool result = false;
    TTriggerListNode* node = FirstEvent;
    while (node) {
        if ((node->Kind == 0x1b || node->Kind == 0x1c) && node->Value == value) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}

// FUNCTION: GAMEMD 0x727050  (__thiscall)
// True if any event sets/clears local variable `value`
// (kind 0x24 = set, 0x25 = clear) with matching Value.
bool TriggerTypeClass::HasLocalSetOrClearedEvent(int value) const
{
    bool result = false;
    TTriggerListNode* node = FirstEvent;
    while (node) {
        if ((node->Kind == 0x24 || node->Kind == 0x25) && node->Value == value) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}

class TriggerNodeView_r12
{
public:
    virtual void vf_00();
    virtual void vf_04();
    virtual void vf_08();
    virtual void vf_0C();
    virtual void vf_10();
    virtual void vf_14();
    virtual void vf_18();
    virtual void vf_1C();
    virtual void vf_20();
    virtual void vf_24();
    virtual void vf_28(void* target, bool removed);     // 10: pointer expired
    char unknown_04[0x28 - 0x04];
    TriggerNodeView_r12* Next;                          // +0x28
};
GG_STATIC_ASSERT(offsetof(TriggerNodeView_r12, Next) == 0x28);

// FUNCTION: GAMEMD 0x727090
// Drops the next-trigger link if it is the expired object, and passes the notice to every action
// and event, unlinking either list head if it is the expired object.
void TriggerTypeClass::vf_10(void* target, bool removed)
{
    if (NextTrigger && (void*)NextTrigger == target) {
        NextTrigger = NextTrigger->NextTrigger;
    }
    TriggerNodeView_r12* node;
    for (node = (TriggerNodeView_r12*)FirstAction; node; node = node->Next) {
        node->vf_28(target, true);
    }
    if ((void*)FirstAction == target) {
        FirstAction = FirstAction->Next;
    }
    for (node = (TriggerNodeView_r12*)FirstEvent; node; node = node->Next) {
        node->vf_28(target, true);
    }
    if ((void*)FirstEvent == target) {
        FirstEvent = FirstEvent->Next;
    }
}

// Event-kind -> flag bits (GAMEMD 0x71F680) and action-kind -> flag bits
// (GAMEMD 0x6E3EE0). Both take the kind in ECX and return the bits in EAX.
int EventKindToFlags(int kind);   // 0x71F680
int ActionKindToFlags(int kind);  // 0x6E3EE0


// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x727120  (__fastcall — name in ECX)
//
// Linear case-insensitive lookup of `name` in TriggerTypeClass::Array, matching
// either the entry's ID (+0x24) or its Name (+0x64). Returns the entry pointer,
// or null. Count/Items are reloaded from the global each iteration.
// ---------------------------------------------------------------------------
TriggerTypeClass* TriggerTypeClass::FindByNameOrID(const char* name)
{
    if (name)
    {
        for (int i = 0; i < TriggerTypeClass::Array.Count; ++i)
        {
            if (_strcmpi(((TriggerTypeClass**)TriggerTypeClass::Array.Items)[i]->ID, name) == 0 ||
                _strcmpi(((TriggerTypeClass**)TriggerTypeClass::Array.Items)[i]->Name, name) == 0)
                return ((TriggerTypeClass**)TriggerTypeClass::Array.Items)[i];
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x7271E0  (__thiscall)
//
// Accumulate the flag bits contributed by every event (FirstEvent list) and
// every action (FirstAction list) of this trigger, then OR in the flags of the
// chained NextTrigger recursively.
// ---------------------------------------------------------------------------
unsigned int TriggerTypeClass::GetFlags()
{
    unsigned int flags = 0;
    TTriggerListNode* node;

    for (node = FirstEvent; node != 0; node = node->Next)
        flags |= EventKindToFlags(node->Kind);

    for (node = FirstAction; node != 0; node = node->Next)
        flags |= ActionKindToFlags(node->Kind);

    if (NextTrigger != 0)
        return NextTrigger->GetFlags() | flags;

    return flags;
}

// FUNCTION: GAMEMD 0x7275D0
//
// Read the trigger list out of an INI. Every key of the list section is a
// trigger ID: the two "no trigger" spellings are rejected, an existing trigger
// type with that ID is reused, and otherwise a new one is allocated and
// constructed. Whatever came out of that (retail dispatches through a null
// item too) is then asked to load itself through its +0x64 virtual.
//
// The key count is hoisted into a frame slot for the loop, but the section-name
// pointer is a global and is re-read after every call.
void TriggerTypeClass::LoadFromINIList(CCINI_007275D0* ini)
{
    int count = ini->GetKeyCount(DAT_007F58C8);
    for (int n = 0; n < count; n++) {
        const char* key = ini->GetKeyName(DAT_007F58C8, n);
        TriggerTypeClass* item;

        if (FUN_007C8D20(STR_00817474, key) != 0
            && FUN_007C8D20(STR_00817694, key) != 0) {

            int i = 0;
            while (i < TriggerTypeClass::Array.Count) {
                if (FUN_007C8D20(reinterpret_cast<TriggerTypeClass**>(TriggerTypeClass::Array.Items)[i]->ID, key) == 0) {
                    item = reinterpret_cast<TriggerTypeClass**>(TriggerTypeClass::Array.Items)[i];
                    goto have_item;
                }
                ++i;
            }

            item = new TriggerTypeClass(key);
            goto have_item;
        }

        item = 0;
have_item:
        TriggerTypeLoadCallView* view = reinterpret_cast<TriggerTypeLoadCallView*>(item);
        (view->*view->Vtable->LoadFromINI)(ini);
    }
}


// FUNCTION: GAMEMD 0x727880
//
// Clear the three trigger sections and rewrite them. Each key in a section
// names a subsection, which is cleared with it; the section itself follows.
// The key names for all three are looked up in the Triggers section, which
// is where the per-trigger records live. Every registered trigger type then
// writes itself back.
//
// Each key name is bound to a local before the read: retail calls
// GetKeyName and only then pushes the read's own arguments, where the
// nested call form pushes the constants first.
void TriggerTypeClass::SaveToINIList(CCINI_00727880* ini)
{
    char buffer[0x20];
    int  i;

    int count = ini->GetKeyCount(DAT_007F58C8);
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007F58C8, i);
        ini->ReadString(DAT_007F58C8, key, STR_00889F64, buffer, 0x20);
        ini->Clear(buffer, 0);
    }
    ini->Clear(DAT_007F58C8, 0);

    count = ini->GetKeyCount(DAT_007F58D0);
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007F58D0, i);
        ini->ReadString(DAT_007F58C8, key, STR_00889F64, buffer, 0x20);
        ini->Clear(buffer, 0);
    }
    ini->Clear(DAT_007F58D0, 0);

    count = ini->GetKeyCount(DAT_007F58CC);
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007F58CC, i);
        ini->ReadString(DAT_007F58C8, key, STR_00889F64, buffer, 0x20);
        ini->Clear(buffer, 0);
    }
    ini->Clear(DAT_007F58CC, 0);

    for (i = 0; i < TriggerTypeClass::Array.Count; i++) {
        TriggerTypeClass* item = reinterpret_cast<TriggerTypeClass**>(TriggerTypeClass::Array.Items)[i];
        TriggerTypeSaveCallView* view = reinterpret_cast<TriggerTypeSaveCallView*>(item);
        (view->*view->Vtable->Method)(ini);
    }
}


// FUNCTION: GAMEMD 0x00727AA0 (entry through RET at 0x727B22, 0x83 bytes)
// GLOBAL: GAMEMD 0x8B4178 TriggerTypeClass::Array (Items +4, Count +0x10).
// Calls constructor 0x726C80; sizeof(TriggerTypeClass) 0xB4.
TriggerTypeClass* TriggerTypeClass::FindOrAllocate(const char* id)
{
    if (_strcmpi("<none>", id) != 0 && _strcmpi("none", id) != 0)
    {
        for (int i = 0; i < TriggerTypeClass::Array.Count; ++i)
        {
            if (_strcmpi(reinterpret_cast<TriggerTypeClass**>(TriggerTypeClass::Array.Items)[i]->ID, id) == 0)
                return reinterpret_cast<TriggerTypeClass**>(TriggerTypeClass::Array.Items)[i];
        }
        return new TriggerTypeClass(id);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x727BF0
HRESULT __stdcall TriggerTypeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0)
        return hr;
    new (this) TriggerTypeClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&NextTrigger);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&FirstEvent);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&FirstAction);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&House);
    return 0;
}


// FUNCTION: GAMEMD 0x727CA0
// Returns a constant. Vtable slot 11 of TriggerTypeClass (RTTI).
int TriggerTypeClass::vf_11()
{
    return 0x27;
}

// FUNCTION: GAMEMD 0x727CB0
// Returns a constant. Vtable slot 12 of TriggerTypeClass (RTTI).
int TriggerTypeClass::vf_12()
{
    return 0xB4;
}

// FUNCTION: GAMEMD 0x727CC0
// Member getter (dword). Vtable slot 16 of TriggerTypeClass (RTTI).
int Obj_00727CC0::FUN_00727CC0() const
{
    return unknown_98;
}

// SYNTHETIC: GAMEMD 0x727CD0 -- TriggerTypeClass scalar deleting destructor, emitted by the compiler from the virtual destructor

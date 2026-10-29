// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small methods and
//   leaves from the 0x63A000-0x6AD000 range; receivers are placeholder views of the members used.
//
// Address index: 0x645BB0 0x6ACB60 0x664390 0x664400 0x690F70 0x68CA50 0x68CAB0 0x5D26C0 0x65D480 0x642E40 0x5D4ED0 0x5AE460 0x5AE4C0 0x5AE500 0x5AE530

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../map/msanim_family_methods.h"

// FUNCTION: GAMEMD 0x645BB0
// Map a small index to its flag bit; unknown indices give zero.
int __fastcall FUN_00645BB0(int index)
{
    switch (index) {
    case 1:
    case 8:
        return 0;
    case 2:  return 0x20;
    case 3:  return 0x40;
    case 4:  return 0x8;
    case 5:  return 0x10;
    case 6:  return 0x1000;
    case 7:  return 0x2000;
    case 9:  return 0x800;
    case 10: return 0x8000;
    case 11: return 0x10000;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6ACB60
// Map an index to its string-table id, or -1.
int __fastcall FUN_006ACB60(int index)
{
    if (index == 0) return 0x50B;
    if (index == 1) return 0x50E;
    if (index == 2) return 0x516;
    if (index == 3) return 0x51A;
    if (index == 4) return 0x51B;
    if (index == 5) return 0x51C;
    if (index == 6) return 0x51D;
    return -1;
}

// One record of the keyed list: key byte at +0x00, name text from +0x01, word at +0x25, byte at +0x28.
#pragma pack(push, 1)
struct KeyedRec_00663D60
{
    char Key;                  // +0x00
    char Name[0x24];           // +0x01
    short Word;                // +0x25
    char unknown_27;
    char Flag;                 // +0x28
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(KeyedRec_00663D60, Word) == 0x25);
GG_STATIC_ASSERT(offsetof(KeyedRec_00663D60, Flag) == 0x28);

struct KeyedList_00663D60
{
    int unknown_00;
    KeyedRec_00663D60** Items;   // +0x04
    int unknown_08;
    int unknown_0C;
    int Count;                   // +0x10

    short FUN_00664390(const char* name);
    void FUN_00664400(int key, short value);
};
GG_STATIC_ASSERT(offsetof(KeyedList_00663D60, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(KeyedList_00663D60, Count) == 0x10);

// FUNCTION: GAMEMD 0x664390
// The word of the first record whose name matches, or zero.
short KeyedList_00663D60::FUN_00664390(const char* name)
{
    for (int i = 0; i < Count; i++) {
        if (_stricmp(Items[i]->Name, name) == 0) {
            return Items[i]->Word;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x664400
// Store the word on the record with the given key.
void KeyedList_00663D60::FUN_00664400(int key, short value)
{
    for (int i = 0; i < Count; i++) {
        if (Items[i]->Key == key) {
            Items[i]->Word = value;
            return;
        }
    }
}

// A countdown stamped against the shared clock: stamp at +0x0C, clock at +0x10, remaining at +0x14.
struct CountdownView_00690F70
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    MSTimerView Timer;     // +0x0C

    void FUN_00690F70();
};
GG_STATIC_ASSERT(offsetof(CountdownView_00690F70, Timer) == 0x0C);

// FUNCTION: GAMEMD 0x690F70
// Bank the time still left and stop the countdown.
void CountdownView_00690F70::FUN_00690F70()
{
    if (Timer.StartTime != -1) {
        int left = Timer.TimeLeft();
        Timer.Remaining = left;
        Timer.StartTime = -1;
    }
}

// Colour scheme record: name text pointer at +0x304 and an id at +0x310.
struct SchemeRec_0068CA50
{
    char        unknown_000[0x304];
    const char* Name;              // +0x304
    char        unknown_308[8];
    int         Id;                // +0x310
};
GG_STATIC_ASSERT(offsetof(SchemeRec_0068CA50, Name) == 0x304);
GG_STATIC_ASSERT(offsetof(SchemeRec_0068CA50, Id) == 0x310);

// GLOBAL: GAMEMD 0xB054E0
extern int DAT_00B054E0;
// GLOBAL: GAMEMD 0xB054D4
extern SchemeRec_0068CA50** DAT_00B054D4;

__forceinline int SchemeIndex_0068CA50(const char* name, int id)
{
    for (int i = 0; i < DAT_00B054E0; i++) {
        if (_stricmp(name, DAT_00B054D4[i]->Name) == 0 && DAT_00B054D4[i]->Id == id) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x68CA50
// The scheme record with the given name and id, or null.
SchemeRec_0068CA50* __fastcall FUN_0068CA50(const char* name, int id)
{
    int index = SchemeIndex_0068CA50(name, id);
    if (index >= 0) {
        return DAT_00B054D4[index];
    }
    return 0;
}

// FUNCTION: GAMEMD 0x68CAB0
// The index of the scheme with the given name and id, or -1.
int __fastcall FUN_0068CAB0(const char* name, int id)
{
    return SchemeIndex_0068CA50(name, id);
}

// Polymorphic list item: slot 8 takes one argument.
class ListItem_005D26C0
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Notify(int arg);   // slot 8
};

struct ItemList_005D26C0
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0C;
    int unknown_10;
    int unknown_14;
    int unknown_18;
    ListItem_005D26C0** Items;   // +0x1C
    int unknown_20;
    int unknown_24;
    int Count;                   // +0x28

    void FUN_005D26C0(int arg);
};
GG_STATIC_ASSERT(offsetof(ItemList_005D26C0, Items) == 0x1C);
GG_STATIC_ASSERT(offsetof(ItemList_005D26C0, Count) == 0x28);

// FUNCTION: GAMEMD 0x5D26C0
// Pass the argument to every item in order.
void ItemList_005D26C0::FUN_005D26C0(int arg)
{
    for (int i = 0; i < Count; i++) {
        Items[i]->Notify(arg);
    }
}

// Reference-counted target: count at +4, slot 2 releases.
class RefObj_0065D480
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Release();   // slot 2
    int RefCount;             // +0x04
};

struct RefHolder_0065D480
{
    int unknown_00;
    RefObj_0065D480* Target;  // +0x04

    void FUN_0065D480(RefObj_0065D480* other);
};

// FUNCTION: GAMEMD 0x65D480
// Take a new counted reference, releasing the old one.
void RefHolder_0065D480::FUN_0065D480(RefObj_0065D480* other)
{
    if (other != Target) {
        if (other != 0) {
            other->RefCount++;
        }
        if (Target != 0) {
            RefObj_0065D480* old = Target;
            Target = 0;
            old->Release();
        }
        Target = other;
    }
}

// Object queried for two values through slots 31 and 32.
class Source_00642E40
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual int GetFirst();    // slot 31
    virtual int GetSecond();   // slot 32
};

// FUNCTION: GAMEMD 0x4E3560 (decl; reloc) -- answers the current source, or null.
Source_00642E40* __fastcall FUN_004E3560(int arg);

// FUNCTION: GAMEMD 0x642E40
// Report the two values of the current source, or null for both when there is none.
void __stdcall FUN_00642E40(int* first, int* second)
{
    Source_00642E40* source = FUN_004E3560(0);
    if (source == 0) {
        *first = (int)source;
        *second = (int)source;
        return;
    }
    *first = source->GetFirst();
    *second = source->GetSecond();
}

// Growable list of pointers: index lookup at slot 4, items at +0x04, count at +0x10.
class PtrList_005D4ED0
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual int  IndexOf(void* const& item);   // slot 4
    void** Items;      // +0x04
    int    unknown_08;
    int    unknown_0C;
    int    Count;      // +0x10
};

// GLOBAL: GAMEMD 0xABFC90 -- the list object itself
extern char DAT_00ABFC90[];

// FUNCTION: GAMEMD 0x5D4ED0
// Remove an entry from the global list, closing the gap.
void __fastcall FUN_005D4ED0(void* item)
{
    PtrList_005D4ED0* list = (PtrList_005D4ED0*)DAT_00ABFC90;
    int index = list->IndexOf(item);
    if (index != -1 && index < list->Count) {
        list->Count--;
        for (; index < list->Count; index++) {
            list->Items[index] = list->Items[index + 1];
        }
    }
}

// Heap-owning narrow string (4-byte handle), as the family header models it, with the entry points
// these methods reach.
struct NameStr_005AE4C0
{
    char* Str;
    bool FUN_007B47F0(const char* text) const;   // FUNCTION: GAMEMD 0x7B47F0 (decl; reloc)
    void FUN_007B4940(const char* text);         // FUNCTION: GAMEMD 0x7B4940 (decl; reloc)
};

class Slot_005D0590
{
public:
    int unknown_00;
    void FUN_005D0590();                         // FUNCTION: GAMEMD 0x5D0590 (decl; reloc)
};

struct SlotTable_005CF840
{
    Slot_005D0590* FUN_005CF840(const NameStr_005AE4C0* name);   // FUNCTION: GAMEMD 0x5CF840 (decl; reloc)
    void FUN_005CF5F0();                                         // FUNCTION: GAMEMD 0x5CF5F0 (decl; reloc)
};

// Named countdown: the name at +0xC8, the timer at +0xCC, the slot table at +0x50.
struct Named_005AE4C0
{
    char             unknown_00[0x50];
    SlotTable_005CF840 Slots;          // +0x50
    char             unknown_50[0xC8 - 0x50 - sizeof(SlotTable_005CF840)];
    NameStr_005AE4C0 Name;             // +0xC8
    MSTimerView          Timer;            // +0xCC

    int  FUN_005AE4C0();
    void FUN_005AE500(const NameStr_005AE4C0* name);
    void FUN_005AE530(const char* name, int duration);
};
GG_STATIC_ASSERT(offsetof(Named_005AE4C0, Name) == 0xC8);
GG_STATIC_ASSERT(offsetof(Named_005AE4C0, Timer) == 0xCC);

// FUNCTION: GAMEMD 0x5AE4C0
// Read the clock when a name is set and the countdown is running.
int Named_005AE4C0::FUN_005AE4C0()
{
    if (Name.FUN_007B47F0(0) && Timer.StartTime != -1) {
        return Timer.Clock.GetTime();
    }
}

// FUNCTION: GAMEMD 0x5AE500
// Look the given name up in the slot table and wake the slot found.
void Named_005AE4C0::FUN_005AE500(const NameStr_005AE4C0* name)
{
    if (name->FUN_007B47F0(0)) {
        Slot_005D0590* slot = Slots.FUN_005CF840(name);
        if (slot != 0) {
            slot->FUN_005D0590();
        }
    }
}

// FUNCTION: GAMEMD 0x5AE530
// Set the name and restart the countdown for the given duration.
void Named_005AE4C0::FUN_005AE530(const char* name, int duration)
{
    Name.FUN_007B4940(name);
    Timer = MSTimerView(duration);
}

// Polymorphic member with a deleting destructor in slot zero.
class Owned_005AE460
{
public:
    virtual ~Owned_005AE460();
};

struct Owner_005AE460
{
    char               unknown_00[0x50];
    SlotTable_005CF840 Slots;          // +0x50
    char               unknown_54[0xAC - 0x54];
    Owned_005AE460*    First;          // +0xAC
    Owned_005AE460*    Second;         // +0xB0
    Owned_005AE460*    Third;          // +0xB4

    void FUN_005AE460();
};
GG_STATIC_ASSERT(offsetof(Owner_005AE460, First) == 0xAC);
GG_STATIC_ASSERT(offsetof(Owner_005AE460, Third) == 0xB4);

// FUNCTION: GAMEMD 0x5AE460
// Delete the three owned members, newest first, then reset the slot table.
void Owner_005AE460::FUN_005AE460()
{
    if (Third) {
        delete Third;
        Third = 0;
    }
    if (Second) {
        delete Second;
        Second = 0;
    }
    if (First) {
        delete First;
        First = 0;
    }
    Slots.FUN_005CF5F0();
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB054E0
int DAT_00B054E0;
// END defined globals

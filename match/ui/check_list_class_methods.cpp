// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Bodies ascending by retail address; bytes diffed against the user's
//   retail gamemd.exe v1.001.
#include "check_list_class_methods.h"

// Retail carries this destructor twice -- once out of line at 0x4882D0 and once
// expanded inside the deleting thunk at 0x4886E0 -- so the drain loop is spelled
// out in both rather than delegated.
//
// Both copies need the vtable seat written through a volatile lvalue cast.
// Retail stores the vptr and only then loads the entry count; with a plain
// assignment cl hoists the count load above the store and the two copies sit at
// 92.0% with an otherwise identical stream. Measured against the plain store,
// a guarded do/while, a volatile *read* of the count, both volatile, a count
// cached in a local and refreshed at the latch, the drain lifted into a
// forced-inline helper, and the seat written through a layout-compatible
// stand-in: every one of those is 92.0%, and only the volatile store is 100%.
// (An earlier pass recorded "a volatile store" as tried and failing; that was a
// volatile *member*, which is a different probe from the lvalue cast.)

// FUNCTION: GAMEMD 0x4882D0
// CheckListClass::~CheckListClass. Each entry is a heap node the base list does
// not own, so the destructor drains the list one entry at a time -- read entry
// zero, unhook it, free it -- and then runs the base list destructor.
void CheckListClass::Dtor()
{
    *(CheckListVtbl* volatile*)&this->Vfptr = (CheckListVtbl*)VT_007E4F84;

    while (this->List.ActiveCount != 0) {
        CheckItemClass* item = (CheckItemClass*)this->ListClass_GetItem(0);

        this->ListClass_RemoveItem(0);
        delete item;
    }
    this->ListClass_Dtor();
}

// FUNCTION: GAMEMD 0x488310
// CheckListClass::Add_Item. Wraps the text in an unchecked heap node and hands
// the node to the base list in the text slot. A failed allocation still calls
// through with a null entry, which is the new-expression's own shape.
void CheckListClass::AddItem(wchar_t const* text)
{
    this->ListClass_AddItem((wchar_t const*)new CheckItemClass(text));
}

// FUNCTION: GAMEMD 0x488380
// CheckListClass::Remove_Item(text). Scans the entries for the one whose text
// compares equal, unhooks it from the base list and frees its node.
void CheckListClass::RemoveItem(wchar_t const* text)
{
    for (int i = 0; i < (this->*this->Vfptr->At_94)(); i++) {
        CheckItemClass* item = (CheckItemClass*)this->ListClass_GetItem(i);

        if (item != 0 && wcscmp(item->Text, text) == 0) {
            this->ListClass_RemoveItem(i);
            delete item;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x4883F0
// The same scan as above, but the matching entry is handed to the virtual at
// slot +0xB8 by index instead of being removed -- the select-by-text form.
void CheckListClass::FUN_004883F0(wchar_t const* text)
{
    for (int i = 0; i < (this->*this->Vfptr->At_94)(); i++) {
        CheckItemClass* item = (CheckItemClass*)this->ListClass_GetItem(i);

        if (item != 0 && wcscmp(item->Text, text) == 0) {
            (this->*this->Vfptr->At_B8)(i);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x4884A0
// CheckListClass::Action. A read-only list swallows the event outright.
// Otherwise the base list handles it, and a left-button event toggles the
// selected entry's check mark, repainting only when the mark actually changed.
int CheckListClass::Action(unsigned flags, void* key, int extra)
{
    if (this->IsReadOnly) {
        return 0;
    }

    {
        int result = this->ListClass_Action(flags, key, 0);

        if (flags & 1) {
            int sel = this->SelectedIndex;
            CheckItemClass* cur = (CheckItemClass*)this->ListClass_GetItem(sel);
            bool want = !(cur != 0 ? cur->IsChecked : false);
            int selAgain = this->SelectedIndex;
            CheckItemClass* item =
                (CheckItemClass*)this->ListClass_GetItem(selAgain);

            if (item != 0 && item->IsChecked != want) {
                item->IsChecked = want;
                (this->*this->Vfptr->At_48)();
            }
        }
        return result;
    }
}

// FUNCTION: GAMEMD 0x4886E0
// CheckListClass::`scalar deleting destructor'. The destructor body is expanded
// here rather than called, so the drain loop is spelled out a second time.
CheckListClass* CheckListClass::ScalarDeletingDtor(unsigned char flags)
{
    *(CheckListVtbl* volatile*)&this->Vfptr = (CheckListVtbl*)VT_007E4F84;

    while (this->List.ActiveCount != 0) {
        CheckItemClass* item = (CheckItemClass*)this->ListClass_GetItem(0);

        this->ListClass_RemoveItem(0);
        delete item;
    }
    this->ListClass_Dtor();

    if (flags & 1) {
        ::operator delete(this);
    }
    return this;
}

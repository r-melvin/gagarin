// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bodies ascending by retail address; bytes diffed against the user's
//   retail gamemd.exe v1.001.
#include "check_list_class_methods.h"

// Retail carries this destructor twice -- once out of line at 0x4882D0 and once
// expanded inside the deleting thunk at 0x4886E0 -- so the drain loop is spelled
// out in both rather than delegated.
//
// Both copies are PARTIAL with the plain vptr store (0x4882D0 92.0%, 23/25;
// 0x4886E0 93.5%, 29/31): retail stores the vptr and only then loads the entry
// count, and cl hoists the count load above the store.

// FUNCTION: GAMEMD 0x4882D0
// CheckListClass::~CheckListClass. Each entry is a heap node the base list does
// not own, so the destructor drains the list one entry at a time -- read entry
// zero, unhook it, free it -- and then runs the base list destructor.
void CheckListClass::Dtor()
{
    this->Vfptr = (CheckListVtbl*)VT_007E4F84;

    while (this->List.Count != 0) {
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
            bool want = !(cur != 0 ? cur->IsTicked : false);
            int selAgain = this->SelectedIndex;
            CheckItemClass* item =
                (CheckItemClass*)this->ListClass_GetItem(selAgain);

            if (item != 0 && item->IsTicked != want) {
                item->IsTicked = want;
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
    this->Vfptr = (CheckListVtbl*)VT_007E4F84;

    while (this->List.Count != 0) {
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

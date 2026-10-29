// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bodies ascending by retail address; bytes diffed against the user's
//   retail gamemd.exe v1.001. The class is the canonical CheckListClass in
//   input_controls/ui_gadget.h (RTTI .?AVCheckListClass@@, vtable 0x7E4F84).
//   Retail carries the destructor twice -- out of line at 0x4882D0 and expanded
//   inside the compiler's scalar deleting destructor at 0x4886E0. One virtual
//   destructor definition under /Ob2 yields both.

#include "input_controls/lists_views.h"

// LIBRARY: GAMEMD 0x7DD0F8 (decl; reloc) -- CRT _wcsicmp: the two text lookups compare case-insensitively.
extern "C" int __cdecl _wcsicmp(wchar_t const* a, wchar_t const* b);

// FUNCTION: GAMEMD 0x4882D0
// SYNTHETIC: GAMEMD 0x4886E0
// CheckListClass::~CheckListClass. Each entry is a heap node the base list does
// not own, so the destructor drains the list one entry at a time -- read entry
// zero, unhook it, free it -- and the base list destructor runs afterwards.
CheckListClass::~CheckListClass()
{
    while (List.GetCount() != 0) {
        CheckItemClass* item = (CheckItemClass*)ListClass::GetItem(0);

        ListClass::RemoveItem(0);
        delete item;
    }
}

// FUNCTION: GAMEMD 0x488310
// CheckListClass::AddItem. Wraps the text in an unchecked heap node and hands
// the node to the base list in the text slot. A failed allocation still calls
// through with a null entry, which is the new-expression's own shape.
int CheckListClass::AddItem(wchar_t const* text)
{
    return ListClass::AddItem((wchar_t const*)new CheckItemClass(text));
}

// FUNCTION: GAMEMD 0x488380
// CheckListClass::RemoveItem(text). Scans the entries for the one whose text
// compares equal, unhooks it from the base list and frees its node.
void CheckListClass::RemoveItem(wchar_t const* text)
{
    for (int i = 0; i < GetCount(); i++) {
        CheckItemClass* item = (CheckItemClass*)ListClass::GetItem(i);

        if (item != 0 && _wcsicmp(item->Text, text) == 0) {
            ListClass::RemoveItem(i);
            delete item;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x4883F0
// The same scan as above, but the matching entry is handed to the virtual at
// slot +0xB8 by index instead of being removed -- the select-by-text form.
void CheckListClass::SetSelectedText(wchar_t const* text)
{
    for (int i = 0; i < GetCount(); i++) {
        CheckItemClass* item = (CheckItemClass*)ListClass::GetItem(i);

        if (item != 0 && _wcsicmp(item->Text, text) == 0) {
            vf_46(i);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x4884A0
// CheckListClass::Action. A read-only list swallows the event outright.
// Otherwise the base list handles it, and a left-button event toggles the
// selected entry's check mark, repainting only when the mark actually changed.
int CheckListClass::Action(unsigned flags, unsigned* key, int modifier)
{
    if (IsReadOnly) {
        return 0;
    }

    int result = ListClass::Action(flags, key, 0);

    if (flags & 1) {
        int sel = SelectedIndex;
        CheckItemClass* cur = (CheckItemClass*)ListClass::GetItem(sel);
        bool want = !(cur != 0 ? cur->IsChecked : false);
        int selAgain = SelectedIndex;
        CheckItemClass* item = (CheckItemClass*)ListClass::GetItem(selAgain);

        if (item != 0 && item->IsChecked != want) {
            item->IsChecked = want;
            MarkRedraw();
        }
    }
    return result;
}

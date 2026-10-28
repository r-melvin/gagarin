// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5D3F60, 0x5D3F90 and 0x5D41E0
//   (list head at MessageListClass+0, label key at +0x28, label text at +0x30).
//
// Address index: 0x5D3F60 0x5D3F90 0x5D41E0

#include "message_list_class_methods.h"
#include "input_controls/ui_gadget.h"

// FUNCTION: GAMEMD 0x5D3F60
// Walks the label list for the label with the given key and returns its text, or 0.
const wchar_t* MessageListClass::FUN_005D3F60(int key)
{
    TextLabelClass* label = MessageList;
    while (label) {
        if (label->unknown_28 == key)
            return label->Text;
        label = static_cast<TextLabelClass*>(label->GetNext());
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5D3F90
// Walks the label list for the label with the given key and returns it, or 0.
TextLabelClass* MessageListClass::FUN_005D3F90(int key)
{
    TextLabelClass* label = MessageList;
    while (label) {
        if (label->unknown_28 == key)
            return label;
        label = static_cast<TextLabelClass*>(label->GetNext());
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5D41E0
// While editing, gives the edit label the focus.
void MessageListClass::FUN_005D41E0()
{
    if (IsEdit)
        EditLabel->SetFocus();
}

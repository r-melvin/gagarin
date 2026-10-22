// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   FUNCTION: GAMEMD 0x5D4AD0  MessageListClass::SetWidth   (__thiscall)
//   LIBRARY:  GAMEMD 0x4068E0  FUN_004068E0 (variadic; release stub)
//   STRING:   GAMEMD 0x8306A8  "MessageListClass"
//
// Bytes reconfirmed from the local Ghidra disassembly of retail gamemd.exe.
#include "message_list_class_more_methods.h"

// Release-build debug printf (0x4068E0 is a bare RET stub). cdecl/variadic so
// the call pushes exactly { format, value }. Reloc-normalised.
extern "C" int __cdecl FUN_004068E0(const char* fmt, ...);

// FUNCTION: GAMEMD 0x5D4AD0  (__thiscall)
// Apply a new width (less an 8px margin) to the list and every gadget: store on
// the object (+0x2C4), trace, walk the GetNext list assigning each node's Width
// (+0x38), then the edit-line gadget when an edit is active.
void MessageListClass::SetWidth(int width)
{
    width -= 8;
    Width = width;
    FUN_004068E0("MessageListClass", width);

    TextLabelClass* node = MessageList;
    while (node)
    {
        node->Width = width;
        node = node->GetNext();
    }

    if (IsEdit)
        EditLabel->Width = width;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp MessageListClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5D4400  MessageListClass::GetEditBuffer (__thiscall)
//   FUNCTION: GAMEMD 0x5D4AA0  MessageListClass::NumMessages   (__thiscall)
//   FUNCTION: GAMEMD 0x5D4BF0  MessageListClass::ComputeY      (__thiscall)

#include "message_list_class_methods.h"

// FUNCTION: GAMEMD 0x5D4400  (__thiscall)
// &EditBuffer[EditInitialPos]:  mov eax,[ecx+0x2b4]; lea eax,[ecx+eax*2+0x28].
wchar_t* MessageListClass::GetEditBuffer() const
{
    return (wchar_t*)&EditBuffer[EditInitialPos];
}

// FUNCTION: GAMEMD 0x5D4AA0  (__thiscall)
// Count the message gadgets (walk the GetNext list), plus one for the active
// edit line when IsEdit && AdjustEdit.
int MessageListClass::NumMessages() const
{
    int count = 0;
    for (TextLabelClass* node = MessageList; node; node = node->GetNext())
        ++count;
    if (IsEdit && AdjustEdit)
        ++count;
    return count;
}

// FUNCTION: GAMEMD 0x5D4BF0  (__thiscall)
// Re-stack the message labels vertically: start at MessagePos.Y (offset by the
// edit-line height when an adjustable edit is active), then assign each gadget's
// Y and step down by Height.
void MessageListClass::ComputeY()
{
    int y;
    if (IsEdit && AdjustEdit)
        y = Height + MessagePos_Y;
    else
        y = MessagePos_Y;

    TextLabelClass* node = MessageList;
    while (node)
    {
        node->Y = y;
        node = node->GetNext();
        y += Height;
    }
}

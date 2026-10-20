// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x724AD0 (name from the
//   YRpp method map, consult-only).

#include "tool_tip_manager_process_methods.h"

// FUNCTION: GAMEMD 0x724AD0
//
// Resolve the current tooltip's text and position it. The text comes from the
// string table when the tip carries a label, otherwise from the virtual by
// gadget id. Empty text drops the tip; otherwise the text is copied into the
// help block, the block is anchored at the mouse and handed to Update, whose
// refusal also drops the tip. Reports whether a tip is still current.
//
// Both drop paths fall through to the single trailing return: VC6 duplicates
// that tail into the Update-refused block with the just-stored zero forwarded
// (`MOV ECX,EBX .. CMP ECX,EBX; SETNZ AL`), which an explicit `return` in that
// block folds away to a bare register return instead.
bool ToolTipManager::Process()
{
    ToolTip* tip = this->CurrentToolTip;
    if (tip != 0) {
        wchar_t* text;
        if (tip->Text == 0)
            text = this->GetToolTipText(tip->GadgetID);
        else
            // STRING: GAMEMD 0x8449CC
            text = StringTable_LoadString(tip->Text, 0, "D:\\ra2mdpost\\ToolTip.cpp", 0x233);

        if (text != 0 && wcslen(text) > 0) {
            wcsncpy(this->CurrentToolTipData.HelpText, text, 0x100);
            this->CurrentToolTipData.X = this->CurrentMousePosition.X;
            this->CurrentToolTipData.Y = this->CurrentMousePosition.Y;
            if (!this->Update(this->CurrentToolTipData)) {
                ClearDimension(this->CurrentToolTipData);
                this->CurrentToolTip = 0;
            }
        } else {
            ClearDimension(this->CurrentToolTipData);
            this->CurrentToolTip = 0;
        }
    }
    return this->CurrentToolTip != 0;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x69E010 / 0x6CFCC0 /
//   0x6D09C0 (Ghidra disasm). Names cross-checked against YRpp
//   ShapeButtonClass.h / ToolTipManager.h (consult-only, no LICENSE; each
//   offset reconfirmed against the user's binary).
//
// Translation unit: ShapeButtonClass flash AI + static helpers.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x69E010   ShapeButtonClass::AI         (__thiscall)
//   FUNCTION: GAMEMD 0x6CFCC0   ShapeButtonClass::FindIndex  (__fastcall)
//   FUNCTION: GAMEMD 0x6D09C0   ShapeButtonClass::SetToolTip (__fastcall)

#include "shape_button_class_ai_methods.h"
#include <string.h>  // strcmp (intrinsic under /O2)

// FUNCTION: GAMEMD 0x69E010   ShapeButtonClass::AI  (__thiscall)
//   if (field_1e == 0) {                 // countdown mode
//       if (FlashCounter != 0 && --FlashCounter == 0) {
//           IsToFlash = !IsToFlash; FlashCounter = FlashDelay; return true;
//       }
//   } else if (FlashDelay != 0) {        // reset mode
//       IsToFlash = 0; FlashCounter = 0; FlashDelay = 0; return true;
//   }
//   return false;
bool ShapeButtonClass::AI()
{
    if (this->field_1e != 0)
    {
        if (this->FlashDelay != 0)
        {
            this->IsToFlash = 0;
            this->FlashCounter = 0;
            this->FlashDelay = 0;
            return true;
        }
    }
    else if (this->FlashCounter != 0)
    {
        if (--this->FlashCounter == 0)
        {
            this->IsToFlash = (this->IsToFlash == 0);
            this->FlashCounter = this->FlashDelay;
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6CFCC0   ShapeButtonClass::FindIndex  (__fastcall)
//   Linear scan of the 11-entry CommandNames table; return the matching index
//   or the not-found default. strcmp is the /O2 intrinsic (2 bytes/iter).
int __fastcall ShapeButtonClass::FindIndex(const char* name)
{
    int index = 0;
    const char* const* p;
    // Retail compares the running pointer against &CommandNames[11] as a
    // SIGNED address (Ghidra: `(int)ppuVar6`), so the bound check is an `int`
    // cast — that yields `jl`, not the unsigned `jb` of a raw pointer compare.
    for (p = CommandNames; (int)p < (int)(CommandNames + 11); ++p)
    {
        if (strcmp(*p, name) == 0)
            return index;
        ++index;
    }
    return DefaultCommandIndex;
}

// FUNCTION: GAMEMD 0x6D09C0   ShapeButtonClass::SetToolTip  (__fastcall)
//   Build a ToolTip from the button's gadget rect + ID and the supplied text,
//   then refresh the global ToolTipManager entry.
void __fastcall ShapeButtonClass::SetToolTip(ShapeButtonClass* pButton, const char* tip)
{
    if (pButton)
    {
        ToolTip tooltip;
        tooltip.Text = tip;
        tooltip.field_18 = false;
        tooltip.GadgetID = pButton->ID;
        tooltip.X = pButton->X;
        tooltip.Y = pButton->Y;
        tooltip.Width = pButton->Width;
        tooltip.Height = pButton->Height;
        ToolTipManager_Instance->Remove(tooltip.GadgetID);
        ToolTipManager_Instance->Add(tooltip);
    }
}

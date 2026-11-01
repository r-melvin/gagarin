// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x642AD0, 0x642AE0,
//   0x642DF0 and 0x642B30.

#include "load_screen_side_caption_methods.h"

// FUNCTION: GAMEMD 0x642AD0
void LoadScreenClass_00642AD0::ClearFlag060()
{
    this->Flag060 = 0;
}

// FUNCTION: GAMEMD 0x642AE0
//
// Release the owned buffer, if any, then unconditionally null the pointer --
// the ordinary "free once, clear always" shape.
void LoadScreenClass_00642AD0::ReleaseBuffer()
{
    if (this->BufferOwned != 0) {
        gg_free_0642AE0(this->Buffer);
        this->BufferOwned = 0;
    }
    this->Buffer = 0;
}

// FUNCTION: GAMEMD 0x642DF0
void LoadScreenClass_00642AD0::SetAt078(int value)
{
    this->At078 = value;
}

// FUNCTION: GAMEMD 0x642B30
//
// Tail call into the gadget-by-caption finder with the caption literal
// picked by side; `return`-ing it directly (rather than storing then
// returning) is what lets cl fold the call into retail's `JMP`.
void* LoadScreenClass_00642AD0::PickSideCaptionGadget()
{
    if (this->PlayerSide == 0) {
        return FindGadgetByCaption_0068CA50(STR_00836EC0, 1);
    }
    return FindGadgetByCaption_0068CA50(STR_00836EB4, 1);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x836EB4
extern const char STR_00836EB4[] = "SovietLoad";
// GLOBAL: GAMEMD 0x836EC0
extern const char STR_00836EC0[] = "AlliedLoad";
// END defined globals

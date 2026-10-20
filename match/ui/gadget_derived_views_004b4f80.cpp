// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The two complete entry-origin bodies and their exact extents are recorded
//   in gadget_derived_views_004b4f80.h. The helper at 0x007CA422 was inspected
//   directly in retail and uses bounded 16-bit copying.
#include "gadget_derived_views_004b4f80.h"

// LIBRARY: GAMEMD 0x007CA422
// Retail body performs a count-bounded 16-bit string copy with zero-padding,
// matching the CRT wcsncpy operation; the library implementation is out of scope.
extern "C" unsigned short* __cdecl FUN_007CA422(unsigned short* destination,
                                                unsigned short* source,
                                                int count);

// FUNCTION: GAMEMD 0x004B4F80
void GadgetDerivedView_004B4F80::FUN_004B4F80()
{
    if (this->unknown_48) {
        this->PartB0.Slot9();
        this->unknown_48 = 0;
    }
    this->Part50.Slot9();
    this->GadgetClass::Remove();
}

// FUNCTION: GAMEMD 0x004B4FB0
void GadgetDerivedMethodView_004B4FB0::FUN_004B4FB0(unsigned short* value)
{
    FUN_007CA422(this->unknown_34,
                 value, this->unknown_38);
    this->MarkRedraw();
    this->PartB0.Slot34(value);
}

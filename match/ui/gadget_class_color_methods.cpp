// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4E12D0.

#include "gadget_class_color_methods.h"

// FUNCTION: GAMEMD 0x4E12D0  GadgetClass::GetColorScheme (__fastcall, static)
// Entry 1 of the colour-scheme collection, dereferenced to its first field.
// A missing entry degrades to 0 rather than faulting.
int __fastcall GadgetClass::GetColorScheme()
{
    void* scheme = ColorSchemeCollection_GetItem(ColorSchemeCollection, 1);
    if (scheme != 0)
        return *(int*)scheme;

    return 0;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x68C9C0.

#include "color_scheme_find_methods.h"

// FUNCTION: GAMEMD 0x68C9C0  ColorScheme::FindByName (__fastcall, static)
// Return the index of the scheme matching this name and shade, creating it
// first if it does not exist. The create path does not return the new object —
// it falls back into the scan, which then finds it. Writing that as an outer
// `for (;;)` is what produces retail's two backward jumps to 0x68C9D3.
//
// The constructor is declared `throw()`: `new` with a throwing constructor
// makes VC6 emit an SEH frame that retail does not have (§4.6).
//
// Argument order to _stricmp is (name, candidate), read off the push order —
// the opposite of HouseTypeClass::FindIndexOfName's inner compare. Getting it
// backwards costs two instructions and 3.8%.
int __fastcall ColorScheme::FindByName(const char* name, HSVClass* hsv,
                                       PaletteClass* pal1, PaletteClass* pal2,
                                       int shade)
{
    for (;;)
    {
        for (int i = 0; i < ColorSchemeArray.Count; i++)
        {
            if (_stricmp(name, ((ColorScheme**)ColorSchemeArray.Items)[i]->Name) == 0
             && ((ColorScheme**)ColorSchemeArray.Items)[i]->unknown_310 == shade)
            {
                return i;
            }
        }

        new ColorScheme(name, hsv, pal1, pal2, shade, true);
    }
}

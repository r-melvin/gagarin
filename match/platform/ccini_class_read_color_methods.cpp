// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x474C70.

#include "ccini_class_read_color_methods.h"

// FUNCTION: GAMEMD 0x474C70
//
// Read an "r,g,b" colour value. The default is first rendered to text so the
// string reader can hand it back when the key is missing; whatever text
// results is parsed with sscanf into three ints (zeroed first, so a short
// value leaves the tail black) and packed into the out struct. When the
// reader finds nothing at all the default is copied straight across.
ColorStruct* CCINIClass::ReadColor(ColorStruct* pOut, const char* pSection,
                                   const char* pKey, const ColorStruct& defValue)
{
    char defText[64];
    char buffer[64];

    sprintf(defText, "%d,%d,%d", defValue.R, defValue.G, defValue.B);
    if (this->ReadString(pSection, pKey, defText, buffer, sizeof(buffer))) {
        int r = 0;
        int g = 0;
        int b = 0;
        sscanf(buffer, "%d,%d,%d", &r, &g, &b);
        *pOut = ColorStruct((unsigned char)r, (unsigned char)g, (unsigned char)b);
    } else {
        *pOut = defValue;
    }
    return pOut;
}

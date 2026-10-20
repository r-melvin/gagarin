// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x474B50.

#include "ccini_class_read3bytes_methods.h"

// FUNCTION: GAMEMD 0x474B50
//
// Read an "R,G,B" triple from the INI. The default is first printed into a
// text buffer so the string reader can hand it back verbatim when the key is
// absent; a present key is parsed back into three ints and narrowed to bytes.
// When the reader reports nothing the default is returned unchanged.
ColorStruct CCINIClass::Read3Bytes(const char* section, const char* key,
                                   const ColorStruct& def)
{
    char defbuf[64];
    char buffer[64];
    int  r;
    int  g;
    int  b;

    sprintf(defbuf, "%d,%d,%d", def.R, def.G, def.B);

    if (this->ReadString(section, key, defbuf, buffer, sizeof(buffer))) {
        sscanf(buffer, "%d,%d,%d", &r, &g, &b);
        return ColorStruct((unsigned char)r, (unsigned char)g, (unsigned char)b);
    }

    return def;
}

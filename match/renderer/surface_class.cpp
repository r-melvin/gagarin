// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// ^ no /GX: paired probe on the XSurface scalar deleting destructor (0x4115A0): with /GX VC6 keeps a
// separate ~XSurface call (0/12), without it the destructor inlines and matches (12/12). The Blit*
// stack locals of 0x7BBB90 also carry no unwind frame in retail.
// Provenance: own-binary-via-Ghidra. Surface (RTTI .?AVSurface@@, vtable
// 0x7E2198) members; every body is the full CFG-closed RET-inclusive span.
#include "surface_class.h"

// FUNCTION: GAMEMD 0x4114F0
bool Surface::unknown_64(unsigned int, unsigned int)
{
    return true;
}

// FUNCTION: GAMEMD 0x411500
bool Surface::unknown_68(unsigned int, unsigned int)
{
    return true;
}

// FUNCTION: GAMEMD 0x411510
RectangleStruct Surface::GetRect() const
{
    RectangleStruct result;

    result.X = 0;
    result.Y = 0;
    result.Width = Width;
    result.Height = Height;

    return result;
}

// FUNCTION: GAMEMD 0x411540
int Surface::GetWidth() const
{
    return Width;
}

// FUNCTION: GAMEMD 0x411550
int Surface::GetHeight() const
{
    return Height;
}

// FUNCTION: GAMEMD 0x4115C0
bool Surface::unknown_84()
{
    return false;
}

// SYNTHETIC: GAMEMD 0x4115D0
// Scalar deleting wrapper emitted by the production Surface constructor TU.

// FUNCTION: GAMEMD 0x4AEC60
Surface::Surface(int width, int height) : Width(width), Height(height)
{
}

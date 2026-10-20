// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail Surface vtable 0x7E2198 slots +0x64/+0x68/+0x78/+0x7C/+0x80/+0x84 identify these
// methods; entry-origin instructions confirm the result ABI and member offsets.
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
// Surface rectangle result uses the retail hidden-result pointer ABI.
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
// Surface::`scalar deleting destructor', generated from the inline destructor.
// Full raw span is 0x20, including the post-delete stack cleanup and RET 4.

// FUNCTION: GAMEMD 0x4AEC60
Surface::Surface(int width, int height) : Width(width), Height(height)
{
}

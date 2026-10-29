// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Out-of-line copy of the (width, height) constructor of the surface base with vtable
// 0x7E2104, found inside the overlay unit's code range at 0x5FE020 and called from
// 0x5FD30B. Elsewhere retail expands this constructor inline (see
// match/renderer/dib_section_ctor_methods.cpp). The constructor is declared in the class
// and defined here, so it is emitted as an ordinary function without needing a caller.

// VTABLE: GAMEMD 0x7E2104
struct SurfaceBase_007E2104
{
    SurfaceBase_007E2104(int width, int height);
    virtual ~SurfaceBase_007E2104();

    int Width;       // +0x04
    int Height;      // +0x08
    int LockLevel;   // +0x0C
};

// FUNCTION: GAMEMD 0x5FE020
SurfaceBase_007E2104::SurfaceBase_007E2104(int width, int height)
    : Width(width), Height(height), LockLevel(0)
{
}

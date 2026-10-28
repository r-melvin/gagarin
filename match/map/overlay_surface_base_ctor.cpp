// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob0 /DNDEBUG /Gy /MT
//
// Out-of-line copy of the (width, height) constructor of the surface base with vtable
// 0x7E2104, found inside the overlay unit's code range at 0x5FE020. Elsewhere retail expands
// this constructor inline (see match/renderer/dib_section_ctor_methods.cpp); the stand-in
// function below only gives the compiler a call site, it is not a retail function.

#include <new.h>
// VTABLE: GAMEMD 0x7E2104
struct SurfaceBase_007E2104
{
    // FUNCTION: GAMEMD 0x5FE020
    SurfaceBase_007E2104(int width, int height) : Width(width), Height(height), LockLevel(0) {}
    virtual ~SurfaceBase_007E2104();

    int Width;       // +0x04
    int Height;      // +0x08
    int LockLevel;   // +0x0C
};

SurfaceBase_007E2104* SurfaceBaseCtorStandIn(void* p, int w, int h)
{
    return new (p) SurfaceBase_007E2104(w, h);
}

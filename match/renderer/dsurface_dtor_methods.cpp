// Provenance: own-binary-via-Ghidra
// SPDX-License-Identifier: GPL-3.0-or-later
// DSurface destructor body (non-deleting; four direct callers). Retail seats
// the DSurface table 0x7E85D4, detaches the shared primary clipper when this
// is the primary surface, frees the surface description, releases the
// DirectDraw surface, then seats the Surface table 0x7E2198 (the empty
// XSurface/Surface destructors inline away).
#include "dsurface_class.h"

// GLOBAL: GAMEMD 0x8A0DCC -- the clipper attached to the primary surface.
extern "C" DDClipper* DAT_008A0DCC;

// FUNCTION: GAMEMD 0x4BA6B0
DSurface::~DSurface()
{
    if (IsPrimary && DDSurf != 0 && DAT_008A0DCC != 0) {
        DDSurf->lpVtbl->SetClipper(DDSurf, 0);
        DAT_008A0DCC->lpVtbl->Release(DAT_008A0DCC);
        DAT_008A0DCC = 0;
    }

    operator delete(Desc);
    Desc = 0;

    if (DDSurf != 0) {
        DDSurf->lpVtbl->Release(DDSurf);
    }
    DDSurf = 0;
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. XSurface RTTI/vtable at 0x7E2104;
// method bodies and +0x0C field accesses confirmed at each entry below.
#include "xsurface_class.h"

// FUNCTION: GAMEMD 0x411560
void* XSurface::Lock(Point2D origin)
{
    ++unknown_0C;
    return 0;
}

// FUNCTION: GAMEMD 0x411570
bool XSurface::Unlock()
{
    --unknown_0C;
    return true;
}

// FUNCTION: GAMEMD 0x411580
bool XSurface::IsLocked()
{
    return unknown_0C != 0;
}

// FUNCTION: GAMEMD 0x411590
bool XSurface::unknown_84()
{
    return false;
}

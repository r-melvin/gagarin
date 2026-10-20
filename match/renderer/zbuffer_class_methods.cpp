// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7BCAE0.
//
// ZBuffer surface ownership.

#include "zbuffer_class_methods.h"

// FUNCTION: GAMEMD 0x7BCAE0  ZBuffer::ReleaseSurface (__thiscall)
// A plain `delete` — the null test retail performs is the one VC6 inlines for
// every scalar delete, not a guard written in the source, and the stale pointer
// is deliberately left behind.
void ZBuffer::ReleaseSurface()
{
    delete Buffer;
}

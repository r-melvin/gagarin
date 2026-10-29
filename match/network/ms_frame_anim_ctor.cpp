// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x767E90 (0x28 bytes); RTTI .?AVMSFrameAnim@@ (vtable 0x7F7104, base MSAnim);
//   layout in match/_layout/ms_anim.h.
#include "../_layout/ms_anim.h"

// FUNCTION: GAMEMD 0x767E90
// A frame animation starts disabled at the origin with the clock stamped.
MSFrameAnim::MSFrameAnim()
{
}

// SYNTHETIC: GAMEMD 0x769BD0 -- MSFrameAnim::`scalar deleting destructor' (seats its vtable, calls the base
// destructor 0x5CB6C0 out of line, frees).

// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x771850 (0x31 bytes); RTTI .?AVAnim@Voices@WorldDominationTour@@ (vtable
//   0x7F7354, base MSAnim); layout in match/_layout/ms_anim.h.
#include "../_layout/ms_anim.h"

// FUNCTION: GAMEMD 0x771850
// A voice animation starts disabled at the origin and remembers its owner.
WorldDominationTour::Voices::Anim::Anim(void* owner) : Owner(owner)
{
}

// SYNTHETIC: GAMEMD 0x771A30 -- Anim::`scalar deleting destructor' (seats its vtable, calls the base
// destructor 0x5CB6C0 out of line, frees).

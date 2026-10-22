// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SidebarClass and TabClass scalar deleting destructors (layout and
// evidence: sidebar_class_layout.h). Both destructors are implicit, so the
// scalar deleting destructors (??_G) are compiler-generated: retail's bodies
// (0x47 bytes each, byte-identical) tear down the four strips inline and call
// the inherited base destructor at 0x652C00.
//
// The two constructors below exist only so that cl emits the vtable and the
// deleting destructor in this translation unit; they are not claims about any
// retail function (the real constructors are outside this module).

#include "sidebar_class_layout.h"

SidebarClass::SidebarClass()
{
}

TabClass::TabClass()
{
}

// SYNTHETIC: GAMEMD 0x5BE9E0
// SYNTHETIC: GAMEMD 0x6AC7F0
// The SidebarClass and TabClass scalar deleting destructors, emitted from their implicit destructors.

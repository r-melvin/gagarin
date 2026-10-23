// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SidebarClass and TabClass scalar deleting destructors (layout and
// evidence: sidebar_class_layout.h). Both destructors are implicit, so the
// scalar deleting destructors (??_G) are compiler-generated: retail's bodies
// (0x47 bytes each, byte-identical) tear down the four strips inline and call
// the inherited base destructor at 0x652C00.
//
// The TabClass constructor below exists only so that cl emits the vtable and
// deleting destructor in this translation unit; it is not a claim about a
// retail function. SidebarClass's ordinary constructor is in Sidebar.cpp.

#include "sidebar_class_layout.h"

TabClass::TabClass()
{
}

// SYNTHETIC: GAMEMD 0x5BE9E0
// The TabClass scalar deleting destructor, emitted from its implicit destructor.

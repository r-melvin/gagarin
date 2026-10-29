// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 (Ghidra disasm at 0x6AC890).
//   Original translation unit is Sidebar.CPP (see Sidebar.cpp); this file holds
//   one compiler-generated function recovered after that file was written.
//   Address index: 0x6AC890.

#include <new.h>
#include "ui_display_chain.h"

// The vector deleting destructor is emitted when the array form of new is seen
// for a class with a destructor; this helper does that and is itself dropped.
static SidebarCameo* GgNewCameoArray(int n) { return new SidebarCameo[n]; }

// SYNTHETIC: GAMEMD 0x6AC890
// SidebarCameo::`vector deleting destructor'

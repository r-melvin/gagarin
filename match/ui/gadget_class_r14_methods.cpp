// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Evidence: disassembly of 0x4E1340; the vtable stores (0x7E9344 then 0x7E92BC) are the
//   LinkClass and GadgetClass constructors, as in the sibling constructor at 0x4E12F0.
//
// GadgetClass copy constructor. Address index: 0x4E1340.
#include "gadget_class_methods.h"

// FUNCTION: GAMEMD 0x4E1340
// Copy the geometry, state flags and option bits; the list links start empty.
GadgetClass::GadgetClass(const GadgetClass& other)
    : X(other.X), Y(other.Y), Width(other.Width), Height(other.Height),
      IsToRepaint(other.IsToRepaint), IsSticky(other.IsSticky),
      IsDisabled(other.IsDisabled), Flags(other.Flags)
{
}

// SYNTHETIC: GAMEMD 0x4E1AD0 -- LinkClass scalar deleting destructor, emitted by the compiler from the virtual destructor

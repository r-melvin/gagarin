// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Seven destructors for classes carrying more than one vtable: four that
// release a held COM interface before relaying to the base destructor, and
// three scalar-deleting destructors that relay and then free. Each body is
// written once as a macro and expanded per instantiation; the variation is the
// seated vtables and, for the first shape, where the interface pointer sits.
// Ordered ascending by retail address.

#include "multi_vtable_dtor_family_methods.h"

// FUNCTION: GAMEMD 0x004AF5E0
GG_COMREL_BODY(004AF5E0)

// FUNCTION: GAMEMD 0x004B5B00
GG_COMREL_BODY(004B5B00)

// FUNCTION: GAMEMD 0x004D03A0
GG_SDD43_BODY(004D03A0, VT_007E8AC0, VT_007E89F4)

// FUNCTION: GAMEMD 0x005172C0
GG_SDD43_BODY(005172C0, VT_007EADC8, VT_007EACFC)

// FUNCTION: GAMEMD 0x005B1B50
GG_SDD43_BODY(005B1B50, VT_007EDC38, VT_007EDB6C)

// FUNCTION: GAMEMD 0x0069ECF0
GG_COMREL_BODY(0069ECF0)

// FUNCTION: GAMEMD 0x0075AB00
GG_COMREL_BODY(0075AB00)

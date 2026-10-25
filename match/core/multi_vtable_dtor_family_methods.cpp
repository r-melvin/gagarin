// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Four destructors for classes carrying more than one vtable release a held
// COM interface before relaying to the base destructor. Each body is
// written once as a macro and expanded per instantiation; the variation is the
// seated vtables and, for the first shape, where the interface pointer sits.
// Ordered ascending by retail address.

#include "multi_vtable_dtor_family_methods.h"

// FUNCTION: GAMEMD 0x004AF5E0
GG_COMREL_BODY(004AF5E0)

// FUNCTION: GAMEMD 0x004B5B00
GG_COMREL_BODY(004B5B00)

// FUNCTION: GAMEMD 0x0069ECF0
GG_COMREL_BODY(0069ECF0)

// FUNCTION: GAMEMD 0x0075AB00
GG_COMREL_BODY(0075AB00)

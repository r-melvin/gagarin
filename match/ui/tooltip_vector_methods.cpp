// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Flag bisection: /GX outlines the derived deleting destructor; omitting
// it reproduces the complete retail 0x724F40 body as well as all other slots.
// Raw vtables 0x7F57E8 and 0x7F57C8, RTTI descriptors 0x844938/0x844968,
// and complete entry-origin instruction spans establish these virtual methods.
// Slot names 5/6 remain placeholders. Generic definitions are shared in
// vector_class_operations.h; these instantiations bind the ToolTip entries.
// LIBRARY: GAMEMD 0x7C8E17
// operator new(size_t), emitted as ??2@YAPAXI@Z for these pointer arrays.
#include "tooltip_manager_shared.h"

// FUNCTION: GAMEMD 0x724C30
// DynamicVectorClass<const ToolTip*>::Clear

// FUNCTION: GAMEMD 0x724C60
// DynamicVectorClass<const ToolTip*>::Slot5

// FUNCTION: GAMEMD 0x724C80
// VectorClass<const ToolTip*>::Slot6

// FUNCTION: GAMEMD 0x724C90
// VectorClass<const ToolTip*>::operator==

// FUNCTION: GAMEMD 0x724CD0
// VectorClass<const ToolTip*>::SetCapacity

// FUNCTION: GAMEMD 0x724D80
// VectorClass<const ToolTip*>::Clear

// FUNCTION: GAMEMD 0x724DB0
// VectorClass<const ToolTip*>::FindItemIndex

// FUNCTION: GAMEMD 0x724DF0
// VectorClass<const ToolTip*>::Slot5

// FUNCTION: GAMEMD 0x724E10
// DynamicVectorClass<const ToolTip*>::SetCapacity

// FUNCTION: GAMEMD 0x724EC0
// DynamicVectorClass<const ToolTip*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x724EF0
// VectorClass<const ToolTip*> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x724F40
// DynamicVectorClass<const ToolTip*> scalar deleting destructor

template class VectorClass<const ToolTip*>;
template class DynamicVectorClass<const ToolTip*>;

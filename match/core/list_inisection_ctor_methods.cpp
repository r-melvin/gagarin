// Provenance: own-binary-via-Ghidra
// SPDX-License-Identifier: GPL-3.0-or-later
// List<INIClass::INISection*> constructor. Retail 0x49E8E0 seats both
// sentinel nodes (0x7E1B0C), the GenericList table (0x7E1B04), links the head
// to the tail, then seats the derived table 0x7E1AFC (RTTI names it
// List<INIClass::INISection*>). Ten callers construct INIClass objects.
#include "../_layout/ini_class.h"

// VTABLE: GAMEMD 0x7E1AFC -- List<INIClass::INISection*>.
extern "C" void* GG_VTABLE_LISTOFINISECTION;

// Bodies owned elsewhere (0x40E320, 0x52ACE0); repeated inline here so /Ob2
// expands them into the derived constructor as retail does.
inline GenericNode::GenericNode()
{
    NextNode = 0;
    PrevNode = 0;
    Vtable = &GG_VTABLE_GENERIC_NODE_SLOTS;
}

inline GenericList::GenericList()
{
    Vtable = &GG_VTABLE_GENERIC_LIST_SLOTS;
    FirstNode.Link(&LastNode);
}

// FUNCTION: GAMEMD 0x49E8E0
template<> List<INIClass::INISection*>::List()
{
    Vtable = &GG_VTABLE_LISTOFINISECTION;
}

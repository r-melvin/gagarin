// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x664D20 / 0x667A30.
#include "rules_class_members.h"

// FUNCTION: GAMEMD 0x664D20
// RulesClass no-init constructor: only the container members are constructed.
// PARTIAL: 95.1% (577/607 instructions). The member list is read straight off
// the function; the remaining delta is one TypeList<int> default constructor
// (LEA/PUSH/PUSH/MOV/CALL) that retail expands inline at 0x12AC and we call out
// of line. VC6's inline budget depends on how many empty inline constructor
// call nodes the full class carries; the class has more such members than are
// identified, and a placeholder member added only to force the count would be
// steering, so it is not modelled.
RulesClassMembers_00664D20::RulesClassMembers_00664D20(const AbstractNoInit& noInit)
{
}


// FUNCTION: GAMEMD 0x667A30
// RulesClass destructor: the container members are destroyed in reverse order.
// PARTIAL: 25.0% positional, instruction multiset within 9 of 748 (retail-only
// push 1, mov 4, cmp 2, je 2, add 1; compiled-only lea 1). Same cause as the
// constructor: retail expands the TypeList<const BuildingTypeClass*> destructor
// at 0xA88 inline where we emit the out-of-line call to 0x50EA00.
RulesClassMembers_00664D20::~RulesClassMembers_00664D20()
{
}

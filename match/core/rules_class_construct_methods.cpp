// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x664D20 / 0x667A30.
//   Member list read from the disassembly: each TypeList is "LEA reg,[ESI+off]; call <capacity
//   ctor>; MOV [reg],<TypeList vtable>". Capacity ctors 0x67AC70 (VoxelAnim), 0x525250 (Anim),
//   0x477DB0 (int), 0x67AFF0 (Smudge), 0x5AC900 (Building), 0x513190 (Unit), 0x513560
//   (Aircraft), 0x512DC0 (Infantry), 0x67B370 (Terrain) pair with the TypeList vtables
//   0x7F0D3C / 0x7EB6D4 / 0x7E4DD8 / 0x7F0D1C / 0x7ED90C / 0x7EABE8 / 0x7EABC8 / 0x7EAC08 /
//   0x7F0CFC. The 0x665650 constructor performs the same member construction between its
//   scalar stores.
#include "../_layout/rules_class.h"

// FUNCTION: GAMEMD 0x664D20
// PARTIAL: 95.1%. One TypeList<int> default ctor (+0x12AC) is called where retail expands it inline. VC6
// reaches retail's inline choices only if RulesClass holds one more member with a user-declared empty
// ctor and dtor after +0xAF8; no retail evidence identifies that member yet, so none is invented.
// RulesClass no-init constructor: only the container members are constructed.
RulesClass::RulesClass(const AbstractNoInit& noInit)
{
}

// FUNCTION: GAMEMD 0x667A30
// PARTIAL: 25.0% positional (instruction multiset within ~9 of 748). Same cause as 0x664D20: retail
// expands the TypeList<Building> dtor at +0xA88 inline; the unidentified empty member is missing.
// RulesClass destructor: the container members are destroyed in reverse order.
RulesClass::~RulesClass()
{
}

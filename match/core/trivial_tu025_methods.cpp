// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Native primary vtable 0x7E3608 and entry-origin disassembly.
#include "../_layout/anim_type_class.h"

// FUNCTION: GAMEMD 0x428C10
void AnimTypeClass::vf_10(void* target, bool removed)
{
    if (Next == target) {
        Next = 0;
    }
}

// FUNCTION: GAMEMD 0x428E50
int AnimTypeClass::vf_11()
{
    return 5;
}

// FUNCTION: GAMEMD 0x428E60
int AnimTypeClass::vf_16()
{
    return ArrayIndex;
}

// FUNCTION: GAMEMD 0x428E70
int AnimTypeClass::vf_12()
{
    return 0x378;
}

// FUNCTION: GAMEMD 0x428E80
bool AnimTypeClass::vf_32(const CellStruct* cell, HouseClass* house)
{
    return false;
}

// FUNCTION: GAMEMD 0x428E90
ObjectClass* AnimTypeClass::vf_35(HouseClass* house)
{
    return 0;
}

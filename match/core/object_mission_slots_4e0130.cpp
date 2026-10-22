// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Two base-class slot bodies emitted together at 0x4E0130: ObjectClass slot
// 34 (every concrete class overrides it) and MissionClass slot 128. Slot
// numbers come from the RTTI-located tables 0x7EF060 / 0x7EDCC0.
#include "../_layout/mission_class.h"

// FUNCTION: GAMEMD 0x4E0130
ObjectTypeClass* ObjectClass::vf_34()
{
    return 0;
}

// FUNCTION: GAMEMD 0x4E0140
bool MissionClass::vf_128()
{
    return true;
}

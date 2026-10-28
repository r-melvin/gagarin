// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at 0x451EA0; Anims at +0x55C and the
//   AnimClass flag byte at +0x19D come from the canonical layouts.
//
//   0x451EA0  BuildingClass::SetAnimInvisible
//   0x454CF0  BuildingClass::FUN_00454CF0
//   0x454D30  BuildingClass::FUN_00454D30
//   0x4598D0  BuildingClass::FUN_004598D0

#include "building_class.h"

// FUNCTION: GAMEMD 0x451EA0
// Hide one (or, for slot == -2, every) building animation.
void BuildingClass::SetAnimInvisible(int slot)
{
    if (slot == -2)
    {
        AnimClass** p = &this->Anims[0];
        for (int i = 0x15; i != 0; --i)
        {
            AnimClass* anim = *p;
            if (anim)
            {
                anim->Invisible = 1;
            }
            ++p;
        }
    }
    else
    {
        AnimClass* anim = this->Anims[slot];
        if (anim)
        {
            anim->Invisible = 1;
        }
    }
}

// FUNCTION: GAMEMD 0x454CF0
// For a type that carries the cloaking data bool: mark the data present, drop
// the radius when it equals the type's, and request a redraw.
void BuildingClass::FUN_00454CF0()
{
    if (Type->bools_16A4[0x23])
    {
        unsigned char radius = CloakRadius;
        HasCloakingData = 1;
        if (radius == Type->CloakRadiusInCells)
        {
            CloakRadius = 0;
        }
        NeedsRedraw = 1;
    }
}

// FUNCTION: GAMEMD 0x454D30
// The opposite step: flag the data as reversed, restore the radius from the
// type when it is zero, and request a redraw.
void BuildingClass::FUN_00454D30()
{
    if (Type->bools_16A4[0x23])
    {
        unsigned char radius = CloakRadius;
        HasCloakingData = -1;
        if (radius == 0)
        {
            CloakRadius = Type->CloakRadiusInCells;
        }
        NeedsRedraw = 1;
    }
}

// FUNCTION: GAMEMD 0x4598D0
// A type that undeploys and gathers resources never qualifies; otherwise the
// answer is the negation of slot 32.
bool BuildingClass::FUN_004598D0()
{
    BuildingTypeClass* type = Type;
    if (type->UndeploysInto != 0 && type->ResourceGatherer)
    {
        return false;
    }
    bool result = !vf_32();
    return result;
}

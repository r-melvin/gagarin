// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x451E40  BuildingClass::DestroyNthAnim    (__thiscall)
//   FUNCTION: GAMEMD 0x4521C0  BuildingClass::DisableTemporal   (__thiscall)
//   FUNCTION: GAMEMD 0x452210  BuildingClass::EnableTemporal    (__thiscall)
//   FUNCTION: GAMEMD 0x4525F0  BuildingClass::IsTraversable     (__thiscall)
//   FUNCTION: GAMEMD 0x457630  BuildingClass::FirstActiveSWIdx  (__thiscall)
//   FUNCTION: GAMEMD 0x457690  BuildingClass::SecondActiveSWIdx (__thiscall)
//   FUNCTION: GAMEMD 0x4A51B0  TransitionTimer::FUN_004A51B0 (referenced; reloc)
//   FUNCTION: GAMEMD 0x49FAE0  HouseSWSlots::IsActive           (referenced; reloc)
//   GLOBAL:   GAMEMD 0x00A83CBC g_SWArray (SWTypeClass** array Items)

#include "building_class.h"

// FUNCTION: GAMEMD 0x451E40  (__thiscall)
// Destroy one (or, for slot == -2, every) building animation. The kill is a
// virtual scalar-deleting-destructor call through AnimClass vtable slot
// 0x20 (`mov [vtbl]; push 1; call [vtbl+0x20]`).
void BuildingClass::DestroyNthAnim(int slot)
{
    if (slot == -2)
    {
        AnimClass** p = &this->Anims[0];
        for (int i = 0x15; i != 0; --i)
        {
            AnimClass* anim = *p;
            if (anim)
            {
                *p = 0;
                delete anim;
            }
            ++p;
        }
    }
    else
    {
        AnimClass* anim = this->Anims[slot];
        if (anim)
        {
            this->Anims[slot] = 0;
            delete anim;
        }
    }
}

// FUNCTION: GAMEMD 0x4521C0  (__thiscall)
// Suspend the active building anims while a temporal weapon targets us: stash
// each anim's current frame in PausedAnimFrame and freeze it.
void BuildingClass::DisableTemporal()
{
    this->HasPower = 0;
    AnimClass** p = &this->Anims[0];
    for (int i = 0x15; i != 0; --i)
    {
        AnimClass* anim = *p;
        if (anim)
        {
            int saved = anim->Value;
            anim->Paused = 1;
            anim->Unpaused = 0;
            anim->PausedAnimFrame = saved;
            anim->UnderTemporal = 1;
        }
        ++p;
    }
}

// FUNCTION: GAMEMD 0x452210  (__thiscall)
// Resume the building anims when the temporal weapon releases us.
void BuildingClass::EnableTemporal()
{
    this->HasPower = 1;
    AnimClass** p = &this->Anims[0];
    for (int i = 0x15; i != 0; --i)
    {
        AnimClass* anim = *p;
        if (anim)
        {
            anim->Paused = 0;
            anim->Unpaused = 1;
            anim->UnderTemporal = 0;
        }
        ++p;
    }
}

// FUNCTION: GAMEMD 0x4525F0  (__thiscall)
// True if a unit may drive across this building's footprint. Always traversable
// unless the type forbids it; then only certain (WhatAmI==0x18) buildings with
// a passable cell qualify. WhatAmI is the virtual at vtable slot 0x184.
bool BuildingClass::IsTraversable()
{
    if (!this->Type->bools_16A4[0x16B7 - 0x16A4])
        return true;

    int kind = this->vf_97();
    if (kind == 0x18 && this->UnloadTimer.FUN_004A51B0())
        return true;

    return false;
}

// FUNCTION: GAMEMD 0x457630  (__thiscall)
// Index of the first super-weapon this building hosts that is currently active
// for the owning house; returns the raw type index (-1 sentinel) otherwise.
int BuildingClass::FirstActiveSWIdx()
{
    int idx = this->Type->SuperWeapon;
    if (idx != -1)
    {
        SWChainNode* node = g_SWArray[idx];
        SWChainC8* sw = node->field_28->field_C8;
        if (sw && !this->Owner->ActiveBuildingTypes.FUN_0049FAE0(sw->field_DF8))
            return -1;
    }
    return this->Type->SuperWeapon;
}

// FUNCTION: GAMEMD 0x457690  (__thiscall)
// As FirstActiveSWIdx, for the building's second hosted super-weapon.
int BuildingClass::SecondActiveSWIdx()
{
    int idx = this->Type->SuperWeapon2;
    if (idx != -1)
    {
        SWChainNode* node = g_SWArray[idx];
        SWChainC8* sw = node->field_28->field_C8;
        if (sw && !this->Owner->ActiveBuildingTypes.FUN_0049FAE0(sw->field_DF8))
            return -1;
    }
    return this->Type->SuperWeapon2;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA83CBC
SWChainNode** g_SWArray;
// END defined globals

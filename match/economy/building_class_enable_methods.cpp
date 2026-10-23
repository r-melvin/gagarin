// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x452410.

#include "building_class_enable_methods.h"

// FUNCTION: GAMEMD 0x452410  BuildingClass::EnableStuff (__thiscall)
// Bring a building's attachments back online: its light source, its end post if
// the type wants one, and every animation the type marks as enabled that the
// instance actually has. VC6 strength-reduces the loop into two induction
// variables — a byte offset stepping 0x44 through the type's records and a
// pointer stepping 4 through the instance's — which is why the bound in the
// disassembly reads 0x594 rather than 21.
void BuildingClass::EnableStuff()
{
    StuffEnabled = true;

    if (LightSource != 0)
        LightSource->Activate(0);

    if (Type->bools_16A4[0x16BE - 0x16A4])
        CreateEndPost(false);

    for (int i = 0; i < 0x15; i++)
    {
        if (Type->BuildingAnim[i].Powered && Anims[i] != 0)
            AnimClass_Enable(Anims[i]);
    }
}

// FUNCTION: GAMEMD 0x451EE0  BuildingClass::ToggleDamagedAnims (__thiscall, ret 0x4)
// Swap the building between its healthy and damaged animation sets. Nothing
// happens if it is already in the requested state.
//
// The `name != 0` guard is a source-level test the compiler kept even though
// the value is a LEA result that can never be null — same shape as the dead
// null checks in MarkPassengersAsExited and MessageListClass::RemoveEdit.
void BuildingClass::ToggleDamagedAnims(bool damaged)
{
    if (IsDamaged == damaged)
        return;

    IsDamaged = damaged;

    for (int i = 0; i < 0x15; i++)
    {
        if (Anims[i] != 0)
        {
            const char* name = damaged ? Type->BuildingAnim[i].Damaged
                                       : Type->BuildingAnim[i].Anim;

            if (name != 0 && *name != 0)
                PlayAnim(name, i, damaged, 0, 0);
        }
    }
}

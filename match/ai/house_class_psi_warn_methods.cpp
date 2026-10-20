// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x43B5E0.

#include "house_class_psi_warn_methods.h"

// FUNCTION: GAMEMD 0x43B5E0
//
// Spawn the psychic-warning animation for an incoming attack: resolve the anim
// type by name, place a new AnimClass at the target's coordinates (loop delay
// 0, one loop, flags 0x600), attach the bullet and this house to it, and mark
// it at +0x19D before returning it.  No null check on the new anim — retail
// calls straight through the pointer.
//
// __fastcall member: this in ECX, the target in EDX, bullet + name on the
// stack (RET 8).
AnimClass* __fastcall HouseClass::PsiWarn(CellClass* target, BulletClass* bullet,
                                          const char* animName)
{
    AnimTypeClass* type =
        ((AnimTypeClass**)AnimTypeArray.Items)[AnimType_FindIndex(animName)];
    CoordStruct coords = target->GetCoords();

    AnimClass* anim = new AnimClass(type, coords, 0, 1, 0x600, 0, false);
    anim->FUN_00424C90(bullet);
    anim->FUN_00424CA0(this);
    anim->At_19D = 1;
    return anim;
}

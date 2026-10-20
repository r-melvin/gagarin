// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x458200.

#include "building_class_garrison_owner_methods.h"

// FUNCTION: GAMEMD 0x458200
//
// Keep a garrisonable civilian structure's ownership in step with whether
// anybody is inside it. Only types whose gate member is still -1 take part.
// A building already down at red health is poked first; then the Civilian
// house is found by walking HouseClass::Array for the house whose type sits
// on the "Civilian" side. Emptying the building hands it back to that house,
// with an abandoned sound, a radar event and the EVA line for the local
// player; garrisoning a building that currently belongs to the Civilian house
// hands it to the first occupant's owner. Both transitions refresh the
// occupant animations first.
//
// PARTIAL (98.0%, 96/98 instructions; the multiset is identical, so the
// residual is scheduling only). The lever that mattered was declaration
// order: the Civilian house pointer has to be zeroed BEFORE the side lookup
// runs, because retail issues `XOR EBX,EBX` ahead of `CALL 0x6A46D0`.
// Declaring it after the lookup puts the zero behind the call: 95.9% versus
// 98.0%. The two remaining instructions are the `MOV EDX,0x2000` of the
// __fastcall sound call, which retail issues between the two argument pushes
// and cl issues after both. Seven spellings of that call were measured in one
// compile — the sound index bound to a local, the volume bound to a const
// float local, the panning bound to a const int local, the volume written as
// `(float)1.0`, the controller bound to a local, the controller left to a
// default argument, and the rules pointer cached first — and all seven score
// 98.0%.
void BuildingClass_00458200::UpdateGarrisonOwner()
{
    if (Type->unknown_634 != -1) {
        return;
    }

    if (reinterpret_cast<ObjectClass*>(this)->IsRedHP()) {
        FUN_00457DE0(0, 0);
    }

    House_00458200* civilian = 0;
    int count = HouseArray_00458200.Count;
    int side = FindSideIndex_00458200(CivilianSideName_00458200);
    for (int i = 0; i < count; ++i) {
        if (HouseArray_00458200.Items[i]->Type->SideIndex == side) {
            civilian = HouseArray_00458200.Items[i];
            break;
        }
    }

    if ((this->*Vtbl->GetOccupantCount)() == 0 && Owner != civilian) {
        if (Owner->IsControlledByCurrentPlayer()) {
            VocClass_00458200::PlayGlobal(RulesInstance_00458200->unknown_1C0,
                                          0x2000, 1.0f, 0);
            CellStruct_00458200 here;
            if (RadarEventClass_00458200::Create(
                    0xF, *(this->*Vtbl->GetMapCoords)(&here))) {
                VoxClass_00458200::Play(EvaStructureAbandoned_00458200, -1, -1);
            }
        }
        UpdateOccupantAnims();
        (this->*Vtbl->SetOwningHouse)(civilian, 0);
    }

    if ((this->*Vtbl->GetOccupantCount)() > 0 && Owner == civilian) {
        UpdateOccupantAnims();
        (this->*Vtbl->SetOwningHouse)(OccupantItems[0]->Owner, 0);
    }
}

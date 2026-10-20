// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6EA500.

#include "team_class_add_member_methods.h"
#include "../_layout/object_class.h"

// FUNCTION: GAMEMD 0x6EA500
//
// Recruit a unit into the team. The fit test hands back the task-force slot
// the unit fills; the unit is freed from any team it already belongs to, the
// slot count is bumped (unless the caller asked not to), the unit is pushed on
// the member chain (marking whether it is the last one), takes the team's
// group, and gets the team's trigger unless its type opts out. The object and
// threat totals are updated, the lazily-built pair at +0x34 is filled if still
// empty, the two recalc bytes are raised and the unit inherits the type's byte
// at +0xF5.
bool Team_006EA500::AddMember(Foot_006EA500* member, bool flag)
{
    if (member == 0) {
        return false;
    }

    int slot;
    if (!this->FUN_006EA610(member, &slot, flag)) {
        return false;
    }

    if (member->Team != 0) {
        member->Team->LiberateMember(member, -1, false);
    }

    if (!flag) {
        this->CountObjects[slot]++;
    }

    member->At_689 = this->FirstUnit == 0;
    member->NextTeamMember = this->FirstUnit;
    this->FirstUnit = member;
    member->Team = this;
    member->Group = this->Type->GetGroup();

    if (this->Trigger != 0) {
        if (this->Type->At_B3 == 0
            || (member->*member->Vtbl->GetTechnoType)()->At_5E0 > 0) {
            // Retail passes member in ECX unchanged to ObjectClass::AttachTrigger.
            reinterpret_cast<ObjectClass*>(member)->AttachTrigger(
                static_cast<TagClass*>(this->Trigger));
        }
    }

    this->TotalObjects = this->TotalObjects + 1;
    this->TotalThreatValue += (member->*member->Vtbl->At_2C0)();
    if (this->At_34 == 0) {
        this->FUN_006EAEE0(&this->At_34, &this->At_38);
    }

    this->At_7E = 1;
    this->At_7D = 1;
    member->At_422 = this->Type->At_F5;
    return true;
}

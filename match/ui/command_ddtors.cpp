// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// CommandClass and its keyboard-command subclasses.
//
// Scalar deleting destructors of classes whose destructor is empty. Each one
// stores the vtable of the class that declares the destructor (the derived
// classes add nothing to it), frees the object when bit 0 of the flag is set,
// and returns `this`. Retail's 32-byte shape:
//
//     MOV AL,[ESP+4]; PUSH ESI; MOV ESI,ECX; TEST AL,1; MOV [ESI],<vtable>
//     JZ +9; PUSH ESI; CALL 0x7C8B3D; ADD ESP,4; MOV EAX,ESI; POP ESI; RET 4
//
// Class names and the base relation come from the retail RTTI descriptors;
// the owning class of each body is the class whose vtable slot 0 holds it.
// Slot 0 is modelled as an ordinary virtual holding the deleting wrapper, as
// FileClass does in match/core/ram_file_class.h: these classes are never
// constructed in this translation unit, so cl would not emit their tables or
// a compiler-generated `??_G`. The classes are opaque views; no member is
// touched, so there is no layout to assert.

// VTABLE: GAMEMD 0x7EBE3C
class CommandClass
{
public:
    ~CommandClass() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB84C
class CreateTeamCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBE64
class SelectTeamCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBE8C
class AddTeamCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBEB4
class CenterTeamCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBEDC
class TauntCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBE14
class MultiplayerDebugCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBDEC
class MultiplayerSyncCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBDC4
class FollowCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBD9C
class View1CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBD74
class View2CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBD4C
class View3CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBD24
class View4CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBCFC
class SetView1CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBCD4
class SetView2CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBCAC
class SetView3CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBC84
class SetView4CommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBC5C
class OptionsCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBC34
class SidebarUpCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBC0C
class SidebarDownCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBBE4
class CenterREventCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBBBC
class BeaconPlacementCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBB94
class ToggleSellCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBB6C
class ToggleRepairCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBB44
class AllianceCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBB1C
class CenterBaseCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBAF4
class CenterViewCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBACC
class ScatterCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBAA4
class GuardCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBA7C
class StopCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBA54
class AllToCheerCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBA2C
class DeployCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBA04
class PrevObjectCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB9DC
class NextObjectCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB9B4
class PlanningModeCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB98C
class CombatantSelectCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB964
class TypeSelectCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB93C
class HealthNavCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB914
class VeterancyNavCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB8EC
class SetStructureTabCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB8C4
class SetDefenseTabCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB89C
class SetUnitTabCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EB874
class SetInfantryTabCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBF04
class ScreenCaptureCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBF2C
class PageUserCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBF54
class CursorPositionCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EBF7C
class DeleteCommandClass : public CommandClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// FUNCTION: GAMEMD 0x535CD0 -- CreateTeamCommandClass scalar deleting destructor
void* CreateTeamCommandClass::DeletingDtor(unsigned int flags)
{
    this->~CreateTeamCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x535D00 -- CommandClass scalar deleting destructor
void* CommandClass::DeletingDtor(unsigned int flags)
{
    this->~CommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x536090 -- SelectTeamCommandClass scalar deleting destructor
void* SelectTeamCommandClass::DeletingDtor(unsigned int flags)
{
    this->~SelectTeamCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x536180 -- AddTeamCommandClass scalar deleting destructor
void* AddTeamCommandClass::DeletingDtor(unsigned int flags)
{
    this->~AddTeamCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x536270 -- CenterTeamCommandClass scalar deleting destructor
void* CenterTeamCommandClass::DeletingDtor(unsigned int flags)
{
    this->~CenterTeamCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x536580 -- TauntCommandClass scalar deleting destructor
void* TauntCommandClass::DeletingDtor(unsigned int flags)
{
    this->~TauntCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x537FA0 -- MultiplayerDebugCommandClass scalar deleting destructor
void* MultiplayerDebugCommandClass::DeletingDtor(unsigned int flags)
{
    this->~MultiplayerDebugCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x537FC0 -- MultiplayerSyncCommandClass scalar deleting destructor
void* MultiplayerSyncCommandClass::DeletingDtor(unsigned int flags)
{
    this->~MultiplayerSyncCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x537FE0 -- FollowCommandClass scalar deleting destructor
void* FollowCommandClass::DeletingDtor(unsigned int flags)
{
    this->~FollowCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538000 -- View1CommandClass scalar deleting destructor
void* View1CommandClass::DeletingDtor(unsigned int flags)
{
    this->~View1CommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538020 -- View2CommandClass scalar deleting destructor
void* View2CommandClass::DeletingDtor(unsigned int flags)
{
    this->~View2CommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538040 -- View3CommandClass scalar deleting destructor
void* View3CommandClass::DeletingDtor(unsigned int flags)
{
    this->~View3CommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538060 -- View4CommandClass scalar deleting destructor
void* View4CommandClass::DeletingDtor(unsigned int flags)
{
    this->~View4CommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538080 -- SetView1CommandClass scalar deleting destructor
void* SetView1CommandClass::DeletingDtor(unsigned int flags)
{
    this->~SetView1CommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5380A0 -- SetView2CommandClass scalar deleting destructor
void* SetView2CommandClass::DeletingDtor(unsigned int flags)
{
    this->~SetView2CommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5380C0 -- SetView3CommandClass scalar deleting destructor
void* SetView3CommandClass::DeletingDtor(unsigned int flags)
{
    this->~SetView3CommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5380E0 -- SetView4CommandClass scalar deleting destructor
void* SetView4CommandClass::DeletingDtor(unsigned int flags)
{
    this->~SetView4CommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538100 -- OptionsCommandClass scalar deleting destructor
void* OptionsCommandClass::DeletingDtor(unsigned int flags)
{
    this->~OptionsCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538120 -- SidebarUpCommandClass scalar deleting destructor
void* SidebarUpCommandClass::DeletingDtor(unsigned int flags)
{
    this->~SidebarUpCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538140 -- SidebarDownCommandClass scalar deleting destructor
void* SidebarDownCommandClass::DeletingDtor(unsigned int flags)
{
    this->~SidebarDownCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538160 -- CenterREventCommandClass scalar deleting destructor
void* CenterREventCommandClass::DeletingDtor(unsigned int flags)
{
    this->~CenterREventCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538180 -- BeaconPlacementCommandClass scalar deleting destructor
void* BeaconPlacementCommandClass::DeletingDtor(unsigned int flags)
{
    this->~BeaconPlacementCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5381A0 -- ToggleSellCommandClass scalar deleting destructor
void* ToggleSellCommandClass::DeletingDtor(unsigned int flags)
{
    this->~ToggleSellCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5381C0 -- ToggleRepairCommandClass scalar deleting destructor
void* ToggleRepairCommandClass::DeletingDtor(unsigned int flags)
{
    this->~ToggleRepairCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5381E0 -- AllianceCommandClass scalar deleting destructor
void* AllianceCommandClass::DeletingDtor(unsigned int flags)
{
    this->~AllianceCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538200 -- CenterBaseCommandClass scalar deleting destructor
void* CenterBaseCommandClass::DeletingDtor(unsigned int flags)
{
    this->~CenterBaseCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538220 -- CenterViewCommandClass scalar deleting destructor
void* CenterViewCommandClass::DeletingDtor(unsigned int flags)
{
    this->~CenterViewCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538240 -- ScatterCommandClass scalar deleting destructor
void* ScatterCommandClass::DeletingDtor(unsigned int flags)
{
    this->~ScatterCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538260 -- GuardCommandClass scalar deleting destructor
void* GuardCommandClass::DeletingDtor(unsigned int flags)
{
    this->~GuardCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538280 -- StopCommandClass scalar deleting destructor
void* StopCommandClass::DeletingDtor(unsigned int flags)
{
    this->~StopCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5382A0 -- AllToCheerCommandClass scalar deleting destructor
void* AllToCheerCommandClass::DeletingDtor(unsigned int flags)
{
    this->~AllToCheerCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5382C0 -- DeployCommandClass scalar deleting destructor
void* DeployCommandClass::DeletingDtor(unsigned int flags)
{
    this->~DeployCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5382E0 -- PrevObjectCommandClass scalar deleting destructor
void* PrevObjectCommandClass::DeletingDtor(unsigned int flags)
{
    this->~PrevObjectCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538300 -- NextObjectCommandClass scalar deleting destructor
void* NextObjectCommandClass::DeletingDtor(unsigned int flags)
{
    this->~NextObjectCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538320 -- PlanningModeCommandClass scalar deleting destructor
void* PlanningModeCommandClass::DeletingDtor(unsigned int flags)
{
    this->~PlanningModeCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538340 -- CombatantSelectCommandClass scalar deleting destructor
void* CombatantSelectCommandClass::DeletingDtor(unsigned int flags)
{
    this->~CombatantSelectCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538360 -- TypeSelectCommandClass scalar deleting destructor
void* TypeSelectCommandClass::DeletingDtor(unsigned int flags)
{
    this->~TypeSelectCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538380 -- HealthNavCommandClass scalar deleting destructor
void* HealthNavCommandClass::DeletingDtor(unsigned int flags)
{
    this->~HealthNavCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5383A0 -- VeterancyNavCommandClass scalar deleting destructor
void* VeterancyNavCommandClass::DeletingDtor(unsigned int flags)
{
    this->~VeterancyNavCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5383C0 -- SetStructureTabCommandClass scalar deleting destructor
void* SetStructureTabCommandClass::DeletingDtor(unsigned int flags)
{
    this->~SetStructureTabCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5383E0 -- SetDefenseTabCommandClass scalar deleting destructor
void* SetDefenseTabCommandClass::DeletingDtor(unsigned int flags)
{
    this->~SetDefenseTabCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538400 -- SetUnitTabCommandClass scalar deleting destructor
void* SetUnitTabCommandClass::DeletingDtor(unsigned int flags)
{
    this->~SetUnitTabCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538420 -- SetInfantryTabCommandClass scalar deleting destructor
void* SetInfantryTabCommandClass::DeletingDtor(unsigned int flags)
{
    this->~SetInfantryTabCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538440 -- ScreenCaptureCommandClass scalar deleting destructor
void* ScreenCaptureCommandClass::DeletingDtor(unsigned int flags)
{
    this->~ScreenCaptureCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538460 -- PageUserCommandClass scalar deleting destructor
void* PageUserCommandClass::DeletingDtor(unsigned int flags)
{
    this->~PageUserCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x538480 -- CursorPositionCommandClass scalar deleting destructor
void* CursorPositionCommandClass::DeletingDtor(unsigned int flags)
{
    this->~CursorPositionCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5384A0 -- DeleteCommandClass scalar deleting destructor
void* DeleteCommandClass::DeletingDtor(unsigned int flags)
{
    this->~DeleteCommandClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

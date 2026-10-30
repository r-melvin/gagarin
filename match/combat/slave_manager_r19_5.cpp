// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 (Ghidra disasm at each
//   address below). Implemented on the canonical SlaveManagerClass.
//
// reccmp annotations (ascending by retail address):
//   FUNCTION: GAMEMD 0x6AF360  SlaveManagerClass::SlaveManagerClass()
//   FUNCTION: GAMEMD 0x6AF440  SlaveManagerClass::SlaveManagerClass(NoInit)
//   FUNCTION: GAMEMD 0x6AF5F0  SlaveManagerClass::vf_23
//   FUNCTION: GAMEMD 0x6AF650  SlaveManagerClass::CreateSlave
//   FUNCTION: GAMEMD 0x6B0490  SlaveManagerClass::GuardAllSlaves
//   FUNCTION: GAMEMD 0x6B0A20  SlaveManagerClass::LostSlave
//   FUNCTION: GAMEMD 0x6B0CC0  SlaveManagerClass::SetStateIdle1
//   FUNCTION: GAMEMD 0x6B0D10  SlaveManagerClass::SetStateIdle4

#include "../FUNCTION.H"
#include "slave_manager_class_methods.h"

// GLOBAL: GAMEMD 0xB0B5F0 -- the slave manager array.
extern DynamicVectorClass<SlaveManagerClass*> DAT_00B0B5F0;

// FUNCTION: GAMEMD 0x6AF360
// Default constructor: an unowned manager with no slaves, registered in the
// global array.
SlaveManagerClass::SlaveManagerClass()
    : SlaveNodes(0, 0), RespawnTimer(0)
{
    Owner = 0;
    SlaveType = 0;
    SlaveCount = 0;
    RegenRate = 0;
    ReloadRate = 0;
    RespawnTimer = CDTimerClass(0);
    State = 0;
    LastScanFrame = 0;
    DAT_00B0B5F0.AddItem(this);
}

// FUNCTION: GAMEMD 0x6AF440
// NoInit constructor (save-game load path): base NoInit constructor, an empty
// growable node vector (step 10), the respawn timer started at the current
// frame with no time left, and the four COM vtable pointers.
SlaveManagerClass::SlaveManagerClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit), SlaveNodes(0, 0), RespawnTimer(0)
{
}

// FUNCTION: GAMEMD 0x6AF5F0
// When the respawn timer has run out, restart it for 10 frames and, if the
// manager still has an owner, run its two update passes.
void SlaveManagerClass::vf_23()
{
    if (this->RespawnTimer.GetTimeLeft() == 0) {
        this->RespawnTimer = CDTimerClass(10);
        if (this->Owner) {
            this->FUN_006AF6C0();
            this->FUN_006AFD60();
        }
    }
}


// FUNCTION: GAMEMD 0x6AF650
// Create one slave from the manager's owner house, then initialize the new
// InfantryClass and start its node timer.
void SlaveManagerClass::CreateSlave(SlaveControl* Control)
{
    Control->Slave = static_cast<InfantryClass*>(this->SlaveType->vf_35(this->Owner->vf_15()));
    if (Control->Slave) {
        Control->Slave->vf_53();
        Control->Slave->SlaveOwner = this->Owner;
        Control->State = 0;
        CDTimerClass timer(0);
        Control->RespawnTimer = timer;
    }
}

// FUNCTION: GAMEMD 0x6B0490
// Order every live slave (State != Dead(6), Slave != null) back to Guard via
// vtable+0x3D0, walking the SlaveNodes vector back-to-front.
void SlaveManagerClass::GuardAllSlaves()
{
    for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
        ::SlaveControl* node = ((::SlaveControl**)this->SlaveNodes.Items)[i];
        int state = node->State;
        SlaveObject* slave = node->Slave;
        if (state != 6 && slave != 0)
            slave->GuardSlot();
    }
}

// FUNCTION: GAMEMD 0x6B0A20
// Search from the back of the SlaveNodes array. Clear the slave's manager
// back-link, empty the node, mark it Dead, and restart its respawn timer.
void SlaveManagerClass::LostSlave(SlaveObject* slave)
{
    for (int i = SlaveNodes.Count - 1; i >= 0; --i) {
        if (((::SlaveControl**)SlaveNodes.Items)[i]->Slave == slave) {
            ::SlaveControl* node = ((::SlaveControl**)SlaveNodes.Items)[i];
            if (node->Slave)
                node->Slave->SlaveOwner = 0;
            node->Slave = 0;
            node->State = 6;
            node->RespawnTimer = SlaveTimerClass(RegenRate);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x6B0CC0
// If the manager is Ready (State 0), switch it to state 1 and send every live
// slave (State != Dead(6), Slave != null) to CancelAndGoIdle, back to front.
//
// PARTIAL: 84.6% -- same prologue scheduling as AllGuard 0x6B0C80: the
// optimiser hoists the SlaveNodes.Count load above the two stores; retail
// stores first. Instruction multiset is identical.
void SlaveManagerClass::SetStateIdle1()
{
    if (this->State != 0)
        return;
    this->State = 1;
    this->LastScanFrame = 0x7FFFFFFF;
    for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
        SlaveControl* node = this->SlaveNodes.Items[i];
        int state = node->State;
        InfantryClass* slave = node->Slave;
        if (state != 6 && slave != 0)
            slave->CancelAndGoIdle();
    }
}

// FUNCTION: GAMEMD 0x6B0D10
// Same as SetStateIdle1 but switches the manager to state 4.
//
// PARTIAL: 84.6% -- same scheduling residual as SetStateIdle1.
void SlaveManagerClass::SetStateIdle4()
{
    if (this->State != 0)
        return;
    this->State = 4;
    this->LastScanFrame = 0x7FFFFFFF;
    for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
        SlaveControl* node = this->SlaveNodes.Items[i];
        int state = node->State;
        InfantryClass* slave = node->Slave;
        if (state != 6 && slave != 0)
            slave->CancelAndGoIdle();
    }
}

// SYNTHETIC: GAMEMD 0x6B1390 -- SlaveManagerClass scalar deleting destructor,
// emitted by the compiler from the virtual destructor.

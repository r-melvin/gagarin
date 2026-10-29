// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x6AF580,
//   0x6AF650, 0x6B0D60). Names cross-checked against YRpp
//   every offset reconfirmed numerically from the disassembly.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6AF580  SlaveManagerClass::SetOwner    (__thiscall)
//   FUNCTION: GAMEMD 0x6AF650  SlaveManagerClass::CreateSlave (__thiscall)
//   FUNCTION: GAMEMD 0x6B0D60  SlaveManagerClass::Deploy2     (__thiscall)

#include "slave_manager_class_more_methods.h"

// FUNCTION: GAMEMD 0x6AF580  (__thiscall)
// Re-parent the manager onto NewOwner: clear the old owner's back-pointer,
// destroy any slave-manager already on the new owner (Killed + delete via the
// COM deleting destructor at vtable+0x20), install `this`, then re-stamp the
// master onto every live slave (slave+0x2DC).
void SlaveManagerClass::SetOwner(TechnoView_006AF580* NewOwner)
{
    this->Owner->SlaveManager = 0;
    this->Owner = NewOwner;

    if (NewOwner->SlaveManager) {
        NewOwner->SlaveManager->Killed(0, 0);
        delete NewOwner->SlaveManager;
    }
    NewOwner->SlaveManager = (SlaveManagerHandle*)this;

    for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
        SlaveControl* node = ((SlaveControl**)this->SlaveNodes.Items)[i];
        SlaveObject* slave = node->Slave;
        if (slave)
            slave->SlaveOwner = this->Owner;
    }
}

// FUNCTION: GAMEMD 0x6AF650  (__thiscall)
// Spawn one slave infantry: SlaveType->CreateObject(Owner->GetCoords()). On
// success, init it (vt+0xD4), stamp the master (slave+0x2DC), and fill the
// node (State = Unknown(0), RespawnTimer = CDTimerClass(0)).
void SlaveManagerClass::CreateSlave(SlaveControl* Node)
{
    Node->Slave = this->SlaveType->CreateObject(this->Owner->GetCoords());
    if (Node->Slave) {
        Node->Slave->OnSlaveCreated();
        Node->Slave->SlaveOwner = this->Owner;
        Node->State = 0;
        CDTimerClass timer(0);
        Node->RespawnTimer = timer;
    }
}

// FUNCTION: GAMEMD 0x6B0D60  (__thiscall)
// If Ready (State==0): switch to Working(4), park LastScanFrame at INT_MAX, and
// order every live slave (State != Dead(6), Slave != null) back to Guard via
// vtable+0x3D0, walking SlaveNodes back-to-front.
//
// PARTIAL (84.6%): source intentionally uses ordinary stores after removing volatile
// codegen steering. The prior forced-order full match is not claimed.
void SlaveManagerClass::Deploy2()
{
    if (this->State == 0) {
        this->State = 4;
        this->LastScanFrame = 0x7FFFFFFF;

        for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
            SlaveControl* node = ((SlaveControl**)this->SlaveNodes.Items)[i];
            int state = node->State;
            SlaveObject* slave = node->Slave;
            if (state != 6 && slave != 0)
                slave->GuardSlot();
        }
    }
}

// FUNCTION: GAMEMD 0x6B0490  (__thiscall)
// Order every live slave (State != Dead(6), Slave != null) back to Guard via
// vtable+0x3D0, walking SlaveNodes back-to-front.
void SlaveManagerClass::GuardAllSlaves()
{
    for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
        SlaveControl* node = ((SlaveControl**)this->SlaveNodes.Items)[i];
        int state = node->State;
        SlaveObject* slave = node->Slave;
        if (state != 6 && slave != 0)
            slave->GuardSlot();
    }
}

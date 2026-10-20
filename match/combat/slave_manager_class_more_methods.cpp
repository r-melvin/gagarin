// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x6AF580,
//   0x6AF650, 0x6B0D60). Names cross-checked against YRpp SlaveManagerClass.h
//   (consult-only); every offset reconfirmed numerically from the disassembly.
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
void SlaveManagerClass::SetOwner(TechnoClass* NewOwner)
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
// MATCH: 26/26 exact (100%). Two things were needed, and the earlier note here
// had the second one backwards.
//
// The header stores go through volatile-qualified lvalues. Plain assignments
// let the optimiser hoist the loop-count load above them and sink the State
// store past the `dec`; volatile stores may not be reordered against each
// other, so the pair stays put.
//
// The store order is State then LastScanFrame, which is what retail does
// (`MOV [ESI+0x5c],4` at 0x6B0D6B before `MOV [ESI+0x60],0x7FFFFFFF`). This
// file previously had them the other way round. That was invisible while the
// scheduler was free to reorder them, and only became a real two-instruction
// diff once the volatile qualifiers pinned source order - so the fix exposed
// an ordering fact rather than merely reproducing one.
void SlaveManagerClass::Deploy2()
{
    if (this->State == 0) {
        *(volatile int*)&this->State = 4;
        *(volatile int*)&this->LastScanFrame = 0x7FFFFFFF;

        for (int i = this->SlaveNodes.Count - 1; i >= 0; --i) {
            SlaveControl* node = ((SlaveControl**)this->SlaveNodes.Items)[i];
            int state = node->State;
            SlaveObject* slave = node->Slave;
            if (state != 6 && slave != 0)
                slave->GuardSlot();
        }
    }
}

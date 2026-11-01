// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x6B0C80).
//   Names cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6B0C80  SlaveManagerClass::AllGuard  (__thiscall)

#include "slave_manager_class_methods.h"

// FUNCTION: GAMEMD 0x6B0C80  (__thiscall)
// Reset the manager to Ready (State=0) at the current frame, then order every
// live slave (State != Dead(6), Slave != null) back to Guard via vtable+0x3D0,
// walking the SlaveNodes vector back-to-front.
//
// PARTIAL (79.2%): the residual is the prologue scheduling permutation - the
// optimiser floats the loop-count load to the top and delays the LastScanFrame
// store to cover the global-frame load's latency. Volatile-qualified stores
// that pinned the pair in source order were removed as match steering.
void SlaveManagerView_006B0A20::AllGuard()
{
    State = 0;
    LastScanFrame = CurrentFrame;

    for (int i = SlaveNodes.Count - 1; i >= 0; --i)
    {
        SlaveControl* node = ((SlaveControl**)SlaveNodes.Items)[i];
        int state = node->State;
        SlaveObject* slave = node->Slave;
        if (state != 6 && slave != 0)
            slave->GuardSlot();
    }
}

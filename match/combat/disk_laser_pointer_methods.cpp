// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4A7900.

#include "disk_laser_pointer_methods.h"

// FUNCTION: GAMEMD 0x4A7900  DiskLaserClass::PointerGotInvalid (__thiscall, ret 0x4)
// Two independent tests, one per end of the laser: if the expiring pointer is
// the owner, or the target, the +0x30 handle is reset and the laser queues
// itself for deletion. Both can fire on the same call, so the AddItem is
// expanded twice.
void DiskLaser_004A7900::PointerGotInvalid(void* pInvalid)
{
    if (pInvalid == this->Owner)
    {
        this->unknown_30 = -1;
        DAT_00B0F698.AddItem(this);
    }

    if (pInvalid == this->Target)
    {
        this->unknown_30 = -1;
        DAT_00B0F698.AddItem(this);
    }
}

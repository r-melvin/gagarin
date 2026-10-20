// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5F65F0.

#include "object_class_uninit_methods.h"

// FUNCTION: GAMEMD 0x5F65F0
//
// Retire the object. Disarm an attached bomb; if this is a TechnoClass
// (AbstractFlags bit 0) kill its passengers with no killer; announce the
// pointer as expired so everything referencing it lets go; limbo it through the
// +0xD4 virtual; mark it dead; and queue it on the pending-delete vector, whose
// AddItem (with its virtual SetCapacity growth path) is inlined into the tail.
void ObjectUnInit::UnInit()
{
    if (this->AttachedBomb != 0)
        ((UnInitBomb*)this->AttachedBomb)->Disarm();

    if (this != 0 && (this->AbstractFlags & 1))
        this->KillPassengers(0);

    this->AnnounceExpiredPointer(1);
    (this->*(*(UnInitVtbl**)this)->Limbo)();
    this->IsAlive = 0;

    PendingDeleteObjects.AddItem(this);
}

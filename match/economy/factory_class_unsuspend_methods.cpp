// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes matched against retail gamemd.exe v1.001 at 0x4C9EA0.

#include "factory_class_unsuspend_methods.h"

// Build time in frames: the object's TimeToBuild() (0 when none) / 54, clamped
// to [1, 255].  Inlined by retail (out-of-line twin at 0x4C9FB0).
inline int Factory_004C9EA0::GetBuildTimeFrames() const
{
    int cost = 0;
    if (this->Object) {
        cost = this->Object->TimeToBuild();
    }
    int frames = cost / 54;
    if (frames < 1) {
        frames = 1;
    } else if (frames > 255) {
        frames = 255;
    }
    return frames;
}

// Credits owed per remaining production step; 0 when nothing is being built.
inline int Factory_004C9EA0::CostPerTick() const
{
    if (this->Object) {
        int steps = 54 - this->Production.Value;
        if (steps) {
            return this->Balance / steps;
        }
        return this->Balance;
    }
    return 0;
}

// Suspend production (no-op when already suspended).  Inlined by retail
// (out-of-line twin at 0x4C9E60).
inline bool Factory_004C9EA0::Suspend(bool manual)
{
    if (!this->IsSuspended) {
        this->IsManual = manual;
        this->IsSuspended = true;
        this->Production.Start(0);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4C9EA0
//
// Resume a suspended production.  Requires something to build (an object or a
// special item), the suspended state, and an unfinished stage.  Restarts the
// progress timer at the build rate, then bails (leaving the factory
// unsuspended) when the owner cannot afford the next tick; otherwise flags the
// resume as manual and, when asked, immediately re-suspends manually.
bool Factory_004C9EA0::Unsuspend(bool manual)
{
    Techno_004C9EA0* obj = this->Object;
    if ((obj || this->SpecialItem)
        && this->IsSuspended
        && !(obj && this->Production.Value == 54)
        && !(this->SpecialItem != -1 && this->Production.Value == 54)) {
        this->IsSuspended = false;
        this->Production.Start(this->GetBuildTimeFrames());
        int cost = this->CostPerTick();
        IHouse_004C9EA0* house = &this->Owner->IHouse;
        if ((*house->Vtbl->Available_Money)(house) >= cost) {
            this->IsManual = true;
            if (manual) {
                this->Suspend(true);
            }
            return true;
        }
    }
    return false;
}

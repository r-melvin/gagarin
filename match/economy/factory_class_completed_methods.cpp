// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4CA1A0. Method name
//   from the consult-only YRpp FactoryClass.h (name only).

#include "factory_class_completed_methods.h"

// FUNCTION: GAMEMD 0x4CA1A0
//
// Called once the produced item has been placed. If a real object is in
// production and the progress stage has reached its final step (0x36), the
// object slot is released, the factory is suspended and flagged changed, and
// the progress stage is reset (Value = 0, then Rate/Timer restarted at 0).
// The same happens for a special-weapon item, whose slot is cleared to -1
// instead. Reports whether anything was completed.
bool FactoryClass::CompletedProduction()
{
    if (this->Object != 0 && this->Production.Value == 0x36) {
        this->Object = 0;
        this->IsSuspended = true;
        this->IsDifferent = true;
        this->Production.Value = 0;
        this->Production.Start(0);
        return true;
    }

    if (this->SpecialItem != 0 && this->Production.Value == 0x36) {
        this->SpecialItem = -1;
        this->IsSuspended = true;
        this->IsDifferent = true;
        this->Production.Value = 0;
        this->Production.Start(0);
        return true;
    }

    return false;
}

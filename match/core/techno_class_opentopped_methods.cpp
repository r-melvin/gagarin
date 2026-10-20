// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x710470.

#include "techno_class_opentopped_methods.h"

// FUNCTION: GAMEMD 0x710470  TechnoClass::EnteredOpenTopped (__thiscall, ret 0x4)
// A passenger boarding an open-topped transport stays visible and keeps firing,
// so it is flagged, given its own per-entry notification, and pushed onto the
// global logic list. `this` (the transport) is never touched.
void TechnoClass::EnteredOpenTopped(TechnoClass* who)
{
    if (who != 0) {
        who->InOpenToppedTransport = true;
        TECHNO_SLOT_3D0(who);
        LogicInstance.AddObject(who, false);
    }
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x5581A0; GaugeClass layout in ui_gadget.h.
#include "controls_views.h"

// FUNCTION: GAMEMD 0x5581A0
// GaugeClass copy constructor: copy the control part, then the flags, range and value fields.
GaugeClass::GaugeClass(const GaugeClass& other)
    : ControlClass(other), unknown_2C(other.unknown_2C), unknown_2D(other.unknown_2D),
      unknown_2E(other.unknown_2E), Maximum(other.Maximum), Value(other.Value), unknown_38(other.unknown_38)
{
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41B7D0.
//   IFlyControl query on AircraftClass (see abstract_class_forward_methods.cpp
//   for the neighbouring slots).
#include "../_layout/abstract_class.h"
#include "../_layout/aircraft_class.h"

// FUNCTION: GAMEMD 0x0041B7D0
// Whether the aircraft is carrying anyone.
int __stdcall AircraftClass::vf_05()
{
    bool has = Passengers.FirstPassenger != 0;
    return has;
}

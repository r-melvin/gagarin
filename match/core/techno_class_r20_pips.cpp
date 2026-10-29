// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm of each
//   address below). Lies inside the Techno.CPP code range 0x6F28A0-0x7108DF.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x708C30   TechnoClass::vf_174

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/capture_manager_class.h"

// FUNCTION: GAMEMD 0x708C30
// Number of filled pips: the held amount for the type's pip scale (ammo,
// stored tiberium, passengers or mind-controlled units) as a fraction of its
// maximum, scaled by the type's slot 29 value and rounded; at least 1 when
// anything is held.
int TechnoClass::vf_174()
{
    double value;
    double limit;
    switch (vf_33()->PipScale) {
    case 1:
        value = Ammo;
        limit = vf_33()->vf_29();
        break;
    case 5:
        if (!CaptureManager) {
            return 0;
        }
        value = ((CaptureManagerClass*)CaptureManager)->GetControlledCount();
        limit = vf_33()->vf_29();
        break;
    case 3:
        value = Passengers.NumPassengers;
        limit = vf_33()->vf_29();
        break;
    case 2:
        value = Tiberium.GetTotalAmount();
        limit = vf_33()->Storage;
        break;
    default:
        return 0;
    }
    int pips = (int)(value / limit * vf_33()->vf_29() + 0.5);
    if (pips == 0 && value > 0.0) {
        pips = 1;
    }
    return pips;
}

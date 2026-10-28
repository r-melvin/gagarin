// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Two TechnoClass virtuals that forward to the object's type, read off retail
//   gamemd.exe v1.001. Functions are in ascending retail address order.

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"

// FUNCTION: GAMEMD 0x6F3270
// The techno type: slot 34 viewed as the derived type class.
TechnoTypeClass* TechnoClass::vf_33()
{
    return static_cast<TechnoTypeClass*>(vf_34());
}

// FUNCTION: GAMEMD 0x708B30
int TechnoClass::vf_35()
{
    return vf_33()->vf_28();
}

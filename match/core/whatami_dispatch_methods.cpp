// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x40DD20 and 0x40DD70.

#include "whatami_dispatch_methods.h"
#include "../_layout/techno_class.h"

// FUNCTION: GAMEMD 0x40DD20
WhatAmIHolder* FUN_0040DD20(WhatAmIHolder* self)
{
    if (!self) {
        return 0;
    }

    switch (self->WhatAmI()) {
    case 1:
    case 2:
    case 6:
        return self;
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        return 0;
    case 15:
        return self;
    }

    return 0;
}

// FUNCTION: GAMEMD 0x40DD70
TechnoClass* FUN_0040DD70(AbstractClass* object)
{
    if (!object) {
        return 0;
    }

    switch (object->vf_11()) {
    case 1:
    case 2:
    case 6:
    case 15:
        return static_cast<TechnoClass*>(object);
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    default:
        return 0;
    }
}

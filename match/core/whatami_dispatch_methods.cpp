// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x40DD20 and 0x40DD70.

#include "whatami_dispatch_methods.h"

// FUNCTION: GAMEMD 0x40DD20
WhatAmIHolder* __fastcall FUN_0040DD20(WhatAmIHolder* self)
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
    case 15:
        return 0;
    }

    return 0;
}

// FUNCTION: GAMEMD 0x40DD70
WhatAmIHolder* __fastcall FUN_0040DD70(WhatAmIHolder* self)
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
    case 15:
        return 0;
    }

    return 0;
}

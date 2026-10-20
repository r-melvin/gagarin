// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The four defaulting accessors, ordered ascending by retail address.

#include "member_or_default_sweep.h"

// FUNCTION: GAMEMD 0x7B5400
// GLOBAL: GAMEMD 0x889F64
void* __fastcall FUN_007B5400(DefaultingHolder* self)
{
    if (self->Object != 0) {
        return self->Object;
    }

    return GLOBAL_00889F64;
}

// FUNCTION: GAMEMD 0x7B5440
// GLOBAL: GAMEMD 0x889F64
void* __fastcall FUN_007B5440(DefaultingHolder* self)
{
    if (self->Object != 0) {
        return self->Object;
    }

    return GLOBAL_00889F64;
}

// FUNCTION: GAMEMD 0x7B7100
// GLOBAL: GAMEMD 0x887734
void* __fastcall FUN_007B7100(DefaultingHolder* self)
{
    if (self->Object != 0) {
        return self->Object;
    }

    return GLOBAL_00887734;
}

// FUNCTION: GAMEMD 0x7B7140
// GLOBAL: GAMEMD 0x887734
void* __fastcall FUN_007B7140(DefaultingHolder* self)
{
    if (self->Object != 0) {
        return self->Object;
    }

    return GLOBAL_00887734;
}


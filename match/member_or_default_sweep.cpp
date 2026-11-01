// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The remaining defaulting accessors, ordered ascending by retail address.

#include "member_or_default_sweep.h"
#include "string_class.h"

// FUNCTION: GAMEMD 0x7B5440
// GLOBAL: GAMEMD 0x889F64
const char* Wstring::FUN_007B5440() const
{
    if (unknown_00 != 0) {
        return unknown_00;
    }
    return GLOBAL_00889F64;
}

// FUNCTION: GAMEMD 0x7B7100
// GLOBAL: GAMEMD 0x887734
void* FUN_007B7100(DefaultingHolder* self)
{
    if (self->Object != 0) {
        return self->Object;
    }

    return GLOBAL_00887734;
}

// FUNCTION: GAMEMD 0x7B7140
// GLOBAL: GAMEMD 0x887734
void* FUN_007B7140(DefaultingHolder* self)
{
    if (self->Object != 0) {
        return self->Object;
    }

    return GLOBAL_00887734;
}


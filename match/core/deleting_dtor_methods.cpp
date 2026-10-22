// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address. The four deleting destructors are
// byte-identical apart from their destructor call target and are written out
// longhand rather than macro-generated, per the family rule.

#include "deleting_dtor_methods.h"
#include "../_layout/ini_class.h"

// FUNCTION: GAMEMD 0x408E00
void Obj_00408E00::FUN_00408E00()
{
    if (unknown_10) {
        FUN_007C8B3D(unknown_10);
    }

    FUN_007C8B3D(this);
}

// FUNCTION: GAMEMD 0x40E4A0
void* Obj_0040E400::FUN_0040E4A0(unsigned int flags)
{
    static_cast<INIClass*>(static_cast<void*>(this))->INIClass::~INIClass();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x41C210
void* AircraftClass_0041C200b::FUN_0041C210(unsigned int flags)
{
    FUN_00414080(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x426590
void* AnimClass_00426500::FUN_00426590(unsigned int flags)
{
    FUN_004228E0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x46B5C0
void* Obj_0046B500::FUN_0046B5C0(unsigned int flags)
{
    FUN_00466560(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x473920
void* Obj_00473900::FUN_00473920(unsigned int flags)
{
    FUN_005565A0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

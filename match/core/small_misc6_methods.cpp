// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc6_methods.h"

// FUNCTION: GAMEMD 0x401190
// The field is taken as a 16.16 fixed-point value: only its high half is used
// (`SHR ECX,0x10`, an unsigned shift), scaled, then divided by 100.
int __fastcall Obj_00401100::FUN_00401190(int value) const
{
    return (int)(unknown_2C >> 16) * value / 100;
}

// FUNCTION: GAMEMD 0x408540
int Obj_00408500c::FUN_00408540(int value, int) const
{
    return unknown_14 * value / 1000;
}

// FUNCTION: GAMEMD 0x42E410
Obj_0042E410* Obj_0042E410::FUN_0042E410(int w, int x, int y, int z)
{
    a = w;
    b = x;
    c = y;
    d = z;

    return this;
}

// FUNCTION: GAMEMD 0x432BD0
void Obj_00432BD0::FUN_00432BD0(int frame)
{
    BinkGoto(Bink, frame, 1);

    unknown_30 = 0;
}

// FUNCTION: GAMEMD 0x437030
bool Obj_00437030::FUN_00437030()
{
    if (FUN_005F4D30(this)) {
        DAT_0087F778.FUN_0055BAE0(this);
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x43A0D0
Vec3f* Vec3f::FUN_0043A0D0(float s)
{
    x = s * x;
    y = s * y;
    z = s * z;

    return this;
}

// FUNCTION: GAMEMD 0x43A100
Vec3f* Vec3f::FUN_0043A100(const Vec3f* other)
{
    x = other->x + x;
    y = other->y + y;
    z = other->z + z;

    return this;
}

// FUNCTION: GAMEMD 0x43A130
double Vec3f::FUN_0043A130() const
{
    return FUN_004CAC40(x * x + y * y + z * z);
}

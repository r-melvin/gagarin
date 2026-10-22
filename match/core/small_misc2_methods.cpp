// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc2_methods.h"

// FUNCTION: GAMEMD 0x405BE0
void Obj_00405B00::FUN_00405BE0()
{
    unknown_0C = DAT_0087E294;
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_08 = 0;
}

// FUNCTION: GAMEMD 0x406650
// True only when the flag is set *and* the pointer is clear.
int Obj_00406600b::FUN_00406650() const
{
    return (Flags & 1) && unknown_4C == 0;
}

// FUNCTION: GAMEMD 0x407150
// `SHL EDX,0x10` puts the value in the high half of the word.
void Obj_00407100::FUN_00407150(int value)
{
    Flags |= 1;
    unknown_08 = value << 16;
}

// FUNCTION: GAMEMD 0x4072D0
void Obj_004072D0::FUN_004072D0()
{
    a = this;
    b = this;
    c = 0;
}

// FUNCTION: GAMEMD 0x40A940
void __cdecl FUN_0040A940b()
{
    if (DAT_0087E8A0) {
        IFACE_CALL(DAT_0087E8A0, 0x48);
    }
}

// FUNCTION: GAMEMD 0x433040
void Obj_00433000::FUN_00433040()
{
    FUN_00432E40(unknown_0C, unknown_10, unknown_14);
}

// FUNCTION: GAMEMD 0x473960
const char* FUN_00473960(unsigned int index)
{
    if (index < 11) {
        return DAT_0081B7CC[index].Name;
    }

    return STR_00817474b;
}

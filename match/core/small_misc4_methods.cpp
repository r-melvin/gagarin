// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc4_methods.h"

// FUNCTION: GAMEMD 0x407040
// Release. Nothing happens at zero, and the teardown runs only on the
// transition to zero - a second release of an already-idle count is inert.
void __cdecl FUN_00407040()
{
    if (DAT_0087E730 != 0) {
        if (--DAT_0087E730 == 0) {
            FUN_0040A950();
        }
    }
}

// FUNCTION: GAMEMD 0x408080
void __fastcall Obj_00408080::FUN_00408080(int fill)
{
    FUN_007C91D0(Buffer, fill, sizeof(Buffer));

    Buffer[sizeof(Buffer) - 1] = 0;
}

// FUNCTION: GAMEMD 0x4080D0
// True when the flag is set and the inner pair disagree.
int Obj_00408000c::FUN_004080D0() const
{
    return (Flags & 1) && unknown_14->at14 != unknown_14->at18;
}

// FUNCTION: GAMEMD 0x4085E0
void __fastcall Obj_004085E0::FUN_004085E0(int a, int b)
{
    unknown_10 = b;
    unknown_0C = a;

    FUN_004072D0b(this);

    unknown_14 = 0;
}

// FUNCTION: GAMEMD 0x4101F0
void Obj_004101F0::FUN_004101F0()
{
    vt0 = VT_007E1F50;
    vt1 = VT_007E1F34;
    vt2 = VT_007E1F2C;
    vt3 = VT_007E1F24;
}

// FUNCTION: GAMEMD 0x458DB0
bool BuildingClass_00458DB0::FUN_00458DB0()
{
    if (SLOT_400(this)) {
        return true;
    }

    return FUN_00701120(this);
}

// BLOCK-ORDER DELTA (status partial, 41.7% - 5/12). Retail branches *into* the
// call (`JNZ` to a block placed after an earlier `POP ESI; RET`), so the
// function carries two epilogues with the call block out of line. We emit one
// epilogue and the call inline, which is what VC6 does for a plain `if` and for
// the inverted early-return form alike. Both were tried.
// Lift pass (2026-09-18): re-tried `if (!FUN_00465D40(...)) return;` and an
// explicit `goto notify;` layout that spells retail's block order literally -
// both 41.7% with a byte-identical stream. cl 8804 always cross-jumps the two
// two-instruction `POP ESI; RET` epilogues into one; retail (8447) keeps both.
// Recording as an 8447-vs-8804 cross-jump difference, not chased further.
// FUNCTION: GAMEMD 0x459C00
void BuildingClass_00459C00::FUN_00459C00()
{
    if (FUN_00465D40(unknown_520)) {
        FUN_006FC030(this);
    }
}

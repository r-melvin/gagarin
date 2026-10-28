// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu065_methods.h"

// FUNCTION: GAMEMD 0x4A5090
// Empty function.
void __cdecl FUN_004A5090()
{
}

// FUNCTION: GAMEMD 0x4A5950
// Member getter (dword).
int Obj_004A5950::FUN_004A5950() const
{
    return unknown_B4;
}

// The object seen as a bare vtable pointer; only slot 18 is called.
struct Vtbl_004A5960;
struct Obj_004A5960View
{
    Vtbl_004A5960* Vtbl;
};
typedef void (Obj_004A5960View::*Slot18_004A5960)();
struct Vtbl_004A5960
{
    char            _pad000[0x48];
    Slot18_004A5960 At_48;      // +0x48
};

// FUNCTION: GAMEMD 0x4A5960
// Store the raw word, move its low byte into the high byte of the direction,
// reduce that to one of eight facings in both facing members, then refresh
// through virtual slot 18.
void Obj_004A5950::FUN_004A5960(DirWord_004A5960 dir)
{
    unknown_B4 = *(int*)&dir;
    dir.Raw = (unsigned short)(dir.Low << 8);
    int f = (((unsigned)*(int*)&dir >> 12) + 1 >> 1) & 7;
    unknown_B8 = f;
    unknown_BC = f;
    Obj_004A5960View* v = (Obj_004A5960View*)this;
    (v->*v->Vtbl->At_48)();
}

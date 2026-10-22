// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu237_methods.h"

// FUNCTION: GAMEMD 0x6F60C0
// Empty function that pops its stack arguments. Vtable slot 274 of TechnoClass (RTTI) and 5 derived vtable(s).
void Obj_006F60C0::FUN_006F60C0(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x6F9DB0
// Member getter (dword). Vtable slot 14 of TechnoClass (RTTI) and 5 derived vtable(s).
int Obj_006F9DB0::FUN_006F9DB0() const
{
    return unknown_21C->unknown_30;
}

// FUNCTION: GAMEMD 0x6F9DC0
// Member getter (dword). Vtable slot 15 of TechnoClass (RTTI) and 5 derived vtable(s).
int Obj_006F9DC0::FUN_006F9DC0() const
{
    return unknown_21C;
}

// FUNCTION: GAMEMD 0x6FC090
// Calls other functions. Vtable slot 239 of TechnoClass (RTTI) and 5 derived vtable(s).
void Obj_006FC090::FUN_006FC090(int a1, int a2)
{
    vf_240(a1, a2, 0);
}

// FUNCTION: GAMEMD 0x6FF950
// Empty function.
void __cdecl FUN_006FF950()
{
}

// FUNCTION: GAMEMD 0x701190
// Returns a constant boolean. Vtable slot 212 of TechnoClass (RTTI) and 4 derived vtable(s).
bool Obj_00701190::FUN_00701190() const
{
    return false;
}

// FUNCTION: GAMEMD 0x703850
// Calls other functions. Vtable slot 63 of TechnoClass (RTTI) and 5 derived vtable(s).
void Obj_00703850::FUN_00703850()
{
    vf_279(0);
}

// FUNCTION: GAMEMD 0x705D30
// Branching.
unsigned char Obj_00705D30::FUN_00705D30()
{
    if (unknown_514 == 0)
    {
        return 0;
    }
    return (unknown_514->FUN_00636DC0() > 0) ? true : false;
}

// FUNCTION: GAMEMD 0x705D50
// Calls other functions. Vtable slot 268 of TechnoClass (RTTI) and 4 derived vtable(s).
bool Obj_00705D50::FUN_00705D50()
{
    return (vf_118() == 0) ? true : false;
}

// FUNCTION: GAMEMD 0x709460
// Branching.
int __stdcall FUN_00709460(int a1)
{
    return a1 != 5 && a1 != 6 && a1 != 8;
}

// FUNCTION: GAMEMD 0x7094E0
// Branching.
int Obj_007094E0::FUN_007094E0()
{
    return unknown_AC == 2 || unknown_AC == 0xA || unknown_AC == 5;
}

// FUNCTION: GAMEMD 0x709800
// Branching.
int __stdcall FUN_00709800(int a1)
{
    return a1 != 5 && a1 != 6;
}

// FUNCTION: GAMEMD 0x7099D0
// Returns zero; pops its stack arguments. Vtable slot 64 of TechnoClass (RTTI) and 3 derived vtable(s).
int Obj_007099D0::FUN_007099D0(int a1, int a2) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x709A20
// Empty function that pops its stack arguments. Vtable slot 287 of TechnoClass (RTTI) and 1 derived vtable(s).
void Obj_00709A20::FUN_00709A20(int a1)
{
}

// FUNCTION: GAMEMD 0x70C5B0
// Member getter (byte). Vtable slot 117 of TechnoClass (RTTI) and 5 derived vtable(s).
unsigned char Obj_0070C5B0::FUN_0070C5B0() const
{
    return unknown_270;
}

// FUNCTION: GAMEMD 0x70C5C0
// Member getter (byte). Vtable slot 118 of TechnoClass (RTTI) and 5 derived vtable(s).
unsigned char Obj_0070C5C0::FUN_0070C5C0() const
{
    return unknown_271;
}

// FUNCTION: GAMEMD 0x70C5D0
// Branching. Vtable slot 119 of TechnoClass (RTTI) and 5 derived vtable(s).
bool Obj_0070C5D0::FUN_0070C5D0()
{
    if (unknown_274 == 0 || unknown_274->unknown_28 == 0)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x70C5F0
// Branching. Vtable slot 120 of TechnoClass (RTTI) and 5 derived vtable(s).
bool Obj_0070C5F0::FUN_0070C5F0()
{
    if (unknown_270 != 0 || unknown_271 != 0)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x70CCF0
// Calls other functions. Vtable slot 295 of TechnoClass (RTTI) and 4 derived vtable(s).
void FUN_0070CCF0(int a1, int a2)
{
    FUN_006562D0(DAT_0087F7E8, a2, a1 + 0x208);
}

// FUNCTION: GAMEMD 0x70D670
// Branching. Vtable slot 228 of TechnoClass (RTTI) and 4 derived vtable(s).
int Obj_0070D670::FUN_0070D670()
{
    int t1 = unknown_2FC;
    if (t1 > 0)
    {
        unknown_2FC = t1 - 1;
        return t1 - 1;
    }
    return t1;
}

// FUNCTION: GAMEMD 0x70D980
// Empty function. Vtable slot 184 of TechnoClass (RTTI) and 4 derived vtable(s).
void Obj_0070D980::FUN_0070D980()
{
}

// FUNCTION: GAMEMD 0x70DCE0
// Returns a comparison result.
bool Obj_0070DCE0::FUN_0070DCE0() const
{
    return unknown_124 != -1;
}

// FUNCTION: GAMEMD 0x70DD90
// Returns a constant. Vtable slot 250 of TechnoClass (RTTI) and 5 derived vtable(s).
int Obj_0070DD90::FUN_0070DD90() const
{
    return 1;
}

// FUNCTION: GAMEMD 0x70DE20
// Updates one member in place.
void Obj_0070DE20::FUN_0070DE20(int a1)
{
    unknown_144 += a1;
}

// FUNCTION: GAMEMD 0x70F000
// Member getter (byte sx); pops its stack arguments. Vtable slot 297 of TechnoClass (RTTI) and 1 derived vtable(s).
int Obj_0070F000::FUN_0070F000(Arg1_0070F000* a1) const
{
    return a1->unknown_0C;
}

// FUNCTION: GAMEMD 0x70F010
// Empty function. Vtable slot 298 of TechnoClass (RTTI) and 1 derived vtable(s).
void Obj_0070F010::FUN_0070F010()
{
}

// FUNCTION: GAMEMD 0x70F020
// Returns a constant boolean. Vtable slot 299 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F020::FUN_0070F020() const
{
    return false;
}

// FUNCTION: GAMEMD 0x70F030
// Returns a constant boolean. Vtable slot 300 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F030::FUN_0070F030() const
{
    return false;
}

// FUNCTION: GAMEMD 0x70F0E0
// Returns a constant boolean. Vtable slot 305 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F0E0::FUN_0070F0E0() const
{
    return false;
}

// FUNCTION: GAMEMD 0x70F0F0
// Returns a constant boolean. Vtable slot 306 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F0F0::FUN_0070F0F0() const
{
    return false;
}

// FUNCTION: GAMEMD 0x70F100
// Empty function. Vtable slot 307 of TechnoClass (RTTI) and 1 derived vtable(s).
void Obj_0070F100::FUN_0070F100()
{
}

// FUNCTION: GAMEMD 0x70F110
// Returns a constant boolean. Vtable slot 308 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F110::FUN_0070F110() const
{
    return false;
}

// FUNCTION: GAMEMD 0x70FE40
// Stores its argument in a member; pops its stack arguments.
void Obj_0070FE40::FUN_0070FE40(int a1)
{
    unknown_1D0 = a1;
}

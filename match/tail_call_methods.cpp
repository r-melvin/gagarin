// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Tail-call forwarders, ordered ascending by retail address.

// 0x4080C0 passes [ECX+0x14]+0x10 to timer entry 0x407170.
#include "tail_call_methods.h"

// FUNCTION: GAMEMD 0x4026A0
void Obj_00402600::FUN_004026A0() { (*(Slot*)(Dispatch + 0x28))(this); }

// FUNCTION: GAMEMD 0x4026B0
void Obj_00402600::FUN_004026B0() { (*(Slot*)(Dispatch + 0x2C))(this); }

// FUNCTION: GAMEMD 0x403810
void Obj_00403800b::FUN_00403810() { Handler(this); }

// FUNCTION: GAMEMD 0x407070
unsigned FUN_00407070(Timer_00401000* self) { return FUN_00407170(self, 0); }

// FUNCTION: GAMEMD 0x4080C0
void Obj_00408000b::FUN_004080C0() { FUN_00407170(reinterpret_cast<Timer_00401000*>(unknown_14 + 0x10), 0); }

// FUNCTION: GAMEMD 0x4084E0
void Obj_00408500b::FUN_004084E0()
{
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_14 = 0;
    unknown_18 = 0;

    FUN_004072C0b((char*)this + 8);
}

// FUNCTION: GAMEMD 0x408520
void Obj_00408500b::FUN_00408520() { FUN_00407470((char*)this + 8); }

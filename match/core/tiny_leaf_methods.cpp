// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "tiny_leaf_methods.h"

// FUNCTION: GAMEMD 0x4065F0
void Obj_00406500b::FUN_004065F0(int value) { unknown_54 = value; }

// FUNCTION: GAMEMD 0x406600
void Obj_00406500b::FUN_00406600(int a, int b) { unknown_58 = a; unknown_5C = b; }

// FUNCTION: GAMEMD 0x406610
void Obj_00406500b::FUN_00406610(int a, int b) { unknown_60 = a; unknown_64 = b; }

// FUNCTION: GAMEMD 0x4068E0
void __cdecl FUN_004068E0() { }

// FUNCTION: GAMEMD 0x4072C0
// Close the head onto itself: an empty circular list points at its own header
// in all three words rather than holding nulls.
void ListHead3::FUN_004072C0() { a = this; b = this; c = this; }

// FUNCTION: GAMEMD 0x407510
void FUN_00407510(void* self) { FUN_007C8B3D(self); }

// FUNCTION: GAMEMD 0x407530
void FUN_00407530(FreeHead2* head, void* payload)
{
    void** node = (void**)((char*)payload - 8);

    *node = head->First;
    head->First = node;
}

// FUNCTION: GAMEMD 0x407B40
void Obj_00407B00::FUN_00407B40(int value) { unknown_14->at94 = value; }

// FUNCTION: GAMEMD 0x407B50
void Obj_00407B00::FUN_00407B50(int value) { unknown_14->at9C = value; }

// FUNCTION: GAMEMD 0x408140
__int64 Obj_00408100::FUN_00408140() const
{
    return *(const __int64*)&unknown_20;
}

// FUNCTION: GAMEMD 0x408530
void __cdecl FUN_00408530() { }

// FUNCTION: GAMEMD 0x40D300
void __cdecl FUN_0040D300() { }

// FUNCTION: GAMEMD 0x410220
int __stdcall FUN_00410220(Obj_00410200* obj) { return obj->unknown_0C; }

// FUNCTION: GAMEMD 0x434110
void Obj_00434100::FUN_00434110(int value) { unknown_20 = value; }

// FUNCTION: GAMEMD 0x454CE0
void __cdecl FUN_00454CE0() { }

// FUNCTION: GAMEMD 0x45E750
void __cdecl FUN_0045E750() { }

// FUNCTION: GAMEMD 0x465CB0
void __cdecl FUN_00465CB0() { }
